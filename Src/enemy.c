#include "enemy.h"

void enemy_init(enemy_t *enemy, int32_t x, int32_t y, enemyBullet_t enemyBullet) {
    enemy->x = (x << 14);
    enemy->y = (y << 14);

    enemy->direction.x = 0;
    enemy->direction.y = 0;

    enemy->hp = 20;
    enemy->alive = 1;
    enemy->clipsize = 3;
    enemy->gun = enemyBullet;
}

void enemy_update(enemy_t *enemies, uint8_t numberOfEnemies, spaceship_t sh, bullet_t *bullet){

	uint8_t i, j, k;
	for (k = 0; k < numberOfEnemies; k++) {
		if (enemies[k].alive) {
			for (i = 0; i < 3; i++) {
				for (j = 0; j < 3; j++) {
					gotoxy((enemies[k].x>>14) - 1 + i,(enemies[k].y>>14) - 1 + j);
					printf(" ");
				}
			}

			/*

			if (enemies[k].hp < 1) enemies[k].alive = 0;

			if(enemyEnemyCollision(&enemies[k], enemies, numberOfEnemies) && !enemies[k].stuck) {
				vector_t temp_dir;
				vector_init(&temp_dir);
				temp_dir.x += FIX10_DIV(((rand() % 100) << 10), (100 << 10)) << 4;
				temp_dir.y += FIX10_DIV(((rand() % 100) << 10), (100 << 10)) << 4;
				enemies[k].direction = temp_dir;
				enemies[k].stuck = 5;
			} else if (enemies[k].stuck) {
				enemies[k].x += enemies[k].direction.x;
				enemies[k].y += enemies[k].direction.y;
				enemies[k].stuck--;
			} else {
				vector_t temp_dir = coordsToVector(enemies[k].x, enemies[k].y, sh.x, sh.y);
				int32_t length = lengthOfVector(temp_dir);
				temp_dir.x = FIX10_DIV((temp_dir.x >> 4), (length >> 4)) << 4;
				temp_dir.y = FIX10_DIV((temp_dir.y >> 4), (length >> 4)) << 4;
				enemies[k].direction = temp_dir;

				if(spaceshipEnemyCollision(enemies[k], sh)) {
					enemies[k].x -= enemies[k].direction.x;
					enemies[k].y -= enemies[k].direction.y;
				} else {
				enemies[k].x += enemies[k].direction.x;
				enemies[k].y += enemies[k].direction.y;
				}
			}
			gotoxy(1,k + 1);
			printf("%d", enemies[k].stuck);

			*/
			if (enemies[k].hp < 1) enemies[k].alive = 0;

			vector_t temp_dir = coordsToVector(enemies[k].x, enemies[k].y, sh.x, sh.y);
			int32_t length = lengthOfVector(temp_dir);
			temp_dir.x = FIX10_DIV((temp_dir.x >> 4), (length >> 4)) << 4;
			temp_dir.y = FIX10_DIV((temp_dir.y >> 4), (length >> 4)) << 4;
			/*
			if(enemyEnemyCollision(&enemies[k], enemies, numberOfEnemies)) {
				rotateVector(&temp_dir, 256);
			}
			*/
			enemies[k].direction = temp_dir;
			if(spaceshipEnemyCollision(enemies[k], sh) || enemyBoundsCheck(enemies[k])) {
				enemies[k].x -= enemies[k].direction.x;
				enemies[k].y -= enemies[k].direction.y;
				//temp_dir.x = FIX10_DIV((temp_dir.x >> 4), (length >> 4)) << 4;
				//temp_dir.y = FIX10_DIV((temp_dir.y >> 4), (length >> 4)) << 4;
			} else {
			enemies[k].x += enemies[k].direction.x;
			enemies[k].y += enemies[k].direction.y;
			}
		}
	}
}

void enemy_render(enemy_t *enemies, uint8_t numberOfEnemies) {

	int i, j, k;
	char face[3][3] = {{218, 196, 191},
						{179, 'O' , 179},
						{192, 196, 217}
										};
	for (k = 0; k < numberOfEnemies; k++) {
		if (enemies[k].alive != 0) {
			if(enemies[k].hp <= 20 && enemies[k].hp > 10) fgcolor(2);
			if(enemies[k].hp <= 10 && enemies[k].hp > 0) fgcolor(1);
			for (i = 0; i < 3; i++) {
				for (j = 0; j < 3; j++) {
					gotoxy((enemies[k].x>>14) - 1 + i,(enemies[k].y>>14) - 1 + j);
					printf("%c", face[j][i]);

				}
			}
		}
	}
	fgcolor(15);
}

