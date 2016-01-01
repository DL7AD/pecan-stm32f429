#include "ch.h"
#include "hal.h"
#include "defines.h"
#include "trace.h"
#include "modules.h"
#include "radio.h"
#include "../drivers/si4x6x.h"

#define TX_CPU_CLOCK			10200
#define CLOCK_PER_TICK			1
#define PLAYBACK_RATE			(TX_CPU_CLOCK / CLOCK_PER_TICK) // Tickrate 46.875 kHz
#define BAUD_RATE				1200
#define SAMPLES_PER_BAUD		(PLAYBACK_RATE / BAUD_RATE) // 52.083333333 / 26.041666667
#define PHASE_DELTA_1200		(10066329600 / CLOCK_PER_TICK / PLAYBACK_RATE) // Fixed point 9.7 // 1258 / 2516
#define PHASE_DELTA_2200		(18454937600 / CLOCK_PER_TICK / PLAYBACK_RATE) // 2306 / 4613

mailbox_t radioMBP;
radioMSG_t buf[10];

uint32_t getAPRSRegionFrequency(void) {
	return 144800000; // TODO: Implement Geofencing
}
uint32_t getAPRSISSFrequency(void) {
	return 145825000;
}
uint32_t getCustomFrequency(void) {
	return 434500000;
}

THD_FUNCTION(moduleRADIO, arg) {
	module_params_t* parm = (module_params_t*)arg;

	// Print infos
	TRACE_INFO("RAD  > Startup module RADIO");

	// Setup mailbox
	TRACE_INFO("RAD  > Setup radio mailbox");
	chMBObjectInit(&radioMBP, (msg_t*)buf, sizeof(buf));

	while(true)
	{
		parm->lastCycle = chVTGetSystemTimeX(); // Watchdog timer

		// Receive message
		radioMSG_t *msg;
		msg_t status = chMBFetch(&radioMBP, (msg_t*)&msg, 0);

		if(status == MSG_OK) { // Message available

			// Determine suitable radio
			radio_t radio = 0;
			if(inRadio1band(msg->freq)) {
				radio = RADIO_2M;
			} else if(inRadio2band(msg->freq)) {
				radio = RADIO_70CM;
			}

			if(radio) { // Radio found
				TRACE_INFO(	"RAD  > Transmit on radio\r\n"
							"%s Radio %d\r\n"
							"%s Frequency %d MHz\r\n"
							"%s Power %d dBm (%d)\r\n"
							"%s Modulation %s",
							TRACE_TAB, radio,
							TRACE_TAB, msg->freq,
							TRACE_TAB, msg->power, dBm2powerLvl(msg->power),
							TRACE_TAB, VAL2MOULATION(msg->mod)
				);
				TRACE_BIN(msg->msg, msg->bin_len);
				switch(msg->mod) {
					case MOD_2FSK:
						//send2FSK(radio, msg); TODO: Implement!
						break;
					case MOD_AFSK:
						sendAFSK(radio, msg);
						break;
					case MOD_CW:
						sendCW(radio, msg);
						break;
				}

			} else { // Error

				TRACE_ERROR("RAD  > No radio available for this frequency\r\n"
							"%s Radio %d\r\n"
							"%s Frequency %d MHz\r\n"
							"%s Power %d dBm (%d)\r\n"
							"%s Modulation %s",
							TRACE_TAB, 10,
							TRACE_TAB, msg->freq,
							TRACE_TAB, msg->power, dBm2powerLvl(msg->power),
							TRACE_TAB, VAL2MOULATION(msg->mod)
				);

			}
		}
		chThdSleepMilliseconds(100);
	}
}

// Module globals
static uint16_t current_byte;
static uint16_t current_sample_in_baud;		// 1 bit = SAMPLES_PER_BAUD samples
static uint32_t phase_delta;				// 1200/2200 for standard AX.25
static uint32_t phase;						// Fixed point 9.7 (2PI = TABLE_SIZE)
static uint32_t packet_pos;					// Next bit to be sent out
static volatile bool modem_busy = false;	// Is timer running
static radio_t cradio;						// Current radio

void sendAFSK(radio_t radio, radioMSG_t *msg) {
	// Initialize radio and tune
	Si446x_Init(radio, MOD_AFSK);
	radioTune(radio, msg->freq, msg->power);

	// Initialize variables for AFSK
	phase_delta = PHASE_DELTA_1200;
	phase = 0;
	packet_pos = 0;
	current_sample_in_baud = 0;
	cradio = radio;
	modem_busy = true;

	// Start timer
	systime_t lastSystemTime = chVTGetSystemTimeX();
	while(afsk_handler(radio, msg)) { // Task
		// Synchronization
		uint32_t i=0;
		while(chVTGetSystemTimeX() == lastSystemTime)
			while(i<0xFF)
				i++;
		lastSystemTime++;
	}

	radioShutdown(radio);	// Shutdown radio
}

bool afsk_handler(radio_t radio, radioMSG_t *msg) {
	// If done sending packet
	if(packet_pos == msg->bin_len) {
		return false;
	}

	// If sent SAMPLES_PER_BAUD already, go to the next bit
	if (current_sample_in_baud == 0) {	// Load up next bit
		if ((packet_pos & 7) == 0) {	// Load up next byte
			current_byte = msg->msg[packet_pos >> 3];
		} else {
			current_byte = current_byte / 2; // ">>1" forces int conversion
		}

		if ((current_byte & 1) == 0) {
			// Toggle tone (1200 <> 2200)
			phase_delta ^= (PHASE_DELTA_1200 ^ PHASE_DELTA_2200);
		}
	}

	phase += phase_delta;

	MOD_GPIO_SET(radio, ((phase >> 7) & 0xFF) > 127);

	if(++current_sample_in_baud == SAMPLES_PER_BAUD) {
		current_sample_in_baud = 0;
		packet_pos++;
	}

	return true;
}

void sendCW(radio_t radio, radioMSG_t *msg) {
	// Initialize radio and tune
	Si446x_Init(radio, MOD_CW);
	radioTune(radio, msg->freq, msg->power);

	// Transmit data
	uint32_t bit = 0;
	systime_t time = chVTGetSystemTimeX();
	while(bit < msg->bin_len) {
		MOD_GPIO_SET(radio, (msg->msg[bit/8] >> (bit%8)) & 0x1);
		bit++;

		time += MS2ST(10);
		chThdSleepUntil(time);
	}

	// Shutdown radio
	radioShutdown(radio);	// Shutdown radio
}






