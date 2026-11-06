# T-173

Targets: `func_801C2F5C` (3 words), `func_801C1434` (3), `func_801B0520` (5), `func_801ADA04` (5).
Counts are `screen.measure` positional words in the full TU.

## Matched

### func_801C1434 (720 B) — T4
- The target compares two *variables* (bne operands in declaration order, `lui` of the first one in the
  `beqz` delay slot). A draft that compares an expression against `player` puts `player` first.
  A real local `fd = D_802D37FD` assigned before `player = D_802D37FC` gives that stream
  (`lbu $2 FD; lbu $16 FC; bne $2,$16`).
- An extra local costs +8 B of frame (0x48). The `u64 value` local reused for both `D_802D3800[n]`
  tests absorbs the 8-byte u64 temp at sp+0x30, so the frame is back at 0x40.
- The last difference (lbu order) is source layout: `fd = D_802D37FD; player = D_802D37FC;` on ONE line.

### func_801ADA04 (208 B) — T4
- Pointer view `s32 *pendingp = &D_801CD4BC` for ALL accesses of the pending word (compare, store,
  index, final store); plain `D_801CD4BC` shares the address in a register.
- `*pendingp = *pendingp;` is the target's redundant store of the loaded value; uopt delays such a store
  to just before the call (that is the late `lui at`/`sw v1` placement). No extra locals needed.
- Remaining word was the tail `-1` in `t3` instead of `v1`. A constant only becomes a uopt web (v0/v1)
  when it sits in its own basic block. `do { *pendingp = -1; } while (0);` gives that block
  (the permuter found the same effect with a dead `if (!p) {}`, which is not honest).

## Not matched

### func_801B0520 — 5 words, 328 B
Best drafts: `func_801B0520.c` (v0 web correct, store 3 insns early) and `func_801B0520_late_store.c`
(store placed as in target, but the part-2 value web is v1 instead of v0). The two goals conflict in every
variant tried:
- store of a variable (`*p = frame`) is placed at statement position (early); `*p = *p` (redundant store of
  the loaded node) is delayed to the call, which is the target placement, but then the load is a web that
  gets v1 because a pointer-variable web (or the copy web) holds v0. As1 cannot move the store pair above
  the `lui at,0xC2B4/mtc1` constant pair (both use `at`), so the early store always shows.
- Without a pointer variable (array view `D_801D2EB8[1]` for the load, direct store) the web is v0
  but the store is early; with same-expression array load/store the address is shared (11 words).
- Tried: pointer vs direct for every access, array views (`D_x[1]`), two pointer vars, extra variable chains,
  `new_var` pointer chains, block-scoped `g`, `register`/`const`/`volatile` pointer, `do{}while(0)` around every
  simple statement (singles and all pairs) and around balanced blocks, line join/split hill climb,
  declaration-order permutations, in-place `frame` reassignment, constant var for -90.0f, else-arm return forms,
  honest-weight permuter (3 runs, 25-50 min).
- Observation: `return frame;` (instead of constants) makes the web v0, so the return-value constants
  `li $2,1` interact with the allocation; a single-return rewrite changes code size (332 B).

### func_801C2F5C — 3 words, 544 B
Draft unchanged (`func_801C2F5C.c`, from T-160). Only difference: the layout-pointer web at the first
use (`addu t0,...; lbu 12(t0)`) is v1 in the draft, t0 in the target; the second site already matches.
- Allocation is first-fit over v0,v1,(a-regs when free),t0...; the draft's pointer takes v1 because v0 is
  held by `var_v0`. The target needs v1 busy too. Adding a flip variable (`flip1 = temp_t0->flip`) makes
  the pointer t0 (v1 goes to the flip web) but then the flip load is v1 instead of the target's rotation temp
  and the temp numbering shifts (50 words). Named intermediates (texture, y sum, scale, fx, clip, call
  result copy chains) leave the pointer in v1.
- do-while wraps (all singles and pairs), line joins, direct/pointer reads at either site, permuter
  (25 min, best weighted score 15, still 3 words): no change.

## Tools (this directory)
`msweep.py` (parallel `screen.measure`), `lab.sh` (`cc -S` ugen stream, deterministic register
allocation: the best way to see web registers), `slotsig.py`, `dowsweep.py`/`dowpairs.py`/`blockwrap.py`
(do-while wraps), `joinclimb.py` (line join/split), `permrun.sh`, `install.py` (splice a draft over a
`GLOBAL_ASM` line).

## Facts worth reusing
- The `cc -S` stream shows the final uopt/ugen register choice: webs use v0,v1,a-regs,t0..; expression temps
  rotate t6,t7,t8,t9,t0,t1,... (never v0/v1). A constant is a web only with 2+ uses or in its own block.
- bne operand order: expression==expression gives (RHS,LHS) with RHS loaded first; variable vs expression gives
  (variable, expression); two variables give (LHS,RHS).
- Any extra function-scope local costs 8 B of frame; a `u64` local replaces the u64 temp slot.
- `*p = *p` style redundant stores are delayed to the next call; stores of variables stay at statement position.
- as1 schedule depends on source lines: two statements on one line changed an lbu order.

## Lead vetting (2026-11-06)

`func_801ADA04` was NOT installed: the draft's `*pendingp = *pendingp;` is a no-op
self-assignment and `pendingp` is an alias for the global, so it fails the honest-source
rule. The function stays at T2; the draft is kept in `func_801ADA04.c`. Best word count
with honest source is the earlier T-159 number (5 words). `func_801C1434` was installed
(both locals are read, `value` is used for both `D_802D3800[]` tests).
