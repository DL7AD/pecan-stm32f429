#ifndef __DEFINES_H__
#define __DEFINES_H__

#include "ch.h"
#include "hal.h"

#define APRS_REGION_FREQ		getAPRSRegionFrequency()
#define SYM_BALLOON				"/O"
#define SYM_SMALLAIRCRAFT		"/'"
#define SYM_SATELLITE			"\S"

// Sleep definitions
#define SLEEP_BELOW_BATTVOLT(v)				(getBatteryVoltage() < (v) ? MOD_SLEEP : MOD_ACTIVE)
#define SLEEP_BELOW_SOLVOLT(v)				(getSolarVoltage() < (v) ? MOD_SLEEP : MOD_ACTIVE)
#define SLEEP_BELOW_SOLBATTVOLT(sol, batt)	(getSolarVoltage() < (sol) || getBatteryVoltage() < (batt) ? MOD_SLEEP : MOD_ACTIVE)

#endif
