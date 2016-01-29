#include "ch.h"
#include "hal.h"
#include "debug.h"
#include "pi2c.h"
#include "pac1720.h"

/* 
 * FSP = FSC * FSV
 * FSV = 40 - 40 / Denominator
 * FSC = FSR / R_sense
 */

#define FSR  80		/* Full-scale-rage voltage in mV */
#define DEMO 2047	/* Denominator see Tab. 4-5 in PAC1720 datasheet */

#define FSV (40 - 40 / (DEMO))
#define FSC ((FSR) / (PAC1720_RSENSE))

static int32_t pac1720_charge;
static int32_t pac1720_counter;

int16_t pac1720_getPowerDischarge(void) {
	int32_t fsp = FSV * FSC;
	return read16(PAC1720_ADDRESS, PAC1720_CH2_PWR_RAT_HIGH) * fsp / 32768;
}

int16_t pac1720_getPowerCharge(void) {
	int32_t fsp = FSV * FSC;
	return read16(PAC1720_ADDRESS, PAC1720_CH1_PWR_RAT_HIGH) * fsp / 32768;
}

int16_t pac1720_getAveragePower(void) {
	// Calculate
	int16_t ret = pac1720_charge / (pac1720_counter == 0 ? 1 : pac1720_counter);

	// Reset current measurement
	pac1720_charge = 0;
	pac1720_counter = 0;

	return ret;
}

bool pac1720_isAvailable(void)
{
	return read8(PAC1720_ADDRESS, PAC1720_PRODUCT_ID) == 0x57;
}

THD_FUNCTION(pac1720_thd, arg)
{
	(void)arg;

	while(true)
	{
		int16_t charge = pac1720_getPowerCharge();
		int16_t discharge = pac1720_getPowerDischarge();
		pac1720_charge += charge - discharge;
		pac1720_counter++;
	}
}

void pac1720_init(void)
{
	TRACE_INFO("PAC  > Init PAC1720");

	/* Write for both channels
	 * Current sensor sampling time	80ms (Denominator 2047)
	 * Current sensing average disabled
	 * Current sensing range +-80mV (FSR)
	 */
	write8(PAC1720_ADDRESS, PAC1720_CH1_VSENSE_SAMP_CONFIG, 0x53);
	write8(PAC1720_ADDRESS, PAC1720_CH2_VSENSE_SAMP_CONFIG, 0x53);

	TRACE_INFO("PAC  > Init PAC1720 continuous measurement");
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(64), NORMALPRIO, pac1720_thd, NULL);
}
