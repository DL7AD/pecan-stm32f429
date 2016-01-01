#ifndef __TRACKING_H__
#define __TRACKING_H__

#include "ch.h"
#include "hal.h"
#include "ptime.h"

typedef struct {
	uint32_t id; // Serial ID
	ptime_t time; // GPS time

	bool gps_lock; // True = on last try GPS has been locked
	int32_t gps_lat; // Latitude in °*10^7
	int32_t gps_lon; // Longitude in °*10^7
	int32_t gps_alt; // Altitude in meter
	uint8_t gps_sats; // Satellites used for solution
	uint8_t gps_ttff; // Time to first fix in seconds

	uint16_t adc_solar; // Current solar voltage
	uint16_t adc_battery; // Current battery voltage
	int32_t adc_charge;	// Power charged in battery last 5min in uWh

	uint32_t air_press; // Airpressure in Pa*10
	uint8_t air_hum; // Rel. humidity in %*10
	int16_t air_temp; // Temperature in degC*100

	uint32_t bal_press; // Airpressure in Pa in balloon
	uint8_t bal_hum; // Rel. humidity in % in balloon
	int16_t bal_temp; // Temperature in K*10 in balloon

	int16_t acc_x; // Acceleration on x-axis in 5min average
	int16_t acc_y; // Acceleration on y-axis in 5min average
	int16_t acc_z; // Acceleration on z-axis in 5min average
	int16_t gyr_x; // Turn rate on x-axis in 5min average
	int16_t gyr_y; // Turn rate on y-axis in 5min average
	int16_t gyr_z; // Turn rate on z-axis in 5min average
} trackPoint_t;

trackPoint_t* getLastTrackPoint(void);
THD_FUNCTION(moduleTRACKING, arg);

#endif
