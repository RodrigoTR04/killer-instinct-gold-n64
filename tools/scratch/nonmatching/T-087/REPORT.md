# T-087 — sol-A29: finish mostly-matched ovl_7DF8 TUs

**8 MATCHED (1,716 bytes), 5 IMPROVED, 8 UNCHANGED.** All 19 required
functions and both optional functions attempted. Changes are uncommitted.
The TUs are not finished: remaining functions stay GLOBAL_ASM.

Scores below count relocation-masked positional differing instruction words plus
the instruction-count delta (T-056 method). Improved drafts were checked in their
complete production TUs through asm-processor, not only standalone. A zero masked
score alone is not a linked-image match; C67CC is the concrete counterexample.

## Per-function results

| Function | Result, old → new words | Retained C / target bytes | Work and remaining issue |
|---|---|---:|---|
| func_801ACB1C | UNCHANGED 176 | 756 / 744 | Reused RenderState in scratch, reconciled command/context prototypes, tried explicit message-address/state pointers and multiline layouts. Saved-register lifetimes, frame and display-list scheduling remain. Original draft retained. |
| func_801AD114 | IMPROVED 159→88 | 612 / 628 | Real callback ABI is `(s32, u64)`; verified BFCBC's aligned input and byte flag. Used the actual two-argument, void B3DB0 prototype and a structured menu branch instead of the shared goto. Control flow, spills and scheduling remain. A 126-word intermediate still had an incompatible three-argument initializer declaration and was rejected. |
| func_801AD568 | MATCHED 128→0 | 556 / 556 | Uses the TU's RenderState/DisplayCommand. Separate scoped command temporaries reproduce the frame and cursor reloads; comparison operand order and command statement layouts finish scheduling. Integrated; draft deleted. |
| func_801AD7D8 | IMPROVED 132→89 | 548 / 556 | Scoped command temporaries and current boot_graphics_queue symbol. Task structure preserved. Command-cursor lowering and repeated microcode-address materialization still differ; two instructions short. |
| func_801ADA04 | IMPROVED 41→39 | 204 / 208 | Reused RenderState, corrected osViSetMode call arity, represented the pending-mode assignment in its indexed argument. Global-address reuse and branch/scheduling differences remain. Old 40-word screen excluded the missing-word penalty. |
| func_801CBBE0 | MATCHED 23→0 | 236 / 236 | ControllerStatus records with type/status/error fields and an explicit returned error-byte local recover the query-buffer stack placement. Typed queue/query prototypes. Integrated; draft deleted. No unused padding local retained. |
| func_801CC0CC | MATCHED 43→0 | 216 / 216 | Structured nested loops, separate CRC result and accumulator addition, original `(length - count) + index + base` grouping, multiline source. Uses a byte-buffer pointer. Integrated; draft deleted. |
| func_801CC1A4 | MATCHED 22→0 | 192 / 192 | Same explicit CRC/result/accumulation structure; separate expressions resolve saved-register assignment and addition operand order. Corrected later declarations to its observed integer return and byte-buffer argument. Integrated; draft deleted. |
| func_801CC3BC | UNCHANGED 88 | 364 / 360 | Checked osPfsChecker's one-argument ABI, full-width shift/mask, flag pointer and error-dispatch forms. Kept the target's unusual `(flags == 0) & mask` behavior. Mask/flag registers, frame and error scheduling remain. Draft callee name updated to the current osPfsChecker symbol. |
| func_801CC908 | UNCHANGED 13 | 424 / 424 | Original draft did not compile against the current TU. Reconciled audio/global declarations and allocation-wrapper ABI; full-TU score reproduces the prior 13. Handle/return spills and scheduling remain. Corrected draft retained in place. |
| func_801CCD74 | UNCHANGED 4 | 116 / 116 | Compared explicit old/current message values and pointers, chained clears, integer/pointer comparisons and layouts. Current/previous base and load-register selection remain. No worse candidate retained. |
| func_801CD1F0 | UNCHANGED 107 | 452 / 460 | Original draft did not compile against the current TU. Reuses T056PfsState and current osPfsNumFiles/osPfsFileState prototypes rather than a duplicate record and obsolete callee names. Saved-register allocation, cursor lifetimes and two missing instructions remain. Corrected draft retained. |
| func_801AF68C | UNCHANGED 231 | 940 / 956 | Tried the established effect layout with typed callback/list words, cached effect versus reloads, pointer-loop structure and layouts. Queue compaction/unrolling, callbacks and frame remain. The one-word flat-layout screen was not retained; final draft remains multiline. |
| func_801C4780 | MATCHED 19→0 | 84 / 84 | Real `(s32, u64)` callback ABI and u64 input-state table assignment reproduce both argument home stores and final word stores. Integrated; draft deleted. |
| func_801C780C | MATCHED 26→0 | 160 / 160 | Same aligned input ABI and full-state assignment. Checked audio/menu helper declarations against their void definitions. Integrated; draft deleted. |
| func_801C4D28 | MATCHED 6→0 | 68 / 68 | Direct indexed vector-component assignments remove scalar-local float register allocation and reproduce f4/f6/f8. Integrated; draft deleted. |
| func_801C4D6C | MATCHED 17→0 | 204 / 204 | Cache the selected list before initializing the counter; chained byte-counter assignments preserve narrowing and put list/counter in the target registers. Integrated; draft deleted. |
| func_801C6D40 | UNCHANGED 74 | 316 / 300 | Checked byte phase updates, argument reuse, unsigned-to-double expression, call arity and layouts. Reconciled its vector lvalue with the owning TU during full-TU checks. Phase/control-flow allocation and conversion scheduling remain. |
| func_801C67CC | IMPROVED 171→0, integration blocked | 692 / 692 | Reuse the unsigned time argument, one phase local, direct expressions and actual 360.0/360.0/372.0 double literals. Complete TU has zero masked instruction differences. **Not MATCHED:** its rodata is asm-owned; see below. Improved draft retained, GLOBAL_ASM restored. |
| func_801C4240 (optional) | IMPROVED 167→150 | 1344 / 1344 | Scoped command temporaries using the existing render/command layouts. Projection-record experiment did not improve it. Projection/float spill layout and global/saved-register allocation remain. |
| func_801C7310 (optional) | UNCHANGED 281 | 1264 / 1276 | Checked list-base pointer initialization, unsigned tick semantics and layouts. Audio-state/float lifetimes and dispatch scheduling remain. Signed-tick experiments were not retained. |

