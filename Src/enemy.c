#include "enemy.h"

void enemy_init(enemy_t *enemy, vector_t direction, int32_t x, int32_t y){
    enemy->x=x;
    enemy->y=y;

    enemy->x <<= 14;
    enemy->y <<= 14;

    enemy->direction=direction;
}

void enemy_update(enemy_t *enemy, spaceship_t *sh){
	//...
}
