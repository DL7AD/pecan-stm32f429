#include "ch.h"
#include "hal.h"
#include "trace.h"

THD_FUNCTION(modulePOS, arg) {
	(void)arg;

	TRACE_INFO("startup module position");
}
