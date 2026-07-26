#include "FreeRTOS.h"
#include <stdio.h>
#include "main.h"
#include <math.h>
#include <stdint.h>
#include "ti_msp_dl_config.h"


void Step_Motor_Task(void *pvParameters)
{
    while (!init_done)
   {
      vTaskDelay(pdMS_TO_TICKS(10));
   }


    while (1) {
    
     vTaskDelay(pdMS_TO_TICKS(10));
    }

}