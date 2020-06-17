#include <stdio.h> // Whatever needs to be included
#include <stdint.h>
#include <string.h>

#include "math.h"

#ifndef _SPACESHIP_H_
#define _SPACESHIP_H_

typedef struct {
    int32_t x, y, angle;
    uint8_t bullet_type, clipsize;

    //vector_t direction;
    //future updates;
    /*
    int32_t hp, dmg, spd, sht_spd, acceleration, bullet style
    */
} spaceship_t;

void spaceshipinit(spaceship_t *sh, int32_t direction, int32_t x, int32_t y);
void update_spaceship(int in, spaceship_t *sh);
void render_spaceship(spaceship_t sh);
void spaceship_sprite(spaceship_t sh, uint8_t n);

#endif