.DEFAULT_GOAL := all

PYTHON := .venv/bin/python
CROSS := tools/ext/binutils/bin/mips64-elf-
AS := $(CROSS)as
LD := $(CROSS)ld
OBJCOPY := $(CROSS)objcopy
CC := tools/ext/ido/5.3/cc
CFLAGS := -c -G 0 -non_shared -Xcpluscomm -Wab,-r4300_mul -O2 -mips2 -32
# Override per object, e.g. build/src/main/sdk.c.o: CFLAGS := ... -O1 ...
# libultra Controller Pak (pfs) TUs are built -mips1 (T-035)
build/src/main/main_24820.c.o: CFLAGS := -c -G 0 -non_shared -Xcpluscomm -Wab,-r4300_mul -O2 -mips1 -32
build/src/main/main_24B50.c.o: CFLAGS := -c -G 0 -non_shared -Xcpluscomm -Wab,-r4300_mul -O2 -mips1 -32
build/src/main/main_24E70.c.o: CFLAGS := -c -G 0 -non_shared -Xcpluscomm -Wab,-r4300_mul -O2 -mips1 -32
build/src/main/main_26480.c.o: CFLAGS := -c -G 0 -non_shared -Xcpluscomm -Wab,-r4300_mul -O2 -mips1 -32
build/src/main/main_265B0.c.o: CFLAGS := -c -G 0 -non_shared -Xcpluscomm -Wab,-r4300_mul -O2 -mips1 -32
build/src/main/main_26860.c.o: CFLAGS := -c -G 0 -non_shared -Xcpluscomm -Wab,-r4300_mul -O2 -mips1 -32
build/src/main/main_2BA80.c.o: CFLAGS := -c -G 0 -non_shared -Xcpluscomm -Wab,-r4300_mul -O2 -mips1 -32
build/src/main/main_2CA60.c.o: CFLAGS := -c -G 0 -non_shared -Xcpluscomm -Wab,-r4300_mul -O2 -mips1 -32
build/src/main/main_2CDF0.c.o: CFLAGS := -c -G 0 -non_shared -Xcpluscomm -Wab,-r4300_mul -O2 -mips1 -32
# T-080: pinned SDK object flags (US IDO 5.3).
SDK_CFLAGS = -c -G 0 -non_shared -Xcpluscomm -Wab,-r4300_mul -nostdinc -signed -32 -DVERSION_US -DTARGET_N64 -D_LANGUAGE_C -DF3D_OLD -D_FINALROM
build/src/boot/libultra/osInitialize.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/osCreateThread.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/osStartThread.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/osCreateMesgQueue.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/osPiStartDma.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/osRecvMesg.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/osPiRawStartDma.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/osSetThreadPri.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/osCreatePiManager.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/string.c.o: CFLAGS := $(SDK_CFLAGS) -O2 -mips2
build/src/boot/libultra/osCreateViManager.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/osSetEventMesg.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/osViSetEvent.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/osSpTaskYield.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/osSpTaskLoadGo.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/osSendMesg.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/osSpTaskYielded.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/osViSwapBuffer.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/osViSetMode.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/__osSiRawReadIo.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/__osSiRawWriteIo.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/osPiRawReadIo.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
$(patsubst %.c,build/%.c.o,$(wildcard src/boot/libultra/*.c)): include/sdk/libultra.h
build/src/boot/libultra/llmuldiv.c.o: tools/build/ido_o32.py
build/src/boot/libultra/llmuldiv.c.o: FIX_IDO_O32 := 1
build/src/boot/libultra/llmuldiv.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips3 -32
build/src/boot/libultra/__osDequeueThread.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/__osPiCreateAccessQueue.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/osGetThreadPri.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/__osDevMgrMain.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/osJamMesg.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/osPiGetCmdQueue.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/osTimer.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/__osViInit.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/__osViGetCurrentContext.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/__osViSwapContext.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/__osSpSetStatus.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/osVirtualToPhysical.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/__osSpSetPc.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/__osSpRawStartDma.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/__osSpDeviceBusy.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/__osSpGetStatus.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/__osSiDeviceBusy.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/kdebugserver.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/__osSyncPutChars.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/osDestroyThread.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/boot/libultra/__osAtomicDec.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2

build/src/main/libultra/osViSetSpecialFeatures.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/main/libultra/guPerspectiveF.c.o: CFLAGS := $(SDK_CFLAGS) -O3 -mips2
build/src/main/libultra/guTranslateF.c.o: CFLAGS := $(SDK_CFLAGS) -O3 -mips2
build/src/main/libultra/guRotateF.c.o: CFLAGS := $(SDK_CFLAGS) -O3 -mips2
build/src/main/libultra/guLookAtRef.c.o: CFLAGS := $(SDK_CFLAGS) -O3 -mips2
build/src/main/libultra/guScaleF.c.o: CFLAGS := $(SDK_CFLAGS) -O3 -mips2
build/src/main/libultra/string.c.o: CFLAGS := $(SDK_CFLAGS) -O2 -mips2
build/src/main/libultra/osEepromProbe.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/main/libultra/osEepromLongWrite.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/main/libultra/osEepromLongRead.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/main/libultra/osViBlack.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/main/libultra/sinf.c.o: CFLAGS := $(SDK_CFLAGS) -O2 -mips2
build/src/main/libultra/cosf.c.o: CFLAGS := $(SDK_CFLAGS) -O2 -mips2
build/src/main/libultra/guMtxF2L.c.o: CFLAGS := $(SDK_CFLAGS) -O3 -mips2
build/src/main/libultra/guOrthoF.c.o: CFLAGS := $(SDK_CFLAGS) -O3 -mips2
build/src/main/libultra/osAiSetNextBuffer.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/main/libultra/osContInit.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/main/libultra/osContStartReadData.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/main/libultra/guNormalize.c.o: CFLAGS := $(SDK_CFLAGS) -O3 -mips2
build/src/main/libultra/__osSiCreateAccessQueue.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/main/libultra/__osSiRawStartDma.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/main/libultra/osEepromWrite.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/main/libultra/osSetTimer.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/main/libultra/osEepromRead.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/main/libultra/__osAiDeviceBusy.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/main/libultra/osGetTime.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2
build/src/main/libultra/crc.c.o: CFLAGS := $(SDK_CFLAGS) -O1 -mips2

ASMPROC := tools/ext/asm-processor/build.py

ASFLAGS := -EB -mips3 -32 -G 0 -I include
ROM := build/kig.us.z64
ELF := build/kig.us.elf
SCRIPT := linker_scripts/kig.us.ld
UNDEFINED := linker_scripts/undefined_funcs_auto.txt linker_scripts/undefined_syms_auto.txt
OBJECTS := build/asm/header.s.o build/assets/ipl3.bin.o \
           build/asm/boot_entry.s.o $(patsubst src/%.c,build/src/%.c.o,$(wildcard src/boot/*.c src/boot/libultra/*.c)) \
           $(patsubst asm/%.s,build/asm/%.s.o,$(wildcard asm/data/*.s)) \
           $(addprefix build/assets/,$(addsuffix .bin.o,opaque_assets opaque_main_gap opaque_tail)) \
           $(addprefix build/assets/code_,$(addsuffix .bin.o,main ovl_7DF8 ovl_7E00))

.PHONY: all extract verify clean verify-images
IMAGES := main ovl_7DF8 ovl_7E00
IMAGE_CONFIGS := $(addprefix kig.,$(addsuffix .us.yaml,$(IMAGES)))
IMAGE_SYMBOLS := $(addprefix symbol_addrs.,$(addsuffix .us.txt,$(IMAGES)))
all: $(ROM) verify $(addprefix build/,$(addsuffix .bin,$(IMAGES))) verify-images

# The stamp is written only after a successful extraction. Grouped outputs also
# allow make to recover when an individual generated file has been removed.
EXTRACTED := asm/ovl_7E00/ovl_7E00.s asm/header.s asm/boot_entry.s asm/data/boot_sdk_data_80006560.data.s asm/data/boot_sdk_bss_800072D0.bss.s asm/data/boot_remaining.data.s \
             assets/ipl3.bin $(addprefix assets/,$(addsuffix .bin,opaque_assets opaque_main_gap opaque_tail)) $(SCRIPT) $(UNDEFINED) include/macro.inc \
             $(foreach image,$(IMAGES),asm/$(image)/data/$(image).data.s linker_scripts/$(image).ld linker_scripts/$(image).undefined_funcs.txt linker_scripts/$(image).undefined_syms.txt) \
             $(addprefix assets/main/,$(addsuffix .bin,rspboot gfx_text audio_text gfx_data audio_data))
$(EXTRACTED) build/.kig-extracted &: kig.us.yaml symbol_addrs.us.txt $(IMAGE_CONFIGS) $(IMAGE_SYMBOLS) $(wildcard src/*/*.c src/*/libultra/*.c) baserom.us.z64
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

# These YAML bin segments are never extracted from the ROM. Assemble only the
# rebuilt compressed stream and its zero alignment padding into each code slot.
build/assets/code_%.bin.o: build/%.1172
	@mkdir -p $(@D)
	@printf '.section .data\n.incbin "$<"\n.balign 16, 0\n' | $(AS) $(ASFLAGS) -o $@

$(ELF): $(OBJECTS) $(SCRIPT) $(UNDEFINED) linker_scripts/libultra.boot_symbols.txt
	$(LD) -m elf32ebmip -e entrypoint -Map build/kig.us.map \
		-T $(SCRIPT) $(addprefix -T ,$(UNDEFINED)) -T linker_scripts/libultra.boot_symbols.txt -o $@

COMPRESSED_IMAGES := $(addprefix build/,$(addsuffix .1172,$(IMAGES)))

build/%.1172: build/%.bin tools/compress/rarezip.py
	$(PYTHON) tools/compress/rarezip.py $< $@

$(ROM): $(ELF) $(addprefix build/,$(addsuffix .bin,$(IMAGES))) $(COMPRESSED_IMAGES) tools/build/splice_rom.py
	$(OBJCOPY) -O binary $< $@.linked
	$(PYTHON) tools/build/splice_rom.py $@.linked $@
	@rm -f $@.linked

verify: $(ROM)
	@sha1sum $(ROM) baserom.us.z64
	@if test "$$(sha1sum $(ROM) | cut -d ' ' -f 1)" = "$$(sha1sum baserom.us.z64 | cut -d ' ' -f 1)" && cmp -s $(ROM) baserom.us.z64; then \
		echo 'OK: rebuilt ROM is byte-identical to baserom.us.z64'; \
	else echo 'FAIL: rebuilt ROM differs from baserom.us.z64'; exit 1; fi

# Preserve outputs belonging to other workers (notably build/segments).
clean:
	rm -rf build/asm build/src build/assets asm
	rm -f build/kig.us.z64 build/kig.us.elf build/kig.us.map build/kig.us.z64.linked $(COMPRESSED_IMAGES) build/.kig-extracted
	rm -f assets/opaque.bin assets/ipl3.bin $(addprefix assets/,$(addsuffix .bin,opaque_assets opaque_main_gap opaque_tail)) $(SCRIPT) $(UNDEFINED)
	rm -rf $(addprefix assets/,$(IMAGES))
	rm -f $(foreach image,$(IMAGES),build/$(image).bin build/$(image).elf build/$(image).map linker_scripts/$(image).ld linker_scripts/$(image).undefined_funcs.txt linker_scripts/$(image).undefined_syms.txt)

.PHONY: progress
progress:
	@test -d asm || $(MAKE) extract
	$(PYTHON) tools/progress/inventory.py
	$(PYTHON) tools/progress/progress.py --markdown
	$(PYTHON) tools/progress/treemap.py

# Each executable payload has its own linker namespace, including the overlays
# whose VRAM ranges overlap. Their matching compressed outputs feed the ROM.
define IMAGE_RULES
IMAGE_OBJECTS_$(1) := $$(patsubst %.s,build/%.s.o,$$(wildcard asm/$(1)/data/*.s))
ifeq ($(1),ovl_7E00)
IMAGE_OBJECTS_$(1) += build/asm/$(1)/$(1).s.o
else
IMAGE_OBJECTS_$(1) += $$(patsubst src/%.c,build/src/%.c.o,$$(wildcard src/$(1)/*.c src/$(1)/libultra/*.c))
endif
ifeq ($(1),main)
IMAGE_OBJECTS_$(1) += $$(addprefix build/assets/main/,$$(addsuffix .bin.o,rspboot gfx_text audio_text gfx_data audio_data))
endif
build/$(1).elf: $$(IMAGE_OBJECTS_$(1)) linker_scripts/$(1).ld linker_scripts/$(1).undefined_funcs.txt linker_scripts/$(1).undefined_syms.txt $(if $(filter main,$(1)),linker_scripts/libultra.main_symbols.txt)
	$$(LD) -m elf32ebmip -e 0 -Map build/$(1).map -T linker_scripts/$(1).ld -T linker_scripts/$(1).undefined_funcs.txt -T linker_scripts/$(1).undefined_syms.txt $(if $(filter main,$(1)),-T linker_scripts/libultra.main_symbols.txt) -o $$@
build/$(1).bin: build/$(1).elf
	$$(OBJCOPY) -O binary $$< $$@
endef
$(foreach image,$(IMAGES),$(eval $(call IMAGE_RULES,$(image))))

verify-images: $(addprefix build/,$(addsuffix .bin,$(IMAGES)))
	$(PYTHON) tools/progress/verify_images.py

# Pure SDK C needs no assembly insertion; asm-processor does not accept -O3.
build/src/main/libultra/%.c.o: src/main/libultra/%.c include/sdk/libultra.h build/.kig-extracted
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -Iinclude -o $@ $<

# asm-processor preserves function order and handles IDO-incompatible GNU asm.
build/src/%.c.o: src/%.c include/common.h include/ultra64.h include/include_asm.h $(ASMPROC) build/.kig-extracted
	@mkdir -p $(@D)
	$(PYTHON) $(ASMPROC) $(CC) -- $(AS) $(ASFLAGS) -- $(CFLAGS) -Iinclude -o $@ $<
	$(if $(FIX_IDO_O32),$(PYTHON) tools/build/ido_o32.py $@)

-include $(wildcard build/src/*/*.d build/src/*/libultra/*.d)
