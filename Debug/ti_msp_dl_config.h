/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X
#define CONFIG_MSPM0G3507

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)



#define CPUCLK_FREQ                                                     32000000



/* Defines for PWM_DI */
#define PWM_DI_INST                                                        TIMA0
#define PWM_DI_INST_IRQHandler                                  TIMA0_IRQHandler
#define PWM_DI_INST_INT_IRQN                                    (TIMA0_INT_IRQn)
#define PWM_DI_INST_CLK_FREQ                                            32000000
/* GPIO defines for channel 0 */
#define GPIO_PWM_DI_C0_PORT                                                GPIOB
#define GPIO_PWM_DI_C0_PIN                                         DL_GPIO_PIN_8
#define GPIO_PWM_DI_C0_IOMUX                                     (IOMUX_PINCM25)
#define GPIO_PWM_DI_C0_IOMUX_FUNC                    IOMUX_PINCM25_PF_TIMA0_CCP0
#define GPIO_PWM_DI_C0_IDX                                   DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_PWM_DI_C1_PORT                                                GPIOB
#define GPIO_PWM_DI_C1_PIN                                         DL_GPIO_PIN_9
#define GPIO_PWM_DI_C1_IOMUX                                     (IOMUX_PINCM26)
#define GPIO_PWM_DI_C1_IOMUX_FUNC                    IOMUX_PINCM26_PF_TIMA0_CCP1
#define GPIO_PWM_DI_C1_IDX                                   DL_TIMER_CC_1_INDEX

/* Defines for PWM_Step1 */
#define PWM_Step1_INST                                                     TIMG7
#define PWM_Step1_INST_IRQHandler                               TIMG7_IRQHandler
#define PWM_Step1_INST_INT_IRQN                                 (TIMG7_INT_IRQn)
#define PWM_Step1_INST_CLK_FREQ                                         32000000
/* GPIO defines for channel 0 */
#define GPIO_PWM_Step1_C0_PORT                                             GPIOA
#define GPIO_PWM_Step1_C0_PIN                                     DL_GPIO_PIN_23
#define GPIO_PWM_Step1_C0_IOMUX                                  (IOMUX_PINCM53)
#define GPIO_PWM_Step1_C0_IOMUX_FUNC                 IOMUX_PINCM53_PF_TIMG7_CCP0
#define GPIO_PWM_Step1_C0_IDX                                DL_TIMER_CC_0_INDEX

/* Defines for PWM_Step2 */
#define PWM_Step2_INST                                                    TIMG12
#define PWM_Step2_INST_IRQHandler                              TIMG12_IRQHandler
#define PWM_Step2_INST_INT_IRQN                                (TIMG12_INT_IRQn)
#define PWM_Step2_INST_CLK_FREQ                                         32000000
/* GPIO defines for channel 0 */
#define GPIO_PWM_Step2_C0_PORT                                             GPIOA
#define GPIO_PWM_Step2_C0_PIN                                     DL_GPIO_PIN_14
#define GPIO_PWM_Step2_C0_IOMUX                                  (IOMUX_PINCM36)
#define GPIO_PWM_Step2_C0_IOMUX_FUNC                IOMUX_PINCM36_PF_TIMG12_CCP0
#define GPIO_PWM_Step2_C0_IDX                                DL_TIMER_CC_0_INDEX




/* Defines for QEI_0 */
#define QEI_0_INST                                                         TIMG8
#define QEI_0_INST_IRQHandler                                   TIMG8_IRQHandler
#define QEI_0_INST_INT_IRQN                                     (TIMG8_INT_IRQn)
/* Pin configuration defines for QEI_0 PHA Pin */
#define GPIO_QEI_0_PHA_PORT                                                GPIOB
#define GPIO_QEI_0_PHA_PIN                                         DL_GPIO_PIN_6
#define GPIO_QEI_0_PHA_IOMUX                                     (IOMUX_PINCM23)
#define GPIO_QEI_0_PHA_IOMUX_FUNC                    IOMUX_PINCM23_PF_TIMG8_CCP0
/* Pin configuration defines for QEI_0 PHB Pin */
#define GPIO_QEI_0_PHB_PORT                                                GPIOB
#define GPIO_QEI_0_PHB_PIN                                         DL_GPIO_PIN_7
#define GPIO_QEI_0_PHB_IOMUX                                     (IOMUX_PINCM24)
#define GPIO_QEI_0_PHB_IOMUX_FUNC                    IOMUX_PINCM24_PF_TIMG8_CCP1



