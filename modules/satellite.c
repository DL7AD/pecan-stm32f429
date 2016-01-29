#include "ch.h"
#include "hal.h"

#include "debug.h"
#include "modules.h"

THD_FUNCTION(moduleSAT, arg) {
	// Print infos
	module_params_t* parm = (module_params_t*)arg;
	TRACE_INFO("SAT  > Startup module SATELLITE");
	TRACE_MODULE_INFO(parm, "SAT", "SATELLITE");

	systime_t time = chVTGetSystemTimeX();
	while(true)
	{
		TRACE_INFO("SAT  > Do module SATELLITE cycle");
		TRACE_WARN("SAT  > Module SATELLITE not implemented"); // FIXME

		time += S2ST(parm->cycle); // Wait until this time
		chThdSleepUntil(time);
	}
}
