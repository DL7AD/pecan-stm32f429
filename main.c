#include "ch.h"
#include "hal.h"

#include "aprs.h"
#include "time.h"
#include "sgp4.h"
#include "config.h"

int main(void) {
	// Startup RTOS
	halInit();
	chSysInit();

	// Startup modules
	MODULES();

	while(true) {
		chThdSleepMilliseconds(100);
	}
}