/*
void fillEnemiesArray(enemy_t *enemies, uint8_t n) {
	uint32_t maxX = 200, maxY = 40;
	uint8_t i;
	for (i = 0; i < n; i++) {
		enemyBullet_t enemyBullet[enemies[i].clipsize]; // set clipsize
		    for (i = 0; i < enemies[i].clipsize; i++) {
		        enemyBullet[i].alive = 0;
		    }
		enemy_t e;
		enemy_init(&e, 2 + (rand() % maxX), 2 + (rand() % maxY), enemyBullet);
		enemies[i] = e;
	}
	gotoxy(5,5);
	printf("fillEnemiesArray()");
}
*/
uint8_t spaceshipEnemyCollision(enemy_t enemy, spaceship_t sh) {
	uint8_t message;
	message = MAX((enemy.x >> 14), (sh.x >> 14)) - MIN((enemy.x >> 14), (sh.x >> 14)) <= 10 &&
		MAX((enemy.y >> 14), (sh.y >> 14)) - MIN((enemy.y >> 14), (sh.y >> 14)) <= 10;

	return message;
}

uint8_t bulletEnemyCollision2(enemy_t *enemy, bullet_t bullet) {
	uint8_t message;
	message = MAX((enemy->x >> 14), (bullet.x >> 14)) - MIN((enemy->x >> 14), (bullet.x >> 14)) <= 1 &&
					MAX((enemy->y >> 14), (bullet.y >> 14)) - MIN((enemy->y >> 14), (bullet.y >> 14)) <= 1;

	if (message) {
		enemy->hp--;
	}
	return message;
}

uint8_t enemyEnemyCollision(enemy_t *enemy, enemy_t *enemies, int8_t numberOfEnemies) {
	uint8_t k, count = 0;
	for(k = 0; k < numberOfEnemies; k++) {
		if(enemies[k].alive) {
			if(MAX((enemy->x >> 14), (enemies[k].x >> 14)) - MIN((enemy->x >> 14), (enemies[k].x >> 14)) <= 6 &&
					MAX((enemy->y >> 14), (enemies[k].y >> 14)) - MIN((enemy->y >> 14), (enemies[k].y >> 14)) <= 6) {
				count++;
			}
		}
	}
	return count > 1;
}


/*
uint8_t bulletEnemyCollision(enemy_t *enemy, bullet_t *bullet, spaceship_t sh) {
	uint8_t i, message;
	for (i = 0; i < sh.clipsize; i++) {
		if (bullet[i].alive) {
			message = MAX((enemy->x >> 14), (bullet[i].x >> 14)) - MIN((enemy->x >> 14), (bullet[i].x >> 14)) <= 3 &&
				MAX((enemy->y >> 14), (bullet[i].y >> 14)) - MIN((enemy->y >> 14), (bullet[i].y >> 14)) <= 3;
			if (message) {
				enemy->hp--;
				break;
			}
		}
	}
	return message;
}
*/

uint8_t enemyBoundsCheck(enemy_t enemy) {
	uint16_t maxX = 200, maxY = 50;
	return (enemy.x >> 14) > maxX || (enemy.y >> 14) > maxY || (enemy.x >> 14) < 0 || (enemy.y >> 14) < 0;
}

/*
void bulletEnemy_init(enemy_t *enemy) {
    uint8_t i, str = 0;
    for(i = 0; i < enemy->clipsize; i++) { // find number of bullets in array
        if(enemy->enemyBullet[i].alive == 0) break;
        str++;
    }

    if(str <= enemy->clipsize) {
        enemy->enemyBullet[str].alive = 1;

        enemy->enemyBullet[str].x =  enemy->x;
        enemy->enemyBullet[str].y = enemy->y;

        enemy->enemyBullet[str].direction = enemy->direction;
        //bullet[str+1].bullet_type = sh.bullet_type;
    }
}

void bulletEnemy_update(enemy_t *enemies, uint8_t numberOfEnemies) {
    uint8_t i, k;

    for (k = 0; k < numberOfEnemies; k++) {
    	for(i = 0; i < enemies[k].clipsize; i++) {
			if (enemies[k].enemyBullet[i].alive == 0) break;

			gotoxy(enemies[k].enemyBullet[i].x >> 14, enemies[k].enemyBullet[i].y >> 14);
			printf(" ");

			enemies[k].enemyBullet[i].x += enemies[k].enemyBullet[i].direction.x;
			enemies[k].enemyBullet[i].y += enemies[k].enemyBullet[i].direction.y;

			gotoxy(enemies[k].enemyBullet[i].x >> 14, enemies[k].enemyBullet[i].y >> 14);
			printf("o");
    	}
    }
}
*/

