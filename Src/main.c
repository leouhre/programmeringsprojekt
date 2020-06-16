#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "ADC1.h"
#include "struct.h"
#include "controls.h"
#include "ansi.h"
#include "enemy.h"
#include "bullet.h"
#include "math.h"


int main(void)
{

	uart_init( 9600 );
    clrscr();


    uint8_t i/*entities[512][512]*/;

    bullet_t bullet[5];


    spaceship_t sh;
    enemy_t enemy;

    spaceshipinit(&sh, 0, 20, 20);
	enemy_init(&enemy, sh, 12, 2);

    for (i = 0; i < 5; i++) {
            bullet[i].alive = 0;
    }


	while(1){

		enemy_update(&enemy, sh);
		enemy_render(enemy);
        update_spaceship(readControls(),&sh);
        render_spaceship(sh);


	    /*bullet_init(&bullet, sh);
        bullet_update(&bullet);*/
	}
}
