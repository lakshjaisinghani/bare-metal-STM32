#include "stm32f070xb.h"
#include "system_stm32f0xx.h"

#define UART_TX (14)
#define UART_RX (3)

void uart_init(void) {
    // enable usart and GPIO clocks
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    RCC->AHBENR  |= RCC_AHBENR_GPIOAEN;
    
    GPIOA->MODER    &= ~ ((0x3 << (UART_TX*2)) | (0x3<<(UART_RX*2)));
    GPIOA->MODER    |=  ((0x2 << (UART_TX*2)) | (0x2 << (UART_RX* 2))); // setting gpio in alternate mode

    // GPIOA->OTYPER   &= ~( ( 0x1 << UART_TX) |
    //                       ( 0x1 << UART_RX ) ); // open drain

    GPIOA->OSPEEDR  &= ~( ( 0x3 << ( UART_TX* 2 ) ) |
                          ( 0x3 << (UART_RX * 2 ) ) );

    GPIOA->OSPEEDR  |=  ( ( 0x2 << ( UART_TX* 2 ) ) |
                          ( 0x2 << ( UART_RX* 2 ) ) ); // low speed

    GPIOA->AFR[1] &= ~( ( 0xF << ((UART_TX%8) * 4))); // alternate function low
    GPIOA->AFR[1] |=  ( ( 0x1 << ((UART_TX%8) * 4))); // set to AF1 (USART 2)
    GPIOA->AFR[0] &= ~( ( 0xF << (UART_RX * 4 ) ) ); // this is in the datasheet
    GPIOA->AFR[0] |=  ( ( 0x1 << (UART_RX * 4 ) ) ); // not the refrence manual.


    // program the M bit to define word length
    USART2->CR1 |= (0 << USART_CR1_M0_Pos);
    USART2->CR1 |= (0 << USART_CR1_M1_Pos);

    // set baud_rate
    uint16_t uartdiv = SystemCoreClock/9600;
    USART2->BRR = uartdiv; 
    
    // Enable the USART peripheral.
    USART2->CR1 |= USART_CR1_UE;
}

/* spin for some amount of ticks */
void delay(unsigned volatile int t) {
    for (unsigned volatile int i = 0; i < t; i++);
}

// your main code 
int main(void) {

    // Init HSI Clock (internal 8MHz clock) 
    RCC->CR2 |= RCC_CR2_HSI14ON;
    while ((RCC->CR2 & RCC_CR2_HSI14RDY) == 0);

    uart_init();

    // Main loop: wait for a new byte, then echo it back.
    char rxb[6] = "LAKSH\n";

    while (1) {
        for (int i = 0; i < 7; i++) {
            USART2->CR1 |= USART_CR1_TE;
            USART2->TDR = rxb[i];
            while ((USART2->ISR & USART_ISR_TC) == 1);
            delay(1000U);
        }
        delay(100000U);
    }
}