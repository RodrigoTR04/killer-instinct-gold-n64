# T-099 — sol-B32

**3 MATCHED (548 bytes), 4 IMPROVED drafts, 3 UNCHANGED. No commits.**

Read TRACKING, latest WORKLOG, Makefile, permuter README/screener, T-092
screen, and T-096/T-097/T-082/T-089/T-067 reports. Missing prerequisites were
symlinked from the authorized shared checkout. No ROM was copied into git.
No commits, subagents, network workers, flag changes, or binary rewriting.

## Refreshed screen and selection

screen.md records the initial current-T2 snapshot: 215 drafts, 214 measured,
one error (func_8001D080, declaration fallback parser missing a type).
The old T-092 screen had 230 drafts. The new table preserves all compiler
fallback diagnostics and ranks equal-size candidates first. No error is
reported as a large score. The screener itself and status.csv are unchanged.

Selected the ten closest eligible equal-size drafts, 2–13 words, excluding
all assigned residue, family B and T-100 functions. Initial instruction
comparisons are in instructions.json. Scores include missing/extra words
and mask only actual ELF relocation fields; weighted permuter penalties are
a separate metric. Prefix/declaration contexts require reconciliation before
promotion. Scratch improvements are diagnostic, not behavior validation.

| Function | Initial words / bytes | Diagnosis before editing |
|---|---:|---|
| func_801C3524 | 2 / 92 | +28/+2C first color/command stores are reversed; registers already agree. |
| func_801CC908 | 2 / 424 | +0C/+19C frame allocation/free: draft 0x40, target 0x30. Actual mask/status/handle spill offsets agree. |
| func_801CCD74 | 4 / 116 | +10/+14 load current/previous pointer into v1/t6 in reverse order; +20 comparison operands and +28 previous-pointer store base follow the reversed address-register ownership. |
| func_801BF988 | 5 / 184 | +6C/+70/+78 final packed word remains in s0 rather than t4; +7C/+90 score halfword uses v1 rather than t5. |
| func_801C85C0 | 5 / 168 | +48..+58 call's index addition/mask must precede the first three clears. Registers, widths and remaining loop already agree. |
| func_801C3990 | 7 / 272 | +04/+0C/+10/+18 and +48/+4C/+50: external scale and zero occupy f0/f2 instead of f2/f0. |
| func_8001E0B4 | 11 / 648 | +34/+40 command/address setup swap; +5C..+70 loop-counter initialization precedes five global bases; +E4/+E8/+F4 flag-load and halfword-clear scheduling. |
| func_8002F45C | 11 / 404 | +C8/+CC/+F8/+118/+12C/+150/+15C pan lives in v1 rather than a1; +D4..+E0 sound/pitch/key/owner scheduling. |
| func_801BD270 | 11 / 396 | +124/+138 buttons spill at sp+22 rather than +26; +12C/+130 axis byte store/reload rather than target halfword at +22. +154..+170 u64 carry-chain scheduling/register choices. |
| func_8001BDE0 | 13 / 316 | +0C/+10/+34/+3C input threshold f24 rather than f20, offset f20 rather than f24; +40/+4C/+64/+74 command cursor v0 rather than v1; dependent FP comparisons/subtractions differ. |

## Method

Hand passes test the diagnosed lifetimes, real local declaration order,
argument/axis/score widths, independent field stores, local pointers, and
ordinary multiline layouts. Search inputs use the production IDO 5.3 -O2
-mips2 asm-processor command. They retain the complete target bodies and
late rodata. Other TU bodies become declarations using pycparser, avoiding
the upstream regex's dense-body truncation. Each search uses -j5,
--stack-diffs --stop-on-zero --best-only --better-only and a 1,200-second outer cap, interrupted after at least 900 seconds
for unresolved functions. The packing search stopped early after an independently
cleaned hand match.
Temporary compiler products and search output remain under /tmp/kig-t099.
Final candidates are rechecked in their complete owning TUs and linked images.

## Retained results

