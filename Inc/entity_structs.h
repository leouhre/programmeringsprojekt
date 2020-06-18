#include <stdint.h>
#include "math.h"

#ifndef _ENTITY_STRUCTS_H_
#define _ENTITY_STRUCTS_H_

typedef struct {
    int32_t x, y, angle;
    uint8_t bullet_type, clipsize;

    //vector_t direction;
    //future updates;
    /*
    int32_t hp, dmg, spd, sht_spd, acceleration, bullet style
    */
} spaceship_t;

typedef struct {
    int32_t x, y, hp;
    uint8_t alive;
    vector_t direction;
    //future updates;
    /*
    int32_t dmg, spd, sht_spd, acceleration, bullet style
    */
} enemy_t;

typedef struct {
    int32_t x, y, angle;
    uint8_t bullet_type, alive;

} bullet_t;

#endif
