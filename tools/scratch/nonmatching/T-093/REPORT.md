# T-093 — sol-A31: main finish-the-TU round

**1 MATCHED (196 bytes), 11 IMPROVED drafts, 22 UNCHANGED.** All 34 requested functions received complete-TU compilation and multiline-layout attempts. The two TUs are **not finished**. No commits.

Read TRACKING, latest WORKLOG, Makefile, T-085/T-087/T-067/T-069/T-046/T-051 and the latest relevant per-function report rows. Missing baserom.us.z64, ROMs, .venv and tools/ext were symlinked from `/home/rodri/Projects/killer-instinct-gold-n64`. No ROM was copied, staged or committed.

## Method and limits

Production IDO 5.3 `-O2 -mips2` flags throughout. Baselines reconcile old declarations against the complete current TU, including declarations after the candidate. Counts are positional instruction-word differences, masking only actual ELF HI16/LO16/26 relocations, plus missing/extra words. They are diagnostic, not behavior validation or linked-match claims. Historic standalone numbers are not directly comparable. Every retained draft was rechecked through asm-processor in the full production TU.

Used established stage/rotation, sprite, position, vertex and BSS-array declarations where available. Checked byte/halfword loads and helper call ABIs against asm. Tested the close functions first, then natural local-lifetime, pointer/command, packed-color, structure and multiline-layout alternatives. Layout probes preserved tokens and statement boundaries; retained code remains multiline. This is a bounded attempt, not an exhaustive search. Temporary candidates, object files and logs are in /tmp, not the repository.

## Per-function results

| Function | Result (old → new words) | Final / target bytes | Work and what remains |
|---|---|---:|---|
| func_80012B7C | UNCHANGED 389 | 1564 / 1576 | Dispatch/table and rendering control flow remain; BSS arrays reconciled. |
| func_800131A4 | UNCHANGED 178 | 676 / 712 | Count/order arrays reconciled; callback ABI and command-loop scheduling remain. |
| func_8001346C | UNCHANGED 165 | 696 / 704 | Switch/transform control flow and two missing words remain. |
| func_8001373C | IMPROVED 66→48 | 256 / 256 | Reuse dx for squared distance removes the frame/spill, reaching target size. FP/general register allocation and scheduling remain. Asm owner hints unchanged. |
| func_80016078 | IMPROVED 120→119 | 448 / 480 | Multiline scheduling improves one word; command/float lifetimes and eight missing words remain. |
| func_800170C4 | UNCHANGED 164 | 692 / 692 | Reused aligned TU vertex union and stage types. Partial actor view needs a cast. Aggregate-copy unrolling/register allocation remain; no improvement over the earlier standalone draft is claimed. |
| func_80017A68 | IMPROVED 151→149 | 764 / 772 | Reused TU stage/rotation types and actual byte-array globals; multiline scheduling. Setup, FP lifetimes and two missing words remain. |
| func_80017D6C | UNCHANGED 194 | 824 / 800 | Stage/rotation types reconciled; transform indexing and FP lifetimes remain. |
| func_8001808C | UNCHANGED 181 | 796 / 808 | Reused TU position/stage views and arrays; initialization/callback scheduling and three missing words remain. |
| func_80018AE0 | UNCHANGED 194 | 900 / 912 | TU arrays/stage types compile; setup scheduling, FP register allocation and three missing words remain. |
| func_80018F20 | IMPROVED 140→138 | 688 / 696 | Multiline scheduling; array globals already reconciled. Setup/constants and two missing words remain. |
| func_800191F0 | UNCHANGED 110 | 476 / 492 | Uses established actor-array address in probe. Actor-loop unrolling and four missing words remain. |
| func_800193DC | UNCHANGED 192 | 788 / 808 | TU byte arrays/stage types compile; setup/FP scheduling and five missing words remain. |
| func_8001AA90 | UNCHANGED 63 | 488 / 496 | Phase/float-call spills and two missing words remain. |
| func_8001AD04 | UNCHANGED 194 | 1088 / 1072 | Established stage/rotation layouts; floating-point/index live ranges remain. |
| func_8001B134 | IMPROVED 215→214 | 980 / 984 | Multiline scheduling improves one word; transform/float allocation remains. Asm owner hints unchanged. |
| func_8001BB64 | UNCHANGED 154 | 592 / 636 | TU color-array globals reconciled. Color loop/switch allocation and eleven missing words remain. |
| func_8001BDE0 | IMPROVED 15→13 | 316 / 316 | Multiline scheduling improves two words. Literal factors, pointer-loop view and load-order experiments did not improve further; FP callee-save allocation remains. |
| func_80015450 | UNCHANGED 68 | 328 / 324 | Extended actor view reconciled against established partial actor type in probe; rotation index reloads/loop shape remain. |
| func_80015594 | UNCHANGED 339 | 1464 / 1488 | Correct float-parameter prototype in probe; command builder/clipping/loop allocation remain. |
| func_8001CD50 | UNCHANGED 104 | 428 / 460 | Reuses T022Sprite. Corrected void, zero-argument 1CF1C and void 1D080/1D37C declarations in probe. Initialization scheduling and eight missing words remain. |
| func_8001D080 | IMPROVED 177→175 | 756 / 764 | Reuses T022Sprite before its first use; missing byte flag declaration supplied. Multiline scheduling improves two words; sprite/buffer address allocation remains. |
| func_8001D47C | UNCHANGED 141 | 748 / 748 | Existing palette array declaration reused; grayscale division/unrolling and register allocation remain. |
| func_8001D7E4 | IMPROVED 427→423 | 1720 / 1656 | Verified 244F0 only consumes a0. Removed spurious second argument and integer return prototype, 427/1724 -> 423/1720. Animation dispatch/frame parsing remain. |
| func_8001DE5C | UNCHANGED 155 | 624 / 600 | Signed scale/frame decoding and general register allocation remain. |
| func_80023EF0 | UNCHANGED 71 | 296 / 312 | Actor traversal, facing/control-flow and four missing words remain. |
| func_80024028 | UNCHANGED 49 | 284 / 284 | Tried separate first-command temporary, argument reuse/widths and packed-color expression forms; register allocation remains. |
| func_800241BC | IMPROVED 161→160 | 840 / 820 | Multiline scheduling improves one word; resource-cache view reconciled with the integrated bank prefix. DMA/slot pointer lifetimes remain. |
| func_800244F0 | **MATCHED 2→0** | 196 / 196 | Separate aligned `next` pointer places size spill/reload at 0x20 instead of 0x24. Integrated C; full ROM/images match. |
| func_800245B4 | UNCHANGED 87 | 344 / 352 | Cache view and start-address ABI reconciled in probe; interval checks/row control flow and two missing words remain. |
| func_80024714 | UNCHANGED 94 | 712 / 712 | Resource-cache byte-address view reconciled; address setup/scheduling remain. |
| func_80024B0C | UNCHANGED 99 | 440 / 464 | Matrix/command pointer scheduling and six missing words remain. |
| func_80021B6C | IMPROVED 1727→1726 | 7004 / 6896 | Reconciled position/global declarations, cache view and helper ABI in complete TU. Multiline scheduling improves one word. Large renderer/dispatch/table contents remain; current full-TU baseline differs from historical standalone counts. |
| func_800216D4 | IMPROVED 230→229 | 1040 / 1032 | Multiline scheduling improves one word; cache loops, resource dispatch and pointer lifetimes remain. |

