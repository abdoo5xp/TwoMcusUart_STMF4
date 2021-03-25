/*
 * Lcd.h
 *
 *  Created on: Mar 12, 2021
 *      Author: abdoo
 */

#ifndef LCD_H_
#define LCD_H_




/*TODO:Nice Bug here the enum is signed integer so the mask i want is a negative value
 * But i casted the macro to unsigned how can it be signed ?*/

/*Packet Data Types */
#define	 IS_CMD						  GPIO_STATUS_LOW
#define	 IS_DATA 					  GPIO_STATUS_HIGH

/* LCD Commands*/
#define	LCD_CMD_CLEAR				BIT_MASK_0
#define LCD_CMD_HOME				BIT_MASK_1

#define LCD_CMD_ENTRY_L				BIT_MASK_2 | BIT_MASK_1
#define LCD_CMD_ENTRY_R				BIT_MASK_2
#define LCD_CMD_SHIFT_EN			BIT_MASK_2 | BIT_MASK_0
#define LCD_CMD_SHIFT_DIS			BIT_MASK_2

#define LCD_CMD_DISP_ON				BIT_MASK_3 | BIT_MASK_2
#define LCD_CMD_DISP_OFF			BIT_MASK_3
#define LCD_CMD_CURSOR_ON			BIT_MASK_3 | BIT_MASK_1
#define LCD_CMD_CURSOR_OFF			BIT_MASK_3
#define LCD_CMD_BLINKING_ON			BIT_MASK_3 | BIT_MASK_0
#define LCD_CMD_BLINKING_OFF		BIT_MASK_3

#define LCD_CMD_SHIFT_CUR_L			BIT_MASK_4
#define LCD_CMD_SHIFT_CUR_R			BIT_MASK_4 | BIT_MASK_2
#define LCD_CMD_SHIFT_DISP_L		BIT_MASK_4 | BIT_MASK_3
#define LCD_CMD_SHIFT_DISP_R		BIT_MASK_4 | BIT_MASK_2 | BIT_MASK_3


#define LCD_CMD_ONE_LINE			BIT_MASK_5
#define LCD_CMD_TWO_LINE			BIT_MASK_5 | BIT_MASK_3
#define LCD_CMD_FONT_5x7			BIT_MASK_5
#define LCD_CMD_FONT_5x10			BIT_MASK_5 | BIT_MASK_2



typedef enum{
	lcdFirstRow  = 0x80,
	lcdSecondRow = 0xC0
}lcd_rows_e;

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
void LCD_Init(void);

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
uint8_t LCD_GoTo(lcd_rows_e Row, uint8_t Col);

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
uint8_t LCD_WriteString( uint8_t *String);

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
uint8_t LCD_SaveCustomCharacter(uint8_t CharIdx,uint8_t * CharData);

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
uint8_t LCD_PrintCustomCharacter(uint8_t CharIdx);

#endif /* LCD_H_ */
