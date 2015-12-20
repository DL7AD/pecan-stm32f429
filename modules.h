#ifndef __MODULES_H__
#define __MODULES_H__

#include "modules/pos.h"
#include "modules/img.h"
#include "modules/gps.h"
#include "modules/sat.h"
#include "modules/tel.h"
#include "modules/log.h"
#include "sgp4.h"
#include "radio.h"

#define MODULE_POS(CYCLE,PWRSAVE,FREQ,PWR,MOD,PROT) { \
	module_params_t parm; \
	parm.cycletime = CYCLE; \
	parm.frequency = FREQ; \
	parm.power = PWR; \
	parm.modulation = MOD; \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), NORMALPRIO, modulePOS, &parm); \
}

#define MODULE_SAT(CYCLE,PWRSAVE,FREQ,PWR,MOD,PROT,TLE1,TLE2) { \
	module_params_t parm; \
	parm.cycletime = CYCLE; \
	parm.frequency = FREQ; \
	parm.power = PWR; \
	parm.modulation = MOD; \
	parm.cycleMethod = sgp4_visible; \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), NORMALPRIO, moduleSAT, &parm); \
}

#define MODULE_TEL(CYCLE,PWRSAVE,FREQ,PWR,MOD,PROT) { \
	module_params_t parm; \
	parm.cycletime = CYCLE; \
	parm.frequency = FREQ; \
	parm.power = PWR; \
	parm.modulation = MOD; \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), NORMALPRIO, moduleTEL, &parm); \
}

#define MODULE_IMG(CYCLE,PWRSAVE,FREQ,PWR,MOD,PROT) { \
	module_params_t parm; \
	parm.cycletime = CYCLE; \
	parm.frequency = FREQ; \
	parm.power = PWR; \
	parm.modulation = MOD; \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), NORMALPRIO, moduleIMG, &parm); \
}

#define MODULE_LOG(CYCLE,PWRSAVE,FREQ,PWR,MOD,PROT) { \
	module_params_t parm; \
	parm.cycletime = CYCLE; \
	parm.frequency = FREQ; \
	parm.power = PWR; \
	parm.modulation = MOD; \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), NORMALPRIO, moduleLOG, &parm); \
}

#define MODULE_GPS() { \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), NORMALPRIO, moduleGPS, NULL); \
}

#define MODULE_SD() (void)0; /* TODO */
#define MODULE_CAM() (void)0; /* TODO */
#define MODULE_SEN() (void)0; /* TODO */

typedef enum {
	MOD_ACTIVE,
	MOD_SLEEP
} pmode_t;

typedef enum {
	MOD_2FSK,
	MOD_AFSK
} modulation_t;

typedef enum {
	PWR_1MW,
	PWR_10MW,
	PWR_50MW,
	PWR_100MW,
	PWR_1W,
	PWR_2W
} power_t;

typedef struct {
	int32_t cycletime; // 0=continuous, -1=refer to cycleMethod
	void* cycleMethod;
	power_t power;
	void* frequency;
	modulation_t modulation;
	void* sleepMethod;
} module_params_t;

#endif
