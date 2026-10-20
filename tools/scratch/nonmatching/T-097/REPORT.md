# T-097 — sol-C36: hard residue round 2

**8 MATCHED (3,232 bytes), 0 IMPROVED, 8 UNCHANGED. No commits.**

Promoted func_801C6A80 (292 B) and all seven family-A functions (420 B
apiece). Replaced their GLOBAL_ASM pragmas and deleted their drafts.
Production edits are confined to ovl_7DF8_190B0.c and ovl_7DF8_5ED0.c.
No shared declaration was changed. Remaining drafts are unchanged.

Read docs/TRACKING.md, latest docs/WORKLOG.md, Makefile, and the complete
T-096 report, then skimmed T-088/T-092 and reused T-096's complete-TU
measurement helpers. Missing baserom.us.z64, ROMs, .venv and tools/ext were
symlinked from /home/rodri/Projects/killer-instinct-gold-n64. No ROM was
copied or added to git. No subagents or permuter workers were used.

## Method and successful hypotheses

Every measurement uses IDO 5.3 -O2 -mips2 through asm-processor in the full
owning TU. Words count instruction differences, including size differences,
with only actual relocation fields masked. The final linked image comparison
is the acceptance test. Compiler errors are recorded, never scored as matches.

C6A80: the direct global read/update allowed IDO to retain the flag's address
across the branch. An explicit local `u8 *flag = &D_802D3984` shortened its
address lifetime and recovered symbolic stores, reducing eight words to four.
Changing `*flag += 1` to `++*flag` then recovered v0 for the load and the
remaining branch/delay-slot operands. Both prefix and postfix increment
measured zero; the delivered source uses prefix increment. The local phase
pointer and existing declarations are preserved. No flag width or ABI change.

Family A: an explicit local pointer to each counter, plus `arg1++ < 1`, gives
the target a2 value, slti/beqz predicate, and shared increment delay slot.
Writing `*counter = arg1` as the lerp's third argument recovers its store in
the jal delay slot. That left two setup instructions reversed at +3C/+40:
the store-address lui and a3=1. Token-preserving line grouping recovered their
order. The cleaned result keeps only the counter assignment/if/else block
on one line, with a comment explaining IDO scheduling. No dead branches,
empty statements, inline assembly, register keyword, #line, new helpers,
changed prototypes, or modified compiler flags are needed. Each sibling was
independently checked at 420 bytes / zero words before all seven were
integrated together. The call remains func_801B19F0. func_801B29E8 preserves
its D_80292960 start value.

## Per-function outcomes

