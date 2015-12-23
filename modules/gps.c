#include "ch.h"
#include "hal.h"
#include "trace.h"

#include "ptime.h"
#include "config.h"
#include "gps.h"
#include "drivers/max.h"

gpsFix_t lastPosition;
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
	return ST2S(chVTGetSystemTimeX() - lastPosition.systime) <= GPS_FIX_TIMEOUT && lastPosition.type == 3;
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
		TRACE_INFO("Deinit GPS uart");
		sdStop(&SD2);

		// Switch MOSFET
		TRACE_INFO("Switch off GPS");
		palSetPad(GPIOE, 7);
	}
}

gpsFix_t getLastGPSPosition(void) {
	if(isGPSFixUpToDate()) { // GPS position up to date

		TRACE_INFO("GPS position up to date");
		return lastPosition;

	} else { // GPS position outdated

		// Acquire new fix and wait until new fix sampled (or timeout)
		TRACE_INFO("GPS position outdated");
		requireNewPosition = true;
		uint32_t counter = 0;
		while(!isGPSFixUpToDate() && GPS_ACQUISITION_TIMEOUT > counter++)
			chThdSleepMilliseconds(100);

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
	palSetPadMode(GPIOD, 5, PAL_MODE_ALTERNATE(7));		// UART TXD
	palSetPadMode(GPIOD, 6, PAL_MODE_ALTERNATE(7));		// UART RXD

	while(true) {
		if(requireNewPosition) {
			requireNewPosition = false; // TODO: Implement interrupt handling

			switchGPS(true); // Switch on GPS

			// Search for GPS satellites
			systime_t start = chVTGetSystemTimeX();
			do {
				TRACE_INFO("Query GPS");
				gps_get_fix(&lastPosition);

				chThdSleepMilliseconds(100);
			} while(lastPosition.type != 0x3 && chVTGetSystemTimeX() <= start + S2ST(GPS_ACQUISITION_TIMEOUT)); // Do as long no GPS lock and within timeout

			setTime(lastPosition.time); // Calibrate RTC

			lastPosition.ttff = ST2S(chVTGetSystemTimeX()-start); // Setting time to first fix
			TRACE_INFO("GPS sampling finished");
			TRACE_GPSFIX(&lastPosition);

			if(lastPosition.ttff < GPS_ACQUISITION_TIMEOUT) { // Fix sampled in time
				switchGPS(false);
			} else { // GPS lost (could not get a valid fix in time)
				requireNewPosition = true; // Try to get a valid fix again
			}
		}
		chThdSleepMilliseconds(100);
	}
}

