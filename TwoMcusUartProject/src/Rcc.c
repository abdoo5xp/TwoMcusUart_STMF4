/*
 * Rcc.c
 *
 *  Created on: Jan 26, 2021
 *      Author: Esraa Abdelnaby
 */

#include "../../Esraa_Lib/Std_Types.h"
#include "../../Esraa_Lib/bit.h"
#include "diag/Trace.h"
#include "Rcc_int.h"

typedef struct
{
	defined_uint32_t RCC_CR         ; //1
	defined_uint32_t RCC_PLLCFGR 	 ; //2
	defined_uint32_t RCC_CFGR       ; //3
	defined_uint32_t RCC_CIR        ; //4
	defined_uint32_t RCC_AHB1RSTR	 ; //5
	defined_uint32_t RCC_AHB2RSTR	 ; //6
	defined_uint32_t RCC_AHB3RSTR	 ; //7
	defined_uint32_t RCC_Reserved1	 ; //8
	defined_uint32_t RCC_APB1RSTR	 ; //9
	defined_uint32_t RCC_APB2RSTR	 ; //10
	defined_uint32_t RCC_Reserved2	 ; //11
	defined_uint32_t RCC_Reserved3	 ; //12
	defined_uint32_t RCC_AHB1ENR    ;
	defined_uint32_t RCC_AHB2ENR    ;
	defined_uint32_t RCC_AHB3ENR    ;
	defined_uint32_t RCC_Reserved4	 ;
	defined_uint32_t RCC_APB1ENR    ;
	defined_uint32_t RCC_APB2ENR    ;
	defined_uint32_t RCC_Reserved5	 ;
	defined_uint32_t RCC_Reserved6	 ;
	defined_uint32_t RCC_AHB1LPENR	 ;
	defined_uint32_t RCC_AHB2LPENR	 ;
	defined_uint32_t RCC_AHB3LPENR	 ;
	defined_uint32_t RCC_Reserved7	 ;
	defined_uint32_t RCC_APB1LPENR	 ;
	defined_uint32_t RCC_APB2LPENR	 ;
	defined_uint32_t RCC_Reserved8	 ;
	defined_uint32_t RCC_Reserved9	 ;
	defined_uint32_t RCC_BDCR		 ;
	defined_uint32_t RCC_CSR		 ;
	defined_uint32_t RCC_Reserved10 ;
	defined_uint32_t RCC_Reserved11 ;
	defined_uint32_t RCC_SSCGR		 ;
	defined_uint32_t RCC_PLLI2SCFGR ;
}RCC_Register;

volatile RCC_Register *RCC = (RCC_Register *)0x40023800;

defined_uint32_t pll_clk = 168000000;

