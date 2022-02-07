################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/core/modules/HostComm.c \
../Drivers/core/modules/dpm.c \
../Drivers/core/modules/observer.c 

OBJS += \
./Drivers/core/modules/HostComm.o \
./Drivers/core/modules/dpm.o \
./Drivers/core/modules/observer.o 

C_DEPS += \
./Drivers/core/modules/HostComm.d \
./Drivers/core/modules/dpm.d \
./Drivers/core/modules/observer.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/core/modules/%.o: ../Drivers/core/modules/%.c Drivers/core/modules/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DPLATFORM_ARM -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Drivers/core -I../Drivers/Platform_ARM/src/USB -I../Drivers/Platform_ARM/src -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/core/modules -I../Drivers/core/vdm -I../Drivers/core/vdm/DisplayPort -I../Drivers/core/modules -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-core-2f-modules

clean-Drivers-2f-core-2f-modules:
	-$(RM) ./Drivers/core/modules/HostComm.d ./Drivers/core/modules/HostComm.o ./Drivers/core/modules/dpm.d ./Drivers/core/modules/dpm.o ./Drivers/core/modules/observer.d ./Drivers/core/modules/observer.o

.PHONY: clean-Drivers-2f-core-2f-modules

