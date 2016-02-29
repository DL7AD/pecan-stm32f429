#include "ch.h"
#include "hal.h"
#include "defines.h"
#include "debug.h"
#include "modules.h"
#include "radio.h"
#include "si4464.h"
#include <string.h>

// Sine table
const uint8_t sine_table[512] = {
	127, 129, 130, 132, 133, 135, 136, 138, 139, 141, 143, 144, 146, 147, 149, 150, 152, 153, 155, 156, 158,
	159, 161, 163, 164, 166, 167, 168, 170, 171, 173, 174, 176, 177, 179, 180, 182, 183, 184, 186, 187, 188,
	190, 191, 193, 194, 195, 197, 198, 199, 200, 202, 203, 204, 205, 207, 208, 209, 210, 211, 213, 214, 215,
	216, 217, 218, 219, 220, 221, 223, 224, 225, 226, 227, 228, 228, 229, 230, 231, 232, 233, 234, 235, 236,
	236, 237, 238, 239, 239, 240, 241, 242, 242, 243, 244, 244, 245, 245, 246, 247, 247, 248, 248, 249, 249,
	249, 250, 250, 251, 251, 251, 252, 252, 252, 253, 253, 253, 253, 254, 254, 254, 254, 254, 254, 254, 254,
	254, 254, 255, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 253, 253, 253, 253, 252, 252, 252, 251,
	251, 251, 250, 250, 249, 249, 249, 248, 248, 247, 247, 246, 245, 245, 244, 244, 243, 242, 242, 241, 240,
	239, 239, 238, 237, 236, 236, 235, 234, 233, 232, 231, 230, 229, 228, 228, 227, 226, 225, 224, 223, 221,
	220, 219, 218, 217, 216, 215, 214, 213, 211, 210, 209, 208, 207, 205, 204, 203, 202, 200, 199, 198, 197,
	195, 194, 193, 191, 190, 188, 187, 186, 184, 183, 182, 180, 179, 177, 176, 174, 173, 171, 170, 168, 167,
	166, 164, 163, 161, 159, 158, 156, 155, 153, 152, 150, 149, 147, 146, 144, 143, 141, 139, 138, 136, 135,
	133, 132, 130, 129, 127, 125, 124, 122, 121, 119, 118, 116, 115, 113, 111, 110, 108, 107, 105, 104, 102,
	101,  99,  98,  96,  95,  93,  91,  90,  88,  87,  86,  84,  83,  81,  80,  78,  77,  75,  74,  72,  71,
	 70,  68,  67,  66,  64,  63,  61,  60,  59,  57,  56,  55,  54,  52,  51,  50,  49,  47,  46,  45,  44,
	 43,  41,  40,  39,  38,  37,  36,  35,  34,  33,  31,  30,  29,  28,  27,  26,  26,  25,  24,  23,  22,
	 21,  20,  19,  18,  18,  17,  16,  15,  15,  14,  13,  12,  12,  11,  10,  10,   9,   9,   8,   7,   7,
	  6,   6,   5,   5,   5,   4,   4,   3,   3,   3,   2,   2,   2,   1,   1,   1,   1,   0,   0,   0,   0,
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1,
	  2,   2,   2,   3,   3,   3,   4,   4,   5,   5,   5,   6,   6,   7,   7,   8,   9,   9,  10,  10,  11,
	 12,  12,  13,  14,  15,  15,  16,  17,  18,  18,  19,  20,  21,  22,  23,  24,  25,  26,  26,  27,  28,
	 29,  30,  31,  33,  34,  35,  36,  37,  38,  39,  40,  41,  43,  44,  45,  46,  47,  49,  50,  51,  52,
	 54,  55,  56,  57,  59,  60,  61,  63,  64,  66,  67,  68,  70,  71,  72,  74,  75,  77,  78,  80,  81,
	 83,  84,  86,  87,  88,  90,  91,  93,  95,  96,  98,  99, 101, 102, 104, 105, 107, 108, 110, 111, 113,
	115, 116, 118, 119, 121, 122, 124, 125
};

