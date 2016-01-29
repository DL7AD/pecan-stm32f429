#include "ch.h"
#include "hal.h"

#include "debug.h"
#include "modules.h"

THD_FUNCTION(moduleLOG, arg) {
	// Print infos
	module_params_t* parm = (module_params_t*)arg;
	TRACE_INFO("LOG  > Startup module LOG");
	TRACE_MODULE_INFO(parm, "LOG", "LOG");

	systime_t time = chVTGetSystemTimeX();
	while(true)
	{
		TRACE_INFO("LOG  > Do module LOG cycle");
		TRACE_WARN("LOG  > Module LOG not fully implemented"); // FIXME

		time = chThdSleepUntilWindowed(time, time + S2ST(parm->cycle)); // Wait until time + cycletime
	}
}
