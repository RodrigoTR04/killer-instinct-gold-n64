# T-064 — sol-B21

One new match: **func_8001CBCC, 320 bytes**. func_80017378 improves to
**8 differing words / 1752 bytes**, remains GLOBAL_ASM. No commits.

## TU boundaries and ownership

Offsets are decompressed main-image offsets, end exclusive.

| Text range | C object |
|---|---|
| 0x2FF0–0xCA10 | main_2FF0 (existing name retained) |
| 0xCA10–0xD3F0 | new main_CA10 |
| 0xD3F0–0x15380 | new main_D3F0 (resumed code) |

Both split points are 16-byte aligned. docs/tu_boundaries.md lists them as
possible boundaries with **zero trailing pad words**: func_8001C2D4 ends
exactly at CA10 and func_8001CD0C ends exactly at D3F0. Thus text padding
alone does not prove the original TU extent. The independent constant block
and the successful linked match support this split; no padding was invented.

main_CA10 contains func_8001C370, func_8001C43C, func_8001C534,
func_8001C5A0, func_8001C5AC (GLOBAL_ASM), func_8001CBCC (new C), and
func_8001CD0C. Declarations needed by these functions moved or were added
once in their new TU. main_D3F0 contains the remaining original functions
through the existing 0x15380 boundary, with their original C bodies and
GLOBAL_ASM stubs. A distinct resumed object is necessary because one object
cannot place its single .text section on both sides of main_CA10.

| Rodata range | Owner |
|---|---|
| 0x350B0–0x362A0 | existing main assembly data |
| 0x362A0–0x362B0 | main_CA10 .rodata: one float plus compiler padding |
| 0x362B0–0x38760 | new main_after_CA10 assembly data fragment |
| 0x38E40–0x390A0 | main_2FF0 .rodata |
| 0x390A0–0x393B0 | main_D3F0 .rodata |

Other data/rodata ownership is unchanged. The assembly fragment uses
`linker_section_order: .rodata`, following the established recipe. D_80045BEC
belongs to the preceding data; the float formerly labeled D_80045C00 is at
0x362A0 and D_80045C10 starts the following fragment. The resumed late pool
starts with func_8001D7E4's constants at 0x390A0, a 16-byte boundary.

BSS remains at 0x8004A730–0x8004A740 in main_2FF0; the preceding assembly
BSS range is unchanged. D_8004A738[8] is now u8, including its extern in
main_CA10. All previously matched functions remain byte-identical.

No symbol_addrs.main.us.txt edits were necessary. The retained force_migration
owners func_8001373C and func_8001B134 remain in main_2FF0; the other retained
owners belong to main_18440. C43C's old hints had already been removed before
this task. No owner hint points to a function moved into main_CA10 or main_D3F0.
Regenerated linker_scripts/*.undefined_syms.txt files were kept; this checkout
produced no differences in those files.

## Function results

| Function | Result |
|---|---|
| func_8001CBCC | MATCHED: literal 0.017453292f emits the original one-float block; complete linked image verifies it |
| func_8001C370 / 8001C43C / 8001C534 / 8001C5A0 / 8001CD0C | Existing C preserved across move; linked image verifies all bytes |
| func_8001C5AC | Existing GLOBAL_ASM preserved in main_CA10 |
| func_80017378 | IMPROVED, not matched: 8 relocation-masked words differ, 1752/1752 bytes |

The checked-out T-033 draft was still the old 463-word version: T-063 had
explicitly omitted the T-055 draft improvement. Recovered that improvement
from T-055/t055-original-vs-2827f78.patch and reconciled it with current array
declarations. The D_8004A688 store uses a u8 access; a signed access merges
the constant 1 and changes scheduling across the function. D_8004A738 also
needs u8 as recorded by T-055.

An endless loop with an explicit endpoint break avoids IDO's unroll/remainder
transformation. Initializing model before rot fixes three setup differences.
The remaining differences are +0x590/+0x598 (base/endpoint setup order), and
+0x59C..+0x5B0 (two increments scheduled after the four model stores rather
than before them). The rest is exact under ELF relocation masks. See
func_80017378.diff.txt; reproduce with T-055/ctx.py and the retained T-033 draft
(reference main.bin goes in /tmp/t055ref as documented by that tool).

The original loop actually processes **three** rotations: AA14 - A9D8 =
0x3C = 3 * 0x14, and three 16-byte model entries. The earlier report's
"4-iteration" description was incorrect. Pointer/struct/byte forms,
pre/post increments, explicit break/goto/continue, relational endpoints,
known bounds and counter forms were tried. Best retained form is ordinary
C; no inline asm, register binding, volatile workaround or compiler change.

Deleted draft: tools/scratch/nonmatching/T-022/func_8001CBCC.c.
Retained improved draft: tools/scratch/nonmatching/T-033/func_80017378.c.

## Validation

`make clean && make extract && make -j4 all && make progress` passed.
The parallel flag only changes build scheduling. `git diff --check` passed.
ROM SHA1: ba52e91b44450c548467044b26951353dc491e04.

- main: 81736d32e8cda8f399b319a49250dff972b81af8
- ovl_7DF8: ea830aae50ff1422da60d4b7fdbfc29f03b1be39
- ovl_7E00: 2b01138a290212b9d886981e1196f7b6fb45ecdb

All verification steps report byte identity. Generated progress documents are
retained. status.csv, boot/overlay sources and configurations, Makefile,
TRACKING and WORKLOG are untouched. Missing prerequisites were symlinked
from /home/rodri/Projects/killer-instinct-gold-n64; no ROM was added to git.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 62,696 (19.65%) | 62,696 (19.65%) | 0 | 288 | 0 | 274 | 437 (138,092) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 173,204 | 38,264 (22.09%) | 38,264 (22.09%) | 0 | 136 | 0 | 154 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 15,964 (11.62%) | 15,964 (11.62%) | 0 | 152 | 0 | 99 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
