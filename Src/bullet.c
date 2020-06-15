#include "bullet.h"
#include "math.h"

void bullet_init(bullet_t *bullet, spaceship_t *sh) {
    uint8_t i, str;
    for(i = 0; i < 20; i++) { // find number of bullets in array
        if(bullet[i] == '\0') break;
        str ++;
    }

    bullet[str+1]->x=sh.x;
    bullet[str+1]->y=sh.y;

    bullet[str+1]->x <<= 14;
    bullet[str+1]->y <<= 14;

    bullet[str+1]->direction=sh.direction;
    bullet[str+1]->bullet_type = sh.bullet_type;
}

void bullet_update(bullet_t bullet, entities *enemies){
    uint8_t i, j;


	for (i = 0; i < 20; i++ ) {
        bullet[i].x += bullet[i].direction.x;
        bullet[i].y += bullet[i].direction.y;

        if(enteties[bullet[i].x][bullet[i].y] != '\0') { //if enemy is hit delete bullet
            bullet[i] = '\0';
            for (j = i; j < 19; j++){
                if(bullet[j] == '\0') break;
                bullet[j] = bullet[j+1];
            }
            bullet[19] = '\0';
        }

	}
}

void bullet_draw() {

}
