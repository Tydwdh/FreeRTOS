#include "stm32f1xx_hal.h"
#include "USART.h"



UCB uart1;  // 定义一个 UCB 结构体的实例
UART_HandleTypeDef uart;  // 定义一个 UART 的句柄

uint8_t TXBUFF [1];  // 定义一个数组来保存要发送的数据
uint8_t RXBUFF [RX_SIZE];  // 定义一个数组来保存接收到的数据

// 初始化 UART 的状态和数据缓冲区的信息
void USART_PTR_Init(UCB *uartb)
{
	uartb->RxInPtr = &uartb->RXLocation[0];
	uartb->RxOutPtr =&uartb->RXLocation[0];
	uartb->RxEndPtr =&uartb->RXLocation[9];
	uartb->RX_Count=0;
	uartb->RxInPtr->start = RXBUFF;
	uartb->TxInPtr = &uartb->TXLocation[0];
	uartb->TxOutPtr =&uartb->TXLocation[0];
	uartb->TxEndtr =&uartb->TXLocation[9];
	uartb->TX_Count=0;
	uartb->TxInPtr->start = TXBUFF;
	
	HAL_UARTEx_ReceiveToIdle_IT(&uartb->uart,uartb->RxInPtr->start,RX_MAX_SIZE);  // 启动 UART 的中断接收

}


// 初始化 UART
void USART_Init(uint32_t bandrate)
{
	uart1.uart.Instance=USART1;
	uart1.uart.Init.BaudRate=bandrate;
	uart1.uart.Init.WordLength=UART_WORDLENGTH_8B;
	uart1.uart.Init.StopBits=UART_STOPBITS_1;
	uart1.uart.Init.Parity=UART_PARITY_NONE;
	uart1.uart.Init.Mode=UART_MODE_TX_RX;
	uart1.uart.Init.HwFlowCtl=UART_HWCONTROL_NONE;
	uart1.uart.Init.OverSampling=UART_OVERSAMPLING_16;
	
	HAL_UART_Init(&uart1.uart);  // 初始化 UART
	
	USART_PTR_Init(&uart1);  // 初始化 UART 的状态和数据缓冲区的信息
}

// 初始化 UART 的硬件资源
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	if(huart->Instance==USART1)
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();  // 启用 GPIOA 的时钟
		__HAL_RCC_USART1_CLK_ENABLE();  // 启用 USART1 的时钟
		GPIO_InitTypeDef GPIO_InitStruct;  // 定义一个 GPIO 的初始化结构体
			
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9|GPIO_PIN_10,GPIO_PIN_SET);  // 设置 GPIOA 的 9 和 10 引脚为高电平
		GPIO_InitStruct.Mode=GPIO_MODE_AF_PP;  // 设置 GPIO 的模式为复用推挽输出
		GPIO_InitStruct.Pin=GPIO_PIN_9;  // 设置 GPIO 的引脚为 9
		GPIO_InitStruct.Pull=GPIO_NOPULL;  // 设置 GPIO 的上拉/下拉模式为无上拉/下拉
		GPIO_InitStruct.Speed=GPIO_SPEED_FREQ_HIGH;  // 设置 GPIO 的速度为高速
		
		HAL_GPIO_Init(GPIOA,&GPIO_InitStruct);  // 初始化 GPIOA 的 9 引脚
			
		GPIO_InitStruct.Mode=GPIO_MODE_INPUT;  // 设置 GPIO 的模式为复用输入
		GPIO_InitStruct.Pull=GPIO_PULLUP;  // 设置 GPIO 的上拉/下拉模式为上拉
		GPIO_InitStruct.Pin=GPIO_PIN_10;  // 设置 GPIO 的引脚为 10
			
		HAL_GPIO_Init(GPIOA,&GPIO_InitStruct);  // 初始化 GPIOA 的 10 引脚
		
		HAL_NVIC_SetPriority(USART1_IRQn,0,0);  // 设置 USART1 中断的优先级
		HAL_NVIC_EnableIRQ(USART1_IRQn);  // 启用 USART1 的中断
	}
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance==USART1)
	{
		uart1.RX_Count+=RX_MAX_SIZE;  // 记录接收到的数据的个数
		uart1.RxInPtr->end =&RXBUFF[uart1.RX_Count-1];  // 记录接收到的数据的结束位置
		if(++uart1.RxInPtr>=uart1.RxEndPtr)
		{
			uart1.RxInPtr=uart1.RXLocation;  // 重置接收数据缓冲区的指针
		}
		if(uart1.RxInPtr->end==&RXBUFF[RX_SIZE])
		{
			uart1.RxInPtr->start=RXBUFF;  // 重置接收数据缓冲区的指针
			uart1.RX_Count=0;  // 重置接收到的数据的个数
		}
		
		uart1.RxInPtr->start = &RXBUFF[uart1.RX_Count];  // 重置接收数据缓冲区的指针
		HAL_UART_Receive_IT(&uart1.uart,uart1.RxInPtr->start,RX_MAX_SIZE);  // 启动 UART 的中断接收
	}
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if(huart->Instance==USART1)
	{
		uart1.RX_Count+=Size;  // 记录接收到的数据的个数
		uart1.RxInPtr->end =&RXBUFF[uart1.RX_Count-1];  // 记录接收到的数据的结束位置
		if(++uart1.RxInPtr>=uart1.RxEndPtr)
		{
			uart1.RxInPtr=uart1.RXLocation;  // 重置接收数据缓冲区的指针
		}
		if(RX_MAX_SIZE-uart1.RX_Count<RX_MAX_SIZE)
		{
			uart1.RxInPtr->start=RXBUFF;  // 重置接收数据缓冲区的指针
			uart1.RX_Count=0;  // 重置接收到的数据的个数
		}
		
		uart1.RxInPtr->start = &RXBUFF[uart1.RX_Count];  // 重置接收数据缓冲区的指针
		HAL_UARTEx_ReceiveToIdle_IT(&uart1.uart,uart1.RxInPtr->start,RX_MAX_SIZE);  // 启动 UART 的中断接收
	}
}



















