#ifndef __GEOFENCE_H__
#define __GEOFENCE_H__

#include "ch.h"
#include "hal.h"

typedef struct {
	int32_t lat;
	int32_t lon;
} coord_t;

bool isPointInPolygon(const coord_t *poly, uint32_t size, int32_t lat, int32_t lon);
bool isPointInAmerica(int32_t lat, int32_t lon);
bool isPointInChina(int32_t lat, int32_t lon);

#endif
