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
#include "Line.h"
#include "ti_msp_dl_config.h"

LinePD_t line_pd =
{
    .kp = 6.0f,
    .kd = 2.0f,
};

Line_t line;


void Line_Update(void)          //基于黑线1白底0
{
    line.sensor[0] = DL_GPIO_readPins(GPIOA, DL_GPIO_PIN_26) ? 1 : 0;
    line.sensor[1] = DL_GPIO_readPins(GPIOA, DL_GPIO_PIN_24) ? 1 : 0;
    line.sensor[2] = DL_GPIO_readPins(GPIOB, DL_GPIO_PIN_24) ? 1 : 0;
    line.sensor[3] = DL_GPIO_readPins(GPIOA, DL_GPIO_PIN_22) ? 1 : 0;
    line.sensor[4] = DL_GPIO_readPins(GPIOA, DL_GPIO_PIN_27) ? 1 : 0;
    line.sensor[5] = DL_GPIO_readPins(GPIOA, DL_GPIO_PIN_25) ? 1 : 0;
    line.sensor[6] = DL_GPIO_readPins(GPIOB, DL_GPIO_PIN_25) ? 1 : 0;
    line.sensor[7] = DL_GPIO_readPins(GPIOB, DL_GPIO_PIN_20) ? 1 : 0;

    static const int weight[8]={-7,-5,-3,-1,1,3,5,7};

    int sum=0;
    int cnt=0;

    for(int i=0;i<8;i++)
    {
        if(line.sensor[i])
        {
            sum+=weight[i];
            cnt++;
        }
    }

    if(cnt==0)
        line.error=0;
    else
        line.error=(float)sum/cnt;          //左负右正，触发哪边就往哪边纠正
}