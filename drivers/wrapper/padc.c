#include "ch.h"
#include "hal.h"
#include "defines.h"
#include "config.h"
#include "padc.h"
#include "pac1720.h"
#include "debug.h"

#define ADC_GRP1_NUM_CHANNELS	3		/* Amount of channels (solar, battery, temperature) */
#define VCC_REF					1836	/* mV */

#define DIVIDER_VSOL			2/1		/* VSol --- 1kOhm -- ADC --- 1kOhm -- GND */
#define DIVIDER_VBAT			200/64	/* VBat -- 33KOhm -- ADC -- 10kOhm -- GND */

static adcsample_t samples[ADC_GRP1_NUM_CHANNELS*2]; // ADC sample buffer

void adccb(ADCDriver *adcp, adcsample_t *buffer, size_t n) {
	(void)adcp;
	(void)buffer;
	(void)n;
}

/*
 * ADC conversion group.
 * Mode:        Linear buffer, 4 samples of 3 channels, SW triggered.
 * Channels:    Solar voltage divider    ADC12_IN14
 *              Battery voltage divider  ADC12_IN15
 *              Temperature sensor       ADC1_IN16
 */
static const ADCConversionGroup adcgrpcfg = {
	FALSE,
	ADC_GRP1_NUM_CHANNELS,
	adccb,
	NULL,
	/* HW dependent part.*/
	0,
	ADC_CR2_SWSTART,
	ADC_SMPR1_SMP_AN14(ADC_SAMPLE_56) | ADC_SMPR1_SMP_AN15(ADC_SAMPLE_56) | ADC_SMPR1_SMP_SENSOR(ADC_SAMPLE_144),
	0,
	ADC_SQR1_NUM_CH(ADC_GRP1_NUM_CHANNELS),
	0,
	ADC_SQR3_SQ2_N(ADC_CHANNEL_IN14) | ADC_SQR3_SQ1_N(ADC_CHANNEL_IN15) | ADC_SQR3_SQ3_N(ADC_CHANNEL_SENSOR)
};
 
void initADC(void)
{
	adcStart(&ADCD1, NULL);
	adcSTM32EnableTSVREFE();
	palSetPadMode(PORT(ADC_VSOLAR), PIN(ADC_VSOLAR), PAL_MODE_INPUT_ANALOG);			// Solar panels
	palSetPadMode(PORT(ADC_VBAT), PIN(ADC_VBAT), PAL_MODE_INPUT_ANALOG);		// Battery voltage divider
}

void deinitADC(void)
{
	adcStop(&ADCD1);
}

void doConversion(void)
{
	initADC();
	adcStartConversion(&ADCD1, &adcgrpcfg, samples, 1);
	chThdSleepMilliseconds(35); // Wait until conversion is finished
	deinitADC();
}

uint16_t getBatteryVoltageMV(void)
{
	doConversion();
	uint16_t vbat = samples[0] * VCC_REF * DIVIDER_VBAT / 4096;

	// Get voltage from PAC1720 (PAC1720 returns false redings below 2.35V)
	if(vbat >= 2400)
	{
		uint16_t vbat_pac = pac1720_getBatteryVoltage(); // Get value from PAC1720
		if(vbat_pac) // Apply it if valid
			vbat = vbat_pac;
	}

	return vbat;
}
uint16_t getSolarVoltageMV(void)
{
	doConversion();
	return samples[1] * VCC_REF * DIVIDER_VSOL / 4096;
}
uint16_t getSTM32Temperature(void)
{
	doConversion();
	return samples[2];
}

