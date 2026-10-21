# T-114 — sol-C42: hard residue round 3

**1 MATCHED (516 bytes): func_8002F6F4.** Remaining nine drafts unchanged. No commits.

func_801C7998 was dropped on the lead’s explicit update: T-113 already has zero instruction differences, pending rodata ownership elsewhere. It was not probed or edited.

## Method and scope

Read TRACKING, latest WORKLOG entries, overview, Makefile and tools/permuter/README first. Missing baserom.us.z64, ROMs, .venv and tools/ext were symlinked from the authorized shared checkout. No ROM was copied or added to git. No subagents were used. Production changes are limited to the listed F6F4 body and deletion of its draft; no boot, ovl_7E00, YAML, Makefile or status.csv changes.

Measurements use production IDO 5.3 -O2 -mips2 through asm-processor in the complete owning TU. Scores below count differing instruction words plus length delta, masking only actual ELF relocations. Compile errors are explicit errors, never matches. Temporary declaration reconciliation follows T-096; BF914 additionally needs its later signed prototype reconciled. No such diagnostic prototype edit is retained in production.

The per-function history below was assembled by searching **every** tools/scratch/nonmatching/*/REPORT.md for each full function name. Matching historical rows/paragraphs are preserved with their report path so measurements and hypotheses are not silently lost. Historical abbreviations within shared sections are summarized as well: T-071 tested own-line braces, joined runs, mixed boundaries, declaration/zero-chain splitting and assignment/argument layout; T-072 tested 159 initial layouts per function plus declaration/chain/readability/expression-layout probes. T-088 tested glyph return/assignment/break/goto/default/pointer forms, C4E38 selector widths/assignment sites, B695C scopes/pointer widths/stride forms, and B6528 index/result/y widths and comparisons. These families are exhausted prior work; any repeated diagnostic controls here are labeled as such.

Prior search context: T-082 established stack-aware import/search and the distinction between weighted scores and words. T-088 ran 45-minute searches with 16 workers shared across 14 representatives, continuation probability 0.8 and heavier temp/type/declaration/layout mutation weights. The current round uses upstream default mutation weights with six workers per function and --stack-diffs. All searches and generated outputs live under /tmp/kig-t114, outside git.

## Per-function results, exact differences, and consolidated history

### func_8002F6F4

**MATCHED: 2→0 words, 516 B; integrated and draft deleted.**

New hypothesis and result: The declaration order suggests that key occupies the otherwise-unused sp+64 home while step occupies sp+74. Swap the two declarations simultaneously, preserving every intervening declaration. The measured step home becomes sp+64, with every other emitted instruction unchanged. This differs from the prior 90 single-declaration moves, which shift intervening homes. All 45 declaration-pair swaps were measured. Only key/step reaches zero. Live-scalar record and array diagnostics retain at least two words. No statement, type, ABI, or event layout changed.

Exact incoming differences (function-relative offsets; target → draft):

| Offset | Target | Draft |
|---|---|---|
| 0x68 | `lw          $s4, 0x64($sp)` | `lw          $s4, 0x74($sp)` |
| 0x160 | `sw          $s4, 0x64($sp)` | `sw          $s4, 0x74($sp)` |

Measurement rows: 195; valid nonempty compiles: 194; compile errors: 1. Detailed labels/results are in measurements.json.

Prior report history:

#### tools/scratch/nonmatching/T-027/REPORT.md

| `func_8002F6F4` | UNCHANGED | T-024: 30 differing words; 516/516 bytes |

#### tools/scratch/nonmatching/T-045/REPORT.md

| `func_8002F6F4` | T-024 | UNCHANGED | screened existing draft; no retained rewrite |

#### tools/scratch/nonmatching/T-052/REPORT.md

| `func_8002F6F4` | UNCHANGED | 516 → 516 (516) | Complement bit clear, word repeat id and event declaration order all reproduce the same 30-word mismatch. |

#### tools/scratch/nonmatching/T-085/REPORT.md

| func_8002F6F4 | IMPROVED 30→18 | 516/516 B. Reused TU player queue declaration, removed conflicting byte-pointer extern and tuned multiline layout. Stack slots, bank/voice registers and repeat-event setup remain. |

#### tools/scratch/nonmatching/T-088/REPORT.md

- C4E38: argument widths; unused locals of different widths; explicit selector locals of different widths, assigned at several points and used in the switch, range check and inner comparison. No improvement. For full-TU probes only, reconciled the scratch return declaration of func_8002F6F4 with the TU's existing s32 declaration; no production declaration edits.
- B695C: removing frame/bank temporaries into direct expressions, narrowing/widening offset, changing pointer types, declaration order, narrower scope, declaration initializers, equivalent multiply/shift/address forms and statement line placement. No accepted improvement. The generated body already has the target's local spill slots; frame size and argument-home offsets remain different. A bank-mask diagnostic with stronger input assumptions was not retained.
- AA98: scaled/narrowed widths, shift forms, call parameter/return types and source line joins. No improvement and no solution to transfer to AAEC. Prototype changes were diagnostic only.
- BF720/BF914: return versus assignment/break/goto cases, default placement, local widths, reusing the input and returning through a pointer. Best remains two words.
- F45C: all five-local declaration orders; none improves the retained 11 words.
- B6528: index/result-pointer/y types and equivalent positive comparisons. No improvement.

#### tools/scratch/nonmatching/T-089/REPORT.md

| func_8002F6F4 | 18 → 2 | IMPROVED | Reorder local declarations and snapshot the chain key after accumulating delay. Only the load/store offsets for the spilled step differ (sp+0x74 versus target sp+0x64). |

#### tools/scratch/nonmatching/T-092/REPORT.md

| func_8002F6F4 | 2 → 2 | 24 | UNCHANGED | Step spill still differs by 0x10; declaration relocation probes did not solve it. Updated queue view only to follow E4A0's reconciled global declaration. |

#### tools/scratch/nonmatching/T-096/REPORT.md

| func_8002F6F4 | UNCHANGED, 2, 516 B | +68 lw s4 and +160 sw s4: target step slot sp+64 versus draft sp+74. Tested callee non-prototypes, event union alignment/size, timing aggregate layouts and step widths/initialization. Valid aligned unions retain two; timing structs reach the target step slot but disturb repeat/time slots (best seven differences). Initializing step changes 71 words. |

#### tools/scratch/nonmatching/T-097/REPORT.md

| func_8002F6F4 | All single declaration moves (90 orders), step widths, event arrays, aggregate timing values, and event-field reuse diagnostics | UNCHANGED, 2→2 | +68/+160 still load/store step at sp+74 rather than sp+64. Array reversal retains two; other aggregate/lifetime forms disturb additional slots or code. No initialization of the existing uninitialized step path was retained. |


### func_801BF720

**UNCHANGED: 2 words, 104 B.**

New hypothesis and result: Explicitly normalize the switch selector with unsigned subtraction by 1/26/27/32/44/65, adjust every case label modulo u32, and separately destructively update the selector after the alphabet guard. Also check pair/triple/offset line grouping, mixed boundaries and alternate return expression forms. None improves two words. The permuter’s score-60 candidate is 108 B / three words and is rejected.

Exact incoming differences (function-relative offsets; target → draft):

| Offset | Target | Draft |
|---|---|---|
| 0x1c | `addiu       $v1, $zero, 0x20` | `addiu       $v0, $zero, 0x20` |
| 0x64 | `move        $v0, $v1` | `nop` |

Measurement rows: 173; valid nonempty compiles: 173; compile errors: 0. Detailed labels/results are in measurements.json.

Prior report history:

#### tools/scratch/nonmatching/T-023/REPORT.md

| `func_801BF720` | 104 | DRAFT | C switch emits a new jump table; assembly-owned rodata blocks retention. |

- `func_801BFB10`: refresh/rebuild high-score tables after loading persistent data; it calls two storage routines and `func_801BEFFC`.
- `func_801BFC08`: advance high-score page/scroll position; the page index is `D_802D37D0`, the scroll position is `D_802D37F8`.
- `func_801BFC8C`: previous high-score page, wrapping from zero to thirteen, then resets scroll to 160.
- `func_801C0784`: draw the high-score page with scroll clamping; clears `D_801CD454`. Its first argument is a display-list cursor despite the currently matching integer signature.
- `func_801BF720`/`func_801BF914`: packed-name glyph encode/decode. The switch tables remain assembly-owned.
- `D_80127D80`: eight-byte table descriptors (entry pointer, u8 count, u8 ordering flag, two padding bytes); entries appear to be eight bytes (u32 packed name, u16 score, two padding bytes). Draft signedness still needs verification.
- `func_801BEA74` and `func_801BED0C` encode/decode a 64-bit mixed-radix score-placement value, using radices 11 and 6.
- `func_801BE540` has an incompatible declaration outside this range: the matched downstream wrapper declares integer text/x arguments and 32-bit colors, while its body indicates a text pointer, float x, and byte colors. This needs coordinated type cleanup rather than editing another worker's function.

#### tools/scratch/nonmatching/T-039/REPORT.md

Skipped for assembly-owned jump tables/rodata: func_801ADCFC, func_801CBCCC, func_801BF720, and func_801BF914. No data ownership changes attempted.

| func_801BF720 | T-023 | UNCHANGED | 2 relocation-masked differing words in original screen. Skipped: rodata ownership. |

#### tools/scratch/nonmatching/T-043/REPORT.md

| func_801BF720 | ovl_7DF8_12C70.c | 104 | Still asm; C draft differs at +0x1C and +0x64 |

#### tools/scratch/nonmatching/T-047/REPORT.md

| func_801BF720 | T-023 | UNCHANGED | 2 words, 104/104 bytes. Retried input/result/return signedness and widths, return conversion/masking, and conditional returns. Original default still uses v1 followed by a return-delay-slot move. Existing TU rodata ownership retained. |

#### tools/scratch/nonmatching/T-056/REPORT.md

| func_801BF720 | 12C70 | UNCHANGED (2) | About 60 more variants: return/local/param types (6×6×5), param reuse, default-assign, loop/do-while forms, case 26. Every variant either constant-folds the default ' ' into `li v0`, or adds a join branch. |

#### tools/scratch/nonmatching/T-061/REPORT.md

| func_801BF720 | UNCHANGED (2) | 104→104 / 104 | Enum input/result and union result storage do not recover the default result in v1 followed by the return move. Existing TU rodata ownership is sufficient. |

#### tools/scratch/nonmatching/T-066/REPORT.md

| func_801BF720 | UNCHANGED (2) | 104 / 104 | Unsigned full-word input comparisons and ordinary word result; no entry narrowing. Tested addressable result arrays/records, bitfield signedness, K&R and aggregate scalar forms. Default still folds into v0 instead of v1 followed by a return move. |

#### tools/scratch/nonmatching/T-071/REPORT.md

| func_801BF720 | UNCHANGED 2→2 | 104 | Default result remains v0 rather than v1 plus the return move (+0x1C/+0x64). |

#### tools/scratch/nonmatching/T-082/REPORT.md

| func_801BF720 | 60 | UNCHANGED | 2→2 | No retained improvement; default return register remains. |

#### tools/scratch/nonmatching/T-088/REPORT.md

| func_801BF720 | 60 | UNCHANGED | 2→2 | Pointer/block candidate did not solve default-result register. Existing signed/unsigned prototype conflict also prevents direct full-TU insertion unchanged. |

#### tools/scratch/nonmatching/T-096/REPORT.md

| func_801BF720 | UNCHANGED, 2, 104 B | +1C target loads space (32) into v1; draft uses v0. +64 target moves v1 to v0 in the return delay slot; draft has nop. Tested TU order/context, result and return widths, shared-label return, case assignments with break, and explicit default case. None improves the two words. No callee/global ABI to alter in this leaf. |

#### tools/scratch/nonmatching/T-097/REPORT.md

| func_801BF720 | Switch assignments/break, return assignment, volatile-result diagnostic, compact layout | UNCHANGED, 2→2 | +1C default space still uses v0 rather than v1; +64 return delay slot still nop rather than move. |


### func_801BF914

**UNCHANGED: 2 words, 116 B.**

New hypothesis and result: Same explicit selector-normalization family, including destructive selector update and braced cases, after the alphabet guard. Full-TU prototype reconciliation is required: the temporary later func_801BF914(s32) declaration becomes u32 to agree with the draft. Initial unreconciled probes are errors; corrected baseline is two words / 116 B. New selector and return-form probes do not improve it.

Exact incoming differences (function-relative offsets; target → draft):

| Offset | Target | Draft |
|---|---|---|
| 0x68 | `addiu       $v1, $zero, 0x1B` | `addiu       $v0, $zero, 0x1B` |
| 0x70 | `move        $v0, $v1` | `nop` |

Measurement rows: 197; valid nonempty compiles: 146; compile errors: 51. Detailed labels/results are in measurements.json.

Prior report history:

#### tools/scratch/nonmatching/T-023/REPORT.md

| `func_801BF914` | 116 | DRAFT | C switch emits a new jump table; default-result register also differs. |

- `func_801BFB10`: refresh/rebuild high-score tables after loading persistent data; it calls two storage routines and `func_801BEFFC`.
- `func_801BFC08`: advance high-score page/scroll position; the page index is `D_802D37D0`, the scroll position is `D_802D37F8`.
- `func_801BFC8C`: previous high-score page, wrapping from zero to thirteen, then resets scroll to 160.
- `func_801C0784`: draw the high-score page with scroll clamping; clears `D_801CD454`. Its first argument is a display-list cursor despite the currently matching integer signature.
- `func_801BF720`/`func_801BF914`: packed-name glyph encode/decode. The switch tables remain assembly-owned.
- `D_80127D80`: eight-byte table descriptors (entry pointer, u8 count, u8 ordering flag, two padding bytes); entries appear to be eight bytes (u32 packed name, u16 score, two padding bytes). Draft signedness still needs verification.
- `func_801BEA74` and `func_801BED0C` encode/decode a 64-bit mixed-radix score-placement value, using radices 11 and 6.
- `func_801BE540` has an incompatible declaration outside this range: the matched downstream wrapper declares integer text/x arguments and 32-bit colors, while its body indicates a text pointer, float x, and byte colors. This needs coordinated type cleanup rather than editing another worker's function.

#### tools/scratch/nonmatching/T-039/REPORT.md

Skipped for assembly-owned jump tables/rodata: func_801ADCFC, func_801CBCCC, func_801BF720, and func_801BF914. No data ownership changes attempted.

| func_801BF914 | T-023 | UNCHANGED | 2 relocation-masked differing words in original screen. Skipped: rodata ownership. |

#### tools/scratch/nonmatching/T-043/REPORT.md

| func_801BF914 | ovl_7DF8_12C70.c | 116 | Still asm; C draft differs at +0x68 and +0x70 |

#### tools/scratch/nonmatching/T-047/REPORT.md

| func_801BF914 | T-023 | UNCHANGED | 2 words, 116/116 bytes. Same type/return-form retries; original default-result register and return move remain. Existing TU rodata ownership retained. |

#### tools/scratch/nonmatching/T-056/REPORT.md

| func_801BF914 | 12C70 | UNCHANGED (2) | Same family of variants; the target's `li v1,27; move v0,v1` default is not reproduced. |

#### tools/scratch/nonmatching/T-061/REPORT.md

| func_801BF914 | UNCHANGED (2) | 116→116 / 116 | Same type/storage experiments; default-result register and return delay slot remain. |

#### tools/scratch/nonmatching/T-066/REPORT.md

| func_801BF914 | UNCHANGED (2) | 116 / 116 | Same input/result audit and result-storage experiments. Default still uses v0 rather than target v1 and return move. |

#### tools/scratch/nonmatching/T-071/REPORT.md

| func_801BF914 | UNCHANGED 2→2 | 116 | Default-result register and return delay slot remain (+0x68/+0x70). |

#### tools/scratch/nonmatching/T-082/REPORT.md

| func_801BF914 | 105 | UNCHANGED | 2→2 | No improvement; default register/return delay slot remains. |

#### tools/scratch/nonmatching/T-088/REPORT.md

| func_801BF914 | 105 | UNCHANGED | 2→2 | Default register/return delay slot remains. |

#### tools/scratch/nonmatching/T-096/REPORT.md

| func_801BF914 | UNCHANGED, 2, 116 B | +68 default 27 goes into v1 versus v0; +70 return move versus nop. Same context, width and switch/return experiments as BF720; unchanged. Narrow return types introduce additional sign/zero extension. |

#### tools/scratch/nonmatching/T-097/REPORT.md

| func_801BF914 | Same return-lifetime/layout probes | UNCHANGED, 2→2 | +68 default 27 still uses v0 rather than v1; +70 return move missing. |


### func_801C4E38

**UNCHANGED: 2 words, 556 B.**

New hypothesis and result: Test mixed partial line groups and additional deterministic mixed boundaries in the reconciled complete TU. There are no scalar local declarations to pair-swap in this body; random-layout controls and the permutation search leave the switch spill at sp+18. Existing selector-local/type/addressability experiments are prior work, not new proposals.

Exact incoming differences (function-relative offsets; target → draft):

| Offset | Target | Draft |
|---|---|---|
| 0x88 | `sw          $v0, 0x1C($sp)` | `sw          $v0, 0x18($sp)` |
| 0xb8 | `lw          $v0, 0x1C($sp)` | `lw          $v0, 0x18($sp)` |

Measurement rows: 143; valid nonempty compiles: 143; compile errors: 0. Detailed labels/results are in measurements.json.

Prior report history:

#### tools/scratch/nonmatching/T-021/REPORT.md

| `func_801C4E38` | 556 | DRAFT | Compile blocked by unresolved types/prototypes: extern s32 func_801C4C64(); |

#### tools/scratch/nonmatching/T-039/REPORT.md

| func_801C4E38 | T-021 | UNCHANGED | Standalone compile failed. |

#### tools/scratch/nonmatching/T-056/REPORT.md

| func_801C4E38 | 190B0 | IMPROVED (didn't compile → 2) | Rewritten from raw m2c with typed tables and function pointers, and a 2-argument func_801C4C64 call. Remaining: arg0 spills at sp+0x18 vs 0x1C. Pad locals grow the frame. |

#### tools/scratch/nonmatching/T-060/REPORT.md

| func_801C4E38 | UNCHANGED (2) | 556 / 556 | Tried parameter widths, K&R definition, mode caches, query/callback return and parameter declarations. Still spills/reloads v0 at sp+0x18 instead of sp+0x1C. No padding or register bindings retained. |

#### tools/scratch/nonmatching/T-062/REPORT.md

| func_801C4E38 | UNCHANGED (2) | 556 / 556 | Tested meaningful mode/player/table/callback locals, scalar and aggregate local forms, 8/16/32/64-bit switch expressions, callee/callback return declarations and argument widths. Still spills/reloads v0 at sp+0x18 instead of target sp+0x1C. No artificial padding retained. |

#### tools/scratch/nonmatching/T-066/REPORT.md

| func_801C4E38 | UNCHANGED (2) | 556 / 556 | Entry lbu establishes two u8 parameters; no a2/a3 wide pair. Checked matched callees and dispatcher declarations; tested K&R arguments, SDK/callee return declarations and scalar aggregate locals. Still saves/reloads the switch value at sp+0x18 instead of sp+0x1C. SDK osViBlack actually takes s32; correcting that prototype alone does not change the score. |

#### tools/scratch/nonmatching/T-071/REPORT.md

| func_801C4E38 | UNCHANGED 2→2 | 556 | Switch-value spill/reload remains sp+0x18 rather than sp+0x1C (+0x88/+0xB8). |

#### tools/scratch/nonmatching/T-082/REPORT.md

| func_801C4E38 | 28 | UNCHANGED | 2→2 | No improvement; switch spill/reload slot remains. |

#### tools/scratch/nonmatching/T-088/REPORT.md

| func_801C4E38 | 28 | UNCHANGED | 2→2 | Switch value spill remains at sp+0x18 versus target sp+0x1C. |

#### tools/scratch/nonmatching/T-090/REPORT.md

| 0x80293830–0x8029484C | 115 ending-text strings, each padded to four bytes | Original data pointer lists beginning at D_80291920; selector tables D_80291B74 and D_80291BA0 are loaded by func_801C4E38 |

Prerequisites baserom.us.z64, ROMs, .venv and tools/ext are symlinks to the
user-authorized main checkout. No ROM was copied or committed. T-088's
func_801C4E38, func_801C5064 and func_801C6A80 bodies remain unchanged.

#### tools/scratch/nonmatching/T-096/REPORT.md

| func_801C4E38 | UNCHANGED, 2, 556 B | +88 sw v0 and +B8 lw v0 use target sp+1C versus draft sp+18. Pointer table/output declarations reconciled; tested unprototyped callees, explicit selector widths, unused third parameters, table extents and surrounding function context. No valid improvement. |

#### tools/scratch/nonmatching/T-097/REPORT.md

| func_801C4E38 | Selector locals with several widths and assignment points before/after calls | UNCHANGED, 2→2 | +88/+B8 selector spill remains sp+18 rather than sp+1C. |


### func_801CC908

**UNCHANGED: 2 words, 424 B.**

New hypothesis and result: Test pairs of real live scalar variables in records in both member orders, and declaration-pair transpositions without deleting the other homes. These retain original behavior and introduce no padding objects. The target 0x30 frame and all existing +24/+28/+2C slots are not simultaneously recovered. Prior single-element storage and dead-home cleanup are controls, not new hypotheses.

Exact incoming differences (function-relative offsets; target → draft):

| Offset | Target | Draft |
|---|---|---|
| 0xc | `addiu       $sp, $sp, -0x30` | `addiu       $sp, $sp, -0x40` |
| 0x19c | `addiu       $sp, $sp, 0x30` | `addiu       $sp, $sp, 0x40` |

Measurement rows: 194; valid nonempty compiles: 194; compile errors: 0. Detailed labels/results are in measurements.json.

Prior report history:

#### tools/scratch/nonmatching/T-021/REPORT.md

| `func_801CC908` | 424 | DRAFT | Compile blocked by unresolved types/prototypes: s32 func_801CC350(s32 *, s32); |

#### tools/scratch/nonmatching/T-039/REPORT.md

| func_801CC908 | T-021 | UNCHANGED | 15 relocation-masked differing words in original screen. |

#### tools/scratch/nonmatching/T-044/REPORT.md

| func_801CC908 | T-021 | IMPROVED 13 words | Was 15; declare D_802927A4 as a pointer table and index it, replacing byte-load-to-pointer conversion. Tried callee return widths and removing dead stores. 424/424 bytes. |

#### tools/scratch/nonmatching/T-087/REPORT.md

| func_801CC908 | UNCHANGED 13 | 424 / 424 | Original draft did not compile against the current TU. Reconciled audio/global declarations and allocation-wrapper ABI; full-TU score reproduces the prior 13. Handle/return spills and scheduling remain. Corrected draft retained in place. |

#### tools/scratch/nonmatching/T-092/REPORT.md

| func_801CC908 | 13 → 4 | 26 | IMPROVED | Local allocation/status result and spill declaration order; removed XOR-zero and multiply-zero expressions. |

#### tools/scratch/nonmatching/T-094/REPORT.md

| func_801CC908 | 4 → 2 | 10 | IMPROVED | Reorder local declarations to fix the status spill slot. Cleaner hand candidate ties the cleaned weighted winner. |

#### tools/scratch/nonmatching/T-099/REPORT.md

| func_801CC908 | 2 / 424 | +0C/+19C frame allocation/free: draft 0x40, target 0x30. Actual mask/status/handle spill offsets agree. |

| func_801CC908 | 2 → 2 | UNCHANGED | Declaration orders, dead home-local cleanup, explicit records/arrays, status widths and compatible callee declarations do not recover the smaller frame. Spill slots already agree; no padding or ABI workaround retained. |

#### tools/scratch/nonmatching/T-104/REPORT.md

| func_801CC908 | 2 / 424 | UNCHANGED | Only +0C/+19C frame allocation/free: 0x40 instead of 0x30. Mask/status/handle spills already agree. Removing duplicate status/dead home locals and permuting the three live locals obtains frame 0x30 but moves the mask spill to +20 instead of +24. Cached handle/status pointers, scopes, unsigned mask, single-element handle array and file-index record do not solve both requirements together. No padding local retained. |

#### tools/scratch/nonmatching/T-109/REPORT.md

| func_801CC908 | Remove the dead mask home, permute the five remaining declarations, consolidate status aliases, and test meaningful handle/mask records. | UNCHANGED, 2; 424 B | Only allocation/free at +0C/+19C remain 0x40 instead of 0x30. Smaller frames disturb the otherwise-correct mask/handle/status slots. No padding local retained. |


### func_801B6528

**UNCHANGED: 3 words, 596 B.**

New hypothesis and result: Check declaration-pair transpositions and mixed partial statement grouping while preserving every display-list command. Pair-record storage and scalar array controls do not improve the three register operands. Reload remains a0 instead of a2. The raw score-155 candidate has seven words / 596 B and is rejected.

Exact incoming differences (function-relative offsets; target → draft):

| Offset | Target | Draft |
|---|---|---|
| 0x178 | `lw          $a2, 0x24($sp)` | `lw          $a0, 0x24($sp)` |
| 0x1a0 | `lw          $t3, 0xC($a2)` | `lw          $t3, 0xC($a0)` |
| 0x1e8 | `lw          $t0, 0xC($a2)` | `lw          $t0, 0xC($a0)` |

Measurement rows: 148; valid nonempty compiles: 147; compile errors: 1. Detailed labels/results are in measurements.json.

Prior report history:

#### tools/scratch/nonmatching/T-029/REPORT.md

| `func_801B6528` | DRAFT | Same 596-byte body; three operands use a0 instead of a2 after guTranslate. |

#### tools/scratch/nonmatching/T-039/REPORT.md

| func_801B6528 | T-029 | UNCHANGED | Standalone compile failed. Further iterations did not match. |

#### tools/scratch/nonmatching/T-056/REPORT.md

| func_801B6528 | 5ED0 | UNCHANGED (3) | Reloads arg1 into a2 vs a0 after guTranslate. Tried a typed param; a separate index local made it worse (77). |

#### tools/scratch/nonmatching/T-060/REPORT.md

| func_801B6528 | UNCHANGED (3) | 596 / 596 | Tried typed card pointer, explicit card cursor, index widths, local order, K&R parameters and postincrement commands. Reloaded card pointer still uses a2 instead of target a0. |

#### tools/scratch/nonmatching/T-062/REPORT.md

| func_801B6528 | UNCHANGED (3) | 596 / 596 | Tested declaration permutations, typed card/matrix parameters, unused fourth-parameter types and omission, local/field/return widths, branch-scoped index locals, guTranslate declarations, cursor updates and address locals. Reload of the card pointer still uses a0 rather than target a2, with two dependent loads differing. |

#### tools/scratch/nonmatching/T-066/REPORT.md

| func_801B6528 | UNCHANGED (3) | 596 / 596 | Card index is lw at +0xC; displacement is lh; selector tables are lbu. guTranslate has the normal pointer/f32/f32/f32 ABI, with floats passed in a1/a2/a3. Tested integer/pointer address types, const card views, matrix pointer types, texture record shapes, fourth-parameter widths, K&R and non-prototype forms. Card reload remains a0 instead of a2, plus its two dependent field loads. Narrow index diagnostics were discarded. |

#### tools/scratch/nonmatching/T-071/REPORT.md

| func_801B6528 | UNCHANGED 3→3 | 596 | Card pointer reload still uses a0 rather than a2, plus its dependent loads (+0x178/+0x1A0/+0x1E8). |

#### tools/scratch/nonmatching/T-082/REPORT.md

| func_801B6528 | 95 | UNCHANGED | 3→3 | Lower weighted score has more differing words; retained 3-word draft. |

#### tools/scratch/nonmatching/T-088/REPORT.md

| func_801B6528 | 95 | UNCHANGED | 3→3 | Raw best has 7 differing words; retained incoming draft. |

#### tools/scratch/nonmatching/T-096/REPORT.md

| func_801B6528 | UNCHANGED, 3, 596 B | +178 target reloads card into a2 from sp+24; draft uses a0. +1A0/+1E8 dependent index loads consequently use a2 versus a0. Tested TU context, symbol extents, and explicitly moving the post-guTranslate card view into arg2, arg3 or a fresh typed local. No improvement; command bytes already match. |

#### tools/scratch/nonmatching/T-097/REPORT.md

| func_801B6528 | Reuse arg2/arg3 for the post-guTranslate card view; compact layout | UNCHANGED, 3→3 | +178 reload remains a0 rather than a2; +1A0/+1E8 index-load bases follow it. |


### func_801B695C

**UNCHANGED: 4 words, 268 B.**

New hypothesis and result: Check simultaneous declaration transpositions and snapshot the source-frame pointer inside the second operand of the existing short-circuit null guard, preserving safety of the first guard. Explicit u8*/void*/integer snapshots are diagnostics; none improves the four frame/home differences. Pair-record live storage and mixed grouping also do not improve it.

