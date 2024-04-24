#include "stm32f1xx_hal.h"
#include "SPI.h"

SPI_HandleTypeDef spi1 = {0};

/**
 * @brief SPI1 初始化函数
 *
 */
void SPI1_Init(void)
{

    spi1.Instance = SPI1;                                  // 使用SPI1
    spi1.Init.Mode = SPI_MODE_MASTER;                      // 主机模式
    spi1.Init.Direction = SPI_DIRECTION_2LINES;            // 双线模式，全双工
    spi1.Init.DataSize = SPI_DATASIZE_8BIT;                // 8位数据模式
    spi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2; // PI1是APB2的时钟源72Mhz，预分频器选择2->36Mhz
    spi1.Init.CLKPolarity = SPI_POLARITY_LOW;              // 时钟极性低
    spi1.Init.CLKPhase = SPI_PHASE_1EDGE;                  // 第1边沿采样  MODE 0
    spi1.Init.NSS = SPI_NSS_SOFT;                          // 软件NSS管脚
    spi1.Init.FirstBit = SPI_FIRSTBIT_MSB;                 // 高位先发
    spi1.Init.TIMode = SPI_TIMODE_DISABLE;                 // 不使用TI模式
    spi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE; // 不计算CRC
    HAL_SPI_Init(&spi1);
}
// SPI1底层初始化函数
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
    if (hspi->Instance == SPI1)
    {
        // PA4=SPI1_NSS,PA5=SPI1_SCK PA6=SPI1_MISO, PA7=SPI1_MOSI,
        __HAL_RCC_SPI1_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
        GPIO_InitTypeDef GPIO_Init;

        GPIO_Init.Pin = GPIO_PIN_7 | GPIO_PIN_5;
        GPIO_Init.Mode = GPIO_MODE_AF_PP;
        GPIO_Init.Pull = GPIO_NOPULL;
        GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;

        HAL_GPIO_Init(GPIOA, &GPIO_Init);

        GPIO_Init.Pin = GPIO_PIN_6;
        GPIO_Init.Mode = GPIO_MODE_AF_INPUT;
        GPIO_Init.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOA, &GPIO_Init);

        GPIO_Init.Pin = GPIO_PIN_4;
        GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_Init.Pull = GPIO_PULLUP;
        GPIO_Init.Speed = GPIO_SPEED_FREQ_LOW;

        HAL_GPIO_Init(GPIOA, &GPIO_Init);
    }
    else if (hspi->Instance == SPI2)
    {
    }
}
