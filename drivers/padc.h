#ifndef __ADC_H__
#define __ADC_H__

#include "ch.h"
#include "hal.h"

void initADC(void);
void deinitADC(void);
uint16_t getBatteryVoltageMV(void);
uint16_t getSolarVoltageMV(void);
uint16_t getSTM32Temperature(void);

#endif
