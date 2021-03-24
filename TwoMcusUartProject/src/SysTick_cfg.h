/*
 * SysTick_cfg.h
 *
 *  Created on: Mar 11, 2021
 *      Author: Esraa Abdelnaby
 */

#ifndef SYSTICK_CFG_H_
#define SYSTICK_CFG_H_

#define STK_CLKSRC_AHB_PRESCALED_8       0
#define STK_CLKSRC_AHB                   1


#define SYSTICK_TICKINT_ENABLE            1
#define SYSTICK_TICKINT_DISABLE           0


#define SYSTICK_CLK_SRC    STK_CLKSRC_AHB
#define SYSTICK_TICKINT    SYSTICK_TICKINT_ENABLE

#endif /* SYSTICK_CFG_H_ */
