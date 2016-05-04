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
	switch(config->type)
	{
		case TRIG_EVENT: // Wait for new tracking point
			switch(config->event)
			{
				case EVENT_NEW_POINT:
					waitForNewTrackPoint();
					return chVTGetSystemTimeX();

				case NO_EVENT: // No event defined
					while(1); // Assert
			}
		
		case TRIG_TIMEOUT: // Wait for specified timeout
			return chThdSleepUntilWindowed(prev, prev + S2ST(config->timeout));

		case TRIG_CONTINOUSLY: // Immediate trigger
			return chVTGetSystemTimeX();

		case TRIG_DISABLED: // No trigger defined
			while(1); // Assert
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

