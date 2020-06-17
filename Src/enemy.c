#include "enemy.h"



void enemy_init(enemy_t *enemy, int32_t x, int32_t y){
    enemy->x = (x << 14);
    enemy->y = (y << 14);

    enemy->direction.x = 0;
    enemy->direction.y = 0;

    enemy->hp = 4;
}

void enemy_update(enemy_t *enemy, spaceship_t sh){
	// Print 'O' as enemy
	/*
	gotoxy((enemy->x>>14),(enemy->y>>14));
	printf(" ");
	*/

	// Print box as enemy
	uint8_t i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			gotoxy((enemy->x>>14) - 1 + i,(enemy->y>>14) - 1 + j);
			printf(" ");

		}
	}

	vector_t temp_dir = coordsToVector(enemy->x, enemy->y, sh.x, sh.y);
    int32_t length = lengthOfVector(temp_dir);

    temp_dir.x = FIX10_DIV((temp_dir.x >> 4), (length >> 4)) << 4;
    temp_dir.y = FIX10_DIV((temp_dir.y >> 4), (length >> 4)) << 4;

    enemy->direction = temp_dir;

    enemy->x += enemy->direction.x;
    enemy->y += enemy->direction.y;

    if (spaceshipCollision(*enemy, sh)) {
    	gotoxy(1,1);
    	printf("%d", spaceshipCollision(*enemy, sh));
    }
}

void enemy_render(enemy_t e) {
	// Print 'O' as enemy
	/*
	gotoxy((e.x>>14),(e.y>>14));
	printf("O");
	*/

	// Print smiley as enemy
	/*
	int i, j;
	char face[3][5] = {{'(', '^', '.', '^', ')'},
						{' ', '/', 'A', '\\', ' '},
						{' ', '\\', 'V', '/', ' '}
												};
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 3; j++) {
			gotoxy((e.x>>14) - 2 + i,(e.y>>14) - 1 + j);
			printf("%c", face[j][i]);

		}
	}
	*/

	// Print box as enemy
	int i, j;
	char face[3][3] = {{218, 196, 191},
						{179, 0 , 179},
						{192, 196, 217}
										};
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			gotoxy((e.x>>14) - 1 + i,(e.y>>14) - 1 + j);
			printf("%c", face[j][i]);

		}
	}
}

void fillEnemiesArray(enemy_t *enemies, uint8_t n) {
	uint8_t i;
	for (i = 0; i < n; i++) {
		enemy_t e;
		enemy_init(&e, 2 + (rand() % 40), 2 + (rand() % 40));
		enemies[i] = e;
	}
}

uint8_t spaceshipCollision(enemy_t enemy, spaceship_t sh) {
	uint8_t i, j, message = 0;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			message = ((enemy.x << 14) - 1 + i == (sh.x << 14) - 1 + j);
		}
	}
	if (message) {
		for (i = 0; i < 3; i++) {
			for (j = 0; j < 3; j++) {
				message = ((enemy.y << 14) - 1 + i == (sh.y << 14) - 1 + j);
			}
		}
	}
	gotoxy(1,2);
	printf("%d", message);
	return message;
}