/* Defines for I2C_0 */
#define I2C_0_INST                                                          I2C1
#define I2C_0_INST_IRQHandler                                    I2C1_IRQHandler
#define I2C_0_INST_INT_IRQN                                        I2C1_INT_IRQn
#define I2C_0_BUS_SPEED_HZ                                                400000
#define GPIO_I2C_0_SDA_PORT                                                GPIOA
#define GPIO_I2C_0_SDA_PIN                                        DL_GPIO_PIN_16
#define GPIO_I2C_0_IOMUX_SDA                                     (IOMUX_PINCM38)
#define GPIO_I2C_0_IOMUX_SDA_FUNC                      IOMUX_PINCM38_PF_I2C1_SDA
#define GPIO_I2C_0_SCL_PORT                                                GPIOA
#define GPIO_I2C_0_SCL_PIN                                        DL_GPIO_PIN_15
#define GPIO_I2C_0_IOMUX_SCL                                     (IOMUX_PINCM37)
#define GPIO_I2C_0_IOMUX_SCL_FUNC                      IOMUX_PINCM37_PF_I2C1_SCL


/* Defines for UART_0 */
#define UART_0_INST                                                        UART0
#define UART_0_INST_FREQUENCY                                           32000000
#define UART_0_INST_IRQHandler                                  UART0_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOB
#define GPIO_UART_0_TX_PORT                                                GPIOB
#define GPIO_UART_0_RX_PIN                                         DL_GPIO_PIN_1
#define GPIO_UART_0_TX_PIN                                         DL_GPIO_PIN_0
#define GPIO_UART_0_IOMUX_RX                                     (IOMUX_PINCM13)
#define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM12)
#define GPIO_UART_0_IOMUX_RX_FUNC                      IOMUX_PINCM13_PF_UART0_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM12_PF_UART0_TX
#define UART_0_BAUD_RATE                                                (115200)
#define UART_0_IBRD_32_MHZ_115200_BAUD                                      (17)
#define UART_0_FBRD_32_MHZ_115200_BAUD                                      (23)
/* Defines for UART_1 */
#define UART_1_INST                                                        UART1
#define UART_1_INST_FREQUENCY                                           32000000
#define UART_1_INST_IRQHandler                                  UART1_IRQHandler
#define UART_1_INST_INT_IRQN                                      UART1_INT_IRQn
#define GPIO_UART_1_RX_PORT                                                GPIOB
#define GPIO_UART_1_TX_PORT                                                GPIOB
#define GPIO_UART_1_RX_PIN                                         DL_GPIO_PIN_5
#define GPIO_UART_1_TX_PIN                                         DL_GPIO_PIN_4
#define GPIO_UART_1_IOMUX_RX                                     (IOMUX_PINCM18)
#define GPIO_UART_1_IOMUX_TX                                     (IOMUX_PINCM17)
#define GPIO_UART_1_IOMUX_RX_FUNC                      IOMUX_PINCM18_PF_UART1_RX
#define GPIO_UART_1_IOMUX_TX_FUNC                      IOMUX_PINCM17_PF_UART1_TX
#define UART_1_BAUD_RATE                                                (115200)
#define UART_1_IBRD_32_MHZ_115200_BAUD                                      (17)
#define UART_1_FBRD_32_MHZ_115200_BAUD                                      (23)
/* Defines for UART_2 */
#define UART_2_INST                                                        UART2
#define UART_2_INST_FREQUENCY                                           32000000
#define UART_2_INST_IRQHandler                                  UART2_IRQHandler
#define UART_2_INST_INT_IRQN                                      UART2_INT_IRQn
#define GPIO_UART_2_RX_PORT                                                GPIOB
#define GPIO_UART_2_TX_PORT                                                GPIOB
#define GPIO_UART_2_RX_PIN                                        DL_GPIO_PIN_18
#define GPIO_UART_2_TX_PIN                                        DL_GPIO_PIN_17
#define GPIO_UART_2_IOMUX_RX                                     (IOMUX_PINCM44)
#define GPIO_UART_2_IOMUX_TX                                     (IOMUX_PINCM43)
#define GPIO_UART_2_IOMUX_RX_FUNC                      IOMUX_PINCM44_PF_UART2_RX
#define GPIO_UART_2_IOMUX_TX_FUNC                      IOMUX_PINCM43_PF_UART2_TX
#define UART_2_BAUD_RATE                                                (115200)
#define UART_2_IBRD_32_MHZ_115200_BAUD                                      (17)
#define UART_2_FBRD_32_MHZ_115200_BAUD                                      (23)
/* Defines for UART_3 */
#define UART_3_INST                                                        UART3
#define UART_3_INST_FREQUENCY                                           32000000
#define UART_3_INST_IRQHandler                                  UART3_IRQHandler
#define UART_3_INST_INT_IRQN                                      UART3_INT_IRQn
#define GPIO_UART_3_RX_PORT                                                GPIOB
#define GPIO_UART_3_TX_PORT                                                GPIOB
#define GPIO_UART_3_RX_PIN                                        DL_GPIO_PIN_13
#define GPIO_UART_3_TX_PIN                                        DL_GPIO_PIN_12
#define GPIO_UART_3_IOMUX_RX                                     (IOMUX_PINCM30)
#define GPIO_UART_3_IOMUX_TX                                     (IOMUX_PINCM29)
#define GPIO_UART_3_IOMUX_RX_FUNC                      IOMUX_PINCM30_PF_UART3_RX
#define GPIO_UART_3_IOMUX_TX_FUNC                      IOMUX_PINCM29_PF_UART3_TX
#define UART_3_BAUD_RATE                                                (115200)
#define UART_3_IBRD_32_MHZ_115200_BAUD                                      (17)
#define UART_3_FBRD_32_MHZ_115200_BAUD                                      (23)





