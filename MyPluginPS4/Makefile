# ==============================================================================
# Makefile Universel pour Plugin GoldHEN PS4 (.prx)
# Compatible compilation locale (OpenOrbis) & GitHub Actions
# ==============================================================================

TARGET     := MyGoldhenPlugin
VERSION    := 1.00

# Détection de la Toolchain OpenOrbis
ifeq ($(OO_PS4_TOOLCHAIN),)
    # Si la variable n'est pas définie, on tente un chemin par défaut
    TOOLCHAIN := $(HOME)/OpenOrbis
else
    TOOLCHAIN := $(OO_PS4_TOOLCHAIN)
endif

INTDIR     := build

# Fichiers sources (Automatique : scanne tout le dossier source/)
CFILES     := $(wildcard source/*.c)
OBJS       := $(patsubst source/%.c, $(INTDIR)/%.o, $(CFILES))

# Flags de compilation (Cible FreeBSD 12 ELF pour la PS4 Orbis OS)
CFLAGS     := --target=x86_64-pc-freebsd12-elf -fPIC -funwind-tables -c \
              -isysroot $(TOOLCHAIN) -isystem $(TOOLCHAIN)/include -Iinclude \
              -O2 -Wall

# Flags de l'éditeur de liens (Génération du module partagé .prx)
LDFLAGS    := -m elf_x86_64 -shared --script $(TOOLCHAIN)/link.x \
              -L$(TOOLCHAIN)/lib -lc -lkernel

# Outils de build
CC         := clang
LD         := ld.lld

# Détection du système pour create-fself (Linux / Windows / macOS)
ifeq ($(OS),Windows_NT)
    CREATE_PRX := $(TOOLCHAIN)/bin/windows/create-fself.exe
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
        CREATE_PRX := $(TOOLCHAIN)/bin/macos/create-fself
    else
        CREATE_PRX := $(TOOLCHAIN)/bin/linux/create-fself
    endif
endif

# Règles de build
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
