#include "ti_msp_dl_config.h"
#include "imu_I2C.h"
#include "imu660rc.h"
#include "FreeRTOS.h"
#include "task.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.1415926f
#endif

/* ========== 寄存器定义 ========== */
#define IMU660RC_CHIP_ID            0x0F
#define IMU660RC_FUNC_CFG_ACCESS    0x01
#define IMU660RC_CTRL1              0x10
#define IMU660RC_CTRL2              0x11
#define IMU660RC_CTRL3              0x12
#define IMU660RC_CTRL4              0x13
#define IMU660RC_CTRL6              0x15
#define IMU660RC_CTRL7              0x16
#define IMU660RC_CTRL8              0x17
#define IMU660RC_CTRL9              0x18
#define IMU660RC_INT2_CTRL          0x0E
#define IMU660RC_FIFO_CRTL1         0x07
#define IMU660RC_FIFO_CRTL4         0x0A
#define IMU660RC_OUTX_L_A           0x28
#define IMU660RC_OUTX_L_G           0x22
#define IMU660RC_PAGE_RW            0x17
#define IMU660RC_PAGE_SEL           0x02
#define IMU660RC_EMB_FUNC_FIFO_EN_A 0x44
#define IMU660RC_SFLP_ODR           0x5E
#define IMU660RC_EMB_FUNC_EN_A      0x04
#define IMU660RC_TIMEOUT_COUNT      1000

/* 宏替换 */
#define imu660rc_write_register(reg, data)      imu660rc_i2c_write_reg((reg), (data))
#define imu660rc_write_registers(reg, data, len) imu660rc_i2c_write_regs((reg), (data), (len))
#define imu660rc_read_register(reg)             imu660rc_i2c_read_reg((reg))
#define imu660rc_read_registers(reg, data, len)  imu660rc_i2c_read_regs((reg), (data), (len))

/* ========== 全局变量 ========== */
float imu660rc_transition_factor[2];
int16_t imu660rc_gyro_x = 0, imu660rc_gyro_y = 0, imu660rc_gyro_z = 0;
int16_t imu660rc_acc_x  = 0, imu660rc_acc_y  = 0, imu660rc_acc_z  = 0;
float imu660rc_roll = 0, imu660rc_pitch = 0, imu660rc_yaw = 0;
float imu660rc_quarternion[4];

static uint8_t imu660rc_quarternion_rate;

typedef enum {
    IMU660RC_MAIN_MEM_BANK = 0x00,
    IMU660RC_EMBED_MEM_BANK = 0x80,
} imu660rc_mem_bank_enum;



static uint32_t fp16_to_float(uint16_t h)
{
    uint16_t h_exp = (h & 0x7c00u);
    uint32_t f_sgn = ((uint32_t)h & 0x8000u) << 16;
    switch (h_exp) {
        case 0x0000u: {
            uint16_t h_sig = (h & 0x03ffu);
            if (h_sig == 0) return f_sgn;
            h_sig <<= 1;
            while ((h_sig & 0x0400u) == 0) {
                h_sig <<= 1;
                h_exp++;
            }
            uint32_t f_exp = ((uint32_t)(127 - 15 - h_exp)) << 23;
            uint32_t f_sig = ((uint32_t)(h_sig & 0x03ffu)) << 13;
            return f_sgn + f_exp + f_sig;
        }
        case 0x7c00u:
            return f_sgn + 0x7f800000u + (((uint32_t)(h & 0x03ffu)) << 13);
        default:
            return f_sgn + (((uint32_t)(h & 0x7fffu) + 0x1c000u) << 13);
    }
}

static void quarternion_normalize(float quat[4], uint16_t *fp16)
{
    float n = 0;
    float temp[4];
    *(uint32_t *)(&temp[0]) = fp16_to_float(fp16[0]);
    *(uint32_t *)(&temp[1]) = fp16_to_float(fp16[1]);
    *(uint32_t *)(&temp[2]) = fp16_to_float(fp16[2]);
    *(uint32_t *)(&temp[3]) = fp16_to_float(fp16[3]);
    n = temp[0]*temp[0] + temp[1]*temp[1] + temp[2]*temp[2] + temp[3]*temp[3];
    n = sqrtf(n);
    if (n > 0.001f) {
        n = temp[3] < 0.0f ? -n : n;
        quat[0] = temp[1] / n;
        quat[1] = temp[2] / n;
        quat[2] = temp[0] / n;
        quat[3] = temp[3] / n;
    }
}

static void quarternion_to_euler(float quat[4], float *roll, float *pitch, float *yaw)     //欧拉角解算
{
    float sqx = quat[0] * quat[0];
    float sqy = quat[1] * quat[1];
    float sqz = quat[2] * quat[2];
    float euler[3];
    euler[0] = atan2f(2.0f * (quat[1]*quat[3] + quat[0]*quat[2]), 1.0f - 2.0f*(sqy + sqx));
    euler[1] = -asinf(2.0f * (quat[0]*quat[3] - quat[1]*quat[2]));
    euler[2] = atan2f(2.0f * (quat[0]*quat[1] + quat[2]*quat[3]), 1.0f - 2.0f*(sqx + sqz));
    euler[0] = 180 * euler[0] / M_PI;
    euler[1] = 180 * euler[1] / M_PI;
    euler[2] = 180 * euler[2] / M_PI;
    euler[2] = (0 > euler[2]) ? euler[2] + 360 : euler[2];
    *roll = euler[0];
    *pitch = euler[1];
    *yaw = euler[2];
}

static void imu660rc_set_mem_bank(imu660rc_mem_bank_enum bank)
{
    imu660rc_write_register(IMU660RC_FUNC_CFG_ACCESS, bank);
}

