# T-170 (second pass)

Official counts are full-TU positional words from `tools/permuter/screen.py`.
Slot signatures come from `tools/scratch/nonmatching/T-170/sig.py`, which prints
every sp offset each side touches, per mnemonic.

| Function | Before this pass | After | Bytes | Instr | Frame |
|---|---:|---:|---|---|---|
| func_801B01EC | 119 | **115** | 820/820 | 205/205 | 0xb0 = target |
| func_801B0CDC | 155 | 155 | 1332/1332 | 333/333 | 0xc0 vs 0xd8 |
| func_801C23C0 | 181 | 181 | 1812/1820 | 453/455 | 0x98 vs 0x70 |

None of the three is under 80. Below is what each new lever actually did, and
what the frame evidence now proves about the original source.

---

## func_801B01EC — 119 -> 115 (820/820 B, 205/205 instr)

**Lever that worked: a single-iteration `do { real_stmt; } while (0);`.**

`wrap3.py` scanned all 48 statement spans in the body. Three of them scored 115
against the 119 baseline, all for the same reason — each one sits at the boundary
where IDO's scheduler was emitting the display-list stores one slot early:

- `g->w0 = 0x03820010;`
- `g->w0 = 0xFA000000;`
- `return result;`

The kept draft wraps the `0x03820010` store, which is real code from the
function. A **pair** scan (`wrap2x.py`) over the 15 spans in the tail window
returned 115 for every pair, i.e. one wrap is the whole win and a second adds
nothing. Committed as `db95a3d4`.

**The frame is already correct (0xb0).** What is wrong is where the colour
lives, and the slot signature pins it exactly:

```
target locals: 0x48 0x60 0x64 0x68
draft  locals: 0x50 0x64 0x68          (plus an extra 0x3c/0x30)
missing:       0x48, 0x60
```

The target stores the colour to `sp+0x64` **before** the first branch
(`sw t7,0x64(sp)` at 0x0220, `t7 = 0xFF`) and reloads it once at the tail
(`lw v0,0x64(sp)`), and it stores `elapsed` to `sp+0x48` then reloads it three
times. It saves **only `s0`** (which holds `arg0`). The draft saves `s1` as well
and keeps both values in registers, which is why an extra 8 bytes of saved
registers push `sdc1 f20` from 0x30 to 0x38 and shift all later slots.

Everything I tried to force those two spill slots, all rejected (score, size):

| Attempt | Result |
|---|---|
| `volatile s32 alpha` | 195 / 840 |
| `s32 alpha[1]` (real memory object) | 185 / 828 |
| address taken through a used `s32 *pa` | 184 / 828 |
| `u8 alpha`, `char alpha`, `register s32` | 177–209 / 820–840 |
| `(alpha & 0xFF)` inline in the colour word | 184 / 824 |
| separate short-lived `u8 shade` | 177 / 820 |
| `s32 tick` local instead of `arg3 = 0x10E - arg3` | 129–130 / 820 |
| `tick` + the `do{}while(0)` win | 125 / 820 |
| `D_802C8750` as `s32[1]`, `u32`, `volatile` | 115–184 |
| `D_801D2EB0` as `f32[1]` | 115 (no change) |
| `f64 angle`/`rise`, extra `f64`/`f32` scratch | 128–181 |
| 5040-order declaration sweep, then a slot-signature hill climb | 119 floor, 1 round, no move |

The colour's address is **never** taken in the target (`addiu .*sp` appears once,
for the 0x70 matrix), so the "pass `&alpha` to a call" hypothesis is ruled out by
the assembly. The target's colour is in memory because the original source
reassigned a parameter or ran out of registers there — a tie-break in IDO's
allocator that no honest declaration form I tried reproduces at 820 bytes.

Permuters: three runs (`--stack-diffs`), best weighted 4,285; extracted best
scores 185 official at 828 B, worse than 115.

## func_801B0CDC — 155 unchanged (1332/1332 B, 333/333 instr)

**The exact layout of the gap is now proven, and it is dead stack.** The target's
frame is 0xD8; the lookat matrix is `addiu a0,sp,0x98` and is the only
`addiu ...,sp` in the function (2 instructions: prologue and epilogue). Locals
stop at 0x5C:

```
0x48 0x4c   sw/lw        (temp pair)
0x58 0x5c   swc1/lwc1    (sin/cos spill)
0x60 .. 0x94             NOTHING
0x94        sw,sw,lw,sw,lw   (sp94, the return value)
0x98 .. 0xD8             the 0x40 matrix
```

0x60 through 0x94 — 0x34 bytes — are never touched. The target simply reserved
0x18 more stack than its locals need (0xD8 is the aligned size for `0x98 + 0x40`,
so the *matrix* placement is consistent; the dead region is above the temps).

