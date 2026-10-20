# T-088 — sol-B29: long-budget permuter round 2

**0 MATCHED, 1 IMPROVED draft, 19 UNCHANGED (including six conditional family-A siblings).** No commits. No production source or declarations changed.

Read docs/TRACKING.md, the latest docs/WORKLOG.md entries, Makefile, tools/permuter/README.md and T-082/REPORT.md before starting. Symlinked missing baserom.us.z64, ROMs, .venv and tools/ext from the authorized project checkout. No ROM was copied or added to git.

## Search setup

All 14 representatives ran concurrently for **2,700 seconds (45 minutes) each** using their current retained drafts. Total allocation: 16 local permuter workers, `-j 2` for B695C and C4E38 and `-j 1` for the other twelve. No network workers or subagents. Other workers were also using the machine, so these are wall-clock budgets, not exclusive CPU time.

Exact flags: `--stack-diffs --stop-on-zero --best-only --better-only --keep-prob 0.8 --quiet -j N`. The increased continuation probability was 0.8 versus the upstream 0.6 default. Per-search settings increased these mutation weights:

| Mutation | Weight |
|---|---:|
| perm_temp_for_expr | 180 |
| perm_randomize_internal_type | 35 |
| perm_pad_var_decl | 15 |
| perm_remove_var | 25 |
| perm_expand_expr | 40 |
| perm_reorder_stmts | 25 |
| perm_reorder_decls | 25 |
| perm_sameline | 30 |

The shared install and import helper were unchanged. Compiles used production IDO 5.3 `-O2 -mips2` through asm-processor. Each search used `timeout --signal=INT --kill-after=15s 2700s`; all returned timeout status 137 at approximately 2700 seconds. No zero-score output appeared and no search processes remain. Buffered quiet logs did not always retain the base score at timeout; each original base was separately debug-scored afterward. Run durations, base scores, best raw scores, worker counts and candidate checks are in results.json. Generated search directories remain outside the repository in `/tmp/kig-t088`.

Permuter penalties are weighted differences, **not differing instruction words**. Best raw scores below include rejected candidates. Lower penalties were not adopted when they worsened independently measured words or changed semantics.

## Per-function outcomes

| Function | Best raw permuter score | Result | Words old→final | Winning change / disposition |
|---|---:|---|---:|---|
| func_8002AA98 | 10 | UNCHANGED | 2→2 | mflo result register remains v0 versus target a2. |
| func_8002AAEC | 10 | UNCHANGED | 2→2 | Same unresolved register difference; no fix to transfer. |
| func_80017378 | 190 | UNCHANGED | 8→8 | No retained candidate; loop scheduling remains. |
| func_8002F45C | 163 | IMPROVED | 13→11 | Retained score-245 declaration-order candidate: key before old. Raw score-163 candidate has 15 differing words. |
| func_8002A900 | 135 | UNCHANGED | 15→15 | No accepted improvement. Full-TU candidate check hits existing conflicting scratch/TU declarations. |
| func_801BF720 | 60 | UNCHANGED | 2→2 | Pointer/block candidate did not solve default-result register. Existing signed/unsigned prototype conflict also prevents direct full-TU insertion unchanged. |
| func_801BF914 | 105 | UNCHANGED | 2→2 | Default register/return delay slot remains. |
| func_801C4E38 | 28 | UNCHANGED | 2→2 | Switch value spill remains at sp+0x18 versus target sp+0x1C. |
| func_801B6528 | 95 | UNCHANGED | 3→3 | Raw best has 7 differing words; retained incoming draft. |
| func_801B695C | 26 | UNCHANGED | 4→4 | Frame remains 0x30 versus target 0x28. |
| func_801C5064 | 20 | UNCHANGED | 4→4 | Recovers existing draft quality after parser normalization, no improvement. |
| func_801C7998 | 5 | UNCHANGED | 6→6 | Raw best truncates buttons to 8 bits, breaking high-button cases; rejected. |
| func_801C6A80 | 180 | UNCHANGED | 8→8 | Named-one temporary has 12 differing words; retained incoming draft. |
| func_801B2010 | 1151 | UNCHANGED | 14→14 | Raw best shortens body to 408/420 bytes and has 88 differing words. No family-A prefix solution. |
| func_801B21B4 | — | UNCHANGED | 14→14 | Conditional transfer target; no representative solution to transfer. |
| func_801B2358 | — | UNCHANGED | 14→14 | Conditional transfer target; no representative solution to transfer. |
| func_801B24FC | — | UNCHANGED | 14→14 | Conditional transfer target; no representative solution to transfer. |
| func_801B26A0 | — | UNCHANGED | 14→14 | Conditional transfer target; no representative solution to transfer. |
| func_801B2844 | — | UNCHANGED | 14→14 | Conditional transfer target; no representative solution to transfer. |
| func_801B29E8 | — | UNCHANGED | 14→14 | Conditional transfer target; no representative solution to transfer. |