Exact incoming differences (function-relative offsets; target → draft):

| Offset | Target | Draft |
|---|---|---|
| 0x0 | `addiu       $sp, $sp, -0x28` | `addiu       $sp, $sp, -0x30` |
| 0x8 | `sw          $a0, 0x28($sp)` | `sw          $a0, 0x30($sp)` |
| 0x5c | `lw          $t7, 0x28($sp)` | `lw          $t7, 0x30($sp)` |
| 0x100 | `addiu       $sp, $sp, 0x28` | `addiu       $sp, $sp, 0x30` |

Measurement rows: 153; valid nonempty compiles: 153; compile errors: 0. Detailed labels/results are in measurements.json.

Prior report history:

#### tools/scratch/nonmatching/T-029/REPORT.md

| `func_801B695C` | DRAFT | Frame is 0x30 instead of 0x28; bank/frame-pointer temporaries and scheduling differ. |

- `func_801B4300`: reset lineup position and shuffle lineup; `D_8012834B` is the reset position byte.
- `func_801B4324`: getSelectionUnlockTier; returns 0/1/2/3 at byte-statistic thresholds 5/55/120 and suppresses the statistic for the player flag.
- `T029Portrait` in the large drafts is a partial 0x8C-byte portrait/character asset record: pixels at +4, palette at +8, signed halfwords at +0x7E/+0x80/+0x82/+0x84, callback at +0x88. Field names remain provisional.
- `func_801B695C` copies 0x60-byte palette banks; `func_801B6A68` emits palette-loading display-list commands.

