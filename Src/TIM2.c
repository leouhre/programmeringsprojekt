/*
 * TIM2.c
 *
 *  Created on: 12 Jun 2020
 *      Author: leo
 */

#include "TIM2.h"

void TIM2_config() {
	RCC->APB1ENR |= RCC_APB1Periph_TIM2; // Enable clock line to timer 2;

		TIM2->CR1 &= (0x0001 << (0 * 1)); // Configure timer 2

		TIM2->CR1 &= ~(0x0001 << (11 * 1)); // Configure timer 2
		TIM2->CR1 &= ~(0x0003 << (8 * 1)); // Configure timer 2
		TIM2->CR1 &= ~(0x0001 << (7 * 1)); // Configure timer 2
		TIM2->CR1 &= ~(0x0003 << (5 * 1)); // Configure timer 2
		TIM2->CR1 &= ~(0x0001 << (4 * 1)); // Configure timer 2
		TIM2->CR1 &= ~(0x0001 << (3 * 1)); // Configure timer 2
		TIM2->CR1 &= ~(0x0001 << (2 * 1)); // Configure timer 2
		TIM2->CR1 &= ~(0x0001 << (1 * 1)); // Configure timer 2
		TIM2->ARR = 639999; // Set auto reload value
		TIM2->PSC = 0;

		TIM2->DIER |= 0x0001; // Enable timer 2 interrupts

		NVIC_SetPriority(TIM2_IRQn, 0); // Set interrupt priority
		NVIC_EnableIRQ(TIM2_IRQn);// Enable interrupt

		TIM2->CR1 |= (0x0001 << (0 * 1)); // Configure timer 2
}

void TIM2_IRQHandler(void) {
	//Do whatever you want here, but make sure it doesn’t take too much time!
	//Kopier evt. den her ind i main og brug et globalt flag
	TIM2->SR &= ~0x0001; // Clear interrupt bit}
}

