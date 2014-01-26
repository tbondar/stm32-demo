/*
 * (C) 2014, Tamas Bondar (www.tamasbondar.info)
 */

#include "stm32f10x.h"


int main(void)
{
	volatile int i;
	GPIO_InitTypeDef  gpio_init;
  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	/* Set GPIOC Pin 6 as output for LED */
	gpio_init.GPIO_Pin = GPIO_Pin_6;
	gpio_init.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &gpio_init);

	while (1)
	{
		/* Busy delay */
		for (i=0; 1 < 1000; i++) {};

		/* LED toggle */
		GPIOC->ODR ^= GPIO_Pin_6;
	}
}
