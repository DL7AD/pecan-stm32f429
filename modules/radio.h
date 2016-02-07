#ifndef __RADIO_H__
#define __RADIO_H__

#include "ch.h"
#include "hal.h"
#include "config.h"
#include "si4x6x.h"

typedef struct { // Radio message type
	uint8_t msg[256];	// Message (Largest type: SSDV packet => 256byte)
	uint32_t bin_len;	// Binary length
	uint32_t freq;		// Frequency
	uint8_t power;		// Power
	mod_t mod;			// Modulation
} radioMSG_t;

uint32_t getAPRSRegionFrequency(void);
uint32_t getAPRSISSFrequency(void);
uint32_t getCustomFrequency(void);

void transmitOnRadio(radioMSG_t *msg);

THD_FUNCTION(moduleRADIO, arg);

#endif