defined_uint8_t Enable_RCC_CR_clk(defined_uint32_t RCC_CR_clkOn)
{
	defined_uint8_t enable_state = FAILURE;
	defined_uint8_t clk = 1 ;
	defined_uint32_t time_out=(0x33);
	defined_uint32_t counter = 0;
	if ((RCC_CR_clkOn & (BIT_0|BIT_24)) == (BIT_0|BIT_24)) clk=4;
	else if ((RCC_CR_clkOn & (BIT_16|BIT_24)) == (BIT_16|BIT_24)) clk=6;
	else if (RCC_CR_clkOn & BIT_0) clk=1;
	else if (RCC_CR_clkOn & BIT_16) clk=2;
	else if (RCC_CR_clkOn & BIT_24) clk=3;


	/*Set clock value*/
	RCC->RCC_CR |= RCC_CR_clkOn;

	if (clk==6)
	{
		//HSE PLL
		while((time_out) &&
				!(
						((RCC->RCC_CR & RCC_CR_HSERDY) >> 16)&&
						((RCC->RCC_CR & RCC_CR_PLLRDY) >> 24)
				)
		)
		{
			time_out--;
			counter++;
		}
		if(time_out || (((RCC->RCC_CR & RCC_CR_HSERDY) >> 16)&&((RCC->RCC_CR & RCC_CR_PLLRDY) >> 24)))
		{
			//trace_printf("time = %d counter = %d \n",time_out,counter);
			enable_state = SUCCESS;
		}
		else
		{
			enable_state = FAILURE;
		}
	}
	else if (clk==4)
	{
		//HSI PLL
		while((time_out) &&
				!(
						((RCC->RCC_CR & RCC_CR_HSIRDY) >> 1) &&
						((RCC->RCC_CR & RCC_CR_PLLRDY) >> 24)
				)
		)
		{
			time_out--;
			counter++;
		}
		if(time_out || (((RCC->RCC_CR & RCC_CR_HSIRDY) >> 1) &&((RCC->RCC_CR & RCC_CR_PLLRDY) >> 24)))
		{
			//trace_printf("time = %d counter = %d \n",time_out,counter);
			enable_state = SUCCESS;
		}
		else
		{
			enable_state = FAILURE;
		}
	}
	else if (clk==3)
	{
		//PLL
		while((time_out) &&
				!(
						((RCC->RCC_CR & RCC_CR_PLLRDY)>>24)
				)
		)
		{
			time_out--;
			counter++;
		}
		if(time_out || ((RCC->RCC_CR & RCC_CR_PLLRDY)>>24))
		{
			//trace_printf("time = %d counter = %d \n",time_out,counter);
			enable_state = SUCCESS;
		}
		else
		{
			enable_state = FAILURE;
		}
	}
	else if (clk==2)
	{
		//HSE
		while((time_out) &&
				!(
						((RCC->RCC_CR & RCC_CR_HSERDY)>>16)
				)
		)
		{
			time_out--;
			counter++;
		}
		if(time_out || ((RCC->RCC_CR & RCC_CR_HSERDY)>>16))
		{
			//trace_printf("time = %d counter = %d \n",time_out,counter);
			enable_state = SUCCESS;
		}
		else
		{
			enable_state = FAILURE;
		}
	}
	else if (clk==1)
	{
		//HSI
		while((time_out) &&
				!(
						((RCC->RCC_CR & RCC_CR_HSIRDY)>>1)
				)
		)
		{
			time_out--;
			counter++;
		}
		if(time_out || ((RCC->RCC_CR & RCC_CR_HSIRDY)>>1))
		{
			//trace_printf("time = %d counter = %d \n",time_out,counter);
			enable_state = SUCCESS;
		}
		else
		{
			enable_state = FAILURE;
		}
	}

	return enable_state;
}

defined_uint8_t Disable_RCC_CR_clk(defined_uint32_t RCC_CR_clkClear)
{
	defined_uint8_t disable_state = FAILURE;
	defined_uint8_t clk=1;
	defined_uint32_t time_out=(0x21);

	if (RCC_CR_clkClear == BIT_0_CLEAR) clk=1;
	else if (RCC_CR_clkClear == BIT_16_CLEAR) clk=2;
	else if (RCC_CR_clkClear == BIT_24_CLEAR) clk=3;
	else if (RCC_CR_clkClear == (BIT_0_CLEAR|BIT_24_CLEAR)) clk=4;
	else if (RCC_CR_clkClear == (BIT_16_CLEAR|BIT_24_CLEAR)) clk=6;
	/*Set clock value*/
	RCC->RCC_CR &= RCC_CR_clkClear;


	if (clk==6)
	{
		//HSE PLL
		while((time_out) &&
				(
						((RCC->RCC_CR & RCC_CR_HSERDY) >> 16)&&
						((RCC->RCC_CR & RCC_CR_PLLRDY) >> 24)
				)
		)
		{
			time_out--;
		}
		if(time_out || !(((RCC->RCC_CR & RCC_CR_HSERDY) >> 16) && ((RCC->RCC_CR & RCC_CR_PLLRDY) >> 24)))
		{
			disable_state = SUCCESS;
		}
		else
		{
			disable_state = FAILURE;
		}
	}
	else if (clk==4)
	{
		//HSI PLL
		while((time_out) &&
				(
						((RCC->RCC_CR & RCC_CR_HSIRDY) >> 1) &&
						((RCC->RCC_CR & RCC_CR_PLLRDY) >> 24)
				)
		)
		{
			time_out--;
		}
		if(time_out || ! (((RCC->RCC_CR & RCC_CR_HSIRDY) >> 1) &&((RCC->RCC_CR & RCC_CR_PLLRDY) >> 24)))
		{
			disable_state = SUCCESS;
		}
		else
		{
			disable_state = FAILURE;
		}
	}
	else if (clk==3)
	{
		//PLL
		while((time_out) && ((RCC->RCC_CR & RCC_CR_PLLRDY)>>24))
		{
			time_out--;
		}
		if(time_out || !((RCC->RCC_CR & RCC_CR_PLLRDY)>>24))
		{
			disable_state = SUCCESS;
		}
		else
		{
			disable_state = FAILURE;
		}
	}
	else if (clk==2)
	{
		//HSE
		while((time_out) && ((RCC->RCC_CR & RCC_CR_HSERDY)>>16))
		{
			time_out--;
		}
		if(time_out || !((RCC->RCC_CR & RCC_CR_HSERDY)>>16))
		{
			disable_state = SUCCESS;
		}
		else
		{
			disable_state = FAILURE;
		}
	}
	else if (clk==1)
	{
		//HSI
		while((time_out) && ((RCC->RCC_CR & RCC_CR_HSIRDY)>>1))
		{
			time_out--;
		}
		if(time_out || !((RCC->RCC_CR & RCC_CR_HSIRDY)>>1))
		{
			disable_state = SUCCESS;
		}
		else
		{
			disable_state = FAILURE;
		}
	}

	return disable_state;
}

