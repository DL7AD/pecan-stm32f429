/**
  * I2C wrapper for ChibiOS due to a bug: I2C blocking when I2C transfer suffered timeout
  * @see https://github.com/psas/stm32/commit/32ec8c97a1e5bf605bd5d41a89fc60b60e136af2
  */
#include "ch.h"
#include "hal.h"
#include "pi2c.h"

const I2CConfig _i2cfg = {
	OPMODE_I2C,
	200000,
	FAST_DUTY_CYCLE_2,
};

void write8(uint8_t address, uint8_t reg, uint8_t value)
{
	uint8_t txbuf[] = {reg, value};
	i2cSend(address, txbuf, 2, NULL, 0, MS2ST(10));
}

uint8_t read8(uint8_t address, uint8_t reg)
{
	uint8_t txbuf[] = {reg};
	uint8_t rxbuf[1];
	i2cSend(address, txbuf, 1, rxbuf, 1, MS2ST(10));
	return rxbuf[0];
}

uint16_t read16(uint8_t address, uint8_t reg)
{
	uint8_t txbuf[] = {reg};
	uint8_t rxbuf[2];
	i2cSend(address, txbuf, 1, rxbuf, 2, MS2ST(10));
	return (rxbuf[0] << 8) | rxbuf[1];
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
