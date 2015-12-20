#ifndef __DEFINES_H__
#define __DEFINES_H__

#define MODULE_POS(CYCLE,PWRSAVE,FREQ,PWR,MOD,PROT) { \
	module_params_t parm; \
	parm.cycletime = CYCLE; \
	parm.radio = RADIO; \
	parm.power = PWR; \
	parm.modulation = MOD; \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), NORMALPRIO, module_pos, NULL); \
}

#define MODULE_SAT(CYCLE,PWRSAVE,FREQ,PWR,MOD,PROT,TLE1,TLE2) { \
	module_params_t parm; \
	parm.cycletime = CYCLE; \
	parm.radio = RADIO; \
	parm.power = PWR; \
	parm.modulation = MOD; \
	parm.cycleMethod = sgp4_visible(TLE1, TLE2); \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), NORMALPRIO, module_pos, NULL); \
}

#define MODULE_TEL(CYCLE,PWRSAVE,FREQ,PWR,MOD,PROT) { \
	module_params_t parm; \
	parm.cycletime = CYCLE; \
	parm.radio = RADIO; \
	parm.power = PWR; \
	parm.modulation = MOD; \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), NORMALPRIO, module_tel, NULL); \
}

#define MODULE_IMG(CYCLE,PWRSAVE,FREQ,PWR,MOD,PROT) { \
	module_params_t parm; \
	parm.cycletime = CYCLE; \
	parm.radio = RADIO; \
	parm.power = PWR; \
	parm.modulation = MOD; \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), NORMALPRIO, module_img, NULL); \
}

#define MODULE_LOG(CYCLE,PWRSAVE,FREQ,PWR,MOD,PROT) { \
	module_params_t parm; \
	parm.cycletime = CYCLE; \
	parm.radio = RADIO; \
	parm.power = PWR; \
	parm.modulation = MOD; \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), NORMALPRIO, module_log, NULL); \
}

#define MOD_ACTIVE	0
#define MOD_SLEEP	1

#define MOD_2FSK	0
#define MOD_AFSK	1

#define PWR_1MW		1
#define PWR_10MW	10
#define PWR_50MW	17
#define PWR_100MW	20
#define PWR_1W		30
#define PWR_2W		33

#define APRS_REGION_FREQ		getAPRSRegionFrequency(void)
#define SYM_BALLOON				/O
#define SYM_SMALLAIRCRAFT		/'
#define SYM_SATELLITE			\S

// Sleep functions
void SLEEP_BELOW_BATTVOLT(v)			{ getBatteryVoltage() < (v) ? MOD_SLEEP : MOD_ACTIVE; }
void SLEEP_BELOW_SOLVOLT(v)				{ getSolarVoltage() < (v) ? MOD_SLEEP : MOD_ACTIVE; }
void SLEEP_BELOW_SOLBATTVOLT(sol, batt)	{ getSolarVoltage() < (sol) || getBatteryVoltage() < (batt) ? MOD_SLEEP : MOD_ACTIVE; }

#endif
