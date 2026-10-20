# T-067 — sol-B22

**7 MATCHED (1,508 bytes), 3 IMPROVED, 5 UNCHANGED.** No commits.

## Flag hypothesis first

Read TRACKING, latest WORKLOG, Makefile, tu_boundaries and T-058/T-040/T-064/T-035/T-037 reports before probing. Missing baserom.us.z64, ROMs, .venv and tools/ext were symlinked from the authorized main checkout; no ROM was copied or added to git.

IDO 5.3 production flags are `-c -G 0 -non_shared -Xcpluscomm -Wab,-r4300_mul -O2 -mips2 -32 -Iinclude`. Tested the existing best drafts with baseline, `-mips1`, removing `-Xcpluscomm`, adding `-signed`, and `-mips1 -signed` (75 compiler results). The 17378 draft needs its owning TU's declarations; its results use that context. Other draft flag results are standalone, as in T-058. Counts mask only actual ELF relocation fields; size mismatches reject a match independently.

No alternative flags matched a target. `-signed` and removing `-Xcpluscomm` retained baseline counts for every target; combining `-mips1 -signed` gave the same counts as `-mips1`. **No Makefile change is retained.**

| Function | TU | Baseline words / bytes | -mips1 words / bytes |
|---|---|---:|---:|
| func_8002DF98 | main_1BE80 | 2 / 244 | 40 / 240 |
| func_8002B95C | main_1BE80 | 2 / 88 | 2 / 88 |
| func_8002B7E0 | main_1BE80 | 2 / 208 | 5 / 208 |
| func_8002B57C | main_1BBA0 | 4 / 368 | 62 / 392 |
| func_8002B1EC | main_1B230 | 4 / 64 | 12 / 68 |
| func_8002B91C | main_1BE80 | 4 / 64 | 8 / 64 |
| func_8002DCC8 | main_1BE80 | 4 / 268 | 27 / 264 |
| func_8002AA98 | main_1AB90 | 9 / 80 | 17 / 80 |
| func_8002AAEC | main_1AB90 | 9 / 80 | 17 / 80 |
| func_80017378 | main_2FF0 | 8 / 1752 | 107 / 1748 |
| func_8002A300 | main_1A880 | 7 / 268 | 8 / 268 |
| func_8002AEE4 | main_1B230 | 13 / 336 | 66 / 364 |
| func_8002A900 | main_1AB90 | 18 / 220 | 43 / 228 |
| func_80015F6C | main_2FF0 | 21 / 268 | 61 / 280 |
| func_8002F45C | main_1EB40 | 27 / 404 | 81 / 416 |

As additional negative evidence, compiled the existing C in every owning TU with all GLOBAL_ASM stubs removed and compared each existing `func_` definition to the original image. All baseline C functions have zero masked differences. The counts below are existing C functions changed by each flag, not assertions that nonzero changes could be retained. Some TUs include SDK-named C definitions not enumerated by this helper; no whole-TU compatibility claim is made for a new flag. There is no candidate flag match to justify installing a per-object override or testing it in the production linker.

| TU | Existing func_ definitions checked | -mips1 changed | no -Xcpluscomm changed | -signed changed |
|---|---:|---:|---:|---:|
| main_1A880 | 2 | 1 | 0 | 0 |
| main_1AB90 | 5 | 5 | 0 | 0 |
| main_1B230 | 2 | 2 | 0 | 0 |
| main_1BBA0 | 3 | 2 | 0 | 0 |
| main_1BE80 | 6 | 6 | 0 | 0 |
| main_1EB40 | 15 | 10 | 0 | 0 |
| main_2FF0 | 46 | 32 | 0 | 0 |

## Why seven tiny misses finally match

While formatting A900 for review, the exact same C tokens scored 15 words rather than 16. This exposed a missing dimension in the earlier searches: **IDO 5.3 instruction scheduling depends on source line boundaries**, even with these production flags. A bounded test of eight token-preserving layouts for all 15 targets produced seven zero-difference functions. Breaking statements or braces onto separate source lines solved their old scheduling swaps. No `#line`, volatile workaround, inline assembly, register variable, toolchain patch or output rewriting is used. Ordinary multiline C is sufficient. This also explains why thousands of token variants in dense one-line drafts could retain the same scheduling miss.

