# T-163

Official counts are `tools/permuter/screen.py` positional words (relocation fields masked). Sequence counts are from `tools/scratch/nonmatching/T-155/cmp.py`.

## func_80012B7C — 327 → 325 words, 1572/1576 bytes

Putting each `command` assignment and the following `value` assignment on one source line lets IDO store the value word before the command word, which is the original order for the constant display-list pairs. The register-masked sequence difference falls from 62 to 14. The official positional count only moves 327 → 325 because about 200 aligned instructions still differ by temporary register (`t3`/`t2` in the original, `t1`/`t0` here, starting at the third command). Saved registers `s0`–`s6` and `f20` already match, and the first 30 instructions match exactly.

Still open, and why they were not committed:

- Writing the value on its own line before the command fixes more of the store order (masked 30) but swaps which temporary receives the constant, and the official count goes back up to 330.
- Hoisting the `2` / `0xFFFE` mode and mask before the `D_8004AA28` branch, so both arms share them, emits 1568 bytes and 326 words. The original materializes `0xFFFE` and `0xFFFD` with `ori` (zero-extended). The delay-slot form in this draft is `addiu` of `-2` / `-3`.
- One `or` that saves the matrix offset across `guMtxCatF` is missing (393 instructions vs 394). The following reload of `D_80044A24` overwrites that register, so keeping the copy live is not a natural use.

## Dead ends

- `func_800297A4`: casting the existing `D_80061D60` instead of redeclaring it compiles in the full translation unit at the same 180 words / 780 bytes. An angle-bounded loop with a step-2 branch counter (`j < 8` / `j < 16`) scores 198 / 796 and was not kept.
- `func_801BF190`: using the translation unit's `T100ScoreTable` compiles in the full unit at 284 words / 1256 bytes, the same count as the old declarations-only score. An unaligned `*(u32 *)(buffer + 1) = name` (the original's `swl`/`swr`) scores 313 / 1248. Register-masked floor is 128; several spills differ by 28 bytes.
- `func_801ACB1C`: prototypes that match `func_801AD3BC` / `func_801AD7D8` (`DisplayCommand`, `RenderState`, fifth argument `s32 *`) compile in the full unit at 176 / 756, same as declarations-only. That needs `DisplayCommand` visible before the function; moving the typedef shifts line numbers of later matched functions, so the overlay source was left unchanged. Frame is still 0x68 vs 0x60. Masked floor 78.
- `func_80027E1C`: 234 official words, 235 vs 234 instructions, masked sequence floor 78. The differences are scattered through the float interpolation and the display-list tail, not one store-order block.
- `func_80025FC4` masked floor 126 (475 vs 477 instructions). `func_801AFAA4` masked floor 94 (8 instructions short). `func_801B9A04` masked floor 197. `func_80028230` masked floor 220 (11 instructions short). None of those floors is under 80 without a structural rewrite, and no single declaration or store-order change moved the official count.
