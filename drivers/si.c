/**
 * Si4x6x driver specialized for APRS transmissions. Modulation concept has been taken
 * from Stefan Biereigel DK3SB.
 * @see http://www.github.com/thasti/utrak
 */
#include "ch.h"
#include "hal.h"
#include "trace.h"

#define RF_SHIFT_SET(Select)		{ \
										if (Select) \
											RADIO_GPIO_GPIO0->DATA &= ~RADIO_PIN_GPIO0; \
										else \
											RADIO_GPIO_GPIO0->DATA |= RADIO_PIN_GPIO0; \
									}
#define RADIO_SDN_SET(Select)		{ \
										if (Select) \
											RADIO_GPIO_SDN->DATA |= RADIO_PIN_SDN; \
										else \
											RADIO_GPIO_SDN->DATA &= ~RADIO_PIN_SDN; \
									}
#define VCXO_EN_SET(Select)			{ \
										if (Select) \
											VCXO_GPIO_EN->DATA |= VCXO_PIN_EN; \
										else \
											VCXO_GPIO_EN->DATA &= ~VCXO_PIN_EN; \
									}

/**
 * Initializes Si406x transceiver chip. Adjustes the frequency which is shifted by variable
 * oscillator voltage.
 * @param mv Oscillator voltage in mv
 */
bool Si_Init(void) {
	// Initialize SPI
	SSP_Init();

	// Configure GPIO pins
	LPC_IOCON->RADIO_PIO_SDN   = 0x30;					// Radio SDN pin
	LPC_IOCON->RADIO_PIO_GPIO0 = 0x30;					// Frequency shifting pin (GPIO0)
	LPC_IOCON->VCXO_PIO_EN     = 0x30;					// TCXO enable pin

	// Set output
	RADIO_GPIO_SDN->DIR |= RADIO_PIN_SDN;
	RADIO_GPIO_GPIO0->DIR |= RADIO_PIN_GPIO0;
	VCXO_GPIO_EN->DIR |= VCXO_PIN_EN;

	// Initialize GPIO pins
	RADIO_SDN_SET(true);								// Power down transmitter
	RF_SHIFT_SET(HIGH);									// Shift high
	VCXO_EN_SET(true);									// Enable TCXO

	delay(10);											// Delay 10ms (for TCXO startup)

	// Power up transmitter
	RADIO_SDN_SET(false);								// Radio SDN low (power up transmitter)

	delay(1);											// Wait for transmitter to power up

	// Power up (transmits oscillator type)
	uint8_t x3 = (OSC_FREQ >> 24) & 0x0FF;
	uint8_t x2 = (OSC_FREQ >> 16) & 0x0FF;
	uint8_t x1 = (OSC_FREQ >>  8) & 0x0FF;
	uint8_t x0 = (OSC_FREQ >>  0) & 0x0FF;
	uint8_t init_command[] = {0x02, 0x01, 0x01, x3, x2, x1, x0};
	SendCmdReceiveAnswerSetDelay(init_command, 7, NULL, 7, 100);

	// Set transmitter GPIOs
	uint8_t gpio_pin_cfg_command[] = {
		0x13,	// Command type = GPIO settings
		0x44,	// GPIO0        0 - PULL_CTL[1bit] - GPIO_MODE[6bit]
		0x00,	// GPIO1        0 - PULL_CTL[1bit] - GPIO_MODE[6bit]
		0x00,	// GPIO2        0 - PULL_CTL[1bit] - GPIO_MODE[6bit]
		0x00,	// GPIO3        0 - PULL_CTL[1bit] - GPIO_MODE[6bit]
		0x00,	// NIRQ
		0x00,	// SDO
		0x00	// GEN_CONFIG
	};
	SendCmdReceiveAnswer(gpio_pin_cfg_command, 8, NULL, 8);

	// Set misc configuration
	setModem();

	return true;
}

void SendCmdReceiveAnswer(uint8_t* txData, uint32_t byteCountTx, uint8_t* rxData, uint32_t byteCountRx) {
	SendCmdReceiveAnswerSetDelay(txData, byteCountTx, rxData, byteCountRx, 10);
}

