# T-112 — sol-C41: resident rendering subsystem

Shared `include/render.h` adopted in all four assigned TUs. No new matches.
No commits. Improved drafts remain drafts; no GLOBAL_ASM was removed.

Read TRACKING, latest WORKLOG, overview rendering sections/TU table,
gfx_format, Makefile, common/ultra64 and audio header conventions, and
T-069/T-081/T-085/T-102/T-108 reports before editing. Missing prerequisites
were symlinked from the authorized main checkout; no ROM was copied into git.

## Shared types and evidence

| Type | Evidence / limits |
|---|---|
| RenderMtx / RenderMatrixF | 64-byte fixed-point matrix union with s64 alignment, following T-069; float transforms are 4×4 arrays. No SDK header dependency or incompatible SDK typedef introduced. |
| RenderGfx | Two u32 words, eight bytes per command; text command emission and stage command output. |
| RenderCameraState / RenderCameraPose | Contiguous B0..E0 state: signed limit at B0, signed byte mode at B4, five target floats B8..C8, five current floats CC..DC and roll E0. B8B0/B91C/B9B4 and D9C4 establish the layout. Original individual global symbols are retained; no aggregate linker alias is invented. |
| RenderWorldPoint | Integer xyz +0/+4/+8; converted x/z/y +C/+10/+14, height +18, integer top +24. Matched BAF0 accesses establish offsets. |
| RenderCameraInput / Output | Input integer xyz +4/+8/+C; projected signed words +68/+6C, distance +70. Output floats +C/+10/+14. E08C and DDD4 establish these. Corrected old projected-float declaration to signed words; existing caller still matches. |
| CameraObject / Preset / Fade / Tracking | Partial record views recovered in the existing BBD0 draft; preset stride 0x28, keyframes 0x14, fade bytes +29/+2A, tracking words +10/+110. Unknown fields remain reserved. These names do not assert the complete engine-object layout. |
| RenderVertex | 16 bytes: signed XYZ +0/+2/+4, flag/reserved +6, signed ST +8/+A, four color bytes +C..F. FDA0 and gfx_format's delta stream establish it. Initial previous vertex is D_80048290. |
| StageRaw / Texture / Triangle / Vertices | Separate packed byte-record views with sizes 9/4/2/3. Tag bits 7:6 select record kind. They are not a fixed-stride array and may be unaligned. gfx_format and FB80 establish the layouts. |
| RenderTextureRecord | Two-byte size/type table entry: high three bits decoder kind, low thirteen bits count, per matched 30020. Source and destination pointers remain parallel arrays. |
| RenderGlyph / Color / GlyphImage | Four-byte width/height/spacing/baseline metrics, four-byte colors, and glyph packet with four reserved bytes then runs at +8. 30440/306B8 establish layout; output slots have 0x120-byte stride. |

Compile-time size checks cover matrix (64), vertex (16), glyph (4), and
camera state (0x34). Shared globals and helper prototypes are declared in the
header. Matrix-function ABI declarations preserve the existing matched calls.

## Adoption

main_1BE80's 12 existing matches, main_20220's four, and main_20AE0's one
retain their instruction bytes. main_1E7F0 has no existing C body; it includes
the same header. The batch wrapper now has typed command/vertex/texture/output
arguments; the vertex base is explicitly converted to u32 for address emission.
No adoption needed reverting. The first linked adoption build passed ROM and
all-image verification; final clean validation is recorded below.

## Remaining functions

Scores are positional differing instruction words, masking only real ELF
relocation fields and including length differences. They are diagnostics,
not behavior validation. `probe.py` compiles inside the complete owning TU
with production asm-processor/IDO 5.3 -O2 -mips2 flags. `results.json` records
retained measurements. Baselines agree with recent reports except E150's
179-word full-TU measurement versus the old prefix report's 180.

| Function | Incoming → retained words | C / original bytes | Result / remaining work |
|---|---:|---:|---|
| 800300DC | 76 → 74 | 316 / 316 | Recovered full-width input value and narrow run-count lifetime; original-sized backreference loop. Cursor/input allocation, byte decoding and loop scheduling remain. |
| 80030220 | 77 → 77 | 340 / 348 | Typed vertex/end-pointer reconstruction and layouts did not improve the saved-register and RNG/division scheduling mismatch; retained incoming draft. |
| 8002DDD4 | 104 → 104 | 444 / 452 | Shared matrix/globals and corrected signed output prototype compile in full TU. Projection/clamp FP live ranges remain. Layout search produced no improvement. |
| 8002D9C4 | 134 → 129 | 548 / 536 | Indexed five-float copies recover original unrolling; conversions moved after direction selection. Frame, copy-address lifetimes and FP scheduling still differ. A 125-word token layout was rejected in favor of the readable retained multiline draft. |
| 8002FB80 | 109 → 67 | 536 / 544 | Per-case advancing input/output cursors, original parameter lifetime and count termination. Remaining vertex-address/store scheduling and two missing instructions. |
| 8002FDA0 | 136 → 107 | 556 / 572 | Shared vertex record, direct coordinate stores in each switch branch, do/while count termination. Initial-record copy scheduling and flag/control-flow allocation remain. |
| 80030440 | 156 → 144 | 556 / 632 | Metrics assigned with width/height capture and direct output-slot indexing. Run unrolling/address registers and row-tail clear remain. |
| 8002E150 | 179 → 179 | 836 / 844 | Exponent-based inverse-sine-style polynomial/range reduction; header compiles and layouts tried. Polynomial FP lifetimes and branches remain. |
| 800306B8 | 510 → 510 | 2096 / 2104 | Shared Gfx/glyph/color types replace independent draft definitions. Layout attempts did not improve clipping/string-loop frame and register allocation. |
| 8002BBD0 | 1843 → 1843 | 7692 / 7668 | Attempted last: migrated recovered camera types and reconciled helper declarations, then measured complete TU. Large state-machine/FP/rodata reconstruction remains; no new structural rewrite claimed. |

The shared decomp-permuter ran a bounded 180-second, three-worker search on
FB80 with --stack-diffs and --stop-on-zero: 7,179 iterations, 213 compile
errors, best weighted score 1,635 from 3,845. Its best candidate remeasured
as the same 67 positional words / 536 bytes, so no permuter candidate was
retained. Compiler errors are not scores. Temporary compiler products,
permuter outputs and bulky logs remain outside the repository.

No function was promoted, so BBD0/E150's function_owner hints and asm-owned
constants remain intact. No YAML, Makefile, boot, overlays, SDK sources,
status.csv, TRACKING or WORKLOG edits. No inline assembly, register bindings,
#line directives, compiler overrides or artificial padding.

## Final clean validation

`make clean && make extract && make all && make progress` passed (exit 0).
The ROM and all executable images are byte-identical:

- ROM: `ba52e91b44450c548467044b26951353dc491e04`
- main: `81736d32e8cda8f399b319a49250dff972b81af8`
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`

All four assigned TUs compile without warnings. Final ten-function full-TU
measurements agree with results.json. `git diff --check` passes. Regenerated
undefined-symbol files have no net changes. Generated functions.csv and
progress.html were restored after recording the table. No task search process
remains, and no commits were made.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 70,628 (24.36%) | 70,628 (24.36%) | 0 | 195 | 0 | 314 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 31,204 (21.67%) | 31,204 (21.67%) | 0 | 90 | 0 | 147 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 30,956 (22.53%) | 30,956 (22.53%) | 0 | 105 | 0 | 146 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
