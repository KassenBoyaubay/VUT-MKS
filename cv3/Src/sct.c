/*
 * sct.c
 *
 *  Created on: 11. 10. 2022
 *      Author: 246477
 */
#include "stm32f0xx.h"
#include "sct.h"

void sct_init(void) {
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	GPIOB->MODER |= GPIO_MODER_MODER5_0;
	GPIOB->MODER |= GPIO_MODER_MODER10_0;
	GPIOB->MODER |= GPIO_MODER_MODER3_0;
	GPIOB->MODER |= GPIO_MODER_MODER4_0;
	sct_led(0);
	sct_noe(0);
}

void sct_led(uint32_t value) {
	for (uint8_t i = 0; i < 32; i++) {
	    sct_sdi(value & 1);
	    value >>= 1;
	    sct_clk(1);
	    sct_clk(0);
    }
    sct_nla(1);
    sct_nla(0);
}

