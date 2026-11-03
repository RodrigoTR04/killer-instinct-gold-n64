# T-153 working notes

Starting commit: 259b07f. Baseline M2 108,600 B / 289,876 (verified clean toolbox build,
ROM sha1 ba52e91b44450c548467044b26951353dc491e04). Target: >= 2,030 newly T4 bytes.

## Tools added (scratch only)
- `measure.py <fn> <draft> [--full]` - score one draft with screen.py's compiler path.
- `batch.py <fn> <dir>` - score every `*.c` variant in a directory.
- `asm.py <fn> <draft>` - print the compiled assembly of the draft function.
- `cmp.py <fn> <draft>` - canonicalised instruction diff vs the original splat asm
  (relocations folded back to symbol names, immediates normalised) so every remaining
  line difference is real codegen.
- `wordiff.py <fn> <draft>` - the exact set of differing words the scorer counts,
  with the target and draft encodings side by side.

## Starting scores (full owning TU, screen.py masks)
| Function | bytes | words | note |
|---|---:|---:|---|
| func_801B5DCC | 1884 | **11** | 2 real sites: v0/lui order around the record pointer, and the `lw t4,60(sp)` hoist in the tail |
| func_801B5534 | 168 | **2** | sp+0x18 vs sp+0x1C for the scaled-index spill |
| func_801C4E38 | 556 | **2** | sp+0x18 vs sp+0x1C for the selector snapshot |
| func_801BD270 | 396 | 7 | 64-bit controller pack ordering |
| func_801B2B8C | 872 | 8 | two address-register spellings (D_801D308C / D_801D3094 bases) |
| func_801BE540 | 288 | 8 | index/glyph-pointer lifetime |
| func_801B1DE4 | 556 | 13 | hoisted D_801D3098 load + store placement |
| func_801BAA78 | 884 | 14 | argument-register spelling of the x0/x1 sums |
| func_801B5650 | 1916 | 30 | carousel mirror of 5DCC plus an extra tail branch |
| func_801C4240 | 1344 | 64 | display-list block scheduling |
| func_801B0CDC | 1332 | 155 | frame 0xd8 target vs 0xc0: missing 0x18 of locals |
| func_801C23C0 | 1820 | 181 | frame 0x70 target vs 0x90: draft uses 0x20 too much |
| func_801B3DB0 | 1360 | 278 | frame 0x48 vs 0x40 |
| func_801BDA6C | 1320 | 266 | frame 0xd8 vs 0xc8 |
| func_801BCB70 | 1676 | 391 | frame 0x138 vs 0x1b0 |
| func_801BDF94 | 1452 | 352 | frame 0x140 vs 0x130 |
| func_801B9A04 | 1668 | 404 | frame 0x38 vs 0x48 |

`func_801B695C` is already T4 (T-145) - the functions.csv note still points at an old draft.

## Probes tried in this run (all scored, none matched)
- `func_801B5DCC`: 20 line-join combinations of the record/height/z/rotation block and the
  height-store/index block (all 11); 8 declaration orders of `z, angle, rotation, height`
  (11 was the best); `z` before/after `record += index` (321/323 - the target's `lui at,49440`
  before `addu v0` needs the height load first); `z` initialised at its declaration (156);
  `height = (f32)record->right` (11); typed `T029Spin` view of D_802C8C64 (51); folded
  `rotation / 8.0f` (49); `next` assigned inside the branch (14); `(s32)i` block for the
  spin store (15); permuter 1500 s (best 140, only formatting) and declorder 540 s.
  Remaining 11 words are two scheduling sites: IDO puts `addu v0,t5,t6` in the `lui` delay
  slot only when the height load comes first, and the tail `lw t4,60(sp)` must stay before
  `mfc1`.
- `func_801B5534`: shared `value` local (18), pointer slots (39), limit-first (44), unsigned
  sample (33), split declaration (2), index local (11). The 2 words are the spill slot for
  the scaled index (`a2` at sp+0x1C, not sp+0x18); every variant that moves it also changes
  the frame or drops the store.
- `func_801C4E38`: named `s32`/`u8` snapshot of arg0 used for the branch and switch (7),
  switch-only (7). Same conclusion: the selector copy belongs at sp+0x1C.
- `func_801BD270`: `(u64)` shift addends instead of the mask chain (21), single expression
  (34), `s16 buttons` (51), `(u32)` addends (21). Target computes `v1 = (x + high) + buttons`
  before the 64-bit carry and the draft orders the halves the other way.
