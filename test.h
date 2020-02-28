/*
 * test.h
 *
 *  Created on: Feb 26, 2020
 *      Author: ahegazipro@live.com
 */

#ifndef UART_TEST_H_
#define UART_TEST_H_

#include "CDD_UART.h"
#include "M4MemMap.h"

/*
 * GPIO driver (AUTOSAR DIO) should handle this initialization, this is merely for testing
 * Register and memory map should be defined and initialized elsewhere
 * */

/*Register memory map*/
typedef volatile uint32* const GPIO_RegAddType;
#define PORTS_NUMBER 6u /* maximum ports number in the kit */

#define PORTA_BASE_ADDRESS 0x40004000
#define PORTB_BASE_ADDRESS 0x40005000
#define PORTC_BASE_ADDRESS 0x40006000
#define PORTD_BASE_ADDRESS 0x40007000
#define PORTE_BASE_ADDRESS 0x40024000
#define PORTF_BASE_ADDRESS 0x40025000
static const uint32 PortsBaseAddressLut[PORTS_NUMBER] =
{       PORTA_BASE_ADDRESS,
    PORTB_BASE_ADDRESS,
    PORTC_BASE_ADDRESS,
    PORTD_BASE_ADDRESS,
    PORTE_BASE_ADDRESS,
    PORTF_BASE_ADDRESS
};
#define GPIO_REG_ADDRESS(CHANNEL_ID,REG_OFFSET)\
(PortsBaseAddressLut[CHANNEL_ID] + REG_OFFSET)

/*Port Control*/
#define GPIODATA_WRITE(DATA,MASK,PORT_ID)  *((GPIO_RegAddType)(GPIO_REG_ADDRESS(PORT_ID,0x000) + (MASK << 2))) = DATA
#define GPIODATA_READ(MASK,PORT_ID)        *((GPIO_RegAddType)(GPIO_REG_ADDRESS(PORT_ID,0x000) + (MASK << 2)))
#define GPIODIR_REG(PORT_ID)               *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x400))

/*Interrupt Control*/
#define GPIOIS_REG(PORT_ID)               *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x404))
#define GPIOIBE_REG(PORT_ID)              *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x408))
#define GPIOIEV_REG(PORT_ID)              *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x40C))
#define GPIOIM_REG(PORT_ID)               *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x410))
#define GPIORIS_REG(PORT_ID)              *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x414))
#define GPIOMIS_REG(PORT_ID)              *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x418))
#define GPIOICR_REG(PORT_ID)              *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x41C))

/*Mode Control*/
#define GPIOAFSEL_REG(PORT_ID)            *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x420))
#define GPIOPCTL_REG(PORT_ID)             *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x52C))
#define GPIOADCCTL_REG(PORT_ID)           *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x530))
#define GPIODMACTL_REG(PORT_ID)           *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x534))

/*Pad control*/
#define GPIODR2R_REG(PORT_ID)           *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x500))
#define GPIODR4R_REG(PORT_ID)           *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x504))
#define GPIODR8R_REG(PORT_ID)           *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x508))
#define GPIOODR_REG(PORT_ID)            *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x50C))
#define GPIOPUR_REG(PORT_ID)            *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x510))
#define GPIOPDR_REG(PORT_ID)            *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x514))
#define GPIOSLR_REG(PORT_ID)            *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x518))
#define GPIODEN_REG(PORT_ID)            *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x51C))
#define GPIOAMSEL_REG(PORT_ID)          *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x528))

/*Commit control*/
#define GPIOLOCK_REG(PORT_ID)          *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x520))
#define GPIOCR_REG(PORT_ID)            *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x524))

/*Internal symbols*/
#define GPIO_PORT_UNLOCK_VALUE 0x4C4F434B
#define GPIO_INT_SENCE_BIT_NUM 1
#define GPIO_INT_SENCE_MASK (1 << GPIO_INT_EVENT_BIT_NUM)
#define GPIO_INT_EVENT_BIT_NUM 0
#define GPIO_INT_EVENT_MASK (1 << GPIO_INT_EVENT_BIT_NUM)
#define GPIO_INT_BE_BIT_NUM 2
#define GPIO_INT_BR_MASK (1 << GPIO_INT_BE_BIT_NUM)

/* Registers for time calculations function */
/* USING WIDE TIMER 0 A */
//*****************************************************************************
//
// Timer registers (WTIMER0)
//
//*****************************************************************************
#define SYSCTL_RCGCWTIMER_R     (*((volatile uint32_t *)0x400FE65C))
#define WTIMER0_CFG_R           (*((volatile uint32_t *)0x40036000))
#define WTIMER0_TAMR_R          (*((volatile uint32_t *)0x40036004))
#define WTIMER0_TBMR_R          (*((volatile uint32_t *)0x40036008))
#define WTIMER0_CTL_R           (*((volatile uint32_t *)0x4003600C))
#define WTIMER0_SYNC_R          (*((volatile uint32_t *)0x40036010))
#define WTIMER0_IMR_R           (*((volatile uint32_t *)0x40036018))
#define WTIMER0_RIS_R           (*((volatile uint32_t *)0x4003601C))
#define WTIMER0_MIS_R           (*((volatile uint32_t *)0x40036020))
#define WTIMER0_ICR_R           (*((volatile uint32_t *)0x40036024))
#define WTIMER0_TAILR_R         (*((volatile uint32_t *)0x40036028))
#define WTIMER0_TBILR_R         (*((volatile uint32_t *)0x4003602C))
#define WTIMER0_TAMATCHR_R      (*((volatile uint32_t *)0x40036030))
#define WTIMER0_TBMATCHR_R      (*((volatile uint32_t *)0x40036034))
#define WTIMER0_TAPR_R          (*((volatile uint32_t *)0x40036038))
#define WTIMER0_TBPR_R          (*((volatile uint32_t *)0x4003603C))
#define WTIMER0_TAPMR_R         (*((volatile uint32_t *)0x40036040))
#define WTIMER0_TBPMR_R         (*((volatile uint32_t *)0x40036044))
#define WTIMER0_TAR_R           (*((volatile uint32_t *)0x40036048))
#define WTIMER0_TBR_R           (*((volatile uint32_t *)0x4003604C))
#define WTIMER0_TAV_R           (*((volatile uint32_t *)0x40036050))
#define WTIMER0_TBV_R           (*((volatile uint32_t *)0x40036054))
#define WTIMER0_RTCPD_R         (*((volatile uint32_t *)0x40036058))
#define WTIMER0_TAPS_R          (*((volatile uint32_t *)0x4003605C))
#define WTIMER0_TBPS_R          (*((volatile uint32_t *)0x40036060))
#define WTIMER0_TAPV_R          (*((volatile uint32_t *)0x40036064))
#define WTIMER0_TBPV_R          (*((volatile uint32_t *)0x40036068))
#define WTIMER0_PP_R            (*((volatile uint32_t *)0x40036FC0))


/* number of characters to receive in receiveStringPA1 */
#define RcvCharCount 8

/* Enabling clock on PORTA GPIO, this should be handled in DIO driver */
void UART_GPIO_init();
/* send a string in port A, Internal loop back to the computer for testing */
void sendStringPA1(uint8 TXWORD[]);
/* receive a string in port A, Internal loop back to the computer for testing */
void receiveStringPA1(uint8 RXWORD[]);

/* calculate function duration in C */
void calcFnTime(uint32_t *duration, void (*fn)(void));

#endif /* UART_TEST_H_ */
