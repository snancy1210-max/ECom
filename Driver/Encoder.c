#include "FreeRTOS.h"
#include <stdio.h>
#include "Encoder.h"
#include <stdint.h>
#include "ti_msp_dl_config.h"



volatile int32_t encoder_countx = 0;
uint8_t last_AB_state = 0;


int32_t Encoder_Get(void)
{
    return DL_Timer_getTimerCount(TIMG8);
}


uint8_t Encoder_Read_AB(void)
{
    uint8_t A;
    uint8_t B;

    if (DL_GPIO_readPins(GPIOA,DL_GPIO_PIN_12)) {
        A = 1;
    }else{
        A = 0;
    }

    if (DL_GPIO_readPins(GPIOA,DL_GPIO_PIN_13)) {
        B = 1;
    }else{
        B = 0;
    }

    return ( A << 1 ) | B;                                  //  00 -> 0  01 -> 1  10 -> 2  11 -> 3  二进制，状态变化不同来判断正反转
}


void GROUP1_IRQHandler(void)
{
    uint32_t status;

    status = DL_GPIO_getEnabledInterruptStatus(                       //获取引脚掩码，后面清除标志位可直接使用
        GPIOA,
        DL_GPIO_PIN_12|DL_GPIO_PIN_13                       
    );


    if(status)
    {

        uint8_t current;

        current = Encoder_Read_AB();

        /*
        正转
           00->01
           01->11
           11->10
           10->00
        */

        if ((last_AB_state == 0 && current == 1)||
            (last_AB_state == 1 && current == 3)||
            (last_AB_state == 3 && current == 2)||
            (last_AB_state == 2 && current == 0))
        {
            encoder_countx++;
        }


        /*
           反转
           00->10
           10->11
           11->01
           01->00
        */

        if ((last_AB_state == 0 && current == 2)||
            (last_AB_state == 2 && current == 3)||
            (last_AB_state == 3 && current == 1)||
            (last_AB_state == 1 && current == 0))
        {
            encoder_countx--;
        }


        last_AB_state = current;



        DL_GPIO_clearInterruptStatus(GPIOA,status);     //status是触发中断的引脚掩码
    }


}