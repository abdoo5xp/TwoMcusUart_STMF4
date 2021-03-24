/*
 * RCC_init.h
 *
 *  Created on: Feb 23, 2021
 *      Author: Esraa Abdelnaby
 */

#ifndef RCC_INT_H_
#define RCC_INT_H_

/*=======================RCC Peripherals masks======================*/
#define RCC_AHB1ENR_MASK         (defined_uint64_t)(0X0001000100000000)
#define RCC_AHB2ENR_MASK         (defined_uint64_t)(0X0001002000000000)
#define RCC_AHB3ENR_MASK         (defined_uint64_t)(0X0001040000000000)

#define RCC_APB1ENR_MASK         (defined_uint64_t)(0X0020000100000000)
#define RCC_APB2ENR_MASK         (defined_uint64_t)(0X0020002000000000)

#define RCC_AHB1LPENR_MASK	      (defined_uint64_t)(0X0400000100000000)
#define RCC_AHB2LPENR_MASK	      (defined_uint64_t)(0X0400002000000000)
#define RCC_AHB3LPENR_MASK	      (defined_uint64_t)(0X0400040000000000)

#define RCC_APB1LPENR_MASK	      (defined_uint64_t)(0X8000000100000000)
#define RCC_APB2LPENR_MASK	      (defined_uint64_t)(0X8000002000000000)
/*===============================================================================*/

/*============== RCC_CR_PIN_MASKS ==============*/
#define RCC_CR_HSION 		    BIT_0
#define RCC_CR_HSI_CLEAR 	    BIT_0_CLEAR
#define RCC_CR_HSIRDY		    BIT_1

#define RCC_CR_HSITRIM_0	    BIT_3
#define RCC_CR_HSITRIM_1	    BIT_4
#define RCC_CR_HSITRIM_2	    BIT_5
#define RCC_CR_HSITRIM_3	    BIT_6
#define RCC_CR_HSITRIM_4	    BIT_7

#define RCC_CR_HSICAL_0         BIT_8
#define RCC_CR_HSICAL_1         BIT_9
#define RCC_CR_HSICAL_2         BIT_10
#define RCC_CR_HSICAL_3         BIT_11
#define RCC_CR_HSICAL_4         BIT_12
#define RCC_CR_HSICAL_5         BIT_13
#define RCC_CR_HSICAL_6         BIT_14
#define RCC_CR_HSICAL_7         BIT_15

#define RCC_CR_HSEON		    BIT_16
#define RCC_CR_HSE_CLEAR      	BIT_16_CLEAR
#define RCC_CR_HSERDY 		    BIT_17

#define RCC_CR_HSEBYP 		    BIT_18
#define RCC_CR_HSEBYP_CLEAR		BIT_18_CLEAR

#define RCC_CR_CSSON 		    BIT_19
#define RCC_CR_CSS_CLEAR      	BIT_19_CLEAR

#define RCC_CR_PLLON		    BIT_24
#define RCC_CR_PLL_CLEAR	    BIT_24_CLEAR
#define RCC_CR_PLLRDY		    BIT_25

#define RCC_CR_PLLI2SON		    BIT_26
#define RCC_CR_PLLI2S_CLEAR		BIT_26_CLEAR
#define RCC_CR_PLLI2SRDY	    BIT_27
/*===============================================*/

/*===================== RCC_CFGR_PIN_MASK =====================*/

#define RCC_CFGR_SW_0			 BIT_0
#define RCC_CFGR_SW_1            BIT_1
#define RCC_CFGR_SW_CLEAR		 (BIT_0_CLEAR & BIT_1_CLEAR)

#define RCC_CFGR_SWS_0           BIT_2
#define RCC_CFGR_SWS_1           BIT_3
#define RCC_CFGR_SWS_LEN		 (BIT_2 | BIT_3)


#define RCC_CFGR_HPRE_MASK 		  (BIT_31|BIT_7 | BIT_6 | BIT_5 | BIT_4)
#define RCC_CFGR_HPRE_READ 		  (BIT_7 | BIT_6 | BIT_5 | BIT_4)
#define RCC_CFGR_HPRE_DIV_2       (BIT_31|BIT_7 ) //1000
#define RCC_CFGR_HPRE_DIV_4       (BIT_31|BIT_7 | BIT_4) //1001
#define RCC_CFGR_HPRE_DIV_8       (BIT_31|BIT_7 | BIT_5)  //1010
#define RCC_CFGR_HPRE_DIV_16      (BIT_31|BIT_7 | BIT_5 | BIT_4) //1011
#define RCC_CFGR_HPRE_DIV_64      (BIT_31|BIT_7 | BIT_6) //1100
#define RCC_CFGR_HPRE_DIV_128     (BIT_31|BIT_7 | BIT_6 | BIT_4) //1101
#define RCC_CFGR_HPRE_DIV_256     (BIT_31|BIT_7 | BIT_6 | BIT_5) //1110
#define RCC_CFGR_HPRE_DIV_512     (BIT_31|BIT_7 | BIT_6 | BIT_5 | BIT_4) // 1111

