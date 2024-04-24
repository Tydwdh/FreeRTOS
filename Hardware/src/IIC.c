#include "stm32f1xx_hal.h"
#include "IIC.h"

I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;

DMA_HandleTypeDef hdma1;

void IIC1_Init(void)
{
    hi2c1.Instance = I2C1;
    hi2c1.Init.ClockSpeed = 400000;

    HAL_I2C_Init(&hi2c1);
}

void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
    if(hi2c->Instance==I2C1)
    {
        __HAL_RCC_I2C1_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();
        __HAL_RCC_AFIO_CLK_ENABLE();
        __HAL_RCC_DMA1_CLK_ENABLE();
        GPIO_InitTypeDef GPIO_Init;
        GPIO_Init.Pin = GPIO_PIN_8|GPIO_PIN_9;
        GPIO_Init.Mode = GPIO_MODE_AF_OD;
        GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOB,&GPIO_Init);

        __HAL_AFIO_REMAP_I2C1_ENABLE();
        HAL_NVIC_SetPriority(I2C1_EV_IRQn,3,0);
        HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);

        hdma1.Instance=DMA1_Channel6;

        hdma1.Init.Direction=DMA_MEMORY_TO_PERIPH;
        hdma1.Init.Mode=DMA_NORMAL;

        hdma1.Init.MemDataAlignment=DMA_MDATAALIGN_BYTE;
        hdma1.Init.MemInc=DMA_MINC_ENABLE;
        
        hdma1.Init.PeriphDataAlignment=DMA_PDATAALIGN_BYTE;
        hdma1.Init.PeriphInc=DMA_PINC_DISABLE;

        hdma1.Init.Priority=DMA_PRIORITY_HIGH;

        HAL_DMA_Init(&hdma1);

        __HAL_LINKDMA(hi2c,hdmatx,hdma1);

        HAL_NVIC_SetPriority(DMA1_Channel6_IRQn,3,0);
        HAL_NVIC_EnableIRQ(DMA1_Channel6_IRQn);
    }
}

