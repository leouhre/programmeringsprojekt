#include <stdio.h> // Whatever needs to be included
#include <stdint.h>
#include <string.h>
#include "math.h"

#ifndef _ENEMY_H_
#define _ENEMY_H_

typedef struct {
    int32_t x, y;
    vector_t direction;
    //future updates;
    /*
    int32_t hp, dmg, spd, sht_spd, acceleration, bullet style
    */
} enemy_t;

void enemy_init(enemy_t *enemy, vector_t direction, int32_t x, int32_t y);
void enemy_update(int in, spaceship_t *sh);
void enemy_draw(spaceship_t sh);

#endif
