#pragma once

#include <stdio.h>

#include "../../MarlinCore.h"
#include "../../inc/MarlinConfig.h"

#ifdef MKS_WIFI

#ifdef STM32F1
#define SHARED_MEM_1KB_COUNT    8
#define SHARED_MEM_SIZE         SHARED_MEM_1KB_COUNT*1024
#endif

#ifdef STM32F4
#define SHARED_MEM_1KB_COUNT    16
#define SHARED_MEM_SIZE         SHARED_MEM_1KB_COUNT*1024
#endif

extern volatile uint8_t shared_mem[SHARED_MEM_SIZE];

#endif