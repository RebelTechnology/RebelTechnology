# object files
OBJS += $(PERIPH) 

OBJS += $(LIBROOT)/BSP/STM32F7xx_Nucleo_144/stm32f7xx_nucleo_144.o
OBJS += $(DRIVERS)/Src/stm32f7xx_hal.o
OBJS += $(DRIVERS)/Src/stm32f7xx_hal_rcc.o
OBJS += $(DRIVERS)/Src/stm32f7xx_hal_dma.o
OBJS += $(DRIVERS)/Src/stm32f7xx_hal_adc.o
OBJS += $(DRIVERS)/Src/stm32f7xx_hal_gpio.o
OBJS += $(DRIVERS)/Src/stm32f7xx_hal_adc_ex.o
OBJS += $(DRIVERS)/Src/stm32f7xx_hal_dma_ex.o
OBJS += $(DRIVERS)/Src/stm32f7xx_hal_pwr_ex.o
OBJS += $(DRIVERS)/Src/stm32f7xx_hal_rcc_ex.o
OBJS += $(DRIVERS)/Src/stm32f7xx_hal_flash_ex.o
OBJS += $(DRIVERS)/Src/stm32f7xx_hal_tim_ex.o
OBJS += $(DRIVERS)/Src/stm32f7xx_hal_tim.o
OBJS += $(DRIVERS)/Src/stm32f7xx_hal_cortex.o
OBJS += $(DRIVERS)/Src/stm32f7xx_hal_sai.o
OBJS += $(DRIVERS)/Src/stm32f7xx_hal_sai_ex.o
OBJS += $(DRIVERS)/Src/stm32f7xx_hal_rng.o
OBJS += $(DRIVERS)/Src/stm32f7xx_hal_qspi.o
OBJS += $(DRIVERS)/Src/stm32f7xx_hal_uart.o
OBJS += $(DRIVERS)/Src/stm32f7xx_hal_spi.o
OBJS += $(DRIVERS)/Src/stm32f7xx_hal_dma2d.o
OBJS += $(DRIVERS)/Src/stm32f7xx_hal_pcd.o # USB Device
OBJS += $(DRIVERS)/Src/stm32f7xx_hal_pcd_ex.o # USB Device
OBJS += $(DRIVERS)/Src/stm32f7xx_ll_usb.o
OBJS += $(USB_DEVICE_FILE)/Core/Src/usbd_core.o
OBJS += $(USB_DEVICE_FILE)/Core/Src/usbd_ioreq.o
OBJS += $(USB_DEVICE_FILE)/Core/Src/usbd_ctlreq.o

# OBJS += $(USB_DEVICE_FILE)/Class/AUDIO/Src/usbd_audio.o

OBJS += $(TEMPLATEROOT)/LibSource/FloatArray.o
OBJS += $(TEMPLATEROOT)/LibSource/StompBox.o

# OBJS += $(BUILD)/startup.o
# OBJS += $(BUILD)/libnosys_gnu.o
# OBJS += $(USB_DEVICE) $(USB_OTG)
# OBJS += $(DSPLIB)/FastMathFunctions/arm_sin_f32.o
# OBJS += $(DSPLIB)/FastMathFunctions/arm_cos_f32.o
# OBJS += $(DSPLIB)/CommonTables/arm_common_tables.o

# OBJS += $(DSPLIB)/TransformFunctions/arm_cfft_f32.o
# OBJS += $(DSPLIB)/TransformFunctions/arm_cfft_radix8_f32.o
# OBJS += $(DSPLIB)/TransformFunctions/arm_bitreversal2.o
# OBJS += $(DSPLIB)/TransformFunctions/arm_rfft_fast_f32.o
# OBJS += $(DSPLIB)/TransformFunctions/arm_rfft_fast_init_f32.o
# OBJS += $(DSPLIB)/CommonTables/arm_const_structs.o

# OBJS += $(DSPLIB)/FilteringFunctions/arm_biquad_cascade_df1_init_f32.o
# OBJS += $(DSPLIB)/FilteringFunctions/arm_biquad_cascade_df1_f32.o

# OBJS += $(DSPLIB)/SupportFunctions/arm_copy_f32.o
# OBJS += $(DSPLIB)/SupportFunctions/arm_float_to_q31.o
# OBJS += $(DSPLIB)/SupportFunctions/arm_q31_to_float.o
# OBJS += $(DSPLIB)/SupportFunctions/arm_float_to_q15.o
# OBJS += $(DSPLIB)/SupportFunctions/arm_q15_to_float.o

# OBJS += $(DSPLIB)/FastMathFunctions/arm_sin_f32.o
# OBJS += $(DSPLIB)/FastMathFunctions/arm_cos_f32.o
# OBJS += $(DSPLIB)/FilteringFunctions/arm_biquad_cascade_df1_f32.o
# OBJS += $(DSPLIB)/FilteringFunctions/arm_biquad_cascade_df1_init_f32.o
# OBJS += $(DSPLIB)/SupportFunctions/arm_float_to_q31.o
# OBJS += $(DSPLIB)/SupportFunctions/arm_q31_to_float.o
# OBJS += $(DSPLIB)/SupportFunctions/arm_float_to_q15.o
# OBJS += $(DSPLIB)/SupportFunctions/arm_q15_to_float.o
