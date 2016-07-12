#ifndef __SI4464__H__
#define __SI4464__H__

#include "ch.h"
#include "hal.h"
#include "defines.h"
#include "types.h"

#define RADIO_2M	1	/* Radio 1 => 2m */
#define RADIO_70CM	2	/* Radio 2 => 70cm */

#define RADIO_SDN_SET(radio, state)			(radio == RADIO_2M ? palWritePad(PORT(RADIO1_SDN), PIN(RADIO1_SDN), state) : palWritePad(PORT(RADIO2_SDN), PIN(RADIO2_SDN), state))
#define RADIO_CS_SET(radio, state)			(radio == RADIO_2M ? palWritePad(PORT(RADIO1_CS), PIN(RADIO1_CS), state) : palWritePad(PORT(RADIO2_CS), PIN(RADIO2_CS), state))
#define RF_GPIO0_SET(radio, state)			(radio == RADIO_2M ? palWritePad(PORT(RADIO1_GPIO0), PIN(RADIO1_GPIO0), state) : palWritePad(PORT(RADIO2_GPIO0), PIN(RADIO2_GPIO0), state))
#define RF_GPIO1_SET(radio, state)			(radio == RADIO_2M ? palWritePad(PORT(RADIO1_GPIO1), PIN(RADIO1_GPIO1), state) : palWritePad(PORT(RADIO2_GPIO1), PIN(RADIO2_GPIO1), state))
#define MOD_GPIO_SET(radio, state)			RF_GPIO0_SET(radio, state)
#define RADIO_WITHIN_MAX_PWR(radio, dBm)	(radio == RADIO_2M ? (dBm) <= RADIO1_MAX_PWR : (dBm) <= RADIO2_MAX_PWR)
#define RADIO_WITHIN_FREQ_RANGE(frequ)		((frequ) >= 119000000 && (frequ) <= 1050000000)
#define RADIO_MAX_PWR(radio)				(radio == RADIO_2M ? RADIO1_MAX_PWR : RADIO2_MAX_PWR)

#define inRadio1band(freq) (RADIO1_MIN_FREQ <= (freq) && (freq) <= RADIO1_MAX_FREQ)
#define inRadio2band(freq) (RADIO2_MIN_FREQ <= (freq) && (freq) <= RADIO2_MAX_FREQ)

void Si4464_Init(radio_t radio, mod_t modulation);
void Si4464_write(radio_t radio, uint8_t* txData, uint32_t len);
void setFrequency(radio_t radio, uint32_t freq, uint16_t shift);
void setShift(radio_t radio, uint16_t shift);
void setModemAFSK(radio_t radio);
void setModemOOK(radio_t radio);
void setModem2FSK(radio_t radio);
void setModem2GFSK(radio_t radio);
void setDeviation(radio_t radio, uint32_t deviation);
void setPowerLevel(radio_t radio, int8_t level);
void startTx(radio_t radio, uint16_t size);
void stopTx(radio_t radio);
void radioShutdown(radio_t radio);
bool radioTune(radio_t radio, uint32_t frequency, uint16_t shift, int8_t level, uint16_t size);
void Si4464_writeFIFO(radio_t radio, uint8_t *msg, uint8_t size);
uint8_t Si4464_freeFIFO(radio_t radio);
uint8_t Si4464_getState(radio_t radio);
int8_t Si4464_getTemperature(radio_t radio);
uint8_t dBm2powerLvl(int32_t dBm);
bool isRadioInitialized(radio_t radio);

#endif

