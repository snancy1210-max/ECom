#include "FreeRTOS.h"
#include "stdio.h"
#include "main.h"
#include "PID.h"
#include <math.h>
#include "PWM.h"
#include "queue.h"
#include <stdint.h>
#include "Encoder.h"
#include "ti_msp_dl_config.h"


uint32_t* count1_la,*count2_la;
State_t Tar_sta_1;
State_t Tar_sta_2;

extern volatile int32_t encoder_count;

PID_t PID = {0.0f};


/**** * xQueueReceive(
            Motor_Queue,
            &cmd,
            portMAX_DELAY
        );
        */
void DI_Motor_Task(void *pvParameters)
{
   uint32_t count1,count2;

   while (!init_done) {                                                
      vTaskDelay(pdMS_TO_TICKS(10));                                        
   }

    while (1) {

        xQueueReceive(                                 //不需要获取这个结构体，应该是获取目标速度，然后按速度曲线给Target赋值
            Motor_DI_Queue,
            &Tar_sta_1,
            portMAX_DELAY
        );

        xQueueReceive(
            Motor_DI2_Queue,
            &Tar_sta_2,
            portMAX_DELAY
        );

    count1 = Encoder_Get();

    count2 = encoder_count;

    int32_t Speed1 = (count1 - *count1_la)/10;       //ci/ms

    int32_t Speed2 = (count2 - *count2_la)/10;

    *count1_la = count1;
    *count2_la = count2;

    PID_Cal(&PID, &Tar_sta_1, Speed1);
    PID_Cal(&PID, &Tar_sta_2, Speed2);

    PWM_Set_DI_L(Tar_sta_1.Output);
    PWM_Set_DI_R(Tar_sta_2.Output);

     
    }
    vTaskDelay(pdMS_TO_TICKS(10));                                       //看一下单位改成大概10ms/次
}


