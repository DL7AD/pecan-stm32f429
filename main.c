#include "ch.h"
#include "hal.h"
#include "chprintf.h"

#include "ptime.h"
#include "config.h"
#include "debug.h"
#include "modules.h"
#include "drivers/pi2c.h"
#include "drivers/pac1720.h"

static virtual_timer_t vt;
uint32_t counter = 0;
uint32_t error = 0;

/**
  * LED blinking routine
  * RED LED blinks: One or more modules crashed (software watchdog)
  * GREEN LED blinks: I'm alive! (STM32 crashed if not blinking)
  * YELLOW LED: Camera takes a photo (See image.c)
  */
static void led_cb(void *led_sw) {
	// Switch LEDs
	palWritePad(PORT(LED_GREEN), PIN(LED_GREEN), (bool)led_sw);	// Show I'M ALIVE
	if(error) {
		palWritePad(PORT(LED_RED), PIN(LED_RED), (bool)led_sw);	// Show error
	} else {
		palSetPad(PORT(LED_RED), PIN(LED_RED));	// Shut off error
	}

	led_sw = (void*)!led_sw; // Set next state

	chSysLockFromISR();
	chVTSetI(&vt, MS2ST(500), led_cb, led_sw);
	chSysUnlockFromISR();
}

/**
  * Main routine is starting up system, runs the software watchdog (module monitoring), controls LEDs
  */
int main(void) {
	halInit();					// Startup HAL
	chSysInit();				// Startup RTOS

	DEBUG_INIT();				// Debug Init (Serial debug port, LEDs)
	TRACE_INFO("MAIN > Startup");

	TRACE_INFO("MAIN > Startup SENSOR I2C");
	i2cInit();					// Startup I2C
	initEssentialModules();		// Startup required modules (input/output modules)
	initModules();				// Startup optional modules (eg. POSITION, LOG, ...)
	pac1720_init();				// Startup current measurement
	initADC();					// Init ADCs

	chThdSleepMilliseconds(100);

	// Initialize LED timer
	chVTObjectInit(&vt);
	chVTSet(&vt, MS2ST(500), led_cb, 0);

	while(true) {
		// Print time
		PRINT_TIME("MAIN");

		// Software watchdog
		for(uint8_t i=0; i<moduleCount; i++) {
			if(ST2S(chVTGetSystemTimeX()-modules[i]->lastCycle) <= (uint32_t)modules[0]->cycle) {
				TRACE_INFO("MAIN > Module %s OK", modules[i]->name);
				error = 0;
			} else {
				TRACE_ERROR("MAIN > Module %s CRASHED", modules[i]->name);
				error = 1; // Let red LED blink in virtual timer
			}
		}

		chThdSleepMilliseconds(30000);
		counter++;
	}
}

