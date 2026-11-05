# T-170

Official counts are full-TU positional words from `tools/permuter/screen.py`
(`screen.measure`, the `docs/t2_drafts.md` score). Target / draft frame sizes are
from `tools/scratch/nonmatching/T-170/stackall.py`.

| Function | Before | After | Bytes | Instr | Status |
|---|---:|---:|---|---|---|
| func_801BADEC | 99 | **74** | 568/568 | 142/142 | under 80 |
| func_801BB7B4 | 220 | **17** | 940/940 | 235/235 | under 80 |
| func_801B01EC | 120 | **119** | 820/820 | 205/205 | not under 80 |
| func_801B0CDC | 155 | 155 | 1332/1332 | 333/333 | not under 80 |
| func_801C23C0 | 181 | 181 | 1812/1820 | 453/455 | not under 80 |

Two of the five are under 80 (func_801BADEC and func_801BB7B4); the other three
are at their honest floors as far as I could take them, each blocked by a
specific and recorded obstacle (below). Nothing was moved into `src/`; nothing
reached 0.

---

## func_801BADEC (ovl, 568 B) — 99 -> 74

The count was already 74 in the earlier work on this function; the file named
`func_801BADEC.c` in this directory had been left at an older 99-word draft, so
the first thing this turn did was restore the 74-word draft as the canonical
`func_801BADEC.c`. No further reduction was found. Register-masked diff is 12.

**Dead end (already recorded in T-167, reconfirmed):** the 8 missing bytes are
the second `lui`/`sw` of each window counter. IDO deletes `*counter = frame` in
the draw arm because the same value was stored before the test, so the original
has a redundant store pair that honest C does not reproduce at this size.

## func_801BB7B4 (ovl, 940 B) — 220 -> 17. 940/940 B, 235/235 instructions

