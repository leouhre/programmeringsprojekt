#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ansi.h"
#include "math.h"
#include "entity_structs.h"
#include "spaceship.h"

#ifndef _HOMING_H_
#define _HOMING_H_

void homing_init(homing_t *h, spaceship_t sh);
void homing_update(homing_t *h, enemy_t *enemies, uint8_t numEnemies);
void homing_render(homing_t *h);
uint8_t homingEnemyDetection(homing_t *h, enemy_t *enemies, uint8_t numEnemies);
uint8_t homingBoundsCheck(homing_t *h);
uint8_t homingHit(homing_t *h, enemy_t e);
void homingExplode(homing_t *h, enemy_t *enemies, uint8_t numEnemies);
void homingExplode_render(homing_t *h);
void homingExplode_render2(homing_t *h);

#endif