#### tools/scratch/nonmatching/T-039/REPORT.md

| func_801B695C | T-029 | IMPROVED | 39 differing words; 268/268 bytes, frame 0x30 versus 0x28 (was 45). |

| func_801B695C | T-029 | IMPROVED | 39 differing words; 268/268 bytes, frame 0x30 versus 0x28 (was 45). |

#### tools/scratch/nonmatching/T-044/REPORT.md

| func_801B695C | T-029 | IMPROVED 4 words | Was 39; reuse the loaded frame index as destination offset, inline the bank toggle and spell the frame stride as (offset * 3 << 5) + frames. All instructions/registers/spill slots now agree except the 0x30 frame versus 0x28 and its parameter reload offsets. Tested local permutations, types, expression order, aggregate layouts, variable reuse and callee return types. 268/268 bytes. |

#### tools/scratch/nonmatching/T-047/REPORT.md

| func_801B695C | T-029 | UNCHANGED | 4 words, 268/268 bytes. Retried parameter/offset widths, memcpy return type, shorter local scopes, stride expressions and separate destination index. Original frame is 0x28 versus C's 0x30; other instructions and spill locations already agree. |

#### tools/scratch/nonmatching/T-056/REPORT.md

| func_801B695C | 5ED0 | UNCHANGED (4) | Frame is 0x30 vs 0x28. Tried early return, block-scoped locals, param/offset/memcpy types (18 combos), u16[][256] destination, split offset variable. All were the same or worse. |

