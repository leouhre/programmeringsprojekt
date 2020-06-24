#include "controls.h"

void readUART(char *buffer){ //copies input from keyboard into the buffer array
	uint8_t i;
	for(i = 0; i < 256; i++) {
		buffer[i] = uart_get_char();
		if(buffer[i] == '\0') break; // if no input is detected stop copying
	}
}

uint8_t readControls() { //returns a value depending on what the input is
    uint8_t i;
    char txt_input[256], buffer[256];
    readUART(buffer);

    for(i = 0; i < strlen(buffer); i++) { //copies members of buffer into txt_input
        txt_input[i] = buffer[i];
    }


	switch (txt_input[0]) //returns a byte with only one bit set to high for easy comparison
	{
		case('w'):
			return 0x01;
		case('s'):
			return 0x02;
		case('a'):
			return 0x04;
		case('d'):
			return 0x08;
		case(' '):
			return 0x10;
		case('p'):
			return 0x20;
		case('q'):
			return 0x40;
		case('e'):
			return 0x80;
		default: return 0x00;
	}
}
