#ifndef IMU660RC_H
#define IMU660RC_H

#include <stdint.h>

typedef enum {
    IMU660RC_QUARTERNION_DISABLE = 0,
    IMU660RC_QUARTERNION_30HZ  = 1,
    IMU660RC_QUARTERNION_60HZ  = 2,
    IMU660RC_QUARTERNION_120HZ = 3,
    IMU660RC_QUARTERNION_240HZ = 4,
} imu660rc_quarternion_rate_config;

extern float imu660rc_transition_factor[2];
extern int16_t imu660rc_gyro_x, imu660rc_gyro_y, imu660rc_gyro_z;
extern int16_t imu660rc_acc_x, imu660rc_acc_y, imu660rc_acc_z;
extern float imu660rc_roll, imu660rc_pitch, imu660rc_yaw;
extern float imu660rc_quarternion[4];

uint8_t imu660rc_init(imu660rc_quarternion_rate_config rate);
void imu660rc_get_acc(void);
void imu660rc_get_gyro(void);
void imu660rc_get_quarternion(void);
void imu660rc_int2_callback(void);
void imu660rc_int2_callback(void);

#endif