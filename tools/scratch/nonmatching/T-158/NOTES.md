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

## Tools
`sc.sh fn draft...` (masked, exact, frame, ninstr), `measure.py` (screen.measure), `dump.sh`, `permrun.sh`, searches `s*.py`.
Run from the repo root with tools/ext, .venv, baserom, asm/ and build/ copied/symlinked from the lead worktree.
