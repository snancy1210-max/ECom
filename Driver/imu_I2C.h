#ifndef IMU_I2C_H
#define IMU_I2C_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

void imu660rc_i2c_init(void);
bool imu660rc_i2c_write_reg(uint8_t reg, uint8_t data);
bool imu660rc_i2c_write_regs(uint8_t reg, uint8_t *data, uint8_t len);
uint8_t imu660rc_i2c_read_reg(uint8_t reg);
void imu660rc_i2c_read_regs(uint8_t reg, uint8_t *data, uint8_t len);

#endif