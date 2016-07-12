#include "ch.h"
#include "hal.h"

#include "debug.h"
#include "modules.h"

THD_FUNCTION(moduleLOG, arg) {
	module_conf_t* config = (module_conf_t*)arg;

	// Execute Initial delay
	if(config->init_delay)
		chThdSleepMilliseconds(config->init_delay);

	// Print initialization message
	TRACE_INFO("LOG  > Startup module %s", config->name);

	systime_t time = chVTGetSystemTimeX();
	while(true)
	{
		TRACE_INFO("LOG  > Do module LOG cycle");
		config->last_update = chVTGetSystemTimeX(); // Update Watchdog timer

		TRACE_WARN("LOG  > Module LOG not implemented"); // FIXME

		if(!p_sleep(&config->sleep_config))
		{
			// TODO: Impelemt Log encoding
		}

		time = waitForTrigger(time, &config->trigger);
	}
}

