#include "struct.h"
#include "math.h"

void vectorinit(vector_t *v, int32_t a){
    v->x=calccos(a);
    v->y=calcsin(a);
}

void spaceshipinit(spaceship_t *sh, vector_t direction, int32_t x, int32_t y){
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

        sh->x += sh->direction.x;
        sh->y += sh->direction.y;
    }

    if (0x02 & input){
        gotoxy(sh->x>>14,sh->y>>14);
        printf(" ");

        sh->x -= sh->direction.x;
        sh->y -= sh->direction.y;
    }

    if (0x04 & input){
        rotateVector(&sh->direction, 1);
    }

    if (0x08 & input){
        rotateVector(&sh->direction, -1);
    }

}

void render_spaceship(spaceship_t sh){
    gotoxy(sh.x>>14,sh.y>>14);
    printf("o");
}
