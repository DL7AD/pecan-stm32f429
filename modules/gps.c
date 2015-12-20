#include "ch.h"
#include "hal.h"

#include "ptime.h"
#include "config.h"
#include "gps.h"
#include "chprintf.h"

volatile gps_t lastPosition;
volatile bool requireNewPosition;

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
			chprintf((BaseSequentialStream*)&SD1, "LLL");
		// Init UART
		sdStart(&SD2, &gps_config);

		// Switch MOSFET
		palClearPad(GPIOE, 7);

	} else { // Switch GPS off

		// Deinit UART
		sdStop(&SD2);

		// Switch MOSFET
		palSetPad(GPIOE, 7);
	}
}

bool processGPSData(void) {

	uint8_t b = sdGetTimeout(&SD2, 0); // Get data non blocking
	if(!b)
		return false;

	// TODO: Process variable b (UART)

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

	// Initialize pins
	palSetPadMode(GPIOE, 7, PAL_MODE_OUTPUT_PUSHPULL);	// GPS_OFF
	palSetPadMode(GPIOA, 2, PAL_MODE_ALTERNATE(7));		// UART TXD
	palSetPadMode(GPIOA, 3, PAL_MODE_ALTERNATE(7));		// UART RXD

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

