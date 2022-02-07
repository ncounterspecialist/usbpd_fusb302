################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/core/vdm/bitfield_translators.c \
../Drivers/core/vdm/vdm.c \
../Drivers/core/vdm/vdm_callbacks.c 

OBJS += \
./Drivers/core/vdm/bitfield_translators.o \
./Drivers/core/vdm/vdm.o \
./Drivers/core/vdm/vdm_callbacks.o 

C_DEPS += \
./Drivers/core/vdm/bitfield_translators.d \
./Drivers/core/vdm/vdm.d \
./Drivers/core/vdm/vdm_callbacks.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/core/vdm/%.o: ../Drivers/core/vdm/%.c Drivers/core/vdm/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DPLATFORM_ARM -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Drivers/core -I../Drivers/Platform_ARM/src/USB -I../Drivers/Platform_ARM/src -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/core/modules -I../Drivers/core/vdm -I../Drivers/core/vdm/DisplayPort -I../Drivers/core/modules -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-core-2f-vdm

clean-Drivers-2f-core-2f-vdm:
	-$(RM) ./Drivers/core/vdm/bitfield_translators.d ./Drivers/core/vdm/bitfield_translators.o ./Drivers/core/vdm/vdm.d ./Drivers/core/vdm/vdm.o ./Drivers/core/vdm/vdm_callbacks.d ./Drivers/core/vdm/vdm_callbacks.o

.PHONY: clean-Drivers-2f-core-2f-vdm