static uint8_t imu660rc_self_check(void)
{
    uint8_t dat = 0;
    uint16_t timeout_count = 0;
    do {
        if (IMU660RC_TIMEOUT_COUNT < timeout_count++) {
            return 1;
        }
        dat = imu660rc_read_register(IMU660RC_CHIP_ID);
        vTaskDelay(pdMS_TO_TICKS(1));
    } while (0x70 != dat);
    return 0;
}

void imu660rc_get_acc(void)
{
    int16_t dat[3];
    if (0 == imu660rc_quarternion_rate) {
        imu660rc_read_registers(IMU660RC_OUTX_L_A, (uint8_t *)dat, 6);
        imu660rc_acc_x = dat[0];
        imu660rc_acc_y = dat[1];
        imu660rc_acc_z = dat[2];
    }
}

void imu660rc_get_gyro(void)
{
    int16_t dat[3];
    if (0 == imu660rc_quarternion_rate) {
        imu660rc_read_registers(IMU660RC_OUTX_L_G, (uint8_t *)dat, 6);
        imu660rc_gyro_x = dat[0];
        imu660rc_gyro_y = dat[1];
        imu660rc_gyro_z = dat[2];
    }
}

void imu660rc_get_quarternion(void)
{
    uint8_t i;
    uint16_t buff[4];
    uint8_t *buff1_ptr;
    int16_t *buff2_ptr;

    if (0 != imu660rc_quarternion_rate) {
        buff1_ptr = (uint8_t *)buff;

        imu660rc_set_mem_bank(IMU660RC_EMBED_MEM_BANK);
        imu660rc_write_register(IMU660RC_PAGE_RW, 0x20);
        imu660rc_write_register(IMU660RC_PAGE_SEL, 0x31);

        for (i = 0; i < 8; i++) {
            imu660rc_write_register(0x08, 0x4C + i);
            buff1_ptr[i] = imu660rc_read_register(0x09);
        }

        imu660rc_write_register(IMU660RC_PAGE_RW, 0x0);
        imu660rc_set_mem_bank(IMU660RC_MAIN_MEM_BANK);

        quarternion_normalize(imu660rc_quarternion, buff);
        quarternion_to_euler(imu660rc_quarternion, &imu660rc_roll, &imu660rc_pitch, &imu660rc_yaw);

        buff2_ptr = (int16_t *)buff;
        imu660rc_read_registers(IMU660RC_OUTX_L_A, (uint8_t *)buff2_ptr, 6);
        imu660rc_acc_x = buff2_ptr[0];
        imu660rc_acc_y = buff2_ptr[1];
        imu660rc_acc_z = buff2_ptr[2];
    }
}

void imu660rc_int2_callback(void)
{
    imu660rc_get_quarternion();
}

uint8_t imu660rc_init(imu660rc_quarternion_rate_config quarternion_rate)
{
    uint8_t return_state = 0;
    imu660rc_quarternion_rate = quarternion_rate;

    vTaskDelay(pdMS_TO_TICKS(10));

    imu660rc_read_register(IMU660RC_CHIP_ID);

    do {
        if (imu660rc_self_check()) {
            return_state = 1;
            break;
        }

        imu660rc_write_register(IMU660RC_FUNC_CFG_ACCESS, 0x04);
        vTaskDelay(pdMS_TO_TICKS(30));

        imu660rc_write_register(IMU660RC_CTRL3, 0x44);

        imu660rc_write_register(IMU660RC_CTRL8, 0x00);
        imu660rc_transition_factor[0] = 16393.44f;

        imu660rc_write_register(IMU660RC_CTRL6, 0x01);
        imu660rc_transition_factor[1] = 114.2857f;

        imu660rc_write_register(IMU660RC_CTRL1, 0x15);
        imu660rc_write_register(IMU660RC_CTRL2, 0x18);

        imu660rc_write_register(IMU660RC_CTRL7, 0x01);
        imu660rc_write_register(IMU660RC_CTRL9, 0x08);

        if (0 != quarternion_rate) {
            imu660rc_write_register(IMU660RC_FIFO_CRTL1, 0x01);
            imu660rc_write_register(IMU660RC_FIFO_CRTL4, 0x06);
            imu660rc_write_register(IMU660RC_INT2_CTRL, 0x80);
            imu660rc_write_register(IMU660RC_CTRL4, 0x08);

            imu660rc_write_register(IMU660RC_CTRL1, 0x10 | (quarternion_rate + 3));
            imu660rc_write_register(IMU660RC_CTRL2, 0x10 | (quarternion_rate + 3));

            imu660rc_set_mem_bank(IMU660RC_EMBED_MEM_BANK);
            imu660rc_write_register(IMU660RC_EMB_FUNC_FIFO_EN_A, 0x02);
            imu660rc_write_register(IMU660RC_SFLP_ODR, 0x43 | (quarternion_rate << 3));
            imu660rc_write_register(IMU660RC_EMB_FUNC_EN_A, 0x02);
            imu660rc_write_register(IMU660RC_PAGE_RW, 0x00);
            imu660rc_set_mem_bank(IMU660RC_MAIN_MEM_BANK);

        }

    } while (0);

    return return_state;
}


/****** 中断读取四元数放在了Encoder.c
void GROUP1_IRQHandler(void)
{
    // 检查是哪个引脚触发
    uint32_t gpioA = DL_GPIO_getEnabledInterruptStatus(GPIOA, 0xFFFF);
    
    if (gpioA & DL_GPIO_PIN_0) {  // PA0 触发
        imu660rc_int2_callback();  // 读四元数
        DL_GPIO_clearInterruptStatus(GPIOA, DL_GPIO_PIN_0);
    }
}

*/