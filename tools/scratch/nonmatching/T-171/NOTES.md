# T-171

Official counts are `screen.measure` on the full owning translation unit.

## func_801C1990 (ovl_7DF8, 676 B)

- Before: 104 words (`tools/scratch/nonmatching/T-147/func_801C1990-decl.c`).
- After: **91 words**, 676/676 B. `tools/scratch/nonmatching/T-171/func_801C1990.c`.

Lever: a single `s32 value` intermediate holds `(3 - stats[0]) & mask`, and the
`u8` global and the `s32 pending` local are then filled from it as
`pending = D_802D37FC = value` (chained assignment, global on the right). That
one expression is what stops IDO from coalescing the store's source register
into `a0`: the value stays live for both the byte store and the `s32` compare,
so `stats` is not copied to `a2`. Previously only `D_802D37FC` was written and
`pending` was read back, which made IDO move `a0` into `a2` and keep the
decremented index in `a0` (the 104-word register-home gap the T-165 notes
describe).

Dead ends so far: `u8 pending` (99–159 words), `u32 value` (91 in one variant),
`pending = value; D_802D37FC = value;` on two lines (99), writing the store
first (122), `u8 player` (128+), `character = D_8004EA9B[player]` after the
decrement (149+), `D_80127C30[player] > value` (91/92).
