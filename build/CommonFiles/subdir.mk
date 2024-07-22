################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
$(FREERTOS_DIR)/Source/Common/Minimal/EventGroupsDemo.c \
$(FREERTOS_DIR)/Source/Common/Minimal/IntQueue.c \
$(FREERTOS_DIR)/Source/Common/Minimal/MessageBufferDemo.c \
$(FREERTOS_DIR)/Source/Common/Minimal/QPeek.c \
$(FREERTOS_DIR)/Source/Common/Minimal/QueueSet.c \
$(FREERTOS_DIR)/Source/Common/Minimal/StreamBufferDemo.c \
$(FREERTOS_DIR)/Source/Common/Minimal/blocktim.c \
$(FREERTOS_DIR)/Source/Common/Minimal/death.c \
$(FREERTOS_DIR)/Source/Common/Minimal/recmutex.c \
$(FREERTOS_DIR)/Source/Common/Minimal/semtest.c 

C_DEPS += \
./CommonFiles/EventGroupsDemo.d \
./CommonFiles/IntQueue.d \
./CommonFiles/MessageBufferDemo.d \
./CommonFiles/QPeek.d \
./CommonFiles/QueueSet.d \
./CommonFiles/StreamBufferDemo.d \
./CommonFiles/blocktim.d \
./CommonFiles/death.d \
./CommonFiles/recmutex.d \
./CommonFiles/semtest.d 

OBJS += \
./CommonFiles/EventGroupsDemo.o \
./CommonFiles/IntQueue.o \
./CommonFiles/MessageBufferDemo.o \
./CommonFiles/QPeek.o \
./CommonFiles/QueueSet.o \
./CommonFiles/StreamBufferDemo.o \
./CommonFiles/blocktim.o \
./CommonFiles/death.o \
./CommonFiles/recmutex.o \
./CommonFiles/semtest.o 


# Each subdirectory must supply rules for building sources it contributes
CommonFiles/EventGroupsDemo.o: $(FREERTOS_DIR)/Source/Common/Minimal/EventGroupsDemo.c CommonFiles/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 $(INCLUDE_DIRS) -std=gnu11 -specs=nano.specs -specs=nosys.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

CommonFiles/IntQueue.o: $(FREERTOS_DIR)/Source/Common/Minimal/IntQueue.c CommonFiles/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 $(INCLUDE_DIRS) -std=gnu11 -specs=nano.specs -specs=nosys.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

CommonFiles/MessageBufferDemo.o: $(FREERTOS_DIR)/Source/Common/Minimal/MessageBufferDemo.c CommonFiles/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 $(INCLUDE_DIRS) -std=gnu11 -specs=nano.specs -specs=nosys.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

CommonFiles/QPeek.o: $(FREERTOS_DIR)/Source/Common/Minimal/QPeek.c CommonFiles/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 $(INCLUDE_DIRS) -std=gnu11 -specs=nano.specs -specs=nosys.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

CommonFiles/QueueSet.o: $(FREERTOS_DIR)/Source/Common/Minimal/QueueSet.c CommonFiles/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 $(INCLUDE_DIRS) -std=gnu11 -specs=nano.specs -specs=nosys.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

CommonFiles/StreamBufferDemo.o: $(FREERTOS_DIR)/Source/Common/Minimal/StreamBufferDemo.c CommonFiles/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 $(INCLUDE_DIRS) -std=gnu11 -specs=nano.specs -specs=nosys.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

CommonFiles/blocktim.o: $(FREERTOS_DIR)/Source/Common/Minimal/blocktim.c CommonFiles/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 $(INCLUDE_DIRS) -std=gnu11 -specs=nano.specs -specs=nosys.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

CommonFiles/death.o: $(FREERTOS_DIR)/Source/Common/Minimal/death.c CommonFiles/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 $(INCLUDE_DIRS) -std=gnu11 -specs=nano.specs -specs=nosys.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

CommonFiles/recmutex.o: $(FREERTOS_DIR)/Source/Common/Minimal/recmutex.c CommonFiles/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 $(INCLUDE_DIRS) -std=gnu11 -specs=nano.specs -specs=nosys.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

CommonFiles/semtest.o: $(FREERTOS_DIR)/Source/Common/Minimal/semtest.c CommonFiles/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 $(INCLUDE_DIRS) -std=gnu11 -specs=nano.specs -specs=nosys.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-CommonFiles

clean-CommonFiles:
	-$(RM) ./CommonFiles/EventGroupsDemo.d ./CommonFiles/EventGroupsDemo.o ./CommonFiles/IntQueue.d ./CommonFiles/IntQueue.o ./CommonFiles/MessageBufferDemo.d ./CommonFiles/MessageBufferDemo.o ./CommonFiles/QPeek.d ./CommonFiles/QPeek.o ./CommonFiles/QueueSet.d ./CommonFiles/QueueSet.o ./CommonFiles/StreamBufferDemo.d ./CommonFiles/StreamBufferDemo.o ./CommonFiles/blocktim.d ./CommonFiles/blocktim.o ./CommonFiles/death.d ./CommonFiles/death.o ./CommonFiles/recmutex.d ./CommonFiles/recmutex.o ./CommonFiles/semtest.d ./CommonFiles/semtest.o

.PHONY: clean-CommonFiles

