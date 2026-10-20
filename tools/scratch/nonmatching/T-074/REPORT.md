# T-074 — sol-C28: ovl_7DF8 declaration and source-layout pass

**17/17 attempted: 0 MATCHED, 10 IMPROVED, 7 UNCHANGED numerically.** One unchanged draft was repaired to compile in the current TU. No commits. No drafts deleted and no GLOBAL_ASM replaced.

Read TRACKING.md, the latest WORKLOG.md entries, Makefile, and T-067/T-071/T-056/T-061/T-065/T-060/T-053/T-050 reports. Missing baserom.us.z64, ROMs, .venv and tools/ext were symlinked from `/home/rodri/Projects/killer-instinct-gold-n64`. ROM content was neither copied nor committed.

## Method

Production IDO 5.3 `-O2 -mips2`, using the owning TU's preceding declarations and matched C definitions with GLOBAL_ASM pragmas stripped (the T-056/T-071 probe method). Scores count differing aligned instruction words plus instruction-count delta, masking only actual ELF relocation fields. Scores are diagnostic, not linked matching or behavior validation.

Reviewed existing TU records, global access widths, matrix offsets, renderer arguments, byte flags, palette stores and counter/callee widths against the assembly. The existing drafts already contain most prior declaration fixes. Screened full-width palette counters and one shared counter, fixed fill-array sizes, signed/unsigned palette elements, matrix pointer/record declarations, renderer color/alpha widths, phase temporary widths and callee arities, aligned matrix storage, full-width Pak masks, vertex records and unsigned conversion locals. Declaration candidates were followed by token-preserving layouts; the second full layout sweep starts from the best declaration candidates. No production declaration changes were needed or retained.

The initial and follow-up sweeps screened 5,401 layouts across all 17 functions. Declaration screens added 330 compiles and targeted follow-ups 700; two refinement passes split shared statement/brace boundaries wherever scores survived. The initial sweep's 159 compile failures for C17D0 were repaired before its follow-up sweep. Tested statements on individual lines, own-line braces, split if/else bodies, joined statement runs, deterministic mixed boundaries, declaration splitting and zero-chain splitting. Retained code uses ordinary multiline C. No inline asm, register variables, #line, volatile, flags changes or output modification.

## Per-function disposition

| Function | Result (words old→new) | Final / target bytes | Change / remaining |
|---|---|---:|---|
| func_801B446C | IMPROVED 31→28 | 292 / 292 | Own-line function and conditional braces; flag/base retention and dependent scheduling remain. |
| func_801B1210 | UNCHANGED 38→38 | 284 / 284 | Renderer/input/color widths, argument reuse and alpha-load forms plus layouts do not resolve alpha/global registers and command/call scheduling. |
| func_801C0610 | UNCHANGED 71→71 | 372 / 372 | Matrix record/pointer forms and layouts leave matrix-index/global address allocation and display-command scheduling. Later TU declaration still permits an unused extra argument; no integration attempted. |
| func_801BBB60 | IMPROVED 71→40 | 292 / 292 | One s32 counter for all palette loops and palette cursor initialized after byte fills; joined setup and color-store/increment lines. Correct target size restored. Palette base/register allocation, unrolled zero-store ordering and subsequent temporaries remain. |
| func_801C6D40 | UNCHANGED 74→74 | 316 / 300 | Callee arity, phase temporary widths, phase reset spelling and layouts screened; phase/control allocation and unsigned double conversion remain. |
| func_801C49A8 | IMPROVED 85→83 | 548 / 548 | Join first display-command stores. Frame, cached mode/flag spills and rendering-call scheduling remain. |
| func_801C3E40 | UNCHANGED 88→88 | 504 / 504 | Matrix alignment/index-width and layout screens leave vertex updates and command/global scheduling. |
| func_801CC3BC | UNCHANGED 88→88 | 364 / 360 | Full-width mask retained; unsigned mask and layout screens leave saved flags/mask allocation and error-chain scheduling. Narrow-mask candidates were excluded. |
| func_801C17D0 | UNCHANGED historical 103→103; compile repaired | 436 / 448 | Incoming draft conflicts with current TU's `T023PairB40 D_80128300`. Reuse that declaration and address its words explicitly. Fresh baseline failed compilation; repaired baseline is 103. Branch-local pointer and explicit 64-bit zero-return/layout screens do not improve it. Stat branches/frame/registers and result comparison remain. |
| func_801B1DE4 | IMPROVED 113→111 | 556 / 556 | Joined command-pointer/word-store lines. Counter/interpolation globals, vertex-helper pointer lifetime and float/register scheduling remain. |
| func_801B3B84 | UNCHANGED 114→114 | 552 / 552 | Color/conversion local widths and layouts screened; counter/global allocation, stack alpha and conversion scheduling remain. |
| func_801B2EF4 | IMPROVED 70→65 | 536 / 536 | Shared family-B multiline layout; counter predicate/base, alpha stack slot and unsigned conversion registers remain. |
| func_801B310C | IMPROVED 70→65 | 536 / 536 | Independently compiled sibling; same family-B layout and remaining issues. |
| func_801B3324 | IMPROVED 70→65 | 536 / 536 | Independently compiled sibling; same family-B layout and remaining issues. |
| func_801B353C | IMPROVED 70→65 | 536 / 536 | Independently compiled sibling; same family-B layout and remaining issues. |
| func_801B3754 | IMPROVED 70→65 | 536 / 536 | Independently compiled sibling; same family-B layout and remaining issues. |
| func_801B396C | IMPROVED 70→65 | 536 / 536 | Independently compiled sibling; same family-B layout and remaining issues. |

Family B is **not solved**. Its existing late-branch uninitialized alpha read is preserved in scratch only, as noted in T-053: the original assembly reads the old stack byte. No behavior-validity claim is made for these drafts and none was promoted. Each sibling retained its own globals, thresholds and translation coordinates.

Updated the ten improved drafts in their original directories plus C17D0's compile repair. No matched production definition changed. Main, boot, ovl_7E00, YAML, Makefile, tools/progress/status.csv, TRACKING and WORKLOG are untouched. Generated progress documents have no final diff.

`results.json` records scores, sizes and batch counts; `remaining-offsets.json` records final differing offsets and target sizes. Compact probe and experiment scripts are retained. The scripts describe staged experiments from the incoming revision; generated `.best.c` duplicates and compiler objects/logs are not retained in the repository. Deleted drafts: **none**.

## Final verification

`make clean && make extract && make all && make progress` **passed (exit 0)**. `git diff --check` passed. ROM and all three executable images are byte-identical, preserving every matched function:

- ROM: `ba52e91b44450c548467044b26951353dc491e04`
- main: `81736d32e8cda8f399b319a49250dff972b81af8`
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 67,608 (21.19%) | 67,608 (21.19%) | 0 | 274 | 0 | 288 | 437 (138,092) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 173,204 | 41,340 (23.87%) | 41,340 (23.87%) | 0 | 128 | 0 | 162 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 17,800 (12.95%) | 17,800 (12.95%) | 0 | 146 | 0 | 105 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
