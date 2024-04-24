#include "key.h"

KEY_InitTypeDef key[KEY_NUM] = {0};

void Key_Init(void)
{

    __HAL_RCC_GPIOB_CLK_ENABLE();

    key[0].GPIOx = GPIOB;
    key[0].GPIO_Pin = GPIO_PIN_1;
    key[0].key_validvalue = GPIO_PIN_RESET;

    for (int i = 0; i < KEY_NUM; i++)
    {
        key[i].key_value = HAL_GPIO_ReadPin(key[i].GPIOx, key[i].GPIO_Pin);
        key[i].key_status = (key[i].key_value == key[i].key_validvalue) ? Key_Status_Hold : Key_Status_Released;
        key[i].key_flag = Key_Flag_None;

        GPIO_InitTypeDef GPIO_InitStructure;

        GPIO_InitStructure.Pin = key[i].GPIO_Pin;
        GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
        GPIO_InitStructure.Pull = GPIO_PULLUP;
        GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;

        HAL_GPIO_Init(key[i].GPIOx, &GPIO_InitStructure);
    }
}

void Key_Scan(void)
{
    for (int i = 0; i < KEY_NUM; i++)
    {
        key[i].key_value = HAL_GPIO_ReadPin(key[i].GPIOx, key[i].GPIO_Pin);

        switch (key[i].key_status)
        {
        case Key_Status_Released:
            if (key[i].key_value == key[i].key_validvalue)
            {
                key[i].key_status = Key_Status_Pressed;
            }
            break;
        case Key_Status_Pressed:
            if (key[i].key_value != key[i].key_validvalue)
            {
                key[i].key_status = Key_Status_Released;
            }
            else if (key[i].key_value == key[i].key_validvalue)
            {
                key[i].key_status = Key_Status_Hold;
            }
            break;
        case Key_Status_Hold:
            if (key[i].key_value != key[i].key_validvalue)
            {
                key[i].key_status = Key_Status_Released;
                key[i].key_flag |= Key_Flag_Single_Press;
            }
            break;
        default:
            break;
        }
    }
}