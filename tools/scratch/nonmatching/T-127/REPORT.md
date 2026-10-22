# T-127 — sol-C47

No new T4 functions: **0 B / 289,876 B (0.00%)**, short of the 2,030 B target.
Seven valid nonmatching drafts improved; no src, symbol hints, YAML, compiler flags,
shared tools, tracking, worklog, inventory overrides, or ROM inputs were changed.

## Method and bounds

Read CONTRIBUTING, the T-127 tracking row and follow-ups, recent worklog, permuter
README, and prior per-function REPORT entries. Baseline and final builds use the
`kig-build` toolbox and the lead's shared toolchain symlinks. The shared ext lacked
decomp-permuter, so the search checkout and extra Python dependencies were put
under /tmp, without changing tools/ext or .venv.

All 25 assigned functions received a bounded permuter pass. 80023EF0 and 800245B4
needed the screener's audited declaration fallback; all other searches imported
TU prefixes. Independently measured candidates in the full TU first, then prefix,
then declaration fallback, as reported in measurements.json. Weighted permuter
scores were never treated as actual differing-word counts or T4 proof.

Additional directed experiments covered table/address views, renderer coordinate
snapshots and direct 2-D tables, video mode control/assignments, glyph character
snapshots and cursor scopes/types, insertion-index lifetime and copy-source
snapshots, argument ABI/array views, palette/control loops, and floating-point
accumulation/declaration orders. Bounded declaration/layout searches:
801BE790 180 s (756 compiles), 801BE540 180 s (966 compiles), and 801BEEA4 180 s.
The final font-only permuter search was capped at 300 s. The five bounded
permuter runs logged 20,397 total iterations; candidates were reviewed and
independently measured rather than accepted by weighted score.

Rejected candidates with empty conditionals, dummy padding/volatile, uninitialized
pointers, pointer substitution that changed traversal, a narrowed rendering Y,
and moving graphics-task stores across osWritebackDCacheAll. Disabled destructive
or artificial mutation passes for later runs, but still reviewed every retained
candidate. No such constructs were promoted or saved in the drafts.

## Results by function

Counts include missing/extra words. Before values are from the supplied screen
(or the newer T-123 draft for 801B5534). Unchanged rows retain the input draft;
weighted-score changes that did not survive review/measurement are excluded.

