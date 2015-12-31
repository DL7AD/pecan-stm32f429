/***************************************************************************
  This is a library for the BME280 humidity, temperature & pressure sensor
  Designed specifically to work with the Adafruit BME280 Breakout
  ----> http://www.adafruit.com/products/2650
  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface.
  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!
  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include "ch.h"
#include "hal.h"
#include "bme280.h"
#include <math.h>
#include "../trace.h"

static bme280_calib_data_t calib;
static int32_t t_fine;

void write8(uint8_t reg, uint8_t value)
{
	uint8_t txbuf[] = {reg, value};
	i2cAcquireBus(&I2CD2);
	i2cMasterTransmitTimeout(&I2CD2, BME280_ADDRESS, txbuf, 2, NULL, 0, MS2ST(10));
	i2cReleaseBus(&I2CD2);
}

uint8_t read8(uint8_t reg)
{
	uint8_t txbuf[] = {reg};
	uint8_t rxbuf[1];

	i2cAcquireBus(&I2CD2);
	i2cMasterTransmitTimeout(&I2CD2, BME280_ADDRESS, txbuf, 1, rxbuf, 1, MS2ST(10));
	i2cReleaseBus(&I2CD2);

	return rxbuf[0];
}

uint16_t read16(uint8_t reg)
{
	uint8_t txbuf[] = {reg};
	uint8_t rxbuf[2];

	i2cAcquireBus(&I2CD2);
	i2cMasterTransmitTimeout(&I2CD2, BME280_ADDRESS, txbuf, 1, rxbuf, 2, MS2ST(10));
	i2cReleaseBus(&I2CD2);

	return (rxbuf[0] << 8) | rxbuf[1];
}

uint16_t read16_LE(uint8_t reg) {
	uint16_t temp = read16(reg);
	return (temp >> 8) | (temp << 8);
}

int16_t readS16(uint8_t reg)
{
	return (int16_t)read16(reg);
}

int16_t readS16_LE(uint8_t reg)
{
	return (int16_t)read16_LE(reg);
}

/**
  * Initializes BME280 and reads calibration data
  */
void BME280_Init(void)
{
	calib.dig_T1 = read16_LE(BME280_REGISTER_DIG_T1);
	calib.dig_T2 = readS16_LE(BME280_REGISTER_DIG_T2);
	calib.dig_T3 = readS16_LE(BME280_REGISTER_DIG_T3);

	calib.dig_P1 = read16_LE(BME280_REGISTER_DIG_P1);
	calib.dig_P2 = readS16_LE(BME280_REGISTER_DIG_P2);
	calib.dig_P3 = readS16_LE(BME280_REGISTER_DIG_P3);
	calib.dig_P4 = readS16_LE(BME280_REGISTER_DIG_P4);
	calib.dig_P5 = readS16_LE(BME280_REGISTER_DIG_P5);
	calib.dig_P6 = readS16_LE(BME280_REGISTER_DIG_P6);
	calib.dig_P7 = readS16_LE(BME280_REGISTER_DIG_P7);
	calib.dig_P8 = readS16_LE(BME280_REGISTER_DIG_P8);
	calib.dig_P9 = readS16_LE(BME280_REGISTER_DIG_P9);

	calib.dig_H1 = read8(BME280_REGISTER_DIG_H1);
	calib.dig_H2 = readS16_LE(BME280_REGISTER_DIG_H2);
	calib.dig_H3 = read8(BME280_REGISTER_DIG_H3);
	calib.dig_H4 = (read8(BME280_REGISTER_DIG_H4) << 4) | (read8(BME280_REGISTER_DIG_H4+1) & 0xF);
	calib.dig_H5 = (read8(BME280_REGISTER_DIG_H5+1) << 4) | (read8(BME280_REGISTER_DIG_H5) >> 4);
	calib.dig_H6 = (int8_t)read8(BME280_REGISTER_DIG_H6);

	write8(BME280_REGISTER_CONTROLHUMID, 0x03); // Set before CONTROL (DS 5.4.3)
	write8(BME280_REGISTER_CONTROL, 0x3F);
	chThdSleepMilliseconds(50); // Wait for BME280

	BME280_getTemperature(); // Read t_fine
}

