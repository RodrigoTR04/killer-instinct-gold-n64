# T-092 — sol-C34

**6 MATCHED (1,156 bytes), 5 IMPROVED, 8 UNCHANGED. No commits.**

Read TRACKING, latest WORKLOG, Makefile, permuter README and T-082/T-089/T-067
reports. Missing local dependencies were symlinked from the authorized shared
checkout. No ROM was copied or added to git. Boot, ovl_7E00, YAML,
symbol_addrs, Makefile and status.csv were not edited.

## Search results

Words are relocation-masked instruction differences, including length differences;
penalties are the permuter's separate weighted scores. Retained improvements
have original body sizes. Scratch improvements are diagnostic, not behavior
validation. The first four functions are T-089 follow-ups; the next fifteen are
the closest equal-size screen entries after excluding the complete T-088 list
and the four follow-ups. Initial measurements are retained in the old column.

| Function | Words old → retained | Best raw penalty | Result | Winning change / disposition |
|---|---:|---:|---|---|
| func_8002F6F4 | 2 → 2 | 24 | UNCHANGED | Step spill still differs by 0x10; declaration relocation probes did not solve it. Updated queue view only to follow E4A0's reconciled global declaration. |
| func_8002E4A0 | 2 → 0 | 0 | MATCHED | Keep voice-list base in the local and form indexed addresses directly at alLink. Removed empty statement. Reconciled existing alternate player views through a void pointer and explicit struct casts. 480 B. |
| func_8002A4F0 | 31 → 31 | 1110 | UNCHANGED | Lower weighted output worsens word count; retained baseline. |
| func_800121C8 | 49 → 47 | 1770 | IMPROVED | Independent global-store order, overlay-data local, joined statement layout. Removed constant-index aliases, redundant masks, comma-zero and do/if wrappers. |
| func_800244F0 | 2 → 0 | 0 | MATCHED | Named ROM-address temporary places size spill at the original slot. 196 B. |
| func_801C3580 | 2 → 0 | 0 | MATCHED | Permuter normalization separates signature, brace and call lines. 44 B. |
| func_801C35AC | 2 → 0 | 0 | MATCHED | Same multiline layout as 3580. 44 B. |
| func_800281C4 | 4 → 4 | baseline | UNCHANGED | No saved improvement. |
| func_801BF850 | 4 → 0 | 0 | MATCHED | Joined loop layout; removed empty conditional and do-once wrapper. Existing s32 global declarations retained via byte-pointer views. 196 B. |
| func_801BFA40 | 4 → 0 | 0 | MATCHED | Named stride and second-call input alias; joined first-loop layout. Removed comma-zero expression. 196 B. |
| func_801C8F28 | 4 → 4 | 0 | UNCHANGED | Raw zero uses alternate array declaration and narrowing cast; reconciled/cleaned complete-TU candidates do not retain zero. Kept original draft. |
| func_801CCD74 | 4 → 4 | baseline | UNCHANGED | No saved improvement. |
| func_801C3990 | 7 → 7 | 0 | UNCHANGED | Raw zero needs empty if(zero); removing it restores 7 words. Rejected despite zero weighted score. Token-preserving layout search did not recover an honest zero. |
| func_801C3524 | 8 → 6 | 40 | IMPROVED | Write color value before command, preserve final command/address line join. |
| func_801C85C0 | 9 → 5 | 120 | IMPROVED | Reorder initial pointer assignments on one line; remove do-once wrapper and simplify subtraction of negative two. |
| func_801CC908 | 13 → 4 | 26 | IMPROVED | Local allocation/status result and spill declaration order; removed XOR-zero and multiply-zero expressions. |
| func_801BD200 | 14 → 14 | 85 | UNCHANGED | Raw 10-word candidate needs if(1); removing the wrapper restores 14 words. Retained baseline. |
| func_801C7A98 | 14 → 14 | 730 | UNCHANGED | Best saved weighted candidate has 27+ words; retained baseline. |
| func_8001BDE0 | 15 → 13 | 97 | IMPROVED | Move cursor declaration ahead of float locals and join command stores. |

All searches used shared decomp-permuter, IDO 5.3 -O2 -mips2 through
asm-processor, `--stack-diffs --stop-on-zero --best-only --better-only`.
At most six single-worker searches ran concurrently (equivalent CPU budget to
-j6). Every nonzero search ran 1,200 seconds. Zero searches stopped early:
E4A0 506 s, 244F0 2 s, 3580/35AC 1 s, BF850 279 s, BFA40 77 s,
C8F28 371 s, C3990 44 s. The latter two zeros were rejected during cleanup.
No network workers or subagents. Generated inputs, outputs, logs and probes
are only in /tmp/kig-t092; no permuter output directory is a deliverable.

Promoted C has no inline asm, #line or register keyword. BF850/BFA40 retain
ordinary statement joins because separating them changes IDO scheduling;
comments document this. BFA40's named stride and input alias are ordinary
values. E4A0's alternate player views share the same underlying address and
preserve every existing function in that TU. No new rodata ownership is
needed by these six promotions. Matched drafts were deleted.

## Screener

`tools/permuter/screen.py` enumerates T2 status rows (including area-qualified
addresses), finds their remaining T-0xx drafts, and attempts complete owning-TU
compilation. Legacy conflicts fall back to TU-prefix compilation and then to
preprocessed TU declarations with explicit draft views taking precedence.
The last mode supplies audited missing shared sprite/global declarations for
older split-TU drafts. Context is explicit in every row; fallback scores are
not integration claims. The ELF reader masks only actual R_MIPS_26/HI16/LO16
relocation fields; stack offsets remain significant. Extra/missing words
count as differences. Errors remain visible rather than becoming fake scores.

The initial selection screen covered all 236 drafts. The delivered screen compiles all 230 drafts without errors and
covers the 230 drafts remaining after six promotions, sorted with equal-size
bodies first and then by differing words/name. Existing progress/status rows
are left for the lead. README documents invocation and dependencies. No ROM
bytes, object files or generated source are embedded in its report.

## Final verification

`make clean && make extract && make -j6 all && make progress` passed.
ROM and all executable images are byte-identical:

- ROM: ba52e91b44450c548467044b26951353dc491e04
- main: 81736d32e8cda8f399b319a49250dff972b81af8
- ovl_7DF8: ea830aae50ff1422da60d4b7fdbfc29f03b1be39
- ovl_7E00: 2b01138a290212b9d886981e1196f7b6fb45ecdb

`git diff --check` passed. No search/probe processes remain.

Generated progress documents were restored after recording this output.
Dependency symlinks are untracked and must not be staged. No commits.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 58,396 (20.15%) | 58,396 (20.15%) | 0 | 230 | 0 | 279 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 28,860 (20.04%) | 28,860 (20.04%) | 0 | 98 | 0 | 139 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 21,068 (15.33%) | 21,068 (15.33%) | 0 | 132 | 0 | 119 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
