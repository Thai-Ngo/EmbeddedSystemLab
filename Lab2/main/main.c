#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"

#define BUTTON_PIN 35

void id_task(void *pvParameter)
{
    while(1)
	{
	    printf("1912046\n");
        vTaskDelay(1000 / portTICK_RATE_MS);
	}
}

void read_button_task(void *pvParameter)
{
    gpio_pad_select_gpio(BUTTON_PIN) ;
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT) ;

    uint8_t curState = 1;
    uint8_t prevState = 1;
    while(1)
	{
        prevState = curState;
        curState = gpio_get_level(BUTTON_PIN);
        if (prevState == 1 && curState == 0) {
            printf("ESP32\n");
        }
	    // printf("Get value of %d\n", prevState);
        // printf("Get value of %d\n", curState);
        
        vTaskDelay(10 / portTICK_RATE_MS);
	}
}
 
void app_main()
{
    xTaskCreate(&id_task, "id_task", 2048, NULL, 5, NULL);
    xTaskCreate(&read_button_task, "read_button_task", 2048, NULL, 5, NULL);
}