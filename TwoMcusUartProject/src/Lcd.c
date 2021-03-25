/*
 * Lcd.c
 *
 *  Created on: Mar 12, 2021
 *      Author: abdoo
 */

#include <stdint.h>
#include "../../../lib/Bit_Mask.h"
#include "../../../lib/Bit_Math.h"
#include "Error_codes.h"
#include "SwTimer.h"
#include "GPIO.h"
#include "Lcd.h"
#include "Lcd_cfg.h"

/*TODO:change this to configuration*/
#define LCD_CMD_DL_8				BIT_MASK_5 | BIT_MASK_4
#define LCD_CMD_DL_4				BIT_MASK_5

#define LCD_CMD_SET_CGRAM_ADD		BIT_MASK_6
#define LCD_CMD_SET_DDRAM_ADD		BIT_MASK_7

typedef enum{
	firstStage,
	secondStage,
	thirdStage,
	forthStage,
	fifthStage,
	lcd_init_done
}lcd_init_seq_e;

typedef struct {
	uint8_t data;
	uint32_t dataType;
}lcd_buff_t;

static lcd_init_seq_e lcdInitState = firstStage;
static lcd_buff_t lcdBuff[LCD_BUFFER_SIZE];
static uint16_t lcdBuffFirst;
static uint16_t lcdBuffRear;


/************************************* static functions declaration ********************************************/

/**************************************************************************************************************
 * static Function: LCD_InitCmds
 * Description: This function writes the initialization commands in sequence using state machine
 * Input Parameters: -Not Applicable (void)
 *
 * Return:           -Not Applicable (void)
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
static void LCD_InitCmds(void);

/**************************************************************************************************************
 * static Function:LCD_Manager
 * Description: This function is being called every 1 ms, when the sw timer fires to handle LCD processes.
 * Input Parameters: -Not Applicable (void)
 *
 * Return:           -Not Applicable (void)
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
static void LCD_Manager(void);

/**************************************************************************************************************
 * static Function:LCD_Process
 * Description: This function is used to
 * Input Parameters: -Not Applicable (void)
 *
 * Return:           -Not Applicable (void)
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
static void LCD_Process(void);

/**************************************************************************************************************
 * static Function:LCD_RegisterByte
 * Description: This function is used to
 * Input Parameters:
 * 					-uint8_t data : The packet to be saved to the LCD buffer.
 *
 *					-lcd_data_type_e dataType: is this packet a command or data packet.
 *												in range { IS_CMD, IS_DATA}
 *
 * Return:           -uint8_t : in range {  RT_PARAM,
 *											RT_ERROR,
 *											RT_SUCCESS }
 *
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
static uint8_t LCD_RegisterByte(uint8_t data,uint32_t dataType);

/**************************************************************************************************************
 * static Function: LCD_SendPacket
 * Description: This function sends the a packet on the LCD Bus.
 * Input Parameters:
 * 					-uint8_t data : The packet to be saved to the LCD buffer.
 *
 *					-lcd_data_type_e dataType: is this packet a command or data packet.
 *												in range { IS_CMD, IS_DATA}
 *
 *
 * Return:           -uint8_t : in range {  RT_PARAM,
 *											RT_ERROR,
 *											RT_SUCCESS }
 *
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
static uint8_t LCD_SendPacket(uint8_t Data,uint32_t DataType);


/************************************* static functions implementation********************************************/


static void LCD_Process(void){
	/*If the queue is not empty,
	 * send the next packet to LCD */
	if (lcdBuffFirst != lcdBuffRear)
	{
		LCD_SendPacket(lcdBuff[lcdBuffFirst].data, lcdBuff[lcdBuffFirst].dataType);
		lcdBuffFirst = (lcdBuffFirst + 1) % LCD_BUFFER_SIZE;
	}
}

