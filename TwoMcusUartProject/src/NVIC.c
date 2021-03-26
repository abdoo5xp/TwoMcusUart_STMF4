/*
 * NVIC.c
 *
 *  Created on: Mar 9, 2021
 *      Author: Esraa Abdelnaby
 */

#include <stdint.h>
#include "bit.h"
#include "NVIC_int.h"

typedef struct {
	uint32_t ISER[8];
	uint32_t Reserved[24];
	uint32_t ICER[8];
	uint32_t Reserved1[24];
	uint32_t ISPR[8];
	uint32_t Reserved2[24];
	uint32_t ICPR[8];
	uint32_t Reserved3[24];
	uint32_t IABR[8];
	uint32_t Reserved4[56];
	uint8_t IPR[240];
}NVIC_Type;

typedef struct {
	uint32_t SCB_CPUID;
	uint32_t SCB_ICSR;
	uint32_t SCB_VTOR;
	uint32_t SCB_AIRCR;
	uint32_t SCB_SCR;
	uint32_t SCB_CCR;
	uint8_t  SCB_SHPR[12];
	uint32_t SCB_SHCSR;
	uint32_t SCB_CFSR;
	uint32_t SCB_HFSR;
	uint32_t SCB_DFSR;
	uint32_t SCB_MMFSR;
	uint32_t SCB_BFAR;
	uint32_t SCB_AFSR;
	uint32_t SCB_PFR[2];
	uint32_t SCB_DFR;
	uint32_t SCB_AFR;
	uint32_t SCB_MMFR[4];
	uint32_t SCB_ISAR[5];
	uint32_t SCB_Reserved[5];
	uint32_t SCB_CPACR;
}SCB_Type;

volatile NVIC_Type * NVIC = (volatile NVIC_Type *)(0xE000E100);

volatile SCB_Type * SCB   = (volatile SCB_Type *)(0xE000ED00);

#define NVIC_STIR	(volatile uint32_t *)(0xE000EF00)


void NVIC_DisableGlobalIRQ()
{
	asm("CPSID I");
}
void NVIC_EnableGlobalIRQ()
{
	asm("CPSIE I");
}
void NVIC_DisableFaultIRQ()
{
	asm("CPSID F");
}
void NVIC_EnableFaultIRQ()
{
	asm("CPSIE F");
}

uint8_t NVIC_EnableIRQ(IRQn_t IRQn)
{
	uint8_t state = FAILURE;

	if ((uint32_t)IRQn <= (uint32_t) 81 )
	{
		NVIC->ISER[IRQn/32] = 1<<(IRQn%32);
		state = SUCCESS;
	}
	return state;
}
uint8_t NVIC_DisableIRQ(IRQn_t IRQn)
{
	uint8_t state = FAILURE;

	if ((uint32_t)IRQn <= (uint32_t) 81 )
	{
		NVIC->ICER[IRQn/32] = 1<<(IRQn%32);
		state = SUCCESS;
	}
	return state;
}

uint8_t NVIC_SetPendingIRQ(IRQn_t IRQn)
{
	uint8_t state = FAILURE;

	if ((uint32_t)IRQn <= (uint32_t) 81 )
	{
		NVIC->ISPR[IRQn/32] = 1<<(IRQn%32);
		state = SUCCESS;
	}
	return state;
}
uint8_t NVIC_CLearPendingIRQ(IRQn_t IRQn)
{
	uint8_t state = FAILURE;

	if ((uint32_t)IRQn <= (uint32_t) 81 )
	{
		NVIC->ICPR[IRQn/32] = 1<<(IRQn%32);
		state = SUCCESS;
	}
	return state;
}

uint8_t NVIC_GenerateSwInt(IRQn_t IRQn)
{
	uint8_t state=FAILURE;
	if(IRQn <= 81)
	{
		*NVIC_STIR = IRQn;
		state = SUCCESS;
	}
	return state;
}

uint8_t NVIC_SetPriority(IRQn_t IRQn,uint8_t ProirityNumber)
{
	uint8_t state = FAILURE;
	uint32_t max_priority = (1<<IMP_BITS) - 1;
	if((IRQn >= _IRQn_WWDG && IRQn <= _IRQn_FPU )  && (ProirityNumber<=max_priority))
	{
		NVIC->IPR[IRQn] = ProirityNumber;
		state = SUCCESS;
	}

	return state;
}

uint8_t NVIC_SetSubGroupBits(uint32_t BitsNumber)
{
	uint8_t state = FAILURE;
	uint32_t temp_reg;

	if((BitsNumber == NVIC_GROUP_PRIORITY_0) ||
			(BitsNumber == NVIC_GROUP_PRIORITY_1) ||
			(BitsNumber == NVIC_GROUP_PRIORITY_2)||
			(BitsNumber == NVIC_GROUP_PRIORITY_3) ||
			(BitsNumber == NVIC_GROUP_PRIORITY_4)  ||
			(BitsNumber == NVIC_GROUP_PRIORITY_5) ||
			(BitsNumber == NVIC_GROUP_PRIORITY_6) ||
			(BitsNumber == NVIC_GROUP_PRIORITY_7))

	{
		temp_reg = SCB->SCB_AIRCR;
		temp_reg &= NVIC_PRIGROUP_CLEAR_MASK;
		temp_reg |= BitsNumber;
		SCB->SCB_AIRCR = temp_reg;
		state = SUCCESS;
	}
	return state;
}

uint8_t NVIC_EncodePriority(uint8_t preemptive, uint8_t subgroup)
{
	uint8_t state = FAILURE;
	uint32_t GroupPriority;

	GroupPriority = (SCB->SCB_AIRCR & NVIC_PRIGROUP_READ_MASK) >> 7;



	return state;
}
uint8_t NVIC_DecodePriority(uint8_t ProirityNumber,uint8_t* preemptive,uint8_t* subgroup)
{
	uint8_t state = FAILURE;


	return state;
}

uint8_t NVIC_GetActivePin(IRQn_t IRQn)
{
	uint8_t state = FAILURE;

	return state;
}

