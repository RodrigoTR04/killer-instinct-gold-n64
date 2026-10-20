# T-053 — ovl_7DF8 finishing pass

Worker sol-B18. **2 MATCHED (500 bytes), 14 IMPROVED, 2 UNCHANGED.** No commits.

Read docs/TRACKING.md, latest docs/WORKLOG.md, Makefile and T-048/REPORT.md before experiments. Linked the missing baserom.us.z64, ROMs, .venv and tools/ext prerequisites from the authorized main checkout; no ROM files were copied or added to git.

## Results

Scores are differing aligned instruction words plus missing/extra words, masking actual ELF relocations, using IDO 5.3 and the production `-O2 -mips2` flags. Byte sizes exclude standalone compiler TU padding. `results.json` records the fresh baseline and final scores/sizes; `probe.py` is T-048's screen with process-specific temporary paths so independent sweeps cannot overwrite each other's objects.

| Function | Result | Draft bytes old → new / original | Change and remaining differences |
|---|---|---|---|
| func_801B18BC | MATCHED 4→0 | 300→300 / 300 | A `for (i = 0; i != 3; i++)` loop moves the initialization after the three address/constant completions. Removed dead x local/update; integrated and deleted draft. |
| func_801B6A68 | UNCHANGED 20 | 368 / 368 | Tried command-store permutations, shared/individual cursor groups, cursor increment forms, argument occupancy and equivalent texture-bank arithmetic. Constant registers and command scheduling remain. |
| func_801BF788 | MATCHED 21→0 | 200→200 / 200 | Build packed input as `(arg0[0] << 8) + arg0[1]`; update the two pointer parameters independently and store the final byte through `arg0[-1]` after advancing. This fixes prologue moves, load order and final temporary. Integrated and deleted draft. |
| func_801C51F8 | IMPROVED 26→2 | 160→160 / 160 | Five separate command pointer temporaries recover all registers. Only offsets 0x14/0x18 differ: first command ori and address addiu are exchanged. |
| func_801C6A80 | UNCHANGED 30 | 292 / 292 | Tried phase/local widths, direct/global comparisons, typed audio-call prototypes, equivalent comparisons/increments and return/argument forms. Global bases, temporary registers and scheduling remain. |
| func_801B2010 | IMPROVED 87→23 | 412→420 / 420 | Explicit old-counter predicate and increment, using otherwise unused scalar parameters as ordinary temporaries; separate command allocation. Counter address/predicate registers and command scheduling remain. |
| func_801B21B4 | IMPROVED 87→23 | 412→420 / 420 | Same family-A change; same remaining differences. |
| func_801B2358 | IMPROVED 87→23 | 412→420 / 420 | Same family-A change; same remaining differences. |
| func_801B24FC | IMPROVED 87→23 | 412→420 / 420 | Same family-A change; same remaining differences. |
| func_801B26A0 | IMPROVED 87→23 | 412→420 / 420 | Same family-A change; same remaining differences. |
| func_801B2844 | IMPROVED 87→23 | 412→420 / 420 | Same family-A change; same remaining differences. |
| func_801B29E8 | IMPROVED 88→22 | 412→420 / 420 | Same family-A change, retaining its global float start value. Counter/address and command scheduling remain. Fresh old score is 88, as T-048's detailed table records. |
| func_801B2EF4 | IMPROVED 88→70 | 536→536 / 536 | Postincrement condition, u16 masked color, separate command temporaries and final command-store order. Counter/global bases, alpha slot, unsigned conversion registers and scheduling remain. |
| func_801B310C | IMPROVED 88→70 | 536→536 / 536 | Same family-B change; same remaining differences. |
| func_801B3324 | IMPROVED 88→70 | 536→536 / 536 | Same family-B change; same remaining differences. |
| func_801B353C | IMPROVED 88→70 | 536→536 / 536 | Same family-B change; same remaining differences. |
| func_801B3754 | IMPROVED 88→70 | 536→536 / 536 | Same family-B change; same remaining differences. |
| func_801B396C | IMPROVED 88→70 | 536→536 / 536 | Same family-B change; same remaining differences. |

## Experiments and follow-up

Each representative received multiple sweeps, followed by targeted assembly inspection. The initialization loop received 288 combinations. Command experiments included store order, cursor spelling, individual versus shared pointer locals, declaration/member signedness, raw equivalent arithmetic, constant/address locals and return/prototype variations. The larger command-cursor sweep alone tried 4,096 combinations; the five-command pointer sweep tried 1,536. Counter experiments included postfix/prefix forms, explicit old-value predicates, per-branch versus common stores, signed/unsigned/short counters, local limits, and reusing unused scalar parameters. The unpacker received loop direction/form, local order, input expression, pointer parameter/local and final load/store lifetime experiments. The phase function received 384 combinations. Non-equivalent or invalid candidates were discarded.

An early concurrent sweep exposed T-048/probe.py's shared `/tmp/t048-probe` filenames. Those runs were stopped; retained results were re-screened with process-specific paths. All clone siblings were screened independently after applying their representative's change.

Neither clone family is solved. Family A now has the original body length, but the original loads the counter directly into a2, computes its predicate in v0, increments a2 in the branch delay slot and emits separate symbolic stores. The retained draft still uses a different counter-address/predicate allocation. Family B retains the original draft's uninitialized alpha read on its late branch; the target itself reads the old stack alpha byte there. Do not treat either family's better screen as behavior validation or integrate it without a byte match.

The nearest remaining target is func_801C51F8: all five pointer allocations and all registers now agree, with just the first command's addiu/ori order exchanged. Separate pointers are essential; replacing them with one shared pointer gives the earlier 26-word mismatch. Additional first-command address/constant local ordering, pointer types, store order and increment placement did not remove the last two words.

Deleted drafts:

- tools/scratch/nonmatching/T-025/func_801B18BC.c
- tools/scratch/nonmatching/T-023/func_801BF788.c

Only these two GLOBAL_ASM functions were replaced. Improved drafts remain in their original directories. No Makefile, YAML, status.csv, main, boot or ovl_7E00 source edits were made.

## Final verification

`make clean && make extract && make all && make progress` passed. ROM SHA1 is `ba52e91b44450c548467044b26951353dc491e04`, and the full byte comparison passed. All executable images also passed byte comparison:

- main: `81736d32e8cda8f399b319a49250dff972b81af8`
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`

T4 increases 250→252; ovl_7DF8 increases 90→92. Matched bytes increase 51,716→52,216. `git diff --check` passed. Generated docs/functions.csv and docs/progress.html were restored after recording this output; status.csv is untouched for lead review.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 52,216 (16.36%) | 52,216 (16.36%) | 0 | 310 | 0 | 252 | 437 (138,092) |
| boot | 8,468 | 8,108 (95.75%) | 8,108 (95.75%) | 0 | 1 | 0 | 20 | 99 (16,028) |
| main | 173,204 | 29,404 (16.98%) | 29,404 (16.98%) | 0 | 150 | 0 | 140 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 14,704 (10.70%) | 14,704 (10.70%) | 0 | 159 | 0 | 92 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
