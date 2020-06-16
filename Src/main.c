#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "ADC1.h"
#include "spaceship.h"
#include "controls.h"
#include "ansi.h"
#include "enemy.h"
#include "bullet.h"
#include "math.h"


int main(void)
{

	uart_init( 153600 );
    clrscr();

<<<<<<< HEAD

    uint8_t i/*entities[512][512]*/;

    bullet_t bullet[5];

=======
	//change
    uint8_t i;
>>>>>>> e5fad626b29b155da05de8abc40361fc503cd73f

    spaceship_t sh;
    enemy_t enemy;

    spaceshipinit(&sh, 0, 20, 20);
	enemy_init(&enemy, sh, 12, 2);

    bullet_t bullet[sh.clipsize]; // set clipsize
    for (i = 0; i < sh.clipsize; i++) {
        bullet[i].alive = 0;
    }


	while(1){
<<<<<<< HEAD

		enemy_update(&enemy, sh);
		enemy_render(enemy);
=======
        if(readControls() & 0x10) {
            bullet_init(&bullet, sh);
        }
        bullet_update(&bullet, sh);
>>>>>>> e5fad626b29b155da05de8abc40361fc503cd73f
        update_spaceship(readControls(),&sh);
        render_spaceship(sh);
	}
}
