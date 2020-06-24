#include "homing.h"

void homing_init(homing_t *h, spaceship_t sh) {
	//initialize a homing missile in the spaceship aim direction
	h->x = sh.x;
	h->y = sh.y;
	h->angle = sh.aim;
	h->locked = 0;
	h->alive = 1;
	h->cnt = 30;
	h->exploded = 0;
}

void homing_update(homing_t *h, enemy_t *enemies, uint8_t numEnemies, spaceship_t *sh) {
	//update homing missile coordinates and explode if enemy is hit
	if(h->exploded > 0) { //wait some time before removing the explosion render from the screen
		h->exploded--;
		if(!h->exploded) homingExplode_render(h, 1);
		return;
	}
	if(h->alive) { //remove previous render
		gotoxy(h->x >> 14, h->y >> 14);
		printf(" ");

		if(!h->locked) { //the missile will lock on to an enemy if they are close to each other
			h->locked = homingEnemyDetection(h, enemies, numEnemies);

			h->x += calccos(h->angle); //continue in 'aim' direction if not locked on to enemy
			h->y += calcsin(h->angle);

		} else { //calculate the desired direction to the locked enemy

			vector_t temp_dir = coordsToVector(h->x, h->y, enemies[h->locked - 1].x, enemies[h->locked - 1].y);
			int32_t length = lengthOfVector(temp_dir);
			temp_dir.x = FIX10_DIV((temp_dir.x >> 4), (length >> 4)) << 4;
			temp_dir.y = FIX10_DIV((temp_dir.y >> 4), (length >> 4)) << 4;
			h->direction = temp_dir;
			h->x += FIX14_MULT((FIX8_DIV((h->cnt << 8), (30 << 8)) << 6), calccos(h->angle))			//mix old and new direction
					+ FIX14_MULT((FIX8_DIV(((30 - h->cnt) << 8), (30 << 8)) << 6), h->direction.x);	//for some time to simulate
			h->y += FIX14_MULT((FIX8_DIV((h->cnt << 8), (30 << 8)) << 6), calcsin(h->angle))			//forces in different
					+ FIX14_MULT((FIX8_DIV(((30 - h->cnt) << 8), (30 << 8)) << 6), h->direction.y);	//directions

			if (h->cnt > 0) h->cnt--;
		}
		if(homingBoundsCheck(h)) { //too bad if your missile left the battleground
			h->alive = 0;
			gotoxy(h->x >> 14, h->y >> 14);
			printf(" ");
		} else if( homingHit(h, enemies[h->locked - 1])) { //explode if enemy is hit
			h->alive = 0;
			h->exploded = 20;
			homingExplode(h, enemies, numEnemies, sh);
		} else homing_render(h);
	}
}

void homing_render(homing_t *h) {
	//draws the missile in the correct direction
	gotoxy(h->x >> 14, h->y >> 14);
	if (!h->locked) {
		fgcolor(11);
		if((h->angle & 0x1FF) > 512 - 64 || (h->angle & 0x1FF) <= 64) {
			printf(">");
		} else if((h->angle & 0x1FF) > 64 && (h->angle & 0x1FF) <= 128 + 64) {
			printf("v");
		} else if((h->angle & 0x1FF) > 128 + 64 && (h->angle & 0x1FF) <= 256 + 64) {
			printf("<");
		} else {
			printf("^");
		}
	} else { //when locked on to an enemy the missile is a green cross
		fgcolor(2); //green
		printf("+");
	}
	fgcolor(15); //white
}

uint8_t homingEnemyDetection(homing_t *h, enemy_t *enemies, uint8_t numEnemies) {
	//detects if the homing missile should lock on to any enemies
	uint8_t i, j = 0;
	uint32_t length0 = 0, length1;
	vector_t temp_dir;
	for(i = 0; i < numEnemies; i++) {
		if(enemies[i].alive) {
			if(MAX((h->x >> 14), (enemies[i].x >> 14)) - MIN((h->x >> 14), (enemies[i].x >> 14)) <= HOMING_DIAMETER &&
					MAX((h->y >> 14), (enemies[i].y >> 14)) - MIN((h->y >> 14), (enemies[i].y >> 14)) <= HOMING_DIAMETER) {
				temp_dir = coordsToVector(h->x, h->y, enemies[i].x, enemies[i].y); 	//this calculation secures that the missile
				length1 = lengthOfVector(temp_dir);									//will lock on to the nearest enemy and not
				if(length1 > length0) {												//enemies[0] before enemies[1] and so on.
					length0 = length1;
					j = i + 1; //if enemies[0] we shouldn't return 0, therefore + 1
				}
			}
		}
	}
	return j;
}

uint8_t homingBoundsCheck(homing_t *h) {
	//returns true if the homing missile leaves the battleground
	return (h->x >> 14) > SCREEN_WIDTH-2 || (h->y >> 14) > SCREEN_HEIGHT-2|| (h->x >> 14) < 3 || (h->y >> 14) < 3;
}

uint8_t homingHit(homing_t *h, enemy_t e) {
	//returns true if an enemy is hit
	return MAX((h->x >> 14), (e.x >> 14)) - MIN((h->x >> 14), (e.x >> 14)) <= 1 &&
		MAX((h->y >> 14), (e.y >> 14)) - MIN((h->y >> 14), (e.y >> 14)) <= 1;
}

void homingExplode(homing_t *h, enemy_t *enemies, uint8_t numEnemies, spaceship_t *sh) {
	//decreases enemy hp and adds to player score if an enemy is hit by the missiles hit ratio
	uint8_t i;
	for (i = 0; i < numEnemies; i++) {
		if(enemies[i].alive) {
			if(MAX((h->x >> 14), (enemies[i].x >> 14)) - MIN((h->x >> 14), (enemies[i].x >> 14)) <= HOMING_DIAMETER &&
					MAX((h->y >> 14), (enemies[i].y >> 14)) - MIN((h->y >> 14), (enemies[i].y >> 14)) <= HOMING_DIAMETER) {
				enemies[i].hp -= 10;
				sh->score += 20;
			}
		}
	}
	homingExplode_render(h, 0);
}

void homingExplode_render(homing_t *h, uint8_t rm) {
	//draws the explosion or removes it
	uint8_t i, j;
	for (i = 0; i < HOMING_DIAMETER; i++) {
		for (j = 0; j < HOMING_DIAMETER; j++) {
			gotoxy((h->x >> 14) - HOMING_DIAMETER/2 + i, (h->y >> 14) - HOMING_DIAMETER/2 + j);
			if (!rm) printf("x");
			else printf(" ");
		}
	}
}
