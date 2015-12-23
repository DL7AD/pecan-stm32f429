#ifndef __GPS_H__
#define __GPS_H__

#include "ptime.h"
#include "drivers/max.h"

gpsFix_t getLastGPSPosition(void);
THD_FUNCTION(moduleGPS, arg);

#endif

