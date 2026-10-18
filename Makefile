.DEFAULT_GOAL := all

PYTHON := .venv/bin/python
CROSS := tools/ext/binutils/bin/mips64-elf-
AS := $(CROSS)as
LD := $(CROSS)ld
OBJCOPY := $(CROSS)objcopy
ASFLAGS := -EB -mips3 -32 -G 0 -I include
ROM := build/kig.us.z64
ELF := build/kig.us.elf
SCRIPT := linker_scripts/kig.us.ld
UNDEFINED := linker_scripts/undefined_funcs_auto.txt linker_scripts/undefined_syms_auto.txt
OBJECTS := build/asm/header.s.o build/assets/ipl3.bin.o \
           build/asm/boot.s.o build/asm/data/boot.data.s.o \
           build/asm/data/boot.bss.s.o build/assets/opaque.bin.o

.PHONY: all extract verify clean verify-images
IMAGES := main ovl_7DF8 ovl_7E00
IMAGE_CONFIGS := $(addprefix kig.,$(addsuffix .us.yaml,$(IMAGES)))
IMAGE_SYMBOLS := $(addprefix symbol_addrs.,$(addsuffix .us.txt,$(IMAGES)))
all: $(ROM) verify $(addprefix build/,$(addsuffix .bin,$(IMAGES))) verify-images

# The stamp is written only after a successful extraction. Grouped outputs also
# allow make to recover when an individual generated file has been removed.
EXTRACTED := asm/header.s asm/boot.s asm/data/boot.data.s asm/data/boot.bss.s \
             assets/ipl3.bin assets/opaque.bin $(SCRIPT) $(UNDEFINED) include/macro.inc \
             $(foreach image,$(IMAGES),asm/$(image)/$(image).s asm/$(image)/data/$(image).data.s linker_scripts/$(image).ld linker_scripts/$(image).undefined_funcs.txt linker_scripts/$(image).undefined_syms.txt) \
             $(addprefix assets/main/,$(addsuffix .bin,rspboot gfx_text audio_text gfx_data audio_data))
$(EXTRACTED) build/.kig-extracted &: kig.us.yaml symbol_addrs.us.txt $(IMAGE_CONFIGS) $(IMAGE_SYMBOLS) baserom.us.z64
	$(MAKE) extract

extract:
	@mkdir -p build linker_scripts
	$(PYTHON) tools/analysis/extract_segments.py baserom.us.z64
	$(PYTHON) -m splat split kig.us.yaml
	@for image in $(IMAGES); do $(PYTHON) -m splat split kig.$$image.us.yaml || exit $$?; done
	@touch $(EXTRACTED) build/.kig-extracted

# SDK exception/cache routines and 64-bit arithmetic helpers require MIPS III.
# Retain the o32 object ABI used by the rest of the build.

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
	rm -rf $(addprefix assets/,$(IMAGES))
	rm -f $(foreach image,$(IMAGES),build/$(image).bin build/$(image).elf build/$(image).map linker_scripts/$(image).ld linker_scripts/$(image).undefined_funcs.txt linker_scripts/$(image).undefined_syms.txt)

.PHONY: progress
progress:
	@test -d asm || $(MAKE) extract
	$(PYTHON) tools/progress/inventory.py
	$(PYTHON) tools/progress/progress.py --markdown
	$(PYTHON) tools/progress/treemap.py

# Each executable payload has its own linker namespace, including the overlays
# whose VRAM ranges overlap. The ROM still uses the original compressed bytes.
define IMAGE_RULES
IMAGE_OBJECTS_$(1) := build/asm/$(1)/$(1).s.o build/asm/$(1)/data/$(1).data.s.o
ifeq ($(1),main)
IMAGE_OBJECTS_$(1) += $$(addprefix build/assets/main/,$$(addsuffix .bin.o,rspboot gfx_text audio_text gfx_data audio_data))
endif
build/$(1).elf: $$(IMAGE_OBJECTS_$(1)) linker_scripts/$(1).ld linker_scripts/$(1).undefined_funcs.txt linker_scripts/$(1).undefined_syms.txt
	$$(LD) -m elf32ebmip -e 0 -Map build/$(1).map -T linker_scripts/$(1).ld -T linker_scripts/$(1).undefined_funcs.txt -T linker_scripts/$(1).undefined_syms.txt -o $$@
build/$(1).bin: build/$(1).elf
	$$(OBJCOPY) -O binary $$< $$@
endef
$(foreach image,$(IMAGES),$(eval $(call IMAGE_RULES,$(image))))

verify-images: $(addprefix build/,$(addsuffix .bin,$(IMAGES)))
	$(PYTHON) tools/progress/verify_images.py
