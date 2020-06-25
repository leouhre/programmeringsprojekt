#include "enemy.h"

void enemy_init(enemy_t *enemy, int32_t x, int32_t y, enemyBullet_t enemyBullet[CLIP_SIZE], uint8_t hp) {
	//initializes an enemy according to level difficulty
	uint8_t i;
    enemy->x = (x << 14);
    enemy->y = (y << 14);

    enemy->direction.x = 0;
    enemy->direction.y = 0;

    enemy->hp = hp;
    enemy->alive = 1;
    enemy->gun = enemyBullet;
    for(i=0; i < CLIP_SIZE; i++) {
        enemy->gun[i].alive= 0;
    }

    enemy->stuck = 0;
}

void enemy_update(enemy_t *enemies, uint8_t numberOfEnemies, spaceship_t *sh, bullet_t *bullet, uint8_t maxHp, powerup_t *powerups, uint32_t tick){
	//updates every enemy i the 'enemies' array
	uint8_t i, j, k;
	for (k = 0; k < numberOfEnemies; k++) {
		if (enemies[k].alive) {
			for (i = 0; i < 3; i++) { //removes previous render
				for (j = 0; j < 3; j++) {
					gotoxy((enemies[k].x>>14) - 1 + i,(enemies[k].y>>14) - 1 + j);
					printf(" ");
				}
			}

			if (enemies[k].hp < 1) {	//Dead enemies enter the if-statement one time to remove their 'corpse'.
				enemies[k].alive = 0; 	//Health points are decreased in bulletEnemy_update() to avoid 'killing'
				sh->score += 100;		//the bullet before hp is decreased. Score is increased when an enemy is killed.
                if(tick % 9 == 1){      //Chance to spawn a powerup
                    powerup_spawn_random((enemies[k].x >> 14), (enemies[k].y >> 14), powerups, tick);
                }
			}

			if(enemyEnemyCollision(&enemies[k], k, enemies, numberOfEnemies) && !enemyBoundsCheck(enemies[k])) {
				//'Stucks' current enemy if two enemies are too close to each other. New direction is given in enemyEnemyCollision().
				enemies[k].x += enemies[k].direction.x;
				enemies[k].y += enemies[k].direction.y;
			} else if (enemies[k].stuck && !enemyBoundsCheck(enemies[k])) {		//A stuck enemy continues in the given 'stuck' direction
				enemies[k].x += enemies[k].direction.x;							//except if out of bounds.
				enemies[k].y += enemies[k].direction.y;
				enemies[k].stuck--;
			} else {	//The enemy is given the direction of the spaceship as a unity vector.
				enemies[k].stuck = 0;
				vector_t temp_dir = coordsToVector(enemies[k].x, enemies[k].y, sh->x, sh->y);
				int32_t length = lengthOfVector(temp_dir);
				temp_dir.x = FIX10_DIV((temp_dir.x >> 4), (length >> 4)) << 4;
				temp_dir.y = FIX10_DIV((temp_dir.y >> 4), (length >> 4)) << 4;
				enemies[k].direction = temp_dir;

				if(spaceshipEnemyCollision(enemies[k], sh)) {	//Keeps the enemy at a distance of the spaceship.
					enemies[k].x -= enemies[k].direction.x;
					enemies[k].y -= enemies[k].direction.y;
				} else {
				enemies[k].x += enemies[k].direction.x;
				enemies[k].y += enemies[k].direction.y;
				}
			}
			if (enemies[k].alive) enemy_render(enemies[k], maxHp); //Enemy might be dead
		}
	}
}

void enemy_render(enemy_t enemy, uint8_t maxHp) {
	int i, j;

	char sprite[3][3] = {	{218, 196, 191},
							{179, 'O', 179},
							{192, 196, 217} };

	if(enemy.hp <= maxHp && enemy.hp > 2*maxHp/3) fgcolor(2); //green
	if(enemy.hp <= 2*maxHp/3 && enemy.hp > maxHp/3) fgcolor(5); //purple
	if(enemy.hp <= maxHp/3 && enemy.hp > 0) fgcolor(1); //red
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			gotoxy((enemy.x>>14) - 1 + i,(enemy.y>>14) - 1 + j);
			printf("%c", sprite[j][i]);
		}
	}
	fgcolor(15);
}

uint8_t spaceshipEnemyCollision(enemy_t enemy, spaceship_t *sh) {
	//returns true if spaceship and enemy distance is 10 'pixels' or less
	uint8_t message;
	message = MAX((enemy.x >> 14), (sh->x >> 14)) - MIN((enemy.x >> 14), (sh->x >> 14)) <= 10 &&
		MAX((enemy.y >> 14), (sh->y >> 14)) - MIN((enemy.y >> 14), (sh->y >> 14)) <= 10;

	return message;
}

