TARGET     := MyPluginPS4
INTDIR     := build

# Inclusions automatiques des sources locales
CFILES     := $(wildcard source/*.c)
OBJS       := $(patsubst source/%.c, $(INTDIR)/%.o, $(CFILES))

# Utilisation des répertoires du SDK parent comme Sysroot
CFLAGS     := --target=x86_64-pc-freebsd12-elf -fPIC -funwind-tables -c \
              -I../include -Iinclude -O2 -Wall

# Flags de liaison pour générer le module partagé
LDFLAGS    := -m elf_x86_64 -shared -L../lib -lc -lkernel

CC         := clang
LD         := ld.lld

all: $(TARGET).prx

$(TARGET).prx: $(INTDIR)/$(TARGET).elf
	@echo "Génération du module de test final..."
	cp $< $@

$(INTDIR)/$(TARGET).elf: $(OBJS)
	$(LD) $(OBJS) -o $@ $(LDFLAGS)

$(INTDIR)/%.o: source/%.c
	@mkdir -p $(INTDIR)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf $(INTDIR) $(TARGET).prx $(INTDIR)/$(TARGET).elf

.PHONY: all clean
