#ifndef __RADIO_H__
#define __RADIO_H__

#include "ch.h"
#include "hal.h"

uint32_t getAPRSRegionFrequency(void);
uint32_t getAPRSISSFrequency(void);
uint32_t getCustomFrequency(void);

#endif
