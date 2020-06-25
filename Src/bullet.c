#include "bullet.h"

void bullet_init(bullet_t *bullet, spaceship_t sh) {
    uint8_t i;
    for (i = 0; i < CLIP_SIZE; i++) {
    	if (!bullet[i].alive) {
    		bullet[i].x = sh.x;
			bullet[i].y = sh.y;
    		bullet[i].angle = sh.aim;
    		bullet[i].alive = 1;
    		break;
		}
	}
}

void bullet_update(bullet_t *bullet, spaceship_t *sh, enemy_t *enemies, uint8_t numberOfEnemies) {
    uint8_t i, k;

    for(i = 0; i < CLIP_SIZE; i++) {
        if (bullet[i].alive) {
        	gotoxy(bullet[i].x >> 14, bullet[i].y >> 14);
			printf(" ");

			bullet[i].x += calccos(bullet[i].angle);
			bullet[i].y += calcsin(bullet[i].angle);

			for(k = 0; k < numberOfEnemies; k++) {
				if(boundsCheck(bullet[i]) || (enemies[k].alive && bulletEnemyCollision(&enemies[k], bullet[i], sh))) {
					bullet[i].alive = 0;
					gotoxy(bullet[i].x >> 14, bullet[i].y >> 14);
					printf(" ");
					return;
				}
			}
			gotoxy(bullet[i].x >> 14, bullet[i].y >> 14);
			printf("o");
        }
    }
}


uint8_t boundsCheck(bullet_t bullet) {
	return (bullet.x >> 14) > SCREEN_WIDTH - 3 || (bullet.y >> 14) > SCREEN_HEIGHT - 3 || (bullet.x >> 14) < 3 || (bullet.y >> 14) < 3;
}

/*
void bullet_init(bullet_t *bullet, spaceship_t sh) { //creates a bullet and places it into an empty space in the bullet array
    uint8_t i, pos = 0;
    for(i = 0; i < CLIP_SIZE; i++) { // find number of bullets in array
        if(!bullet[i].alive) break;
        pos++;
    }

    if(pos < CLIP_SIZE) { // stop creating bullets when the array is full
        bullet[pos].alive = 1;

        bullet[pos].x =  sh.x;
        bullet[pos].y = sh.y;

        bullet[pos].angle = sh.aim;
    }
}
*/



/*
void bullet_update(bullet_t *bullet, spaceship_t *sh, enemy_t *enemies, uint8_t numberOfEnemies) {
	//deletes all each bullet, moves them, and prints them unless they hit an enemy or is out of bounds
    uint8_t i, j, k;

    for(i = 0; i < CLIP_SIZE; i++) {
        if (bullet[i].alive) {
        	gotoxy(bullet[i].x >> 14, bullet[i].y >> 14);
			printf(" "); //deletes bullet

			bullet[i].x += calccos(bullet[i].angle);
			bullet[i].y += calcsin(bullet[i].angle);

			gotoxy(bullet[i].x >> 14, bullet[i].y >> 14);
			printf("o"); //reprints bullet

			for(k = 0; k < numberOfEnemies; k++) {
				if(boundsCheck(bullet[i]) || (enemies[k].alive && bulletEnemyCollision(&enemies[k], bullet[i], sh))) {
					bullet[i].alive = 0;
					for(j = i; j < CLIP_SIZE - 1; j++) {
						bullet[j] = bullet[j+1];
					}
					bullet[CLIP_SIZE - 1].alive = 0;
					//i--;
				}
			}
        }
    }
}
*/
