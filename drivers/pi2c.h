/**
  * I2C wrapper for ChibiOS due to a bug: I2C blocking when I2C transfer suffered timeout
  * @see https://github.com/psas/stm32/commit/32ec8c97a1e5bf605bd5d41a89fc60b60e136af2
  */

#ifndef __I2C_H__
#define __I2C_H__

#include "ch.h"
#include "hal.h"
#include "../trace.h"

#define i2cInit() i2cStart(&I2CD2, &_i2cfg);
#define i2cCamInit() i2cStart(&I2CD1, &_i2cfg);

#define i2cSendDriver(driver, addr, txbuf, txbytes, rxbuf, rxbytes, timeout) { \
	i2cAcquireBus(driver); \
	msg_t i2c_status = i2cMasterTransmitTimeout(driver, addr, txbuf, txbytes, rxbuf, rxbytes, timeout); \
	if(i2c_status == MSG_TIMEOUT) { /* Restart I2C at timeout */ \
		TRACE_ERROR("I2C  > TIMEOUT > RESTART"); \
		i2cStop(driver); \
		i2cStart(driver, &_i2cfg); \
	} \
	i2cReleaseBus(driver); \
}

#define i2cReceiveDriver(driver, addr, rxbuf, rxbytes, timeout) { \
	i2cAcquireBus(driver); \
	msg_t i2c_status = i2cMasterTransmitTimeout(driver, addr, rxbuf, rxbytes, timeout); \
	if(i2c_status == MSG_TIMEOUT) { /* Restart I2C at timeout */ \
		TRACE_ERROR("I2C  > TIMEOUT > RESTART"); \
		i2cStop(driver); \
		i2cStart(driver, &_i2cfg); \
	} \
	i2cReleaseBus(driver); \
}

#define i2cSend(addr, txbuf, txbytes, rxbuf, rxbytes, timeout)		i2cSendDriver(&I2CD2, addr, txbuf, txbytes, rxbuf, rxbytes, timeout)
#define i2cReceive(addr, rxbuf, rxbytes, timeout)					i2cReceiveDriver(&I2CD2, addr, rxbuf, rxbytes, timeout)

#define i2cCamSend(addr, txbuf, txbytes, rxbuf, rxbytes, timeout)	i2cSendDriver(&I2CD1, addr, txbuf, txbytes, rxbuf, rxbytes, timeout)
#define i2cCamReceive(addr, rxbuf, rxbytes, timeout)				i2cReceiveDriver(&I2CD1, addr, rxbuf, rxbytes, timeout)

extern const I2CConfig _i2cfg;

#endif

