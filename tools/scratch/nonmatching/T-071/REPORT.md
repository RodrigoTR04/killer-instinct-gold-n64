# T-071 — sol-C27: ovl_7DF8 source-line boundaries

**3 MATCHED (1,096 bytes), 8 IMPROVED, 8 UNCHANGED.** Uncommitted for lead review.

Read docs/TRACKING.md, latest WORKLOG.md, Makefile, T-067 (especially source-line boundaries), and T-066/T-065/T-062/T-061/T-057/T-053 reports before probing. Missing baserom.us.z64, ROMs, .venv and tools/ext were symlinked from `/home/rodri/Projects/killer-instinct-gold-n64`. No ROM was copied or committed.

## Method and results

Production IDO 5.3 -O2 -mips2 flags, with each draft compiled after its owning TU prefix. Scores count aligned differing instruction words plus length delta, masking actual ELF relocations. Every final draft retains the target body size. Only promoted functions have resolved-link equivalence verified by the full image/ROM comparisons.

The initial bounded sweep tested separate statements, own-line function/conditional braces, joined statement runs, and deterministic mixed line boundaries (up to 100 layouts per function). All seven clone siblings received independent baseline and layout checks. Greedy follow-up split shared boundaries wherever the best score survived, retaining the few necessary joins. Declaration splitting and zero-chain splitting were also screened, followed by small glyph result, unsigned switch-width, loop initialization, float-zero local and representative clone-counter experiments. Speculative glyph variants that removed the default assignment were diagnostic only and never retained. No volatile, register variables, inline assembly, #line, padding, flag changes, or output rewriting.

| Function | Result (words old→new) | Body bytes | Change / remaining issue |
|---|---|---:|---|
| func_801C4E38 | UNCHANGED 2→2 | 556 | Switch-value spill/reload remains sp+0x18 rather than sp+0x1C (+0x88/+0xB8). |
| func_801BF720 | UNCHANGED 2→2 | 104 | Default result remains v0 rather than v1 plus the return move (+0x1C/+0x64). |
| func_801BF914 | UNCHANGED 2→2 | 116 | Default-result register and return delay slot remain (+0x68/+0x70). |
| func_801C51F8 | MATCHED 2→0 | 160 | Own-line function brace and joined first command-word stores fix the first address/opcode scheduling swap. |
| func_801B6528 | UNCHANGED 3→3 | 596 | Card pointer reload still uses a0 rather than a2, plus its dependent loads (+0x178/+0x1A0/+0x1E8). |
| func_801C35D8 | MATCHED 4→0 | 384 | Joined command stores plus offset initialization before cloud initialization, sharing the line with do, fix command and loop setup scheduling. |
| func_801B695C | UNCHANGED 4→4 | 268 | Frame remains 0x30 rather than 0x28; entry/exit and argument-home offsets differ. |
| func_801C7998 | UNCHANGED 6→6 | 256 | High-word initialization and 0x8000 materialization remain (+0x08 through +0x1C). No rodata ownership changes. |
| func_801C5064 | IMPROVED 6→4 | 404 | Joining depth initialization with do fixes two scheduling words. Float zero/depth allocation remains (+0xB0/+0xBC/+0xE8/+0x114). |
| func_801C2D34 | MATCHED 6→0 | 552 | Own-line braces and joined first/final command-word stores recover all six scheduling differences. |
| func_801C7CD0 | UNCHANGED 6→6 | 380 | Replay-state base remains a2 rather than v1 (two address words and four stores). |
| func_801C6A80 | UNCHANGED 8→8 | 292 | Byte flag load/store base reuse remains (+0x44 through +0x64). |
| func_801B2010 | IMPROVED 23→17 | 420 | Joining each command pair removes six scheduling differences. Counter address/predicate allocation and lerp setup remain at +0x34..+0x74; subsequent command code matches under relocation masking. |
| func_801B21B4 | IMPROVED 23→17 | 420 | Joining each command pair removes six scheduling differences. Counter address/predicate allocation and lerp setup remain at +0x34..+0x74; subsequent command code matches under relocation masking. |
| func_801B2358 | IMPROVED 23→17 | 420 | Joining each command pair removes six scheduling differences. Counter address/predicate allocation and lerp setup remain at +0x34..+0x74; subsequent command code matches under relocation masking. |
| func_801B24FC | IMPROVED 23→17 | 420 | Joining each command pair removes six scheduling differences. Counter address/predicate allocation and lerp setup remain at +0x34..+0x74; subsequent command code matches under relocation masking. |
| func_801B26A0 | IMPROVED 23→17 | 420 | Joining each command pair removes six scheduling differences. Counter address/predicate allocation and lerp setup remain at +0x34..+0x74; subsequent command code matches under relocation masking. |
| func_801B2844 | IMPROVED 23→17 | 420 | Joining each command pair removes six scheduling differences. Counter address/predicate allocation and lerp setup remain at +0x34..+0x74; subsequent command code matches under relocation masking. |
| func_801B29E8 | IMPROVED 22→16 | 420 | Joining each command pair removes six scheduling differences. Counter address/predicate allocation and lerp setup remain at +0x34..+0x74; subsequent command code matches under relocation masking. |

Family A is **not solved**. Six siblings improve 23→17 and func_801B29E8 improves 22→16. The same readable layout improvement is retained independently in all seven drafts, including the last sibling's distinct global float start value.

## Delivered files

Replaced the three GLOBAL_ASM sites in `src/ovl_7DF8/ovl_7DF8_190B0.c` and `src/ovl_7DF8/ovl_7DF8_13FF0.c`; accompanying declarations use the existing best drafts. No existing matched definition was edited. Eight improved drafts were updated in place (seven T-025 clones and T-030/func_801C5064.c).

Deleted drafts:

- `tools/scratch/nonmatching/T-021/func_801C51F8.c`
- `tools/scratch/nonmatching/T-030/func_801C35D8.c`
- `tools/scratch/nonmatching/T-030/func_801C2D34.c`

`results.json` records fresh old/final scores and sizes; `remaining-offsets.json` records final mismatch offsets. The compact probe/generator scripts are retained, with isolated /tmp/t071-* compiler artifacts. Generators describe the staged experiment and expect incoming drafts from the parent revision; matched drafts and duplicate best candidates have been removed. No bulky logs or binaries are retained.

T-070's assigned functions, main, boot, ovl_7E00, YAML, Makefile, status.csv, TRACKING and WORKLOG are untouched. Generated progress documents were restored after recording the table. No commits.

## Final verification

`make clean && make extract && make all && make progress` **passed (exit 0)** after all production edits. `git diff --check` passed. The full byte comparisons verify all previously matched functions and resolve every relocation:

- ROM: `ba52e91b44450c548467044b26951353dc491e04`
- main: `81736d32e8cda8f399b319a49250dff972b81af8`
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 66,040 (20.70%) | 66,040 (20.70%) | 0 | 275 | 0 | 287 | 437 (138,092) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 173,204 | 39,772 (22.96%) | 39,772 (22.96%) | 0 | 129 | 0 | 161 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 17,800 (12.95%) | 17,800 (12.95%) | 0 | 146 | 0 | 105 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
