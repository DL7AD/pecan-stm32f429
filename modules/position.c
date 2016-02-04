#include "ch.h"
#include "hal.h"

#include "debug.h"
#include "modules.h"
#include "radio.h"
#include "aprs.h"
#include "cw.h"
#include "chprintf.h"
#include <string.h>
#include <math.h>

void str_replace(char *string, uint32_t size, char *search, char *replace) {
	for(uint32_t i=0; string[i] != 0; i++) { // Find search string
		uint32_t j=0;
		for(j=0; search[j] != 0; j++)
			if(string[i+j] != search[j])
				break;
		if(search[j] == 0) { // String found, replace it
			string[i] = 0;
			char temp[size-i-j];
			memcpy(temp, &string[i+j], size-i-j);
			chsnprintf(string, size, "%s%s%s", string, replace, temp);
			return;
		}
	}
}

uint16_t crc16(char *string) {
	size_t i;
	uint16_t crc;

	crc = 0xFFFF;

	for(i = 0; i < strlen(string); i++) {
		crc = crc ^ ((uint16_t)string[i] << 8);
		for(uint8_t j=0; j<8; j++)
		{
		    if(crc & 0x8000)
		        crc = (crc << 1) ^ 0x1021;
		    else
		        crc <<= 1;
		}
	}

	return crc;
}

void positionToMaidenhead(char m[], double lat, double lon)
{
	lon = lon + 180;
	lat = lat + 90;

	m[0] = ((uint8_t)'A') + ((uint8_t)(lon / 20));
	m[1] = ((uint8_t)'A') + ((uint8_t)(lat / 10));

	m[2] = ((uint8_t)'0') + ((uint8_t)(fmod(lon, 20)/2));
	m[3] = ((uint8_t)'0') + ((uint8_t)(fmod(lat, 10)/1));

	m[4] = ((uint8_t)'A') + ((uint8_t)((lon - ( ((uint8_t)(lon/2))*2)) / (5.0/60.0)));
	m[5] = ((uint8_t)'A') + ((uint8_t)((lat - ( ((uint8_t)(lat/1))*1)) / (2.5/60.0)));

	m[6] = 0;
}

/**
  * Replaces placeholders with variables
  */
void replace_placeholders(char* fskmsg, uint16_t size, trackPoint_t *trackPoint) {
	char buf[16];

	str_replace(fskmsg, size, "<CALL>", FSK_CALLSIGN);
	chsnprintf(buf, sizeof(buf), "%d", trackPoint->id);
	str_replace(fskmsg, size, "<ID>", buf);
	chsnprintf(buf, sizeof(buf), "%04d-%02d-%02d", trackPoint->time.year, trackPoint->time.month, trackPoint->time.day);
	str_replace(fskmsg, size, "<DATE>", buf);
	chsnprintf(buf, sizeof(buf), "%02d:%02d:%02d", trackPoint->time.hour, trackPoint->time.minute, trackPoint->time.second);
	str_replace(fskmsg, size, "<TIME>", buf);
	chsnprintf(buf, sizeof(buf), "%d.%07d", trackPoint->gps_lat/10000000, trackPoint->gps_lat%10000000);
	str_replace(fskmsg, size, "<LAT>", buf);
	chsnprintf(buf, sizeof(buf), "%d.%07d", trackPoint->gps_lon/10000000, trackPoint->gps_lon%10000000);
	str_replace(fskmsg, size, "<LON>", buf);
	chsnprintf(buf, sizeof(buf), "%d", trackPoint->gps_alt);
	str_replace(fskmsg, size, "<ALT>", buf);
	chsnprintf(buf, sizeof(buf), "%d", trackPoint->gps_sats);
	str_replace(fskmsg, size, "<SATS>", buf);
	chsnprintf(buf, sizeof(buf), "%d", trackPoint->gps_ttff);
	str_replace(fskmsg, size, "<TTFF>", buf);
	chsnprintf(buf, sizeof(buf), "%d", trackPoint->adc_battery);
	str_replace(fskmsg, size, "<VBAT>", buf);
	chsnprintf(buf, sizeof(buf), "%d", trackPoint->adc_solar);
	str_replace(fskmsg, size, "<VSOL>", buf);
	chsnprintf(buf, sizeof(buf), "%d", trackPoint->adc_charge);
	str_replace(fskmsg, size, "<CHARGE>", buf);
	chsnprintf(buf, sizeof(buf), "%d", trackPoint->air_press);
	str_replace(fskmsg, size, "<IPRESS>", buf);
	chsnprintf(buf, sizeof(buf), "%d", trackPoint->air_temp);
	str_replace(fskmsg, size, "<ITEMP>", buf);
	chsnprintf(buf, sizeof(buf), "%d", trackPoint->air_hum);
	str_replace(fskmsg, size, "<IHUM>", buf);
	chsnprintf(buf, sizeof(buf), "%d", trackPoint->bal_press);
	str_replace(fskmsg, size, "<EPRESS>", buf);
	chsnprintf(buf, sizeof(buf), "%d", trackPoint->bal_temp);
	str_replace(fskmsg, size, "<ETEMP>", buf);
	chsnprintf(buf, sizeof(buf), "%d", trackPoint->bal_hum);
	str_replace(fskmsg, size, "<EHUM>", buf);
	positionToMaidenhead(buf, trackPoint->gps_lat/10000000.0, trackPoint->gps_lon/10000000.0);
	str_replace(fskmsg, size, "<LOC>", buf);
}