All seven candidates were checked in their owning C context and then promoted together. A300's redundant incompatible u8 declarations were omitted so it uses the owning TU's s32 decoder arrays. B7E0's forward declarations use the actual B8B0 s32 parameter and B95C u16 pointer. These declaration reconciliations retain zero differences. Full linked image/ROM verification confirms the resolved relocation operands and all previously matched functions, rather than relying on masked scores.

Additional bounded probes used logical local records, explicit wait-loop exits and bound locals, derived quit values, RGB aggregate stores, and a cursor/endpoint record for 17378. These do not repeat T-058's large statement/declaration permutation search. The compact experiment-summary.json records the batch sizes; generated per-candidate logs and duplicate candidates were removed.

## Per-function result

| Function | Result | Remaining / evidence |
|---|---|---|
| func_8002DF98 | MATCHED, 244 B | Multiline body; linked image exact |
| func_8002B95C | MATCHED, 88 B | Function brace on its own line; linked image exact |
| func_8002B7E0 | MATCHED, 208 B | Separate statement lines; linked image exact |
| func_8002B57C | MATCHED, 368 B | Separate statement lines; linked image exact |
| func_8002B1EC | UNCHANGED, 4 words | Separate load/store address materialization; line variants and redundant-store expressions did not solve it |
| func_8002B91C | MATCHED, 64 B | Multiline body fixes both home-store swaps |
| func_8002DCC8 | MATCHED, 268 B | Multiline body fixes both schedule pairs |
| func_8002AA98 | UNCHANGED, 9 emitted words + missing word | Still 80/84 B; multiply/sign-extension/tail move shape |
| func_8002AAEC | UNCHANGED, 9 emitted words + missing word | Still 80/84 B; same scaling family |
| func_80017378 | UNCHANGED, 8 words | 1752/1752 B; endpoint/base setup and loop increment/store scheduling, as in T-064; cursor records and line variants do not improve it |
| func_8002A300 | MATCHED, 268 B | Separate statement lines solve the seven prologue differences |
| func_8002AEE4 | IMPROVED 13→3 | 336/336 B; +0x48 message-address setup, +0x9C/+0x108 quit constant register vs immediate; resolved-link count also 3 |
| func_8002A900 | IMPROVED 18→15 | 220/220 B; explicit loop bound and exit tests, multiline body; +0x00..0x24 prologue, +0x34 DMA setup, +0x58..0x64/+0x6C stop/wait setup; resolved-link count also 15 |
| func_80015F6C | UNCHANGED, 21 words | 268/268 B; white constant allocation and ensuing temporary register numbering; RGB aggregates and line variants do not help |
| func_8002F45C | IMPROVED 27→20 | 404/404 B; separate statements improve scheduling; frame 0x30 vs target 0x38, spills, pan/temp allocation and stores remain; resolved-link count also 20 |

Deleted drafts (all under `tools/scratch/nonmatching/T-024/`):

- func_8002DF98.c
- func_8002B95C.c
- func_8002B7E0.c
- func_8002B57C.c
- func_8002B91C.c
- func_8002DCC8.c
- func_8002A300.c

The three improved drafts remain in T-024. No boot/overlay source, YAML, status.csv, TRACKING or WORKLOG changes. No Makefile change. No commits.

## Final verification

`make clean && make extract && make -j8 all && make progress` **passed** after all promotions. The parallel flag only schedules independent build jobs.

- ROM: `ba52e91b44450c548467044b26951353dc491e04`, byte-identical.
- main: `81736d32e8cda8f399b319a49250dff972b81af8`, byte-identical.
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`, byte-identical.
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`, byte-identical.
- `git diff --check` passed.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 64,576 (20.24%) | 64,576 (20.24%) | 0 | 279 | 0 | 283 | 437 (138,092) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 173,204 | 39,772 (22.96%) | 39,772 (22.96%) | 0 | 129 | 0 | 161 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 16,336 (11.89%) | 16,336 (11.89%) | 0 | 150 | 0 | 101 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
