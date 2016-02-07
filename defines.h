#ifndef __DEFINES_H__
#define __DEFINES_H__

#include "ch.h"
#include "hal.h"

#define CONCAT(A,B)         A ## B
#define EXPAND_CONCAT(A,B)  CONCAT(A, B)

#define ARG_0(A0, ...)      A0
#define ARG_1(A0, A1, ...)  A1
#define ARGN(N, LIST)       EXPAND_CONCAT(ARG_, N) LIST

#define SYM_GET_TABLE(A)	ARGN(0, A)
#define SYM_GET_SYMBOL(A)	ARGN(1, A)
#define PORT(A)				ARGN(0, A)
#define PIN(A)				ARGN(1, A)

#define APRS_REGION_FREQ			getAPRSRegionFrequency
#define APRS_ISS_FREQ				getAPRSISSFrequency
#define CUSTOM_FREQ					getCustomFrequency
#define SYM_BALLOON					('/', 'O')
#define SYM_SMALLAIRCRAFT			('/', '\'')
#define SYM_SATELLITE				('\\', 'S')

// Sleep definitions
#define SLEEP_BELOW_BATTVOLT(v)				(getBatteryVoltage() < (v) ? MOD_SLEEP : MOD_ACTIVE)
#define SLEEP_BELOW_SOLVOLT(v)				(getSolarVoltage() < (v) ? MOD_SLEEP : MOD_ACTIVE)
#define SLEEP_BELOW_SOLBATTVOLT(sol, batt)	(getSolarVoltage() < (sol) || getBatteryVoltage() < (batt) ? MOD_SLEEP : MOD_ACTIVE)

#define RADIO_2M	1	/* Radio 1 => 2m */
#define RADIO_70CM	2	/* Radio 2 => 70cm */

#define HIGH	true
#define LOW		false

#define WAIT_FOR_TRACKING_POINT		-1

// Sleep mode type
typedef enum {
	MOD_ACTIVE,
	MOD_SLEEP
} smode_t;

// Protocol type
typedef enum {
	PROT_UKHAS_2FSK,
	PROT_UKHAS_DOMINOEX16,
	PROT_APRS_AFSK,
	PROT_SSDV_2FSK,
	PROT_SSDV_APRS_AFSK,
	PROT_RAW_CW
} prot_t;

#endif

