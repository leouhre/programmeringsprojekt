#include <stdio.h> // Whatever needs to be included
#include <stdint.h>
#include <string.h>
#include "math.h"
#include "spaceship.h"
#include "ansi.h"
#include <stdlib.h>
#include "bullet.h"

#ifndef _ENEMY_H_
#define _ENEMY_H_

typedef struct {
    int32_t x, y, hp;
    vector_t direction;
    //future updates;
    /*
    int32_t dmg, spd, sht_spd, acceleration, bullet style
    */
} enemy_t;

void enemy_init(enemy_t *enemy, int32_t x, int32_t y);
void enemy_update(enemy_t *enemy, spaceship_t sh, bullet_t *bullet);
void enemy_render(enemy_t e);
void fillEnemiesArray(enemy_t *enemies, uint8_t n);
uint8_t spaceshipCollision(enemy_t enemy, spaceship_t sh);
uint8_t bulletCollision(enemy_t enemy, bullet_t *bullet, spaceship_t sh);
#endif
