# T-154 working notes (ovl_7DF8 text-render family in ovl_7DF8_116E0.c)

Start commit 62c5c59, baseline M2 111,380 B (clean toolbox build, ROM sha1 ba52e91b...).
Target functions: func_801BDF94 (1,452 B), func_801BD640 (1,068 B), func_801BDA6C (1,320 B). The three were
"straight m2c" drafts at 191-352 words off; with the recipe below BDF94/BD640 are down to 0-6
register-numbering lines (see per-function sections).

## Result: 4 matches, 2,444 B (M2 111,380 -> 113,824; clean toolbox build, ROM sha1 ba52e91b...)
| Function | Bytes | Structural cause |
|---|---:|---|
| func_801BDF94 | 1,452 | pointer view of the frame counter (`tick`), no `matrix` variable (`&matrices[count++]`), one shared `f64 width`, declaration order for the frame, two cmd statements on one line |
| func_801BD3FC | 580 | the draft copied `buttons`/`old`; the original uses the u64 parameter and the table entry directly (re-loaded each time), plus two discarded 64-bit shifts |
| func_801BE660 | 300 | `width / 2` (int literal) gives `div.s`; `if (*text) { p = text; do ... }` as in the matched sibling BE540 |
| func_801BD200 | 112 | clamp compares against the value just stored into `D_80282A60` |

Not matched (drafts kept): `func_801BD640` (`wd640/i.c`: reg-masked identical, only temp-register numbering of the
colour-pack differs, 63 exact lines), `func_801BDA6C` (`wda6c/a.c`, 70 words after a clean rewrite; frame 240 vs 216),
`func_801C5E74` (`w5e74/ptr1.c`: the pointer-view trick removes the `D_802D3980` address sharing; `D_80291FE8` table
address is now shared where the target recomputes it, frame 232 vs 224, `dc` is rematerialised instead of spilled).

Match-only constructs in func_801BDF94 (lead-tested ablations in `ablate_df94.py`): `s32 *tick = &D_80282DC0`
(without it IDO keeps the address in a saved register), the shared `f64 width` (two width variables, or the ternary,
change the frame / `mul.d` operand order), the `sine` local (an inline `sinf` works only together with a `matrix`
local for the `guTranslate` call; both spellings match), the declaration order, and the two lines that hold both
command words (`g->w0 = ...; g->w1 = ...;`: splitting them reorders a `lui/ori` pair).

## Tools (all in this directory)
- `cmp.py fn draft` - canonicalised instruction diff vs the original splat asm. Relocs are folded to absolute
  addresses (splat names `D_xxxxxxxx` by address), `REGMASK=1` masks registers, `RONORM=1` normalises the
  `.rodata` float loads (6+ false diffs otherwise), `COUNT=1` prints only a count, `STACK=1` lists sp slots,
  `PREFIX=1` compiles only the text before the function (needed when later functions in the TU redeclare a global).
- `c.sh/ce.sh/cb.sh/d.sh` wrappers (toolbox); `asm.py`, `mini.py` (compile a standalone snippet).
- `vgen.py` (apply named edit lists), `pairs.py` (every single/pair of atomic edits), `dsearch3.py`
  (declaration-order search, objective = (reg-masked, exact)), `joinclimb3.py` (hill-climb which source lines are
  joined), `cmdsearch2.py`, `gen2_df94.py`/`gen_d640.py` (template generators for random structural search),
  `tokdiff.py` (token diff of permuter output).

## Findings that generalise (all verified by compiling)
1. **Address CSE of a global that is read around calls and incremented.** `G` read, `jal`, read, ..., `G++`
   makes IDO keep `lui;addiu` of `&G` in a saved register (`lw t9,0(s0)`). The original has plain `lui/lw` and
   `lui at/sw`. `volatile`, `static`, array or struct spellings do not change it; a local pointer `s32 *tick =
   &G;` used for all accesses does (T-145 `counter` trick, reproduced here).
2. **No `matrix` variable.** `m = &mtx[count]; f(m); cmd->w1 = m; count++` compiles to `addu a0;..;move s0,a0`
   (copy propagation). `f(&mtx[count]); cmd->w1 = (u32)&mtx[count++];` gives the original `addu s0;..;move a0,s0`.
3. **Frame size and spill slots follow the locals.** Each local (block-scoped `Gfx *g`, f64 temps, pointers) can
   reserve slots; the first declared local is highest. The frame, the `Mtx` address and the f32 spill slot
   are matched by declaration order (dsearch3.py) and by the number of f64 temporaries (one `f64 width` shared by
   the three width selections; `x + scale * (c ? a : b)` flips the `mul.d` operand order, `x + scale * width`
   does not).
4. **Line structure matters.** IDO schedules `lui/ori` pairs differently depending on which statements share a
   source line (macro expansions are one line). joinclimb3.py finds the joins automatically.
5. The final register-numbering difference of the temps (`t7` vs `t9`, `a0` vs `v1`) is sensitive to every one
   of the above; the random searches (`gen*.py`) are how it is explored.
