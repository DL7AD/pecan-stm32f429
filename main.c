#include "ch.h"
#include "hal.h"
#include "chprintf.h"

#include "ptime.h"
#include "config.h"
#include "debug.h"
#include "modules.h"
#include "drivers/pi2c.h"
#include "drivers/pac1720.h"

uint32_t counter = 0;
uint32_t error = 0;

int main(void) {
	halInit();			// Startup HAL
	chSysInit();		// Startup RTOS

	DEBUG_INIT();		// Debug Init (Serial debug port, LEDs)

	TRACE_INFO("MAIN > Startup");
	TRACE_INFO("MAIN > Startup SENSOR I2C");
	i2cInit();					// Startup I2C
	initEssentialModules();		// Startup required modules
	initModules();				// Startup optional modules
	pac1720_init();				// Startup current measurement

	while(true) {
		palWritePad(PORT(LED_GREEN), PIN(LED_GREEN), counter%2);	// Show I'M ALIVE
		if(error)
			palWritePad(PORT(LED_RED), PIN(LED_RED), counter%2);	// Show error

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

