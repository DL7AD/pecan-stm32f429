#include "ch.h"
#include "hal.h"
#include "sleep.h"
#include "padc.h"
#include "tracking.h"

bool p_sleep(const sleep_config_t *config)
{
	(void)config;

	// TODO: Implement this function

	return false;
}

systime_t waitForTrigger(systime_t prev, trigger_config_t *config)
{
	void (*fptr)(void);

	switch(config->type)
	{
		case TRIG_EVENT: // Wait for new tracking point
			
			fptr = config->events[0]; // FIXME: Currently its only possible to trigger on one event
			(*fptr)();
		
		case TRIG_TIMEOUT: // Wait for specified timeout
			return chThdSleepUntilWindowed(prev, prev + S2ST(config->timeout));

		default: // No trigger FIXME
			break;
	}

	return chVTGetSystemTimeX();
}

void trigger_new_tracking_point(void)
{
	uint32_t oldID = getLastTrackPoint()->id;
	trackPoint_t *newtp;
	do { // Wait for new serial ID to be deployed
		chThdSleepMilliseconds(100);
		newtp = getLastTrackPoint();
	} while(newtp->id == oldID);
}

void trigger_immediately(void)
{
	// Nothing to do here
}
