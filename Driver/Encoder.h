#ifndef ENCODER_H
#define ENCODER_H

volatile int32_t encoder_count;

uint8_t Encoder_Read_AB(void);
int32_t Encoder_Get(void);
void GROUP1_IRQHandler(void);

extern volatile int32_t encoder_count;
extern uint8_t last_AB_state;

#endif