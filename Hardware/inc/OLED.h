#ifndef __OLED_H
#define __OLED_H

#include "stm32f1xx_hal.h"
#include "stdbool.h"
#include "stdio.h"
#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_PAGE_NUM 8
#define OLED_COLUMN_NUM 16


#define OLED_I2C_ADDR 0x78

#define COM         0x00
#define DATA        0x40

#define DISPLAY_OFF 0xAE
#define DISPLAY_ON  0xAF

#define SET_LOW_COLUMN 0x00
#define SET_HIGH_COLUMN 0x10

#define SET_START_LINE 0x40

#define SET_PAGE 0xB0

#define SET_CONTRAST 0x81

#define SET_SEGMENT_REMAP 0xA1

#define SET_NORMAL_DISPLAY 0xA6
#define SET_INVERSE_DISPLAY 0xA7

#define SET_MULTIPLEX_RATIO 0xA8

#define COM_SCAN_INC 0xC0
#define COM_SCAN_DEC 0xC8

#define SET_DISPLAY_OFFSET 0xD3

#define SET_OSC_DIV 0xD5

#define SET_PRECHARGE 0xD9

#define SET_COM_PINS 0xDA

#define SET_VCOM_DESEL 0xDB

#define SET_CHARGE_PUMP 0x8D


extern bool OLED_SHOW_FLAG;
extern uint8_t   OLED_ShowBuffer_bak[8][128];// 备份缓存区

void OLED_Init(void);
static void OLED_Cmd(uint8_t cmd);
static void OLED_Data(uint8_t *data, uint16_t len);
void OLED_DrawPoint(uint8_t x, uint8_t y);
void OLED_Printf(uint8_t x, uint8_t y, const char * fmt, ...);
void OLED_Clear(void);
static void OLED_TransPosition(uint8_t Y, uint8_t X);//尽量不要使用，调用太快I2C通讯会出问题
void OLED_Buf_Show(void);
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);
void OLED_ShowString(uint8_t x, uint8_t y, char *p);
void OLED_SetCursor(uint8_t Y, uint8_t X);
void OLED_ReverseArea(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height);

#endif
