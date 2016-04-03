#include "ch.h"
#include "hal.h"

#include "debug.h"
#include "modules.h"
#include "ov9655.h"
#include "pi2c.h"
#include "ssdv.h"
#include "aprs.h"
#include "base.h"
#include <string.h>

static uint32_t image_id;

void encode_ssdv(uint8_t *image, uint32_t image_len, module_params_t* parm) {
	ssdv_t ssdv;
	uint8_t pkt[SSDV_PKT_SIZE];
	uint8_t pkt_base91[BASE91LEN(SSDV_PKT_SIZE-37)];
	uint16_t i = 0;
	uint8_t *b;
	uint16_t bi = 0;
	uint8_t c = SSDV_OK;

	// Init SSDV (FEC at 2FSK, non FEC at APRS)
	ssdv_enc_init(&ssdv, parm->protocol == PROT_SSDV_2FSK ? SSDV_TYPE_NORMAL : SSDV_TYPE_NORMAL, SSDV_CALLSIGN, ++image_id);
	ssdv_enc_set_buffer(&ssdv, pkt);

	while(true)
	{
		parm->lastCycle = chVTGetSystemTimeX(); // Update Watchdog timer

		while((c = ssdv_enc_get_packet(&ssdv)) == SSDV_FEED_ME)
		{
			b = &image[bi];
			uint8_t r = bi < image_len-128 ? 128 : image_len - bi;
			bi += 128;

			if(r <= 0)
			{
				TRACE_ERROR("SSDV > Premature end of file");
				break;
			}
			ssdv_enc_feed(&ssdv, b, r);
		}

		if(c == SSDV_EOI)
		{
			TRACE_INFO("SSDV > ssdv_enc_get_packet said EOI");
			break;
		} else if(c != SSDV_OK) {
			TRACE_ERROR("SSDV > ssdv_enc_get_packet failed: %i", c);
			return;
		}

		// Transmit packet
		radioMSG_t msg;
		uint32_t (*fptr)(void);
		fptr = parm->frequencyMethod;

		switch(parm->protocol) {
			case PROT_SSDV_APRS_2GFSK:
				TRACE_ERROR("IMG  > 2GFSK not yet implemented")
				break;

			case PROT_SSDV_APRS_AFSK:
				msg.mod = MOD_AFSK;
				msg.freq = (*fptr)();
				msg.power = parm->power;

				// Deleting buffer
				for(int t=0; t<256; t++)
					pkt_base91[t] = 0;

				base91_encode(&pkt[1], pkt_base91, sizeof(pkt)-37); // Sync byte, CRC and FEC of SSDV not transmitted
				msg.bin_len = aprs_encode_image(msg.msg, msg.mod, pkt_base91, strlen((char*)pkt_base91));

				while(!transmitOnRadio(&msg)) // Try to insert message into message box less aggressively
					chThdSleepMilliseconds(2000);
				break;

			case PROT_SSDV_2FSK:
				msg.mod = MOD_2FSK;
				msg.freq = (*fptr)();
				msg.power = parm->power;

				memcpy(msg.msg, pkt, sizeof(pkt));
				msg.bin_len = 8*sizeof(pkt);

				while(!transmitOnRadio(&msg)) // Try to insert message into message box less aggressively
					chThdSleepMilliseconds(2000);
				break;

			default:
				TRACE_ERROR("IMG  > Unsupported protocol selected for module IMAGE");
		}

		i++;
	}

	TRACE_INFO("SSDV > %i packets", i);
}

THD_FUNCTION(moduleIMG, arg) {
	// Print infos
	module_params_t* parm = (module_params_t*)arg;
	TRACE_INFO("IMG  > Startup module IMAGE");
	TRACE_MODULE_INFO(parm, "IMG", "IMAGE");

	uint32_t (*sleep)(void);
	sleep = parm->sleepMethod;

	systime_t time = chVTGetSystemTimeX();
	while(true)
	{
		parm->lastCycle = chVTGetSystemTimeX(); // Watchdog timer
		TRACE_INFO("IMG  > Do module IMAGE cycle");

		if(sleep() == SMOD_SLEEP) { // Sleep

			TRACE_INFO("IMG  > Sleep (60sec+Cycle)");
			chThdSleepMilliseconds(60000);

		} else { // Active

			// Lock RADIO from producing interferences
			TRACE_INFO("IMG  > Lock radio");
			chMtxLock(&interference_mtx);

			// Shutdown radios (to avoid interference)
			radioShutdown(RADIO_2M);
			radioShutdown(RADIO_70CM);

			// Init I2C
			TRACE_INFO("IMG  > Init camera I2C");
			i2cCamInit();

			// Init camera
			OV9655_init();

			// Sample data from DCMI through DMA into RAM
			TRACE_INFO("IMG  > Capture image");
			uint8_t tries = 5; // Try 5 times at maximum
			bool status;
			do { // Try capturing image until capture successful
				status = OV9655_Snapshot2RAM();
			} while(!status && --tries);

			uint8_t *image;
			uint32_t image_len = OV9655_getBuffer(&image);

			// Switch off camera
			OV9655_deinit();

			// Unlock radio
			TRACE_INFO("IMG  > Unlock radio");
			chMtxUnlock(&interference_mtx);

			if(tries) { // Capture successful
				TRACE_INFO("IMG  > Encode/Transmit SSDV");
				encode_ssdv(image, image_len, parm);
			} else {
				TRACE_ERROR("IMG  > Image capturing failed");
			}

		}

		time = chThdSleepUntilWindowed(time, time + S2ST(parm->cycle)); // Wait until time + cycletime
	}
}













