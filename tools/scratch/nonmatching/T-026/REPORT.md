# T-026 / sol-B11

Worktree: `/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-e798001a`

All 71 assigned T1 functions attempted. 5 MATCHED (48 original bytes); 66 DRAFT; 0 NOT ATTEMPTED. No commits. Only full-ROM-verified matches remain in `src/main/main.c`.

Attempts began in ascending size order; larger drafts were prepared while earlier builds ran. A few queued attempts passed pending entries before those entries were ready. All entries ultimately received a C compile attempt.

The word counts below compare linked instructions at corresponding positions, including assembly trailing padding. They are not asm-differ edit distances; changed sizes can also change relocation words. Counts with original sizes larger than the inventory include padding after the function body. Drafts are provisional reconstructions, especially private-register assembly fragments; they are not verified runtime replacements.

| Function | Bytes | Status | Remaining difference |
|---|---:|---|---|
| `func_80030218` | 8 | MATCHED | — |
| `func_80039AC0` | 8 | MATCHED | — |
| `func_80039C00` | 8 | MATCHED | — |
| `func_8003D348` | 8 | MATCHED | — |
| `func_80037770` | 16 | MATCHED | — |
| `func_80032738` | 20 | DRAFT | 10 positional words; 40/24 bytes including padding. Native daddiu/sd sequence and final a0 clear differ. |
| `func_80032750` | 60 | DRAFT | 15 positional words; 44/60 bytes. Original materializes each global address and uses hand-assigned temporary registers. |
| `func_80037A30` | 60 | DRAFT | 14 positional words; 56/60 bytes. Mixed f12/a0 input ABI and extra return stub differ. |
| `func_800326F0` | 72 | DRAFT | 69 positional words; 276/72 bytes. Original uses native 64-bit register shifts/stores; O2/mips2 lowers C to word pairs. |
| `func_8003278C` | 92 | DRAFT | 26 positional words; 104/92 bytes. Original uses trapping addi plus private register choices. |
| `func_80038EA4` | 96 | DRAFT | 26 positional words; 104/96 bytes. Private t1-t3 state survives calls in original. |
| `func_80031050` | 112 | DRAFT | 30 positional words; 120/112 bytes. Shared continuation at 80031188 needs private saved-register ABI. |
| `func_80032600` | 112 | DRAFT | 37 positional words; 148/112 bytes. Decoder input state is carried in t4-t8/fp; explicit C arguments differ. |
| `func_8003BFC0` | 112 | DRAFT | 21 differing instruction words; emitted 108 / original 112 bytes (positional comparison). |
| `func_80032670` | 116 | DRAFT | 45 positional words; 180/128 bytes including padding. Private decoder register ABI differs. |
| `func_8003D71C` | 120 | DRAFT | 16 differing instruction words; emitted 120 / original 120 bytes (positional comparison). |
| `func_8003B3E0` | 124 | DRAFT | 6 differing words / 124 bytes: pointer increment and load/add scheduling; same registers and arithmetic. |
| `func_80035C84` | 160 | DRAFT | 32 differing instruction words; emitted 156 / original 172 bytes (positional comparison). |
| `func_800344B0` | 164 | DRAFT | 23 differing instruction words; emitted 164 / original 164 bytes (positional comparison). |
| `func_800343F4` | 180 | DRAFT | 41 differing instruction words; emitted 176 / original 188 bytes (positional comparison). |
| `func_80030020` | 188 | DRAFT | 46 differing instruction words; emitted 176 / original 188 bytes (positional comparison). |
| `func_8003037C` | 188 | DRAFT | 49 differing instruction words; emitted 180 / original 196 bytes (positional comparison). |
| `func_80038DE0` | 196 | DRAFT | 49 differing instruction words; emitted 200 / original 196 bytes (positional comparison). |
| `func_8003431C` | 216 | DRAFT | 54 differing instruction words; emitted 200 / original 216 bytes (positional comparison). |
| `func_80034554` | 220 | DRAFT | 35 differing instruction words; emitted 212 / original 220 bytes (positional comparison). |
| `func_80035240` | 224 | DRAFT | 53 differing instruction words; emitted 208 / original 224 bytes (positional comparison). |
| `func_80036644` | 228 | DRAFT | 39 differing instruction words; emitted 228 / original 236 bytes (positional comparison). |
| `func_80032504` | 240 | DRAFT | 63 differing instruction words; emitted 68 / original 252 bytes (positional comparison). |
| `func_80037780` | 244 | DRAFT | 64 differing instruction words; emitted 256 / original 244 bytes (positional comparison). |
| `func_8003B45C` | 252 | DRAFT | 60 differing instruction words; emitted 228 / original 252 bytes (positional comparison). |
| `func_8003BC0C` | 280 | DRAFT | 54 differing instruction words; emitted 280 / original 280 bytes (positional comparison). |
| `func_80035DE0` | 296 | DRAFT | 55 differing instruction words; emitted 292 / original 304 bytes (positional comparison). |
| `func_8003FB20` | 300 | DRAFT | 77 positional words; 308/300 bytes. Continuation consumes s0-s6 live state; explicit C arguments differ. |
| `func_800300DC` | 316 | DRAFT | 77 differing instruction words; emitted 308 / original 316 bytes (positional comparison). |
| `func_80030220` | 348 | DRAFT | 85 differing instruction words; emitted 340 / original 348 bytes (positional comparison). |
| `func_80030EF0` | 348 | DRAFT | Body matches all 348 bytes; missing 4-byte trailing alignment gap shifts following code. |
| `func_8003C25C` | 348 | DRAFT | 88 differing instruction words; emitted 336 / original 356 bytes (positional comparison). |
| `func_8003B8A4` | 356 | DRAFT | 79 differing instruction words; emitted 360 / original 356 bytes (positional comparison). |
| `func_8003C5E4` | 360 | DRAFT | 89 differing instruction words; emitted 348 / original 364 bytes (positional comparison). |
| `func_80034630` | 404 | DRAFT | 71 differing instruction words; emitted 404 / original 416 bytes (positional comparison). |
| `func_80034180` | 412 | DRAFT | 70 differing instruction words; emitted 404 / original 412 bytes (positional comparison). |
| `func_800350A0` | 416 | DRAFT | 101 differing instruction words; emitted 408 / original 416 bytes (positional comparison). |
| `func_80032360` | 420 | DRAFT | 105 differing instruction words; emitted 116 / original 420 bytes (positional comparison). |
| `func_8003C750` | 424 | DRAFT | 91 differing instruction words; emitted 296 / original 432 bytes (positional comparison). |
| `func_80037A6C` | 464 | DRAFT | 125 positional words; 500/464 bytes. Original player input in s7; explicit C argument changes ABI and allocation. |
| `func_80035A84` | 512 | DRAFT | 121 differing instruction words; emitted 520 / original 512 bytes (positional comparison). |
| `func_80036440` | 516 | DRAFT | 126 differing instruction words; emitted 448 / original 516 bytes (positional comparison). |
| `func_8003BA08` | 516 | DRAFT | 116 differing instruction words; emitted 496 / original 516 bytes (positional comparison). |
| `func_8003C3C0` | 548 | DRAFT | 131 differing instruction words; emitted 496 / original 548 bytes (positional comparison). |
| `func_8003C030` | 556 | DRAFT | 130 differing instruction words; emitted 496 / original 556 bytes (positional comparison). |
| `func_80030440` | 632 | DRAFT | 157 differing instruction words; emitted 512 / original 632 bytes (positional comparison). |
| `func_800361C0` | 640 | DRAFT | 154 differing instruction words; emitted 612 / original 640 bytes (positional comparison). |
| `func_80039C08` | 648 | DRAFT | 160 differing instruction words; emitted 608 / original 648 bytes (positional comparison). |
| `func_8003BD24` | 668 | DRAFT | 166 differing instruction words; emitted 660 / original 668 bytes (positional comparison). |
| `func_80035F10` | 676 | DRAFT | 169 differing instruction words; emitted 560 / original 688 bytes (positional comparison). |
| `func_80034DBC` | 740 | DRAFT | 176 differing instruction words; emitted 692 / original 740 bytes (positional comparison). |
| `func_8003B558` | 844 | DRAFT | 208 differing instruction words; emitted 832 / original 844 bytes (positional comparison). |
| `func_80035320` | 880 | DRAFT | 218 differing instruction words; emitted 872 / original 880 bytes (positional comparison). |
| `func_80031A38` | 920 | DRAFT | 229 differing instruction words; emitted 680 / original 920 bytes (positional comparison). |
| `func_80035690` | 1012 | DRAFT | 245 differing instruction words; emitted 988 / original 1012 bytes (positional comparison). |
| `func_8003EF90` | 1048 | DRAFT | 263 differing instruction words; emitted 892 / original 1056 bytes (positional comparison). |
| `func_800327E8` | 1092 | DRAFT | 286 differing instruction words; emitted 1168 / original 1096 bytes (positional comparison). |
| `func_80031DD0` | 1420 | DRAFT | 356 differing instruction words; emitted 1020 / original 1424 bytes (positional comparison). |
| `func_800347D0` | 1516 | DRAFT | 361 differing instruction words; emitted 1280 / original 1516 bytes (positional comparison). |
| `func_8003846C` | 1556 | DRAFT | 387 differing instruction words; emitted 1300 / original 1556 bytes (positional comparison). |
| `func_8003E1DC` | 1572 | DRAFT | 389 differing instruction words; emitted 1392 / original 1572 bytes (positional comparison). |
| `func_800330B0` | 1900 | DRAFT | 499 differing instruction words; emitted 2012 / original 1900 bytes (positional comparison). |
| `func_8003D9BC` | 2080 | DRAFT | 522 differing instruction words; emitted 2112 / original 2080 bytes (positional comparison). |
| `func_80037C3C` | 2096 | DRAFT | 538 differing instruction words; emitted 2164 / original 2096 bytes (positional comparison). |
| `func_800306B8` | 2104 | DRAFT | 521 differing instruction words; emitted 1892 / original 2104 bytes (positional comparison). |
| `func_800310C0` | 2424 | DRAFT | 685 differing instruction words; emitted 2744 / original 2424 bytes (positional comparison). |

