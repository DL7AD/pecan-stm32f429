#include "ch.h"
#include "hal.h"
#include "chprintf.h"

#include "ptime.h"
#include "config.h"
#include "trace.h"
#include "modules.h"
#include "drivers/pi2c.h"
#include "drivers/pac1720.h"

uint32_t counter = 0;
uint32_t error = 0;

int main(void) {
	// Startup RTOS
	halInit();
	chSysInit();

	palSetPadMode(GPIOE, 3, PAL_MODE_OUTPUT_PUSHPULL);	// LED green
	palSetPadMode(GPIOC, 13, PAL_MODE_OUTPUT_PUSHPULL);	// LED yellow
	palSetPadMode(GPIOC, 15, PAL_MODE_OUTPUT_PUSHPULL);	// LED red

	// Trace Init
	TRACE_INIT();
	TRACE_INFO("MAIN > Startup");

	// Startup I2C
	TRACE_INFO("MAIN > Startup SENSOR I2C");
	i2cInit();

	// Startup modules
	MODULES();

	// Startup current measurement
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(256), NORMALPRIO, pac1720, NULL);

	while(true) {
		palWritePad(GPIOE, 3, counter%2);		// Show I'M ALIVE
		if(error)
			palWritePad(GPIOC, 15, counter%2);	// Show error

		if(counter%60 == 0) {

			// Print time
			PRINT_TIME("MAIN");

			// Module integration check (software watchdog)
			for(uint8_t i=0; i<moduleCount; i++) {
				if(ST2S(chVTGetSystemTimeX()-modules[i]->lastCycle) <= (uint32_t)modules[0]->cycle) {
					TRACE_INFO("MAIN > Module %s OK", modules[i]->name);
				} else {
					TRACE_ERROR("MAIN > Module %s CRASHED", modules[i]->name);
					error = 1;
				}
			}

		}

		chThdSleepMilliseconds(500);
		counter++;
	}
}