#### tools/scratch/nonmatching/T-061/REPORT.md

| func_801B695C | UNCHANGED (4) | 268→268 / 268 | Frame/index lifetime and record/array-of-96-byte-frame declarations tested, together with local widths and memcpy length type. Best remains four frame/argument-offset words: frame 0x30 versus target 0x28. Extra-argument diagnostic candidates were discarded. |

#### tools/scratch/nonmatching/T-066/REPORT.md

| func_801B695C | UNCHANGED (4) | 268 / 268 | Asset has pointer at +8; frame/bank selectors use lbu; memcpy has three word arguments (no wide pair). Tested source frame records, destination palette rows/elements, copy-context records, pointer-to-frame locals, index/local widths, parameter reuse, memcpy return/prototype forms and integer asset address. Same instructions otherwise, but frame remains 0x30 instead of 0x28, affecting entry/exit and argument-home offsets. |

#### tools/scratch/nonmatching/T-071/REPORT.md

| func_801B695C | UNCHANGED 4→4 | 268 | Frame remains 0x30 rather than 0x28; entry/exit and argument-home offsets differ. |

#### tools/scratch/nonmatching/T-082/REPORT.md

| func_801B695C | 26 | UNCHANGED | 4→4 | No improvement; 0x30 versus 0x28 frame remains. |

