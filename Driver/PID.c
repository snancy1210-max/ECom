#include <stdio.h>
#include "PID.h"

#include <math.h>
#include "FreeRTOS.h"
#include "ti_msp_dl_config.h"


void PID_Init(PID_t *speed_pid,PID_t *yaw_pid)
{
    // 速度环
    speed_pid->kp = 2.0f;        // 起步误差 50 ticks 时，输出约 100 PWM
    speed_pid->ki = 0.1f;
    speed_pid->kd = 0.0f;
    speed_pid->IntegralK = 0.5f;
    speed_pid->alpha = 0.3f;
    speed_pid->MaxOutput = 1000;
    
    // 航向环
    yaw_pid->kp = 3.0f;          // 从 1~5 开始试
    yaw_pid->ki = 0.0f;          // 航向环一般不加 I，容易绕圈
    yaw_pid->kd = 0.5f;          // 用陀螺仪做 D，抑制摇头
    yaw_pid->IntegralK = 1.0f;   // 反正 ki=0，无所谓
    yaw_pid->alpha = 1.0f;       // Yaw 如果已滤波，不再二次滤波
    yaw_pid->MaxOutput = 300;    // 差速限制！调这个控制转弯灵敏度
}


void PID_Speed_Cal(PID_t *pid,State_t *state,float Speed)      //Speed新获取的速度
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

    if(state->Output > pid->MaxOutput){                                     //限1000，PWM  -1000~1000
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


float Yaw_Error(float target, float current)       //航向角
{
    float err = target - current;
    while (err > 180.0f)  err -= 360.0f;
    while (err < -180.0f) err += 360.0f;
    return err;
}


void PID_Yaw_Cal(PID_t *pid, State_t *state, float Yaw, float Gyro_Z)  //Yaw为current
{
    float err = Yaw_Error(state->Target, Yaw);
    
    state->Speed_f += pid->alpha * (Yaw - state->Speed_f);                     //读取Yaw已经滤波了，alpha = 1
    
    float C = 1.0f / (pid->IntegralK * fabsf(err) + 1);
    
    // 增量式输出
    // D 项用陀螺仪 Z 轴（°/s），比角度差分响应快、无跳变
    // 符号实测：如果车越控越晃，把 -Gyro_Z 改成 +Gyro_Z
    state->Output +=
        pid->kp * (err - state->error_last) +
        pid->ki * C * err +
        pid->kd * (-Gyro_Z);
    
    // 限幅（差速 PWM）
    if (state->Output > pid->MaxOutput)  state->Output = pid->MaxOutput;         //限300，转弯不要太猛
    if (state->Output < -pid->MaxOutput) state->Output = -pid->MaxOutput;
    
    
    state->error_last = err;
}

float Line_PD(LinePD_t *pd,float error)
{
    float out;

    out =
        pd->kp * error
      + pd->kd * (error - pd->last_error);

    pd->last_error = error;

    return out;
}
