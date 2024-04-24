#ifndef __KEY_H__
#define __KEY_H__

#include "main.h"

#define KEY_NUM 2
#define KEY_SCAN_INTERVAL 10 // ms

typedef enum
{
    Key_Status_Released = 0,
    Key_Status_Pressed,
    Key_Status_Hold
} Key_Status;

typedef enum
{
    Key_Flag_None = 0x0001,
    Key_Flag_Single_Press = 0x0002,
    Key_Flag_Double_Press = 0x0004,
    Key_Flag_Long_Press = 0x0008
} Key_Flag;

typedef struct
{
    char key_name[10];
    Key_Flag key_flag;
} Key_QueueMsg;

typedef struct
{
    char  key_name[10];

    GPIO_TypeDef *GPIOx;
    uint16_t GPIO_Pin;

    GPIO_PinState key_validvalue;
    GPIO_PinState key_value;
    Key_Status key_status;

    Key_Flag key_flag;
} KEY_InitTypeDef;

extern KEY_InitTypeDef key[KEY_NUM];

void Key_Init(void);

void Key_Scan(void);

#endif // !__KEY_H__
