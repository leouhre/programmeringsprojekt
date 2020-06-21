#include <stdio.h> // Whatever needs to be included
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "spaceship.h"
#include "30010_io.h"
#include "charset.h"

#ifndef _LED_H_
#define _LED_H_

void led_enable();
void led_init();
void led_hp_update(uint32_t tick, uint8_t hp);

#endif
