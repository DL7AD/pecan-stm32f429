#ifndef __TRACKING_H__
#define __TRACKING_H__

#include "ch.h"
#include "hal.h"
#include "ptime.h"

typedef struct {
	uint32_t id;			// Serial ID
	ptime_t time;			// GPS time

	bool gps_lock;			// True = on last try GPS has been locked
	int32_t gps_lat;		// Latitude in °*10^7
	int32_t gps_lon;		// Longitude in °*10^7
	int32_t gps_alt;		// Altitude in meter
	uint8_t gps_sats;		// Satellites used for solution
	uint8_t gps_ttff;		// Time to first fix in seconds

	uint16_t adc_solar;		// Current solar voltage in mV
	uint16_t adc_battery;	// Current battery voltage in mV
	int16_t adc_charge;		// Average power charge into battery in mW in last cycle

	uint32_t air_press;		// Airpressure in Pa*10 (in 0.1Pa)
	uint8_t air_hum;		// Rel. humidity in %*10 (in 0.1%)
	int16_t air_temp;		// Temperature in degC*100 (in 0.01°C)

	uint32_t bal_press;		// Airpressure in Pa in balloon (in 0.1Pa)
	uint8_t bal_hum;		// Rel. humidity in % in balloon (in 0.1%)
	int16_t bal_temp;		// Temperature in K*100 in balloon (in 0.01°C)
} trackPoint_t;

trackPoint_t* getLastTrackPoint(void);
THD_FUNCTION(moduleTRACKING, arg);

#endif
