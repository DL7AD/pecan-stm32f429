#include "ch.h"
#include "hal.h"
#include "defines.h"
#include "config.h"
#include "padc.h"
#include "pac1720.h"

#define ADC_GRP1_NUM_CHANNELS	3	// Amount of channels (solar, battery, temperature)

static adcsample_t samples[ADC_GRP1_NUM_CHANNELS]; // ADC sample buffer

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
	NULL,
	NULL,
	/* HW dependent part.*/
	0,
	ADC_CR2_SWSTART,
	ADC_SMPR1_SMP_AN11(ADC_SAMPLE_144) | ADC_SMPR1_SMP_SENSOR(ADC_SAMPLE_144) | ADC_SMPR1_SMP_VBAT(ADC_SAMPLE_144),
	0,
	ADC_SQR1_NUM_CH(ADC_GRP1_NUM_CHANNELS),
	0,
	ADC_SQR2_SQ12_N(ADC_CHANNEL_IN14) | ADC_SQR2_SQ12_N(ADC_CHANNEL_IN15) | ADC_SQR3_SQ1_N(ADC_CHANNEL_SENSOR)
};


smode_t SLEEP_WHEN_BATT_BELOW_2V9(void) { return getBatteryVoltageMV() < 2900 ? MOD_SLEEP : MOD_ACTIVE; }
smode_t SLEEP_WHEN_BATT_BELOW_3V0(void) { return getBatteryVoltageMV() < 3000 ? MOD_SLEEP : MOD_ACTIVE; }
smode_t SLEEP_WHEN_BATT_BELOW_3V1(void) { return getBatteryVoltageMV() < 3100 ? MOD_SLEEP : MOD_ACTIVE; }
smode_t SLEEP_WHEN_BATT_BELOW_3V2(void) { return getBatteryVoltageMV() < 3200 ? MOD_SLEEP : MOD_ACTIVE; }
smode_t SLEEP_WHEN_BATT_BELOW_3V3(void) { return getBatteryVoltageMV() < 3300 ? MOD_SLEEP : MOD_ACTIVE; }
smode_t SLEEP_WHEN_BATT_BELOW_3V4(void) { return getBatteryVoltageMV() < 3400 ? MOD_SLEEP : MOD_ACTIVE; }
smode_t SLEEP_WHEN_BATT_BELOW_3V5(void) { return getBatteryVoltageMV() < 3500 ? MOD_SLEEP : MOD_ACTIVE; }
smode_t SLEEP_WHEN_BATT_BELOW_3V6(void) { return getBatteryVoltageMV() < 3600 ? MOD_SLEEP : MOD_ACTIVE; }
smode_t SLEEP_WHEN_BATT_BELOW_3V7(void) { return getBatteryVoltageMV() < 3700 ? MOD_SLEEP : MOD_ACTIVE; }
smode_t SLEEP_WHEN_BATT_BELOW_3V8(void) { return getBatteryVoltageMV() < 3800 ? MOD_SLEEP : MOD_ACTIVE; }
smode_t SLEEP_WHEN_BATT_BELOW_3V9(void) { return getBatteryVoltageMV() < 3900 ? MOD_SLEEP : MOD_ACTIVE; }
smode_t SLEEP_WHEN_BATT_BELOW_4V0(void) { return getBatteryVoltageMV() < 4000 ? MOD_SLEEP : MOD_ACTIVE; }
smode_t SLEEP_WHEN_BATT_BELOW_4V1(void) { return getBatteryVoltageMV() < 4100 ? MOD_SLEEP : MOD_ACTIVE; }
 
void initADC(void)
{
	adcStart(&ADCD1, NULL);
	adcSTM32EnableTSVREFE();
	palSetPadMode(PORT(ADC_VSOLAR), PIN(ADC_VSOLAR), PAL_MODE_INPUT_ANALOG);			// Solar panels
	palSetPadMode(PORT(ADC_VBAT_DIFF), PIN(ADC_VBAT_DIFF), PAL_MODE_INPUT_ANALOG);		// Battery voltage divider
}

void doConversion(void)
{
	chSysLockFromISR();
	adcStartConversionI(&ADCD1, &adcgrpcfg, samples, 1);
	chSysUnlockFromISR();

	while(ADCD1.state != ADC_COMPLETE) // Wait for conversion to be completed
		chThdSleepMilliseconds(1);
}

uint16_t getBatteryVoltageMV(void)
{
	return pac1720_getBatteryVoltage(); // Get value from PAC1720
}
uint16_t getSolarVoltageMV(void)
{
	doConversion();
	return samples[1];
}
uint16_t getSTM32Temperature(void)
{
	doConversion();
	return samples[2];
}










