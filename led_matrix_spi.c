/*
 * led_matrix_spi.c
 *
 *  Created on: 30 juil. 2022
 *      Author: LECLERCQ Antonin
 */


#include <led_matrix_spi.h>

void LED_Matrix_SPI_Init(const uint8_t scan_limit, const uint8_t intensity, const uint8_t decode_mode, const uint8_t demo)
{
	/*
	 * Using SPI1 peripheral
	 * 		CS --> PA4
	 * 		SPI_MOSI --> PA7 (AF0)
	 * 		SPI_SCK --> PA5 (AF0)
	 *
	 * APB2 peripherals run at 8MHz (internal oscillator of stm32f030)
	 *
	 * Baudrate = fPCLK/64 = 8MHz / 64 = 125KHz
	 */

	// Enable GPIOA clock
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

	// Set PA5 and PA7 to alternate function, PA4 to output
	GPIOA->MODER &= ~(GPIO_MODER_MODER4_Msk | GPIO_MODER_MODER5_Msk | GPIO_MODER_MODER6_Msk);
	GPIOA->MODER |= (0x01 << GPIO_MODER_MODER4_Pos) | (0x02 << GPIO_MODER_MODER5_Pos) | (0x02 << GPIO_MODER_MODER7_Pos);

	// Set PA4 to high speed
	GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEEDR4_Msk;
	GPIOA->OSPEEDR |= (0x03 << GPIO_OSPEEDR_OSPEEDR4_Pos);

	// Idle state is high
	GPIOA->ODR |= GPIO_ODR_4;

	// Set PA5 and PA7 to AF0
	GPIOA->AFR[0] &= ~(GPIO_AFRL_AFRL5_Msk | GPIO_AFRL_AFRL7_Msk);

	// Enable SPI1 clock
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

	// Reset SPI1 configuration
	SPI1->CR1 = 0x0000;
	SPI1->CR2 = 0x0700;

	// Select Baudrate 125kHz --> 8MHZ /64 --> SPI_BR = 5
	SPI1->CR1 &= ~SPI_CR1_BR_Msk;
	SPI1->CR1 |= (0x05 << SPI_CR1_BR_Pos);

	// Microcontroller is Master, software controlled CS
	SPI1->CR1 |= SPI_CR1_MSTR | SPI_CR1_SSI | SPI_CR1_SSM;

	// Set data size to 8 bits
	SPI1->CR2 &= ~SPI_CR2_DS_Msk;
	SPI1->CR2 |= (0x07 << SPI_CR2_DS_Pos);

	// Enable SPI1
	SPI1->CR1 |= SPI_CR1_SPE;

	if(demo)
	{
		// Test demo
		LED_Matrix_SPI_Write(DISPLAY_TEST, 0x01);

		delay_ms(1500);

		// Exit Test demo
		LED_Matrix_SPI_Write(DISPLAY_TEST, 0x00);


	}

	delay_ms(10);

	// Display all 0 to scan_limit
	LED_Matrix_SPI_Write(SCAN_LIMIT, scan_limit);

	delay_ms(10);

	// Set display intensity
	LED_Matrix_SPI_Write(INTENSITY, intensity);

	delay_ms(10);

	// No decode (displays whatever data it's sent)
	LED_Matrix_SPI_Write(DECODE_MODE, decode_mode);

	delay_ms(10);

	// Begin normal operation
	LED_Matrix_SPI_Write(SHUTDOWN, 0x01);

	delay_ms(10);
}

void LED_Matrix_SPI_Write(const uint8_t register_address, const uint8_t data)
{
	// Set FIFO threshold to 1-byte
	SPI1->CR2 |= SPI_CR2_FRXTH;

	// Select slave (through pin PA4)
	GPIOA->ODR &= ~GPIO_ODR_4;

	// Send address  (function defined in led_matrix_spi.h)
	LED_Matrix_SPI_SendReceive(register_address);
	// Then send data
	LED_Matrix_SPI_SendReceive(data);

	// Release slave
	GPIOA->ODR |= GPIO_ODR_4;
}
