################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
$(FREERTOS_DIR)/Source/portable/GCC/ARM_CM3/port.c 

C_DEPS += \
./FreeRTOS_Source/portable/GCC/ARM_CM3/port.d 

OBJS += \
./FreeRTOS_Source/portable/GCC/ARM_CM3/port.o 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS_Source/portable/GCC/ARM_CM3/port.o: $(FREERTOS_DIR)/Source/portable/GCC/ARM_CM3/port.c FreeRTOS_Source/portable/GCC/ARM_CM3/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 $(INCLUDE_DIRS) -std=gnu11 -specs=nano.specs -specs=nosys.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-FreeRTOS_Source-2f-portable-2f-GCC-2f-ARM_CM3

clean-FreeRTOS_Source-2f-portable-2f-GCC-2f-ARM_CM3:
	-$(RM) ./FreeRTOS_Source/portable/GCC/ARM_CM3/port.d ./FreeRTOS_Source/portable/GCC/ARM_CM3/port.o

.PHONY: clean-FreeRTOS_Source-2f-portable-2f-GCC-2f-ARM_CM3