defined_uint8_t Select_SysClk_RCC_CFGR_SW(defined_uint32_t SYSCLK_SWS_clk)
{
	defined_uint8_t selection_state = FAILURE;
	defined_uint32_t temp_reg;
	switch(SYSCLK_SWS_clk)
	{

	//use HSI as SYSCLK
	case SYSCLK_SWS_HSI:
		RCC->RCC_CFGR &= RCC_CFGR_SW_CLEAR;

		if (((RCC->RCC_CFGR & RCC_CFGR_SWS_LEN)>>2) == SYSCLK_SWS_HSI)
			selection_state = SUCCESS;

		else selection_state= FAILURE;
		break;
		//use HSE as SYSCLK
	case SYSCLK_SWS_HSE:
		//HSEON ==> 1
		temp_reg = RCC->RCC_CFGR;
		temp_reg &= RCC_CFGR_SW_CLEAR;
		temp_reg |= RCC_CFGR_SW_0;
		RCC->RCC_CFGR = temp_reg ;

		if(((RCC->RCC_CFGR & RCC_CFGR_SWS_LEN)>>2) == SYSCLK_SWS_HSE)
			selection_state = SUCCESS;
		else
			selection_state= FAILURE;
		break;

		//use PLLCLK as SYSCLK
	case SYSCLK_SWS_PLL:
		temp_reg = RCC->RCC_CFGR;
		temp_reg &= RCC_CFGR_SW_CLEAR;
		temp_reg |= RCC_CFGR_SW_1;
		RCC->RCC_CFGR = temp_reg ;

		if(((RCC->RCC_CFGR & RCC_CFGR_SWS_LEN) >> 2) == SYSCLK_SWS_PLL)
			selection_state = SUCCESS;
		else selection_state= FAILURE;
		break;

		//SYSCLK failed to change SYSCLK
	default:
		selection_state= FAILURE;
		break;
	}

	return selection_state;

}

