################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-225427105: ../E-Competition.syscfg
	@echo 'SysConfig - building file: "$<"'
	"D:/study_software/ti/ccs/utils/sysconfig_1.27.1/sysconfig_cli.bat" -s "D:/study_software/ti/mspm0_sdk_2_11_00_07/.metadata/product.json" --script "C:/Users/shinanxi/workspace_ccstheia/E-Competition/E-Competition.syscfg" -o "." --compiler ticlang
	@echo 'Finished building: "$<"'
	@echo ' '

ti_msp_dl_config.c: build-225427105 ../E-Competition.syscfg
ti_msp_dl_config.h: build-225427105
Event.dot: build-225427105

%.o: ./%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Arm Compiler - building file: "$<"'
	"D:/study_software/ti/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"C:/Users/shinanxi/workspace_ccstheia/E-Competition" -I"C:/Users/shinanxi/workspace_ccstheia/E-Competition/Debug" -I"D:/study_software/ti/mspm0_sdk_2_11_00_07/source/third_party/CMSIS/Core/Include" -I"D:/study_software/ti/mspm0_sdk_2_11_00_07/kernel/freertos/Source/include" -I"D:/study_software/ti/mspm0_sdk_2_11_00_07/source" -I"D:/study_software/ti/mspm0_sdk_2_11_00_07/kernel/freertos/Source/portable/TI_ARM_CLANG/ARM_CM0" -I"D:/study_software/ti/mspm0_sdk_2_11_00_07/source/ti/posix/ticlang" -I"C:/Users/shinanxi/workspace_ccstheia/freertos_builds_LP_MSPM0G3507_release_ticlang" -I"C:/Users/shinanxi/workspace_ccstheia/E-Competition/Driver" -I"C:/Users/shinanxi/workspace_ccstheia/E-Competition/targetConfigs" -I"C:/Users/shinanxi/workspace_ccstheia/E-Competition/Body_task" -I"C:/Users/shinanxi/workspace_ccstheia/E-Competition/SEGGER" -D__MSPM0G3507__ -g -Wall -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Arm Compiler - building file: "$<"'
	"D:/study_software/ti/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"C:/Users/shinanxi/workspace_ccstheia/E-Competition" -I"C:/Users/shinanxi/workspace_ccstheia/E-Competition/Debug" -I"D:/study_software/ti/mspm0_sdk_2_11_00_07/source/third_party/CMSIS/Core/Include" -I"D:/study_software/ti/mspm0_sdk_2_11_00_07/kernel/freertos/Source/include" -I"D:/study_software/ti/mspm0_sdk_2_11_00_07/source" -I"D:/study_software/ti/mspm0_sdk_2_11_00_07/kernel/freertos/Source/portable/TI_ARM_CLANG/ARM_CM0" -I"D:/study_software/ti/mspm0_sdk_2_11_00_07/source/ti/posix/ticlang" -I"C:/Users/shinanxi/workspace_ccstheia/freertos_builds_LP_MSPM0G3507_release_ticlang" -I"C:/Users/shinanxi/workspace_ccstheia/E-Competition/Driver" -I"C:/Users/shinanxi/workspace_ccstheia/E-Competition/targetConfigs" -I"C:/Users/shinanxi/workspace_ccstheia/E-Competition/Body_task" -I"C:/Users/shinanxi/workspace_ccstheia/E-Competition/SEGGER" -D__MSPM0G3507__ -g -Wall -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


