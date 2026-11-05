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

## Round 4 (T-169 continued): func_8001D47C matched, DE5C 134, C317C 211-honest

### func_8001D47C: 134 -> 0 (MATCHED, in src/main/main_D3F0.c)

The missing piece was the **null-based destination cursor**, written honestly:

```c
u16 *dst = (u16 *) 0;
```

All three loops store through `dst[i]`. The target's zero-fill and copy loops
use `sh $t3,-0x8($t0)` where `$t0` is the loop counter starting at 0, i.e. a
destination pointer whose value is literally 0. Spelling that as a real local
makes IDO allocate `dst` to `t0`/`a1` exactly as the target does, and the whole
register-masked diff collapses.

Two other levers came with it:

- **No cached pixel local.** Writing `p = var_v0[i];` and reusing `p` forces a
  separate live value and costs a register. Repeating `var_v0[i]` in the
  expression (three times) lets IDO schedule the `lh` like the original.
- **Grey term order R, B, G.** `((v & 0xF800) >> 11) + ((v & 0x7C0) >> 6) +
  ((v & 0x3E) >> 1)` emits the `andi`/`sra` pairs in the target's order;
  G,R,B and every other permutation scored 44-49.

Progression: 134 (T-022/T-168 floor) -> 125 (source/dest cursor locals) ->
34 (no cached pixel local, R,B,G order) -> **0** (null `dst` cursor).
T-169 official counts along the way: 125, 49, 34, 15 (permuter, fake
zero-vars), **0**. ROM sha1 `ba52e91b...491e04` verified after `make clean &&
make extract && make`.

### func_8001DE5C: 154 -> 134

Best is 134 at 592 B (target 600, frame 0x78 vs 0x68). The two useful levers:

- **Read the far rectangle into flat locals** (not a `struct b`): 154 -> 148.
- **`(u16) bx` on the min-x subtraction**: `dx = mx - (u16) bx;` -> 134. The
  target computes `subu` on the *unsigned* 16-bit pair, so the cast is real
  code, not a hint. Written without the cast the same function is 136.

A separate rewrite from the asm reaches the **exact 600 bytes** (141 words):
treat `bx2`/`by2` as the running edges (`bx2 += dx; by2 += dyb;`) and pass
`(ry - by2)` as the second writer's height. Frame 0x48, no callee-saved
registers, all 150 instructions present -- but the schedule of the eight
`lbu`/`sll`/`addu` decodes and of the four clamps differs, which is worth 141
words by itself. Saved as `de5c_v14.c`; the 134-word draft's structure is
closer in *count*.

Dead ends this round: struct-typed far rectangle in all 24 field orders
(166 each), `maxX`/`maxY` named edges (141), declaring every derived edge
(141), reusing `ax1`/`ay1`/`bx1` as the max accumulators (147), all wrap
combinations on the 141 version (141), permuter (4288 weighted -> 134
official), removing the permuter's `u16` temp by inlining its assignment
(136).

### func_801B1A7C: 206, blocked by an IDO unroll cutoff

Confirmed the rule much more precisely this round. The target body has, **per
copy**: one `div.s`, two `mul.s`, one `add.s`, one `cvt.d.s`, one `mul.d`, two
`trunc.w.s`, one `trunc.w.d`, two `multu`, and three stores -- in a loop that
IDO unrolled **4x** (`andi $t6,$v0,0x3` preheader).

Measured on the exact body with the exact flags:

| body contains | preheader |
|---|---|
| `div.s` + 2 scaled stores + the `mul.d` z | 2x (`andi ...,1`) |
| `div.s` + 1 scaled store | 4x |
| no `div.s` + 2 scaled stores | 4x |
| `div.s` hoisted out of the loop + 2 scaled stores | 4x |
| `div.s` on a non-constant divisor (`count2`, a global) | 2x |

So it is the **number of float ops inside the loop**, not the integer multiply
count (T-165's conclusion) and not the loop shape. Hoisting `ratio` and `scale`
before the loop is the only way to get 4x, and it changes the function
(`ratio` and `scale` are per-element in the original only through `amount`,
which is loop-invariant, so hoisting is semantically safe but changes the
*bytes*: 216 words at 752 B vs the target's 218 at 872 B -- the target really
does re-divide inside each unrolled copy).

Dead ends this round: named `radius`/`k=256.0f`/`half` locals in all
combinations (2x), `f64 amount` local (2x), `s16`/`u32`/`s32` scale spellings
(2x), `div256` instead of `>> 8` (4x but 194-209 instrs, 10 `multu`),
`do{...}while(0)` around each store (2x), splitting the guard into three
separate `if (z >= 6)` blocks (2x, 192 instrs), `-O1` (1x), `-mips1`
(2x, 209 instrs), IDO 7.1 (2x), every declaration order (2x), permuter
(11368 weighted, no change), wrapclimb (206, no wraps accepted).

### func_801C317C: 215, register allocation across two `func_801BD640` calls

Promoted the permuter's best to 215 / 900 B. One of its outputs scores 211 but
contains an **empty `if ((!D_802937BC) && (!D_802937BC)) { }` block**, which is
not honest source; the two honest parts of that candidate (a named `slots`
recompute and `x = x + f()` instead of `x += f()`) are each neutral at 215.

Remaining diff is the prologue's callee-saved set (target s0-s7+fp+ra and
f20/f22/f24 at frame 0x70; draft s0-s7 at 0x80) and the reload of
`D_802D3834` before each call. Every shape tried this round:

