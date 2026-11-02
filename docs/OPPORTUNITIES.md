# Decompilation opportunities ledger

Purpose: stop every worker from re-screening 168 T2 drafts. This file records, per function, what is
**close**, what was **tried and failed** (so it is not repeated), what was **passed over** by the
T-136..T-139 round, and which cross-cutting defects are likely hiding in the other drafts. A future
brief should say: *start from docs/OPPORTUNITIES.md, pick a bundle, claim it on the TRACKING board*.

Written 2026-10-29 by the lead from: the T-136/T-137 final reports (vetted), the running notes of
T-138 (**not yet final, not vetted; T-138's numbers are labelled "reports"**; T-139 is final and vetted), the T-136 uncommitted
drafts, and a fresh screen of every T2 draft on the merged tree (`d66b273`, M2 = 87,100 B), re-screened after the T-139 merge (M2 = 88,408 B).
Numbers in the tables are the lead tree's own `tools/permuter/screen.py` results, not worker claims,
except where a note says "reports".

## 0. Snapshot

Fresh screen, 168 T2 drafts (2 do not compile standalone: `func_8001D080`, `func_80021B6C`):

| Band (differing words) | Functions | Original bytes |
|---|---:|---:|
| 0–8 | 15 | 6,448 |
| 9–50 | 28 | 7,084 |
| 51–150 | 50 | 28,360 |
| >150 | 73 | 153,224 |

The 0.70% quota is 2,030 B. **Every band-0–8 and band-9–50 function is under 600 B except
`func_80017378` (1,752) (`func_800193DC` matched in T-148).** Reaching the quota from near-misses alone needs
several of them; reaching it from one function needs a >2 KB rewrite.

Ranges are the T-136..T-139 split (main at `0x80021B6C`, ovl_7DF8 at `0x801BBE88`) so bundles can be
handed out without overlap. A word count in parentheses `(prefix)` / `(declarations)` was measured with
the TU prefix or only TU declarations, because the full TU hits a declaration conflict; such a count is
**not trustworthy until the declarations are reconciled** (that reconciliation is itself a task).

Reproduce: `toolbox run -c kig-build bash -c 'make extract && .venv/bin/python tools/permuter/screen.py -j 8 --json /tmp/screen.json --output /tmp/screen.md'` (about 45 s).

## 1. Ready-made bundles (each ≥ 2,030 B)

These are the combinations I would hand out next. None is guaranteed: every function in A and B has
18+ reports of history, so the cheap searches are spent.

| Bundle | Functions (bytes, words off) | Total | Why this grouping |
|---|---|---:|---|
| **A: main near-misses** | `func_80017378` (1,752, 6), `func_8001BDE0` (316, 8), `func_8002A900` (220, 15), `func_8002FB80` (544, 20) | 3,640 | `193DC` matched in T-148. `17378` alone is 0.60%. |
| **B: ovl_7DF8 ≤7-word sweep** | `func_801C8004` (236, 6), `func_801B5534` (168, 2), `func_801BF720` (104, 2), `func_801BF914` (116, 2), `func_801C4E38` (556, 2), `func_801B695C` (268, 4), `func_801C224C` (372, 6),  | 2,504 | Eight functions, all within 8 words and exact size. `801BF720`/`801BF914` first need the declaration conflict in `ovl_7DF8_12C70.c` reconciled (true score unknown). `224C`, `BD270`, `BE540` were not touched by any worker this round. |
| **C: carousel pair** | `func_801B5DCC` (1,884), `func_801B5650` (1,916) | 3,800 | One recipe, two functions (similarity 0.885). **Latest (T-145): `5DCC` 11 words exact size, `5650` 30 words and 4 B oversize (T-141 had 15/31).** Remaining diffs: selected record pointer in `v1` vs `v0`; `-10.0f` and height-conversion FP temporaries swapped; card-pointer load scheduled after the height store; in `5650` an extra late unconditional branch from the `if (state != 5) {…} return result; return 0;` shape. Tried and failed: recompute record at final store (285 words), defer `-10.0f` into the state paths (1,928 B), early return of state 5 (99 words), narrowed index, field-offset pointer, local-region permuter with `--stack-diffs`. 1.31% on its own; needs a new idea for the record-pointer lifetime. |
| **D: 9–50-word band** | 28 functions, 7,084 B (§3) | 7,084 | The best bytes-per-effort pool once A–C are drained. |

If T-138's claimed matches are accepted (§8), several rows above disappear. Refresh the tables after vetting.

## 2. Near misses (≤ 15 words)

| Function | Bytes | Words off | Prior reports | Range | Notes |
|---|---:|---:|---:|---|---|
| `func_801B5534` | 168 | 2 | 10 | ovl ≤BBE88 | 2-word spill-slot difference. T-138: type, index, offset, explicit remainder, pointer-view probes. No gain. |
| `func_801C4E38` | 556 | 2 | 16 | ovl >BBE88 | Scored with TU declarations. Left: stack spill at +0x18 instead of +0x1C. T-139: selector/handler locals, branch-local state (moves spill right but frame grows 0x20→0x28), reusing an arg after last use. Chained-clear order was reversed to match relocation targets (no score change). |
| `func_8001BDE0` | 316 | 8 | 13 | main ≤21B6C | Differs only in which FP registers hold threshold and scale. T-136: argument/local layouts, comparison forms, loop forms, const-qualified constants, alternate 3rd-arg ABI (worse), for/do loops, separate fwd/rev cursors, 300 s permuter. None below 8. |
| `func_80032738` | 20 | 10 [emits 40] | 3 | main >21B6C | Handwritten-ABI cluster (see §5). |
| `func_8002A900` | 220 | 15 | 13 | main >21B6C | T-137: argument, loop, local-variable, type variants; sequence-loop rewrite search. No gain. |
| `func_80032750` | 60 | 15 [emits 44] | 3 | main >21B6C | Handwritten-ABI cluster (see §5). |

## 3. 16–50 words

| Function | Bytes | Words off | Prior reports | Range | Notes |
|---|---:|---:|---:|---|---|
| `func_801ADA04` | 208 | 18 | 6 | ovl ≤BBE88 |  |
| `func_8002FB80` | 544 | 20 | 10 | main >21B6C | T-137: cursor/pointer-order, address-byte and cursor variants; non-sequential output writes gave −1 word but unclear source, not kept. Decoder routine. |
| `func_801C0800` | 248 | 21 | 7 | ovl >BBE88 |  |
| `func_801B0520` | 328 | 22 | 9 | ovl ≤BBE88 | T-138: alternate frame/local views, no gain. |
| `func_801C8004` | 236 | 6 | 6 | ovl >BBE88 | T-139 reports 6 words (compound OR on the byte mask; one cursor for both scans). |
| `func_8003278C` | 92 | 26 [emits 104] | 3 | main >21B6C |  |
| `func_800268C0` | 236 | 28 (declarations) | 7 | main >21B6C | T-137: typed and aggregate dimension-copy variants, offset groupings: no gain. |
| `func_801B1210` | 284 | 28 | 15 | ovl ≤BBE88 | T-138: argument reuse, alpha types, command order, renderer return type: no gain. Clone-family sibling of the T-132 string recipe. |
| `func_801B446C` | 292 | 28 | 14 | ovl ≤BBE88 |  |
| `func_801C3758` | 564 | 30 | 12 | ovl >BBE88 |  |
| `func_80031050` | 112 | 30 (declarations) [emits 120] | 3 | main >21B6C | Handwritten-ABI cluster (§5). |
| `func_80032600` | 112 | 37 [emits 148] | 3 | main >21B6C |  |
| `func_801BBB60` | 292 | 40 | 12 | ovl ≤BBE88 | T-138 reports 29 (for-loop palette clears, split flag/buffer init). Unvetted. |
| `func_80032670` | 116 | 45 [emits 180] | 3 | main >21B6C |  |
| `func_800121C8` | 304 | 46 | 9 | main ≤21B6C | T-136: packed-input snapshot 47→46. |
| `func_801C2F5C` | 544 | 44 | 7 | ovl >BBE88 | T-139 reports 44 (readable statement split). |
| `func_80024028` | 284 | 49 | 7 | main >21B6C |  |

## 4. Larger rewrites

### 4a. 51–150 words (top 25 by bytes)

| Function | Bytes | Words off | Prior reports | Range | Notes |
|---|---:|---:|---:|---|---|
| `func_80014D5C` | 1780 | 135 (prefix) | 6 | main ≤21B6C | T-136: declaration-order search 136→135 (prefix, 1,140 compiles); full-TU alternative reconciles the three legacy declarations (139 words, stack frame 0x20 = target). Early-branch/setup region is where it diverges. |
| `func_801C4240` | 1344 | 126 | 9 | ovl >BBE88 |  |
| `func_801C3AA0` | 928 | 119 | 6 | ovl >BBE88 | T-139: fresh m2c + 600 s full-TU declaration/layout search: no gain at 119. |
| `func_8001D47C` | 748 | 134 (declarations) [emits 744] | 8 | main ≤21B6C |  |
| `func_801C1434` | 720 | 132 | 5 | ovl >BBE88 |  |
| `func_8001BB64` | 636 | 142 (declarations) [emits 632] | 9 | main ≤21B6C |  |
| `func_801C2ADC` | 600 | 71 | 6 | ovl >BBE88 |  |
| `func_801AFFAC` | 576 | 99 | 5 | ovl ≤BBE88 |  |
| `func_8002FDA0` | 572 | 107 [emits 556] | 7 | main >21B6C |  |
| `func_801BADEC` | 568 | 101 [emits 560] | 7 | ovl ≤BBE88 |  |
| `func_801B1DE4` | 556 | 111 | 6 | ovl ≤BBE88 | T-138 reports 111→15 (unvetted): reload `D_801D3098` after `func_801B19F0`/`func_801AF5EC`, flag store ordering, incremented-frame local. |
| `func_801C49A8` | 548 | 83 | 10 | ovl >BBE88 |  |
| `func_8001272C` | 540 | 103 [emits 544] | 6 | main ≤21B6C |  |

### 4b. >150 words (top 30 by bytes)

| Function | Bytes | Words off | Prior reports | Range | Notes |
|---|---:|---:|---:|---|---|
| `func_8001EC74` | 8740 | 2175 (declarations) [emits 8476] | 3 | main ≤21B6C |  |
| `func_8002BBD0` | 7668 | 1843 [emits 7692] | 5 | main >21B6C |  |
| `func_8000FA80` | 7436 | 2014 (prefix) [emits 8148] | 4 | main ≤21B6C |  |
| `func_801B6E4C` | 5712 | 1417 (declarations) [emits 5652] | 3 | ovl ≤BBE88 |  |
| `func_801ADEA0` | 5508 | 1349 (prefix) [emits 5524] | 3 | ovl ≤BBE88 |  |
| `func_801B849C` | 5296 | 1267 (declarations) [emits 5312] | 2 | ovl ≤BBE88 |  |
| `func_80026B38` | 4708 | 1182 [emits 4792] | 5 | main >21B6C |  |
| `func_80019880` | 4456 | 1297 (declarations) [emits 5216] | 3 | main ≤21B6C |  |
| `func_801CAA00` | 3992 | 992 (declarations) [emits 3884] | 5 | ovl >BBE88 |  |
| `func_801ABB20` | 3644 | 658 (prefix) [emits 3576] | 3 | ovl ≤BBE88 |  |
| `func_801B47A4` | 3472 | 862 (prefix) [emits 3260] | 3 | ovl ≤BBE88 |  |
| `func_80028A00` | 3340 | 802 (declarations) [emits 3264] | 3 | main >21B6C |  |
| `func_801C9B14` | 3184 | 629 (declarations) [emits 3140] | 3 | ovl >BBE88 |  |
| `func_801C5298` | 3036 | 741 (declarations) [emits 3000] | 4 | ovl >BBE88 |  |
| `func_8002E724` | 2832 | 658 [emits 2728] | 5 | main >21B6C |  |
| `func_801BC1B0` | 2496 | 624 (declarations) [emits 2320] | 3 | ovl >BBE88 |  |
| `func_800310C0` | 2424 | 683 (declarations) [emits 2744] | 2 | main >21B6C |  |
| `func_800142E0` | 2400 | 593 (declarations) [emits 2100] | 4 | main ≤21B6C |  |
| `func_801C5E74` | 2392 | 527 | 4 | ovl >BBE88 | T-139: boot DMA / inflate / audio-call arities and flag reloads corrected, then 557→504–527 words. Frame 0xB0 vs target 0xE0; one stale-flag draft hits size+frame at 504 (git history of T-139 branch). |
| `func_801BFCBC` | 2388 | 596 (prefix) [emits 2084] | 2 | ovl >BBE88 |  |
| `func_8001E33C` | 2360 | 571 (declarations) [emits 2412] | 4 | main ≤21B6C |  |
| `func_801C08F8` | 2296 | 561 [emits 2216] | 3 | ovl >BBE88 |  |
| `func_80020E98` | 2108 | 497 (prefix) [emits 2076] | 4 | main ≤21B6C |  |
| `func_800306B8` | 2104 | 510 [emits 2096] | 4 | main >21B6C |  |
| `func_8001178C` | 2104 | 570 (prefix) [emits 2296] | 5 | main ≤21B6C |  |
| `func_801B5650` | 1916 | 423 [emits 1924] | 4 | ovl ≤BBE88 | See `func_801B5DCC`. |
| `func_80025FC4` | 1908 | 454 [emits 1896] | 3 | main >21B6C |  |
| `func_801B5DCC` | 1884 | 386 | 4 | ovl ≤BBE88 | **Carousel pair with `func_801B5650` (3,800 B together, ≈1.31%).** T-138 reports 386→155 words (unvetted) by fixing `func_801AFA48` arity (it takes ONE integer arg; the draft passed four), three state reloads after helper calls, card-record stride (4-byte height / 8-byte rotation tables), grouped carousel-frame local (recovers the 0x38 frame). Same recipe applied to `func_801B5650`: 423→271. Still 155/271 words off. |
| `func_801C23C0` | 1820 | 189 [emits 1812] | 4 | ovl >BBE88 | T-139: 222→189 (frame 0x90 vs 0x70). Duplicate late constants: ownership of the rodata float pairs must be reconciled before promotion. |
| `func_801BCB70` | 1676 | 391 | 3 | ovl >BBE88 |  |

Everything else >150 words is a straight rewrite from m2c output; `func_8001EC74` (8,740 B),
`func_8002BBD0` (7,668), `func_8000FA80` (7,436) and `func_80021B6C` (6,896) are the largest and cannot
be matched in one pass; they are only worth attacking as multi-day tasks. The two ovl_7DF8 mega-drafts
`func_801B6E4C` (5,712) and `func_801ADEA0` (5,508) are in the same class.

## 5. Not obviously C: the handwritten-ABI cluster

`func_80032738`, `func_800326F0`, `func_80032750`, `func_8003278C`, `func_80031050`, `func_80032600`,
`func_80032670`, `func_80032504` (824 B together) plus the two large ones tagged `Handwritten function` by
splat, `func_80031DD0` (1,420) and `func_800327E8` (1,092). T-026 found they use native 64-bit
`daddiu`/`sd`, trapping `addi`, private temporaries that survive calls, and decoder state carried in
`t4-t8/fp`. IDO -O2 -mips2 cannot emit that from C. I excluded this cluster from T-137's brief and nobody
looked at it this round.

This is a **policy question, not a decompilation job**: treat them as handwritten asm and exclude them
from the eligible total (as the 169 ovl_7E00 functions were, FU-9), or keep them as T2 forever.
Needs a user decision before anyone spends time.

## 6. Cross-cutting defects hiding in other drafts

These are the findings that paid off this round. They are systematic, so each is worth one automated
pass over all drafts instead of being rediscovered function by function.

1. **Wrong callee arity.** m2c guessed arities and drafts passed extra arguments, sometimes to keep a
   value live across the call. Real cases: `func_801AFA48` takes **one** integer (drafts passed four:
   `func_801B5DCC` 303→157 words, `func_801B5650` 323→272); `func_8002F6DC` takes one voice arg
   (`func_801BB7B4`); boot DMA / inflate and the audio call in `func_801C5E74`.
   `tools/analysis/draft_arity.py` lists every draft call whose argument count differs from an existing
   C definition. **It is a lead generator, not proof:** a matched C function may simply ignore trailing
   arguments the caller really does set (`func_8001B620` is defined with 2 params but the original
   caller sets 4). Check the caller's asm. 23 flags in 14 drafts at the time of writing, including
   `func_801BFCBC` (2,388 B), `func_801C5298`, `func_801C23C0`, `func_8001E33C`, `func_800170C4`,
   `func_8001178C`, `func_801CAA00`, `func_801ACB1C`, `func_8000FA80`.
2. **Globals cached across calls.** m2c hoists a global into a temp before a call; the original reloads
   it afterwards. Found in `func_801B1DE4` (`D_801D3098` after `func_801B19F0` / `func_801AF5EC`),
   `func_801B5DCC` / `func_801B5650` (`D_802C8D06` after helper paths), `func_801C5E74` (flag reloads).
   Look for a `lw`/`lbu` of the same address after a `jal` in the asm. Not yet audited elsewhere.
3. **Integer widths and signedness.** Narrow argument types where the original uses the whole register
   (`func_80025D58`: 146→1 word together with the loop-bound fix); unsigned vs signed global decides `cvt` vs unsigned conversion
   (`func_8002AB90`: `D_80068168` is `u32`).
4. **Float constants as globals.** Drafts that read an `f32` from a `D_8004xxxx` symbol often want an
   inline literal, which lets IDO pick the FP registers (`func_801C9698`, `func_800193DC`:
   `(802.0f)` / `(1551.0f)`). Check each draft's `D_` floats against the rodata.
5. **Declaration order and scalar placement set stack slots.** `func_80025D58` needed its scalar row
   locals declared before the two copied tables. `tools/permuter/declorder.py` automates it; it corrected the second table's slot in `func_80025D58`
   but found nothing on `func_80014D5C` (1,140 compiles), so budget it.
6. **Store order inside command pairs and statement splitting.** `func_800269AC` matched after writing the
   environment command's first word before its second; `func_801C2F5C` and `func_801BBB60` improved just
   from splitting a one-line statement. IDO schedules from statement boundaries.
7. **Shared scalar reuse.** `func_8002F45C` matched with one scalar used first for the priority
   adjustment and later as the 6000-cent base. A dead assignment would be an artificial construct; a
   shared *used* scalar is not.
8. **Record strides.** The carousel functions use a 4-byte height table and an 8-byte rotation table
   indexed separately; sharing one intermediate index cost ≈25 words.

Unreconciled declaration conflicts block honest scoring of: `func_801BF720`, `func_801BF914`,
`func_801C4E38`, `func_801B695C`, `func_801C85C0`, `func_8001373C`, `func_800268C0`, `func_80031050`,
`func_80015450`, `func_80023EF0`, `func_80024714`, `func_801BE790`, `func_800245B4`, `func_801C3E40`,
`func_80026738`, `func_8001CD50`. Reconciling them (headers, not matching) is cheap and unlocks real
scores; it is the first step of Bundle B.

Rodata ownership still open: `func_801C23C0` has duplicate late float constants whose owner must be
decided; `func_801C9698` is done. The
string-pool recipe (`force_migration` / `force_not_migration`, T-115/T-123/T-126/T-132; whole-range move
at `0xE7BF0` by T-139) is documented in `tools/scratch/nonmatching/T-043/REPORT.md`.

## 7. Rules that held, and dead ends to skip

- Permuter output containing `if (0) {}`, empty branches or dead temporaries was rejected by T-137 and
  by T-138 (on `func_801BA884`). Always read the winning candidate before using it.
- T-138 reports `func_801BA884` matched via "a real do-once block that conditionally exits". **Look at
  that carefully when vetting** — it is the one claim this round that could be an artificial construct.
- Do not retry (already exhausted): the 2,048 loop-boundary layouts and 600 s permuter on
  `func_80017378`; declaration-order searches on `func_80014D5C` (two, to 135/139 words) and
  `func_801BAA78` (900 s, stuck at 15); 840 + 1,680 + 1,728 field/flag orderings on `func_8002F45C`
  before the shared-scalar fix; const-qualified constants and alternate third-arg ABIs on `func_8001BDE0`.
- Lower-threshold clone screen (0.70) found **no further T2 clone cluster in main** (T-136, T-137). The
  only unmatched clone family is the carousel pair. `docs/clones.md` is stale (it still lists the six
  536-B `func_801B2EF4` clones, all T4 now).
- The two screening errors (`func_8001D080`, `func_80021B6C`) are draft-declaration problems, not
  codegen: duplicated `extern`s and a `T022Sprite` typedef the screen cannot see.

## 8. Worker claims awaiting vetting (do not count these)

**T-139 is final and vetted (2026-10-30):** `func_801C7F90` 116, `func_801C2ADC` 600, `func_801C85C0` 168, `func_801CC908` 424 and, after being resumed, `func_801C9698` 1,148 are T4 (2,456 B total; M2 now 89,556 B, 30.89%); those rows were removed from §2–§4. `func_801C9698` was fixed by sharing one variable between the row alpha and the text pointer (the stack slot was the whole difference). Its last notes: `func_801C224C` declaration reconciled (full TU, still 6 words); `func_801C4E38` still 2. Only T-138's claims below are outstanding.

T-138 is final and vetted (2026-10-30). Four of its five claimed matches are in (`func_801BB464` 304, `func_801B677C` 480, `func_801B6528` 596, `func_801B43A8` 196 = 1,576 B). The fifth is **rejected**:

| Worker | Function | Bytes | Claim |
|---|---|---:|---|
| T-138 
T-138's branch (`t3/t-138-ovl-7df8-matches`) also holds improved
non-matching drafts (e.g. `func_801B1DE4` at 15 words, `func_801BAA78` at 15, carousel pair at 155/271).
When its final report is vetted, update §1–§4. T-139's improved drafts (`func_801C9698` 2, `func_801C8004` 6, `func_801C23C0` 189) are already in the tree.

## 9. What the four workers each passed over

| Worker | Matched (vetted) | Passed over for something else |
|---|---|---|
| T-136 | `func_80018F20` 696, `func_8001808C` 808, `func_80018AE0` 912 | `func_80017378` (1,752 B, 6 words) and `func_8001BDE0` (316, 8) were its first targets and consumed most of its first run without moving; abandoned for the stage-init functions. `func_800193DC` (808 B, 7 words) was left on the table unfinished. `func_80014D5C` (1,780), `func_80015450`, `func_800121C8`, `func_8001373C` only improved by 1–5 words. |
| T-137 | `func_80025D58` 620, `func_800269AC` 236, `func_8002F45C` 404, `func_8002AB90` 852 | `func_8002B22C` (380 B, 66 words, size exact), `func_8002FB80` (544, 20), `func_8002A900` (220, 15), `func_800268C0` (236, 28). Scanned the whole `>0x80021B6C` range for clone families: none. |
| T-138 | (claims, §8) | `func_801B5534`, `func_801B6528`, `func_801B695C` (all ≤4 words, 168–596 B) abandoned after probes; `func_801BADEC` (568 B, 100 words), `func_801B0520`, `func_801B1210` not improved. |
| T-139 | `func_801C7F90` 116, `func_801C2ADC` 600, `func_801C85C0` 168, `func_801CC908` 424 (2,456 B total with `func_801C9698` 1,148) | `func_801C4E38` (556 B, 2 words) abandoned; `func_801C3AA0` (928 B, no gain from fresh m2c + 600 s search), `func_801C2F5C` (544, 44 words) and `func_801C8004` (236, 6 words) not finished. Never touched `func_801C224C`, `func_801BD270`, `func_801BE540`, `func_801C47E0`, `func_801BD200` (together 1,428 B at ≤14 words). |

The consistent pattern: workers abandon a ≤8-word near-miss after a few hundred compiles, because a
mid-sized function that needs a *structural* fix (wrong arity, stale reload, narrow type) turns into a
full match faster. That is the right call under a hard quota, but it leaves the near-misses to a task
that is dedicated to them.

## 10. T-141 round (stopped by the user 2026-10-31, 196 B landed)

Matched: `func_801C48E4` (196 B; `u16` dimension args, `u32` callee args). Full table of 25 functions with start/best words is in `tools/scratch/nonmatching/T-141/NOTES.md`. Highlights for the next brief:

| Function | Bytes | Before → best words | Note |
|---|---:|---|---|
| `func_801BEEA4` | 344 | 39 → 16 | shared insertion index and position scalar; best new mid-size lead |
| `func_801C11F0` | 580 | 113 → 90 | separate intensity scalar restored the 580 B size; frame and registers still differ |
| `func_801C47E0` | 260 | 11 → 10 | bank value reused for the transfer length |
| `func_801BADEC` | 568 | 100 → 99 | shared vertical offset |
| `func_801BF720`, `func_801BF914` | 104+116 | → 2 each (full TU now) | declaration conflict reconciled (`u32` params); 2 words left, many forms tried |
| `func_801B695C` | 268 | → 4 (full TU) | frame 0x28 vs spill slots trade-off |
| `func_801C5298` | 3,036 | 741 → 738 | declaration diagnostic: `func_801C48E4` takes 3 args, `func_800131A4` 6; needs full-TU reconciliation |
| `func_801AD114` | 628 | 88 | correcting two no-arg callees gave 123 words / 608 B: target keeps argument setup through call branches |
| `func_801C49A8` | 548 | 83 | correct reload variant scored 108: old draft caches a global across a call |

Pattern: the one match came from argument and callee *types* (narrow inputs, unsigned callee params), not from scheduling. Near-misses at ≤15 words resisted all structural variants; the T-141 worker burned five resumes on them for 0 B.


## 11. T-140 round (main, 2,060 B landed, vetted 2026-10-31)

Matched: `func_8001373C` 256, `func_80017A68` 772, `func_8001AA90` 496 (includes the 8-byte empty callback at `0x8001AC78`, named `D_8001AC78` in the C), `func_8002D9C4` 536. Causes: two globals were really `u8` and `func_8001AC80(15, 23)` was called with its original arguments (80017A68); squared-distance expression and narrow `s16` impulses (8001373C); integer inputs cast at each use and operand order of the interpolation (8002D9C4); declaration order of the locals (8001AA90). The worker's first text used a `savedAngle = angle` copy purely to move the spill slot; the lead replaced it with the declaration order `sine, cosine, period, angle` (24 orders searched; two match) and plain `while` loops.

Improved but not matching (full-TU words from the worker's report; remeasure before use):

| Function | Bytes | Words | Note |
|---|---:|---:|---|
| `func_80024714` | 712 | 6 | **best new near-miss in main** |
| `func_8001CD50` | 460 | 32 | |
| `func_80024028` | 284 | 45 | |
| `func_800268C0` | 236 | 28 | reconciled to full TU |
| `func_800300DC` | 316 | 69 | |
| `func_8002DDD4` | 452 | 79 | |
| `func_80026738` | 392 | 81 | |
| `func_800191F0` | 492 | 109 | declarations context |
| `func_800170C4` | 692 | 136 | now full TU |
| `func_80014D5C` | 1,780 | 322 | full TU, 4 B size deficit |
| `func_8001E33C` | 2,360 | 569 | declarations context |

Passed over (bytes, words): `func_80017378` 1,752/6, `func_800193DC` 808/7, `func_8001BDE0` 316/8, `func_8002A900` 220/15, `func_8002FB80` 544/20, `func_8002B22C` 380/66, `func_8001BB64` 636/142, `func_8001D47C` 748/134, `func_80030440` 632/144, `func_8001272C` 540/103, `func_8002FDA0` 572/106, `func_800297A4` 780/180, `func_800121C8` 304/46, `func_80015450` 324/40 (prefix), `func_8001D080` 764/175. Same lesson as T-141: the near-misses at ≤8 words did not move again; the matches came from correcting types and arguments in mid-size drafts. Next brief for main: start with `func_80024714` (6 words).


## 12. T-142 round (main near-miss bundle, 2,464 B landed, vetted 2026-10-31)

Matched: `func_80024714` 712 B (resource address as base plus little-endian offset bytes `p[4] + (p[5]<<8) + (p[6]<<16) + (p[7]<<24)`, padded resource view, integer casts) and `func_80017378` 1,752 B (a single shared index across the model and rotation arrays gave the original pointer updates; the callee `func_8001B620` is called with 2 args). The scheduling sweeps of three earlier workers had missed both: **the 6-word near-misses were fixed by changing what the code computes, not how statements are ordered.** Passed over: `func_800193DC` 808, `func_8001BDE0` 316, `func_8002A900` 220, `func_8002FB80` 544, `func_8002B22C` 380 (no new scores reported).


## 13. T-144 round (main high half, 2,048 B landed, vetted 2026-10-31)

Matched: `func_800253D0` 1,068 B (HUD display-list routine; use the current sprite slot for lookups and calls; the Gfx typedef moved earlier in main_15380.c), `func_80030440` 632 B (glyph RLE decoder: run loop advances `x` by `n - 1` inside a `for` whose increment advances the last pixel; padding `for` loops), `func_80030220` 348 B (index advances by three vertices, `guRandom() & 15` jitter, operand order). Improved but not matching: `func_80023EF0` 67 → **12 words** (best new main near-miss), `func_8002DDD4` 79 → 78, `func_8002FDA0` 106 → 81. Investigated and passed over: `func_80024028` 284, `func_80026738` 392, `func_800268C0` 236, `func_800297A4` 780, `func_800300DC` 316, `func_8002E150` 844, `func_800310C0` 2,424, `func_80031A38` 920, `func_80032360` 420.


## 14. T-147 round (ovl_7DF8 high half, 2,432 B landed, vetted 2026-10-31)

Matched: `func_801C80F0` 1,232 B (packed-name addresses corrected, name-table selector reloaded after `sinf`, shared selection branch) and `func_801C90D4` 1,200 B (direct fade-array expressions, full-width unsigned red conversion). Improved but not matching (differing words / bytes): `func_801C17D0` 102/448, `func_801C1990` 104/676, `func_801C23C0` 181/1,820, `func_801C317C` 215/936, `func_801C3758` 28/564, `func_801C4240` 90/1,344, `func_801C49A8` 44/548 (preserves the reloads the original has), `func_801C5298` 610/3,036. Passed over: `func_801BD200` 112, `func_801BD270` 396, `func_801BE540` 288, `func_801BE660` 300, `func_801BE790` 384, `func_801C0800` 248, `func_801C224C` 372, `func_801C2F5C` 544, `func_801C3AA0` 928, `func_801C3E40` 504, `func_801C7310` 1,276, `func_801C8004` 236, `func_801CC3BC` 360. Worker notes with the per-function analysis are in `tools/scratch/nonmatching/T-147/NOTES.md`.


## 15. T-146 round (ovl_7DF8 low half, 2,620 B landed, vetted 2026-10-31)

Matched: `func_801AD114` 628 B (real no-argument callees, byte-width player index, value lifetime of the selection global), `func_801AD7D8` 556 B (graphics-task submit: `rspboot_end` and `D_800427E0` are two symbols at the same address, the end of the boot microcode and the start of the graphics microcode, as in the SDK's `rspbootTextEnd`/`ucodeTextStart`; `symbol_addrs` has `allow_duplicated:True` for both), `func_801B6BD8` 628 B (direct count accumulation, `(u8)(255 - x)` byte colour expressions, local declaration order), `func_801BBE88` 808 B (display-list drawing; the lead folded the worker's two cursors and `p1 = *arg0; *arg0 = p1 + 1` into plain `(*arg0)++`, still matching). Improved but not matching: `func_801B2B8C` 872 B at **8 words** (best new ovl near-miss; the draft keeps the original completed-animation path's uninitialized alpha read), `func_801B0668` 984 B at 114, `func_801BBB60` 292 B at 26. Passed over: `func_801B5534` 168, `func_801ADA04` 208, `func_801B0520` 328, `func_801B1210` 284, `func_801B446C` 292, `func_801BBC84` 516, `func_801AFFAC` 576, `func_801BADEC` 568, `func_801ACB1C` 744, `func_801B1A7C` 872, `func_801B3DB0` 1,360.


## 16. T-143 round (main low half, 2,296 B landed, vetted 2026-10-31)

Matched: `func_80015450` 324 B (indexed 40-object loop, full-width kind snapshot, typed views), `func_80016078` 480 B (display-list setup; a `FILL_RECTANGLE_COMMAND(pkt, …)` macro evaluates `g++` once), `func_800170C4` 692 B (indexed vertex-copy and object-update loops, compound speed update), `func_80017D6C` 800 B (direct indexed transform-array access, stage-part view for indices 0 and 23, float literals). Improved but not matching (full-TU words / bytes; drafts copied into the tree from the worker's uncommitted work): `func_80014D5C` **14**/1,780 (best new main near-miss: ~1.8 KB), `func_800121C8` 22/304, `func_80012390` 67/476, `func_8001272C` 86/540, `func_8001BB64` 98/636, `func_8001CD50` 46/460, `func_8001D080` 74/764, `func_8001D47C` 134/748, `func_8001346C` 166/704, `func_8001DE5C` 155/600, `func_8001E33C` 522/2,360 (needs player-index cleanup). Passed over: `func_8000FA80` 7,436, `func_8001178C` 2,104, `func_80012B7C` 1,576, `func_800142E0` 2,400, `func_80015594` 1,488, `func_800191F0` 492, `func_80019880` 4,456, `func_8001D7E4` 1,656, `func_8001EC74` 8,740, `func_80020E98` 2,108, `func_800216D4` 1,032, `func_80021B6C` 6,896.


## 17. T-145 round (ovl_7DF8 near-miss bundle, 2,172 B landed, vetted 2026-10-31)

Matched: `func_801B695C` 268 (a two-dimensional texture-buffer view instead of one overloaded offset), `func_801BA884` 500 (shared counter pointer `counter = &D_801F39EC`, separate `x0/x1/y0/y1` positions as in the sibling draw routines `func_801BA674` etc., result assigned once; the lead tested a single Y local and inlined expressions: both break the match, so the two identical Y computations are real family structure, not a trick), `func_801BEEA4` 344 (typed score entries `{data, u16 score}`, descending copy cursor with `memcpy`), `func_801BF720` 104 and `func_801BF914` 116 (single result variable assigned in the letter branch and the switch, one return), `func_801C11F0` 580 (byte casts, shared phase reads, declaration order), `func_801C47E0` 260 (SDK TLB prototypes, two-stage page-offset calculation). Still open in this bundle: carousel `func_801B5DCC` (1,884 B, 11 words), `func_801B5650` (1,916 B, 30 words, 4 B oversize), `func_801B1DE4` (556 B, 13 words), `func_801BAA78` (884 B, 14 words). Worker notes in `tools/scratch/nonmatching/T-145/` (if present) and the T-141 notes.

## 18. T-148 round (near-miss bundle 2, SHORT: 808 B landed, vetted 2026-11-01)
Matched: `func_800193DC` 808 B (chained assignment of the four equal bytes in `D_80061520`, sequential `D_80061CB8` bytes, float literals; raw-offset store style like its T-136 siblings, so FU-13 cleanup applies).
Not matched, with the worker's evidence (all in `tools/scratch/nonmatching/T-148/NOTES.md`): `func_80014D5C` 14 words in the full TU (three address-register choices, two zero stores around the division checks; indexed views, chained init and a colour struct all failed; the full-TU draft needs `D_8004A264` as `s32` cast to pointer), carousel `801B5DCC` 11 words / `801B5650` 30 words (simpler draft without `next`), `801B2B8C` 8 words (global-address registers, 940+180 s permuter unchanged), `801BBB60` 292 B 26 -> 11 words, `80023EF0` 12 -> 10 words (real y snapshot), `800268C0` 28 -> 26, `801B1DE4` 13 words (target passes old frame before incrementing; post-increment forms emit 552 B), `801BAA78` 14 words, `8001BDE0` 8 words, `801C8004` honest 16-word/236 B form.

## 19. T-149 round (near-miss bundle 3, SHORT: 372 B, vetted 2026-11-01)
Matched: `func_801C224C` 372 B (the stage byte is re-read into a real local after the init calls, which may change the global; no matching-only locals). Later drafts: `func_801C4240` 64 words, `func_800238C4` 336, `func_8001178C` 556 (see NOTES). Merged corrections: `D_80061490` is `u16`, `D_8012834B` is `u8`, real prototype for `func_80015594`, `T032Bank`/`D_8004D278` declared before `func_8001D7E4`. Draft progress (full TU, in `tools/scratch/nonmatching/T-149/`): `func_801C4240` 90 -> 64 words (typed view of the adjacent victory-scene fields), `func_801B0CDC` 202 -> 155 (integer `/ 2` gives the target `div.d`), `func_80015594` 305 -> 276 (200-command buffer type, u32 horizontal step), `func_801B3DB0` 278 words (callee arities: `801B446C`/`801B5534` take one arg, byte second param), `func_801B9A04` 404 (target reloads `D_8004A4B0` after each `guRandom` and `D_802C9F64` after `func_801ADE48`; integer 3-component coordinate), `func_8001D7E4` four call-arity errors fixed in the draft (`24144(player, arg1)`, `241BC`/`24714` one arg, `1DE5C` three, `310C0`/`31A38` one), `func_800257FC` 337 -> 319. Unchanged: `801B5534` 2, `801C4E38` 2, `801BE540` 8, `801C23C0` 181.

## 20. T-152 round (main, SHORT: 0 B, vetted 2026-11-02)
No match, no source change. Worker audit of the 73 main T2 drafts (jal counts, frame sizes, referenced globals, access widths): one wrong `jal` count (`func_8002E724`, 658 words), one missing-globals case (`func_80012390`, 476 B, 67 words: target reads the archive through absolute literals `D_80300004..7`), no width mismatches. Best words: `func_80014D5C` 13 (was 14), `func_8001BDE0` 8, `func_80023EF0` 12, `func_8002FB80` 21 (exact size, 98-word prefix), `func_800300DC` 69 (target walks the parameter as cursor), `func_800121C8` 22. Large drafts need rewrites: `func_800306B8` (draft frame 0xD8 vs target 0x50), `func_800142E0` (75 words of logic missing), `func_80015594` (target is a leaf; draft saves `ra`). The worker claimed `func_80014D5C`'s remaining diffs are rodata-literal false negatives in `screen.py`, but its own note says the linked image differs at 0x1b0, 0x1b4, 0x1bc, 0x530-0x558 (the address-register choices and the zero stores around the division checks that T-148 also recorded), so I treat it as unproven and not a match. Notes: `tools/scratch/nonmatching/T-152/NOTES.md`.

## 21. T-153 round (ovl mid-size, SHORT: 684 B, vetted 2026-11-02)
Matched: `func_801BE540` 288 B (the loop pointer is assigned inside `if (*text)`, not at its declaration; multiplier order `10.0f * glyph->width * scale`; the lead moved the `glyph` address computation out of the condition and it still matches), `func_801BD270` 396 B (the `u16` button field is masked at the 64-bit add: `result += buttons & 0xFFFF`, otherwise IDO sign-extends the half). Improved drafts: `func_801B3DB0` 278 -> 261 words (direct `D_802C8C30[i][col]`/`D_802C8C60[i][col]` stores), `func_801C4240` fresh draft, carousel 11/30 unchanged. The worker says the permuter reached 0 on several near-misses only through forbidden constructs (copies, `volatile`, `do{}while(0)`), which it discarded. Not attempted: `func_801BCB70` (1,676 B, draft frame 0x1b0 vs target 0x138) and `func_801BDF94` (1,452 B, 0x130 vs 0x140): straight m2c output with 300+ words off; they need clean-room rewrites from the asm and total 3,128 B. Helper scripts (measure, batch, cmp, wordiff, regs, callset, stmtorder) are in `tools/scratch/nonmatching/T-153/`; the 250 throwaway variant dirs were not merged.

## 22. T-151 round (ovl large drafts, 2,096 B landed, vetted 2026-11-02)
Matched: `func_801CC3BC` 360 B (pak-error strings C-owned as `D_80295560..F8`; connected-pak byte read into a real local after `func_801CBF8C()`; the test is `(current == 0) & (1 << arg1)`, which looks like a bug-for-bug copy of the original), `func_801CD1F0` 460 B (`for (i..)` over `list[i]`, `names` cursor, `str[16] = str[17] = str[18] = ' '`, C-owned `"jEMPTY"`), `func_801C7310` 1,276 B (98 credits strings and the float pool C-owned, ROM rodata identical; switch with bodies t, c, h, g, default; `idx` reset then one read).
Match-only constructs, all lead-tested: `scale = 1;` (int literal) in the default arm (`1.0f` costs 8 B); `text = (u8 *)((u32)D_802921E0[i]);` in the `'g'`/`'h'` arms (dropping it, or dropping the `u32` cast, breaks the ROM); `volume = D_802D39C0;` per branch (once before the branch breaks the ROM). Accepted as disclosed, queued under FU-13 for a cleaner spelling.
Not matched: `func_801C5E74` (2,392 B; exact frame/slots/size, ~500 of 596 instructions equal; blockers: IDO shares the `D_802D3980` address between the null test and the store while the target does not, and `flags & 2` is recomputed), `func_801C8004` best honest form 16 words. Untouched, hundreds of words off: `801C5298`, `801BFCBC`, `801BC1B0`, `801C08F8`, `801C9B14`, `801CAA00`, `801ABB20`, `801ADEA0`, `801B47A4`, `801B6E4C`, `801B849C`. Notes: `tools/scratch/nonmatching/T-151/NOTES.md`; the worker deleted the three consumed T-021/T-030/T-034 drafts.

## 23. T-154 round (ovl 116E0 text/menu file, 2,444 B landed, vetted 2026-11-02)
Matched (all in `ovl_7DF8_116E0.c`): `func_801BDF94` 1,452 B, `func_801BD3FC` 580 B (uses the u64 parameter and `D_802D3678[player]` directly, reloaded each time, no copies), `func_801BE660` 300 B (`x -= width / 2` with an int literal gives `div.s`), `func_801BD200` 112 B (`D_80282A60 = D_800684A0;` then compare against the stored global).
Match-only spellings, lead-tested: in `func_801BDF94` `s32 *tick = &D_80282DC0` (the T-145 counter-pointer trick; keeps IDO from sharing the global's address), one shared `f64 width`, the `sine` local, declaration order, and `g->w0 = ..; g->w1 = ..;` joined on one line for the `D_802D36C0` / `D_80282D28` commands. In `func_801BD3FC` the two discarded statements `input >> 32; input >> 16;` are needed: removing them breaks the ROM because the target really calls `__ull_rshift` twice (dead-result shifts, kept under FU-13). The lead hoisted the `glyph = &D_80282C48[character]` assignment out of the condition (still matches). `func_8002B6EC` is declared `()` because `func_801BD200` passes no argument and `func_801BD270` passes one.
Improved, unmatched: `func_801BD640` 1,068 B (191 words -> only temp-register numbering in the colour pack differs: target t9, draft t7; `T-154/wd640/i.c`), `func_801BDA6C` 1,320 B (289 -> 70 words, frame 240 vs 216; `T-154/wda6c/a.c`), `func_801C5E74` (the pointer view removes the `D_802D3980` sharing but now `D_80291FE8` is shared and `dc` is rematerialised; `T-154/w5e74/ptr1.c`). Passed over: `func_801B5534`, `func_801C4E38` (spill slot sp+0x18 vs 0x1C, one local and a nested-block local did not move it). Notes and tools: `tools/scratch/nonmatching/T-154/`.
