/**
  * I2C wrapper for ChibiOS due to a bug: I2C blocking when I2C transfer suffered timeout
  * @see https://github.com/psas/stm32/commit/32ec8c97a1e5bf605bd5d41a89fc60b60e136af2
  */

#ifndef __I2C_H__
#define __I2C_H__

#include "ch.h"
#include "hal.h"
#include "debug.h"
#include "config.h"

#define I2C_DRIVER_MAIN	(&I2CD2)
#define I2C_DRIVER_CAM	(&I2CD1)

#define i2cInit() { \
	palSetPadMode(PORT(I2C_SDA), PIN(I2C_SDA), PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN); /* I2C SCL */ \
	palSetPadMode(PORT(I2C_SCL), PIN(I2C_SCL), PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN); /* I2C SDA */ \
	i2cStart(&I2CD2, &_i2cfg); \
}
#define i2cCamInit() { \
	palSetPadMode(PORT(CAM_SDA), PIN(CAM_SDA), PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN); /* Camera I2C SCL */ \
	palSetPadMode(PORT(CAM_SCL), PIN(CAM_SCL), PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN); /* Camera I2C SDA */ \
	i2cStart(&I2CD1, &_i2cfg); \
}

#define i2cSendDriver(driver, addr, txbuf, txbytes, rxbuf, rxbytes, timeout) { \
	i2cAcquireBus(driver); \
	msg_t i2c_status = i2cMasterTransmitTimeout(driver, addr, txbuf, txbytes, rxbuf, rxbytes, timeout); \
	if(i2c_status == MSG_TIMEOUT) { /* Restart I2C at timeout */ \
		TRACE_ERROR("I2C  > TIMEOUT > RESTART"); \
		i2cStop(driver); \
		i2cStart(driver, &_i2cfg); \
	} else if(i2c_status == MSG_RESET) { \
		TRACE_ERROR("I2C  > RESET"); \
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
	} else if(i2c_status == MSG_RESET) { \
		TRACE_ERROR("I2C  > RESET"); \
	} \
	i2cReleaseBus(driver); \
}

#define i2cSend(addr, txbuf, txbytes, rxbuf, rxbytes, timeout)		i2cSendDriver(I2C_DRIVER_MAIN, addr, txbuf, txbytes, rxbuf, rxbytes, timeout)
#define i2cReceive(addr, rxbuf, rxbytes, timeout)					i2cReceiveDriver(I2C_DRIVER_MAIN, addr, rxbuf, rxbytes, timeout)

#define i2cCamSend(addr, txbuf, txbytes, rxbuf, rxbytes, timeout)	i2cSendDriver(I2C_DRIVER_CAM, addr, txbuf, txbytes, rxbuf, rxbytes, timeout)
#define i2cCamReceive(addr, rxbuf, rxbytes, timeout)				i2cReceiveDriver(I2C_DRIVER_CAM, addr, rxbuf, rxbytes, timeout)

extern const I2CConfig _i2cfg;

void write8(uint8_t address, uint8_t reg, uint8_t value);
uint8_t read8(uint8_t address, uint8_t reg);
uint16_t read16(uint8_t address, uint8_t reg);
uint16_t read16_LE(uint8_t address, uint8_t reg);
int16_t readS16(uint8_t address, uint8_t reg);
int16_t readS16_LE(uint8_t address, uint8_t reg);

#endif

