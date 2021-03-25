/*
 * Lcd_cfg.c
 *
 *  Created on: Mar 16, 2021
 *      Author: abdoo
 */


#include <stdint.h>
#include "../../../lib/Bit_Mask.h"
#include "../../../lib/Bit_Math.h"
#include "../../../lib/Error_codes.h"
#include "GPIO.h"
#include "Lcd_cfg.h"


const gpio_pinConfig_t lcdPins[11]={
	[LCD_D0] = {
		.port   = GPIO_PORTE,
		.pinNum = GPIO_PIN_4,
		.mode   = GPIO_MODE_OUTPUT,
		.pupd   = GPIO_NO_PULL,
		.otype  = GPIO_OTYPE_PUSH_PULL,
		.ospeed = GPIO_OSPEED_MED
	},
	[LCD_D1] = {
		.port   = GPIO_PORTE,
		.pinNum = GPIO_PIN_5,
		.mode   = GPIO_MODE_OUTPUT,
		.pupd   = GPIO_NO_PULL,
		.otype  = GPIO_OTYPE_PUSH_PULL,
		.ospeed = GPIO_OSPEED_MED
	},
	[LCD_D2] = {
		.port   = GPIO_PORTE,
		.pinNum = GPIO_PIN_6,
		.mode   = GPIO_MODE_OUTPUT,
		.pupd   = GPIO_NO_PULL,
		.otype  = GPIO_OTYPE_PUSH_PULL,
		.ospeed = GPIO_OSPEED_MED
	},
	[LCD_D3] = {
		.port   = GPIO_PORTE,
		.pinNum = GPIO_PIN_7,
		.mode   = GPIO_MODE_OUTPUT,
		.pupd   = GPIO_NO_PULL,
		.otype  = GPIO_OTYPE_PUSH_PULL,
		.ospeed = GPIO_OSPEED_MED
	},

#if LCD_u8MODE == LCD_u8_8BITS_MODE
	[LCD_D4] = {
		.port   = GPIO_PORTE,
		.pinNum = GPIO_PIN_8,
		.mode   = GPIO_MODE_OUTPUT,
		.pupd   = GPIO_NO_PULL,
		.otype  = GPIO_OTYPE_PUSH_PULL,
		.ospeed = GPIO_OSPEED_MED
	},
	[LCD_D5] = {
		.port   = GPIO_PORTE,
		.pinNum = GPIO_PIN_9,
		.mode   = GPIO_MODE_OUTPUT,
		.pupd   = GPIO_NO_PULL,
		.otype  = GPIO_OTYPE_PUSH_PULL,
		.ospeed = GPIO_OSPEED_MED
	},
	[LCD_D6] = {
		.port   = GPIO_PORTE,
		.pinNum = GPIO_PIN_10,
		.mode   = GPIO_MODE_OUTPUT,
		.pupd   = GPIO_NO_PULL,
		.otype  = GPIO_OTYPE_PUSH_PULL,
		.ospeed = GPIO_OSPEED_MED
	},
	[LCD_D7] = {
		.port   = GPIO_PORTE,
		.pinNum = GPIO_PIN_11,
		.mode   = GPIO_MODE_OUTPUT,
		.pupd   = GPIO_NO_PULL,
		.otype  = GPIO_OTYPE_PUSH_PULL,
		.ospeed = GPIO_OSPEED_MED
	},
#endif
	[LCD_RS] = {
		.port   = GPIO_PORTE,
		.pinNum = GPIO_PIN_12,
		.mode   = GPIO_MODE_OUTPUT,
		.pupd   = GPIO_NO_PULL,
		.otype  = GPIO_OTYPE_PUSH_PULL,
		.ospeed = GPIO_OSPEED_MED
	},
	[LCD_RW] = {
		.port   = GPIO_PORTE,
		.pinNum = GPIO_PIN_13,
		.mode   = GPIO_MODE_OUTPUT,
		.pupd   = GPIO_NO_PULL,
		.otype  = GPIO_OTYPE_PUSH_PULL,
		.ospeed = GPIO_OSPEED_MED
	},
	[LCD_EN] = {
		.port   = GPIO_PORTE,
		.pinNum = GPIO_PIN_14,
		.mode   = GPIO_MODE_OUTPUT,
		.pupd   = GPIO_NO_PULL,
		.otype  = GPIO_OTYPE_PUSH_PULL,
		.ospeed = GPIO_OSPEED_MED
	}
};