void SendCmdReceiveAnswerSetDelay(uint8_t* txData, uint32_t byteCountTx, uint8_t* rxData, uint32_t byteCountRx, uint32_t delays) {
	// Kommunikation vorbereiten
	SSPStruct.pTxData = txData;
	SSPStruct.pRxData = rxData;
	SSPStruct.TxCount = byteCountTx;
	SSPStruct.RxCount = byteCountRx;

	// Kommunikation durchführen
	SSP_START_IRQ();

	// Warten auf beenden der Kommunikation
	SSP_WaitTransferComplete();

	// Warten auf Antwort
	uint8_t rx_answer[] = {0x00, 0x00};

	while(rx_answer[0] != 0xFF) {
		uint8_t rx_ready[] = {0x44, 0x00};


		SSPStruct.pTxData = rx_ready;
		SSPStruct.pRxData = rx_answer;
		SSPStruct.TxCount = 2;
		SSPStruct.RxCount = 2;

		// Kommunikation durchführen
		SSP_START_IRQ();

		// Warten auf beenden der Kommunikation
		SSP_WaitTransferComplete();

		if(rx_answer[1] != 0xFF) {
			delay(1);
		}
	}


	// Zusaetzliches delay
	if(delays)
		delay(delays);
}

void sendFrequencyToSi(uint32_t freq) {
	// Set the output divider according to recommended ranges given in Si406x datasheet
	uint32_t band = 0;
	uint32_t outdiv;
	if(freq < 705000000UL) {outdiv = 6;  band = 1;};
	if(freq < 525000000UL) {outdiv = 8;  band = 2;};
	if(freq < 353000000UL) {outdiv = 12; band = 3;};
	if(freq < 239000000UL) {outdiv = 16; band = 4;};
	if(freq < 177000000UL) {outdiv = 24; band = 5;};

	// Set the band parameter
	uint32_t sy_sel = 8;
	uint8_t set_band_property_command[] = {0x11, 0x20, 0x01, 0x51, (band + sy_sel)};
	SendCmdReceiveAnswerSetDelay(set_band_property_command, 5, NULL, 5, 100);

	// Set the PLL parameters
	uint32_t f_pfd = 2 * OSC_FREQ / outdiv;
	uint32_t n = ((uint32_t)(freq / f_pfd)) - 1;
	float ratio = (float)freq / (float)f_pfd;
	float rest  = ratio - (float)n;

	uint32_t m = (uint32_t)(rest * 524288UL);
	uint32_t m2 = m >> 16;
	uint32_t m1 = (m - m2 * 0x10000) >> 8;
	uint32_t m0 = (m - m2 * 0x10000 - (m1 << 8));

	// Transmit frequency to chip
	uint8_t set_frequency_property_command[] = {0x11, 0x40, 0x04, 0x00, n, m2, m1, m0};
	SendCmdReceiveAnswerSetDelay(set_frequency_property_command, 8, NULL, 8, 100);

	uint32_t x = ((((uint32_t)1 << 19) * outdiv * 1300.0)/(2*OSC_FREQ))*2;
	uint8_t x2 = (x >> 16) & 0xFF;
	uint8_t x1 = (x >>  8) & 0xFF;
	uint8_t x0 = (x >>  0) & 0xFF;
	uint8_t set_deviation[] = {0x11, 0x20, 0x03, 0x0a, x2, x1, x0};
	SendCmdReceiveAnswerSetDelay(set_deviation, 7, NULL, 7, 100);
}

