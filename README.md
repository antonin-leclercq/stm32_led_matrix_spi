# stm32_led_matrix_spi
This is a basic program which allows the STM32F030 MCU to drive MAX7219 based LED-matrices <br>
It uses the SPI protocol, with software controlled Chip-Select (pin PA4 here, but you can use any GPIO)

The pin connection is the following (again, CS can be any GPIO and you can choose any SPI peripheral if your MCU has several)

| MAX7219 based module | STM32F030       |
|----------------------|-----------------|
| VCC                  | VCC (3.3 or 5V) |
| GND                  | GND             |
| DIN (or MOSI)        | PA7             |
| CS                   | PA4             |
| CLK                  | PA5             |
