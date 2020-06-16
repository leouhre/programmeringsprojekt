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
	//change
    uint8_t i, clipsize = 5;
    uint8_t enemies = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    spaceship_t sh;

    bullet_t bullet[clipsize]; // initialize empty array of bullets
    for (i = 0; i < clipsize; i++) {
            bullet[i].alive = 0;
    }

	while(1){
	    bullet_init(&bullet, sh);
        bullet_update(&bullet);
	}
}
