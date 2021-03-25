/*
 * Hal_Uart.c
 *
 *  Created on: Mar 23, 2021
 *      Author: Esraa Abdelnaby
 */

#include <stdint.h>
#include "../../Lib/bit.h"
#include "Error_codes.h"
#include "Rcc_int.h"
#include "GPIO.h"
#include "NVIC_int.h"
#include "SysTick_int.h"
#include "SwTimer.h"
#include "Frame.h"
#include "Uart.h"
#include "Hal_Uart_cfg.h"
#include "Hal_Uart_int.h"

/*instance index */
uint8_t module_idx;


/*
 * HalUart_Init()
 * * enable Rcc peripheral that enable gpio
 * * init Rx and Tx Gpio pins
 * * init uart
 * * init NVIC in Interrupt based mode
 */

static void recive_done(void);

uint8_t HalUart_Init(void)
{
	/*Enbale rcc peripherals for gpio*/
	Enable_RCC_AHB1_PERI(RCC_AHB1_PERI_GPIOAEN);
	/*config rx pin , tx pin and uart channel*/
	for(;module_idx<H_UART_MODULES_NUM;module_idx++)
	{
		GPIO_InitPin(&H_Uart_Module[module_idx].tx_pin_cfg);
		GPIO_InitPin(&H_Uart_Module[module_idx].rx_pin_cfg);



#if UART_MODE == UART_MODE_EVENT_BASED
		IRQn_t Uart_channel;
		uint8_t id = H_Uart_Module[module_idx].Uart_Channel;
		switch(id)
		{
		case usart_1:
			Enable_RCC_APB2_PERI(RCC_APB2_PERI_USART1EN);
			Uart_channel = _IRQn_USART1;
			break;
		case usart_2:
			Enable_RCC_APB1_PERI(RCC_APB1_PERI_USART2EN);
			Uart_channel = _IRQn_USART2;
			break;
		case usart_3:
			Enable_RCC_APB1_PERI(RCC_APB1_PERI_USART3EN);
			Uart_channel = _IRQn_USART3;
			break;
		case usart_6:
			Enable_RCC_APB2_PERI(RCC_APB2_PERI_USART6EN);
			Uart_channel = _IRQn_USART6;
			break;
		case uart_4:
			Enable_RCC_APB1_PERI(RCC_APB1_PERI_UART4EN);
			Uart_channel = _IRQn_UART4;
			break;
		case uart_5:
			Enable_RCC_APB1_PERI(RCC_APB1_PERI_UART5EN);
			Uart_channel = _IRQn_UART5;
			break;

		default:
			return RT_ERROR;
		}

		Usart_Init(H_Uart_Module[module_idx].Uart_Channel);
		Uart_SetRecvCbf(H_Uart_Module[module_idx].Uart_Channel,recive_done);
		NVIC_EnableIRQ(Uart_channel);
#endif
	}


	return RT_SUCCESS;
}

buffer_t tx_buffer;
buffer_t rx_buffer;
buffer_t Hal_recBuffer;

/*HalUart_SendBuffer()
 * if time based :
 * => init swTimer
 * => assign the cbf and set its mode
 * => assign user rx_buffer to the cbf function
 * */
static uint8_t  Hal_Uart_Buffer[FRAME_SIZE];
uint8_t HalUart_SendBuffer(uint8_t * UserBuffer, uint16_t size,Hal_Uart_Module_idx_t HalUartModule_idx)
{
	uint8_t state = RT_ERROR;
	uint16_t newsize;
	state = Frame_Construct_buffer(UserBuffer,size,Hal_Uart_Buffer,&newsize);
	if(state == RT_SUCCESS)
	{
		state = Uart_SendBuff(H_Uart_Module[HalUartModule_idx].Uart_Channel,Hal_Uart_Buffer,newsize);
		tx_buffer.data = Hal_Uart_Buffer;
		tx_buffer.idx = HalUartModule_idx;
		tx_buffer.size = newsize;
	}
	return state;
}

uint8_t HalUart_SendRawData(uint8_t * UserBuffer, uint16_t size,Hal_Uart_Module_idx_t HalUartModule_idx)
{
	uint8_t state = RT_ERROR;
	state = Uart_SendBuff(H_Uart_Module[HalUartModule_idx].Uart_Channel,UserBuffer,size);
	tx_buffer.data = UserBuffer;
	tx_buffer.idx = HalUartModule_idx;
	tx_buffer.size = size;
	return state;
}

uint8_t HalUart_ReciveRawData(uint8_t * UserBuffer,uint16_t size,Hal_Uart_Module_idx_t HalUartModule_idx)
{
	uint8_t state = RT_ERROR;
	uint8_t Rec_size = FRAME_SIZE;
	uint8_t checkSum;
	state = Uart_RecvBuff(H_Uart_Module[HalUartModule_idx].Uart_Channel,UserBuffer,Rec_size);
	if(state == RT_SUCCESS)
	{
		checkSum = calc_checkSum(Sig,Rec_size);
		rx_buffer.data = UserBuffer;
		rx_buffer.idx = HalUartModule_idx;
		rx_buffer.size = Rec_size;
		rx_buffer.size++;
		rx_buffer.data[size-1] = checkSum;
	}
	return state;
}



/*HalUart_ReciveBuffer()
 * if time based :
 * => init swTimer
 * => assign the cbf and set its mode
 * => assign user tx_buffer to the cbf function
 * */

uint8_t HalUart_ReciveBuffer(uint8_t * UserBuffer,uint16_t size,Hal_Uart_Module_idx_t HalUartModule_idx)
{
	uint8_t state = RT_ERROR;
	uint8_t Rec_size = FRAME_SIZE;
	state = Uart_RecvBuff(H_Uart_Module[HalUartModule_idx].Uart_Channel,UserBuffer,Rec_size);
	if(state == RT_SUCCESS)
	{
		rx_buffer.data = UserBuffer;
		rx_buffer.idx = HalUartModule_idx;
		rx_buffer.size = Rec_size;
	}
	return state;
}

static void recive_done()
{
	uint8_t state;
	state = Frame_Deconstruct_buffer(rx_buffer.data,rx_buffer.size,Hal_recBuffer.data);
	if(Notify_recieve_done && state == RT_SUCCESS)
		Notify_recieve_done();
}
void HalUart_SetReciveCbf(HuartCbf userCbf)
{
	Notify_recieve_done = userCbf;
}

void HalUart_SetSendCbf(HuartCbf userCbf)
{
	Uart_SetSendCbf(H_Uart_Module[tx_buffer.idx].Uart_Channel,userCbf);
}


void HalUart_SendSig(Hal_Uart_Module_idx_t idx)
{
	Uart_SendBuff(H_Uart_Module[idx].Uart_Channel,Sig,SIG_BYTES_NUM);
}
void HalUart_RecieveSig(Hal_Uart_Module_idx_t idx)
{
	Uart_RecvBuff(H_Uart_Module[idx].Uart_Channel,Sig,SIG_BYTES_NUM);
}
