#include "shared_mem.h"

#ifdef MKS_WIFI

volatile uint8_t __attribute__ ((aligned (4))) shared_mem[SHARED_MEM_SIZE];

#endif