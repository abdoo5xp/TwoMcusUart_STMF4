/*
 * Frame.h
 *
 *  Created on: Mar 24, 2021
 *      Author: Esraa Abdelnaby
 */

#ifndef FRAME_H_
#define FRAME_H_

#include "Frame_cfg.h"

extern uint8_t Frame_Construct_buffer(uint8_t * UserBuffer,uint16_t size,uint8_t * Constructed_buff,uint16_t * newsize);
extern uint8_t Frame_Deconstruct_buffer(uint8_t * UserBuffer,uint16_t size,uint8_t * Constructed_buff);
extern uint8_t calc_checkSum(uint8_t * UserBuffer,uint16_t size);
#endif /* FRAME_H_ */
