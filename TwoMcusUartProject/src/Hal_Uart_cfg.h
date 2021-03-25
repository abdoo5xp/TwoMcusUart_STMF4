/*
 * Hal_Uart_cfg.h
 *
 *  Created on: Mar 23, 2021
 *      Author: Esraa Abdelnaby
 */

#ifndef HAL_UART_CFG_H_
#define HAL_UART_CFG_H_

#define H_UART_MODULES_NUM 1

typedef struct{
	gpio_pinConfig_t tx_pin_cfg;
	gpio_pinConfig_t rx_pin_cfg;
	usart_Id_e Uart_Channel;
}HalUart_cfg_t;

extern HalUart_cfg_t H_Uart_Module[H_UART_MODULES_NUM];

#endif /* HAL_UART_CFG_H_ */
