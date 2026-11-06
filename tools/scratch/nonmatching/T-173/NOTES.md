# T-173

Targets: `func_801C2F5C`, `func_801C1434`, `func_801B0520`, `func_801ADA04`. All four are T4 now.
Counts are `screen.measure` positional words in the full TU (`msweep.py`).

## Matched (final sources are the `func_*.c` files in this directory)

### func_801C1434 (720 B)
- The target compares two *variables* (bne operands in declaration order, `lui` of the first one in the
  `beqz` delay slot). Comparing an expression against `player` puts `player` first. A real local
  `fd = D_802D37FD` assigned before `player = D_802D37FC` gives the right stream.
- An extra function-scope local costs +8 B of frame. The `u64 value` local reused for both
  `D_802D3800[n]` tests absorbs the 8-byte u64 temp at sp+0x30, so the frame is back at 0x40.
- Last difference (lbu order) is source layout: `fd = ...; player = ...;` on ONE line.

### func_801ADA04 (208 B)
- `VideoState *state = &D_801CD4B8` (struct `{current, pending}`), all accesses through `state->`.
  Memory locations reached through a pointer local are candidates for uopt web promotion; direct globals
  (or a struct/array *global*) share a `la` address instead and give 196-200 B.
- No self assignment is needed: the late `sw v1,BC` before `osViSetMode` is the write-back of the
  promoted `state->pending` web (it has a def later on the path). `do { state->pending = -1; } while (0);`
  is what turns the promotion on and puts the `-1` into that web (v1) instead of a `t3` temp. Without the
  do-while the function is 200 B.
- Compare operand order: `arg0->mode != state->current` (variable first) gives `beql t8,v0`.

### func_801B0520 (328 B)
- `s32 *frame = &D_801D2EBC;`, every access of the counter through `*frame`, and
  `do { *frame = arg3 * 2; } while (0);` for the first definition. Same mechanism as 801ADA04: the
  counter becomes one promoted web (v0), written back before each call, reloaded after the display-list
  stores; the store is sunk into the `< 230` arm, the `else` store disappears (it is the exit write-back).
- Direct `D_801D2EBC`, `D_801D2EB8[1]` and struct views of the neighbours give 316 B (shared `la`).
  The wrap has to be on the definition; wrapping other statements does nothing.

### func_801C2F5C (544 B)
- The target's layout pointer is a web in t0 even though v1 is free, because a hidden v1 web overlaps it.
  That web is a *named constant local*: `byteVal = 0xFF;` at the top, later passed as the alpha argument
  and then reused for the flip byte at the draw call. The constant is propagated (no instruction), but
  the variable's live range keeps v1 busy at the first layout use, so the pointer web goes to t0.
- All `D_802854D0[D_802D38C8]` reads are plain expressions (no `temp_t0` pointer local). Found by the
  permuter on that base (`temp_t1 = 0xFF` + a zero-compare local); only the 0xFF local is needed.
- No extra locals: the byte local is shared, frame stays 0x60.

## Facts worth reusing
- `cc -S` shows uopt/ugen register choices. Webs take v0,v1,(a-regs when no arg write in range),t0,t1...
  Expression temps rotate t6,t7,t8,t9,t0,t1,... and never v0/v1. A constant is a web only with 2+ uses or in
  its own basic block (a do-while(0) with a real statement gives one).
- Promotion: `*p` through a pointer local becomes a register web with write-back before calls (when the web
  has a def anywhere on the path) and at exit. Requires a do-while(0) around a def.
- A named constant local (even if propagated away) can occupy a register in the allocation and push
  another web out of v1.
- bne operand order: expr==expr gives (RHS,LHS); variable vs expression gives (variable, expression); two
  variables give (LHS,RHS).
- Any extra function-scope local costs 8 B of frame; a `u64` local replaces the u64 temp slot.
- as1 schedule depends on source lines (two statements on one line changed an lbu order).
- IDO 7.1 gives identical results to 5.3 for these functions; -O3 breaks asm-processor size accounting.

## Tools (this directory)
`msweep.py` (parallel `screen.measure`), `lab.sh` (`cc -S` ugen stream), `slotsig.py`,
`dowsweep.py`/`dowpairs.py`/`blockwrap.py`/`rangewrap.py` (do-while wraps), `joinclimb.py` (line join/split),
`permrun.sh` (honest-weight permuter), `install.py` (splice a draft over a `GLOBAL_ASM` line).

## Judgment calls for review
- 801ADA04 and 801B0520 use a pointer local to a global (`state`, `frame`). The effect (promotion with
  write-back) cannot be had with direct global access, a struct global, or an array view. The same idiom
  (`u8 *second = &D_80127CC1;`, `s32 *tick = &G`) is already in matched sources. `state` is a typed struct
  view with two real fields; `frame` is a single-word pointer.
- 801C2F5C's `byteVal` is initialised with the real alpha constant and reused later for the flip byte.
