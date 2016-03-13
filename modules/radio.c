#include "ch.h"
#include "hal.h"
#include "defines.h"
#include "debug.h"
#include "modules.h"
#include "radio.h"
#include "si4464.h"
#include "geofence.h"
#include "pi2c.h"
#include <string.h>

#define PLAYBACK_RATE		1620000									/* Samples per second (SYSCLK = 45MHz) */
#define BAUD_RATE			1200									/* APRS AFSK baudrate */
#define SAMPLES_PER_BAUD	(PLAYBACK_RATE / BAUD_RATE)				/* Samples per baud */
#define PHASE_DELTA_1200	(((2 * 1200) << 16) / PLAYBACK_RATE)	/* Delta-phase per sample for 1200Hz tone */
#define PHASE_DELTA_2200	(((2 * 2200) << 16) / PLAYBACK_RATE)	/* Delta-phase per sample for 2200Hz tone */
#define MB_SIZE 2													/* Radio mailbox size */

mailbox_t radioMB;
msg_t mb_pbuffer[MB_SIZE];		// Mailbox pointer buffer (contains radioMSG_t pointer)
radioMSG_t mb_buffer[MB_SIZE];	// Mailbox data buffer
uint32_t mb_buffer_index;
static uint8_t mb_free = MB_SIZE;
mutex_t radio_mtx;

void sendAFSK(radio_t radio, radioMSG_t *msg) {
	// Initialize variables for AFSK
	uint32_t phase_delta = PHASE_DELTA_1200;	// 1200/2200 for standard AX.25
	uint32_t phase = 0;							// Fixed point 9.7 (2PI = TABLE_SIZE)
	uint32_t packet_pos = 0;					// Next bit to be sent out
	uint32_t current_sample_in_baud = 0;		// 1 bit = SAMPLES_PER_BAUD samples
	uint8_t current_byte = 0;

	// Initialize radio and tune
	Si4464_Init(radio, MOD_AFSK);
	radioTune(radio, msg->freq, 0, msg->power);

	// Modulate
	while(true)
	{
		if(packet_pos == msg->bin_len) // Packet transmission finished
			return;

		if (current_sample_in_baud == 0) {
			if ((packet_pos & 7) == 0) {					// Load up next byte
				current_byte = msg->msg[packet_pos >> 3];
			} else {
				current_byte = current_byte / 2;			// Load up next bit
			}

			phase_delta = (current_byte & 1) ? PHASE_DELTA_1200 : PHASE_DELTA_2200; // Toggle tone (1200 <> 2200)
		}

		phase += phase_delta;								// Add delta-phase (delta-phase tone dependent)
		MOD_GPIO_SET(radio, (phase >> 16) & 1);				// Set modulaton pin (connected to Si4464)

		if(++current_sample_in_baud == SAMPLES_PER_BAUD) {	// Old bit consumed, load next bit
			palTogglePad(GPIOC, 3); // Pad for measuring clock
			current_sample_in_baud = 0;
			packet_pos++;
		}
		__NOP();__NOP();__NOP();__NOP();__NOP();
	}
}

/**
  * Transmits binary CW message. One bit = 20ms (1: TONE, 0: NO TONE)
  */
void sendCW(radio_t radio, radioMSG_t *msg) {
	// Initialize radio and tune
	Si4464_Init(radio, MOD_CW);
	radioTune(radio, msg->freq, 0, msg->power);

	// Transmit data
	uint32_t bit = 0;
	systime_t time = chVTGetSystemTimeX();
	while(bit < msg->bin_len) {
		MOD_GPIO_SET(radio, (msg->msg[bit/8] >> (bit%8)) & 0x1);
		bit++;

		time = chThdSleepUntilWindowed(time, time + MS2ST(1200 / CW_SPEED));
	}
}

// Transmit data (Software UART)
static uint8_t txs;			// Serial maschine state
static uint8_t txc;			// Current byte
static uint32_t txi;		// Bitcounter of current byte
static uint32_t txj;		// Bytecounter
static radio_t fsk_radio;	// Current radio
static radioMSG_t *fsk_msg;	// Current message
static virtual_timer_t vt;

