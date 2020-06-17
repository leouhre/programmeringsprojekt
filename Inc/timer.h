#include <stdio.h> // Whatever needs to be included
#include <stdint.h>
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h"

#ifndef _TIMER_H_
#define _TIMER_H_

extern volatile uint8_t flag;

void timer_configure();
void TIM2_IRQHandler(void);

#endif