Final clean validation: `make clean && make extract && make && make progress` passed. ROM and all three images are byte-identical. T4 increased from 88 to 93.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,544 | 9,636 (3.02%) | 9,636 (3.02%) | 344 | 132 | 0 | 93 | 430 (137,648) |
| boot | 8,468 | 0 (0.00%) | 0 (0.00%) | 21 | 0 | 0 | 0 | 99 (16,028) |
| main | 173,204 | 4,248 (2.45%) | 4,248 (2.45%) | 208 | 40 | 0 | 42 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 5,388 (3.92%) | 5,388 (3.92%) | 108 | 92 | 0 | 51 | 0 (0) |
| ovl_7E00 | 444 | 0 (0.00%) | 0 (0.00%) | 7 | 0 | 0 | 0 | 162 (87,228) |

Suggested names/types:

- `func_80030EF0`: character-to-glyph-index mapper; u8 input is necessary to reproduce its argument spill and temporary register. The body matches, but the trailing gap requires a layout solution outside this task’s allowed edits.
- `func_8003B3E0`: 16-bit byte checksum. `func_8003B45C` computes paired ID checksums. Most functions from 80034180 through 80036644 and 8003B3E0 through 8003C750 appear to implement Controller Pak operations and need consistent SDK structs/prototypes.
- `func_80031A38`: packed RLE sprite decode. `func_80031DD0`: additive sprite compositor with byte intensity and RGB555 planes. `T022Sprite` already describes the shared 0x1C-byte record.
- `func_80032750` / `func_8003278C`: initialize/read an LSB-first bit stream. The decoder family uses private temporary registers across calls.
- `func_80037780`: relocate instrument/sound/wavetable pointers. `func_80039C08`: synth audio-frame generation. `func_8003EF90`: effect initialization.

No header or symbol changes were made. No inline assembly, register binding, new data definitions, or compiler pragmas were introduced. The 16-byte `func_80037770` assembly span contains two adjacent empty return stubs; its C replacement defines `func_80037770` and `func_80037778`. Draft decoder contexts expose private register inputs explicitly; they cannot match the original ABI as written. Audio switches and float/double literals may emit new rodata, another reason those drafts cannot be promoted without solving data ownership.
