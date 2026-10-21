# T-118 — sol-A40: declaration order and source layout

Implementation: `tools/permuter/declorder.py`, with usage and limits documented in
`tools/permuter/README.md`. No commits. No subagents.

## Method

Read TRACKING, latest WORKLOG, Makefile, permuter README, screen.py, T-113's
screen, and T-067/T-114/T-097 reports. Missing baserom.us.z64, ROMs, .venv and
tools/ext were symlinked from /home/rodri/Projects/killer-instinct-gold-n64.
No copyrighted ROM content was copied into git.

Compilation and scoring reuse screen.measure: IDO 5.3 -O2 -mips2 through
asm-processor, in the owning TU, with only ELF relocation fields masked.
Differing words include missing/extra instructions; absolute byte-size difference
breaks ties. A context is selected once per search and never changed between
variants. Prefix/declaration fallback zeros require full-TU reconciliation.

The tool permutes simple uninitialized leading locals (all orders for ≤6,
400 sampled orders above that), tries separate vs adjacent same-type combined
declarations, and joins/splits statement and brace boundaries. Initialized
declarations remain fixed. Initializers mentioning a local form scope/dependency
barriers; independent initializers let unrelated declarations cross. Executable
tokens and their order are preserved. No #line, register keyword, source rewrite
through an AST, changed expressions, ABI or compiler flags is used.

Three staged passes per target: a 300-second initial implementation (strict
hill climbing and leading declaration prefix), a 300-second extended pass
(equal-score reservoir and declarations beyond independent initializers), and
a 60-second final-tool pass including function-brace placement. Each next pass
starts from the preceding best and waits for that function to finish; no function
is searched concurrently twice. The first pass runs eight functions concurrently;
later passes overlap only different functions, each with one compiler worker.
CLI -j parallel compilation was independently exercised by the regression probes.
Small proposal spaces can stop early after 100 duplicate proposals; seconds are
actual wall time, not an assertion of exhaustive layout enumeration. Budget caps
can also stop declaration enumeration early; initial_exhausted records this.
No raw compile logs, search directories, objects or candidate dumps are retained
in git. measurements.json records compact per-pass scores, sizes and counts.

## Selection

Parsed every numeric ≤40-word row of T-113/screen.md, including size-mismatched
rows later in that report. 28 current drafts remain after exclusions. T-116's
selection was read from its shared worktree report:
`/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-e7e76605/tools/scratch/nonmatching/T-116/REPORT.md`.
All 15 of its selected functions and T-117's five reservations were excluded.
The decoder range 0x80031050–0x800327E8 was excluded; already-promoted
func_8002F6F4 and func_801C7998 have no drafts. selection.json records the audit.
Current measured baselines, rather than stale screen values, are reported below
(e.g. func_80017378 is already six words).

## Results

| Function | Before → after words | Result | Compiled / target B | Context | Search seconds | Winning variant |
|---|---:|---|---:|---|---:|---|
| func_800269AC | 2 → 2 | UNCHANGED | 236 / 236 | full | 660.5 | incoming draft |
| func_801BF720 | 2 → 2 | UNCHANGED | 104 / 104 | prefix | 576.4 | incoming draft |
| func_801BF914 | 2 → 2 | UNCHANGED | 116 / 116 | prefix | 577.6 | incoming draft |
| func_801C4E38 | 2 → 2 | UNCHANGED | 556 / 556 | declarations | 660.7 | incoming draft |
| func_801CC908 | 2 → 2 | UNCHANGED | 424 / 424 | full | 661.0 | incoming draft |
| func_801B6528 | 3 → 3 | UNCHANGED | 596 / 596 | full | 661.2 | incoming draft |
| func_8002F45C | 4 → 4 | UNCHANGED | 404 / 404 | full | 660.6 | incoming draft |
| func_801B695C | 4 → 4 | UNCHANGED | 268 / 268 | prefix | 660.7 | incoming draft |
| func_801C85C0 | 4 → 4 | UNCHANGED | 168 / 168 | full | 660.4 | incoming draft |
| func_801B5534 | 5 → 5 | UNCHANGED | 168 / 168 | full | 204.7 | incoming draft |
| func_801C224C | 6 → 6 | UNCHANGED | 372 / 372 | full | 660.6 | incoming draft |
| func_801BD270 | 7 → 7 | UNCHANGED | 396 / 396 | full | 660.6 | incoming draft |
| func_80017378 | 6 → 6 | UNCHANGED | 1752 / 1752 | full | 661.0 | incoming draft |
| func_8001BDE0 | 8 → 8 | UNCHANGED | 316 / 316 | full | 660.7 | incoming draft |
| func_801C7A98 | 14 → 14 | UNCHANGED | 568 / 568 | full | 660.5 | incoming draft |
| func_8002A900 | 15 → 15 | UNCHANGED | 220 / 220 | full | 660.5 | incoming draft |
| func_801B2EF4 | 19 → 19 | UNCHANGED | 536 / 536 | full | 661.3 | incoming draft |
| func_801B310C | 19 → 19 | UNCHANGED | 536 / 536 | full | 661.4 | incoming draft |
| func_801B3324 | 19 → 19 | UNCHANGED | 536 / 536 | full | 660.7 | incoming draft |
| func_801B353C | 19 → 19 | UNCHANGED | 536 / 536 | full | 661.0 | incoming draft |
| func_801B3754 | 19 → 19 | UNCHANGED | 536 / 536 | full | 660.5 | incoming draft |
| func_801B396C | 19 → 19 | UNCHANGED | 536 / 536 | full | 660.7 | incoming draft |
| func_801B1210 | 28 → 28 | UNCHANGED | 284 / 284 | full | 660.3 | incoming draft |
| func_801B446C | 28 → 28 | UNCHANGED | 292 / 292 | full | 660.9 | incoming draft |
| func_8002A4F0 | 31 → 27 | IMPROVED | 920 / 920 | full | 660.3 | settings before entry; separate declaration lines |
| func_8001373C | 36 → 36 | UNCHANGED | 256 / 256 | prefix | 533.4 | incoming draft |
| func_801BBB60 | 40 → 40 | UNCHANGED | 292 / 292 | full | 661.3 | incoming draft |
| func_801C3758 | 32 → 32 | UNCHANGED | 572 / 564 | full | 660.7 | incoming draft |


