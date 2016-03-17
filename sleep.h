#ifndef __SLEEP_H__
#define __SLEEP_H__

#include "ch.h"
#include "hal.h"

typedef enum {
	SMOD_ACTIVE,
	SMOD_SLEEP
} smode_t;

smode_t SLEEP_WHEN_BATT_BELOW_2V9(void);
smode_t SLEEP_WHEN_BATT_BELOW_3V0(void);
smode_t SLEEP_WHEN_BATT_BELOW_3V1(void);
smode_t SLEEP_WHEN_BATT_BELOW_3V2(void);
smode_t SLEEP_WHEN_BATT_BELOW_3V3(void);
smode_t SLEEP_WHEN_BATT_BELOW_3V4(void);
smode_t SLEEP_WHEN_BATT_BELOW_3V5(void);
smode_t SLEEP_WHEN_BATT_BELOW_3V6(void);
smode_t SLEEP_WHEN_BATT_BELOW_3V7(void);
smode_t SLEEP_WHEN_BATT_BELOW_3V8(void);
smode_t SLEEP_WHEN_BATT_BELOW_3V9(void);
smode_t SLEEP_WHEN_BATT_BELOW_4V0(void);
smode_t SLEEP_WHEN_BATT_BELOW_4V1(void);
smode_t SLEEP_WHEN_BATTERY_LOW(void);

#endif
