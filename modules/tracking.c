#include "ch.h"
#include "hal.h"
#include "debug.h"

#include "ptime.h"
#include "config.h"
#include "max.h"
#include "bme280.h"
#include "padc.h"
#include "pac1720.h"
#include "radio.h"

#include "stm32f4xx_rcc.h"
#define RCC_PLLM_MASK    ((uint32_t)0x0000003F)
#define RCC_PLLM_POS     0
#define RCC_PLLN_MASK    ((uint32_t)0x00007FC0)
#define RCC_PLLN_POS     6
#define RCC_PLLP_MASK    ((uint32_t)0x00030000)
#define RCC_PLLP_POS     16
#define RCC_PLLQ_MASK    ((uint32_t)0x0F000000)
#define RCC_PLLQ_POS     24
#define RCC_PLLR_MASK    ((uint32_t)0x70000000)
#define RCC_PLLR_POS     28

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
	(void)arg;

	// Print initialization message
	TRACE_INFO("TRAC > Startup module TRACKING MANAGER");

	uint32_t id = 1;
	lastTrackPoint = &trackPoints[0];

	systime_t time = chVTGetSystemTimeX();
	while(true)
	{
		TRACE_INFO("TRAC > Do module TRACKING MANAGER cycle");
		watchdog_tracking = chVTGetSystemTimeX(); // Update watchdog timer

		trackPoint_t* tp = &trackPoints[id % (sizeof(trackPoints) / sizeof(trackPoint_t))]; // Current track point
		trackPoint_t* ltp = &trackPoints[(id-1) % (sizeof(trackPoints) / sizeof(trackPoint_t))]; // Last track point

		// Search for GPS satellites
		gpsFix_t gpsFix = {{0,0,0,0,0,0,0},0,0,0,0,0};
		GPS_Init();

		do {
			gps_get_fix(&gpsFix);
		} while(!isGPSLocked(&gpsFix) && chVTGetSystemTimeX() <= time + S2ST(TRACK_CYCLE_TIME-5)); // Do as long no GPS lock and within timeout, timeout=cycle-1sec (-1sec in order to keep synchronization)

		if(isGPSLocked(&gpsFix)) { // GPS locked

			// Switch off GPS
			GPS_Deinit();

			// Debug
			TRACE_INFO("TRAC > GPS sampling finished GPS LOCK");
			TRACE_GPSFIX(&gpsFix);

			
			if(gpsFix.time.year) {
				// Calibrate RTC
				setTime(gpsFix.time);

				// Take time from GPS
				tp->time.year = gpsFix.time.year;
				tp->time.month = gpsFix.time.month;
				tp->time.day = gpsFix.time.day;
				tp->time.hour = gpsFix.time.hour;
				tp->time.minute = gpsFix.time.minute;
				tp->time.second = gpsFix.time.second;
			} else {
				// Take time from internal RTC
				ptime_t time;
				getTime(&time);
				tp->time.year = time.year;
				tp->time.month = time.month;
				tp->time.day = time.day;
				tp->time.hour = time.hour;
				tp->time.minute = time.minute;
				tp->time.second = time.second;
			}

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
		tp->adc_solar = getSolarVoltageMV();
		tp->adc_battery = getBatteryVoltageMV();
		tp->adc_charge = pac1720_getAverageChargePower();
		tp->adc_discharge = pac1720_getAverageDischargePower();

		bme280_t bmeInt;
		bme280_t bmeExt;

		// Atmosphere condition
		if(BME280_isAvailable(BME280_ADDRESS_INT)) {
			BME280_Init(&bmeInt, BME280_ADDRESS_INT);
			tp->int_press = BME280_getPressure(&bmeInt, 256);
			tp->int_hum = BME280_getHumidity(&bmeInt);
			tp->int_temp = BME280_getTemperature(&bmeInt);
		} else { // No internal BME280 found
			TRACE_ERROR("TRAC > Internal BME280 not available");
			tp->int_press = 0;
			tp->int_hum = 0;
			tp->int_temp = 0;
		}

		// External BME280
		if(BME280_isAvailable(BME280_ADDRESS_EXT)) {
			BME280_Init(&bmeExt, BME280_ADDRESS_EXT);
			tp->ext_press = BME280_getPressure(&bmeExt, 256);
			tp->ext_hum = BME280_getHumidity(&bmeExt);
			tp->ext_temp = BME280_getTemperature(&bmeExt);
		} else { // No external BME280 found
			TRACE_WARN("TRAC > External BME280 not available");
			tp->ext_press = 0;
			tp->ext_hum = 0;
			tp->ext_temp = 0;
		}

		// Trace data
		TRACE_INFO(	"TRAC > New tracking point available (ID=%d)\r\n"
					"%s Time %04d-%02d-%02d %02d:%02d:%02d\r\n"
					"%s Pos  %d.%07d %d.%07d Alt %dm\r\n"
					"%s Sats %d  TTFF %dsec\r\n"
					"%s ADC Vbat=%d.%03dV  Vsol=%d.%03dV Pin=%dmW Pout=%dmW\r\n"
					"%s INT p=%6d.%01dPa T=%2d.%02ddegC phi=%2d.%01d%%\r\n"
					"%s EXT p=%6d.%01dPa T=%2d.%02ddegC phi=%2d.%01d%%",
					tp->id,
					TRACE_TAB, tp->time.year, tp->time.month, tp->time.day, tp->time.hour, tp->time.minute, tp->time.day,
					TRACE_TAB, tp->gps_lat/10000000, (tp->gps_lat > 0 ? 1:-1)*tp->gps_lat%10000000, tp->gps_lon/10000000, (tp->gps_lon > 0 ? 1:-1)*tp->gps_lon%10000000, tp->gps_alt,
					TRACE_TAB, tp->gps_sats, tp->gps_ttff,
					TRACE_TAB, tp->adc_battery/1000, (tp->adc_battery%1000), tp->adc_solar/1000, (tp->adc_solar%1000), tp->adc_charge, tp->adc_discharge,
					TRACE_TAB, tp->int_press/10, tp->int_press%10, tp->int_temp/100, tp->int_temp%100, tp->int_hum/10, tp->int_hum%10,
					TRACE_TAB, tp->ext_press/10, tp->ext_press%10, tp->ext_temp/100, tp->ext_temp%100, tp->ext_hum/10, tp->ext_hum%10
		);


		// Switch last recent track point
		lastTrackPoint = tp;
		id++;

		time = chThdSleepUntilWindowed(time, time + S2ST(TRACK_CYCLE_TIME)); // Wait until time + cycletime
	}
}

void waitForNewTrackPoint(void)
{
	uint32_t old_id = getLastTrackPoint()->id;
	while(old_id == getLastTrackPoint()->id)
		chThdSleepMilliseconds(1000);
}



















