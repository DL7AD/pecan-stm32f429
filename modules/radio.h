#ifndef __RADIO_H__
#define __RADIO_H__

#include "ch.h"
#include "hal.h"
#include "defines.h"
#include "../config.h"
#include "../drivers/si4x6x.h"

extern mailbox_t radioMBP;

#define inRadio1band(freq) (RADIO1_MIN_FREQ <= (freq) && (freq) <= RADIO1_MAX_FREQ)
#define inRadio2band(freq) (RADIO2_MIN_FREQ <= (freq) && (freq) <= RADIO2_MAX_FREQ)

uint32_t getAPRSRegionFrequency(void);
uint32_t getAPRSISSFrequency(void);
uint32_t getCustomFrequency(void);

THD_FUNCTION(moduleRADIO, arg);
void sendAFSK(radio_t radio, radioMSG_t *msg);
bool afsk_handler(radio_t radio, radioMSG_t *msg);
uint8_t dBm2powerLvl(int32_t dBm);

#endif

