#include "ch.h"
#include "hal.h"

#include "time.h"
#include "config.h"
#include "gps.h"

volatile gps_t lastPosition;
volatile bool requireNewPosition;

bool isGPSFixUpToDate(void) {
	return date2UnixTimestamp(lastPosition.time) + GPS_FIX_TIMEOUT >= getTime()/1000;
}
void switchGPS(bool on) {
	// TODO: switch GPS
	(void)on;
}
bool processGPSData(void) {
	// TODO: Process UART data
	return false;
}

gps_t getLastGPSPosition(void) {
	if(isGPSFixUpToDate()) { // GPS position up to date
		return lastPosition;
	} else { // GPS position outdated

		// Acquire new fix and wait until new fix sampled (or timeout)
		requireNewPosition = true;
		uint32_t counter = 0;
		while(!isGPSFixUpToDate() && GPS_ACQUISITION_TIMEOUT < counter++)
			chThdSleepMilliseconds(1000);

		return lastPosition;
	}
}

/**
  * GPS Module (Thread)
  */
THD_FUNCTION(moduleGPS, arg) {
	(void)arg;

	if(requireNewPosition) {
		requireNewPosition = false; // TODO: Implement interrupt handling

		switchGPS(true); // Switch on GPS

		bool lock;
		uint32_t counter = 0;
		do {
			lock = processGPSData(); // Process byte
			chThdSleepMilliseconds(1);
		} while(!lock && counter++ <= GPS_ACQUISITION_TIMEOUT*1000);
		
		lastPosition.ttff = counter/1000; // Setting time to first fix

		if(lastPosition.ttff < GPS_ACQUISITION_TIMEOUT) { // Fix sampled in time
			switchGPS(false);
		} else { // GPS lost (could not get a valid fix in time)
			requireNewPosition = true; // Try to get a valid fix again
		}
	}
	chThdSleepMilliseconds(100);
}

