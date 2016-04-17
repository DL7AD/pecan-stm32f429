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
	chprintf((BaseSequentialStream*)&SD4, "[%8d.%03d][%s] ", chVTGetSystemTimeX()/CH_CFG_ST_FREQUENCY, (chVTGetSystemTimeX()*1000/CH_CFG_ST_FREQUENCY)%1000, type); \
	chprintf((BaseSequentialStream*)&SD4, (format), ##args); \
	chprintf((BaseSequentialStream*)&SD4, "\r\n"); \
	chMtxUnlock(&trace_mtx); \
}

#define TRACE_DEBUG(format, args...) TRACE_BASE(format, "DEBUG", ##args)
#define TRACE_INFO(format, args...)  TRACE_BASE(format, "     ", ##args)
#define TRACE_WARN(format, args...) TRACE_BASE(format, "WARN ", ##args)
#define TRACE_ERROR(format, args...) TRACE_BASE(format, "ERROR", ##args)

#define TRACE_TAB "                            "

#define TRACE_GPSFIX(fix) { \
	TRACE_INFO("GPS  > New GPS Fix\r\n"\
		"%s GPS Time: %04d-%02d-%02d %02d:%02d:%02d\r\n" \
		"%s Sats: %d (used for solution)\r\n" \
		"%s Latitude: %d.%07ddeg\r\n" \
		"%s Longitude: %d.%07ddeg\r\n" \
		"%s Altitude: %d Meter", \
		TRACE_TAB, (fix)->time.year, (fix)->time.month, (fix)->time.day, (fix)->time.hour, (fix)->time.minute, (fix)->time.second, \
		TRACE_TAB, (fix)->num_svs, \
		TRACE_TAB, (fix)->lat/10000000, (fix)->lat%10000000, /* TODO: this calculation does not work in other hemispheres */ \
		TRACE_TAB, (fix)->lon/10000000, (fix)->lon%10000000, /* TODO: this calculation does not work in other hemispheres */ \
		TRACE_TAB, (fix)->alt \
	); \
}

#define TRACE_BIN(data, len) { \
	chMtxLock(&trace_mtx); \
	chprintf((BaseSequentialStream*)&SD4, "[%8d.%03d][DEBUG] ", chVTGetSystemTimeX()/CH_CFG_ST_FREQUENCY, (chVTGetSystemTimeX()*1000/CH_CFG_ST_FREQUENCY)%1000); \
	chprintf((BaseSequentialStream*)&SD4, "     > Binary data (%d bits)\r\n", (len)); \
	for(uint32_t i=0; i<((len)+7)/8; i+=8) \
		chprintf((BaseSequentialStream*)&SD4, "%s 0x%03x ... 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\r\n", \
		TRACE_TAB, i, (data)[i], (data)[i+1], (data)[i+2], (data)[i+3], (data)[i+4], (data)[i+5], (data)[i+6], (data)[i+7]); \
	chMtxUnlock(&trace_mtx); \
}

#define TRACE_BIN_CHAR(data, len) { \
	chMtxLock(&trace_mtx); \
	chprintf((BaseSequentialStream*)&SD4, "[%8d.%03d][DEBUG] ", chVTGetSystemTimeX()/CH_CFG_ST_FREQUENCY, (chVTGetSystemTimeX()*1000/CH_CFG_ST_FREQUENCY)%1000); \
	chprintf((BaseSequentialStream*)&SD4, "     > Binary data (%d bits)\r\n", (len)); \
	for(uint32_t i=0; i<((len)+7)/8; i+=8) \
		chprintf((BaseSequentialStream*)&SD4, "%s %c%c%c%c%c%c%c%c\r\n", \
		TRACE_TAB, i, (data)[i], (data)[i+1], (data)[i+2], (data)[i+3], (data)[i+4], (data)[i+5], (data)[i+6], (data)[i+7]); \
	chMtxUnlock(&trace_mtx); \
}

#define PRINT_TIME(thd) { \
	ptime_t dbgtime; \
	getTime(&dbgtime); \
	TRACE_INFO("%-4s > Current time: %02d-%02d-%02d %02d:%02d:%02d:%03d", thd, dbgtime.year, dbgtime.month, dbgtime.day, dbgtime.hour, dbgtime.minute, dbgtime.second, dbgtime.millisecond); \
}

#endif

