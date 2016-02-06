#include "ch.h"
#include "hal.h"
#include "debug.h"

#include "ptime.h"
#include "config.h"
#include "drivers/max.h"
#include "drivers/bme280.h"
#include "drivers/pac1720.h"

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

	uint32_t id = 0;
	lastTrackPoint = &trackPoints[0];

	systime_t time = chVTGetSystemTimeX();
	while(true)
	{
		parm->lastCycle = chVTGetSystemTimeX(); // Watchdog timer
		TRACE_INFO("TRAC > Do module TRACKING MANAGER cycle");
		trackPoint_t* tp = &trackPoints[id % (sizeof(trackPoints) / sizeof(trackPoint_t))]; // Current track point
		trackPoint_t* ltp = &trackPoints[(id-1) % (sizeof(trackPoints) / sizeof(trackPoint_t))]; // Last track point

		// Search for GPS satellites
		gpsFix_t gpsFix;
		GPS_Init();

		do {
			gps_get_fix(&gpsFix);
		} while(!isGPSLocked(&gpsFix) && chVTGetSystemTimeX() <= time + S2ST(parm->cycle-3)); // Do as long no GPS lock and within timeout, timeout=cycle-1sec (-1sec in order to keep synchronization)

		if(isGPSLocked(&gpsFix)) { // GPS locked

			// Switch off GPS
			GPS_Deinit();

			// Debug
			TRACE_INFO("TRAC > GPS sampling finished GPS LOCK");
			TRACE_GPSFIX(&gpsFix);

			// Calibrate RTC
			setTime(gpsFix.time);

			// Take time from GPS
			tp->time.year = gpsFix.time.year;
			tp->time.month = gpsFix.time.month;
			tp->time.day = gpsFix.time.day;
			tp->time.hour = gpsFix.time.hour;
			tp->time.minute = gpsFix.time.minute;
			tp->time.second = gpsFix.time.second;

			// Set new GPS fix
			tp->gps_lat = gpsFix.lat;
			tp->gps_lon = gpsFix.lon;
			tp->gps_alt = gpsFix.alt;

			tp->gps_lock = isGPSLocked(&gpsFix);
			tp->gps_sats = gpsFix.num_svs;

		} else { // GPS lost (keep GPS switched on)

			// Debug
			TRACE_WARN("TRAC > GPS sampling finished GPS LOSS");

			// Take time from internal RTC
			ptime_t time;
			getTime(&time);
			tp->time.year = time.year;
			tp->time.month = time.month;
			tp->time.day = time.day;
			tp->time.hour = time.hour;
			tp->time.minute = time.minute;
			tp->time.second = time.second;

			// Take GPS fix from old lock
			tp->gps_lat = ltp->gps_lat;
			tp->gps_lon = ltp->gps_lon;
			tp->gps_alt = ltp->gps_alt;

			// Mark gpsloss
			tp->gps_lock = false;
			tp->gps_sats = 0;

		}

		tp->id = id; // Serial ID
		tp->gps_ttff = ST2S(chVTGetSystemTimeX() - time); // Time to first fix

		// Power management
		tp->adc_solar = 0; // TODO: Implement ADC
		tp->adc_battery = 0; // TODO: Implement ADC
		tp->adc_charge = pac1720_getAveragePower();

		bme280_t bmeInt;
		bme280_t bmeExt;

		// Atmosphere condition
		if(BME280_isAvailable(BME280_ADDRESS_INT)) {
			BME280_Init(&bmeInt, BME280_ADDRESS_INT);
			tp->air_press = BME280_getPressure(&bmeInt, 256);
			tp->air_hum = BME280_getHumidity(&bmeInt);
			tp->air_temp = BME280_getTemperature(&bmeInt);
		} else { // No internal BME280 found
			TRACE_ERROR("TRAC > Internal BME280 not available");
			tp->air_press = 0;
			tp->air_hum = 0;
			tp->air_temp = 0;
		}

		// Balloon condition
		if(BME280_isAvailable(BME280_ADDRESS_EXT)) {
			BME280_Init(&bmeExt, BME280_ADDRESS_EXT);
			tp->bal_press = BME280_getPressure(&bmeExt, 256);
			tp->bal_hum = BME280_getHumidity(&bmeExt);
			tp->bal_temp = BME280_getTemperature(&bmeExt);
		} else { // No external BME280 found
			TRACE_WARN("TRAC > External BME280 not available");
			tp->bal_press = 0;
			tp->bal_hum = 0;
			tp->bal_temp = 0;
		}

		// Movement TODO: Implement this!
		tp->acc_x = 0;
		tp->acc_y = 0;
		tp->acc_z = 0;
		tp->gyr_x = 0;
		tp->gyr_y = 0;
		tp->gyr_z = 0;


		// Trace data
		TRACE_INFO(	"TRAC > New tracking point available (ID=%d)\r\n"
					"%s Time %04d-%02d-%02d %02d:%02d:%02d\r\n"
					"%s Pos  %d.%07d %d.%07d Alt %dm\r\n"
					"%s Sats %d  TTFF %dsec\r\n"
					"%s ADC Vbat=%d.%dV  Vsol=%d.%dV  P=%dmW\r\n"
					"%s Air  p=%6d.%01dPa T=%2d.%02ddegC phi=%2d.%01d%%\r\n"
					"%s Ball p=%6d.%01dPa T=%2d.%02ddegC phi=%2d.%01d%%\r\n"
					"%s Acc %05d %05d %05d\r\n"
					"%s Gyr %05d %05d %05d\r\n",
					tp->id,
					TRACE_TAB, tp->time.year, tp->time.month, tp->time.day, tp->time.hour, tp->time.minute, tp->time.day,
					TRACE_TAB, tp->gps_lat/10000000, tp->gps_lat%10000000, tp->gps_lon/10000000, tp->gps_lon%10000000, tp->gps_alt,
					TRACE_TAB, tp->gps_sats, tp->gps_ttff,
					TRACE_TAB, tp->adc_solar/1000, (tp->adc_solar%1000)%10, tp->adc_battery/1000, (tp->adc_battery%1000)%10, tp->adc_charge,
					TRACE_TAB, tp->air_press/10, tp->air_press%10, tp->air_temp/100, tp->air_temp%100, tp->air_hum/10, tp->air_hum%10,
					TRACE_TAB, tp->bal_press/10, tp->bal_press%10, tp->bal_temp/100, tp->bal_temp%100, tp->bal_hum/10, tp->bal_hum%10,
					TRACE_TAB, tp->acc_x, tp->acc_y, tp->acc_z,
					TRACE_TAB, tp->gyr_x, tp->gyr_y, tp->gyr_z
		);


		// Switch last recent track point
		lastTrackPoint = tp;
		id++;

		time = chThdSleepUntilWindowed(time, time + S2ST(parm->cycle)); // Wait until time + cycletime
	}
}

