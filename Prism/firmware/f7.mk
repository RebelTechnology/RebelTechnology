# Library path
LIBROOT=$(TEMPLATEROOT)/Libraries/STM32Cube_FW_F7_V1.3.0/Drivers/

# Build path
BUILD=$(TEMPLATEROOT)/Build

# Code Paths
DEVICE=$(LIBROOT)/CMSIS/Device/ST/STM32F7xx
CMSIS=$(LIBROOT)/CMSIS/Include
PERIPH_FILE=$(LIBROOT)/STM32F7xx_StdPeriph_Driver
DSPLIB=$(LIBROOT)/CMSIS/DSP_Lib/Source
USB_DEVICE_FILE=$(LIBROOT)/STM32_USB_Device_Library
USB_HOST_FILE=$(LIBROOT)/STM32_USB_HOST_Library
USB_OTG_FILE=$(LIBROOT)/STM32_USB_OTG_Driver
DRIVERS=$(LIBROOT)/STM32F7xx_HAL_Driver

# Processor specific
# LDSCRIPT ?= $(DEMO_FILE)/TrueSTUDIO/STM32F7-Discovery_Demo/stm32_flash.ld
# STARTUP ?= $(BUILD)/startup_stm32f7xx.o
# SYSTEM ?= $(BUILD)/system_stm32f7xx.o
# PERIPH = $(BUILD)/stm32f7xx_gpio.o $(BUILD)/stm32f7xx_adc.o $(BUILD)/stm32f7xx_rcc.o $(BUILD)/stm32f7xx_syscfg.o $(BUILD)/stm32f7xx_pwr.o 
# PERIPH += $(BUILD)/stm32f7xx_exti.o $(BUILD)/stm32f7xx_dac.o $(BUILD)/stm32f7xx_tim.o $(BUILD)/stm32f7xx_dma.o
# PERIPH += $(BUILD)/stm32f7xx_usart.o
# PERIPH += $(BUILD)/stm32f7xx_spi.o $(BUILD)/stm32f7xx_i2c.o $(BUILD)/stm32f7xx_dbgmcu.o 
# PERIPH += $(BUILD)/stm32f7xx_flash.o $(BUILD)/stm32f7xx_fsmc.o
# PERIPH += $(BUILD)/misc.o # stm32f7xx_comp.o 
# USB_OTG = $(BUILD)/usb_dcd.o $(BUILD)/usb_core.o $(BUILD)/usb_dcd_int.o
# USB_DEVICE = $(BUILD)/usbd_core.o $(BUILD)/usbd_ioreq.o $(BUILD)/usbd_req.o

# Compilation Flags
ARCH_FLAGS = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16
ARCH_FLAGS += -fsingle-precision-constant
DEF_FLAGS = -DUSE_STDPERIPH_DRIVER -DARM_MATH_CM4 -D__FPU_PRESENT -D__FPU_USED=1
DEF_FLAGS = -DSTM32F746xx
# DEF_FLAGS = -DSTM32F745VG
INC_FLAGS = -I$(TEMPLATEROOT)/Libraries -I$(CMSIS) -I$(TEMPLATEROOT)/Source
INC_FLAGS += -I$(DEVICE)/Include -I$(CMSIS)
INC_FLAGS += -I$(DRIVERS)/Inc
INC_FLAGS += -I$(USB_DEVICE_FILE)/Core/inc -I$(USB_DEVICE_FILE)/Class/cdc/inc
INC_FLAGS += -I$(USB_OTG_FILE)/inc
CFLAGS += $(ARCH_FLAGS) $(INC_FLAGS) $(DEF_FLAGS)
CXXFLAGS += $(ARCH_FLAGS) $(INC_FLAGS) $(DEF_FLAGS)
LDFLAGS += -T$(LDSCRIPT) $(ARCH_FLAGS)

include $(TEMPLATEROOT)/common.mk
