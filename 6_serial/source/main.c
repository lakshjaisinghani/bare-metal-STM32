#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "stm32f070xb.h"

#define UART_TX (2)
#define UART_RX (3)

void uart_init(void) {
    // enable usart and GPIO clocks
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    RCC->AHBENR  |= RCC_AHBENR_GPIOAEN;
    
    // Configure pins A2, A15 for USART2 (AF7, AF3).
    GPIOA->MODER    &= ~ ((0x3 << (UART_TX*2)) | (0x3<<(UART_RX*2)));
    GPIOA->MODER    |=  ((0x2 << (UART_TX*2)) | (0x2 << (UART_RX* 2))); // setting gpio in alternate mode

    GPIOA->OTYPER   &= ~( ( 0x1 << UART_TX) |
                          ( 0x1 << UART_RX ) ); // open drain

    GPIOA->OSPEEDR  &= ~( ( 0x3 << ( UART_TX* 2 ) ) |
                          ( 0x3 << (UART_RX * 2 ) ) );

    GPIOA->OSPEEDR  |=  ( ( 0x2 << ( UART_TX* 2 ) ) |
                          ( 0x2 << ( UART_RX* 2 ) ) ); // low speed
    
    GPIOA->AFR[0] &= ~( ( 0xF << (UART_TX * 4 ) ) ); // alternate function low
    GPIOA->AFR[0] |=  ( ( 0x1 << (UART_TX * 4 ) ) ); // set to AF1 (USART 2)
    GPIOA->AFR[0] &= ~( ( 0xF << (UART_RX * 4 ) ) ); // this is in the datasheet
    GPIOA->AFR[0] |=  ( ( 0x1 << (UART_RX * 4 ) ) ); // not the refrence manual.

    // set baud_rate
    uint16_t uartdiv = 833;
    USART2->BRR = uartdiv; 

    // Enable the USART peripheral.
    USART2->CR1 |= ( USART_CR1_RE | USART_CR1_TE | USART_CR1_UE );
}

// your main code 
int main(void) {

    uart_init();

    // Main loop: wait for a new byte, then echo it back.
    char rxb = 'A';
    
    while (1) {
        USART2->TDR = rxb;
        while ((USART2->ISR & USART_ISR_TC) == 1);
    }
}