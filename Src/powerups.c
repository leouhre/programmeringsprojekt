#include "powerups.h"

void powerup_init(uint32_t x, uint32_t y, uint8_t type, powerup_t *powerups){ //initialisere poweruppen
    uint8_t i, str = 0;
    for(i = 0; i < 5; i++) { // find number of powerups in array
        if(powerups[i].alive == 0) break;
        str++;
    }

    if(str < 5) {
        powerups[str].alive = 1;
        powerups[str].x = x;
        powerups[str].y = y;
        powerups[str].type = type;
    }
}

void powerup_render(powerup_t *powerups){ //draws the powerup in putty
    uint8_t i;
    for(i = 0; i < 5; i++) {
        if(powerups[i].alive == 1) { // only draw existing powerups
            switch(powerups[i].type) {
                case 0:
                    break;

                case 1: //draw missile
                    gotoxy(powerups[i].x - 2, powerups[i].y);
                    printf(">");
                    gotoxy(powerups[i].x - 1, powerups[i].y);
                    printf("=");
                    gotoxy(powerups[i].x, powerups[i].y);
                    printf("=");
                    gotoxy(powerups[i].x + 1, powerups[i].y);
                    printf("x");
                    gotoxy(powerups[i].x + 2, powerups[i].y);
                    printf(">");
                    break;

                case 2: //draw nuke
                    gotoxy(powerups[i].x - 3, powerups[i].y);
                    printf("|");
                    gotoxy(powerups[i].x - 2, powerups[i].y);
                    printf("|");
                    gotoxy(powerups[i].x - 1, powerups[i].y);
                    printf("=");
                    gotoxy(powerups[i].x, powerups[i].y);
                    printf("(");
                    gotoxy(powerups[i].x + 1, powerups[i].y);
                    printf("0");
                    gotoxy(powerups[i].x + 2, powerups[i].y);
                    printf("0");
                    gotoxy(powerups[i].x + 3, powerups[i].y);
                    printf("0");
                    gotoxy(powerups[i].x + 4, powerups[i].y);
                    printf(")");
                    break;
            }
        }
    }
}

void powerup_spawn_random(uint32_t x, uint32_t y,powerup_t *powerups, uint32_t tick){//can spawn a random weapon or nothing
    powerup_init(x, y, tick%3, powerups);
                   printf("%d", tick%3);
}


void powerup_spawn_random_place(powerup_t *powerups, uint32_t tick){ //can spawn random weapon with random place factor in front of random decides window size
    powerup_init(tick%40, tick%40, rand()%3, powerups);
}

