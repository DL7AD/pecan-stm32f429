#include "ch.h"
#include "hal.h"
#include "chprintf.h"

#include "ptime.h"
#include "config.h"
#include "trace.h"

uint32_t counter = 0;

int main(void) {
	// Startup RTOS
	halInit();
	chSysInit();

	// Trace Init
	TRACE_INIT();
	TRACE_INFO("MAIN > Startup");

	// Startup modules
	MODULES();

    palSetPadMode(GPIOE, 3, PAL_MODE_OUTPUT_PUSHPULL);

	while(1) {
		palTogglePad(GPIOE, 3); // Toggle LED to show: I'M ALIVE

		if(counter%60 == 0) // Print time every 30 seconds
			PRINT_TIME("MAIN");

		chThdSleepMilliseconds(500);
		counter++;
	}
}

