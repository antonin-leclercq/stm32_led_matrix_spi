/*
 * led_matrix_spi.h
 *
 *  Created on: 30 juil. 2022
 *      Author: LECLERCQ Antonin
 */

#ifndef BSP_INC_LED_MATRIX_SPI_H_
#define BSP_INC_LED_MATRIX_SPI_H_

#include "stm32f0xx.h"
#include "delay.h"

// MAX7219 register addresses
#define DECODE_MODE 0x09
#define SHUTDOWN 0x0C
#define INTENSITY 0x0A
#define DISPLAY_TEST 0x0F
#define SCAN_LIMIT 0x0B

void LED_Matrix_SPI_Init(
		const uint8_t scan_limit, const uint8_t intensit, const uint8_t decode_mode, const uint8_t demo);

void LED_Matrix_SPI_Write(const uint8_t register_address, const uint8_t data);

static inline uint8_t LED_Matrix_SPI_SendReceive(const uint8_t tx_byte)
{
	uint8_t rx_byte = 0;

	// Wait until TX is ready
	while((SPI1->SR & SPI_SR_TXE) != SPI_SR_TXE);

	// Send tx_byte
	*(volatile uint8_t*)&SPI1->DR = tx_byte;

	// Wait until RX has received everything
	while((SPI1->SR & SPI_SR_RXNE) != SPI_SR_RXNE);

	// Copy received byte
	rx_byte = *(volatile uint8_t*)&SPI1->DR;

	return rx_byte;
}

#endif /* BSP_INC_LED_MATRIX_SPI_H_ */
