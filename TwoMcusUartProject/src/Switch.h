/*
 * Switch.h
 *
 *  Created on: Mar 15, 2021
 *      Author: abdoo
 */

#include "Switch_cfg.h"

#ifndef SWITCH_H_
#define SWITCH_H_

typedef enum {
	switch_not_pressed,
	switch_pressed
}switch_status_e;

extern void Switch_Init(void);


/*
 * =================================================================================================================
 * Name: Switch_GetSwitchStatus
 * Description: this function is used to get the current switch state .
 *
 * Input:
 *		   - switch_Ids_e switch_Id: The switch that you want to get its status
 *		   						in range {switch_Id_0 : _switch_Id_Length_ }
 *
 * return: switch_status_e : in range{switch_pressed,switch_not_pressed }
 *
 * *****************************************************************************************************************
 * */
extern switch_status_e Switch_GetSwitchStatus(switch_Ids_e switch_Id);

#endif /* SWITCH_H_ */
