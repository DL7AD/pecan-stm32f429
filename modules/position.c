#include "ch.h"
#include "hal.h"

#include "trace.h"
#include "modules.h"

THD_FUNCTION(modulePOS, arg) {
	// Print infos
	module_params_t* parm = (module_params_t*)arg;
	TRACE_INFO("Startup module position");
	TRACE_MODULE_INFO(parm, "POSITION");

	systime_t time = chVTGetSystemTimeX();
	while(true)
	{
		TRACE_INFO("Do module position cycle");
		TRACE_WARN("Module position not fully implemented"); // FIXME

		TRACE_INFO("Get GPS position");
		getLastGPSPosition();

		time += S2ST(parm->cycle); // Wait until this time
		chThdSleepUntil(time);
	}
}

