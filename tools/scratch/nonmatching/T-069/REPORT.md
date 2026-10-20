# T-069 — sol-A24: large main drafts, structure first

**1 MATCHED (1,568 B), 8 IMPROVED drafts, 1 UNCHANGED.** All ten functions received focused attempts. No commits. Only `main_CA10.c` changes production C; improved drafts replace their existing files.

## Results

Counts are differing corresponding instruction words in the **current owning TU**, masking only actual ELF relocation fields and including length differences. They are diagnostic counts, not an edit distance or behavior certification. Baselines were remeasured rather than copied from old reports. Missing/conflicting declarations were reconciled in temporary TU copies for 31DD0, 15594, 1D7E4 and 14D5C. `probe.py` reproduces the retained draft measurements using T-055's compiler/comparison code.

| Function | Result | Final C / original bytes | Attempt and remaining issue |
|---|---|---:|---|
| func_800257FC | IMPROVED **343→337** | 1,232 / 1,372 | Word-aligned union for the copied eight-byte width table; recovered u16 health/u8 player and flash parameters, unsigned health reads, byte endpoints. Tried endpoint type combinations. Remaining clipping/loop register allocation and control-flow differences are substantial. |
| func_80031DD0 | UNCHANGED **355** | 1,020 / 1,420 | Recovered 28-byte sprite and four-byte bounds structures; attempted natural top-row/padding clears with u64 stores and typed bounds. Candidate grew to 1,264 B but still differed in 355 words; retained original draft. Original is explicitly marked handwritten, saves/restores gp, has nonstandard save ordering, duplicate even/odd pixel paths and internal entry labels. No register bindings or inline asm attempted. |
| func_80015594 | IMPROVED **358→339** | 1,464 / 1,488 | Rewrote the command builder around a single advancing two-word Gfx pointer and a natural ten-strip loop; replaced 360.0 external load with literal. Still differs in scheduling, clipped rectangle branches, loop strength reduction and command temporaries. Probe reconciles the earlier non-prototype declaration with its float parameters. |
| func_8001C5AC | **MATCHED**, 425→0 | 1,568 / 1,568 | Proper Gfx, 64-byte matrix union with s64 alignment, per-frame matrix arrays, float translation prototype/parameters and natural reverse display loop. Full ROM and image verification passed. |
| func_800238C4 | IMPROVED **392→384** | 1,600 / 1,580 | Retained the shared sprite layout; recovered full-width decoded dimensions and an advancing pixel-row index instead of repeated row multiplication. Remaining run decoding, unrolling and alpha/pixel address register differences. |
| func_80024CE0 | IMPROVED **407→400** | 1,600 / 1,652 | Sprite pointers selected through the assigned global slot; natural pointer loop over the dimensions/output-pointer tables. Corrected the original draft's `D_8004CED4[12*7]` store: asm writes the scalar pointer at D_8004CED4, not sprite 12's alpha field. Tried constant/global/assignment-index sprite selection and signed symbol-address size arithmetic. Still large scheduling/address-expression differences. |
| func_8001D7E4 | IMPROVED **435→427** | 1,724 / 1,656 | Recovered animation table as `[animation][player]` pairs of normal/fallback pointers. Removed redundant byte-argument copies and reconciled func_80024144's actual void(s32,s32) declaration. Dispatch and frame-offset parsing still differ. |
| func_80014D5C | IMPROVED **394→373** | 1,444 / 1,780 | Retained stage-part struct, replaced six owned float loads with their recovered literals, simplified advancing rotation access and shared the identical converted byte value across the three channel stores. Original repeats unsigned FP conversions; candidate shares them, so its shorter code is still far from matching. |
| func_800330B0 | IMPROVED **499→0, masked body only** | 1,900 / 1,900 | Identified SDK guLookAtHiliteF; natural vector math with LookAt/Light/Hilite layouts. Final FTOFRAC8 unsigned-short conversion resolves the last twelve integer-register differences. **Not promoted: constants remain asm-owned; see below.** |
| func_80025FC4 | IMPROVED **456→454** | 1,896 / 1,908 | Single Gfx cursor replaces the draft's artificial saved command-pointer aliases and explicit spill/reload copies. Restored shared multiplier use in the HUD geometry. Remaining coordinate-control-flow, live-range and register differences; only a small positional improvement. |

