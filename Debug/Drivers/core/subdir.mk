################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/core/Log.c \
../Drivers/core/PDPolicy.c \
../Drivers/core/PDProtocol.c \
../Drivers/core/Port.c \
../Drivers/core/TypeC.c \
../Drivers/core/core.c \
../Drivers/core/fusb30X.c \
../Drivers/core/timer.c \
../Drivers/core/vendor_info.c 

OBJS += \
./Drivers/core/Log.o \
./Drivers/core/PDPolicy.o \
./Drivers/core/PDProtocol.o \
./Drivers/core/Port.o \
./Drivers/core/TypeC.o \
./Drivers/core/core.o \
./Drivers/core/fusb30X.o \
./Drivers/core/timer.o \
./Drivers/core/vendor_info.o 

C_DEPS += \
./Drivers/core/Log.d \
./Drivers/core/PDPolicy.d \
./Drivers/core/PDProtocol.d \
./Drivers/core/Port.d \
./Drivers/core/TypeC.d \
./Drivers/core/core.d \
./Drivers/core/fusb30X.d \
./Drivers/core/timer.d \
./Drivers/core/vendor_info.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/core/%.o: ../Drivers/core/%.c Drivers/core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DPLATFORM_ARM -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Drivers/core -I../Drivers/Platform_ARM/src/USB -I../Drivers/Platform_ARM/src -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/core/modules -I../Drivers/core/vdm -I../Drivers/core/vdm/DisplayPort -I../Drivers/core/modules -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-core

clean-Drivers-2f-core:
	-$(RM) ./Drivers/core/Log.d ./Drivers/core/Log.o ./Drivers/core/PDPolicy.d ./Drivers/core/PDPolicy.o ./Drivers/core/PDProtocol.d ./Drivers/core/PDProtocol.o ./Drivers/core/Port.d ./Drivers/core/Port.o ./Drivers/core/TypeC.d ./Drivers/core/TypeC.o ./Drivers/core/core.d ./Drivers/core/core.o ./Drivers/core/fusb30X.d ./Drivers/core/fusb30X.o ./Drivers/core/timer.d ./Drivers/core/timer.o ./Drivers/core/vendor_info.d ./Drivers/core/vendor_info.o

.PHONY: clean-Drivers-2f-core

