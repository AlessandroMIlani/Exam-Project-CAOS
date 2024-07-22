################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c \
../src/startup.c \
../src/DisplayDemo.c \
../src/InputDemo.c \
../src/ChaosDemo.c \
../src/Pong.c \

C_DEPS += \
./main.d \
./startup.d \
./DisplayDemo.d \
./InputDemo.d \
./ChaosDemo.d \
./Pong.d \


OBJS += \
./main.o \
./startup.o \
./DisplayDemo.o \
./InputDemo.o \
./ChaosDemo.o \
./Pong.o \

ifeq ($(DEMO), 1)
	SELECTED_DEMO += -DmainSELECTED_DEMO=1
else ifeq ($(DEMO), 2)
	SELECTED_DEMO += -DmainSELECTED_DEMO=2

else ifeq ($(DEMO), 3)
	SELECTED_DEMO += -DmainSELECTED_DEMO=3
else ifeq ($(DEMO), 4)
	SELECTED_DEMO += -DmainSELECTED_DEMO=4
else
	SELECTED_DEMO += -DmainSELECTED_DEMO=0
endif

# Each subdirectory must supply rules for building sources it contributes
%.o: ../src/%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc $(SELECTED_DEMO) -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 $(INCLUDE_DIRS) -std=gnu90 -specs=nano.specs -specs=nosys.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<" $(DSELECT)
	@echo 'Finished building: $<'
	@echo ' '

startup.o: ../src/startup.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 $(INCLUDE_DIRS) -std=gnu90 -O3 -specs=nano.specs -specs=nosys.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

DisplayDemo.o: ../src/DisplayDemo.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 $(INCLUDE_DIRS) -std=gnu90 -O3 -specs=nano.specs -specs=nosys.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

InputDemo.o: ../src/InputDemo.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 $(INCLUDE_DIRS) -std=gnu90 -O3 -specs=nano.specs -specs=nosys.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

ChaosDemo.o: ../src/ChaosDemo.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 $(INCLUDE_DIRS) -std=gnu90 -O3 -specs=nano.specs -specs=nosys.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Pong.o: ../src/Pong.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 $(INCLUDE_DIRS) -std=gnu90 -O3 -specs=nano.specs -specs=nosys.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean--2e-

clean--2e-:
	-$(RM) ./main.d ./main.o ./startup.d ./startup.o ./DisplayDemo.d ./DisplayDemo.o ./InputDemo.d ./InputDemo.o ./ChaosDemo.d ./ChaosDemo.o ./Pong.d ./Pong.o

.PHONY: clean--2e-