THD_FUNCTION(modulePOS, arg) {
	// Print infos
	module_params_t* parm = (module_params_t*)arg;
	TRACE_INFO("POS  > Startup module POSITION");
	TRACE_MODULE_INFO(parm, "POS", "POSITION");

	systime_t time = chVTGetSystemTimeX();
	while(true)
	{
		parm->lastCycle = chVTGetSystemTimeX(); // Watchdog timer
		TRACE_INFO("POS  > Do module POSITION cycle");

		TRACE_INFO("POS  > Get last track point");
		trackPoint_t *trackPoint = getLastTrackPoint();

		TRACE_INFO("POS  > Transmit GPS position");

		radioMSG_t msg;
		uint32_t (*fptr)(void);
		fptr = parm->frequencyMethod;
		msg.freq = (*fptr)();
		msg.power = parm->power;

		switch(parm->protocol) {

			case PROT_APRS_AFSK: // Encode APRS
				msg.mod = MOD_AFSK;
				msg.bin_len = aprs_encode_position(msg.msg, trackPoint);
				transmitOnRadio(&msg);
				break;

			case PROT_UKHAS_2FSK: // Encode UKHAS
				msg.mod = MOD_2FSK;

				char fskmsg[256];

				memcpy(fskmsg, FSK_FORMAT, sizeof(FSK_FORMAT));
				replace_placeholders(fskmsg, sizeof(fskmsg), trackPoint);
				msg.bin_len = 8*chsnprintf((char*)msg.msg, sizeof(fskmsg), "$$$$$%s*%04X\n", fskmsg, crc16(fskmsg));
				transmitOnRadio(&msg);
				break;

			case PROT_RAW_CW: // Encode CW
				msg.mod = MOD_CW;

				char cwmsg[256];
				memcpy(cwmsg, CW_FORMAT, sizeof(CW_FORMAT));
				replace_placeholders(cwmsg, sizeof(cwmsg), trackPoint);
				msg.bin_len = CW_encode(msg.msg, cwmsg);
				transmitOnRadio(&msg);
				break;

			default:
				TRACE_ERROR("POS  > Unsupported modulation/protocol selected for module POSITION");
		}

		time = chThdSleepUntilWindowed(time, time + S2ST(parm->cycle)); // Wait until time + cycletime
	}
}

