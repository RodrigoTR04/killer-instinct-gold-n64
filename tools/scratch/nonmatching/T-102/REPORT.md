# T-102 — sol-C38

**2 MATCHED (820 bytes), 5 IMPROVED drafts, 13 UNCHANGED. No commits.**

Read TRACKING, latest WORKLOG, Makefile, permuter README, T-100, T-092 screen, T-056/T-061/T-069/T-096/T-097/T-067, and each target's latest report entries before probing. Missing baserom.us.z64, ROMs, .venv and tools/ext were symlinked from the authorized main checkout. No ROM was copied or added to git.

## Results

Words count differing aligned instructions, masking actual ELF relocation fields and including size differences. Bytes are compiled/original function bytes, excluding trailing TU padding. Baselines were freshly measured and agree with the requested screen. All original functions were inspected. Only integrated matches have final linked-image validation; improved drafts remain nonmatching.

| Function | Result, old → new words | Final bytes | Retained change / remaining cause |
|---|---|---:|---|
| func_801AD114 | UNCHANGED 88 | 612/628 | Input reuse and layouts do not recover menu-branch/address lifetimes; four instructions short. Existing aligned u64 callback ABI retained. |
| func_801C3E40 | UNCHANGED 88 | 504/504 | Ring-index widths, flat vertices and cached phase/count pointers tried. Vertex/global reload allocation and command scheduling remain. |
| func_801CC3BC | UNCHANGED 88 | 364/360 | Explicit flag pointer and ordered error chain do not recover mask spills, frame and error dispatch. Full-width mask and unusual bitwise predicate preserved. |
| func_801AD7D8 | UNCHANGED 89 | 548/556 | Separate command cursors and layouts tried; cursor spill and repeated microcode-address materialization remain. |
| func_801BEEA4 | IMPROVED 90 → 40 | 356/344 | Unsigned stored score, full-width incoming score/count/shift index, distinct search and shift temporaries. Search/insertion register lifetimes, frame and three extra instructions remain. |
| func_8002B22C | IMPROVED 91 → 85 | 396/380 | Reuse current block after traversal, signed endpoint comparison as in target, subtract odd address bit. Head remains a distinct pointer. Frame/list allocation still differs; word reduction costs four additional bytes versus initial draft. |
| func_801C224C | IMPROVED 91 → 6 | 372/372 | Reuse incoming byte mode for both mode loads and copy indexing. Only entry allocation/scheduling at +04/+08/+0C/+10/+14/+1C remains. |
| func_80024714 | IMPROVED 94 → 69 | 712/712 | Advance the same resource cursor through packed records. Address materialization and store scheduling remain. |
| func_80026738 | UNCHANGED 96 | 388/392 | Original reads unsigned x/y/scale; coordinate/type and increment-order experiments do not improve score. Sprite setup and effect traversal allocation remain. |
| func_801BE910 | MATCHED 96 → 0 | 356/356 | Full-width score accumulator, cached source table after RNG, data store before score update, token-preserving line grouping. |
| func_8001CD50 | UNCHANGED 98 | 436/460 | Confirmed current callee declarations; zero-argument/void declaration experiment gives 104 words at 428 B. Initialization scheduling and missing instructions remain; original draft retained. |
| func_80024B0C | MATCHED 99 → 0 | 464/464 | Typed 64-byte matrix base, explicit byte offsets with shift by six, scoped command temporaries and final opcode/address store order. |
| func_80012390 | UNCHANGED 101 | 500/476 | Cursor grouping, signed length, cached dimensions and separate image advances tried. Initial loop and image-copy allocation remain; repeated dimension reads preserved. |
| func_8001272C | UNCHANGED 103 | 544/540 | Fade widths/layouts tried. Projection storage, effect clamp temporaries and rendering-call setup remain. Depth-clobbering reuse diagnostic rejected. |
| func_801C17D0 | UNCHANGED 103 | 436/448 | Branch-local stat pointers, player width, explicit wide-result predicate tried. Stat branches and result/frame allocation remain. |
| func_8002DDD4 | UNCHANGED 104 | 444/452 | Reconstructed transform/projection computation order and input reuse; candidates reach 460 B but worsen words. FP lifetimes and clamp scheduling remain. |
| func_801CD1F0 | IMPROVED 107 → 91 | 456/460 | Reuse completed error-result variable for enumeration index. Pfs retry still receives original controller argument. Saved registers, cursor lifetimes and one missing instruction remain. |
| func_8002FB80 | UNCHANGED 109 | 512/544 | Count widths/layouts tried; variable packed-command pointer advances and switch allocation remain. |
| func_800191F0 | UNCHANGED 110 | 476/492 | Inspected four-way actor loop and target halfword writebacks; explicit writeback experiments produce excess code. Actor-loop allocation and four missing words remain. |
| func_801B1DE4 | UNCHANGED 111 | 556/556 | Counter reloads, reuse of position and command-cursor lifetime tried. Interpolation/global lifetimes and FP scheduling remain. |

