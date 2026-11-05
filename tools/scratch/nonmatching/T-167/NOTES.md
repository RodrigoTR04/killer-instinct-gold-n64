# T-167

Official counts are `tools/permuter/screen.py` positional words.

## func_801C3E40 — 88 → 0 words, 504/504 bytes. MATCHED

The published 88 was declarations-only. That draft redeclares `D_802D3940` as a triangle array, so the full unit does not compile. In the unit, `D_802D3940` is `T030Vertex *` and the original multiplies the ring index by 3 (`multu`) then shifts by 4.

Full-unit vertex form `index * 3` with one long-lived `dl` was 121 words / 496 bytes (four saved registers; `3` stayed in a temporary). Giving each display-list store its own block-scoped pointer puts `3` in `s0`, restores the 0x18 frame (`s0`–`s4`), and the `v0`/`a2` prologue. Writing the triangle words as `w0` then `w1` on one line stores `0xA14` before `0xBF000000`. Dropping the `slot` local so every access is `index * 3` moves `mflo` from `t0` to `t1`.

`0.1f` pools into the same rodata image as the old late-rodata constant (the unit's `.rodata` is unchanged). Clean `make clean && make extract && make` reproduces baserom `ba52e91b44450c548467044b26951353dc491e04`.

### Dead ends

- Triangle struct `D_802D3940[slot].v[]` (the declarations draft): conflicts with the unit's vertex pointer.
- Declaration order, `three = 3` / `u8` / `register` / `three = 2; three += 1`: constant propagation puts `3` back in a temporary. Still 496 bytes.
- `do { } while (0)` around a single `dl` local, and a `for` header: 122 words / 496 bytes.
- Explicit `s32 *` cursors for the two counters: 115 words / 492 bytes.
- Caching `Vtx *vtx = &D_802D3940[index * 3]`: 124 words / 416 bytes (the original reloads the global).
- Line breaks that mention `0xA14` before `0xBF000000` swap the saved registers and score 5–7 instead of 0.
