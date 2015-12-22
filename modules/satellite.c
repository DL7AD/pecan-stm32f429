#include "ch.h"
#include "hal.h"

#include "trace.h"
#include "modules.h"

THD_FUNCTION(moduleSAT, arg) {
	// Print infos
	module_params_t* parm = (module_params_t*)arg;
	TRACE_INFO("startup module satellite");
	TRACE_MODULE_INFO(parm, "satellite");

	systime_t time = chVTGetSystemTimeX();
	while(true)
	{
		TRACE_INFO("Do module satellite cycle");
		TRACE_WARN("module satellite not fully implemented"); // FIXME

		time += S2ST(parm->cycle); // Wait until this time
		chThdSleepUntil(time);
	}
}
