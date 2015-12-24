#include "ch.h"
#include "hal.h"
#include "chprintf.h"

#include "aprs.h"
#include "ptime.h"
#include "config.h"
#include "trace.h"

const SerialConfig sc1_config =
{
    115200,     // baud rate
    0,          // CR1 register
    0,          // CR2 register
    0           // CR3 register
};

int main(void) {
	// Startup RTOS
	halInit();
	chSysInit();

	// Trace Init
	TRACE_INIT();
	TRACE_INFO("Startup");

	// Startup modules
	MODULES();

	while(true) { // Print time every 30 seconds
		PRINT_TIME();
		chThdSleepMilliseconds(30000);
	}
}

