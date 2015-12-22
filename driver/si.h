#ifndef __SI__H__
#define __SI__H__

bool Si_Init(void);
void SendCmdReceiveAnswer(uint8_t* txData, uint32_t byteCountTx, uint8_t* rxData, uint32_t byteCountRx);
void SendCmdReceiveAnswerSetDelay(uint8_t* txData, uint32_t byteCountTx, uint8_t* rxData, uint32_t byteCountRx, uint32_t delays);
void sendFrequencyToSi(uint32_t freq);
void setModem();
void setDeviation(uint32_t deviation);
void setPowerLevel(uint8_t level);
void startTx(void);
void stopTx(void);
void radioShutdown(void);
void radioTune(uint32_t frequency, uint8_t level);
inline void setGPIO(bool s);
int8_t Si_getTemperature(void);

#endif

