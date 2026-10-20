# T-094 — sol-A32

**2 MATCHED (536 bytes), 4 IMPROVED drafts, 7 UNCHANGED. No commits.**

Read TRACKING, latest WORKLOG, Makefile, permuter README, T-092 REPORT/screen,
T-089/T-082 practice reports and T-067 line-boundary scheduling report.
Missing baserom.us.z64, ROMs, .venv and tools/ext were symlinked from the
user-authorized shared checkout. No ROM was copied or added to git.

The brief calls these never-permuted, but T-092 records previous searches for
several of them, including rejected zeros for C8F28 and C3990. This task runs
a fresh round rather than assuming those prior zeros were usable.

## Results

Words count relocation-masked instruction differences, including body-length
differences. Weighted permuter penalties are separate and may include rejected
candidates. All retained drafts have their original body size. Full owning-TU
checks confirm retained improvements; scratch drafts are diagnostic, not
behavior-validation claims. The two promotions also pass resolved image/ROM
comparisons.

| Function | Words old → retained | Best raw penalty | Result | Winning change / disposition |
|---|---:|---:|---|---|
| func_800281C4 | 4 → 0 | hand | MATCHED | Separate start/end assignments onto individual lines; 108 B. |
| func_801C8F28 | 4 → 0 | 0 | MATCHED | Signed-halfword first-row intensity temporary. Reconcile the alternate 2D global view with the TU's flat byte array; use flat indices. Remove unnecessary split-index temporary; 428 B. |
| func_801CC908 | 4 → 2 | 10 | IMPROVED | Reorder local declarations to fix the status spill slot. Cleaner hand candidate ties the cleaned weighted winner. |
| func_801CCD74 | 4 → 4 | 45 | UNCHANGED | Layout, clear-store permutations and local-width probes do not improve it. |
| func_801C85C0 | 5 → 5 | 120 | UNCHANGED | No retained improvement; raw candidate changes an external declaration to volatile int and is rejected. |
| func_801C3524 | 6 → 2 | 40 | IMPROVED | Write command before color value; preserve final command/address store line join. Remove the raw candidate's duplicate color store. |
| func_801C3990 | 7 → 7 | 0 | UNCHANGED | Raw zero requires empty if(zero); rejected. Removing it restores seven words. Global-store permutations and meaningful zero-value uses do not recover a clean match. |
| func_8001BDE0 | 13 → 13 | 85 | UNCHANGED | Best raw candidate overwrites the scale with the threshold and changes the second loop's arithmetic; rejected. |
| func_801BD200 | 14 → 14 | 85 | UNCHANGED | Remove permuter's dummy goto/label; cleaned candidate remains fourteen words. |
| func_801C7A98 | 14 → 14 | 730 | UNCHANGED | Raw candidates use an empty conditional, if(1), a redundant mask or comparison multiplied by zero; cleaned forms do not improve the draft. |
| func_801C7F90 | 16 → 16 | 345 | UNCHANGED | Mode temporary and line joins lower the weighted score but worsen size/word differences. Pointer-loop variants also do not improve the draft. |
| func_801BF988 | 17 → 5 | 305 | IMPROVED | Use input/output parameters directly and combine packing in one unsigned accumulator. Remove unused locals. Remaining five words are final packed-result and score register choices. |
| func_801B5534 | 19 → 18 | 474 | IMPROVED | Direct array indexing removes the explicit byte-offset local. Narrow parameter variants are shorter and worse; retain s32 signature. |

## Method and cleanup

Quick probes covered multiline layouts, local declaration order, local and
parameter widths, callee prototypes, independent stores and direct array/
pointer expressions. The hand match at 281C4 needed no random search.
C8F28's fresh random zero appeared after 24 seconds, C3990's rejected zero
after 3 seconds. The ten other assigned functions completed 1,200-second searches,
with at most five single-worker searches concurrently (approximately -j5).
Commands use --stack-diffs --stop-on-zero --best-only --better-only with the
exact IDO 5.3 -O2 -mips2 game flags through asm-processor. No network workers
or subagents were used. Search inputs include complete target bodies; legacy
prefix conflicts use a temporary declarations-only context, without changing
the shared import helper. Final retained results are checked in complete TUs.

C8F28 retains an ordinary signed-halfword intensity local to obtain the target
register allocation. Its values are 0, 5, 55 or 120; the conversion preserves
all values. The code comment documents the reason for keeping it. 281C4 uses
ordinary multiline assignments. There is no inline asm, #line, register
keyword, empty conditional or dummy control-flow construct in promoted C.

Deleted the matched T-024/func_800281C4.c and T-034/func_801C8F28.c drafts.
Improved drafts remain in their original T-021/T-023/T-029 directories.
The 3524 final command/address stores deliberately share a line; its draft
comment documents the IDO scheduling dependence.
Generated search inputs, outputs, logs and probe scripts are only under
/tmp/kig-t094, outside the tracked tree. No permuter output directory is a
deliverable. Boot, ovl_7E00, YAML, Makefile, status.csv, TRACKING and WORKLOG
were not edited. Dependency symlinks remain untracked; do not stage them.

## Final verification

`make clean && make extract && make all && make progress` passed (exit 0).
ROM and all executable images remain byte-identical:

- ROM: `ba52e91b44450c548467044b26951353dc491e04`
- main: `81736d32e8cda8f399b319a49250dff972b81af8`
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`

All ten nonzero searches completed the 1,200-second cap (exit 137 after the
bounded timeout). The two random zeros stopped early; 281C4 was solved by
hand. results.json records each duration and raw score. No search/probe
processes remain.

`git diff --check` passes. Generated docs/functions.csv and docs/progress.html
are restored after recording the table. No status.csv changes or commits.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 58,932 (20.33%) | 58,932 (20.33%) | 0 | 228 | 0 | 281 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 28,968 (20.12%) | 28,968 (20.12%) | 0 | 97 | 0 | 140 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 21,496 (15.64%) | 21,496 (15.64%) | 0 | 131 | 0 | 120 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