## Integration and limits

Both matches replace GLOBAL_ASM in their owning TUs; their drafts are deleted. func_801BE910's existing D_80127E50 declaration now uses the eight-byte entry type, allowing the existing caller body to remain unchanged. Its score parameter is s32 while the stored field remains s16: widening the record field would change its stride and is not retained. Both production functions independently measured zero in complete TU context after cleanup.

func_80024B0C retains a 64-byte, u64-aligned matrix view. Replacing its base with an untyped byte pointer changes six commutative addu operand orders. Explicit byte offsets and scoped Gfx commands recover the target without register bindings or artificial control flow. No matched function owns a function_owner reservation; no symbol hint changes are necessary. Keep any regenerated undefined-symbol changes (net result recorded below).

Improved drafts were updated in place. Measurement prefers the whole owning TU and falls back to prefix/declarations for legacy conflicts, following screen.py. In particular BEEA4 and 24714 require declaration reconciliation, so their reduced scores are provisional and do not imply integration readiness.

Permuter used -j5, --stack-diffs, --stop-on-zero, --best-only and --better-only. C224C ran its complete 20-minute bound (about 41,595 iterations); its best weighted score 20 candidate adds repeated masks and an empty branch and was rejected. The clean draft remains six differing words. A search on 24B0C was stopped after the independent structural match (roughly six minutes); its results were not promoted. A 910 search exited promptly after finding a candidate, while independent token layouts already produced zero. All output directories and logs remain in /tmp.

Rejected diagnostics include an early cache-block merge that lost the old head pointer, an early Pfs input-reuse variant that clobbered the controller before the retry, and an early broad score replacement that widened the record as well as the argument. Corrected candidates were measured separately; none of those rejected forms is retained. Compiler errors and partial-context scores are not matches. No inline asm, #line, register keyword, compiler changes or synthetic padding were introduced.

results.json is compact diagnostic evidence. probe.py/harness.py are incoming-source measurement helpers, not a rerunnable post-promotion sweep: matched draft files are now deleted. No compiler products or bulky logs are included.

## Final validation

`make clean && make extract && make all && make progress` passed (exit 0). The inventory's additional matching make also passed with the final declarations. ROM and all executable images are byte-identical:

- ROM: ba52e91b44450c548467044b26951353dc491e04
- main: 81736d32e8cda8f399b319a49250dff972b81af8 (239,824 bytes)
- ovl_7DF8: ea830aae50ff1422da60d4b7fdbfc29f03b1be39 (957,392 bytes)
- ovl_7E00: 2b01138a290212b9d886981e1196f7b6fb45ecdb (153,904 bytes)

`git diff --check` passed. Regenerated linker_scripts/*.undefined_syms.txt have no net changes. Generated docs/functions.csv and docs/progress.html were restored after recording the table. status.csv, Makefile, YAML, boot, ovl_7E00, TRACKING and WORKLOG are untouched. No task search/probe process remains. No commits. Matched game bytes increase 65,028 → 65,848 (+820); T4 increases 299 → 301.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 65,848 (22.72%) | 65,848 (22.72%) | 0 | 208 | 0 | 301 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 30,556 (21.22%) | 30,556 (21.22%) | 0 | 91 | 0 | 146 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 26,824 (19.52%) | 26,824 (19.52%) | 0 | 117 | 0 | 134 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
