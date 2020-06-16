#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "math.h"
#include "struct.h"

#ifndef _ENEMY_H_
#define _ENEMY_H_

typedef struct {
    int32_t x, y, angle;
    uint8_t bullet_type, alive;

} bullet_t;

void bullet_init(bullet_t *bullet, spaceship_t sh);
void bullet_update(bullet_t *bullet, uint8_t **entities);
void bullet_draw();

#endif
