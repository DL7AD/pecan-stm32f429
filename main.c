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

	// Startup I2C
	TRACE_INFO("MAIN > Startup SENSOR I2C");
	i2cStart(&I2CD2, &i2cfg2);

	// Startup modules
	MODULES();

	while(true) {
		palTogglePad(GPIOE, 3); // Toggle LED to show: I'M ALIVE

		if(counter%60 == 0) // Print time every 30 seconds
			PRINT_TIME("MAIN");

		chThdSleepMilliseconds(500);
		counter++;
	}
}

