#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "defines.h"
#include "modules.h"
#include "board_pecanpico7a/board.h"

// Tracking manager
#define CYCLE_TIME				120				/* Tracking cycle */

// APRS configuration
#define APRS_CALLSIGN			"DL7AD"			/* APRS callsign */
#define APRS_SSID				11				/* APRS SSID */
#define APRS_SYMBOL				SYM_BALLOON		/* APRS symbol */
#define APRS_PATH				"WIDE1,WIDE2-1"	/* APRS path */
#define APRS_PATH_SAT			"RS0ISS"		/* APRS path */
#define APRS_TXDELAY			200				/* APRS preamble length in ms */

// FSK configuration
#define FSK_CALLSIGN			"D-11"			/* UKHAS callsign for RTTY or DominoEX */
#define FSK_PREDELAY			500				/* 2FSK pre-transmission delay */
#define FSK_POSTDELAY			100				/* 2FSK post-transmission delay */
#define FSK_BAUD				600				/* 2FSK baudrate */
#define FSK_STOPBITS			2				/* 2FSK stopbits */
#define FSK_ASCII				8				/* 2FSK bits */

// Log configuration
#define LOG_SIZE				14				/* Log size in days */
#define LOG_CYCLE				120				/* Log cycle in minutes */
#define LOG_TRX_NUM				6				/* Log message that are transmitted in one packet */

// Sat configuration
#define SAT_TLE1 				"1 25544U 98067A   15353.57439117  .00014117  00000-0  21367-3 0  9990" /* ISS (ZARYA) */
#define SAT_TLE2 				"2 25544  51.6441 238.8813 0008350 299.4829 139.1404 15.54920935976888"

#define MODULES() { \
                  /* Cycle Sleep Frequency         Power Protocol       */ \
	MODULE_IMAGE    (300,  NULL, CUSTOM_FREQ,      10,   PROT_SSDV_2FSK ); \
/*	MODULE_POSITION (120,  NULL, CUSTOM_FREQ,      10,   PROT_UKHAS_2FSK);*/ \
	MODULE_SATELLITE(60,   NULL, APRS_ISS_FREQ,    33,   PROT_APRS_AFSK ); \
	MODULE_LOG      (120,  NULL, APRS_REGION_FREQ, 10,   PROT_APRS_AFSK ); \
}

#endif