- caching global *addresses* (`s32 *counter = &D_802956F4;` etc.): 220-232
- `u8 ***table` so `**table` is the entry: 233
- entry reloaded through the loop condition (`while ((entry = *slots))`): 232
- `slots = (u8 **) ((u8 *) entry + first * 4)`: 215-216
- named `next` for the advance-then-store: 215-222
- `x = x + f()` vs `x += f()`: 215
- early returns for `entry == 0` / `arg3 <= 0`: 237
- `do{...}while(0)` on either loop call: 224
- wrapclimb over 31 statements, 60 iterations: 215, no wraps accepted
- permuter, two runs (11822 -> 9442 weighted): 211 dishonest, 215 honest

## Round 5: slot/register signatures as the objective

New probes (both in T-169, reusable):

- `slotsig.py FN DRAFT` — frame size + which `sp` slots are touched and how
  often, for target (splat asm) and draft (compiled the same way as screen.py).
- `regset.py FN DRAFT...` — frame size + the exact callee-saved integer and
  float register set. This is what IDO's allocator decides, so it separates
  "wrong source" from "wrong allocation" much better than the word count.

### func_801C317C: 215 -> 211 (commit 09dc5311)

`regset.py` shows the target is frame 0x70, int `{s0-s7,ra}`, float
`{f20,f22,f24}`; the 215 draft already had the right frame and integer set but
only `f20`. The target's three live floats are decodable from the asm:
`f24 = D_802937B8`, `f22 = D_802937BC`, and `f20 = (f32)(arg2 - 0x5DC)` (both
calls pass `$f20` at argument slot +0x14). Hoisting two of them as named f32
locals before the loop (`shade = D_802937B8; depth = (f32)(arg2 - 0x5DC);`)
gives **211**. Hoisting all three gives the target's exact float set
`{f20,f22,f24}` but pushes the frame to 0x80 (220-229), so it is a net loss.

Dead ends: three floats at four declaration positions x two load orders (214
to 229), `s32 matrix = (s32) D_802C9F70.matrices;` (221-224), naming the frame
counter (228).

### func_801B1A7C: 206 -> 198 (commit 4a7c4b49)

IDO **never** produces this loop's 4x unroll. Probed directly with the compiler
(not through asm-processor): IDO 5.3 and 7.1 at `-O1` (no unroll), `-O2`, and
`-O3` all give `andi ...,0x1` (2x) for the real body, and `-Wo,-loopunroll,4`
and `-Wo,-loopunroll,8` change nothing. So the original source was
**hand-unrolled** in the target's layout: a `(n & 3)` prefix loop followed by a
stride-4 loop with four explicit copies. Writing exactly that gives 888 B
(target 872) and **198**, with the target's own slot map (`0x10`, `0x18`,
`0x24`, `0x28`, `0x2c`) and its exact float set `{f20,f22}`.

Sub-levers inside the hand-unroll: `i != n` as the main guard (202 -> 198);
`i < (n & 3)` for the prefix (a `rem` local costs 7).

Remaining: frame 0x30 vs 0x28 — the draft homes `arg0`/`arg1` at 0x28/0x2c
*and* spills `count` to 0x3c, i.e. three homes where the target has two plus
one. Typed pointer parameters instead of `void *` reorder them but do not
shrink the frame; declaration order in all permutations is invariant.

### func_8001DE5C: 134 stands

`slotsig.py` decodes the target exactly: frame 0x68, local slots
`0x20 = dx`, `0x24 = dx0`, `0x30 = ry`, and the far rectangle **in place** at
`0x48 = by, 0x4c = bx, 0x50 = bx2, 0x54 = by2` (the target rewrites those four
locals with the spanned edges, which is why 0x50 and 0x54 have 4 and 6
accesses), plus `arg2` homed at 0x70. `de5c_v14`/`de5c_v15` already reproduce
this frame and the four in-place rect slots.

Dead ends this round: 165-candidate declaration-order/inline sweep filtered on
the exact slot signature (frames 0x64, 0x6c, 0x70, 0x78 - never 0x68 with the
right slot set); block-scoped far rectangle (155); writing the max back into
`x`/`y` instead of `mx`/`my` (148); `>= 0x8000u` clamps (135-144);
`+= 0xFFFF0000` clamps (134, unchanged); declare-then-assign decode (134);
parameter walk to read the byte pairs (does not compile cleanly); a
layout-guided climb (`de5c_climb4.py`) converging at 135.
