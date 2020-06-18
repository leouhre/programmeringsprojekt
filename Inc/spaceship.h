#include <stdio.h> // Whatever needs to be included
#include <stdint.h>
#include <string.h>
#include "entity_structs.h"
#include "math.h"

#ifndef _SPACESHIP_H_
#define _SPACESHIP_H_

void spaceship_init(spaceship_t *sh, int32_t direction, int32_t x, int32_t y);
void spaceship_update(int in, spaceship_t *sh);
void spaceship_render(spaceship_t sh);
void spaceship_sprite(spaceship_t sh, uint8_t n);

#endif
