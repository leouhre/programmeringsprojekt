#include "homing.h"

void homing_init(homing_t *h, spaceship_t sh) {
	h->x = sh.x;
	h->y = sh.y;
	h->angle = sh.aim;
	h->locked = 0;
	h->alive = 1;
	h->count = 30;
	h->exploded = 0;
}

void homing_update(homing_t *h, enemy_t *enemies, uint8_t numEnemies) {
	if(h->exploded > 0) {
		h->exploded--;
		if(!h->exploded) homingExplode_render2(h);
		return;
	}
	if(h->alive) {
		gotoxy(h->x >> 14, h->y >> 14);
		printf(" ");

		if(!h->locked) {
			h->locked = homingEnemyDetection(h, enemies, numEnemies);

			h->x += calccos(h->angle);
			h->y += calcsin(h->angle);
		} else {
			vector_t temp_dir = coordsToVector(h->x, h->y, enemies[h->locked - 1].x, enemies[h->locked - 1].y);
			int32_t length = lengthOfVector(temp_dir);
			temp_dir.x = FIX10_DIV((temp_dir.x >> 4), (length >> 4)) << 4;
			temp_dir.y = FIX10_DIV((temp_dir.y >> 4), (length >> 4)) << 4;
			h->direction = temp_dir;
			h->x += FIX14_MULT((FIX8_DIV((h->count << 8), (30 << 8)) << 6), calccos(h->angle))
					+ FIX14_MULT((FIX8_DIV(((30 - h->count) << 8), (30 << 8)) << 6), h->direction.x);
			h->y += FIX14_MULT((FIX8_DIV((h->count << 8), (30 << 8)) << 6), calcsin(h->angle))
					+ FIX14_MULT((FIX8_DIV(((30 - h->count) << 8), (30 << 8)) << 6), h->direction.y);

			if (h->count > 0) h->count--;
		}
		if(homingBoundsCheck(h) || homingHit(h, enemies[h->locked - 1])) {
			h->alive = 0;
			h->exploded = 20;
			homingExplode(h, enemies, numEnemies);
		} else homing_render(h);
	}

}

void homing_render(homing_t *h) {
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
	} else {
		fgcolor(2);
		printf("x");
	}
	fgcolor(15);
}

uint8_t homingEnemyDetection(homing_t *h, enemy_t *enemies, uint8_t numEnemies) {
	uint8_t i, j = 0;
	uint32_t length0, length1;
	vector_t temp_dir;
	temp_dir.x = 0;
	temp_dir.y = 0;
	length0 = lengthOfVector(temp_dir);
	for(i = 0; i < numEnemies; i++) {
		if(enemies[i].alive) {
			if(MAX((h->x >> 14), (enemies[i].x >> 14)) - MIN((h->x >> 14), (enemies[i].x >> 14)) <= 5 &&
					MAX((h->y >> 14), (enemies[i].y >> 14)) - MIN((h->y >> 14), (enemies[i].y >> 14)) <= 5) {
				temp_dir = coordsToVector(h->x, h->y, enemies[i].x, enemies[i].y);
				length1 = lengthOfVector(temp_dir);
				if(length1 > length0) {
					length0 = length1;
					j = i + 1;
				}
			}
		}
	}
	return j;
}

uint8_t homingBoundsCheck(homing_t *h) {
	return (h->x >> 14) > 200 || (h->y >> 14) > 40 || (h->x >> 14) < 0 || (h->y >> 14) < 0;
}

uint8_t homingHit(homing_t *h, enemy_t e) {
	return MAX((h->x >> 14), (e.x >> 14)) - MIN((h->x >> 14), (e.x >> 14)) <= 1 &&
		MAX((h->y >> 14), (e.y >> 14)) - MIN((h->y >> 14), (e.y >> 14)) <= 1;
}

void homingExplode(homing_t *h, enemy_t *enemies, uint8_t numEnemies) {
	uint8_t i;
	for (i = 0; i < numEnemies; i++) {
		if(enemies[i].alive) {
			if(MAX((h->x >> 14), (enemies[i].x >> 14)) - MIN((h->x >> 14), (enemies[i].x >> 14)) <= 5 &&
					MAX((h->y >> 14), (enemies[i].y >> 14)) - MIN((h->y >> 14), (enemies[i].y >> 14)) <= 5) {
				enemies[i].hp -= 10;
			}
		}
	}
	homingExplode_render(h);
}

void homingExplode_render(homing_t *h) {
	uint8_t i, j;
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			gotoxy((h->x >> 14) - 2 + i, (h->y >> 14) - 2 + j);
			printf("x");
		}
	}
}
void homingExplode_render2(homing_t *h) {
	uint8_t i, j;
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			gotoxy((h->x >> 14) - 2 + i, (h->y >> 14) - 2 + j);
			printf(" ");
		}
	}
}
