################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/acmp_8xx.c \
../src/chip_8xx.c \
../src/clock_8xx.c \
../src/crc_8xx.c \
../src/gpio_8xx.c \
../src/i2c_8xx.c \
../src/iocon_8xx.c \
../src/pinint_8xx.c \
../src/pmu_8xx.c \
../src/ring_buffer.c \
../src/sct_8xx.c \
../src/spi_8xx.c \
../src/swm_8xx.c \
../src/syscon_8xx.c \
../src/sysinit_8xx.c \
../src/uart_8xx.c \
../src/wkt_8xx.c \
../src/wwdt_8xx.c 

OBJS += \
./src/acmp_8xx.o \
./src/chip_8xx.o \
./src/clock_8xx.o \
./src/crc_8xx.o \
./src/gpio_8xx.o \
./src/i2c_8xx.o \
./src/iocon_8xx.o \
./src/pinint_8xx.o \
./src/pmu_8xx.o \
./src/ring_buffer.o \
./src/sct_8xx.o \
./src/spi_8xx.o \
./src/swm_8xx.o \
./src/syscon_8xx.o \
./src/sysinit_8xx.o \
./src/uart_8xx.o \
./src/wkt_8xx.o \
./src/wwdt_8xx.o 

C_DEPS += \
./src/acmp_8xx.d \
./src/chip_8xx.d \
./src/clock_8xx.d \
./src/crc_8xx.d \
./src/gpio_8xx.d \
./src/i2c_8xx.d \
./src/iocon_8xx.d \
./src/pinint_8xx.d \
./src/pmu_8xx.d \
./src/ring_buffer.d \
./src/sct_8xx.d \
./src/spi_8xx.d \
./src/swm_8xx.d \
./src/syscon_8xx.d \
./src/sysinit_8xx.d \
./src/uart_8xx.d \
./src/wkt_8xx.d \
./src/wwdt_8xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -DCORE_M0PLUS -I"D:\Users\dmamalis\Iris\LPC812\lpc_chip_8xx_lib\inc" -Og -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