static void serial_cb(void *arg) {
	(void)arg;

	switch(txs)
	{
		case 6: // TX-delay
			txj++;
			if(txj > FSK_PREDELAY) {
				txj = 0;
				txs = 7;
			}
			break;

		case 7: // Transmit a single char
			if(txj < fsk_msg->bin_len/8) {
				txc = fsk_msg->msg[txj]; // Select char
				txj++;
				MOD_GPIO_SET(fsk_radio, LOW); // Start Bit (Synchronizing)
				txi = 0;
				txs = 8;
			} else {
				txj = 0;
				txs = 0; // Finished to transmit string
				MOD_GPIO_SET(fsk_radio, HIGH);
			}
			break;

		case 8:
			if(txi < FSK_ASCII) {
				txi++;
				MOD_GPIO_SET(fsk_radio, txc & 1);
				txc = txc >> 1;
			} else {
				MOD_GPIO_SET(fsk_radio, HIGH); // Stop Bit
				txi = 0;
				txs = 9;
			}
			break;

		case 9:
			if(FSK_STOPBITS == 2)
				MOD_GPIO_SET(fsk_radio, HIGH); // Stop Bit
			txs = 7;
	}

	// Reload timer
	if(txs) {
		chSysLockFromISR();
		chVTSetI(&vt, US2ST(1000000/FSK_BAUD), serial_cb, NULL);
		chSysUnlockFromISR();
	}
}

void send2FSK(radio_t radio, radioMSG_t *msg) {
	// Prepare serial machine states
	txs = 6;
	txc = 0;
	txi = 0;
	txj = 0;
	fsk_msg = msg;
	fsk_radio = radio;

	// Initialize radio and tune
	Si4464_Init(radio, MOD_2FSK);
	MOD_GPIO_SET(radio, HIGH);
	radioTune(radio, msg->freq, FSK_SHIFT, msg->power);

	// Modulate
	chVTSet(&vt, 1, serial_cb, NULL);	// Start timer
	while(txs)
		chThdSleepMilliseconds(1);		// Wait for routine to finish
}

void send2GFSK(radio_t radio, radioMSG_t *msg) {
	// Initialize radio and tune
	Si4464_Init(radio, MOD_2GFSK);
	radioTune(radio, msg->freq, 0, msg->power);

	// Transmit data
	uint32_t bit = 0;
	uint8_t ctone = 0;
	uint8_t current_byte = 0;
	systime_t time = chVTGetSystemTimeX();
	while(bit < msg->bin_len) {

		if((bit & 7) == 0) { // Load up next byte
			current_byte = msg->msg[bit >> 3];
		} else {
			current_byte = current_byte / 2; // Load next bit
		}

		chprintf((BaseSequentialStream*)&SD4, "%d", (current_byte & 1));

		if((current_byte & 1) == 0)
			ctone = !ctone; // Switch shifting
		MOD_GPIO_SET(radio, ctone);
		bit++;

		time = chThdSleepUntilWindowed(time, time + 107);
		palTogglePad(PORT(LED_YELLOW), PIN(LED_YELLOW));
	}
}

THD_FUNCTION(moduleRADIO, arg) {
	module_params_t* parm = (module_params_t*)arg;
	time_t lastMessage[2]; // Last transmission time (end of transmission)
	mod_t lastModulation[2]; // Last modulation

	// Print infos
	TRACE_INFO("RAD  > Startup module RADIO");

	// Setup mailbox
	TRACE_INFO("RAD  > Setup radio mailbox");
	chMBObjectInit(&radioMB, mb_pbuffer, MB_SIZE);
	chMtxObjectInit(&radio_mtx);

	// Setup timer
	chVTObjectInit(&vt);

	while(true)
	{
		parm->lastCycle = chVTGetSystemTimeX(); // Watchdog timer

		// Lock interference mutex
		chMtxLock(&interference_mtx);

		// Receive message
		radioMSG_t *msg;
		msg_t status = chMBFetch(&radioMB, (msg_t*)&msg, 0);

		if(status == MSG_OK) { // Message available

			// Determine suitable radio
			radio_t radio = 0;
			if(inRadio1band(msg->freq)) {
				radio = RADIO_2M;
			} else if(inRadio2band(msg->freq)) {
				radio = RADIO_70CM;
			}

			if(radio) { // Radio found
				TRACE_INFO(	"RAD  > Transmit on radio (%d bits)\r\n"
							"%s Radio %d\r\n"
							"%s Frequency %d.%03d MHz\r\n"
							"%s Power %d dBm (%d)\r\n"
							"%s Modulation %s",
							msg->bin_len,
							TRACE_TAB, radio,
							TRACE_TAB, msg->freq/1000000, (msg->freq%1000000)/1000,
							TRACE_TAB, msg->power, dBm2powerLvl(msg->power),
							TRACE_TAB, VAL2MOULATION(msg->mod)
				);

				if(msg->mod != lastModulation[radio]) // Modulation of last msg was different
					radioShutdown(radio); // Shutdown radio for reinitialization

				switch(msg->mod) {
					case MOD_2FSK:
						send2FSK(radio, msg);
						break;
					case MOD_2GFSK:
						send2GFSK(radio, msg);
						break;
					case MOD_AFSK:
						sendAFSK(radio, msg);
						break;
					case MOD_CW:
						sendCW(radio, msg);
						break;
					case MOD_DOMINOEX16:
						TRACE_ERROR("RAD  > Unimplemented modulation DominoEX16"); // TODO: Implement this
						break;
				}

				lastMessage[radio] = chVTGetSystemTimeX(); // Mark time for radio shutdown
				lastModulation[radio] = msg->mod;

			} else { // Error

				TRACE_ERROR("RAD  > No radio available for this frequency\r\n"
							"%s Radio %d\r\n"
							"%s Frequency %d.%03d MHz\r\n"
							"%s Power %d dBm (%d)\r\n"
							"%s Modulation %s",
							TRACE_TAB, 10,
							TRACE_TAB, msg->freq/1000000, (msg->freq%1000000)/1000,
							TRACE_TAB, msg->power, dBm2powerLvl(msg->power),
							TRACE_TAB, VAL2MOULATION(msg->mod)
				);

			}

			chMtxLock(&radio_mtx);
			mb_free++;
			chMtxUnlock(&radio_mtx);

		} else {
			for(uint8_t i=0; i<2; i++) {
				if(ST2MS(chVTGetSystemTimeX() - lastMessage[i]) >= RADIO_TIMEOUT) // Timeout reached
					radioShutdown(i); // Shutdown radio
			}
		}
		chMtxUnlock(&interference_mtx); // Heavy interference finished (HF)

		chThdSleepMilliseconds(1);
	}
}

