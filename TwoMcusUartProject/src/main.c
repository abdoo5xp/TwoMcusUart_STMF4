/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// ----------------------------------------------------------------------------
#include <stdint.h>
#include <diag/Trace.h>
#include "bit.h"
#include "Bit_Mask.h"
#include "Error_codes.h"
#include "NVIC_int.h"
#include "GPIO.h"
#include "Rcc_int.h"
#include "SwTimer.h"
#include "Uart.h"


// ----------------------------------------------------------------------------
//
// Standalone STM32F4 empty sample (trace via DEBUG).
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the DEBUG output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

typedef struct {
	uint32_t startOfValidRange;
	uint32_t endOfValidRange;
	uint32_t startOfInvalidRange;
	uint32_t endOfInvalidRange;
}test_t ;



void test_rcv(void){
	trace_printf("Receiving is done \n ");
}

void test_send(void){
	trace_printf("Sending is done \n ");
}
int
main(int argc, char* argv[])
{
  // At this stage the system clock should have already been configured
  // at high speed.
	/*Don't forget to enable the NVIC for USART */

	uint32_t CurrentSysClkFreq;

		Enable_RCC_AHB1_PERI(RCC_AHB1_PERI_GPIOAEN);
		Enable_RCC_APB1_PERI(RCC_APB1_PERI_USART2EN);

		Set_RCC_CFGR_PPRE1(RCC_CFGR_PPRE1_DIV_4);

//		RCC_GetCurrentSysClkFreq(&CurrentSysClkFreq);
//		RCC_GetAHBFreqMhz(&CurrentSysClkFreq);

		uint32_t sysfreq = Get_RCC_AHB_Freq();


		gpio_pinConfig_t Rx2_pin ={
				.mode   =  GPIO_MODE_AF,
				.port   =  GPIO_PORTA,
				.pinNum =  GPIO_PIN_3,
				.pupd   =  GPIO_PULL_UP,
				.AF     =  GPIO_AF7_USART1_3,
				.otype  =  GPIO_OTYPE_PUSH_PULL,
				/*try very high*/
				.ospeed =  GPIO_OSPEED_HIGH,
		};
		gpio_pinConfig_t Tx2_pin ={
				.mode    = GPIO_MODE_AF,
				.port    = GPIO_PORTA,
				.pinNum  = GPIO_PIN_2,
				.pupd    = GPIO_PULL_UP,
				.AF      = GPIO_AF7_USART1_3,
				.otype   = GPIO_OTYPE_PUSH_PULL,
				.ospeed  = GPIO_OSPEED_HIGH,
		};

		uint8_t buffer [8] ={
				'f',
				'r',
				'f',
				'r',
				'f',
				'r',
				'f',
				'r'
		};
		uint8_t buffer2[8] ;
		GPIO_InitPin(&Tx2_pin);
		GPIO_InitPin(&Rx2_pin);

		Usart_Init(usart_2);
		// Infinite loop

		NVIC_EnableIRQ(_IRQn_USART2);
		Uart_SetRecvCbf(usart_2, test_rcv);
		Uart_SetSendCbf(usart_2, test_send);

		Uart_SendBuff(usart_2,buffer, 8);
		Uart_RecvBuff(usart_2,buffer2, 8);
  while (1)
    {
	  trace_printf("shit\n");
//		Uart_SendBuff(usart_2,buffer, 8);
       // Add your code here.
    }
}


#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
