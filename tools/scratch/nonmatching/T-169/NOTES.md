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
