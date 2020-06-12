#include "struct.h"


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


