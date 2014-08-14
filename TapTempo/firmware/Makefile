TEMPLATEROOT = .

CFLAGS = -g -Wall -Wcpp -DUSE_FULL_ASSERT
# CFLAGS   = -O2 -Wall -Wcpp -DUSE_FULL_ASSERT
CXXFLAGS = -fno-rtti -fno-exceptions -std=c++11 $(CFLAGS) 
# LDSCRIPT = Source/flash.ld

C_SRC  = main.c gpio.c periph.c
OBJS =  $(C_SRC:%.c=Build/%.o)

# object files
# OBJS += $(BUILD)/stm32f10x_gpio.o
# OBJS += $(BUILD)/stm32f10x_rcc.o
# OBJS += $(BUILD)/startup.o
OBJS += $(SYSCALLS)
OBJS += $(PERIPH)
# OBJS += $(STARTUP)
# OBJS += $(SYSTEM)
OBJS += $(BUILD)/system_stm32f10x.o
OBJS += $(BUILD)/startup_stm32f10x_md_vl.o # medium density value line

# include common make file
include $(TEMPLATEROOT)/Makefile.f1