#define RCC_CFGR_PPRE1_MASK   	 (BIT_12 | BIT_11 | BIT_10)
#define RCC_CFGR_PPRE1_DIV_2  	 (BIT_12)
#define RCC_CFGR_PPRE1_DIV_4  	 (BIT_12 | BIT_10)
#define RCC_CFGR_PPRE1_DIV_8     (BIT_12 | BIT_11)
#define RCC_CFGR_PPRE1_DIV_16    (BIT_12 | BIT_11 | BIT_10)

#define RCC_CFGR_PPRE2_MASK    	 (BIT_15|BIT_14|BIT_13)
#define RCC_CFGR_PPRE2_DIV_2	 (BIT_15)
#define RCC_CFGR_PPRE2_DIV_4     (BIT_15|BIT_13)
#define RCC_CFGR_PPRE2_DIV_8     (BIT_15|BIT_14)
#define RCC_CFGR_PPRE2_DIV_16    (BIT_15|BIT_14|BIT_13)

#define RCC_CFGR_I2SSRC   (BIT_23)

#define RCC_CFGR_MCO1_MASK (defined_uint64_t) (0x0001000000000000)

#define RCC_CFGR_MCO1_HSI (defined_uint64_t) ( (RCC_CFGR_MCO1_MASK) | ( (defined_uint64_t)( (BIT_21 & BIT_22) ) ) )
#define RCC_CFGR_MCO1_LSE (defined_uint64_t) ( (RCC_CFGR_MCO1_MASK) | ( (defined_uint64_t)( (BIT_21)          ) ) )
#define RCC_CFGR_MCO1_HSE (defined_uint64_t) ( (RCC_CFGR_MCO1_MASK) | ( (defined_uint64_t)( (BIT_22)          ) ) )
#define RCC_CFGR_MCO1_PLL (defined_uint64_t) ( (RCC_CFGR_MCO1_MASK) | ( (defined_uint64_t)( (BIT_21 | BIT_22) ) ) )

#define RCC_CFGR_MCO1PRE_DIV_2	    (defined_uint64_t) ( (RCC_CFGR_MCO1_MASK) | ( (defined_uint64_t)( (BIT_26)                  ) ) )
#define RCC_CFGR_MCO1PRE_DIV_3      (defined_uint64_t) ( (RCC_CFGR_MCO1_MASK) | ( (defined_uint64_t)( (BIT_26 | BIT_24)         ) ) )
#define RCC_CFGR_MCO1PRE_DIV_4	    (defined_uint64_t) ( (RCC_CFGR_MCO1_MASK) | ( (defined_uint64_t)( (BIT_26 | BIT_25)         ) ) )
#define RCC_CFGR_MCO1PRE_DIV_5	    (defined_uint64_t) ( (RCC_CFGR_MCO1_MASK) | ( (defined_uint64_t)( (BIT_26 | BIT_25 | BIT_24)) ) )

#define RCC_CFGR_MCO2_MASK (defined_uint64_t) (0x0020000000000000)

#define RCC_CFGR_MCO2_SYSCLK 		(defined_uint64_t) ( (RCC_CFGR_MCO2_MASK) | ( (defined_uint64_t)( (BIT_30 & BIT_31) ) ) )
#define RCC_CFGR_MCO2_PLLI2S 		(defined_uint64_t) ( (RCC_CFGR_MCO2_MASK) | ( (defined_uint64_t)( (BIT_30)          ) ) )
#define RCC_CFGR_MCO2_HSE 	 		(defined_uint64_t) ( (RCC_CFGR_MCO2_MASK) | ( (defined_uint64_t)( (BIT_31)          ) ) )
#define RCC_CFGR_MCO2_PLL    		(defined_uint64_t) ( (RCC_CFGR_MCO2_MASK) | ( (defined_uint64_t)( (BIT_30 | BIT_31) ) ) )

#define RCC_CFGR_MCO2PRE_DIV_2	 	(defined_uint64_t) ( (RCC_CFGR_MCO2_MASK) | ( (defined_uint64_t)( (BIT_29)                   ) ) )
#define RCC_CFGR_MCO2PRE_DIV_3   	(defined_uint64_t) ( (RCC_CFGR_MCO2_MASK) | ( (defined_uint64_t)( (BIT_29 | BIT_27)          ) ) )
#define RCC_CFGR_MCO2PRE_DIV_4	 	(defined_uint64_t) ( (RCC_CFGR_MCO2_MASK) | ( (defined_uint64_t)( (BIT_29 | BIT_28)          ) ) )
#define RCC_CFGR_MCO2PRE_DIV_5	 	(defined_uint64_t) ( (RCC_CFGR_MCO2_MASK) | ( (defined_uint64_t)( (BIT_29 | BIT_28 | BIT_27) ) ) )

/**********************************************AHB1ENR**********************************************/

