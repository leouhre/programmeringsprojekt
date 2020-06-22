#include "bullet.h"


void bullet_init(bullet_t *bullet, spaceship_t sh) { //creates a bullet and places it into an empty space in the bullet array
    uint8_t i, pos = 0;
    for(i = 0; i < CLIP_SIZE; i++) { // find number of bullets in array
        if(bullet[i].alive == 0) break;
        pos++;
    }

    if(pos < CLIP_SIZE) { // stop creating bullets when the is full
        bullet[pos].alive = 1;

        bullet[pos].x =  sh.x;
        bullet[pos].y = sh.y;

        bullet[pos].angle = sh.aim;
        //bullet[str+1].bullet_type = sh.bullet_type;
    }
}

/*

void bullet_init(bullet_t *bullet, spaceship_t sh) {
    uint8_t i, str = 0;
    for(i = 0; i < sh.clipsize; i++) { // find number of bullets in array
        if(bullet[i].alive != 0) str++;
    }

    if(str <= sh.clipsize) {
        bullet[str].alive = 1;

        bullet[str].x =  sh.x;
        bullet[str].y = sh.y;

        bullet[str].angle = sh.angle;
        //bullet[str+1].bullet_type = sh.bullet_type;
    }
}
*/


void bullet_update(bullet_t *bullet, spaceship_t *sh, enemy_t *enemies, uint8_t numberOfEnemies) {
    uint8_t i, j, k;

    for(i = 0; i < CLIP_SIZE; i++) {
        if (bullet[i].alive) {
        	gotoxy(bullet[i].x >> 14, bullet[i].y >> 14);
			printf(" ");

			bullet[i].x += calccos(bullet[i].angle);
			bullet[i].y += calcsin(bullet[i].angle);

			for(k = 0; k < numberOfEnemies; k++) {
				if(boundsCheck(bullet[i]) || (enemies[k].alive && bulletEnemyCollision(&enemies[k], bullet[i], sh))) {
					bullet[i].alive = 0;
					for(j = i; j < CLIP_SIZE - 1; j++) {
						bullet[j] = bullet[j+1];
					}
					bullet[CLIP_SIZE - 1].alive = 0;
					//i--;
				} else {
					gotoxy(bullet[i].x >> 14, bullet[i].y >> 14);
					printf("o");
				}
			}
        }
    }
}


/*
void bullet_update(bullet_t *bullet, spaceship_t sh, enemy_t *enemies, uint8_t numberOfEnemies) {
    uint8_t i, k;

    for(i = 0; i < sh.clipsize; i++) {
        if (bullet[i].alive != 0) {
        	gotoxy(bullet[i].x >> 14, bullet[i].y >> 14);
			printf(" ");

			bullet[i].x += calccos(bullet[i].angle);
			bullet[i].y += calcsin(bullet[i].angle);

			for(k = 0; k < numberOfEnemies; k++) {
				if(boundsCheck(bullet[i]) || (enemies[k].alive != 0 && bulletEnemyCollision2(&enemies[k], bullet[i]))) {
					bullet[i].alive = 0;
				}
			}
			bullet_render(bullet[i]);
        }
    }
}
*/

uint8_t boundsCheck(bullet_t bullet) {
	return (bullet.x >> 14) > 209+1 || (bullet.y >> 14) > 54+1 || (bullet.x >> 14) < 2 || (bullet.y >> 14) < 2;
}

void bullet_render(bullet_t bullet) {
	gotoxy(bullet.x >> 14, bullet.y >> 14);
	printf("-");
}