The declarations had to be reconciled with the owning unit first (the previous
turn's `D_802C9F69` / `T023Sound` work), which took the full-TU score from a
compile failure to 195. Three levers then took it to 17:

1. **`arg0` is reassigned, not copied.** `arg0 = arg0 + 1;` on the `u8` parameter
   emits the target's `or a2,a0,zero` / `addiu a2,a2,1` / `andi t6,a2,0xFF` /
   `or a2,t6,zero`. A separate truncating local (`u8 next = (arg0 + 1) & 0xFF`)
   instead reserves a stack slot and shifts the frame from 0x20 to 0x28. This one
   change: 195 -> 136.
2. **Two sound blocks rebuilt as block-scoped `u8 *p` + `s16 sound`.** The
   pointer makes the counter address (`lui` + `addiu`, then `lbu 0`) and the
   increment share one base; the `s16` keeps the `lh` out of the `jal` delay
   slot. `D_80127CE8[0][*p]` (not `D_80127CE8[*p][0]`) — the unit declares
   `u8 [][11]`, so the target's flat `addu`/`lbu %lo` is the `[x][0]` form.
3. **`D_802C8CB9` read as `D_802C8CB8[1]`** so the `lui`/`lbu 1` pair matches;
   the unit's `s8 D_802C8CB9` extern emits `lb`.

`D_80066C40` must stay the direct argument (no `handle` local) — caching it
hoists the `lui`/`lw` above the index chain and scores 231.

**Remaining 17 words, one schedule:** frame 0x30 against 0x20 because the two
block-scoped pointer+short pairs each get a stack home, and the target reloads
`D_80066C40` *after* the `sll`/`addu`/`subu` chain (the draft loads it just
before, pushing `sb t4,0(v1)` one slot earlier). Hoisting the pair to function
scope, a `struct { u8 *p; s16 sound; }` per block, `sound` before `p`, and an
inline `func_8002F6F4(..., D_801F2EB8[...].sound, ...)` with no local are all
17 or worse.

## func_801B01EC (ovl, 820 B) — 120 -> 119. 820/820 B, 205/205 instructions

`declorder.py` (260 s, 12 threads) found a source-layout win: the function
signature's `{` on its own line, and the `guRotate` / `result = 2` /
`angle > 60` statements plus the display-list store pairs on shared source
lines. That is 119 and `initial_exhausted: true` — a second 260 s pass from the
winner returned 119 again, so the layout space is exhausted.

**Why it cannot go lower.** The target's frame is 0xB0 with the colour in the
**stack slot at sp+0x64** (`sw t7,0x64(sp)` before the first test, `lw v0,0x64(sp)`
at the tail) and only `s0` saved besides. The draft holds the colour in `s1`,
which is why it saves an extra register and puts `sdc1 f20` at 0x30 instead of
0x38. Every honest way of making the colour a memory object (`volatile`,
address-taken through a used pointer, `s32[1]`, `u8`) moves the spill to
0x5C/0x60 and the body grows to 824–840 B. `(alpha & 0xFF)` inside the shift
expression gives the right 0x64 slot but 824 B, and 206 instructions. The exact
820 B body only exists with the colour in a saved register.

Also tried and rejected (all 120 or worse, exact 820 B): `u32 alpha`,
`register s32 alpha`, a `f32 zero` local for the `0.0f` operands (120),
`D_802C8750` as `u32` / `volatile` / `s32[]`, a `tick` local in place of the
`arg3` mirror (130), `u8 alpha` with and without the redundant `&= 0xFF`
(177/185 — the target stores a *word*, so `u8` emits `sb`). Two 1,500 s
decomp-permuter runs (`--stack-diffs`) bottomed at weighted score 3,298, which
scores 179 in official words — worse than the layout win.

## func_801B0CDC (ovl, 1,332 B) — 155 unchanged (1,332/1,332 B, 333/333 instr)

**The frame is the whole score and the target's extra 0x18 is dead space.**
The target frame is 0xD8 with the 0x40 `guLookAtReflect` matrix at sp+0x98
(0x98 + 0x40 = 0xD8) and the sin/cos spill temps at sp+0x58/0x5C. Nothing in the
function's assembly occupies 0x68 through 0x94 — the target simply reserved
0x18 more stack than its own locals need. The draft frame is 0xC0 with the
matrix at 0x88.

I swept every honest local that the function plausibly owns (an `eye` struct or
`f32[3]` or three named floats, separate `temp_f0` / `temp_f12` / `f64 var_f18`,
a named `n1`) inserted at every declaration position: 132 variants, and the
frame never exceeds 0xC8. Named `eyeX/eyeY/eyeZ` at least restore the exact
1,332 B and 333 instructions — that is the draft kept here.

This confirms T-165's conclusion independently: the only draft that ever reached
0xD8 did it with fixed-value locals that existed purely to reserve stack, which
is not honest source.

Two 1,500 s permuter runs bottomed at weighted 3,877 (official 278, and it grows
the body to 1,340 B), so the search is not finding anything either.

## func_801C23C0 (ovl, 1,820 B) — 181 unchanged. 1,812/1,820 B, 453/455 instr

I rebuilt the function from the assembly against the owning unit's real views
(`func_801C2110(f32, f32 *, f32 *, f32 *)` from `ovl_7DF8_13FF0.c`, the
`D_802D3898[3][4]` coefficient table, `D_80293778`/`D_80293788`/`D_80293798`
doubles and `D_802937A0`), which is a much cleaner source than the old draft but
scores 276. It does take the frame from 0x98 to 0x80, and it shows where the
real gap is:

The target passes `addiu a2,sp,0x64` (position) and `addiu a3,sp,0x58`
(velocity) — two 12-byte `f32[3]` arrays packed head-to-tail at 0x58..0x70,
with a single 4-byte temporary at 0x4C, in a **0x70** frame. The old draft has
position at 0x64 and velocity at 0x54 in a 0x98 frame; the clean rebuild has them
at 0x74/0x68 in 0x80. The residual 181 is the old draft's 0x28 of unused frame
plus the register pressure that follows from it (the target's `sp+0x4C`
temporary is `swc1`-spilled in the draft at 0x5C/0x60, which shifts every later
slot by 4).

A `declorder.py` run (240 s, 12 threads) on the old draft reported
`181 -> 181 baseline`, so the declaration order space is exhausted there. Two
decomp-permuter runs on each draft bottomed at weighted 1,816 and 3,877; the
1,816 one scores 181 official, i.e. the same. The remaining difference is spread
across the whole body (register-masked diff 40), not one missing block.

---

## What was not done

No function reached 0 words, so `src/`, `docs/functions.csv` and
`docs/t2_drafts.*` were not touched, and no baserom-sha1 verification was needed.
Nothing was pushed and no PR was opened.

Drafts kept here as the best honest form of each function:
`func_801BADEC.c` (74), `func_801BB7B4.c` (17), `func_801B01EC.c` (119),
`func_801B0CDC.c` (155, identical to `T-149/func_801B0CDC.c` but with the
`eye` fields named individually), `func_801C23C0.c` (181, the T-147 draft).
