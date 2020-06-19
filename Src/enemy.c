#include "enemy.h"

void enemy_init(enemy_t *enemy, int32_t x, int32_t y){
    enemy->x = (x << 14);
    enemy->y = (y << 14);

    enemy->direction.x = 0;
    enemy->direction.y = 0;

    enemy->hp = 20;
    enemy->alive = 1;
}

void enemy_update(enemy_t *enemies, uint8_t numberOfEnemies, spaceship_t sh, bullet_t *bullet){

	gotoxy(1,1);
	clreol();
	gotoxy(1,2);
	clreol();
	gotoxy(1,3);
	clreol();

	uint8_t i, j, k;
	for (k = 0; k < numberOfEnemies; k++) {
		if (enemies[k].alive != 0) {
			for (i = 0; i < 3; i++) {
				for (j = 0; j < 3; j++) {
					gotoxy((enemies[k].x>>14) - 1 + i,(enemies[k].y>>14) - 1 + j);
					printf(" ");
				}
			}

			if (enemies[k].hp < 1) enemies[k].alive = 0;
			vector_t temp_dir = coordsToVector(enemies[k].x, enemies[k].y, sh.x, sh.y);
			int32_t length = lengthOfVector(temp_dir);

			temp_dir.x = FIX10_DIV((temp_dir.x >> 4), (length >> 4)) << 4;
			temp_dir.y = FIX10_DIV((temp_dir.y >> 4), (length >> 4)) << 4;

			enemies[k].direction = temp_dir;

			enemies[k].x += enemies[k].direction.x;
			enemies[k].y += enemies[k].direction.y;

			/*
			if (spaceshipEnemyCollision(enemies[k], sh)) {
				gotoxy(1,1);
				printf("crash!");
			}
			if (bulletEnemyCollision(&enemies[k], bullet, sh)) {
				gotoxy(1,2);
				printf("hit!");
			}
			*/
			gotoxy(1,k + 1);
			printf("%d", enemies[k].hp);
		}
	}
}

void enemy_render(enemy_t *enemies, uint8_t numberOfEnemies) {

	int i, j, k;
	char face[3][3] = {{218, 196, 191},
						{179, 0 , 179},
						{192, 196, 217}
										};
	for (k = 0; k < numberOfEnemies; k++) {
		if (enemies[k].alive != 0) {
			for (i = 0; i < 3; i++) {
				for (j = 0; j < 3; j++) {
					gotoxy((enemies[k].x>>14) - 1 + i,(enemies[k].y>>14) - 1 + j);
					printf("%c", face[j][i]);

				}
			}
		}
	}
}

void fillEnemiesArray(enemy_t *enemies, uint8_t n) {
	uint32_t maxX = 200, maxY = 40;
	uint8_t i;
	for (i = 0; i < n; i++) {
		enemy_t e;
		enemy_init(&e, 2 + (rand() % maxX), 2 + (rand() % maxY));
		enemies[i] = e;
	}
}

uint8_t spaceshipEnemyCollision(enemy_t enemy, spaceship_t sh) {
	uint8_t message;
	message = MAX((enemy.x >> 14), (sh.x >> 14)) - MIN((enemy.x >> 14), (sh.x >> 14)) <= 3 &&
		MAX((enemy.y >> 14), (sh.y >> 14)) - MIN((enemy.y >> 14), (sh.y >> 14)) <= 3;

	return message;
}

uint8_t bulletEnemyCollision2(enemy_t *enemy, bullet_t bullet) {
	uint8_t message;
	message = MAX((enemy->x >> 14), (bullet.x >> 14)) - MIN((enemy->x >> 14), (bullet.x >> 14)) <= 3 &&
					MAX((enemy->y >> 14), (bullet.y >> 14)) - MIN((enemy->y >> 14), (bullet.y >> 14)) <= 3;

	if (message) {
		enemy->hp--;
	}
	return message;
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

