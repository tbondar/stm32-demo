CC=arm-none-eabi-gcc
AR=arm-none-eabi-ar
MKDIR=mkdir -p

PROJECT_NAME = Demo01
STMLIB_DIR = ../tools/STM32F10x_StdPeriph_Lib_V3.5.0
DRVLIB_DIR = $(STMLIB_DIR)/Libraries/STM32F10x_StdPeriph_Driver
CMSIS_CORE_DIR = $(STMLIB_DIR)/Libraries/CMSIS/CM3/CoreSupport
CMSIS_DEV_DIR = $(STMLIB_DIR)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x
PROJECT_DIR = .
BUILD_DIR = build
DEVBOARD = STM3210B_EVAL

LD_SCRIPT = $(STMLIB_DIR)/Project/STM32F10x_StdPeriph_Template/TrueSTUDIO/STM3210B-EVAL/stm32_flash.ld
STM32_LIB = $(BUILD_DIR)/libstm32.a

CMSIS_INC = -I $(CMSIS_CORE_DIR) -I $(CMSIS_DEV_DIR)
DRVLIB_INC = -I $(DRVLIB_DIR)/inc
PROJECT_INC = -I $(PROJECT_DIR)/inc
INCLUDES = $(CMSIS_INC) $(DRVLIB_INC) $(PROJECT_INC)


COMMON_CFLAGS = -mthumb -mcpu=cortex-m3 -std=gnu90 -Os -Wall -ffunction-sections -fdata-sections
DRVLIB_CFLAGS = -DUSE_$(DEVBOARD) -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER

LD_SYS_LIBS = -lc_s
#LD_SYS_LIBS = --specs=nano.specs -lc -lc -lnosys
LFLAGS = -mthumb -mcpu=cortex-m3 -T$(LD_SCRIPT) $(LD_SYS_LIBS) -static -Wl,-cref,-Map=$(BUILD_DIR)/$(PROJECT_NAME).map -Wl,--gc-sections

DRVLIB_SRCS = $(wildcard $(DRVLIB_DIR)/src/*.c)
DRVLIB_SRCS += $(STMLIB_DIR)/Project/STM32F10x_StdPeriph_Template/system_stm32f10x.c
DRVLIB_OBJS = $(patsubst $(STMLIB_DIR)/%.c, $(BUILD_DIR)/%.o, $(DRVLIB_SRCS))

STARTUP_SRC = startup/TrueSTUDIO/startup_stm32f10x_md.s
STARTUP_OBJ = $(addprefix $(BUILD_DIR)/, $(patsubst %.s, %.o, $(STARTUP_SRC)))

PROJECT_SRCS = $(wildcard $(PROJECT_DIR)/src/*.c)
PROJECT_OBJS = $(patsubst $(PROJECT_DIR)/%.c, $(BUILD_DIR)/%.o, $(PROJECT_SRCS))


all: libstm32 demo

libstm32: $(STM32_LIB)

demo: $(STM32_LIB) $(PROJECT_OBJS)
	$(CC) $(LFLAGS) $(PROJECT_OBJS) $(STM32_LIB) -o $(BUILD_DIR)/$(PROJECT_NAME).elf

$(PROJECT_OBJS): $(BUILD_DIR)/%.o: %.c
	@$(MKDIR) $(@D)
	$(CC) -c $(COMMON_CFLAGS) $(DRVLIB_CFLAGS) $(INCLUDES) $< -o $@

$(DRVLIB_OBJS): $(BUILD_DIR)/%.o: $(STMLIB_DIR)/%.c
	@$(MKDIR) $(@D)
	$(CC) -c $(COMMON_CFLAGS) $(DRVLIB_CFLAGS) $(INCLUDES) $< -o $@

$(STARTUP_OBJ): $(CMSIS_DEV_DIR)/$(STARTUP_SRC)
	@$(MKDIR) $(@D)
	$(CC) -c -mthumb -mcpu=cortex-m3 -g -Wa,--warn -x assembler-with-cpp $< -o $@

$(STM32_LIB): $(DRVLIB_OBJS) $(STARTUP_OBJ)
	$(AR) rc $@ $?

clean:
	rm -r $(BUILD_DIR)/*

.PHONY: clean libstm32 demo
