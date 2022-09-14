/*
 * delay.h
 *
 *  Created on: 11 sept. 2022
 *      Author: LECLERCQ Antonin
 */

#ifndef BSP_INC_DELAY_H_
#define BSP_INC_DELAY_H_

#include <stm32f0xx.h>

void TIMER6_init(void);

void delay_ms(const uint32_t ms);

#endif /* BSP_INC_DELAY_H_ */
