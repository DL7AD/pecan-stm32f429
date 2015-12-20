#ifndef __GPS_H__
#define __GPS_H__

typedef struct {
	date_t time;
	float latitude;
	float longitude;
	uint16_t altitude;
	uint8_t satellites;
	uint16_t speed;
	uint16_t course;
	bool active; // has lock
	uint8_t ttff;
} gps_t;

#endif