/**
  * Returns APRS region specific frequency determined by GPS location. It will
  * use the APRS default frequency set in the config file if no GPS fix has
  * been received.
  * TODO: Countries missing: Brasil, Chile,
  * Argentinia/Bolivia/Uruguay, Venezuela/Panama, Costa Rica, Australia, New Zealand
  */
uint32_t getAPRSRegionFrequency(void) {
	trackPoint_t *point = getLastTrackPoint();

	// Use this frequency for the rest of the world (unset regions, 144.800 MHz)
	uint32_t freq = APRS_FREQ_OTHER;

	// Use default frequency set in config file
	if(!point->gps_lat && !point->gps_lon)
		freq = APRS_DEFAULT_FREQ;
	
	// America 144.390 MHz
	if(isPointInAmerica(point->gps_lat, point->gps_lon))
		freq = APRS_FREQ_AMERICA;

	// China 144.640 MHz
	if(isPointInChina(point->gps_lat, point->gps_lon))
		freq = APRS_FREQ_CHINA;

	// Japan 144.660 MHz
	if(isPointInJapan(point->gps_lat, point->gps_lon))
		freq = APRS_FREQ_JAPAN;

	// Southkorea 144.620 MHz
	if(isPointInSouthkorea(point->gps_lat, point->gps_lon))
		freq = APRS_FREQ_SOUTHKOREA;

	// Southkorea 144.620 MHz
	if(isPointInSoutheastAsia(point->gps_lat, point->gps_lon))
		freq = APRS_FREQ_SOUTHEASTASIA;

	// Australia 145.175 MHz
	if(isPointInAustralia(point->gps_lat, point->gps_lon))
		freq = APRS_FREQ_AUSTRALIA;

	// Australia 144.525 MHz
	if(isPointInNewZealand(point->gps_lat, point->gps_lon))
		freq = APRS_FREQ_NEWZEALAND;

	// Argentina/Paraguay/Uruguay 144.930 MHz
	if(isPointInArgentina(point->gps_lat, point->gps_lon))
		freq = APRS_FREQ_ARGENTINA;

	// Brazil 145.575 MHz
	if(isPointInBrazil(point->gps_lat, point->gps_lon))
		freq = APRS_FREQ_BRAZIL;

	return freq;
}
uint32_t getAPRSISSFrequency(void) {
	return 145825000;
}
uint32_t getCustomFrequency(void) {
	return 434500000;
}

/**
  * Sends radio message into message box. This method will return false if message box is full.
  */
bool transmitOnRadio(radioMSG_t *msg) {
	chMtxLock(&radio_mtx);
	if(mb_free > 0) { // Buffer is free
		chMBPost(&radioMB, (msg_t)&mb_buffer[mb_buffer_index % MB_SIZE], TIME_IMMEDIATE);	// Post pointer into messagebox
		memcpy(&mb_buffer[mb_buffer_index % MB_SIZE], msg, sizeof(radioMSG_t));				// Copy buffer into messagebox-buffer
		mb_buffer_index++;																	// Increment buffer index
		mb_free--;																			// Decrement free counter
		chMtxUnlock(&radio_mtx);
		return true;
	}
	chMtxUnlock(&radio_mtx);
	return false;
}






