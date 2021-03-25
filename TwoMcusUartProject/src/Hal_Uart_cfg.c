/*
 * Hal_Uart_cfg.c
 *
 *  Created on: Mar 23, 2021
 *      Author: Esraa Abdelnaby
 */

#include <stdint.h>
#include "Rcc_int.h"
#include "GPIO.h"
#include "Uart.h"
#include "Hal_Uart_cfg.h"


HalUart_cfg_t H_Uart_Module[H_UART_MODULES_NUM]={
		[0]={
				{
						/*Tx pin config*/
						.mode    = GPIO_MODE_AF,
						.port    = GPIO_PORTA,
						.pinNum  = GPIO_PIN_2,
						.pupd    = GPIO_PULL_UP,
						.AF      = GPIO_AF7_USART1_3,
						.otype   = GPIO_OTYPE_PUSH_PULL,
						.ospeed  = GPIO_OSPEED_HIGH,
				},
				{
						/*Rx pin config*/
						.mode   =  GPIO_MODE_AF,
						.port   =  GPIO_PORTA,
						.pinNum =  GPIO_PIN_3,
						.pupd   =  GPIO_PULL_UP,
						.AF     =  GPIO_AF7_USART1_3,
						.otype  =  GPIO_OTYPE_PUSH_PULL,
						/*try very high*/
						.ospeed =  GPIO_OSPEED_HIGH,

				},
				{
						/*uart channel config*/
						usart_2
				}
		}
};
