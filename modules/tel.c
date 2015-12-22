#include "ch.h"
#include "hal.h"
#include "trace.h"

THD_FUNCTION(moduleTEL, arg) {
	(void)arg;

	TRACE_INFO("startup module telemetry");
}
