#include "OLED.h"
#include "OLED_Font.h"
uint8_t OLED_ShowBuffer[OLED_PAGE_NUM][OLED_WIDTH] = {0};     // 显示缓存区
uint8_t OLED_ShowBuffer_bak[OLED_PAGE_NUM][OLED_WIDTH] = {0}; // 备份缓存区
uint8_t oled_x = 1, oled_y = 1;                               // 当前光标位置
/**
 * @brief 初始化OLED
 * @param  void
 * @return void
 */
void OLED_Init(void)
{
    IIC1_Init();
    OLED_Cmd(DISPLAY_OFF);
    OLED_Cmd(SET_OSC_DIV);
    OLED_Cmd(0x80);
    OLED_Cmd(SET_MULTIPLEX_RATIO);
    OLED_Cmd(0x3f);
    OLED_Cmd(SET_DISPLAY_OFFSET);
    OLED_Cmd(0x00);
    OLED_Cmd(SET_START_LINE);
    OLED_Cmd(SET_LOW_COLUMN);
    OLED_Cmd(SET_HIGH_COLUMN);
    OLED_Cmd(SET_SEGMENT_REMAP);
    OLED_Cmd(COM_SCAN_DEC);
    OLED_Cmd(SET_COM_PINS);
    OLED_Cmd(0x12);
    OLED_Cmd(SET_CONTRAST);
    OLED_Cmd(0xff);
    OLED_Cmd(SET_PRECHARGE);
    OLED_Cmd(0xff);
    OLED_Cmd(SET_VCOM_DESEL);
    OLED_Cmd(0x30);
    OLED_Cmd(0xa4);
    OLED_Cmd(SET_NORMAL_DISPLAY);
    OLED_Cmd(SET_CHARGE_PUMP);
    OLED_Cmd(0x14);
    OLED_Cmd(DISPLAY_ON);
    OLED_Clear();
}

/**
 * @brief 发送命令到OLED
 * @param cmd 要发送的命令
 * @return void
 */
void OLED_Cmd(uint8_t cmd)
{
    HAL_I2C_Mem_Write(&hi2c1, OLED_I2C_ADDR, COM, I2C_MEMADD_SIZE_8BIT, &cmd, 1, 1000);
}

/**
 * @brief 发送数据到OLED
 * @param data 要发送的数据
 * @param len 数据的长度
 * @return void
 */
void OLED_Data(uint8_t *data, uint16_t len)
{
    HAL_I2C_Mem_Write_DMA(&hi2c1, OLED_I2C_ADDR, DATA, I2C_MEMADD_SIZE_8BIT, data, len);
}

/**
 * @brief 清除OLED显示
 * @param  void
 * @return void
 */
void OLED_Clear(void)
{
    memset(OLED_ShowBuffer, 0, sizeof(OLED_ShowBuffer));
}

/**
 * @brief 在OLED上显示字符串
 * @param x 字符串的x坐标 1-16
 * @param y 字符串的y坐标 1-4
 * @param p 要显示的字符串
 * @return void
 */
void OLED_ShowString(uint8_t x, uint8_t y, char *p)
{
    uint8_t len1 = strlen(p);
    for (uint8_t i = 0; i < len1; i++)
    {
        OLED_ShowChar(y, x + i, p[i]);
    }
}

/**
 * @brief 在OLED上显示字符
 * @param Line 字符的行号 1-4
 * @param Column 字符的列号 1-16
 * @param Char 要显示的字符
 * @return void
 */
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char)
{
    uint8_t i;
    if (Column <= OLED_COLUMN_NUM)
    {
        for (i = 0; i < 8; i++)
        {
            OLED_ShowBuffer_bak[(Line - 1) * 2][(Column - 1) * 8 + i] = OLED_F8x16[Char - ' '][i];
            OLED_ShowBuffer_bak[(Line - 1) * 2 + 1][(Column - 1) * 8 + i] = OLED_F8x16[Char - ' '][i + 8];
        }
    }
    else
    {
        for (i = 0; i < 8; i++)
        {
            OLED_ShowBuffer_bak[(Line) * 2][(Column - 1 - OLED_COLUMN_NUM) * 8 + i] = OLED_F8x16[Char - ' '][i];
            OLED_ShowBuffer_bak[(Line) * 2 + 1][(Column - 1 - OLED_COLUMN_NUM) * 8 + i] = OLED_F8x16[Char - ' '][i + 8];
        }
    }
}

