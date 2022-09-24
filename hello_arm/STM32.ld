/*
    Here I am using a Nucleo-F070RB : https://os.mbed.com/platforms/ST-Nucleo-F070RB/
    Datasheet: https://datasheetspdf.com/pdf-file/1308606/STMicroelectronics/STM32F070RB/1
*/
/* FLASH: 128Kb  0x0800 0000 - 0x0800 03FF (page 0) each 1k bytes long*/
/* SRAM: 16Kb and starts at  0x2000 0000 */
/* end of program stack 0x2000 0000 + 16Kb*/
_estack = 0x20004000; 

MEMORY
{
    FLASH ( rx )      : ORIGIN = 0x08000000, LENGTH = 128K
    RAM ( rxw )       : ORIGIN = 0x20000000, LENGTH = 16K
}