defined_uint8_t Configure_RCC_PLLCFGR(RCC_PLL_configration pll)
{
	defined_uint32_t pllcfgr = RCC->RCC_PLLCFGR;
	defined_uint32_t vco;
	defined_uint8_t  cfg_state = FAILURE;

	if((RCC->RCC_CR & RCC_CR_PLLRDY) >> 24)
	{
		cfg_state = FAILURE;
	}
	else
	{
		if((pll.pll_m >= 2 && pll.pll_m <= 63) &&
				(pll.pll_n >= 50 && pll.pll_n <= 432 ) &&
				(pll.pll_p == 2 || pll.pll_p == 4 || pll.pll_p == 6 || pll.pll_p ==8) &&
				(pll.pll_q >=2 && pll.pll_q <= 15))

		{
			if(pll.pll_src == PLL_SRC_HSE)
			{
				vco = HSE_CLK / pll.pll_m;
			}
			else if (pll.pll_src == PLL_SRC_HSI)
			{
				vco = HSI_CLK / pll.pll_m;
			}
			else
			{
				cfg_state = FAILURE;
				return cfg_state;
			}
			pll_clk = ((vco*pll.pll_n) / pll.pll_p);

			pllcfgr &= ~(RCC_PLLCFGR_PLLM);

			pllcfgr |= (RCC_PLLCFGR_PLLM & pll.pll_m);
			pllcfgr &= ~(RCC_PLLCFGR_PLLN);

			pllcfgr |= ((pll.pll_n << 6) & RCC_PLLCFGR_PLLN ) ;


			pllcfgr &= ~ (RCC_PLLCFGR_PLLP);

			pllcfgr |= (RCC_PLLCFGR_PLLP & (pll.pll_p << 16));

			pllcfgr &= ~(RCC_PLLCFGR_PLLSRC);

			pllcfgr |= (RCC_PLLCFGR_PLLSRC & (pll.pll_src << 22));

			pllcfgr &= ~(RCC_PLLCFGR_PLLQ);

			pllcfgr |= (RCC_PLLCFGR_PLLQ & (pll.pll_q << 24));

			RCC->RCC_PLLCFGR = pllcfgr;

			cfg_state = SUCCESS;
		}
		else
		{
			cfg_state = FAILURE;
		}
	}
	return cfg_state;
}

defined_uint8_t get_current_sysclk_frequency(defined_uint32_t *sysclk_frequency)
{
	defined_uint8_t get_current_freq_state = FAILURE;

	if(((RCC->RCC_CFGR & RCC_CFGR_SWS_LEN)>>2) == SYSCLK_SWS_HSI)
	{
		*sysclk_frequency = HSI_CLK;
		get_current_freq_state = SUCCESS;
	}
	else if(((RCC->RCC_CFGR & RCC_CFGR_SWS_LEN) >> 2) == SYSCLK_SWS_HSE)
	{
		*sysclk_frequency = HSE_CLK;
		get_current_freq_state = SUCCESS;
	}

	else if(((RCC->RCC_CFGR & RCC_CFGR_SWS_LEN) >> 2) == SYSCLK_SWS_PLL)
	{
		*sysclk_frequency = pll_clk;
		get_current_freq_state = SUCCESS;
	}
	else
	{
		get_current_freq_state = FAILURE;
	}
	return get_current_freq_state;
}

defined_uint8_t Set_RCC_CFGR_HPRE(uint64_t RCC_CFGR_HPRE_DIV_number)
{
	defined_uint32_t set_prescaler_state = FAILURE;
	defined_uint32_t AHB_prescaler;
	if(RCC_CFGR_HPRE_DIV_number & RCC_CFGR_HPRE_MASK)
	{
		AHB_prescaler = RCC->RCC_CFGR;
		AHB_prescaler &= ~(RCC_CFGR_HPRE_MASK);
		AHB_prescaler |= RCC_CFGR_HPRE_DIV_number;
		RCC->RCC_CFGR |= AHB_prescaler ;
		set_prescaler_state = SUCCESS;
	}
	else
	{
		set_prescaler_state = FAILURE;
	}
	return set_prescaler_state;
}

defined_uint32_t Get_RCC_AHB_Freq()
{
	defined_uint32_t SysCurrentClk_freq=0;
	defined_uint32_t AHB_prescaler;
	defined_uint32_t prescaler;

	if(((RCC->RCC_CFGR & RCC_CFGR_SWS_LEN)>>2) == SYSCLK_SWS_HSI)
	{
		SysCurrentClk_freq = HSI_CLK;
	}
	else if(((RCC->RCC_CFGR & RCC_CFGR_SWS_LEN) >> 2) == SYSCLK_SWS_HSE)
	{
		SysCurrentClk_freq = HSE_CLK;
	}

	else if(((RCC->RCC_CFGR & RCC_CFGR_SWS_LEN) >> 2) == SYSCLK_SWS_PLL)
	{
		SysCurrentClk_freq = pll_clk;
	}

	AHB_prescaler = RCC->RCC_CFGR;

	AHB_prescaler &= RCC_CFGR_HPRE_READ;

	AHB_prescaler >>= 4;

	switch(AHB_prescaler)
	{
	case RCC_CFGR_HPRE_DIV_2:
		prescaler=2;
		break;
	case RCC_CFGR_HPRE_DIV_4:
		prescaler=4;
				break;
	case RCC_CFGR_HPRE_DIV_8:
		prescaler=8;
				break;
	case RCC_CFGR_HPRE_DIV_16:
		prescaler=16;
				break;
	case RCC_CFGR_HPRE_DIV_64:
		prescaler=64;
				break;
	case RCC_CFGR_HPRE_DIV_128:
		prescaler=128;
				break;
	case RCC_CFGR_HPRE_DIV_512:
		prescaler=512;
				break;
	default:
		prescaler=1;
				break;
	}
	return SysCurrentClk_freq/prescaler;
}

