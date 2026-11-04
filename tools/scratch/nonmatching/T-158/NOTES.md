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

## func_801BBB60 (292 B): MATCHED
- 11 -> 4 words: ramps are `GPACK_RGBA5551` with 8-bit components (red `(i-8)<<3`, green `248, (i-40)<<3`, blue `248, 248, (i-72)<<2`).
  The mask/shift pairs of the macro leave dead nodes that account for the skipped temporaries (t8,t0,t1 / t3,t4,t6,t7 / t2,t3).
- 4 -> 0: source line layout. With header and body on one line the increment lands after the shift; with the `for` body on its
  own line (`for (; i < 40; i++)` newline `*palette++ = ...;`) as1 emits `addiu v1,v1,1` before the shift. Line joins/splits are a real lever.
- Dead ends (many): cast chains, variables, loop-form permutations, statement order, i++ placement, 1,200 random natural variants,
  30 min permuter (never changes line layout), as1 scheduler lab (hand-written .s: scheduling is a function of the DAG only,
  source statement order never changes it; the `.loc` line info is what the C path adds).

## Tools
cmp.py/lib.py/asm.py/wordiff.py (T-155 copies, root paths fixed, addend fix), c.sh, ev.py (variant list -> score),
mv.py (move one line everywhere), bbsearch.py, autosearch2.py.
