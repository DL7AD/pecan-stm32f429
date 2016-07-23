#include "ch.h"
#include "hal.h"
#include "ff.h"
#include "debug.h"
#include "config.h"

MMCDriver MMCD1;
bool sdInitialized = false;

bool initSD(void)
{
	TRACE_INFO("SD   > Initialize SD card");

	// Maximum speed SPI configuration
	static SPIConfig hs_spicfg = {
		.ssport	= PORT(SD_CS),
		.sspad	= PIN(SD_CS)
	};

	// Low speed SPI configuration
	static SPIConfig ls_spicfg = {
		.ssport	= PORT(SD_CS),
		.sspad	= PIN(SD_CS),
		.cr1	= SPI_CR1_BR_2 | SPI_CR1_BR_1
	};

	// MMC/SD over SPI driver configuration
	static MMCConfig mmccfg = {&SPID2, &ls_spicfg, &hs_spicfg};

	// Init MMC
	mmcObjectInit(&MMCD1);
	mmcStart(&MMCD1, &mmccfg);

	// Check SD card presence
	spiAcquireBus(&SPID2);
	if(mmcConnect(&MMCD1)) {
		TRACE_ERROR("SD   > No SD card found");
	} else {
		TRACE_INFO("SD   > SD card found");
		sdInitialized = true;
	}
	spiReleaseBus(&SPID2);

	return sdInitialized;
}

bool writeBufferToFile(const char *filename, const uint8_t *buffer, uint32_t len)
{
	if(!sdInitialized)
		return false;

	spiAcquireBus(&SPID2);

	static FATFS fs;
	static FIL fdst;
	FRESULT res;
	bool gres = true; // Optimist

	// Mount SD card
	TRACE_INFO("SD   > Mount");
	res = f_mount(&fs, "/", 0);
	if(res != FR_OK)
	{

		TRACE_ERROR("SD   > Mounting failed (err=%d)", res);
		gres = false;

	} else {

		// Open file
		TRACE_INFO("SD   > Open file %s", filename);
		res = f_open(&fdst, (TCHAR*)filename, FA_CREATE_ALWAYS | FA_WRITE);
		if(res != FR_OK)
		{

			TRACE_ERROR("SD   > Opening file failed (err=%d)", res);
			gres = false;

		} else {

			// Write buffer into file
			TRACE_INFO("SD   > Write buffer to file (len=%d)", len);
			uint32_t len_written;
			f_write(&fdst, buffer, len, (UINT*)&len_written);
			if(len_written != len)
			{
				TRACE_ERROR("SD   > Writing failed (err=%d)", res);
				gres = false;
			}

			// Close file
			TRACE_INFO("SD   > Close file");
			res = f_close(&fdst);
			if(res != FR_OK)
			{
				TRACE_ERROR("SD   > Closing file failed (err=%d)", res);
				gres = false;
			}

		}

		// Unmount
		TRACE_INFO("SD   > Unmount");
		res = f_mount(0, "", 0);
		if(res != FR_OK)
		{
			TRACE_ERROR("SD   > Unmounting failed (err=%d)", res);
			gres = false;
		}
	}

	spiReleaseBus(&SPID2);

	return gres;
}

