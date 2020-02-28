

/**
 * main.c
 */

#include "test.h"

int main(void)
    {
    UART_GPIO_init();
    uint8 TXWORD[RcvCharCount] = "TEST8ch"; /* string 9 chars*/

    while(1){
        sendStringPA1(TXWORD); /* send a string first */
        receiveStringPA1((uint8 *)TXWORD); /*receive a string 8 chars*/
    }
#if 0
    TX_RX_StatusType statusTX, statusRx;
    uint32 i;
    uint8 TXbyte, TXbytePrev = 0; /*a byte received to be redirected*/

    sendStringPA1(TXWORD); /* send a string first */
    TXbyte='A';

    for(i=0;i<100000;i++){
        //wait for a while before checking the RX
    }

    while(1){

        while(UART_RX_EMPTY(0) == 0xff); //RX fifo empty, wait till it has data to be received
        statusRx = UART_RX(0, &TXbyte); /*receive whatever is sent and transmit it*/
        if (statusTX != TX_RX_OK){
            while(1){} /* error while sending */
        }

        /* not to send the same byte multiple times*/
        if(TXbytePrev != TXbyte){
            statusTX = UART_TX(0, '\n');/*send a new line*/
        }
        while(UART_TX_FULL(0) == 0xff); /* wait till the transmitter is free */

        statusTX = UART_TX(0, TXbyte);/*send a new line*/
        if (statusTX != TX_RX_OK){
            while(1){} /* error while sending */
        }

        TXbytePrev = TXbyte;
    }
   return 0;
#endif
}
