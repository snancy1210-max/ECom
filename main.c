#include "FreeRTOS.h"
#include <stdio.h>
#include "queue.h"
#include "task.h"
#include <stdint.h>
#include "PWM.h"
#include "PID.h"
#include "queue.h"
#include "DIMotor.h"
#include "StepMotor.h"
#include "UART.h"
#include "imu_I2C.h"
#include "imu660rc.h"
#include "ti_msp_dl_config.h"
#include "Encoder.h"

#include "SEGGER_RTT.h"


QueueHandle_t Motor_DI_Queue;
QueueHandle_t Motor_DI2_Queue;
 
static void prvSetupHardware(void);
volatile uint8_t init_done = 0;


int main(void)
{
     

    prvSetupHardware();

    SEGGER_RTT_Init();
    SEGGER_RTT_printf(0, "[MAIN] Boot OK\r\n");



    Motor_DI_Queue = xQueueCreate(10,sizeof(State_t));
    Motor_DI2_Queue = xQueueCreate(10,sizeof(State_t));


  BaseType_t ret;

   /*  xTaskCreate(Uart_Task,
                "UART",
                256,
                NULL,
                1,
                NULL);
*/
     ret = 
    xTaskCreate(DI_Motor_Task,
                "Motor",
                512,
                NULL,
                2,
                NULL);

SEGGER_RTT_printf(0, "[MAIN] UART create=%d\r\n", ret);

ret =
    xTaskCreate(Step_Motor_Task,
                "Motor",
                512,
                NULL,
                1,
                NULL);

SEGGER_RTT_printf(0, "[MAIN] UART create=%d\r\n", ret);


    // 启动FreeRTOS
    vTaskStartScheduler();

SEGGER_RTT_printf(0, "[MAIN] Scheduler returned!\r\n");  
    while(1);




    return 0;
}
/*-----------------------------------------------------------*/

static void prvSetupHardware(void)
{
    SYSCFG_DL_init();
    imu660rc_i2c_init();
    GROUP1_NVIC_init();
    PWM_Set_DI_L(0);
    PWM_Set_DI_R(0);
   // PWM_Set_Step_L(0);
   // PWM_Set_Step_R(0);
    last_AB_state = Encoder_Read_AB();


    init_done = 1;
}
/*-----------------------------------------------------------*/

// #if (configSUPPORT_STATIC_ALLOCATION == 1)
// /*
//  *  ======== vApplicationGetIdleTaskMemory ========
//  *  When static allocation is enabled, the app must provide this callback
//  *  function for use by the Idle task.
//  */
// void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
//     StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize)
// {
//     static StaticTask_t xIdleTaskTCB;
//     static StackType_t uxIdleTaskStack[configIDLE_TASK_STACK_DEPTH];

//     *ppxIdleTaskTCBBuffer   = &xIdleTaskTCB;
//     *ppxIdleTaskStackBuffer = uxIdleTaskStack;
//     *pulIdleTaskStackSize   = configIDLE_TASK_STACK_DEPTH;
// }

// #if (configUSE_TIMERS == 1)
// /*
//  *  ======== vApplicationGetTimerTaskMemory ========
//  *  When static allocation is enabled, and timers are used, the app must provide
//  *  this callback function for use by the Timer Service task.
//  */
// void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer,
//     StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize)
// {
//     static StaticTask_t xTimerTaskTCB;
//     static StackType_t uxTimerTaskStack[configTIMER_TASK_STACK_DEPTH];

//     *ppxTimerTaskTCBBuffer   = &xTimerTaskTCB;
//     *ppxTimerTaskStackBuffer = uxTimerTaskStack;
//     *pulTimerTaskStackSize   = configTIMER_TASK_STACK_DEPTH;
// }
// #endif

// #endif

#if (configCHECK_FOR_STACK_OVERFLOW)
/*
     *  ======== vApplicationStackOverflowHook ========
     *  When stack overflow checking is enabled the application must provide a
     *  stack overflow hook function. This default hook function is declared as
     *  weak, and will be used by default, unless the application specifically
     *  provides its own hook function.
     */
#if defined(__IAR_SYSTEMS_ICC__)
__weak void vApplicationStackOverflowHook(
    TaskHandle_t pxTask, char *pcTaskName)
#elif (defined(__TI_COMPILER_VERSION__))
#pragma WEAK(vApplicationStackOverflowHook)
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
#elif (defined(__GNUC__) || defined(__ti_version__))
void __attribute__((weak))
vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
#endif
{
    /* default to spin upon stack overflow */
    while (1) {
    }
}
#endif

/*-----------------------------------------------------------*/
