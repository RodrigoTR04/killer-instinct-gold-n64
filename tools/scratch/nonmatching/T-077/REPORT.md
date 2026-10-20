# T-077 — sol-C29: clone-family counter/lerp investigation

**0 MATCHED, 7 IMPROVED, 6 UNCHANGED.** No commits. Family A improves to 14 differing words for every sibling; Family B remains 65. Both families remain nonmatching scratch drafts. No GLOBAL_ASM was replaced and no draft was deleted.

Read docs/TRACKING.md, latest docs/WORKLOG.md, Makefile, and the complete T-048/T-053/T-057/T-061/T-071/T-074/T-067/T-056 reports. Missing baserom.us.z64, ROMs, .venv and tools/ext were symlinked from `/home/rodri/Projects/killer-instinct-gold-n64`. No ROM was copied into git.

## Instruction-level Family A analysis

Offsets below are relative to func_801B2010. This is the original assembly, not the draft's generated assembly. The counter is signed 32-bit; the entry and completion flags are unsigned bytes. There is no shared counter base in the target. The load uses `lui a2; lw a2,lo(a2)`, and stores use symbolic `lo(at)` operands. The counter predicate uses **signed slti**, followed by ordinary **beqz**, not sltiu, slt, or a branch-likely instruction.

| Offset | Instruction | Meaning |
|---|---|---|
| 00 | lui t6,hi(D_801D308C) | Entry flag address high half |
| 04 | lbu t6,lo(D_801D308C)(t6) | Unsigned entry flag |
| 08 | addiu sp,sp,-0x28 | 40-byte frame |
| 0C | sw s0,0x18(sp) | Save display-list cursor owner register |
| 10 | slti at,t6,2 | Entry flag is below 2 |
| 14 | or s0,a0,zero | Preserve first argument |
| 18 | sw ra,0x1C(sp) | Save return address |
| 1C | sw a1,0x2C(sp) | Home second argument |
| 20 | sw a2,0x30(sp) | Home matrix pointer |
| 24 | bnez at,+0x34 | Enter animation when flag < 2 |
| 28 | sw a3,0x34(sp) | Home fourth argument in branch delay slot |
| 2C | b,+0x190 | Early return path |
| 30 | or v0,zero,zero | Return zero in delay slot |
| 34 | lui a2,hi(D_801D309C) | Counter load high half, directly in eventual lerp argument register |
| 38 | lw a2,lo(D_801D309C)(a2) | Old counter |
| 3C | lui at,hi(D_801D309C) | Store high half for late branch |
| 40 | addiu a3,zero,1 | Lerp denominator |
| 44 | slti v0,a2,1 | Signed old-counter predicate |
| 48 | beqz v0,+0x74 | Skip lerp if old counter >= 1 |
| 4C | addiu a2,a2,1 | Increment on both paths, in ordinary branch delay slot |
| 50 | lui at,0xC0C0 | -6.0f bits |
| 54 | mtc1 at,f12 | First float argument loaded first |
| 58 | lui at,0xC316 | -150.0f bits |
| 5C | mtc1 at,f14 | Second float argument |
| 60 | lui at,hi(D_801D309C) | Restore store high half after float constant materialization |
| 64 | jal func_801B19F0 | Call actual lerp helper |
| 68 | sw a2,lo(D_801D309C)(at) | Store incremented counter in call delay slot |
| 6C | b,+0x84 | Join with late branch |
| 70 | mov.s f2,f0 | Preserve lerp result |
| 74 | sw a2,lo(D_801D309C)(at) | Late branch counter store |
| 78 | lui at,0xC316 | Late branch -150.0f bits |
| 7C | mtc1 at,f2 | Late branch result |
| 80 | nop | Float-load delay before joined code |

At +0x84 the target loads the signed z coordinate into t7, constructs x = position + 25.0f, and calls guTranslate. Its later vertex helper, display commands and completion test already match under relocation masking in the incoming draft. All final A drafts still match from +0x84 onward.