defined_uint8_t Set_RCC_CFGR_PPRE1(uint64_t RCC_CFGR_PPRE1_DIV_number)
{
	defined_uint32_t set_prescaler_state = FAILURE;
	defined_uint32_t APB1_prescaler;
	if(RCC_CFGR_PPRE1_DIV_number & RCC_CFGR_PPRE1_MASK)
	{
		APB1_prescaler = RCC->RCC_CFGR;
		APB1_prescaler &= ~(RCC_CFGR_PPRE1_MASK);
		APB1_prescaler |= RCC_CFGR_PPRE1_DIV_number;
		RCC->RCC_CFGR |= APB1_prescaler ;
		set_prescaler_state = SUCCESS;
	}
	else
	{
		set_prescaler_state = FAILURE;
	}
	return set_prescaler_state;
}

defined_uint8_t Set_RCC_CFGR_PPRE2(uint64_t RCC_CFGR_PPRE2_DIV_number)
{
	defined_uint32_t set_prescaler_state = FAILURE;
	defined_uint32_t APB2_prescaler;
	if(RCC_CFGR_PPRE2_DIV_number & RCC_CFGR_PPRE2_MASK)
	{
		APB2_prescaler = RCC->RCC_CFGR;
		APB2_prescaler &= ~(RCC_CFGR_PPRE2_MASK);
		APB2_prescaler |= RCC_CFGR_PPRE2_DIV_number;
		RCC->RCC_CFGR |= APB2_prescaler ;
		set_prescaler_state = SUCCESS;
	}
	else
	{
		set_prescaler_state = FAILURE;
	}
	return set_prescaler_state;
}

defined_uint8_t Set_RCC_CFGR_MCO1_clk(uint64_t RCC_CFGR_MCO1_clk)
{
	defined_uint32_t clock = (defined_uint32_t)(RCC_CFGR_MCO1_clk);
	defined_uint8_t enable_mco_state = FAILURE;

	if(RCC_CFGR_MCO1_clk & RCC_CFGR_MCO1_MASK)
	{
		RCC->RCC_CFGR |= clock;
		enable_mco_state = SUCCESS;
	}

	return enable_mco_state;
}

defined_uint8_t Set_RCC_CFGR_MCO2_clk(uint64_t RCC_CFGR_MCO2_clk)
{
	defined_uint32_t clock = (defined_uint32_t)(RCC_CFGR_MCO2_clk);
	defined_uint8_t enable_mco_state = FAILURE;
	if(RCC_CFGR_MCO2_clk & RCC_CFGR_MCO2_MASK)
	{
		RCC->RCC_CFGR |= clock;
		enable_mco_state = SUCCESS;
	}

	return enable_mco_state;
}

defined_uint8_t Set_RCC_CFGR_MCO1PRE(uint64_t RCC_CFGR_MCO1PRE_DIV_number)
{
	defined_uint32_t prescaler = (defined_uint32_t)(RCC_CFGR_MCO1PRE_DIV_number);
	defined_uint32_t set_prescaler_state = FAILURE;
	if(RCC_CFGR_MCO1PRE_DIV_number & RCC_CFGR_MCO1_MASK)
	{
		RCC->RCC_CFGR |= prescaler;
		set_prescaler_state = SUCCESS;
	}
	return set_prescaler_state;
}

