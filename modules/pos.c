#include "ch.h"
#include "hal.h"
#include "trace.h"

#include "modules.h"

uint32_t (*fptr)();

THD_FUNCTION(modulePOS, arg) {

	// Print infos (atomic)
	TRACE_INFO("startup module position");
	TRACE_INFO("> Cycle: %d", ((module_params_t*)arg)->cycle);
	fptr = ((module_params_t*)arg)->frequencyMethod;
	TRACE_INFO("> Power: %d", ((module_params_t*)arg)->power);
	TRACE_INFO("> Frequency: %d", (*fptr)() );
	TRACE_INFO("> Modulation: %s", VAL2MOULATION(((module_params_t*)arg)->modulation));
	TRACE_INFO("> Protocol: %s", VAL2PROTOCOL(((module_params_t*)arg)->protocol));

	TRACE_WARN("module position not implemented"); // FIXME
}

