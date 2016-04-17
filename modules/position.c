#include "ch.h"
#include "hal.h"

#include "debug.h"
#include "modules.h"
#include "config.h"
#include "radio.h"
#include "aprs.h"
#include "morse.h"
#include "sleep.h"
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
	chsnprintf(buf, sizeof(buf), "%d", trackPoint->id);
	str_replace(fskmsg, size, "<ID>", buf);
	chsnprintf(buf, sizeof(buf), "%04d-%02d-%02d", trackPoint->time.year, trackPoint->time.month, trackPoint->time.day);
	str_replace(fskmsg, size, "<DATE>", buf);
	chsnprintf(buf, sizeof(buf), "%02d:%02d:%02d", trackPoint->time.hour, trackPoint->time.minute, trackPoint->time.second);
	str_replace(fskmsg, size, "<TIME>", buf);
	chsnprintf(buf, sizeof(buf), "%d.%07d", "%s%d.%07d", -10000000<trackPoint->gps_lat && trackPoint->gps_lat<0 ? "-" : "",  trackPoint->gps_lat/10000000, (trackPoint->gps_lat >= 0 ? 1 : -1) * (trackPoint->gps_lat%10000000));
	str_replace(fskmsg, size, "<LAT>", buf);
	chsnprintf(buf, sizeof(buf), "%s%d.%07d", -10000000<trackPoint->gps_lon && trackPoint->gps_lon<0 ? "-" : "",  trackPoint->gps_lon/10000000, (trackPoint->gps_lon >= 0 ? 1 : -1) * (trackPoint->gps_lon%10000000));
	str_replace(fskmsg, size, "<LON>", buf);
	chsnprintf(buf, sizeof(buf), "%d", trackPoint->gps_alt);
	str_replace(fskmsg, size, "<ALT>", buf);
	chsnprintf(buf, sizeof(buf), "%d", trackPoint->gps_sats);
	str_replace(fskmsg, size, "<SATS>", buf);
	chsnprintf(buf, sizeof(buf), "%d", trackPoint->gps_ttff);
	str_replace(fskmsg, size, "<TTFF>", buf);
	chsnprintf(buf, sizeof(buf), "%d.%02d", trackPoint->adc_battery/1000, (trackPoint->adc_battery%1000)/10);
	str_replace(fskmsg, size, "<VBAT>", buf);
	chsnprintf(buf, sizeof(buf), "%d.%02d", trackPoint->adc_solar/1000, (trackPoint->adc_solar%1000)/10);
	str_replace(fskmsg, size, "<VSOL>", buf);
	chsnprintf(buf, sizeof(buf), "%d.%03d", trackPoint->adc_charge/1000, (trackPoint->adc_charge >= 0 ? 1 : -1) * (trackPoint->adc_charge%1000));
	str_replace(fskmsg, size, "<CHARGE>", buf);
	chsnprintf(buf, sizeof(buf), "%d.%03d", trackPoint->adc_discharge/1000, (trackPoint->adc_discharge >= 0 ? 1 : -1) * (trackPoint->adc_discharge%1000));
	str_replace(fskmsg, size, "<DISCHARGE>", buf);
	chsnprintf(buf, sizeof(buf), "%d", trackPoint->int_press/10);
	str_replace(fskmsg, size, "<IPRESS>", buf);
	chsnprintf(buf, sizeof(buf), "%d.%d", trackPoint->int_temp/100, (trackPoint->int_temp%100)/10);
	str_replace(fskmsg, size, "<ITEMP>", buf);
	chsnprintf(buf, sizeof(buf), "%d", trackPoint->int_hum/10);
	str_replace(fskmsg, size, "<IHUM>", buf);
	chsnprintf(buf, sizeof(buf), "%d", trackPoint->ext_press/10);
	str_replace(fskmsg, size, "<EPRESS>", buf);
	chsnprintf(buf, sizeof(buf), "%d.%d", trackPoint->ext_temp/100, (trackPoint->ext_temp%100)/10);
	str_replace(fskmsg, size, "<ETEMP>", buf);
	chsnprintf(buf, sizeof(buf), "%d", trackPoint->ext_hum/10);
	str_replace(fskmsg, size, "<EHUM>", buf);
	positionToMaidenhead(buf, trackPoint->gps_lat/10000000.0, trackPoint->gps_lon/10000000.0);
	str_replace(fskmsg, size, "<LOC>", buf);
}