- `func_801BE540`: while/do-while/for/`&&`-comma shapes (69-71 at 280-332 B). The 288 B
  target keeps `a0 = text` and reloads `*a0` per iteration; every honest shape that does that
  also keeps `f0` in one place and the draft loses the shared width accumulation.
- `func_801B1DE4`: frame read into a local before the increment and `frame - 1` (139),
  flattened early return (139). The 13 words are the target hoisting `lw v0,D_801D3098`
  above the prologue.
- `func_801BAA78`: split y0 computation (16), `arg3` reuse for y1 (136), no yOffsetScaled
  local (141); the base 14 is unchanged. `addu t5,t9,a3` vs `addu t5,a3,t9` is operand order
  in the y0 sum.
- `func_801B2B8C`: `AnimationState` split into two scalars (164). The 8 words are the two
  `lui/addiu` base pairs the target forms with a2/a1 instead of a1/a2.
- `func_801B5650`: `if (state == 5) return 0;` early return instead of the wrapper (95).

## Round 2: structural probes (all scored; none matched)

New tools: `regs.py` (frame + saved-register set vs target), `callset.py` (call
multiset vs target), `stmtorder.py` (permute named statement groups).

Findings that constrain every later attempt:
- **Call sets match exactly** for all 15 functions checked (`callset.py`): no
  draft is missing or duplicating a call, so arity/control flow at call sites is
  not the remaining error.
- **Saved-register sets match** for every function except `func_801BDA6C`,
  `func_801BCB70`, `func_801BDF94` (each one extra `s8`).
- **Frame deltas** (target - draft): `801C4240` 0, `801B5DCC` 0, `801B5650` 0,
  `801B2B8C` 0, `801BD270` 0, `801BE540` 0, `801C4E38` 0, `801B5534` 0
  (these seven are pure scheduling), but `801B0CDC` +0x18, `801B3DB0` +0x8,
  `801BDA6C` +0x10, `801BDF94` +0x10, `801C23C0` -0x20, `801B9A04` -0x10,
  `801BCB70` -0x78.

### func_801C4240 (64 words)
The scene fields at D_802D3950 are *adjacent separate symbols*, confirmed from the
asm: D_802D3954 (u8 perfect), D_802D3956 (u16 sound), D_802D3958 (u8 speed),
D_802D395C (s32 start), D_802D3960 (u8 alpha); D_802937F8 = "VICTORY" and
D_80293800 = "PERFECT" (verified against the segment bytes), and D_8029381C/20/24/28
are the floats 3000.0, -1380.0, 1700.0, -1700.0. Tried: plain-symbol form (90),
struct read + scalar write (64), scalar read + struct write (64), statement split
of the start store and the two snapshots (64 in all four orders), `ResultScene *`
local (144), a full fresh rewrite with real symbols and the target's evaluation
order (`draft_801C4240.c`, 294). Best remains T-149's 64: the target keeps
`D_802D3950` itself for the `start` reads, so a struct view is unavoidable there,
and the rest of the difference is display-list scheduling.

### func_801B0CDC (155 words)
Frame is 0x18 short. The target's block at sp+0x58/0x5C is the sin/cos pair and
the block at 0x2C/0x30 is the two func_801BC1B0 float arguments; the draft puts
them at 0x48/0x4C and 0x6C/0x70. Tried: eye as three scalars (155), sin/cos as named
f32 locals (155), `eye[3]` (226), `eye[3] + up[3]` (248), u32 sp94 (155), u64
buffer (155), argument copy local (155), declaration swap (155). All 155 at the
correct 1332 B: the residual is the frame's 0x18 of float staging.

### func_801B0CDC func_801B5DCC carousel (11 / 30 words)
- `z = -10.0f` placement: before the record advance (321, +4 B), on its own line
  (323), after the rotation load (323), comma-joined with the height load (323),
  indexed height with z first (326). Only "record += index; height = record->right;
  z = -10.0f; rotation = ..." keeps 11.
- declaration orders: all 8 permutations of `z, angle, rotation, height` for the
  three placements tried; only `z, angle, rotation, height` gives 11.
- `stmtorder.py` over both 3-statement groups: 30 orders, best 354.
- permuter 1500 s (best 140 = formatting only), 2700 s (best 140), declorder 540 s
  (1,488 orders, baseline wins).
- Remaining 11 words are two sites: `addu v0,t5,t6` must go in the `lui` delay slot
  (needs the height load first, which is what the draft does — IDO still hoists the
  `lui`), and the tail `lw t4,60(sp)` must precede `mfc1 t3,f6`. Both are pure
  scheduling of live ranges that C cannot steer without a dummy local.
