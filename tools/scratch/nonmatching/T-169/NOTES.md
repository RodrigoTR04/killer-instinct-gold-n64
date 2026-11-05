# T-169

Official counts are full-TU positional words from `tools/permuter/screen.py` (`screen.measure`).

| Function | Before | After | Bytes | Lever |
|---|---:|---:|---|---|
| func_801AFFAC | 80 | 59 | 576 / 576 | The two channel scales are `(u32)` casts of `temp_f0 * D_802928A8` / `D_802928B0`, but the `w1` OR chain is written green-first (`(var_a3 & 0xFF) << 8`, then the blue `andi`, then `red << 24`) so IDO emits the first `andi` before `cfc1` and puts the `sll *,8` beside the second multiply. |

## func_801AFFAC

Before 80, after **59**, exact 576 bytes, full TU, commit `c70f33c`.

The 99 -> 80 step (T-168) had made each channel scale its own `(u32)` cast and
moved the env word ahead of its value. The remaining gap was purely the first
conversion's schedule. Writing the composite word in the order the target builds
it (green byte first, then the blue `andi`, then the red shift) is what fixes it:
`temp_a0->w1 = ((var_a3 & 0xFF) << 8) | (((u32)(temp_f0 * D_802928B0) & 0xFF) << 16) | red << 24;`
with `red = (u32)(temp_f0 * D_802928A8)` and `mid` declared but unused for the
OR (the blue expression is repeated so IDO keeps the `andi` on the first
product). Register-masked sequence diff falls to 5 of 144 words; the five are the
`sw w1`/`sw w0` pair on the second command (a scheduler tie) and the trailing
`sw` order. Saved.

Dead ends (not kept):

- Inlining `mid` in place of the repeated blue expression: 80 words, and the
  `andi` moves after `cfc1`.
- `green` reused for the second command's `w1` instead of `green << 24`: 81.
- `p0`/`p1` split declarations, `f64` locals for the products, and any OR order
  starting with red or blue: 80-99.

## func_8001D47C

Before 134, best **134** (744/748). Not improved. Register-masked sequence diff
of the T-022 draft is 10 words of 187; the 134 is almost entirely register
allocation, so every honest rewrite lands on the same count.

What the target does and the draft cannot reproduce:

- The `bnez D_8004EA78` null-path `nop` is filled with `lui t4,%hi(D_801D3433)`.
  Reordering the `&&` operands to `(D_801D3433 != 0) && (D_8004EA78 == 0)` *does*
  fill it (variant `dy/k1.c`), but then the `beqz` after the `lbu` keeps a `nop`
  and the extra `bnez` slides, so the count stays 134.
- The target loads the palette into `v0`, copies it to `a0` for the grayscale
  loop and keeps the *source* in `v0`; the draft always swaps the two, so every
  load/store in the 4x-unrolled grayscale body differs by register name.
  Naming the copy (`p = var_v0;`) before the `*_EAB8` test gets the *copy* but
  the grayscale body still comes out 6 words worse (136) because the extra live
  pointer costs a register elsewhere.  Hoisting `&D_8004EA9E[arg0]` into an
  `entry` pointer is neutral at 134.
- The target's zero-fill and copy loops are 4-wide with the final `sh -8` in the
  branch delay slot. Writing them out 4-wide (rotated store order, or `dst[i]`)
  compiles to 214-217 instructions (856-868 bytes) instead of 187; IDO also
  unrolls the `i += 2` form to 2 only.

Dead ends (all 134 unless noted): 16-declaration order hill-climb (stopped at
134), `entry` hoist before/after the palette copy (134/136), a `p = var_v0`
copy before the test (136), the copy inside each branch (160), three tail-loop
shapes with `dst[i]`/`((u16*)0)[i]`/`<` (134), `s32`/`u16`/`s16` pixel and
level types (134-162), 4-wide explicit unrolls (163-164), permuter (1350
weighted -> 134 official after removing its dummy statement), and the T-022
T-126 draft itself (134).

## func_8001DE5C

Before 154, best **152** (624/600). Not improved enough. Frame stays `0x60`
where the target has `0x68`.

The target spills four derived edges at `sp+0x20`, `0x24`, `0x30` and `0x54` and
the incoming `arg2` home is `sp+0x70`. The draft's spill block sits at
`sp+0x38..0x4c` and `arg2` at `sp+0x6c`, i.e. exactly 8 bytes low. Adding one
unused `s32` local widens the frame to `0x68` and moves `arg2` to `0x70` (152
words) but does **not** move the derived-edge block, and an unused local is not
honest C, so it was not kept.

Dead ends: a fifth `color` field in the rect struct (frame 0x80, 158), reusing
the rect fields for the spanned edges (`b.x2 += dx;` / `b.y2 += dyb;` -- 158/632
with a 0x80 frame), 120 random declaration orders of the 13 scalars (all 152),
T-162's own permuter run (5664 weighted, 156 official), and a 900s permuter run
(4805 weighted, 156 official).

