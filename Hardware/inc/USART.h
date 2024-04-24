#ifndef USART_H_
#define USART_H_

#include "string.h"

#define RX_MAX_SIZE 1024
#define TX_SIZE 3073
#define RX_SIZE 3072

extern uint8_t TXBUFF [1];  // 定义一个数组来保存要发送的数据
extern uint8_t RXBUFF [RX_SIZE];  // 定义一个数组来保存接收到的数据

typedef struct
{
	uint8_t *start;
	uint8_t *end;
	
}LCB;

typedef struct
{
	uint32_t RX_Count;  // 接收到的数据的数量
	uint32_t TX_Count;  // 发送的数据的数量

	uint8_t  TXState;   // UART 的发送状态

	LCB      RXLocation[10];  // 接收数据缓冲区的位置信息
	LCB      TXLocation[10];  // 发送数据缓冲区的位置信息

	LCB      *RxInPtr;  // 指向接收数据缓冲区的输入指针
	LCB      *RxOutPtr;  // 指向接收数据缓冲区的输出指针
	LCB      *RxEndPtr;  // 指向接收数据缓冲区的结束指针

	LCB      *TxInPtr;  // 指向发送数据缓冲区的输入指针
	LCB      *TxOutPtr;  // 指向发送数据缓冲区的输出指针
	LCB      *TxEndtr;  // 指向发送数据缓冲区的结束指针
	UART_HandleTypeDef uart;  // UART 的句柄
}UCB;

extern UCB uart1;

void USART_Init(uint32_t bandrate);
void USART_TXData(UCB *uartb,uint8_t *data,uint32_t data_len);
extern UCB uart1;
#endif
