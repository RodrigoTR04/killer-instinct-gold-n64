# T-172

Official counts are `screen.measure` positional words on the owning translation unit.

| Function | Before | After | Bytes | Under 80 | Best draft |
|---|---:|---:|---|---|---|
| func_801C3AA0 | 108 | **55** | 928 / 928 | yes | `func_801C3AA0.c` |
| func_800191F0 | 109 | **69** | 492 / 492 | yes | `func_800191F0.c` |
| func_801ACB1C | 176 | **136** | 744 / 744 | no | `func_801ACB1C.c` |
| func_8002E150 | 179 | **94** | 844 / 844 | no | `func_8002E150.c` |
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

## func_801ACB1C: 176 -> 136, 744/744 (commits `edd755f`, `082b7cc`, `fde905d`, `de5abb47`)

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

## func_8002E150: 179 -> 94, 844/844 (commits `d5d8af2`, `fde905d`, `4f1c8b97`, `15765276`, `da690c16`, `055fc7bd`, `13b29d68`)

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

Remaining 94 words: the target homes the argument at sp+0x60 and the two saved temporaries
at sp+0x1C (`hi`) and sp+0x30 (`z`); the draft homes them at sp+0x60, sp+0x5C and sp+0x18.
Frame size now matches exactly and the instruction count matches exactly (212/212), so
this is purely IDO's temp-slot assignment. Exhaustive searches that did not move it:

- all 40,320 permutations of the eight double declarations, scored by exact sp-slot
  signature against the original (no hit; the slot set `hi`=0x1C, `z`=0x30 needs an
  integer temp *below* the frame top that this declaration set cannot produce);
- all 120 permutations of the five `sqrt`-branch statements × 4 abs shapes × with/without
  the `p` wrap (480 variants; floor 95, and 94 after lever 7);
- `do { } while (0)` around each of the 39 statements individually (best 94);
- three levels of polynomial inlining (locals / inline / fully inlined) — 118 down to 249,
  never better;
- a `union { double d; struct { u32 lo, hi; } w; }` bit view instead of `*(s32 *)&x`
  — 194 at a 0x30 frame;
- `s32` vs `u32` for `hi` / `exponent` (+3 words), `exponent` computed inline at each test
  (95), int locals declared before the doubles (95), one declaration per line (103);
- K&R and `register` parameter forms, a `float` parameter (type error), and removing the
  `a` local entirely (141 / 171 / 175);
- `0.5 * (...)` vs `(...) * 0.5` vs `/ 2.0` (all 95 at the time);
- the decomp-permuter (~15k iterations, `--stack-diffs`) never beat score 1731.

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

- recomputing `T172_LE216(p + 4)` inside the second loop instead of reading `p[4..7]`
  directly into `p` (227);
- the second cache loop restructured to `if (entry->first) continue; if (entry->second)
  continue;` and to nested `if (!entry->first) { if (!entry->second) { ... } }` (226,
  same — the branch shape is right, the words are in the register homes);
- a `u8 *palette` local fed from `rom->palette` (226 at 1,036 B — gets the size *under*
  the target but leaves the palette load in the wrong place);
- `palette` read from `D_80045E50[bank].palette` instead, `palette` grouped with the other
  `u8 *` locals, and `palette` declared first in that group (all 226 / 1,036);
- `rom` assigned only in the `else` arm and reused for the palette read (251 at 1,036),
  and `rom` declared last / after `entry` / first among the pointers (all 251).