/**
 * @brief 反转OLED显示区域
 * @param X 区域的x坐标
 * @param Y 区域的y坐标
 * @param Width 区域的宽度
 * @param Height 区域的高度
 * @return void
 */
void OLED_ReverseArea(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height)
{
    uint8_t i, j;
    if (X > 127)
    {
        return;
    }
    if (Y > 63)
    {
        return;
    }
    if (X + Width > OLED_WIDTH)
    {
        Width = OLED_WIDTH - X;
    }
    if (Y + Height > OLED_HEIGHT)
    {
        Height = OLED_HEIGHT - Y;
    }
    for (j = Y; j < Y + Height; j++)
    {
        for (i = X; i < X + Width; i++)
        {
            OLED_ShowBuffer_bak[j / 8][i] ^= 0x01 << (j % 8);
        }
    }
}

/**
 * @brief 设置OLED的光标位置
 * @param Y 光标的Y坐标
 * @param X 光标的X坐标
 * @return 无
 */
void OLED_TransPosition(uint8_t Y, uint8_t X)
{
    OLED_Cmd(SET_PAGE | Y);
    OLED_Cmd(SET_HIGH_COLUMN | ((X & 0xF0) >> 4));
    OLED_Cmd(SET_LOW_COLUMN | (X & 0x0F));
}

/**
 * @brief 显示OLED的缓冲区内容
 * @param 无
 * @return 无
 */
void OLED_Buf_Show(void)
{
    memcpy(OLED_ShowBuffer, OLED_ShowBuffer_bak, sizeof(OLED_ShowBuffer));
    OLED_TransPosition(0, 0);
    OLED_Data(OLED_ShowBuffer[0], OLED_WIDTH); // 一次发送整个缓冲区
}

/**
 * @brief 画点
 *
 * @param x 0-127
 * @param y 0-63
 * @return 无
 */
void OLED_DrawPoint(uint8_t x, uint8_t y)
{
    OLED_ShowBuffer_bak[y / 8][x] |= 0x01 << (y % 8);
}

/**
 * @brief 输出字符串
 *
 * @param x 1-16
 * @param y 1-4
 * @param fmt 要输出的字符串格式
 * @param ...
 */
void OLED_Printf(uint8_t x, uint8_t y, const char *fmt, ...)
{
    char buf[OLED_WIDTH]; // 缓冲区，你可以根据需要调整大小
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);

    OLED_ShowString(x, y, buf); // 将buf的内容显示在OLED上
}

int fputc(int ch, FILE *f)
{

    if (ch == '\n')
    {
        oled_y = oled_y % 4 + 1;
        oled_x = 1;
    }
    else if (ch == '\t')
    {
        oled_x = (oled_x + 3) % 16 + 1;
        if (oled_x > 16)
        {
            oled_x = 1;
            oled_y = oled_y % 4 + 1;
        }
    }
    else
    {
        if (oled_x > 16)
        {
            oled_x = 1;
            oled_y = oled_y % 4 + 1;
        }
        OLED_ShowChar(oled_y, oled_x++, ch);
    }

    // HAL_UART_Transmit(&uart1.uart, (uint8_t *)&ch, 1, 1000);

    return ch;
}
/**
 * @brief 设置OLED的光标位置
 * @param Y 光标的Y坐标 1-4
 * @param X 光标的X坐标 1-16
 * @return 无
 */
void OLED_SetCursor(uint8_t Y, uint8_t X)
{
    oled_x = X;
    oled_y = Y;
}

/**
 * @brief I2C内存发送完成的回调函数
 * @param hi2c I2C句柄
 * @return 无
 */
void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    static uint8_t i = 1;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    if (hi2c->Instance == I2C1)
    {
        OLED_TransPosition(i, 0);
        OLED_Data(OLED_ShowBuffer[i], OLED_WIDTH);
        i++;
        if (i == OLED_PAGE_NUM)
        {
            i = 0;
            xSemaphoreGiveFromISR(holedsem, &xHigherPriorityTaskWoken);
        }
    }
}
