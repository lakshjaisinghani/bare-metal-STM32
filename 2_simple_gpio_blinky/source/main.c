#ifndef _VVC_MAIN_H
#define _VVC_MAIN_H 

#include <stdint.h>
#include "stm32f070xb.h"

// define GPIO mappings
#define BUTTON_PIN (13) // PC13 -> GPIOC pin 13
#define LED_PIN (5)     // PA5 -> GPIOA pin 5

/* spin for some amount of ticks */
void delay(unsigned volatile int t) {
    for (unsigned volatile int i = 0; i < t; i++);
}

// your main code 
int main(void) {

    // enable RCC 
    // this is not really namdatory
    RCC->CR |= RCC_CR_HSEON;             // (1u << 16)
    while(!(RCC->CR & RCC_CR_HSERDY)){}  // if this can't handle it RCC->CFGR |= (1 << 0)

    // enable GPIOs
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    // init button
    GPIOC->MODER  &= ~(0x3 << (BUTTON_PIN*2)); // set to 00 -> input mode
    GPIOC->PUPDR  &= ~(0x3 << (BUTTON_PIN*2)); // clear all previous values (good practice)
    GPIOC->PUPDR  |=  (0x1 << (BUTTON_PIN*2)); // set to 01 -> pull up
    
    // init led 
    GPIOA->MODER  &= ~(0x3 << (LED_PIN*2)); // clear all previous values (good practice)
    GPIOA->MODER  |=  (0x1 << (LED_PIN*2)); // set to 01 -> output mode
    GPIOA->OTYPER &= ~(1 << LED_PIN);       // set to 1 -> open-drain

    while (1) {
        uint32_t idr_val = ~(GPIOC->IDR);
        uint32_t button_press = (1 << BUTTON_PIN);

        if (idr_val & button_press){
            GPIOA->ODR |= (1 << LED_PIN);
        } 
        else {
            GPIOA->ODR &= 0;
        }
    }
}

#endif