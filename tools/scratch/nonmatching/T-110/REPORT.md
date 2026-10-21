# T-110 — sol-B35: frontend subsystem types

Shared `include/frontend.h` adopted in both requested TUs. All 30 existing C
matches are preserved (13 in 13FF0, 17 in 1BD90). **No new function matched.**
All 24 requested drafts now compile inside their complete owning TU using the
header. The settings validator improved substantially. No commits.

Read TRACKING, latest WORKLOG, overview frontend/rendering sections and TU
inventory, Makefile, common/ultra64/audio headers, T-108's header-adoption
report and probe, and the relevant T-021/023/030/034/070/076/079/095/100/102/
104/105 findings. Missing prerequisites were symlinked from the authorized
main checkout; no ROM was copied or added to git.

## Layout evidence

Offsets and sizes are N64 o32, not host ABI. Unknown fields remain reserved.
Names express observed use; they are not proposed symbol renames.

| Shared type | Evidence |
|---|---|
| `FrontendRenderContext` | First word selects the render-buffer bank in C9B14; +4 is the frame clock used by C23C0 and menu pulse calculations. C23C0 writes camera x/z/y/pitch/yaw at D4/D8/DC/E0/E4. Matched C0610/C2D34 and the text callers use the matrix arena at F8 with 64-byte strides. The prefix views from several drafts are now one FC-byte record. |
| `FrontendGfxWords`, `FrontendGfx` | Two 32-bit command words, eight-byte stride. C0610/C3524/C35D8 use sw. C2D34 also writes a whole 64-bit B600000000060004 command; its union retains eight-byte alignment and the full-word view. The word-only view retains the original four-byte alignment. |
| `FrontendGlyph` | BD640/BE540 use the 80282A70 font; BDF94/BE660 use 80282C48. Both have a command address at +0 and float width at +4, stride eight. These are distinct from main's bitmap-font metrics. |
| `FrontendMenuItem`, `FrontendMenuText` | C9B14 follows the three text pointers at +0/+4/+8. C7A98 changes the menu text at +10/+14 of 80292450. No claim is made about the unaccessed prefix. |
| `FrontendCloud`, `FrontendVertex` | Matched C35D8 advances 12 bytes, reads signed halfwords for coordinates/angle/width and signed alpha at +B. C3758 advances the animation byte at +A and writes vertices with xyz +0/+2/+4, texture coordinates +8/+A, RGBA +C..F, stride 16. |
| `FrontendSprite`, `FrontendSpriteLayout` | C2F5C's sprite array stride is 8C: texture +4, clip data +12, scale halfword +7E, y halfword +80 and callback +88. Its separate 10-byte (hex) layout record contains x/y/scale words and flip byte +C. The sound view starting at 801F2EB8 is retained separately. |
| `FrontendButtonMap`, `FrontendSettings` | Matched C78B0/C7E4C/C7E98/C86A8/C8868 establish six bytes per button mapping and 34 nibble-valued settings. The settings union exposes the same storage as first/second/remaining bytes and as the flat serialization array. No enum meanings were invented. |
| `FrontendScoreEntry`, `FrontendScoreTable` | Related matched BE910/BED0C and BF788/BF988 establish the eight-byte name/score entry and the eight-byte pointer/count/descending table descriptor. Score writes are halfwords; name is a packed word. |
| `FrontendMatchStats` | C17D0/C1990 consume seven input words: participant mask, two paired counter groups, result flag and minimum accumulator. Counter meanings remain unresolved. This is a documented input layout, not a replacement of the existing exported globals. |
| `FrontendNameState` | Layout view of 802D37D0..382D: phase +0; paired cursor words +8/+10; direction/cursor bytes +18/+1A; packed names +20; scroll +28; pending/active bytes +2C/+2D; two u64 packed scores +30; completion byte +40; timer words +48/+4C/+50/+54; state +58 and volume halfword +5C. BFB40/BFC08/BFC8C and BFCBC/1434/1990 support the accesses. Reserved gaps are explicit. |
| `FrontendMenuState`, `FrontendStatsText`, `FrontendReplayInputs` | Menu view starts at 39F8: scroll +0, selection +4, per-player selections +6/+7, mode +8, phase/pulse +9/+A, replay +E, transition +F, scale floats +18/+1C. C9584 copies exactly two eight-byte text lines. Matched C7CD0 initializes two u64 replay words to 1000. |

