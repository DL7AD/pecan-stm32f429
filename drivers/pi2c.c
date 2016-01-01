/**
  * I2C wrapper for ChibiOS due to a bug: I2C blocking when I2C transfer suffered timeout
  * @see https://github.com/psas/stm32/commit/32ec8c97a1e5bf605bd5d41a89fc60b60e136af2
  */
#include "ch.h"
#include "hal.h"

const I2CConfig _i2cfg2 = {
	OPMODE_I2C,
	200000,
	FAST_DUTY_CYCLE_2,
};