- `func_801B5650`: single-result-with-`else` (95), early return (95) vs the
  wrapper (30). The target's `bne a3,at` + `bnezl` shape needs `state != 5` and the
  draft's `state != 5` wrapper is the closest honest form.

### func_801B3DB0 (278 -> 261)
Replacing the typed two-column pointer walk with direct `D_802C8C30[i][col]` /
`D_802C8C60[i][col]` stores dropped 278 -> **261** and the size 1344 -> 1352
(target 1360). Same loop with the height stores grouped first: 263.
The target's frame is 8 B larger and keeps `arg1 & 0xFF` in `a1` for the whole
function, so the remaining gap is the initial mode-selection block.

### func_801B2B8C (8 words)
The 8 are two `lui/addiu` base pairs the target forms in `a1`/`a3` where the draft
forms them in `a2`/`a3` — the target reloads `D_801D308C` and `D_801D3094` as
addresses inside the display-list block. Tried: `D_801D308C = D_801D308C + 1` (8),
byte/u8 local for the fade guard (20 / 111), `tilt` local for the 3094 compare (20).

### func_801BD270 (7 words)
The 7 are the 64-bit pack order. Tried `(u64)... << 32` addends (21), single
expression (34), `s16 buttons` (51), `(u32)` addends (21). The target computes
`v1 = (x + high16) + buttons` *before* the carry add; every honest spelling makes
IDO order the halves the other way.

### func_801BE540 (8 words)
Loop shapes while/do-while/for/`&&`-comma (66-71 at 276-332 B), `*text` read inside
the loop with `p` advanced separately (66), index from `*text` and condition from
`*p` (66). All lose the shared width accumulation into `f0`.

### func_801B9A04 (404)
The target processes **two vertices per iteration** (`addiu a0,a0,2` and the body
appears twice with a `bne t2,a0` back-edge). Tried: literal bound 118 (410),
`count = 118` with a 0-based loop (410), a hand-written pair with a comma-seeded
`i += 2` and two copies of the body (412, and that shape is an artificial unroll),
a nested `for (j = 0; j < 2; j++)` over `src[j]`/`dst[j]` (414 at 1240 B). The
honest inner-2 loop loses the target's shared register rotation, so the 404 stays.

### func_801BCB70 / func_801BDF94 / func_801BDA6C
Frames are 0x78 / 0x10 short / 0x10 short and each draft keeps one extra `s8`.
`func_801BCB70`: folding the `arg9 - arg7` temp into `sp94` and reusing `(f32)arg13`
kept 391/1676 (target size). These three need a fresh reconstruction; the current
drafts are straight m2c with dozens of `temp_*`/`var_*` locals.

## MATCH: func_801BE540 (288 B)

Landed in `src/ovl_7DF8/ovl_7DF8_116E0.c`; ROM sha1 ba52e91b…, functions.csv T4,
M2 108,600 -> 108,888 (+288 B).

The structural cause: **the loop pointer must be assigned inside the
`if (*text)` block, not at its declaration.** `u8 *p = text;` at the top makes
IDO keep `p` and the accumulator alive across the whole function and the loop
rotates with `bgtzl`/`bnezl` the other way round; `u8 *p; ... if (*text) { p =
text; do {...} while (*p); }` gives the target's exact rotation, 0 differing
words at 288/288.

Second, smaller cause: the multiplier order is `10.0f * glyph->width * scale`
(`glyph->width * 10.0f * scale` leaves `mul.s $f6,$f14,$f4` vs the target's
`mul.s $f6,$f14,$f4` in the other operand slot, 2 bytes).

Both are ordinary C; no dummy locals, no volatile, no artificial construct.

The permuter reached score 0 on this function too, but only through
`new_var`/`new_var2` copies and `volatile unsigned int matrix`; those were
discarded. The honest minimal change above was found by reading the first
diverging instruction of the loop (`lbu v1,1(a0)` — the target indexes `a0`,
the draft `a2`, i.e. `p` vs `text`), which is why `p = text` had to move inside.

## MATCH: func_801BD270 (396 B)

Landed in `src/ovl_7DF8/ovl_7DF8_116E0.c`; ROM sha1 ba52e91b…, functions.csv T4.

Structural cause: **the `u16` button field must be masked at the final add**,
`result += buttons & 0xFFFF`. The target sums `v1 = (x + high16) + buttons`
*before* propagating the 64-bit carry; without the mask IDO widens `buttons`
to a signed 16-bit addend, reorders the two 32-bit halves and emits the
`sra t8,t0,31` sign fill. With the mask the pack is 0 differing words at
396/396 bytes.

