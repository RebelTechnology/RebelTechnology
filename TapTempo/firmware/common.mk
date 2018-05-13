# name of executable
ELF=$(BUILD)/TapTempo.elf                    
BIN=$(BUILD)/TapTempo.bin

# Tool path
TOOLROOT ?= ~/bin/gcc-arm-none-eabi-7-2017-q4-major/bin
STLINK = /home/mars/bin

# Tools
CC=$(TOOLROOT)/arm-none-eabi-gcc
CXX=$(TOOLROOT)/arm-none-eabi-g++
LD=$(TOOLROOT)/arm-none-eabi-gcc
AR=$(TOOLROOT)/arm-none-eabi-ar
AS=$(TOOLROOT)/arm-none-eabi-as
GDB=$(TOOLROOT)/arm-none-eabi-gdb
OBJCOPY=$(TOOLROOT)/arm-none-eabi-objcopy
OBJDUMP=$(TOOLROOT)/arm-none-eabi-objdump
STFLASH=$(STLINK)/st-flash
STUTIL=$(STLINK)/st-util
DFUUTIL=dfu-util

# Set up search path
vpath %.c $(TEMPLATEROOT)/Src
vpath %.cpp $(TEMPLATEROOT)/Source
vpath %.c $(TEMPLATEROOT)/Source
vpath %.s $(TEMPLATEROOT)/Source
# vpath %.c $(CMSIS_DEVICE)/Source
# vpath %.c $(PERIPH_PATH)/Src

all: bin

# Build executable 
$(ELF) : $(OBJS) $(LDSCRIPT)
	$(LD) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

# compile and generate dependency info
$(BUILD)/%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
	$(CC) -MM -MT"$@" $(CFLAGS) $< > $(@:.o=.d)

$(BUILD)/%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@
	$(CXX) -MM -MT"$@" $(CXXFLAGS) $< > $(@:.o=.d)

$(BUILD)/%.o: %.s
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD)/%.s: %.c
	$(CC) -S $(CFLAGS) $< -o $@

$(BUILD)/%.s: %.cpp
	$(CXX) -S $(CXXFLAGS) $< -o $@

$(BUILD)/%.bin: $(BUILD)/%.elf
	$(OBJCOPY) -O binary $< $@
	@echo Successfully built OWL firmware $@

clean:
	rm -f $(OBJS) $(OBJS:.o=.d) $(ELF) $(CLEANOTHER) $(BIN) gdbscript

debug: $(ELF)
	echo "target extended localhost:4242" > gdbscript
	echo "load $(ELF)" >> gdbscript
	$(GDB) -x gdbscript $(ELF)
# 	bash -c "$(GDB) -x <(echo target extended localhost:4242) $(ELF)"

flash: $(BIN)
	$(STFLASH) write $(BIN) 0x8000000

stlink:
	echo "target extended localhost:4242" > gdbscript
	$(GDB) -x gdbscript $(ELF)

etags:
	find $(PERIPH_FILE) -type f -iname "*.[ch]" | xargs etags --append
	find $(DEVICE) -type f -iname "*.[ch]" | xargs etags --append
	find $(CORE) -type f -iname "*.[ch]" | xargs etags --append
	find $(DISCOVERY_FILE) -type f -iname "*.[ch]" | xargs etags --append
	find . -type f -iname "*.[ch]" | xargs etags --append

bin: $(BIN)

as: $(ELF)
	$(OBJDUMP) -S $(ELF) > $(ELF:.elf=.s)

dfu: $(BIN)
	$(DFUUTIL) -d 0483:df11 -c 1 -i 0 -a 0 -s 0x8000000:leave -D $(BIN)
	@echo Uploaded $(BIN) to OWL

# pull in dependencies
-include $(OBJS:.o=.d)
