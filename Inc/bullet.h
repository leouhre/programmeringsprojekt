#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "math.h"
#include "spaceship.h"

#ifndef _BULLET_H_
#define _BULLET_H_

typedef struct {
    int32_t x, y, angle;
    uint8_t bullet_type, alive;

} bullet_t;
void bullet_init(bullet_t *bullet, spaceship_t sh);
void bullet_update(bullet_t *bullet, spaceship_t sh);

#endif
