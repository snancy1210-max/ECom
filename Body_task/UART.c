#include "FreeRTOS.h"
#include <stdio.h>
#include "main.h"
#include <math.h>
#include <stdint.h>
#include "ti_msp_dl_config.h"

// 定义一个极简的全局变量，存放最新收到的单字节数据
volatile uint8_t g_rx_temp_byte = 0; 

// UART_3 中断服务函数
void UART_3_INST_IRQHandler(void)
{
    switch (DL_UART_getPendingInterrupt(UART_3_INST)) {
        case DL_UART_IIDX_RX: // 产生串口接收中断
        {
            // 收到什么字节，就直接存入 g_rx_temp_byte 变量中
            g_rx_temp_byte = DL_UART_receiveData(UART_3_INST);
            
            /* TODO: 后面通路测试成功后，可以在这里加入帧头、帧尾等协议解析代码 */
            
            break;
        }
        default:
            break;
    }
}

// FreeRTOS 串口任务
void Uart_Task(void *pvParameters)
{
    while (!init_done) {
        vTaskDelay(pdMS_TO_TICKS(10));
    }

    // 手动使能中断
    DL_UART_enableInterrupt(UART_3_INST, DL_UART_INTERRUPT_RX);
    NVIC_EnableIRQ(UART_3_INST_INT_IRQN);

    while (1) {
        // 任务循环目前无需做任何事情
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}