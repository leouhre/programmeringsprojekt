#include "SPACESHIP.h"

void spaceship_init(spaceship_t *sh, int32_t direction, int32_t x, int32_t y)
{
    sh->x = (x << 14);
    sh->y = (y << 14);
    sh->angle=direction;
    sh->hp = 15;
    sh->aim = 288;
    sh->bullet_type = 0;
    sh->score = 0;
}

void spaceship_update(uint8_t input,spaceship_t *sh)
{
    if(!input)return; //doesnt update if there is no input from the user
    uint8_t i, j;

    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            gotoxy((sh->x>>14) - 1 + i,(sh->y>>14) - 1 + j);
            printf(" ");
        }
    }

	gotoxy((sh->x + (calccos(sh->aim) << 3)) >> 14, (sh->y + (calcsin(sh->aim) << 3)) >> 14);
	printf(" ");

    if (0x01 & input)
    {
        if(!spaceshipBoundsCheck(*sh)){//not hit anything
    	//move forward
            sh->x += calccos(sh->angle) << 1;
            sh->y += calcsin(sh->angle) << 1;
        }
        else if (spaceshipBoundsCheck(*sh) & 0x01){ //hit left wall
            if( (sh->angle & 0x1ff) <= 128 || (sh->angle & 0x1ff) >= 256+128){
                sh->x += calccos(sh->angle) << 1;
                sh->y += calcsin(sh->angle) << 1;
            }
        }
        else if (spaceshipBoundsCheck(*sh) & 0x02){ //hit right wall
            if( (sh->angle & 0x1ff) >= 128 && (sh->angle & 0x1ff) <= 256+128){
                sh->x += calccos(sh->angle) << 1;
                sh->y += calcsin(sh->angle) << 1;
            }
        }
        else if (spaceshipBoundsCheck(*sh) & 0x04){ //hit bottom wall
            if( (sh->angle & 0x1ff) >= 256 || (sh->angle & 0x1ff) == 0){
                sh->x += calccos(sh->angle) << 1;
                sh->y += calcsin(sh->angle) << 1;
            }
        }
        else if (spaceshipBoundsCheck(*sh) & 0x08){ //hit top wall
            if( (sh->angle & 0x1ff) <= 256){
                sh->x += calccos(sh->angle) << 1;
                sh->y += calcsin(sh->angle) << 1;
            }
        }
    }
    if (0x04 & input)
    {
    	//turn spaceship counter clockwise
        sh->angle -= 32;
    }

    if (0x08 & input)
    {
    	//turn spaceship clockwise
        sh->angle += 32;
    }
    if (0x40 & input)
    {
    	//rotate aim counter clockwise
        sh->aim -= 16;
    }
    if (0x80 & input)
    {
    	//rotate aim clockwise
        sh->aim += 16;
    }

}
void spaceshipAim_render(spaceship_t sh) {
	gotoxy((sh.x + (calccos(sh.aim) << 3)) >> 14, (sh.y + (calcsin(sh.aim) << 3)) >> 14);
	fgcolor(1);
	printf("x");
	fgcolor(15);
}

void spaceship_render(spaceship_t sh)
{
    int32_t n = sh.angle & 0x1FF;

    gotoxy(sh.x>>14,sh.y>>14);

    if(n > 512 - 16 || n <= 16) spaceship_sprite(sh, 0);

	else if(n > 32 - 16 && n <= 32 + 16) spaceship_sprite(sh, 1);

	else if(n > 64 - 16 && n <= 64 + 16) spaceship_sprite(sh, 2);

	else if(n > 96 - 16 && n <= 96 + 16) spaceship_sprite(sh, 3);

	else if(n > 128 - 16 && n <= 128 + 16) spaceship_sprite(sh, 4);

	else if(n > 160 - 16 && n <= 160 + 16) spaceship_sprite(sh, 5);

	else if(n > 192 - 16 && n <= 192 + 16) spaceship_sprite(sh, 6);

	else if(n > 224 - 16 && n <= 224 + 16) spaceship_sprite(sh, 7);

	else if(n > 256 - 16 && n <= 256 + 16) spaceship_sprite(sh, 8);

	else if(n > 288 - 16 && n <= 288 + 16) spaceship_sprite(sh, 9);

	else if(n > 320 - 16 && n <= 320 + 16) spaceship_sprite(sh, 10);

	else if(n > 352 - 16 && n <= 352 + 16) spaceship_sprite(sh, 11);

	else if(n > 384 - 16 && n <= 384 + 16) spaceship_sprite(sh, 12);

	else if(n > 416 - 16 && n <= 416 + 16) spaceship_sprite(sh, 13);

	else if(n > 448 - 16 && n <= 448 + 16) spaceship_sprite(sh, 14);

	else if(n > 480 - 16 && n <= 480 + 16) spaceship_sprite(sh, 15);

    spaceshipAim_render(sh);
}

