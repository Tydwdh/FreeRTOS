#include "FreeRTOSF.h"

#define TASK_STACK_SIZE 128
TaskHandle_t htask_start;
TaskHandle_t htask1;
TaskHandle_t htask2;
TaskHandle_t htask3;
TaskHandle_t hkeytask;
QueueHandle_t hkeyqueue;
void FreeRTOS_Init(void)
{

    hkeyqueue = xQueueCreate(3, sizeof(Key_Flag)); // 按键队列
    xTaskCreate(
        vtask_start,
        "task_start",
        TASK_STACK_SIZE,
        NULL,
        1,
        &htask_start);
    vTaskStartScheduler();
}

void vtask_start(void *pvParameters)
{
    taskENTER_CRITICAL();
    xTaskCreate(
        vtask1,
        "task1",
        TASK_STACK_SIZE,
        NULL,
        2,
        &htask1);
    xTaskCreate(
        vtask2,
        "task2",
        TASK_STACK_SIZE,
        NULL,
        2,
        &htask2);
    xTaskCreate(
        vtask3,
        "task3",
        TASK_STACK_SIZE,
        NULL,
        1,
        &htask3);
    xTaskCreate(
        vkeytask,
        "vkeytask",
        TASK_STACK_SIZE,
        NULL,
        1,
        &hkeytask);
    vTaskDelete(NULL);
    taskEXIT_CRITICAL();
}

void vtask1(void *pvParameters)
{
    int i = 0;
    Key_Flag flag;
    while (1)
    {
        xQueuePeek(hkeyqueue, &flag, portMAX_DELAY);
        if (flag == Key_Flag_Single_Press)
        {
            xQueueReceive(hkeyqueue, &flag, 0);
            taskENTER_CRITICAL();
            OLED_SetCursor(1, 1);
            printf("%d", i++);
            taskEXIT_CRITICAL();
            flag = Key_Flag_None;
        }
    }
}

void vtask2(void *pvParameters)
{
    int i = 0;
    while (1)
    {
        taskENTER_CRITICAL();
        OLED_SetCursor(2, 1);
        printf("%d", i++);
        taskEXIT_CRITICAL();
        vTaskDelay(1000);
    }
}
void vtask3(void *pvParameters)
{
    while (1)
    {
        OLED_Buf_Show();
        vTaskDelay(50);
    }
}

void vkeytask(void *pvParameters)
{
    Key_Flag flag;
    while (1)
    {
        Key_Scan();
        for (int i = 0; i < KEY_NUM; i++)
        {
            if (key[i].key_flag != Key_Flag_None)
            {
                if ((key[i].key_flag & Key_Flag_Single_Press) == Key_Flag_Single_Press)
                {
                    flag = Key_Flag_Single_Press;
                    xQueueSend(hkeyqueue, &flag, 1000);
                }
                if ((key[i].key_flag & Key_Flag_Long_Press) == Key_Flag_Long_Press)
                {
                    flag = Key_Flag_Long_Press;
                    xQueueSend(hkeyqueue, &flag, 1000);
                }
                if ((key[i].key_flag & Key_Flag_Double_Press) == Key_Flag_Double_Press)
                {
                    flag = Key_Flag_Double_Press;
                    xQueueSend(hkeyqueue, &flag, 1000);
                }
            }
            key[i].key_flag = Key_Flag_None;
        }
        vTaskDelay(KEY_SCAN_INTERVAL);
    }
}