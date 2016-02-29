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

// Module globals
uint16_t crc;
uint8_t ones_in_a_row;

// TODO: Move the 2 following variables to heap in order to make multiple access to all functions possible
uint8_t modem_packet[MODEM_MAX_PACKET];  // Upper layer data
uint16_t modem_packet_size;              // in bits

// Module functions
static void update_crc(unsigned char bit)
{
	crc ^= bit;
	if (crc & 1)
		crc = (crc >> 1) ^ 0x8408;  // X-modem CRC poly
	else
		crc = crc >> 1;
}



static uint8_t old_out[17];

void *my_memmove(void *dest, const void *src, size_t n) {
  int8_t operation;
  size_t end;
  size_t current;

  if(dest != src) {
    if(dest < src) {
      operation = 1;
      current = 0;
      end = n;
    } else {
      operation = -1;
      current = n - 1;
      end = -1;
    }

    for( ; current != end; current += operation) {
      *(((uint8_t*)dest) + current) = *(((uint8_t*)src) + current);
    }
  }
  return dest;
}

// @see http://www.dtusat.dtu.dk/cgi-bin/viewcvs.cgi/dtusat/pro/physical/Attic/scramble.c?rev=1.6&content-type=text/vnd.viewcvs-markup

// perform descrambling one bit at a time
uint8_t scramble_bitwise(uint8_t bit) {
	bit ^= 1 ^ old_out[12-1] ^ old_out[17-1];

	// update old_out buffer
	my_memmove(&old_out[1], old_out, 16);
	old_out[0] = bit;

	return bit;
}

// naive bitwise G3RUH scrambling
void bit_scramble(void) {
	uint8_t bit;
	uint32_t i, shift, idx;

	for(i = (AFSK_TXDELAY+3)*8; i < modem_packet_size; ++i) {
		// fetch input bit
		idx = i / 8;
		shift = i % 8;
		bit = 1 & (modem_packet[idx] >> shift);

		// calculate output bit
		bit = scramble_bitwise(bit);

		// save output in memory
		modem_packet[idx] &= ~(1 << shift); // clear bit
		modem_packet[idx] |= bit << shift;  // correct bit
	}
}

static void send_byte(char byte)
{
	int i;
	for(i = 0; i < 8; i++) {
		update_crc((byte >> i) & 1);
		if((byte >> i) & 1) {
			// Next bit is a '1'
			if (modem_packet_size >= MODEM_MAX_PACKET * 8)  // Prevent buffer overrun
				return;
			modem_packet[modem_packet_size >> 3] |= (1 << (modem_packet_size & 7));
			modem_packet_size++;
			ones_in_a_row++;
			if(ones_in_a_row < 5)
				continue;
		}
		// Next bit is a '0' or a zero padding after 5 ones in a row
		if(modem_packet_size >= MODEM_MAX_PACKET * 8)    // Prevent buffer overrun
			return;
		modem_packet[modem_packet_size >> 3] &= ~(1 << (modem_packet_size & 7));
		modem_packet_size++;
		ones_in_a_row = 0;
	}
}

// Exported functions
void ax25_send_byte(char byte)
{
  // Wrap around send_byte, but prints debug info
  send_byte(byte);
}

void ax25_send_sync(void)
{
	unsigned char byte = 0x00;
	int i;
	for(i = 0; i < 8; i++, modem_packet_size++) {
		if(modem_packet_size >= MODEM_MAX_PACKET * 8)  // Prevent buffer overrun
			return;
		if ((byte >> i) & 1)
			modem_packet[modem_packet_size >> 3] |= (1 << (modem_packet_size & 7));
		else
			modem_packet[modem_packet_size >> 3] &= ~(1 << (modem_packet_size & 7));
	}
}

void ax25_send_flag(void)
{
  unsigned char byte = 0x7e;
  int i;
  for (i = 0; i < 8; i++, modem_packet_size++) {
    if (modem_packet_size >= MODEM_MAX_PACKET * 8)  // Prevent buffer overrun
      return;
    if ((byte >> i) & 1)
      modem_packet[modem_packet_size >> 3] |= (1 << (modem_packet_size & 7));
    else
      modem_packet[modem_packet_size >> 3] &= ~(1 << (modem_packet_size & 7));
  }
}

void ax25_send_string(const char *string)
{
	int i;
	for (i = 0; string[i]; i++) {
		ax25_send_byte(string[i]);
	}
}

void ax25_send_header(const s_address_t addresses[], int num_addresses)
{
	int i, j;
	modem_packet_size = 0;
	ones_in_a_row = 0;
	crc = 0xffff;

	// Send sync ("a bunch of 0s")
	for (i = 0; i < AFSK_TXDELAY; i++)
	{
		ax25_send_sync();
	}

	//start the actual frame. Send 3 of them (one empty frame and the real start)
	for (i = 0; i < 3; i++)
	{
		ax25_send_flag();
	}

	for (i = 0; i < num_addresses; i++) {
		// Transmit callsign
		for (j = 0; addresses[i].callsign[j]; j++) {
			send_byte(addresses[i].callsign[j] << 1);
		}
		// Transmit pad
		for ( ; j < 6; j++)
			send_byte(' ' << 1);
		// Transmit SSID. Termination signaled with last bit = 1
		if (i == num_addresses - 1)
			send_byte(('0' + addresses[i].ssid) << 1 | 1);
		else
			send_byte(('0' + addresses[i].ssid) << 1);
	}

	// Control field: 3 = APRS-UI frame
	send_byte(0x03);

	// Protocol ID: 0xf0 = no layer 3 data
	send_byte(0xf0);
}

void ax25_send_footer(void)
{
	// Save the crc so that it can be treated it atomically
	unsigned short int final_crc = crc;

	// Send the CRC
	send_byte(~(final_crc & 0xff));
	final_crc >>= 8;
	send_byte(~(final_crc & 0xff));

	//bit_scramble();

	// Signal the end of frame
	ax25_send_flag();
}

