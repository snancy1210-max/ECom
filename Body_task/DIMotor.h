#ifndef DIMOTOR_H
#define DIMOTOR_H


void DI_Motor_Task(void *pvParameters);

void Tar_Sp_Cal(State_t *state,uint16_t Tar_Speed,uint16_t Step_calsp,float current);


#endif