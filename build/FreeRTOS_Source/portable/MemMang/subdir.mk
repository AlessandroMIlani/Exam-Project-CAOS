################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
$(FREERTOS_DIR)/Source/portable/MemMang/heap_4.c 

C_DEPS += \
./FreeRTOS_Source/portable/MemMang/heap_4.d 

OBJS += \
./FreeRTOS_Source/portable/MemMang/heap_4.o 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS_Source/portable/MemMang/heap_4.o: $(FREERTOS_DIR)/Source/portable/MemMang/heap_4.c FreeRTOS_Source/portable/MemMang/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 $(INCLUDE_DIRS) -std=gnu11 -specs=nano.specs -specs=nosys.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-FreeRTOS_Source-2f-portable-2f-MemMang

clean-FreeRTOS_Source-2f-portable-2f-MemMang:
	-$(RM) ./FreeRTOS_Source/portable/MemMang/heap_4.d ./FreeRTOS_Source/portable/MemMang/heap_4.o

.PHONY: clean-FreeRTOS_Source-2f-portable-2f-MemMang

