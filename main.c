#include "ch.h"
#include "hal.h"
#include "chprintf.h"

#include "ptime.h"
#include "config.h"
#include "trace.h"

uint32_t counter = 0;

static const I2CConfig i2cfg2 = {
	OPMODE_I2C,
	400000,
	FAST_DUTY_CYCLE_2,
};

int main(void) {
	// Startup RTOS
	halInit();
	chSysInit();

	palSetPadMode(GPIOE, 3, PAL_MODE_OUTPUT_PUSHPULL);

	// Trace Init
	TRACE_INIT();
	TRACE_INFO("MAIN > Startup");

	// Startup modules
	//MODULES();




	palSetPadMode(GPIOB, 10, PAL_MODE_ALTERNATE(4));
	palSetPadMode(GPIOB, 11, PAL_MODE_ALTERNATE(4));
	i2cStart(&I2CD2, &i2cfg2);

	uint8_t rxbuf[1];
	uint8_t txbuf[1];
	for(uint8_t i=1; i<127; i++) {
		i2cAcquireBus(&I2CD2);

		palSetPad(GPIOE, 3);
		msg_t status = i2cMasterTransmitTimeout(&I2CD2, i, txbuf, 1, rxbuf, 1, MS2ST(100));

		i2cReleaseBus(&I2CD2);
		if(status == MSG_OK) {
			TRACE_DEBUG("Found I2C slave %d", i);
		} else {
			TRACE_DEBUG("No I2C slave %d (%d)", i, status);

			i2cStop(&I2CD2);
			i2cStart(&I2CD2, &i2cfg2);
		}
		chThdSleepMilliseconds(100);
	}





	while(1) {
		palTogglePad(GPIOE, 3); // Toggle LED to show: I'M ALIVE

		if(counter%60 == 0) // Print time every 30 seconds
			PRINT_TIME("MAIN");

		chThdSleepMilliseconds(500);
		counter++;
	}
}

