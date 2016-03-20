#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "defines.h"
#include "modules.h"
#include "sleep.h"
#include "board_pecanpico7a/board.h"

/* -------------------------------------------------------------- Protocols ------------------------------------------------------------- */

// APRS configuration
#define APRS_CALLSIGN			"DL7AD"			/* APRS callsign */
#define APRS_SSID				12				/* APRS SSID */
#define APRS_SYMBOL				SYM_BALLOON		/* APRS symbol (options: SYM_BALLOON, SYM_SMALLAIRCRAFT, SYM_SATELLITE) */
#define APRS_PATH				"WIDE1"			/* APRS path (does not apply for APRS images)
												 * Multiple path's can be separated with comma e.g. WIDE1-1,WIDE2-2 */
#define APRS_PATH_SAT			"RS0ISS"		/* APRS path */
#define APRS_DEFAULT_FREQ		144800000		/* APRS default frequency (for region method if no GPS location unknown) */

// SSDV configuration
#define SSDV_CALLSIGN			"DL7AD-12"		/* SSDV callsign */

// UKHAS configuration
#define UKHAS_CALLSIGN			"DL7AD-12"		/* UKHAS callsign */
#define UKHAS_FORMAT			"<CALL>,<ID>,<TIME>,<LAT>,<LON>,<ALT>,<SATS>,<TTFF>,<VBAT>,<VSOL>,<CHARGE>,<DISCHARGE>,<IPRESS>,<ITEMP>,<IHUM>"
                                                /* UKHAS format, possible params:
                                                 * <ID> Tracking manager serial ID
                                                 * <DATE> GPS date (Format YYYY-MM-DD)
                                                 * <TIME> GPS time (Format HH:MM:SS)
                                                 * <LAT> Latitude (Format: 0.0000000)
                                                 * <LON> Longitude (Format: 0.0000000)
                                                 * <ALT> Altitude in meters (no decimals)
                                                 * <SATS> Amount of GPS satellites being used for fix
                                                 * <TTFF> Time to first fix (or how long did it take to sample the fix after GPS was switched on)
                                                 * <VBAT> Battery voltage in Volts (Format: 0.00)
                                                 * <VSOL> Solar voltage in Volts (Format: 0.00)
                                                 * <CHARGE> Solar battery charge in Watt (Format: [-]0.000), positive value: charging, negative value, discharging
                                                 * <IPRESS> Internal airpressure (From BME280 on PCB)
                                                 * <ITEMP> Internal temperature (From BME280 on PCB)
                                                 * <IHUM> Internal humidity (From BME280 on PCB)
                                                 * <EPRESS> External airpressure (From BME280 attached to I2C pinheader)
                                                 * <ETEMP> External temperature (From BME280 attached to I2C pinheader)
                                                 * <EHUM> External humidity (From BME280 attached to I2C pinheader)
                                                 * <LOC> Maidenhead Locator (6 char)
                                                 */

// CW configuration
#define CW_CALLSIGN				"D-9"			/* CW callsign */
#define CW_FORMAT				"<CALL> <LOC> <ALT>M PSE QSL" /* CW format, the same params can be used as it's the case for the UKHAS protocol */

// Log configuration
#define LOG_SIZE				14				/* Log size in days */
#define LOG_CYCLE				120				/* Log cycle in minutes */
#define LOG_TRX_NUM				6				/* Amount of log messages which are transmitted in one packet */

/* ------------------------------------------------------------- Modulation ------------------------------------------------------------- */

// AFSK configuration
#define AFSK_PREAMBLE			300				/* APRS AFSK preamble length in ms */

// 2GFSK configuration
#define GFSK_PREAMBLE			50				/* APRS 2GFSK preamble length in ms */

// 2FSK configuration
#define FSK_PREDELAY			0				/* 2FSK pre-transmission delay */
#define FSK_POSTDELAY			0				/* 2FSK post-transmission delay */
#define FSK_BAUD				600				/* 2FSK baudrate */
#define FSK_SHIFT				1000			/* 2FSK baudrate */
#define FSK_STOPBITS			2				/* 2FSK stopbits */
#define FSK_ASCII				8				/* 2FSK bits */

// CW configuration
#define CW_SPEED				20				/* CW Speed in WpM */