The name/menu structures are **layout views only**: member symbols remain
separate externs. No contiguous object ownership or linker regrouping is
asserted. The matched paired-word accesses retain `.x/.y`; drafts needing
player indexing use explicit word views. Size-check typedefs verify context,
name/menu state, score/glyph records, clouds and vertices without emitting data.

Assembly explicitly uses lbu for 39FC/3A01/3A02/3A07; their formerly signed
matched-TU declarations are now unsigned. Existing matched uses only store
these bytes, and remain exact. Cloud alpha remains signed because C35D8 uses
signed comparisons. Matrix-font prototypes retain promoted color arguments;
callees consume their low bytes. C11F0 keeps explicit byte narrowing for its
three shade arguments to preserve its best draft.

## Adoption and rejected changes

Both TUs include the header in place of duplicated task-local types and
externs. Existing command-pair source-line grouping is preserved. C2D34 uses
the aligned command union; C0610/C3524/C35D8 use its word-only counterpart.
C7CD0 retains its exact pair of u64 assignments. Settings serialization uses
`D_80127CC0.bytes`, and CBA2C reads the first member of the paired mode record.

An attempted `func_801C78B0(u8,u8)` prototype changed the matched callers:
its K&R definition/call sites use default argument promotion. The resulting
ROM check failed, so that prototype was reverted to the original unspecified
argument declaration. All 30 matched functions were then independently
compared against original bytes, masking only actual ELF relocation fields.
No mismatching production adoption is retained. The three functions excluded
by the brief (C7998/C85C0/CB998) remain untouched GLOBAL_ASM entries.

## Function results

`probe.py` reuses the existing relocation-aware ELF reader and screener with
production IDO 5.3 -O2 -mips2 through asm-processor. **Every final row below is
full-TU**, not prefix/declaration fallback. Counts are positional differing
words, including size differences, and are not behavioral certification.
`results.json` contains compact reproducible final measurements.

