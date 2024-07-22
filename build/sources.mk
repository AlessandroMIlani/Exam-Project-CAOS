################################################################################
# Automatically-generated file. Do not edit!
################################################################################

ASM_SRCS := 
C_SRCS := 
ELF_SRCS := 
OBJ_SRCS := 
O_SRCS := 
SX_SRCS := 
S_UPPER_SRCS := 
ASM_DEPS := 
C_DEPS := 
OBJS := 
SECONDARY_FLASH := 
SECONDARY_SIZE := 
SX_DEPS := 
S_UPPER_DEPS := 

# Every subdirectory with source files must be described here
SUBDIRS := \
CommonFiles \
FreeRTOS_Source \
FreeRTOS_Source/portable/GCC/ARM_CM3 \
FreeRTOS_Source/portable/MemMang \
LegacyDrivers \
LocalFiles \
. \

FREERTOS_DIR = ../FreeRTOS/FreeRTOS
FREERTOS_PLUS_DIR = ../FreeRTOS/FreeRTOS-Plus
SRC_DIR = ../src

INCLUDE_DIRS += -I$(FREERTOS_DIR)/Source/Common/include \
				-I$(FREERTOS_PLUS_DIR)/Source/FreeRTOS-Plus-Trace/Include \
				-I$(SRC_DIR) \
				-I$(FREERTOS_DIR)/Source/Common/drivers/LuminaryMicro \
				-I$(SRC_DIR)/LocalFiles \
				-I$(FREERTOS_DIR)/Source/include \
				-I$(FREERTOS_DIR)/Source/portable/GCC/ARM_CM3


