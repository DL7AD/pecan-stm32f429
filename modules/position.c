#include "ch.h"
#include "hal.h"
#include "trace.h"

#include "modules.h"

THD_FUNCTION(modulePOS, arg) {
	// Print infos
	module_params_t* parm = (module_params_t*)arg;
	TRACE_MODULE_INFO(parm, "position");

	systime_t time = chVTGetSystemTimeX();
	while(true)
	{
		TRACE_INFO("Do module position cycle");
		TRACE_WARN("module position not fully implemented"); // FIXME

		time += S2ST(parm->cycle); // Wait until this time
		chThdSleepUntil(time);
	}
}

