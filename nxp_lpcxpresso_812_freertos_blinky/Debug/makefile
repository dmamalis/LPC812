################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include freertos/src/subdir.mk
-include example/src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: nxp_lpcxpresso_812_freertos_blinky.axf

# Tool invocations
nxp_lpcxpresso_812_freertos_blinky.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"/home/dmamalis/Iris/LPC812/nxp_lpcxpresso_812_board_lib/Debug" -L"/home/dmamalis/Iris/LPC812/lpc_chip_8xx_lib/Debug" -Xlinker -Map="nxp_lpcxpresso_812_freertos_blinky.map" -Xlinker --gc-sections -mcpu=cortex-m0 -mthumb -T "nxp_lpcxpresso_812_freertos_blinky_Debug.ld" -o "nxp_lpcxpresso_812_freertos_blinky.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) nxp_lpcxpresso_812_freertos_blinky.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "nxp_lpcxpresso_812_freertos_blinky.axf"; # arm-none-eabi-objcopy -O binary "nxp_lpcxpresso_812_freertos_blinky.axf" "nxp_lpcxpresso_812_freertos_blinky.bin" ; checksum -p LPC812 -d "nxp_lpcxpresso_812_freertos_blinky.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