void spaceship_sprite(spaceship_t sh, uint8_t n)
{
    uint8_t i, j;
    int32_t x = sh.x >> 14, y = sh.y >> 14;
    char sprite[3][3];

    switch (n)
	{
    	case 0 :
    		sprite[0][0] = '\\';
    		sprite[0][1] = ' ';
    		sprite[0][2] = ' ';
    		sprite[1][0] = '<';
    		sprite[1][1] = '-';
    		sprite[1][2] = 'o';
    		sprite[2][0] = '/';
    		sprite[2][1] = ' ';
    		sprite[2][2] = ' ';

    		break;
    	case 1 :
    		sprite[0][0] = '\\';
    		sprite[0][1] = ' ';
    		sprite[0][2] = ' ';
    		sprite[1][0] = '<';
    		sprite[1][1] = '-';
    		sprite[1][2] = 'o';
    		sprite[2][0] = '-';
    		sprite[2][1] = ' ';
    		sprite[2][2] = ' ';

    		break;
    	case 2 :
    		sprite[0][0] = 'M';
    		sprite[0][1] = ' ';
    		sprite[0][2] = '|';
    		sprite[1][0] = '-';
    		sprite[1][1] = '\\';
    		sprite[1][2] = ' ';
    		sprite[2][0] = ' ';
    		sprite[2][1] = ' ';
    		sprite[2][2] = 'o';

    		break;
    	case 3 :
    		sprite[0][0] = '\\';
    		sprite[0][1] = 'M';
    		sprite[0][2] = '/';
    		sprite[1][0] = ' ';
    		sprite[1][1] = '\\';
    		sprite[1][2] = ' ';
    		sprite[2][0] = ' ';
    		sprite[2][1] = ' ';
    		sprite[2][2] = 'o';

    		break;
    	case 4 :
    		sprite[0][0] = '\\';
    		sprite[0][1] = 'M';
    		sprite[0][2] = '/';
    		sprite[1][0] = ' ';
    		sprite[1][1] = '|';
    		sprite[1][2] = ' ';
    		sprite[2][0] = ' ';
    		sprite[2][1] = 'o';
    		sprite[2][2] = ' ';

    		break;
    	case 5 :
    		sprite[0][0] = '\\';
    		sprite[0][1] = 'M';
    		sprite[0][2] = '/';
    		sprite[1][0] = ' ';
    		sprite[1][1] = '/';
    		sprite[1][2] = ' ';
    		sprite[2][0] = 'o';
    		sprite[2][1] = ' ';
    		sprite[2][2] = ' ';

    		break;
    	case 6 :
    		sprite[0][0] = ' ';
    		sprite[0][1] = '|';
    		sprite[0][2] = 'M';
    		sprite[1][0] = ' ';
    		sprite[1][1] = '/';
    		sprite[1][2] = '-';
    		sprite[2][0] = 'o';
    		sprite[2][1] = ' ';
    		sprite[2][2] = ' ';

    		break;
    	case 7 :
    		sprite[0][0] = ' ';
    		sprite[0][1] = ' ';
    		sprite[0][2] = '/';
    		sprite[1][0] = 'o';
    		sprite[1][1] = '-';
    		sprite[1][2] = '>';
    		sprite[2][0] = ' ';
    		sprite[2][1] = ' ';
    		sprite[2][2] = '-';

    		break;
    	case 8 :
    		sprite[0][0] = ' ';
    		sprite[0][1] = ' ';
    		sprite[0][2] = '/';
    		sprite[1][0] = 'o';
    		sprite[1][1] = '-';
    		sprite[1][2] = '>';
    		sprite[2][0] = ' ';
    		sprite[2][1] = ' ';
    		sprite[2][2] = '\\';

    		break;
    	case 9 :
    		sprite[0][0] = ' ';
    		sprite[0][1] = ' ';
    		sprite[0][2] = '-';
    		sprite[1][0] = 'o';
    		sprite[1][1] = '-';
    		sprite[1][2] = '>';
    		sprite[2][0] = ' ';
    		sprite[2][1] = ' ';
    		sprite[2][2] = '\\';

    		break;
    	case 10 :
    		sprite[0][0] = 'o';
    		sprite[0][1] = ' ';
    		sprite[0][2] = ' ';
    		sprite[1][0] = ' ';
    		sprite[1][1] = '\\';
    		sprite[1][2] = '-';
    		sprite[2][0] = ' ';
    		sprite[2][1] = '\\';
    		sprite[2][2] = 'W';

    		break;
    	case 11 :
    		sprite[0][0] = 'o';
    		sprite[0][1] = ' ';
    		sprite[0][2] = ' ';
    		sprite[1][0] = ' ';
    		sprite[1][1] = '\\';
    		sprite[1][2] = ' ';
    		sprite[2][0] = '/';
    		sprite[2][1] = 'W';
    		sprite[2][2] = '\\';

    		break;
    	case 12 :
			sprite[0][0] = ' ';
			sprite[0][1] = 'o';
			sprite[0][2] = ' ';
			sprite[1][0] = ' ';
			sprite[1][1] = '|';
			sprite[1][2] = ' ';
			sprite[2][0] = '/';
			sprite[2][1] = 'W';
			sprite[2][2] = '\\';

			break;
		case 13 :
			sprite[0][0] = ' ';
			sprite[0][1] = ' ';
			sprite[0][2] = 'o';
			sprite[1][0] = ' ';
			sprite[1][1] = '/';
			sprite[1][2] = ' ';
			sprite[2][0] = '/';
			sprite[2][1] = 'W';
			sprite[2][2] = '\\';

			break;
		case 14 :
			sprite[0][0] = ' ';
			sprite[0][1] = ' ';
			sprite[0][2] = 'o';
			sprite[1][0] = '-';
			sprite[1][1] = '/';
			sprite[1][2] = ' ';
			sprite[2][0] = 'W';
			sprite[2][1] = '|';
			sprite[2][2] = ' ';

			break;
		case 15 :
			sprite[0][0] = '-';
			sprite[0][1] = ' ';
			sprite[0][2] = ' ';
			sprite[1][0] = '<';
			sprite[1][1] = '-';
			sprite[1][2] = 'o';
			sprite[2][0] = '/';
			sprite[2][1] = ' ';
			sprite[2][2] = ' ';

			break;
	}

    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            gotoxy(x - 1 + i,y - 1 + j);
            printf("%c", sprite[j][i]);
        }
    }
}


uint8_t spaceshipBoundsCheck(spaceship_t sh) {
	//returns true if the enemy is out of bounds.
	// 0, 1, 2, 3 = left, right, bot, top
	uint8_t val =0;
	if((sh.x >> 14) < 5 )              val |= 0x01;
	if((sh.x >> 14) > SCREEN_WIDTH-4)  val |= 0x02;

	if((sh.y >> 14) > SCREEN_HEIGHT-4)  val |= 0x04;
	if((sh.y >> 14) < 5)                val |= 0x08;

	return val;
}

uint8_t spaceshipDead(spaceship_t sh){
    uint8_t val = 0;
    if(sh.hp <= 0) val = 1;
    return val;
}
