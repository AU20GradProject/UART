#ifndef UART_H
#define UART_H

#include <stdint.h>
#include "CDD_UART_Cfg.h"

typedef enum {Baud_110 = 110 ,Baud_300 = 300,Baud_600 = 600 ,Baud_1200 = 1200 ,Baud_2400 = 2400 ,Baud_4800 = 4800 ,Baud_9600 = 9600,Baud_14400 = 14400,Baud_19200 = 19200,Baud_38400 = 38400,Baud_57600 = 57600,Baud_115200 = 115200,Baud_128000 = 128000,Baud_256000 = 256000 } UART_BaudRate;

/* 0x00 -> 5 bits , 0x01 -> 6 bits , 0x02 -> 7 bits , 0x03 -> 8 bits*/
typedef enum {Word_5Bits = 0,Word_6Bits,Word_7Bits,Word_8Bits} WordLengthType;

typedef enum {TX_RX_OK = 0,FIFO_FULL,FIFO_EMPTY,FRAMING_ERROR,PARITY_ERROR,BREAK_ERROR,OVERRUN_ERROR,NO_INIT } TX_RX_StatusType;


typedef struct
{
    uint8_t UARTModule; /* UART modules from 0 to 7 */

    UART_BaudRate UART_BaudRate;
    uint8_t UART_ClockMhz; /* In MHz */

    uint8_t HSE;/* HighSpeedEnable 0-> clkDiv: 16, 0xff-> clkDiv: 8.*/

    uint8_t StopBits; /*0-> 1 stopbit , 0xff-> 2 stop bits*/

    uint8_t Parity; /* 0xff -> Enable parity , 0 -> disable parity*/
    uint8_t ParityType; /* 0 -> odd, 0xff: even*/
    uint8_t StickParity; /* 0xff -> Enable Stick parity , 0 -> disable Stick parity*/

    uint8_t Fifo; /* 0xff -> Enable FIFO , 0 -> disable FIFO*/

    WordLengthType WordLength;

    uint8_t UART_CC; /* 0x00 : system clock, 0xff PIOSC*/

}UART_CfgType;

/* defined at UART_Cfg.c */
extern const UART_CfgType UART_ConfigParam [UART_GROUPS_NUMBER];


void UART_INIT();
/* Transmit Data through group */
TX_RX_StatusType UART_TX(uint8_t ModuleId,uint8_t TXByte);
/* Receive Data through group */
TX_RX_StatusType UART_RX(uint8_t ModuleId,uint8_t* RXBytePtr);

#endif
