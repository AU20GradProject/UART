/*
 * test.c
 * functions to test UART driver functionality
 *  Created on: Feb 26, 2020
 *      Author: ahegazipro@live.com
 */

#include "test.h"

/*
 * GPIO driver (AUTOSAR DIO) should handle this initialization, this is merely for testing
 * */

void UART_GPIO_init(){
    /* GPIO PORTA INIT*/
       RCGCGPIO_REG |= (1<<0);/*ENABLE CLOCK PORT A*/
       GPIOAFSEL_REG(0) |= (1<<1) | (1<<0); /* 32 Bit 0x00000011 write 1 to PORT A0,A1 to enable UART  */
       GPIODR2R_REG(0) |= (1<<1) & ~(1<<0);/* PORT A1 output transmit, A0 input receive*/

       GPIODR2R_REG(0) |= (1<<1);

       GPIODEN_REG(0)   |= (1<<0) | (1<<1); //digital enable
       GPIOAFSEL_REG(0)  |= (1<<1)|(1<<0); //alternate function

       UART_INIT();
}

void sendStringPA1(uint8 TXWORD[]){
    TX_RX_StatusType status;
    uint8 TXi = 0;



    while( TXWORD[TXi] != '\0'){

        status = UART_TX(0, TXWORD[TXi]);
        if (status != TX_RX_OK){
            while(1){} /* error while sending */
        }

        while(UART_TX_FULL(0) == 0xff); /* wait till transmitter fifo is empty*/
        TXi++;

    }

}

void receiveStringPA1(uint8 *RXWORD){
    TX_RX_StatusType status;
    uint8 RXi;
    RXi=0;

    while( RXi < RcvCharCount){

        while(UART_RX_EMPTY(0) == 0xff); //RX fifo empty, wait till it has data to be received

        status = UART_RX(0, &(RXWORD[RXi]));
        if (status != TX_RX_OK){
            while(1){} /* error while sending */
        }

        RXi++;
    }
}
