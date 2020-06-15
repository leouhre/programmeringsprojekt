#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "ADC1.h"
uint8_t flag = 0;

void TIM2_IRQHandler(void) {
    flag = 1;
	TIM2->SR &= ~0x0001; // Clear interrupt bit}
}

void readUART(char *buffer){
	uint8_t i;
	for(i = 0; i < 256; i++) {
		buffer[i] = uart_get_char();
		if(buffer[i] == '\0') break;
	}
}


int main(void)
{
    uint8_t i;

    char buffer[256];

    char txt_input[256];

    uint16_t pos = 0;

    uint8_t enterKey = 0;

    while(1) {
        readUART(buffer);
        for(i = 0; i < strlen(buffer); i++) {
            if(buffer[i] == 0x0D) {
                enterKey = 1;
            } else {
                txt_input[i + pos] = buffer[i];
                pos++;
            }
        }

        switch (buffer[0])
        {
            case('w'):
                printf("up");
                //spaceship struct up
                break;
             case('a'):
                printf("left");
                //spaceship struct up
                break;
             case('d'):
                printf("right");
                //spaceship struct up
                break;
             case('s'):
                printf("down");
                //spaceship struct up
                break;
        }

        memset(buffer,0x00,256);

        //printf("%s",buffer);

        if(enterKey) {
            enterKey = 0;
            txt_input[pos] = '\0';

            if(!strcmp("start", txt_input)) {
                printf("start");

            } else if(!strcmp("stop", txt_input)) {
                printf("stop");
            }

            memset(txt_input,0x00,256);
            pos = 0;
        }*/
    }

 /*
    while(1) {
        if(flag) {
            t.ds++;
            flag = 0;
        }

        if(t.ds % 99 == 1) {
            timerUpdate();
            printf("%02d:%02d:%02d\n", t.h%60, t.m%60, t.s%60);
        }
    }
*/

  while(1){}
}
