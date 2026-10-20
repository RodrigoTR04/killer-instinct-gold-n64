# T-054 — sol-C21: main polish round 4

**2 MATCHED (1,736 bytes), 17 IMPROVED drafts, 13 UNCHANGED.** All **32**
functions in the brief received rewrite/type/loop experiments, beyond baseline
screening. No commits. Changes are left for lead review.

## Matches and ownership

- `func_80016910` (720 B): C now writes the sine expression directly to its
  destination, uses ordinary double literals `3.14159` / `180.0` and float
  `359.0f`, and divides by `(f32)256`. IDO otherwise folds the float-literal
  division to multiplication by its reciprocal; the integer-to-float constant
  conversion preserves the original `div.s`. No compiler options or register
  bindings are involved. Its two pairs of double literals and final float are
  emitted into their original late-rodata slots.
- `func_8001B620` (1,016 B): C uses typed 12-byte stage records, expressions
  for the stage addresses rather than a saved local pointer, direct global
  state dispatch, and six ordinary float literals. The address expressions
  eliminate an extra stack slot. The existing `T0331383CStagePart` layout is
  reused; no unrelated function body is changed.
- The four `force_migration function_owner:func_8001B620` hints for
  `D_80048998`, `D_800489A0`, `D_800489A8`, `D_800489B0` are reassigned to
  adjacent retained asm `func_8001B134`. These doubles are used by already
  matched `func_8001B50C`; keeping them assembly-defined preserves that C's
  existing external loads and pool order. The new B620 C emits its own six
  floats after those reserved doubles. No YAML changes.
- Added local extern declarations for the newly promoted functions' globals
  and callees. `func_800326F0` retains the TU's existing non-prototype unsigned
  declaration because existing earlier callers pass extra arguments. Existing
  callers and all existing matched C remain byte-exact.

Deleted original drafts:

- `tools/scratch/nonmatching/T-033/func_80016910.c`
- `tools/scratch/nonmatching/T-022/func_8001B620.c`

`func_80029BE0` remains asm, so its owned vertex/display-list data and hints
are unchanged. Regenerated undefined-symbol files are retained if changed.

## Per-function results

Old→new counts use the **same standalone IDO 5.3 production flags**, masking
only real ELF HI16/LO16/26 relocations. They count corresponding instruction
words over the **emitted** body, including overshoot into following original
bytes for oversized candidates. A shorter body can lower this positional
count without being closer in edit distance; emitted/original sizes are
therefore reported alongside it. These counts are diagnostics, not a claim
that an improved draft is byte-exact or behavior-certified. Only the two
promoted functions have full linked validation.

T-022 baselines needed shared declarations. `1808C` additionally needed its
stale A730 scalar declaration reconciled with the current byte array before
measurement. Baseline snapshots and compile diagnostics are retained here.
Each bounded pass tried a few concrete forms, then moved on; this was not an
exhaustive search. Failed and behavior-changing probes were not installed.

