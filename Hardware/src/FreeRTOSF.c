#include "FreeRTOSF.h"

#define TASK_STACK_SIZE 128
TaskHandle_t htask_start;
TaskHandle_t htask1;
TaskHandle_t htask2;
TaskHandle_t htask3;
TaskHandle_t hkeytask;
QueueHandle_t hkeyqueue;
QueueHandle_t hkeysem;
QueueHandle_t holedsem;
void FreeRTOS_Init(void)
{

    hkeyqueue = xQueueCreate(1, sizeof(Key_QueueMsg)); // 按键队列
    vSemaphoreCreateBinary(holedsem);
    hkeysem = xSemaphoreCreateBinary();
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
        10,
        &htask3);
    xTaskCreate(
        vkeytask,
        "vkeytask",
        TASK_STACK_SIZE,
        NULL,
        10,
        &hkeytask);
    vTaskDelete(NULL);
    taskEXIT_CRITICAL();
}

void vtask1(void *pvParameters)
{
    int i = 0;
    Key_QueueMsg keyq;
    while (1)
    {
        xQueuePeek(hkeyqueue, &keyq, portMAX_DELAY);
        if (keyq.key_flag == Key_Flag_Single_Press && !strcmp(keyq.key_name, "KEY1"))
        {
            xQueueReceive(hkeyqueue, &keyq, 0);
            taskENTER_CRITICAL();
            OLED_SetCursor(1, 1);
            printf("%d", i++);
            taskEXIT_CRITICAL();
            keyq.key_flag = Key_Flag_None;
        }
    }
}

void vtask2(void *pvParameters)
{
    int i = 0;
    Key_QueueMsg keyq;
    while (1)
    {
        xQueuePeek(hkeyqueue, &keyq, portMAX_DELAY);
        if (keyq.key_flag == Key_Flag_Single_Press && !strcmp(keyq.key_name, "KEY2"))
        {
            xQueueReceive(hkeyqueue, &keyq, 0);
            taskENTER_CRITICAL();
            OLED_SetCursor(2, 1);
            printf("%d", i++);
            taskEXIT_CRITICAL();
            keyq.key_flag = Key_Flag_None;
        }
    }
}
void vtask3(void *pvParameters)
{
    TickType_t pxPreviousWakeTime = xTaskGetTickCount();
    while (1)
    {
        xSemaphoreTake(holedsem, portMAX_DELAY);
        OLED_Buf_Show();
        xTaskDelayUntil(&pxPreviousWakeTime, 50);
    }
}

void vkeytask(void *pvParameters)
{
    Key_QueueMsg keyq;
    while (1)
    {
        Key_Scan();
        for (int i = 0; i < KEY_NUM; i++)
        {
            if (key[i].key_flag != Key_Flag_None)
            {
                memcpy(&keyq.key_name, &key[i].key_name, sizeof(keyq.key_name));
                if ((key[i].key_flag & Key_Flag_Single_Press) == Key_Flag_Single_Press)
                {
                    keyq.key_flag = Key_Flag_Single_Press;
                }
                else if ((key[i].key_flag & Key_Flag_Long_Press) == Key_Flag_Long_Press)
                {
                    keyq.key_flag = Key_Flag_Long_Press;
                }
                else if ((key[i].key_flag & Key_Flag_Double_Press) == Key_Flag_Double_Press)
                {
                    keyq.key_flag = Key_Flag_Double_Press;
                }
                xQueueOverwrite(hkeyqueue, &keyq);
            }
            key[i].key_flag = Key_Flag_None;
        }
        vTaskDelay(KEY_SCAN_INTERVAL);
    }
}