defined_uint8_t Set_RCC_CFGR_MCO2PRE(uint64_t RCC_CFGR_MCO2PRE_DIV_number)
{
	defined_uint32_t prescaler = (defined_uint32_t)(RCC_CFGR_MCO2PRE_DIV_number);
	defined_uint32_t set_prescaler_state = FAILURE;
	if(RCC_CFGR_MCO2PRE_DIV_number & RCC_CFGR_MCO2_MASK)
	{
		RCC->RCC_CFGR |= prescaler;
		set_prescaler_state = SUCCESS;
	}
	return set_prescaler_state;
}

defined_uint8_t Enable_RCC_AHB1_PERI(uint64_t RCC_AHB1_PERI_name)
{
	defined_uint32_t peripheral = (defined_uint32_t)(RCC_AHB1_PERI_name);

	defined_uint8_t enable_state = FAILURE;
	if((RCC_AHB1_PERI_name & RCC_AHB1ENR_MASK) == RCC_AHB1ENR_MASK)
	{
		RCC->RCC_AHB1ENR |= peripheral;
		enable_state = SUCCESS;
	}
	else
	{
		enable_state = FAILURE;
	}
	return enable_state;
}

defined_uint8_t Enable_RCC_AHB2_PERI(uint64_t RCC_AHB2_PERI_name)
{
	defined_uint32_t peripheral = (defined_uint32_t)(RCC_AHB2_PERI_name);

	defined_uint8_t enable_state = FAILURE;
	if((RCC_AHB2_PERI_name & RCC_AHB2ENR_MASK) == RCC_AHB2ENR_MASK)
	{
		RCC->RCC_AHB2ENR |= peripheral;
		enable_state = SUCCESS;
	}
	else
	{
		enable_state = FAILURE;
	}
	return enable_state;

}

defined_uint8_t Enable_RCC_AHB3_PERI(uint64_t RCC_AHB3_PERI_name)
{
	defined_uint32_t peripheral = (defined_uint32_t)(RCC_AHB3_PERI_name);

	defined_uint8_t enable_state = FAILURE;
	if((RCC_AHB3_PERI_name & RCC_AHB3ENR_MASK) == RCC_AHB3ENR_MASK)
	{
		RCC->RCC_AHB3ENR |= peripheral;
		enable_state = SUCCESS;
	}
	else
	{
		enable_state = FAILURE;
	}
	return enable_state;
}

defined_uint8_t Enable_RCC_APB1_PERI(uint64_t RCC_APB1_PERI_name)
{
	defined_uint32_t peripheral = (defined_uint32_t)(RCC_APB1_PERI_name);

	defined_uint8_t enable_state = FAILURE;
	if((RCC_APB1_PERI_name & RCC_APB1ENR_MASK) == RCC_APB1ENR_MASK)
	{
		RCC->RCC_APB1ENR |= peripheral;
		enable_state = SUCCESS;
	}
	else
	{
		enable_state = FAILURE;
	}
	return enable_state;
}

defined_uint8_t Enable_RCC_APB2_PERI(uint64_t RCC_APB2_PERI_name)
{
	defined_uint32_t peripheral = (defined_uint32_t)(RCC_APB2_PERI_name);

	defined_uint8_t enable_state = FAILURE;
	if((RCC_APB2_PERI_name & RCC_APB2ENR_MASK) == RCC_APB2ENR_MASK)
	{
		RCC->RCC_APB2ENR |= peripheral;
		enable_state = SUCCESS;
	}
	else
	{
		enable_state = FAILURE;
	}
	return enable_state;
}

defined_uint8_t Enable_RCC_AHB1LP_PERI(uint64_t RCC_AHB1LP_PERI_name)
{
	defined_uint32_t peripheral = (defined_uint32_t)(RCC_AHB1LP_PERI_name);

	defined_uint8_t enable_state = FAILURE;
	if((RCC_AHB1LP_PERI_name & RCC_AHB1LPENR_MASK) == RCC_AHB1LPENR_MASK)
	{
		RCC->RCC_AHB1LPENR |= peripheral;
		enable_state = SUCCESS;
	}
	else
	{
		enable_state = FAILURE;
	}
	return enable_state;
}

