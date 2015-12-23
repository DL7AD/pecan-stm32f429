#include "ch.h"
#include "hal.h"

#include "trace.h"
#include "modules.h"

THD_FUNCTION(moduleSAT, arg) {
	// Print infos
	module_params_t* parm = (module_params_t*)arg;
	TRACE_INFO("Startup module SATELLITE");
	TRACE_MODULE_INFO(parm, "SATELLITE");

	systime_t time = chVTGetSystemTimeX();
	while(true)
	{
		TRACE_INFO("Do module SATELLITE cycle");
		TRACE_WARN("Module SATELLITE not implemented"); // FIXME

		time += S2ST(parm->cycle); // Wait until this time
		chThdSleepUntil(time);
	}
}
