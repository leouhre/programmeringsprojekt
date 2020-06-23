#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ansi.h"
#include "entity_structs.h"
#include "ADC1.h"

#define NUKE_DIAMETER 25

#ifndef _NUKE_H_
#define _NUKE_H_

void nuke_init(nuke_t *nuke, spaceship_t sh);
void nuke_update(nuke_t *nuke, enemy_t *enemies, uint8_t numEnemies, spaceship_t *sh, uint8_t *nukeCount);
void nuke_render(nuke_t nuke);
uint8_t nukeHit(nuke_t nuke, enemy_t *enemies, uint8_t numEnemies);
uint8_t nukeBoundsCheck(nuke_t nuke);
void nukeExplode(nuke_t nuke, enemy_t *enemies, uint8_t numEnemies);
void nukeExplosion_render(nuke_t nuke, uint8_t nukeCount, uint8_t rm, spaceship_t *sh);

#endif
