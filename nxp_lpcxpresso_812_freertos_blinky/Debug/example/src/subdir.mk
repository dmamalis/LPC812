################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../example/src/cr_startup_lpc8xx.c \
../example/src/crp.c \
../example/src/freertos_blinky.c \
../example/src/mtb.c \
../example/src/sysinit.c 

OBJS += \
./example/src/cr_startup_lpc8xx.o \
./example/src/crp.o \
./example/src/freertos_blinky.o \
./example/src/mtb.o \
./example/src/sysinit.o 

C_DEPS += \
./example/src/cr_startup_lpc8xx.d \
./example/src/crp.d \
./example/src/freertos_blinky.d \
./example/src/mtb.d \
./example/src/sysinit.d 


# Each subdirectory must supply rules for building sources it contributes
example/src/cr_startup_lpc8xx.o: ../example/src/cr_startup_lpc8xx.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M0PLUS -D__MTB_DISABLE -D__MTB_BUFFER_SIZE=512 -I"/home/dmamalis/Iris/LPC812/nxp_lpcxpresso_812_freertos_blinky/example/inc" -I"/home/dmamalis/Iris/LPC812/nxp_lpcxpresso_812_freertos_blinky/freertos/inc" -I"/home/dmamalis/Iris/LPC812/lpc_chip_8xx_lib/inc" -I"/home/dmamalis/Iris/LPC812/nxp_lpcxpresso_812_board_lib/inc" -Os -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"example/src/cr_startup_lpc8xx.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

example/src/%.o: ../example/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_LPCOPEN -DCORE_M0PLUS -D__MTB_DISABLE -D__MTB_BUFFER_SIZE=512 -I"/home/dmamalis/Iris/LPC812/nxp_lpcxpresso_812_freertos_blinky/example/inc" -I"/home/dmamalis/Iris/LPC812/nxp_lpcxpresso_812_freertos_blinky/freertos/inc" -I"/home/dmamalis/Iris/LPC812/lpc_chip_8xx_lib/inc" -I"/home/dmamalis/Iris/LPC812/nxp_lpcxpresso_812_board_lib/inc" -Og -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


