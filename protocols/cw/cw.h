#ifndef __CW_H__
#define __CW_H__

#include "ch.h"
#include "hal.h"

void dah(void);
void dit(void);
uint32_t CW_encode(uint8_t** data, const char* letter);
void CW_encode_char(char letter);
void positionToMaidenhead(double lat, double lon, char m[]);

#endif

