/*
 * Switch.c
 *
 *  Created on: Mar 15, 2021
 *      Author: abdoo
 */


#include <stdint.h>
#include "Bit_Mask.h"
#include "Bit_Math.h"
#include "Error_codes.h"
#include "GPIO.h"
#include "SwTimer.h"
#include "Switch.h"
#include "Switch_cfg.h"

typedef struct {
	gpio_pinConfig_t switchPin ;
	uint8_t switchStatus;
}switch_t;


extern const switch_t switches[_switch_Id_Length_];

static uint8_t switchesPinVals[_switch_Id_Length_];

/*should this function be static or not ?? */
void Switch_CheckStatus(void){
	/*TODO:put these three arrays in a structure */
	static uint8_t counter[_switch_Id_Length_];
	static uint8_t prevState[_switch_Id_Length_];
	static uint8_t curState[_switch_Id_Length_];
	uint8_t switchIdx;

	for(switchIdx = 0;switchIdx < _switch_Id_Length_ ;switchIdx++){
		/*read the current pin value curState[switchIdx] */
		GPIO_ReadPin((void*)switches[switchIdx].switchPin.port, switches[switchIdx].switchPin.pinNum,&curState[switchIdx]);

		/*if the current pin value equals the last read pin value -> increase the counter */
		if(curState[switchIdx] == prevState[switchIdx])
		{
			counter[switchIdx]++;
		}
		/*if not, clear the counter (to read the new 5 values ) */
		else
		{
			counter[switchIdx] = 0;
		}

		/* If the counter of a switch reaches 5 unchanged readings,then this is the current pin value (not a noise) */
		if(counter[switchIdx] == 5 )
		{
			switchesPinVals[switchIdx] = curState[switchIdx];
			counter[switchIdx] = 0;
		}

		/*update the previous value with the current value */
		prevState[switchIdx] = curState[switchIdx];
	}


}

void Switch_Init(void){
	uint8_t switch_idx;
	for(switch_idx = 0;switch_idx < _switch_Id_Length_;switch_idx++){
		GPIO_InitPin(&switches[switch_idx].switchPin);
	}

	SwTimer_RegisterCBF(5, SWTimer_TimerMode_Periodic, Switch_CheckStatus);
}

/*
 * 	pull up    ----  not pressed_pin_val  -- >     0   --> SWITCH_NOT_PRESSED
 * 	   1				1
 *
 * 	pull up    ----  pressed_pin_val      -- >     1	--> SWITCH_PRESSED
 * 	   1 				0
 *
 * 	pull down  ----  pressed_pin_val      -- >     1    --> SWITCH_PRESSED
 * 		0				1
 *
 * 	pull down  ----  not pressed_pin_val  -- >     0	--> SWITCH_NOT_PRESSED
 *		0               0
 *
 *
 * */
switch_status_e Switch_GetSwitchStatus(switch_Ids_e switch_Id){
	if (switch_Id > _switch_Id_Length_){
		return RT_PARAM;
	}

//	uint32_t pinValue;
//	GPIO_ReadPin(switches[switch_Id].switchPin.port, switches[switch_Id].switchPin.pinNum, &pinValue);

	return switchesPinVals[switch_Id] ^ switches[switch_Id].switchStatus;
}




