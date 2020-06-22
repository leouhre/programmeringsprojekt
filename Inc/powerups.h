#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "ansi.h"
#include "spaceship.h"
#include "entity_structs.h"
#include "math.h"

#ifndef _POWERUPS_H_
#define _POWERUPS_H_

void powerup_init(uint32_t x, uint32_t y, uint8_t type, powerup_t *powerups);
void powerup_render(powerup_t *powerups, spaceship_t *sh);
void powerup_spawn_random(uint32_t x, uint32_t y, powerup_t *powerups, uint32_t tick);
uint8_t playerPowerupCollision(powerup_t powerup, spaceship_t *sh);

#endif

