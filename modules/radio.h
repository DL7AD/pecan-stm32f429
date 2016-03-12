#ifndef __RADIO_H__
#define __RADIO_H__

#include "ch.h"
#include "hal.h"
#include "config.h"
#include "si4464.h"

#define RADIO_2M	1	/* Radio 1 => 2m */
#define RADIO_70CM	2	/* Radio 2 => 70cm */

#define APRS_REGION_FREQ			getAPRSRegionFrequency
#define APRS_ISS_FREQ				getAPRSISSFrequency
#define CUSTOM_FREQ					getCustomFrequency

#define APRS_FREQ_OTHER		144800000
#define APRS_FREQ_AMERICA	144390000
#define APRS_FREQ_CHINA		144640000

typedef struct { // Radio message type
	uint8_t msg[512];	// Message (data)
	uint32_t bin_len;	// Binary length
	uint32_t freq;		// Frequency
	uint8_t power;		// Power
	mod_t mod;			// Modulation
} radioMSG_t;

extern mutex_t radio_image_mtx;

uint32_t getAPRSRegionFrequency(void);
uint32_t getAPRSISSFrequency(void);
uint32_t getCustomFrequency(void);
bool transmitOnRadio(radioMSG_t *msg);

THD_FUNCTION(moduleRADIO, arg);

#endif

