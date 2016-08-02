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
#include "flash.h"

static trackPoint_t trackPoints[2];
static trackPoint_t* lastTrackPoint;
static uint32_t logEntryCounter;
static systime_t nextLogEntryTimer;

/**
  * Returns most recent track point witch is complete.
  */
trackPoint_t* getLastTrackPoint(void)
{
	return lastTrackPoint;
}

void getLogTrackPoints(logTrackPoint_t* log, uint32_t id, uint8_t size)
{
	uint32_t address = LOG_FLASH_ADDR + (id % (LOG_FLASH_SIZE/sizeof(logTrackPoint_t))) * sizeof(logTrackPoint_t);
	flashRead(address, (char*)log, sizeof(logTrackPoint_t) * size);
}

static void writeLogTrackPoint(trackPoint_t* tp)
{
	// Create Log track point
	logTrackPoint_t ltp;
	ltp.time = date2UnixTimestamp(tp->time);
	ltp.gps_lat = tp->gps_lat;
	ltp.gps_lon = tp->gps_lon;
	ltp.gps_alt = tp->gps_alt < 0 ? 0 : (uint16_t)tp->gps_alt & 0xFFFF;

	// Erase flash if start of new sector is reached
	uint32_t address = LOG_FLASH_ADDR + logEntryCounter * sizeof(logTrackPoint_t);
	if(address % LOG_FLASH_PAGE_SIZE == 0) // Found start of flash sector
	{
		if(!flashIsErased(address, LOG_FLASH_PAGE_SIZE))
		{
			TRACE_INFO("TRAC > Erase flash %08x", address);
			flashErase(address, LOG_FLASH_PAGE_SIZE);
		}
	}

	// Write data into flash
	TRACE_INFO("TRAC > Flash write (ADDR=%08x)", address);
	flashSectorBegin(flashSectorAt(address));
	flashWrite(address, (char*)&ltp, sizeof(logTrackPoint_t));
	flashSectorEnd(flashSectorAt(address));

	// Verify
	if(flashCompare(address, (char*)&ltp, sizeof(logTrackPoint_t)))
		TRACE_INFO("TRAC > Flash write OK")
	else
		TRACE_ERROR("TRAC > Flash write failed");

	// Increment log counter
	logEntryCounter = (logEntryCounter+1) % (LOG_FLASH_SIZE/sizeof(logTrackPoint_t));
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

	// Find next free log entry
	for(uint32_t address = LOG_FLASH_ADDR; address < LOG_FLASH_ADDR+LOG_FLASH_SIZE; address += sizeof(logTrackPoint_t))
	{
		logTrackPoint_t pt;
		flashRead(address, (char*)&pt, sizeof(logTrackPoint_t));
		if(pt.time == 0xFFFFFFFF)
			break;
		logEntryCounter++;
	}
	TRACE_WARN("TRAC > Next log entry ID=%d", logEntryCounter);


	// Initial fill by PAC1720 and BME280 and RTC

	// Time
	ptime_t rtc;
	getTime(&rtc);
	lastTrackPoint->time.year = rtc.year;
	lastTrackPoint->time.month = rtc.month;
	lastTrackPoint->time.day = rtc.day;
	lastTrackPoint->time.hour = rtc.hour;
	lastTrackPoint->time.minute = rtc.minute;
	lastTrackPoint->time.second = rtc.second;

	// Get last GPS fix from memory
	logTrackPoint_t lastLogPoint;
	uint32_t address = LOG_FLASH_ADDR + ((logEntryCounter-1) % (LOG_FLASH_SIZE/sizeof(logTrackPoint_t))) * sizeof(logTrackPoint_t);
	flashRead(address, (char*)&lastLogPoint, sizeof(logTrackPoint_t));

	// Last GPS fix
	lastTrackPoint->gps_lock = 0;
	lastTrackPoint->gps_lat = lastLogPoint.gps_lat;
	lastTrackPoint->gps_lon = lastLogPoint.gps_lon;
	lastTrackPoint->gps_alt = lastLogPoint.gps_alt;
	lastTrackPoint->gps_sats = 0;
	lastTrackPoint->gps_ttff = 0;

	// Debug last stored GPS position
	if(lastLogPoint.time != 0xFFFFFFFF) {
		TRACE_INFO(
			"TRAC > Last GPS position (from memory)\r\n"
			"%s Latitude: %d.%07ddeg\r\n"
			"%s Longitude: %d.%07ddeg\r\n"
			"%s Altitude: %d Meter",
			TRACE_TAB, lastTrackPoint->gps_lat/10000000, (lastTrackPoint->gps_lat > 0 ? 1:-1)*lastTrackPoint->gps_lat%10000000,
			TRACE_TAB, lastTrackPoint->gps_lon/10000000, (lastTrackPoint->gps_lon > 0 ? 1:-1)*lastTrackPoint->gps_lon%10000000,
			TRACE_TAB, lastTrackPoint->gps_alt
		);
	} else {
		TRACE_INFO("TRAC > No GPS position in memory");
	}

	// Voltage/Current
	lastTrackPoint->adc_solar = getSolarVoltageMV();
	lastTrackPoint->adc_battery = getBatteryVoltageMV();
	lastTrackPoint->adc_charge = pac1720_getPowerCharge();
	lastTrackPoint->adc_discharge = pac1720_getPowerDischarge();

	bme280_t bmeInt;
	bme280_t bmeExt;

	// Atmosphere condition
	if(BME280_isAvailable(BME280_ADDRESS_INT)) {
		BME280_Init(&bmeInt, BME280_ADDRESS_INT);
		lastTrackPoint->int_press = BME280_getPressure(&bmeInt, 256);
		lastTrackPoint->int_hum = BME280_getHumidity(&bmeInt);
		lastTrackPoint->int_temp = BME280_getTemperature(&bmeInt);
	} else { // No internal BME280 found
		TRACE_ERROR("TRAC > Internal BME280 not available");
		lastTrackPoint->int_press = 0;
		lastTrackPoint->int_hum = 0;
		lastTrackPoint->int_temp = 0;
	}

	// External BME280
	if(BME280_isAvailable(BME280_ADDRESS_EXT)) {
		BME280_Init(&bmeExt, BME280_ADDRESS_EXT);
		lastTrackPoint->ext_press = BME280_getPressure(&bmeExt, 256);
		lastTrackPoint->ext_hum = BME280_getHumidity(&bmeExt);
		lastTrackPoint->ext_temp = BME280_getTemperature(&bmeExt);
	} else { // No external BME280 found
		TRACE_WARN("TRAC > External BME280 not available");
		lastTrackPoint->ext_press = 0;
		lastTrackPoint->ext_hum = 0;
		lastTrackPoint->ext_temp = 0;
	}

	systime_t time = chVTGetSystemTimeX();
	while(true)
	{
		TRACE_INFO("TRAC > Do module TRACKING MANAGER cycle");
		watchdog_tracking = chVTGetSystemTimeX(); // Update watchdog timer

		trackPoint_t* tp = &trackPoints[id % (sizeof(trackPoints) / sizeof(trackPoint_t))]; // Current track point
		trackPoint_t* ltp = &trackPoints[(id-1) % (sizeof(trackPoints) / sizeof(trackPoint_t))]; // Last track point

		// Search for GPS satellites
		gpsFix_t gpsFix = {{0,0,0,0,0,0,0},0,0,0,0,0};

		// Switch on GPS is enough power is available
		uint16_t batt = getBatteryVoltageMV();
		if(batt >= GPS_ON_VBAT)
		{
			// Switch on GPS
			GPS_Init();

			// Search for lock as long enough power is available
			do {
				batt = getBatteryVoltageMV();
				gps_get_fix(&gpsFix);
			} while(!isGPSLocked(&gpsFix) && batt >= GPS_OFF_VBAT && chVTGetSystemTimeX() <= time + S2ST(TRACK_CYCLE_TIME-5)); // Do as long no GPS lock and within timeout, timeout=cycle-1sec (-1sec in order to keep synchronization)

			if(batt < GPS_OFF_VBAT) // Switch off GPS at low batt
				GPS_Deinit();
		}

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
			getTime(&rtc);
			tp->time.year = rtc.year;
			tp->time.month = rtc.month;
			tp->time.day = rtc.day;
			tp->time.hour = rtc.hour;
			tp->time.minute = rtc.minute;
			tp->time.second = rtc.second;

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

		// Append logging (timeout)
		if(nextLogEntryTimer <= chVTGetSystemTimeX() && isGPSLocked(&gpsFix))
		{
			writeLogTrackPoint(tp);
			nextLogEntryTimer += S2ST(LOG_CYCLE_TIME);
		}

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

