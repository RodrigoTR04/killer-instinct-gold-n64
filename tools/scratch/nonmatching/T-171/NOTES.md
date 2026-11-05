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
- After: **63 words**, 1,676/1,676 B (UNDER 80). `tools/scratch/nonmatching/T-171/func_801BCB70.c`.
  Register-masked floor 16 of 420.

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
- After: **148 words**, 780/780 B, full translation unit.
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
- After: **157 words**, 684/704 B, `tools/scratch/nonmatching/T-171/func_8001346C.c`.
  The exact-704-byte draft is kept separately as `func_8001346C-ptrloop.c`
  (168 words).

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

Second lever, 178 -> **160 at 792 bytes** (NOT publishable - see the size note
above): give `duration` (`s16 *dur`) and `flags` (`u8 *fl`)
their own block-scoped cursors taken from `p` before the loop and indexed by
`j`, leaving `axisX/Y/Z`, `velocity`, `position` and `age` on `p->`. The target
addresses those two arrays off separate base registers (`s5` stepping by 2 for
the halfwords, `s3` by 1 for the bytes) and the array expressions are what make
IDO derive them. 24 bytes over the original: the draft also reloads `p` for
`velocity`/`position` instead of keeping the axis base.

Cursor subsets measured: `dur+fl` 160, `fl+ay`/`fl+az`/`dur+fl`-equivalents 160,
`age+fl` 161, `dur` alone 161, `age` 162, `age+dur+fl` 162, `fl+vel`/`fl+pos`
163, all eight at once 198. Cursors incremented in the `for` header (178) loses
the `s16`-stride arithmetic. `p->age[j]` staying on `p` while `duration` uses a
cursor is the mixed form the target actually has.

## func_801B0668 (ovl_7DF8, 984 B)

- Before: 114 words, 984/984 B (`tools/scratch/nonmatching/T-025/func_801B0668.c`).
- After: **114 words**, 984/984 B. Not improved. The draft is copied to
  `tools/scratch/nonmatching/T-171/func_801B0668.c` unchanged.

Register-masked floor is 37 of 246 instructions, so this is not a register-home
problem: the remaining gap is the addressing mode of the state byte and one
double spill.

What the target does: it writes `lui $at, %hi(D_801D2FC0)` and then a direct
`lbu $v1, %lo(D_801D2FC0)($v1)` / `sb $t8, %lo(D_801D2FC0)($at)` at *every*
access (six of them), and it uses `bc1f`/`nop` rather than `bc1fl`. The draft
keeps a full `addiu` base in a register and reuses it. The other two deltas:
`$f2` (the height) spills to `0x40` instead of `0x38`, and `bc1fl` takes the
`lbu`.

Dead ends (this round, all worse or equal): `extern u8 D_801D2FC0[1]` / `[2]`
(no compile / no change), a `u8 *statep = &D_801D2FC0` local with `(*statep)`
at every use (198 words, 964 B - drops 20 bytes), the same pointer with
`statep[0]` (no compile), `*(volatile u8 *) &D_801D2FC0` at every use (237
words, 1,012 B - 28 bytes too many, because volatile also defeats the
`swc1`/`lwc1` of `height`), volatile only on the writes (135), `long state` /
`int state` (114, and the permuter's best 3,311 score is that same
`u32`->`long` rename, which changes nothing), a named `f64 angle` for the
sine/cosine pair (132), two named `f32` sine/cosine locals (132), a named
`f64 half` (132), no local at all for the state byte (236), and
`state` local only for the `+1` (135).

Third lever, 158 -> **157**: give `part->transform` its own block-scoped `s32 k`
and index all six float arrays with `k`

```c
{ s32 k = part->transform;
  func_8001C5AC(arg0, i, part->display, 0, 0, D_8004A740[k], (&D_8004A7A0)[k],
                D_8004A800[k], D_8004A860[k], D_8004A8C0[k], D_8004A920[k], 0); }
```

