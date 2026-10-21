# T-103 — sol-A35: family B, round 3

**0 MATCHED, 0 IMPROVED; all six remain 19 words off at 536/536 bytes. Family B remains unsolved. No commits.**

Only this task report and diagnostic helpers were added. No draft was changed or deleted and no GLOBAL_ASM was replaced.

## Method and scope

Read docs/TRACKING.md, latest docs/WORKLOG.md, Makefile, and T-101/T-098/T-097 reports. Linked missing baserom.us.z64, ROMs, .venv and tools/ext to the shared project; no ROM contents were copied into git. No commits or subagents. All candidate measurements use production IDO 5.3 -O2 -mips2 through asm-processor in the complete owning TU. The comparator masks actual ELF relocations only and counts size differences. Compiler errors are failures, not matches.

All six incoming drafts independently reproduce 19 differing words at 536 bytes. Production GLOBAL_ASM functions and matched family A are untouched. The inherited uninitialized alpha path remains scratch-only; no attempt to initialize it or substitute a different stack byte is accepted.

## Exact remaining regions and hypotheses

The reference is func_801B2EF4; offsets are relative to its entry. T-101/final.json contains the individual original/generated instructions.

- **+3C/+40:** target has counter-store `lui at` and primitive constant `lui t9,FA00`; draft hoists completion-flag `lui/addiu a3` here. Tested direct/global versus local counter stores, branch-local address temporaries, completion pointer scopes, flag value reuse, declaration moves, and natural goto forms. The counter still needs a2 through its late store; recovering a2 for the flag requires an earlier end to that live range without hoisting the flag.
- **+7C, +10C/+110, +124:** target primitive constant is t9, cursor increment t8; draft reverses those assignments. Unsigned float conversion itself, FCSR t7 save/restore, mask into t1, and cursor load at +F0 already agree. Tested named primitive constants, store placement, packed-result reuse, and grouping. No signed-conversion substitution is acceptable.
- **+128–+14C:** target starts with counter store using the pre-branch at, then cursor load, stale `lbu t7,27(sp)`, palette address in v0, cursor increment/store t8, primitive store t9, palette lh, completion address in a2. Draft instead introduces the counter lui here and reads stale alpha into t0. Explicit counter/flag address lifetime hypotheses have not recovered this schedule.
- **+150–+164:** palette mask/shift/OR chain already agrees, using t1–t6.
- **+168/+16C, +170/+184:** target packs t6 OR old-alpha t7 into t8, then loads/stores completion via a2; draft uses old-alpha t0, packed t7, completion a3. Tested alpha widths, dead incoming scalar reuse, separate old-alpha locals, masked reads, and local byte pointers. Different stack offsets are diagnostic failures, not fixes.
- **+188–+214:** signed depth, guTranslate, alpha spill/reload at sp+27, final commands and epilogue already agree. No tail edits are proposed.

The source-line sweeps preserve tokens and vary contiguous joins plus seeded random joins. Declaration sweeps move individual locals. Natural gotos route actual early/late control flow to a shared translation tail; dummy labels and empty conditionals are rejected.

## Search results

`experiments.json` records compact completed-sweep counts; `baseline.json` and `final.json` independently record all six unchanged measurements. Completed focused sweeps: 291 lifetime/declaration/line-join, 20 natural-flow, 228 alpha, 152 counter/flag, 8 cleaned broad-permuter, 48 call-setup, and 36 command-scope measurements (783 total; 27 compiler errors). Their minimum differing-word counts are respectively 19, 19, 42, 19, 23, 19, 19. A further structural/layout sweep was stopped after at least 1,000 completed measurements with best 19. Its partial in-memory rows were not retained; the report makes no exhaustive-search claim. The scripted early-store placements intentionally deduplicate identical sources; they do not cover all possible permutations.

The shared decomp-permuter ran for **30 minutes**, `--stack-diffs --stop-on-zero --best-only --better-only -j 3`, on a separate imported copy of the representative. Last reported iteration: 8,868, with 119 errors. A second overlapping **15-minute**, one-worker run used `PERM_RANDOMIZE` to restrict mutation to the late branch; last reported iteration: 818, with 18 errors. Each had its own input and output directory. Both ended at their timeout (the interrupt grace period ultimately returned exit 137). These are weighted assembly scores, not byte-difference counts.

Broad search best weighted score 395 depended on `goto dummy_label; dummy_label: ;` immediately after the late counter store. Rejected as artificial. Removing it measured 23 words in the full TU. Seven cleanup variants measured 23–27 words. Natural goto versions without that barrier were separately tested and did not improve 19. Late-region best weighted score 677 introduced a gratuitous volatile local/store. Rejected; full-TU diagnostic 69 words / 540 bytes, cleaned form 23 words / 536 bytes. No result was automatically promoted.

All searches and candidate compiler products stayed under /tmp. Only compact summaries, representative instruction differences, and small diagnostic scripts are retained. The scripts depend on the existing T-098/T-096 full-TU harness and on extraction; the late-permuter cleanup scripts also refer to their disposable /tmp search inputs. No task probe remains.

Next useful work still concerns coupled counter-store, command-constant and completion-pointer lifetimes. A new alpha model must preserve the actual sp+27 read without artificial control flow, volatile traffic, or stack-padding repairs. The stable conversion and tail are not the source of the remaining mismatch.

## Final verification

`make clean && make extract && make all && make progress` passed (exit 0). All existing matches, including family A, remain intact. ROM and all executable images are byte-identical:

- ROM: ba52e91b44450c548467044b26951353dc491e04
- main: 81736d32e8cda8f399b319a49250dff972b81af8
- ovl_7DF8: ea830aae50ff1422da60d4b7fdbfc29f03b1be39
- ovl_7E00: 2b01138a290212b9d886981e1196f7b6fb45ecdb

Final independent draft checks: func_801B2EF4, func_801B310C, func_801B3324, func_801B353C, func_801B3754 and func_801B396C each remain 19 differing words / 536 bytes. Their constants and globals remain unchanged. No promotion or draft deletion.

`git diff --check` passed. Generated progress files do not differ. main, boot, ovl_7E00, YAML, Makefile, status.csv, TRACKING and WORKLOG are untouched. No commits. Dependency symlinks remain untracked. The requested exact matches were not achieved.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 65,576 (22.62%) | 65,576 (22.62%) | 0 | 207 | 0 | 302 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 30,092 (20.90%) | 30,092 (20.90%) | 0 | 92 | 0 | 145 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 27,016 (19.66%) | 27,016 (19.66%) | 0 | 115 | 0 | 136 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
