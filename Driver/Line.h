#ifndef LINE_H
#define LINE_H



typedef struct
{
    uint8_t sensor[8];    // 八路红外状态
    float error;         // 加权后的误差

}Line_t;

void Line_Update(void);


#endif