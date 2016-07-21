#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "types.h"
#include "radio.h"
#include "sleep.h"

extern module_conf_t config[8];

#define RADIO_TIMEOUT			300				/* Radio transmission timeout in milliseconds (radio switched off after x ms in idling) */
#define TRACK_CYCLE_TIME		60				/* Tracking cycle (all peripheral data [airpressure, GPS, temperature, ...] is collected each x seconds */

#define MIN_GPS_VBAT			3000			/* Battery voltage threshold for GPS usage, if below GPS will be switched off, 0 will disable feature */
#define MIN_LED_VBAT			4600			/* Battery voltage threshold for LED usage, if below all debug LEDs will be switched off, 0 will disable feature */

void initModules(void);

#endif

