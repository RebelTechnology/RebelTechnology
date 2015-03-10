# $Id: Makefile 1820 2013-09-01 15:44:33Z tk $

################################################################################
# following setup taken from environment variables
################################################################################

PROCESSOR =	$(MIOS32_PROCESSOR)
FAMILY    = 	$(MIOS32_FAMILY)
BOARD	  = 	$(MIOS32_BOARD)
LCD       =     $(MIOS32_LCD)


################################################################################
# Source Files, include paths and libraries
################################################################################

THUMB_SOURCE    = app.c
THUMB_SOURCE   += i2s.c codec.c

THUMB_CPP_SOURCE   = audio.cpp
THUMB_CPP_SOURCE   += CodecController.cpp ApplicationSettings.cpp

# THUMB_SOURCE   += terminal.c

# (following source stubs not relevant for Cortex M3 derivatives)
THUMB_AS_SOURCE =
ARM_SOURCE      =
ARM_AS_SOURCE   =

C_INCLUDE = 	-I .
A_INCLUDE = 	-I .

LIBS = 		


################################################################################
# Remaining variables
################################################################################

LD_FILE   = 	$(MIOS32_PATH)/etc/ld/$(FAMILY)/$(PROCESSOR).ld
PROJECT   = 	project

DEBUG     =	-g
OPTIMIZE  =	-Os

CFLAGS =	$(DEBUG) $(OPTIMIZE)


################################################################################
# Include source modules via additional makefiles
################################################################################

# sources of programming model
include $(MIOS32_PATH)/programming_models/traditional/programming_model.mk

# application specific LCD driver (selected via makefile variable)
# include $(MIOS32_PATH)/modules/app_lcd/$(LCD)/app_lcd.mk

# MIDImon
# include $(MIOS32_PATH)/modules/midimon/midimon.mk

# common make rules
# Please keep this include statement at the end of this Makefile. Add new modules above.
include $(MIOS32_PATH)/include/makefile/common.mk
GDB=arm-none-eabi-gdb
ELF=$(PROJECT_OUT)/$(PROJECT).elf
stlink:
	echo "target extended localhost:4242" > gdbscript
	$(GDB) -x gdbscript $(ELF)

# debug: $(ELF)
# 	echo "target extended localhost:4242" > gdbscript
# 	echo "load $(ELF)" >> gdbscript
# 	$(GDB) -x gdbscript $(ELF)
