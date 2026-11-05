# T-162

Official counts are full-TU positional words from `tools/permuter/screen.py` (the same number as `docs/t2_drafts.md`).

## Improved

- `func_8001DE5C` (600 B): 155 → 154, still 624 B. The second rectangle's x is sign-extended and then decremented (`bx -= 1`); the `%lo(D_FFFEFFFF)` in the original is `addiu ..., -1`, not a real symbol. Reads are little-endian byte pairs. Sprite stores go through `T022Sprite` plus the three halfwords at 0x14, 0x16 and 0x1A. Frame stays 0x60 versus the original 0x68, so the stack slots for the derived edges (0x18/0x20/0x24/0x30 versus a packed 0x38 block) still shift the rest of the function. Register-masked sequence diff is 79.
- `func_801BCB70` (1,676 B): 258 → 221, 1,672 → 1,668 B. `uls = (pos != 0) ? pos : 0` (same score as the if/else). The preset `uls = 0; if (pos) uls = pos` is still the closer instruction stream (418 vs 420, 12 register-masked) but the missing `b` shifts the positional score to 258. The else arm does not add that `b` without reordering the texture-command block (masked diff 57, three instructions short). Same conclusion as T-157: no honest form both emits the branch and keeps `i` in memory.

## Looked at, not improved

- `func_800238C4` (1,580 B, exact size, 336 words). Register-masked diff is 35–38. The original frame is 0x50 and spills the row `end` at sp+0x40; the draft frame is 0x48 and keeps `end` in `ra`, with `rowBase` in `fp` instead of `ra`. Moving `rowBase = 0` and `pos = 8` to the loop dropped the masked diff 38 → 35 and left the official count at 336. Hoisting `255` into a local and widening `coverage` to `s32` did not change the official count. Saved registers are s0–s7, fp and ra on both sides; the eight-byte gap is that one spill.
- `func_8002E150` (844 B, asin, 179 words, 836 B). Register-masked diff of the T-024 draft is 42; the frame is 0x38 versus 0x60, and `2*x*x` / `2*r` are `add.d` of a value with itself. Rewriting it to take the parameter's address (`*(s32 *)&x`) and to add instead of multiply compiled to 848 B / 200 words (worse). Not kept.
- `func_800216D4` (1,032 B). Reconciling `D_8004D278` with the translation unit's struct (cast to a `[3]` cache table, `(s32)` casts on `boot_dma`) makes the draft compile in the full TU at 230 words / 1,040 B. That is one word worse than the declarations-only 229, so the declarations score was already the real one.
- `func_8002BBD0`: 1,917 vs 1,923 instructions, sequence diff 1,429. Not a six-instruction shift; the bodies differ throughout.
- `func_801B132C`: 292 vs 286 instructions, frame 0x68 vs 0x88, early float/address scheduling differs. Not a single missing block.
- `func_800257FC`: sequence diff 341 of 343 instructions (146 register-masked). Not close.
- `func_80031A38`: draft comment and the 680/920 B gap are the `sd`/`sdl` decoder shape from the T-026 cluster. Left alone.
- `func_80028A00` / `func_800310C0` / `func_801ABB20` / `func_801B849C` / `func_801BFCBC` / `func_801C23C0`: still structurally far (hundreds of words, or a declarations count that T-149 already remeasured in the full TU at 181 for `func_801C23C0`). `func_801BFCBC` still needs the volatile byte update T-157 parked.

A 150-second permuter on `func_8001DE5C` (stack diffs, the padding and dummy-expression weights zeroed) reported a lower score only by rewriting `x2 += dx0; rx = x2` into `x2 = (rx = dx0)`, which drops the added edge, and by inserting an empty statement before the sprite stores. Neither was kept.

No function reached 0 words. `src/` was not changed.