uint8_t bulletEnemyCollision(enemy_t *enemy, bullet_t bullet, spaceship_t *sh) {
	//returns true if bullet hits the enemy, decreasing enemy hp by 1.
	uint8_t message;
	message = MAX((enemy->x >> 14), (bullet.x >> 14)) - MIN((enemy->x >> 14), (bullet.x >> 14)) <= 1 &&
					MAX((enemy->y >> 14), (bullet.y >> 14)) - MIN((enemy->y >> 14), (bullet.y >> 14)) <= 1;

	if (message) {
		enemy->hp--; //Enemy hp decreasing is done here to avoid confusion when updating bullets and enemies at different paces.
		sh->score += 10;
	}
	return message;
}

uint8_t enemyEnemyCollision(enemy_t *enemy, uint8_t n, enemy_t *enemies, int8_t numberOfEnemies) {
	//Returns true if two enemies are 9 'pixels' or closer to each other. Also changes the direction of the current enemy.
	uint8_t k, cnt = 0;
	for(k = 0; k < numberOfEnemies; k++) {
		if(k != n && enemies[k].alive && !enemies[k].stuck) {
			if(MAX((enemy->x >> 14), (enemies[k].x >> 14)) - MIN((enemy->x >> 14), (enemies[k].x >> 14)) <= 9 &&
					MAX((enemy->y >> 14), (enemies[k].y >> 14)) - MIN((enemy->y >> 14), (enemies[k].y >> 14)) <= 9) {
				enemy->direction = rotate_vector2(enemies[k].direction, 512/8); 	//Current enemy gets stuck for 5 updates to move away from
				enemy->stuck = 5;													//the other enemy close by
				cnt++;
			}
		}
	}
	return cnt > 0;
}

uint8_t enemyBoundsCheck(enemy_t enemy) {
	//returns true if the enemy is out of bounds.
	return (enemy.x >> 14) > SCREEN_WIDTH - 25 || (enemy.y >> 14) > SCREEN_HEIGHT - 15 || (enemy.x >> 14) < 25 || (enemy.y >> 14) < 15;
}

void bulletEnemy_init(enemy_t *enemy) {
	//initializes an enemy's bullet
    uint8_t i;
    for(i = 0; i < CLIP_SIZE; i++) { // finds an empty space in array of bullets
        if(!enemy->gun[i].alive){
            enemy->gun[i].alive = 1;

            enemy->gun[i].x =  enemy->x;
            enemy->gun[i].y = enemy->y;

            enemy->gun[i].direction = rotate_vector2(enemy->direction, 8 - rand() % (512/32));
            //adds a pseudo random 32nd of a circle angle to the enemy bullet
            return;
        }

    }
}

void bulletEnemy_update(enemy_t *enemies, uint8_t numberOfEnemies, spaceship_t *sh) {
	//moves the enemy's bullet forward and checks for hits.
    uint8_t i, j;
    for (i = 0; i < numberOfEnemies; i++) {
    	for(j = 0; j < CLIP_SIZE; j++) {
			if (enemies[i].gun[j].alive) {
				gotoxy((enemies[i].gun[j].x >> 14), (enemies[i].gun[j].y >> 14));
				printf(" ");

				enemies[i].gun[j].x += enemies[i].gun[j].direction.x;
				enemies[i].gun[j].y += enemies[i].gun[j].direction.y;

				if (bulletEnemy_boundsCheck(enemies[i].gun[j]) || playerHit(enemies[i].gun[j], sh)) {
					// OBS! Player hp is decreased in the playerHit() function
					enemies[i].gun[j].alive = 0;
				} else {
					gotoxy(enemies[i].gun[j].x >> 14, enemies[i].gun[j].y >> 14);
					printf("o");
				}
			}
		}
    }
}

uint8_t bulletEnemy_boundsCheck(enemyBullet_t bullet) {
	//returns true if bullet leaves the area.
	return (bullet.x >> 14) > SCREEN_WIDTH - 3 || (bullet.y >> 14) > SCREEN_HEIGHT - 3 || (bullet.x >> 14) < 3|| (bullet.y >> 14) < 3;
}

uint8_t playerHit(enemyBullet_t bullet, spaceship_t *sh) {
	//returns true if the player is hit by an enemy's bullet. Also decreases the player's hp to avoid confusion when 'killing' the bullet.
	uint8_t message;
	message = MAX((sh->x >> 14), (bullet.x >> 14)) - MIN((sh->x >> 14), (bullet.x >> 14)) <= 1 &&
					MAX((sh->y >> 14), (bullet.y >> 14)) - MIN((sh->y >> 14), (bullet.y >> 14)) <= 1;

	if (message) {
		sh->hp--; //player hp is decreased here.
	}
	return message;
}