The permuter reached score 0 only with an `int new_var = x & 0xFFFF;` copy
plus the same mask; the copy was dropped and the mask alone matches.

## Round 3 summary

Two matches for **684 B**:

| Function | Bytes | Cause |
|---|---:|---|
| func_801BE540 | 288 | loop pointer assigned inside `if (*text)`, not at its declaration |
| func_801BD270 | 396 | `u16` button field masked at the 64-bit add |

Everything else in the assignment stayed at or near its starting score. The
remaining near-misses were re-probed with four new structural tools
(`callset.py`, `regs.py`, `wordiff.py`, `stmtorder.py`) plus long permuter
runs (`--stack-diffs`, 1500-3000 s, 3-8 jobs each) and 200+ hand-written
variants. The permuter's only zero/near-zero results on the others depend on
constructs this task forbids:
- `func_801BE540` winner: `new_var`/`new_var2` copies + `volatile` matrix arg
  (the honest subset was extracted and matched, see above);
- `func_801BD270` winner: an `int new_var` copy (honest subset extracted);
- `func_801B2B8C` 260: `do{...}while(0)` wrapper only;
- `func_801BAA78` 140: `T023State801BAA78 *new_var = arg4;` copy;
- `func_801B5DCC` 140/220, `func_801B5650` 775/915, `func_801C4E38` 8,
  `func_801B5534` 8: reformatting only — re-measured with `measure.py` they
  are 11-15, 30, 7 and 2 differing words, i.e. unchanged from the drafts.

Best honest drafts are committed under this directory:
`func_801B3DB0.c` (261 words, was 278), `func_801B5534.c` (2),
`func_801C4E38.c` (7), `func_801B2B8C.c` (8), `func_801BD270.c` (now T4),
`func_801BE540.c` (now T4), `draft_801C4240.c` (fresh rewrite, 294),
`v4240e/a_memberread.c` (64, best for 4240), `v13/*` and `v14/*` (carousel
line-join and declaration sweeps).

## Round 4: further probes (no new matches)

- `func_801B3DB0`: direct indexed stores 278 -> **261** (best in this run). Then
  `kind`/`selection` as `u8` (304/324/328), `kind = mode` first (261), no `kind`
  local (287). The target's `mode` byte at sp+0x4B is the *argument home slot*
  (`sw a1,0x4C`), so it re-reads its parameter; that is already what the draft
  does for the guard. Remaining 261 differ in the initial mode-selection block.
- `func_801C23C0`: velocity as three scalars (181), arrays on one line (198),
  dropping the single-use float temps (410). The target frame is 0x20 smaller;
  no honest local set reproduces it.
- `func_801C4E38`: explicit `& 0xFF` at the callee and the table index (111,
  and it grows the body by 4 B), byte local for the selector across both calls
  (18). The two-word spill slot is not a masking issue.
- `func_801B5534`: `u32`/`s16` index (42/11), byte masks (40).
- `func_801C4240`: sound read into a local (121), split statements (64).
- `func_801B5650`/`func_801B5DCC`: single-result `else` tail (95) and the
  pointer-assignment move that worked for `func_801BE540` (15 vs 11).

## Status

Matches: **func_801BE540 288 B + func_801BD270 396 B = 684 B** of the 2,030 B
goal. ROM sha1 `ba52e91b44450c548467044b26951353dc491e04` on a clean build,
`docs/functions.csv` shows both as T4, M2 108,600 -> 109,284 B.

The remaining 14 functions in the assignment are all still short. For each, the
measured evidence is:
- call set identical to the original (`callset.py`): no missing/extra call;
- saved-register set identical except one extra `s8` in `func_801BDA6C`,
  `func_801BCB70`, `func_801BDF94`;
- frame deltas: 0 for `func_801C4240`, `func_801B5DCC`, `func_801B5650`,
  `func_801B2B8C`, `func_801B5534`, `func_801C4E38` (pure scheduling); +0x18
  `func_801B0CDC`, +0x8 `func_801B3DB0`, +0x10 `func_801BDA6C`,
  +0x10 `func_801BDF94`; -0x20 `func_801C23C0`, -0x10 `func_801B9A04`,
  -0x78 `func_801BCB70`.

What I did not get to: a full clean-room rewrite of `func_801BCB70` and
`func_801BDF94` from their assembly (both are still straight m2c with dozens of
`temp_*`/`var_*` locals and 300+ differing words). Those two are the remaining
1,676 + 1,452 = 3,128 B that a later worker should start from.
