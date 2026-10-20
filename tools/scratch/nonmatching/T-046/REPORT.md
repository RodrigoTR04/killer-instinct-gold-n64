# T-046 — sol-B16: main rodata ownership (FU-16 part 1)

Partial result: **2 functions MATCHED (476 bytes)**. `func_8001CBCC`
remains UNCHANGED, two instruction words off; its early constant is outside
its owning C object's later rodata range. No commits were made.

## Ownership and layout

All offsets below are decompressed main-image offsets, end exclusive.

| Range | Ownership |
|---|---|
| 0x350B0–0x38760 | Existing main assembly data |
| 0x38760–0x387E0 | `main_18440.c` .rodata |
| 0x387E0–0x38E40 | Assembly data fragment `main_remaining_early` |
| 0x38E40–0x393B0 | `main_2FF0.c` .rodata |
| 0x393B0–0x39E10 | Assembly data fragment `main_remaining_0` |
| 0x39E10–0x3A610 | Existing gfx_data binary |
| 0x3A610–0x3A8D0 | Existing audio_data binary |

Both C-owned ranges have 16-byte-aligned starts and ends. The whole
main_18440 rodata block includes the vertex array D_800480C0 and display-list
array D_80048100 before the float literal at 0x387D8. These arrays migrate
as ordinary .rodata into the existing func_80029BE0 GLOBAL_ASM file; the
matched rotation function emits the late float literal. No C padding was added.

The entire later main_2FF0 pool (including all its asm functions' constants
and jump tables) is C-object-owned. Fourteen constants already used by matched
C must remain assembly-defined to preserve their existing codegen. Explicit
`force_migration`/`function_owner` metadata in symbol_addrs.main.us.txt assigns
them to adjacent retained asm functions in pool order. This avoids changing
unrelated matched C bodies: replacing these accesses with literals changes
instruction scheduling, constant deduplication and/or immediate generation.
The owners are func_8001373C, func_80018664, func_8001B620, func_8001BB10 and
func_8001C43C. When promoting one of these asm functions later, preserve or
reassign its reserved constants in order. The first owner deliberately avoids
func_80013C84, which T-045 is working on.

Remaining assembly fragments retain `type: data` and use
`linker_section_order: .rodata`. gfx_data/audio_data also need that ordering:
otherwise splat places those .data inputs before the new C .rodata and shifts
the pool by 0xAC0. Their bytes and original locations are unchanged. No
Makefile change was necessary; T-043's generic wildcard already collects the
extra generated assembly objects.

## Requested functions

| Function | Result | Bytes | Details |
|---|---|---:|---|
| func_80018E88 | MATCHED | 152 | Float 359.0f and double 0.2 literals, whole main_2FF0 later rodata pool owned |
| func_8002A004 | MATCHED | 324 | 0.017453292f literal, including preceding vertex/display-list rodata |
| func_8001CBCC | UNCHANGED | 320 | Two swapped words at +0x04/+0x08; early constant provenance still unresolved |

Deleted drafts:

- tools/scratch/nonmatching/T-022/func_80018E88.c
- tools/scratch/nonmatching/T-024/func_8002A004.c

The retained CBCC draft's header now records the exact remaining blocker.
Its body is unchanged. The brief's constants for A004 and 18E88 were swapped:
A004 uses 0.017453292f; 18E88 uses 359.0f and 0.2.

### Remaining CBCC blocker

The original CBCC load references D_80045C00 at image offset **0x362A0**,
not the later 0x38E40–0x393B0 rodata pool. A standalone literal gives identical
instructions after masking real ELF relocations, but relocates against the
compiler's .rodata section rather than D_80045C00. Installing that literal
in the current object would therefore load from the later pool and shift its
subsequent contents. The T-040 standalone result alone does not establish a
linked match. Assigning a second disconnected .rodata range to the same
object cannot independently place portions of its single .rodata section.
I did not split or move unrelated source bodies to manufacture a new TU.

