/*
 * led_types.h
 *
 *  Created on: Feb 24, 2021
 *      Author: abdoo
 */

#ifndef LED_TYPES_H_
#define LED_TYPES_H_

typedef struct {
	gpio_pinConfig_t ledPin;
	uint32_t ledStatus;
}led_t;

#endif /* LED_TYPES_H_ */
