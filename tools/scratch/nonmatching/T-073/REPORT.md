# T-073 — sol-B24: guLookAtHiliteF rodata ownership

**MATCHED: func_800330B0 (guLookAtHiliteF), 1,900 bytes.** Promoted the
T-069 exact masked-body draft into main_23750; the full linked build now
proves matching. No commits were made.

## Complete TU range evidence

All offsets are decompressed main-image offsets, end exclusive.
main_23750 text is 0x23750–0x23F80: func_800330B0 at 0x800330B0,
then guLookAtHilite at 0x8003381C, including its trailing text alignment.
Scanning both generated assembly bodies shows only func_800330B0 references
rodata; guLookAtHilite is a wrapper with no constant-pool references.

| Image offset | Address | Contents | Reference |
|---|---|---|---|
| 0x39690 | D_80048FF0 | double 0.017453292222222222, then 8 zero bytes | guPerspectiveF in main_23490 |
| 0x396A0 | D_80049000 | double 0.1, bits 3FB999999999999A | func_800330B0 load at 0x80033304 |
| 0x396A8 | D_80049008 | second double 0.1, same bits | func_800330B0 load at 0x800334A4 |
| 0x396B0 | D_80049010 | double 127.0, bits 405FC00000000000 | func_800330B0 load at 0x800335AC |
| 0x396B8 | 0x80049018 | 8 zero padding bytes | TU section alignment |
| 0x396C0 | D_80049020 | float 0.01745329238, then 12 zero bytes | guRotateF in main_24020 |

A repository-wide generated-main-assembly reference search confirms the three
moved constant symbols are used only by func_800330B0. Thus the complete
main_23750 rodata is **0x396A0–0x396C0**, with both boundaries 16-byte
aligned. The neighboring pools belong to other TUs and remain assembly-owned.

## Changes

kig.main.us.yaml splits the former main_remaining_0 range as follows:

| Range | Owner |
|---|---|
| 0x39410–0x396A0 | existing main_remaining_0 data fragment |
| 0x396A0–0x396C0 | new `[0x396A0, .rodata, main_23750]` |
| 0x396C0–0x39D30 | new main_after_23750 data fragment |

The new assembly fragment uses `type: data` and
`linker_section_order: .rodata`, preserving every original address and numeric
assembly jump-table entry. No symbol file edits or force_migration/function_owner
hints are needed: the retained guLookAtHilite wrapper uses none of the pool.
Regenerated linker_scripts/*.undefined_syms.txt files were kept; they have no
net changes.

src/main/main_23750.c contains the T-069 SDK-derived ordinary C body and its
Light/LookAt/Hilite layouts, replacing only func_800330B0's GLOBAL_ASM.
The source retains libreultra lookathil.c provenance. guLookAtHilite remains
GLOBAL_ASM. No inline asm, register bindings, manual padding, or compiler
changes were introduced.

Deleted matched draft: `tools/scratch/nonmatching/T-026/func_800330B0.c`.

## Linked validation

`make clean && make extract && make all && make progress` passed.
The linker map places main_23750.c.o(.rodata) at **0x80049000, size 0x20**.
The object dump emits the exact three doubles in original order, including
the duplicate 0.1, followed by eight zero bytes. Explicit linked-image slice
comparisons also passed for 0x23750–0x23F80 and 0x396A0–0x396C0.
The full ROM and all three images are byte-identical:

- ROM: ba52e91b44450c548467044b26951353dc491e04
- main: 81736d32e8cda8f399b319a49250dff972b81af8
- ovl_7DF8: ea830aae50ff1422da60d4b7fdbfc29f03b1be39
- ovl_7E00: 2b01138a290212b9d886981e1196f7b6fb45ecdb

`git diff --check` passed. Generated progress documents were restored after
recording the table below; status.csv is untouched. No boot/overlay source or
configuration, Makefile, TRACKING, WORKLOG, or other main TU was edited.
Missing baserom.us.z64, ROMs, .venv and tools/ext prerequisites were symlinked
from /home/rodri/Projects/killer-instinct-gold-n64. No ROM was copied into git.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 69,508 (21.78%) | 69,508 (21.78%) | 0 | 273 | 0 | 289 | 437 (138,092) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 173,204 | 43,240 (24.96%) | 43,240 (24.96%) | 0 | 127 | 0 | 163 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 17,800 (12.95%) | 17,800 (12.95%) | 0 | 146 | 0 | 105 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
