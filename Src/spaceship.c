#include "SPACESHIP.h"

void spaceshipinit(spaceship_t *sh, int32_t direction, int32_t x, int32_t y)
{

    sh->x=x;
    sh->y=y;

    sh->x <<= 14;
    sh->y <<= 14;

    sh->angle=direction;
    sh->clipsize = 5;
}

void update_spaceship(int input,spaceship_t *sh)
{

    uint8_t i, j;

    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            gotoxy((sh->x>>14) - 1 + i,(sh->y>>14) - 1 + j);
            printf(" ");
        }
    }

    if (0x01 & input)
    {
        sh->x += calccos(sh->angle);
        sh->y += calcsin(sh->angle);
    }

    if (0x02 & input)
    {
        sh->x -= calccos(sh->angle);
        sh->y -= calcsin(sh->angle);
    }

    if (0x04 & input)
    {
        sh->angle += 32;
        //rotateVector(&sh->direction, 1);
    }

    if (0x08 & input)
    {
        sh->angle -= 32;
        //rotateVector(&sh->direction, -1);
    }

}

void render_spaceship(spaceship_t sh)
{
    gotoxy(sh.x>>14,sh.y>>14);

    int32_t n = sh.angle & 0x1FF;

    //printf("cos = %d, sin = %d", cos, sin);

    if(n <= 64 || n > 512 - 64)
    {
        //printf("right");
        spaceship_sprite(sh, 0);
    }

    else if(n > 64 && n < 128 + 64)
    {
        //printf("down");
        spaceship_sprite(sh, 1);
    }

    else if(n >= 128 + 64 && n < 256 + 64)
    {
        //printf("left");
        spaceship_sprite(sh, 2);
    }

    else if(n >= 256 + 64 && n <= 512 - 64)
    {
        //printf("up");
        spaceship_sprite(sh, 3);
    }
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
        sprite[1][0] = 199;
        sprite[1][1] = 254;
        sprite[1][2] = 'D';
        sprite[2][0] = '/';
        sprite[2][1] = ' ';
        sprite[2][2] = ' ';

        break;
    case 1 :
        sprite[0][0] = '\\';
        sprite[0][1] = 209;
        sprite[0][2] = '/';
        sprite[1][0] = ' ';
        sprite[1][1] = 219;
        sprite[1][2] = ' ';
        sprite[2][0] = ' ';
        sprite[2][1] = 'u';
        sprite[2][2] = ' ';

        break;
    case 2 :
        sprite[0][0] = ' ';
        sprite[0][1] = ' ';
        sprite[0][2] = '/';
        sprite[1][0] = 'c';
        sprite[1][1] = 254;
        sprite[1][2] = 182;
        sprite[2][0] = ' ';
        sprite[2][1] = ' ';
        sprite[2][2] = '\\';

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