/**
  * Reads the temperature
  * @return Temperature in degC * 100
  */
int16_t BME280_getTemperature(void)
{
	int32_t var1, var2;

	int32_t adc_T = read16(BME280_REGISTER_TEMPDATA);
	adc_T <<= 8;
	adc_T |= read8(BME280_REGISTER_TEMPDATA+2);
	adc_T >>= 4;

	var1 = ((((adc_T>>3) - ((int32_t)calib.dig_T1 <<1))) * ((int32_t)calib.dig_T2)) >> 11;
	var2 = (((((adc_T>>4) - ((int32_t)calib.dig_T1)) * ((adc_T>>4) - ((int32_t)calib.dig_T1))) >> 12) * ((int32_t)calib.dig_T3)) >> 14;

	t_fine = var1 + var2;

	return (t_fine * 5 + 128) >> 8;
}

/**
  * Reads the barometric pressure
  * @param Values to be sampled
  * @return Pressure in Pa * 10
  */
uint32_t BME280_getPressure(uint16_t means) {
	int64_t var1, var2, p;

	uint64_t sum = 0;
	for(uint16_t i=0; i<means; i++) {
		int32_t adc_P = read16(BME280_REGISTER_PRESSUREDATA);
		adc_P <<= 8;
		adc_P |= read8(BME280_REGISTER_PRESSUREDATA+2);
		adc_P >>= 4;

		var1 = ((int64_t)t_fine) - 128000;
		var2 = var1 * var1 * (int64_t)calib.dig_P6;
		var2 = var2 + ((var1*(int64_t)calib.dig_P5)<<17);
		var2 = var2 + (((int64_t)calib.dig_P4)<<35);
		var1 = ((var1 * var1 * (int64_t)calib.dig_P3)>>8) + ((var1 * (int64_t)calib.dig_P2)<<12);
		var1 = (((((int64_t)1)<<47)+var1))*((int64_t)calib.dig_P1)>>33;

		if (var1 == 0)
			return 0;  // avoid exception caused by division by zero

		p = 1048576 - adc_P;
		p = (((p<<31) - var2)*3125) / var1;
		var1 = (((int64_t)calib.dig_P9) * (p>>13) * (p>>13)) >> 25;
		var2 = (((int64_t)calib.dig_P8) * p) >> 19;

		sum += ((p + var1 + var2) >> 8) + (((int64_t)calib.dig_P7)<<4);
	}

	return sum/(means*26);
}

/**
  * Reads the relative humidity
  * @return rel. humidity in % * 10
  */
uint16_t BME280_getHumidity(void) {
	int32_t adc_H = read16(BME280_REGISTER_HUMIDDATA);

	int32_t v_x1_u32r;

	v_x1_u32r = (t_fine - ((int32_t)76800));

	v_x1_u32r = (((((adc_H << 14) - (((int32_t)calib.dig_H4) << 20) -
		(((int32_t)calib.dig_H5) * v_x1_u32r)) + ((int32_t)16384)) >> 15) *
		(((((((v_x1_u32r * ((int32_t)calib.dig_H6)) >> 10) *
		(((v_x1_u32r * ((int32_t)calib.dig_H3)) >> 11) + ((int32_t)32768))) >> 10) +
		((int32_t)2097152)) * ((int32_t)calib.dig_H2) + 8192) >> 14));

	v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) * ((int32_t)calib.dig_H1)) >> 4));

	v_x1_u32r = (v_x1_u32r < 0) ? 0 : v_x1_u32r;
	v_x1_u32r = (v_x1_u32r > 419430400) ? 419430400 : v_x1_u32r;
	float h = (v_x1_u32r>>12);
	return h / 102;
}

/**
  * Calculates the altitude (in meters) from the specified atmospheric
  * pressure (in Pa*10), and sea-level pressure (in Pa).
  * @param seaLevel Sea-level pressure in Pa
  * @param atmospheric Airpressure in Pa*10
  * @return altitude in cm
  */
int32_t BME280_getAltitude(uint32_t seaLevel, uint32_t atmospheric)
{
	return (1.0-pow((float)atmospheric/(float)(seaLevel*10), 1.0/5.255)) * 288150000 / 65;
}