| Function | Result | Emitted/original B | Attempt / remaining blocker |
|---|---|---:|---|
| func_80025D58 | UNCHANGED (73 words) | 328/620 | Tried equality termination, signed/unsigned/narrow row counters and aligned aggregate height copies. Equality termination enables IDO peeling/unrolling but emits 656 B and 162 differences; original paired-row loop still differs. |
| func_80030440 | IMPROVED **127→122** | 488/632 | Replaced integer source offset with byte cursor. Also tried pixel-run countdown and narrow counters; remaining RLE loop/control-flow differences. |
| func_8001BB64 | IMPROVED **195→144** | 592/636 | Rewrote packed-color output using Gfx records, full-width channel arithmetic and a short local color array. Tried separate-symbol versus indexed loop sentinel. Register/control-flow and loop unrolling still differ. |
| func_8001E0B4 | IMPROVED **61→59** | 648/648 | Widened scale intermediates while preserving the explicit narrowing at half scale. Single widened locals, unsigned half scale, mirror boolean and actor-index forms were also tried. Scheduling/register differences remain. |
| func_80039C08 | UNCHANGED (150 words) | 608/648 | Tried sample-count width and command-count pointer types. Client selection/callback scheduling remains different; no convincing improvement retained. |
| func_800170C4 | IMPROVED **266→134** | 696/692 | Replaced scalar vertex stores with aggregate assignments and an indexed eight-vertex loop. Checked the original four-way unrolled loop: eight vertices, not eleven. Original register allocation and loop setup remain different. |
| func_80018F20 | IMPROVED **127→91** | 696/696 | Reconciled globals/A730 array; typed stage-field and indexed transform probes, then correct float literal for D_80048900. Remaining setup-store scheduling/register differences. |
| func_800131A4 | IMPROVED **181→169** | 676/712 | Tried command cursor/order forms and full-width part/counter locals. Callback and loop/register differences remain. |
| func_80024714 | IMPROVED **104→94** | 712/712 | Signed boot_dma address ABI and signed symbol-address subtraction; full-width dispatch local. Resource-slot/address setup still differs. |
| func_80016910 | **MATCHED** | 720/720 | Direct sine-result assignment, literal pool and ordinary cast divisor; full linked checks. |
| func_8001D47C | IMPROVED **213→179** | 752/748 | Replaced manually unrolled palette operations with counted loops. Tried short/unsigned indices and narrow selector ABI; rejected shorter narrow-loop forms as poor matches. Remaining division/unroll/register differences. |
| func_8001D080 | UNCHANGED (175 words) | 756/764 | Tried indexed sprite fields instead of raw offsets, plus full-width buffer selectors. No difference reduction. |
| func_80017A68 | UNCHANGED (155 words) | 768/772 | Cached typed stage pointer and indexed-byte-table forms; pointer caching worsens size/register allocation. |
| func_800297A4 | UNCHANGED (180 words) | 780/780 | Tried indexed free-burst search and short counters. Signed-random geometry emits less code but changes unsigned conversion behavior and was rejected. |
| func_80017D6C | UNCHANGED (194 words) | 824/800 | Typed stage indices and indexed transform access probes; no retained improvement. One broad declaration substitution failed compilation and was discarded. |
| func_8001808C | UNCHANGED (178 words) | 796/808 | Reconciled stale A730 array type for probes; typed stage records and indexed transform stores produce the same metric. Original draft left unchanged. |
| func_800193DC | IMPROVED **187→186** | 796/808 | Shared declarations/A730 indexing, typed-stage and indexed-transform probes, then D_80048908 literal. Substantial setup scheduling/register differences remain. |
| func_800241BC | IMPROVED **166→161** | 840/820 | Signed DMA ABI/address differences and full-width resource dispatch. Resource address/slot layout and scheduling remain different. |
| func_8002E150 | UNCHANGED (177 words) | 836/844 | Tried unsigned exponent, double sqrt, and Horner evaluation ordering. No reduction; changed sqrt precision was diagnostic only. |
| func_8002AB90 | UNCHANGED (199 words) | 816/852 | Tried signed allocation loops, aligned aggregate parameter copy and explicit rounded-frame increment. All retain the baseline metric. |
| func_80018AE0 | UNCHANGED (203 words) | 928/912 | Reconciled shared declarations and A730 array, then typed stage records and indexed transform fields. No metric reduction. |
| func_8002A4F0 | IMPROVED **145→129** | 916/920 | Explicit production signed DMA ABI and address casts. Also tried narrow sequence length and unsigned count. Stack/setup scheduling still differs. |
| func_80027E1C | IMPROVED **238→234** | 940/936 | Postincrement Gfx cursor, command ordering and full-width age arithmetic (bounded to 124). Floating-point interpolation/register differences remain. |
| func_80028230 | UNCHANGED (231 words) | 932/976 | Tried GBI word order and background packet cursor/index forms. Remaining rectangle packing and signed coordinate control flow. |
| func_8001B134 | IMPROVED **228→214** | 980/984 | Corrected 12-byte stage-record indexing, typed float-array cursors and B620 call arguments; removed dead save artifacts. Remaining float/register scheduling. Still asm and now owns the four reserved doubles. |
| func_8001B620 | **MATCHED** | 1016/1016 | Typed stage expressions, direct state dispatch, float literals and ownership reassignment; full linked checks. |
| func_800216D4 | UNCHANGED (230 words) | 1040/1032 | Tried signed DMA address arithmetic and full-width dispatch/cache-loop counters. Wider counters worsen differences; no retained rewrite. |
| func_8003EF90 | IMPROVED **222→213** | 884/1048 | Sequential parameter pointer replaces indexed parameter stream. Also tested native short indices and signed delay offsets. Original mask/index and allocation scheduling remain different. |
| func_80029BE0 | UNCHANGED (260 words) | 1048/1060 | GBI command ordering and loop-counter widths tried. Narrow counters lower the positional metric but lack support in original loop arithmetic; rejected. Owned arrays remain asm. |
| func_800253D0 | IMPROVED **205→180** | 1044/1068 | Postincrement Gfx cursor and command-first GBI stores. Remaining HUD call/register scheduling. |
| func_8001AD04 | IMPROVED **249→194** | 1088/1072 | Typed stage records fix scaled-pointer indexing; corrected the final rotation-array index and B620 arguments, removed dead compiler-save artifacts. Remaining float/register scheduling. |
| func_800327E8 | IMPROVED **286→284** | 1156/1092 | Corrected byte-versus-element offsets and steps in frequency-tree/reset/update pointers. Remaining arithmetic decoder control flow, double operations and registers. |