| Function | Final words | C / target bytes | Result / remaining cause |
|---|---:|---:|---|
| 801BFCBC | 596 | 2084 / 2388 | Shared paired-word/replay views compile; input/state-machine branches, 64-bit ABI, and clear-loop lowering remain. |
| 801C0800 | 21 | 248 / 248 | Shared command words; RGBA packing and command/index temporary allocation remain. |
| 801C08F8 | 561 | 2216 / 2296 | Shared command/text interfaces; score decoding, text buffers, float union and branch/call setup remain. |
| 801C11F0 | 113 | 584 / 580 | Shared text prototype with explicit byte colors preserves incoming best; phase/shade/divisor ownership and digit-buffer frame remain. |
| 801C1434 | 176 | 736 / 720 | Score loads/call ABI and player/state branches remain. |
| 801C17D0 | 103 | 436 / 448 | Reconciled pair and [][11] stat arrays; branch-local updates, saved registers and 64-bit output test remain. |
| 801C1990 | 159 | 604 / 676 | Correct two-dimensional stat indexing compiles fully; stat branches and paired 64-bit clears remain. Incoming 159/588 was declaration fallback and is not directly comparable. |
| 801C1C34 | 242 | 1224 / 1244 | Shared context/text prototypes preserve best; maxima walk, float/buffer stack locations and saved-register lifetimes remain. |
| 801C224C | 6 | 372 / 372 | All differences are entry allocation/scheduling: incoming mode owns s0 instead of a2 before the first call. Separate mode locals lose argument homes and worsen size. |
| 801C23C0 | 222 | 1812 / 1820 | One shared context now replaces camera and frame-prefix views. Vector stack layout, FP ownership and calls remain. Conflicting later command-builder declaration fixed. |
| 801C2ADC | 71 | 600 / 600 | Input comparisons, state clears, switch and call scheduling remain. |
| 801C2F5C | 128 | 556 / 544 | Shared sprite/layout types; callback and sprite-pointer lifetimes, frame and command scheduling remain. |
| 801C317C | 225 | 940 / 936 | Shared render context and text calls; float coordinates, counters and stack slots remain. |
| 801C3758 | 32 | 572 / 564 | Shared cloud/vertex records preserve incoming best; argument spill, animation wrap and vertex/store scheduling remain. |
| 801C7A98 | 14 | 568 / 568 | Paired mode record resolves full-TU conflict. Tail wants mode base a1, maximum address a0, five a2. Permuter's maximum-reuse candidate worsened to 23 words after cleanup. |
| 801C7F90 | 16 | 116 / 116 | Settings view resolves full-TU conflict. Initial clear/address retention and four-way zero-store order remain. |
| 801C8004 | **47** | **228 / 236** | **Improved from 110 / 444.** Correct pointer-table dereferences and no-argument reset call; explicit exit inside the scan prevents IDO's unwanted four-way unroll. A named shift value before the inner updates improves 53→47. Remaining: loop comparison/constant, register ownership, mask copy and two missing instructions. |
| 801C80F0 | 284 | 1228 / 1232 | Shared full context; pulse constants, per-player columns, saved FP registers and scheduling remain. |
| 801C8AE0 | 21 | 324 / 324 | Real queue array, no scalar/array conflict or duplicated typedef. Packed-result and tail temporary numbering remain. |
| 801C8C24 | 22 | 396 / 408 | Loop agrees; tail still lacks explicit arg0+1/+2/+3 addresses and target epilogue interleaving. |
| 801C90D4 | 219 | 1192 / 1200 | Shared context and unsigned selection recover the correct load. Text call setup and fade-loop scheduling remain. |
| 801C9698 | 135 | 1148 / 1148 | Shared context/text ABI and unsigned phase/selection; frame/hoisted constants/color registers remain. Narrow-color shared prototype worsened this and was rejected. |
| 801C9B14 | 629 | 3140 / 3184 | Shared item/context records, corrected float/text helper ABI and unsigned selection/transition; item traversal, branch layout, FP/frame allocation remain. Initial declaration fallback was 630 / 3140. |
| 801CAA00 | 992 | 3884 / 3992 | Reconciled real replay-word view, menu globals and actual one-argument C7CD0 call. Full-TU compiles; state dispatch, previous-input pointer spills and queue clearing remain. Incoming 972 / 3908 was declaration fallback using incompatible legacy views/calls, not an equivalent full-TU baseline. |

All drafts were updated in place to consume the shared declarations where
applicable. No GLOBAL_ASM was replaced and no draft was deleted.

Experiments covered parameter/local widths, pointer-table reconstruction,
mode-byte/record views, explicit loop exits, indexed/pointer loops, command
store permutations, character packing widths, nibble-tail cursor forms, and
ordinary multiline layouts across all 24 drafts. Whole-body line joins gave
one/two-word gains in three larger functions but were discarded rather than
retained as unreadable single-line bodies.

Three bounded local decomp-permuter runs used -j3, --stack-diffs,
--stop-on-zero, --best-only and --better-only, 120 seconds each: C224C
(2399 iterations / 30 errors), C7A98 (2287 / 29), and C8004 (2534 / 36). C224C produced
no improvement. C7A98's raw output had an unnecessary label; after removing
it and retaining only legitimate assignments it was worse than baseline.
C8004's useful named shift was retained with s32 type; its unnecessary
widening and `^ 0` mutation were discarded. No raw permuter output, objects,
assembly dumps or bulky probe logs are kept in the repository.

## Verification

`make clean && make extract && make all && make progress` passed (exit 0).
The final independent per-function check again preserved all 13 + 17 matches.
`git diff --check` passed. Both edited production TUs compiled without warnings;
pre-existing warnings in other TUs were not changed.

- ROM: `ba52e91b44450c548467044b26951353dc491e04`
- main: `81736d32e8cda8f399b319a49250dff972b81af8`
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`

No task search/probe process remains. No Makefile, YAML, status.csv, main,
boot, ovl_7E00 or other worker's function edits. Generated progress documents
have no net changes. Authorized prerequisite symlinks remain local. Changes
are uncommitted for the lead to vet.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 66,512 (22.94%) | 66,512 (22.94%) | 0 | 204 | 0 | 305 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 30,556 (21.22%) | 30,556 (21.22%) | 0 | 91 | 0 | 146 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 27,488 (20.00%) | 27,488 (20.00%) | 0 | 113 | 0 | 138 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
