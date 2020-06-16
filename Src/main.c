#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "ADC1.h"
#include "struct.h"
#include "controls.h"
#include "ansi.h"
#include "bullet.h"

int main(void)
{

	uart_init( 9600 );
    clrscr();


	clrscr();

	//change
    uint8_t i, clipsize = 20;
    spaceship_t sh;
    vector_t v;

    bullet_t bullet[clipsize]; // initialize empty array of bullets
    for (i = 0; i < clipsize; i++) {
            bullet[i].alive = 0;
    }


    vectorinit(&v,0);

    spaceshipinit(&sh, 0, 15, 15);

    bullet_init(&bullet, sh);

	while(1){
		//comment empty
        update_spaceship(readControls(),&sh);
        render_spaceship(sh);

        gotoxy(1,1);
         printFix(expand(calccos(sh.direction)));
                                        clreol();
                                        printf("\n");
        printFix(expand(calcsin(sh.direction)));
                                        clreol();
                                        printf("\n");

	}
}