static uint8_t LCD_RegisterByte(uint8_t data,uint32_t dataType)
{	uint8_t return_status = RT_ERROR;
	/*If the queue is not full ,,add the data to the buffer */
	if(lcdBuffFirst != (lcdBuffRear + 1) )
	{
		lcdBuff[lcdBuffRear].data =data;
		lcdBuff[lcdBuffRear].dataType =dataType;
		lcdBuffRear = (lcdBuffRear + 1) % LCD_BUFFER_SIZE;
		return_status = RT_SUCCESS;
	}
	return return_status;
}

static void LCD_Manager(void)
{
	if(lcd_init_done == lcdInitState)
	{
		LCD_Process();
	}
	else
	{
		LCD_InitCmds();
	}
}

static void LCD_InitCmds(void){
	/*we can make this a global variable instead of is ready */
	static uint8_t counter;

#if LCD_u8MODE == LCD_u8_8BITS_MODE
	switch(lcdInitState){
	case firstStage:
		if( LCD_INIT_UP_TIME == counter )
		{
			lcdInitState = secondStage;
		}
		else
		{
			counter++;
		}
		break;
	case secondStage:
		LCD_SendPacket(LCD_CMD_DL_8|LCD_CMD_TWO_LINE|LCD_CMD_FONT_5x7,IS_CMD);
		lcdInitState = thirdStage;
		 break;
	case thirdStage:
		LCD_SendPacket(LCD_CMD_DISP_ON |LCD_CMD_CURSOR_OFF|LCD_CMD_BLINKING_OFF,IS_CMD);
		lcdInitState = forthStage;
		 break;
	case forthStage:
		LCD_SendPacket(LCD_CMD_CLEAR,IS_CMD);
		lcdInitState = fifthStage;
		 break;
	case fifthStage:
		LCD_SendPacket(LCD_CMD_ENTRY_L|LCD_CMD_SHIFT_DIS,IS_CMD);
		lcdInitState = lcd_init_done;
		break;
	}
#endif
}

static uint8_t LCD_SendPacket(uint8_t Data,uint32_t DataType){
	uint8_t  lcdPinIdx;

	if(DataType != IS_CMD && DataType != IS_DATA )
	{
		return RT_PARAM;
	}


	GPIO_WritePin(lcdPins[LCD_RS].port, lcdPins[LCD_RS].pinNum, DataType);
	GPIO_WritePin(lcdPins[LCD_RW].port, lcdPins[LCD_RW].pinNum, GPIO_STATUS_LOW);

	/*TODO: it is required to have 300 ns of high state on the enable pin,so test this */
	GPIO_WritePin(lcdPins[LCD_EN].port, lcdPins[LCD_EN].pinNum, GPIO_STATUS_HIGH);

	for(lcdPinIdx = 0 ;lcdPinIdx < 8;lcdPinIdx++)
	{
		if(GET_BIT(Data,lcdPinIdx))
		{
			GPIO_WritePin(lcdPins[lcdPinIdx].port, lcdPins[lcdPinIdx].pinNum, GPIO_STATUS_HIGH);
		}
		else
		{
			GPIO_WritePin(lcdPins[lcdPinIdx].port, lcdPins[lcdPinIdx].pinNum, GPIO_STATUS_LOW);
		}
	}

	GPIO_WritePin(lcdPins[LCD_EN].port, lcdPins[LCD_EN].pinNum, GPIO_STATUS_LOW);

	return RT_SUCCESS;
}


/************************************* API functions implementation********************************************/

