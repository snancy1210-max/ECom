#include <stdio.h>
#include "PID.h"

#include <math.h>
#include "FreeRTOS.h"
#include "ti_msp_dl_config.h"



void PID_Cal(PID_t *pid,State_t *state,float Speed)      //Speed新获取的速度
{   

    state->Speed_f += pid->alpha* (Speed-state->Speed_f);//一阶低通滤波

    state->error = state->Target-state->Speed_f;   
    
    float C = 1.0f/(pid->IntegralK*fabsf(state->error)+1);
   /*
   if (fabsf(pid->error) < pid->E) {
      C = 1;
   }
    */

    state->Output +=
        pid->kp * (state->error - state->error_last) +
        pid->ki * C*state->error +
        pid->kd * (state->Speed_f-2.0f*state->Speed_f_last+state->Speed_f_lastlast);   //微分先行

    if(state->Output > pid->MaxOutput){
       state->Output = pid->MaxOutput;
    }
    if(state->Output < -pid->MaxOutput){
       state->Output = -pid->MaxOutput;
    }
   /* if(fabsf(pid->Output)<5){
        pid->Output = 0;          //死区放Motor_PWM里面，pwm<5 >> pwm=0
    }
   */
    state->Speed_f_lastlast = state->Speed_f_last;
    state->Speed_f_last = state->Speed_f;

    state->error_last = state->error;

}