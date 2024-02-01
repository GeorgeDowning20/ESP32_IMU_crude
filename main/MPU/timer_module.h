#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void timer_setup(void);

extern volatile uint64_t counter;  // Global counter variable, can be accessed from main.c

#ifdef __cplusplus
}
#endif

