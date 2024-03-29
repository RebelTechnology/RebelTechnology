TARGET = Triggy
INSTALL_DIR = /usr/share/arduino/
PORT = /dev/ttyUSB0
PROGRAMMER = avrispv2
F_CPU = 16000000
MCU = atmega168
UPLOAD_RATE = 19200

ARDUINO = $(INSTALL_DIR)/hardware/cores/arduino

CXXSRC = Triggy.cpp adc_freerunner.cpp main.cpp
SRC =

############################################################################

AVR_TOOLS_PATH = $(INSTALL_DIR)/hardware/tools/avr/bin
# AVR_TOOLS_PATH = $(INSTALL_DIR)/bin
FORMAT = ihex


# Name of this Makefile (used for "make depend").
MAKEFILE = Makefile

# Debugging format.
# Native formats for AVR-GCC's -g are stabs [default], or dwarf-2.
# AVR (extended) COFF requires stabs, plus an avr-objcopy run.
DEBUG = stabs

OPT = 2 # -mcall-prologues 

# Place -D or -U options here
CDEFS = -DF_CPU=$(F_CPU)
CXXDEFS = -DF_CPU=$(F_CPU)

# Place -I options here
CINCS = -I$(ARDUINO)
CXXINCS = -I$(ARDUINO)

# Compiler flag to set the C Standard level.
# c89   - "ANSI" C
# gnu89 - c89 plus GCC extensions
# c99   - ISO C99 standard (not yet fully implemented)
# gnu99 - c99 plus GCC extensions
CSTANDARD = -std=gnu99
CDEBUG = # -g$(DEBUG)
CWARN = -Wall -Wstrict-prototypes
CTUNING = -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
#CEXTRA = -Wa,-adhlns=$(<:.c=.lst)

CFLAGS = $(CDEBUG) $(CDEFS) $(CINCS) -O$(OPT) $(CWARN) $(CSTANDARD) $(CEXTRA)
CXXFLAGS = $(CDEFS) $(CINCS) -O$(OPT)
#ASFLAGS = -Wa,-adhlns=$(<:.S=.lst),-gstabs 
LDFLAGS = -lm

# Program settings
CC = $(AVR_TOOLS_PATH)/avr-gcc
CXX = $(AVR_TOOLS_PATH)/avr-g++
OBJCOPY = $(AVR_TOOLS_PATH)/avr-objcopy
OBJDUMP = $(AVR_TOOLS_PATH)/avr-objdump
AR  = $(AVR_TOOLS_PATH)/avr-ar
SIZE = $(AVR_TOOLS_PATH)/avr-size
NM = $(AVR_TOOLS_PATH)/avr-nm
AVRDUDE = avrdude
REMOVE = rm -f
MV = mv -f

# Define all object files.
OBJ = $(SRC:%.c=build/%.o) $(CXXSRC:%.cpp=build/%.o) $(ASRC:%.S=build/%.o) 

# Define all listing files.
LST = $(ASRC:.s=.lst) $(CXXSRC:.cpp=.lst) $(SRC:.c=.lst)

# Combine all necessary flags and optional flags.
# Add target processor to flags.
ALL_CFLAGS = -mmcu=$(MCU) -I. $(CFLAGS)
ALL_CXXFLAGS = -mmcu=$(MCU) -I. $(CXXFLAGS)
ALL_ASFLAGS = -mmcu=$(MCU) -I. -x assembler-with-cpp $(ASFLAGS)


# Default target.
all: compile sizeafter

compile: elf hex
# compile: elf hex eep

elf: build/$(TARGET).elf
hex: build/$(TARGET).hex
eep: build/$(TARGET).eep
lss: build/$(TARGET).lss 
sym: build/$(TARGET).sym

# Program the device.  
flash: build/$(TARGET).hex
	$(AVRDUDE) -p $(MCU) -P $(PORT) -c $(PROGRAMMER) -e -U flash:w:build/$(TARGET).hex

