TARGET = main

BUILD_DIR = build


C_SOURCES = $(shell find . -name "*.c")
ASM_SOURCES = $(shell find . -name "*.s")


PREFIX = arm-none-eabi
CC = $(PREFIX)-gcc.exe
AS = $(PREFIX)-as.exe
CP = $(PREFIX)-objcopy.exe
LD = $(PREFIX)-ld.bfd.exe
SZ = $(PREFIX)-size.exe
GDB = $(PREFIX)-gdb.exe

BIN = $(CP) -O binary

CPU = -mcpu=cortex-m0
MCU = $(CPU) -mthumb -g

C_INCLUDES = -Iinclude
CFLAGS = $(MCU) $(C_INCLUDES)

LDSCRIPT = STM32.ld
LDFLAGS = -T $(LDSCRIPT)

all: $(BUILD_DIR)/$(TARGET).bin

OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.s | $(BUILD_DIR)
	$(AS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) | $(BUILD_DIR)
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@

$(BUILD_DIR):
	mkdir $@

list:
	@echo $(shell find . -name "*.c")
	@echo $(shell find . -name "*.s")

clean:
	-rm -fR $(BUILD_DIR)

flash:
	st-flash --reset write ./$(BUILD_DIR)/$(TARGET).bin 0x08000000