## func_801B1A7C

Before 206 (declarations), **206 full TU** (596/872). Not improved.

The declarations score was already the real one: with `void *` parameters and a
local `T169Vertex *` cast the draft compiles in the full owning TU at the same
206.

The blocker is the loop unroll factor. The target is IDO's ordinary 4x unroll
(`andi v0,0x3` preheader, four copies, remainder loop). At `-O2`, this body
unrolls **2x only** (`andi v0,0x1`); the second integer multiply (two `multu`
per iteration) crosses IDO's unroll cutoff. Measured directly:

- one scaled store in the loop: 4x (`andi t6,a1,0x3`);
- two scaled stores, or one scaled store plus any second float/double op: 2x.

Options tried and rejected: `-O3` for this TU (asm-processor refuses with
"Wrongly computed size for section .text", and the sibling `func_801B1A14` is a
byte-exact `-O2` match -- it changes under `-O3` before the call is even
reached); IDO 7.1 (same 2x); `-mips1`; hand-written 4x unroll with a
`(n & 3)` prologue (299 words / 1220 bytes); pointer-walk loops (204-208);
`while (n--)` (207 / 300 bytes -- IDO collapses it); naming `radius`, `256.0f`,
`0.5` and `1.5` as locals; `f64` locals for `amount`; `continue` forms;
`i != count + 1` / `i < count + 1` / `i--` shapes; a permuter run (11368
weighted, no unroll change).

## func_801C317C

Before 215 (declarations), **233 full TU** (896/936). Not improved.

Getting the full TU to compile is the useful result here: `D_80285574` is the
owning TU's `s32 D_80285574` (a `D_8028326C[selected]` menu-table base, set by
`func_801C224C`), so the draft's `u8 ***` extern has to become
`extern s32 D_80285574` with explicit `(u8 **)*(u8 **)&D_80285574` indexing.
`D_802C9F70` is the TU's `FrontendRenderContext` (`.matrices` at 0xF8), and the
text helpers are the `frontend.h` prototypes. With those, the function compiles
in `ovl_7DF8_13FF0.c` at 896/936 bytes.

Remaining diff is register allocation plus the float-argument scheduling of the
two `func_801BDF94`/`func_801BD640` calls; the register-masked sequence diff is
123 of 234 words, so this is not one missing block. The target also reloads
`D_802D3834` before each call (the draft keeps it in a register), which is what
the `lui %hi(D_802D3834)` / `lw` pairs in both loop headers are.

Dead ends: the `u8 ***` extern (does not compile -- conflicts with the TU's
`s32`), the T-147 draft (declarations-only 215, 932 bytes), and the early-return
form T-164 measured at 232.

## Dead ends added after the first notes commit

### func_801AFFAC

Nothing further needed: it is at 59 and saved.

### func_8001D47C (additional)

The grayscale loop *is* 4-wide in the target but not by IDO's unroller: the loop
index steps by 8 (`addiu $t0,$t0,0x8`) and each pass does four `lhu`/`sh` pairs,
i.e. it is hand-written. Reproducing that shape:

- `src[0..3]` / `dst[0..3]` with `i += 8`: 197 words, 872 bytes (target 187 /
  748) -- the indexed form reloads the base every store.
- the same with `*src++` / `*dst++` inside an `i += 2` loop: 179 words, 904 B.
- `dst = (u16 *)0; *dst++ = ...` (the target uses a null-based destination
  cursor with negative offsets, `sh $t3,-0x8($t0)`) reaches 142 words at 756 B
  -- the closest of the rewritten forms -- but a fourth live pointer costs a
  register, so the two `div` guard sequences and the prologue shift.
- `u32` pixel/level or a named divisor: 162 / 164 (the unsigned form changes the
  `div` to `divu` and drops a register).
- `(u16 *)(i & 0xFFFF)`: 164.

### func_8001DE5C (additional)

- Moving the `struct b` declaration to the end or the middle of the scalars does
  not move the frame (154).
- Adding an unused `s32` widens the frame to 0x68 and fixes the `arg2` home, but
  the derived-edge spill block still lands 8 bytes low, and an unused local is
  not honest C.

### func_801B1A7C (additional)

Confirmed with a standalone probe: `for (i = 0; i <= count; i++)` with *one*
scaled store unrolls 4x (`andi t6,a1,0x3`); adding any second
store/float/double op drops it to 2x (`andi t6,v1,0x1`). `-O3`, IDO 7.1,
`-mips1`, `while (n--)`, pointer walks and `i != count+1` do not restore it.

### func_801C317C (additional)

`extern s32 D_80285574` plus `(u8 **)*(u8 **)&D_80285574` is the only shape that
compiles in `ovl_7DF8_13FF0.c` (the TU sets it from `D_8028326C[selected]` in
`func_801C224C`); `D_802C9F70` is the TU's `FrontendRenderContext`. 233 words at
896/936 bytes.

