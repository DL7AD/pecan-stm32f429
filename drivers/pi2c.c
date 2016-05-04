/**
  * I2C wrapper for ChibiOS due to a bug: I2C blocking when I2C transfer suffered timeout
  * @see https://github.com/psas/stm32/commit/32ec8c97a1e5bf605bd5d41a89fc60b60e136af2
  */
#include "ch.h"
#include "hal.h"
#include "pi2c.h"

const I2CConfig _i2cfg = {
	OPMODE_I2C,
	150000,
	FAST_DUTY_CYCLE_2,
};

mutex_t pi2c_mtx;

void write8_lock(uint8_t address, uint8_t reg, uint8_t value)
{
	uint8_t txbuf[] = {reg, value};
	i2cSend(address, txbuf, 2, NULL, 0, MS2ST(100));
}

void writeN_lock(uint8_t address, uint8_t *txbuf, uint32_t length)
{
	i2cSend(address, txbuf, length, NULL, 0, MS2ST(100));
}

uint8_t read8_lock(uint8_t address, uint8_t reg)
{
	uint8_t txbuf[] = {reg};
	uint8_t rxbuf[1];
	i2cSend(address, txbuf, 1, rxbuf, 1, MS2ST(100));
	return rxbuf[0];
}

uint16_t read16_lock(uint8_t address, uint8_t reg)
{
	uint8_t txbuf[] = {reg};
	uint8_t rxbuf[2];
	i2cSend(address, txbuf, 1, rxbuf, 2, MS2ST(100));
	return (rxbuf[0] << 8) | rxbuf[1];
}


void write8(uint8_t address, uint8_t reg, uint8_t value)
{
	chMtxLock(&pi2c_mtx);
	write8_lock(address, reg, value);
	chMtxUnlock(&pi2c_mtx);
}

void writeN(uint8_t address, uint8_t *txbuf, uint32_t length)
{
	chMtxLock(&pi2c_mtx);
	writeN_lock(address, txbuf, length);
	chMtxUnlock(&pi2c_mtx);
}

uint8_t read8(uint8_t address, uint8_t reg)
{
	chMtxLock(&pi2c_mtx);
	uint8_t ret = read8_lock(address, reg);
	chMtxUnlock(&pi2c_mtx);
	return ret;
}

uint16_t read16(uint8_t address, uint8_t reg)
{
	chMtxLock(&pi2c_mtx);
	uint16_t ret = read16_lock(address, reg);
	chMtxUnlock(&pi2c_mtx);
	return ret;
}

uint16_t read16_LE(uint8_t address, uint8_t reg) {
	uint16_t temp = read16(address, reg);
	return (temp >> 8) | (temp << 8);
}

int16_t readS16(uint8_t address, uint8_t reg)
{
	return (int16_t)read16(address, reg);
}

int16_t readS16_LE(uint8_t address, uint8_t reg)
{
	return (int16_t)read16_LE(address, reg);
}

void pi2cInit(void)
{
	TRACE_INFO("I2C  > Startup");
	// palSetPadMode(PORT(I2C_SDA), PIN(I2C_SDA), PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN); // I2C SCL
	// palSetPadMode(PORT(I2C_SCL), PIN(I2C_SCL), PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN); // I2C SDA
	i2cStart(&I2CD2, &_i2cfg);
	chMtxObjectInit(&pi2c_mtx);
}

void aquireI2cExclusive(void)
{
	chMtxLock(&pi2c_mtx);
}

void releaseI2cExclusive(void)
{
	chMtxUnlock(&pi2c_mtx);
}

