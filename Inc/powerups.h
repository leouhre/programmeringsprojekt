#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "ansi.h"
#include "spaceship.h"
#include "entity_structs.h"
#include <time.h>

#ifndef _POWERUPS_H_
#define _POWERUPS_H_

void powerup_init(uint32_t x, uint32_t y, uint8_t type, powerup_t *powerups);
void powerup_render(powerup_t *powerups);
void powerup_spawn_random(uint32_t x, uint32_t y, powerup_t *powerups, uint32_t tick);
void powerup_spawn_random_place(powerup_t *powerups, uint32_t tick);

#endif

