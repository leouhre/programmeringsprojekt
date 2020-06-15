#include <stdio.h> // Whatever needs to be included
#include <stdint.h>
#include <string.h>
#include "math.h"

#ifndef _ENEMY_H_
#define _ENEMY_H_

typedef struct {
    int32_t x, y;
    uint8_t bullet_type;
    vector_t direction;

} bullet_t;

void bullet_init(bullet_t bullet, spaceship_t *sh);
void bullet_update(bullet_t bullet, entities *enemies);
void bullet_draw();

#endif
