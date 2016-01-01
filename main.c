#include "ch.h"
#include "hal.h"
#include "chprintf.h"

#include "ptime.h"
#include "config.h"
#include "trace.h"
#include "modules.h"
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

		if(counter%60 == 0) {

			// Print time
			PRINT_TIME("MAIN");

			// Module integration check (software watchdog)
			for(uint8_t i=0; i<moduleCount; i++) {
				if(ST2S(chVTGetSystemTimeX()-modules[i]->lastCycle) <= (uint32_t)modules[0]->cycle) {
					TRACE_INFO("MAIN > Module %s OK", modules[i]->name);
				} else {
					TRACE_ERROR("MAIN > Module %s CRASHED", modules[i]->name);
				}
			}

		}

		chThdSleepMilliseconds(500);
		counter++;
	}
}

