#ifndef W25Q64_H
#define W25Q64_H

#include "stm32f1xx_hal.h"

#define CS_ENABLE   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)
#define CS_DISABLE   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET)

void W25Q64_Init(void);

void W25Q64_Busy(void);

void W25Q64_WriteEnable(void);

void W25Q64_EraseSector(uint32_t sectornum);

void W25Q64_WritePage(uint8_t *data, uint32_t pagenum);

void W25Q64_ReadData(uint8_t *data, uint32_t addr, uint16_t len);

#endif // !W25Q64_H


