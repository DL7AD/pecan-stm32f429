#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "defines.h"
#include "modules.h"

// Hardware definitions (which cant be changed easily)
#define OSC_FREQ				26000000		/* Oscillator frequency */
#define CAM_AVAIL				TRUE			/* Camera available */
#define GPS_AVAIL				TRUE			/* uBlox MAX7/8 GNSS receiver available */
#define SD_AVAIL				TRUE			/* microSD card available */
#define RADIO1_AVAIL			TRUE			/* Radio 1 available */
#define RADIO2_AVAIL			TRUE			/* Radio 2 available */
#define BME280_AVAIL			TRUE			/* BME280 air pressure sensor available */
#define MPU9250_AVAIL			TRUE			/* MPU9250 9 axis sensor available */
#define PAC1720_AVAIL			TRUE			/* PAC1720 current sensor available */

#define RADIO1_MIN_FREQ			144000000		/* Min. Frequency range of Radio 1 */
#define RADIO1_MAX_FREQ			148000000		/* Min. Frequency range of Radio 1 */
#define RADIO2_MIN_FREQ			420000000		/* Min. Frequency range of Radio 2 */
#define RADIO2_MAX_FREQ			450000000		/* Min. Frequency range of Radio 2 */

// User configurations
#define APRS_CALLSIGN			"DL7AD"			/* APRS callsign */
#define APRS_SSID				11				/* APRS SSID */
#define APRS_SYMBOL				SYM_BALLOON		/* APRS symbol */
#define APRS_PATH				"WIDE1,WIDE2-1"	/* APRS path */
#define APRS_PATH_SAT			"RS0ISS"		/* APRS path */
#define APRS_TXDELAY			200				/* APRS preamble length in ms */

#define FSK_CALLSIGN			"D-11"			/* FSK callsign for RTTY and DominoEX */

#define GPS_FIX_TIMEOUT			5				/* GPS fix gets outdated after */

#define LOG_SIZE				14				/* Log size in days */
#define LOG_CYCLE				120				/* Log cycle in minutes */
#define LOG_TRX_NUM				6				/* Log message that are transmitted in one packet */

#define SAT_TLE1 				"1 25544U 98067A   15353.57439117  .00014117  00000-0  21367-3 0  9990" /* ISS (ZARYA) */
#define SAT_TLE2 				"2 25544  51.6441 238.8813 0008350 299.4829 139.1404 15.54920935976888"

// Module definitions (can be any number of modules)
#if 0
#define MODULES() { \
	MODULE_SD(); \
	chThdSleepMilliseconds(100); \
	MODULE_CAM(); \
	chThdSleepMilliseconds(100); \
	MODULE_GPS(); \
	chThdSleepMilliseconds(100); \
	MODULE_SEN(); \
	chThdSleepMilliseconds(100); \
	MODULE_RADIO(); \
	\
	MODULE_POSITION(120, NULL, APRS_REGION_FREQ, 10, MOD_AFSK, PROT_APRS); \
	chThdSleepMilliseconds(100); \
	MODULE_TELEMETRY(120, NULL, APRS_REGION_FREQ, 10, MOD_AFSK, PROT_APRS); \
	chThdSleepMilliseconds(100); \
	MODULE_LOG(120, NULL, APRS_REGION_FREQ, 10, MOD_AFSK, PROT_APRS); \
	chThdSleepMilliseconds(100); \
	\
	MODULE_SATELLITE(60, NULL, APRS_ISS_FREQ, 33, MOD_AFSK, PROT_APRS, SAT_TLE1, SAT_TLE2); \
	chThdSleepMilliseconds(100); \
	\
	MODULE_IMAGE(300, NULL, CUSTOM_FREQ, 10, MOD_2FSK, PROT_SSDV); \
	chThdSleepMilliseconds(100); \
	MODULE_TELEMETRY(20, NULL, CUSTOM_FREQ, 10, MOD_2FSK, PROT_UKHAS); \
	chThdSleepMilliseconds(100); \
}
#endif

#define MODULES() { \
	MODULE_GPS(); \
	chThdSleepMilliseconds(100); \
	MODULE_RADIO(); \
	chThdSleepMilliseconds(100); \
	\
	MODULE_POSITION(120, NULL, APRS_REGION_FREQ, 10, MOD_AFSK, PROT_APRS); \
	chThdSleepMilliseconds(100); \
}

#endif










