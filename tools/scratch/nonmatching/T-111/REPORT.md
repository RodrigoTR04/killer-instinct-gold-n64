# T-111 — sol-A38: clone screening and first attacks

**0 MATCHED; 3 drafts IMPROVED. No commits.**

Added tools/analysis/clones.py and docs/clones.md. Retained improvements:
func_801BADEC 118→106 words, func_801B5650 425→423, and
func_801B5DCC 387→386. BB258 remains 20. No GLOBAL_ASM was replaced;
no draft was deleted. The requested new byte-exact matches were not achieved.

Read TRACKING, latest WORKLOG, overview, Makefile and the four requested
family reports. Missing dependencies were symlinked to the authorized main
checkout. No ROM contents were copied into git. No subagents were used.
Skipped the T-109/T-110 functions and all prohibited production/build files.

## Scanner

Run `.venv/bin/python tools/analysis/clones.py` after `make extract`.
The delivered document uses `--measurements tools/scratch/nonmatching/T-111/results.json`
to show final full-TU counts alongside the historical screen, plus family B
counts explicitly attributed to the T-103 report.
509 eligible T2/T4 functions are compared, including all 198 T2 functions.
The scanner combines inventory metadata with status.csv tier overrides and
uses original-functions.json sizes. It decodes untouched original image
words with rabbitizer for both tiers. This is equivalent original code for
T2 and avoids depending on assembly that splat removes after C promotion.
It checks that every T2 has original nonmatching assembly present.
Boot T4 words are read from baserom; extracted original main/overlay images
supply the other words. No built C output is used for similarity.

Normalization masks register identities (retaining integer/FP classes),
constants, relocations and branch targets, retaining opcodes, operand shape,
and memory addressing. Normalized instruction Levenshtein similarity and
size ratio must independently reach 0.85. A multiset-overlap upper bound
avoids unnecessary edit-distance calculations. Qualifying edges form
connected components; all edges and similarity to each component's first
member are reported. This is screening, not equivalence proof. Constants,
register dataflow and target identities are intentionally lost.

Final output has four clusters containing T2:

- BA674 (T4) / BB258: 524 T2 bytes, 0.879 similarity. Only matched-template
  lead at this threshold. Inspected the existing matched coordinate family.
- B5650 / B5DCC: 3,800 T2 bytes, 0.885. Both carousel functions are unsolved.
- Family B and B3B84: 3,772 T2 bytes. Six identical normalized streams,
  B3B84 similarity 0.921. No T4 template: skipped per instructions.
- 8001AD04 / 8001B134: 2,056 T2 bytes, 0.866. Inspected drafts; no matched
  template. Their conditional animation/audio differences need separate work.

T4-only components are omitted. A component can contain transitive pairs
below threshold. Historical T-099 differing-word counts are explicitly
labeled; they are not falsely presented as fresh measurements. This matters
for family B (now 19), BB258 (20), and BADEC (now 106, not screened 144).
An initial multiplicative size penalty found three components; final scoring
uses separate thresholds to avoid applying the size penalty twice.

## Attacks and retained results

| Function | Before → after words | Compiled / original bytes | Outcome |
|---|---:|---:|---|
| func_801BB258 | 20 → 20 | 524 / 524 | Unchanged |
| func_801BADEC | 118 → 106 | 568 / 568 | Improved draft |
| func_801B5650 | 425 → 423 | 1924 / 1916 | Improved draft |
| func_801B5DCC | 387 → 386 | 1884 / 1884 | Improved draft |

BB258: tested shared-x copy placement, signed/unsigned scale expressions,
explicit cached scales, assignment chains, source-line grouping, reversing
which x local holds the original calculation, and 360 declaration orders
for that alternate form. No retained change. One scale-declaration generator
initially emitted a declaration after a statement; IDO rejected it and the
generator was corrected. No compiler error was scored as a match.
The remaining original/draft register cycle is scale t0/t1 and the shared-x
pair t1,t2 versus t0,t2. A mere rename does not change allocation. Caching
scale again did not resolve it. The report and actual matched C, rather than
the contradictory short WORKLOG summary, guided the scale experiments.

BADEC: tested cached/direct scale, arrays/scalar coordinates, explicit
counter pointers, and redundant store elimination. Retained **only** pointers
to D_801F3AA0/D_801F3AA4. Both conditional windows, redundant stores, early
return, scale width and coordinate arrays remain. The pointers recover
symbolic accesses without changing global state semantics. Full production
TU measurement confirms 106 words and 568 bytes.

Carousel pair: tested moving each of six float declarations first/last and
three equivalent translation-depth expression forms (15 candidates each).
Retained height declared last in B5650 and next declared first in B5DCC.
The same general lifetime technique gives small improvements in both, but
no common byte-exact solution. Frame/register/matrix-call scheduling and
B5650's eight-byte size excess remain. No production declarations changed.

All four final measurements use IDO 5.3 -O2 -mips2 through asm-processor in
the complete owning TU. Differing words include size differences and mask
only actual ELF relocations. `recheck.py` repeats them after extraction.
Early candidate screening used T-106's standalone probe; accepted drafts
were independently reconciled in full TU context. Temporary candidates,
objects and verbose logs stay under /tmp, not in the deliverable.

## Verification

`make clean && make extract && make all && make progress` passed (exit 0).
The ROM and all three executable images are byte-identical. Checksums:

- ROM: ba52e91b44450c548467044b26951353dc491e04
- main: 81736d32e8cda8f399b319a49250dff972b81af8
- ovl_7DF8: ea830aae50ff1422da60d4b7fdbfc29f03b1be39
- ovl_7E00: 2b01138a290212b9d886981e1196f7b6fb45ecdb

Normalization/edit-distance sanity checks and Python compilation passed.
`git diff --check` passed. No task search processes remain. No commits.
No production source, status.csv, Makefile, YAML, TRACKING or WORKLOG edits.
Only the scanner/docs/report/recheck/results and three drafts are delivered.
Dependency symlinks remain untracked. No ROM data is included.


Final `make progress` table (unchanged):

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 69,664 (24.03%) | 69,664 (24.03%) | 0 | 198 | 0 | 311 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 30,556 (21.22%) | 30,556 (21.22%) | 0 | 91 | 0 | 146 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 30,640 (22.30%) | 30,640 (22.30%) | 0 | 107 | 0 | 144 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
