# T-057 — ovl_7DF8 finishing experiments

Worker sol-B19. No commits. **0 matched, 0 improved, 16 unchanged.** No production source or existing draft was changed; no drafts were deleted.

Read docs/TRACKING.md, latest WORKLOG.md, Makefile, and reports T-053/T-048 before probing. Missing baserom.us.z64, ROMs, .venv and tools/ext were symlinked from the authorized main checkout. No ROM was copied into git.

Scores are differing aligned words plus missing/extra words, masking actual ELF relocations, using IDO 5.3 production -O2 -mips2 flags. All siblings received fresh independent baseline checks. Family experiments target representatives; since neither representative improved, no changes were propagated to siblings.

| Function | Result | Words still different | Draft / target bytes | Remaining issue |
|---|---|---:|---:|---|
| func_801C51F8 | UNCHANGED | 2 | 160 / 160 | First command address addiu and opcode ori exchanged; all registers agree. |
| func_801B2010 | UNCHANGED | 23 | 420 / 420 | Counter address/predicate allocation and command scheduling. |
| func_801B21B4 | UNCHANGED | 23 | 420 / 420 | Counter address/predicate allocation and command scheduling. |
| func_801B2358 | UNCHANGED | 23 | 420 / 420 | Counter address/predicate allocation and command scheduling. |
| func_801B24FC | UNCHANGED | 23 | 420 / 420 | Counter address/predicate allocation and command scheduling. |
| func_801B26A0 | UNCHANGED | 23 | 420 / 420 | Counter address/predicate allocation and command scheduling. |
| func_801B2844 | UNCHANGED | 23 | 420 / 420 | Counter address/predicate allocation and command scheduling. |
| func_801B29E8 | UNCHANGED | 22 | 420 / 420 | Counter address/predicate allocation and command scheduling. |
| func_801B6A68 | UNCHANGED | 20 | 368 / 368 | Command constants, temporary registers and texture-address scheduling. |
| func_801C6A80 | UNCHANGED | 30 | 292 / 292 | Scalar global bases are retained across stores; target repeats symbolic stores, changing downstream scheduling. |
| func_801B2EF4 | UNCHANGED | 70 | 536 / 536 | Counter/global bases, alpha stack slot, unsigned float conversion and command scheduling. |
| func_801B310C | UNCHANGED | 70 | 536 / 536 | Counter/global bases, alpha stack slot, unsigned float conversion and command scheduling. |
| func_801B3324 | UNCHANGED | 70 | 536 / 536 | Counter/global bases, alpha stack slot, unsigned float conversion and command scheduling. |
| func_801B353C | UNCHANGED | 70 | 536 / 536 | Counter/global bases, alpha stack slot, unsigned float conversion and command scheduling. |
| func_801B3754 | UNCHANGED | 70 | 536 / 536 | Counter/global bases, alpha stack slot, unsigned float conversion and command scheduling. |
| func_801B396C | UNCHANGED | 70 | 536 / 536 | Counter/global bases, alpha stack slot, unsigned float conversion and command scheduling. |

## Experiment log

Reproducible generators and the isolated PID-specific probe are included here. Candidate counts include duplicates and compiler failures; a candidate is not a validated implementation. No unverified best candidate was installed.

- `sweep.py`: command-word store permutations (all 2^N combinations), word signedness, pointer indexing/raw byte offsets, cursor update spelling, all 120 five-pointer declaration permutations for func_801C51F8. The 11-pointer function has 2,048 store-order combinations. Neither representative improved.
- `near.py`: func_801C51F8 address declaration as byte/word scalar, byte/word array or function; address temporary widths; address/opcode store and evaluation order; signed/volatile word fields. No improvement. Volatile is diagnostic only, not a proposed source declaration.
- `layout.py`: union-aligned and indexed command layouts; equivalent canceled symbol offsets; address/opcode locals evaluated before/after cursor update in all permutations. No improvement.
- `first.py`: 1,728 combinations for func_801C51F8: signed/unsigned/64-bit command local, eight constant spellings, four store/access forms, three cursor updates, all six initialization orders. Best remains 2 / 160.
- `families.py`: 896 family-A counter/predicate combinations (signed/unsigned/short local, unused argument reuse, predicate spelling, common versus branch-local stores, postfix forms); 384 family-B alpha/color widths, old counter local/argument forms, color masking and conversion experiments; 160 phase local-width/update-expression/prototype/comparison combinations. No improvement. Narrowing, changed conversion behavior, and non-equivalent overflow cases were diagnostic only and were not retained.
- `counter.py`: additional family-A branch-local update forms and direct lerp counter arguments, independent counter/predicate names and comparison spelling. No improvement. The target's a2 counter plus v0 predicate was not recovered.
- `aargs.py`: 256 additional family-A postfix/prefix and split-branch forms with lerp argument prototype widths. No improvement; speculative narrow prototypes were discarded.
- `commands.py`: command store/access sweeps on both clone representatives and func_801B6A68; texture bank arithmetic regrouping and individual explicit cursor increments. The 7DF8 texture representative received 2,264 candidates; clone representatives received 224 each. Pointer merge attempts with invalid declarations failed compilation and are not evidence about the target. No improvement.
- `declarations.py`: 450 deterministic shuffled local declaration orders per representative (family A, family B, phase and texture commands), plus float intermediate/alpha widths and argument widths. No improvement. Many declaration permutations compile identically because IDO orders locals by use.
- `globals.py`: scalar versus array and diagnostic volatile global declarations for the phase function, plus increment/store and bound spelling. No improved retained result. The array substitution involving address-of uses can fail compilation; volatile variants are not intended as behavior recovery.

Family B still reads an uninitialized alpha byte on its late branch in the existing draft; the original reads the old stack byte. No candidate that initialized or changed that read was accepted. No behavior-validation claim is made for any draft.

The remaining two words in func_801C51F8 are precisely offsets +0x14 and +0x18: generated ori t7 precedes addiu t8, while the target has addiu t8 before ori t7. All following 33 words agree under relocation masking. This round did not find a C expression that changes that scheduling without disturbing registers or other instructions.

Deleted drafts: **none**. Existing improved drafts from T-053 remain untouched in their original directories.

## Final verification

`make clean && make extract && make all && make progress` passed. ROM byte comparison passed; SHA1 `ba52e91b44450c548467044b26951353dc491e04`.

All executable images passed byte comparison:

- main: `81736d32e8cda8f399b319a49250dff972b81af8`
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`

Generated progress files have no diff. Makefile, YAML, status.csv, production sources, and existing drafts are unchanged. No commits were made.


| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 52,412 (16.42%) | 52,412 (16.42%) | 0 | 309 | 0 | 253 | 437 (138,092) |
| boot | 8,468 | 8,108 (95.75%) | 8,108 (95.75%) | 0 | 1 | 0 | 20 | 99 (16,028) |
| main | 173,204 | 29,600 (17.09%) | 29,600 (17.09%) | 0 | 149 | 0 | 141 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 14,704 (10.70%) | 14,704 (10.70%) | 0 | 159 | 0 | 92 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
