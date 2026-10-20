# T-068 — sol-C26: four near-misses and compiler flags

Uncommitted work for lead review. **0 MATCHED, 0 IMPROVED, 4 UNCHANGED.** Production source, Makefile and incoming drafts are unchanged. Deleted drafts: **none**.

Read TRACKING.md, latest WORKLOG.md, Makefile, tu_boundaries.md and T-065/T-061/T-056/T-035/T-037 reports first. Missing baserom.us.z64, ROMs, .venv and tools/ext were symlinked from /home/rodri/Projects/killer-instinct-gold-n64. No ROMs were copied or committed.

## Results

Used IDO 5.3 with the T-056/T-061 TU-prefix method and isolated /tmp/t068-probe files. Scores count relocation-masked differing aligned words plus missing/extra words. Incoming baselines independently reproduce 6/6/6/8. Small scripts retain the focused substitutions, not bulky logs.

| Function | TU | Result | Body / target bytes | Evidence and remaining issue |
|---|---|---|---|---|
| func_801C7998 | 1BD90 | UNCHANGED (6) | 256 / 256 | Rechecked halfword mask and byte-result truncations. The two-word temporary is a widened switch expression, not an a2/a3 parameter. Tested unsigned intermediates/masks/constants and separate high/low union initialization. High-word sra/store versus zero store/move and 0x8000 materialization remain. No rodata changes. |
| func_801C5064 | 190B0 | UNCHANGED (6) | 404 / 404 | Assembly confirms lbu count/alpha, word list entries, 64-byte matrices and float fourth renderer argument through a3. Tested zero/depth initialization placement, literal forms and depth expressions. Zero/depth remain f24/f22 instead of f22/f24; depth-load scheduling differs. |
| func_801C2D34 | 13FF0 | UNCHANGED (6) | 552 / 552 | Rechecked word coordinate spills and fifth argument, matrix stride and 8-byte commands. Tested first/final store order, full-command assignment, member signedness/alignment and referenced-symbol types/address forms. First/final stores and final address/opcode materialization remain. |
| func_801C6A80 | 190B0 | UNCHANGED (8) | 292 / 292 | Rechecked unsigned frame comparison, lbu/sb flags and no-argument func_8002A8C4. Tested read/store expression forms, increment/assignment and volatile byte reads as diagnostics. Target uses separate flag load/store bases; compiler reuses the address. No wider flag retained. |

No declaration changes retained, no inline assembly or register-variable tricks. These focused follow-ups did not rerun the prior broad code-shape sweeps.

## Compiler-flag hypothesis

Tested the requested flags in order. Also compiled each complete TU's C contents with GLOBAL_ASM pragmas removed, comparing EVERY existing C function against original image bytes with actual ELF relocation masks. Baseline reproduces all 31/31 matches. flags.py and compact flags.json retain per-function evidence.

| Flags (common -G 0 -non_shared -Wab,-r4300_mul -32) | 7998 words | 5064 words | 2D34 words | 6A80 words | Existing matches 13FF0 / 190B0 / 1BD90 |
|---|---:|---:|---:|---:|---|
| -O2 -mips2 -Xcpluscomm | 6 | 6 | 6 | 8 | 7/7 · 10/10 · 14/14 |
| -O2 -mips1 -Xcpluscomm | 60 | 91 | 62 | 62 | 2/7 · 3/10 · 3/14 |
| -O1 -mips2 -Xcpluscomm | 70 | 100 | 184 | 88 | 1/7 · 3/10 · 1/14 |
| -O2 -mips2 without -Xcpluscomm | 6 | 6 | 6 | 8 | 7/7 · 10/10 · 14/14 |

-mips1 and -O1 are invalid for every tested TU: both break existing matches and worsen the drafts. Removing -Xcpluscomm preserves matches but makes no difference to these drafts. No per-object CFLAGS override is justified or retained. Unlike the pfs findings, there is no evidence for the tested alternate flags here. Rejection uses function-body comparisons; no full linked alternate-flag match is claimed.

## Final validation

make clean && make extract && make all && make progress passed (exit 0). ROM and all executable images are byte-identical:

- ROM: ba52e91b44450c548467044b26951353dc491e04
- main: 81736d32e8cda8f399b319a49250dff972b81af8
- ovl_7DF8: ea830aae50ff1422da60d4b7fdbfc29f03b1be39
- ovl_7E00: 2b01138a290212b9d886981e1196f7b6fb45ecdb

Generated progress files have no diff. T-066 functions and all restricted files untouched. No commits. git diff --check passed. Final progress:

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 63,068 (19.76%) | 63,068 (19.76%) | 0 | 286 | 0 | 276 | 437 (138,092) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 173,204 | 38,264 (22.09%) | 38,264 (22.09%) | 0 | 136 | 0 | 154 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 16,336 (11.89%) | 16,336 (11.89%) | 0 | 150 | 0 | 101 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
