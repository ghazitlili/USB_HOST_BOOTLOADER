################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../fat_fs/src/fattime.c \
../fat_fs/src/ff.c 

OBJS += \
./fat_fs/src/fattime.o \
./fat_fs/src/ff.o 

C_DEPS += \
./fat_fs/src/fattime.d \
./fat_fs/src/ff.d 


# Each subdirectory must supply rules for building sources it contributes
fat_fs/src/%.o: ../fat_fs/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F407VGTx -DSTM32F4 -DSTM32F4DISCOVERY -DSTM32 -DDEBUG -DUSE_STDPERIPH_DRIVER -DSTM32F40XX -DSTM32F40_41xxx -I"/home/ghazi/Documents/swstm32_workspace/USB_HOST/inc" -I"/home/ghazi/Documents/swstm32_workspace/USB_HOST/fat_fs/inc" -I"/home/ghazi/Documents/swstm32_workspace/USB_HOST/StdPeriph_Driver/inc" -I"/home/ghazi/Documents/swstm32_workspace/USB_HOST/USB_OTG_Driver/inc" -I"/home/ghazi/Documents/swstm32_workspace/USB_HOST/Utilities" -I"/home/ghazi/Documents/swstm32_workspace/USB_HOST/USB_HOST_Library/Core/inc" -I"/home/ghazi/Documents/swstm32_workspace/USB_HOST/USB_HOST_Library/Class/MSC/inc" -I"/home/ghazi/Documents/swstm32_workspace/USB_HOST/CMSIS/core" -I"/home/ghazi/Documents/swstm32_workspace/USB_HOST/CMSIS/device" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


