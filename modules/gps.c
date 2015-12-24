#include "ch.h"
#include "hal.h"
#include "trace.h"

#include "ptime.h"
#include "config.h"
#include "gps.h"
#include "drivers/max.h"

gpsFix_t lastPosition;		// Last position fix
bool requireNewPosition;	// GPS thread synchronization handle (True = new fix needed)

// Serial driver for GPS
const SerialConfig gps_config =
{
	9600,	// baud rate
	0,		// CR1 register
	0,		// CR2 register
	0		// CR3 register
};

/**
  * Returns the validity of the existing fix. The fix is up to date if it the
  * time past last sampling is not larger than GPS_FIX_TIMEOUT and has GPS
  * locked. This can be configured in the config file.
  * @return GPS fix data in lastPosition locked and up to date
  */
bool isGPSFixUpToDate(void) {
	return ST2S(chVTGetSystemTimeX() - lastPosition.systime) <= GPS_FIX_TIMEOUT && lastPosition.type == 3 && lastPosition.num_svs >= 5;
}

/**
  * Switched GPS on and off. Also initializes UART and GPS
  * @param on On
  */
void switchGPS(bool on) {

	if(on) { // Switch GPS on

		// Init UART
		TRACE_INFO("GPS  > Init GPS UART");
		sdStart(&SD2, &gps_config);

		// Switch MOSFET
		TRACE_INFO("GPS  > Switch on");
		palClearPad(GPIOE, 7);
		
		// Wait for GPS startup
		chThdSleepMilliseconds(3000);

		// Configure GPS
		TRACE_INFO("GPS  > Initialize GPS");
		if(gps_disable_nmea_output()) {
			TRACE_INFO("GPS  > Disable NMEA output OK");
		} else {
			TRACE_ERROR("GPS  > Disable NMEA output FAILED");
		}
		if(gps_set_gps_only()) {
			TRACE_INFO("GPS  > Set GPS only OK");
		} else {
			TRACE_ERROR("GPS  > Set GPS only FAILED");
		}
		if(gps_set_airborne_model()) {
			TRACE_INFO("GPS  > Set airborne model OK");
		} else {
			TRACE_ERROR("GPS  > Set airborne model FAILED");
		}
		if(gps_set_power_save()) {
			TRACE_INFO("GPS  > Configure power save OK");
		} else {
			TRACE_ERROR("GPS  > Configure power save FAILED");
		}
		if(gps_power_save(0)) {
			TRACE_INFO("GPS  > Disable power save OK");
		} else {
			TRACE_ERROR("GPS  > Disable power save FAILED");
		}

	} else { // Switch GPS off

		// Deinit UART
		TRACE_INFO("GPS  > Deinit UART");
		sdStop(&SD2);

		// Switch MOSFET
		TRACE_INFO("GPS  > Switch off");
		palSetPad(GPIOE, 7);

	}
}

/**
  * Returns position struct. Checks if last sampled position and samples new
  * GPS fix if last GPS is outdated.
  * @param timeout Wait until max. time
  * @return Last sampled position
  */
gpsFix_t getLastGPSPosition(systime_t timeout) {

	systime_t start = chVTGetSystemTimeX(); // Mark time for timeout

	if(isGPSFixUpToDate()) { // GPS position up to date

		TRACE_INFO("GPS  > GPS position up to date");
		return lastPosition;

	} else { // GPS position outdated, Acquire new fix and wait until new fix sampled (or timeout)

		TRACE_INFO("GPS  > GPS position outdated");

		// Wakeup GPS thread to search for GPS
		requireNewPosition = true;

		// Wait for new fix
		while(!isGPSFixUpToDate() && start+timeout >= chVTGetSystemTimeX())
			chThdSleepMilliseconds(100);

		if(!isGPSFixUpToDate() && start+timeout < chVTGetSystemTimeX()) {
			TRACE_INFO("GPS  > GPS position sampling TIMEOUT");
		} else {
			TRACE_INFO("GPS  > GPS position sampling OK");
		}

		return lastPosition;

	}
}

/**
  * GPS Module (Thread)
  */
THD_FUNCTION(moduleGPS, arg) {
	(void)arg;

	TRACE_INFO("GPS  > Startup module");

	// Initialize pins
	palSetPadMode(GPIOE, 7, PAL_MODE_OUTPUT_PUSHPULL);	// GPS_OFF
	palSetPadMode(GPIOD, 5, PAL_MODE_ALTERNATE(7));		// UART TXD
	palSetPadMode(GPIOD, 6, PAL_MODE_ALTERNATE(7));		// UART RXD

	while(true) {
		if(requireNewPosition) {
			// Switch on GPS and configure GPS/UART
			switchGPS(true);

			// Search for GPS satellites
			systime_t start = chVTGetSystemTimeX();
			do {
				TRACE_INFO("GPS  > Polling");
				gps_get_fix(&lastPosition);
				chThdSleepMilliseconds(100);
			} while(lastPosition.type != 0x3 && chVTGetSystemTimeX() <= start + S2ST(120)); // Do as long no GPS lock and within timeout (120 seconds)

			// Calibrate RTC
			setTime(lastPosition.time);

			// Set TTFF
			lastPosition.ttff = ST2S(chVTGetSystemTimeX() - start);

			if(lastPosition.ttff < 120) { // GPS locked
				switchGPS(false); // Switch off GPS
				requireNewPosition = false; // Mark no new position needed TODO: Implement interrupt handling

				TRACE_INFO("GPS  > GPS sampling finished GPS LOCK");
				TRACE_GPSFIX(&lastPosition);
			} else {
				TRACE_INFO("GPS  > GPS sampling finished GPS LOSS");
			}
		}
		chThdSleepMilliseconds(100);
	}
}

