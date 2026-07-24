#include "FreeRTOS.h"
#include "stdio.h"
#include "main.h"
#include "PID.h"
#include <math.h>
#include "PWM.h"
#include "queue.h"
#include <stdint.h>
#include "DIMotor.h"
#include "imu660rc.h"
#include "imu_I2C.h"
#include "Encoder.h"
#include "ti_msp_dl_config.h"



uint16_t Stepts = 1;            //速度曲线斜率
uint16_t Tar_Speed = 0;         //最终要的速度
uint32_t *count1_las = NULL;
uint32_t *count2_las = NULL;

extern volatile int32_t encoder_count;


PID_t   speed_pid, yaw_pid;
State_t speed_state = {0}, yaw_state = {0};

//void Tar_Sp_Cal(State_t *state,uint16_t Tar_Speed,uint16_t Step_calsp);
/**** * xQueueReceive(
            Motor_Queue, 
            &cmd,
            portMAX_DELAY
        );
        */
void DI_Motor_Task(void *pvParameters)
{
   uint32_t count1,count2;
   PID_Init(speed_pid,yaw_pid);

 //  初始化，开四元数120Hz
    while (imu660rc_init(IMU660RC_QUARTERNION_120HZ)) {
        vTaskDelay(pdMS_TO_TICKS(100));
    }

   while (!init_done) {                                                
      vTaskDelay(pdMS_TO_TICKS(10));                                        
   }

    while (1) {

        Tar_Sp_Cal(&speed_state,Tar_Speed,Stepts);  
                                                
        count1 = Encoder_Get();

        count2 = encoder_count;

        int32_t Speed1 = (count1 - *count1_las)/10;       //ci/ms

        int32_t Speed2 = (count2 - *count2_las)/10;

        int32_t Speed_ave = (Speed1 + Speed2) * 0.5;

        *count1_las = count1;
        *count2_las = count2;

    PID_Speed_Cal(&speed_pid, &speed_state, Speed_ave);


        // 角度（度）← INT2中断自动更新
        float yaw   = imu660rc_yaw;     // 航向角 0~360
        //float pitch = imu660rc_pitch;   // 俯仰角 -90~90
        //float roll  = imu660rc_roll;    // 横滚角 -180~180

        /**四元数 ------此处不用
        float q1 = imu660rc_quarternion[0];
        float q2 = imu660rc_quarternion[1];
        float q3 = imu660rc_quarternion[2];
        float q0 = imu660rc_quarternion[3];       
                  
        // 加速度
        int16_t ax = imu660rc_acc_x;
        int16_t ay = imu660rc_acc_y;
        int16_t az = imu660rc_acc_z;
        */

        imu660rc_get_gyro();  // 获取各轴角速度
        float gyro_z = imu660rc_gyro_z;

    PID_Yaw_Cal(&yaw_pid, &yaw_state, yaw, gyro_z);

    int16_t left_pwm  = (int16_t)(speed_state.Output + yaw_state.Output);
    int16_t right_pwm = (int16_t)(speed_state.Output - yaw_state.Output);
     
    if (left_pwm > 1000) {
        left_pwm = 1000;
    }else if (left_pwm < 1000) {
        left_pwm = -1000;
    }

    if (right_pwm > 1000) {
        right_pwm = 1000;
    }else if (right_pwm < 1000) {
        right_pwm = -1000;
    }

    PWM_Set_DI_L(left_pwm);
    PWM_Set_DI_R(right_pwm);

    }
    vTaskDelay(pdMS_TO_TICKS(10));                                       //看一下单位改成大概10ms/次
}


void Tar_Sp_Cal(State_t *state,uint16_t Tar_Speed,uint16_t Step_calsp)     //Tar_Speed 单位 r/ms    Step越小，梯形斜率越陡
{
     uint16_t Speed_aStep = Tar_Speed / Step_calsp ;
     if (state->Target + Speed_aStep < Tar_Speed) {
         state->Target += Speed_aStep;
     }else {
         state->Target = Tar_Speed;
     }

}