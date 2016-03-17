#include "ch.h"
#include "hal.h"
#include "sleep.h"
#include "padc.h"

smode_t SLEEP_WHEN_BATT_BELOW_2V9(void) { return getBatteryVoltageMV() < 2900 ? SMOD_SLEEP : SMOD_ACTIVE; }
smode_t SLEEP_WHEN_BATT_BELOW_3V0(void) { return getBatteryVoltageMV() < 3000 ? SMOD_SLEEP : SMOD_ACTIVE; }
smode_t SLEEP_WHEN_BATT_BELOW_3V1(void) { return getBatteryVoltageMV() < 3100 ? SMOD_SLEEP : SMOD_ACTIVE; }
smode_t SLEEP_WHEN_BATT_BELOW_3V2(void) { return getBatteryVoltageMV() < 3200 ? SMOD_SLEEP : SMOD_ACTIVE; }
smode_t SLEEP_WHEN_BATT_BELOW_3V3(void) { return getBatteryVoltageMV() < 3300 ? SMOD_SLEEP : SMOD_ACTIVE; }
smode_t SLEEP_WHEN_BATT_BELOW_3V4(void) { return getBatteryVoltageMV() < 3400 ? SMOD_SLEEP : SMOD_ACTIVE; }
smode_t SLEEP_WHEN_BATT_BELOW_3V5(void) { return getBatteryVoltageMV() < 3500 ? SMOD_SLEEP : SMOD_ACTIVE; }
smode_t SLEEP_WHEN_BATT_BELOW_3V6(void) { return getBatteryVoltageMV() < 3600 ? SMOD_SLEEP : SMOD_ACTIVE; }
smode_t SLEEP_WHEN_BATT_BELOW_3V7(void) { return getBatteryVoltageMV() < 3700 ? SMOD_SLEEP : SMOD_ACTIVE; }
smode_t SLEEP_WHEN_BATT_BELOW_3V8(void) { return getBatteryVoltageMV() < 3800 ? SMOD_SLEEP : SMOD_ACTIVE; }
smode_t SLEEP_WHEN_BATT_BELOW_3V9(void) { return getBatteryVoltageMV() < 3900 ? SMOD_SLEEP : SMOD_ACTIVE; }
smode_t SLEEP_WHEN_BATT_BELOW_4V0(void) { return getBatteryVoltageMV() < 4000 ? SMOD_SLEEP : SMOD_ACTIVE; }
smode_t SLEEP_WHEN_BATT_BELOW_4V1(void) { return getBatteryVoltageMV() < 4100 ? SMOD_SLEEP : SMOD_ACTIVE; }

smode_t SLEEP_WHEN_ISS_NOT_VISIBLE(void) { // TODO: Not implemented yet
	return SMOD_SLEEP;
}

smode_t SLEEP_WHEN_BATTERY_LOW(void) {
	if(getBatteryVoltageMV() < 3600 || getSolarVoltageMV() < 500) {
		return SMOD_SLEEP;
	} else {
		return SMOD_ACTIVE;
	}
}
