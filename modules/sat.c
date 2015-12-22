#include "ch.h"
#include "hal.h"
#include "trace.h"

THD_FUNCTION(moduleSAT, arg) {
	(void)arg;

	TRACE_INFO("startup module satellite");
}
