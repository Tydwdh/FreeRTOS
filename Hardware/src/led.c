#include "stm32f1xx_hal.h"
#include "led.h"

void LED_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
	
	GPIO_InitTypeDef GPIO_Init;
	GPIO_Init.Pin=GPIO_PIN_0;
	GPIO_Init.Mode=GPIO_MODE_OUTPUT_PP;
	GPIO_Init.Pull=GPIO_NOPULL;
	GPIO_Init.Speed=GPIO_SPEED_FREQ_HIGH;
	
	
	HAL_GPIO_Init(GPIOA,&GPIO_Init);
	
}

