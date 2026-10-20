# T-056 — opus-5: ovl_7DF8 near-misses and never-compiled drafts

Uncommitted changes, left for the lead to vet. **8 functions MATCHED (1,076 B) and 7 drafts IMPROVED.** No rodata subsegments were added and kig.ovl_7DF8.us.yaml is unchanged. Two strings that had migrated into the asm files are now defined in C at their original slots in ovl_7DF8_200C0.c, which already owns that rodata (T-043 recipe step 4): D_80295618, D_80295628 and D_80295664.

## Final validation
`make clean && make extract && make all && make progress`: the ROM and all three images are byte-identical (ovl_7DF8 ea830aae…). Afterwards I restored the generated docs/functions.csv and docs/progress.html.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 53,172 (16.66%) | 53,172 (16.66%) | 0 | 304 | 0 | 258 | 437 (138,092) |
| boot | 8,468 | 8,108 (95.75%) | 8,108 (95.75%) | 0 | 1 | 0 | 20 | 99 (16,028) |
| main | 173,204 | 29,600 (17.09%) | 29,600 (17.09%) | 0 | 149 | 0 | 141 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 15,464 (11.25%) | 15,464 (11.25%) | 0 | 154 | 0 | 97 | 0 (0) |


## Tools
Everything is in `tools/scratch/nonmatching/T-056/`:
- `probe.py`: a copy of T-050's probe, writing to /tmp/t056-*.
- `tu.py`: compiles a draft *in its TU context*. It prepends the TU text that comes before the function's GLOBAL_ASM line, with the pragmas stripped.
- `sweep.py`: a `{{a||b}}` template sweeper that runs in TU context.
- `ad.py`: a difflib diff of target vs. compiled instructions.
- `run.sh`: a standalone runner.

Scores are relocation-masked differing words plus the instruction-count delta (T-050 metric).

## Per-function results
| Function | TU | Result | Notes |
|---|---|---|---|
| func_801BF720 | 12C70 | UNCHANGED (2) | About 60 more variants: return/local/param types (6×6×5), param reuse, default-assign, loop/do-while forms, case 26. Every variant either constant-folds the default ' ' into `li v0`, or adds a join branch. |
| func_801BF914 | 12C70 | UNCHANGED (2) | Same family of variants; the target's `li v1,27; move v0,v1` default is not reproduced. |
| func_801B695C | 5ED0 | UNCHANGED (4) | Frame is 0x30 vs 0x28. Tried early return, block-scoped locals, param/offset/memcpy types (18 combos), u16[][256] destination, split offset variable. All were the same or worse. |
| func_801C8A38 | 1BD90 | **MATCHED** | Uses the TU's `T021Six D_80127C68[]` (`D_80127C68[arg1].b[j]`), like sibling func_801C8868. |
| func_801C7E98 | 1BD90 | **MATCHED** | `D_80127C68[arg1].b[i] = D_80127C68[arg0].b[i]`. |
| func_801CC878 | 200C0 | **MATCHED** | Twin of func_801CC784 (`D_80127D58[i + 16]`); defines D_80295664 in C. |
| func_801CC668 | 200C0 | **MATCHED** | Inline `1 << arg0` (a mask local moves the spill slot). Defines D_80295618/D_80295628 in C. |
| func_801CD078 | 200C0 | **MATCHED** | A local OSPfsState-shaped struct; func_800361C0 behaves like osPfsDeleteFile. |
| func_801B4590 | 5ED0 | **MATCHED** | Declares `u8 D_802C8D0F` (s8 made IDO CSE the constant 1) and `u8 D_80127CE8[][11]`. |
| func_801C1704 | 13FF0 | **MATCHED** | 2D `[][11]` tables indexed by the u8 player, s32 loop counter. |
| func_801C4E38 | 190B0 | IMPROVED (didn't compile → 2) | Rewritten from raw m2c with typed tables and function pointers, and a 2-argument func_801C4C64 call. Remaining: arg0 spills at sp+0x18 vs 0x1C. Pad locals grow the frame. |
| func_801B446C | 5ED0 | IMPROVED 72→34 | Flags cached in a local, 2D tables. Remaining: the target keeps &D_802C8CE0 in a base register. |
| func_801BFB40 | 13FF0 | IMPROVED 47→12 | Field-wise pair copy. Remaining: temp register numbering. Permuting the statement order made it worse. |
| func_801C71FC | 190B0 | IMPROVED 39→38 | Pad-state struct. Remaining: arg spill placement. |
| func_801C80F0 | 1BD90 | IMPROVED (didn't compile → 284) | The `T034_D_80127D30` macro is replaced by the real `u8 D_80127D30[8]`. Compiles, still large. |
| func_801CAA00 | 1BD90 | IMPROVED (didn't compile → 972) | Same macro fix; func_801CA784 takes 1 argument (it is matched C in this TU). |
| func_801B6528 | 5ED0 | UNCHANGED (3) | Reloads arg1 into a2 vs a0 after guTranslate. Tried a typed param; a separate index local made it worse (77). |
| func_801B465C | 5ED0 | UNCHANGED (71) | Saved-register order and temporaries differ; inspected only. |
| func_801B1210, func_801C7998, func_801C35D8, func_801C0610, func_801BBB60, func_801C6D40, func_801C7CD0, func_801C49A8, func_801C3E40, func_801C5064, func_801C17D0 | various | UNCHANGED (baseline measured in TU context: 39/55/65/71/71/74/74/85/96/93/105) | Not reached in this round. |
| func_801B47A4, func_801B5650, func_801B5DCC, func_801B6E4C, func_801B9A04 | 5ED0 | UNCHANGED (compiles in TU: 862/425/387/1417/416) | They do compile in TU context. Their status is now known, but they are far from matching. |

## Deleted drafts
T-021/func_801C8A38.c, T-021/func_801C7E98.c, T-021/func_801CC878.c, T-021/func_801CC668.c, T-021/func_801CD078.c, T-029/func_801B4590.c, T-023/func_801C1704.c.

## Lessons
Most of the matches came from fixing declarations rather than tuning code: the right global types (u8 vs s8), the TU's existing structs, the real callee arity, and compiling in TU context. Drafts that "never compiled" were blocked only by standalone context or raw m2c syntax.