## Integration, drafts and ownership

Replaced only `func_800244F0`'s GLOBAL_ASM in `src/main/main_D3F0.c`. Added its ROM-boundary declarations and eight-byte bank-prefix view; the body uses the existing `boot_dma(s32,s32,s32)` ABI. No code or data pool is emitted for the views. Deleted draft: `tools/scratch/nonmatching/T-032/func_800244F0.c`.

The eleven improved drafts are updated in their original directories (paths in results.json). Unchanged drafts remain original; context adaptations for their probes live in reconcile.py. `context_changes.json` records production-TU declaration substitutions needed by retained drafts. These probe-only substitutions are not production edits. In particular, the cache at D_8004D278 has several extended views; the new production declaration describes only the bank prefix used by 244F0.

func_8001373C and func_8001B134 remain asm, so their function_owner hints remain intact. No new zero-score function is blocked solely on rodata ownership. Existing YAML maps main_2FF0 rodata at 0x38E40 and main_D3F0 at 0x390A0; jump-table candidates still differ in code and table contents. No YAML edits or ownership sweep attempted. Regenerated linker_scripts/*.undefined_syms.txt have no net changes.

Skipped all explicitly reserved/huge functions, including func_80017378 and func_8001E0B4. No boot/overlay source, Makefile, status.csv, TRACKING or WORKLOG changes. No inline asm, #line, register bindings, compiler overrides or binary rewriting.

Recheck the final drafts after extraction:

```
.venv/bin/python tools/scratch/nonmatching/T-093/check_drafts.py
```

## Final validation

`make clean && make extract && make -j8 all && make progress` passed (exit 0). Parallel jobs affect build scheduling only. Full main-image equality verifies every already-matched function in both TUs remains matching. ROM and all executable images are byte-identical:

- ROM: `ba52e91b44450c548467044b26951353dc491e04`
- main: `81736d32e8cda8f399b319a49250dff972b81af8`
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`

Final draft recheck: all 33 remaining drafts reproduce their reported complete-TU scores. `git diff --check` passes. Generated docs/functions.csv and docs/progress.html were restored after capturing the table. status.csv is untouched. T4 increases 273→274; matched game bytes increase 57,240→57,436 (+196).

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 57,436 (19.81%) | 57,436 (19.81%) | 0 | 235 | 0 | 274 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 28,380 (19.71%) | 28,380 (19.71%) | 0 | 99 | 0 | 138 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 20,588 (14.98%) | 20,588 (14.98%) | 0 | 136 | 0 | 115 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
