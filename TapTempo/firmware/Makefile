TEMPLATEROOT = .

# CFLAGS = -g -Wall -Wcpp -DUSE_FULL_ASSERT
CFLAGS   = -O2 -Wall -Wcpp # -DUSE_FULL_ASSERT
CFLAGS += -DSTM32F100xB
CXXFLAGS = -fno-rtti -fno-exceptions -std=c++11 $(CFLAGS) 

C_SRC   = main.c stm32f1xx_it.c stm32f1xx_hal_msp.c system_stm32f1xx.c
C_SRC  += gpio.c periph.c
CPP_SRC = TapTempo.cpp DDS.cpp

OBJS = $(C_SRC:%.c=Build/%.o) $(CPP_SRC:%.cpp=Build/%.o)
include $(TEMPLATEROOT)/libs.mk
include $(TEMPLATEROOT)/f1.mk
