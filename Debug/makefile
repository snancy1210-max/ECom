################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/study_software/ti/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./ti_msp_dl_config.o" \
"./main-blinky.o" \
"./main.o" \
"./Body_task/DIMotor.o" \
"./Body_task/StepMotor.o" \
"./Body_task/UART.o" \
"./Driver/Encoder.o" \
"./Driver/Line.o" \
"./Driver/PID.o" \
"./Driver/PWM.o" \
"./Driver/imu660rc.o" \
"./Driver/imu_I2C.o" \
"./SEGGER/SEGGER_RTT.o" \
"./SEGGER/SEGGER_RTT_printf.o" \
"./freertos/ticlang/startup_mspm0g350x_ticlang.o" \
"../mspm0g3507.cmd" \
$(GEN_CMDS__FLAG) \
-Wl,-lfreertos_builds_LP_MSPM0G3507_release_ticlang.lib \
-Wl,-l"D:/study_software/ti/mspm0_sdk_2_11_00_07/source/ti/driverlib/lib/ticlang/m0p/mspm0g1x0x_g3x0x/driverlib.a" \
-Wl,-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include Body_task/subdir_vars.mk
-include Driver/subdir_vars.mk
-include SEGGER/subdir_vars.mk
-include freertos/ticlang/subdir_vars.mk
-include subdir_rules.mk
-include Body_task/subdir_rules.mk
-include Driver/subdir_rules.mk
-include SEGGER/subdir_rules.mk
-include freertos/ticlang/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
blink_led.out 

EXE_OUTPUTS__QUOTED += \
"blink_led.out" 


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "blink_led.out"

dependents:
	-cd C:/Users/shinanxi/workspace_ccstheia/freertos_builds_LP_MSPM0G3507_release_ticlang/Debug && $(MAKE) all

# Tool invocations
blink_led.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS) C:/Users/shinanxi/workspace_ccstheia/freertos_builds_LP_MSPM0G3507_release_ticlang/Debug/freertos_builds_LP_MSPM0G3507_release_ticlang.lib
	@echo 'Arm Linker - building target: "$@"'
	"D:/study_software/ti/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -D__MSPM0G3507__ -g -Wall -Wl,-m"blink_led.map" -Wl,-i"C:/Users/shinanxi/workspace_ccstheia/freertos_builds_LP_MSPM0G3507_release_ticlang/Debug" -Wl,-i"D:/study_software/ti/mspm0_sdk_2_11_00_07/source" -Wl,-i"C:/Users/shinanxi/workspace_ccstheia/E-Competition" -Wl,-i"C:/Users/shinanxi/workspace_ccstheia/E-Competition/Debug/syscfg" -Wl,-i"D:/study_software/ti/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/lib" -Wl,--diag_wrap=off -Wl,--display_error_number -Wl,--warn_sections -Wl,--xml_link_info="blink_led_linkInfo.xml" -Wl,--rom_model -o "blink_led.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(GEN_MISC_FILES__QUOTED)$(GEN_FILES__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "ti_msp_dl_config.o" "main-blinky.o" "main.o" "Body_task\DIMotor.o" "Body_task\StepMotor.o" "Body_task\UART.o" "Driver\Encoder.o" "Driver\Line.o" "Driver\PID.o" "Driver\PWM.o" "Driver\imu660rc.o" "Driver\imu_I2C.o" "SEGGER\SEGGER_RTT.o" "SEGGER\SEGGER_RTT_printf.o" "freertos\ticlang\startup_mspm0g350x_ticlang.o" 
	-$(RM) "ti_msp_dl_config.d" "main-blinky.d" "main.d" "Body_task\DIMotor.d" "Body_task\StepMotor.d" "Body_task\UART.d" "Driver\Encoder.d" "Driver\Line.d" "Driver\PID.d" "Driver\PWM.d" "Driver\imu660rc.d" "Driver\imu_I2C.d" "SEGGER\SEGGER_RTT.d" "SEGGER\SEGGER_RTT_printf.d" "freertos\ticlang\startup_mspm0g350x_ticlang.d" 
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
C:/Users/shinanxi/workspace_ccstheia/freertos_builds_LP_MSPM0G3507_release_ticlang/Debug/freertos_builds_LP_MSPM0G3507_release_ticlang.lib:

-include ../makefile.targets

