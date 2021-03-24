/*
 * NVIC_int.h
 *
 *  Created on: Mar 9, 2021
 *      Author: Esraa Abdelnaby
 */

#ifndef NVIC_INT_H_
#define NVIC_INT_H_

#include "NVIC_Port.h"

#define FAILURE 0
#define SUCCESS 1

#define NVIC_PRIGROUP_MASK 0x5FA00000
#define NVIC_PRIGROUP_READ_MASK  (BIT_10 | BIT_9 | BIT_8)
#define NVIC_PRIGROUP_CLEAR_MASK (NVIC_PRIGROUP_MASK & ~ ( BIT_10 | BIT_9 | BIT_8))

#define NVIC_GROUP_PRIORITY_0 	(uint32_t)(NVIC_PRIGROUP_MASK                         )
#define NVIC_GROUP_PRIORITY_1	(uint32_t)(NVIC_PRIGROUP_MASK | BIT_8                 )
#define NVIC_GROUP_PRIORITY_2	(uint32_t)(NVIC_PRIGROUP_MASK | BIT_9                 )
#define NVIC_GROUP_PRIORITY_3	(uint32_t)(NVIC_PRIGROUP_MASK | BIT_9 | BIT_8         )
#define NVIC_GROUP_PRIORITY_4	(uint32_t)(NVIC_PRIGROUP_MASK | BIT_10                )
#define NVIC_GROUP_PRIORITY_5	(uint32_t)(NVIC_PRIGROUP_MASK | BIT_10 | BIT_8        )
#define NVIC_GROUP_PRIORITY_6	(uint32_t)(NVIC_PRIGROUP_MASK | BIT_10 | BIT_9        )
#define NVIC_GROUP_PRIORITY_7	(uint32_t)(NVIC_PRIGROUP_MASK | BIT_10 | BIT_9 | BIT_8)


void NVIC_DisableGlobalIRQ();
void NVIC_EnableGlobalIRQ();
void NVIC_DisableFaultIRQ();
void NVIC_EnableFaultIRQ();

uint8_t NVIC_EnableIRQ(IRQn_t IRQn);
uint8_t NVIC_DisableIRQ(IRQn_t IRQn);

uint8_t NVIC_SetPendingIRQ(IRQn_t IRQn);
uint8_t NVIC_CLearPendingIRQ(IRQn_t IRQn);

uint8_t NVIC_GenerateSwInt(IRQn_t IRQn);

uint8_t NVIC_SetPriority(IRQn_t IRQn,uint8_t ProirityNumber);

uint8_t NVIC_SetSubGroupBits(uint32_t BitsNumber);
uint8_t NVIC_EncodePriority(uint8_t preemptive, uint8_t subgroup);
uint8_t NVIC_DecodePriority(uint8_t ProirityNumber,uint8_t* preemptive,uint8_t* subgroup);

uint8_t NVIC_GetActivePin(IRQn_t IRQn);






#endif /* NVIC_INT_H_ */