#define RCC_AHB1_PERI_GPIOIEN		    (defined_uint64_t) ( (RCC_AHB1ENR_MASK) | ( (defined_uint64_t) BIT_8) )
#define RCC_AHB1_PERI_GPIOHEN		    (defined_uint64_t) ( (RCC_AHB1ENR_MASK) | ( (defined_uint64_t) BIT_7) )
#define RCC_AHB1_PERI_GPIOGEN		    (defined_uint64_t) ( (RCC_AHB1ENR_MASK) | ( (defined_uint64_t) BIT_6) )
#define RCC_AHB1_PERI_GPIOFEN		    (defined_uint64_t) ( (RCC_AHB1ENR_MASK) | ( (defined_uint64_t) BIT_5) )
#define RCC_AHB1_PERI_GPIOEEN		    (defined_uint64_t) ( (RCC_AHB1ENR_MASK) | ( (defined_uint64_t) BIT_4) )
#define RCC_AHB1_PERI_GPIODEN		    (defined_uint64_t) ( (RCC_AHB1ENR_MASK) | ( (defined_uint64_t) BIT_3) )
#define RCC_AHB1_PERI_GPIOCEN		    (defined_uint64_t) ( (RCC_AHB1ENR_MASK) | ( (defined_uint64_t) BIT_2) )
#define RCC_AHB1_PERI_GPIOBEN		    (defined_uint64_t) ( (RCC_AHB1ENR_MASK) | ( (defined_uint64_t) BIT_1) )
#define RCC_AHB1_PERI_GPIOAEN		    (defined_uint64_t) ( (RCC_AHB1ENR_MASK) | ( (defined_uint64_t) BIT_0) )
#define RCC_AHB1_PERI_CRCEN		        (defined_uint64_t) ( (RCC_AHB1ENR_MASK) | ( (defined_uint64_t) BIT_12) )
#define RCC_AHB1_PERI_BKPSRAMEN		    (defined_uint64_t) ( (RCC_AHB1ENR_MASK) | ( (defined_uint64_t) BIT_18) )
#define RCC_AHB1_PERI_DMA2EN		    (defined_uint64_t) ( (RCC_AHB1ENR_MASK) | ( (defined_uint64_t) BIT_22) )
#define RCC_AHB1_PERI_DMA1EN		    (defined_uint64_t) ( (RCC_AHB1ENR_MASK) | ( (defined_uint64_t) BIT_21) )
#define RCC_AHB1_PERI_CCMDATARAMEN	    (defined_uint64_t) ( (RCC_AHB1ENR_MASK) | ( (defined_uint64_t) BIT_20) )
#define RCC_AHB1_PERI_OTGHSULPIEN		(defined_uint64_t) ( (RCC_AHB1ENR_MASK) | ( (defined_uint64_t) BIT_30) )
#define RCC_AHB1_PERI_OTGHSEN		    (defined_uint64_t) ( (RCC_AHB1ENR_MASK) | ( (defined_uint64_t) BIT_29) )
#define RCC_AHB1_PERI_ETHMACPTPEN		(defined_uint64_t) ( (RCC_AHB1ENR_MASK) | ( (defined_uint64_t) BIT_28) )
#define RCC_AHB1_PERI_ETHMACRXEN		(defined_uint64_t) ( (RCC_AHB1ENR_MASK) | ( (defined_uint64_t) BIT_27) )
#define RCC_AHB1_PERI_ETHMACTXEN		(defined_uint64_t) ( (RCC_AHB1ENR_MASK) | ( (defined_uint64_t) BIT_26) )
#define RCC_AHB1_PERI_ETHMACEN		    (defined_uint64_t) ( (RCC_AHB1ENR_MASK) | ( (defined_uint64_t) BIT_25) )

/**********************************************AHB2ENR**********************************************/

#define RCC_AHB2_PERI_OTGFSEN           (defined_uint64_t) ( (RCC_AHB2ENR_MASK) | ( (defined_uint64_t) BIT_7) )
#define RCC_AHB2_PERI_RNGEN             (defined_uint64_t) ( (RCC_AHB2ENR_MASK) | ( (defined_uint64_t) BIT_6) )
#define RCC_AHB2_PERI_HASHEN            (defined_uint64_t) ( (RCC_AHB2ENR_MASK) | ( (defined_uint64_t) BIT_5) )
#define RCC_AHB2_PERI_CRYPEN            (defined_uint64_t) ( (RCC_AHB2ENR_MASK) | ( (defined_uint64_t) BIT_4) )
#define RCC_AHB2_PERI_DCMIEN            (defined_uint64_t) ( (RCC_AHB2ENR_MASK) | ( (defined_uint64_t) BIT_0) )

/**********************************************AHB3ENR**********************************************/

#define RCC_AHB3ENR_FSMCEN	            (defined_uint64_t) ( (RCC_AHB3ENR_MASK) | ( (defined_uint64_t) BIT_0 ) )

/**********************************************APB1ENR**********************************************/

