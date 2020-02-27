#include "CDD_UART.h"
#include "M4MemMap.h" /* for UART initialization registers*/
#include "CDD_UART_Internal.h"

/* UART Addresses lookup table */
VAR( static const uint32_t, static ) ModulesBaseAddressLut[MODULES_NUMBER] =
{
        UART0_BASE_ADDRESS,
        UART1_BASE_ADDRESS,
        UART2_BASE_ADDRESS,
        UART3_BASE_ADDRESS,
        UART4_BASE_ADDRESS,
        UART5_BASE_ADDRESS,
        UART6_BASE_ADDRESS,
        UART7_BASE_ADDRESS
};

/* UART groups initialization status */
VAR(static uint8_t, static )UART_GroupState[UART_GROUPS_NUMBER] = {0};


FUNC(void, AUTOMATIC) UART_INIT(){
    VAR(uint16_t, AUTOMATIC) IntBrd;
    VAR(uint8_t, AUTOMATIC) FracBrd;
    VAR(uint8_t, AUTOMATIC) LoopIndex;
    VAR(uint8_t, AUTOMATIC) ErrorFlag = 0;

    VAR(double, AUTOMATIC) Brd; /* Baud Rate divsor */
    CONST(UART_CfgType *, AUTOMATIC) Init_CfgPtr;
    for(LoopIndex = 0; (LoopIndex < UART_GROUPS_NUMBER) && (ErrorFlag == 0); LoopIndex ++)
    {
        if(UART_ConfigParam[LoopIndex].UARTModule < MODULES_NUMBER)
        {
            Init_CfgPtr = & UART_ConfigParam[LoopIndex];
     /* Enabling the clock on the UART module.*/
        RCGCUART_REG |= ( 1 << ( Init_CfgPtr->UARTModule ) );

        Brd = (double) ( Init_CfgPtr->UART_ClockMhz * 1000000 ) / (double)( ( Init_CfgPtr->HSE ? 8 : 16 ) * (Init_CfgPtr->UART_BaudRate) );
        IntBrd = (uint16_t) Brd;
        FracBrd = (uint8_t) ( ( Brd - IntBrd ) * 64 + 0.5);

        /*Disable the UART : UARTEN bit 0 */
        UARTCTL_REG( Init_CfgPtr->UARTModule ) &= ~0x01;

        /* UART configuration*/
            /* baud rate */
        UARTIBRD_REG( Init_CfgPtr->UARTModule ) = IntBrd;
        UARTFBRD_REG( Init_CfgPtr->UARTModule ) = FracBrd;
            /* Line control */
                /* Reset UARTLCRH bits  1111 1110 */
        UARTLCRH_REG( Init_CfgPtr->UARTModule ) &= ~(0xfe);
                /* Configure UARTLCRH */
        UARTLCRH_REG( Init_CfgPtr->UARTModule ) |= ( Init_CfgPtr->Parity & 0x02 );
        UARTLCRH_REG( Init_CfgPtr->UARTModule ) |= (Init_CfgPtr->ParityType & 0x04 );
        UARTLCRH_REG( Init_CfgPtr->UARTModule ) |= (Init_CfgPtr->StopBits & 0x08);
        UARTLCRH_REG( Init_CfgPtr->UARTModule ) |= (Init_CfgPtr->Fifo & 0x10);
        UARTLCRH_REG( Init_CfgPtr->UARTModule ) |= (Init_CfgPtr->WordLength << 5);
        UARTLCRH_REG( Init_CfgPtr->UARTModule ) |= ( Init_CfgPtr->StickParity & 0x80 );

            /* UART CLOCK */
        UARTCC_REG ( Init_CfgPtr->UARTModule ) = ( Init_CfgPtr->UART_CC ? 0x05 : 0x00 );

            /* DMA configuration */

        /* Enable UART */
        UARTCTL_REG( Init_CfgPtr->UARTModule ) |= 0x01;

        /* OK */
        UART_GroupState[LoopIndex] = 1;
        /*
        UARTLCRH_REG( Init_CfgPtr->UARTModule ) = Init_CfgPtr->Parity ? ( UARTLCRH_REG( Init_CfgPtr->UARTModule) | 0x02 ) : ( UARTLCRH_REG( Init_CfgPtr->UARTModule) & ~0x02 );
        UARTLCRH_REG( Init_CfgPtr->UARTModule ) = Init_CfgPtr->ParityType ? ( UARTLCRH_REG( Init_CfgPtr->UARTModule) | 0x04 ) : ( UARTLCRH_REG( Init_CfgPtr->UARTModule) & ~0x04 );
        UARTLCRH_REG( Init_CfgPtr->UARTModule ) = Init_CfgPtr->StopBits ? ( UARTLCRH_REG( Init_CfgPtr->UARTModule) | 0x08 ) : ( UARTLCRH_REG( Init_CfgPtr->UARTModule) & ~0x08 );
        UARTLCRH_REG( Init_CfgPtr->UARTModule ) = Init_CfgPtr->Fifo ? ( UARTLCRH_REG( Init_CfgPtr->UARTModule) | 0x10 ) : ( UARTLCRH_REG( Init_CfgPtr->UARTModule) & ~0x10 );
    */  }else {
            /* Invalid UART ID*/
            ErrorFlag = 1;
        }
    }
}