# Display size of file.
HEXSIZE = $(SIZE) --target=$(FORMAT) build/$(TARGET).hex
ELFSIZE = $(SIZE)  build/$(TARGET).elf
sizebefore:
	@if [ -f build/$(TARGET).elf ]; then echo; echo $(MSG_SIZE_BEFORE); $(HEXSIZE); echo; fi

sizeafter:
	@if [ -f build/$(TARGET).elf ]; then echo; echo $(MSG_SIZE_AFTER); $(HEXSIZE); echo; fi


# Convert ELF to COFF for use in debugging / simulating in AVR Studio or VMLAB.
COFFCONVERT=$(OBJCOPY) --debugging \
--change-section-address .data-0x800000 \
--change-section-address .bss-0x800000 \
--change-section-address .noinit-0x800000 \
--change-section-address .eeprom-0x810000 


coff: build/$(TARGET).elf
	$(COFFCONVERT) -O coff-avr build/$(TARGET).elf build/$(TARGET).cof


extcoff: build/$(TARGET).elf
	$(COFFCONVERT) -O coff-ext-avr build/$(TARGET).elf build/$(TARGET).cof


.SUFFIXES: .elf .hex .eep .lss .sym

.elf.hex:
	$(OBJCOPY) -O $(FORMAT) -R .eeprom $< $@

.elf.eep:
	-$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" \
	--change-section-lma .eeprom=0 -O $(FORMAT) $< $@

# Create extended listing file from ELF output file.
.elf.lss:
	$(OBJDUMP) -h -S $< > $@

# Create a symbol table from ELF output file.
.elf.sym:
	$(NM) -n $< > $@

# Link: create ELF output file from library.
build/$(TARGET).elf: build/core.a
	$(CC) $(ALL_CXXFLAGS) -o $@ -L. build/core.a $(LDFLAGS)

build/core.a: $(OBJ)
	@for i in $(OBJ); do echo $(AR) rcs build/core.a $$i; $(AR) rcs build/core.a $$i; done


# Compile: create object files from C++ source files.
build/%.o : %.cpp
	$(CXX) -c $(ALL_CXXFLAGS) $< -o $@ 

# Compile: create object files from C source files.
build/%.o : %.c
	$(CC) -c $(ALL_CFLAGS) $< -o $@ 


# Compile: create assembler files from C source files.
build/%.s : %.c
	$(CC) -S $(ALL_CFLAGS) $< -o $@


# Assemble: create object files from assembler source files.
build/%.o : %.s
	$(CC) -c $(ALL_ASFLAGS) $< -o $@


# Target: clean project.
clean:
	$(REMOVE) build/$(TARGET).hex build/$(TARGET).eep build/$(TARGET).cof build/$(TARGET).elf \
	build/$(TARGET).map build/$(TARGET).sym build/$(TARGET).lss build/core.a \
	$(OBJ) $(LST) \
	$(SRC:%.c=build/%.s) $(SRC:%.c=build/%.d) $(CXXSRC:%.cpp=build/%.s) $(CXXSRC:%.cpp=build/%.d)

depend:
	if grep '^# DO NOT DELETE' $(MAKEFILE) >/dev/null; \
	then \
		sed -e '/^# DO NOT DELETE/,$$d' $(MAKEFILE) > \
			$(MAKEFILE).$$$$ && \
		$(MV) $(MAKEFILE).$$$$ $(MAKEFILE); \
	fi
	echo '# DO NOT DELETE THIS LINE -- make depend depends on it.' \
		>> $(MAKEFILE); \
	$(CC) -M -mmcu=$(MCU) $(CDEFS) $(CINCS) $(SRC) $(ASRC) >> $(MAKEFILE)

.PHONY:	all compile elf hex eep lss sym program coff extcoff clean depend sizebefore sizeafter
# DO NOT DELETE THIS LINE -- make depend depends on it.