#define RCC_APB1_PERI_TIM14EN		(defined_uint64_t) ( (RCC_APB1ENR_MASK) | ( (defined_uint64_t) BIT_8) )
#define RCC_APB1_PERI_TIM13EN		(defined_uint64_t) ( (RCC_APB1ENR_MASK) | ( (defined_uint64_t) BIT_7) )
#define RCC_APB1_PERI_TIM12EN		(defined_uint64_t) ( (RCC_APB1ENR_MASK) | ( (defined_uint64_t) BIT_6) )
#define RCC_APB1_PERI_TIM7EN		(defined_uint64_t) ( (RCC_APB1ENR_MASK) | ( (defined_uint64_t) BIT_5) )
#define RCC_APB1_PERI_TIM6EN		(defined_uint64_t) ( (RCC_APB1ENR_MASK) | ( (defined_uint64_t) BIT_4) )
#define RCC_APB1_PERI_TIM5EN		(defined_uint64_t) ( (RCC_APB1ENR_MASK) | ( (defined_uint64_t) BIT_3) )
#define RCC_APB1_PERI_TIM4EN		(defined_uint64_t) ( (RCC_APB1ENR_MASK) | ( (defined_uint64_t) BIT_2) )
#define RCC_APB1_PERI_TIM3EN		(defined_uint64_t) ( (RCC_APB1ENR_MASK) | ( (defined_uint64_t) BIT_1) )
#define RCC_APB1_PERI_TIM2EN		(defined_uint64_t) ( (RCC_APB1ENR_MASK) | ( (defined_uint64_t) BIT_0) )
#define RCC_APB1_PERI_WWDGEN		(defined_uint64_t) ( (RCC_APB1ENR_MASK) | ( (defined_uint64_t) BIT_11) )
#define RCC_APB1_PERI_SPI3EN		(defined_uint64_t) ( (RCC_APB1ENR_MASK) | ( (defined_uint64_t) BIT_15) )
#define RCC_APB1_PERI_SPI2EN        (defined_uint64_t) ( (RCC_APB1ENR_MASK) | ( (defined_uint64_t) BIT_14) )
#define RCC_APB1_PERI_I2C3EN		(defined_uint64_t) ( (RCC_APB1ENR_MASK) | ( (defined_uint64_t) BIT_23) )
#define RCC_APB1_PERI_I2C2EN        (defined_uint64_t) ( (RCC_APB1ENR_MASK) | ( (defined_uint64_t) BIT_22) )
#define RCC_APB1_PERI_I2C1EN        (defined_uint64_t) ( (RCC_APB1ENR_MASK) | ( (defined_uint64_t) BIT_21) )
#define RCC_APB1_PERI_UART5EN       (defined_uint64_t) ( (RCC_APB1ENR_MASK) | ( (defined_uint64_t) BIT_20) )
#define RCC_APB1_PERI_UART4EN       (defined_uint64_t) ( (RCC_APB1ENR_MASK) | ( (defined_uint64_t) BIT_19) )
#define RCC_APB1_PERI_USART3EN      (defined_uint64_t) ( (RCC_APB1ENR_MASK) | ( (defined_uint64_t) BIT_18) )
#define RCC_APB1_PERI_USART2EN      (defined_uint64_t) ( (RCC_APB1ENR_MASK) | ( (defined_uint64_t) BIT_17) )
#define RCC_APB1_PERI_CAN2EN		(defined_uint64_t) ( (RCC_APB1ENR_MASK) | ( (defined_uint64_t) BIT_26) )
#define RCC_APB1_PERI_CAN1EN        (defined_uint64_t) ( (RCC_APB1ENR_MASK) | ( (defined_uint64_t) BIT_25) )
#define RCC_APB1_PERI_DACEN         (defined_uint64_t) ( (RCC_APB1ENR_MASK) | ( (defined_uint64_t) BIT_29) )
#define RCC_APB1_PERI_PWREN         (defined_uint64_t) ( (RCC_APB1ENR_MASK) | ( (defined_uint64_t) BIT_28) )

/*******************************************APB2ENR**********************************************/

