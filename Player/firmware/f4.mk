# Library path
LIBROOT=$(TEMPLATEROOT)/Drivers/

# Build path
BUILD=$(TEMPLATEROOT)/Build

# Code Paths
DRIVERS=$(LIBROOT)/STM32F4xx_HAL_Driver
CMSIS_DEVICE=$(LIBROOT)/CMSIS/Device/ST/STM32F4xx
CMSIS_CORE=$(LIBROOT)/CMSIS/Include
DSPLIB=$(LIBROOT)/CMSIS/DSP_Lib/Source
USB_DEVICE_FILE=$(TEMPLATEROOT)/Middlewares/ST/STM32_USB_Device_Library
USB_HOST_FILE=$(TEMPLATEROOT)/Middlewares/ST/STM32_USB_Host_Library
USB_OTG_FILE=$(LIBROOT)/STM32_USB_OTG_Driver
FREERTOS_DIR=$(TEMPLATEROOT)/Middlewares/Third_Party/FreeRTOS/Source

# Processor specific
LDSCRIPT = STM32F439ZG_FLASH.ld
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
ARCH_FLAGS = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16
ARCH_FLAGS += -fsingle-precision-constant
DEF_FLAGS = -DSTM32F439xx -DARM_MATH_CM4
DEF_FLAGS += -D__FPU_PRESENT

INC_FLAGS = -I$(CMSIS_CORE) -I$(CMSIS_DEVICE)/Include -I$(DRIVERS)/Inc 
INC_FLAGS += -I$(TEMPLATEROOT)/Source -I$(TEMPLATEROOT)/Inc
INC_FLAGS += -I$(USB_HOST_FILE)/Core/Inc
INC_FLAGS += -I$(USB_DEVICE_FILE)/Core/Inc
INC_FLAGS += -I$(USB_HOST_FILE)/Class/CDC/Inc -I$(USB_HOST_FILE)/Class/AUDIO/Inc
INC_FLAGS += -I$(USB_DEVICE_FILE)/Class/CDC/Inc -I$(USB_DEVICE_FILE)/Class/AUDIO/Inc
INC_FLAGS += -I$(USB_OTG_FILE)/inc
INC_FLAGS += -I$(FREERTOS_DIR)/include
INC_FLAGS += -I$(FREERTOS_DIR)/portable/GCC/ARM_CM4F/
INC_FLAGS += -I$(FREERTOS_DIR)/CMSIS_RTOS
CFLAGS += $(ARCH_FLAGS) $(INC_FLAGS) $(DEF_FLAGS)
CXXFLAGS += $(ARCH_FLAGS) $(INC_FLAGS) $(DEF_FLAGS)
LDFLAGS += -T$(LDSCRIPT) $(ARCH_FLAGS)

include $(TEMPLATEROOT)/common.mk
