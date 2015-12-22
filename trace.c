#include "ch.h"
#include "hal.h"
#include "trace.h"

mutex_t trace_mtx; // Used internal to synchronize multiple chprintf
