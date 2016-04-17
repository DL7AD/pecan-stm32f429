#include "config.h"
#include "debug.h"

module_conf_t config[8];

// Put your configuration settings here
void initModules(void)
{

	// Module POSITION, APRS 2m AFSK, day
	/*chsnprintf(config[0].instance_name, 16, "POS APRS 2m day"); // Instance name
	config[0].power = 10;									// Power 10 dBm
	config[0].protocol = PROT_APRS_2GFSK;					// Protocol APRS, modulation AFSK
	config[0].frequency.type = FREQ_DYNAMIC;				// Dynamic frequency allocation
	config[0].frequency.hz = 144800000;						// Default frequency 144.800 MHz
	config[0].frequency.method = APRS_REGION_FREQ_2M;		// Determine local APRS frequency on 2m
	config[0].init_delay = 0;								// Module startup delay in sec
	config[0].sleep.types[0] = SLEEP_WHEN_VBAT_ABOVE_THRES; // Sleep when battery above threshold
	config[0].sleep.vbat_thres = 4000;						// Battery voltage threshold 4000mV
	config[0].trigger.type = TRIG_TIMEOUT;					// Trigger transmission on timeout (Periodic cycling)
	config[0].trigger.timeout = 180;						// Timeout 180sec
	chsnprintf(config[0].aprs_config.callsign, 6, "DL7AD"); // APRS Callsign
	config[0].aprs_config.ssid = 12;						// APRS SSID
	config[0].aprs_config.symbol = SYM_BALLOON;				// APRS Symbol
	chsnprintf(config[0].aprs_config.path, 8, "WIDE1-1");	// APRS Path
	config[0].aprs_config.preamble = 200;					// APRS Preamble
	config[0].aprs_config.tel1 = TEL_VBAT;					// APRS Telemetry parameter 1
	config[0].aprs_config.tel2 = TEL_VSOL;					// APRS Telemetry parameter 2
	config[0].aprs_config.tel3 = TEL_IPRESS;				// APRS Telemetry parameter 3
	config[0].aprs_config.tel4 = TEL_ITEMP;					// APRS Telemetry parameter 4
	config[0].aprs_config.tel5 = TEL_IHUM;					// APRS Telemetry parameter 5
	config[0].aprs_config.tel_encoding = TRUE;				// Transmit Telemetry encoding information activated
	config[0].aprs_config.tel_encoding_cycle = 3600;		// Transmit Telemetry encoding information every 3600sec
	MODULE_POSITION(&config[0]);*/

	// Module POSITION, APRS 2m AFSK, night
	/*
	chsnprintf(config[1].instance_name, 18, "POS APRS 2m night");// Instance name
	config[1].power = 10;									// Power 10 dBm
	config[1].protocol = PROT_APRS_2GFSK;					// Protocol APRS, modulation AFSK
	config[1].frequency.type = FREQ_DYNAMIC;				// Dynamic frequency allocation
	config[1].frequency.hz = 144800000;						// Default frequency 144.800 MHz
	config[1].frequency.method = APRS_REGION_FREQ_2M;		// Determine local APRS frequency on 2m
	config[1].init_delay = 0;								// Module startup delay in sec
	config[1].sleep.types[0] = SLEEP_WHEN_VBAT_BELOW_THRES; // Sleep when battery below threshold
	config[1].sleep.vbat_thres = 4000;						// Battery voltage threshold 4000mV
	config[1].trigger.type = TRIG_TIMEOUT;					// Trigger transmission on timeout (Periodic cycling)
	config[1].trigger.timeout = 600;						// Timeout 180sec
	chsnprintf(config[1].aprs_config.callsign, 6, "DL7AD"); // APRS Callsign
	config[1].aprs_config.ssid = 12;						// APRS SSID
	config[1].aprs_config.symbol = SYM_BALLOON;				// APRS Symbol
	chsnprintf(config[1].aprs_config.path, 8, "WIDE1-1");	// APRS Path
	config[1].aprs_config.preamble = 200;					// APRS Preamble
	config[1].aprs_config.tel1 = TEL_VBAT;					// APRS Telemetry parameter 1
	config[1].aprs_config.tel2 = TEL_VSOL;					// APRS Telemetry parameter 2
	config[1].aprs_config.tel3 = TEL_IPRESS;				// APRS Telemetry parameter 3
	config[1].aprs_config.tel4 = TEL_ITEMP;					// APRS Telemetry parameter 4
	config[1].aprs_config.tel5 = TEL_IHUM;					// APRS Telemetry parameter 5
	config[1].aprs_config.tel_encoding = FALSE;				// Transmit Telemetry encoding information disabled
	MODULE_POSITION(&config[1]);*/

	// Module POSITION, UKHAS 2m 2FSK
	/*chsnprintf(config[2].instance_name, 13, "POS UKHAS 2m"); // Instance name
	config[2].power = 10;									// Power 10 dBm
	config[2].protocol = PROT_UKHAS_2FSK;					// Protocol UKHAS, modulation 2FSK
	config[2].frequency.type = FREQ_STATIC;					// Static frequency allocation
	config[2].frequency.hz = 145300000;						// Transmission frequency 145.300 MHz
	config[2].init_delay = 0;								// Module startup delay in sec
	config[2].sleep.types[0] = SLEEP_WHEN_VBAT_BELOW_THRES; // Sleep when battery below threshold
	config[2].sleep.vbat_thres = 3000;						// Battery voltage threshold 3000mV
	config[2].trigger.type = TRIG_TIMEOUT;					// Trigger transmission on timeout (Periodic cycling)
	config[2].trigger.timeout = 180;						// Timeout 180sec
	config[2].fsk_config.bits = 8;							// 8bit
	config[2].fsk_config.stopbits = 2;						// 2 Stopbits
	config[2].fsk_config.predelay = 1000;					// Predelay in ms (continuos carrier before actual transmission)
	config[2].fsk_config.baud = 50;							// Baudrate
	config[2].fsk_config.shift = 425;						// Frequency shift in Hz
	chsnprintf(config[2].ukhas_config.callsign, 6, "DL7AD"); // UKHAS Callsign
	chsnprintf(config[2].ukhas_config.format, 134, "<CALL>,<ID>,<TIME>,<LAT>,<LON>,<ALT>,<SATS>,<TTFF>,<VBAT>,<VSOL>,<CHARGE>,<DISCHARGE>,<IPRESS>,<ITEMP>,<IHUM>,<EPRESS>,<ETEMP>,<EHUM>"); // UKHAS Format
	MODULE_POSITION(&config[2]);*/

	// Module POSITION, Morse 2m OOK
	/*chsnprintf(config[3].instance_name, 11, "POS OOK 2m");// Instance name
	config[3].power = 10;									// Power 10 dBm
	config[3].protocol = PROT_MORSE;						// Protocol Morse, modulation OOK
	config[3].frequency.type = FREQ_STATIC;					// Static frequency allocation
	config[3].frequency.hz = 145300000;						// Transmission frequency 145.300 MHz
	config[3].init_delay = 0;								// Module startup delay in sec
	config[3].sleep.types[0] = SLEEP_WHEN_VBAT_BELOW_THRES; // Sleep when battery below threshold
	config[3].sleep.vbat_thres = 3000;						// Battery voltage threshold 3000mV
	config[3].trigger.type = TRIG_TIMEOUT;					// Trigger transmission on timeout (Periodic cycling)
	config[3].trigger.timeout = 180;						// Timeout 180sec
	config[3].ook_config.speed = 20;						// Speed 20wpm
	chsnprintf(config[3].morse_config.callsign, 6, "DL7AD"); // UKHAS Callsign
	chsnprintf(config[3].morse_config.format, 28, "<CALL> <LOC> <ALT>M PSE QSL"); // Morse Format
	MODULE_POSITION(&config[3]);*/

	// Module IMAGE, APRS 2m AFSK
	/*chsnprintf(config[4].instance_name, 12, "IMG AFSK 2m");// Instance name
	config[4].power = 10;									// Power 10 dBm
	config[4].protocol = PROT_APRS_AFSK;					// Protocol Morse, modulation OOK
	config[4].frequency.type = FREQ_STATIC;					// Static frequency allocation
	config[4].frequency.hz = 145300000;						// Transmission frequency 145.300 MHz
	config[4].init_delay = 0;								// Module startup delay in sec
	config[4].packet_spacing = 20000;						// Packet spacing in ms
	config[4].sleep.types[0] = SLEEP_WHEN_VBAT_BELOW_THRES; // Sleep when battery below threshold
	config[4].sleep.vbat_thres = 3500;						// Battery voltage threshold 3000mV
	config[4].trigger.type = TRIG_TIMEOUT;					// Trigger transmission on timeout (Periodic cycling)
	config[4].trigger.timeout = 0;							// Transmit continously
	chsnprintf(config[4].ssdv_config.callsign, 6, "DL7AD"); // SSDV Callsign
	config[4].ssdv_config.res = RES_QVGA;					// Resolution QVGA
	MODULE_IMAGE(&config[4]);*/

	// Module IMAGE, APRS 2m 2GFSK
	chsnprintf(config[5].instance_name, 13, "IMG 2GFSK 2m");// Instance name
	config[5].power = 10;									// Power 10 dBm
	config[5].protocol = PROT_APRS_2GFSK;					// Protocol Morse, modulation OOK
	config[5].frequency.type = FREQ_STATIC;					// Static frequency allocation
	config[5].frequency.hz = 145300000;						// Transmission frequency 145.300 MHz
	config[5].init_delay = 0;								// Module startup delay in sec
	config[5].packet_spacing = 0;							// Packet spacing in ms
	config[5].sleep.types[0] = SLEEP_WHEN_VBAT_BELOW_THRES; // Sleep when battery below threshold
	config[5].sleep.vbat_thres = 3500;						// Battery voltage threshold 3000mV
	config[5].trigger.type = TRIG_TIMEOUT;					// Trigger transmission on timeout (Periodic cycling)
	config[5].trigger.timeout = 0;							// Transmit continously
	chsnprintf(config[5].ssdv_config.callsign, 6, "DL7AD"); // SSDV Callsign
	config[5].ssdv_config.res = RES_UXGA;					// Resolution QVGA
	MODULE_IMAGE(&config[5]);

	// Module IMAGE, SSDV 2m 2FSK
	/*chsnprintf(config[6].instance_name, 12, "IMG 2FSK 2m");// Instance name
	config[6].power = 10;									// Power 10 dBm
	config[6].protocol = PROT_SSDV_2FSK;					// Protocol SSDV, modulation 2FSK
	config[6].frequency.type = FREQ_STATIC;					// Static frequency allocation
	config[6].frequency.hz = 145300000;						// Transmission frequency 145.300 MHz
	config[6].init_delay = 0;								// Module startup delay in sec
	config[6].packet_spacing = 0;							// Packet spacing in ms
	config[6].sleep.types[0] = SLEEP_WHEN_VBAT_BELOW_THRES; // Sleep when battery below threshold
	config[6].sleep.vbat_thres = 3500;						// Battery voltage threshold 3000mV
	config[6].trigger.type = TRIG_TIMEOUT;					// Trigger transmission on timeout (Periodic cycling)
	config[6].trigger.timeout = 0;							// Transmit continously
	config[6].fsk_config.bits = 8;							// 8bit
	config[6].fsk_config.stopbits = 2;						// 2 Stopbits
	config[6].fsk_config.predelay = 0;						// Predelay in ms (continuos carrier before actual transmission)
	config[6].fsk_config.baud = 600;						// Baudrate
	config[6].fsk_config.shift = 1000;						// Frequency shift in Hz
	chsnprintf(config[6].ssdv_config.callsign, 6, "DL7AD"); // SSDV Callsign
	config[6].ssdv_config.res = RES_QVGA;					// Resolution QVGA
	MODULE_IMAGE(&config[6]);*/
}














