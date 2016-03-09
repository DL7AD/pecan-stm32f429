#ifndef __OV9655_H__
#define __OV9655_H__

#include "ch.h"
#include "hal.h"

#define OV9655_I2C_ADR        0x30	/* Slave-address of OV9655 */

#define QVGA	/* else VGA (not working) */
#define SEC1_80	/* else shutter 1/20 sec */

bool OV9655_Snapshot2RAM(void);
void OV9655_InitDMA(void);
void OV9655_DeinitDMA(void);
void OV9655_InitDCMI(void);
void OV9655_DeinitDCMI(void);
void OV9655_InitGPIO(void);
uint32_t OV9655_getBuffer(uint8_t** buffer);
void OV9655_TransmitConfig(void);
void OV9655_init(void);
void OV9655_deinit(void);

#endif
