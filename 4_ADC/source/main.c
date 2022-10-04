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
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    // set to ADC mode
    GPIOA->MODER  &= ~(0x3 << (ADC_PIN *2)); // clear all previous values (good practice)
    GPIOA->MODER  |=  (0x3 << (ADC_PIN *2)); // set to 11 -> analog mode
    
    // Init HSI Clock 
    RCC->CR2 |= RCC_CR2_HSI14ON;
    while ((RCC->CR2 & RCC_CR2_HSI14RDY) == 0);

    // ADC calibration routine
    ADC1->CR |= ADC_CR_ADCAL;
    while ((ADC1->CR & ADC_CR_ADCAL) != 0);

    // Enable ADC
    ADC1->CFGR2 &= ~ADC_CFGR2_CKMODE; // use HSI
    ADC1->CR &= ~(ADC_CR_ADDIS);      // disable ADC Disable
    ADC1->CR |= ADC_CR_ADEN;          // enable ADC
    while ((ADC1->ISR & ADC_ISR_ADRDY) == 0); // wait until ADC is enabled

    // set ADC resolution, channel (GPIO pins), and sampling time 
    ADC1->CFGR1 &= ~(ADC_CFGR1_RES);
    ADC1->CHSELR |= (1 << 5); 
    ADC1->SMPR |= 0x2;

    // APPLICATION COODE
    while (1) {
        ADC1->CR |= ADC_CR_ADSTART;  // start ADC
        while ((ADC1->ISR & ADC_ISR_EOC) == 0); // wait until end of conversion
        pot_val = ADC1->DR;  // Store the ADC conversion result
    }
}

#endif