#include "ch.h"
#include "hal.h"

#include "trace.h"
#include "modules.h"

THD_FUNCTION(moduleIMG, arg) {
	// Print infos
	module_params_t* parm = (module_params_t*)arg;
	TRACE_INFO("Startup module IMAGE");
	TRACE_MODULE_INFO(parm, "IMAGE");

	systime_t time = chVTGetSystemTimeX();
	while(true)
	{
		TRACE_INFO("Do module IMAGE cycle");
		TRACE_WARN("Module IMAGE not implemented"); // FIXME

		time += S2ST(parm->cycle); // Wait until this time
		chThdSleepUntil(time);
	}
}
