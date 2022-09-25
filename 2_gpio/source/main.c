#ifndef _VVC_MAIN_H
#define _VVC_MAIN_H 

#include <stdint.h>
#include "stm32f070xb.h"

// define GPIO mappings
#define BUTTON_PIN (13) // PC13 -> GPIOC pin 13
#define LED_PIN (5) // PA5 -> GPIOA pin 5

/* spin for some amount of ticks */
void delay(unsigned volatile int t) {
    for (unsigned volatile int i = 0; i < t; i++);
}

// your main code 
int main(void) {

    // enable GPIOs
    // RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
    // RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    // Initialize the GPIOB pins.
    // B1 should be set to 'input' mode with pull-up.
    // GPIOC->MODER  &= ~(0x3 << (BUTTON_PIN*2));
    // GPIOC->PUPDR  &= ~(0x3 << (BUTTON_PIN*2));
    // GPIOC->PUPDR  |=  (0x1 << (BUTTON_PIN*2));
    // B3 is connected to an LED on the 'Nucleo' board.
    // It should be set to push-pull low-speed output.
    GPIOA->MODER  &= ~(0x3 << (LED_PIN*2));
    GPIOA->MODER  |=  (0x1 << (LED_PIN*2));
    GPIOA->OTYPER &= ~(1 << LED_PIN);

    while (1) {
       GPIOB->ODR ^= (1 << LED_PIN);
       delay(10000000U); 
    }
}

#endif