#define TABLE_SIZE			sizeof(sine_table)
#define PLAYBACK_RATE		450000
#define BAUD_RATE			1200
#define SAMPLES_PER_BAUD	(PLAYBACK_RATE / BAUD_RATE) // 52.083333333 / 26.041666667
#define PHASE_DELTA_1200	(((TABLE_SIZE * 1200) << 7) / PLAYBACK_RATE) // Fixed point 9.7 // 1258 / 2516
#define PHASE_DELTA_2200	(((TABLE_SIZE * 2200) << 7) / PLAYBACK_RATE) // 2306 / 4613

#define MB_SIZE 4

mailbox_t radioMB;
msg_t mb_pbuffer[MB_SIZE];
radioMSG_t mb_buffer[MB_SIZE];
uint32_t mb_buffer_index;
static uint8_t mb_free = MB_SIZE;
mutex_t radio_mtx;

static uint16_t current_byte;
static uint16_t current_sample_in_baud;		// 1 bit = SAMPLES_PER_BAUD samples
static uint32_t phase_delta;				// 1200/2200 for standard AX.25
static uint32_t phase;						// Fixed point 9.7 (2PI = TABLE_SIZE)
static uint32_t packet_pos;					// Next bit to be sent out
static volatile bool modem_busy = false;	// Is timer running
static radio_t afsk_radio;					// Current radio
static radioMSG_t *afsk_msg;				// Current message
static bool timer_running;					// Is timer running

static void afsk_callback(GPTDriver *gptp) {
	(void)gptp;

	// If done sending packet
	if(packet_pos == afsk_msg->bin_len) {
		timer_running = false;
		return;
	}

	// If sent SAMPLES_PER_BAUD already, go to the next bit
	if (current_sample_in_baud == 0) {    // Load up next bit
		if ((packet_pos & 7) == 0) {          // Load up next byte
			current_byte = afsk_msg->msg[packet_pos >> 3];
		} else {
			current_byte = current_byte / 2;  // ">>1" forces int conversion
		}

		if ((current_byte & 1) == 0) {
			// Toggle tone (1200 <> 2200)
			phase_delta ^= (PHASE_DELTA_1200 ^ PHASE_DELTA_2200);
		}
	}

	phase += phase_delta;

	MOD_GPIO_SET(afsk_radio, sine_table[(phase >> 7) & (TABLE_SIZE - 1)] > 127);

	if(++current_sample_in_baud == SAMPLES_PER_BAUD) {
		palTogglePad(PORT(LED_YELLOW), PIN(LED_YELLOW));
		current_sample_in_baud = 0;
		packet_pos++;
	}
}

static GPTConfig gptcfg_afsk = {
	180000000,
	afsk_callback,
	0,
	0
};

void sendAFSK(radio_t radio, radioMSG_t *msg) {
	// Initialize radio and tune
	Si4464_Init(radio, MOD_AFSK);
	radioTune(radio, msg->freq, 0, msg->power);

	// Initialize variables for AFSK
	phase_delta = PHASE_DELTA_1200;
	phase = 0;
	packet_pos = 0;
	current_sample_in_baud = 0;
	modem_busy = true;
	afsk_msg = msg;
	afsk_radio = radio;
	timer_running = true;

	// Start timer
	gptStart(&GPTD1, &gptcfg_afsk);
	gptStartContinuous(&GPTD1, 250);

	// Wait for routine to finish
	while(timer_running)
		chThdSleepMilliseconds(1);

	// Stop timer
	gptStopTimer(&GPTD1);
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

		time = chThdSleepUntilWindowed(time, time + MS2ST(20));
	}
}


// Transmit data (Software UART)
static uint8_t txs;			// TX state
static uint8_t txc;			// Current char
static uint32_t txi;
static uint32_t txj;
static radio_t fsk_radio;	// Current radio
static radioMSG_t *fsk_msg;	// Current message

static void serial_callback(GPTDriver *gptp) {
	(void)gptp;

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
}

