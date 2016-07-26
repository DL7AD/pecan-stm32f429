#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "types.h"
#include "radio.h"
#include "sleep.h"

extern module_conf_t config[8];

#define TRACK_CYCLE_TIME		60				/* Tracking cycle (all peripheral data [airpressure, GPS, temperature, ...] is collected each x seconds */
#define ERRORLOG_SIZE			25				/* Amount of error messages being sent in one error log packet */

#define MIN_GPS_VBAT			2800			/* Battery voltage threshold for GPS usage, if below GPS will be switched off, 0 will disable feature */
#define MIN_LED_VBAT			4500			/* Battery voltage threshold for LED usage, if below all debug LEDs will be switched off, 0 will disable feature */

#define TRACE_TIME				TRUE			/* Enables time tracing on serial connection */
#define TRACE_FILE				TRUE			/* Enables file and line tracing on serial connection */

void initModules(void);

#endif