| Function | Hypothesis tried | Result / words | Remaining diagnosis |
|---|---|---|---|
| func_8002F6F4 | All single declaration moves (90 orders), step widths, event arrays, aggregate timing values, and event-field reuse diagnostics | UNCHANGED, 2→2 | +68/+160 still load/store step at sp+74 rather than sp+64. Array reversal retains two; other aggregate/lifetime forms disturb additional slots or code. No initialization of the existing uninitialized step path was retained. |
| func_801B695C | Inline frame/bank expressions; offset widths; reuse incoming index; narrow local scopes; declaration orders | UNCHANGED, 4→4 | Frame remains 0x30 versus 0x28; arg0 home follows it. Local spills already agree. Removing expressions or locals did not remove the excess eight bytes without other differences. |
| func_801C7998 | Parameter widths including diagnostic u64; explicit wide local; explicit homing/mask forms | UNCHANGED, 6→6 | +08..+1C homing/high-word initialization order remains. No evidence justifies changing the u16 input ABI or taking its address; narrowing that loses high-button cases was not retained. |
| func_801C6A80 | Explicit cached flag pointer with prefix increment | MATCHED, 8→0 | None; 292 B. |
| func_801C4E38 | Selector locals with several widths and assignment points before/after calls | UNCHANGED, 2→2 | +88/+B8 selector spill remains sp+18 rather than sp+1C. |
| func_801B6528 | Reuse arg2/arg3 for the post-guTranslate card view; compact layout | UNCHANGED, 3→3 | +178 reload remains a0 rather than a2; +1A0/+1E8 index-load bases follow it. |
| func_801BF720 | Switch assignments/break, return assignment, volatile-result diagnostic, compact layout | UNCHANGED, 2→2 | +1C default space still uses v0 rather than v1; +64 return delay slot still nop rather than move. |
| func_801BF914 | Same return-lifetime/layout probes | UNCHANGED, 2→2 | +68 default 27 still uses v0 rather than v1; +70 return move missing. |
| func_80017378 | Move both pointer increments ahead of stores, reverse initialization order, joined loop/body layouts | UNCHANGED, 8→8 | +590/+598 base/endpoint setup and +59C..+5B0 increments/stores retain earlier scheduling diagnosis. |
| func_801B2010 | Cached counter pointer, postfix predicate, assignment in lerp argument, joined counter block | MATCHED, 14→0 | None; 420 B. |
| func_801B21B4 | Independently transfer and compile family solution for D_801D30A0 | MATCHED, 14→0 | None; 420 B. |
| func_801B2358 | Independently transfer and compile family solution for D_801D30A4 | MATCHED, 14→0 | None; 420 B. |
| func_801B24FC | Independently transfer and compile family solution for D_801D30A8 | MATCHED, 14→0 | None; 420 B. |
| func_801B26A0 | Independently transfer and compile family solution for D_801D30AC | MATCHED, 14→0 | None; 420 B. |
| func_801B2844 | Independently transfer and compile family solution for D_801D30B0 | MATCHED, 14→0 | None; 420 B. |
| func_801B29E8 | Independently transfer and compile family solution for D_801D30B4 | MATCHED, 14→0 | None; 420 B; mutable global start preserved. |

## Evidence and limits

results.json contains the first sweep and instruction-level baselines;
extra.json, stack.json, and flag.json cover focused follow-ups. family*.json
record the staged counter experiments and layout search. family-clean.json
records cleanup checks; promotion.json records all seven final independent
full-TU zeros. Scripts are diagnostic records for the incoming source/drafts
and temporary inputs in /tmp/kig-t097; they are not a rerunnable harness after
the matched drafts have been deleted. No compiler products or ROM contents
are included in this deliverable.

Some diagnostic variants intentionally changed parameter widths or used
volatile locals; those are not proposed C. Event-field reuse and aggregate
variants were not adopted. One aggregate-step probe and two pointer-qualifier probes failed compilation
and are recorded as errors. An initial auxiliary-script import failed before
any measurements; the module was renamed sweep.py and that import corrected.
The measured sweeps completed before the final clean removed generated asm.

## Final verification

`make clean && make extract && make all && make progress` passed (exit 0).
The ROM and all three executable images are byte-identical:

- ROM: ba52e91b44450c548467044b26951353dc491e04
- main: 81736d32e8cda8f399b319a49250dff972b81af8
- ovl_7DF8: ea830aae50ff1422da60d4b7fdbfc29f03b1be39
- ovl_7E00: 2b01138a290212b9d886981e1196f7b6fb45ecdb

`git diff --check` passed. No task probe processes remain. No commits.
Generated docs/functions.csv and docs/progress.html were restored after
recording this table. status.csv, boot, ovl_7E00, YAML, Makefile, TRACKING
and WORKLOG are untouched. Local dependency symlinks remain untracked.
Matched game bytes increase 58,968→62,200 (+3,232); T4 increases 282→290.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 62,200 (21.46%) | 62,200 (21.46%) | 0 | 219 | 0 | 290 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 29,028 (20.16%) | 29,028 (20.16%) | 0 | 96 | 0 | 141 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 24,704 (17.98%) | 24,704 (17.98%) | 0 | 123 | 0 | 128 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
