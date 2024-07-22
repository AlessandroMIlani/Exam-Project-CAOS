################################################################################
# Automatically-generated file. Do not edit!
################################################################################


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
$(FREERTOS_DIR)/Source/Common/drivers/LuminaryMicro/ustdlib.c 

C_DEPS += \
./LegacyDrivers/ustdlib.d 

OBJS += \
./LegacyDrivers/ustdlib.o 


# Each subdirectory must supply rules for building sources it contributes
LegacyDrivers/ustdlib.o: $(FREERTOS_DIR)/Source/Common/drivers/LuminaryMicro/ustdlib.c LegacyDrivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 $(INCLUDE_DIRS) -std=gnu11 -specs=nano.specs -specs=nosys.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-LegacyDrivers

clean-LegacyDrivers:
	-$(RM) ./LegacyDrivers/ustdlib.d ./LegacyDrivers/ustdlib.o

.PHONY: clean-LegacyDrivers