void bulletEnemy_init(enemy_t *enemy) {
	enemy->gun.x = enemy->x;
	enemy->gun.y = enemy->y;
	enemy->gun.direction = rotateVector2(enemy->direction, 8 - rand() % 16);
	enemy->gun.alive = 1;
}

void bulletEnemy_update(enemy_t *enemies, uint8_t numEnemies, spaceship_t *sh) {
	uint8_t i;
	for (i = 0; i < numEnemies; i++) {
		if (enemies[i].gun.alive) {
			gotoxy(enemies[i].gun.x >> 14, enemies[i].gun.y >> 14);
			printf(" ");

			enemies[i].gun.x += enemies[i].gun.direction.x;
			enemies[i].gun.y += enemies[i].gun.direction.y;

			if (enemyBullet_boundsCheck(enemies[i].gun) || playerHit(enemies[i].gun, sh)) {
				gotoxy(enemies[i].gun.x >> 14, enemies[i].gun.y >> 14);
				printf(" ");
				enemies[i].gun.alive = 0;
			} else {
				gotoxy(enemies[i].gun.x >> 14, enemies[i].gun.y >> 14);
				printf("o");
			}

		}
	}
}

/*
void bulletEnemyClip_init(enemy_t *enemy) {
    uint8_t i, str = 0;
    for(i = 0; i < enemy->clipsize; i++) { // find number of bullets in array
        if(enemy->enemyBullet[i].alive != 0) str++;
    }

    if(str < enemy->clipsize) {
    	enemy->enemyBullet[str].alive = 1;

    	enemy->enemyBullet[str].x =  enemy->x;
    	enemy->enemyBullet[str].y = enemy->y;

    	enemy->enemyBullet[str].direction = enemy->direction;
        //bullet[str+1].bullet_type = sh.bullet_type;
    }
}

void bulletEnemyClip_update(enemy_t *enemies, uint8_t numberOfEnemies, spaceship_t *sh) {
    uint8_t i, k;

    for (k = 0; k < numberOfEnemies; k++) {
    	for(i = 0; i < enemies[k].clipsize; i++) {
			if (enemies[k].enemyBullet[i].alive) {
				gotoxy(enemies[k].enemyBullet[i].x >> 14, enemies[k].enemyBullet[i].y >> 14);
				printf(" ");

				enemies[k].enemyBullet[i].x += enemies[k].enemyBullet[i].direction.x;
				enemies[k].enemyBullet[i].y += enemies[k].enemyBullet[i].direction.y;

				if (enemyBullet_boundsCheck(enemies[k].enemyBullet[i]) || playerHit(enemies[k].enemyBullet[i], sh)) {
					gotoxy(enemies[k].enemyBullet[i].x >> 14, enemies[k].enemyBullet[i].y >> 14);
					printf(" ");
					enemies[k].enemyBullet[i].alive = 0;
				} else {
					gotoxy(enemies[k].enemyBullet[i].x >> 14, enemies[k].enemyBullet[i].y >> 14);
					printf("o");
				}
			}
		}
    }
}
*/
uint8_t enemyBullet_boundsCheck(enemyBullet_t bullet) {
	return (bullet.x >> 14) > 200 || (bullet.y >> 14) > 40 || (bullet.x >> 14) < 0 || (bullet.y >> 14) < 0;
}

uint8_t playerHit(enemyBullet_t bullet, spaceship_t *sh) {
	uint8_t message;
	message = MAX((sh->x >> 14), (bullet.x >> 14)) - MIN((sh->x >> 14), (bullet.x >> 14)) <= 1 &&
					MAX((sh->y >> 14), (bullet.y >> 14)) - MIN((sh->y >> 14), (bullet.y >> 14)) <= 1;

	if (message) {
		sh->hp--;
	}
	return message;
}