The owning TU defines `func_801B19F0(f32, f32, s32, s32)` as `((end-start)*((f32)count/(f32)duration))+start`; func_801AFA80 is its earlier per-TU copy. The target has a real `jal func_801B19F0`, so inlining and f64 arithmetic are not consistent with the observed code. Both float constants are loaded with lui/mtc1, in start-then-end order. There is no double intermediate or double argument in this region.

The retained C reads the old counter into ordinary arg1, tests it, and passes `counter_global = ++arg1` as the third lerp argument. The other branch increments arg1 and stores it separately. This preserves the old-counter test and the new-counter lerp input, with one increment/store per execution. It has no unsequenced access to arg1. Compared with the incoming predicate/common-store draft, it recovers three aligned words (two for the final sibling).

**Remaining mismatch:** IDO retains `&counter_global` in v1, loads old counter into v0, uses `bgtzl v0` with an increment only in the taken delay slot, and increments again on the other path. It moves the new value into a2 in the call delay slot. The target instead retains the value in a2, computes its predicate in v0, increments once before either branch store, and uses symbolic stores through at. The final A mismatch offsets are recorded per sibling in remaining-offsets.json; for 2010 they are 34,38,3C,44,48,4C,60,64,68,6C,70,74,78,80 (hex). This is a smaller screen, not a solved prefix.

## Hypotheses tested

All screens used production IDO 5.3 `-O2 -mips2` flags and the owning TU prefix (matched definitions and declarations, GLOBAL_ASM pragmas stripped). Counts are aligned differing words plus word-count delta, masking actual ELF relocation fields. They are not behavior validation or resolved-link matching. The scripts retain generators; bulky compiler outputs and per-candidate logs are not retained.

| Experiment | Screens | Hypotheses and outcome |
|---|---:|---|
| experiment.py | 432 | Explicit predicate vs postfix/prefix increment; predicate truth vs equality; arg1/arg3/fresh counter; signed/unsigned local; common vs branch stores; four statement/brace layouts. No improvement. |
| storage.py | 384 | Extern scalar, defined scalar, file-static scalar, one-element array, struct member, offset struct member; volatile scalar/struct diagnostics; separate stores and multiple layouts. No improvement. Volatile was not retained. |
| conditional.py | 384 | Conditional operator, inverted conditional, comma-expression setup, preincrement, postfix comparison, explicit predicate, ordinary if; f32/f64 late constants and argument assignment; expression line boundaries. No improvement. |
| branch.py | 512 | Move increment into branches, into call argument, or into assignment used as call argument; compare before increment; inverted if and conditional forms; arg1/arg3/local/global counter. Assignment inside third lerp argument improves 17→15 then 14 with layout. |
| predicate.py | 672 | s32/u32/u8/s16 predicates, argument reuse, truth vs equality, common or branch stores, direct postfix and layouts. No further improvement. |
| limit.py | 672 | Explicit denominator/limit in ordinary arg1/arg3/local; compare against that limit; equality/bit-mask predicate forms; pre/postincrement and expression layouts. No further improvement. |
| lerp.py | 384 | Real helper, earlier identical helper, inline f32 expression, inline f64 expression, f64 constants converted by prototype, assignment/comma/compound-assignment forms, denominator argument evaluation and layouts. No further improvement. Earlier helper candidates are diagnostic only: their call target is wrong despite relocation masking. |
| switch.py | 960 | Switch on predicate, case 0/1/default order, explicit predicate switches, boolean float local, direct if and expression layouts. No further improvement. |
| bitfield.py | 960 | Signed 32-bit bitfield, union/struct member, array, static/defined scalar, volatile bitfield diagnostic; direct increment, common/branch assignment and conditional forms. No further improvement. |
| reuse.py | 1,152 | Reuse predicate as lerp denominator on its true path; local/argument/alpha predicate; separate/common stores, conditional expression and layouts. No further improvement. |
| static local diagnostic | 9 | Function-static s32/u32/volatile counter, implicit/explicit zero and one initialization. No improvement; no symbol-storage changes retained. |
| install.py | 2,100 | 300 layouts per sibling around the improved branch block, independently preserving every sibling's constants. Readable ordinary multiline layout wins immediately for all seven, at 14 words/420 bytes. |
| family_b.py | 480 | Counter/predicate forms, branch-local stores, assignment in lerp argument, explicit new counter argument; u32/u16/u8 conversion result, u16 late color, separate old-alpha diagnostic, full-body layouts. No improvement over 65 words/536 bytes. |

