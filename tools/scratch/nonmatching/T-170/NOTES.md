# T-170

Official counts are full-TU positional words from `tools/permuter/screen.py` (the
`docs/t2_drafts.md` score).

## func_801BB7B4 (ovl, 940 B)

Before: 220 official, declarations-only, full TU failed to compile (`D_802C9F69`).
After: **17 official, full TU, 940/940 B, 235/235 instructions.** Commits `2a84a195`,
`0bc8f1b9`, `07b91552`.

The declarations had to be reconciled first (previous turn: `D_802C9F69` and the
`T023Sound` view) so the unit compiles; that took the full-TU score to 195.

Levers that actually moved it:

- **`arg0` is reassigned, not copied.** `arg0 = arg0 + 1;` (u8 parameter) makes
  IDO emit the target's `or a2,a0,zero` / `addiu a2,a2,1` / `andi t6,a2,0xFF` /
  `or a2,t6,zero` sequence. A separate `u8 next = (arg0+1) & 0xFF` local instead
  reserves a stack slot and shifts the frame to 0x28. This single change took
  the count from 195 to 136 and the frame from 0x28 to the correct 0x20.
- **The two sound blocks reload `D_80066C40` after the index math**, not before.
  Caching the handle in a local (`s32 handle = D_80066C40;`) hoists the `lui`/`lw`
  above the `sll`/`addu`/`subu` chain and scores 231.
- **Block-scoped `u8 *p` and `s16 sound` per sound block.** The pointer makes the
  counter address (`lui` + `addiu`, then `lbu 0`) and the increment share one
  base, which is what the target does; a plain `D_802C8D0D++` in the index makes
  IDO fold `addiu` differently. The `s16 sound` local is what keeps the `lh` out
  of the `jal` delay slot.
- `D_802C8CB9` is `s8` in the unit; the second `else if` sound uses `D_802C8CB8[1]`
  so the `lbu`/`lbu 1` pair matches (an `s8` extern emits `lb`).
- The final block tests `D_802C8CE0 & 3` three times rather than caching it in a
  local; caching moves `andi`/`lui` out of the delay slots.

Remaining (17 words, all one schedule): the frame is 0x30 against 0x20 because
the two block-scoped `u8 *p` + `s16 sound` pairs each get a stack home, and the
`(u8 *) D_802C8CE0 &` test keeps an extra copy. The target reloads `D_80066C40`
*after* the `sll`/`addu`/`subu` index chain and before `jal`; the draft loads it
just before the chain, which pushes `sb t4,0(v1)` one slot earlier.

Further levers that did not help (all 17, 940/940):
hoisting `p`/`sound` to function scope (frame 0x28, 17 words), a
`struct { u8 *p; s16 sound; }` per block (17), `sound` declared before `p` (17),
an inline `func_8002F6F4(..., D_801F2EB8[...].sound, ...)` with no `sound` local
(201 words, 952 B).

### Dead ends

- `u8 next = (arg0 + 1) & 0xFF` / `(u8)(arg0 + 1)` / `next &= 0xFF` / `next++`
  / `next = arg0; next += 1`: 231 words, frame 0x28 (the extra local reserves a
  slot). All 24 combinations of {u8,s32,u32} parameter x {u8,s32,u32,s8} local
  were swept; only reassigning the parameter keeps the 0x20 frame.
- `s32`/`u32` parameter with a truncated local: exact 940 bytes and 235
  instructions but 195 words, because `sll`/`sra` sign-extension pairs appear at
  each `next` test.
- Declaration initializer (`u8 next = arg0 + 1;`): 231, frame 0x28.
- `s32 handle = D_80066C40` in the sound blocks: 231 (hoists the load).
- `D_80127CE8[0][D_802C8D0D]` instead of `D_80127CE8[D_802C8D0D][0]`: 231 and
  the function shrinks to 936 B; the unit declares it `u8 [][11]`, so the row
  stride is 11 and the target's flat `addu`/`lbu %lo` is the `[x][0]` form.
