
#include "RCC.h"

void SystemTime_Init(void)
{
	__HAL_RCC_GPIOC_CLK_ENABLE();

	RCC_OscInitTypeDef  RCC_OscInitStruct;
	
	RCC_OscInitStruct.HSEPredivValue=RCC_HSE_PREDIV_DIV1;
	RCC_OscInitStruct.OscillatorType=RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState=RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLMUL=RCC_PLL_MUL9;
	RCC_OscInitStruct.PLL.PLLSource=RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLState=RCC_PLL_ON;
	
	RCC_ClkInitTypeDef  RCC_ClkInitStruct;
	RCC_ClkInitStruct.AHBCLKDivider=RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider=RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider=RCC_HCLK_DIV1;
	RCC_ClkInitStruct.ClockType=RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource=RCC_SYSCLKSOURCE_PLLCLK;

	// RCC_PeriphCLKInitTypeDef PeriphClkInit;
	// PeriphClkInit.PeriphClockSelection=RCC_PERIPHCLK_RTC;
	// PeriphClkInit.RTCClockSelection=RCC_RTCCLKSOURCE_LSI;
	
	HAL_RCC_OscConfig(&RCC_OscInitStruct);
	
	HAL_RCC_ClockConfig(&RCC_ClkInitStruct,FLASH_LATENCY_2);

	//HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);
}
