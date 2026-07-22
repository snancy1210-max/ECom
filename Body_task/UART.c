#include "FreeRTOS.h"
#include <stdio.h>
#include "main.h"
#include <math.h>
#include <stdint.h>
#include "ti_msp_dl_config.h"

void Uart_Task(void *pvParameters)      //xQueueOverwrite()
{
    while (!init_done) {
      vTaskDelay(pdMS_TO_TICKS(10));
   }


    while (1) {
    
    }

    vTaskDelay(pdMS_TO_TICKS(10));
}