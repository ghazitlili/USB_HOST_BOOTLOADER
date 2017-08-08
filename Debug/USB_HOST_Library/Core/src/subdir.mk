################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../USB_HOST_Library/Core/src/usbh_core.c \
../USB_HOST_Library/Core/src/usbh_hcs.c \
../USB_HOST_Library/Core/src/usbh_ioreq.c \
../USB_HOST_Library/Core/src/usbh_stdreq.c 

OBJS += \
./USB_HOST_Library/Core/src/usbh_core.o \
./USB_HOST_Library/Core/src/usbh_hcs.o \
./USB_HOST_Library/Core/src/usbh_ioreq.o \
./USB_HOST_Library/Core/src/usbh_stdreq.o 

C_DEPS += \
./USB_HOST_Library/Core/src/usbh_core.d \
./USB_HOST_Library/Core/src/usbh_hcs.d \
./USB_HOST_Library/Core/src/usbh_ioreq.d \
./USB_HOST_Library/Core/src/usbh_stdreq.d 


# Each subdirectory must supply rules for building sources it contributes
USB_HOST_Library/Core/src/%.o: ../USB_HOST_Library/Core/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F407VGTx -DSTM32F4 -DSTM32F4DISCOVERY -DSTM32 -DDEBUG -DUSE_STDPERIPH_DRIVER -DSTM32F40XX -DSTM32F40_41xxx -I"/home/ghazi/Documents/swstm32_workspace/USB_HOST/inc" -I"/home/ghazi/Documents/swstm32_workspace/USB_HOST/fat_fs/inc" -I"/home/ghazi/Documents/swstm32_workspace/USB_HOST/StdPeriph_Driver/inc" -I"/home/ghazi/Documents/swstm32_workspace/USB_HOST/USB_OTG_Driver/inc" -I"/home/ghazi/Documents/swstm32_workspace/USB_HOST/Utilities" -I"/home/ghazi/Documents/swstm32_workspace/USB_HOST/USB_HOST_Library/Core/inc" -I"/home/ghazi/Documents/swstm32_workspace/USB_HOST/USB_HOST_Library/Class/MSC/inc" -I"/home/ghazi/Documents/swstm32_workspace/USB_HOST/CMSIS/core" -I"/home/ghazi/Documents/swstm32_workspace/USB_HOST/CMSIS/device" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