#define RCC_APB2_PERI_TIM11EN            (defined_uint64_t) ( (RCC_APB2ENR_MASK) | ( (defined_uint64_t) BIT_18) )
#define RCC_APB2_PERI_TIM10EN            (defined_uint64_t) ( (RCC_APB2ENR_MASK) | ( (defined_uint64_t) BIT_17) )
#define RCC_APB2_PERI_TIM9EN             (defined_uint64_t) ( (RCC_APB2ENR_MASK) | ( (defined_uint64_t) BIT_16) )
#define RCC_APB2_PERI_SYSCFGEN           (defined_uint64_t) ( (RCC_APB2ENR_MASK) | ( (defined_uint64_t) BIT_14) )
#define RCC_APB2_PERI_SPI1EN             (defined_uint64_t) ( (RCC_APB2ENR_MASK) | ( (defined_uint64_t) BIT_12) )
#define RCC_APB2_PERI_SDIOEN             (defined_uint64_t) ( (RCC_APB2ENR_MASK) | ( (defined_uint64_t) BIT_11) )
#define RCC_APB2_PERI_ADC3EN             (defined_uint64_t) ( (RCC_APB2ENR_MASK) | ( (defined_uint64_t) BIT_10) )
#define RCC_APB2_PERI_ADC2EN             (defined_uint64_t) ( (RCC_APB2ENR_MASK) | ( (defined_uint64_t) BIT_9 ) )
#define RCC_APB2_PERI_ADC1EN             (defined_uint64_t) ( (RCC_APB2ENR_MASK) | ( (defined_uint64_t) BIT_8 ) )
#define RCC_APB2_PERI_USART6EN           (defined_uint64_t) ( (RCC_APB2ENR_MASK) | ( (defined_uint64_t) BIT_5 ) )
#define RCC_APB2_PERI_USART1EN           (defined_uint64_t) ( (RCC_APB2ENR_MASK) | ( (defined_uint64_t) BIT_4 ) )
#define RCC_APB2_PERI_TIM8EN             (defined_uint64_t) ( (RCC_APB2ENR_MASK) | ( (defined_uint64_t) BIT_1 ) )
#define RCC_APB2_PERI_TIM1EN             (defined_uint64_t) ( (RCC_APB2ENR_MASK) | ( (defined_uint64_t) BIT_0 ) )

/**********************************************AHB1LPENR**********************************************/

#define RCC_AHB1LP_PERI_GPIOILPEN		       (defined_uint64_t) ( (RCC_AHB1LPENR_MASK) | ( (defined_uint64_t) BIT_8 ) )
#define RCC_AHB1LP_PERI_GPIOHLPEN		       (defined_uint64_t) ( (RCC_AHB1LPENR_MASK) | ( (defined_uint64_t) BIT_7 ) )
#define RCC_AHB1LP_PERI_GPIOGLPEN		       (defined_uint64_t) ( (RCC_AHB1LPENR_MASK) | ( (defined_uint64_t) BIT_6 ) )
#define RCC_AHB1LP_PERI_GPIOFLPEN		       (defined_uint64_t) ( (RCC_AHB1LPENR_MASK) | ( (defined_uint64_t) BIT_5 ) )
#define RCC_AHB1LP_PERI_GPIOELPEN		       (defined_uint64_t) ( (RCC_AHB1LPENR_MASK) | ( (defined_uint64_t) BIT_4 ) )
#define RCC_AHB1LP_PERI_GPIODLPEN		       (defined_uint64_t) ( (RCC_AHB1LPENR_MASK) | ( (defined_uint64_t) BIT_3 ) )
#define RCC_AHB1LP_PERI_GPIOCLPEN		       (defined_uint64_t) ( (RCC_AHB1LPENR_MASK) | ( (defined_uint64_t) BIT_2 ) )
#define RCC_AHB1LP_PERI_GPIOBLPEN		       (defined_uint64_t) ( (RCC_AHB1LPENR_MASK) | ( (defined_uint64_t) BIT_1 ) )
#define RCC_AHB1LP_PERI_GPIOALPEN		       (defined_uint64_t) ( (RCC_AHB1LPENR_MASK) | ( (defined_uint64_t) BIT_0 ) )
#define RCC_AHB1LP_PERI_CRCLPEN		           (defined_uint64_t) ( (RCC_AHB1LPENR_MASK) | ( (defined_uint64_t) BIT_12) )
#define RCC_AHB1LP_PERI_BKPSRAMLPEN	           (defined_uint64_t) ( (RCC_AHB1LPENR_MASK) | ( (defined_uint64_t) BIT_18) )
#define RCC_AHB1LP_PERI_SRAM2LPEN		       (defined_uint64_t) ( (RCC_AHB1LPENR_MASK) | ( (defined_uint64_t) BIT_17) )
#define RCC_AHB1LP_PERI_SRAM1LPEN		       (defined_uint64_t) ( (RCC_AHB1LPENR_MASK) | ( (defined_uint64_t) BIT_16) )
#define RCC_AHB1LP_PERI_FLITFLPEN		       (defined_uint64_t) ( (RCC_AHB1LPENR_MASK) | ( (defined_uint64_t) BIT_15) )
#define RCC_AHB1LP_PERI_DMA2LPEN		       (defined_uint64_t) ( (RCC_AHB1LPENR_MASK) | ( (defined_uint64_t) BIT_22) )
#define RCC_AHB1LP_PERI_DMA1LPEN		       (defined_uint64_t) ( (RCC_AHB1LPENR_MASK) | ( (defined_uint64_t) BIT_21) )
#define RCC_AHB1LP_PERI_OTGHSULPILPEN	       (defined_uint64_t) ( (RCC_AHB1LPENR_MASK) | ( (defined_uint64_t) BIT_30) )
#define RCC_AHB1LP_PERI_OTGHSLPEN		       (defined_uint64_t) ( (RCC_AHB1LPENR_MASK) | ( (defined_uint64_t) BIT_29) )
#define RCC_AHB1LP_PERI_ETHMACPTPLPEN	       (defined_uint64_t) ( (RCC_AHB1LPENR_MASK) | ( (defined_uint64_t) BIT_28) )
#define RCC_AHB1LP_PERI_ETHMACRXLPEN	       (defined_uint64_t) ( (RCC_AHB1LPENR_MASK) | ( (defined_uint64_t) BIT_27) )
#define RCC_AHB1LP_PERI_ETHMACTXLPEN	       (defined_uint64_t) ( (RCC_AHB1LPENR_MASK) | ( (defined_uint64_t) BIT_26) )
#define RCC_AHB1LP_PERI_ETHMACLPEN	           (defined_uint64_t) ( (RCC_AHB1LPENR_MASK) | ( (defined_uint64_t) BIT_25) )

