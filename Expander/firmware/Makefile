TEMPLATEROOT = .

# CFLAGS = -g -Wall -Wcpp -DUSE_FULL_ASSERT
CFLAGS   = -O2 -Wall -Wcpp -DUSE_FULL_ASSERT
CXXFLAGS = -fno-rtti -fno-exceptions -std=c++11 $(CFLAGS) 

C_SRC  = gpio.c periph.c serial.c
CPP_SRC = main.cpp Expander.cpp Pixi.cpp midi.cpp
OBJS = $(C_SRC:%.c=Build/%.o) $(CPP_SRC:%.cpp=Build/%.o)

# object files
OBJS += $(SYSCALLS)
OBJS += $(PERIPH)
# OBJS += $(STARTUP)
# OBJS += $(SYSTEM)
OBJS += $(BUILD)/system_stm32f10x.o
OBJS += $(BUILD)/startup_stm32f10x_md_vl.o # medium density value line

# include common make file
include $(TEMPLATEROOT)/f1.mk
