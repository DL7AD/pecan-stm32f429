#ifndef __MODULES_H__
#define __MODULES_H__

#include "modules/position.h"
#include "modules/image.h"
#include "modules/gps.h"
#include "modules/satellite.h"
#include "modules/telemetry.h"
#include "modules/log.h"
#include "modules/radio.h"
#include "sgp4.h"

#define ARG2PARM(CYCLE,SLEEP,FREQ,PWR,MOD,PROT) \
	module_params_t* parm = chHeapAlloc(NULL, sizeof(module_params_t)); \
	parm->cycle = CYCLE; \
	parm->frequencyMethod = FREQ; \
	parm->power = PWR; \
	parm->modulation = MOD; \
	parm->protocol = PROT; \
	parm->sleepMethod = SLEEP;

#define MODULE_POSITION(CYCLE,SLEEP,FREQ,PWR,MOD,PROT) { \
	ARG2PARM(CYCLE,SLEEP,FREQ,PWR,MOD,PROT); \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), NORMALPRIO, modulePOS, parm); \
}

#define MODULE_SATELLITE(CYCLE,SLEEP,FREQ,PWR,MOD,PROT,TLE1,TLE2) { \
	ARG2PARM(CYCLE,SLEEP,FREQ,PWR,MOD,PROT); \
	parm->sleepMethod = sgp4_visible; \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), NORMALPRIO, moduleSAT, parm); \
}

#define MODULE_TELEMETRY(CYCLE,SLEEP,FREQ,PWR,MOD,PROT) { \
	ARG2PARM(CYCLE,SLEEP,FREQ,PWR,MOD,PROT); \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), NORMALPRIO, moduleTEL, parm); \
}

#define MODULE_IMAGE(CYCLE,SLEEP,FREQ,PWR,MOD,PROT) { \
	ARG2PARM(CYCLE,SLEEP,FREQ,PWR,MOD,PROT); \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), NORMALPRIO, moduleIMG, parm); \
}

#define MODULE_LOG(CYCLE,SLEEP,FREQ,PWR,MOD,PROT) { \
	ARG2PARM(CYCLE,SLEEP,FREQ,PWR,MOD,PROT); \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), NORMALPRIO, moduleLOG, parm); \
}

#define MODULE_GPS() { \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), NORMALPRIO, moduleGPS, NULL); \
}

#define MODULE_RADIO() { \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), NORMALPRIO, moduleRADIO, NULL); \
}

#define MODULE_SD() (void)0; /* TODO */
#define MODULE_CAM() (void)0; /* TODO */
#define MODULE_SEN() (void)0; /* TODO */

typedef enum {
	MOD_ACTIVE,
	MOD_SLEEP
} smode_t;

typedef enum {
	MOD_2FSK,
	MOD_AFSK
} modulation_t;

typedef enum {
	PROT_RAW,
	PROT_SSDV,
	PROT_APRS,
	PROT_UKHAS
} protocol_t;

typedef struct {
	char msg[256];
	uint32_t freq;
	modulation_t mod;
} radioMSG_t;

extern char *SMODE_STRING[];
extern char *MOULATION_STRING[];
extern char *PROTOCOL_STRING[];
#define VAL2SMODE(v) SMODE_STRING[v]
#define VAL2MOULATION(v) MOULATION_STRING[v]
#define VAL2PROTOCOL(v) PROTOCOL_STRING[v]

typedef struct {
	int32_t cycle;				// Cycletime in seconds
	uint8_t power;				// Radio power in dBm
	void* frequencyMethod;		// Method which returns the frequency
	modulation_t modulation;	// Modulation (2FSK, AFSK, ...)
	protocol_t protocol;		// Protocol (SSDV, APRS, ...)
	void* sleepMethod;			// Method which returns MOD_ACTIVE or MOD_SLEEP
} module_params_t;

#endif
