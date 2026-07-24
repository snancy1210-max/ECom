#include "ti_msp_dl_config.h"
#include "imu660rc.h"
#include "FreeRTOS.h"
#include "imu_I2C.h"
#include "imu660rc.h"
#include "task.h"

#define IMU660RC_I2C_ADDR   0x6B        //SA0接VCC -> 0x6B    SA0接GND -> 0x6A

static volatile bool g_txDone = false;
static volatile bool g_rxDone = false;
static volatile bool g_i2cError = false;

static uint8_t g_txBuf[32];
static uint8_t g_rxBuf[32];
static uint16_t g_txLen = 0;
static uint16_t g_rxLen = 0;
static uint16_t g_txCount = 0;
static uint16_t g_rxCount = 0;

static volatile enum { MODE_IDLE, MODE_TX, MODE_RX } g_mode = MODE_IDLE;

void I2C_0_INST_IRQHandler(void)
{
    // 检查错误状态
    uint32_t status = DL_I2C_getControllerStatus(I2C_0_INST);
    if (status & DL_I2C_CONTROLLER_STATUS_ERROR) {
        g_i2cError = true;
        g_txDone = true;
        g_rxDone = true;
        return;
    }
    
    switch (DL_I2C_getPendingInterrupt(I2C_0_INST)) {
        case DL_I2C_IIDX_CONTROLLER_TXFIFO_EMPTY:
            if (g_txCount < g_txLen) {
                uint16_t remaining = g_txLen - g_txCount;
                g_txCount += DL_I2C_fillControllerTXFIFO(
                    I2C_0_INST,
                    &g_txBuf[g_txCount],
                    remaining
                );
            }
            break;

        case DL_I2C_IIDX_CONTROLLER_RXFIFO_TRIGGER:
            while (!DL_I2C_isControllerRXFIFOEmpty(I2C_0_INST)) {
                if (g_rxCount < g_rxLen) {
                    g_rxBuf[g_rxCount++] = DL_I2C_receiveControllerData(I2C_0_INST);
                }
            }
            break;

        case DL_I2C_IIDX_CONTROLLER_RX_DONE:
            while (!DL_I2C_isControllerRXFIFOEmpty(I2C_0_INST)) {
                if (g_rxCount < g_rxLen) {
                    g_rxBuf[g_rxCount++] = DL_I2C_receiveControllerData(I2C_0_INST);
                }
            }
            g_rxDone = true;
            break;

        case DL_I2C_IIDX_CONTROLLER_STOP:
            if (g_mode == MODE_TX) {
                g_txDone = true;
            }
            break;

        case DL_I2C_IIDX_CONTROLLER_ARBITRATION_LOST:
        case DL_I2C_IIDX_CONTROLLER_NACK:      
            g_i2cError = true;
            g_txDone = true;
            g_rxDone = true;
            break;

        default:
            break;
    }
}

static bool i2c_wait_done(volatile bool *flag, uint32_t timeout_ms)
{
    TickType_t start = xTaskGetTickCount();
    while (!(*flag)) {
        if (g_i2cError) {
            return false;
        }
        taskYIELD();
        if ((xTaskGetTickCount() - start) > pdMS_TO_TICKS(timeout_ms)) {
            g_i2cError = true;
            return false;
        }
    }
    return true;
}

bool imu660rc_i2c_write_reg(uint8_t reg, uint8_t data)
{
    g_txBuf[0] = reg;
    g_txBuf[1] = data;
    g_txLen = 2;
    g_txCount = 0;
    g_txDone = false;
    g_i2cError = false;
    g_mode = MODE_TX;

    g_txCount = DL_I2C_fillControllerTXFIFO(I2C_0_INST, g_txBuf, g_txLen);

    DL_I2C_startControllerTransfer(
        I2C_0_INST,
        IMU660RC_I2C_ADDR,
        DL_I2C_CONTROLLER_DIRECTION_TX,
        g_txLen
    );

    return i2c_wait_done(&g_txDone, 100);
}