## Retained change and hand checks

The only retained code change is in T-024/func_8002F45C.c: move `T024KeyMap *key` immediately before `s32 old`. No expression changes. Its full owning TU was independently compiled through asm-processor: 404/404 bytes, 11 relocation-masked differing words at offsets 0xC8, 0xCC, 0xD4, 0xD8, 0xDC, 0xE0, 0xF8, 0x118, 0x12C, 0x150 and 0x15C. The original savedKey alias is still needed by the incoming draft and remains documented in T-082; this round adds no new oddity. No GLOBAL_ASM was replaced and no draft was deleted.

Additional hand-generated screens tested:

- C4E38: argument widths; unused locals of different widths; explicit selector locals of different widths, assigned at several points and used in the switch, range check and inner comparison. No improvement. For full-TU probes only, reconciled the scratch return declaration of func_8002F6F4 with the TU's existing s32 declaration; no production declaration edits.
- B695C: removing frame/bank temporaries into direct expressions, narrowing/widening offset, changing pointer types, declaration order, narrower scope, declaration initializers, equivalent multiply/shift/address forms and statement line placement. No accepted improvement. The generated body already has the target's local spill slots; frame size and argument-home offsets remain different. A bank-mask diagnostic with stronger input assumptions was not retained.
- AA98: scaled/narrowed widths, shift forms, call parameter/return types and source line joins. No improvement and no solution to transfer to AAEC. Prototype changes were diagnostic only.
- BF720/BF914: return versus assignment/break/goto cases, default placement, local widths, reusing the input and returning through a pointer. Best remains two words.
- F45C: all five-local declaration orders; none improves the retained 11 words.
- B6528: index/result-pointer/y types and equivalent positive comparisons. No improvement.

C7998 also generated a candidate that widens the buttons argument to u64, changing the ABI; rejected independently of its poor word count. Its score-5 candidate retains the ABI but masks away the high byte and is likewise rejected. No inline asm, #line, register keyword, dead conditional or new permuter artifact was retained in a draft or production C.

## Final verification

`make clean && make extract && make all && make progress` **passed (exit 0)** after the retained draft change. Searches continued afterward without any further retained code changes. Generated progress documents have no diff. `git diff --check` passed.

ROM and all executable images remain byte-identical:

- ROM: `ba52e91b44450c548467044b26951353dc491e04`
- main: `81736d32e8cda8f399b319a49250dff972b81af8`
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`

Boot, ovl_7E00, YAML, Makefile, status.csv, TRACKING and WORKLOG were not edited. Only the F45C draft and this report/results are reviewable changes; local dependency symlinks remain untracked. Nothing was committed.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 53,904 (18.60%) | 53,904 (18.60%) | 0 | 249 | 0 | 260 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 27,256 (18.93%) | 27,256 (18.93%) | 0 | 104 | 0 | 133 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 18,180 (13.23%) | 18,180 (13.23%) | 0 | 145 | 0 | 106 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
