#include "ch.h"
#include "hal.h"

#include "trace.h"
#include "modules.h"
#include "radio.h"
#include "../protocols/aprs/aprs.h"

THD_FUNCTION(modulePOS, arg) {
	// Print infos
	module_params_t* parm = (module_params_t*)arg;
	TRACE_INFO("POS  > Startup module POSITION");
	TRACE_MODULE_INFO(parm, "POS", "POSITION");

	systime_t time = chVTGetSystemTimeX();
	while(true)
	{
		TRACE_INFO("POS  > Do module POSITION cycle");
		TRACE_WARN("POS  > Module POSITION not fully implemented"); // FIXME

		TRACE_INFO("POS  > Get last track point");
		trackPoint_t *trackPoint = getLastTrackPoint();

		TRACE_INFO("POS  > Transmit GPS position");

		radioMSG_t msg;
		uint32_t (*fptr)(void);
		fptr = parm->frequencyMethod;

		switch(parm->protocol) {

			case PROT_APRS:
				msg.mod = MOD_AFSK;
				msg.freq = (*fptr)();
				msg.power = parm->power;
				msg.bin_len = aprs_encode_position(&msg.msg, trackPoint);

				chMBPost(&radioMBP, (msg_t)&msg, 0);
				break;

			case PROT_UKHAS:
				// TODO: Implement protocol

				chMBPost(&radioMBP, (msg_t)&msg, 0);
				break;

			default:
				TRACE_ERROR("POS  > Unsupported protocol selected for module POSITION");
		}

		time += S2ST(parm->cycle); // Wait until this time
		chThdSleepUntil(time);
	}
}

