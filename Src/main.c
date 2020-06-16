#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "ADC1.h"
#include "struct.h"
#include "controls.h"
#include "ansi.h"


int main(void)
{

	uart_init( 9600 );
    clrscr();


    vector_t v;

	//change

    spaceship_t sh;
    vector_t v;
    vectorinit(&v,0);

    spaceshipinit(&sh, 0, 15, 15);

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
