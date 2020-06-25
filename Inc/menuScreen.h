#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "ansi.h"
#include "controls.h"
#include "entity_structs.h"
#include "spaceship.h"
#include "enemy.h"
#include "math.h"
#define MAX_ENEMIES 32



#ifndef _MENUSCREEN_H_
#define _MENUSCREEN_H_


void gameInit(gameHandler_t *game);

void loadMenu();

void selectInMenu(gameHandler_t *game);

void loadOptions(gameHandler_t *game);

void selectInOptions(gameHandler_t *game);

void loadHowToPlay();

void loadCredits();

void selectInCreditsAndHowToPlay();

void loadPause();

void selectInPause(gameHandler_t *game);

void nextLevel(gameHandler_t *game);

void gameOver(gameHandler_t *game);

void levelInit(gameHandler_t *game, spaceship_t *sh, nuke_t *n, homing_t *h, uint8_t *numEnemies, enemy_t enemies[MAX_ENEMIES], powerup_t *powerups,enemyBullet_t enemyBullets[MAX_ENEMIES][CLIP_SIZE], bullet_t playerBullet[CLIP_SIZE]);

#endif
