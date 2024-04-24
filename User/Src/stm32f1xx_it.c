#include "stm32f1xx_it.h"
#include "main.h"

void TIM1_UP_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim1);
}

void TIM2_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim2);
}

void USART1_IRQHandler(void)
{
  HAL_UART_IRQHandler(&uart1.uart);
}
void DMA1_Channel6_IRQHandler(void)
{
  HAL_DMA_IRQHandler(hi2c1.hdmatx);
}
void I2C1_EV_IRQHandler(void)
{
  HAL_I2C_EV_IRQHandler(&hi2c1);
}


void ADC1_2_IRQHandler(void)
{
  HAL_ADC_IRQHandler(&adc1);
}
void NMI_Handler(void)
{

  while (1)
  {
  }

}

void HardFault_Handler(void)
{
  while (1)
  {

  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{

  while (1)
  {

  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{

  while (1)
  {

  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{

  while (1)
  {

  }
}

// /**
//   * @brief This function handles System service call via SWI instruction.
//   */
// void SVC_Handler(void)
// {

// }

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{

}

// /**
//   * @brief This function handles Pendable request for system service.
//   */
// void PendSV_Handler(void)
// {

// }


extern void xPortSysTickHandler(void);
/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{

  HAL_IncTick();
#if (INCLUDE_xTaskGetSchedulerState  == 1 )
  if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
  {
#endif/* INCLUDE_xTaskGetSchedulerState */
    xPortSysTickHandler();
#if (INCLUDE_xTaskGetSchedulerState  == 1 )
  }
#endif/* INCLUDE_xTaskGetSchedulerState */

}