#### tools/scratch/nonmatching/T-088/REPORT.md

| func_801B695C | 26 | UNCHANGED | 4→4 | Frame remains 0x30 versus target 0x28. |

#### tools/scratch/nonmatching/T-096/REPORT.md

| func_801B695C | UNCHANGED, 4, 268 B | +00/+100 frame allocation/free is target 28 versus draft 30; +08/+5C arg0 home/store follows that frame, target sp+28 versus sp+30. All actual local spill slots already agree. Tested memcpy absent/non-prototype/typed declarations and void/int/pointer/u64 returns, size widths, unused third parameters, asset qualifiers, palette view reconciliation and TU context. Valid copy-prototype changes retain four differences; extra parameters worsen code. |

#### tools/scratch/nonmatching/T-097/REPORT.md

| func_801B695C | Inline frame/bank expressions; offset widths; reuse incoming index; narrow local scopes; declaration orders | UNCHANGED, 4→4 | Frame remains 0x30 versus 0x28; arg0 home follows it. Local spills already agree. Removing expressions or locals did not remove the excess eight bytes without other differences. |


### func_801C85C0

**UNCHANGED: 4 words, 168 B.**

New hypothesis and result: Exhaust all 24 permutations of the four zero stores with grouping into individual, pair-chained or fully chained assignments (72 probes). Keep every clear before the call and preserve every table/counter width. None improves four words. Mixed grouping and pair-record diagnostics likewise do not recover earlier argument add/mask scheduling. Lower weighted candidates are not independent improvements.