| Function | Words old → retained | Result | Change / remaining difference |
|---|---:|---|---|
| func_801C3524 | 2 → 0 | MATCHED, 92 B | Join the first command/value stores on one source line, as already needed for the final pair. Clean named command cursor; both pairs have a scheduling comment. |
| func_801CC908 | 2 → 2 | UNCHANGED | Declaration orders, dead home-local cleanup, explicit records/arrays, status widths and compatible callee declarations do not recover the smaller frame. Spill slots already agree; no padding or ABI workaround retained. |
| func_801CCD74 | 4 → 4 | UNCHANGED | Separate current/previous pointer reads, reversed predicates, explicit local pointers, and layouts leave the address/register ownership issue. Later s32-output prototype also needs reconciliation before integration. |
| func_801BF988 | 5 → 0 | MATCHED, 184 B | Explicit u16 narrowing for the packed character word and direct halfword score read at its final byte store recover t4/t5. Remove redundant random mask, extra pointer and unused score temporary. |
| func_801C85C0 | 5 → 4 | IMPROVED | Reorder independent zero stores (first byte, word, second byte, final byte). Still declaration-fallback only; remaining argument/mask scheduling is not an integration claim. |
| func_801C3990 | 7 → 0 | MATCHED, 272 B | Use the original 0.1f literal instead of an external float read and explicit zero literals at guTranslate. Removes unused zero local and external constant declaration. |
| func_8001E0B4 | 11 → 9 | IMPROVED | Token-preserving ordinary line joins fix the command/address setup swap. Remaining +5C..+70 counter/global-base setup and +E4/+E8/+F4 flag/halfword scheduling. Full-TU checked. |
| func_8002F45C | 11 → 4 | IMPROVED | Load/store key flags before clearing owner, with a named u8 flags value. This recovers a1 for pan and its spills. Remaining +B4/+C0 loop load/add uses a1 rather than v1; +DC/+E4 raw flag load/mask uses v1 rather than t3. Full-TU checked. |
| func_801BD270 | 11 → 7 | IMPROVED | Signed-halfword Y local and declaration order fix the axis/button spill widths and offsets. Remaining +154..+170 carry-chain register allocation/scheduling. Full-TU checked. |
| func_8001BDE0 | 13 → 13 | UNCHANGED | Input-threshold snapshot, equivalent comparisons, constant/scale initialization order, literal diagnostics, layouts and random search do not yield a retained improvement. Original external-value semantics preserved. |

The three promotions total 548 game bytes. Improved drafts stay in their
original T-021/T-022/T-023/T-024 directories. Matched drafts were deleted.
Only three production functions and their required local declarations were
changed. Boot, ovl_7E00, YAML, Makefile, status.csv, TRACKING and WORKLOG are
untouched. There is no inline assembly, register keyword, #line, empty
condition or dummy control flow in the retained changes.

C85C0 reconciliation exposes a real context limitation: the earlier matching
func_801C7E98 definition takes two u8 arguments, whereas the fallback draft
uses a non-prototype call. Reconciled arrays and that existing prototype
measure 24 words for the four-word fallback candidate. Moving the candidate
ahead of the callee is rejected by IDO's prototype/promotion compatibility
check, so no source movement or prototype change is retained. No other
function was altered to accommodate this draft.

Raw packing output's redundant &0xFFFF mask was replaced with a meaningful
u16 conversion; the direct final score read then supplies the remaining
register allocation. This read stays after the same two packed-byte stores
as the original target; pointer increments do not change its address. The
score still comes from the full input halfword and is narrowed only by the
byte output store. No input character bits or score semantics were discarded.

The final E0B4 draft keeps its original readable multiline body, joining
only the initial command/address stores. This minimal cleanup independently
retains nine words; a comment explains the line dependence. Allocator flag/owner store order follows the original target.
All improved drafts remain target-sized.

All eight searches have finished. The seven unresolved searches ran
900.4–905.5 seconds each; packing stopped after 327.3 seconds following its
independently cleaned match. Exit 137 records bounded interrupt termination,
not a compiler/build failure. No T-099 search or probe processes remain.
results.json records durations, raw penalties, probe summaries and final
independent retained measurements. The best raw BDE0 candidate changes the
second loop's scale and was rejected; dummy-control-flow candidates were
also rejected. No additional match emerged in the final searches.

## Final verification

`make clean && make extract && make all && make progress` passed (exit 0).
The ROM and all executable images are byte-identical:

- ROM: ba52e91b44450c548467044b26951353dc491e04
- main: 81736d32e8cda8f399b319a49250dff972b81af8
- ovl_7DF8: ea830aae50ff1422da60d4b7fdbfc29f03b1be39
- ovl_7E00: 2b01138a290212b9d886981e1196f7b6fb45ecdb

`git diff --check` passes. Matched game bytes increase 63,432→63,980
(+548); T4 increases 294→297. status.csv stays unchanged for the lead.
Dependency symlinks remain untracked. No ROM or generated search directory
is included in the changes. Generated progress documents are restored after
recording the table below.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 63,980 (22.07%) | 63,980 (22.07%) | 0 | 212 | 0 | 297 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 29,576 (20.54%) | 29,576 (20.54%) | 0 | 94 | 0 | 143 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 25,936 (18.87%) | 25,936 (18.87%) | 0 | 118 | 0 | 133 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
