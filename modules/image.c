#include "ch.h"
#include "hal.h"

#include "trace.h"
#include "modules.h"

THD_FUNCTION(moduleIMG, arg) {
	// Print infos
	module_params_t* parm = (module_params_t*)arg;
	TRACE_INFO("startup module image");
	TRACE_MODULE_INFO(parm, "image");

	systime_t time = chVTGetSystemTimeX();
	while(true)
	{
		TRACE_INFO("Do module image cycle");
		TRACE_WARN("module image not fully implemented"); // FIXME

		time += S2ST(parm->cycle); // Wait until this time
		chThdSleepUntil(time);
	}
}
