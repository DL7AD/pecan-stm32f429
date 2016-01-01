#include "ch.h"
#include "hal.h"

#include "trace.h"
#include "modules.h"

char *SMODE_STRING[] = {
	"ACTIVE", "SLEEP"
};
char *MOULATION_STRING[] = {
	"CW", "2FSK", "AFSK"
};
char *PROTOCOL_STRING[] = {
	"CW", "SSDV", "APRS", "UKHAS"
};

module_params_t *modules[16];
uint8_t moduleCount;
