/*
 * Switch_cfg.c
 *
 *  Created on: Mar 16, 2021
 *      Author: abdoo
 */

#include <stdint.h>
#include "../../lib/Bit_Mask.h"
#include "../../lib/Bit_Math.h"
#include "../../lib/Error_codes.h"
#include "GPIO.h"
#include "Switch_cfg.h"

typedef struct {
	gpio_pinConfig_t switchPin ;
	uint8_t switchStatus;
}switch_t;

#define SWITCH_STATUS_PRESSED_HIGH		0
#define SWITCH_STATUS_PRESSED_LOW		1

/*when the switch is pulled up the switch status must be SWITCH_STATUS_PRESSED_LOW and vice versa */
switch_t switches[_switch_Id_Length_]={
		[switch_Id_0] = {
				.switchPin = {
					.port   = GPIO_PORTA,
					.pupd   = GPIO_PULL_DOWN,
					.pinNum = GPIO_PIN_0,
					.mode   = GPIO_MODE_INPUT,
				},
				.switchStatus = SWITCH_STATUS_PRESSED_HIGH
			}

};

