################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/FUSB_CORE/Log.c \
../Drivers/FUSB_CORE/PDPolicy.c \
../Drivers/FUSB_CORE/PDProtocol.c \
../Drivers/FUSB_CORE/Port.c \
../Drivers/FUSB_CORE/TypeC.c \
../Drivers/FUSB_CORE/core.c \
../Drivers/FUSB_CORE/fusb30X.c \
../Drivers/FUSB_CORE/timer.c \
../Drivers/FUSB_CORE/vendor_info.c 

OBJS += \
./Drivers/FUSB_CORE/Log.o \
./Drivers/FUSB_CORE/PDPolicy.o \
./Drivers/FUSB_CORE/PDProtocol.o \
./Drivers/FUSB_CORE/Port.o \
./Drivers/FUSB_CORE/TypeC.o \
./Drivers/FUSB_CORE/core.o \
./Drivers/FUSB_CORE/fusb30X.o \
./Drivers/FUSB_CORE/timer.o \
./Drivers/FUSB_CORE/vendor_info.o 

C_DEPS += \
./Drivers/FUSB_CORE/Log.d \
./Drivers/FUSB_CORE/PDPolicy.d \
./Drivers/FUSB_CORE/PDProtocol.d \
./Drivers/FUSB_CORE/Port.d \
./Drivers/FUSB_CORE/TypeC.d \
./Drivers/FUSB_CORE/core.d \
./Drivers/FUSB_CORE/fusb30X.d \
./Drivers/FUSB_CORE/timer.d \
./Drivers/FUSB_CORE/vendor_info.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/FUSB_CORE/%.o: ../Drivers/FUSB_CORE/%.c Drivers/FUSB_CORE/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DFSC_HAVE_SNK -DFSC_GSCE_FIX -DFSC_HAVE_EXT_MSG -DNUMBER_OF_SNK_PDOS_ENABLED=4 -DDEBUG -DI2C1_TIMEOUT_MAX=0xFFFF -DFSC_POLLING_MODE -DHAL_PCD_MODULE_ENABLED -DPLATFORM_ARM -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver_custom/Inc -I../Drivers/STM32F1xx_HAL_Driver_custom/Src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Drivers/FUSB_CORE -I../Drivers/Platform_ARM/src/USB -I../Drivers/Platform_ARM/src -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/FUSB_CORE/modules -I../Drivers/FUSB_CORE/vdm -I../Drivers/FUSB_CORE/vdm/DisplayPort -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-FUSB_CORE

clean-Drivers-2f-FUSB_CORE:
	-$(RM) ./Drivers/FUSB_CORE/Log.d ./Drivers/FUSB_CORE/Log.o ./Drivers/FUSB_CORE/PDPolicy.d ./Drivers/FUSB_CORE/PDPolicy.o ./Drivers/FUSB_CORE/PDProtocol.d ./Drivers/FUSB_CORE/PDProtocol.o ./Drivers/FUSB_CORE/Port.d ./Drivers/FUSB_CORE/Port.o ./Drivers/FUSB_CORE/TypeC.d ./Drivers/FUSB_CORE/TypeC.o ./Drivers/FUSB_CORE/core.d ./Drivers/FUSB_CORE/core.o ./Drivers/FUSB_CORE/fusb30X.d ./Drivers/FUSB_CORE/fusb30X.o ./Drivers/FUSB_CORE/timer.d ./Drivers/FUSB_CORE/timer.o ./Drivers/FUSB_CORE/vendor_info.d ./Drivers/FUSB_CORE/vendor_info.o

.PHONY: clean-Drivers-2f-FUSB_CORE

