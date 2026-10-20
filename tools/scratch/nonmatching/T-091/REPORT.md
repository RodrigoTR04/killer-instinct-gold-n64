# T-091 — sol-B30: rodata ownership sweep

Ten additional TUs own their complete identified pools: five main and five
ovl_7DF8. No new functions landed. No commits or function-body edits.
All offsets below are decompressed image offsets, end exclusive; boundaries
are 16-byte aligned. Each candidate was extracted and rebuilt separately.

| TU | Range | Final result / evidence |
|---|---|---|
| main_1BE80 | 0x39410–0x39580 | done; BBD0 constants plus existing C constants at both pool ends |
| main_1E7F0 | 0x39580–0x39650 | done; E150 strings, doubles and padding |
| main_1EB40 | 0x39650–0x39690 | done; E724 switch table and alignment |
| main_27490 | 0x39780–0x39790 | done; guRotateRPYF float and alignment |
| main_2B780 | 0x399f0–0x39a00 | done; alCents2Ratio constants and alignment |
| ovl_7DF8_2380 | 0xe6cc0–0xe6cd0 | done; AF424 float and alignment |
| ovl_7DF8_3F60 | 0xe6cd0–0xe6e40 | done; strings, both switch tables and floating pools |
| ovl_7DF8_5ED0 | 0xe6e40–0xe7030 | reverted; indirect strings initially undefined; hints link but image differs (f91b3743…). Needs pool ordering/type investigation |
| ovl_7DF8_116E0 | 0xe7030–0xe7070 | done; four-double group and other doubles; corrected end excludes next TU strings |
| ovl_7DF8_17E70 | 0xe7ca0–0xe7cc0 | done; 3990 float, 3AA0 double, 3E40 float and alignment |
| ovl_7DF8_13FF0 | 0xe7160–0xe7ca0 | reverted; indirect strings initially undefined; hints link but image differs (0c85d325…). Needs string ordering/alignment investigation |
| ovl_7DF8_1B790 | 0xe8da0–0xe93f0 | done; entire credits string pool and five floats |
| ovl_7DF8_1BD90 | 0xe93f0–0xe9a40 | reverted; existing C and indirect strings initially undefined; hint retry still nonmatching; retain original assembly fragment |

The original 116E0 attempt extended through 0xE70D0 and was reverted.
0xE7070 begins LEGENDS/STREAKS/FATALS/SPEED/HITS/DAMAGE and initials,
indirectly referenced through D_80282DD0/D_80282DE8 by 12C70 and 13FF0.
They remain asm-owned. The existing 12C70 ownership therefore remains partial;
this sweep does not claim every TU is fully migrated. 18CC0 has no pool
references. Main TUs without references do not need empty .rodata segments.
`inventory.json` records every main/overlay C TU, retained ownership range,
and direct references from C and GLOBAL_ASM. Its scan is limited to the known
late rodata regions; it is not proof that earlier mutable-data references are
constant pools. main_CA10's earlier pool was already owned before this task.
Unassigned main 0x39A00 is the SDK NaN object; 0x39D60 onward is graphics
vertex/display-list data. These were not guessed into an unrelated TU.

## Hints and implementation

Remaining fragments use data with linker_section_order .rodata. No Makefile
changes. Existing matched C bodies and all reserved functions are untouched.
New force_migration/function_owner hints preserve:

- main D_80048D70 / D_80048EDC in func_8002BBD0 (matched C extern users).
- main D_80048EE0 / 48F10 / 48F38 / 48F58 in func_8002E150 (strings).
- overlay D_802927E0 in func_801ADEA0 (matched AF424 extern user).
- eight indirect strings D_80292814–D_80292870 in func_801B1210.
- credits strings D_802948C0–D_80294ED8 in func_801C7310, preserving
  the original data-pointer-table references and pool order.

When promoting these asm owners, retain/reassign their reserved constants.
Rejected candidates' hints were also reverted. No padding arrays, inline asm,
register bindings, binary rewriting or compiler changes were used.

## Draft re-test

`report-search.txt` is the requested repository report grep. Previously exact
rodata-only bodies (ADCFC, CBCCC, 18E88, 2A004, 1CBCC, 330B0, C67CC)
already landed before this task. BF720/BF914 belong to T-088 and still have
instruction differences per T-043/T-061; they were not edited.
`screen.txt` re-tests retained drafts in the thirteen candidate TUs through
T-055/ctx.py using production TU context and IDO flags. No compiled candidate
has zero masked instruction differences. Some old drafts fail declaration
reconciliation; these failures are recorded, not claimed to be matches or
exhaustive proof of nonmatchability. Reserved functions were excluded.
No draft was deleted or promoted.

## Validation

Local prerequisites are symlinks to /home/rodri/Projects/killer-instinct-gold-n64.
ROMs were never copied or added to git. Final validation and progress below.

Final `make clean && make extract && make all && make progress` passed
(exit 0), serially. ROM SHA1 ba52e91b44450c548467044b26951353dc491e04.
All three image hashes remain original:
main 81736d32e8cda8f399b319a49250dff972b81af8;
ovl_7DF8 ea830aae50ff1422da60d4b7fdbfc29f03b1be39;
ovl_7E00 2b01138a290212b9d886981e1196f7b6fb45ecdb.
`git diff --check` passes. Regenerated undefined_syms files are retained.
TRACKING/WORKLOG/status.csv and generated progress documents have no net edits.
Migration scripts are historical experiment drivers, not idempotent tools;
results.json records all rounds, with the last row per TU authoritative.
The final per-TU table above supersedes provisional range guesses.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 56,616 (19.53%) | 56,616 (19.53%) | 0 | 238 | 0 | 271 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 27,560 (19.14%) | 27,560 (19.14%) | 0 | 102 | 0 | 135 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 20,588 (14.98%) | 20,588 (14.98%) | 0 | 136 | 0 | 115 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
