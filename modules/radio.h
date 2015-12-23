#ifndef __RADIO_H__
#define __RADIO_H__

#include "ch.h"
#include "hal.h"

extern mailbox_t radioMBP;

uint32_t getAPRSRegionFrequency(void);
uint32_t getAPRSISSFrequency(void);
uint32_t getCustomFrequency(void);

THD_FUNCTION(moduleRADIO, arg);

#endif
