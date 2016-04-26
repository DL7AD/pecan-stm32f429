#include "ch.h"
#include "hal.h"

#include "debug.h"
#include "modules.h"
#include "ov9655.h"
#include "ov2640.h"
#include "pi2c.h"
#include "ssdv.h"
#include "aprs.h"
#include "radio.h"
#include "base.h"
#include <string.h>
#include "types.h"
#include "sleep.h"

static uint32_t image_id;

void encode_ssdv(uint8_t *image, uint32_t image_len, module_conf_t* config) {
	ssdv_t ssdv;
	uint8_t pkt[SSDV_PKT_SIZE];
	uint8_t pkt_base91[BASE91LEN(SSDV_PKT_SIZE-37)];
	uint16_t i = 0;
	uint8_t *b;
	uint32_t bi = 0;
	uint8_t c = SSDV_OK;

	// Init SSDV (FEC at 2FSK, non FEC at APRS)
	ssdv_enc_init(&ssdv, config->protocol == PROT_SSDV_2FSK ? SSDV_TYPE_NORMAL : SSDV_TYPE_NORMAL, config->ssdv_config.callsign, ++image_id);
	ssdv_enc_set_buffer(&ssdv, pkt);

	while(true)
	{
		// parm->lastCycle = chVTGetSystemTimeX(); // Update Watchdog timer FIXME

		while((c = ssdv_enc_get_packet(&ssdv)) == SSDV_FEED_ME)
		{
			b = &image[bi];
			uint8_t r = bi < image_len-128 ? 128 : image_len - bi;
			bi += r;

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
		msg.freq = getFrequency(&config->frequency);
		msg.power = config->power;

		switch(config->protocol) {
			case PROT_APRS_2GFSK:
			case PROT_APRS_AFSK:
				msg.mod = config->protocol == PROT_APRS_AFSK ? MOD_AFSK : MOD_2GFSK;
				msg.afsk_config = &(config->afsk_config);
				msg.gfsk_config = &(config->gfsk_config);

				// Deleting buffer
				for(int t=0; t<256; t++)
					pkt_base91[t] = 0;

				base91_encode(&pkt[1], pkt_base91, sizeof(pkt)-37); // Sync byte, CRC and FEC of SSDV not transmitted
				msg.bin_len = aprs_encode_image(msg.msg, msg.mod, &config->aprs_config, pkt_base91, strlen((char*)pkt_base91));

				while(!transmitOnRadio(&msg)) // Try to insert message into message box less aggressively
					chThdSleepMilliseconds(100);
				break;

			case PROT_SSDV_2FSK:
				msg.mod = MOD_2FSK;
				msg.fsk_config = &(config->fsk_config);

				memcpy(msg.msg, pkt, sizeof(pkt));
				msg.bin_len = 8*sizeof(pkt);

				while(!transmitOnRadio(&msg)) // Try to insert message into message box less aggressively
					chThdSleepMilliseconds(100);
				break;

			default:
				TRACE_ERROR("IMG  > Unsupported protocol selected for module IMAGE");
		}

		// Packet spacing (delay)
		if(config->packet_spacing)
			chThdSleepMilliseconds(config->packet_spacing);

		i++;
	}

	TRACE_INFO("SSDV > %i packets", i);
}

THD_FUNCTION(moduleIMG, arg) {
	module_conf_t* config = (module_conf_t*)arg;

	// Execute Initial delay
	if(config->init_delay)
		chThdSleepMilliseconds(config->init_delay);

	// Print infos
	TRACE_INFO("IMG  > Startup module %s", config->name);

	systime_t time = chVTGetSystemTimeX();
	while(true)
	{
		// TODO: Implement software watchdog
		TRACE_INFO("IMG  > Do module IMAGE cycle");

		if(!p_sleep(&config->sleep)) {

			// Lock RADIO from producing interferences
			TRACE_INFO("IMG  > Lock radio");
			chMtxLock(&interference_mtx);

			// Shutdown radios (to avoid interference)
			radioShutdown(RADIO_2M);
			radioShutdown(RADIO_70CM);

			uint8_t *image;
			uint8_t tries;

			if(config->ssdv_config.res == RES_MAX && CAMERA_TYPE == OV2640) // Maximum resolution
			{

				config->ssdv_config.res = RES_UXGA;

				do {

					// Init camera
					OV2640_init(&config->ssdv_config);

					// Sample data from DCMI through DMA into RAM
					TRACE_INFO("IMG  > Capture image");

					tries = 5; // Try 5 times at maximum
					bool status;
					do { // Try capturing image until capture successful
						status = OV2640_Snapshot2RAM();
					} while(!status && --tries);

					config->ssdv_config.res--;

				} while(OV2640_BufferOverflow() && config->ssdv_config.res >= RES_QVGA);

				config->ssdv_config.res = RES_MAX;

			} else { // Static resolution

				// Init camera
				if(CAMERA_TYPE == OV9655)
					OV9655_init(&config->ssdv_config);
				if(CAMERA_TYPE == OV2640)
					OV2640_init(&config->ssdv_config);

				// Sample data from DCMI through DMA into RAM
				TRACE_INFO("IMG  > Capture image");

				tries = 5; // Try 5 times at maximum
				bool status;
				do { // Try capturing image until capture successful
					if(CAMERA_TYPE == OV9655)
						status = OV9655_Snapshot2RAM();
					if(CAMERA_TYPE == OV2640)
						status = OV2640_Snapshot2RAM();
				} while(!status && --tries);

			}

			uint32_t image_len;
			if(CAMERA_TYPE == OV9655)
				image_len = OV9655_getBuffer(&image);
			if(CAMERA_TYPE == OV2640)
				image_len = OV2640_getBuffer(&image);
			TRACE_INFO("CAM > Image size: %d bytes", image_len);

			// Switch off camera
			if(CAMERA_TYPE == OV9655)
				OV9655_deinit();
			if(CAMERA_TYPE == OV2640)
				OV2640_deinit();

			// Unlock radio
			TRACE_INFO("IMG  > Unlock radio");
			chMtxUnlock(&interference_mtx);

			if(tries) { // Capture successful
				TRACE_INFO("IMG  > Encode/Transmit SSDV");
				encode_ssdv(image, image_len, config);
			} else {
				TRACE_ERROR("IMG  > Image capturing failed");
			}

		}

		time = waitForTrigger(time, &config->trigger);
	}
}

