################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Platform_ARM/src/USB/usbd_conf.c \
../Drivers/Platform_ARM/src/USB/usbd_desc.c \
../Drivers/Platform_ARM/src/USB/usbd_hid.c \
../Drivers/Platform_ARM/src/USB/usbd_main.c 

OBJS += \
./Drivers/Platform_ARM/src/USB/usbd_conf.o \
./Drivers/Platform_ARM/src/USB/usbd_desc.o \
./Drivers/Platform_ARM/src/USB/usbd_hid.o \
./Drivers/Platform_ARM/src/USB/usbd_main.o 

C_DEPS += \
./Drivers/Platform_ARM/src/USB/usbd_conf.d \
./Drivers/Platform_ARM/src/USB/usbd_desc.d \
./Drivers/Platform_ARM/src/USB/usbd_hid.d \
./Drivers/Platform_ARM/src/USB/usbd_main.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Platform_ARM/src/USB/%.o: ../Drivers/Platform_ARM/src/USB/%.c Drivers/Platform_ARM/src/USB/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DFSC_HAVE_SRC -DFSC_GSCE_FIX -DFSC_HAVE_EXT_MSG -DDEBUG -DI2C1_TIMEOUT_MAX=0xF -DFSC_POLLING_MODE -DHAL_PCD_MODULE_ENABLED -DPLATFORM_ARM -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver_custom/Inc -I../Drivers/STM32F1xx_HAL_Driver_custom/Src -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Drivers/FUSB_CORE -I../Drivers/Platform_ARM/src/USB -I../Drivers/Platform_ARM/src -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/FUSB_CORE/modules -I../Drivers/FUSB_CORE/vdm -I../Drivers/FUSB_CORE/vdm/DisplayPort -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-Platform_ARM-2f-src-2f-USB

clean-Drivers-2f-Platform_ARM-2f-src-2f-USB:
	-$(RM) ./Drivers/Platform_ARM/src/USB/usbd_conf.d ./Drivers/Platform_ARM/src/USB/usbd_conf.o ./Drivers/Platform_ARM/src/USB/usbd_desc.d ./Drivers/Platform_ARM/src/USB/usbd_desc.o ./Drivers/Platform_ARM/src/USB/usbd_hid.d ./Drivers/Platform_ARM/src/USB/usbd_hid.o ./Drivers/Platform_ARM/src/USB/usbd_main.d ./Drivers/Platform_ARM/src/USB/usbd_main.o

.PHONY: clean-Drivers-2f-Platform_ARM-2f-src-2f-USB

