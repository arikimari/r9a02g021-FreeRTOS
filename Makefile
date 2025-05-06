

SRC_DIR     := .
BUILD_DIR   := build
SRCS        := \
	start.S		\
	main.c          \
	main_blinky.c	\
	interrupt.c          \
	clock.c          \
	pins.c          \
	trace.c          \
	FreeRTOS-Kernel/event_groups.c \
	FreeRTOS-Kernel/list.c \
	FreeRTOS-Kernel/queue.c \
	FreeRTOS-Kernel/stream_buffer.c \
	FreeRTOS-Kernel/tasks.c \
	FreeRTOS-Kernel/timers.c \
	FreeRTOS-Kernel/portable/GCC/RISC-V/port.c \
	portASM.S \
	FreeRTOS-Kernel/portable/MemMang/heap_4.c
	
SRCS        := $(SRCS:%=$(SRC_DIR)/%)
OBJS        := $(SRCS:$(SRC_DIR)/%=$(BUILD_DIR)/%.o)
DEPS 	    := $(OBJS:.o=.d)


CFLAGS      := --target=riscv32 -march=rv32imaczba_zbb_zbs -mabi=ilp32 -O0 -Wall -Wextra -Werror -MMD -MP -g -gdwarf-4 -ffunction-sections -fdata-sections
CPPFLAGS    := -I . -I FreeRTOS-Kernel/include -I FreeRTOS-Kernel/portable/GCC/RISC-V
LDFLAGS     := -e _PowerON_Reset -Wl,-Map=$(BUILD_DIR)/blinker.map -Wl,--cref
LD_SCRIPT   := -T linker_script.ld

CC          := clang
OBJDUMP     := llvm-objdump
SIZE   	    := llvm-size
RM          := rm -fr
MAKEFLAGS   += --no-print-directory
DIR_DUP     = mkdir -p $(@D)

.PHONY: all clean asm

all: $(BUILD_DIR)/blinky.elf

asm: $(BUILD_DIR)/blinky.elf
	$(OBJDUMP) -d -S -z $< > $(BUILD_DIR)/blinky.asm

$(BUILD_DIR)/blinky.elf: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LD_SCRIPT) $^ -o $(BUILD_DIR)/blinky.elf
	$(SIZE) $(BUILD_DIR)/blinky.elf
	
$(BUILD_DIR)/%.c.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(info CREATED $@)

$(BUILD_DIR)/%.S.o: $(SRC_DIR)/%.S
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(info CREATED $@)

clean:
	$(RM) $(BUILD_DIR)

-include $(DEPS)


