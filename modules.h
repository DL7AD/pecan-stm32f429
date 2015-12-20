#ifndef __MODULES_H__
#define __MODULES_H__

typedef struct {
	int32_t cycletime;
	(void*) cycleMethod;
	uint8_t radio;
	uint16_t power;
	uint32_t frequency;
	mod_t modulation;
	(void*) sleepMethod;
} module_params_t;

#endif
