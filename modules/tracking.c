#include "ch.h"
#include "hal.h"
#include "trace.h"

#include "ptime.h"
#include "config.h"
#include "drivers/max.h"

trackPoint_t trackPoints[2];
trackPoint_t* lastTrackPoint;

/**
  * Returns most recent track point witch is complete.
  */
trackPoint_t* getLastTrackPoint(void) {
	return lastTrackPoint;
}

/**
  * Tracking Module (Thread)
  */
THD_FUNCTION(moduleTRACKING, arg) {
	// Print infos
	module_params_t* parm = (module_params_t*)arg;
	TRACE_INFO("TRAC > Startup module TRACKING MANAGER");
	TRACE_INFO("TRAC > Module TRACKING MANAGER info\r\n"
			   "%s Cycle: %d sec",
			   TRACE_TAB, parm->cycle
	);

	// Initialize pins
	palSetPadMode(GPIOE, 7, PAL_MODE_OUTPUT_PUSHPULL);	// GPS_OFF
	palSetPadMode(GPIOD, 5, PAL_MODE_ALTERNATE(7));		// UART TXD
	palSetPadMode(GPIOD, 6, PAL_MODE_ALTERNATE(7));		// UART RXD

	uint32_t id = 0;

	systime_t time = chVTGetSystemTimeX();
	while(true)
	{
		TRACE_INFO("POS  > Do module TRACKING MANAGER cycle");
		trackPoint_t* newTrackPoint = &trackPoints[(id+1) % sizeof(trackPoints)];

		// Search for GPS satellites
		GPS_Init();
		gpsFix_t gpsFix;

		do {
			chThdSleepMilliseconds(100);
			if(gps_get_fix(&gpsFix)) {
				TRACE_INFO("GPS  > Polling OK");
			} else {
				TRACE_ERROR("GPS  > Polling FAILED");
			}
		} while(!isGPSLocked(&gpsFix) && chVTGetSystemTimeX() <= time + S2ST(parm->cycle-2)); // Do as long no GPS lock and within timeout, timeout=cycle-1sec (-1sec in order to keep synchronization)

		// Trace GPS result TODO: Do a rework. Add more information and rename it to track point
		if(isGPSLocked(&gpsFix)) {
			GPS_Deinit(); // Switch off GPS

			TRACE_INFO("TRAC > GPS sampling finished GPS LOCK");
			TRACE_GPSFIX(&gpsFix);
		} else {
			TRACE_WARN("TRAC > GPS sampling finished GPS LOSS");
		}

		// Calibrate RTC
		setTime(gpsFix.time);

		// Fill tracking point

		// GPS fix and time
		newTrackPoint->id = id;
		newTrackPoint->time = gpsFix.time;
		newTrackPoint->gps_lock = isGPSLocked(&gpsFix);
		newTrackPoint->gps_lat = gpsFix.lat;
		newTrackPoint->gps_lon = gpsFix.lon;
		newTrackPoint->gps_alt = gpsFix.alt;
		newTrackPoint->gps_sats = gpsFix.num_svs;
		newTrackPoint->gps_ttff = ST2S(chVTGetSystemTimeX() - time);

		// Power management TODO: Implement this!
		newTrackPoint->adc_solar = 0;
		newTrackPoint->adc_battery = 0;
		newTrackPoint->adc_charge = 0;

		// Atmosphere condition TODO: Implement this!
		newTrackPoint->air_press = 0;
		newTrackPoint->air_hum = 0;
		newTrackPoint->air_temp = 0;

		// Balloon condition TODO: Implement this!
		newTrackPoint->bal_press = 0;
		newTrackPoint->bal_hum = 0;
		newTrackPoint->bal_temp = 0;

		// Movement TODO: Implement this!
		newTrackPoint->acc_x = 0;
		newTrackPoint->acc_y = 0;
		newTrackPoint->acc_z = 0;
		newTrackPoint->gyr_x = 0;
		newTrackPoint->gyr_y = 0;
		newTrackPoint->gyr_z = 0;

		// Switch last recent track point
		lastTrackPoint = newTrackPoint;
		id++;

		time += S2ST(parm->cycle); // Wait until this time
		chThdSleepUntil(time);
	}
}

