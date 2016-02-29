#include "ch.h"
#include "hal.h"

#include "debug.h"
#include "modules.h"

char *SMODE_STRING[] = {
	"ACTIVE", "SLEEP"
};
char *PROTOCOL_STRING[] = {
	"UKHAS 2FSK", "UKHAS DominoEX16", "APRS AFSK 1200", "APRS 2GFSK 9600",
	"APRS TELEMETRY CONFIG AFSK 1200", "APRS TELEMETRY CONFIG 2GFSK 9600",
	"SSDV 2FSK", "SSDV on APRS", "CW"
};
char *MOULATION_STRING[] = {
	"CW", "2FSK", "2GFSK", "DOMINOEX16", "AFSK"
};

module_params_t *modules[16];
uint8_t moduleCount;
