# T-070 — sol-B23: ovl_7DF8 structure-first pass

All ten requested functions attempted. **0 MATCHED, 9 IMPROVED, 1 UNCHANGED.**
Changes are uncommitted. No drafts were deleted and no GLOBAL_ASM was replaced.
The improved drafts remain in their original task directories.

## Results

Scores use T-056's relocation-masked positional differing words plus the
instruction-count delta. These are candidate scores, not linked matching claims.
The requested old scores came from earlier screens; the baseline column below
records what actually compiled with this checkout's TU declarations before work.
All nine retained candidates also compile in their **complete production TU**
through asm-processor, not just the declaration prefix used for scoring.

| Function | Result (requested old → retained) | Initial TU probe | Retained bytes | Work and remaining blocker |
|---|---|---|---:|---|
| func_801B0668 | IMPROVED 231→159 | 231 | 984 | Recovered height/state transitions from asm, cached the state value, used unsigned tick conversion and real audio/render prototypes. Removed redundant explicit float saves. Same size as target; state/float register allocation, spills and scheduling differ. |
| func_801BD640 | IMPROVED 265→195 | 265 | 1068 | Typed glyph table and two-word Gfx commands, correct guScale/guTranslate float prototypes, typed matrix/glyph pointers, shared command temporary. A separate natural text-loop rewrite scored 232 and was discarded. Same size as target; saved-register/lifetime and command scheduling differences remain. |
| func_801B3DB0 | UNCHANGED (273 old screen; 277 in current TU) | 277 | 1344 | Read both initialization loops and their pointer termination conditions. Tried pointer induction, do/while forms, signed/unsigned mode locals, parameter widths and initial-value widths (72 combinations in the final sweep, plus earlier structural attempts). Pointer rewrite scored 305; no variant beat 277. Original draft retained verbatim. |
| func_801B132C | IMPROVED 296→240 | 296 | 1144 | Correct float x/z and byte color arguments to the text renderer; unsigned tick conversion; removed a carried m2c double temporary in favor of the referenced constant. Verified D_80292940 and D_80292950 are both 0.7. Selection-loop float lifetime and scheduling remain different. |
| func_801B0CDC | IMPROVED 301→209 | 301 | 1336 | Real 15-argument sprite-renderer prototype (two float stack arguments), unsigned tick conversion, render-state struct for +0x10, unsigned flag declaration and one Gfx temporary. Matrix/float spills and display-list scheduling remain different. Preserved the target's integer tick/40 division. |
| func_801BF190 | IMPROVED 310→303 | 310 | 1248 | Typed render-context global (+4 ticks, +0xF8 matrices), score/header structures and full rendering prototypes. Corrected the name formatting: byte 4 is a space after copying the name; byte 5 is also a space. Byte-wise copy avoids an unaligned u32 store in C. Tried struct/byte copies, count widths and buffer layouts. Nested table traversal, copy lowering and stack/register allocation remain different. |
| func_801C1C34 | IMPROVED 310→262 | did not compile | 1232 | Reused the TU's existing [][11] player tables; typed global render context and float text-call prototypes. Preserved the full-width score argument to the digit formatter, initialized byte maxima before calls as in asm, and tried indexed/pointer traversal and player widths. Stack offsets and saved-register lifetimes remain different. |
| func_801C7310 | IMPROVED 316→301 | did not compile | 1256 | Resolved signed/unsigned declaration conflict, typed float text calls and one-argument audio functions. Rewrote the credits traversal as a do/while list loop with normal switch cases. Corrected timer logic to test the old value (`countdown-- == 0`), as the asm does. Float/register and audio-state scheduling remain different. |
| func_801C4240 | IMPROVED 326→167 | did not compile | 1344 | Correct unsigned tick arithmetic and byte/halfword global widths, typed render context/Gfx, shared command temporary, and removed a spurious fourth audio argument. Existing TU declarations were the key: fixing them lowered the candidate from 335 to 167. Same size as target; projection-output and float spill layout and register choices remain different. |
| func_801BDA6C | IMPROVED 348→300 | 348 | 1328 | Typed Gfx/glyph records, real float matrix-helper prototypes, glyph traversal and a single running x value across translation calls. Tried matrix pointer representations and consolidated command lifetimes. Float/double lifetimes, saved registers and cursor/highlight scheduling remain different. |

## Declaration changes

Production changes are declarations only:

- `src/ovl_7DF8/ovl_7DF8_18520.c`: D_802C8724, D_802D3954 and
  D_802D3958 are u8; D_802D3956 is u16. The target reads these with lbu/lhu.
  The sound ID is explicitly converted to s16 when passed to audio.
- `src/ovl_7DF8/ovl_7DF8_1B790.c`: D_802D39D5 is u8 (target lbu).

Existing matched function bodies are unchanged. The final full image comparison
checks that these declarations preserve every existing match.

Draft-local declarations supply Gfx records, glyph records, render-context layouts,
real float call arguments, and existing TU-compatible player arrays. No yaml or
rodata ownership changes were needed: the existing assembly functions continue
to own their constants and strings. T-043's recipe was read; no candidate reached
a point requiring additional migration.

## Reproduction and scope

`probe.py`, `tu.py` and `ad.py` are the T-056 tools copied with isolated
`/tmp/t070-*` outputs. `check_drafts.py` additionally substitutes each of the nine
retained candidates into its complete source TU and compiles it through production
asm-processor/IDO flags. Run from the repository root:

```
.venv/bin/python tools/scratch/nonmatching/T-070/check_drafts.py
```

Probes were bounded to structural/type/layout variations per function; no inline
assembly or register variables were used. Rejected candidates and bulky logs are
not retained. No main/boot/ovl_7E00 source, protected yaml, Makefile, status.csv,
tracking or worklog files were edited. Missing local prerequisites were symlinked
to the main checkout; ROMs were not copied or staged.

## Final validation

`make clean && make extract && make all && make progress` passed.
The ROM is byte-identical (SHA1 `ba52e91b44450c548467044b26951353dc491e04`),
and main, ovl_7DF8 and ovl_7E00 each printed OK. The overlay SHA1 remains
`ea830aae50ff1422da60d4b7fdbfc29f03b1be39`. `git diff --check` passed.
Progress is unchanged because all improved functions remain assembly-backed.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 63,436 (19.88%) | 63,436 (19.88%) | 0 | 285 | 0 | 277 | 437 (138,092) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 173,204 | 38,264 (22.09%) | 38,264 (22.09%) | 0 | 136 | 0 | 154 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 16,704 (12.15%) | 16,704 (12.15%) | 0 | 149 | 0 | 102 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