THD_FUNCTION(modulePOS, arg) {
	// Print infos
	module_conf_t* config = (module_conf_t*)arg;
	TRACE_INFO("POS  > Startup module POSITION");
	// TRACE_MODULE_INFO(parm, "POS", "POSITION"); FIXME

	trackPoint_t *trackPoint = getLastTrackPoint();

	systime_t time = chVTGetSystemTimeX();
	while(true)
	{
		//parm->lastCycle = chVTGetSystemTimeX(); // Watchdog timer TODO
		TRACE_INFO("POS  > Do module POSITION cycle");

		TRACE_INFO("POS  > Get last track point");
		trackPoint = getLastTrackPoint();

		if(!p_sleep(&config->sleep)) {

			TRACE_INFO("POS  > Transmit GPS position");

			radioMSG_t msg;
			msg.freq = getFrequency(&config->frequency);
			msg.power = config->power;

			switch(config->protocol) {

				case PROT_APRS_2GFSK: // Encode APRS
				case PROT_APRS_AFSK:
					msg.mod = config->protocol == PROT_APRS_AFSK ? MOD_AFSK : MOD_2GFSK;
					msg.gfsk_config = &(config->gfsk_config);
					msg.afsk_config = &(config->afsk_config);
					msg.bin_len = aprs_encode_position(msg.msg, msg.mod, &(config->aprs_config), trackPoint);
					while(!transmitOnRadio(&msg)) // Try to insert message into message box aggressively (transmission)
						chThdSleepMilliseconds(10);
					break;

				/*case PROT_APRSCONFIG_2GFSK: // Encode APRS telemetry encoding definition (conversion formulae) FIXME: This must be included in PROT_APRS_2GFSK and PROT_APRS_AFSK
				case PROT_APRSCONFIG_AFSK:
					msg.mod = config->protocol == PROT_APRSCONFIG_AFSK ? MOD_AFSK : MOD_2GFSK;

					telemetry_config_t config[] = {CONFIG_PARM, CONFIG_UNIT, CONFIG_EQNS, CONFIG_BITS};
					for(uint8_t i=0; i<sizeof(config); i++) {
						msg.bin_len = aprs_encode_telemetry_configuration(msg.msg, msg.mod, config[i]); // Encode packet
						while(!transmitOnRadio(&msg)) // Try to insert message into message box aggressively (transmission)
							chThdSleepMilliseconds(10);
						chThdSleepMilliseconds(5000); // Take a litte break between the package transmissions
					}

					break;*/

				case PROT_UKHAS_2FSK: // Encode UKHAS
					msg.mod = MOD_2FSK;
					msg.fsk_config = &(config->fsk_config);

					// Encode packet
					char fskmsg[256];
					memcpy(fskmsg, config->ukhas_config.format, sizeof(config->ukhas_config.format));
					replace_placeholders(fskmsg, sizeof(fskmsg), trackPoint);
					str_replace(fskmsg, sizeof(fskmsg), "<CALL>", config->ukhas_config.callsign);
					msg.bin_len = 8*chsnprintf((char*)msg.msg, sizeof(fskmsg), "$$$$$%s*%04X\n", fskmsg, crc16(fskmsg));

					// Transmit message
					while(!transmitOnRadio(&msg)) // Try to insert message into message box aggressively (transmission)
						chThdSleepMilliseconds(10);
					break;

				case PROT_MORSE: // Encode Morse
					msg.mod = MOD_OOK;
					msg.ook_config = &(config->ook_config);

					// Encode morse message
					char morse[128];
					memcpy(morse, config->morse_config.format, sizeof(config->morse_config.format));
					replace_placeholders(morse, sizeof(morse), trackPoint);
					str_replace(morse, sizeof(morse), "<CALL>", config->morse_config.callsign);

					// Transmit message
					msg.bin_len = morse_encode(msg.msg, morse); // Convert message to binary stream
					while(!transmitOnRadio(&msg)) // Try to insert message into message box aggressively (transmission)
						chThdSleepMilliseconds(10);
					break;

				default:
					TRACE_ERROR("POS  > Unsupported modulation/protocol selected for module POSITION");
			}
		}

		time = waitForTrigger(time, &config->trigger);
	}
}