| Function | Words before → final | Final draft bytes / target | Work / remaining diagnosis |
|---|---:|---:|---|
| func_801AD114 | 88 → 88 | 612 / 628 | Bounded search; menu-branch/callback lifetimes and four missing instructions remain. |
| func_801AD7D8 | 89 → 89 | 548 / 556 | Bounded search; 38-word candidate moves code-pointer store before cache flush, rejected. Cursor/microcode-address rematerialization remains. |
| func_801BA884 | 86 → 86 | 496 / 500 | Tested first-Y snapshot, scale width, coordinate evaluation order and direct 2-D image refs. Lower raw scores narrow Y or add padding; rejected. |
| func_801BE790 | 78 → 77 | 372 / 384 | Token-preserving line layout retained. Tested fixed aggregate/byte/table views and initial pointer views. Draft holds initial table/end addresses across calls; target rematerializes them. |
| func_801CC3BC | 88 → 88 | 364 / 360 | Bounded search; lower candidate uses gratuitous 64-bit return cast. Full-width mask and unusual bitwise predicate retained. |
| func_800245B4 | 83 → 83 | 348 / 352 | Declaration-context search. Lower scores change signed range bounds or move entry increment outside loop; rejected. |
| func_80030220 | 77 → 73 | 344 / 348 | Snapshot the second random result in the existing s16 temporary before masking its low four bits (narrowing preserves those bits). Lower candidates substitute output for input traversal, rejected. |
| func_801BEEA4 | 39 → 39 | 356 / 344 | Copy-source snapshot and index/slot merging, cast, count comparison and declaration searches. 16-word candidate reuses slot as constant decrement 1; not retained. Clean direct i-1 source variants remain 39–40 words. |
| func_801B465C | 71 → 71 | 332 / 328 | Bounded search; selection-byte saved registers and branch scheduling remain. |
| func_80015450 | 66 → 51 | 324 / 324 | Snapshot current object into a separate pointer for rotation/position work. Correct target size restored; index reload/loop allocation remain. |
| func_80023EF0 | 71 → 67 | 296 / 312 | Snapshot count pointer and facing byte after camera update. Also tested explicit facing branches and counter widths; frame/traversal allocation and four missing words remain. |
| func_800121C8 | 47 → 47 | 304 / 304 | Bounded search; lower candidate overwrites mode with boolean before saving mode, rejected. Global scheduling/frame residue remains. |
| func_801BB464 | 76 → 76 | 308 / 304 | Bounded search; lower candidates add volatile/empty conditions. Coordinate/call spill scheduling remains. |
| func_801BE660 | 41 → 41 | 300 / 300 | Tested raw character snapshots/cursor forms and index widths; no measured gain. Floating/text register and spacing-constant scheduling remain. |
| func_801BBB60 | 40 → 40 | 292 / 292 | Bounded search; lower weighted outputs worsen words or alter store semantics. Palette base and unrolled zero stores remain. |
| func_801BE540 | 69 → 8 | 288 / 288 | Cache the unsigned character before converting to signed glyph index. Correct size and all FP/call instructions; only cursor a3 vs a0 and character a0 vs v1 (including first load base) remain. Full-TU measurement. |
| func_80024028 | 49 → 49 | 284 / 284 | Bounded search; packing/register residue remains. |
| func_8001373C | 36 → 34 | 256 / 256 | Stage X subtraction through the dy temporary before assigning dx. Tested separate distance declarations/order and incremental squared sums; extra local distance often adds a frame. FP/general registers remain. |
| func_801C0800 | 21 → 21 | 248 / 248 | Bounded search; lower weighted layout outputs still measure 21 words in TU. Color-pack/final command allocation remains. |
| func_800268C0 | 28 → 28 | 236 / 236 | Bounded search; lower weighted outputs worsen actual word count. Offset/dimension copy registers remain. |
| func_801C8004 | 38 → 27 | 232 / 236 | Use u8 accumulated button mask and direct shift tests/OR; remove the redundant intermediate bit variables. Full-width shift behavior preserved. One instruction short; scan/mask register allocation remains. |
| func_801ADA04 | 18 → 18 | 208 / 208 | Tested mode update forms, comparison order, final pending variable reuse and assignment within indexed call. Global-register allocation remains. |
| func_801C48E4 | 25 → 25 | 196 / 196 | Tested ANSI/K&R halfword parameters, explicit narrowing placement and sized backing arrays. Existing homing/address scheduling remains best. |
| func_801B43A8 | 34 → 34 | 196 / 196 | Lower scores merge group/current cursor or introduce uninitialized group snapshot; rejected. Shuffle pointer lifetimes remain. |
| func_801B5534 | 2 → 2 | 168 / 168 | Bounded search; scaled-index spill remains sp+18 vs target sp+1C. No padding added. |

## Follow-ups

Prioritize 801BE540's eight register-only words. Its raw-character snapshot is
semantically ordinary and now the best saved draft. Changing cursor scope,
character width, parameter pointer types, array-vs-glyph refs, cached loop
characters, and declaration/layout search did not solve it. The 801BE660 font
analogue did not improve under the same transformation.

801BEEA4's optimizer tracks separate index/slot expressions and preserves the
incremented slot in a3 across memcpy; target uses the saved next index directly.
Avoid accepting the promising but contrived slot=1 temporary without a cleaner
source explanation. 801AD7D8's tempting store-reordering result crosses a cache
flush and is unsuitable.

## Final clean validation

Command: `toolbox run -c kig-build bash -c 'make clean && make extract && make -j8 && make progress'`

All three image checks passed. Final output:

```
OK: rebuilt ROM is byte-identical to baserom.us.z64
| Total | 289,876 | 82,004 (28.29%) | 82,004 (28.29%) | 0 | 176 | 0 | 333 | 490 (167,316) |
```

Progress outputs have no net change. README was restored as required.
