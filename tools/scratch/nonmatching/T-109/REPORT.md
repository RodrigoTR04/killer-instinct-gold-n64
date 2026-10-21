# T-109 — sol-A37: diagnosis-driven near misses

**3 MATCHED (964 B), 1 IMPROVED, 6 UNCHANGED. No commits.**

Work remains uncommitted for lead review. Read TRACKING, latest WORKLOG,
overview, Makefile, permuter README, T-104/T-105 diagnoses, T-096/T-097,
and T-067 scheduling notes. Missing baserom.us.z64, ROMs, .venv and tools/ext
were symlinked from the authorized shared checkout. No ROM was copied or
added to git. The audio TUs owned by T-108 were skipped entirely.

## Method

Production IDO 5.3 -O2 -mips2 through asm-processor throughout. Comparisons
count differing aligned instructions plus length differences, masking only
actual ELF relocation fields. Full owning-TU compilation is preferred;
C85C0's legacy declaration fallback is explicitly distinguished below.
A masked zero is only a candidate until the linked images and ROM match.

Concrete C probes precede ordinary token-preserving line layouts. Search
inputs and compiler products stay under /tmp/kig-t109, outside git. No inline
assembly, #line, register keyword, padding objects, new compiler flags,
binary rewriting, or unrelated source changes are used.

## Per-function results

| Function | Hypothesis tested | Result | Remaining diagnosis / evidence |
|---|---|---|---|
| func_801CB998 | Use the incoming byte argument directly instead of creating a separate flags local. | MATCHED, 2→0; 148 B | This gives the preserved flags value its target sp+1C spill instead of sp+18. The existing packed-u64 callee ABI is retained. Clean full-TU zero, integrated and draft deleted. |
| func_801CC908 | Remove the dead mask home, permute the five remaining declarations, consolidate status aliases, and test meaningful handle/mask records. | UNCHANGED, 2; 424 B | Only allocation/free at +0C/+19C remain 0x40 instead of 0x30. Smaller frames disturb the otherwise-correct mask/handle/status slots. No padding local retained. |
| func_800269AC | Reverse or combine the primitive-command stores, delay cursor advancement, and vary their line grouping. | UNCHANGED, 2; 236 B | The primitive pair at +88/+8C still has reversed scheduling. All display-list cursor advances and command positions are preserved. |
| func_801C85C0 | Precompute the next-index argument before clears, vary index widths, and reconcile the owning TU's actual arrays and callee prototype. | UNCHANGED, 4; 168 B in declaration fallback | Index add/mask at +48/+4C remain after the first clears. Compatible arrays plus an explicit u8 argument cast also reproduce 4 words / 168 B in the full TU. The four-word order miss persists. |
| func_801B5534 | Byte parameter and index views, K&R byte input, explicit narrowing, and sample initialization layouts. | UNCHANGED, 5; 168 B | Target byte home reloads and move-only call argument are coupled to a different spill slot. Byte parameter alone changes size/order and is worse. |
| func_801BF678 | Express the pointer and counter decrement as a for-loop update instead of statements in the do-while body. | MATCHED, 7→0; 168 B (was 164 B) | Recovers decrement before mflo, pointer decrement before branch and target nop. A combined for initializer preserves setup constant order. Readable full-TU zero, integrated and draft deleted. |
| func_801BD270 | Reassociate the 64-bit axis/button sum and test an explicitly unsigned low word and bitwise packing. | UNCHANGED, 7; 396 B | High-word addition, carry and sign contribution at +154..+170 remain. No signedness change is promoted. |
| func_8001BDE0 | Preserve the threshold in a local, then reuse the incoming float argument for the scale; also test declaration/load order, comparisons and structured loops. | IMPROVED, 9→8; 316 B | Offset now owns target f24. Threshold and scale own f22/f20 rather than f20/f22; saves, multiply operands and comparisons follow them. Independently checked in the full TU and saved to its original draft. Mutable global reads and float arithmetic are preserved. |
| func_8001E0B4 | Put the counter in a for initializer, then snapshot the scale flag between high-bit evaluation and the shared fade clear. | MATCHED, 9→0; 648 B | For-loop setup fixes six counter/global-base scheduling differences. The scale-flag snapshot and clear order fix the last three. Cleaned to named locals and direct field casts; full-TU zero, integrated and draft deleted. |
| func_801C47E0 | Reuse incoming bank, vary offset/bank widths, split page/payload offsets, and commute pointer/return additions. | UNCHANGED, 11; 260 B | Temporary ownership and commutative addu operands remain at the T-105 offsets; target frame and slots already agree. |

## Validation

`make clean && make extract && make -j6 all && make progress` passed (exit 0).
The parallel flag only schedules independent build jobs. ROM and all three
executable images are byte-identical:

- ROM: ba52e91b44450c548467044b26951353dc491e04
- main: 81736d32e8cda8f399b319a49250dff972b81af8
- ovl_7DF8: ea830aae50ff1422da60d4b7fdbfc29f03b1be39
- ovl_7E00: 2b01138a290212b9d886981e1196f7b6fb45ecdb

Matched bytes increase 66,512→67,476 (+964); T4 increases 305→308.
status.csv, TRACKING, WORKLOG, boot, ovl_7E00, YAML and Makefile are untouched.
Generated progress documents are restored after recording the table.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 67,476 (23.28%) | 67,476 (23.28%) | 0 | 201 | 0 | 308 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 31,204 (21.67%) | 31,204 (21.67%) | 0 | 90 | 0 | 147 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 27,804 (20.23%) | 27,804 (20.23%) | 0 | 111 | 0 | 140 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |


## Search outcomes and diagnostic limits

Seven unresolved functions completed 900-second decomp-permuter searches,
each with -j5, --stack-diffs, --stop-on-zero, --best-only and --better-only.
E0B4's search stopped after 534 seconds once its independent C hypothesis
matched. Exit 137 records bounded interrupt termination, not a build failure.
No search output was promoted. Lower weighted scores in B5534 and C85C0
were worse under independent word counts; BDE0's output retained nine words,
behind the hand-derived eight-word draft. No task search process remains.

The final linked build is essential evidence: E0B4's initial zero used TU
prefix context because its scalar global declaration conflicted with a later
position-record array. An intermediate production build exposed that conflict.
The existing T032Pos24B typedef/array declaration was moved earlier, E0B4's
accesses now use byte views, and the unrelated 24B0C body is unchanged.
The corrected complete TU independently measures zero, followed by the clean
linked image and ROM verification above. No conflicting declaration was kept.
C85C0's reconciled draft now also measures in its full owning TU, at the same
four words; its original fallback was not claimed as an integration match.

instructions.json records incoming instruction differences. experiments.json
summarizes concrete and layout probes; searches.json records measured search
durations. Diagnostic width changes, failed declarations and raw candidates
are experiments, not proposed code. Generated inputs, compiler products,
complete probe logs and permuter output trees remain under /tmp/kig-t109.
Only the three matched bodies and their needed declarations change production
source; the BDE0 improvement and C85C0 declaration reconciliation remain drafts.
`git diff --check` passes. No commits or ROM additions.
