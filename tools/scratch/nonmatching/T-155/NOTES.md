# T-155 working notes (ovl_7DF8 mid-size functions)

Start commit be2cd2c, baseline ovl_7DF8 M2 55,188 B (clean toolbox build, ROM sha1 ba52e91b...).

## Matches
| Function | Bytes | Structural cause |
|---|---:|---|
| func_801BD640 | 1,068 | colour pack written as the SDK-style masked component macro `(((u32)(v) & 0xFF) << s)` for every component (plain `<<` leaves temp registers numbered differently); `w0`/`w1` of the FC and B6 commands on one line each |
| func_801B5534 | 168 | no local `sample`: the s8 table is filled by re-reading the s32 element just stored (`B[i] = A[i];`), which moves the index scaling and the spill slot |
| func_801C0800 | 248 | same colour macro for r/g/b/a, last command's two words on one line |
| func_801C4E38 | 556 | the `switch (arg0)` is a negated if/else chain (`if (a != 1 && a != 5) { if (a != 9) default else case9 } else case15`): it gives the same body layout as the switch but no hidden switch temp, so the promoted argument's spill slot lands at sp+0x1C instead of sp+0x18; no `selector` local (D_80127CC1 is read twice) |

Total 2,040 B (ovl_7DF8 M2 55,188 -> 57,228; clean `make clean && make extract && make -j8 && make progress`, ROM sha1 ba52e91b...).

## Tools (this directory)
- `cmp.py`, `wordiff.py`, `asm.py` (copies of the T-154 tools); `c.sh fn draft` (canonical diff; env PREFIX, REGMASK, STACK, COUNT),
  `frame.sh fn draft...` (frame size, exact and register-masked word diffs), `batch.sh`.
- `lib.py`: `score_src(fn, text, prefix)` -> (masked, exact, frame, ninstr); `run()` scores many variants in parallel threads.
- Searches built on lib: `declhill.py` (move one declaration), `declrand.py` (random declaration orders), `sitehill.py`
  (swap / join the two words of each `x->w0 = ..; x->w1 = ..;` pair), `joinhill.py` (statement-atom line joins),
  `autosearch.py` / `autosearch2.py` (decl order + joins + local types (+ safe statement swaps)), `permrun.sh`
  (decomp-permuter with the forbidden mutations (empty stmt, dummy comma, self assignment, mask/xor/mult zero, ...) weighted 0).
- Permuter caveat: its score is not the word count; several "improvements" were only line joins or forbidden wrappers
  (`do { } while (0)`), re-score its output with `frame.sh` before believing it.

## Findings
1. Colour packs of u8 arguments: use the masked component macro (BD640, C0800). Not helpful for 2B8C, 49A8, AFFAC, B0520.
2. A function-level shared `TextGfx *cmd` gets s0; block-scoped command pointers become v0 temps and each reserves a frame slot.
   Per-site `f64` width temps (3 widths) set the 216-byte frame of func_801BDA6C.
3. Call (sinf) before the display-list pointer fetch, and the T-145 pointer view `f32 *glowPhase = &D_80282D20` for the global that is read and
   written around calls; without it the address is hoisted into the last saved register and displaces the 0xE7000000 constant.
4. Spill slots of promoted values are allocated top-down after the locals; a local that IDO keeps only in a register still pushes the spill slot down
   by one word (5534). A `switch` also consumes one slot (4E38: if-chain gives the target's 0x1C, switch gives 0x18).
5. A constant-trip loop IDO can unroll is unrolled (8004 first loop, 8x/4x) unless its exit test is not the canonical `i < N`;
   `for (;;) { ...; if (i < 34) continue; break; }` and `i += step` avoid it but are not honest-looking; no natural spelling found.

## Not matched (best drafts kept)
- func_801BDA6C (1,320 B): `da6c/w1.c`, 14 reg-masked / 37 exact words; frame 216 correct, s-register assignment correct;
  remaining: the target hoists `lbu a2,255(sp)` (the u8 argument `a`) to the start of the block and spills it before the colour pack.
- func_801C8004 (236 B): `d8004/best_k7.c` 4 masked / 20 exact, needs `step` (not honest).
- func_801C4E38, func_801B1DE4, func_801BAA78, func_801ADA04, func_801B0520, func_801C3758, func_801B2B8C, func_801C4240, func_801C23C0:
  drafts under `d4e38/ d1de4/ dbaa78/ dada04/ db0520/ dc3758/ d2b8c/ d4240/ d23c0/`.
