#include "bullet.h"
#include "math.h"

void bullet_init(bullet_t *bullet, spaceship_t sh) {
    uint8_t i, str = 0;
    for(i = 0; i < 20; i++) { // find number of bullets in array
        if(bullet[i].alive == 0) break;
        str++;
    }
    printf("str");
    bullet[str].alive = 1;

    bullet[str].x =  1;//sh.x;
    bullet[str].y = 1;//sh.y;

    bullet[str].x <<= 14;
    bullet[str].y <<= 14;

    bullet[str].angle = 0.5;//sh.angle;
   // bullet[str+1].bullet_type = sh.bullet_type;
}

void bullet_update(bullet_t *bullet, uint8_t **entities){
    uint8_t i, j;


	for (i = 0; i < 20; i++ ) { // update all bullets
        if(bullet[i].alive == 1) {
            gotoxy(bullet[i].x >> 14, bullet[i].y >> 14);
            printf(" "); //clear current bullet position

            bullet[i].x += calccos(bullet[i].angle);
            bullet[i].y += calcsin(bullet[i].angle);

            gotoxy(bullet[i].x >> 14, bullet[i].y >> 14);

            if(entities[bullet[i].x >> 14][bullet[i].y >> 14] != 0) { //if enemy is hit delete bullet
                //goto xy play animation
                for (j = i; j < 19; j++){
                    bullet[j] = bullet[j+1];
                }
                bullet[19].alive = 0;
                i--; // go one position back in the array
            } else {
                printf("o");
            }
        } else {
            break;
        }

	}
}

void bullet_draw() {

}