/**********************************************AHB2LPENR**********************************************/

#define RCC_AHB2LP_PERI_DCMILPEN			   (defined_uint64_t) ( (RCC_APB2LPENR_MASK) | ( (defined_uint64_t) BIT_0 ) )
#define RCC_AHB2LP_PERI_CRYPLPEN			   (defined_uint64_t) ( (RCC_APB2LPENR_MASK) | ( (defined_uint64_t) BIT_4 ) )
#define RCC_AHB2LP_PERI_HASHLPEN			   (defined_uint64_t) ( (RCC_APB2LPENR_MASK) | ( (defined_uint64_t) BIT_5 ) )
#define RCC_AHB2LP_PERI_RNGLPEN			       (defined_uint64_t) ( (RCC_APB2LPENR_MASK) | ( (defined_uint64_t) BIT_6 ) )
#define RCC_AHB2LP_PERI_OTGFSLPEN              (defined_uint64_t) ( (RCC_APB2LPENR_MASK) | ( (defined_uint64_t) BIT_7 ) )

/********************************************************************************************/



/**********************************************APB1LPENR**********************************************/

#define RCC_APB1LP_PERI_TIM14LPEN		(defined_uint64_t) ( (RCC_APB1LPENR_MASK) | ( (defined_uint64_t) BIT_8 ) )
#define RCC_APB1LP_PERI_TIM13LPEN		(defined_uint64_t) ( (RCC_APB1LPENR_MASK) | ( (defined_uint64_t) BIT_7 ) )
#define RCC_APB1LP_PERI_TIM12LPEN		(defined_uint64_t) ( (RCC_APB1LPENR_MASK) | ( (defined_uint64_t) BIT_6 ) )
#define RCC_APB1LP_PERI_TIM7LPEN		(defined_uint64_t) ( (RCC_APB1LPENR_MASK) | ( (defined_uint64_t) BIT_5 ) )
#define RCC_APB1LP_PERI_TIM6LPEN		(defined_uint64_t) ( (RCC_APB1LPENR_MASK) | ( (defined_uint64_t) BIT_4 ) )
#define RCC_APB1LP_PERI_TIM5LPEN		(defined_uint64_t) ( (RCC_APB1LPENR_MASK) | ( (defined_uint64_t) BIT_3 ) )
#define RCC_APB1LP_PERI_TIM4LPEN		(defined_uint64_t) ( (RCC_APB1LPENR_MASK) | ( (defined_uint64_t) BIT_2 ) )
#define RCC_APB1LP_PERI_TIM3LPEN		(defined_uint64_t) ( (RCC_APB1LPENR_MASK) | ( (defined_uint64_t) BIT_1 ) )
#define RCC_APB1LP_PERI_TIM2LPEN		(defined_uint64_t) ( (RCC_APB1LPENR_MASK) | ( (defined_uint64_t) BIT_0 ) )
#define RCC_APB1LP_PERI_SPI3LPEN		(defined_uint64_t) ( (RCC_APB1LPENR_MASK) | ( (defined_uint64_t) BIT_14) )
#define RCC_APB1LP_PERI_SPI2LPEN		(defined_uint64_t) ( (RCC_APB1LPENR_MASK) | ( (defined_uint64_t) BIT_13) )
#define RCC_APB1LP_PERI_Reserved		(defined_uint64_t) ( (RCC_APB1LPENR_MASK) | ( (defined_uint64_t) BIT_12) )
#define RCC_APB1LP_PERI_WWDGLPEN		(defined_uint64_t) ( (RCC_APB1LPENR_MASK) | ( (defined_uint64_t) BIT_11) )
#define RCC_APB1LP_PERI_I2C3LPEN		(defined_uint64_t) ( (RCC_APB1LPENR_MASK) | ( (defined_uint64_t) BIT_23) )
#define RCC_APB1LP_PERI_I2C2LPEN		(defined_uint64_t) ( (RCC_APB1LPENR_MASK) | ( (defined_uint64_t) BIT_22) )
#define RCC_APB1LP_PERI_I2C1LPEN		(defined_uint64_t) ( (RCC_APB1LPENR_MASK) | ( (defined_uint64_t) BIT_21) )
#define RCC_APB1LP_PERI_UART5LPEN		(defined_uint64_t) ( (RCC_APB1LPENR_MASK) | ( (defined_uint64_t) BIT_20) )
#define RCC_APB1LP_PERI_UART4LPEN		(defined_uint64_t) ( (RCC_APB1LPENR_MASK) | ( (defined_uint64_t) BIT_19) )
#define RCC_APB1LP_PERI_USART3LPEN		(defined_uint64_t) ( (RCC_APB1LPENR_MASK) | ( (defined_uint64_t) BIT_18) )
#define RCC_APB1LP_PERI_USART2LPEN		(defined_uint64_t) ( (RCC_APB1LPENR_MASK) | ( (defined_uint64_t) BIT_17) )
#define RCC_APB1LP_PERI_CAN2LPEN		(defined_uint64_t) ( (RCC_APB1LPENR_MASK) | ( (defined_uint64_t) BIT_26) )
#define RCC_APB1LP_PERI_CAN1LPEN		(defined_uint64_t) ( (RCC_APB1LPENR_MASK) | ( (defined_uint64_t) BIT_25) )
#define RCC_APB1LP_PERI_DACLPEN			(defined_uint64_t) ( (RCC_APB1LPENR_MASK) | ( (defined_uint64_t) BIT_29) )
#define RCC_APB1LP_PERI_PWRLPEN			(defined_uint64_t) ( (RCC_APB1LPENR_MASK) | ( (defined_uint64_t) BIT_28) )
/*=================================================================================================*/