defined_uint8_t Enable_RCC_AHB2LP_PERI(uint64_t RCC_AHB2LP_PERI_name)
{
	defined_uint32_t peripheral = (defined_uint32_t)(RCC_AHB2LP_PERI_name);

	defined_uint8_t enable_state = FAILURE;
	if((RCC_AHB2LP_PERI_name & RCC_AHB2LPENR_MASK) == RCC_AHB2LPENR_MASK)
	{
		RCC->RCC_AHB2LPENR |= peripheral;
		enable_state = SUCCESS;
	}
	else
	{
		enable_state = FAILURE;
	}
	return enable_state;
}

defined_uint8_t Enable_RCC_AHB3LP_PERI(uint64_t RCC_AHB3LP_PERI_name)
{
	defined_uint32_t peripheral = (defined_uint32_t)(RCC_AHB3LP_PERI_name);

	defined_uint8_t enable_state = FAILURE;
	if((RCC_AHB3LP_PERI_name & RCC_AHB3LPENR_MASK) == RCC_AHB3LPENR_MASK)
	{
		RCC->RCC_AHB3LPENR |= peripheral;
		enable_state = SUCCESS;
	}
	else
	{
		enable_state = FAILURE;
	}
	return enable_state;
}

defined_uint8_t Enable_RCC_APB1LP_PERI(uint64_t RCC_APB1LP_PERI_name)
{
	defined_uint32_t peripheral = (defined_uint32_t)(RCC_APB1LP_PERI_name);

	defined_uint8_t enable_state = FAILURE;
	if((RCC_APB1LP_PERI_name & RCC_APB1LPENR_MASK) == RCC_APB1LPENR_MASK)
	{
		RCC->RCC_APB1LPENR |= peripheral;
		enable_state = SUCCESS;
	}
	else
	{
		enable_state = FAILURE;
	}
	return enable_state;
}

defined_uint8_t Enable_RCC_APB2LP_PERI(uint64_t RCC_APB2LP_PERI_name)
{
	defined_uint32_t peripheral = (defined_uint32_t)(RCC_APB2LP_PERI_name);

	defined_uint8_t enable_state = FAILURE;
	if((RCC_APB2LP_PERI_name & RCC_APB2LPENR_MASK) == RCC_APB2LPENR_MASK)
	{
		RCC->RCC_APB2LPENR |= peripheral;
		enable_state = SUCCESS;
	}
	else
	{
		enable_state = FAILURE;
	}
	return enable_state;
}


defined_uint8_t Disable_RCC_AHB1_PERI(uint64_t RCC_AHB1_PERI_name)
{
	defined_uint32_t peripheral = (defined_uint32_t)(RCC_AHB1_PERI_name);

	defined_uint8_t disable_state = FAILURE;
	if((RCC_AHB1_PERI_name & RCC_AHB1ENR_MASK) == RCC_AHB1ENR_MASK)
	{
		RCC->RCC_AHB1ENR &= ~peripheral;
		disable_state = SUCCESS;
	}
	else
	{
		disable_state = FAILURE ;
	}
	return disable_state;

}

defined_uint8_t Disable_RCC_AHB2_PERI(uint64_t RCC_AHB2_PERI_name)
{
	defined_uint32_t peripheral = (defined_uint32_t)(RCC_AHB2_PERI_name);

	defined_uint8_t disable_state = FAILURE;
	if((RCC_AHB2_PERI_name & RCC_AHB2ENR_MASK) == RCC_AHB2ENR_MASK)
	{
		RCC->RCC_AHB2ENR &= ~peripheral;
		disable_state = SUCCESS;
	}
	else
	{
		disable_state = FAILURE ;
	}
	return disable_state;

}

defined_uint8_t Disable_RCC_AHB3_PERI(uint64_t RCC_AHB3_PERI_name)
{
	defined_uint32_t peripheral = (defined_uint32_t)(RCC_AHB3_PERI_name);

	defined_uint8_t disable_state = FAILURE;
	if((RCC_AHB3_PERI_name & RCC_AHB3ENR_MASK) == RCC_AHB3ENR_MASK)
	{
		RCC->RCC_AHB3ENR &= ~peripheral;
		disable_state = SUCCESS;
	}
	else
	{
		disable_state = FAILURE ;
	}
	return disable_state;
}

