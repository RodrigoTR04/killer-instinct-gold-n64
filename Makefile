.DEFAULT_GOAL := all

PYTHON := .venv/bin/python
CROSS := tools/ext/binutils/bin/mips64-elf-
AS := $(CROSS)as
LD := $(CROSS)ld
OBJCOPY := $(CROSS)objcopy
ASFLAGS := -EB -mips2 -G 0 -I include
ROM := build/kig.us.z64
ELF := build/kig.us.elf
SCRIPT := linker_scripts/kig.us.ld
UNDEFINED := linker_scripts/undefined_funcs_auto.txt linker_scripts/undefined_syms_auto.txt
OBJECTS := build/asm/header.s.o build/assets/ipl3.bin.o \
           build/asm/boot.s.o build/asm/data/boot.data.s.o \
           build/asm/data/boot.bss.s.o build/assets/opaque.bin.o

.PHONY: all extract verify clean
all: $(ROM) verify

# The stamp is written only after a successful extraction. Grouped outputs also
# allow make to recover when an individual generated file has been removed.
EXTRACTED := asm/header.s asm/boot.s asm/data/boot.data.s asm/data/boot.bss.s \
             assets/ipl3.bin assets/opaque.bin $(SCRIPT) $(UNDEFINED) include/macro.inc
$(EXTRACTED) build/.kig-extracted &: kig.us.yaml symbol_addrs.us.txt baserom.us.z64
	@mkdir -p build linker_scripts
	$(PYTHON) -m splat split kig.us.yaml
	@touch build/.kig-extracted

extract:
	@mkdir -p build linker_scripts
	$(PYTHON) -m splat split kig.us.yaml
	@touch build/.kig-extracted

# SDK exception/cache routines and 64-bit arithmetic helpers require MIPS III.
# Retain the o32 object ABI used by the rest of the build.
build/asm/boot.s.o: ASFLAGS += -mips3 -32

build/asm/%.s.o: asm/%.s include/macro.inc
	@mkdir -p $(@D)
	$(AS) $(ASFLAGS) -o $@ $<

# Assemble incbins so all ROM bytes pass through the same ELF/linker pipeline.
build/assets/%.bin.o: assets/%.bin
	@mkdir -p $(@D)
	@printf '.section .data\n.incbin "$<"\n' | $(AS) $(ASFLAGS) -o $@

$(ELF): $(OBJECTS) $(SCRIPT) $(UNDEFINED)
	$(LD) -m elf32ebmip -e entrypoint -Map build/kig.us.map \
		-T $(SCRIPT) $(addprefix -T ,$(UNDEFINED)) -o $@

$(ROM): $(ELF)
	$(OBJCOPY) -O binary $< $@

verify: $(ROM)
	@sha1sum $(ROM) baserom.us.z64
	@if test "$$(sha1sum $(ROM) | cut -d ' ' -f 1)" = "$$(sha1sum baserom.us.z64 | cut -d ' ' -f 1)" && cmp -s $(ROM) baserom.us.z64; then \
		echo 'OK: rebuilt ROM is byte-identical to baserom.us.z64'; \
	else echo 'FAIL: rebuilt ROM differs from baserom.us.z64'; exit 1; fi

# Preserve outputs belonging to other workers (notably build/segments).
clean:
	rm -rf build/asm build/assets asm
	rm -f build/kig.us.z64 build/kig.us.elf build/kig.us.map build/.kig-extracted
	rm -f assets/ipl3.bin assets/opaque.bin $(SCRIPT) $(UNDEFINED)

.PHONY: progress
progress:
	@test -d asm || $(MAKE) extract
	$(PYTHON) tools/progress/inventory.py
	$(PYTHON) tools/progress/progress.py --markdown
	$(PYTHON) tools/progress/treemap.py
