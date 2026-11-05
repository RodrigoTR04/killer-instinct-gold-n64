# T-171

Official counts are `screen.measure` on the full owning translation unit.

## func_801C1990 (ovl_7DF8, 676 B)

- Before: 104 words (`tools/scratch/nonmatching/T-147/func_801C1990-decl.c`).
- After: **77 words**, 676/676 B. `tools/scratch/nonmatching/T-171/func_801C1990.c` (UNDER 80).

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

Further: reading the two stat rows straight out of `stats[]` instead of through
the `value` local (`if (D_80128328[player][character] < (u32) stats[3])
D_80128328[player][character] = stats[3];`) takes 91 -> **89**. That is the
first `lw`/`lbu` scheduling pair in the row updates. Direct reads for all four
rows at once is 135 words, so only the `player == 0` arm may use them.

## func_801BCB70 (ovl_7DF8, 1,676 B)

- Before: 221 words (`tools/scratch/nonmatching/T-162/func_801BCB70.c`), full TU.
- After: **221 words**, 1,668/1,676 B. Not improved. No commit of a draft change.

The permuter found a 97-word form, but only by inserting `if (1) { }` before
`y1c = 480.0f;` inside the 480 clamp. That is an empty statement: it changes
IDO's block numbering without adding code, so it is not honest source. Nine
honest substitutes for the same block boundary (a bare nested scope, a
`do {} while (0)`, hoisting `y1c = y1f` above the `x1c` clamp, an explicit
`else`, `if (y1f >= 480.0f)`, and a shared `if` chain) all score 242-326.
The 97-word draft was not kept.

What the 97-word form shows about the original: the target's `y1c` update does
sit inside its own block, and only then does `sw $t7, 0x94($sp)` (the cached
`bottom - top`) land in the right slot. The draft spills that to 0x98 instead,
which is the whole 8-byte frame difference.

Dead ends recorded: `uls = (pos != 0) ? pos : 0` (already 221, same as if/else),
the preset-then-assign `uls = 0; if (pos) uls = pos;` (closer instruction
stream, 242 official because a `b` is missing), swapped `y1c`/`x1c` clamp order
(321), and every honest block-boundary form above.

## func_800297A4 (main, 780 B)

- Before: 180 words, declarations-only (`tools/scratch/nonmatching/T-024/func_800297A4.c`).
- After: **178 words**, 780/780 B, full translation unit.
  `tools/scratch/nonmatching/T-171/func_800297A4.c`.

Lever: the slot scan is a do/while-free `while (p->timer >= 0) { i++; if (i >= 4)
break; p++; }` (increment then a break test) instead of
`while (i < 4 && p->timer >= 0)`. The target's `bltzl` + `slti`/`bnez` pair is
that shape; the `&&` form emits a `beqz` on the combined predicate instead.
Also worth keeping: the draft is a typed view of the TU's `D_80061D60` with no
redeclaration, which is what makes it compile in the full unit at 780 bytes.

The register-masked floor is 46, and the remaining official gap is two 32-bit
float temporaries: the target keeps `(float) (u32) (...)` at 0x300/0x324/0x332
of the stack and spills the `add.s` schedule differently. Dead ends: the
two-counter loop (`i += 2`, `j`, `angle`) written as `for (...; angle != 1080; ...)`
(192-194), `base = angle - 30` as a block-scoped local (179-180), reading fields
through `D_80061D60[i]` (197-203), per-array cursor pointers (192, and 218 when
all eight cursors are separate), and `while (p->timer >= 0 && i < 4)` (179).

## func_8001346C (main, 704 B)

- Before: 158 words, 680/704 B (`tools/scratch/nonmatching/T-166/func_8001346C.c`).
- After: 158 words, 680/704 B when indexed; **168 words at the exact 704/704 B**
  with the pointer-loop form below. The pointer-loop draft is kept as
  `tools/scratch/nonmatching/T-171/func_8001346C-ptrloop.c`; the published best is
  still the 158-word indexed draft, because 168 > 158 and the official count is
  what matters.

New finding (not in the T-166 notes): copying the palette rows through four
block-scoped cursors

```c
u8 *src = a, *dst = D_8004AC8E;
u8 *src2 = b, *dst2 = D_8004AC92;
for (i = 0; i != 3; i++) { *dst++ = *src++; *dst2++ = *src2++; }
```

gives **exactly 704/704 bytes** and 176 instructions (the target's counts) at
168 words - the frame is right for the first time. Without the block scope the
draft is 158 words at 680 B. So the original writes those two rows with
incremented pointers, not with `D_8004AC8E[i] = a[i]`; the 0x58 frame follows
from that. The remaining words come from the `u8 arg1` home: the target keeps
the index in `a1` and reads `sll/subu/sll` straight off it, while this draft
stores it to `0x7C(sp)` and reloads with `lbu`.

Dead ends: `unroll` (six explicit stores) 149 words / 696 B, which is worse than
the baseline; `*(D_8004AC8E + i) = *(a + i)` 178 words / 736 B; converting the
clear loop at the end to an indexed form 182-183 words.

Second lever, 89 -> **77**: write the "already applied" test as the global
compare `if (D_802D37FC == 3)` instead of the local `if (pending == 3)`. Because
the byte was just stored, IDO keeps it in a register for `pending` but still
re-reads the global for the test, and that re-read is what the target's
`andi $t1, $t6, 0xFF` / `bne $t1, $at` pair shows: the target compares the
*stored* byte against a freshly materialised 3. With the local compare IDO
reused the register and skipped the `andi`, and also hoisted the
`lui/addiu D_802D37FC` above the `bnez`. Keeping the `value` intermediate
(`value = (3 - stats[0]) & mask; pending = D_802D37FC = value;`) plus the local
reload in the `pending > 0` arm was already right; only the compare operand
changed.
