#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "ADC1.h"
#include "spaceship.h"
#include "controls.h"
#include "ansi.h"
#include "enemy.h"
#include "bullet.h"
#include "math.h"
#include "timer.h"

volatile uint8_t flag = 0;

int main(void)
{
	uart_init( 150600 );
	timer_configure();

    clrscr();

	uint32_t tick = 0;
    uint8_t i;

    spaceship_t sh;

    spaceship_init(&sh, 0, 80, 40);

    bullet_t bullet[sh.clipsize]; // set clipsize
    for (i = 0; i < sh.clipsize; i++) {
        bullet[i].alive = 0;
    }

    uint8_t numberOfEnemies = 2;
    enemy_t enemies[numberOfEnemies];
    fillEnemiesArray(enemies, numberOfEnemies);


	while(1){
		if(flag) {
			tick++;
			if(tick % 24 == 1) {
				enemy_update(enemies, numberOfEnemies, sh, bullet);
				enemy_render(enemies, numberOfEnemies);
			}
			if(tick % 2 == 1) {
		        spaceship_update(readControls(),&sh);
		        spaceship_render(sh);
			}
			if(readControls() & 0x10) {
				bullet_init(bullet, sh);
			}
			if(tick % 2 == 1) {
		        bullet_update(bullet, sh, enemies, numberOfEnemies);
			}
			flag = 0;
		}
	}

}