void setModem() {

	// Disable preamble
	uint8_t disable_preamble[] = {0x11, 0x10, 0x01, 0x00, 0x00};
	SendCmdReceiveAnswer(disable_preamble, 5, NULL, 5);

	// Do not transmit sync word
	uint8_t no_sync_word[] = {0x11, 0x11, 0x01, 0x11, (0x01 << 7)};
	SendCmdReceiveAnswer(no_sync_word, 5, NULL, 5);

	// Setup the NCO modulo and oversampling mode
	uint32_t s = OSC_FREQ / 10;
	uint8_t f3 = (s >> 24) & 0xFF;
	uint8_t f2 = (s >> 16) & 0xFF;
	uint8_t f1 = (s >>  8) & 0xFF;
	uint8_t f0 = (s >>  0) & 0xFF;
	uint8_t setup_oversampling[] = {0x11, 0x20, 0x04, 0x06, f3, f2, f1, f0};
	SendCmdReceiveAnswer(setup_oversampling, 8, NULL, 8);

	// setup the NCO data rate for APRS
	uint8_t setup_data_rate[] = {0x11, 0x20, 0x03, 0x03, 0x00, 0x11, 0x30};
	SendCmdReceiveAnswer(setup_data_rate, 7, NULL, 7);

	// use 2GFSK from async GPIO0
	uint8_t use_2gfsk[] = {0x11, 0x20, 0x01, 0x00, 0x0B};
	SendCmdReceiveAnswer(use_2gfsk, 5, NULL, 5);

	// Set AFSK filter
	uint8_t coeff[] = {0x81, 0x9f, 0xc4, 0xee, 0x18, 0x3e, 0x5c, 0x70, 0x76};
	uint8_t i;
	for(i=0; i<sizeof(coeff); i++) {
		uint8_t msg[] = {0x11, 0x20, 0x01, 0x17-i, coeff[i]};
		SendCmdReceiveAnswer(msg, 5, NULL, 5);
	}
}

void setPowerLevel(uint8_t level) {
	// Set the Power
	uint8_t set_pa_pwr_lvl_property_command[] = {0x11, 0x22, 0x01, 0x01, level};

	// send parameters
	SendCmdReceiveAnswer(set_pa_pwr_lvl_property_command, 5, NULL, 5);
}

void startTx(void) {
	uint8_t change_state_command[] = {0x34, 0x07};
	SendCmdReceiveAnswerSetDelay(change_state_command, 2, NULL, 2, 100);
}

void stopTx(void) {
	uint8_t change_state_command[] = {0x34, 0x03};
	SendCmdReceiveAnswerSetDelay(change_state_command, 2, NULL, 2, 100);
}

void radioShutdown(void) {
	RADIO_SDN_SET(true);	// Power down chip
	VCXO_EN_SET(false);		// Power down oscillator

	SSP_DeInit();			// Power down SPI
}

/**
 * Tunes the radio and activates transmission.
 * @param frequency Transmission frequency in Hz
 * @param shift Shift of FSK in Hz
 * @param level Transmission power level (see power level description in config file)
 */
void radioTune(uint32_t frequency, uint8_t level) {
	stopTx();

	if(frequency < 119000000UL || frequency > 1050000000UL)
		frequency = 145300000UL;

	sendFrequencyToSi(frequency);	// Frequency
	setPowerLevel(level);				// Power level

	startTx();
}

inline void setGPIO(bool s) {
	RF_SHIFT_SET(s);
}

int8_t Si_getTemperature(void) {
	uint8_t txData[7] = {0x14, 0x10};
	uint8_t rxData[7];

	// Kommunikation vorbereiten
	SSPStruct.pTxData = txData;
	SSPStruct.pRxData = rxData;
	SSPStruct.TxCount = 2;
	SSPStruct.RxCount = 2;

	// Kommunikation durchführen
	SSP_START_IRQ();

	// Warten auf beenden der Kommunikation
	SSP_WaitTransferComplete();

	delay(10);

	uint8_t rx_answer[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	uint8_t rx_ready[] = {0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	while(rx_answer[0] != 0xFF) {

		SSPStruct.pTxData = rx_ready;
		SSPStruct.pRxData = rx_answer;
		SSPStruct.TxCount = 8;
		SSPStruct.RxCount = 8;

		// Kommunikation durchführen
		SSP_START_IRQ();

		// Warten auf beenden der Kommunikation
		SSP_WaitTransferComplete();

		if(rx_answer[1] != 0xFF) {
			delay(1);
		}
	}

	uint16_t adc = rx_answer[7] | ((rx_answer[6] & 0x7) << 8);
	return (899*adc)/4096 - 293;
}

