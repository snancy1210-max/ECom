#include <stdio.h>
#include "PID.h"
#include <math.h>
#include "FreeRTOS.h"
#include "ti_msp_dl_config.h"



void PWM_Set_DI_L(uint16_t duty)
{
    if (duty > 100) {
       duty = 100;
    }else if (duty < 5) {                 //解决死区，防止抖动
       duty = 0;
    }

    DL_TimerA_setCaptureCompareValue(
        PWM_DI_INST ,
        duty,
        DL_TIMER_CC_0_INDEX
    );
}


void PWM_Set_DI_R(uint16_t duty)
{
    if (duty > 100) {
       duty = 100;
    }else if (duty < 5) {                 //解决死区，防止抖动
       duty = 0;
    }

    DL_TimerA_setCaptureCompareValue(
        PWM_DI_INST ,
        duty,
        DL_TIMER_CC_1_INDEX
    );
}


void PWM_Set_Step_L(uint16_t duty)
{
    if (duty > 100) {
       duty = 100;
    }else if (duty < 5) {                 //解决死区，防止抖动，云台可看着决定是否改0
       duty = 0;
    }

    DL_TimerG_setCaptureCompareValue(
        PWM_Step1_INST,
        duty,
        DL_TIMER_CC_0_INDEX
    );
}


void PWM_Set_Step_R(uint16_t duty)
{
    if (duty > 100) {
       duty = 100;
    }else if (duty < 5) {                 //解决死区，防止抖动
       duty = 0;
    }

    DL_TimerG_setCaptureCompareValue(
        PWM_Step2_INST,
        duty,
        DL_TIMER_CC_0_INDEX
    );
}


