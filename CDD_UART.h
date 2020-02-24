#ifndef UART_H
#define UART_H

#include <stdint.h>
#include "CDD_UART_Cfg.h"
#include "../Common/Std_Types.h"

/* available baudrates */

#define Baud_110 110
#define Baud_300 300
#define Baud_600 600
#define Baud_1200 1200
#define Baud_2400 2400
#define Baud_4800 4800
#define Baud_9600 9600
#define Baud_14400 14400
#define Baud_19200 19200
#define Baud_38400 38400
#define Baud_57600 57600
#define Baud_115200 115200
#define Baud_128000 128000
#define Baud_256000 256000
/* baudrate enum type */
typedef VAR( uint32, TYPEDEF )   UART_BaudRate;

/* 0x00 -> 5 bits , 0x01 -> 6 bits , 0x02 -> 7 bits , 0x03 -> 8 bits*/
#define Word_5Bits 0x00u
#define Word_6Bits 0x01u
#define Word_7Bits 0x02u
#define Word_8Bits 0x03u
/* wordlength enum type  */
typedef VAR( uint8, TYPEDEF )  WordLengthType;


#define TX_RX_OK 0x00u
#define FIFO_FULL 0x01u
#define FIFO_EMPTY 0x02u
#define FRAMING_ERROR 0x03u
#define PARITY_ERROR 0x04u
#define BREAK_ERROR 0x05u
#define OVERRUN_ERROR 0x06u
#define INVALID_UART_ID 0x07u
#define NO_INIT 0xffu
/* enum UART status type */
typedef VAR( uint8, TYPEDEF ) TX_RX_StatusType;


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
extern CONST( UART_CfgType, AUTOMATIC) UART_ConfigParam [UART_GROUPS_NUMBER];

/* Initialize UART chosen modules in configuration file*/
FUNC(void, AUTOMATIC) UART_INIT();
/* Transmit Data through module group */
FUNC(TX_RX_StatusType, AUTOMATIC) UART_TX(uint8_t ModuleId,uint8_t TXByte);
/* Receive Data through module group */
FUNC(TX_RX_StatusType, AUTOMATIC) UART_RX(uint8_t ModuleId,uint8_t* RXBytePtr);

#endif
