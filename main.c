#include "ch.h"
#include "hal.h"

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

