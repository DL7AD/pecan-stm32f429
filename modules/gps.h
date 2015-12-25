#ifndef __GPS_H__
#define __GPS_H__

#include "ch.h"
#include "hal.h"
#include "ptime.h"
#include "drivers/max.h"

#define isGPSFixUpToDate(pos) (ST2S(chVTGetSystemTimeX() - (pos)->systime) <= GPS_FIX_TIMEOUT && isGPSLocked(pos))

THD_FUNCTION(moduleGPS, arg);
gpsFix_t getLastGPSPosition(systime_t timeout);

#endif

