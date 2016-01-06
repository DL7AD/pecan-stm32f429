#include "ch.h"
#include "hal.h"

#include "trace.h"
#include "../modules.h"
#include "../drivers/ov9655.h"
#include "../drivers/pi2c.h"

#include "../protocols/ssdv/ssdv.h"

static uint32_t image_id;

void encode_ssdv(uint8_t *image, uint32_t image_len, module_params_t* parm) {
	ssdv_t ssdv;
	uint8_t pkt[SSDV_PKT_SIZE];
	uint16_t i = 0;
	uint8_t b;
	uint16_t bi = 0;
	uint8_t c = SSDV_OK;

	ssdv_enc_init(&ssdv, SSDV_TYPE_NORMAL, FSK_CALLSIGN, ++image_id);
	ssdv_enc_set_buffer(&ssdv, pkt);

	while(c == SSDV_OK)
	{
		// Encode packet
		while((c = ssdv_enc_get_packet(&ssdv)) == SSDV_FEED_ME)
		{
			b = image[bi++];
			if(bi == image_len)
			{
				TRACE_INFO("IMG  > Image transfer completed");
				break;
			}
			ssdv_enc_feed(&ssdv, &b, 1);
		}
		
		if(c == SSDV_EOI) {
			TRACE_INFO("IMG  > Image transfer completed\n");
			break;
		} else if(c != SSDV_OK) {
			TRACE_ERROR("IMG  > SSDV ERROR\n");
			return;
		}

		// Transmit packet
		radioMSG_t msg;
		uint32_t (*fptr)(void);
		fptr = parm->frequencyMethod;

		switch(parm->protocol) {
			case PROT_APRS:
				TRACE_ERROR("IMG  > APRS not implemented!");

				//chMBPost(&radioMBP, (msg_t)&msg, 0);
				break;

			case PROT_SSDV:
				msg.mod = MOD_2FSK;
				msg.freq = (*fptr)();
				msg.power = parm->power;
				msg.msg = pkt;
				msg.bin_len = sizeof(pkt) * sizeof(uint8_t);
				chMBPost(&radioMBP, (msg_t)&msg, 0);
				break;

			default:
				TRACE_ERROR("POS  > Unsupported protocol selected for module POSITION");
		}





		i++;
	}
}

THD_FUNCTION(moduleIMG, arg) {
	// Print infos
	module_params_t* parm = (module_params_t*)arg;
	TRACE_INFO("IMG  > Startup module IMAGE");
	TRACE_MODULE_INFO(parm, "IMG", "IMAGE");

	systime_t time = chVTGetSystemTimeX();
	while(true)
	{
		parm->lastCycle = chVTGetSystemTimeX(); // Watchdog timer
		TRACE_INFO("IMG  > Do module IMAGE cycle");
		TRACE_WARN("IMG  > Module IMAGE not fully implemented"); // FIXME

		// Init I2C
		TRACE_INFO("IMG  > Init camera I2C");
		i2cCamInit();

		// Init OV9655
		OV9655_init();

		// Sample data from DCMI through DMA to RAM
		TRACE_INFO("IMG  > Capture image");
		OV9655_Snapshot2RAM();

		uint8_t *image;
		uint32_t image_len = OV9655_getBuffer(&image);

		TRACE_INFO("IMG  > Encode/Transmit SSDV");
		encode_ssdv(image, image_len, parm);

		time += S2ST(parm->cycle); // Wait until this time
		chThdSleepUntil(time);
	}
}













