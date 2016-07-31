#ifndef __TRACKING_H__
#define __TRACKING_H__

#include "ch.h"
#include "hal.h"
#include "ptime.h"

#define LOG_FLASH_ADDR		0x080C0000	/* Log flash memory address */
#define LOG_FLASH_SIZE		(256*1024)	/* Log flash memory size */
#define LOG_FLASH_PAGE_SIZE	(128*1024)	/* Log memory sector size */

typedef struct {
	uint32_t id;			// Serial ID
	ptime_t time;			// GPS time

	// GPS
	bool gps_lock;			// True = on last try GPS has been locked
	int32_t gps_lat;		// Latitude in °*10^7
	int32_t gps_lon;		// Longitude in °*10^7
	int32_t gps_alt;		// Altitude in meter
	uint8_t gps_sats;		// Satellites used for solution
	uint8_t gps_ttff;		// Time to first fix in seconds

	// Voltage and current measurement
	uint16_t adc_solar;		// Current solar voltage in mV
	uint16_t adc_battery;	// Current battery voltage in mV
	int16_t adc_charge;		// Average charge power into battery in mW in last cycle
	int16_t adc_discharge;	// Average discharge power from battery in mW in last cycle

	// Internal BME280 (on board)
	uint32_t int_press;		// Airpressure in Pa*10 (in 0.1Pa)
	uint16_t int_hum;		// Rel. humidity in %*10 (in 0.1%)
	int16_t int_temp;		// Temperature in degC*100 (in 0.01°C)

	// External BME280 (off board)
	uint32_t ext_press;		// Airpressure in Pa in balloon (in 0.1Pa)
	uint16_t ext_hum;		// Rel. humidity in % in balloon (in 0.1%)
	int16_t ext_temp;		// Temperature in K*100 in balloon (in 0.01°C)
} trackPoint_t;

typedef struct {
	uint32_t time;			// GPS time (UNIX timestamp)
	int32_t gps_lat;		// Latitude in °*10^7
	int32_t gps_lon;		// Longitude in °*10^7
	int32_t gps_alt;		// Altitude in meter
} logTrackPoint_t; // !!! IMPORTANT sizeof(logTrackPoint_t) must be multiple of 128*1024 (address is used for flash erase trigger)

void waitForNewTrackPoint(void);
trackPoint_t* getLastTrackPoint(void);
void getLogTrackPoints(logTrackPoint_t* log, uint32_t id, uint8_t size);
THD_FUNCTION(moduleTRACKING, arg);

#endif