## C67CC rodata blocker

The original double values at 0x802948A0, 0x802948A8 and 0x802948B0 are
360.0, 360.0 and 372.0. Expressing them as literals removes the artificial local
slots and gives the exact 0x28 frame and all target instructions. The linked
experiment failed: ovl_7DF8_190B0 has no paired `.rodata` subsegment. Its new
0x20-byte constant pool instead appeared at 0x80293830, shifting later
asm-owned data and resolving the three loads to the wrong addresses.

The failed integration was removed. The final production TU still uses
GLOBAL_ASM for C67CC; only its improved draft is retained. As the user prohibited
YAML edits, this task does not migrate ownership. A follow-up can apply T-043's
whole-TU ownership recipe, including preceding constants and tables, then verify
the complete image. Extern-constant variants were also tried; the closest was
five frame-size/argument-offset words off, with a 0x40 frame.

## Declaration changes and deleted drafts

Production changes besides the eight bodies are local declarations and the
allocation wrapper func_801CC58C: it now takes an output handle pointer and returns
osPfsAllocateFile's integer status. CC908's assembly checks that returned v0;
the old void declaration prevented its draft from compiling. The wrapper's code
remains byte-identical. CC908's later forward declaration is corrected to s32.
The whole-image check verifies every previously matched function too.

Deleted drafts:

- T-019/func_801AD568.c
- T-021/func_801CBBE0.c
- T-021/func_801CC0CC.c
- T-021/func_801CC1A4.c
- T-021/func_801C4780.c
- T-021/func_801C780C.c
- T-021/func_801C4D28.c
- T-021/func_801C4D6C.c

Read TRACKING.md, latest WORKLOG.md, Makefile, T-067/T-056/T-061/T-070/T-076,
T-043, and the latest relevant per-function report rows before probing.
Missing baserom.us.z64, ROMs, .venv and tools/ext were symlinked from the authorized
main checkout. No ROM was copied or staged. No commits, inline asm, #line,
register bindings, output rewriting or compiler flag changes. No main, boot,
ovl_7E00, YAML, Makefile, status.csv, TRACKING or WORKLOG edits. T-082 functions
were not edited. Rejected probes/logs remain outside the repository in /tmp.

`check_drafts.py` compiles all 13 remaining drafts in their complete TUs and
reports the masked score. It documents scratch-only type reconciliations for
unchanged drafts. Run after extraction:

```
.venv/bin/python tools/scratch/nonmatching/T-087/check_drafts.py
```

## Final validation

`make clean && make extract && make all && make progress` passed (exit 0)
on the final source, after all integrations, formatting and declaration changes.
The ROM and all three executable images are byte-identical:

- ROM: `ba52e91b44450c548467044b26951353dc491e04`
- main: `81736d32e8cda8f399b319a49250dff972b81af8`
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`

`git diff --check` passed. Generated docs/functions.csv and docs/progress.html
were restored after recording their output. T4 increases 256→264; matched game
bytes increase 52,808→54,524 (+1,716). No commits were made.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 54,524 (18.81%) | 54,524 (18.81%) | 0 | 245 | 0 | 264 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 26,540 (18.43%) | 26,540 (18.43%) | 0 | 107 | 0 | 130 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 19,516 (14.20%) | 19,516 (14.20%) | 0 | 138 | 0 | 113 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
