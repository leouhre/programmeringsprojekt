#include "bullet.h"


void bullet_init(bullet_t *bullet, spaceship_t sh) {
    uint8_t i, str = 0;
    for(i = 0; i < sh.clipsize; i++) { // find number of bullets in array
        if(bullet[i].alive == 0) break;
        str++;
    }

    if(str <= sh.clipsize) {
        bullet[str].alive = 1;

        bullet[str].x =  sh.x;
        bullet[str].y = sh.y;

        bullet[str].angle = sh.aim;
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


void bullet_update(bullet_t *bullet, spaceship_t sh, enemy_t *enemies, uint8_t numberOfEnemies) {
    uint8_t i, j, k;

    for(i = 0; i < sh.clipsize; i++) {
        if (bullet[i].alive == 0) break;

        gotoxy(bullet[i].x >> 14, bullet[i].y >> 14);
        printf(" ");

        bullet[i].x += calccos(bullet[i].angle);
        bullet[i].y += calcsin(bullet[i].angle);

        for(k = 0; k < numberOfEnemies; k++) {
        	if(boundsCheck(bullet[i]) || (enemies[k].alive != 0 && bulletEnemyCollision2(&enemies[k], bullet[i]))) {
				bullet[i].alive = 0;
				for(j = i; j < sh.clipsize-1; j++) {
					bullet[j] = bullet[j+1];
				}
				bullet[sh.clipsize-1].alive = 0;
				//i--;
			} else {
				gotoxy(bullet[i].x >> 14, bullet[i].y >> 14);
				printf("o");
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
	return (bullet.x >> 14) > 150 || (bullet.y >> 14) > 40 || (bullet.x >> 14) < 0 || (bullet.y >> 14) < 0;
}

void bullet_render(bullet_t bullet) {
	gotoxy(bullet.x >> 14, bullet.y >> 14);
	printf("-");
}
