#include "ch.h"
#include "hal.h"

#include "trace.h"
#include "modules.h"
#include "radio.h"

THD_FUNCTION(modulePOS, arg) {
	// Print infos
	module_params_t* parm = (module_params_t*)arg;
	TRACE_INFO("Startup module POSITION");
	TRACE_MODULE_INFO(parm, "POSITION");

	systime_t time = chVTGetSystemTimeX();
	while(true)
	{
		TRACE_INFO("Do module POSITION cycle");
		TRACE_WARN("Module POSITION not implemented"); // FIXME

		TRACE_INFO("Get GPS position");
		getLastGPSPosition(S2ST(parm->cycle-1)); // Timeout max. cycle time - 1sec

		TRACE_INFO("Transmit GPS position");

		radioMSG_t msg;
		uint32_t (*fptr)(void);
		fptr = parm->frequencyMethod;

		switch(parm->protocol) {

			case PROT_APRS:
				// TODO: Implement protocol
				msg.msg[0] = 'B';
				msg.msg[1] = 'L';
				msg.msg[2] = 'A';
				msg.msg[3] = 'B';
				msg.msg[4] = 'L';
				msg.msg[5] = 'A';
				msg.msg[6] = 0;
				msg.mod = MOD_AFSK;
				msg.freq = (*fptr)();

				chMBPost(&radioMBP, (msg_t)&msg, 0);
				break;

			case PROT_UKHAS:
				// TODO: Implement protocol

				chMBPost(&radioMBP, (msg_t)&msg, 0);
				break;

			default:
				TRACE_ERROR("Unsupported protocol selected for module POSITION");
		}

		time += S2ST(parm->cycle); // Wait until this time
		chThdSleepUntil(time);
	}
}

