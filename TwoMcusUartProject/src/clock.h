/*
 * Clock.h
 *
 *  Created on: Mar 17, 2021
 *      Author: Esraa Abdelnaby
 */

#ifndef CLOCK_H_
#define CLOCK_H_

typedef struct{
	uint32_t sec;
	uint32_t min;
	uint32_t hrs;
	uint32_t Days;
	uint32_t Months;
	uint32_t Years;
}Calendar_t;

void Clock_init(uint32_t d,uint32_t m,uint32_t y,uint32_t h,uint32_t mins );
uint8_t Clock_getter(Calendar_t * Calender);
#endif /* CLOCK_H_ */
