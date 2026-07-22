#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>
#include "queue.h"

extern QueueHandle_t Motor_DI_Queue;
extern QueueHandle_t Motor_DI2_Queue;

extern volatile uint8_t init_done;



#endif
