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

#ifndef __AX25_H__
#define __AX25_H__

#include "ch.h"
#include "hal.h"

#define MODEM_MAX_PACKET 512 /* Max size of modem packet */

typedef struct s_address {
	char callsign[7];
	unsigned char ssid;
} s_address_t;

extern uint8_t modem_packet[MODEM_MAX_PACKET];  // Upper layer data
extern uint16_t modem_packet_size;              // in bits

void ax25_send_header(const s_address_t addresses[], int num_addresses);

void ax25_send_byte(char byte);
void ax25_send_string(const char *string);
void ax25_send_footer(void);
//void bit_scramble(void);

#endif

