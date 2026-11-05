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

## func_801BADEC — 99 words, 560/568 bytes. Unchanged

The 99-word offset draft already has the prologue (including `sw a3`) and the `nop` in the `jr` delay slot. The 8 missing bytes are the second `lui`/`sw` of each window counter. IDO deletes `*counter = frame` in the draw arm when the same value was stored before the test.

### Dead ends

- Sibling inline scale (no shared `yOffset`): 101 words / 560 bytes, masked diff 73.
- Storing `frame` only in the low arm and the draw arm, with `D_801F3AA8` as `s32[]`: 134 words / 576 bytes. The extra stores are not the original's redundant pair, and the function grows by 8.

## func_801B0668 — 114 words, 984/984 bytes. Unchanged

The masked diff is the `D_801D2FC0` address. The original uses `lui`/`lbu %lo` and the load kills the address register; the draft keeps a full address (`addiu` + `lbu 0`) and uses `bc1fl` with the load in the delay slot. Also `sltiu` against `slti`, a missing `andi 0xFF`, a missing `or` copy, and the double spill at 0x40 against 0x38. Height at 0x5C and the sine spill at 0x48 already match. `volatile` does not split the address: IDO still shares it, and the score stays 114.

### Dead ends

- `s32 state` and `(state + 1) & 0xFF`: 224 words / 988 bytes.
- `u8 state`: 230 words / 992 bytes.
- `s32 next = state + 1` with the store `next & 0xFF`: the else store becomes a fresh `%lo` via `$at` and `slti`/`andi` appear, but the other arm still keeps the address. 237 words / 992 bytes.
- Caching the then-arm flag in a local: same 237 / 992.
- Moving or block-scoping the `f64` product: spill stays at 0x40 (114), or 119 if the local is declared first.
- Declaring `state` only inside the else: 132 words, and the double spill moves to 0x48.

## func_801C1434 — 132 → 3 words, 720/720 bytes

`D_802D3800[player - 1]` is `D_802D37F8 + player * 8` with a `-8` immediate. `((u64 *) &D_802D37F8)[player]` addresses that symbol directly; once relocations are masked, the high-half `lw 4` matches `%lo(D_802D37FC)`. Assign `player` inside each arm of `if (D_8004A407)`, and do not cache `D_802D3810`. The last call reloads the global: `3 - D_802D37FC * 2`. The frame is then 0x40.

The last 3 words are one schedule. The `beqz` delay slot is `lui s0, %hi(D_802D37FC)` against `lui v0, %hi(D_802D37FD)`, the `lui` at the join is swapped the other way, and `bne` has `s0, v0` against `v0, s0`. Both symbols share a `%hi`, so only the register fields differ.

### Dead ends

- A `flags` local for `D_802D3810`: frame 0x48, 36 words.
- A `shown` local loaded before `player`: frame 0x48, 27 words, and the `lbu` destinations swap.
- Comparing the two globals without assigning `player` first: 728 bytes, 132 words.
- `player == D_802D37FD` instead of `D_802D37FD == player`: still 3.
- Packing two named `s32` halves with `<< 32` calls the 64-bit shift helper. Not used.