Natural extern/const-extern, array, local-factor and operand-order forms were
checked; none fixes the schedule with the correct external address. No inline
asm, register bindings, hardcoded-address replacement or build transformation
was retained. `rotation_probe.py` and `rotation_probe.txt` reproduce the
relocation distinction and the two-word external-load result.

## Other float/switch drafts

Reports T-020/022/024/026/027/032/033/035/036/040 and TRACKING were searched,
and main drafts were scanned for float literals and switches. `screen.py`
screened 72 drafts, 45 of which compile standalone. `screen_context.py`
retried the other 27 within copies of their current owning source TUs;
13 more compile there, and 14 still require declaration/type reconciliation.
These retries write only /tmp objects and never modify source TUs.

No additional screened function has zero non-relocation instruction differences.
Large rendering/audio switches have instruction/size differences in addition
to ownership issues; e.g. 21B6C, 249DC, 26B38 and 42198. No other ownership
range or draft implementation was changed. Screening is diagnostic, not a
proof that all possible C forms were exhausted. Counts mask only actual ELF
HI16/LO16/26 relocation fields and compare corresponding emitted words; an
oversized body extends into following original bytes. Exact body lengths and
raw compile failures are retained in `screen.json`.

| Function | Result | Differing words / screen note |
|---|---|---|
| func_8001808C | UNCHANGED | Compile blocked by declarations/types; see screen.json |
| func_80018664 | UNCHANGED | 287 (TU context) |
| func_80018AE0 | UNCHANGED | Compile blocked by declarations/types; see screen.json |
| func_80018E88 | MATCHED | Full linked image validated; see above |
| func_80018F20 | UNCHANGED | Compile blocked by declarations/types; see screen.json |
| func_800191F0 | UNCHANGED | 123 (TU context) |
| func_800193DC | UNCHANGED | Compile blocked by declarations/types; see screen.json |
| func_80019880 | UNCHANGED | Compile blocked by declarations/types; see screen.json |
| func_8001AA90 | UNCHANGED | 62 (TU context) |
| func_8001AD04 | UNCHANGED | 249 (TU context) |
| func_8001B134 | UNCHANGED | 228 (TU context) |
| func_8001B620 | UNCHANGED | Compile blocked by declarations/types; see screen.json |
| func_8001BB64 | UNCHANGED | 195 (TU context) |
| func_8001C5AC | UNCHANGED | Compile blocked by declarations/types; see screen.json |
| func_8001CBCC | UNCHANGED | 2 (standalone) |
| func_8001D7E4 | UNCHANGED | Compile blocked by declarations/types; see screen.json |
| func_8001E33C | UNCHANGED | 602 (TU context) |
| func_8001EC74 | UNCHANGED | Compile blocked by declarations/types; see screen.json |
| func_80028A00 | UNCHANGED | Compile blocked by declarations/types; see screen.json |
| func_800297A4 | UNCHANGED | 180 (standalone) |
| func_80029AB0 | UNCHANGED | 64 (standalone) |
| func_80029BE0 | UNCHANGED | 260 (standalone) |
| func_8002A004 | MATCHED | Full linked image validated; see above |
| func_8002AB90 | UNCHANGED | 199 (standalone) |
| func_8002AEE4 | UNCHANGED | 71 (standalone) |
| func_8002B7E0 | UNCHANGED | 2 (standalone) |
| func_8002B9B4 | UNCHANGED | 10 (standalone) |
| func_8002BBD0 | UNCHANGED | 1913 (standalone) |
| func_8002DDD4 | UNCHANGED | 102 (standalone) |
| func_8002E150 | UNCHANGED | 177 (standalone) |
| func_8002E724 | UNCHANGED | 581 (standalone) |
| func_8002F45C | UNCHANGED | 76 (standalone) |
| func_8002FB80 | UNCHANGED | 101 (standalone) |
| func_8002FDA0 | UNCHANGED | 143 (standalone) |
| func_800330B0 | UNCHANGED | 499 (standalone) |
| func_80035F10 | UNCHANGED | 146 (standalone) |
| func_80037C3C | UNCHANGED | 531 (standalone) |
| func_8003846C | UNCHANGED | 318 (standalone) |
| func_80039C08 | UNCHANGED | 150 (standalone) |
| func_8003D9BC | UNCHANGED | 521 (standalone) |
| func_8003E1DC | UNCHANGED | 339 (standalone) |
| func_8003EF90 | UNCHANGED | 222 (standalone) |
| func_80021B6C | UNCHANGED | 1709 (TU context) |
| func_800241BC | UNCHANGED | 166 (standalone) |
| func_80024714 | UNCHANGED | 104 (TU context) |
| func_800249DC | UNCHANGED | 63 (standalone) |
| func_80024B0C | UNCHANGED | 93 (standalone) |
| func_80026B38 | UNCHANGED | 1183 (TU context) |
| func_80027E1C | UNCHANGED | 238 (standalone) |
| func_8000FA80 | UNCHANGED | Compile blocked by declarations/types; see screen.json |
| func_8001178C | UNCHANGED | Compile blocked by declarations/types; see screen.json |
| func_80012950 | UNCHANGED | 56 (standalone) |
| func_80012B7C | UNCHANGED | 387 (standalone) |
| func_8001346C | UNCHANGED | 170 (standalone) |
| func_80013CD8 | UNCHANGED | Compile blocked by declarations/types; see screen.json |
| func_800142E0 | UNCHANGED | 518 (standalone) |
| func_80014D5C | UNCHANGED | 395 (standalone) |
| func_80015450 | UNCHANGED | 68 (standalone) |
| func_80015594 | UNCHANGED | 328 (standalone) |
| func_80016078 | UNCHANGED | 112 (standalone) |
| func_80016258 | UNCHANGED | 200 (TU context) |
| func_80016910 | UNCHANGED | 74 (standalone) |
| func_80016BE0 | UNCHANGED | 316 (TU context) |
| func_800170C4 | UNCHANGED | 266 (standalone) |
| func_80017378 | UNCHANGED | 458 (TU context) |
| func_80017A68 | UNCHANGED | 155 (standalone) |
| func_80017D6C | UNCHANGED | 194 (standalone) |
| func_800405E4 | UNCHANGED | Compile blocked by declarations/types; see screen.json |
| func_800407B4 | UNCHANGED | 168 (standalone) |
| func_80040A4C | UNCHANGED | 22 (standalone) |
| func_80041978 | UNCHANGED | 16 (standalone) |
| func_80042198 | UNCHANGED | 130 (standalone) |

## Validation

`make clean && make extract && make all && make progress` passed.
The ROM SHA1 remains `ba52e91b44450c548467044b26951353dc491e04`.
Main (`81736d32e8cda8f399b319a49250dff972b81af8`), ovl_7DF8 and
ovl_7E00 each printed OK; all three images are byte-identical.
`git diff --check` passed. T4 increases by 2 functions / 476 bytes.
Generated progress files and overlay undefined-symbol files are restored after
recording results; tools/progress/status.csv is untouched. Prerequisites are
symlinks to /home/rodri/Projects/killer-instinct-gold-n64; ROM bytes were never
copied into git. Source changes are local to the two promoted functions and
one extern declaration. No boot/overlay source or config was edited.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 44,232 (13.86%) | 44,232 (13.86%) | 0 | 328 | 0 | 234 | 437 (138,092) |
| boot | 8,468 | 2,812 (33.21%) | 2,812 (33.21%) | 0 | 6 | 0 | 15 | 99 (16,028) |
| main | 173,204 | 28,684 (16.56%) | 28,684 (16.56%) | 0 | 155 | 0 | 135 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 12,736 (9.27%) | 12,736 (9.27%) | 0 | 167 | 0 | 84 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
