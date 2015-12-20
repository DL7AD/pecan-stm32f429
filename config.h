#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "defines.h"

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
#define MODULES { \
	MODULE_SD(); \
	MODULE_CAM(); \
	MODULE_GPS(); \
	MODULE_SEN(); \
	\
	MODULE_POS(120, SLEEP_BELOW_BATTVOLT(2.7), APRS_REGION_FREQ, PWR_10MW, MOD_AFSK, PROT_APRS); \
	MODULE_TEL(120, SLEEP_BELOW_BATTVOLT(2.7), APRS_REGION_FREQ, PWR_10MW, MOD_AFSK, PROT_APRS); \
	MODULE_LOG(120, SLEEP_BELOW_BATTVOLT(3.3), APRS_REGION_FREQ, PWR_10MW, MOD_AFSK, PROT_APRS); \
	\
	MODULE_SAT(60,  SLEEP_BELOW_BATTVOLT(3.0), 145825000, PWR_2W, MOD_AFSK, PROT_APRS, SAT_TLE1, SAT_TLE2); \
	\
	MODULE_IMG(0, SLEEP_BELOW_SOLBATTVOLT(0.5, 4.0), 434500000, PWR_10MW, MOD_2FSK, PROT_SSDV); \
	MODULE_TEL(20, SLEEP_BELOW_SOLBATTVOLT(0.5, 4.0), 434500000, PWR_10MW, MOD_2FSK, PROT_UKHAS); \
}

#endif
