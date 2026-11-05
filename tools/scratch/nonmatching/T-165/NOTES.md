# T-165

Official counts are full-TU positional words from `tools/permuter/screen.py` (`screen.measure`). A declarations-only count is labeled.

## func_800245B4

Before: 83 words, declarations only, 348/352 B (`tools/scratch/nonmatching/T-032/func_800245B4.c`).
After: **78 words, full TU, 352/352 B**. Register-masked sequence diff is 2.

Lever: compile against the translation unit's `D_8004D278` struct (cast to the 8-byte cache entry; the function reads the symbol base, not `banks[]` at 0x12A8). The block length is the same expression as the matched sibling `func_800241BC`: `p + p[4] + (p[5] << 8) + (p[6] << 16) + (p[7] << 24)`. Load `D_8004EA60` before the null check and `D_8004D290` after it, so the null branch keeps a `nop` delay and the row pointer is not computed early.

The two remaining instructions: there is no opening `or` that copies the start address out of `a1` (it stays coalesced there), and `player << 3` is recomputed for the row because the first shift is clobbered by the length temps. That is the whole register-masked gap.

Dead ends (same or worse official count): an explicit `slot` local (88 words, 348 B); `start | 0` / `start + 0` (optimized away, 88); reassigning the `start` parameter to the scaled index (does not pin the shift to `a1`, 88); K&R definition (still 78); field-by-field copy instead of `*entry = *bank` (still 78); assignment-in-condition (80); reusing `start` as the loop data pointer (79, regmask 12, and the length adds slide).
