# T-065 — sol-C25: argument-width follow-up

Uncommitted work for lead review. **11/11 attempted: 0 MATCHED, 3 IMPROVED, 8 UNCHANGED.** No production source or declaration changes. Deleted drafts: **none**.

Read docs/TRACKING.md, latest docs/WORKLOG.md, Makefile, and reports T-061, T-056, T-060 and T-048 before probing. Missing baserom.us.z64, ROMs, .venv and tools/ext were symlinked from `/home/rodri/Projects/killer-instinct-gold-n64`; no ROM content was copied into git.

## Method

Used IDO 5.3 with the production `-O2 -mips2` flags. Every candidate compiled inside its owning TU prefix using the T-056/T-061 tools, with separate `/tmp/t065-probe` output. Scores count differing aligned words plus missing/extra words, masking actual ELF relocations. `results.json` records fresh incoming and final scores and sizes. `tu.py`, `probe.py` and `ad.py` reproduce final measurements; no bulky round logs are retained.

Inspected original entry spills, extensions, call setup and global access widths before focused experiments. Checked calls to the targets and the text renderer's assembly. In particular, func_801BE540 loads its fourth argument as a float and its color/alpha arguments as bytes. The existing drafts incorrectly declared the fourth argument as an integer. The 7998 switch really uses a two-word temporary even though its parameter is a halfword; its table covers indices 0 through 32 and index zero selects the default return. No register bindings, inline assembly, padding tricks or compiler changes.

## Every requested function

| Function | Result (words old→new) | Final / target bytes | Attempt and remaining issue |
|---|---|---|---|
| func_801C2D34 | UNCHANGED (6) | 552 / 552 | Call sites confirm five full-word arguments; matrix offsets use 64-byte records. Tested display-list symbol element types, complete 64-bit commands and word access forms after checking declarations. First/final command stores and address/opcode scheduling remain. |
| func_801C6A80 | UNCHANGED (8) | 292 / 292 | Confirmed full-width unsigned frame comparison and byte phase/flags. Tested cached flag values, scalar/one-element-array declarations and assignment forms. Target separately materializes the flag's load and store bases; compiler reuses its address. Wider flag declarations were not retained. |
| func_801B1210 | IMPROVED 39→38 | 284 / 284 | Correct fourth text-renderer argument to f32 and pass 0.0f. Tested input widths, typed query, alpha/input reuse and byte renderer arguments. Alpha/global registers and command/call scheduling remain. |
| func_801C7998 | IMPROVED 55→6 | 256 / 256 | Use u8 result, explicitly handle zero with break, and widen the masked halfword expression for the switch. The zero case preserves behavior while recovering the original zero-based jump table. Tested signed/unsigned input/local widths and equivalent mask/widen forms. High-word initialization emits sra/store instead of target zero store/move; 0x8000 materialization also differs. No integration: code is still nonmatching and TU rodata ownership would need review. |
| func_801C0610 | UNCHANGED (71) | 372 / 372 | Checked matrix loads and helper arguments; tested pointer-valued matrix base and aligned command union. Matrix/global and display-command register allocation remain. Existing TU has a later two-argument declaration/call; no production declaration was changed. |
| func_801BBB60 | UNCHANGED (71) | 296 / 292 | Global address differences establish 4096-byte and 64-byte fill regions and a halfword palette. Tested explicit fill array sizes and unsigned halfword palette elements. Palette unrolling/store/base scheduling remain. |
| func_801C6D40 | UNCHANGED (74) | 316 / 300 | Confirmed byte phase accesses and full-width unsigned time arithmetic. Tested explicit phase pointer and first-parameter widths. Phase/control-flow allocation and unsigned floating conversion remain. Kept the original draft's call forms after prior T-060 arity experiments. |
| func_801C49A8 | UNCHANGED (85) | 548 / 548 | Checked seven-argument callers and eight-argument rendering helper; record stride is 28 bytes and flags/colors are byte loads. Tested coordinate parameter widths. Frame, flag spills, cached mode and call scheduling remain. |
| func_801C3E40 | UNCHANGED (88) | 504 / 504 | Checked 48-byte triangle stride, signed byte velocities and byte alpha. Tested aligned matrix-array shape and vertex flag signedness. Vertex updates and command/global scheduling remain. |
| func_801CC3BC | UNCHANGED (88) | 364 / 360 | Rechecked one-argument Pak checker and full-word shift/mask behavior. Tested slot parameter widths without narrowing the mask. Saved flags/mask registers and error-chain scheduling remain; retained the full-width mask. |
| func_801C5064 | IMPROVED 93→6 | 404 / 404 | Correct renderer fourth argument to f32 and alpha to u8. Reload count after each rendering call, as the original does; reload before updating the matrix index. Spell origin as negative count times positive 20. This recovers frame, saved registers and integer scheduling. Remaining six words allocate zero/depth to f24/f22 instead of f22/f24 and schedule the depth load differently. Tested byte color prototypes, pointer globals, parameter widths and zero/depth locals. |

## Disposition

Updated drafts in place:

- `T-025/func_801B1210.c`
- `T-030/func_801C7998.c`
- `T-030/func_801C5064.c`

All other requested drafts are unchanged. No functions matched, so no GLOBAL_ASM replacements or draft deletions. T-062's six assigned functions were untouched. Main, boot, ovl_7E00, all YAML, Makefile, status.csv, TRACKING.md and WORKLOG.md are unchanged. No commits.

## Final validation

`make clean && make extract && make all && make progress` passed (exit 0). ROM comparison and all three executable-image comparisons passed:

- ROM: `ba52e91b44450c548467044b26951353dc491e04`
- main: `81736d32e8cda8f399b319a49250dff972b81af8`
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`

`git diff --check` passed. Generated progress files have no final diff. Final progress is unchanged:

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 62,548 (19.60%) | 62,548 (19.60%) | 0 | 288 | 0 | 274 | 437 (138,092) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 173,204 | 37,944 (21.91%) | 37,944 (21.91%) | 0 | 137 | 0 | 153 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 16,136 (11.74%) | 16,136 (11.74%) | 0 | 151 | 0 | 100 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
