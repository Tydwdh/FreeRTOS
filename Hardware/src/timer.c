#include "stm32f1xx_hal.h"
#include "time.h"

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_OC_InitTypeDef htim2_ch1_config;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

DMA_HandleTypeDef tim1_dma;

void Timer1_Init(uint16_t arr,uint16_t psc,uint8_t rep)
{
    htim1.Instance=TIM1;
    
    htim1.Init.Period=arr-1;
    htim1.Init.Prescaler=psc-1;
    htim1.Init.CounterMode=TIM_COUNTERMODE_UP;
    htim1.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//信号防干扰
    htim1.Init.RepetitionCounter=rep;
    htim1.Init.AutoReloadPreload=TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_Base_Init(&htim1);
    __HAL_TIM_CLEAR_FLAG(&htim1,TIM_FLAG_UPDATE);
}
void Timer2_Init(uint16_t arr,uint16_t psc)
{
    htim2.Instance=TIM2;
    
    htim2.Init.Period=arr-1;
    htim2.Init.Prescaler=psc-1;
    htim2.Init.CounterMode=TIM_COUNTERMODE_UP;
    htim2.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//信号防干扰
    htim2.Init.AutoReloadPreload=TIM_AUTORELOAD_PRELOAD_ENABLE;

    HAL_TIM_PWM_Init(&htim2);
    __HAL_TIM_CLEAR_FLAG(&htim2,TIM_FLAG_UPDATE);

    htim2_ch1_config.OCMode=TIM_OCMODE_PWM1;
    htim2_ch1_config.Pulse=500;
    htim2_ch1_config.OCPolarity=TIM_OCPOLARITY_HIGH;
    htim2_ch1_config.OCFastMode=TIM_OCFAST_DISABLE;

    HAL_TIM_PWM_ConfigChannel(&htim2,&htim2_ch1_config,TIM_CHANNEL_1);
    //HAL_TIM_Base_Init(&htim2);
    
}
void Timer3_Init(uint16_t arr,uint16_t psc)
{
    htim3.Instance=TIM3;
    
    htim3.Init.Period=arr-1;
    htim3.Init.Prescaler=psc-1;
    htim3.Init.CounterMode=TIM_COUNTERMODE_UP;
    htim3.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//信号防干扰
    htim3.Init.AutoReloadPreload=TIM_AUTORELOAD_PRELOAD_ENABLE;

    HAL_TIM_Base_Init(&htim3);

    __HAL_TIM_CLEAR_FLAG(&htim3,TIM_FLAG_UPDATE);
}
void Timer4_Init(uint16_t arr,uint16_t psc)
{
    htim4.Instance=TIM4;
    
    htim4.Init.Period=arr-1;
    htim4.Init.Prescaler=psc-1;
    htim4.Init.CounterMode=TIM_COUNTERMODE_UP;
    htim4.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//信号防干扰
    htim4.Init.AutoReloadPreload=TIM_AUTORELOAD_PRELOAD_ENABLE;

    HAL_TIM_Base_Init(&htim4);

    __HAL_TIM_CLEAR_FLAG(&htim4,TIM_FLAG_UPDATE);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM1)
    {
        __HAL_RCC_TIM1_CLK_ENABLE();
        __HAL_RCC_DMA1_CLK_ENABLE();


        HAL_NVIC_SetPriority(TIM1_UP_IRQn,0,0);
        HAL_NVIC_EnableIRQ(TIM1_UP_IRQn);

        // tim1_dma.Instance=DMA1_Channel5;

        // tim1_dma.Init.Direction=DMA_MEMORY_TO_PERIPH;
        // tim1_dma.Init.PeriphInc=DMA_PINC_DISABLE;
        // tim1_dma.Init.MemInc=DMA_MINC_ENABLE;
        // tim1_dma.Init.PeriphDataAlignment=DMA_PDATAALIGN_HALFWORD;
        // tim1_dma.Init.MemDataAlignment=DMA_MDATAALIGN_HALFWORD;
        // tim1_dma.Init.Mode=DMA_NORMAL;
        // tim1_dma.Init.Priority=DMA_PRIORITY_HIGH;

        // __HAL_LINKDMA(&htim1,hdma[TIM_DMA_ID_UPDATE],tim1_dma);

        // HAL_DMA_Init(&tim1_dma);

        // HAL_NVIC_SetPriority(DMA1_Channel5_IRQn,3,0);
        // HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);
    }else if(htim->Instance==TIM2)
    {
        __HAL_RCC_TIM2_CLK_ENABLE();
    }else if(htim->Instance==TIM3)
    {
        __HAL_RCC_TIM3_CLK_ENABLE();
    }else if(htim->Instance==TIM4)
    {
        __HAL_RCC_TIM4_CLK_ENABLE();
    }
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM2)
    {
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_TIM2_CLK_ENABLE();

        GPIO_InitTypeDef GPIO_Init;
        GPIO_Init.Pin=GPIO_PIN_0;
        GPIO_Init.Mode=GPIO_MODE_AF_PP;
        GPIO_Init.Pull=GPIO_NOPULL;
        GPIO_Init.Speed=GPIO_SPEED_FREQ_MEDIUM;
        HAL_GPIO_Init(GPIOA,&GPIO_Init);

        HAL_NVIC_SetPriority(TIM2_IRQn,3,0);
        HAL_NVIC_EnableIRQ(TIM2_IRQn);
    }
}


void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM1)
    {
        __HAL_RCC_TIM1_CLK_DISABLE();

    }else if(htim->Instance==TIM2)
    {
        __HAL_RCC_TIM2_CLK_DISABLE();
    }else if(htim->Instance==TIM3)
    {
        __HAL_RCC_TIM3_CLK_DISABLE();
    }else if(htim->Instance==TIM4)
    {
        __HAL_RCC_TIM4_CLK_DISABLE();
    }
}

