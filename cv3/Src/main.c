/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include "sct.h"

int main(void)
{
	sct_init();
//	sct_led((uint32_t) 0x7A5C36DE);
	while (1) {
		for (uint16_t value = 0; value <= 999; value += 111) {
			sct_value(value);
			for (volatile uint32_t i = 0; i < 100000; i++) {}
		}
	}
}
