#include "struct.h"
#include "math.h"
#include "ansi.h"



void spaceshipinit(spaceship_t *sh, int32_t direction, int32_t x, int32_t y){

    sh->x=x;
    sh->y=y;

    sh->x <<= 14;
    sh->y <<= 14;

    sh->direction=direction;
}

void update_spaceship(int input,spaceship_t *sh){

    if (0x01 & input){
        gotoxy(sh->x>>14,sh->y>>14);
        printf(" ");

        sh->x += calccos(sh->direction);
        sh->y += calcsin(sh->direction);
    }

    if (0x02 & input){
        gotoxy(sh->x>>14,sh->y>>14);
        printf(" ");

        sh->x -= calccos(sh->direction);
        sh->y -= calcsin(sh->direction);
    }

    if (0x04 & input){
        sh->direction += 4;
        //rotateVector(&sh->direction, 1);
    }

    if (0x08 & input){
        sh->direction -= 4;
        //rotateVector(&sh->direction, -1);
    }

}

void render_spaceship(spaceship_t sh){
    gotoxy(sh.x>>14,sh.y>>14);

    int32_t n = sh.direction & 0x1FF;

    //printf("cos = %d, sin = %d", cos, sin);

    if(n <= 64 || n > 512 - 64) {
        //printf("right");
    	spaceship_sprite(sh, 0);
    }

    else if(n > 64 && n < 128 + 64) {
		//printf("down");
    	spaceship_sprite(sh, 1);
	}

    else if(n >= 128 + 64 && n < 256 + 64) {
		//printf("left");
    	spaceship_sprite(sh, 2);
	}

    else if(n >= 256 + 64 && n <= 512 - 64) {
		//printf("up");
    	spaceship_sprite(sh, 3);
	}
}

void spaceship_sprite(spaceship_t sh, uint8_t n) {
	uint8_t i, j;
	int32_t x = sh.x >> 14, y = sh.y >> 14;
	char sprite[3][3];
	switch (n) {
	case 0 :
		gotoxy(x + 1, y + 9);
		printf("\\");
		gotoxy(x + 1, y + 10);
		printf("%c", 199);
		gotoxy(x + 1,y + 11);
		printf("/");
		gotoxy(x + 2, y + 10);
		printf("%c", 254);
		gotoxy(x + 3, y + 10);
		printf("D");
		break;
	case 1 :
		gotoxy(x + 2, y + 5);
		printf("\\");
		gotoxy(x + 3, y + 5);
		printf("%c", 209);
		gotoxy(x + 4, y + 5);
		printf("/");
		gotoxy(x + 3, y + 6);
		printf("%c", 219);
		gotoxy(x + 3, y + 7);
		printf("u");
		break;
	case 2 :

		sprite[0][0] = ' ';
		sprite[0][1] = ' ';
		sprite[0][2] = '/';
		sprite[1][0] = 'c';
		sprite[1][1] = 219;
		sprite[1][2] = ' ';
		sprite[2][0] = '/';
		sprite[2][1] = 207;
		sprite[2][2] = '\\';

		gotoxy(x + 3, y + 13);
		printf("/");
		gotoxy(x + 3, y + 14);
		printf("%c", 182);
		gotoxy(x + 3,y + 15);
		printf("\\");
		gotoxy(x + 2,y + 14);
		printf("%c", 254);
		gotoxy(x + 1, y + 14);
		printf("c");
		break;
	case 3 :

		sprite[0][0] = ' ';
		sprite[0][1] = 239;
		sprite[0][2] = ' ';
		sprite[1][0] = ' ';
		sprite[1][1] = 219;
		sprite[1][2] = ' ';
		sprite[2][0] = '/';
		sprite[2][1] = 207;
		sprite[2][2] = '\\';

		/*
		sprite[0][0] = ' ';
		sprite[0][1] = 'n';
		sprite[0][2] = ' ';
		sprite[1][0] = '/';
		sprite[1][1] = '|';
		sprite[1][2] = '\\';
		sprite[2][0] = ' ';
		sprite[2][1] = 'w';
		sprite[2][2] = ' ';


		char sprite[3][3] = {
			{' ','n',' ' },
			{'/','|','\\'},
			{' ','w',' ' }
		};
		*/
		break;
	}
	for(i=0; i<3; i++) {
		for(j=0; j<3; j++) {
			gotoxy(x - 1 + i,y - 1 + j);
			printf("%c", sprite[j][i]);
		}
	}
}