No new exact matches. One improved draft, func_8002A4F0 (31→27), is retained
in T-024. The winning order puts AudioSettings settings before ALSeqData *entry.
Normal one-per-line formatting and an explanatory comment independently measure
27 words / 920 B in the full TU (integration.json). Executable tokens are unchanged.
No production C function or GLOBAL_ASM was changed and no draft was deleted.

func_801B5534 has no movable uninitialized local and only eight layout boundaries.
All 256 join/split patterns were additionally compiled in full TU context, with
zero errors and a best score of five words (finite-layout.json). This explains its
shorter search time; the final layout dimension is exhaustively checked there.

An initial round-2 lookup of func_801C3758 rejected its K&R parameter declaration
syntax before compilation. The locator was corrected without rewriting the ABI;
round 2 was restarted. The old round-3 launcher also rejected it before compilation
and that pass was replaced by the corrected tool. Neither parse failure is a
negative compile/search result. Both corrected passes are recorded in measurements.

## Tool verification

In disposable TU snapshots, without editing production source:

- Joined func_8002B95C: 2 → 0 words / 88 B with split-all, reproducing T-067's layout sensitivity.
- Reversed key/step declarations in func_8002F6F4: 2 → 0 words / 516 B through declaration hill climbing, reproducing T-114's match.

regression.json and declaration-regression.json record these checks. They are
existing matches used to validate the search, not new matches credited to T-118.
Additional checks exercised literal/comment-aware lexing, for-loop separators,
prototype-vs-definition lookup, initializer dependency barriers, stable repeated
declaration rendering, and 150 randomized token-order-preserving layouts across
three real drafts. Python syntax compilation and git diff --check pass.


## Final verification

All 84 bounded passes completed: 41,698 successful variant compiles and
0 variant compile errors (baseline/context selection is counted separately).
The additional exhaustive sweep compiled 256 layouts without errors.
`regression.py` reproduces the two known-match checks using disposable TU snapshots.

`make clean && make extract && make all && make progress` passed (exit 0).
The ROM and all executable images are byte-identical:

- ROM: `ba52e91b44450c548467044b26951353dc491e04`
- main: `81736d32e8cda8f399b319a49250dff972b81af8`
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 71,400 (24.63%) | 71,400 (24.63%) | 0 | 193 | 0 | 316 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 31,720 (22.03%) | 31,720 (22.03%) | 0 | 89 | 0 | 148 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 31,212 (22.71%) | 31,212 (22.71%) | 0 | 104 | 0 | 147 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |

No production source, boot, ovl_7E00, YAML, Makefile, status.csv, TRACKING or
WORKLOG changes. No commits. Dependency symlinks remain local/untracked.
Generated progress files have no net diff. Search products and raw logs remain
under /tmp; only compact measurements and two reproducible regression probes
are retained here. All task search processes have stopped.
