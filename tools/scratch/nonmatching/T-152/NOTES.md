# T-152 working notes (DeepSeek V4.1 Flash)

Starting commit: `259b07f` ("Board: T-150 blocked until Nov 4"). Lead-tree baseline M2 = 108,600 B / 379 T4.
**Result: 0 B newly T4 — SHORT of the 2,030 B goal.** No function in my ownership list could be closed.

Clean toolbox verification at the end of the run: `make clean && make extract && make -j8 && make progress` →
ROM sha1 `ba52e91b44450c548467044b26951353dc491e04`, `docs/functions.csv` unchanged (379 T4 / 130 T2),
M1 = M2 = 108,600 B (37.46%). The `.venv` and `tools/ext` symlinks and `baserom.us.z64` are intentional
and untracked; `README.md` regeneration was reverted.

## Method (what I built and used)

- `/tmp/t152/t.py` — splices a draft into its owning TU, compiles with the exact game rule through
  asm-processor, and reports relocation-masked differing words plus the first differing offsets.
- `/tmp/t152/cmp.py` — ordinal-aligned two-column disassembly of draft vs. the untouched TU's
  GLOBAL_ASM object (relocation lines folded into the instruction they annotate). This is what made the
  "first diverging instruction" readable, including which symbol each `lui`/`lw` refers to.
- `/tmp/t152/link.py` + a linked-image comparison: `tools/scratch/flagprobe/compare.py`'s mask is correct
  but **rodata-relative relocations mask only the HI16/LO16 addend**, so a draft that reads an inline float
  literal scores N "differences" that vanish in the linked image. `func_80014D5C`'s 14 words are exactly
  this case: splicing it and building links byte-identically. It is a false negative in `screen.py`, but
  `docs/functions.csv` still refuses T4 (`build/src/main/main_2FF0.c.o` is the object the linker names, and
  the linked `build/main.bin` differs at `0x1b0`, `0x1b4`, `0x1bc`, `0x530`–`0x558` from
  `build/segments/main.bin`), so it is **not** a landed match. I did not claim it.
- `/tmp/t152/runs2.py`, `/tmp/t152/jalframe.py`, `/tmp/t152/syms.py`, `/tmp/t152/widths.py` —
  whole-pool diagnostics: matching-prefix/matching-run length, `jal` count, stack-frame size, and the
  set of `D_` symbols referenced. These produced the structural leads below.

## Whole-pool diagnostics (main T2 drafts)