## Round 2 (T-169 continued)

Draft 154 -> **148** for `func_8001DE5C` (`tools/scratch/nonmatching/T-169/func_8001DE5C.c`).
The lever is the rect reads and the last argument of the second writer call: the
draft keeps the second rectangle in a `struct b` and passes `ry - spanY`, which
makes IDO build a fourth stack spill. Reading the far rectangle into flat locals
and writing the final `(ry - ry)` edge (the original's `y2` is already the
clamped `ry` at that point) drops three instructions and the 0x70 frame to a
0x68 one. Frame and `arg2` home now match; the residual 8 bytes are one derived
edge the target spills twice.

### func_8001D47C: 134 confirmed as the floor for this compiler

- A 900-mutation hill-climb on the *official* metric (statement order,
  declaration order, `&&` operand order) never beat 134.
- The grayscale loop shape was fully re-derived: `i != 16; i++` with `src[i]` /
  `dst[i]` reproduces the target's `addiu v0,v0,8` + `sh -8(v0)` + `lhu -6(a0)`
  and its 4x unroll exactly, and takes the register-masked diff from 73 to
  **36** of 187 -- but the official count goes *up* to 171, because the score
  counts register names and the target keeps source in `a0`/dest in `t0`, which
  no C spelling of this body reproduces.
- Pointer-bounded `while (dst != dst_end)` loops keep the 4 stores but cost a
  fourth live pointer: 197-231.

### func_801B1A7C: the unroll cutoff is a hard compiler rule

Measured directly, same TU flags (`-O2 -mips2`), same loop:
- zero or one *scaled* (integer-multiply) store in the body: 4x (`andi ...,3`);
- two scaled stores: 2x (`andi ...,1`), regardless of whether they are the same
  expression, different fields, packed into one u32 store, or preceded by a
  `div.s`;
- three *unscaled* int stores: still 4x. So it is the multiply sites, not the
  store count or body length.

The target has two `multu` per iteration and is 4x, so its body must have had
fewer multiply sites than the C equivalent of the asm -- which means the asm's
second `multu` comes from a source the draft cannot express without a second
multiply. Every C form of "scale x and y by the same s16" is two `multu`.
`-O3` for this TU aborts asm-processor ("Wrongly computed size for section
.text"); IDO 7.1, `-mips1`, `while (n--)`, and hand-written 4x prologues do not
help.

### func_801C317C

Rewritten from the asm rather than mutated: 226-233 words. The target's frame is
0x70 with s0-s7+fp+ra and f20/f22/f24; the closest draft is 0x80 with s0-s7+fp+ra
and f20 only, so two float values the target keeps live across both
`func_801BD640` calls (the y coordinate and the alpha byte) are not live in any
honest C form that still compiles: the target reloads `D_802D3834` before each
call, so the alpha is a freshly loaded global each time, not a kept local.

## Round 3: `do { ... } while (0)` block boundaries

Wrapping a real statement in a single-iteration `do { } while (0);` changes IDO's
basic-block numbering and therefore the schedule, at zero code cost. Scanner:
`wrap2.py FN DRAFT [--combos N]` (wraps each non-declaration simple statement at
any nesting, one at a time, then random combinations); hill-climber over the wrap
set: `wrapclimb.py`.

| Function | Before round 3 | After | Lever |
|---|---:|---:|---|
| func_8001DE5C | 148 | **136** | `do { rx = x2; } while (0);` between the edge sums and `ry = y2;` |
| func_801C317C | 219 | **215** | wraps on the two `D_802D3834`/`slots` statements before the loop |

`func_8001D47C` (126) and `func_801B1A7C` (206) are unaffected: for D47C every
single wrap and 60 random combinations stay at 126; for 1B1A7C all 8 single
wraps and 800 combinations stay at 206.

### func_801B1A7C: `do` statements are not unrolled at all

A `do { ... } while (i <= count)` vertex loop compiles to 288 bytes with no
`andi` preheader -- IDO does not unroll `do` loops on this target. Wrapping the
loop *body* in `do { } while (0);` or rewriting the guard as
`if (z < 6) continue;` both keep 2x. So the 4x-vs-2x cutoff is driven by the
multiply count alone, not by loop shape.

### func_801C317C: the decide block is three separate ifs

The target's fade/entry selection is not one nested `if`: `.L801C3348` is a
`fade -= 0x10` arm reached from two places, and the `fade < -0xFF` step is a
separate `if` after it, with `index += 1` writing back through `D_80285578`.
Rewriting it that way (separate `if (fade < 0x100) { if (fade >= 0) {...} else
{...} } else {...}`, then `if (fade < -0xFF) {...}`) compiles at 229 / 912 B and
its best wrap combination is 222 -- so the original nesting is not the missing
40 bytes either; the remainder is register allocation across the two
`func_801BD640` calls.
