#include "controls.h"


void readUART(char *buffer){
	uint8_t i;
	for(i = 0; i < 256; i++) {
		buffer[i] = uart_get_char();
		if(buffer[i] == '\0') break;
	}
}

void storeBuffer(char *buffer) {
    uint8_t i, pos = 0;
    char txt_input[256];
    readUART(buffer);

    for(i = 0; i < strlen(buffer); i++) {
        txt_input[i + pos] = buffer[i];
        pos++;
    }

    for(i = 0; i < strlen(txt_input); i++) {
        switch (txt_input[i])
        {
            case('w'):
                printf("up");
                return 0x01;
                //spaceship moves up
                break;
             case('a'):
                printf("left");
                return 0x02;
                //spaceship moves left
                break;
             case('d'):
                printf("right");
                return 0x04;
                //spaceship moves right
                break;
             case('s'):
                printf("down");
                return 0x08;
                //spaceship moves down
                break;
            case(' '):
                printf("shoot");
                return 0x10;
                //shoot
                break;
        }
    }
        memset(buffer,0x00,256);
        memset(txt_input,0x00,256);
        pos = 0;
}
