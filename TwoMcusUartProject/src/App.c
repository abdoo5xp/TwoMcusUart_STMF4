/*
 * App.c
 *
 *  Created on: Mar 24, 2021
 *      Author: abdoo
 */


#include <stdint.h>
#include "Bit_Mask.h"
#include "bit.h"
#include "Bit_Math.h"
#include "Error_codes.h"
#include "Rcc_int.h"
#include "Switch.h"
#include "SwTimer.h"
#include "Lcd.h"
#include "led.h"
#include "clock.h"
#include "Hal_Uart_int.h"
//#include "Frame.h"
#include "App_Types.h"
#include "App.h"

App_Data_t Recieved_Data;
App_Data_t Transmitted_Data;

static uint8_t SigRecieved_flag;
static uint8_t IsDataRecieved;
static uint8_t IsDataSent;
static uint8_t ModuleIdx;

static uint8_t AppSentBuff[DATA_BYTES_NUM];
static uint8_t AppRecievedBuff[DATA_BYTES_NUM];


static void App_RecieveDone(void);
static void App_TransmitDone(void);
static void App_stablishComm(void);
static void App_DispAll(App_Data_t * data);
static void App_Disp_init(void);
static void itoa(uint32_t Copy_u32Number,uint8_t *Copy_pu8NumArr);

void App_Init(void)
{

	Set_RCC_CFGR_PPRE1(RCC_CFGR_PPRE1_DIV_4);
	led_init();
	LCD_Init();
	App_Disp_init();
	Clock_init(25,3,2021,7,33);
	HalUart_Init();
	SwTimer_RegisterCBF(2,SWTimer_TimerMode_Periodic,App_stablishComm);
	HalUart_SetReciveCbf(App_RecieveDone);
	HalUart_SetSendCbf(App_TransmitDone);
	ModuleIdx = Hal_Uart_Module_1;
	SwTimer_init(1);
}

void App_main(void)
{
	if(IsDataRecieved)
	{

		IsDataRecieved=0;
		HalUart_ReciveBuffer(AppSentBuff,DATA_BYTES_NUM,ModuleIdx);

		Recieved_Data.date_time.Days = AppRecievedBuff[0];
		Recieved_Data.date_time.Months = AppRecievedBuff[1];
		Recieved_Data.date_time.Years = (uint32_t)((uint32_t) AppRecievedBuff[2] )| ((uint32_t) AppRecievedBuff[3]);
		Recieved_Data.date_time.hrs = AppRecievedBuff[4];
		Recieved_Data.date_time.min = AppRecievedBuff[5];
		Recieved_Data.swtich_state = AppRecievedBuff[6];
		App_DispAll(&Recieved_Data);
		if(Recieved_Data.swtich_state == switch_pressed)
			led_Control(LED_ZAR2A,LED_ON);
		else if(Recieved_Data.swtich_state == switch_not_pressed)
			led_Control(LED_ZAR2A,LED_OFF);

	}

	if(IsDataSent)
	{

		IsDataSent=0;
		Clock_getter(&Transmitted_Data.date_time);
		Transmitted_Data.swtich_state = Switch_GetSwitchStatus(switch_Id_0);

		AppSentBuff[0] = Transmitted_Data.date_time.Days;
		AppSentBuff[1] = Transmitted_Data.date_time.Months;
		AppSentBuff[2] = ((uint8_t)(Transmitted_Data.date_time.Years));
		AppSentBuff[3] = ((uint8_t)((Transmitted_Data.date_time.Years)>>4));
		AppSentBuff[4] = Transmitted_Data.date_time.hrs;
		AppSentBuff[5] = Transmitted_Data.date_time.min;
		AppSentBuff[6] = Transmitted_Data.swtich_state;

		HalUart_ReciveBuffer(AppSentBuff,DATA_BYTES_NUM,ModuleIdx);
	}

}

