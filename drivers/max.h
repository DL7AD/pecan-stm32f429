/**
  * @see https://github.com/thasti/utrak
  */

#ifndef __MAX_H__
#define __MAX_H__

#include "ch.h"
#include "hal.h"
#include "ptime.h"

typedef struct {
	uint8_t type;				// type of fix (validity)
	uint8_t num_svs;			// number of satellites used for solution, range 0 .. 19
	uint64_t time;				// Time unixTimestamp in ms
	int32_t lat;				// latitude in deg * 10^7, range -90 .. +90 * 10^7
	int32_t lon;				// longitude in deg * 10^7, range -180 .. +180 * 10^7
	uint16_t alt;				// altitude in m, range 0m, up to ~40000m, clamped
	uint16_t voltage_bat;		// battery voltage in mV, range 0 .. 3300mV
	int16_t temperature_int;	// tracker interval temperature in °C, range -100 .. 100
} gps_fix_t;

uint8_t gps_set_gps_only(void);
uint8_t gps_disable_nmea_output(void);
uint8_t gps_set_airborne_model(void);
uint8_t gps_set_power_save(void);
uint8_t gps_power_save(int on);
//uint8_t gps_save_settings(void);
void gps_get_fix(gps_fix_t *fix);

#endif

