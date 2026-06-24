TARGET     := MyPluginPS4
INTDIR     := build

# Utilise la variable d'environnement du conteneur Docker
TOOLCHAIN  := $(OO_PS4_TOOLCHAIN)

# Inclusions des fichiers sources
CFILES     := $(wildcard source/*.c)
OBJS       := $(patsubst source/%.c, $(INTDIR)/%.o, $(CFILES))

# Flags de compilation stricts pour forcer l'inclusion Orbis OS et rejeter l'hôte Linux
CFLAGS     := -target x86_64-pc-freebsd12-elf -fPIC -funwind-tables -c \
              -isysroot $(TOOLCHAIN) -isystem $(TOOLCHAIN)/include \
              -I../include -Iinclude -O2 -Wall

# Flags de liaison pour le module .prx
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
