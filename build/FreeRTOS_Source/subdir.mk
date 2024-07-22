################################################################################
# Automatically-generated file. Do not edit!
################################################################################


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
$(FREERTOS_DIR)/Source/croutine.c \
$(FREERTOS_DIR)/Source/event_groups.c \
$(FREERTOS_DIR)/Source/list.c \
$(FREERTOS_DIR)/Source/queue.c \
$(FREERTOS_DIR)/Source/stream_buffer.c \
$(FREERTOS_DIR)/Source/tasks.c \

C_DEPS += \
./FreeRTOS_Source/croutine.d \
./FreeRTOS_Source/event_groups.d \
./FreeRTOS_Source/list.d \
./FreeRTOS_Source/queue.d \
./FreeRTOS_Source/stream_buffer.d \
./FreeRTOS_Source/tasks.d \

OBJS += \
./FreeRTOS_Source/croutine.o \
./FreeRTOS_Source/event_groups.o \
./FreeRTOS_Source/list.o \
./FreeRTOS_Source/queue.o \
./FreeRTOS_Source/stream_buffer.o \
./FreeRTOS_Source/tasks.o \

# Each subdirectory must supply rules for building sources it contributes
FreeRTOS_Source/croutine.o: $(FREERTOS_DIR)/Source/croutine.c FreeRTOS_Source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 $(INCLUDE_DIRS) -std=gnu11 -specs=nano.specs -specs=nosys.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS_Source/event_groups.o: $(FREERTOS_DIR)/Source/event_groups.c FreeRTOS_Source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 $(INCLUDE_DIRS) -std=gnu11 -specs=nano.specs -specs=nosys.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS_Source/list.o: $(FREERTOS_DIR)/Source/list.c FreeRTOS_Source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 $(INCLUDE_DIRS) -std=gnu11 -specs=nano.specs -specs=nosys.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS_Source/queue.o: $(FREERTOS_DIR)/Source/queue.c FreeRTOS_Source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 $(INCLUDE_DIRS) -std=gnu11 -specs=nano.specs -specs=nosys.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS_Source/stream_buffer.o: $(FREERTOS_DIR)/Source/stream_buffer.c FreeRTOS_Source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 $(INCLUDE_DIRS) -std=gnu11 -specs=nano.specs -specs=nosys.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS_Source/tasks.o: $(FREERTOS_DIR)/Source/tasks.c FreeRTOS_Source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 $(INCLUDE_DIRS) -std=gnu11 -specs=nano.specs -specs=nosys.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOS_Source/timers.o: $(FREERTOS_DIR)/Source/timers.c FreeRTOS_Source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 $(INCLUDE_DIRS) -std=gnu11 -specs=nano.specs -specs=nosys.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-FreeRTOS_Source

clean-FreeRTOS_Source:
	-$(RM) ./FreeRTOS_Source/croutine.d ./FreeRTOS_Source/croutine.o ./FreeRTOS_Source/event_groups.d ./FreeRTOS_Source/event_groups.o ./FreeRTOS_Source/list.d ./FreeRTOS_Source/list.o ./FreeRTOS_Source/queue.d ./FreeRTOS_Source/queue.o ./FreeRTOS_Source/stream_buffer.d ./FreeRTOS_Source/stream_buffer.o ./FreeRTOS_Source/tasks.d ./FreeRTOS_Source/tasks.o ./FreeRTOS_Source/timers.d ./FreeRTOS_Source/timers.o

.PHONY: clean-FreeRTOS_Source

