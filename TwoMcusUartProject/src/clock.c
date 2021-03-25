/*
 * clock.c
 *
 *  Created on: Mar 17, 2021
 *      Author: Esraa Abdelnaby
 */


#include <stdint.h>
#include "bit.h"
#include <diag/Trace.h>
#include "Error_codes.h"
#include "SwTimer.h"
#include "Clock.h"


static void Clock_time(void);
static Calendar_t Clndr;
/*************************
 * Clock_init(uint32_t d,uint32_t m,uint32_t y,uint32_t h,uint32_t mins )
 *
 * function to set the Time  Day/Month/Year, Hours,Minutes
 * and register the Clock_Time func into the Software Timer "Scheduler"
 *
 *************************/
void Clock_init(uint32_t d,uint32_t m,uint32_t y,uint32_t h,uint32_t mins )
{
	Clndr.min    = mins;
	Clndr.hrs    = h;
	Clndr.Months = m;
	Clndr.Years  = y;
	Clndr.Days  = d;

	SwTimer_RegisterCBF(1000,SWTimer_TimerMode_Periodic,Clock_time);
}


/*
 * function to get the Current time hrs, min, sec
 */
static void Clock_time(void)
{
	static uint32_t counter;
	counter = (counter+1) % 60;
	if((Clndr.sec)==59)
	{
		Clndr.min++;
		Clndr.sec=0;
	}
	if((Clndr.min)==60)
	{
		Clndr.hrs++;
		Clndr.min=0;
	}
	if((Clndr.hrs)==24)
	{
		Clndr.Days++;
		Clndr.hrs=0;
	}
	if((Clndr.Days) == 30)
	{
		Clndr.Months++;
		Clndr.Days=0;
	}
	if((Clndr.Months )== 12)
	{
		Clndr.Years++;
		Clndr.Months=0;
	}
	Clndr.sec = counter;
	//trace_printf("\n**************************\n");
	//trace_printf("%i/%i/%i \n%i:%i:%i",Clndr.Days,Clndr.Months,Clndr.Years,Clndr.hrs,Clndr.min,Clndr.sec);
}

uint8_t Clock_getter(Calendar_t * Calender)
{
	uint8_t state = RT_ERROR;
	if(Calender)
	{
		Calender->Days = Clndr.Days;
		Calender->Months = Clndr.Months;
		Calender->Years = Clndr.Years;
		Calender->hrs = Clndr.hrs;
		Calender->min = Clndr.min;
		Calender->sec = Clndr.sec;
		state = RT_SUCCESS;
	}
	return state;
}
