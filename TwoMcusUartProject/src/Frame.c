/*
 * Frame.c
 *
 *  Created on: Mar 24, 2021
 *      Author: Esraa Abdelnaby
 */
#include <stdint.h>
#include "Error_codes.h"
#include "Frame.h"


static uint8_t Frame_Check_Buffer (uint8_t * UserBuffer,uint16_t size);

uint8_t Frame_Construct_buffer(uint8_t * UserBuffer,uint16_t size,uint8_t * Constructed_buff, uint16_t *newsize)
{
	uint8_t state = RT_ERROR;
	uint8_t idx;
	uint8_t data_idx=0;
	volatile uint8_t Constructed_buff_size= SIG_BYTES_NUM+size;
	*newsize = SIG_BYTES_NUM+size+1;

	if((UserBuffer) && (size > 0))
	{

		/*TODO:This function adds some rubbish at the end */
		for(idx=0;idx<Constructed_buff_size;idx++)
		{
			if(idx<SIG_BYTES_NUM)
			{
				Constructed_buff[idx] = Sig[idx];
			}
			else
			{
				Constructed_buff[idx] = UserBuffer[data_idx++];
			}
	}
		Constructed_buff[idx] = calc_checkSum(Constructed_buff,Constructed_buff_size);
		state = RT_SUCCESS;
	}

	return state;
}



uint8_t  Frame_Deconstruct_buffer(uint8_t * UserBuffer,uint16_t size,uint8_t * Deconstructed_buff)
{
	uint8_t state = RT_ERROR;
	uint8_t idx;
	if(UserBuffer && size > 0 )
	{
		state = Frame_Check_Buffer(UserBuffer,size);
		if (state == RT_SUCCESS)
		{
			for(idx = SIG_BYTES_NUM ; idx<size;idx++)
			{
				Deconstructed_buff[idx - SIG_BYTES_NUM] = UserBuffer[idx];
			}
		}
	}
	return state;
}


static uint8_t Frame_Check_Buffer (uint8_t * UserBuffer,uint16_t size)
{
	uint8_t  idx;
	uint8_t state= RT_SUCCESS;
	uint8_t checksum;
	for(idx=0;idx<SIG_BYTES_NUM;idx++)
	{
		if(UserBuffer[idx] != Sig[idx])
		{
			state = RT_ERROR;
		}
	}

	checksum = calc_checkSum(UserBuffer,size-1);
	if(state == RT_SUCCESS && UserBuffer[size-1] == checksum)
	{
		state= RT_SUCCESS;
	}
	else
	{
		state = RT_ERROR;
	}
	return state;
}

uint8_t calc_checkSum(uint8_t * UserBuffer,uint16_t size)
{
	uint8_t idx;
	uint8_t checksum=0;
	for(idx=0;idx<size;idx++)
	{
		checksum += UserBuffer[idx];
	}

	return checksum;
}
