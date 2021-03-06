
#include <stdio.h> // Whatever needs to be included
#include <stdint.h>
#include <string.h>
#include "entity_structs.h"
#include "math.h"
#include "ansi.h"

#ifndef _SPACESHIP_H_
#define _SPACESHIP_H_

void spaceship_init(spaceship_t *sh, int32_t direction, int32_t x, int32_t y);
void spaceship_update(uint8_t in, spaceship_t *sh);
void spaceship_render(spaceship_t sh);
void spaceship_sprite(spaceship_t sh, uint8_t n);
void spaceshipAim_render(spaceship_t sh);
uint8_t spaceshipBoundsCheck(spaceship_t sh);
uint8_t spaceshipDead(spaceship_t sh);
#endif
