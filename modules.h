#ifndef __MODULES_H__
#define __MODULES_H__

#include "position.h"
#include "image.h"
#include "tracking.h"
#include "satellite.h"
#include "log.h"
#include "radio.h"
#include "sgp4.h"

#define ARG2PARM(NAME,CYCLE,SLEEP,FREQ,PWR,PROT) \
	module_params_t* parm = chHeapAlloc(NULL, sizeof(module_params_t)); \
	parm->name = NAME; \
	parm->cycle = CYCLE; \
	parm->frequencyMethod = FREQ; \
	parm->power = PWR; \
	parm->protocol = PROT; \
	parm->sleepMethod = SLEEP;

#define MODULE_POSITION(CYCLE,SLEEP,FREQ,PWR,PROT) { \
	ARG2PARM("POS", CYCLE,SLEEP,FREQ,PWR,PROT); \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), NORMALPRIO, modulePOS, parm); \
	modules[moduleCount++] = parm; \
}

#define MODULE_SATELLITE(CYCLE,SLEEP,FREQ,PWR,PROT) { \
	ARG2PARM("SAT", CYCLE,SLEEP,FREQ,PWR,PROT); \
	parm->sleepMethod = sgp4_visible; \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), NORMALPRIO, moduleSAT, parm); \
	modules[moduleCount++] = parm; \
}

#define MODULE_IMAGE(CYCLE,SLEEP,FREQ,PWR,PROT) { \
	ARG2PARM("IMG", CYCLE,SLEEP,FREQ,PWR,PROT); \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(8192), HIGHPRIO, moduleIMG, parm); \
	modules[moduleCount++] = parm; \
}

#define MODULE_LOG(CYCLE,SLEEP,FREQ,PWR,PROT) { \
	ARG2PARM("LOG", CYCLE,SLEEP,FREQ,PWR,PROT); \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), NORMALPRIO, moduleLOG, parm); \
	modules[moduleCount++] = parm; \
}

#define MODULE_TRACKING(CYCLE) { \
	module_params_t* parm = chHeapAlloc(NULL, sizeof(module_params_t)); \
	parm->cycle = CYCLE; \
	parm->name = "TRAC"; \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(2048), NORMALPRIO, moduleTRACKING, parm); \
	modules[moduleCount++] = parm; \
}

#define MODULE_RADIO() { \
	module_params_t* parm = chHeapAlloc(NULL, sizeof(module_params_t)); \
	parm->cycle = 30; /* only relevant for the watchdog monitor */ \
	parm->name = "RAD"; \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), HIGHPRIO, moduleRADIO, parm); \
	modules[moduleCount++] = parm; \
}

#define initModules() MODULES()
#define initEssentialModules() { \
	MODULE_TRACKING(CYCLE_TIME); /* Tracker data input */ \
	MODULE_RADIO(); /* Tracker data output */ \
	chThdSleepMilliseconds(1000); \
}

#define MODULE_SD() (void)0; /* TODO */

extern char *SMODE_STRING[];
extern char *MOULATION_STRING[];
extern char *PROTOCOL_STRING[];
#define VAL2SMODE(v) SMODE_STRING[v]			/* Returns sleep as string */
#define VAL2MOULATION(v) MOULATION_STRING[v]	/* Returns modulation as string */
#define VAL2PROTOCOL(v) PROTOCOL_STRING[v]		/* Returns protocol as string */

typedef struct {
	char* name;					// Name of this module
	int32_t cycle;				// Cycletime in seconds
	uint8_t power;				// Radio power in dBm
	void* frequencyMethod;		// Method which returns the frequency
	prot_t protocol;			// Protocol/Modulation (APRS_AFSK, SSDV_2FSK, SSDV_APRS_AFSK, ...)
	void* sleepMethod;			// Method which returns MOD_ACTIVE or MOD_SLEEP
	systime_t lastCycle;		// Last cycle time
} module_params_t;

extern module_params_t *modules[16];
extern uint8_t moduleCount;

#endif
