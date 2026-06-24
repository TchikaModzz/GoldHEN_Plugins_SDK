TARGET     := MyPluginPS4
INTDIR     := build

ifeq ($(OO_PS4_TOOLCHAIN),)
    TOOLCHAIN := $(HOME)/OpenOrbis
else
    TOOLCHAIN := $(OO_PS4_TOOLCHAIN)
endif

CFILES     := $(wildcard source/*.c)
OBJS       := $(patsubst source/%.c, $(INTDIR)/%.o, $(CFILES))

# -nobuiltininc et -nostdinc empêchent Clang d'aller lire les fichiers d'Ubuntu
CFLAGS     := -target x86_64-pc-freebsd12-elf -fPIC -funwind-tables -c \
              -nostdinc -nobuiltininc \
              -I../include -Iinclude -O2 -Wall

# Liaison minimaliste autonome
LDFLAGS    := -m elf_x86_64 -shared --script $(TOOLCHAIN)/link.x

CC         := clang
LD         := ld.lld

all: $(TARGET).prx

$(TARGET).prx: $(INTDIR)/$(TARGET).elf
	@echo "Génération du module final..."
	cp $< $@

$(INTDIR)/$(TARGET).elf: $(OBJS)
	$(LD) $(OBJS) -o $@ $(LDFLAGS)

$(INTDIR)/%.o: source/%.c
	@mkdir -p $(INTDIR)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf $(INTDIR) $(TARGET).prx

.PHONY: all clean
