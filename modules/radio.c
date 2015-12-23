#include "ch.h"
#include "hal.h"
#include "trace.h"
#include "modules.h"

mailbox_t radioMBP;
radioMSG_t buf[10];

uint32_t getAPRSRegionFrequency(void) {
	return 144800000; // TODO: Implement Geofencing
}
uint32_t getAPRSISSFrequency(void) {
	return 145825000;
}
uint32_t getCustomFrequency(void) {
	return 434500000;
}

THD_FUNCTION(moduleRADIO, arg) {
	(void)arg;

	// Print infos
	TRACE_INFO("Startup module RADIO");

	// Setup mailbox
	TRACE_INFO("Setup mailbox");
	chMBObjectInit(&radioMBP, (msg_t*)buf, sizeof(buf));

	while(true)
	{
		radioMSG_t msg;
		msg_t status = chMBFetch(&radioMBP, (msg_t*)&msg, 0);
		if(status == MSG_OK) {
			TRACE_INFO(	"Transmit on radio\r\n"
						"%s > Message %s\r\n"
						"%s > Radio %d\r\n"
						"%s > Frequency %d MHz\r\n"
						"%s > Modulation %s",
						TRACE_TAB, msg.msg,
						TRACE_TAB, 10,
						TRACE_TAB, msg.freq,
						TRACE_TAB, VAL2MOULATION(msg.mod)
			);
		}
		chThdSleepMilliseconds(100);
	}
}

