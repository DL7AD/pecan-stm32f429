#include "time.h"

const uint16_t nonLeapYear[] = {0,31,59,90,120,151,181,212,243,273,304,334,365};
const uint16_t leapYear[] = {0,31,60,91,121,152,182,213,244,274,305,335,366};

/**
 * Calculates UNIX timestamp and writes it to internal interrupt controlled RTC.
 * Calculation valid until 2100 due to missing leapyear in 2100.
 * @param time Date to be converted
 */
uint64_t date2UnixTimestamp(date_t time) {
	uint64_t timeC = 0;
	timeC  = time.second;
	timeC += time.minute * 60;
	timeC += time.hour * 3600;
	timeC += (time.day-1) * 86400;

	if(time.year % 4 == 0) { // is leapyear?
		timeC += leapYear[time.month-1] * 86400;
	} else {
		timeC += nonLeapYear[time.month-1] * 86400;
	}

	uint16_t i;
	for(i=1970; i<time.year; i++) {
		if(i % 4 == 0) { // is leapyear?
			timeC += 31622400;
		} else {
			timeC += 31536000;
		}
	}

	return timeC * 1000;
}

date_t unixTimestamp2Date(uint64_t time) {
	date_t date;
	uint64_t dateRaw = time / 1000;

	date.year = 1970;
	while(true)
	{
		uint32_t secondsInThisYear = date.year % 4 ? 31536000 : 31622400;
		if(dateRaw >= secondsInThisYear) {
			dateRaw -= secondsInThisYear;
			date.year++;
		} else {
			break;
		}
	}

	for(date.month=1; (date.year%4 ? nonLeapYear[date.month] : leapYear[date.month])*86400<=dateRaw; date.month++);
	dateRaw -= (date.year%4 ? nonLeapYear[date.month-1] : leapYear[date.month-1])*86400;

	date.day    = (dateRaw / 86400) + 1;
	date.hour   = (dateRaw % 86400) / 3600;
	date.minute = (dateRaw % 3600) / 60;
	date.second = dateRaw % 60;

	return date;
}

uint64_t getTime(void) {
	return 0; // TODO: implement RTC
}

