/* trackuino copyright (C) 2010  EA5HAV Javi
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
#include "ch.h"
#include "hal.h"
#include "ax25.h"
#include "config.h"
#include "debug.h"

#define AX25_WRITE_BIT(data, size) { \
	data[size >> 3] |= (1 << (size & 7)); \
}
#define AX25_CLEAR_BIT(data, size) { \
	data[size >> 3] &= ~(1 << (size & 7)); \
}


static void update_crc(ax25_t *packet, char bit)
{
	packet->crc ^= bit;
	if(packet->crc & 1)
		packet->crc = (packet->crc >> 1) ^ 0x8408;  // X-modem CRC poly
	else
		packet->crc = packet->crc >> 1;
}

uint32_t state;
uint8_t scramble_bit(uint8_t _in) {
	uint8_t _out = (_in ^ (state >> 16) ^ (state >> 11)) & 0x1;
	state = ((state << 0x1) | (_in & 0x1));
	return _out;
}

static void send_byte(ax25_t *packet, char byte)
{
	int i;
	for(i = 0; i < 8; i++) {
		update_crc(packet, (byte >> i) & 1);
		if((byte >> i) & 1) {
			// Next bit is a '1'
			if (packet->size >= packet->max_size * 8)  // Prevent buffer overrun
				return;

			AX25_WRITE_BIT(packet->data, packet->size);

			packet->size++;
			packet->ones_in_a_row++;
			if(packet->ones_in_a_row < 5)
				continue;
		}
		// Next bit is a '0' or a zero padding after 5 ones in a row
		if(packet->size >= packet->max_size * 8)    // Prevent buffer overrun
			return;

		AX25_CLEAR_BIT(packet->data, packet->size);

		packet->size++;
		packet->ones_in_a_row = 0;
	}
}

// Exported functions
void ax25_send_byte(ax25_t *packet, char byte)
{
  // Wrap around send_byte, but prints debug info
  send_byte(packet, byte);
}

void ax25_send_sync(ax25_t *packet)
{
	unsigned char byte = 0x00;
	int i;
	for(i = 0; i < 8; i++, packet->size++) {
		if(packet->size >= packet->max_size * 8)  // Prevent buffer overrun
			return;
		if ((byte >> i) & 1)
			packet->data[packet->size >> 3] |= (1 << (packet->size & 7));
		else
			packet->data[packet->size >> 3] &= ~(1 << (packet->size & 7));
	}
}

void ax25_send_flag(ax25_t *packet)
{
  unsigned char byte = 0x7e;
  int i;
  for (i = 0; i < 8; i++, packet->size++) {
    if (packet->size >= packet->max_size * 8)  // Prevent buffer overrun
      return;
    if ((byte >> i) & 1)
      packet->data[packet->size >> 3] |= (1 << (packet->size & 7));
    else
      packet->data[packet->size >> 3] &= ~(1 << (packet->size & 7));
  }
}

void ax25_send_string(ax25_t *packet, const char *string)
{
	int i;
	for (i = 0; string[i]; i++) {
		ax25_send_byte(packet, string[i]);
	}
}

void ax25_send_header(ax25_t *packet, const s_address_t addresses[], int num_addresses)
{
	int i, j;
	packet->size = 0;
	packet->ones_in_a_row = 0;
	packet->crc = 0xffff;

	for(uint16_t t=0; t<512; t++) // TMP blanking
		packet->data[t] = 0;

	// Send sync ("a bunch of 0s")
	for (i = 0; i < AFSK_TXDELAY; i++)
	{
		ax25_send_sync(packet);
	}

	//start the actual frame. Send 3 of them (one empty frame and the real start)
	for (i = 0; i < 4; i++)
	{
		ax25_send_flag(packet);
	}

	//start the actual frame. Send 3 of them (one empty frame and the real start)
	for (i = 0; i < 4; i++)
	{
		ax25_send_flag(packet);
	}

	for (i = 0; i < num_addresses; i++) {
		// Transmit callsign
		for (j = 0; addresses[i].callsign[j]; j++) {
			send_byte(packet, addresses[i].callsign[j] << 1);
		}
		// Transmit pad
		for ( ; j < 6; j++)
			send_byte(packet, ' ' << 1);
		// Transmit SSID. Termination signaled with last bit = 1
		if (i == num_addresses - 1)
			send_byte(packet, ('0' + addresses[i].ssid) << 1 | 1);
		else
			send_byte(packet, ('0' + addresses[i].ssid) << 1);
	}

	// Control field: 3 = APRS-UI frame
	send_byte(packet, 0x03);

	// Protocol ID: 0xf0 = no layer 3 data
	send_byte(packet, 0xf0);
}

void ax25_send_footer(ax25_t *packet)
{
	// Save the crc so that it can be treated it atomically
	uint16_t final_crc = packet->crc;

	// Send CRC
	send_byte(packet, ~(final_crc & 0xff));
	final_crc >>= 8;
	send_byte(packet, ~(final_crc & 0xff));

	packet->crc = final_crc;

	// Signal the end of frame
	for (uint8_t i = 0; i < 4; i++)
	{
		ax25_send_flag(packet);
	}
}

/**
  * Scrambling for 2GFSK
  */
void scramble(ax25_t *packet) {
	// Scramble
	state = 0x0;
	for(uint32_t i=AFSK_TXDELAY*8+32; i<packet->size; i++) {
		uint8_t bit = scramble_bit((packet->data[i >> 3] >> (i & 0x7)) & 0x1);
		if(bit) {
			AX25_WRITE_BIT(packet->data, i);
		} else {
			AX25_CLEAR_BIT(packet->data, i);
		}
	}
}

/**
  * NRZ-I tone encoding (0: bit change, 1: no bit change)
  */
void nrzi_encode(ax25_t *packet) {
	uint8_t ctone = 0;
	for(uint32_t i=0; i<packet->size; i++) {
		if(((packet->data[i >> 3] >> (i & 0x7)) & 0x1) == 0)
			ctone = !ctone;
		if(ctone) {
			AX25_WRITE_BIT(packet->data, i);
		} else {
			AX25_CLEAR_BIT(packet->data, i);
		}
	}
}














