#ifndef __BASE64_H__
#define __BASE64_H__

#include "ch.h"
#include "hal.h"

#define BASE64LEN(in) (4 * (((in) + 2) / 3))

void base64_encode(const uint8_t *in, uint8_t *out, uint16_t input_length);

#endif