- **Call count is right almost everywhere.** Only `func_8002E724` (2,832 B) has a wrong `jal` count: the
  target calls `func_8002F234` **5** times, the draft **4** (`case 2` sub-state `case 4/5` falls through
  without the call in the draft's version of the shared arm). 658 differing words, so not close.
- **Frame-size mismatches** (real, unfixed structural defects): `func_800306B8` 0x50 vs 0xD8,
  `func_8002BBD0` 0xC8 vs 0x1D8, `func_80026B38` 0x1F0 vs 0x278, `func_800327E8` 0x30 vs 0xA8,
  `func_80012390` 0x40 vs 0x50, `func_8001272C` 0xA0 vs 0x78, `func_8001DE5C` 0x68 vs 0x90,
  `func_8002E150` 0x60 vs 0x38, `func_8001272C`, `func_80028230` 0x50 vs 0x48.
- **Missing/extra globals** (only `func_80012390`, 476 B): the target touches `D_80300004..7` and
  `D_8030000F` — i.e. the decompressed archive is read through **absolute literals**, not through a
  cursor derived from `0x80300000`. The draft's `cursor[4] << 24` form is why four globals are missing.
  67 differing words, too far to be worth the quota on a 476 B function.
- **Global width audit** (`asm` access width vs. C declaration) found only mis-typed *non*-target symbols
  (`func_80019880` `D_8004A428`, `func_8001BDE0` `D_8004A4C8`, `func_8001E33C` `D_800698C4`,
  `func_8001EC74` `D_8004CED4/DE`, `func_8000FA80` `D_8004A230`) — those are the drafts' own view
  errors, not the target's types, so fixing them is not evidence of a structural fix.

## Per-function evidence (all probes are genuine C; no artificial constructs used or considered)

### `func_80014D5C` — 1,780 B, best 13 words (T-148 draft: 14); **closest large function in main**
Two residual clusters, both analysed instruction by instruction:
1. `0x1b0`/`0x1b4`/`0x1bc`: the three array bases (`D_8004A740` → a1, `D_8004AC98` → a0,
   `D_8004ACB0` → v1) are materialised in a different register order. The target's `lui`s interleave
   `D_800695CC`'s load and the `c.lt.s`, i.e. the compares happen *between* the address computations.
   Probes: 6 permutations of pointer initialization; hoisting the three bases before the
   `D_8004ACF8 == 0` if-chain (28 → 79 words); pure index form `D_8004A740[i]`/`D_8004AC98[i*3]`
   with an explicit `for` (286 words, and the whole 1,780 B size is lost); `u8 (*)[3]` view; `while (i < 3)`.
   Best is still 13. Not a scheduling tweak: any 3-cursor form loses the `i`-based `multu`, any
   index form loses the pointers.
2. `0x530`–`0x558`: the `div` in the `else` arm. IDO emits `sb zero,1(a0)`/`sb zero,2(a0)` in the
   division's `mflo` delay slot **before** the divide-by-zero check; the target emits them after
   `break 6`. I micro-tested this in isolation (`/tmp/t152/micro/m.c`): IDO 5.3 -O2 moves trailing
   zero-stores into that delay slot for every statement order I could write — 6-permutation brute force
   (120 compiles), chained assignment, `(s8) 0` casts, a `{ }` sub-block, a local `q = 0x2710 / v0`, a
   `u16` pointer store, `*var_a0++` form. The original's shape therefore isn't plain C store ordering;
   I found no honest formulation that keeps the size at 1,780 B.
3. `decomp-permuter`, 900 s, `--stack-diffs --stop-on-zero --better-only -j 8`: 10,311 iterations,
   no candidate with a lower score; all candidates were worse (best seen 150 vs. the draft's 14-word score).

### `func_8002FB80` — 544 B, exact size, 98-word matching prefix, 21 words off
The first 98 words match exactly. The divergence is `case 0xC0`'s four address bytes (the draft's
`data++` sits between `out[0]` and `out[1]`, the target's `addiu a0` sits after the `srl`s and before
`sb`s) and `case 0x40`'s texture bytes. Probes: 5 placements of `data++`, 4 orderings of the 0x40
stores, `*address++`-style pointer advance, deferred `textures[]` load. Best 21 (draft), 20 in the
T-128 form. The bytes are right, the schedule is not.

### `func_80023EF0` — 312 B, exact size, 50-word matching prefix, 12 words off
Target order is `lbu count`; `sll/subu/sll` for the point index; `lbu x`, `lbu y` **both before**
`sb count`; then `sw x`, `sw y`, `sb facing` after the `mflo`. Probes: 120-permutation brute force over
the six trailing statements (best 73 words), explicit `px`/`py` snapshots (27), `*count = old + 1`
moved before the stores (15), `D_8004F390[player] = old + 1` (15), `while` variants,
`decomp-permuter` 420 s (0 improvements). Best remains 12.

### `func_8001BDE0` — 316 B, exact size, only FP saved-register allocation differs (8 words)
Target: `f20`=threshold, `f24`=bias (590), `f22`=scale (1500), `f26` unused. Draft: `f20`/`f22`
swapped. Probes: 24 permutations of the four `f32` local declarations (all compile-error or unchanged),
6 declaration/initialisation orderings, `u8` param widths, `Bone` struct view with `f32 y` at 0xF0,
nested-`if` vs. early-return guard, `scale`/`bias` named locals vs. reading the globals in place.
Every form lands at 68+ words once the guard is a nested `if`; the 8-word draft is the only shape that
keeps IDO's original FP assignment order. Not closable.

### `func_800300DC` — 316 B, exact size, 69 words off
Real defect found: the target saves `a1` into `s0` and **moves `a0` into `a1`**, walking the *parameter*
as the input cursor — the draft copies `a0` into `v0`. Also the target's literal pass computes
`addu v0, t5, t6` (a separate sum) rather than adding into the running value. Probes: parameter-as-cursor
(p.c, 75), pointer-advance-first, `u8` count/distance, `i = i + count - 1`, `for` vs. `while`,
operand reorder `(first << 8) + ((second & 0xC0) * 2) + (...)`, `do/while` with swapped arms.
Best 69.

### `func_800121C8` — 304 B, exact size, 22 words off
Target stores `D_8004A3E4..F0` in address order but reads `D_801D87B8/BBC/C0/C4` into `t9/t0/t1/t2`
first; the draft interleaves store-then-load. Probes: one-statement-per-line split, a 10-statement
crammed line, a load-all-then-store-all form with four temporaries (37), `u8`/`u32` `mode` (61),
reordering the `D_8004A3E0` store before the packed word (31). Also found the draft's `_ovl_7DF8SegmentStart`
should be `func_801ABB20` (same address) and `D_800071F0` should be `boot_overlay_table` — real symbol
fixes that cost 0 words because the layout is `{u8 pad[8]; u8 *start, *end;}` and the target reads
`0x8`/`0xC` off the table base. Best 22.

### `func_80015594` — 1,488 B, 276 words off, 16 B *short*
The target is a **leaf** (0 `jal`, no `ra` save, frame 0x28, only `s0-s8`/`fp` spilled, args 4-7 read
directly at `0x3C(sp)`/`0x40(sp)`). The draft's 0x30 frame adds `ra` and 8 more bytes of spills, which is
the whole 16 B deficit, and the FP argument registers are transposed (`f12`/`f14`). Probes: `f32` vs.
`f64` offset arithmetic (353 words / 1,436 B). The 276-word gap is in the command-emission loop, not the
prologue, so this is not a near-miss despite the size being close.

### `func_80024CE0` — 1,652 B, 4 B short, 390 words off
Draft frame 0x78 vs. target 0x60 (24 bytes of extra spills). Target keeps the decompressed-archive base in
`s5` and a *second* copy at `0x38(sp)`, and materialises the three `D_8004CExx` pointers before the first
`boot_inflate` call — the draft recomputes them per block. 390 words is a rewrite, not a fix.

### `func_800306B8` — 2,104 B, 510 words off, frame 0x50 vs. the draft's 0xD8
The draft's 216-byte frame against the target's 80 proves it has wholesale extra locals (its declaration
block alone is 45 m2c temporaries). A correct version needs a full rewrite of a 526-word function: a
two-pass glyph-layout loop that walks the string twice (once to measure via `func_80030EF0` +
`D_80069E48`/`D_800482B8`, once to emit ~7 Gfx commands per character with four clamps and three
`div`-by-`D_800482B8[arg5]` scale computations). I read the whole body and did not have time to write and
converge it.

## Near-miss functions I re-tested and could not move (all with a *new* probe, not a repeat)

| Function | Bytes | Words | New probe tried | Result |
|---|---:|---:|---|---|
| `func_8001BDE0` | 316 | 8 | 24 declaration-order permutations of the four `f32` locals; nested-`if` guard; `Bone` view | no change (compile error or ≥68) |
| `func_80023EF0` | 312 | 12 | 120-way brute force of the six trailing statements; permuter 420 s | best 12 → 73 for reorders |
| `func_8002FB80` | 544 | 20 | 5 `data++` placements, 4 0x40 orderings, pointer-advance-first | 21 (draft 20) |
| `func_8002A900` | 220 | 15 | (per T-148/149 notes) not re-probed | unchanged |
| `func_80014D5C` | 1,780 | 14 | 6 cursor permutations, base hoisting, index form, 120-way store brute force, permuter 900 s | 13 (best) |
| `func_800121C8` | 304 | 22 | statement split, load-all-then-store, `u8` mode, symbol corrections | 22 |
| `func_800268C0` | 236 | 28 | (T-148 26) not re-probed | unchanged |
| `func_80024028` | 284 | 45 | not re-probed | unchanged |

## Passed over with byte size (no new idea, would repeat a recorded failure)

`func_8001178C` 2,104 (556 words, 2,272 B — 168 B oversized; unresolved control flow),
`func_80012B7C` 1,576 (327), `func_800142E0` 2,400 (593, emits 2,100 — 75 words of logic missing),
`func_80015594` 1,488 (276), `func_8001D7E4` 1,656 (309, frame 0x20 vs 0x58),
`func_8001E33C` 2,360 (569), `func_80020E98` 2,108 (497), `func_800238C4` 1,580 (336),
`func_80024CE0` 1,652 (390), `func_800257FC` 1,372 (319), `func_80025FC4` 1,908 (274),
`func_800306B8` 2,104 (510), `func_800310C0` 2,424 (683, handwritten-ABI cluster — excluded by brief),
`func_80017378` (matched), `func_8002FB80` 544 (20), `func_8002A900` 220 (15),
`func_80024028` 284 (45), `func_800268C0` 236 (28), `func_8001CD50` 460 (46),
`func_8002B22C` 380 (66), `func_800300DC` 316 (69), `func_8002DDD4` 452 (78),
`func_8001272C` 540 (86), `func_8001D080` 764 (90), `func_8001BB64` 636 (101).

## Why the goal was not met

The brief anticipated the quota coming from MEDIUM/LARGE T2 functions fixed by *structural* corrections
(callee arities, types, global widths, reloads, shared indexes, struct views). I ran that audit across the
whole main T2 pool and it came back nearly empty: 73 main drafts, exactly **one** wrong `jal` count
(`func_8002E724`, 658 words off), **one** missing-globals case (`func_80012390`, 67 words off), and zero
cases where the target's global widths disagree with a *correct* C view. Every function that is within
reach by word count (≤22 words) is stuck on IDO register allocation or on a scheduling difference that no
statement ordering or declaration order reproduces — the same wall T-123, T-141, T-145, T-148 and T-149
hit from the other side. The two large functions whose drafts are provably structurally wrong
(`func_800306B8`, `func_8002E724`) need full 500–1,800-word rewrites; I started `func_800306B8` and did not
converge it in the time available.

## Files

`tools/scratch/nonmatching/T-152/func_80014D5C.c` (13 words, 1,780 B — best ever for this function),
`func_80023EF0.c` (12, 312 B), `func_8001BDE0.c` (8, 316 B), `func_8002FB80.c` (21, 544 B),
`func_800300DC.c` (69, 316 B), plus copies of T-149's best `func_8001D7E4.c` (309/1,656),
`func_800238C4.c` (336/1,580) and `func_80025FC4.c` (274/1,900) so the next worker finds them here.
Committed as `4cb5b3e`.
