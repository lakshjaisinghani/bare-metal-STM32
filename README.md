# STM32 from scratch

Firmware is a type of software that is programmed into a ROM (read-only memory). It provides specific low level control over hardware, and can
be found anywhere from your webcam and keyboard, to your car. 

These systems are called embedded systems and run on a Microcontroller (MCU). 

Learning about emedded systems has increased my understanding on how computers work 10x and has made me a better software engineer. It might sound scary at first, when we talk about writing to registers, bootloaders, flash, compiler optimisation, etc, but in reality they are easy to understand concepts (except that last one: i lied) at least from a surface level.

There is no end to each topic, as it could be broken down into lower an lower levels, and for more complex hardware. But the bare metal firmware level is intreseting, and all you need to know to get paid for MOST embedded systems roles. This is as deep as this project will take you.

The MCUs used in this project are the STM32F0 and F4 chips in the form of a Nucleo dev board and a blue pill respectively.

### Aside
This project is a collection of ideas and work from books, blogs, and GitHub repos. All I have done is funneled all that knowledge into one project. 

Please take a look at the refrences for the original resources.

## Topics

1. Intro to ARM

2. Running a C project

3. OpenOCD and embedded debugging in VSCode
    
4. Using GPIOs

5. Hardware Interrupts

6. ADCs and DACs

7. Serial communication (USART)

8. I2C

9. CANBUS

10. SPI

11. USB

12. Timers and Timer Interrupts

13. Direct Memory Access (DMA)

14. Real Time Clocks

15. Bootloaders


## Refrences

- [arm Developer documentation](https://developer.arm.com/documentation)
- [Vivonomicon's blogs](https://vivonomicon.com/)
- [HACKADAY articles](https://hackaday.com/2020/11/17/bare-metal-stm32-from-power-up-to-hello-world/)
- [Edward Lu's STM32-From-Scratch repo](https://github.com/EdwardLu2018/STM32-From-Scratch)

## TODO

- [X] Run thumb assembly

- [X] Run a c program

    - [ ] Memory allocation 

- [X] GPIO 

    - [ ] PWM

- [X] hardware interrupts

- [X] ADCs

- [ ] Serial communication

- [ ] Debugging using openOCD and GDB

- [ ] DACs

- [ ] timers and timer-interrupts

- [ ] real-time clocks

- [ ] DMA

- [ ] Bootloader

- [ ] I2C

- [ ] USB

