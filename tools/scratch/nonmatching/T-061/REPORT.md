# T-061 — sol-C23: declaration and ABI pass

Uncommitted work for lead review. **16/16 attempted: 1 MATCHED (172 bytes), 2 IMPROVED, 13 UNCHANGED.**

Read TRACKING.md, latest WORKLOG.md, Makefile, and T-056/T-053/T-057/T-048/T-050/T-043 reports before experiments. Missing local prerequisites were symlinked from `/home/rodri/Projects/killer-instinct-gold-n64`. No ROM content was copied into git.

## Method

Used production IDO 5.3 `-O2 -mips2` flags and each function's existing TU prefix, including its matched definitions and declarations, through the T-056 `tu.py` method. Copies of `probe.py`, `tu.py`, and `ad.py` use isolated `/tmp/t061-probe` filenames. `baseline.json` records fresh original draft scores. Scores count differing aligned words plus missing/extra words, masking actual ELF relocations. Only the integrated match has linked-image validation; improved drafts remain nonmatching.

Prior exhaustive code-shape sweeps were not rerun wholesale. Experiments focused on ABI, global/record types, callee definitions, removing unnecessary locals, and focused command experiments after a new improvement.

## Per-function results

| Function | Result (words old→new) | Draft bytes old→new / target | Attempt and remaining issue |
|---|---|---|---|
| func_801C51F8 | UNCHANGED (2) | 160→160 / 160 | Sized/aligned symbol declarations and Gfx union alignment leave the first address addiu/opcode ori exchange unchanged. |
| func_801BF720 | UNCHANGED (2) | 104→104 / 104 | Enum input/result and union result storage do not recover the default result in v1 followed by the return move. Existing TU rodata ownership is sufficient. |
| func_801BF914 | UNCHANGED (2) | 116→116 / 116 | Same type/storage experiments; default-result register and return delay slot remain. |
| func_801B695C | UNCHANGED (4) | 268→268 / 268 | Frame/index lifetime and record/array-of-96-byte-frame declarations tested, together with local widths and memcpy length type. Best remains four frame/argument-offset words: frame 0x30 versus target 0x28. Extra-argument diagnostic candidates were discarded. |
| func_801B6A68 | UNCHANGED (20) | 368→368 / 368 | Global symbol alignment, command union alignment, and full-command representations retain constant/register and texture-address scheduling differences. |
| func_801C6A80 | IMPROVED 30→8 | 292→292 / 292 | Local `u32 *phase = &D_802921D4` recovers accumulator address allocation. Checked func_8002A8C4's matched definition: it is `void(void)`; corrected the draft and removed its spurious argument. Byte flag D_802D3984's load/store base reuse remains different. |
| func_801C71FC | MATCHED 38→0 | 176→172 / 172 | Real ABI is `(s32, u64)`, with the second argument aligned into a2/a3. `u64 D_802D3678[]` and one full-state assignment reproduce both entry spills and final stores. Struct and manually split-word approaches were worse. Integrated and deleted draft. |
| func_801B2010 | UNCHANGED (23) | 420→420 / 420 | Representative: checked lerp/vertex helper definitions; typed 128-entry vertex arrays, callee pointer types, global array/pointer forms, and Gfx union alignment. Counter address/predicate allocation and command scheduling remain. |
| func_801B21B4 | UNCHANGED (23) | 420→420 / 420 | Independently compiled TU baseline and typed vertex/global symbol experiments. Same counter and command differences. |
| func_801B2358 | UNCHANGED (23) | 420→420 / 420 | Independently compiled TU baseline and typed vertex/global symbol experiments. Same counter and command differences. |
| func_801B24FC | UNCHANGED (23) | 420→420 / 420 | Independently compiled TU baseline and typed vertex/global symbol experiments. Same counter and command differences. |
| func_801B26A0 | UNCHANGED (23) | 420→420 / 420 | Independently compiled TU baseline and typed vertex/global symbol experiments. Same counter and command differences. |
| func_801B2844 | UNCHANGED (23) | 420→420 / 420 | Independently compiled TU baseline and typed vertex/global symbol experiments. Same counter and command differences. |
| func_801B29E8 | UNCHANGED (22) | 420→420 / 420 | Independently compiled TU baseline and typed vertex/global symbol experiments. Same differences, retaining its global float start value. |
| func_801CC3BC | UNCHANGED (88) | 364→364 / 360 | Verified no-argument func_801CBF8C and one-argument Pfs checker. Tried flags pointer/array declarations, full-width mask types, string arrays, and common-return error chain. No valid improvement; an 84-word candidate narrowed the mask and was rejected. Saved flags/mask registers and error-chain scheduling remain. |
| func_801C2D34 | IMPROVED 95→6 | 548→552 / 552 | Reuse arg1 for transformed x rather than introducing var_s2. This recovers saved registers, matrix call setup, and the correct size. Represent the third command with a Gfx-style union's u64 member. Remaining six words are first/final command stores and final address/opcode materialization. Explicit index/render-state pointer locals were worse. |

## Declaration changes and ownership

The only production source integration is func_801C71FC in `src/ovl_7DF8/ovl_7DF8_190B0.c`. Added its local extern declarations, including `u64 D_802D3678[]`, and used the verified two-argument signature. Existing matched functions in that TU still match in the linked build. Other TUs' callback declarations are unchanged.

Draft-only changes: func_801C6A80's no-argument audio prototype and local phase pointer; func_801C2D34's 8-byte-aligned command union and removal of the extra coordinate local. Both improved drafts were updated in their original directories.

Deleted draft: `tools/scratch/nonmatching/T-021/func_801C71FC.c`.

No T-060 function was edited. No main, boot, ovl_7E00, YAML, Makefile, status.csv, TRACKING.md, or WORKLOG.md edits. No inline assembly, register bindings, compiler changes, or new rodata ownership. No commits.

## Final validation

`make clean && make extract && make all && make progress` passed (exit 0) on final source. ROM and all three executable images are byte-identical:

- ROM: `ba52e91b44450c548467044b26951353dc491e04`
- main: `81736d32e8cda8f399b319a49250dff972b81af8`
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`

`git diff --check` passed. Generated docs/functions.csv and docs/progress.html were restored after recording the output. T4 increases 264→265; matched bytes increase by 172.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 56,016 (17.55%) | 56,016 (17.55%) | 0 | 297 | 0 | 265 | 437 (138,092) |
| boot | 8,468 | 8,108 (95.75%) | 8,108 (95.75%) | 0 | 1 | 0 | 20 | 99 (16,028) |
| main | 173,204 | 31,772 (18.34%) | 31,772 (18.34%) | 0 | 145 | 0 | 145 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 16,136 (11.74%) | 16,136 (11.74%) | 0 | 151 | 0 | 100 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