## Matched implementation: func_8001C5AC

The old draft advanced an s32 pointer by eight elements per command and used byte pointers for display-list arrays. The replacement uses `T069Gfx { u32 w0, w1; }` and increments once per command. `D_8004A998` is an array of four display-list pointers per group. Matrices are 64-byte unions with s64 alignment; each frame contains three banks of twenty matrices, giving the observed 0x500 bank stride and 0xF00 frame stride.

Using the real frame/matrix indexing, rather than spelling out byte-offset multiplications, reduced a 181-word same-size candidate to two words. Dividing the float scale by integer `4096` generates the original `div.s`; `4096.0f` is folded into reciprocal multiplication by IDO. The ordinary descending indexed loop is unrolled by IDO into the original remainder loop and four-way body.

Added local declarations/types in main_CA10 only: T069Gfx, T069Matrix, T069Frame; D_80044A24/D_8004A984/D_8004A980/D_8004AEB8/D_8004A998; prototypes for func_8001BB64, guTranslate, guRotateRPY, guScale and func_8001CD0C. Translation x/y/z are floats, as required by guTranslate. Existing D_8004AEB0 declaration is reused. Other production functions are unchanged.

Deleted draft: `tools/scratch/nonmatching/T-022/func_8001C5AC.c`.

## func_800330B0: exact body, ownership still blocked

Reference source: https://github.com/n64decomp/libreultra/blob/master/src/gu/lookathil.c (guLookAtHiliteF). The retained draft records this provenance. The original light records have a 16-byte stride, with direction bytes at +8/+9/+10. Hilite is four s32 coordinates. FTOFRAC8 clamps `(x * 128.0)` to 127.0, converts to s32 and then u16 before the byte store; this reproduces the original integer temporary allocation.

The original constants are at main-image offsets **0x396A0/0x396A8/0x396B0**, addresses D_80049000/D_80049008/D_80049010: doubles 0.1, 0.1, 127.0, followed by padding through 0x396C0. They belong to `main_remaining_0` assembly data. `main_23750` has no C rodata ownership. The zero-difference candidate emits its own literal pool; masking relocations does not prove those loads link to the original pool. Mutable and const extern variants were tried and emit 1,924 bytes with 163 words off. No production source or YAML was changed for this candidate. Lead follow-up: authorize/map the complete appropriate C rodata range, then verify literal ordering, duplicate thresholds and padding in a linked build.

## Hints, generated files and scope

None of these ten functions owns a `force_migration function_owner` reservation in the starting symbol file. No hint or symbol file was changed. Regenerated `linker_scripts/*.undefined_syms.txt` changes are retained if any; this conversion needs no new ownership hint. No Makefile, YAML, boot/overlay source, tracking/worklog or status.csv edits. No inline asm, register variables, padding arrays or compiler overrides.

Prerequisites were missing and are symlinks to `/home/rodri/Projects/killer-instinct-gold-n64` (baserom.us.z64, ROMs, .venv, tools/ext). No ROM was copied or added to git. Temporary objects/disassemblies/build logs stay under /tmp; only compact probe code and one rejected 31DD0 candidate are retained here.

## Final clean validation

`make clean && make extract && make -j8 all && make progress` passed. ROM SHA1 remains `ba52e91b44450c548467044b26951353dc491e04`; main is `81736d32e8cda8f399b319a49250dff972b81af8`, ovl_7DF8 is `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`, and ovl_7E00 is `2b01138a290212b9d886981e1196f7b6fb45ecdb`. All three images and the ROM are byte-identical. `git diff --check` passes. No undefined-symbol file has a net change after regeneration. Generated docs/functions.csv and docs/progress.html were restored after recording the table; lead-maintained status.csv was untouched.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 65,004 (20.37%) | 65,004 (20.37%) | 0 | 284 | 0 | 278 | 437 (138,092) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 173,204 | 39,832 (23.00%) | 39,832 (23.00%) | 0 | 135 | 0 | 155 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 16,704 (12.15%) | 16,704 (12.15%) | 0 | 149 | 0 | 102 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
