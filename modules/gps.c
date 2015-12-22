#include "ch.h"
#include "hal.h"
#include "trace.h"

#include "ptime.h"
#include "config.h"
#include "gps.h"
#include "drivers/max.h"

gps_fix_t lastPosition;
bool requireNewPosition;
char lineBuffer[128];
uint32_t linePos;

const SerialConfig gps_config =
{
	9600,	// baud rate
	0,		// CR1 register
	0,		// CR2 register
	0		// CR3 register
};

bool isGPSFixUpToDate(void) {
	return lastPosition.time + GPS_FIX_TIMEOUT*1000 >= date2UnixTimestamp(getTime()) && lastPosition.time != 0;
}

void switchGPS(bool on) {

	if(on) { // Switch GPS on

		// Init UART
		TRACE_INFO("Init GPS UART");
		sdStart(&SD2, &gps_config);

		// Switch MOSFET
		TRACE_INFO("Switch on GPS");
		palClearPad(GPIOE, 7);
		
		// Wait for GPS startup
		chThdSleepMilliseconds(3000);

		TRACE_INFO("Initialize GPS");
		if(gps_disable_nmea_output()) {
			TRACE_INFO("Disable NMEA output OK");
		} else {
			TRACE_ERROR("Disable NMEA output FAILED");
		}
		if(gps_set_gps_only()) {
			TRACE_INFO("Set GPS only OK");
		} else {
			TRACE_ERROR("Set GPS only FAILED");
		}
		if(gps_set_airborne_model()) {
			TRACE_INFO("Set airborne model OK");
		} else {
			TRACE_ERROR("Set airborne model FAILED");
		}
		if(gps_set_power_save()) {
			TRACE_INFO("Configure power save OK");
		} else {
			TRACE_ERROR("Configure power save FAILED");
		}
		if(gps_power_save(0)) {
			TRACE_INFO("Disable power save OK");
		} else {
			TRACE_ERROR("Disable power save FAILED");
		}

	} else { // Switch GPS off

		// Deinit UART
		TRACE_INFO("Deinit gps uart");
		sdStop(&SD2);

		// Switch MOSFET
		TRACE_INFO("Switch off gps");
		palSetPad(GPIOE, 7);
	}
}

gps_fix_t getLastGPSPosition(void) {
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

	TRACE_INFO("Startup module GPS");

	// Initialize pins
	palSetPadMode(GPIOE, 7, PAL_MODE_OUTPUT_PUSHPULL);	// GPS_OFF
	palSetPadMode(GPIOA, 2, PAL_MODE_ALTERNATE(7));		// UART TXD
	palSetPadMode(GPIOA, 3, PAL_MODE_ALTERNATE(7));		// UART RXD

	while(true) {
		if(requireNewPosition) {
			requireNewPosition = false; // TODO: Implement interrupt handling

			TRACE_INFO("GPS position outdated");

			switchGPS(true); // Switch on GPS

			uint32_t counter = 0;
			do {
				gps_get_fix(&lastPosition);
				chThdSleepMilliseconds(500);
			} while(!lastPosition.type && counter++ <= GPS_ACQUISITION_TIMEOUT*2);
		
			uint32_t ttff = counter/2; // Setting time to first fix
			TRACE_INFO("GPS sampling finished");
			TRACE_INFO("GPS TTFF %d", ttff);

			if(ttff < GPS_ACQUISITION_TIMEOUT) { // Fix sampled in time
				switchGPS(false);
			} else { // GPS lost (could not get a valid fix in time)
				requireNewPosition = true; // Try to get a valid fix again
			}
		}
		chThdSleepMilliseconds(100);
	}
}

