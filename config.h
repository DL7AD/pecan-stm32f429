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

#define CHECK_RADIO1_BAND(f)	(144000000 <= f && f <= 148000000) /* Frequency range of Radio 1 */
#define CHECK_RADIO2_BAND(f)	(420000000 <= f && f <= 450000000) /* Frequency range of Radio 2 */


// User configurations
#define APRS_CALLSIGN			"DL7AD"			/* APRS callsign */
#define APRS_SSID				11				/* APRS SSID */
#define APRS_SYMBOL				SYM_BALLOON		/* APRS symbol */
#define APRS_PATH				"WIDE1,WIDE2-1"	/* APRS path */
#define APRS_PATH_SAT			"RS0ISS"		/* APRS path */
#define APRS_TXDELAY			200				/* APRS preamble length */

#define FSK_CALLSIGN			"D-11"			/* FSK callsign for RTTY and DominoEX */

#define GPS_ACQUISITION_TIMEOUT	120				/* GPS acquisition timeout */
#define GPS_FIX_TIMEOUT			120				/* GPS fix gets outdated after */

#define LOG_SIZE				14				/* Log size in days */
#define LOG_CYCLE				120				/* Log cycle in minutes */
#define LOG_TRX_NUM				6				/* Log message that are transmitted in one packet */

#define SAT_TLE1 				"1 25544U 98067A   15353.57439117  .00014117  00000-0  21367-3 0  9990" /* ISS (ZARYA) */
#define SAT_TLE2 				"2 25544  51.6441 238.8813 0008350 299.4829 139.1404 15.54920935976888"

// Module definitions (can be any number of modules)
#define MODULES() { \
	MODULE_SD(); \
	chThdSleepMilliseconds(1); \
	MODULE_CAM(); \
	chThdSleepMilliseconds(1); \
	MODULE_GPS(); \
	chThdSleepMilliseconds(1); \
	MODULE_SEN(); \
	chThdSleepMilliseconds(1); \
	MODULE_RADIO(); \
	chThdSleepMilliseconds(1); \
	\
	module_params_t pos,tel,log,sat,img,te2; \
	MODULE_POS(pos, 120, NULL, APRS_REGION_FREQ, 10, MOD_AFSK, PROT_APRS); \
	chThdSleepMilliseconds(1); \
	MODULE_TEL(tel, 120, NULL, APRS_REGION_FREQ, 10, MOD_AFSK, PROT_APRS); \
	chThdSleepMilliseconds(1); \
	MODULE_LOG(log, 120, NULL, APRS_REGION_FREQ, 10, MOD_AFSK, PROT_APRS); \
	chThdSleepMilliseconds(1); \
	\
	MODULE_SAT(sat, 60,  NULL, APRS_ISS_FREQ, 33, MOD_AFSK, PROT_APRS, SAT_TLE1, SAT_TLE2); \
	chThdSleepMilliseconds(1); \
	\
	MODULE_IMG(img, 1,   NULL, CUSTOM_FREQ, 10, MOD_2FSK, PROT_SSDV); \
	chThdSleepMilliseconds(1); \
	MODULE_TEL(te2, 20,  NULL, CUSTOM_FREQ, 10, MOD_2FSK, PROT_UKHAS); \
}

#endif