/* --------------------------------------------------------------- Modules -------------------------------------------------------------- */

// Radio
#define RADIO_TIMEOUT			300				/* Radio transmission timeout in ms (radio switched off after x ms in idling) */

// Tracking manager
#define CYCLE_TIME				60				/* Tracking cycle (all peripheral data [airpressure, GPS, temperature, ...] is collected each x seconds */


/*
 * Below all operation activities (modules) of the tracker will be configured. The modules must be
 * inserted in the MODULES() macro. It's allowed to use the same modules multiple times. All options
 * of the params are listed and described below.
 * 
 * MODULE_IMAGE(trigger, sleep, frequency, power, protocol)
 * ----------------------------------------------------------------------------------------------------
 * PARAM trigger:   TX_CONTINUOSLY               Generates a new picture once old is transmitted completely
 *                  <integer>                    Cyclic operation (e.g. 60 => one picture is transmitted every 60 seconds)
 * PARAM sleep:     SLEEP_WHEN_BATT_BELOW_2V9    Module hibernates when battery voltage below 2.9V
 *                  SLEEP_WHEN_BATT_BELOW_3V0    Module hibernates when battery voltage below 3.0V
 *                  SLEEP_WHEN_BATT_BELOW_3V1    Module hibernates when battery voltage below 3.1V
 *                  ...
 *                  SLEEP_WHEN_BATT_BELOW_4V1    Module hibernates when battery voltage below 4.1V
 *                  SLEEP_WHEN_ISS_NOT_VISIBLE   Module hibernates when ISS not visible (requires TLE) TODO: Not implemented yet
 *                  NO_SLEEP                     Sleep disabled
 * PARAM frequency: CUSTOM_FREQ                  Transmit on 434.500 MHz
 *                  APRS_REGION_FREQ             Transmit on regional APRS frequency
 *                  APRS_ISS_FREQ                Transmit on 145.825 MHz (Doppler not considered)
 * PARAM power:     <integer>                    Transmission power in dBm (e.g. 7 for 7dBm = 5mW)
 * PARAM protocol:  PROT_SSDV_2FSK               Transmission by 2FSK (See 2FSK modulation configuration)
 *                  PROT_SSDV_APRS_AFSK          Transmission by APRS AFSK 1k2
 * 
 * MODULE_POSITION(trigger, sleep, frequency, power, protocol)
 * ----------------------------------------------------------------------------------------------------
 * PARAM trigger:   TX_CONTINUOSLY               Generates a new packet once old is transmitted completely
 *                  WAIT_FOR_TRACKING_POINT      Waits for tracking manager getting a new track point published
 *                  <integer>                    Cyclic operation (e.g. 60 => position is transmitted every 60 seconds)
 * PARAM sleep:     SLEEP_WHEN_BATT_BELOW_2V9    Module hibernates when battery voltage below 2.9V
 *                  SLEEP_WHEN_BATT_BELOW_3V0    Module hibernates when battery voltage below 3.0V
 *                  SLEEP_WHEN_BATT_BELOW_3V1    Module hibernates when battery voltage below 3.1V
 *                  ...
 *                  SLEEP_WHEN_BATT_BELOW_4V1    Module hibernates when battery voltage below 4.1V
 *                  SLEEP_WHEN_ISS_NOT_VISIBLE   Module hibernates when ISS not visible (requires TLE) TODO: Not implemented yet
 *                  NO_SLEEP                     Sleep disabled
 * PARAM frequency: CUSTOM_FREQ                  Transmit on 434.500 MHz
 *                  APRS_REGION_FREQ             Transmit on regional APRS frequency
 *                  APRS_ISS_FREQ                Transmit on 145.825 MHz (Doppler not considered)
 * PARAM power:     <integer>                    Transmission power in dBm (e.g. 7 for 7dBm = 5mW)
 * PARAM protocol:  PROT_APRS_2GFSK              Transmission by APRS 2GFSK 9k6 (FIXME: 2GFSK not decodeable yet)
 *                  PROT_APRS_AFSK               Transmission by APRS AFSK 1k2
 *                  PROT_UKHAS_2FSK              Transmission by specific UKHAS protocol in 2FSK (See 2FSK modulation and UKHAS format configuration)
 *                  PROT_RAW_CW                  Transmission by specific CW protocol (See CW modulation and CW format configuration)
 *                  PROT_APRSCONFIG_AFSK         Transmit APRS telemetry encoding definition (conversion formulae) in AFSK
 *                  PROT_APRSCONFIG_2GFSK        Transmit APRS telemetry encoding definition (conversion formulae) in 2GFSK
 *
 * MODULE_LOG(trigger, sleep, frequency, power, protocol) (TODO: Not implemented yet!)
 * ----------------------------------------------------------------------------------------------------
 * PARAM trigger:   TX_CONTINUOSLY               Generates a new packet once old is transmitted completely
 *                  WAIT_FOR_TRACKING_POINT      Waits for tracking manager getting a new track point published
 *                  <integer>                    Cyclic operation (e.g. 3600 => log is transmitted every 3600 seconds)
 * PARAM sleep:     SLEEP_WHEN_BATT_BELOW_2V9    Module hibernates when battery voltage below 2.9V
 *                  SLEEP_WHEN_BATT_BELOW_3V0    Module hibernates when battery voltage below 3.0V
 *                  SLEEP_WHEN_BATT_BELOW_3V1    Module hibernates when battery voltage below 3.1V
 *                  ...
 *                  SLEEP_WHEN_BATT_BELOW_4V1    Module hibernates when battery voltage below 4.1V
 *                  SLEEP_WHEN_ISS_NOT_VISIBLE   Module hibernates when ISS not visible (requires TLE) TODO: Not implemented yet
 *                  NO_SLEEP                     Sleep disabled
 * PARAM frequency: CUSTOM_FREQ                  Transmit on 434.500 MHz
 *                  APRS_REGION_FREQ             Transmit on regional APRS frequency
 *                  APRS_ISS_FREQ                Transmit on 145.825 MHz (Doppler not considered)
 * PARAM power:     <integer>                    Transmission power in dBm (e.g. 7 for 7dBm = 5mW)
 * PARAM protocol:  TODO: not specified yet
 *
 */