bool imu660rc_i2c_write_regs(uint8_t reg, uint8_t *data, uint8_t len)
{
    if (len > 30) return false;
    g_txBuf[0] = reg;
    memcpy(&g_txBuf[1], data, len);
    g_txLen = 1 + len;
    g_txCount = 0;
    g_txDone = false;
    g_i2cError = false;
    g_mode = MODE_TX;

    g_txCount = DL_I2C_fillControllerTXFIFO(I2C_0_INST, g_txBuf, g_txLen);

    DL_I2C_startControllerTransfer(
        I2C_0_INST,
        IMU660RC_I2C_ADDR,
        DL_I2C_CONTROLLER_DIRECTION_TX,
        g_txLen
    );

    return i2c_wait_done(&g_txDone, 100);
}

uint8_t imu660rc_i2c_read_reg(uint8_t reg)
{
    uint8_t rxData = 0;

    // 写寄存器地址，不发 Stop
    g_txBuf[0] = reg;
    g_txLen = 1;
    g_txCount = 0;
    g_txDone = false;
    g_i2cError = false;
    g_mode = MODE_TX;

    g_txCount = DL_I2C_fillControllerTXFIFO(I2C_0_INST, g_txBuf, g_txLen);

    DL_I2C_startControllerTransferAdvanced(
        I2C_0_INST,
        IMU660RC_I2C_ADDR,
        DL_I2C_CONTROLLER_DIRECTION_TX,
        g_txLen,
        DL_I2C_CONTROLLER_START_ENABLE,
        DL_I2C_CONTROLLER_STOP_DISABLE,
        DL_I2C_CONTROLLER_ACK_ENABLE
    );

    if (!i2c_wait_done(&g_txDone, 100)) {
        return 0;
    }

    // 读数据
    g_rxLen = 1;
    g_rxCount = 0;
    g_rxDone = false;
    g_i2cError = false;
    g_mode = MODE_RX;

    DL_I2C_startControllerTransfer(
        I2C_0_INST,
        IMU660RC_I2C_ADDR,
        DL_I2C_CONTROLLER_DIRECTION_RX,
        g_rxLen
    );

    if (i2c_wait_done(&g_rxDone, 100)) {
        rxData = g_rxBuf[0];
    }

    return rxData;
}

void imu660rc_i2c_read_regs(uint8_t reg, uint8_t *data, uint8_t len)
{
    g_txBuf[0] = reg;
    g_txLen = 1;
    g_txCount = 0;
    g_txDone = false;
    g_i2cError = false;
    g_mode = MODE_TX;

    g_txCount = DL_I2C_fillControllerTXFIFO(I2C_0_INST, g_txBuf, g_txLen);

    DL_I2C_startControllerTransferAdvanced(
        I2C_0_INST,
        IMU660RC_I2C_ADDR,
        DL_I2C_CONTROLLER_DIRECTION_TX,
        g_txLen,
        DL_I2C_CONTROLLER_START_ENABLE,
        DL_I2C_CONTROLLER_STOP_DISABLE,
        DL_I2C_CONTROLLER_ACK_ENABLE
    );

    if (!i2c_wait_done(&g_txDone, 100)) {
        return;
    }

    g_rxLen = len;
    g_rxCount = 0;
    g_rxDone = false;
    g_i2cError = false;
    g_mode = MODE_RX;

    DL_I2C_startControllerTransfer(
        I2C_0_INST,
        IMU660RC_I2C_ADDR,
        DL_I2C_CONTROLLER_DIRECTION_RX,
        g_rxLen
    );

    if (i2c_wait_done(&g_rxDone, 100)) {
        memcpy(data, (void *)g_rxBuf, len);
    }
}

void imu660rc_i2c_init(void)
{
    NVIC_ClearPendingIRQ(I2C_0_INST_INT_IRQN);
    

    NVIC_EnableIRQ(I2C_0_INST_INT_IRQN);
    

    NVIC_SetPriority(I2C_0_INST_INT_IRQN, 2); 
}