/*******************************************APB2LPENR**********************************************/

#define RCC_APB2LP_PERI_TIM11LPEN     (defined_uint64_t) ( (RCC_APB2LPENR_MASK) | ( (defined_uint64_t)BIT_18) )
#define RCC_APB2LP_PERI_TIM10LPEN     (defined_uint64_t) ( (RCC_APB2LPENR_MASK) | ( (defined_uint64_t)BIT_17) )
#define RCC_APB2LP_PERI_TIM9LPEN      (defined_uint64_t) ( (RCC_APB2LPENR_MASK) | ( (defined_uint64_t)BIT_16) )
#define RCC_APB2LP_PERI_SYSCFGLPEN    (defined_uint64_t) ( (RCC_APB2LPENR_MASK) | ( (defined_uint64_t)BIT_14) )
#define RCC_APB2LP_PERI_SPI1LPEN      (defined_uint64_t) ( (RCC_APB2LPENR_MASK) | ( (defined_uint64_t)BIT_12) )
#define RCC_APB2LP_PERI_SDIOLPEN      (defined_uint64_t) ( (RCC_APB2LPENR_MASK) | ( (defined_uint64_t)BIT_11) )
#define RCC_APB2LP_PERI_ADC3LPEN      (defined_uint64_t) ( (RCC_APB2LPENR_MASK) | ( (defined_uint64_t)BIT_10) )
#define RCC_APB2LP_PERI_ADC2LPEN      (defined_uint64_t) ( (RCC_APB2LPENR_MASK) | ( (defined_uint64_t)BIT_9 ) )
#define RCC_APB2LP_PERI_ADC1LPEN      (defined_uint64_t) ( (RCC_APB2LPENR_MASK) | ( (defined_uint64_t)BIT_8 ) )
#define RCC_APB2LP_PERI_USART6LPEN    (defined_uint64_t) ( (RCC_APB2LPENR_MASK) | ( (defined_uint64_t)BIT_5 ) )
#define RCC_APB2LP_PERI_USART1LPEN    (defined_uint64_t) ( (RCC_APB2LPENR_MASK) | ( (defined_uint64_t)BIT_4 ) )
#define RCC_APB2LP_PERI_TIM8LPEN      (defined_uint64_t) ( (RCC_APB2LPENR_MASK) | ( (defined_uint64_t)BIT_1 ) )
#define RCC_APB2LP_PERI_TIM1LPEN      (defined_uint64_t) ( (RCC_APB2LPENR_MASK) | ( (defined_uint64_t)BIT_0 ) )
/*================================================================================================*/

/*======================RCC_PLLCFGR======================*/
#define RCC_PLLCFGR_PLLM 			(BIT_0|BIT_1|BIT_2|BIT_3|BIT_4|BIT_5)
#define RCC_PLLCFGR_PLLN			(BIT_6|BIT_7|BIT_8|BIT_9|BIT_10|BIT_11|BIT_12|BIT_13|BIT_14)
#define RCC_PLLCFGR_PLLP			(BIT_16|BIT_17)
#define RCC_PLLCFGR_PLLSRC  		(BIT_22)
#define RCC_PLLCFGR_PLLQ			(BIT_24|BIT_25|BIT_26|BIT_27)
/*========================================================*/

/*===========ERROR_CODES===========*/
#define FAILURE 0
#define SUCCESS 1
/*===============================================*/

