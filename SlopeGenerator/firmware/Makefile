TEMPLATEROOT = .

CFLAGS = -g -Wall -Wcpp -DUSE_FULL_ASSERT
# CFLAGS   = -O2 -Wall -Wcpp # -DUSE_FULL_ASSERT # does not work?!
CFLAGS   = -O1 -Wall -Wcpp # -DUSE_FULL_ASSERT
CFLAGS += -DSTM32F100xB
CXXFLAGS = -fno-rtti -fno-exceptions -std=c++11 $(CFLAGS) 
# LDSCRIPT ?= $(TEMPLATEROOT)/STM32F100C8_FLASH.ld
LDSCRIPT ?= $(TEMPLATEROOT)/STM32F100CB_FLASH.ld
CPPFLAGS += -flto
LDFLAGS += -flto

C_SRC   = main.c stm32f1xx_it.c stm32f1xx_hal_msp.c system_stm32f1xx.c
C_SRC  += gpio.c periph.c
CPP_SRC = SlopeGenerator.cpp DDS.cpp

OBJS = $(C_SRC:%.c=Build/%.o) $(CPP_SRC:%.cpp=Build/%.o)
include $(TEMPLATEROOT)/libs.mk
include $(TEMPLATEROOT)/f1.mk
