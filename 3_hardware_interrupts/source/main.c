#ifndef _VVC_MAIN_H
#define _VVC_MAIN_H 

#include <stdint.h>
#include "stm32f070xb.h"


// define GPIO mappings
#define BUTTON_PIN (13) // PC13 -> GPIOC pin 13
#define LED_PIN (5)     // PA5 -> GPIOA pin 5

void EXTI4_15_IRQHandler(void);

// define global variables
volatile unsigned char led_on;


// your main code 
int main(void) {

    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
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
  
    /*
        select fource of interrupt:
        ---------------------------
        make sure to use onply 1 pin at a time
        even though you have different banks (GPIOA-D)
    */
    // Set SYSCFG to connect the button EXTI line to GPIOC pin 13.
    // see 9.1.5 in reference manual
    // need to write x010 to bits 7-4 of SYSCFG_EXTICR4 
    SYSCFG->EXTICR[3] &= ~(0xF << ((BUTTON_PIN % 4) * 4)); 
    SYSCFG->EXTICR[3] |=  (0x2 << ((BUTTON_PIN % 4) * 4)); 

    /*
        These are the interrupt regesters that handle
        the schedule. 
        IMR -> enable
        RTSR -> rising edge
        FTSR -> falling edge
        SWIER -> software based intterup (sets pending bit and acts like a hardware ISR)
        PR -> pending register
    */
    // Setup the button's EXTI line as an interrupt.
    EXTI->IMR  |=  (1 << BUTTON_PIN);
    // Disable the 'rising edge' trigger (button release).
    EXTI->RTSR &= ~(1 << BUTTON_PIN);
    // Enable the 'falling edge' trigger (button press).
    EXTI->FTSR |=  (1 << BUTTON_PIN);

    // Enable the NVIC interrupt for EXTI0 and EXTI1 at minimum priority.
    NVIC_SetPriority(EXTI4_15_IRQn, 0x03);
    NVIC_EnableIRQ(EXTI4_15_IRQn);
    led_on = 0;

    while (1) {
        if (led_on) {
            GPIOA->ODR |= (1 << LED_PIN);
        }
        else {
            GPIOA->ODR &= 0; 
        }

    }
}

void EXTI4_15_IRQHandler(void) {
    if (EXTI->PR & (1 << BUTTON_PIN)) {
       // clear the EXTI status flag
       EXTI->PR |= (1 << BUTTON_PIN);

       // toggle led on
       led_on = !led_on; 
    }
}

#endif