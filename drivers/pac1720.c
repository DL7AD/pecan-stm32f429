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
static int32_t pac1720_discharge;
static int32_t pac1720_charge_counter;
static int32_t pac1720_discharge_counter;

int16_t pac1720_getPowerDischarge(void) {
	int32_t fsp = FSV * FSC;
	uint16_t val;
	if(I2C_read16(PAC1720_ADDRESS, PAC1720_CH2_PWR_RAT_HIGH, &val))
		return val * fsp / 65536;
	else
		return 0; // PAC1720 not available (maybe Vcc too low)
}

int16_t pac1720_getPowerCharge(void) {
	int32_t fsp = FSV * FSC;
	uint16_t val;
	if(I2C_read16(PAC1720_ADDRESS, PAC1720_CH1_PWR_RAT_HIGH, &val))
		return val * fsp / 65536;
	else
		return 0; // PAC1720 not available (maybe Vcc too low)
}

int16_t pac1720_getAverageChargePower(void) {
	// Return current value if time interval too short
	if(!pac1720_charge_counter)
		pac1720_getPowerCharge();

	// Calculate average power
	int16_t ret = pac1720_charge / pac1720_charge_counter;

	// Reset current measurement
	pac1720_charge = 0;
	pac1720_charge_counter = 0;

	return ret;
}

int16_t pac1720_getAverageDischargePower(void) {
	// Return current value if time interval too short
	if(!pac1720_discharge_counter)
		pac1720_getPowerDischarge();

	// Calculate average power
	int16_t ret = pac1720_discharge / pac1720_discharge_counter;

	// Reset current measurement
	pac1720_discharge = 0;
	pac1720_discharge_counter = 0;

	return ret;
}

uint16_t pac1720_getBatteryVoltage(void) {
	uint16_t val;
	if(!I2C_read16(PAC1720_ADDRESS, PAC1720_CH2_VSOURCE_HIGH, &val))
		return 0; // PAC1720 not available (maybe Vcc too low)

	return (val >> 5) * 20000 / 0x400;
}

bool pac1720_isAvailable(void)
{
	uint8_t val;
	if(I2C_read8(PAC1720_ADDRESS, PAC1720_PRODUCT_ID, &val))
		return val == 0x57;
	else
		return false; // PAC1720 not available (maybe Vcc too low)
}

THD_FUNCTION(pac1720_thd, arg)
{
	(void)arg;

	while(true)
	{
		pac1720_charge += pac1720_getPowerCharge();
		pac1720_discharge += pac1720_getPowerDischarge();
		pac1720_charge_counter++;
		pac1720_discharge_counter++;

		chThdSleepMilliseconds(100);
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
	I2C_write8(PAC1720_ADDRESS, PAC1720_CH1_VSENSE_SAMP_CONFIG, 0x53);
	I2C_write8(PAC1720_ADDRESS, PAC1720_CH2_VSENSE_SAMP_CONFIG, 0x53);
	I2C_write8(PAC1720_ADDRESS, PAC1720_V_SOURCE_SAMP_CONFIG,   0xFF);

	TRACE_INFO("PAC  > Init PAC1720 continuous measurement");
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(256), "PAC1720", NORMALPRIO, pac1720_thd, NULL);
}
