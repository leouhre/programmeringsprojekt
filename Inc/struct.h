#include <stdio.h> // Whatever needs to be included
#include <stdint.h>
#include <string.h>

#include "math.h"

#ifndef _STRUCT_H_
#define _STRUCT_H_

typedef struct {
    int32_t x, y;
    vector_t direction;
    //future updates;
    /*
    int32_t hp, dmg, spd, sht_spd, acceleration, bullet style
    */
} spaceship_t;

void spaceshipinit(spaceship_t *sh, vector_t direction, int32_t x, int32_t y);









#endif
