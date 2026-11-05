# T-161

No draft in this pool lowered its official full-TU word count. Nothing was committed as a replacement. Counts below are `screen.measure` (the table's score) and, where useful, the best-alignment diff from `T-155/cmp.py` (`diffwords`, with `REGMASK` ignoring register names).

## func_80015594 (main, 1,488 B) — closest, still above 80

Official 276, compiled 1,472. Best alignment: 174 words, 94 with registers ignored. The function is a leaf. The target frame is 0x28 (s0–fp only). The draft frame is 0x30 because `tex * -0x10000` is a `multu` by `0xFFFF0000` held in `ra`, so `ra` is saved.

`((-tex) << 16) | (-yy & 0xFFFF)` removes that multiply. Registers-ignored alignment falls to 80 and the function shrinks to 1,468 B, but the official score rises to 358: `ra` is still saved, now holding the constant `0x02000200`, and the stack offsets stay shifted. Ternary clamps (`x > 0 ? x : 0` / `x < 0 ? x : 0`) match the target's `blez`/`bgez` shape more closely (registers-ignored 81, 1,476 B) and also raise the official score (356).

The extra saved register is the hoisted texture step. The target keeps that in a temporary (`t5`) and the five command constants in s4–fp. The draft keeps the step in a saved register and pushes `0x02000200` into `ra`. Ten long-lived values, nine callee-saved registers. Previous notes already recorded that ternary clamps restore the size but not the frame.

## func_801B1A7C (ovl, 872 B) — unroll factor

Full TU compiles once the parameters are `void *` (the later block-scope externs). Official 206–208, compiled 596–604 against 872. The body (divide by 50, scale by 256, `multu` of x and y, `amount * 0.5` as a double, return `amount * 1.5`) is the right one, and the multiply is already `multu`.

The target is the ordinary IDO 4× unroll (`andi` mask 3, four copies, remainder loop). At `-O2` a loop that scales both x and y unrolls twice. Scaling only one component, or one component plus the double store, still unrolls 4×. The second integer multiply is what crosses the `-O2` cutoff. `-O3` unrolls the full body 4×, but `-O3` changes the already-matched `func_801B1A14` in the same file, so this translation unit stays `-O2`.

## func_80029BE0 (main, 1,060 B) — declarations were already the real score

The draft's own `D_80061D60` and `func_8002A004(void *)` declarations conflict with the translation unit. The symbol is the existing `T024ResetEffect` array; a same-layout view (angles in the 0x90 pad, `x,y,z` in the 0xC pad, `scale`/`flags` in the 0x10 tail) compiles in the full TU. Official stays 263, compiled 1,048. Best alignment 211, 97 with registers ignored. Target frame 0x120 versus draft 0x110. Not an improvement over the table.

## func_8001D7E4 (main, 1,656 B)

Official 309 at the exact size. Best alignment 355, 159 with registers ignored. The target frame is 0x58 and the early tests are `bnel` chains; the draft is one compound condition and a 0x20 frame. Same instruction count, different control flow. Not a one-edit drop.

## func_801C5E74 (ovl, 2,392 B)

Official 512 at the exact size (T-151). Best alignment 554, 178 with registers ignored. The T-154 pointer view is worse (550 words, 2,400 B). The recorded blockers remain: IDO common-subexpressions the `D_802D3980` address across the null test and the store, and `flags & 2` is recomputed. A second symbol at the same address is not an honest fix.

## Not re-scored as improvements

`func_800306B8`: T-026 is the table row (510 words, 2,096/2,104). T-156's draft is 514 official / 2,044 B; the "127 words" note was register-masked, and the masked alignment is 163. `func_801B3DB0` and `func_801BB7B4` still fail the full TU on a redeclaration (`D_8012834B` as `s8` versus the unit's `u8`; `D_802C9F69`).
