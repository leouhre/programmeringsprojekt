#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "ADC1.h"
#include "struct.h"
int main(void)
{

	uart_init( 9600 );
	printf("hey allesammen:)");
	printf("ye");

	//change
    spaceship_t sh;
    vector_t v;
    vectorinit(&v,300);

    spaceshipinit(&sh, v, 5, 5);

	while(1){

        update_spaceship(&sh);
        render_spaceship(sh);

	}
}
