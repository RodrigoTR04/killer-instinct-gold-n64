# T-172

Official counts are `screen.measure` positional words on the owning translation unit.

| Function | Before | After | Bytes | Under 80 | Best draft |
|---|---:|---:|---|---|---|
| func_801C3AA0 | 108 | **55** | 928 / 928 | yes | `func_801C3AA0.c` |
| func_800191F0 | 109 | **69** | 492 / 492 | yes | `func_800191F0.c` |
| func_801ACB1C | 176 | **129** | 744 / 744 | no | `func_801ACB1C.c` |
| func_8002E150 | 179 | **93** | 844 / 844 | no | `func_8002E150.c` |
| func_800216D4 | 229 | **226** | 1040 / 1032 | no | `func_800216D4.c` |

Two of the five are under 80 (`func_801C3AA0` 55, `func_800191F0` 69). The other three
are honestly stuck; each has a fully diagnosed residual below.

## func_801C3AA0: 108 -> 55, 928/928 (commit `a73c21e`, from T-168/T-172 run 1)

Lever: drop the `slot = index * 3` local and write `D_802D3940[index * 3 + n]` at every
vertex access. T-168's local made IDO hoist `multu` ahead of the `lw %lo(D_802D3940)`
vertex-base load and reuse it across all ten stores; with the index expression repeated,
the base reload appears exactly where the original has it, which collapses the whole
inner block. Then assigning `cosine` before `sine` (so `cosf` is the first call) is worth
one more word.

Remaining: the two saved-float `sdc1` slots (`f22`/`f24` at sp+32/sp+40) are still
swapped, and the final `sb ...g` sits one slot early. Declaration order over 46
permutations of the floats and ints does not move either.

## func_800191F0: 109 -> 69, 492/492 (commit `ee845c0`, from T-165/T-166/T-172 run 1)

Lever: the function walks `D_801D3430` four objects at a time in the original, and each
block begins `lh vx; sh vx, vx; lh vx` — a store of the halfword back to its own slot
followed by a reload. Honest C that reproduces it is a named `s16` local round-trip
inside a block scope:

```c
{ s16 v = (*p).vx; (*p).vx = v; }
D_8004A920[0] -= (f32)(*p).vx / unit;
(*p).vx = (s16)((f32)(*p).vx + D_8004A920[0] * unit / 200.0f);
```

With `for (i = 0; i < 40; i += 4) { p = &D_801D3430[i]; ... }` and four such blocks
(`(*p)`, `p[1]`, `p[2]`, `p[3]`) the body lands at exactly 492 bytes. T-166's
"`obj->vx = obj->vx`" was the same idea but written without the local, and IDO folded it
away; the named local is what keeps the store. `unit` has to be a real `256.0f`
initialiser as well.

Dead ends: a `do { } while (p != D_801D5C30)` pointer walk (75), four pointer locals each
advanced (110-127), `obj++` between blocks (122), array indexing by `i` inside the loop
(109-115), and every `D_801D5C30` end-pointer form.

## func_801ACB1C: 176 -> 129, 744/744 (commits `edd755f`, `082b7cc`, `fde905d`, `de5abb47`, `80acfe0f`, `3f0255a7`)

Reconciliation first: the draft's `T034GameState` / `T034Gfx` became the TU's
`RenderState` / `DisplayCommand`, `D_802C9F70.unk0` is `RenderState.index`, and the
`func_801AD7D8` prototype takes `s32 *` for its last argument. `DisplayCommand` was moved
above `RenderState` in `src/ovl_7DF8/ovl_7DF8.c`; a clean
`make clean && make extract && make` still reproduces baserom
`ba52e91b44450c548467044b26951353dc491e04`.

Levers from the earlier run: split `gfxStart = gfx = ...` into two assignments with the
`RenderState` ints declared before the two pointers (176 -> 173); write the outer dispatch
as `if (*D_801CD458 != 1) { if (*D_801CD458 == 2) { D_8004A414--; } } else { ... }`
(173 -> 166); `do { ... } while (0)` around the two `D_802C9F70.unk4` counter statements
(166 -> 165).

