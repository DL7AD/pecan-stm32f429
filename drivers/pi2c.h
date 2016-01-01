/**
  * I2C wrapper for ChibiOS due to a bug: I2C blocking when I2C transfer suffered timeout
  * @see https://github.com/psas/stm32/commit/32ec8c97a1e5bf605bd5d41a89fc60b60e136af2
  */

#ifndef __I2C_H__
#define __I2C_H__

#include "ch.h"
#include "hal.h"

#define i2cInit() i2cStart(&I2CD2, &_i2cfg2);

#define i2cSend(addr, txbuf, txbytes, rxbuf, rxbytes, timeout) { \
	i2cAcquireBus(&I2CD2); \
	msg_t i2c_status = i2cMasterTransmitTimeout(&I2CD2, addr, txbuf, txbytes, rxbuf, rxbytes, timeout); \
	if(i2c_status == MSG_TIMEOUT) { /* Restart I2C at timeout */ \
		i2cStop(&I2CD2); \
		i2cStart(&I2CD2, &_i2cfg2); \
	} \
	i2cReleaseBus(&I2CD2); \
}

#define i2cReceive(addr, rxbuf, rxbytes, timeout) { \
	i2cAcquireBus(&I2CD2); \
	msg_t i2c_status = i2cMasterTransmitTimeout(&I2CD2, addr, rxbuf, rxbytes, timeout); \
	if(i2c_status == MSG_TIMEOUT) { /* Restart I2C at timeout */ \
		i2cStop(&I2CD2); \
		i2cStart(&I2CD2, &_i2cfg2); \
	} \
	i2cReleaseBus(&I2CD2); \
}

extern const I2CConfig _i2cfg2;

#endif

