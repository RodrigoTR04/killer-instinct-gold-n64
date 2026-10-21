# T-125 — sol-B40

Three functions promoted to matching C: **2,188 bytes / 2,030-byte target** (0.7548% of the 289,876-byte metric), exceeding the target by **158 bytes**. Three additional improved drafts are retained. No commits.

## Per-function results

Words are differing corresponding instruction words, with relocation fields masked, including missing/extra words. Permuter weighted scores are different measurements. Only full-TU zeros verified by the linked build are promotions.

| Function | Original bytes | Differing words before → retained | Result/context |
|---|---:|---:|---|
| func_800131A4 | 712 | 41 → 0 | T4; full TU and linked image match |
| func_800287D4 | 556 | 77 → 0 | T4; reconciled full TU and linked image match |
| func_8002A4F0 | 920 | 27 → 0 | T4; full TU and linked image match |
| func_801C3758 | 564 | 32 → 30 | Improved; 572 → 564 B, full TU |
| func_801C2F5C | 544 | 53 → 47 | Improved; 548 → 544 B, full TU |
| func_80024714 | 712 | 69 → 69 | Unchanged; 712 B, declarations context |
| func_801C2ADC | 600 | 71 → 71 | Unchanged; 600 B, full TU |
| func_801C49A8 | 548 | 83 → 83 | Unchanged; 548 B, full TU |
| func_801C3E40 | 504 | 88 → 88 | Unchanged; 504 B, declarations context |
| func_801AFFAC | 576 | 99 → 99 | Unchanged; 576 B, full TU |
| func_8002AB90 | 852 | 119 → 119 | Unchanged; 852 B, full TU |
| func_801C3AA0 | 928 | 119 → 119 | Unchanged; 928 B, full TU |
| func_801B0520 | 328 | 22 → 22 | Unchanged; 328 B, full TU |
| func_801B1210 | 284 | 28 → 28 | Unchanged; 284 B, full TU |
| func_801B446C | 292 | 28 → 28 | Unchanged; 292 B, full TU |
| func_8001AA90 | 496 | 60 → 60 | Unchanged; 488 B, full TU |
| func_8002FB80 | 544 | 67 → 23 | Improved; 536 → 544 B, full TU |

The three promoted GLOBAL_ASM pragmas were replaced and their drafts deleted. None of the promoted functions owns rodata constants, so no symbol ownership hints required removal. Protected tracking, worklog and status files were not edited.

## Findings

- **800131A4:** A seven-byte array view preserves the intended address arithmetic. A full-width loop variable with an explicit signed-halfword update recovers the saved-register allocation. Independent command-pointer scopes recover the remaining command constant allocation. Source statement boundaries affect IDO scheduling; the integrated form was measured in its full TU before promotion.
- **800287D4:** Removing the cached particle pointer and using direct two-dimensional array references recovers pointer reloads and the exact target. The permuter zero contained an unused pointer declaration and an empty statement; both were removed and the zero reverified. Its draft's alternate particle declaration conflicted with the later matched initializer. Moving the existing TU declaration before the new function and using its existing `active` field (the same signed halfword as the draft's `speed`) reconciles the types without changing the initializer. Full-TU score is zero.
- **8002A4F0:** Direct halfword destination stores and an in-place odd-length increment recover the byte-offset induction loop. Separate bank and sequence allocation lengths recover the stack layout. The final two words were the allocation-size stores to `sp+0x10` and `sp+0x38`, exchanged around the allocator call. Saving the DMA length separately while calculating the allocator argument directly from the sequence count lets IDO share the arithmetic and emit the required store order. There are no extra operations, artificial branches or padding. The final full-TU score is zero.
- **801C2F5C:** A byte temporary for the final selector and joined statement boundaries recover exact size and six differing words. The permuter supplied a redundant `do/while (0)` wrapper; removing it and its scope preserves the 47-word result. The temporary was given a meaningful name.
- **801C3758:** A masked animation increment and conditional selection recover the original size and avoid spilling the display-list argument. Initial animation value duplication, UV-pointer allocation and command-pointer allocation remain different.
- **801C49A8:** The target reloads the mode byte after the first drawing callback. The old draft caches it across that callback. Correcting that reload did not improve the measured draft, so no speculative rewrite was retained.
- **8002AB90:** The target keeps a DMA-loop count and the current buffer separately. The compiler eliminates the draft's count in favor of an end pointer; the draft also has an eight-byte larger frame. Pointer/index and rounding-expression probes did not improve the retained result.
- **8002FB80:** Branch-local output-cursor updates recover the two missing instructions. Reversing the address summands with an explicit signed intermediate prevents unsigned reassociation, and moving the final texture-byte source read before address stores recovers further scheduling. The retained draft is exact size, with 23 differing words; address-byte and texture-byte register allocation/scheduling remain.

Low weighted permuter scores were audited rather than promoted automatically. Rejected results included empty/constant branches, dummy labels, truncating a display-list pointer into a byte index, removing an alpha mask, writing flags through a position cursor, and recomputing a particle destination after incrementing its index. Removing constant branches from several apparent improvements restored their baseline score. None of these constructs is retained.

## Searches and evidence

Read the requested tracking conventions, recent worklog, overview, clones, permuter documentation, T-121/T-122 reports and October 21 screen. Prerequisites were symlinked from the authorized shared checkout; no ROM was copied or added. No subagents were used.

Instruction-level disassembly and focused C variants preceded the searches. Permuter runs used `--stack-diffs --stop-on-zero --best-only --better-only`, bounded at 300, 600 or 900 seconds. Full context inputs had unrelated GLOBAL_ASM pragmas removed before stripping other function bodies. An earlier batch accidentally retained unrelated assembly stubs; it was stopped and its results discarded. Corrected inputs produced the audited 800287D4 zero. Search logs, generated candidates, disassembly and objects are in `/tmp/t125-*`; bulky output is not added to the repository.

## Final validation

`make clean && make extract && make -j6 all && make progress` passed. ROM and all executable images are byte-identical:

- ROM: `ba52e91b44450c548467044b26951353dc491e04`
- main: `81736d32e8cda8f399b319a49250dff972b81af8` (239,824 B)
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39` (957,392 B)
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb` (153,904 B)

Validation log: `/tmp/t125-final-validation.log`. `git diff --check` passes. Generated progress inventory/HTML reflect the three promotions; `status.csv`, TRACKING and WORKLOG remain unchanged.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 77,796 (26.84%) | 77,796 (26.84%) | 0 | 184 | 0 | 325 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 35,964 (24.98%) | 35,964 (24.98%) | 0 | 84 | 0 | 153 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 33,364 (24.28%) | 33,364 (24.28%) | 0 | 100 | 0 | 151 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
