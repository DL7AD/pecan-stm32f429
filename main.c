#include "ch.h"
#include "hal.h"
#include "chprintf.h"

#include "ptime.h"
#include "config.h"
#include "trace.h"
#include "drivers/bme280.h"

uint32_t counter = 0;

static const I2CConfig i2cfg2 = {
	OPMODE_I2C,
	400000,
	FAST_DUTY_CYCLE_2,
};

int main(void) {
	// Startup RTOS
	halInit();
	chSysInit();

	palSetPadMode(GPIOE, 3, PAL_MODE_OUTPUT_PUSHPULL);

	// Trace Init
	TRACE_INIT();
	TRACE_INFO("MAIN > Startup");

	TRACE_INFO("MAIN > Startup SENSOR I2C");
	i2cStart(&I2CD2, &i2cfg2);

	// Startup modules
	MODULES();

	BME280_Init();
	while(true) {
		palTogglePad(GPIOE, 3); // Toggle LED to show: I'M ALIVE

		int16_t  temp  = BME280_getTemperature();
		uint32_t press = BME280_getPressure(256);
		uint16_t hum   = BME280_getHumidity();
		int32_t alt    = BME280_getAltitude(P_0, press);
		TRACE_INFO("BME  > T=%d.%02ddegC p=%d.%01dPa phi=%d.%01d%% a=%d.%02dm", temp/100, temp%100, press/10, press%10, hum/10, hum%10, alt/100, alt%100);

		if(counter%60 == 0) // Print time every 30 seconds
			PRINT_TIME("MAIN");

		chThdSleepMilliseconds(500);
		counter++;
	}
}

