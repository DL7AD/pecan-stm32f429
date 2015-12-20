#ifndef __GPS_H__
#define __GPS_H__

#include "ptime.h"

typedef struct {
	ptime_t time;
	float latitude;
	float longitude;
	uint16_t altitude;
	uint8_t satellites;
	uint16_t speed;
	uint16_t course;
	bool active; // has lock
	uint8_t ttff;
} gps_t;

gps_t getLastGPSPosition(void);
THD_FUNCTION(moduleGPS, arg);

#endif

