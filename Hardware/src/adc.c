#include "adc.h"
#include "stm32f1xx_hal_adc.h"

ADC_HandleTypeDef adc1;
ADC_ChannelConfTypeDef adc1_0;


void ADC1_Init(void)
{
    

    adc1.Instance                   = ADC1;
    adc1.Init.ContinuousConvMode    = ENABLE;//连续扫描模式
    adc1.Init.DataAlign             = ADC_DATAALIGN_RIGHT;//对齐方式
    //adc1.Init.DiscontinuousConvMode = ;//规则组间断模式
    adc1.Init.ExternalTrigConv      = ADC_SOFTWARE_START;//规则组外部触发
    //adc1.Init.NbrOfConversion       = ;//扫描模式下规则组通道数量
    //adc1.Init.NbrOfDiscConversion   = ;//规则组间断模式下每次间断的通道数
    adc1.Init.ScanConvMode          = ADC_SCAN_DISABLE;//扫描方式

    HAL_ADC_Init(&adc1);

    adc1_0.Channel=ADC_CHANNEL_0;
    adc1_0.Rank=ADC_REGULAR_RANK_1;
    adc1_0.SamplingTime=ADC_SAMPLETIME_41CYCLES_5;

    HAL_ADC_ConfigChannel(&adc1,&adc1_0);

    HAL_ADCEx_Calibration_Start(&adc1);//自校准
}

void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc)
{
    if (hadc->Instance == ADC1) {
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_ADC1_CLK_ENABLE();

        GPIO_InitTypeDef GPIO_Init;

        GPIO_Init.Pin   = GPIO_PIN_0;
        GPIO_Init.Mode  = GPIO_MODE_ANALOG;
        GPIO_Init.Speed = GPIO_SPEED_HIGH;

        HAL_GPIO_Init(GPIOA, &GPIO_Init);

        HAL_NVIC_SetPriority(ADC1_2_IRQn,3,0);
        HAL_NVIC_EnableIRQ(ADC1_2_IRQn);
    }
}
