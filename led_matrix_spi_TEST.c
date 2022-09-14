/*
 * main.c
 *
 *  Created on: 30 juil. 2022
 *      Author: LECLERCQ Antonin
 */

#include "led_matrix_spi.h"
#include "delay.h"

int main(void)
{
	// For delay function
	TIMER6_init();

	// scan_limit = 3, intensity = 0 (lowest), decode_mode = 0 (no decode), begin with demo
	LED_Matrix_SPI_Init(0x03, 0x00, 0x00, 0x01);

	delay_ms(1000);

	const uint8_t reg[3][4] = {
			{ 0x01, 0x02, 0x03, 0x04 },
			{ 170, 85, 170, 85 },
			{ 85, 170, 85, 170 }
	};

	while(1)
	{
		for(uint8_t i = 0; i < 4; i++)
		{
			LED_Matrix_SPI_Write(reg[0][i], reg[1][i]);
		}
		delay_ms(500);
    
		for(uint8_t i = 0; i < 4; i++)
		{
			LED_Matrix_SPI_Write(reg[0][i], reg[2][i]);
		}
		delay_ms(500);
	}

	return 0;
}
