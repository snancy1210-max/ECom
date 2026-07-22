#ifndef PID_H
#define PID_H

typedef struct
{
    float kp;
    float ki;
    float kd;

    float IntegralK;             //变速积分参数，K越小，error积分阈值越大越容易积分
    float alpha;         //滤波系数，越大越相信新值，1没滤波，一般0.2,范围0-1

   
    float MaxOutput;

}PID_t;

typedef struct
{
    float Target;    
    float Speed_f;     //滤波后
    float Speed_f_last;
    float Speed_f_lastlast;
    float error;
    float error_last;

    float Output;
    
}State_t;

void PID_Cal(PID_t *pid,State_t *state,float Speed);

#endif



