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

void led_hp_update(uint32_t tick, uint8_t hp) {
    switch (hp) {
        case 0:
            GPIOA->ODR |= (0x0001 << 9); //Set pin PA9 to high color: blue
            GPIOB->ODR |= (0x0001 << 4); //Set pin PB4 to high color: red
            GPIOC->ODR |= (0x0001 << 7); //Set pin PC7 to high color: green
            break;

        case 1:
            GPIOA->ODR |= (0x0001 << 9); //Set pin PA9 to high color: blue
            GPIOB->ODR &= ~(0x0001 << 4); //Set pin PB4 to low color: red
            GPIOC->ODR |= (0x0001 << 7); //Set pin PC7 to high color: green
            break;

        case 2:
            GPIOA->ODR |= (0x0001 << 9); //Set pin PA9 to high color: blue
            GPIOB->ODR &= ~(0x0001 << 4); //Set pin PB4 to low color: red
            if(tick % 2 == 1) {
                GPIOC->ODR &= ~(0x0001 << 7); //Set pin PC7 to low color: green
            } else {
                GPIOC->ODR |= (0x0001 << 7); //Set pin PC7 to high color: green
            }
            break;

        case 3:
            GPIOA->ODR |= (0x0001 << 9); //Set pin PA9 to high color: blue
            GPIOB->ODR &= ~(0x0001 << 4); //Set pin PB4 to low color: red
            GPIOC->ODR &= ~(0x0001 << 7); //Set pin PC7 to high color: green
            break;

        case 4:
            GPIOA->ODR |= (0x0001 << 9); //Set pin PA9 to high color: blue
            GPIOC->ODR &= ~(0x0001 << 7); //Set pin PB4 to low color: green
            if(tick % 2 == 1) {
                GPIOB->ODR &= ~(0x0001 << 4); //Set pin PC7 to low color: red
            } else {
                GPIOB->ODR |= (0x0001 << 4); //Set pin PC7 to high color: red
            }
            break;

        case 5:
            GPIOC->ODR &= ~(0x0001 << 7); //Set pin PC7 to low color: green
            break;
    }
}
