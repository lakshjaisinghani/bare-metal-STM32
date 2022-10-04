#ifndef _ADC_H
#define _ADC_H

#include <stdint.h>
#include "stm32f070xb.h"

int pot_val;

// init ADC pins
#define ADC_PIN (5)

// your main code 
int main(void) { 

    // enable RCC 
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    // set to ADC mode
    // GPIOA->MODER  &= ~(0x3 << (ADC_PIN *2)); // clear all previous values (good practice)
    GPIOA->MODER  |=  (0x3 << (ADC_PIN *2)); // set to 11 -> analog mode
    // GPIOA->OTYPER &= ~(0x0 << ADC_PIN);      // set to 1 -> open-drain

    // calibration routine
    // ADC1->CR |= ADC_CR_ADCAL;
    // while ((ADC1->CR & ADC_CR_ADCAL) != 0) { }

    // assigning an asynchronous clock source
    RCC->AHBENR |= RCC_APB2ENR_ADC1EN;
    RCC->CR2 |= RCC_CR2_HSI14ON;
    while ((RCC->CR2 & RCC_CR2_HSI14RDY) == 0) { }

     /* (1) Select HSI14 by writing 00 in CKMODE (reset value) */
    /* (2) Select CHSEL0, CHSEL9, CHSEL10 andCHSEL17 for VRefInt */
    /* (3) Select a sampling mode of 111 i.e. 239.5 ADC clk to be greater
    than 17.1us */
    /* (4) Wake-up the VREFINT (only for VBAT, Temp sensor and VRefInt) */
    ADC1->CHSELR = (1 << 5); /* (2) */
    ADC1->SMPR |= ADC_SMPR_SMP_0 | ADC_SMPR_SMP_1 | ADC_SMPR_SMP_2; /* (3) */
    // ADC->CCR |= ADC_CCR_VREFEN; /* (4) */

    // enable ADC registers
    /*
        1. Ensure that ADRDY = 0
        2. clear ADRDY
        3. enable ADC
        4. wait till adc ready
    */
    ADC1->CFGR2 &= ~ADC_CFGR2_CKMODE; /* (1) */
    ADC1->CFGR2 |=  ADC_CFGR2_CKMODE_0;
    ADC1->CFGR1 &= ~ADC_CFGR1_AUTOFF;
    // ADC1->ISR |= ADC_ISR_ADRDY;
    while ((ADC1->ISR & ADC_ISR_ADRDY) == 0){};
    ADC1->CR |= ADC_CR_ADEN;




    while (1) {
        ADC1->CR |= ADC_CR_ADSTART; /* Start the ADC conversion */
        for (int i=0; i < 4; i++) {
            while ((ADC1->ISR & ADC_ISR_EOC) == 0) {}
            pot_val = ADC1->DR; /* Store the ADC conversion result */
        }
        ADC1->CFGR1 ^= ADC_CFGR1_SCANDIR; /* Toggle the scan direction */
    }
}

#endif