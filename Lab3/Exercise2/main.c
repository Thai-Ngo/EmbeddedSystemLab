#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define OFFSET               130000                
#define ONE_TICK             290000
#define getTICKDELAY(n)      (n + 1) * ONE_TICK - OFFSET

char cBuffer[512];

void vApplicationIdleHook(void) { 
    printf("IdleTask: Start at tick %d\n", xTaskGetTickCount()); 
    vTaskGetRunTimeStats(cBuffer);
    printf("%s\n", cBuffer);
    fflush(stdout);
}

void vApplicationTickHook(void) { }

void delay(char* name, int maxVal) {
    printf("%s: Dummy delay\n", name);
    for (int i = 0; i < maxVal; i++) { }
}

void vTask0(void *pvParameter)
{
    while(1)
	{
        printf("vTask0: Start at tick %d\n", xTaskGetTickCount());
        delay("vTask0", getTICKDELAY(3));
        printf("vTask0: Blocked at tick %d\n", xTaskGetTickCount());
        fflush(stdout);
        vTaskDelay(120 / portTICK_RATE_MS);
	}
}

void vTask1(void *pvParameter)
{
    while(1)
	{
        printf("vTask1: Start at tick %d\n", xTaskGetTickCount());
        delay("vTask1", getTICKDELAY(3));
        printf("vTask1: Blocked at tick %d\n", xTaskGetTickCount());
        fflush(stdout);
        vTaskDelay(50 / portTICK_RATE_MS);
	}
}

void vTask2(void *pvParameter)
{
    vTaskDelay(40 / portTICK_RATE_MS);
    while(1)
	{
        printf("vTask2: Start at tick %d\n", xTaskGetTickCount());
        delay("vTask2", getTICKDELAY(3));
        printf("vTask2: Blocked at tick %d\n", xTaskGetTickCount());
        fflush(stdout);
        vTaskDelay(80 / portTICK_RATE_MS);
	}
}

void app_main(void)
{
    xTaskCreate(&vTask0, "vTask0", 2048, NULL, 1, NULL);
    xTaskCreate(&vTask1, "vTask1", 2048, NULL, 1, NULL);
    xTaskCreate(&vTask2, "vTask2", 2048, NULL, 2, NULL);
}