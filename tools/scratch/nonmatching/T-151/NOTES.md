# T-151 working notes (ovl_7DF8 mid/large drafts)

Matched: func_801CC3BC (360 B), func_801CD1F0 (460 B), func_801C7310 (1,276 B) = 2,096 B. See the final report for causes.

Not matched (drafts here): func_801C5E74 (2,392 B; frame, slots and ~500 of 596 instructions equal modulo registers), func_801C8004 (236 B, honest 16-word form), plus the older T-023/T-025/T-029/T-030/T-034 drafts that were not touched (801C5298, 801BFCBC, 801BC1B0, 801C08F8, 801C9B14, 801CAA00, 801ABB20, 801ADEA0, 801B47A4, 801B6E4C, 801B849C): all still in the hundreds of differing words.

Tools built this round (not committed, they live in /tmp): a fast evaluator that compiles a draft in its
owning TU without linking and counts masked-relocation words, plus an LCS instruction diff with registers
masked (`REGMASK`) so register-allocation noise can be separated from structural differences.

Findings that generalise:

* IDO factors a global's address into a register when a load and a later store/load of the same symbol sit in
  nested blocks. The original code often does not (`lui; lw` then `lui at; sw`). A second access that is reached
  from a *join* after an `if` (`if (tbl[idx] == 0) idx = 0; x = tbl[idx];`) is not factored and IDO still emits the
  reload only on the changed path. This produced the unfactored `D_80292378[...]` accesses of func_801C7310.
* Chained assignment `a[16] = a[17] = a[18] = ' '` changes the register priority of the repeated constant
  (func_801CD1F0) and the frame layout.
* An integer literal `var = 1` for a float stops IDO hoisting the repeated `1.0f` into an FP register across the
  loop (func_801C7310), the same way `/ 2` instead of `/ 2.0f` did for func_801C5298.
* switch case order controls block layout: compare chain is sorted by case value but the bodies follow source order
  (func_801C7310 wants `default` inline, then t, c, h, g).
* func_801C5E74: frame 0xE0 and every stack slot (0x50, 0x98..0xA0, 0xD4, 0xDC, 0xE4/0xE8 homes) are reproduced when
  each display-list command has its own pointer local and the call-site address `dc = D_8007DC00` is assigned just
  before the `flags & 2` block. Remaining blockers: IDO shares the address of `D_802D3980` between the `== 0` test and
  the store (target keeps two independent `lui` pairs), and `flags & 2` is recomputed instead of staying in v0.
  Compiling with a second symbol at the same address for the test reproduces the target (diagnostic only, rejected as
  an artificial construct), so there is some other way the original avoided the CSE that I did not find.
