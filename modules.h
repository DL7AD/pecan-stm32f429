#ifndef __MODULES_H__
#define __MODULES_H__

typedef enum {
	MOD_ACTIVE,
	MOD_SLEEP
} mode_t;

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
	uint32_t frequency;
	modulation_t modulation;
	void* sleepMethod;
} module_params_t;

#endif
