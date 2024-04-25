#ifndef _FREERTOSF_H_
#define _FREERTOSF_H_


#include "main.h"
extern QueueHandle_t holedsem;

void FreeRTOS_Init(void);

void vtask_start(void* pvParameters);

void vtask1(void* pvParameters);

void vtask2(void* pvParameters);

void vtask3(void* pvParameters);

void vkeytask(void *pvParameters);

#endif

