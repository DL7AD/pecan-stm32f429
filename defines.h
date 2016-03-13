#ifndef __DEFINES_H__
#define __DEFINES_H__

#include "ch.h"
#include "hal.h"

#define CONCAT(A,B)         A ## B
#define EXPAND_CONCAT(A,B)  CONCAT(A, B)

#define ARG_0(A0, ...)      A0
#define ARG_1(A0, A1, ...)  A1
#define ARGN(N, LIST)       EXPAND_CONCAT(ARG_, N) LIST

#define SYM_GET_TABLE(A)	ARGN(0, A)
#define SYM_GET_SYMBOL(A)	ARGN(1, A)
#define PORT(A)				ARGN(0, A)
#define PIN(A)				ARGN(1, A)

#define HIGH	true
#define LOW		false

#endif

