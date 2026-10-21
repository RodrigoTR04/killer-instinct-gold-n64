# T-124 — sol-A42

Promoted **7 functions, 3,540 bytes (1.22% of 289,876 B)**. Target: 2,030 B;
exceeded by 1,510 B. No commits, subagents, ROM copies, compiler/build changes,
or edits to status.csv, TRACKING or WORKLOG.

| Function | Original B | Incoming differing words | Final differing words | Result |
|---|---:|---:|---:|---|
| func_801B2EF4 | 536 | 7 | 0 | Promoted |
| func_801B310C | 536 | 7 | 0 | Promoted |
| func_801B3324 | 536 | 7 | 0 | Promoted |
| func_801B353C | 536 | 7 | 0 | Promoted |
| func_801B3754 | 536 | 7 | 0 | Promoted |
| func_801B396C | 536 | 7 | 0 | Promoted |
| func_801C7A98 | 568 | 14 | 0 text | Improved draft; pool integration outstanding |
| func_801BD270 | 396 | 7 | 7 | Unchanged draft |
| func_801C8AE0 | 324 | 15 | 0 | Promoted |
| func_8001BDE0 | 316 | 8 | 8 | Unchanged draft |
| func_801C47E0 | 260 | 11 | 11 | Diagnosis only; unchanged draft |
| func_8002A900 | 220 | 15 | 15 | Diagnosis only; unchanged draft |
| func_801BD200 | 112 | 14 | 14 | Unchanged draft |

## Instruction diagnosis and accepted changes

`diagnosis.json` records instruction-level incoming differences for all eight
representatives; `production.json` independently checks all seven integrated
functions in complete production TUs, with relocation-aware zero differing
words and original sizes.

Family B's seven offsets are +3C/+40/+130/+148/+14C/+170/+184. The
uninitialized old-alpha load was hoisted into the prefix; the primitive constant
was delayed; completion used a3 instead of a2. The matched B3B84 template has
an actually later counter store and a further frame predicate, so copying its
counter lifetime would change B's original behavior.

The successful form keeps the counter store at late entry, then expresses the
completed-animation block as `do { ...; if (completion >= limit) break;
completion += 1; } while (0)`. The break is a real exit from the block that
suppresses the existing completion increment. All packet stores, alpha handling,
and final translation remain in their original observable order. This natural
completion control flow creates the compiler block boundary that releases the
counter register, preserves late alpha loading and restores primitive scheduling.
All six distinct thresholds, counter globals and translations are retained.
The original uninitialized stack-byte read is preserved and commented, as in
matched B3B84. No empty branch, dummy label/goto, padding or artificial test is
accepted. Necessary early and tail store line joins are preserved.

C8AE0's first three nibble-pair expressions needed the low nibble on the left
of OR. Removing the separate final low-nibble local and expressing the fourth
pair in the same order restores its last three register differences. This is a
straightforward pack of four nibble pairs, with unchanged bytes and evaluation
semantics. No owned rodata constants occur in these seven promotions.

C7A98 reaches exact text by expressing the final narrow store and local value
as `level = D_802923A0.maximum = maximum;`. It is retained as a draft: T-115
assigned its GLOBAL_ASM all 90 regular string objects of this TU, including
indirectly referenced and duplicate strings. Its integration requires migrating
that complete pool and removing/reassigning hints, beyond the text change.
No ownership hints were changed for this unpromoted function.

## Search accounting and audit

Disposable scripts, candidates and logs remain under `/tmp/t124-*`; no bulky
search output is delivered. Focused full-TU source sweeps covered pointer,
struct/union/array access, counter widths, assignment/increment forms, local
copies, statement ordering, real completion predicates, inverse branch/goto
layouts, scopes and do/while regions. Five initial B sweeps tested 146, 45,
57, 41 and 25 unique forms (including baselines and diagnostic compile errors).
A 91-form region sweep located zero with do/while boundaries; redundant
single-store/wrapper forms were not promoted. A subsequent 13-form sweep
explicitly connected the loop exit to the real completion predicate; its six
late-block variants reached zero. Formatted propagation and production
integration independently measured all six copies at zero.

The first bounded permuter run used 300 seconds, -j4,
`--stack-diffs --stop-on-zero --best-only --better-only`; last recorded
iteration 4,234, 51 errors. Its best weighted 160 inserted `if (0) {}` and
was rejected. A second run, bounded at 300 seconds with the same flags,
preserved required store joins and randomized the late region. It stopped at
626 iterations/10 errors on weighted zero, but inserted an immediate dummy
goto/label and was rejected. Neither permuter result is the production source.
The accepted real-break form came from targeted source diagnosis/sweeps.
All searches have ended.

Other targeted sweeps tested nibble operand order, FP value ownership,
64-bit result expressions, maximum types/store forms and controller-count
copies. Improvements were independently remeasured in full TU context.

## Final verification

`make clean && make extract && make all && make progress` passed (exit 0).
The ROM and all three executable images are byte-identical:

- ROM: `ba52e91b44450c548467044b26951353dc491e04`
- main: `81736d32e8cda8f399b319a49250dff972b81af8`
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`

Seven promoted drafts were deleted. C7A98's improved draft remains in place.
Generated progress documents are restored after recording the table below.
Prerequisite symlinks use the authorized shared checkout; no ROM was copied
or added. No searches remain. `git diff --check` passes.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 79,148 (27.30%) | 79,148 (27.30%) | 0 | 180 | 0 | 329 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 33,776 (23.46%) | 33,776 (23.46%) | 0 | 87 | 0 | 150 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 36,904 (26.85%) | 36,904 (26.85%) | 0 | 93 | 0 | 158 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