/* Port definition for Pin Group GPIO_GRP_QEIA */
#define GPIO_GRP_QEIA_PORT                                               (GPIOA)

/* Defines for PIN_0: GPIOA.12 with pinCMx 34 on package pin 5 */
// groups represented: ["GPIO_GRP_QEIB","GPIO_GRP_int2","GPIO_GRP_QEIA"]
// pins affected: ["PIN_1","Int2","PIN_0"]
#define GPIO_MULTIPLE_GPIOA_INT_IRQN                            (GPIOA_INT_IRQn)
#define GPIO_MULTIPLE_GPIOA_INT_IIDX            (DL_INTERRUPT_GROUP1_IIDX_GPIOA)
#define GPIO_GRP_QEIA_PIN_0_IIDX                            (DL_GPIO_IIDX_DIO12)
#define GPIO_GRP_QEIA_PIN_0_PIN                                 (DL_GPIO_PIN_12)
#define GPIO_GRP_QEIA_PIN_0_IOMUX                                (IOMUX_PINCM34)
/* Port definition for Pin Group GPIO_GRP_QEIB */
#define GPIO_GRP_QEIB_PORT                                               (GPIOA)

/* Defines for PIN_1: GPIOA.13 with pinCMx 35 on package pin 6 */
#define GPIO_GRP_QEIB_PIN_1_IIDX                            (DL_GPIO_IIDX_DIO13)
#define GPIO_GRP_QEIB_PIN_1_PIN                                 (DL_GPIO_PIN_13)
#define GPIO_GRP_QEIB_PIN_1_IOMUX                                (IOMUX_PINCM35)
/* Port definition for Pin Group GPIO_INFR_L1 */
#define GPIO_INFR_L1_PORT                                                (GPIOA)

/* Defines for PIN_2: GPIOA.22 with pinCMx 47 on package pin 18 */
#define GPIO_INFR_L1_PIN_2_PIN                                  (DL_GPIO_PIN_22)
#define GPIO_INFR_L1_PIN_2_IOMUX                                 (IOMUX_PINCM47)
/* Port definition for Pin Group GPIO_INFR_R1 */
#define GPIO_INFR_R1_PORT                                                (GPIOA)

