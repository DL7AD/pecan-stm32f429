#include "ch.h"
#include "hal.h"
#include "chprintf.h"

#include "ptime.h"
#include "config.h"
#include "trace.h"
#include "drivers/bme280.h"
#include "drivers/pi2c.h"

uint32_t counter = 0;

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
	i2cInit();

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

