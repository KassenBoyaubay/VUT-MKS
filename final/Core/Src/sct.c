/*
 * sct.c
 *
 *  Created on: 11. 10. 2022
 *      Author: 246477
 */
#include <stdint.h>
#include <stdbool.h>
#include "main.h"
#include "sct.h"

static const uint32_t reg_values[4][10] = {
	{
	//PCDE--------GFAB @ DIS1
	0b0111000000000111 << 16,
	0b0100000000000001 << 16,
	0b0011000000001011 << 16,
	0b0110000000001011 << 16,
	0b0100000000001101 << 16,
	0b0110000000001110 << 16,
	0b0111000000001110 << 16,
	0b0100000000000011 << 16,
	0b0111000000001111 << 16,
	0b0110000000001111 << 16,
	},
	{
	//----PCDEGFAB---- @ DIS2
	0b0000011101110000 << 0,
	0b0000010000010000 << 0,
	0b0000001110110000 << 0,
	0b0000011010110000 << 0,
	0b0000010011010000 << 0,
	0b0000011011100000 << 0,
	0b0000011111100000 << 0,
	0b0000010000110000 << 0,
	0b0000011111110000 << 0,
	0b0000011011110000 << 0,
	},
	{
	//PCDE--------GFAB @ DIS3
	0b0111000000000111 << 0,
	0b0100000000000001 << 0,
	0b0011000000001011 << 0,
	0b0110000000001011 << 0,
	0b0100000000001101 << 0,
	0b0110000000001110 << 0,
	0b0111000000001110 << 0,
	0b0100000000000011 << 0,
	0b0111000000001111 << 0,
	0b0110000000001111 << 0,
	},
	{
	//----43215678---- @ LED
	0b0000000100000000 << 16,
	0b0000001100000000 << 16,
	0b0000011100000000 << 16,
	0b0000111000000000 << 16,
	0b0000110010000000 << 16,
	0b0000100011000000 << 16,
	0b0000000011100000 << 16,
	0b0000000001110000 << 16,
	0b0000000000110000 << 16,
	0b0000000000010000 << 16,
	}
};

void sct_init(void) {
	sct_led(0);
}

void sct_led(uint32_t value) {
	for (uint8_t i = 0; i < 32; i++) {
		HAL_GPIO_WritePin(SCT_SDI_GPIO_Port, SCT_SDI_Pin, value & 1);
	    value >>= 1;
	    HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_CLK_Pin, 1);
	    HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_CLK_Pin, 0);
    }
	HAL_GPIO_WritePin(SCT_NLA_GPIO_Port, SCT_NLA_Pin, 1);
	HAL_GPIO_WritePin(SCT_NLA_GPIO_Port, SCT_NLA_Pin, 0);
}

void sct_value(uint16_t value) {
	uint32_t reg = 0;
	static uint32_t delay = 0;
	static uint8_t led = 0;									// value of led positions, 10 in total
	static bool right = true;								// direction; 1 - right, 0 - left

	reg |= reg_values[0][value / 100 % 10]; 				// first digit
	reg |= reg_values[1][value / 10 % 10];  				// second digit
	reg |= reg_values[2][value / 1 % 10];   				// third digit
	reg |= reg_values[3][led];								// led3 - led10

	if (HAL_GetTick() > delay + value) {					// non-blocked waiting
			  delay = HAL_GetTick();
			  led = (right == true) ? led + 1 : led - 1;	// next state of leds depending on direction
			  if (led == 9) {								// reaches last led => direction becomes left
				  right = false;
			  } else if (led == 0) {						// reaches first led => direction becomes right
				  right = true;
			  }
	}

	sct_led(reg);
}

