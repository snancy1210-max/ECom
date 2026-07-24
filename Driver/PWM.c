#include <stdio.h>
#include "PID.h"
#include <math.h>
#include "FreeRTOS.h"
#include "ti_msp_dl_config.h"


uint16_t  PWM_DEADZONE = 0; //死区阈值，防止抖动
uint16_t PWM_MAX = 1000;



void PWM_Set_DI_L(int16_t pwm)   // 传入 -1000 ~ +1000
{
    uint16_t duty;
 /*****************************只有正传暂时不用   
    if (pwm > 0) {
        DL_GPIO_setPins(DIR_L_PORT, DIR_L_PIN);     // 正转
        duty = (uint16_t)pwm;
    } else if (pwm < 0) {
        DL_GPIO_clearPins(DIR_L_PORT, DIR_L_PIN);   // 反转
        duty = (uint16_t)(-pwm);
    } else {
        duty = 0;
    }
    */
    if (pwm > 0) {
        duty = (uint16_t)pwm;
    }else {
        duty = 0;
    }

    if (duty > 0 && duty < PWM_DEADZONE) {
        duty = PWM_DEADZONE;
    }
    if (duty > PWM_MAX) duty = PWM_MAX;
    
    DL_TimerA_setCaptureCompareValue(PWM_DI_INST, (uint32_t)duty, DL_TIMER_CC_0_INDEX);
}

void PWM_Set_DI_R(int16_t pwm)
{
    uint16_t duty;
 /*****************************只有正传暂时不用   
    if (pwm > 0) {
        DL_GPIO_setPins(DIR_L_PORT, DIR_L_PIN);     // 正转
        duty = (uint16_t)pwm;
    } else if (pwm < 0) {
        DL_GPIO_clearPins(DIR_L_PORT, DIR_L_PIN);   // 反转
        duty = (uint16_t)(-pwm);
    } else {
        duty = 0;
    }
    */
    if (pwm > 0) {
        duty = (uint16_t)pwm;
    }else {
        duty = 0;
    }

    if (duty > 0 && duty < PWM_DEADZONE) {
        duty = PWM_DEADZONE;
    }
    if (duty > PWM_MAX) duty = PWM_MAX;
    
    DL_TimerA_setCaptureCompareValue(PWM_DI_INST, (uint32_t)duty, DL_TIMER_CC_1_INDEX);
}

/********* 不用云台
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

*/
