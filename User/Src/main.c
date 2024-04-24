#include "main.h"


int main()
{

    HAL_Init();
    SystemTime_Init();
    OLED_Init();
    // USART_Init(9600);
    Key_Init();
	int a;
	int b;
    FreeRTOS_Init();
	
    while (1)
    {
    }
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
    if (htim->Instance == TIM1)
    {

    } else if (htim->Instance == TIM2)
    {

    } else if (htim->Instance == TIM3)
    {

    } else if (htim->Instance == TIM4)
    {

    }
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef* htim)
{
    if (htim->Instance == TIM2)
    {
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
        {
        }
    }
}
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    if (hadc->Instance == ADC1)
    {
    }
}
