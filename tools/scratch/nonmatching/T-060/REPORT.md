# T-060 — sol-B20: declaration-first ovl_7DF8 pass

All 15 requested functions were attempted in the requested order. **0 MATCHED, 5 IMPROVED, 10 UNCHANGED.** Only scratch drafts and this task's probe/report files changed; no production source or YAML edits were needed. No commits were made.

Scores use T-056's relocation-masked differing aligned words plus instruction-count delta. Every candidate was compiled with IDO 5.3 production flags in its owning TU's preceding C context using `tu.py`. This is a screening metric, not linked-match evidence. None reached zero, so every GLOBAL_ASM remains in place.

| Function | Result | Final bytes / target | Attempts and remaining differences |
|---|---|---:|---|
| func_801C4E38 | UNCHANGED (2) | 556 / 556 | Tried parameter widths, K&R definition, mode caches, query/callback return and parameter declarations. Still spills/reloads v0 at sp+0x18 instead of sp+0x1C. No padding or register bindings retained. |
| func_801B6528 | UNCHANGED (3) | 596 / 596 | Tried typed card pointer, explicit card cursor, index widths, local order, K&R parameters and postincrement commands. Reloaded card pointer still uses a2 instead of target a0. |
| func_801BFB40 | IMPROVED 12→8 | 200 / 200 | Move pair loads/copy before the initialization stores. Tried chained byte clears, field/store orders, explicit copy temporaries and array declarations. Temporary numbering and v0/v1 base assignments remain. |
| func_801B446C | UNCHANGED (34) | 292 / 292 | Tried TU-consistent unsigned selection table, flag/bit/choice/position widths and direct versus cached flag accesses. Base-pointer retention and flag/store scheduling remain. |
| func_801B1210 | UNCHANGED (39) | 284 / 284 | Tried alpha widths, explicit one-argument query prototype and both command-store orders. Alpha/global/call register allocation and scheduling remain. |
| func_801C7998 | UNCHANGED (55) | 220 / 256 | Tried narrow/wide result, explicit u64 local, volatile local, signed/unsigned widened switch expression. High-word/stack setup and narrow increment sequence remain. No rodata split needed while retained as asm. |
| func_801C35D8 | IMPROVED 65→5 | 384 / 384 | Give renderer its three-argument prototype, use typed postincrement command cursor, explicit if/else visibility assignment and direct alpha updates. Tried command order, argument arithmetic and loop initialization orders. Remaining five words concern initial command scheduling, loop initialization and pointer-add operands. |
| func_801C0610 | UNCHANGED (71) | 372 / 372 | Tried command-store orders and matrix-base expressions. Display-list/matrix address registers and scheduling remain; retained original accesses. |
| func_801BBB60 | UNCHANGED (71) | 296 / 292 | Tried signed/unsigned 16/32-bit palette counters and indexed palette initialization. Unrolling, stores and base scheduling remain. |
| func_801C6D40 | UNCHANGED (74) | 316 / 300 | Tried direct byte phase updates, phase-local widths and removing unused extra call arguments. Phase/control-flow/unsigned conversion allocation remains. |
| func_801C7CD0 | IMPROVED 74→63 | 380 / 380 | Test global replay, initialize it if zero, then load replay. Tried mode widths and callee argument counts. Mode/global/call register allocation and scheduling remain. |
| func_801C49A8 | UNCHANGED (85) | 548 / 548 | Tried mode-cache widths and shared command cursor. Frame, flag/argument spills and call scheduling remain. |
| func_801C5064 | UNCHANGED (93) | 404 / 404 | Tried count widths, coordinate expression grouping and multiply order. Frame, saved float/integer registers and text-call scheduling remain. |
| func_801C3E40 | IMPROVED 96→88 | 504 / 504 | Byte ring index and slot, consistent with masking at 255. Tried cached triangle pointer and separate index/slot widths. Vertex updates, command registers and scheduling remain. |
| func_801C17D0 | IMPROVED 105→103* | 436 / 448 | Use TU's existing `u8[][11]` tables and index rows directly; correct score callee's third argument to s32 (original loads a word). Tried branch-local table pointers, value/character widths, output cursor forms and 64-bit zero literals. Stat branches, frame/register allocation and result comparison remain. |

*105 is the historical T-048/T-056 reported score. The incoming draft actually fails to compile in the current TU context because its flat stat-table declarations conflict with the already integrated two-dimensional declarations before func_801C1704. The repaired draft compiles at 103; this is not a fresh apples-to-apples 105 baseline.

## Declaration changes and draft disposition

- All declaration changes are confined to drafts; already matched functions and production declarations are untouched.
- func_801C35D8: `func_801C3758(CloudCmd **, T030Cloud *, s32)` replaces unspecified arguments. `CloudCmd` contains the two 32-bit display-command words; the cloud retains its original 12-byte layout and signed alpha byte.
- func_801C17D0: remove conflicting flat declarations of the TU-owned stat arrays, reuse `D_80128310[][11]` / `D_80128328[][11]`, and declare the third func_801BEA74 argument s32 rather than u8.
- Updated drafts in place: T-023/func_801BFB40.c, T-023/func_801C17D0.c, T-030/func_801C35D8.c, T-030/func_801C3E40.c, T-030/func_801C7CD0.c.
- Deleted drafts: **none**. No matches were integrated; no rodata ownership changes were made.

## Probe tools

`probe.py`, `tu.py`, `ad.py` and `sweep.py` are the T-056 tools with a separate `/tmp/t060-probe` workspace. `first.py`, `mid.py`, `refine.py`, `last.py`, `arrays.py` and `cloud*.py` retain the candidate experiments (run from repository root; scripts update a draft only on a lower score). Their original inputs are the incoming git versions; rerunning on the final drafts starts from the improved candidates. `results.json` records the final fresh scores, sizes, owning TUs and paths.

Local prerequisites were symlinked from `/home/rodri/Projects/killer-instinct-gold-n64`. ROM contents were neither copied nor added to git.

## Final verification

`make clean && make extract && make all && make progress` passed (exit 0). ROM SHA1: `ba52e91b44450c548467044b26951353dc491e04`; byte comparison against baserom passed. All images passed:

- main: `81736d32e8cda8f399b319a49250dff972b81af8`
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`

`git diff --check` passed. Generated progress and linker files have no final changes. Main, boot, ovl_7E00, all YAML files, Makefile, status.csv, TRACKING.md and WORKLOG.md are unchanged. Final progress is unchanged:

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 55,844 (17.50%) | 55,844 (17.50%) | 0 | 298 | 0 | 264 | 437 (138,092) |
| boot | 8,468 | 8,108 (95.75%) | 8,108 (95.75%) | 0 | 1 | 0 | 20 | 99 (16,028) |
| main | 173,204 | 31,772 (18.34%) | 31,772 (18.34%) | 0 | 145 | 0 | 145 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 15,964 (11.62%) | 15,964 (11.62%) | 0 | 152 | 0 | 99 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
