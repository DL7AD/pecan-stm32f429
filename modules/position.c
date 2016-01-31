#include "ch.h"
#include "hal.h"

#include "debug.h"
#include "modules.h"
#include "radio.h"
#include "aprs.h"
#include "cw.h"
#include "chprintf.h"

THD_FUNCTION(modulePOS, arg) {
	// Print infos
	module_params_t* parm = (module_params_t*)arg;
	TRACE_INFO("POS  > Startup module POSITION");
	TRACE_MODULE_INFO(parm, "POS", "POSITION");

	systime_t time = chVTGetSystemTimeX();
	while(true)
	{
		parm->lastCycle = chVTGetSystemTimeX(); // Watchdog timer
		TRACE_INFO("POS  > Do module POSITION cycle");
		TRACE_WARN("POS  > Module POSITION not fully implemented"); // FIXME

		TRACE_INFO("POS  > Get last track point");
		trackPoint_t *trackPoint = getLastTrackPoint();

		TRACE_INFO("POS  > Transmit GPS position");

		radioMSG_t msg;
		uint32_t (*fptr)(void);
		fptr = parm->frequencyMethod;

		switch(parm->protocol) {

			case PROT_APRS_AFSK:
				msg.mod = MOD_AFSK;
				msg.freq = (*fptr)();
				msg.power = parm->power;
				msg.bin_len = aprs_encode_position(&msg.msg, trackPoint);

				chMBPost(&radioMBP, (msg_t)&msg, 0);
				break;

			case PROT_UKHAS_2FSK:
				msg.mod = MOD_2FSK;
				msg.freq = (*fptr)();
				msg.power = parm->power;
				uint8_t fskmsg[64];
				msg.bin_len = 8*chsnprintf((char*)fskmsg, sizeof(fskmsg), "$$$$$%s,%d,<TODO>,*<CRC>\n", FSK_CALLSIGN, trackPoint->id); // TODO: Implement protocol
				msg.msg = fskmsg;

				chMBPost(&radioMBP, (msg_t)&msg, 0);
				break;

			case PROT_RAW_CW:
				msg.mod = MOD_CW;
				msg.freq = (*fptr)();
				msg.power = parm->power;
				const char *cwmsg = "POSITION TODO"; // TODO: Implement protocol
				msg.bin_len = CW_encode(&msg.msg, cwmsg);

				chMBPost(&radioMBP, (msg_t)&msg, 0);
				break;

			default:
				TRACE_ERROR("POS  > Unsupported modulation/protocol selected for module POSITION");
		}

		time = chThdSleepUntilWindowed(time, time + S2ST(parm->cycle)); // Wait until time + cycletime
	}
}