Exact incoming differences (function-relative offsets; target → draft):

| Offset | Target | Draft |
|---|---|---|
| 0x48 | `addiu       $a1, $s0, 0x2` | `sb          $zero, 0x0($s1)` |
| 0x4c | `andi        $t6, $a1, 0xFF` | `sw          $zero, 0x0($s3)` |
| 0x50 | `sb          $zero, 0x0($s1)` | `addiu       $a1, $s0, 0x2` |
| 0x58 | `sw          $zero, 0x0($s3)` | `andi        $t6, $a1, 0xFF` |

Measurement rows: 221; valid nonempty compiles: 221; compile errors: 0. Detailed labels/results are in measurements.json.

Prior report history:

#### tools/scratch/nonmatching/T-021/REPORT.md

| `func_801C85C0` | 168 | DRAFT | Saved pointer register assignment and loop scheduling differ. |

#### tools/scratch/nonmatching/T-039/REPORT.md

| func_801C85C0 | T-021 | UNCHANGED | 14 relocation-masked differing words in original screen. |

#### tools/scratch/nonmatching/T-044/REPORT.md

| func_801C85C0 | T-021 | IMPROVED 9 words | Was 14; reorder cursor initialization. Tested all 24 initialization permutations and indexed writes. 168/168 bytes. |

#### tools/scratch/nonmatching/T-092/REPORT.md

| func_801C85C0 | 9 → 5 | 120 | IMPROVED | Reorder initial pointer assignments on one line; remove do-once wrapper and simplify subtraction of negative two. |

#### tools/scratch/nonmatching/T-094/REPORT.md

| func_801C85C0 | 5 → 5 | 120 | UNCHANGED | No retained improvement; raw candidate changes an external declaration to volatile int and is rejected. |

#### tools/scratch/nonmatching/T-099/REPORT.md

| func_801C85C0 | 5 / 168 | +48..+58 call's index addition/mask must precede the first three clears. Registers, widths and remaining loop already agree. |

| func_801C85C0 | 5 → 4 | IMPROVED | Reorder independent zero stores (first byte, word, second byte, final byte). Still declaration-fallback only; remaining argument/mask scheduling is not an integration claim. |

#### tools/scratch/nonmatching/T-104/REPORT.md

| func_801C85C0 | 4 / 168 | UNCHANGED | +48/+4C index add/mask should precede byte/word clears at +50/+58. Tested explicit next-index local, counter starting at two, widths and layouts. Existing earlier callee definition takes two u8 arguments. Reconciled full TU is 24 words; byte/halfword counters reach 11, still worse than the fallback. No callee change retained. |

#### tools/scratch/nonmatching/T-109/REPORT.md

| func_801C85C0 | Precompute the next-index argument before clears, vary index widths, and reconcile the owning TU's actual arrays and callee prototype. | UNCHANGED, 4; 168 B in declaration fallback | Index add/mask at +48/+4C remain after the first clears. Compatible arrays plus an explicit u8 argument cast also reproduce 4 words / 168 B in the full TU. The four-word order miss persists. |


### func_801BD270

**UNCHANGED: 7 words, 396 B.**

New hypothesis and result: Split the 64-bit shift and axis addition into distinct assignments/compound assignments; combine each with direct/commuted button returns. Store the actual 64-bit accumulator in a one-element array, single-member record, or signed/unsigned union, with joined and ordinary layout. These are new accumulator-storage diagnostics beyond the prior axis-word probes; no improvement. Existing reassociation/signedness probes are historical controls.

Exact incoming differences (function-relative offsets; target → draft):

| Offset | Target | Draft |
|---|---|---|
| 0x154 | `addu        $t2, $t2, $t8` | `addu        $v1, $t3, $t0` |
| 0x158 | `addu        $v1, $t3, $t0` | `addu        $t2, $t2, $t8` |
| 0x15c | `sw          $t2, 0x18($sp)` | `sltu        $at, $v1, $t0` |
| 0x160 | `sltu        $at, $v1, $t0` | `addu        $t8, $at, $t2` |
| 0x164 | `addu        $t2, $at, $t2` | `sra         $t6, $t0, 31` |
| 0x168 | `sra         $t8, $t0, 31` | `sw          $t2, 0x18($sp)` |
| 0x170 | `addu        $v0, $t2, $t8` | `addu        $v0, $t8, $t6` |

