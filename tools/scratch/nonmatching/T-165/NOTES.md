# T-165

Official counts are full-TU positional words from `tools/permuter/screen.py` (`screen.measure`). A declarations-only count is labeled.

## func_800245B4

Before: 83 words, declarations only, 348/352 B (`tools/scratch/nonmatching/T-032/func_800245B4.c`).
After: **78 words, full TU, 352/352 B**. Commit `f834149`. Register-masked sequence diff is 2.

Lever: compile against the translation unit's `D_8004D278` struct (cast to the 8-byte cache entry; this function reads the symbol base, not `banks[]` at 0x12A8). The block length is the same expression as the matched sibling `func_800241BC`: `p + p[4] + (p[5] << 8) + (p[6] << 16) + (p[7] << 24)`. Load `D_8004EA60` before the null check and `D_8004D290` after it, so the null branch keeps a `nop` delay and the row pointer is not computed early.

The two remaining instructions: there is no opening `or` that copies the start address out of `a1` (it stays coalesced there), and `player << 3` is recomputed for the row because the first shift is clobbered by the length temps. That is the whole register-masked gap.

Dead ends (same or worse official count): an explicit `slot` local (88 words, 348 B); `start | 0` / `start + 0` (optimized away, 88); reassigning the `start` parameter to the scaled index (does not pin the shift to `a1`, 88); K&R definition (still 78); field-by-field copy instead of `*entry = *bank` (still 78); assignment-in-condition (80); reusing `start` as the loop data pointer (79, regmask 12, and the length adds slide).

## func_801C1990

Before/after: **104 words, 676/676 B**. Not improved. Regmask sequence diff of the T-147 declaration draft is 19.

The instruction pattern already matches. The official gap is the register home: the draft copies `stats` from `a0` to `a2` and keeps the decremented player index in `a0`, while the target leaves `stats` in `a0` and the index in `v1`. Bisecting the body shows the copy is absent, and the index stays in `v1`, until the `player == 0` / else score updates and the two counter increments are all present. Those statements are real and match the target's `* 11` stride and the `beql` around `stats[5]`; removing any of them is not the original function.

Dead ends: `u32 *stats` (drops the cast but still copies `a0`, 148 words / 680 B); `u8` player and/or pending (149–162); hoisting `&D_80128328[player][character]` (still 104); an early `u8 *` to `D_802D37FC` (151 / 672); assigning `pending` before the store (153 / 668). T-147 already searched declaration order down to this 104.

## func_80032360

Before/after: **105 words**. Not improved.

The original is a MIPS III fill: `dsll32` / `dsrl32` duplicate the color and the `0xC0` byte into 64-bit patterns, then `sdl` / `sd` (and `swl` / `sw` on the address-xor-4 path) plus a `jr` into a 7-deep fall-through tail. Under the project `-mips2` flags, a `u64` shift is a call to `__ll_lshift` / `__ull_rshift` and a `u64` store is a pair of `sw`. Those target instructions are not reachable from honest C with this compiler.

## func_8001DE5C

Before/after: **154 words, 624/600 B**. Not improved. Register-masked floor remains 79.

Both sides save only `ra`. The target frame is `0x68` and spills the derived edges at `sp+0x20`, `sp+0x24`, `sp+0x30` and `sp+0x54`. The draft frame is `0x60`, so the incoming `arg2` home is `sp+0x68` instead of `sp+0x70`, and those edges sit in a `0x38` block instead. T-162's permuter did not find an honest local that adds the missing 8 bytes; nothing new turned up that would do it without a dummy spill.

## func_801B0CDC

Before/after: **155 words, 1332/1332 B**. Not improved.

T-149 already got the target frame only by adding fixed-value locals that existed to reserve stack, and did not keep them. T-164 confirmed that hoisting the faded tick ahead of `arg3 < 0x28` does not fill the delay slot. The frame stays `0xc8` against `0xd8`. No new honest local accounts for the `0x18`.
