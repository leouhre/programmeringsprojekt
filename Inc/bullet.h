#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "math.h"
#include "entity_structs.h"
#include "spaceship.h"
#include "enemy.h"
#include "ansi.h"
#define CLIP_SIZE 5


#ifndef _BULLET_H_
#define _BULLET_H_
// The bullet_t is defined in entity_structs.h

void bullet_init(bullet_t *bullet, spaceship_t sh);
void bullet_update(bullet_t *bullet, spaceship_t *sh, enemy_t *enemy, uint8_t numberOfEnemies);
uint8_t boundsCheck(bullet_t bullet);

#endif
