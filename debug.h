#ifndef __TRACE_H__
#define __TRACE_H__

#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "ptime.h"

extern mutex_t trace_mtx;
extern const SerialConfig uart_config;

// Initializer for serial debug and LEDs
#define DEBUG_INIT() { \
	palSetPadMode(PORT(LED_GREEN), PIN(LED_GREEN), PAL_MODE_OUTPUT_PUSHPULL); \
	palSetPadMode(PORT(LED_YELLOW), PIN(LED_YELLOW), PAL_MODE_OUTPUT_PUSHPULL); \
	palSetPadMode(PORT(LED_RED), PIN(LED_RED), PAL_MODE_OUTPUT_PUSHPULL); \
	\
	sdStart(&SD4, &uart_config); \
	palSetPadMode(GPIOA, 0, PAL_MODE_ALTERNATE(8)); \
	palSetPadMode(GPIOA, 1, PAL_MODE_ALTERNATE(8)); \
	chMtxObjectInit(&trace_mtx); \
	chMtxLock(&trace_mtx); \
	chprintf((BaseSequentialStream*)&SD4, "\r\n"); \
	chMtxUnlock(&trace_mtx); \
}

#define TRACE_BASE(format, type, args...) { \
	chMtxLock(&trace_mtx); \
	chprintf((BaseSequentialStream*)&SD4, "[%8d.%04d][%s] ", chVTGetSystemTimeX()/CH_CFG_ST_FREQUENCY, chVTGetSystemTimeX()%CH_CFG_ST_FREQUENCY, type); \
	chprintf((BaseSequentialStream*)&SD4, (format), ##args); \
	chprintf((BaseSequentialStream*)&SD4, "\r\n"); \
	chMtxUnlock(&trace_mtx); \
}

#define TRACE_DEBUG(format, args...) TRACE_BASE(format, "DEBUG", ##args)
#define TRACE_INFO(format, args...)  TRACE_BASE(format, "     ", ##args)
#define TRACE_WARN(format, args...) TRACE_BASE(format, "WARN ", ##args)
#define TRACE_ERROR(format, args...) TRACE_BASE(format, "ERROR", ##args)

#define TRACE_TAB "                             "

#define TRACE_MODULE_INFO(parm, thd, name) { \
	uint32_t (*fptr)(void); \
	fptr = (parm)->frequencyMethod; \
	TRACE_INFO(	"%-4s > Module %s info\r\n" \
		"%s Cycle: %d sec\r\n" \
		"%s Power: %d dBm\r\n" \
		"%s Frequency: %d.%03d MHz (current)\r\n" \
		"%s Protocol: %s", \
		thd, name, \
		TRACE_TAB, (parm)->cycle, \
		TRACE_TAB, (parm)->power, \
		TRACE_TAB, (*fptr)()/1000000, ((*fptr)()%1000000)/1000, \
		TRACE_TAB, VAL2PROTOCOL((parm)->protocol) \
	); \
}

#define TRACE_GPSFIX(fix) { \
	TRACE_INFO(	"GPS  > New GPS Fix\r\n"\
		"%s GPS Time: %04d-%02d-%02d %02d:%02d:%02d\r\n" \
		"%s Sats: %d (used for solution)\r\n" \
		"%s Latitude: %d.%07ddeg\r\n" \
		"%s Longitude: %d.%07ddeg\r\n" \
		"%s Altitude: %d Meter" \
		TRACE_TAB, (fix)->time.year, (fix)->time.month, (fix)->time.day, (fix)->time.hour, (fix)->time.minute, (fix)->time.second, \
		TRACE_TAB, (fix)->num_svs, \
		TRACE_TAB, (fix)->lat/10000000, (fix)->lat%10000000, \
		TRACE_TAB, (fix)->lon/10000000, (fix)->lon%10000000, \
		TRACE_TAB, (fix)->alt \
	); \
}

#define TRACE_BIN(data, len) { \
	chMtxLock(&trace_mtx); \
	chprintf((BaseSequentialStream*)&SD4, "[%8d.%04d][     ] ", chVTGetSystemTimeX()/CH_CFG_ST_FREQUENCY, chVTGetSystemTimeX()%CH_CFG_ST_FREQUENCY); \
	chprintf((BaseSequentialStream*)&SD4, "RAD  > Transmit binary data (%d bits)\r\n", len); \
	for(uint32_t i=0; i<(len+7)/8; i+=8) \
		chprintf((BaseSequentialStream*)&SD4, "%s 0x%03x ... 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\r\n", \
		TRACE_TAB, i, data[i], data[i+1], data[i+2], data[i+3], data[i+4], data[i+5], data[i+6], data[i+7]); \
	chMtxUnlock(&trace_mtx); \
}

#define PRINT_TIME(thd) { \
	ptime_t time = getTime(); \
	TRACE_INFO("%-4s > Current time: %02d-%02d-%02d %02d:%02d:%02d:%03d", thd, time.year, time.month, time.day, time.hour, time.minute, time.second, time.millisecond); \
}

#endif