/* Transmit Data through group */
FUNC(TX_RX_StatusType, AUTOMATIC) UART_TX(uint8_t ModuleId,uint8_t TXByte){
    VAR(TX_RX_StatusType, AUTOMATIC) status;
    CONST(UART_CfgType *, AUTOMATIC) UART_Info;

    if ( ModuleId < UART_GROUPS_NUMBER ){
        if( (UART_GroupState[ModuleId]==1 ) ){
        UART_Info = &  UART_ConfigParam[ModuleId];

        /// 0010 0000 TXFF UART Transmit FIFO Full pin 5
            if( ( UARTFR_REG( UART_Info->UARTModule ) & (0x20) ) == 0x00 ){
                UARTDR_REG( UART_Info->UARTModule ) = TXByte;
                status = TX_RX_OK;
            }else {
                status = FIFO_FULL;
            }

        }else {
            /* I may call the initialization function here */
            status = NO_INIT;
        }
    }else {
        /* Invalid UART ID*/
        status = INVALID_UART_ID;
    }
    return status;
}
/* Receive Data through group */
FUNC(TX_RX_StatusType, AUTOMATIC) UART_RX(uint8_t ModuleId,uint8_t* RXBytePtr){
    VAR(TX_RX_StatusType, AUTOMATIC) status;
    CONST(UART_CfgType *, AUTOMATIC) UART_Info;

    if ( ModuleId < UART_GROUPS_NUMBER ){
        if( (UART_GroupState[ModuleId]==1 ) ){
            UART_Info = &  UART_ConfigParam[ModuleId];

        /// 0000 1000 RXFE UART Receive FIFO Empty pin 4 : 0001 0000
        if( ( UARTFR_REG( UART_Info->UARTModule ) & (0x10) ) == 0 ){

            if ( (UARTRSR_REG( UART_Info->UARTModule ) & (0x01)) != 0 ){
                status = FRAMING_ERROR;
            }else if ( (UARTRSR_REG( UART_Info->UARTModule ) & (0x02)) != 0 ){
                status = PARITY_ERROR;
            }else if ( (UARTRSR_REG( UART_Info->UARTModule ) & (0x04)) != 0 ){
                status = BREAK_ERROR;
            }else if ( (UARTRSR_REG( UART_Info->UARTModule ) & (0x08)) != 0 ){
                status = OVERRUN_ERROR;
            }else {
                *RXBytePtr = UARTDR_REG( UART_Info->UARTModule ); //( UARTDR_REG( UART_Info->UARTModule ) & 0x0ff );
                status = TX_RX_OK;
            }
        }else {
            status = FIFO_EMPTY;
        }
    }else {
        /* I may call the initialization function here */
        status = NO_INIT;
    }

    }else {
    /* Invalid UART ID*/
        status = INVALID_UART_ID;
    }
return status;

}

FUNC(uint8_t, AUTOMATIC) UART_TX_FULL(uint8_t ModuleId){
    return (TXFIFOFULL(ModuleId) ? 0xff : 0x00);
}

FUNC(uint8_t, AUTOMATIC) UART_RX_EMPTY(uint8_t ModuleId){
    return (RXFIFOEMPTY(ModuleId) ? 0xff : 0x00);
}
