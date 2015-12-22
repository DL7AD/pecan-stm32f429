#include "ch.h"
#include "hal.h"
#include "trace.h"

THD_FUNCTION(moduleLOG, arg) {
	(void)arg;

	TRACE_INFO("startup module log");
}
