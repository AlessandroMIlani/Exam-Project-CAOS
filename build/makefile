################################################################################
# Automatically-generated file. Do not edit!
################################################################################
.PHONY: all clean dependents main-build run edf help

-include ../makefile.init

RM := rm -rf
MV := mv

ifeq ($(OS), Windows_NT)
	RM := del
	MV := move
endif

FREERTOS_DIR = ../FreeRTOS/FreeRTOS
LIBS_DIR = -L$(FREERTOS_DIR)/Source/Common/drivers/LuminaryMicro/arm-none-eabi-gcc/
LIBS_FILES = -ldriver -lgr

OUTPUT_DIR = .
IMAGE = RTOSDemo.elf



# All of the sources participating in the build are defined here
-include sources.mk
-include LocalFiles/subdir.mk
-include LegacyDrivers/subdir.mk
-include FreeRTOS_Source/portable/MemMang/subdir.mk
-include FreeRTOS_Source/portable/GCC/ARM_CM3/subdir.mk
-include FreeRTOS_Source/subdir.mk
-include CommonFiles/subdir.mk
-include subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(SX_DEPS)),)
-include $(SX_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := RTOSDemo
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
RTOSDemo.hex \

SECONDARY_SIZE += \
RTOSDemo.siz \

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



# All Target
all: main-build

# Main-build Target
main-build: RTOSDemo.elf secondary-outputs

# Tool invocations
RTOSDemo.elf: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM Cross C Linker'
	arm-none-eabi-gcc $(SELECTED_DEMO) -mcpu=cortex-m3 -mthumb -O0 -MD -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 -nostartfiles $(LIBS_DIR)  -Wl,--gc-sections,-Map,"RTOSDemo.map" --specs=nano.specs -T../src/standalone.ld -nostartfiles -o "RTOSDemo.elf" $(OBJS) $(USER_OBJS) $(LIBS) $(LIBS_FILES)
	@echo 'Finished building target: $@'
	@echo ' '

RTOSDemo.hex: RTOSDemo.elf makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: GNU ARM Cross Create Flash Image'
	arm-none-eabi-objcopy -O ihex "RTOSDemo.elf"  "RTOSDemo.hex"
	@echo 'Finished building: $@'
	@echo ' '

RTOSDemo.siz: RTOSDemo.elf makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: GNU ARM Cross Print Size'
	arm-none-eabi-size --format=berkeley "RTOSDemo.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) RTOSDemo.elf RTOSDemo.hex RTOSDemo.siz
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)


# Targets for compile demo with EDF scheduler
edf: rename_edf all edf_back

rename_edf:
	@echo 'Rename files'
	$(MV) ../src/main.c ../src/main.c.bak
	$(MV) ../src/$(DEMO) ../src/main.c

edf_back:
	@echo 'Rename files'
	$(MV) ../src/main.c ../src/$(DEMO)
	$(MV) ../src/main.c.bak ../src/main.c


run:
	qemu-system-arm -machine lm3s6965evb --kernel $(OUTPUT_DIR)/$(IMAGE) -serial stdio 


help:
	@echo Usage: make all-edf-clean-run-help
	@echo - all: Build the project
	@echo        Need the argument DEMO=1,2,3,4
	@echo - edf: Build the project with EDF scheduler
	@echo        Need the argument DEMO equal to the file to be executed
	@echo - clean: Clean the project
	@echo - run: Run the project on QEMU




-include ../makefile.targets