static void gfsk_callback(GPTDriver *gptp) {
	(void)gptp;

	switch(txs)
	{
		case 6: // Transmit a single char
			if(txj < fsk_msg->bin_len/8 && txi == 0) {
				palSetPad(PORT(LED_YELLOW), PIN(LED_YELLOW));__NOP();__NOP();__NOP();__NOP();__NOP();
				palClearPad(PORT(LED_YELLOW), PIN(LED_YELLOW));
				txc = fsk_msg->msg[txj]; // Select char
				txi = 8;
				txj++;
			}

			palSetPad(PORT(LED_YELLOW), PIN(LED_YELLOW));__NOP();__NOP();__NOP();__NOP();__NOP();
			palClearPad(PORT(LED_YELLOW), PIN(LED_YELLOW));
			txi--;
			MOD_GPIO_SET(fsk_radio, txc & 1);
			txc = txc >> 1;

			if(txj == fsk_msg->bin_len/8)
				txs = 7;
			break;
		case 7:
			txj = 0;
			txs = 0;
			MOD_GPIO_SET(fsk_radio, HIGH);
			break;
	}
}

static GPTConfig gptcfg_serial = {
	19200,
	serial_callback,
	0,
	0
};

void send2FSK(radio_t radio, radioMSG_t *msg) {
	// Initialize radio and tune
	Si4464_Init(radio, MOD_2FSK);
	MOD_GPIO_SET(radio, HIGH);
	radioTune(radio, msg->freq, FSK_SHIFT, msg->power);

	txs = 6;
	txc = 0;
	txi = 0;
	txj = 0;
	fsk_msg = msg;
	fsk_radio = radio;

	// Start timer
	gptStart(&GPTD1, &gptcfg_serial);
	gptStartContinuous(&GPTD1, gptcfg_serial.frequency / FSK_BAUD);

	// Wait for routine to finish
	while(txs)
		chThdSleepMilliseconds(1);

	// Stop timer
	gptStopTimer(&GPTD1);
}

static GPTConfig gptcfg_gfsk = {
	360000,
	gfsk_callback,
	0,
	0
};

void send2GFSK(radio_t radio, radioMSG_t *msg) {
	// Initialize radio and tune
	Si4464_Init(radio, MOD_2GFSK);
	MOD_GPIO_SET(radio, HIGH);
	radioTune(radio, msg->freq, 9600, msg->power);

	txs = 6;
	txc = 0;
	txi = 0;
	txj = 0;
	fsk_msg = msg;
	fsk_radio = radio;

	// Start timer
	gptStart(&GPTD1, &gptcfg_gfsk);
	gptStartContinuous(&GPTD1, 39);

	uint8_t ctone = 0;
	for(uint32_t i=0; i<msg->bin_len; i++) {
		uint8_t a = i/8;
		uint8_t s = i%8;
		if(((msg->msg[a] >> s) & 0x1) == 0) // Change tone
			ctone = !ctone;
		msg->msg[a] = (msg->msg[a] & ~(0x1 << s)) | (ctone << s);
	}
	TRACE_BIN(msg->msg, msg->bin_len);

	// Wait for routine to finish
	while(txs)
		chThdSleepMilliseconds(1);

	// Stop timer
	gptStopTimer(&GPTD1);
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

	while(true)
	{
		parm->lastCycle = chVTGetSystemTimeX(); // Watchdog timer

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
				TRACE_INFO(	"RAD  > Transmit on radio\r\n"
							"%s Radio %d\r\n"
							"%s Frequency %d.%03d MHz\r\n"
							"%s Power %d dBm (%d)\r\n"
							"%s Modulation %s",
							TRACE_TAB, radio,
							TRACE_TAB, msg->freq/1000000, (msg->freq%1000000)/1000,
							TRACE_TAB, msg->power, dBm2powerLvl(msg->power),
							TRACE_TAB, VAL2MOULATION(msg->mod)
				);
				TRACE_BIN(msg->msg, msg->bin_len);

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
				if(ST2MS(chVTGetSystemTimeX() - lastMessage[i]) >= RADIO_TIMEOUT)
					radioShutdown(i); // Shutdown radio
			}
		}
		chThdSleepMilliseconds(1);
	}
}


uint32_t getAPRSRegionFrequency(void) {
	return 144800000; // TODO: Implement Geofencing
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






