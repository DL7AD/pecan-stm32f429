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

	TRACE_INFO("startup");

	// Startup modules
	MODULES();

	/* ptime_t time;
	time.year = 2015;
	time.month = 12;
	time.day = 20;
	time.hour = 23;
	time.minute = 40;
	time.second = 30;
	setTime(time); */

	getLastGPSPosition();

	while(true) { // Print time every 60 seconds
		ptime_t time = getTime();
		TRACE_INFO("Current time: %02d-%02d-%02d %02d:%02d:%02d %03d", time.year, time.month, time.day, time.hour, time.minute, time.second, time.millisecond);
		chThdSleepMilliseconds(60000);
	}
}

