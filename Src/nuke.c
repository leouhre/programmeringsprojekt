#include "nuke.h"

void nuke_init(nuke_t *nuke, spaceship_t sh) {
	//initializes a nuke in the spaceship aim direction

	nuke->x = (ADC1_1_read() / 23 + 2) << 14;
	nuke->y = (ADC1_2_read() / 78 + 2) << 14;
	nuke->alive = 1;
	//nuke->angle = sh.aim;
	//nuke->count = 3;
	nuke->exploded = 0;
}

void nuke_update(nuke_t *nuke, enemy_t *enemies, uint8_t numEnemies, spaceship_t *sh, uint8_t *nukeCount) {
	//updates nuke's coordinates and explodes if time
	gotoxy(3,5);
	printf("%d", nuke->exploded);
	if(nuke->exploded > 0) { //wait some time before removing 'dust'
		nuke->exploded--;
		if(!nuke->exploded) nukeExplosion_render(*nuke, 1);
		return;
	}
	if(!nuke->alive) {
		gotoxy(nuke->x >> 14, nuke->y >> 14);
		printf(" ");
		nuke->x = (ADC1_1_read() / 23 + 2) << 14;
		nuke->y = (ADC1_2_read() / 78 + 2) << 14;
		gotoxy(nuke->x >> 14, nuke->y >> 14);
		fgcolor(1);//red
		printf("+");
		fgcolor(15);//white
	}
	if (nuke->alive && *nukeCount) {
		nuke->alive = 0;
		nuke->exploded = 30;
		nukeExplode(*nuke, enemies, numEnemies); //enemy hp is decreased in nukeExplode()
		*nukeCount -= 1;
		if (*nukeCount < 1) sh->bullet_type = 0;
	}
	/*
	if (nuke->alive && nuke->count) { //remove previous render and update coords
		uint8_t i, j;
		for (i = 0; i < 3; i++) {
			for (j = 0; j < 3; j++) {
				gotoxy((nuke->x >> 14) - 1 + i, (nuke->y >> 14) - 1 + j);
				printf(" ");
			}
		}
		nuke->x += calccos(nuke->angle);
		nuke->y += calcsin(nuke->angle);
		nuke->count--;
		if (nukeBoundsCheck(*nuke)) { //bad luck if you sent the nuke out of bounds
			nuke->alive = 0;
			for (i = 0; i < 3; i++) {
				for (j = 0; j < 3; j++) {
					gotoxy((nuke->x >> 14) - 1 + i, (nuke->y >> 14) - 1 + j);
					printf(" ");
				}
			}
		} else if (nukeHit(*nuke, enemies, numEnemies) || !nuke->count) {
			nuke->alive = 0;
			nuke->exploded = 30;
			nukeExplode(*nuke, enemies, numEnemies); //enemy hp is decreased in nukeExplode()
		} else nuke_render(*nuke); //draw nuke on screen
	}
	*/
}

void nuke_render(nuke_t nuke) {
	//draw nuke on screen
	uint8_t i, j;
	char bomb[3][3] = {	{' ', 196, ' '},
						{'/', '+', '\\'},
						{196, 196, 196} };
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			gotoxy((nuke.x >> 14) - 1 + i, (nuke.y >> 14) - 1 + j);
			printf("%c", bomb[j][i]);
		}
	}
}

uint8_t nukeBoundsCheck(nuke_t nuke) {
	//returns true if nuke is out of bounds
	return (nuke.x >> 14) > 209 || (nuke.y >> 14) > 53
			|| (nuke.x >> 14) < 3 || (nuke.y >> 14) < 3;
}

uint8_t nukeHit(nuke_t nuke, enemy_t *enemies, uint8_t numEnemies) {
	//returns true if an enemy is hit by the nuke causing explosion
	uint8_t i;
	for (i = 0; i < numEnemies; i++) {
		if(enemies[i].alive) {
			return MAX((nuke.x >> 14), (enemies[i].x >> 14)) - MIN((nuke.x >> 14), (enemies[i].x >> 14)) <= 2 &&
					MAX((nuke.y >> 14), (enemies[i].y >> 14)) - MIN((nuke.y >> 14), (enemies[i].y >> 14)) <= 2;
		}
	}
	return 0;
}

void nukeExplode(nuke_t nuke, enemy_t *enemies, uint8_t numEnemies) {
	//decrease enemies' hp if their in the nuke's explosion range
	uint8_t i;
	for (i = 0; i < numEnemies; i++) {
		if(enemies[i].alive) {
			if(MAX((nuke.x >> 14), (enemies[i].x >> 14)) - MIN((nuke.x >> 14), (enemies[i].x >> 14)) <= 11 &&
					MAX((nuke.y >> 14), (enemies[i].y >> 14)) - MIN((nuke.y >> 14), (enemies[i].y >> 14)) <= 11) {
				enemies[i].hp -= 10;
			}
		}
	}
	nukeExplosion_render(nuke, 0);
}

void nukeExplosion_render(nuke_t nuke, uint8_t remove) {
	//draws or removes the nuke dust on/from the screen
	uint8_t i, j;
	for (i = 0; i < 25; i++) {
		for (j = 0; j < 25; j++) {
			if(!((nuke.x >> 14) - 6 + i > 210) && !((nuke.x >> 14) - 6 + i < 2)
					&& !((nuke.y >> 14) - 8 + j > 54) && !((nuke.y >> 14) - 8 + j < 2)) {
				gotoxy((nuke.x >> 14) - 12 + i, (nuke.y >> 14) - 12 + j);
				if(!remove && i % 2 && j % 2) {
					printf("@");
				} else printf(" ");
			}
		}
	}
}
