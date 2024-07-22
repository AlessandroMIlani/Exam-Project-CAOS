################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/LocalFiles/IntQueueTimer.c \
../src/LocalFiles/osram128x64x4.c \
../src/LocalFiles/rit128x96x4.c \
../src/LocalFiles/printf-stdarg.c \
../src/LocalFiles/timertest.c 

C_DEPS += \
./LocalFiles/IntQueueTimer.d \
./LocalFiles/osram128x64x4.d \
./LocalFiles/rit128x96x4.d \
./LocalFiles/printf-stdarg.d \
./LocalFiles/timertest.d 

OBJS += \
./LocalFiles/IntQueueTimer.o \
./LocalFiles/osram128x64x4.o \
./LocalFiles/rit128x96x4.o \
./LocalFiles/printf-stdarg.o \
./LocalFiles/timertest.o 


# Each subdirectory must supply rules for building sources it contributes
LocalFiles/%.o: ../src/LocalFiles/%.c LocalFiles/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 $(INCLUDE_DIRS) -std=gnu11 -specs=nano.specs -specs=nosys.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-LocalFiles

clean-LocalFiles:
	-$(RM) ./LocalFiles/IntQueueTimer.d ./LocalFiles/IntQueueTimer.o ./LocalFiles/osram128x64x4.d ./LocalFiles/osram128x64x4.o ./LocalFiles/printf-stdarg.d ./LocalFiles/printf-stdarg.o ./LocalFiles/timertest.d ./LocalFiles/timertest.o ./LocalFiles/rit128x96x4.d ./LocalFiles/rit128x96x4.o 

.PHONY: clean-LocalFiles

