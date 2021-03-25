/*
 * led.c
 *
 *  Created on: Feb 24, 2021
 *      Author: abdoo
 */

#include "../../../lib/Bit_Mask.h"
#include "../../../lib/Bit_Math.h"
#include "../../../lib/Error_codes.h"
#include "led_types.h"
#include "led.h"
#include "led_cfg.h"
#include "GPIO.h"

extern const led_t led_arr[LEDS_COUNT];

void led_init(){
	uint8_t led_idx;
	for(led_idx = 0;led_idx < LEDS_COUNT ;led_idx++ ){
		GPIO_InitPin(&led_arr[led_idx].ledPin);
	}
}


/*  XNOR
 *    led.status     :      status
 * 	!(LED_ACTIVE_LOW   ^     LED_ON )	-->		0  which will turn the led on
 * 	!(LED_ACTIVE_LOW   ^     LED_OFF)   -->		1  which will turn the led off
 * 	!(LED_ACTIVE_HIGH  ^     LED_ON )   -->		1  which will turn the led on
 * 	!(LED_ACTIVE_HIGH  ^     LED_OFF)   -->		0  which will turn the led off
 *
 * */
uint32_t led_Control(uint32_t led,uint8_t status){
	if(		(status != LED_ACTIVE_HIGH && status != LED_ACTIVE_LOW )
			|| led <= LEDS_COUNT ){
		return RT_PARAM;
	}
	GPIO_WritePin(led_arr[led].ledPin.port, led_arr[led].ledPin.pinNum, !(led_arr[led].ledStatus ^ status) );
	return RT_SUCCESS;

}
