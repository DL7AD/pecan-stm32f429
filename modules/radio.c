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
	TRACE_INFO("RAD  > Startup module RADIO");

	// Setup mailbox
	TRACE_INFO("RAD  > Setup radio mailbox");
	chMBObjectInit(&radioMBP, (msg_t*)buf, sizeof(buf));

	while(true)
	{
		// Receive message
		radioMSG_t *msg;
		msg_t status = chMBFetch(&radioMBP, (msg_t*)&msg, 0);

		if(status == MSG_OK) { // Message available

			// Determine suitable radio
			uint32_t radio = 0;
			if(inRadio1band(msg->freq)) {
				radio = 1;
			} else if(inRadio2band(msg->freq)) {
				radio = 2;
			}

			if(radio) { // Radio found

				TRACE_INFO(	"RAD  > Transmit on radio\r\n"
							"%s Radio %d\r\n"
							"%s Frequency %d MHz\r\n"
							"%s Power %d dBm\r\n"
							"%s Modulation %s",
							TRACE_TAB, radio,
							TRACE_TAB, msg->freq,
							TRACE_TAB, msg->power,
							TRACE_TAB, VAL2MOULATION(msg->mod)
				);
				TRACE_BIN(msg->msg, msg->bin_len);

			} else { // Error

				TRACE_ERROR("RAD  > No radio available for this frequency\r\n"
							"%s Radio %d\r\n"
							"%s Frequency %d MHz\r\n"
							"%s Power %d dBm\r\n"
							"%s Modulation %s",
							TRACE_TAB, 10,
							TRACE_TAB, msg->freq,
							TRACE_TAB, msg->power,
							TRACE_TAB, VAL2MOULATION(msg->mod)
				);

			}
		}
		chThdSleepMilliseconds(100);
	}
}

