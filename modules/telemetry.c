#include "ch.h"
#include "hal.h"

#include "trace.h"
#include "modules.h"

THD_FUNCTION(moduleTEL, arg) {
	// Print infos
	module_params_t* parm = (module_params_t*)arg;
	TRACE_INFO("TEL  > Startup module TELEMETRY");
	TRACE_MODULE_INFO(parm, "TEL", "TELEMETRY");

	systime_t time = chVTGetSystemTimeX();
	while(true)
	{
		TRACE_INFO("TEL  > Do module TELEMETRY cycle");
		TRACE_WARN("TEL  > Module TELEMETRY not implemented"); // FIXME

		time += S2ST(parm->cycle); // Wait until this time
		chThdSleepUntil(time);
	}
}
