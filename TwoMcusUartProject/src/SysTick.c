/*
 * SysTick.c
 *
 *  Created on: Mar 11, 2021
 *      Author: Esraa Abdelnaby
 */

#include <stdint.h>
#include "../../Lib/bit.h"
#include <diag/Trace.h>
#include "SysTick_cfg.h"
#include "SysTick_int.h"



typedef struct{
	uint32_t STK_CTRL;
	uint32_t STK_LOAD;
	uint32_t STK_VAL;
	uint32_t STK_CALIB;
}SysTick_Type;

volatile SysTick_Type * SysTick =(volatile SysTick_Type*)(0xE000E010);
uint32_t global_freq;

void SysTick_init(uint32_t freq)
{
	uint32_t temp_reg;
	global_freq = freq;

	/*reset control register*/
	SysTick->STK_CTRL = 0;

	/*choose clk source*/
#if SYSTICK_CLK_SRC == STK_CLKSRC_AHB
	temp_reg=SysTick->STK_CTRL;
	temp_reg &= ~(STK_CTRL_CLKSOURCE);
	temp_reg |= STK_CTRL_CLKSOURCE;
	SysTick->STK_CTRL = temp_reg;

#elif SYSTICK_CLK_SRC == STK_CLKSRC_AHB_PRESCALED_8
	temp_reg=SysTick->STK_CTRL;
	temp_reg &= ~(STK_CTRL_CLKSOURCE);
	SysTick->STK_CTRL = temp_reg;
	global_freq/=8;
#endif

	/*choose tick_int*/
#if SYSTICK_TICKINT == SYSTICK_TICKINT_ENABLE
	temp_reg=SysTick->STK_CTRL;
	temp_reg &= ~(STK_CTRL_TICKINT);
	temp_reg |= STK_CTRL_TICKINT;
	SysTick->STK_CTRL = temp_reg;

#elif SYSTICK_TICKINT    SYSTICK_TICKINT_DISABLE
	temp_reg=SysTick->STK_CTRL;
	temp_reg &= ~(STK_CTRL_TICKINT);
	SysTick->STK_CTRL = temp_reg;
#endif

	/* clear current value */
	SysTick->STK_VAL=0;
}

void SysTick_Start()
{
	SysTick->STK_CTRL |= STK_CTRL_ENABLE;
}

void SysTick_Stop()
{
	SysTick->STK_CTRL &= STK_CTRL_DISABLE;
}

uint8_t SysTick_SetTime_ms(uint32_t ms)
{
	uint32_t time;
	uint32_t ticks;
	uint8_t state;

//	time = (1.0/global_freq)*1000;
//
//	ticks = ms/time;
	ticks = (ms * global_freq)/1000;
	if(ticks <= STK_VAL_LIMIT)
	{
		SysTick->STK_LOAD = ticks;
		state=SUCCESS;
	}
	return state;
}

uint8_t SysTick_SetCallBack(CallBackPointer ptr_fun)
{
	uint8_t state=FAILURE;
	if(ptr_fun)
	{
		App_Notify = ptr_fun;
		state = SUCCESS;
	}
	return state;
}

void SysTick_Handler(void)
{
	if (App_Notify)
	{
		App_Notify();
	}
}


