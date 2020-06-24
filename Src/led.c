#include "led.h"

void led_enable(){
    RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A
    // Set pin PA9 to output
    GPIOA->OSPEEDR &= ~(0x00000003 << (9 * 2)); // Clear speed register
    GPIOA->OSPEEDR |= (0x00000002 << (9 * 2)); // set speed register (0x01 - 10MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
    GPIOA->OTYPER &= ~(0x0001 << (9)); // Clear output type register
    GPIOA->OTYPER |= (0x0000 << (9)); // Set output type register (0x00 -Push pull, 0x01 - Open drain)
    GPIOA->MODER &= ~(0x00000003 << (9 * 2)); // Clear mode register
    GPIOA->MODER |= (0x00000001 << (9 * 2)); // Set mode register (0x00 –Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)

    RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C
    // Set pin PC7 to output
    GPIOC->OSPEEDR &= ~(0x00000003 << (7 * 2)); // Clear speed register
    GPIOC->OSPEEDR |= (0x00000002 << (7 * 2)); // set speed register (0x01 - 10MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
    GPIOC->OTYPER &= ~(0x0001 << (7)); // Clear output type register
    GPIOC->OTYPER |= (0x0000 << (7)); // Set output type register (0x00 -Push pull, 0x01 - Open drain)
    GPIOC->MODER &= ~(0x00000003 << (7 * 2)); // Clear mode register
    GPIOC->MODER |= (0x00000001 << (7 * 2)); // Set mode register (0x00 –Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)

    RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B
    // Set pin PB4 to output
    GPIOB->OSPEEDR &= ~(0x00000003 << (4 * 2)); // Clear speed register
    GPIOB->OSPEEDR |= (0x00000002 << (4 * 2)); // set speed register (0x01 - 10MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
    GPIOB->OTYPER &= ~(0x0001 << (4)); // Clear output type register
    GPIOB->OTYPER |= (0x0000 << (4)); // Set output type register (0x00 -Push pull, 0x01 - Open drain)
    GPIOB->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
    GPIOB->MODER |= (0x00000001 << (4 * 2)); // Set mode register (0x00 –Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
}

void led_init() {
    led_enable(); //enable pins to led for output
    //turn off all led's
    GPIOA->ODR |= (0x0001 << 9); //Set pin PA9 to high color: blue
    GPIOB->ODR |= (0x0001 << 4); //Set pin PB4 to high color: red
    GPIOC->ODR |= (0x0001 << 7); //Set pin PC7 to high color: green
}

void led_color(uint8_t color){
    switch (color) {
        case 0:
            //LED off
            GPIOA->ODR |= (0x0001 << 9); //Set pin PA9 to high color: blue
            GPIOB->ODR |= (0x0001 << 4); //Set pin PB4 to high color: red
            GPIOC->ODR |= (0x0001 << 7); //Set pin PC7 to high color: green
            break;
        case 1:
            //green
            GPIOA->ODR |= (0x0001 << 9); //Set pin PA9 to high color: blue
            GPIOB->ODR |= (0x0001 << 4); //Set pin PB4 to high color: red
            GPIOC->ODR &= ~(0x0001 << 7); //Set pin PC7 to low color: green
            break;

        case 2:
            //red
            GPIOA->ODR |= (0x0001 << 9); //Set pin PA9 to high color: blue
            GPIOB->ODR &= ~(0x0001 << 4); //Set pin PB4 to low color: red
            GPIOC->ODR |= (0x0001 << 7); //Set pin PC7 to high color: green
            break;

        case 3:
            //yellow
            GPIOA->ODR |= (0x0001 << 9); //Set pin PA9 to high color: blue
            GPIOB->ODR &= ~(0x0001 << 4); //Set pin PB4 to low color: red
            GPIOC->ODR &= ~(0x0001 << 7); //Set pin PC7 to low color: green
            break;
        default:
            //all LED's off
            GPIOA->ODR |= (0x0001 << 9); //Set pin PA9 to high color: blue
            GPIOB->ODR |= (0x0001 << 4); //Set pin PB4 to high color: red
            GPIOC->ODR |= (0x0001 << 7); //Set pin PC7 to high color: green
            break;
    }
}
/*
void led_hp_update(spaceship_t sh) {
	if (sh.hp < 1) {
		GPIOB->ODR |= (0x0001 << 4); //Set pin PB4 to high color: red
		GPIOC->ODR |= (0x0001 << 7); //Set pin PC7 to high color: green
	} else {
		switch (sh.hp % 3) {
			case 0:
				//green
				GPIOB->ODR |= (0x0001 << 4); //Set pin PB4 to high color: red
				GPIOC->ODR &= ~(0x0001 << 7); //Set pin PC7 to low color: green
				break;

			case 1:
				//red
				GPIOB->ODR &= ~(0x0001 << 4); //Set pin PB4 to low color: red
				GPIOC->ODR |= (0x0001 << 7); //Set pin PC7 to high color: green
				break;

			case 2:
				//yellow
				GPIOB->ODR &= ~(0x0001 << 4); //Set pin PB4 to low color: red
				GPIOC->ODR &= ~(0x0001 << 7); //Set pin PC7 to low color: green
				break;
		}
	}
}
*/
