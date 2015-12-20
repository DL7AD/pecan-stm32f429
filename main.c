#include "ch.h"
#include "hal.h"
#include "chprintf.h"

#include "aprs.h"
#include "ptime.h"
#include "config.h"

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

    sdStart(&SD1, &sc1_config);
    palSetPadMode(GPIOA, 9,  PAL_MODE_ALTERNATE(7)); // Must be changed to PA0 and PA1 when Pecan Pico 7 is used instead of discovery board
    palSetPadMode(GPIOA, 10, PAL_MODE_ALTERNATE(7));

	// Startup modules
	MODULES();

	ptime_t time;
	time.year = 2015;
	time.month = 12;
	time.day = 20;
	time.hour = 23;
	time.minute = 40;
	time.second = 30;
	setTime(time);

	while(true) {
		ptime_t time = getTime();
		chprintf((BaseSequentialStream*)&SD1, "%02d-%02d-%02d %02d:%02d:%02d %03d\r\n", time.year, time.month, time.day, time.hour, time.minute, time.second, time.millisecond);
		chThdSleepMilliseconds(100);
	}
}

