#include "ch.h"
#include "hal.h"
#include "trace.h"

THD_FUNCTION(moduleIMG, arg) {
	(void)arg;

	TRACE_INFO("startup module image");
}