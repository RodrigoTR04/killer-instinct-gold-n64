# T-051 — sol-C20: main rodata ownership round 2

**1 MATCHED (196 bytes), 2 IMPROVED drafts, 7 UNCHANGED.** All ten requested
functions were attempted. Changes are uncommitted for lead review.

## Ownership

Image offsets are end exclusive. All C rodata ranges have 16-byte-aligned
starts and ends. Remaining fragments stay `type: data` with
`linker_section_order: .rodata`; their numeric jump-table words stay intact.

| Image range | Owner |
|---|---|
| 0x350B0–0x38760 | Existing main assembly data |
| 0x38760–0x387E0 | Existing main_18440 .rodata |
| 0x387E0–0x38E00 | main_remaining_early assembly data |
| **0x38E00–0x38E40** | **New main .rodata**: FA80 doubles, 1178C jump table, padding |
| 0x38E40–0x393B0 | Existing main_2FF0 .rodata: 12B7C/1346C/21B6C/249DC tables and other constants |
| **0x393B0–0x39410** | **New main_17140 .rodata**: both 26B38 tables and padding |
| 0x39410–0x39D30 | main_remaining_0 assembly data |
| **0x39D30–0x39D60** | **New main_321A0 .rodata**: 42198 table, float, double |
| 0x39D60–0x39E10 | New main_remaining_1 assembly data |
| 0x39E10–0x3A610 | Existing gfx_data binary |
| 0x3A610–0x3A8D0 | Existing audio_data binary |

No force_migration/function_owner hint was removed or reassigned: none of
the promoted function's code owns such constants. All existing hints remain.

### 16760: BSS ownership is also necessary

D_8004A730 must be defined in the same C TU for IDO to share the stores' base
address during loop unrolling. An extern array emits 204 bytes; an ordinary
uninitialized array definition emits the exact 196-byte function.

The YAML now describes the first 0x510 bytes of main BSS, without changing
ROM/image length: assembly BSS 0x8004A230–0x8004A730, then main_2FF0 .bss
0x8004A730–0x8004A740. The preceding range remains generated assembly with
its original symbol addresses. C defines `u8 D_8004A730[8]` and adjacent
`s8 D_8004A738`; IDO supplies section-end alignment. The loop touches the
first seven array bytes. The eighth byte is the existing end sentinel at
A737, also referenced by the preceding asm function.

`size:0x8 allow_addend:True` on D_8004A730 lets splat express interior asm
references as array addends. Existing matched C assignments through the old
A730/A736 scalar declarations now use array elements 0/6. Their code stays
byte-exact. D_8004A738 is defined because it also lies in the owned BSS range.
No manual padding arrays, inline asm, register bindings, or compiler overrides
were added. Regenerated undefined-symbol files are retained, including the
overlays' added external declaration for D_8004A730.

## Per-function results

Counts below compare corresponding instruction words and mask only actual
ELF relocations. They diagnose code generation, not linked matching. Only
16760 is claimed matched, based on the full image/ROM checks. Counts for
oversized functions include words extending past the original body.

| Function | Result | Evidence / remaining blocker |
|---|---|---|
| func_8001178C | UNCHANGED | 570 words, 2296/2104 B. Reconciled missing EA9C declaration for standalone probes; signed/unsigned switch forms retain large register/control-flow differences. New main rodata ownership resolves its table placement. |
| func_80012B7C | UNCHANGED | 387 words, 1560/1576 B. Dispatch casts to s32/u32/u8 do not improve it; remaining body differences extend beyond the migrated table. |
| func_8001346C | IMPROVED **170→163** | 732→696 B, original 704 B. Moved transform rendering into cases 1/2 with a shared draw label, removing the redundant post-switch mode test. Remaining scheduling/register/control-flow differences. Updated T-033 draft in place. |
| func_80015450 | UNCHANGED | 68 words, 328/324 B. Tried cached rotation pointers, compound assignment, loop structure, and local discriminator forms. Shorter candidates lose required index reloads and do not provide a convincing improvement. **50.0 is emitted using mtc1 immediates in both original and draft; it needs no rodata slot.** |
| func_80016760 | **MATCHED** | 196 B, full linked validation. Defined the byte array in its TU and mapped its BSS; deleted the T-020 draft. |
| func_8001CBCC | UNCHANGED | 2 words at +0x04/+0x08, 320/320 B. Tried defined mutable/const data, extern array, volatile qualifiers, local factor, multiply operand order, and all xyz scaling orders. Ordinary external-address forms retain the schedule difference. Literal emits into the later pool, not original D_80045C00 at image 0x362A0. No disconnected section or unrelated TU reshuffling retained. |
| func_80021B6C | UNCHANGED | Reconciled declarations and compiled standalone: 1704 words, 6908/6896 B; unsigned switch form is worse (1712, 6920 B). This differs from T-046's TU-context metric; no improvement is claimed. Existing five migrated tables are already owned by main_2FF0. |
| func_800249DC | IMPROVED **63→10** | 312→304 B, original 304 B. Counter advances before testing the entry, and a common found label bypasses the fallback reset. Remaining loop pointer registers and compiler's equality termination versus original signed bound check. Updated T-032 draft in place. |
| func_80026B38 | UNCHANGED | 1183 words, 4792/4708 B. Reconciled counter declarations; signed/unsigned switch forms do not improve the body. Both tables now migrate into main_17140. |
| func_80042198 | UNCHANGED | 130 words, 528/536 B. Tested signed/unsigned/modulo dispatch and case order. Unsigned p shortens code but changes the original signed division behavior and is rejected. Original retains a redundant switch bounds check after AND 7; IDO -O2 removes it. New whole-TU rodata ownership resolves table/literal placement, not these instructions. |

Deleted draft: `tools/scratch/nonmatching/T-020/func_80016760.c`.

Probe scripts and JSON diagnostics are stored here. Some deliberately tested
forms change signedness/alias assumptions; these are compiler diagnostics and
were not installed as source or retained drafts. The source and two retained
draft changes use ordinary C. No assertion of exhaustive search is made.

## Validation

`make clean && make extract && make all && make progress` passed.
The ROM SHA1 is `ba52e91b44450c548467044b26951353dc491e04`; all three
images printed OK. Main is `81736d32e8cda8f399b319a49250dff972b81af8`,
ovl_7DF8 is `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`, and ovl_7E00
is `2b01138a290212b9d886981e1196f7b6fb45ecdb`.

Final linker map places D_8004A730 at 0x8004A730 and D_8004A738 at
0x8004A738. The partial main BSS ends at 0x8004A740. No ROM data was copied
or committed; prerequisites are symlinks to the authorized main checkout.
No boot/overlay source, other YAML, Makefile, tracking/worklog, or status.csv
was changed. Generated docs/functions.csv and docs/progress.html were restored
after capturing this table. All regenerated undefined_syms changes are kept.
`git diff --check` passed.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 50,844 (15.93%) | 50,844 (15.93%) | 0 | 314 | 0 | 248 | 437 (138,092) |
| boot | 8,468 | 8,108 (95.75%) | 8,108 (95.75%) | 0 | 1 | 0 | 20 | 99 (16,028) |
| main | 173,204 | 29,600 (17.09%) | 29,600 (17.09%) | 0 | 149 | 0 | 141 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 13,136 (9.56%) | 13,136 (9.56%) | 0 | 164 | 0 | 87 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