extern defined_uint32_t pll_clk;

/*=============SYSCLK_SWS_STATES=============*/
#define SYSCLK_SWS_HSI	0
#define SYSCLK_SWS_HSE  1
#define SYSCLK_SWS_PLL  2
#define PLL_SRC_HSI 0
#define PLL_SRC_HSE 1
#define HSI_CLK 16000000
#define HSE_CLK 8000000
/*===============================================*/


/*=============ENABLE_DISABLE_STATES=============*/
#define ENABLE  1
#define DISABLE 0
/*===============================================*/

typedef struct
{
	defined_uint32_t pll_m;
	defined_uint32_t pll_n;
	defined_uint32_t pll_p;
	defined_uint32_t pll_q;
	defined_uint32_t pll_src;
}RCC_PLL_configration;


defined_uint8_t Enable_RCC_CR_clk(defined_uint32_t RCC_CR_clkOn);

defined_uint8_t Disable_RCC_CR_clk(defined_uint32_t RCC_CR_clkClear);

defined_uint8_t Select_SysClk_RCC_CFGR_SW(defined_uint32_t SYSCLK_SWS_clk);

defined_uint8_t Configure_RCC_PLLCFGR(RCC_PLL_configration pll);

defined_uint8_t get_current_sysclk_frequency(defined_uint32_t * sysclk_frequency);

defined_uint8_t Set_RCC_CFGR_HPRE(defined_uint64_t RCC_CFGR_HPRE_DIV_number);

defined_uint32_t Get_RCC_AHB_Freq();

defined_uint8_t Set_RCC_CFGR_PPRE1(defined_uint64_t RCC_CFGR_PPRE1_DIV_number);

defined_uint8_t Set_RCC_CFGR_PPRE2(defined_uint64_t RCC_CFGR_PPRE2_DIV_number);

defined_uint8_t Set_RCC_CFGR_MCO1_clk(defined_uint64_t RCC_CFGR_MCO1_clk);

defined_uint8_t Set_RCC_CFGR_MCO2_clk(defined_uint64_t RCC_CFGR_MCO2_clk);

defined_uint8_t Set_RCC_CFGR_MCO1PRE(defined_uint64_t RCC_CFGR_MCO1PRE_DIV_number);

defined_uint8_t Set_RCC_CFGR_MCO2PRE(defined_uint64_t RCC_CFGR_MCO2PRE_DIV_number);

defined_uint8_t Enable_RCC_AHB1_PERI(defined_uint64_t RCC_AHB1_PERI_name);

defined_uint8_t Enable_RCC_AHB2_PERI(defined_uint64_t RCC_AHB2_PERI_name);

defined_uint8_t Enable_RCC_AHB3_PERI(defined_uint64_t RCC_AHB3_PERI_name);

defined_uint8_t Enable_RCC_APB1_PERI(defined_uint64_t RCC_APB1_PERI_name);

defined_uint8_t Enable_RCC_APB2_PERI(defined_uint64_t RCC_APB2_PERI_name);

defined_uint8_t Enable_RCC_AHB1LP_PERI(defined_uint64_t RCC_AHB1LP_PERI_name);

defined_uint8_t Enable_RCC_AHB2LP_PERI(defined_uint64_t RCC_AHB2LP_PERI_name);

defined_uint8_t Enable_RCC_AHB3LP_PERI(defined_uint64_t RCC_AHB3LP_PERI_name);

defined_uint8_t Enable_RCC_APB1LP_PERI(defined_uint64_t RCC_APB1LP_PERI_name);

defined_uint8_t Enable_RCC_APB2LP_PERI(defined_uint64_t RCC_APB2LP_PERI_name);

defined_uint8_t Disable_RCC_AHB1_PERI(defined_uint64_t RCC_AHB1_PERI_name);

defined_uint8_t Disable_RCC_AHB2_PERI(defined_uint64_t RCC_AHB2_PERI_name);

defined_uint8_t Disable_RCC_AHB3_PERI(defined_uint64_t RCC_AHB3_PERI_name);

defined_uint8_t Disable_RCC_APB1_PERI(defined_uint64_t RCC_APB1_PERI_name);

defined_uint8_t Disable_RCC_APB2_PERI(defined_uint64_t RCC_APB2_PERI_name);

defined_uint8_t Disable_RCC_AHB1LP_PERI(defined_uint64_t RCC_AHB1LP_PERI_name);

defined_uint8_t Disable_RCC_AHB2LP_PERI(defined_uint64_t RCC_AHB2LP_PERI_name);

defined_uint8_t Disable_RCC_AHB3LP_PERI(defined_uint64_t RCC_AHB3LP_PERI_name);

defined_uint8_t Disable_RCC_APB1LP_PERI(defined_uint64_t RCC_APB1LP_PERI_name);

defined_uint8_t Disable_RCC_APB2LP_PERI(defined_uint64_t RCC_APB2LP_PERI_name);

#endif /* RCC_INT_H_ */