Some generator candidates intentionally test narrowed conversion types, changed signedness, different storage, extra increments, or incomplete switch coverage. Those are diagnostic hypotheses, not proposed equivalent C, and none was installed. Only the readable branch-local assignment transformation was retained. Probe artifacts use PID-specific /tmp paths; final candidates were independently recompiled by inspect.py. No inline asm, register-variable tricks, #line, compiler flag changes or production declaration changes.

## Family B analysis and limitation

The entry has the same 0x28 frame and argument homes as A, but returns zero while D_801D3088 < 2. At +0x34/+0x38 it loads the signed counter directly into a2; +0x3C materializes its symbolic store high half in at. At +0x40 it constructs FA000000 in t9, +0x44 computes `slti v0,a2,10`, +0x48 uses ordinary beqz, and +0x4C increments a2. The early path loads **255.0f into f14 first**, restores the store high half, loads zero into f12 with mtc1 zero, stores a2, and calls lerp with a3=10 in the delay slot. This float-load order differs from A because the first float argument is zero.

The result conversion is the compiler's unsigned float-to-integer sequence: saves/restores FCSR in t7, uses a0 for conversion status/result, and handles the 2^31 subtraction path. The grayscale byte is kept in t1 and replicated through shifts; the final alpha byte is kept separately in t0 across branch convergence and saved at sp+0x27 across guTranslate. Late-path assembly reads the **old sp+0x27 byte before assigning alpha=255**. The incoming scratch draft models that as an uninitialized alpha read. This unresolved C undefined behavior is another reason it cannot be promoted on a merely improved instruction score. Changing it to an initialized alpha or a distinct uninitialized local did not solve the screen, and no such change was retained.

No A match was found to transfer to B. B's representative received the 480 dedicated screens above; each of its six siblings received an independent final baseline check. No B draft was edited.

## Per-function disposition

| Function | Result | Old → new words | Final / target bytes |
|---|---|---:|---:|
| func_801B2010 | IMPROVED | 17→14 | 420 / 420 |
| func_801B21B4 | IMPROVED | 17→14 | 420 / 420 |
| func_801B2358 | IMPROVED | 17→14 | 420 / 420 |
| func_801B24FC | IMPROVED | 17→14 | 420 / 420 |
| func_801B26A0 | IMPROVED | 17→14 | 420 / 420 |
| func_801B2844 | IMPROVED | 17→14 | 420 / 420 |
| func_801B29E8 | IMPROVED | 16→14 | 420 / 420 |
| func_801B2EF4 | UNCHANGED | 65→65 | 536 / 536 |
| func_801B310C | UNCHANGED | 65→65 | 536 / 536 |
| func_801B3324 | UNCHANGED | 65→65 | 536 / 536 |
| func_801B353C | UNCHANGED | 65→65 | 536 / 536 |
| func_801B3754 | UNCHANGED | 65→65 | 536 / 536 |
| func_801B396C | UNCHANGED | 65→65 | 536 / 536 |

Updated only the seven A drafts in T-025, plus this task's report/scripts/results. Deleted drafts: **none**. Production sources and declarations, other workers' functions, main, boot, ovl_7E00, YAML, Makefile, tools/progress/status.csv, TRACKING and WORKLOG are unchanged. Generated progress documents have no diff.

## Final verification

`make clean && make extract && make all && make progress` **passed**. ROM and all executable images are byte-identical, preserving all previously matched functions:

- ROM: `ba52e91b44450c548467044b26951353dc491e04`
- main: `81736d32e8cda8f399b319a49250dff972b81af8`
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 69,508 (21.78%) | 69,508 (21.78%) | 0 | 273 | 0 | 289 | 437 (138,092) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 173,204 | 43,240 (24.96%) | 43,240 (24.96%) | 0 | 127 | 0 | 163 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 17,800 (12.95%) | 17,800 (12.95%) | 0 | 146 | 0 | 105 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
