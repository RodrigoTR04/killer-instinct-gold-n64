# T-158 notes (func_801C8004, func_801B2B8C, func_8001BDE0, func_80023EF0)

func_80032738 dropped: handwritten T-026 cluster (IDO -mips3 emits `daddiu`/`sd` for an s64 add, but the function is
hand-written asm, so no C form is expected). The other four are IDO output (same size, near-identical code).

Official counts (`screen.measure`, positional words) before -> after: 801C8004 6 -> 6 (honest form, see below),
801B2B8C 8 -> 8, 8001BDE0 8 -> 8, 80023EF0 10 -> 10. No count improved.

## func_801C8004 (236 B)
`func_801C8004.c`: 6 exact words, 0 register-masked, **no `step` variable**: first scan ends with
`if (var_a0 < 34) { continue; } break;` (the `>= 34 break` / `for (;;)` canonical forms get 7 masked; the
`continue; break;` spelling avoids IDO's slti->bne rewrite). Second loop is the T-139 goto form.
Remaining 6 words are register naming only (pointer cursor v0/v1 in the target, a3/v0 here). 250 random
declaration orders, separate second-loop cursor (9 exact), pointer/for/do second loops: none better. Permuter 900 s: no gain.

## func_8001BDE0 (316 B)
Target: threshold f20, scale(1500) f22, bias(590) f24. Every form tried gives a rotation of those three:
- literals `1500.0f`/`590.0f` (natural for-loops over a 0x30 stride array, 12 words; goto form 8 masked): scale f20, bias f22, threshold f24.
- extern-global locals (`func_8001BDE0-loc.c`): 3 masked, 9 exact: threshold f24, bias f20, scale f22.
- T-109 form (`arg2` reused as scale): 2 masked / 8 exact (best).
- statement order x placement (pre/mid/late) x decl order x lit/ext/local, `register`, extra copy of arg2 (adds `mov.s`): none 0.
- Permuter (honest weights): only "improvement" was `(temp_f0 = threshold) < temp_f0_2`, a fake alias; not used.

## func_80023EF0 (312 B)
Frame 136 requires the T-148 local set. Snapshotting both `x = actor->x; y = actor->y;` before the stores gives the target
instruction order (lw lw ... srl srl ... sw sw sb) = 2 masked words (`func_80023EF0-regmask2.c`), but x/y then take a0/a1 and
shift facing/D_8004F390-base to a2/a3 (19 exact words vs T-148's 10). The target has x/y as t3/t5 (expression temps).
1,080 variants (facing spelling, body order, u32/s32/u8 types, random decl orders) did not change the register choice.
Adding a third snapshot local (x) without removing another pushes the frame to 144.

## func_801B2B8C (872 B)
150 random declaration orders: best 13 masked / 21 exact (the T-025 order); address-sharing for D_801D308C/D_801D3094
(a2/a3 vs a3/a1) is unchanged. Permuter run was cancelled when the task changed (no result).

## Round 2 findings (register-allocation model, none matched yet)

func_8001BDE0 (FP saved registers f20/f22/f24; target = threshold/scale/bias):
- Literal form `z * 1500.0f - 590.0f` with `arg2` as threshold gives scale f20, bias f22, threshold f24 (the param web ranks last).
- Adding ONE extra reference to the threshold web flips it to f20 and gives exactly the target assignment and load order
  (bias f24 loaded first, scale f22): micro test `temp <= arg2 && arg2 == arg2` (adds a compare, so not usable), and the
  conditional redundant def `if (arg1 > 3) thr = arg2;` before the second loop (no code emitted) -> 3 official words
  (`w_bde_hack.c`, NOT honest, kept only as evidence). Unconditional copies/chains of arg2 are copy-propagated and do nothing.
- With explicit float locals instead of literals, ties are broken by definition order (first def = lowest register) and the
  two loads are emitted in program order, so bias-first emission always gives bias < scale (target is scale < bias): never matches.
- Remaining mismatch with the hack is the placement of the second hoisted constant load (2 instructions late).
- `T-158/r8001{e,h,i,l}.py`: 2,300-3,200 variant families (roles x copy chains x slot positions), best 4 exact words.

func_801C8004: the target uses v0/v1 for the pointer cursor/value, a0/a1 for index/table. In call-free micro tests webs get v0/v1
first; in functions with a call (this one has `jal` at the end) IDO gives webs a0..a3 and keeps v0/v1 as temps, yet the target
cursor/value are in v0/v1. 877 variable-sharing partitions, 576 loop spellings, index vs pointer cursor: none reproduces it.

func_80023EF0: frame 136 needs about 8 locals; target x/y loads are expression temporaries (t3/t5), not locals. A snapshot local
becomes an a0/a1 web. Every plain/ordered spelling keeps the second load after the first store.

func_801B2B8C: only the two address-web registers differ (308C: a2 vs a3, 3094: a3 vs a1). Reusing arg1/arg3/local for fade, tick,
value (27 combos) and plain locals do not change them (locals add frame slots: 192 vs 184).

## Round 2 results

MATCHED func_80023EF0 (312 B, official 0 words, ROM byte-identical): the lever was the *declaration*, not statement order.
`D_801D3430` was `extern u8` indexed through casts and a pointer cursor (`actor`). Declaring it as an array of the actor struct
and writing `for (i = 0; i < 40; i++) D_801D3430[i].field` (no `actor`/`point`/`y` locals) makes IDO (1) strength-reduce the index
into the s0 pointer loop with the end pointer `D_801D3430 + 0x2800` (= D_801D5C30, folded into %hi/%lo of the same symbol), and
(2) treat the actor reads and the `D_8004F2D0` stores as different symbols, so both coordinate loads move above the first store
(this is why the target has them as temporaries t3/t5 and no x/y webs). Pointer loops over a cast `u8` symbol never hoist the loads.
`func_8001E0B4` now indexes the same array (`state = (u8 *)&D_801D3430[player]`), codegen unchanged.

func_801B2B8C: the matched siblings (func_801B2EF4/310C/...) show the family template: `s32 *counter = &D_801D30xx;` for the fade,
`arg1 = *counter; if (arg1++ < 10) {...} else { *counter = arg1; do { ...; if ((s32)D_801D308C >= N) break; D_801D308C += 1; } while (0); }`.
Applying the do/while/break form to the else arm of the T-025 draft fixes the 308C address register (a3 -> a2): `w_2b8c_dw.c`,
3 register words left (the 3094 address web is a1, target a3). Going fully sibling-style (separate p0..p5, color2, packed, primitive,
counter/timer pointers) gets both address registers right but frame 216 vs 184 (extra spill slots).

func_8001BDE0: FP register order is decided by web priority (references weighted by loop depth). The permuter (all mutations) reaches
0 with `do { dl setup; loop 1; ... } while (0)` around the first loop, or with `if (arg1 > 3) thr = arg2;` before loop 2; both are
semantically empty structure whose only effect is the priority/weight of the threshold web. Not committed (fake step).

MATCHED func_8001BDE0 (316 B, official 0): same lever as 23EF0. `D_801D7E00` is a struct `{ u8 pad[0xF0]; T020DrawEntry entries[40]; }`
(0x30-byte entries, z first); two natural for-loops with `if (depth <= arg2) call else break;` (loop 1) and
`if (arg2 < depth) call else break;` (loop 2, i from 39). IDO then strength-reduces the typed index into the s1 pointer with the
0xF0 displacement and ranks f20/f22/f24 as in the target; no thr/scale/bias locals. The two dl stores sit on one line (scheduling).

MATCHED func_801B2B8C (872 B, official 0) and func_801C8004 (236 B, official 0; typed `FrontendSettings` pointer tables + plain loops).
2B8C lever: the address-web registers (308C a2, 3094 a3) follow the number/identity of the dl-command pointer webs. Seven command writes
share four pointer variables in the order p3,p0,p1,p3 (else arm, inside the sibling-style do/while/break), p1,p2,p3; `phase` dropped.
Found by random assignment of pointer names to the seven writes (`r2b8c14.py`, ~250 of 1,500 samples had frame 184 and the right
address registers; the best scored the 6-word noise floor and official 0). Phase local removal keeps frame 184.

## Tools
`sc.sh fn draft...` (masked, exact, frame, ninstr), `measure.py` (screen.measure), `dump.sh`, `permrun.sh`, searches `s*.py`.
Run from the repo root with tools/ext, .venv, baserom, asm/ and build/ copied/symlinked from the lead worktree.
