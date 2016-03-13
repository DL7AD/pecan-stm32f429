#include "ch.h"
#include "hal.h"
#include "defines.h"
#include "config.h"
#include "padc.h"
#include "pac1720.h"
#include "debug.h"

#define ADC_GRP1_NUM_CHANNELS	3	// Amount of channels (solar, battery, temperature)

static adcsample_t samples[ADC_GRP1_NUM_CHANNELS*2]; // ADC sample buffer

void adccb(ADCDriver *adcp, adcsample_t *buffer, size_t n) {
	(void)adcp;
	(void)buffer;
	(void)n;
}

/*
 * ADC conversion group.
 * Mode:        Linear buffer, 4 samples of 3 channels, SW triggered.
 * Channels:    Solar                    ADC12_IN14
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
	ADC_SQR2_SQ12_N(ADC_CHANNEL_IN14) | ADC_SQR2_SQ12_N(ADC_CHANNEL_IN15) | ADC_SQR3_SQ1_N(ADC_CHANNEL_SENSOR)
};
 
void initADC(void)
{
	adcStart(&ADCD1, NULL);
	adcSTM32EnableTSVREFE();
	palSetPadMode(PORT(ADC_VSOLAR), PIN(ADC_VSOLAR), PAL_MODE_INPUT_ANALOG);			// Solar panels
	palSetPadMode(PORT(ADC_VBAT_DIFF), PIN(ADC_VBAT_DIFF), PAL_MODE_INPUT_ANALOG);		// Battery voltage divider
}

void doConversion(void)
{
	TRACE_DEBUG("B");
	chThdSleepMilliseconds(100);
	chSysLockFromISR();
	adcStartConversionI(&ADCD1, &adcgrpcfg, samples, 2);
	chSysUnlockFromISR();
	TRACE_DEBUG("C");
	chThdSleepMilliseconds(100);
	while(ADCD1.state != ADC_COMPLETE) // Wait for conversion to be completed
		chThdSleepMilliseconds(1);
	TRACE_DEBUG("D");
	chThdSleepMilliseconds(100);
}

uint16_t getBatteryVoltageMV(void)
{
	return pac1720_getBatteryVoltage(); // Get value from PAC1720
}
uint16_t getSolarVoltageMV(void)
{
	TRACE_DEBUG("A");
	chThdSleepMilliseconds(100);
	doConversion();
	TRACE_DEBUG("E");
	chThdSleepMilliseconds(100);
	return samples[1];
}
uint16_t getSTM32Temperature(void)
{
	doConversion();
	return samples[2];
}