## Diagnostics

`probe.py`, `attempts.py`, `refine.py`, `focused.py`, `loops.py`, `vertex.py`,
`literals.py`, `near.py`, `finish_near.py`, `color_clean.py`, and `repair.py`
record the experiments. JSON files keep counts, sizes, failures and the first
16 mismatch offsets. `*-base.c` snapshots retain reconciled baselines;
`*-best.c` are intermediate candidates, **not necessarily the retained final
choice**. `retained.json` identifies the choices copied to the original draft
locations. Scripts are historical experiment stages, not a production build
step; some expect previous stages' generated candidates or drafts since
deleted after promotion. No objects, ROMs, or image binaries are stored here.

## Final clean validation

`make clean && make extract && make -j8 all && make progress` passed after
the final source edit. The ROM and all three images printed OK.

- ROM SHA1: `ba52e91b44450c548467044b26951353dc491e04`
- main: `81736d32e8cda8f399b319a49250dff972b81af8`
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`

A cleanup edit temporarily removed adjacent existing matched C; the final
clean build caught the missing symbols. Those bodies were restored verbatim
from HEAD before the passing run. The final production diff replaces only
the two requested pragmas and adds their declarations.

`git diff --check` passes. No boot/overlay source, YAML, Makefile, tracking,
worklog, or status.csv was edited. Generated docs/functions.csv and
docs/progress.html are restored after capturing this output. Dependency
symlinks point to `/home/rodri/Projects/killer-instinct-gold-n64`; no ROM was
copied or committed. No commits were made.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 53,648 (16.81%) | 53,648 (16.81%) | 0 | 309 | 0 | 253 | 437 (138,092) |
| boot | 8,468 | 8,108 (95.75%) | 8,108 (95.75%) | 0 | 1 | 0 | 20 | 99 (16,028) |
| main | 173,204 | 31,336 (18.09%) | 31,336 (18.09%) | 0 | 147 | 0 | 143 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 14,204 (10.34%) | 14,204 (10.34%) | 0 | 161 | 0 | 90 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