static void App_DispAll(App_Data_t * data)
{
	uint8_t charcter[10];
	LCD_GoTo(lcdSecondRow,0);

	itoa(data->date_time.Days%10,charcter);
	LCD_WriteString(charcter);
	itoa(data->date_time.Days/10,charcter);
	LCD_WriteString(charcter);

	LCD_GoTo(lcdSecondRow,2);
	itoa(data->date_time.Months%10,charcter);
	LCD_WriteString(charcter);
	itoa(data->date_time.Months/10,charcter);
	LCD_WriteString(charcter);


	LCD_GoTo(lcdSecondRow,4);
	itoa(data->date_time.Years%10,charcter);
	LCD_WriteString(charcter);
	itoa(((data->date_time.Years/10)%10),charcter);
	LCD_WriteString(charcter);
	itoa(((data->date_time.Years/100)%10),charcter);
	LCD_WriteString(charcter);
	itoa((data->date_time.Years/1000),charcter);
	LCD_WriteString(charcter);

	LCD_GoTo(lcdSecondRow,8);
	itoa(data->date_time.hrs%10,charcter);
	LCD_WriteString(charcter);
	itoa(data->date_time.hrs/10,charcter);
	LCD_WriteString(charcter);

	LCD_GoTo(lcdSecondRow,10);
	itoa(data->date_time.min%10,charcter);
	LCD_WriteString(charcter);
	itoa(data->date_time.min/10,charcter);
	LCD_WriteString(charcter);

	LCD_GoTo(lcdSecondRow,12);
	itoa(data->date_time.sec%10,charcter);
	LCD_WriteString(charcter);
	itoa(data->date_time.sec/10,charcter);
	LCD_WriteString(charcter);

	LCD_GoTo(lcdSecondRow,14);
	if(data->swtich_state == switch_pressed)
	{
		LCD_WriteString("N");
	}
	else if(data->swtich_state == switch_not_pressed)
	{
		LCD_WriteString("F");
	}

}

static void App_RecieveDone(void)
{

	if(!SigRecieved_flag)
	{
		SigRecieved_flag ++;
		IsDataSent=1;
		SwTimer_UnRegisterCBF(App_stablishComm);
	}
	else
	{
		IsDataRecieved = 1;
	}
}
static void App_TransmitDone(void)
{
	if(SigRecieved_flag)
		IsDataSent = 1;
}

static void App_stablishComm(void)
{
	HalUart_SendSig(ModuleIdx);
	HalUart_RecieveSig(ModuleIdx);
}


static void App_Disp_init(void)
{
	LCD_GoTo(lcdFirstRow,0);
	LCD_WriteString("D");
	LCD_GoTo(lcdSecondRow,0);
	LCD_WriteString("0");
	LCD_WriteString("0");

	LCD_GoTo(lcdFirstRow,2);
	LCD_WriteString("M");
	LCD_GoTo(lcdSecondRow,2);
	LCD_WriteString("0");
	LCD_WriteString("0");

	LCD_GoTo(lcdFirstRow,4);
	LCD_WriteString("Y");
	LCD_GoTo(lcdSecondRow,4);
	LCD_WriteString("0");
	LCD_WriteString("0");

	LCD_GoTo(lcdFirstRow,6);
	LCD_GoTo(lcdSecondRow,6);
	LCD_WriteString("0");
	LCD_WriteString("0");

	LCD_GoTo(lcdFirstRow,8);
	LCD_WriteString("H");
	LCD_GoTo(lcdSecondRow,8);
	LCD_WriteString("0");
	LCD_WriteString("0");

	LCD_GoTo(lcdFirstRow,10);
	LCD_WriteString("M");
	LCD_GoTo(lcdSecondRow,10);
	LCD_WriteString("0");
	LCD_WriteString("0");

	LCD_GoTo(lcdFirstRow,12);
	LCD_WriteString("S");
	LCD_GoTo(lcdSecondRow,12);
	LCD_WriteString("0");
	LCD_WriteString("0");

	LCD_GoTo(lcdFirstRow,14);
	LCD_WriteString("L");
	LCD_GoTo(lcdSecondRow,14);
	LCD_WriteString("-");
	LCD_WriteString("-");
}

static void itoa(uint32_t Copy_u32Number,uint8_t *Copy_pu8NumArr){
	uint8_t  Loc_u8NumLoopIdx=0;
	uint8_t  Loc_u8Digit=0;
	uint8_t  Loc_u8Temp;
	uint8_t  Loc_u8Counter = 0;
	do{
		/*Get the digit to be inserted in the array  */
		Loc_u8Digit = '0' + Copy_u32Number % 10;
		Copy_pu8NumArr[Loc_u8NumLoopIdx] = Loc_u8Digit;

		/*move to the next digit */
		Copy_u32Number /= 10;
		Loc_u8NumLoopIdx++;

	}while (Copy_u32Number != 0);

	Copy_pu8NumArr[Loc_u8NumLoopIdx] = '\0';

	/*
	 * Now reverse the characters
	 * */
	while (Loc_u8Counter < Loc_u8NumLoopIdx)
	{
		Loc_u8Temp = Copy_pu8NumArr[Loc_u8NumLoopIdx];
		Copy_pu8NumArr[Loc_u8NumLoopIdx] = Copy_pu8NumArr[Loc_u8Counter];
		Copy_pu8NumArr[Loc_u8Counter]	 =Loc_u8Temp;
		Loc_u8Counter++;
		Loc_u8NumLoopIdx--;
	}

}







