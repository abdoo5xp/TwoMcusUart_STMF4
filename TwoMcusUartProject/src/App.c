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
/*TODO: now we have a problem the receive function doesn't get called,
 * 		which means receiving is not done successfully,
 * 		what could be the problem ??
 * 			-> check do we send the SIG + checksum  ??
 * 			-> check do we receive the SIG + checksum ??
 * 			-> check the above two cases by sniffing on the usart channel.
			-> the deconstruct frame faces a problem while deconstructing the frame.
 * 			-> the frame is not received successfully.
 * 			-> that we noticed that RXNEIE flag is not enabled.
 * 		  */

static void App_RecieveDone(void);
static void App_TransmitDone(void);
static void App_stablishComm(void);
static void App_DispAll(App_Data_t * data);
static void App_Disp_init(void);
static void itoa(uint32_t Copy_u32Number,uint8_t *Copy_pu8NumArr);

/**************************************************************************************************************
 * Public Function: App_Init
 * Description: This function is used to initialize the system.
 * Input Parameters:
 * 				   	 -Not Applicable (void)
 *
 *
 * Return:           -Not Applicable (void)
 *
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
void App_Init(void)
{
	/*SwTimer initialization */
	SwTimer_init(1);

	/*LCD initialization */
	LCD_Init();

	/*the uart channel that aour app will work on */
	ModuleIdx = Hal_Uart_Module_1;

	/*the buses clock frequencies */
	Set_RCC_CFGR_PPRE1(RCC_CFGR_PPRE1_DIV_4);
	Enable_RCC_AHB1_PERI(RCC_AHB1_PERI_GPIODEN);

	/*Led initialization */
	led_init();

	/*Display zeros as initial value for all values till a transmission is constructed */
	App_Disp_init();

	/*Clock initialization */
	Clock_init(25,3,2021,7,33);

	/*Uart channel initialization */
	HalUart_Init();
	HalUart_SetReciveCbf(App_RecieveDone);
	HalUart_SetSendCbf(App_TransmitDone, ModuleIdx);

	/*Establishing the communication */
	SwTimer_RegisterCBF(200,SWTimer_TimerMode_Periodic,App_stablishComm);
}

/**************************************************************************************************************
 * Public Function: App_main
 * Description: This function is used to -> 1- collect the data and send a new frame when isDataSent flag is raised,
 * 											2- display the Received data on LCD, and update the LED status when isDataReceived flag is raised.
 * Input Parameters:
 * 					 -Not Applicable (void)
 *
 *
 * Return:           -Not Applicable (void)
 *
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
void App_main(void)
{
	if(IsDataRecieved)
	{
		IsDataRecieved=0;

		Recieved_Data.date_time.Days = AppRecievedBuff[0];
		Recieved_Data.date_time.Months = AppRecievedBuff[1];
		Recieved_Data.date_time.Years = (uint32_t)((uint32_t) AppRecievedBuff[3] << 8)| ((uint32_t) AppRecievedBuff[2]);
		Recieved_Data.date_time.hrs = AppRecievedBuff[4];
		Recieved_Data.date_time.min = AppRecievedBuff[5];
		Recieved_Data.swtich_state = AppRecievedBuff[6];

		App_DispAll(&Recieved_Data);

		if(Recieved_Data.swtich_state == switch_pressed)
			led_Control(LED_ZAR2A,LED_ON);
		else if(Recieved_Data.swtich_state == switch_not_pressed)
			led_Control(LED_ZAR2A,LED_OFF);

		HalUart_ReciveBuffer(AppSentBuff,DATA_BYTES_NUM,ModuleIdx);
	}

	if(IsDataSent)
	{

		IsDataSent=0;
		Clock_getter(&Transmitted_Data.date_time);
		Transmitted_Data.swtich_state = Switch_GetSwitchStatus(switch_Id_0);

		AppSentBuff[0] = Transmitted_Data.date_time.Days;
		AppSentBuff[1] = Transmitted_Data.date_time.Months;
		AppSentBuff[2] = ((uint8_t)(Transmitted_Data.date_time.Years));
		AppSentBuff[3] = ((uint8_t)((Transmitted_Data.date_time.Years)>> 8 ));
		AppSentBuff[4] = Transmitted_Data.date_time.hrs;
		AppSentBuff[5] = Transmitted_Data.date_time.min;
		AppSentBuff[6] = Transmitted_Data.date_time.sec;
		AppSentBuff[7] = Transmitted_Data.swtich_state;

		HalUart_SendBuffer(AppSentBuff,DATA_BYTES_NUM,ModuleIdx);
	}

}

/**************************************************************************************************************
 * Public Function: App_DispAll
 * Description: This function is used to display the structure data on the LCD.
 * Input Parameters:
 * 					 -App_Data_t * data: A pointer to structure that contains the data to be displayed
 *
 *
 * Return:           -Not Applicable (void)
 *
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
/*TODO: the structure should be sent by value not by pointer
 * because the interrupt can update it while it is not displayed yet -> Racing Condition  */
