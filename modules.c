#include "ch.h"
#include "hal.h"

#include "debug.h"
#include "modules.h"

char *SMODE_STRING[] = {
	"ACTIVE", "SLEEP"
};
char *PROTOCOL_STRING[] = {
	"UKHAS 2FSK", "UKHAS DominoEX16", "APRS",
	"SSDV 2FSK", "SSDV on APRS", "CW"
};
char *MOULATION_STRING[] = {
	"CW", "2FSK", "DOMINOEX16", "AFSK"
};

module_params_t *modules[16];
uint8_t moduleCount;
