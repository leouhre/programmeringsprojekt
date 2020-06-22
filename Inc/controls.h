#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h"
#include <stdio.h> // Whatever needs to be included
#include <stdint.h>
#include <string.h>

#ifndef _CONTROLS_H_
#define _CONTROLS_H_

void readUART(char *buffer);
uint8_t readControls();


#endif
