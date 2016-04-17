#include "ch.h"
#include "hal.h"

#include "debug.h"
#include "modules.h"

THD_FUNCTION(moduleLOG, arg) {
	// Print infos
	module_conf_t* config = (module_conf_t*)arg;
	TRACE_INFO("LOG  > Startup module LOG");
	//TRACE_MODULE_INFO(parm, "LOG", "LOG"); FIXME

	systime_t time = chVTGetSystemTimeX();
	while(true)
	{
		TRACE_INFO("LOG  > Do module LOG cycle");
		TRACE_WARN("LOG  > Module LOG not fully implemented"); // FIXME

		if(!p_sleep(&config->sleep)) {
			// TODO: Impelemt Log encoding
		}

		time = waitForTrigger(time, &config->trigger);
	}
}
