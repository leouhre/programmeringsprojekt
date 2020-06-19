#include "lcd_display.h"

void lcd_player_hp_update(uint8_t hp, uint8_t maxHp, uint8_t *buffer) {
    uint8_t i, j;
	for(i = 0; i < maxHp; i++) {
        for(j = 0; j < 7; j++) { // this loop is for each individual character
            if(i < hp) {
                buffer[i*8+j] = full_heart[j];
            } else {
                buffer[i*8+j] = empty_heart[j];
            }
        }
	}
}

void lcd_player_score_update(uint32_t score, uint8_t *buffer) {
    uint8_t i, j, pos = 0;
    char scoreBuffer [10];
    char printScore [7] = {'S', 'C', 'O', 'R', 'E', ':'};

    sprintf(scoreBuffer,"%d",score);  // convert score to integer
    fflush(stdout);

    for(i = 0; i < strlen(printScore); i++) { //print "SCORE:"
        for(j = 0; j < 5; j++) {
            buffer[128-strlen(scoreBuffer)*6-6*6+j+i*6] = character_data[printScore[i] - 0x20][j];
        }
    }

	for(i = 0; i < strlen(scoreBuffer); i++) { //print score
		for(j = 0; j < 5; j++) {
			buffer[128-strlen(scoreBuffer)*6 + i*6 + j] = character_data[scoreBuffer[i] - 0x20][j];
		}
	}
}

void lcd_weapons_draw(uint8_t *buffer) {
    uint8_t i, j;

    for(i = 0; i < 21; i++) { //print standard gun
        for(j = 0; j < 2; j++) {
            buffer[256+j*128+32-21+i] = standard_gun[i][j];
        }
    }

    for(i = 0; i < 31; i++) { //print missile
        for(j = 0; j < 2; j++) {
            buffer[256+j*128+64-31/2+i] = missile[i][j];
        }
    }

    for(i = 0; i < 36; i++) { //print nuke
        for(j = 0; j < 2; j++) {
            buffer[256+j*128+128-35+i-4] = nuke[i][j];
        }
    }

}

void lcd_weapons_select(uint8_t bulletType, uint8_t *buffer) {
    uint8_t i, j, k;

    for(k = 0; k < 3; k++) {  // remove marking
        buffer[256+k*128/3] &= ~0xFF;
        buffer[256+128+k*128/3] &= ~0xFF;
        for(i = 0; i < 128/3; i++) {
            for(j = 0; j < 2; j++) {
                buffer[256+j*128+i+k*128/3] &= ~(0x01 << j*7);
            }
        }
        buffer[256+128/3+k*128/3] &= ~0xFF;
        buffer[256+128+128/3+k*128/3] &= ~0xFF;
    }

    buffer[256+bulletType*128/3] |= 0xFF; // mark the equipped weapon
    buffer[256+128+bulletType*128/3] |= 0xFF;
    for(i = 0; i < 128/3; i++) {
        for(j = 0; j < 2; j++) {
            buffer[256+j*128+i+bulletType*128/3] |= 0x01 << j*7;
        }
    }
    buffer[256+128/3+bulletType*128/3] |= 0xFF;
    buffer[256+128+128/3+bulletType*128/3] |= 0xFF;
}
