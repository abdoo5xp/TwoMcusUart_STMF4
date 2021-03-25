/*
 * Hal_Uart_int.h
 *
 *  Created on: Mar 23, 2021
 *      Author: Esraa Abdelnaby
 */

#ifndef HAL_UART_INT_H_
#define HAL_UART_INT_H_

#define FRAME_SIZE 13

typedef enum{
	Hal_Uart_Module_1,
	Hal_Uart_Module_2,
	Hal_Uart_Module_3,
	Hal_Uart_Module_4,
	Hal_Uart_Module_5,
	Hal_Uart_Module_6
}Hal_Uart_Module_idx_t;



typedef struct{
	uint8_t * data;
	Hal_Uart_Module_idx_t idx;
	uint16_t size;
}buffer_t;

typedef void (*HuartCbf) (void);
HuartCbf Notify_recieve_done;

uint8_t HalUart_Init(void);

extern uint8_t HalUart_SendBuffer(uint8_t * UserBuffer,uint16_t size,Hal_Uart_Module_idx_t HalUartModule_idx);

extern uint8_t HalUart_ReciveBuffer(uint8_t * UserBuffer,uint16_t size,Hal_Uart_Module_idx_t HalUartModule_idx);
extern void HalUart_SetReciveCbf(HuartCbf userCbf);

extern void HalUart_SetSendCbf(HuartCbf userCbf);

extern uint8_t HalUart_ReciveRawData(uint8_t * UserBuffer,uint16_t size,Hal_Uart_Module_idx_t HalUartModule_idx);

extern uint8_t HalUart_SendRawData(uint8_t * UserBuffer, uint16_t size,Hal_Uart_Module_idx_t HalUartModule_idx);

extern void HalUart_SendSig(Hal_Uart_Module_idx_t idx);
extern void HalUart_RecieveSig(Hal_Uart_Module_idx_t idx);

#endif /* HAL_UART_INT_H_ */