**New lever (T-172): take the address of `D_8004A414` into a `s32 *` local** and use
`(*a414)--` / `(*a414) < 2`. 165 -> **136 at the exact 744 bytes.** This is what makes
the `lui/addiu` pair for `D_8004A414` land in the same place the original has it, instead
of being re-materialised in each arm.

Remaining: the extra pointer costs one stack slot, so the frame is 0x68 against 0x60, and
every `lw`/`sw` of `gfxStart`/`gfx`/`sp48`/`sp44` is offset by 8. I swept
(a) all 720 declaration orders of the eight locals and scored each by official words —
best 135, none reached 0x60 with the target's 0x44/0x48/0x58/0x5C slot set;
(b) the same sweep filtered only on frame size + the target slot set — no order produced
0x60 with the pointer present;
(c) `h`, `diff` and `i` moved into C89 block scopes, and the `for` bodies' locals
declared inside their own blocks — frame stays 0x68;
(d) a `do { } while (0)` / `for(;;){break;}` wrap of every statement in the function.
No wrap moved the count.

Dead ends to record: pointer locals for `D_801CD45C` (172), for both `D_801CD45C` and
`D_8004A414` (171), an initialised `s32 *a414 = &D_8004A414;` at the top (135) or just
before the branch (135), declaring `a414` last (135), `u32 *a414` (137), `switch` on the
message (173), `else if` instead of the nested form (173), a local copy of the message
(169), guard-clause early return (does not compile against the TU's prototype),
`&D_8004A414` written inline as `(*&D_8004A414)` (165), and moving `D_8004A414`'s
increment into the `== 2` arm only (129 at 748 B).

**New levers (T-172 run 2), 136 -> 129:**

1. Compute `gfx` *before* the `D_80044A24` index store
   (`gfx = index ? D_80076240 : D_8006F1C0; D_80044A24 = D_802C9F70.index;`) — 136 -> 130.
   The permuter surfaced the same swap but surrounded by `int new_var` dummies; taken
   alone it is honest source and worth 6 words.
2. Declaration order `i, gfxStart, diff, gfx, sp48, sp44, a414, h` as separate
   declaration statements — 130 -> 129. Found by sweeping 768 combinations of ordering
   × which locals are block-scoped into the branch (the permuter's other two 129 hits
   were exactly this: `sp48` moved into the branch, or `sp44` moved last).

Remaining: the `a414` pointer costs one stack slot, so the frame is 0x68 against 0x60
and every `lw`/`sw` of `gfxStart`/`gfx`/the two outs is offset by 8. The target instead
materialises `&D_8004A414` into a register *separately in each arm* and does
`lw 0(reg); addiu -1; sw 0(reg)` — the address is live across the load/store, which a
plain `D_8004A414--` does not reproduce (IDO fuses the load into `%lo(reg)`).

Dead ends (all measured):

- `extern s32 D_8004A414[1]` with `D_8004A414[0]--`: the TU's own
  `extern s32 D_8004A414;` in the same file makes every form of the array/struct view
  a conflicting declaration, including a block-scoped `extern` inside the function.
  The array type cannot be introduced without editing the shared TU declaration, which
  would also change the already-matched `func_801ADB20` / `func_801ADBB0`.
- `register s32 *a414` (136, unchanged — cannot be spilled but IDO still allocates it).
- pointer scoped inside each arm (169); `s32 *a414 = &D_8004A414;` at the top (135) or
  just before the branch (135); `u32 *a414` (137); `(*&D_8004A414)` inline (165).
- all 720 declaration orders of the eight locals (best 135) and all 120 filtered on the
  exact target slot signature (no hit).
- the two callback outs as an `s32 outs[2]` array (165), and block-scoping them:
  a nested block around the `arg0` call + `func_801AD7D8` puts the outs at exactly
  0x44/0x48 as the target has them, but the block's slots are then allocated *first*,
  pushing `gfx` to 0x60/0x68 (161 words at a 0x68 frame); combined with gfx-first
  declarations it reaches 156 at a 0x60 frame but is still worse than 129.
- `switch` on the message (173), `else if` (173), a local message copy (169),
  guard-clause early return (does not compile), `D_8004A414 = D_8004A414 - 1` / `-= 1`
  / `+ -1` read-modify-writes (all 165, same as `--`).

## func_8002E150: 179 -> 93, 844/844 (commits `d5d8af2`, `fde905d`, `4f1c8b97`, `15765276`, `da690c16`, `055fc7bd`, `13b29d68`, `24a9f139`)

This is the `asin` implementation. Levers, in order:

1. Name the two polynomial temps of the `sqrt` branch as locals
   (`u = D_80048F38[1] + (D_80048F38[3]*z + D_80048F38[2])*z;`,
   `w = D_80048F58[0] + ((z + D_80048F58[2])*z + D_80048F58[1])*z;`,
   `r = z*u*t/w + t;`) — 179 -> 170.
2. `t = 2.0 * (x * x) - D_80048F78;` then `do { z = t * t; } while (0);` — 170 -> 118
   at the exact 844 bytes. The wrap only renumbers the basic block so the scheduler
   matches the original's `mul.d`/`add.d` interleave.
3. **Frame size is set by the order of the uninitialised double declarations.** Writing
   `double z, p, q, a, t, r, u, w;` gives `addiu sp,sp,-0x28`; the reversed
   `double w, u, r, t, a, q, p, z;` gives exactly `-0x60`, the target's frame — with the
   code otherwise identical. 118 -> 112. (Any *extra* declared double also grows the
   frame, but by the wrong amount: `s` -> 0x68, `s,k` -> 0x70, `s,k,n2` -> 0x78.)
4. Write the absolute value as `a = -x; if (x >= 0.0) a = x;` — 112 -> 100. IDO's
   `c.le.d`/`neg.d`/`mov.d` sequence for this shape matches the original's
   `c.lt.d`/`bc1f`/`b`/`neg.d` skeleton far better than `if (a < 0.0) a = -a;`.
5. Compute `w` before `u` in the `sqrt` branch — 100 -> 99.
6. `do { p = ...; } while (0);` around the `p` polynomial in the small-|x| branch —
   99 -> 95. (The permuter's best hit was an empty `if (0) { }` at exactly this boundary;
   the honest form puts the real assignment inside.)
7. `a = x; if (a < 0.0) a = -x;` (compare `a`, negate `x`) — 95 -> 94.
8. One declaration statement per local, with `hi`/`exponent` last — 94 -> 93.
   This also moved the `hi` spill from sp+0x5C to sp+0x1C, which is exactly where the
   target keeps it.

Remaining 93 words: the slot signature is now one diff away. `slotsig.py` reports

    TARGET  frame 0x60: 0x14=3 0x1c=2 0x30=2 0x60=9
    DRAFT   frame 0x60: 0x14=3 0x1c=2 0x20=2 0x60=8

so every `hi`/`ra` slot matches, the frame matches, the instruction count matches
(212/212), and the only differences are (a) the spill of `z` landing at sp+0x20 instead
of sp+0x30, and (b) the target re-reading the *argument home* (sp+0x60) once more than
the draft does — 9 uses vs 8 — which is the `b ...; neg.d` absolute-value skeleton.

Searches that did not move it (all measured, all honest):

- all 40,320 permutations of the eight double declarations as separate statements;
- **interleaving the `s32 hi;` / `s32 exponent;` statements between individual
  `double` statements** at every one of the 72 ordered position pairs (this is the only
  thing that changes slot *assignment* order, and the best result is 93 with `hi` at
  0x1C — already what we have);
- declaration grouping (all one line / pairs / triples / singles) — no effect at all,
  which is why the 40,320-order sweep is equivalent to 5,040;
- a slot-signature-filtered sweep of the 720 abs-shape × `sqrt`-branch-order combinations
  (`abs3_150.py`) — no signature match;
- block-scoping `p`,`q`: this is the most interesting near miss. It puts `z` at exactly
  the target's *relative* distance below the argument home, but the frame collapses to
  0x50 and the count rises to 116. Reordering the remaining six function-scope doubles
  (720 variants) keeps the frame at 0x50 with `z` at 0x30 — right relative offset, frame
  0x10 too small — and no honest shape that adds a live value at 0x20/0x28 was found.
- block-scoped *copies* of the polynomial temporaries (`double p2, q2;` inside the
  branch): 187 words at a 0x68 frame;
- expression splits of the `u`, `w` and `r` chains into sequential statements on the same
  locals (99-101), and naming the ratio (`r = z*u*t; r = r/w; r = r+t;`) — slot values
  do not move at all;
- `float` intermediates (`f32 ft = sqrtf(...); t = ft;`) — 94;
- pairwise `do { } while (0)` wraps of all 407 statement pairs — nothing beat 93;
- **source line layout**: joining each branch body (and all three) onto one line, which
  is what the permuter kept "winning" with, changes the emitted code by exactly zero
  words here — IDO 5.3 is insensitive to it in this function, so those permuter score
  improvements are noise, not progress;
- declaring `z` only after the `sqrtf` call so it is not live across it (148 at 872 B).

## func_800216D4: 229 -> 226, 1040/1032 (commits `b8b2199`, `738e3c3`, `cca4cbe6`)

Reconciliation: `D_8004D278` in `main_D3F0.c` is
`struct { u8 pad[0x12A8]; T032Bank banks[2]; }`, so `D_8004D278[i][player]` is
`((T172Cache (*)[3])&D_8004D278)[i][player]`. With that the full TU compiles at
229 / 1040 (8 bytes long).

Levers: `do { } while (0)` around the two cache-zero stores (229 -> 227) and around
`id = p[0] + (p[1] << 8);` in the header walk (227 -> 226).

Remaining: the eight-byte size excess and the register homes. The target keeps the masked
`kind` in `s1` and `player` in `s4` with byte homes at sp+0x8F and sp+0x8B, and stores the
`rom` pointer at sp+0x54 where the draft uses sp+0x80. Dead ends: explicit `u8` locals for
`player` (257 at 1,052 B), `(u8)` casts on both arguments (257), masking `wanted` after
the bank dispatch instead of before (260), `(u16)wanted` instead of `wanted &= 65535`
(226, same), and `for(;;){break;}` at the cache-loop boundary (reverted; it cost a word).

Later T-172 attempts on this function (all measured, none better than 226 / 1,040):

- **the two extra instructions are now identified**: the draft stores `loaded = 0`
  (`sw zero,96(sp)` + `or fp,zero,zero`) and the target has no such store at all —
  its `size`/`loaded` slots (sp+0x5C, sp+0x60) are only written on the found path.
  Dropping the initialiser gives 253 words at 1,036 bytes, i.e. it loses the two
  instructions but the whole `loaded` register plan moves, so it is not a win;
- merging `loaded` into `size` (`size += offset; size += size & 7; ... return size - offset;`)
  — 244 at 1,008 B, frame 0x80;
- returning from inside the loop with `break` at the found site — 264 at 1,056 B;
- a separate `done` variable copied from `loaded` in the found branch — 240 at 1,040 B;
- `u8 *palette` fed from `rom->palette` — 226 at 1,036 B (this is the one-instruction
  reduction the lead's hint predicted, but it does not move the word count);
  combined with dropping the `loaded` initialiser — 239 at exactly 1,032 B;
- `palette` declared first / last / grouped with the other `u8 *` locals — all 226/1,036;
- separate declaration statements for every local (the lever that helped `func_8002E150`)
  — 226, unchanged; `bank` moved to the top of the list — 227;
- recomputing `T172_LE216(p + 4)` inside the second loop instead of caching `size` (227);
- the second cache loop restructured to `continue` guards and to nested
  `if (!entry->first) { if (!entry->second) { ... } }` (226, same);
- `rom` as a single pointer assigned in the `else` arm and reused for the palette read
  (251 at 1,036), in every declaration position (251);
- the decomp-permuter (`--stack-diffs`, two runs) never produced a form that beats 226.

