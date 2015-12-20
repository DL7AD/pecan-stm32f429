#ifndef __DEFINES_H__
#define __DEFINES_H__

#include "ch.h"
#include "hal.h"

#define MODULE_POS(CYCLE,PWRSAVE,FREQ,PWR,MOD,PROT) { \
	module_params_t parm; \
	parm.cycletime = CYCLE; \
	parm.frequency = FREQ; \
	parm.power = PWR; \
	parm.modulation = MOD; \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), NORMALPRIO, modulePOS, parm); \
}

#define MODULE_SAT(CYCLE,PWRSAVE,FREQ,PWR,MOD,PROT,TLE1,TLE2) { \
	module_params_t parm; \
	parm.cycletime = CYCLE; \
	parm.frequency = FREQ; \
	parm.power = PWR; \
	parm.modulation = MOD; \
	parm.cycleMethod = sgp4_visible(TLE1, TLE2); \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), NORMALPRIO, moduleSAT, parm); \
}

#define MODULE_TEL(CYCLE,PWRSAVE,FREQ,PWR,MOD,PROT) { \
	module_params_t parm; \
	parm.cycletime = CYCLE; \
	parm.frequency = FREQ; \
	parm.power = PWR; \
	parm.modulation = MOD; \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), NORMALPRIO, moduleTEL, parm); \
}

#define MODULE_IMG(CYCLE,PWRSAVE,FREQ,PWR,MOD,PROT) { \
	module_params_t parm; \
	parm.cycletime = CYCLE; \
	parm.frequency = FREQ; \
	parm.power = PWR; \
	parm.modulation = MOD; \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), NORMALPRIO, moduleIMG, parm); \
}

#define MODULE_LOG(CYCLE,PWRSAVE,FREQ,PWR,MOD,PROT) { \
	module_params_t parm; \
	parm.cycletime = CYCLE; \
	parm.frequency = FREQ; \
	parm.power = PWR; \
	parm.modulation = MOD; \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), NORMALPRIO, moduleLOG, parm); \
}

#define MODULE_SD() (void)0; /* TODO */
#define MODULE_CAM() (void)0; /* TODO */
#define MODULE_GPS() (void)0; /* TODO */
#define MODULE_SEN() (void)0; /* TODO */

#define getAPRSRegionFrequency() (void)0; // FIXME: Replace me!
#define APRS_REGION_FREQ		getAPRSRegionFrequency()
#define SYM_BALLOON				"/O"
#define SYM_SMALLAIRCRAFT		"/'"
#define SYM_SATELLITE			"\S"

// Sleep definitions
#define SLEEP_BELOW_BATTVOLT(v)				(getBatteryVoltage() < (v) ? MOD_SLEEP : MOD_ACTIVE)
#define SLEEP_BELOW_SOLVOLT(v)				(getSolarVoltage() < (v) ? MOD_SLEEP : MOD_ACTIVE)
#define SLEEP_BELOW_SOLBATTVOLT(sol, batt)	(getSolarVoltage() < (sol) || getBatteryVoltage() < (batt) ? MOD_SLEEP : MOD_ACTIVE)

#endif