Measurement rows: 202; valid nonempty compiles: 193; compile errors: 9. Detailed labels/results are in measurements.json.

Prior report history:

#### tools/scratch/nonmatching/T-023/REPORT.md

| `func_801BD270` | 396 | DRAFT | 64-bit return packing, stack temporaries and pad-field scheduling differ. |

#### tools/scratch/nonmatching/T-039/REPORT.md

| func_801BD270 | T-023 | UNCHANGED | 21 relocation-masked differing words in original screen. |

#### tools/scratch/nonmatching/T-047/REPORT.md

| func_801BD270 | T-023 | UNCHANGED | 21 words, 396/396 bytes. Tried signed axis widths and signed/unsigned 64-bit intermediate/cast forms; return packing and spill scheduling remain. |

#### tools/scratch/nonmatching/T-095/REPORT.md

| func_801BD270 | IMPROVED | 21 → 11 | 396 | Initialize the u64 result before shifting and combine the shifted axis with its first addition. Remaining: axis/button spill widths/slots and carry-chain register/scheduling differences. |

#### tools/scratch/nonmatching/T-099/REPORT.md

| func_801BD270 | 11 / 396 | +124/+138 buttons spill at sp+22 rather than +26; +12C/+130 axis byte store/reload rather than target halfword at +22. +154..+170 u64 carry-chain scheduling/register choices. |

| func_801BD270 | 11 → 7 | IMPROVED | Signed-halfword Y local and declaration order fix the axis/button spill widths and offsets. Remaining +154..+170 carry-chain register allocation/scheduling. Full-TU checked. |

#### tools/scratch/nonmatching/T-104/REPORT.md

| func_801BD270 | 7 / 396 | UNCHANGED | +154..+170 high-word addition, low-word carry and sign contribution order/registers differ. Incoming s16 Y and u16 buttons already recover the target halfword spill widths/slots. Explicit axis words of u32/s32/u64, commuted additions and layouts do not solve the carry chain. |

#### tools/scratch/nonmatching/T-109/REPORT.md

| func_801BD270 | Reassociate the 64-bit axis/button sum and test an explicitly unsigned low word and bitwise packing. | UNCHANGED, 7; 396 B | High-word addition, carry and sign contribution at +154..+170 remain. No signedness change is promoted. |


### func_80017378

**UNCHANGED: 8 words, 1752 B.**

New hypothesis and result: Hoist the actual symbolic rotation endpoint into a local before model initialization or before the preceding setup call, with byte/rotation/void pointer views; preserve the symbolic endpoint and iteration count. Mixed grouping and real-local records do not improve it. The raw score-185 candidate still has eight words / 1752 B. No loop bound or store semantics is changed.

Exact incoming differences (function-relative offsets; target → draft):

| Offset | Target | Draft |
|---|---|---|
| 0x590 | `addiu       $a0, $a0, -0x55EC` | `addiu       $v1, $v1, 0x0` |
| 0x598 | `addiu       $v1, $v1, -0x5668` | `addiu       $a0, $a0, 0x0` |
| 0x59c | `addiu       $v0, $v0, 0x14` | `sw          $t0, 0x0($v1)` |
| 0x5a0 | `addiu       $v1, $v1, 0x10` | `sw          $zero, 0x4($v1)` |
| 0x5a4 | `sw          $t0, -0x10($v1)` | `sw          $zero, 0x8($v1)` |
| 0x5a8 | `sw          $zero, -0xC($v1)` | `sw          $zero, 0xC($v1)` |
| 0x5ac | `sw          $zero, -0x8($v1)` | `addiu       $v0, $v0, 0x14` |
| 0x5b0 | `sw          $zero, -0x4($v1)` | `addiu       $v1, $v1, 0x10` |

Measurement rows: 151; valid nonempty compiles: 151; compile errors: 0. Detailed labels/results are in measurements.json.

Prior report history:

#### tools/scratch/nonmatching/T-033/REPORT.md

| `func_80017378` | 1752 | DRAFT | 463 positional differing words; 1904/1752 bytes |

#### tools/scratch/nonmatching/T-045/REPORT.md

| `func_80017378` | T-033 | UNCHANGED | screened existing draft; no retained rewrite; standalone requires shared TU declarations/types |

#### tools/scratch/nonmatching/T-046/REPORT.md

| func_80017378 | UNCHANGED | 458 (TU context) |

#### tools/scratch/nonmatching/T-055/REPORT.md

| func_80017378 | IMPROVED 463 → 41 | Exact up to 0x574 (natural order plus literals). The remaining words are all in the final 4-iteration A998/A9D8 loop: the original is a non-unrolled pointer loop that ends at the symbol D_8004AA14. It also needs D_8004A738 as u8; that change was **not** kept in src. Draft updated in place. |

#### tools/scratch/nonmatching/T-063/REPORT.md

Together these add 6,216 matching bytes. Applied the original T-055 patch with `git apply --3way`, then reconciled declarations against master. The unrelated `func_80017378` draft improvement was deliberately left unchanged.

#### tools/scratch/nonmatching/T-064/REPORT.md

One new match: **func_8001CBCC, 320 bytes**. func_80017378 improves to
**8 differing words / 1752 bytes**, remains GLOBAL_ASM. No commits.

| func_80017378 | IMPROVED, not matched: 8 relocation-masked words differ, 1752/1752 bytes |

An endless loop with an explicit endpoint break avoids IDO's unroll/remainder
transformation. Initializing model before rot fixes three setup differences.
The remaining differences are +0x590/+0x598 (base/endpoint setup order), and
+0x59C..+0x5B0 (two increments scheduled after the four model stores rather
than before them). The rest is exact under ELF relocation masks. See
func_80017378.diff.txt; reproduce with T-055/ctx.py and the retained T-033 draft
(reference main.bin goes in /tmp/t055ref as documented by that tool).

Deleted draft: tools/scratch/nonmatching/T-022/func_8001CBCC.c.
Retained improved draft: tools/scratch/nonmatching/T-033/func_80017378.c.

#### tools/scratch/nonmatching/T-067/REPORT.md

| func_80017378 | main_2FF0 | 8 / 1752 | 107 / 1748 |

| func_80017378 | UNCHANGED, 8 words | 1752/1752 B; endpoint/base setup and loop increment/store scheduling, as in T-064; cursor records and line variants do not improve it |

#### tools/scratch/nonmatching/T-072/REPORT.md

