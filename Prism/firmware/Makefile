TEMPLATEROOT = .

ifndef CONFIG
  CONFIG = Debug
endif

ifeq ($(CONFIG),Debug)
  CPPFLAGS = -g -Wall -Wcpp -Wunused-function -DDEBUG -DUSE_FULL_ASSERT
  ASFLAGS  = -g
endif

ifeq ($(CONFIG),Release)
  CPPFLAGS = -O2
endif

LDFLAGS += -Wl,--gc-sections
#LDSCRIPT = Source/flash.ld
LDSCRIPT = Source/STM32F746VG_FLASH.ld

CPPFLAGS += --specs=nano.specs
CPPFLAGS += -DEXTERNAL_SRAM -DARM_CORTEX
# CPPFLAGS += -fpic -fpie
CPPFLAGS += -fdata-sections
CPPFLAGS += -ffunction-sections
#CPPFLAGS +=  -mno-unaligned-access
#CPPFLAGS  += -fno-omit-frame-pointer
CPPFLAGS += -nostdlib -nostartfiles -fno-builtin -ffreestanding
CPPFLAGS += -mtune=cortex-m4
CXXFLAGS = -fno-rtti -fno-exceptions -std=c++11
CFLAGS  += -std=gnu99

C_SRC  = stm32f7xx_it.c main.c stm32f7xx_hal_msp.c
C_SRC += system_stm32f7xx.c

# CPP_SRC = main.cpp

OBJS = $(C_SRC:%.c=Build/%.o) $(CPP_SRC:%.cpp=Build/%.o)
OBJS += startup_stm32f746xx.o

include $(TEMPLATEROOT)/libs.mk
include $(TEMPLATEROOT)/f7.mk
