ifndef TARGET_COMPILE
    TARGET_COMPILE = aarch64-none-elf-
endif

ifndef KP_DIR
    KP_DIR = ./lib
endif

CC = $(TARGET_COMPILE)gcc
LD = $(TARGET_COMPILE)ld

INCLUDE_DIRS := . include patch/include linux/include linux/arch/arm64/include linux/tools/arch/arm64/include

INCLUDE_FLAGS := $(foreach dir,$(INCLUDE_DIRS),-I$(KP_DIR)/kernel/$(dir))

objs := sam_hid_kbd_rem.c

all: sam_hid_kbd_rem.kpm

sam_hid_kbd_rem.kpm: ${objs}
	${CC} $(CFLAGS) $(INCLUDE_FLAGS) -O2 $^ -r -o ../build/$@


.PHONY: clean
clean:
	rm -rf ../build/*.kpm
	find . -name "../build/*.o" | xargs rm -f