| func_80017378 | UNCHANGED 8→8 | 1752 / 1752 | Endpoint/base setup +0x590/+0x598 and loop pointer-increment/store schedule +0x59C..+0x5B0. |

#### tools/scratch/nonmatching/T-082/REPORT.md

| func_80017378 | 190 | UNCHANGED | 8→8 | No improvement; loop endpoint/increment scheduling remains. |

#### tools/scratch/nonmatching/T-088/REPORT.md

| func_80017378 | 190 | UNCHANGED | 8→8 | No retained candidate; loop scheduling remains. |

#### tools/scratch/nonmatching/T-093/REPORT.md

Skipped all explicitly reserved/huge functions, including func_80017378 and func_8001E0B4. No boot/overlay source, Makefile, status.csv, TRACKING or WORKLOG changes. No inline asm, #line, register bindings, compiler overrides or binary rewriting.

#### tools/scratch/nonmatching/T-096/REPORT.md

| func_80017378 | UNCHANGED, 8, 1752 B | +590/+598 endpoint/base addiu order differs. +59C..+5B0 target increments rotation/model pointers before four stores through negative offsets; draft stores first, then increments. Tested declared global array extents, grouped rotation clear, reversed model/rotation order, and explicit common increments before stores. No improvement. Earlier T-064 already tested ordinary pointer/for/goto forms. |

#### tools/scratch/nonmatching/T-097/REPORT.md

| func_80017378 | Move both pointer increments ahead of stores, reverse initialization order, joined loop/body layouts | UNCHANGED, 8→8 | +590/+598 base/endpoint setup and +59C..+5B0 increments/stores retain earlier scheduling diagnosis. |


## Integration and limits

F6F4’s delivered C keeps all incoming executable statements and shared audio types. Only the positions of ALKeyMap *key and s32 step are exchanged. The target loads the uninitialized step home before the first allocation and can consume it if allocation fails; that pre-existing target/draft path is preserved, not initialized or hidden. The resulting C measures zero at 516 B and the linked incremental build verifies all images and the ROM byte-identical.

The clean-build verification and completed bounded-search audit are recorded below.

## Clean verification (completed)

`make clean && make extract && make -j6 all && make progress` passed (exit 0).
All four byte-comparison checks pass:

- ROM: ba52e91b44450c548467044b26951353dc491e04
- main: 81736d32e8cda8f399b319a49250dff972b81af8
- ovl_7DF8: ea830aae50ff1422da60d4b7fdbfc29f03b1be39
- ovl_7E00: 2b01138a290212b9d886981e1196f7b6fb45ecdb

Matched bytes increase 70,628→71,144 (+516); T4 increases 314→315.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 71,144 (24.54%) | 71,144 (24.54%) | 0 | 194 | 0 | 315 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 31,720 (22.03%) | 31,720 (22.03%) | 0 | 89 | 0 | 148 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 30,956 (22.53%) | 30,956 (22.53%) | 0 | 105 | 0 | 146 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |

Historical wording is preserved above, including T-060’s reversed B6528 operand description. The current target assembly and instructions.json establish the direction unambiguously: target reloads a2, draft reloads a0. Generated functions.csv/progress.html were restored after recording the final table; status.csv remains untouched for the lead. `git diff --check` passes. No commits.

## Diagnostic generator corrections

BF914’s first selector-normalization generator parsed the colon character literal as a case-label separator; those 18 rows are syntax errors. The corrected literal-aware generator compiles all 18 variants, none better than two words. Some BD270 aggregate/array generators also rewrote identically named pad members; those rows are explicit errors. Six corrected two-field record variants compile, none better than seven words. Initial failed BF914 full-TU probes and the later valid reconciled baseline are distinguished in measurements.json. No failed probe supports a matching or negative-result claim.

The small generator scripts describe the staged experiment and use snapshot inputs under /tmp/kig-t114; sweep.py additionally expects the incoming drafts before F6F4 promotion. They are diagnostic records, not a self-contained test suite after promotion. measurements.json retains compact outcomes, instructions.json the exact baselines, and candidates.json the independent full-TU candidate checks. Raw logs, temporary objects and all permuter output directories stay outside git.

## Completed permuter searches

Nine unresolved functions each completed **1,800 seconds (30 minutes)** with **-j6 --stack-diffs --stop-on-zero --best-only --better-only**, using the shared decomp-permuter install. They ran concurrently on the shared 16-CPU machine; these are wall-clock budgets, not exclusive CPU allocations. All returned bounded interrupt status 137 and no search/probe processes remain. No zero-score permuter result appeared.

F6F4’s initial import failed before search because host preprocessing omitted SDK declarations guarded by _LANGUAGE_C. The temporary input was corrected with -D_LANGUAGE_C; the retry ran until the independent declaration-swap match was found, then was stopped early. Its log lifetime is approximately 423 seconds, 1,941 iterations. The early stop is intentional because its final linked C already matches. No import failure is counted as a completed search.

| Function | Seconds | Iterations / compile errors | Normalized base weighted score | Best weighted score (including base) | Best saved candidate words / B |
|---|---:|---:|---:|---:|---|
| func_80017378 | 1800.1 | 6118 / 269 | 190 | 185 | 8 / 1752 |
| func_801BD270 | 1800.1 | 11387 / 202 | 110 | 70 | 10 / 396 |
| func_801C85C0 | 1800.1 | 11525 / 145 | 385 | 120 | 4 / 168 |
| func_801B695C | 1800.1 | 11508 / 284 | 26 | 26 | none |
| func_801B6528 | 1800.1 | 10599 / 294 | 235 | 95 | 7 / 596 |
| func_801CC908 | 1800.1 | 10515 / 196 | 10 | 10 | none |
| func_801C4E38 | 1800.1 | 10885 / 290 | 28 | 28 | none |
| func_801BF914 | 1800.1 | 13354 / 691 | 105 | 105 | none |
| func_801BF720 | 1800.1 | 13143 / 473 | 105 | 60 | 3 / 108 |
| func_8002F6F4 | 423 (retry, approx.) | 1941 / 39 | 32 | 32 | none |

Weighted scores are not word counts, and normalization can worsen the incoming draft before randomization. Every saved candidate was recompiled as a body inside its original complete TU; no mutation of external globals/prototypes was accepted. None improves the retained instruction count. Tied eight-word 80017378 and four-word C85C0 candidates were not retained. BF720’s best saved body is 108 rather than 104 bytes; other lower weighted scores have more differing words. No permuter output directory or raw candidate was added to git.

Final checks: `git diff --check` passes. The clean build above remains the last production-code verification; subsequent work changed report/evidence files only. All edits are left uncommitted for lead review.
