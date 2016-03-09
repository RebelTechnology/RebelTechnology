# Library path
LIBROOT=$(TEMPLATEROOT)/Libraries/STM32F10x_StdPeriph_Lib_V3.5.0

# Build path
BUILD=$(TEMPLATEROOT)/Build

# Code Paths
DEVICE=$(LIBROOT)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/
CORE=$(LIBROOT)/Libraries/CMSIS/CM3/CoreSupport/
PERIPH_FILE=$(LIBROOT)/Libraries/STM32F10x_StdPeriph_Driver/
SYSTEM_FILE=$(LIBROOT)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/
STARTUP_FILE=$(LIBROOT)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/TrueSTUDIO/

# Processor specific
LDSCRIPT ?= $(LIBROOT)/Project/STM32F10x_StdPeriph_Template/TrueSTUDIO/STM32100B-EVAL/stm32_flash.ld
STARTUP ?= $(BUILD)/startup_stm32f10x_md_vl.o # medium density value line
SYSTEM ?= $(BUILD)/system_stm32f10x.o
PERIPH = $(BUILD)/stm32f10x_gpio.o $(BUILD)/stm32f10x_adc.o $(BUILD)/stm32f10x_rcc.o $(BUILD)/stm32f10x_pwr.o 
PERIPH += $(BUILD)/stm32f10x_exti.o $(BUILD)/stm32f10x_dac.o $(BUILD)/stm32f10x_tim.o $(BUILD)/stm32f10x_dma.o
PERIPH += $(BUILD)/stm32f10x_usart.o
PERIPH += $(BUILD)/stm32f10x_spi.o $(BUILD)/stm32f10x_i2c.o $(BUILD)/stm32f10x_dbgmcu.o 
PERIPH += $(BUILD)/stm32f10x_flash.o $(BUILD)/stm32f10x_fsmc.o
PERIPH += $(BUILD)/misc.o # stm32f10x_comp.o 
SYSCALLS = $(BUILD)/libnosys_gnu.o # Syscalls/syscalls.o

# Compilation Flags
ARCH_FLAGS = -mcpu=cortex-m3 -mthumb -mfloat-abi=soft
ARCH_FLAGS += -fsingle-precision-constant -ffast-math
DEF_FLAGS = -DUSE_STDPERIPH_DRIVER -DARM_MATH_CM3 -DSTM32F10X_MD_VL
INC_FLAGS = -I$(TEMPLATEROOT)/Libraries -I$(DEVICE) -I$(CORE) -I$(PERIPH_FILE)/inc -I$(TEMPLATEROOT)/Source
INC_FLAGS += -I$(DEVICE)/Include -I$(CORE)
CFLAGS += $(ARCH_FLAGS) $(INC_FLAGS) $(DEF_FLAGS)
CFLAGS += -fno-builtin -std=c99
CXXFLAGS += $(ARCH_FLAGS) $(INC_FLAGS) $(DEF_FLAGS)
LDFLAGS += -T$(LDSCRIPT) $(ARCH_FLAGS)

include $(TEMPLATEROOT)/common.mk
