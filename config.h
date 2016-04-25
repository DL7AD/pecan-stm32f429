#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "types.h"
#include "radio.h"
#include "sleep.h"

#define RADIO_TIMEOUT			300				/* Radio transmission timeout in milliseconds (radio switched off after x ms in idling) */
#define TRACK_CYCLE_TIME		120				/* Tracking cycle (all peripheral data [airpressure, GPS, temperature, ...] is collected each x seconds */
#define CAMERA_TYPE				OV9655			/* Either OV9655 or OV2640 */

void initModules(void);

#endif