/* Defines for PIN_3: GPIOA.27 with pinCMx 60 on package pin 31 */
#define GPIO_INFR_R1_PIN_3_PIN                                  (DL_GPIO_PIN_27)
#define GPIO_INFR_R1_PIN_3_IOMUX                                 (IOMUX_PINCM60)
/* Port definition for Pin Group GPIO_GRP_int2 */
#define GPIO_GRP_int2_PORT                                               (GPIOA)

/* Defines for Int2: GPIOA.0 with pinCMx 1 on package pin 33 */
#define GPIO_GRP_int2_Int2_IIDX                              (DL_GPIO_IIDX_DIO0)
#define GPIO_GRP_int2_Int2_PIN                                   (DL_GPIO_PIN_0)
#define GPIO_GRP_int2_Int2_IOMUX                                  (IOMUX_PINCM1)
/* Port definition for Pin Group GPIO_INFR_L2 */
#define GPIO_INFR_L2_PORT                                                (GPIOB)

/* Defines for PIN_4: GPIOB.24 with pinCMx 52 on package pin 23 */
#define GPIO_INFR_L2_PIN_4_PIN                                  (DL_GPIO_PIN_24)
#define GPIO_INFR_L2_PIN_4_IOMUX                                 (IOMUX_PINCM52)
/* Port definition for Pin Group GPIO_INFR_L3 */
#define GPIO_INFR_L3_PORT                                                (GPIOA)

/* Defines for PIN_5: GPIOA.24 with pinCMx 54 on package pin 25 */
#define GPIO_INFR_L3_PIN_5_PIN                                  (DL_GPIO_PIN_24)
#define GPIO_INFR_L3_PIN_5_IOMUX                                 (IOMUX_PINCM54)
/* Port definition for Pin Group GPIO_INFR_L4 */
#define GPIO_INFR_L4_PORT                                                (GPIOA)

/* Defines for PIN_6: GPIOA.26 with pinCMx 59 on package pin 30 */
#define GPIO_INFR_L4_PIN_6_PIN                                  (DL_GPIO_PIN_26)
#define GPIO_INFR_L4_PIN_6_IOMUX                                 (IOMUX_PINCM59)
/* Port definition for Pin Group GPIO_INFR_R2 */
#define GPIO_INFR_R2_PORT                                                (GPIOA)

/* Defines for PIN_7: GPIOA.25 with pinCMx 55 on package pin 26 */
#define GPIO_INFR_R2_PIN_7_PIN                                  (DL_GPIO_PIN_25)
#define GPIO_INFR_R2_PIN_7_IOMUX                                 (IOMUX_PINCM55)
/* Port definition for Pin Group GPIO_INFR_R3 */
#define GPIO_INFR_R3_PORT                                                (GPIOB)

/* Defines for PIN_8: GPIOB.25 with pinCMx 56 on package pin 27 */
#define GPIO_INFR_R3_PIN_8_PIN                                  (DL_GPIO_PIN_25)
#define GPIO_INFR_R3_PIN_8_IOMUX                                 (IOMUX_PINCM56)
/* Port definition for Pin Group GPIO_INFR_R4 */
#define GPIO_INFR_R4_PORT                                                (GPIOB)

/* Defines for PIN_9: GPIOB.20 with pinCMx 48 on package pin 19 */
#define GPIO_INFR_R4_PIN_9_PIN                                  (DL_GPIO_PIN_20)
#define GPIO_INFR_R4_PIN_9_IOMUX                                 (IOMUX_PINCM48)


/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_PWM_DI_init(void);
void SYSCFG_DL_PWM_Step1_init(void);
void SYSCFG_DL_PWM_Step2_init(void);
void SYSCFG_DL_QEI_0_init(void);
void SYSCFG_DL_I2C_0_init(void);
void SYSCFG_DL_UART_0_init(void);
void SYSCFG_DL_UART_1_init(void);
void SYSCFG_DL_UART_2_init(void);
void SYSCFG_DL_UART_3_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
