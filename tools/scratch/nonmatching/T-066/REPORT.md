# T-066 — sol-A23: type and array-shape pass

Uncommitted for lead review. **10/10 attempted: 1 MATCHED (368 bytes), 1 IMPROVED, 8 UNCHANGED.**

Read docs/TRACKING.md, latest docs/WORKLOG.md, Makefile, and T-061/T-062/T-057/T-056/T-053 reports first. Missing baserom.us.z64, ROMs, .venv and tools/ext were symlinked from the authorized main checkout. ROM content was never copied or committed.

## Results

Scores are differing aligned instruction words plus length delta, masking ELF relocations, using IDO 5.3 production flags and the owning TU's preceding C context. The integrated match also passed the complete linked-image and ROM comparison. Improved draft scores alone do not establish linked equivalence.

| Function | Result | Final / target bytes | Type audit, experiments, and remaining issue |
|---|---|---:|---|
| func_801C4E38 | UNCHANGED (2) | 556 / 556 | Entry lbu establishes two u8 parameters; no a2/a3 wide pair. Checked matched callees and dispatcher declarations; tested K&R arguments, SDK/callee return declarations and scalar aggregate locals. Still saves/reloads the switch value at sp+0x18 instead of sp+0x1C. SDK osViBlack actually takes s32; correcting that prototype alone does not change the score. |
| func_801B6528 | UNCHANGED (3) | 596 / 596 | Card index is lw at +0xC; displacement is lh; selector tables are lbu. guTranslate has the normal pointer/f32/f32/f32 ABI, with floats passed in a1/a2/a3. Tested integer/pointer address types, const card views, matrix pointer types, texture record shapes, fourth-parameter widths, K&R and non-prototype forms. Card reload remains a0 instead of a2, plus its two dependent field loads. Narrow index diagnostics were discarded. |
| func_801C35D8 | UNCHANGED (4) | 384 / 384 | Coordinates/angles/width use lh; alpha uses lb. Callee func_801C3758 explicitly sign-extends its a2 argument to s8. Tested that prototype, record fields, full-width/narrow parameter diagnostics, scalar aggregates, command/address types and K&R. Initial command scheduling and loop initialization remain different. |
| func_801BF720 | UNCHANGED (2) | 104 / 104 | Unsigned full-word input comparisons and ordinary word result; no entry narrowing. Tested addressable result arrays/records, bitfield signedness, K&R and aggregate scalar forms. Default still folds into v0 instead of v1 followed by a return move. |
| func_801BF914 | UNCHANGED (2) | 116 / 116 | Same input/result audit and result-storage experiments. Default still uses v0 rather than target v1 and return move. |
| func_801C51F8 | UNCHANGED (2) | 160 / 160 | Pointer-to-display-list cursor, two 32-bit command halves, no callee. Tested physical matrix symbol element widths/array sizes, command word signedness and integer cursor address form. First address addiu and command ori remain exchanged. |
| func_801B695C | UNCHANGED (4) | 268 / 268 | Asset has pointer at +8; frame/bank selectors use lbu; memcpy has three word arguments (no wide pair). Tested source frame records, destination palette rows/elements, copy-context records, pointer-to-frame locals, index/local widths, parameter reuse, memcpy return/prototype forms and integer asset address. Same instructions otherwise, but frame remains 0x30 instead of 0x28, affecting entry/exit and argument-home offsets. |
| func_801B6A68 | MATCHED 20→0 | 368 / 368 | **D_802C8808 is a palette buffer with 512-byte rows.** `extern u8 D_802C8808[][512]` and `&D_802C8808[arg2][D_802C8D08[arg2] * 2]` recover every constant register and texture-address scheduling word. The data pointer remains at asset +8, row index is full-width, and return is s32 (0 or 2). Integrated into ovl_7DF8_5ED0.c. |
| func_801B446C | UNCHANGED (31) | 292 / 292 | u8 player/flags/positions and 11-byte unsigned rows agree with lbu/sb and addressing. Tested flag record/array representations, cached flag widths, result aggregates, history record shapes, K&R and assignment-expression forms. Target retains &D_802C8CE0 in t0; generated code still folds it into symbolic loads/stores, changing scheduling downstream. |
| func_801C7CD0 | IMPROVED 34→6 | 380 / 380 | **Replay local is u32**, avoiding an extra byte narrowing. Compare the stored u8 mode global for both mode branches, recovering mode narrowing, global address retention and almost all registers. Confirmed func_801CD038 is `u8(s32,s32)` from matched C and corrected the draft declaration/cast; func_801C7A98 is called with no argument. Kept the two u64 replay values. Remaining: replay-state base uses a2 instead of v1 (two address instructions and four stores). Tested global state views/pointers, replay pair records/unions/rows, signedness, pointer-local lifetimes and assignment expressions. |

## Delivered changes

- Replaced only func_801B6A68's GLOBAL_ASM in src/ovl_7DF8/ovl_7DF8_5ED0.c. No existing declaration needed changing; the new row-shaped palette declaration has no earlier declaration in the TU.
- Deleted `tools/scratch/nonmatching/T-029/func_801B6A68.c`.
- Updated `tools/scratch/nonmatching/T-030/func_801C7CD0.c` in place.
- Other eight drafts remain unchanged. No T-065 functions, main, boot, ovl_7E00, YAML, Makefile, status.csv, tracking, or worklog edits. No inline asm, register bindings, artificial padding or commits.

## Probe evidence

`probe.py`, `tu.py`, and `ad.py` are copies of the T-062 tools with isolated `/tmp/t066-*` paths. `types.py`, `abi.py`, `shapes.py`, `expressions.py`, `replay.py`, and `addresses.py` record focused experiments; compact JSON files record results. Approximately 437 generated experiments, including duplicates and compiler failures. No exhaustive statement-order permutation pass was repeated. Speculative narrowing and incompatible ABI diagnostics were discarded.

The palette-row candidate was found by `abi.py` and verified by the linked build before deleting its draft. `expressions.py` found the improved mode/replay draft; `replay.py` confirmed the six remaining words. Generators consume the incoming drafts, so scripts targeting the deleted match or the old replay baseline require those files from the parent revision. An initial state-pointer generator lookup failed after replacing its search text; corrected before the completed run. No bulky logs or compiled probes are retained in the repo.

## Final validation

`make clean && make extract && make all && make progress` passed (exit 0). The complete overlay comparison also verifies every previously matched function in the edited TU. ROM and all three executable images are byte-identical:

- ROM: `ba52e91b44450c548467044b26951353dc491e04`
- main: `81736d32e8cda8f399b319a49250dff972b81af8`
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`

Generated docs/functions.csv and docs/progress.html were restored after recording the table. status.csv is untouched for lead review. T4 increases 275→276 and matching bytes increase 62,748→63,116. `git diff --check` passed.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 63,116 (19.78%) | 63,116 (19.78%) | 0 | 286 | 0 | 276 | 437 (138,092) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 173,204 | 37,944 (21.91%) | 37,944 (21.91%) | 0 | 137 | 0 | 153 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 16,704 (12.15%) | 16,704 (12.15%) | 0 | 149 | 0 | 102 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
