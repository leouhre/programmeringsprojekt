#include <stdint.h>
#include "math.h"

#ifndef _ENTITY_STRUCTS_H_
#define _ENTITY_STRUCTS_H_

typedef struct {
    uint8_t difficulty, mode, currentScore, currentLevel, status;
} gameHandler_t;



typedef struct {

    int32_t x, y, angle, hp, aim, score;
    uint8_t bullet_type;

    //vector_t direction;
    //future updates;
    /*
    int32_t dmg, spd, sht_spd, acceleration, bullet style
    */
} spaceship_t;

typedef struct {
    int32_t x, y;
    uint8_t bullet_type, alive;
    vector_t direction;

} enemyBullet_t;

typedef struct {
    int32_t x, y, hp;
    uint8_t alive, stuck;
    vector_t direction;
    enemyBullet_t *gun;
    //future updates;
    /*
    int32_t dmg, spd, sht_spd, acceleration, bullet style
    */
} enemy_t;

typedef struct {
    int32_t x, y, angle;
    uint8_t bullet_type, alive;

} bullet_t;

typedef struct {
	int32_t x, y, angle;
	uint8_t locked, alive, count, exploded;
	vector_t direction;
}homing_t;

typedef struct {
    int32_t x, y;
    uint8_t type, alive;
} powerup_t;

typedef struct {
	int32_t x, y, angle;
	uint8_t alive, count, exploded;
} nuke_t;

#endif
