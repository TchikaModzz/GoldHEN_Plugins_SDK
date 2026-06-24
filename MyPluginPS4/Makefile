TARGET     := MyPluginPS4
INTDIR     := build

# Détection de la Toolchain
ifeq ($(OO_PS4_TOOLCHAIN),)
    TOOLCHAIN := $(HOME)/OpenOrbis
else
    TOOLCHAIN := $(OO_PS4_TOOLCHAIN)
endif

CFILES     := $(wildcard source/*.c)
OBJS       := $(patsubst source/%.c, $(INTDIR)/%.o, $(CFILES))

# Flags officiels d'OpenOrbis pour isoler la compilation PS4
CFLAGS     := --target=x86_64-pc-freebsd12-elf -fPIC -funwind-tables -c \
              -isysroot $(TOOLCHAIN) -isystem $(TOOLCHAIN)/include -I../include -Iinclude \
              -O2 -Wall

LDFLAGS    := -m elf_x86_64 -shared --script $(TOOLCHAIN)/link.x \
              -L$(TOOLCHAIN)/lib -lc -lkernel

CC         := clang
LD         := ld.lld
CREATE_PRX := $(TOOLCHAIN)/bin/linux/create-fself

all: $(TARGET).prx

$(TARGET).prx: $(INTDIR)/$(TARGET).elf
	$(CREATE_PRX) -in=$< -out=$@ --intprx --paid 0x3800000000000011

$(INTDIR)/$(TARGET).elf: $(OBJS)
	$(LD) $(OBJS) -o $@ $(LDFLAGS)

$(INTDIR)/%.o: source/%.c
	@mkdir -p $(INTDIR)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf $(INTDIR) $(TARGET).prx

.PHONY: all clean
