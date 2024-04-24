#ifndef __TIME_H
#define __TIME_H

#include "stm32f1xx_hal.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim2;
void Timer1_Init(uint16_t arr,uint16_t psc,uint8_t rep);
void Timer2_Init(uint16_t arr,uint16_t psc);
void Timer3_Init(uint16_t arr,uint16_t psc);
void Timer4_Init(uint16_t arr,uint16_t psc);

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *htim);
#endif
