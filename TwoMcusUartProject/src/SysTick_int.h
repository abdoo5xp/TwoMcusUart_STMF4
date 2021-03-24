/*
 * SysTick_int.h
 *
 *  Created on: Mar 11, 2021
 *      Author: Esraa Abdelnaby
 */

#ifndef SYSTICK_INT_H_
#define SYSTICK_INT_H_

#define FAILURE 0
#define SUCCESS 1

#define STK_CTRL_ENABLE 	BIT_0
#define STK_CTRL_DISABLE	~(BIT_0)
#define STK_CTRL_TICKINT 	BIT_1
#define STK_CTRL_CLKSOURCE	BIT_2
#define STK_CTRL_COUNTFLAG	BIT_16

#define STK_VAL_LIMIT 0x00ffffff

typedef void (*CallBackPointer) (void);

static CallBackPointer App_Notify;

void SysTick_init(defined_uint32_t freq);
defined_uint8_t SysTick_SetTime_ms(defined_uint32_t ticks);
void SysTick_Start();
void SysTick_Stop();
defined_uint8_t SysTick_SetCallBack(CallBackPointer ptr_fun);

#endif /* SYSTICK_INT_H_ */