#define MODULES() { \
                  /* Cycle (sec) or Trigger   Sleep                       Frequency         Power Protocol              */ \
	MODULE_IMAGE    (600,                     SLEEP_WHEN_BATTERY_LOW,     CUSTOM_FREQ,      13,   PROT_SSDV_2FSK      ); \
/*	MODULE_IMAGE    (TX_CONTINUOSLY,          NO_SLEEP,                   CUSTOM_FREQ,      10,   PROT_SSDV_APRS_AFSK );*/ \
/*	MODULE_POSITION (WAIT_FOR_TRACKING_POINT, SLEEP_WHEN_BATTERY_LOW,     CUSTOM_FREQ,      10,   PROT_UKHAS_2FSK     );*/ \
/*	MODULE_POSITION (WAIT_FOR_TRACKING_POINT, SLEEP_WHEN_BATT_BELOW_3V0,  CUSTOM_FREQ,      10,   PROT_RAW_CW         );*/ \
	MODULE_POSITION (3600,                    NO_SLEEP,                   APRS_REGION_FREQ, 10,   PROT_APRSCONFIG_AFSK); \
	MODULE_POSITION (WAIT_FOR_TRACKING_POINT, NO_SLEEP,                   APRS_REGION_FREQ, 10,   PROT_APRS_AFSK      ); \
/*	MODULE_POSITION (WAIT_FOR_TRACKING_POINT, SLEEP_WHEN_BATT_BELOW_3V0,  CUSTOM_FREQ,      10,   PROT_APRS_2GFSK     );*/ /* TODO: Not working yet */ \
/*	MODULE_LOG      (120,                     SLEEP_WHEN_BATT_BELOW_3V3,  APRS_REGION_FREQ, 10,   PROT_APRS_AFSK      );*/ /* TODO: Not implemented yet */ \
}

/* ------------------------------------------------------------ Miscellaneous ----------------------------------------------------------- */

// Sat configuration
#define SAT_TLE1 				"1 25544U 98067A   15353.57439117  .00014117  00000-0  21367-3 0  9990" /* ISS (ZARYA) */
#define SAT_TLE2 				"2 25544  51.6441 238.8813 0008350 299.4829 139.1404 15.54920935976888"


#endif





