# T-168

Official counts are full-TU positional words from `tools/permuter/screen.py`.

| Function | Before | After | Bytes | Lever |
|---|---:|---:|---|---|
| func_8001BB64 | 98 | 78 | 636 / 636 | Indexed walk `for (i = 0, dst = colors; i < 3; i++)` so the end address is `D_8004AC92+3` (splat's `D_8004AC95`), plus three pointers declared before the `s16[3]` so the array sits at `sp+0x24` in a `0x38` frame. Primitive color is packed red, then green, then blue. |

Dead ends for `func_8001BB64` (not kept):

- Comparing the cursor with `&D_8004AC95` makes the trip count unknown and IDO emits the alignment-optimized loop (776 bytes, 185 words).
- `s16 colors[3]` with one command pointer is a `0x28` frame and the array at `sp+0x20` (98 words). `int colors[3]` hits offset `0x24` but only a `0x30` frame.
- Reusing one command pointer after the indexed loop scores 84. Same-line command stores, `>=` versus `>`, assigning in the `if`, a ternary clamp, and `0xFA000000 | 0x100` all stay at 78.
- Computing `amount << 2` once and reusing it scores 92. A block-scope `s32` for the primitive pack scores 84 / 640 bytes.
- The other five primitive-pack orders score 80–82. Case 2 / default operand orders do not beat 78.
