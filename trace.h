#ifndef __TRACE_H__
#define __TRACE_H__

#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include <math.h>

extern mutex_t trace_mtx;

#define TRACE_INIT() { \
	sdStart(&SD1, &sc1_config); \
	palSetPadMode(GPIOA, 9,  PAL_MODE_ALTERNATE(7)); /* Must be changed to PA0 and PA1 when Pecan Pico 7 is used instead of discovery board */ \
	palSetPadMode(GPIOA, 10, PAL_MODE_ALTERNATE(7)); \
	chMtxObjectInit(&trace_mtx); \
}

#define TRACE_BASE(format, type, args...) { \
	chMtxLock(&trace_mtx); \
	chprintf((BaseSequentialStream*)&SD1, "[%8d.%04d][%c] ", chVTGetSystemTimeX()/CH_CFG_ST_FREQUENCY, chVTGetSystemTimeX()%CH_CFG_ST_FREQUENCY, type); \
	chprintf((BaseSequentialStream*)&SD1, (format), ##args); \
	chprintf((BaseSequentialStream*)&SD1, "\r\n"); \
	chMtxUnlock(&trace_mtx); \
}

#define TRACE_DEBUG(format, args...) TRACE_BASE(format, 'D', ##args)
#define TRACE_INFO(format, args...)  TRACE_BASE(format, 'I', ##args)
#define TRACE_WARN(format, args...) TRACE_BASE(format, 'W', ##args)
#define TRACE_ERROR(format, args...) TRACE_BASE(format, 'E', ##args)

#define TRACE_TAB "                  "

#define TRACE_MODULE_INFO(parm, name) { \
	uint32_t (*fptr)(void); \
	fptr = (parm)->frequencyMethod; \
	TRACE_INFO(	"module %s info\r\n" \
		"%s > Cycle: %d sec\r\n" \
		"%s > Power: %d dBm\r\n" \
		"%s > Frequency: %d.%03d MHz (current)\r\n" \
		"%s > Modulation: %s\r\n" \
		"%s > Protocol: %s", \
		name, \
		TRACE_TAB, (parm)->cycle, \
		TRACE_TAB, (parm)->power, \
		TRACE_TAB, (*fptr)()/1000000, ((*fptr)()%1000000)/1000, \
		TRACE_TAB, VAL2MOULATION((parm)->modulation), \
		TRACE_TAB, VAL2PROTOCOL((parm)->protocol) \
	); \
}

#endif