static void App_DispAll(App_Data_t * data)
{
	uint8_t charcter[10];
	LCD_GoTo(lcdSecondRow,0);

	itoa(data->date_time.Days/10,charcter);
	LCD_WriteString(charcter);
	itoa(data->date_time.Days%10,charcter);
	LCD_WriteString(charcter);

	LCD_GoTo(lcdSecondRow,2);
	itoa(data->date_time.Months/10,charcter);
	LCD_WriteString(charcter);
	itoa(data->date_time.Months%10,charcter);
	LCD_WriteString(charcter);


	LCD_GoTo(lcdSecondRow,4);
	itoa((data->date_time.Years/1000),charcter);
	LCD_WriteString(charcter);
	itoa(((data->date_time.Years/100)%10),charcter);
	LCD_WriteString(charcter);
	itoa(((data->date_time.Years/10)%10),charcter);
	LCD_WriteString(charcter);
	itoa(data->date_time.Years%10,charcter);
	LCD_WriteString(charcter);




	LCD_GoTo(lcdSecondRow,8);
	itoa(data->date_time.hrs/10,charcter);
	LCD_WriteString(charcter);
	itoa(data->date_time.hrs%10,charcter);
	LCD_WriteString(charcter);


	LCD_GoTo(lcdSecondRow,10);
	itoa(data->date_time.min/10,charcter);
	LCD_WriteString(charcter);
	itoa(data->date_time.min%10,charcter);
	LCD_WriteString(charcter);


	LCD_GoTo(lcdSecondRow,12);
	itoa(data->date_time.sec/10,charcter);
	LCD_WriteString(charcter);
	itoa(data->date_time.sec%10,charcter);
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

/**************************************************************************************************************
 * Public Function: App_RecieveDone
 * Description: This function is used as a call back function when a successful frame is received .
 * Input Parameters:
 * 					 -Not Applicable (void)
 *
 *
 * Return:           -Not Applicable (void)
 *
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
static void App_RecieveDone(void)
{

	if(!SigRecieved_flag)
	{
		SigRecieved_flag ++;
		IsDataSent=1;
		SwTimer_UnRegisterCBF(App_stablishComm);
	}
	//	else
	//	{
	IsDataRecieved = 1;
	//	}
}

/*TODO: Don't Register this function from the beginning,
 *  	Register it when you communication is established  */
/**************************************************************************************************************
 * Public Function: App_TransmitDone
 * Description: This function is used to as a call back function to trigger the next send.
 * Input Parameters:
 * 					 -Not Applicable (void)
 *
 *
 * Return:           -Not Applicable (void)
 *
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
static void App_TransmitDone(void)
{
	if(SigRecieved_flag)
		IsDataSent = 1;
}

/**************************************************************************************************************
 * Public Function: App_stablishComm
 * Description: This function is used to send a signature , and receive a signature.
 * Input Parameters:
 * 					- Not Applicable (void)
 *
 *
 * Return:           -Not Applicable (void)
 *
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
static void App_stablishComm(void)
{
	HalUart_SendSig(ModuleIdx);
	//	HalUart_RecieveSig(ModuleIdx);
	HalUart_ReciveBuffer(AppRecievedBuff, DATA_BYTES_NUM, ModuleIdx);
}

/**************************************************************************************************************
 * Public Function: App_Disp_init
 * Description: This function is used to to initialize the LCD with all zero values
 * Input Parameters:
 * 					 -Not Applicable (void)
 *
 *
 * Return:           -Not Applicable (void)
 *
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
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

/**************************************************************************************************************
 * Public Function: itoa
 * Description: This function is used to convert integer numbers to array of characters
 * Input Parameters:
 * 					 - uint32_t Copy_u32Number
 * 					 - uint8_t *Copy_pu8NumArr
 *
 *
 * Return:           -Not Applicable (void)
 *
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
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

	/*
	 * Now reverse the characters
	 * */
	while (Loc_u8Counter < Loc_u8NumLoopIdx-1)
	{
		Loc_u8Temp = Copy_pu8NumArr[Loc_u8NumLoopIdx];
		Copy_pu8NumArr[Loc_u8NumLoopIdx] = Copy_pu8NumArr[Loc_u8Counter];
		Copy_pu8NumArr[Loc_u8Counter]	 =Loc_u8Temp;
		Loc_u8Counter++;
		Loc_u8NumLoopIdx--;
	}

	Copy_pu8NumArr[Loc_u8NumLoopIdx] = '\0';

}







