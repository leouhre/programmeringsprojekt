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
<<<<<<< HEAD

    clrscr();

	//change
    uint8_t i, clipsize = 20 /*entities[512][512]*/;
    //spaceship_t sh;

   // vector_t v;
=======
	clrscr();
	//change
    uint8_t i, clipsize = 5;
    uint8_t enemies = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    spaceship_t sh;
>>>>>>> 11782427c730031df89c55965a16ef679b50a6d8

    bullet_t bullet[clipsize]; // initialize empty array of bullets

    for (i = 0; i < clipsize; i++) {
            bullet[i].alive = 0;
    }

	while(1){
<<<<<<< HEAD
	    //bullet_init(&bullet, sh);
        //bullet_update(&bullet, entities);
        printf("while");
=======
	    bullet_init(&bullet, sh);
        bullet_update(&bullet);
>>>>>>> 11782427c730031df89c55965a16ef679b50a6d8
	}
}
