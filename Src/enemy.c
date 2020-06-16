#include "enemy.h"



void enemy_init(enemy_t *enemy, spaceship_t sh, int32_t x, int32_t y){
    enemy->x=x;
    enemy->y=y;

    enemy->x <<= 14;
    enemy->y <<= 14;


    enemy->direction.x = 0;
    enemy->direction.y = 0;
}

void enemy_update(enemy_t *enemy, spaceship_t sh){
	vector_t temp_dir = coordsToVector(enemy->x, enemy->y, sh.x, sh.y);
    int32_t length = lengthOfVector(temp_dir);

    temp_dir.x = FIX10_DIV((temp_dir.x >> 4), (length >> 4)) << 4;
    temp_dir.y = FIX10_DIV((temp_dir.y >> 4), (length >> 4)) << 4;

    enemy->direction = temp_dir;

    enemy->x += enemy->direction.x;
    enemy->y += enemy->direction.y;
}

void enemy_render(enemy_t e) {
	gotoxy(e.x>>14,e.y>>14);
	printf("O");
}
