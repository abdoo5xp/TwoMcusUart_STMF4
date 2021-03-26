/*
 * Lcd_cfg.h
 *
 *  Created on: Mar 12, 2021
 *      Author: abdoo
 */

#ifndef LCD_CFG_H_
#define LCD_CFG_H_


#define LCD_u8_4BITS_MODE			4
#define LCD_u8_8BITS_MODE			8
#define LCD_u8MODE				LCD_u8_8BITS_MODE

#define LCD_BUFFER_SIZE				2048

/*LCD first delay time divided by 2, because the function is recalled every 2 ms by the sw timer  */
#define LCD_INIT_UP_TIME			20

/*LCD Pin Assignation */
#define LCD_RS			8
#define LCD_RW			9
#define LCD_EN			10

#define LCD_D0			0
#define LCD_D1			1
#define LCD_D2			2
#define LCD_D3			3

#if LCD_u8MODE == LCD_u8_8BITS_MODE
#define LCD_D4			4
#define LCD_D5			5
#define LCD_D6			6
#define LCD_D7			7
#endif

extern const gpio_pinConfig_t lcdPins[11];

#endif /* LCD_CFG_H_ */
