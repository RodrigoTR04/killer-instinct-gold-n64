# T-168

Official counts are full-TU positional words from `tools/permuter/screen.py`.

| Function | Before | After | Bytes | Lever |
|---|---:|---:|---|---|
| func_8001BB64 | 98 | 78 | 636 / 636 | Indexed walk `for (i = 0, dst = colors; i < 3; i++)` so the end address is `D_8004AC92+3` (splat's `D_8004AC95`), plus three pointers declared before the `s16[3]` so the array sits at `sp+0x24` in a `0x38` frame. Primitive color is packed red, then green, then blue. |

| func_80027E1C | 234 | 233 | 936 / 936 | The other actor's scale is loaded once into a local and reused, which removes a repeated address computation and brings the body to the original 936 bytes. |
| func_801C3AA0 | 119 | 108 | 928 / 928 | The `% 3` and `% 5` rolls are both written before `i` and `index` increment, so the red store can sit in the next `guRandom` delay slot. |
| func_801AFFAC | 99 | 80 | 576 / 576 | Each channel scale is its own `(u32)` cast of `temp_f0 * D_802928A8` / `D_802928B0`, and the env command word is stored before its value. |

Dead ends for `func_80027E1C` (not kept):

- Splitting the six float conversions into separate statements in the original's conversion order scores 251 / 1020 bytes (the temps spill).
- Copying `arg1` into a local pointer stays at 233 and still does not save `s0`. The original keeps `D_80061CDC`'s address in `a3`, saves `arg1` in `s0`, and reuses `a1` for the other scale; the draft keeps the address in `a2` and never builds the 8-byte frame.
- The vertex `sh` stores and the display-list `sw` pairs are still scheduled apart from the original, so the one-word drop does not collapse the scattered float and tail differences. Register-masked floor on the previous draft was 78.

Dead ends for `func_801B01EC` (not kept, still 120 / 820):

- Masking the colour in the expression (`(alpha & 0xFF) << 24` and the same for the other two shifts) does spill it out of `s1` onto the stack, but the slot lands at `sp+0x5C` instead of `sp+0x64` and the function grows to 824 bytes (183–185 words across declaration orders). The in-place `alpha &= 0xFF` is what holds the exact 820-byte body.
- The earlier 720 declaration orders, the `func_8002F6F4` else-if, and the swapped `D_801D2EB0` / `D_801D2EB4` stores were not repeated.

Dead ends for `func_801C3AA0` (not kept):

- Computing the first roll as an `s32` before the float subtract stays at 108. The division sequence is still scheduled after the vertex-base load and the `255` constant; the original divides immediately after `guRandom`. Saved-float stores at `sp+32` and `sp+40` are swapped (`f22` / `f24`).

Dead ends for `func_801AFFAC` (not kept):

- Inlining the `& 0xFF` into one expression stays at 99. A `(s32)` cast of the product drops the inlined conversion and emits 320 bytes.
- Double literals `0.1` / `0.2` score 99. Splitting the products into `f64` locals scores 77 but emits 572 bytes (one instruction short; the second constant is loaded during the first conversion).
- Storing the env value before its command word scores 81 at the exact size. `|=` of the low byte after the other two channels also stays at 80 or 81.
- The remaining exact-size gap is the first conversion: `andi` / `mul.d` are swapped and `(color & 0xFF) << 8` is scheduled before `cfc1` instead of beside the second multiply.

Dead ends for `func_8001BB64` (not kept):

- Comparing the cursor with `&D_8004AC95` makes the trip count unknown and IDO emits the alignment-optimized loop (776 bytes, 185 words).
- `s16 colors[3]` with one command pointer is a `0x28` frame and the array at `sp+0x20` (98 words). `int colors[3]` hits offset `0x24` but only a `0x30` frame.
- Reusing one command pointer after the indexed loop scores 84. Same-line command stores, `>=` versus `>`, assigning in the `if`, a ternary clamp, and `0xFA000000 | 0x100` all stay at 78.
- Computing `amount << 2` once and reusing it scores 92. A block-scope `s32` for the primitive pack scores 84 / 640 bytes.
- The other five primitive-pack orders score 80–82. Case 2 / default operand orders do not beat 78.
