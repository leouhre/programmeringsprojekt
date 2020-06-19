#include <stdio.h> // Whatever needs to be included
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "spaceship.h"
#include "30010_io.h"
#include "charset.h"

#ifndef _LCD_DISPLAY_H_
#define _LCD_DISPLAY_H_

void lcd_player_hp_update(uint8_t hp, uint8_t maxHp, uint8_t *buffer);
void lcd_player_score_update(uint32_t score, uint8_t *buffer);
void lcd_weapons_draw(uint8_t *buffer);
void lcd_weapons_select(uint8_t bulletType, uint8_t *buffer);

#endif