/**************************************************************************************************************
 * Public Function: LCD_Init
 * Description: This function is used to initialize the lcd at the start of the program
 * Input Parameters:-Not Applicable (void)
 *
 * Return:          -Not Applicable (void)
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
void LCD_Init(void)
{
	uint8_t lcdPinIdx;

	for(lcdPinIdx = 0 ;lcdPinIdx < (LCD_u8MODE + 3)  ; lcdPinIdx++)
	{
		GPIO_InitPin(&lcdPins[lcdPinIdx]);
	}

	SwTimer_RegisterCBF(2, SWTimer_TimerMode_Periodic, LCD_Manager);
}

/**************************************************************************************************************
 * Public Function: LCD_GoTo
 * Description: This function is used to set to cursor position to the passed position.
 * Input Parameters:
 * 					-lcd_rows_e Row: in range { lcdFirstRow, lcdSecondRow }
 *
 *					-uint8_t Col: in range { 0 -> 15  }
 *
 * Return:           -uint8_t : in range {  RT_PARAM,
 *											RT_ERROR,
 *											RT_SUCCESS }
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
uint8_t LCD_GoTo(lcd_rows_e Row, uint8_t Col)
{
	if(	Col > 16 ||
		(Row != lcdFirstRow &&
		Row != lcdSecondRow)
		)
	{
		return RT_PARAM;
	}
	uint8_t  return_status = RT_ERROR;

	 return_status = LCD_RegisterByte(LCD_CMD_SET_DDRAM_ADD | Row | Col,IS_CMD);

	return return_status;
}

/**************************************************************************************************************
 * Public Function: LCD_WriteString
 * Description: This function is used to display a string on the LCD.
 * Input Parameters:
 * 					 -const uint8_t *String: in range  { 0 -> 1024 characters}
 *
 *
 * Return:           -uint8_t : in range {  RT_PARAM,
 *											RT_ERROR,
 *											RT_SUCCESS }
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
uint8_t LCD_WriteString( uint8_t *String){
	if(String == NULL){
		return RT_PARAM;
	}
	uint8_t  return_status = RT_ERROR;
 	uint32_t Character_Idx =0;
	while(String[Character_Idx] != '\0')
	{
		 return_status = LCD_RegisterByte(String[Character_Idx],IS_DATA);
		Character_Idx++;
	}
	return  return_status;
}

/**************************************************************************************************************
 * Public Function: LCD_SaveCustomCharacter
 * Description: This function is used to save a custom character in the CGRAM of the LCD,
 * 				 so that you can print it later using print Custom character API.
 * Input Parameters:
 * 					 -uint8_t CharIdx : in range { 0 -> 7}
 *
 * 					 -uint8_t * CharData : The character drawn in 5 * 8 ,
 * 					 					   the array size should be 8.
 *
 *
 * Return:           -uint8_t : in range {  RT_PARAM,
 *											RT_ERROR,
 *											RT_SUCCESS }
 *
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
uint8_t LCD_SaveCustomCharacter(uint8_t CharIdx,uint8_t * CharData){
	if(CharIdx >8 || CharData == NULL)
	{
		return RT_PARAM;
	}
	uint8_t return_status = RT_ERROR;
	/*set CGRAM Address in the address counter of your MCU */
	//multiply the index by 8
	uint8_t  Loc_u8AddCounter = CharIdx << 3;
	uint8_t  Loc_u8CharDataIdx;
	 return_status = LCD_RegisterByte( LCD_CMD_SET_CGRAM_ADD | Loc_u8AddCounter,IS_CMD);
	/*Write on CGRAM/DDRAM
	 * NOTE: that CGRAM is contigous so you write your character rows after each other each character*/
	for(Loc_u8CharDataIdx =0; Loc_u8CharDataIdx < 8;Loc_u8CharDataIdx++)
	{
		 return_status = LCD_RegisterByte(CharData[Loc_u8CharDataIdx],IS_DATA);
	}

	return return_status;
}

/**************************************************************************************************************
 * Public Function: LCD_PrintCustomCharacter
 * Description: This function is used to display a custom character saved earlier on the LCD.
 * Input Parameters:
 * 				     -uint8_t CharIdx : in range { 0 -> 7}
 *
 *
 *
 * Return:           -uint8_t : in range {  RT_PARAM,
 *											RT_ERROR,
 *											RT_SUCCESS }
 *
 *
 * Input/Output Parameters:
 * 					-Not Applicable (void)
 * ***************************************************************************************************************/
uint8_t LCD_PrintCustomCharacter(uint8_t CharIdx){
	if(CharIdx >8)
	{
		return RT_PARAM;
	}

	return LCD_RegisterByte(CharIdx,IS_DATA);
}