defined_uint8_t Disable_RCC_APB1_PERI(uint64_t RCC_APB1_PERI_name)
{
	defined_uint32_t peripheral = (defined_uint32_t)(RCC_APB1_PERI_name);

	defined_uint8_t disable_state = FAILURE;
	if((RCC_APB1_PERI_name & RCC_APB1ENR_MASK) == RCC_APB1ENR_MASK)
	{
		RCC->RCC_APB1ENR &= ~peripheral;
		disable_state = SUCCESS;
	}
	else
	{
		disable_state = FAILURE ;
	}
	return disable_state;
}

defined_uint8_t Disable_RCC_APB2_PERI(uint64_t RCC_APB2_PERI_name)
{
	defined_uint32_t peripheral = (defined_uint32_t)(RCC_APB2_PERI_name);

	defined_uint8_t disable_state = FAILURE;
	if((RCC_APB2_PERI_name & RCC_APB2ENR_MASK) == RCC_APB2ENR_MASK)
	{
		RCC->RCC_APB2ENR &= ~peripheral;
		disable_state = SUCCESS;
	}
	else
	{
		disable_state = FAILURE ;
	}
	return disable_state;

}

defined_uint8_t Disable_RCC_AHB1LP_PERI(uint64_t RCC_AHB1LP_PERI_name)
{
	defined_uint32_t peripheral = (defined_uint32_t)(RCC_AHB1LP_PERI_name);

	defined_uint8_t disable_state = FAILURE;
	if((RCC_AHB1LP_PERI_name & RCC_AHB1LPENR_MASK) == RCC_AHB1LPENR_MASK)
	{
		RCC->RCC_AHB1LPENR &= ~peripheral;
		disable_state = SUCCESS;
	}
	else
	{
		disable_state = FAILURE ;
	}
	return disable_state;
}

defined_uint8_t Disable_RCC_AHB2LP_PERI(uint64_t RCC_AHB2LP_PERI_name)
{
	defined_uint32_t peripheral = (defined_uint32_t)(RCC_AHB2LP_PERI_name);

	defined_uint8_t disable_state = FAILURE;
	if((RCC_AHB2LP_PERI_name & RCC_AHB2LPENR_MASK) ==RCC_AHB2LPENR_MASK)
	{
		RCC->RCC_AHB2LPENR &= ~peripheral;
		disable_state = SUCCESS;
	}
	else
	{
		disable_state = FAILURE ;
	}
	return disable_state;
}

defined_uint8_t Disable_RCC_AHB3LP_PERI(uint64_t RCC_AHB3LP_PERI_name)
{
	defined_uint32_t peripheral = (defined_uint32_t)(RCC_AHB3LP_PERI_name);

	defined_uint8_t disable_state = FAILURE;
	if((RCC_AHB3LP_PERI_name & RCC_AHB3LPENR_MASK) == RCC_AHB3LPENR_MASK)
	{
		RCC->RCC_AHB3LPENR &= ~peripheral;
		disable_state = SUCCESS;
	}
	else
	{
		disable_state = FAILURE ;
	}
	return disable_state;
}

defined_uint8_t Disable_RCC_APB1LP_PERI(uint64_t RCC_APB1LP_PERI_name)
{
	defined_uint32_t peripheral = (defined_uint32_t)(RCC_APB1LP_PERI_name);

	defined_uint8_t disable_state = FAILURE;
	if((RCC_APB1LP_PERI_name & RCC_APB1LPENR_MASK) == RCC_APB1LPENR_MASK)
	{
		RCC->RCC_APB1LPENR &= ~peripheral;
		disable_state = SUCCESS;
	}
	else
	{
		disable_state = FAILURE ;
	}
	return disable_state;
}

defined_uint8_t Disable_RCC_APB2LP_PERI(uint64_t RCC_APB2LP_PERI_name)
{
	defined_uint32_t peripheral = (defined_uint32_t)(RCC_APB2LP_PERI_name);

	defined_uint8_t disable_state = FAILURE;
	if((RCC_APB2LP_PERI_name & RCC_APB2LPENR_MASK) == RCC_APB2LPENR_MASK)
	{
		RCC->RCC_APB2LPENR &= ~peripheral;
		disable_state = SUCCESS;
	}
	else
	{
		disable_state = FAILURE ;
	}
	return disable_state;
}
