#include <stdio.h> // Whatever needs to be included
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ansi.h"
#include "math.h"
#include "entity_structs.h"
#include "spaceship.h"
#include "powerups.h"
#define CLIP_SIZE 5

#ifndef _ENEMY_H_
#define _ENEMY_H_
// The enemy_t is defined in entity_structs.h

void enemy_init(enemy_t *enemy, int32_t x, int32_t y, enemyBullet_t enemyBullet[CLIP_SIZE], uint8_t hp);
void enemy_update(enemy_t *enemies, uint8_t numberOfEnemies, spaceship_t *sh, bullet_t *bullet, uint8_t maxHp, powerup_t *powerups, uint32_t tick);
void enemy_render(enemy_t enemy, uint8_t maxHp);
void fillEnemiesArray(enemy_t *enemies, uint8_t n);
uint8_t spaceshipEnemyCollision(enemy_t enemy, spaceship_t *sh);
uint8_t bulletEnemyCollision(enemy_t *enemy, bullet_t bullet, spaceship_t *sh);
uint8_t enemyEnemyCollision(enemy_t *enemy, uint8_t n, enemy_t *enemies, int8_t numberOfEnemies);
uint8_t enemyBoundsCheck(enemy_t enemy);
void bulletEnemyClip_init(enemy_t *enemy);
void bulletEnemy_init(enemy_t *enemy);
void bulletEnemyClip_update(enemy_t *enemies, uint8_t numberOfEnemies, spaceship_t *sh);
void bulletEnemy_update(enemy_t *enemies, uint8_t numberOfEnemies, spaceship_t *sh);
uint8_t bulletEnemy_boundsCheck(enemyBullet_t bullet);
uint8_t playerHit(enemyBullet_t bullet, spaceship_t *sh);

#endif
