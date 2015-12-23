#ifndef __TIME_H__
#define __TIME_H__

#include "ch.h"
#include "hal.h"

#define PRINT_TIME() { \
	ptime_t time = getTime(); \
	TRACE_INFO("Current time: %02d-%02d-%02d %02d:%02d:%02d:%03d", time.year, time.month, time.day, time.hour, time.minute, time.second, time.millisecond); \
}

typedef struct {
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	uint16_t millisecond;
} ptime_t;

uint64_t date2UnixTimestamp(ptime_t time);
ptime_t unixTimestamp2Date(uint64_t time);
ptime_t getTime(void);
void setTime(ptime_t date);

#endif
