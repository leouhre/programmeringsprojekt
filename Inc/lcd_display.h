#include <stdio.h> // Whatever needs to be included
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "entity_structs.h"
#include "30010_io.h"
#include "charset.h"

#ifndef _LCD_DISPLAY_H_
#define _LCD_DISPLAY_H_

void lcd_player_hp_update(spaceship_t sh, uint8_t *buffer);
void lcd_player_score_update(spaceship_t sh, uint8_t *buffer);
void lcd_weapons_draw(uint8_t *buffer);
void lcd_weapons_select(spaceship_t sh, uint8_t *buffer);

#endif

