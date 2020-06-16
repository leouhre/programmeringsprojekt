#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "ADC1.h"
#include "struct.h"
#include "controls.h"
#include "ansi.h"
#include "enemy.h"

int main(void)
{

	uart_init( 9600 );

	clrscr();


    spaceship_t sh;

    spaceshipinit(&sh, 0, 20, 20);

    enemy_t enemy;

	enemy_init(&enemy, sh, 12, 2);



	//printFix(expand(lengthOfVector(v)));
    //printFix(((7 << 14) >> 6)*((7 << 14) >> 6) >> 8 << 8);
    //printFix(	expand(	FIX8_MULT((7 << 14) >> 6,(7 << 14) >> 6) << 6));




	while(1){
		//comment empty
		gotoxy(1,1);
		printFix(expand(enemy.direction.x));
		gotoxy(1,5);
		printFix(expand(enemy.direction.y));
		enemy_update(&enemy, sh);
		enemy_render(enemy);
        update_spaceship(readControls(),&sh);
        render_spaceship(sh);
	}
}
