#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "defines.h"
#include "modules.h"
#include "padc.h"
#include "board_pecanpico7a/board.h"

/* -------------------------------------------------------------- Protocols ------------------------------------------------------------- */

// APRS configuration
#define APRS_CALLSIGN			"DL7AD"			/* APRS callsign */
#define APRS_SSID				11				/* APRS SSID */
#define APRS_SYMBOL				SYM_BALLOON		/* APRS symbol */
#define APRS_PATH				"WIDE1,WIDE2-1"	/* APRS path */
#define APRS_PATH_SAT			"RS0ISS"		/* APRS path */

// SSDV configuration
#define SSDV_CALLSIGN			"D-9"			/* SSDV callsign */

// UKHAS configuration
#define UKHAS_CALLSIGN			"D-9"			/* UKHAS callsign */
#define UKHAS_FORMAT			"<CALL>,<ID>,<TIME>,<LAT>,<LON>,<ALT>,<SATS>,<TTFF>,<VBAT>,<VSOL>,<CHARGE>,<IPRESS>,<ITEMP>,<IHUM>,<EPRESS>,<ETEMP>,<EHUM>"

// CW configuration
#define CW_CALLSIGN				"D-9"			/* CW callsign */
#define CW_FORMAT				"<CALL> <LOC> <ALT>M PSE QSL"

// Log configuration
#define LOG_SIZE				14				/* Log size in days */
#define LOG_CYCLE				120				/* Log cycle in minutes */
#define LOG_TRX_NUM				6				/* Log message that are transmitted in one packet */

// Sat configuration
#define SAT_TLE1 				"1 25544U 98067A   15353.57439117  .00014117  00000-0  21367-3 0  9990" /* ISS (ZARYA) */
#define SAT_TLE2 				"2 25544  51.6441 238.8813 0008350 299.4829 139.1404 15.54920935976888"

/* ------------------------------------------------------------- Modulation ------------------------------------------------------------- */

// AFSK configuration
#define AFSK_TXDELAY			200				/* APRS preamble length in ms */

// 2FSK configuration
#define FSK_PREDELAY			0				/* 2FSK pre-transmission delay */
#define FSK_POSTDELAY			0				/* 2FSK post-transmission delay */
#define FSK_BAUD				600				/* 2FSK baudrate */
#define FSK_SHIFT				1000			/* 2FSK baudrate */
#define FSK_STOPBITS			2				/* 2FSK stopbits */
#define FSK_ASCII				8				/* 2FSK bits */

// CW configuration
#define CW_SPEED				20				/* CW Speed in WpM TODO: Not supported yet */

/* --------------------------------------------------------------- Modules -------------------------------------------------------------- */

// Radio
#define RADIO_TIMEOUT			300				/* Radio transmission timeout in ms (radio switched off after x ms in idling) */

// Tracking manager
#define CYCLE_TIME				60				/* Tracking cycle */

#define MODULES() { \
                  /* Cycle (sec)  Sleep                       Frequency         Power Protocol       */ \
	MODULE_IMAGE    (0,           SLEEP_WHEN_BATT_BELOW_3V5,  CUSTOM_FREQ,      10,   PROT_SSDV_2FSK ); \
	MODULE_POSITION (60,          SLEEP_WHEN_BATT_BELOW_3V0,  CUSTOM_FREQ,      10,   PROT_UKHAS_2FSK); \
/*	MODULE_POSITION (120,         SLEEP_WHEN_BATT_BELOW_3V0,  CUSTOM_FREQ,      10,   PROT_RAW_CW    );*/ \
/*	MODULE_SATELLITE(60,          SLEEP_WHEN_ISS_NOT_VISIBLE, APRS_ISS_FREQ,    33,   PROT_APRS_AFSK );*/ \
/*	MODULE_LOG      (120,         SLEEP_WHEN_BATT_BELOW_3V3,  APRS_REGION_FREQ, 10,   PROT_APRS_AFSK );*/ \
}

#endif

