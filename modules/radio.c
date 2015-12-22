#include "ch.h"
#include "hal.h"
#include "trace.h"

uint32_t getAPRSRegionFrequency(void) {
	return 144800000; // TODO: Implement Geofencing
}
uint32_t getAPRSISSFrequency(void) {
	return 145825000;
}
uint32_t getCustomFrequency(void) {
	return 434500000;
}

THD_FUNCTION(moduleRADIO, arg) {
	(void)arg;

	TRACE_INFO("startup module radio");
}
