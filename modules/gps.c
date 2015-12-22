#include "ch.h"
#include "hal.h"
#include "trace.h"

#include "ptime.h"
#include "config.h"
#include "gps.h"

volatile gps_t lastPosition;
volatile bool requireNewPosition;
volatile char lineBuffer[128];
volatile uint32_t linePos;

const SerialConfig gps_config =
{
	9600,	// baud rate
	0,		// CR1 register
	0,		// CR2 register
	0		// CR3 register
};

bool isGPSFixUpToDate(void) {
	return date2UnixTimestamp(lastPosition.time) + GPS_FIX_TIMEOUT*1000 >= date2UnixTimestamp(getTime()) && lastPosition.time.year != 0;
}

void switchGPS(bool on) {

	if(on) { // Switch GPS on

		// Init UART
		TRACE_INFO("init gps uart");
		sdStart(&SD2, &gps_config);

		// Switch MOSFET
		TRACE_INFO("switch on gps");
		palClearPad(GPIOE, 7);

	} else { // Switch GPS off

		// Deinit UART
		TRACE_INFO("deinit gps uart");
		sdStop(&SD2);

		// Switch MOSFET
		TRACE_INFO("switch off gps");
		palSetPad(GPIOE, 7);
	}
}

bool processGPSData(void) {

	uint8_t b = sdGetTimeout(&SD2, 0); // Get data non blocking
	if(b == 0xFF)
		return false;

	if(b != 10 && b != 13 && linePos < sizeof(lineBuffer)-1) {

		lineBuffer[linePos++] = b; // Append buffer

	} else if(linePos > 10) { // LF/CF received

		lineBuffer[linePos] = 0; // Mark end of string

		//TRACE_INFO("received NMEA %s", lineBuffer);
		linePos = 0; // Clear buffer

	}

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

	TRACE_INFO("startup module gps");
	TRACE_WARN("module position not completely implemented"); // FIXME

	// Initialize pins
	palSetPadMode(GPIOE, 7, PAL_MODE_OUTPUT_PUSHPULL);	// GPS_OFF
	palSetPadMode(GPIOA, 2, PAL_MODE_ALTERNATE(7));		// UART TXD
	palSetPadMode(GPIOA, 3, PAL_MODE_ALTERNATE(7));		// UART RXD

	while(true) {
		if(requireNewPosition) {
			requireNewPosition = false; // TODO: Implement interrupt handling

			TRACE_INFO("gps position outdated");

			switchGPS(true); // Switch on GPS

			bool lock;
			uint32_t counter = 0;
			do {
				lock = processGPSData(); // Process byte
				chThdSleepMilliseconds(1);
			} while(!lock && counter++ <= GPS_ACQUISITION_TIMEOUT*1000);
		
			lastPosition.ttff = counter/1000; // Setting time to first fix
			TRACE_INFO("gps sampling finished");
			TRACE_INFO("gps ttff %d", lastPosition.ttff);

			if(lastPosition.ttff < GPS_ACQUISITION_TIMEOUT) { // Fix sampled in time
				switchGPS(false);
			} else { // GPS lost (could not get a valid fix in time)
				requireNewPosition = true; // Try to get a valid fix again
			}
		}
		chThdSleepMilliseconds(100);
	}
}