**The lead's "declare a partly-used block" idea was tested and is the right
shape.** Adding a `f32 vel[5]` gives frame **0xD8 with the matrix at 0x98 — an
exact match** (score 141, 1332/1332, slot diff down to 2):

```
0cdc_frame_reference.c:  frame 0xd8  buf 0x98  w=141  1332/1332
                         extra 0x6c, 0x88   missing 0x58, 0x5c
```

I did **not** keep it: `vel[]` is declared and never read, which is a dummy local
under the rules. `vel[3]` (frame 0xD0) and `vel[6]` (0xD8, matrix at 0x98) behave
the same way. So the 0x18 is reproducible only by declaring storage the function
does not use — exactly the conclusion T-165 reached, now confirmed from the slot
signature rather than by inspection.

Honest variants tried: `eye` as `struct{f32 x,y,z;}`, as `f32[3]`, as three named
floats; `eye` plus a `f32 vel[3]`; a whole `struct{f32 x,y,z; f32 pad[13];}`.
Frames 0xC0–0xF8, never 0xD8 without an unread array.

`wrap3.py` over all 102 spans: 57 variants stayed at 155, none improved (best
non-155 was 158).

## func_801C23C0 — 181 unchanged (1812/1820 B, 453/455 instr)

**Big structural finding: the target's frame is 0x70 and I can now reach it
honestly.** The target packs `position` at 0x64 and `velocity` at 0x58
head-to-tail with only three float temps at 0x4c/0x50/0x54, and it uses **five**
distinct double constants (`D_80293778`, `D_80293780`, `D_80293788`,
`D_80293790`, `D_80293798`) with **no `sdc1` at all**.

The old draft and my first rebuild both spilled an `f64` to the stack (an
`sdc1` at 0x20), which is what pushed the frame to 0x98 / 0x80. The cause is
`(f64)(var_f0 - 120.0f)` written inline: IDO keeps the converted double live
across the branch and spills it. The target instead computes `sub.s` into a
**float** once and converts to double at each multiply. Writing it that way
(`fade = angle - 120.0f;` then `(f64) fade * D_80293778 * 3.0`) removes the
`sdc1`, and the frame becomes **exactly 0x70 with position at 0x64 and velocity
at 0x58**:

```
func_801C23C0_frame.c:  frame 0x70  pos 0x64  vel 0x58   (target: same)
                        score 422, 1832/1820, 458 instr
                        extra 0x47, 0x48   missing 0x30, 0x4b
```

That draft is not the answer yet — 422 is far worse than 181 — because the
target's *body* keeps 19 cached temporaries (`sp4C`, `sp54`, `sp50`, `var_f1`,
`temp_f12`, `temp_f16`, ...), and writing the body that way is what keeps the
score at 181 even though the frame is wrong. The two facts are coupled through
IDO's allocator in opposite directions: the 181 body wants 19 locals and a 0x98
frame; the 0x70 frame wants 7 locals and a body that reads very differently.

Evidence collected:

- The 181 draft's `position` is **already** at 0x64 (correct!); only `velocity`
  is at 0x84. Moving `velocity` adjacent to `position` in the declaration list
  gives 0x70/0x58 for the *pairs* but the frame stays 0x98 (152).
- Slot-signature hill climb on both draft shapes: 1 round, no move.
- 5040-order permutation sweeps on both shapes: too slow to finish (>2457 of
  5040 after 13 min each), aborted; the partial results contained no layout hit.
- decomp-permuter on the 181 draft and on the frame-correct draft: best weighted
  1,816 and 5,976; the 1,816 one is 181 official (no gain).
- `decl23.py` (drop declarations, re-measure): **none of the 19 locals is unused**
  — every one is referenced, so the frame cannot be shrunk by deleting anything.

---

## Verdict on the three

Every function now has its target layout *measured*, not guessed:

- `func_801B01EC` — frame already correct; the colour needs to sit in memory at
  sp+0x64 while saving only `s0`. Not reachable at 820 B from any honest form I
  found; the target's allocator chose memory where mine chooses `s1`.
- `func_801B0CDC` — the 0x18 is dead stack. Reproducible only with storage the
  function never reads.
- `func_801C23C0` — 0x70 frame with position 0x64 / velocity 0x58 **is**
  reachable honestly (the float-then-convert trick). It scores 422 against the
  181 draft because the target body caches 19 temporaries that force the frame
  up again. Both halves cannot be had at once with this compiler.

Files kept as references (not replacements): `func_801C23C0_frame.c`
(measured 0x70/0x64/0x58, 422), `0cdc_frame_reference.c` (measured 0xD8/0x98,
141, needs an unread array), `ec115.c` (the committed 115-word 01EC).
