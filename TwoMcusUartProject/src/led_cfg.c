/*
 * led_cfg.c
 *
 *  Created on: Feb 24, 2021
 *      Author: abdoo
 */


#include "../../../lib/Bit_Mask.h"
#include "../../../lib/Bit_Math.h"
#include "../../../lib/Error_codes.h"
#include "led.h"
#include "led_types.h"
#include "led_cfg.h"
#include "GPIO.h"


const led_t led_arr[LEDS_COUNT] = {
	[LED_ALRAM]={
			.ledPin = {
					.port    = GPIO_PORTD,
					.pinNum  = GPIO_PIN_13,
					.mode	 = GPIO_MODE_OUTPUT,
					.otype   = GPIO_OTYPE_PUSH_PULL,
					.ospeed  = GPIO_OSPEED_MED,
					.pupd    = GPIO_NO_PULL,
					.AF      = GPIO_AF0_SYSTEM
			},
			.ledStatus = LED_ACTIVE_HIGH
	},
	[LED_7AMRA]={
			.ledPin = {
					.port    = GPIO_PORTD,
					.pinNum  = GPIO_PIN_12,
					.mode	 = GPIO_MODE_OUTPUT,
					.otype   = GPIO_OTYPE_PUSH_PULL,
					.ospeed  = GPIO_OSPEED_MED,
					.pupd    = GPIO_NO_PULL,
					.AF      = GPIO_AF0_SYSTEM
			},
			.ledStatus = LED_ACTIVE_HIGH
	}
};
