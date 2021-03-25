/*
 * led.h
 *
 *  Created on: Feb 24, 2021
 *      Author: abdoo
 */
#include "led_cfg.h"

#ifndef LED_H_
#define LED_H_

/*
 * 0   ^   0  -->  0    ! --> 1
 * 1   ^   0  -->  1    ! --> 0
 *
 * */

#define LED_OFF				0
#define LED_ON				1


void led_init();

uint32_t led_Control(uint32_t led,uint8_t status);

#endif /* LED_H_ */
