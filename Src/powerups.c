#include "powerups.h"

void powerup_init(uint32_t x, uint32_t y, uint8_t type, powerup_t *powerups){ //initialisere poweruppen
    uint8_t i, pos = 0;
    for(i = 0; i < 5; i++) { //finds a empty place in the array if available
        if(powerups[i].alive == 0) break;
        pos++;
    }

    if(pos < 5) {
        powerups[pos].alive = 1;
        powerups[pos].x = (x << 14);
        powerups[pos].y = (y << 14);
        powerups[pos].type = type;
    }
}

void powerup_render(powerup_t *powerups, spaceship_t *sh) { //draws the powerup in putty depending on collision
    char missleArray[6] = {'>','=','=','x','>'};
    char nukeArray[9] = {'|','|','=','(','0','0','0',')'};
    char deleteArray[9] = {' ',' ',' ',' ',' ',' ',' ',' '};
    uint8_t i;
    for(i = 0; i < 5; i++) {
        if(powerups[i].alive == 1) { // only draw existing powerups
            if(!playerPowerupCollision(powerups[i], sh)) {
                switch(powerups[i].type) {
                    case 1: //draw missile
                        gotoxy((powerups[i].x >> 14) - 2, (powerups[i].y >> 14));
                        printf("%s", missleArray);
                        break;

                    case 2: //draw nuke
                        gotoxy((powerups[i].x >> 14) - 3, (powerups[i].y >> 14));
                        printf("%s", nukeArray);
                        break;
                    }
                } else {
                    powerups[i].alive = 0;
                    switch(powerups[i].type) {
                    case 1: //erase missile
                        gotoxy((powerups[i].x >> 14) - 3, (powerups[i].y >> 14));
                        printf("%s", deleteArray);
                        break;

                    case 2: //erase nuke
                        gotoxy((powerups[i].x >> 14) - 3, (powerups[i].y >> 14));
                        printf("%s", deleteArray);
                        break;
                }
            }
        }
    }
}

void powerup_spawn_random(uint32_t x, uint32_t y,powerup_t *powerups, uint32_t tick){//spawn a random weapon
    uint8_t type;
    if(tick%10 > 3) { //this decides the chance. when called with tick%24 == 1 and 9% == 1 this becomes 3/5 for missile and 2/5 for nuke
        type = 1; //missile
    } else {
        type = 2; //nuke
    }
    powerup_init(x, y, type, powerups);
}


uint8_t playerPowerupCollision(powerup_t powerup, spaceship_t *sh) {
	//returns true if player is on top of a powerup, also changed player bullet type and increases score.
	uint8_t message;
	message = MAX((sh->x >> 14), (powerup.x >> 14)) - MIN((sh->x >> 14), (powerup.x >> 14)) <= 5 &&
					MAX((sh->y >> 14), (powerup.y >> 14)) - MIN((sh->y >> 14), (powerup.y >> 14)) <= 5;

	if (message) {
		sh->bullet_type = powerup.type; //bullet type on spaceship is changed to the type of powerup
		sh->score += 2;
	}
	return message;
}
