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
	printf("hey allesammen:)");
	printf("ye");

	clrscr();

	//change
	int in=1;
	uint8_t entities[512][512];
    spaceship_t sh;
    bullet_t bullet[20];
    vector_t v;
    vectorinit(&v,0);

    spaceshipinit(&sh, v, 5, 5);

    bullet_init(&bullet, sh); // skal køres når der affyres en kugle

	while(1){

        update_spaceship(readControls(),&sh);
        render_spaceship(sh);
        gotoxy(1,1);
        printFix(expand(sh.direction.x));
        gotoxy(1,3);
		printFix(expand(sh.direction.y));

	}
}
