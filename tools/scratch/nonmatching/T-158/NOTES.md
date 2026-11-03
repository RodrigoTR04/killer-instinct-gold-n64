# T-158 notes (ovl_7DF8: carousel pair + func_801BBB60)

## Matched
- func_801B5DCC (1,884 B) and func_801B5650 (1,916 B): ROM byte-identical, M2 117,912 -> 121,712 B.
  Cause: the drafts kept an `index` local and re-derived `record = &D_802C8C30[arg1->index]` after each helper call.
  The original just reads `arg1->index` / `D_802C8C30[arg1->index].right` at every use; IDO's PRE then recomputes the
  record address only on the paths that crossed a call, and the late `lw arg1` hoists above the `sh` store.
  Then: `z = -10.0f` before the height load (gives f10/f18 FP temp order and the `lui at` before `addu v0`), the
  end store of the rotation as `*(f32 *)((u8 *)D_802C8C60 + arg1->index * 8)` (the `D_802C8C60[arg1->index * 2]` form
  burns one temporary register), early `if (state == 5) return 0;`, and `D_802C8C28` as `u8[]` (lbu, not lb).
  The `divisor = 8.0f` float local must stay (`/ 8` or `/ 8.0f` gives 36-50 words).

## func_801BBB60 (292 B): still 11 exact / 4 register-masked words
- cmp.py false-diff fixed: the REL addend sits in the immediate (`lui a1,%hi(D_802C8D20)` + `addiu a1,a1,4096` is the same
  address as splat's `D_802C9D20`), `fix_addends()` folds it, so the real diff is only the red/green gradient loops
  (registers t8,t0,t1 / t3,t4,t6,t7 in the target vs a0,t7,t8 / a0,t9,t0,t1, and `ori` after `slti` in the target).
- Tried, no gain: pointer loops with the symbol end bound (CSE'd with the palette pointer, 12-45 words), 3x3x... cross
  product of 12 loop forms per gradient loop (`bbsearch.py`, 1728 candidates, best stays 11), local types for red/green/i,
  separate palette index `j`, 300 s `autosearch2` (decl order, joins, swaps, types). The target does not use a0 for
  `i - 8`; why is unknown.

## Tools
cmp.py/lib.py/asm.py/wordiff.py (T-155 copies, root paths fixed, addend fix), c.sh, ev.py (variant list -> score),
mv.py (move one line everywhere), bbsearch.py, autosearch2.py.
