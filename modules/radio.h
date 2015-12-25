#ifndef __RADIO_H__
#define __RADIO_H__

#include "ch.h"
#include "hal.h"
#include "../config.h"

extern mailbox_t radioMBP;

#define inRadio1band(freq) (RADIO1_MIN_FREQ <= (freq) && (freq) <= RADIO1_MAX_FREQ)
#define inRadio2band(freq) (RADIO2_MIN_FREQ <= (freq) && (freq) <= RADIO2_MAX_FREQ)

uint32_t getAPRSRegionFrequency(void);
uint32_t getAPRSISSFrequency(void);
uint32_t getCustomFrequency(void);

THD_FUNCTION(moduleRADIO, arg);

#endif
