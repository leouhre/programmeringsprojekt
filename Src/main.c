#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "ADC1.h"
#include "spaceship.h"
#include "controls.h"
#include "ansi.h"
#include "enemy.h"
#include "bullet.h"
#include "math.h"
#include "led.h"
#include "TIM2.h"
#include "timer.h"

volatile uint8_t flag = 0;

int main(void)
{

	uart_init( 153600 );
    clrscr();

    uint8_t i;
    uint32_t tick = 0;
    uint8_t hp = 5;

    spaceship_t sh;
    enemy_t enemy;

    //spaceship_init(&sh, 0, 20, 20, 8);

    bullet_t bullet[sh.clipsize]; // set clipsize
    for (i = 0; i < sh.clipsize; i++) {
        bullet[i].alive = 0;
    }


    timer_configure();

    led_init();


	while(1) {
        if(flag) {
            flag = 0;
            led_hp_update(tick, hp);
            tick++;
            if(tick % 100 == 99) {
                hp--;
            }
        }
	}
}
