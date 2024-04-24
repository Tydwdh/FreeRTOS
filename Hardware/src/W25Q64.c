#include "stm32f1xx_hal.h"
#include "W25Q64.h"
#include "SPI.h"
#include "OLED.h"


void W25Q64_Init(void)
{
    SPI1_Init();
    CS_DISABLE;
}

void W25Q64_Busy(void)
{
    uint8_t cmd[2]  = {0x05, 0xff};
    uint8_t data[2]={0,0};
    do {
        CS_ENABLE;
        HAL_SPI_TransmitReceive(&spi1, cmd, data, 2, 1000);
        CS_DISABLE;
    } while(data[1] & 0x01);
}

void W25Q64_WriteEnable(void)
{
    uint8_t cmd = 0x06;
    W25Q64_Busy();
    CS_ENABLE;
    HAL_SPI_Transmit(&spi1, &cmd, 1, 1000);
    CS_DISABLE;
}

/**
 * @brief 擦除一个扇区4k字节
 *
 * @param sectornum 地址等于  sectornum*扇区大小
 */
void W25Q64_EraseSector(uint32_t sectornum)
{
    uint8_t cmd[4] = {0x20, 0x00, 0x00, 0x00};
    cmd[1]         = (sectornum * 4096) >> 16;
    cmd[2]         = (sectornum * 4096) >> 8;
    cmd[3]         = sectornum * 4096;

    W25Q64_WriteEnable();
    W25Q64_Busy();
    CS_ENABLE;
    HAL_SPI_Transmit(&spi1, cmd, 4, 1000);
    CS_DISABLE;
}

/**
 * @brief 写一个页256字节
 *
 * @param data 待写入数据
 * @param pagenum 地址等于  扇区地址*扇区大小
 */
void W25Q64_WritePage(uint8_t *data, uint32_t pagenum)
{
    uint8_t cmd[4] = {0x02, 0x00, 0x00, 0x00};
    cmd[1]         = (pagenum * 256) >> 16;
    cmd[2]         = (pagenum * 256) >> 8;
    cmd[3]         = pagenum * 256;

    W25Q64_WriteEnable();
    W25Q64_Busy();
    CS_ENABLE;
    HAL_SPI_Transmit(&spi1, cmd, 4, 1000);
    HAL_SPI_Transmit(&spi1, data, 256, 50000);
    CS_DISABLE;
}

/**
 * @brief 读取数据
 *
 * @param data
 * @param addr
 * @param len
 */
void W25Q64_ReadData(uint8_t *data, uint32_t addr, uint16_t len)
{
    uint8_t cmd[4] = {0x03, 0x00, 0x00, 0x00};
    cmd[1]         = addr >> 16;
    cmd[2]         = addr >> 8;
    cmd[3]         = addr;

    W25Q64_Busy();
    CS_ENABLE;
    HAL_SPI_Transmit(&spi1, cmd, 4, 1000);
    HAL_SPI_Receive(&spi1, data, len, 50000);
    CS_DISABLE;
}