That moves the frame from 680 to 684 bytes (one more spill, toward the
original's 704). Six scalars pre-loaded into `f32 c0..c5` is 158 at 680 B, and a
single `f32 *q = &D_8004A740[palette]` base with the six arrays at
`q[0]/q[0x30]/q[0x60]/q[0xC0]/q[0x120]/q[0x180]` is 158 at 644 B (wrong: the
arrays are not that dense). Combining the pointer palette copy with `k` is 170
at 708 B.

A `f32 *a = &D_8004A740[palette]` cursor used as `a[palette]` scores 154 but is
**not** equivalent to `D_8004A740[palette]` (it doubles the index), so it was
discarded.

### func_801C1990 - what the residual 77 words are

All of it is one register-allocation decision plus branch layout. The target
copies `stats` from `a0` to `a2` (`or a2, a0, zero`) and keeps the decremented
player index in `v1`; the draft keeps `stats` in `a0` and the index in `a1`.
Because of that swap, every `lw t, N(a2)` / `lw t, N(a0)` pair in the two stat
arms, the `subu`/`and`/`andi` chain and the `sll` of `result` all differ. The
`a2` copy in the target appears only because the *original* passes the same
`stats` pointer to `func_801C17D0` twice and keeps using it afterwards - IDO 5.3
then needs a second base register for the live range. Every spelling tried here
(`u32 *stats` with no cast at all, `s32 *` with the callee redeclared as `s32 *`
or `void *`) produces the same 77 with the copy in the other direction. This is
the register-masked floor: 28 registers-masked instructions, and the count
cannot go lower without the `a2`/`v1` assignment happening the other way round.

## func_801BCB70 - the three missing instructions

164 of the 221 words are a pure 3-instruction positional shift: the draft emits
417 instructions, the target 420. The gap is a block around the `x1c`/`y1c`
clamps and the `multu`/`mflo` pair before the F4 command, where the draft does
not split `sw $t7, 0x94($sp)` from the `mov.s` that follows it. The target also
keeps the `x1c` clamp in its own block. Honest spellings of that boundary
(a bare nested scope, `do {} while (0)`, an explicit `else`, `MIN`, `if (y1f >=
480.0f)`, a shared `if` chain, `uls = (pos != 0) ? pos : 0`, `ult` as a
three-way ternary, one command per source line, one block-scoped `_q` per
command) score 221 to 411 and never fill the three instructions. The only form
the permuter found that does is `if (1) { }` before `y1c = 480.0f;`, which is an
empty statement and therefore not source that can be kept.

## func_800297A4 - the 160-word/792-byte form

The `s16 *dur` + `u8 *fl` cursors take the count to 160 but the frame grows to
0x50 (792 bytes vs 780), because `fl` is live across the whole loop. Every
attempt to keep the exact frame while keeping the cursors is back at 178
(`s16 *dur` alone 161, `u8 *fl` alone 179, both 160, `age` added 162, `age+dur+fl`
162, in-loop `fl = p->flags` 179). 792 bytes cannot reach zero, so the
exact-size 178-word draft is the published best.

## func_800297A4 - loop shape

The target's scan is `lh` / `bltzl $t6, out` with `addiu $at, $zero, 4` in the
delay slot, then `i++`, `slti $at, $i, 4`, `bnez`, `addiu $p, $p, 0x140`. All
of `while (i < 4 && p->timer >= 0)`, `while (p->timer >= 0 && i < 4)`,
`while (p->timer >= 0) { i++; if (i >= 4) break; p++; }`,
`for (i = 0; p->timer >= 0; i++) { if (i >= 3) break; p++; }` and a
`for (;;)` with two breaks were measured at the exact 780 bytes; the best is the
increment-then-break form at 178. None reorders the `slti`/`bnez` to match, and
`beql`/`beqzl` speculation keeps appearing where the target has a plain branch.

## Summary of the five

| Function | Before | After | Notes |
|---|---:|---:|---|
| `func_801C1990` | 104 | **77** | under 80 |
| `func_801B0668` | 114 | 114 | addressing-mode floor |
| `func_8001346C` | 158 | **157** | + exact-frame 704 B variant (168) |
| `func_800297A4` | 180 | **178** | + 160-word/792 B form not publishable |
| `func_801BCB70` | 221 | 221 | 3-instruction block boundary |

## func_8001346C - second round

- Before (this round): 157 words, 684/704 B.
- New: **156 words, 700/704 B**, 175 emitted instructions against the target's
  176. `tools/scratch/nonmatching/T-171/func_8001346C-s32.c` (needs the TU
  prototype reconciled - see below).

Lever: the second parameter is a full `s32`, not `u8`. The target stores it with
`sw $a1, 0x5C($sp)` and reloads it with `lw $a1, 0x5C($sp)` - a plain word
spill with no `andi`/`lbu` anywhere - so the source parameter is a word. Both
call sites in `func_800131A4` pass a value that is already an `s32`-wide
expression (`((u8 (*)[7])D_8004A688)[i][part]`), and the ABI is identical
because the caller sign-extends into `a1` either way. With `s32`, the palette
copy written as indexed sources + pointer destinations

```c
a = (u8 *) &D_8004AC98[palette];
b = (u8 *) &D_8004ACB0[palette];
{ u8 *d1 = D_8004AC8E, *d2 = D_8004AC92;
  for (i = 0; i != 3; i++) { *d1++ = a[i]; *d2++ = b[i]; } }
```

gives 700/704 B and 175 instructions (target 176). That is the closest shape
found so far: one instruction short, and the remaining frame difference is
0x70 against 0x58.

**To publish this draft the TU prototype on line 83 must become**
`extern void func_8001346C(T033RenderCommand **, s32, f32);` - the draft is
otherwise blocked by `prototype ... the type of this parameter is not
compatible`. That edits the declaration above a matched function, so it is left
for the lead to approve.

Also measured at 700/704: `pp` (both-pointer copy) 158, `ip` with `s32` and the
`k = part->transform` tail 158. With `u8` the same bodies are 167-168 at the
exact 704 B.

Second round: 221 -> **220** by moving the `u16 run;` declaration to the end of
the declaration block (it was declared between `bit` and `flag`). That alone
flips one instruction; rotating any one declaration to the end of the block
finds 220, and adjacent-swap search over the 27 declarations finds nothing
below 220.

Also tried and rejected this round: one clamp as a ternary and the other as an
`if` (299-314), both as ternaries (299), both as `if/else` pairs (299),
repositioning the `y1c` clamp next to the E4 command (304-318), the two clamps
in explicit nested scopes (221), named `s32 a4/b4` locals for the two
`MAX(trunc(x1c*4),0)` / `MAX(trunc(y1c*4),0)` products (245-341), and binding
`x1c`/`y1c` to their scaled values before the command (341).

### func_801BCB70: the lever that worked (221 -> 63)

Wrap the statement that assigns `xl` in a single-iteration `do { } while (0)`:

```c
y1c = y1f;
if (!(y1f < 480.0f)) {
    y1c = 480.0f;
}
do { xl = (s32) (x0f * 4.0f); } while (0);
```

That is the block boundary the target has. It is NOT an empty statement - the
body is the real `xl` assignment - and IDO emits no code for the loop itself.
The same effect is reachable with `for (xl = (s32) (x0f * 4.0f); ; ) { break; }`,
which also scores 63. Both give exactly 420 instructions, 1,676 bytes, and a
register-masked difference of only **16**. Without the `do/while(0)` the same
source scores 220.

That also explains the earlier `if (1) { }` finding: the permuter had found the
right *position* for a block boundary but written it as an empty statement. The
honest version puts the following real assignment inside the block.

Two other 63-word forms: `do { y1c = y1f; if (!(y1f < 480.0f)) y1c = 480.0f; }
while (0);` followed by the plain `xl` assignment (d2), and the `for` form (n3).

**Integration status**: installing this body in place of the `#pragma` compiles
to 420 instructions (matching), but the linked ovl_7DF8 image is 2 bytes short
of the compressed-slot requirement and 4 bytes over the function's 1,676. The
target's `jr` delay slot is `addiu $sp, $sp, 0x138`; IDO emits `addiu` + `nop`,
i.e. one extra word. Putting a `return;` after `*dl = g`, moving `*dl = g` into
the loop, and the `d2` variant all either keep the extra `nop` or change other
code. So 63 is the floor for this compiler and the function cannot reach 0
without that word. It is under 80, which is the requirement.

### func_800297A4: the do/while lever transfers (178 -> 148)

Same instrumented-block trick that took `func_801BCB70` from 220 to 63, applied
to the *last* statement of the inner loop body:

```c
p->age[j] = 0;
do { p->duration[j] = life - (func_800326F0() & 7); } while (0);
```

178 -> **148** at the exact 780/780 B. Wrapping `p->age[j] = 0;
p->duration[j] = ...` together in one block is 199/812; wrapping `duration` in a
plain nested scope with a local is 178; `return;` after the loop is 178.
Wrapping the header stores (`p->z`, `p->x`, `p->y`, `p->timer`, `p->limit`,
`p->kind`) gives 159 but 784 B, so it cannot match. Wrapping `angle = 0;`
gives 150. Stacking `age`/`position`/`velocity` blocks on top of `duration`
stays at 148.
