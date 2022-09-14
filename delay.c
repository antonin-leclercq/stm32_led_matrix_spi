/*
 * delay.c
 *
 *  Created on: 11 sept. 2022
 *      Author: LECLERCQ Antonin
 */


#include <delay.h>

void TIMER6_init(void)
{
	/*
	 * APB1 peripherals run at 8MHz
	 * 1kHz counter frequency --> 1ms resolution
	 * --> PSC = 8MHz / 1kHz = 8000;
	 */

	// Enable TIM6 clock
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;

	// Reset TIM6 configuration
	TIM6->CR1 = 0x0000;
	TIM6->CR2 = 0x0000;

	// Set pre-scaler value and ARR (0xFFFF is default)
	TIM6->PSC = (uint16_t)8000 -1;
	TIM6->ARR = (uint16_t)0xFFFF;

	// Make sure that counter is disabled
	TIM6->CR1 &= ~TIM_CR1_CEN;
}

void delay_ms(const uint32_t ms)
{
	// Update registers
	TIM6->EGR |= TIM_EGR_UG;

	// Start counter
	TIM6->CR1 |= TIM_CR1_CEN;

	// Actual delay loop
	while(TIM6->CNT < ms);

	// Disable counter
	TIM6->CR1 &= ~TIM_CR1_CEN;
}
