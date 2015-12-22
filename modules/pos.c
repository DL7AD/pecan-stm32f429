#include "ch.h"
#include "hal.h"
#include "trace.h"

#include "modules.h"

uint32_t (*fptr)();

THD_FUNCTION(modulePOS, arg) {
	// Params
	module_params_t* parm = (module_params_t*)arg;

	// Print infos
	fptr = ((module_params_t*)arg)->frequencyMethod;
	TRACE_INFO(	"startup module position\r\n"
				"%s > Cycle: %d sec\r\n"
				"%s > Power: %d dBm\r\n"
				"%s > Frequency: %d.%03d MHz (current)\r\n"
				"%s > Modulation: %s\r\n"
				"%s > Protocol: %s",
				TRACE_TAB, parm->cycle,
				TRACE_TAB, parm->power,
				TRACE_TAB, (*fptr)()/1000000, ((*fptr)()%1000000)/1000,
				TRACE_TAB, VAL2MOULATION(parm->modulation),
				TRACE_TAB, VAL2PROTOCOL(parm->protocol)
	);

	systime_t time = chVTGetSystemTimeX();
	while(true) {
		TRACE_INFO("Do module position cycle");
		TRACE_WARN("module position not fully implemented"); // FIXME

		time += S2ST(parm->cycle); // Wait until this time
		chThdSleepUntil(time);
	}
}

