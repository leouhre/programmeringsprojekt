#include "bullet.h"
#include "math.h"

void bullet_init(bullet_t *bullet, spaceship_t sh) {
    uint8_t i, str = 0;
    for(i = 0; i < 5; i++) { // find number of bullets in array
        if(bullet[i].alive == 0) break;
        str++;
    }

    if(str <= 5) {
        bullet[str].alive = 1;

        bullet[str].x =  2;//sh.x;
        bullet[str].y = 2;//sh.y;

        bullet[str].x <<= 14;
        bullet[str].y <<= 14;

        bullet[str].angle = 64;//sh.angle;
       // bullet[str].bullet_type = sh.bullet_type;
    }
}

void bullet_update(bullet_t *bullet) {
    uint8_t i, j;

    for(i = 0; i < 5; i++) {
        if (bullet[i].alive == 0) break;

        gotoxy(bullet[i].x >> 14, bullet[i].y >> 14);
        printf(" ");

        bullet[i].x += calccos(bullet[i].angle);
        bullet[i].y += calcsin(bullet[i].angle);
        if((bullet[i].x >> 14) > 40 || (bullet[i].y >> 14) > 40 || (bullet[i].x >> 14) < 0 || (bullet[i].y >> 14) < 0) {
            bullet[i].alive = 0;
            for(j = i; j < 4; j++) {
                bullet[j] = bullet[j+1];
            }
            bullet[4].alive = 0;
            i--;
        } else {
            gotoxy(bullet[i].x >> 14, bullet[i].y >> 14);
            printf("o");
        }

    }
}

void bullet_draw() {

}
