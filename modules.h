#ifndef __MODULES_H__
#define __MODULES_H__

#include "modules/pos.h"
#include "modules/img.h"
#include "modules/gps.h"
#include "modules/sat.h"
#include "modules/tel.h"
#include "modules/log.h"
#include "modules/radio.h"
#include "sgp4.h"

#define MODULE_POS(PARM,CYCLE,SLEEP,FREQ,PWR,MOD,PROT) { \
	PARM.cycle = CYCLE; \
	PARM.frequencyMethod = FREQ; \
	PARM.power = PWR; \
	PARM.modulation = MOD; \
	PARM.protocol = PROT; \
	PARM.sleepMethod = SLEEP; \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), NORMALPRIO, modulePOS, &PARM); \
}

#define MODULE_SAT(PARM,CYCLE,SLEEP,FREQ,PWR,MOD,PROT,TLE1,TLE2) { \
	PARM.cycle = CYCLE; \
	PARM.frequencyMethod = FREQ; \
	PARM.power = PWR; \
	PARM.modulation = MOD; \
	PARM.protocol = PROT; \
	PARM.sleepMethod = sgp4_visible; \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), NORMALPRIO, moduleSAT, &PARM); \
}

#define MODULE_TEL(PARM,CYCLE,SLEEP,FREQ,PWR,MOD,PROT) { \
	PARM.cycle = CYCLE; \
	PARM.frequencyMethod = FREQ; \
	PARM.power = PWR; \
	PARM.modulation = MOD; \
	PARM.sleepMethod = SLEEP; \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), NORMALPRIO, moduleTEL, &PARM); \
}

#define MODULE_IMG(PARM,CYCLE,SLEEP,FREQ,PWR,MOD,PROT) { \
	PARM.cycle = CYCLE; \
	PARM.frequencyMethod = FREQ; \
	PARM.power = PWR; \
	PARM.modulation = MOD; \
	PARM.protocol = PROT; \
	PARM.sleepMethod = SLEEP; \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), NORMALPRIO, moduleIMG, &PARM); \
}

#define MODULE_LOG(PARM,CYCLE,SLEEP,FREQ,PWR,MOD,PROT) { \
	PARM.cycle = CYCLE; \
	PARM.frequencyMethod = FREQ; \
	PARM.power = PWR; \
	PARM.modulation = MOD; \
	PARM.protocol = PROT; \
	PARM.sleepMethod = SLEEP; \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), NORMALPRIO, moduleLOG, &PARM); \
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

extern char *SMODE_STRING[];
extern char *MOULATION_STRING[];
extern char *PROTOCOL_STRING[];
#define VAL2SMODE(v) SMODE_STRING[v]
#define VAL2MOULATION(v) MOULATION_STRING[v]
#define VAL2PROTOCOL(v) PROTOCOL_STRING[v]

typedef struct {
	int32_t cycle; // Cycletime in seconds
	uint8_t power; // Radio power in dBm
	void* frequencyMethod; // Method which returns the frequency
	modulation_t modulation;
	protocol_t protocol;
	void* sleepMethod; // Method which returns MOD_ACTIVE or MOD_SLEEP
} module_params_t;

#endif
