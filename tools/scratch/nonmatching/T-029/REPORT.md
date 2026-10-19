# T-029 / sol-A14

Worktree: `/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-84f71892`

2 new matches / 168 bytes. All 19 functions received reconstructed C compile attempts, smallest first. No commits. `func_801B55DC` is unchanged. Only verified C remains in src. All 17 drafts compiled; their build logs and bounded asm-differ outputs are retained alongside them. Drafts are reconstructions, not behavior-validated replacements.

| Function | Status | Remaining diff |
|---|---|---|
| `func_801B4300` | MATCHED |  |
| `func_801B4324` | MATCHED |  |
| `func_801B43A8` | DRAFT | Shuffle pointer lifetime, saved/temporary registers, and one extra instruction differ. |
| `func_801B446C` | DRAFT | Flag/global address reuse, byte temporaries and store scheduling differ. |
| `func_801B4590` | DRAFT | Byte argument is saved twice; frame is 0x28 instead of 0x20; registers differ. |
| `func_801B465C` | DRAFT | Selection-byte temporaries, saved registers and branch scheduling differ. |
| `func_801B47A4` | DRAFT | Input/state reconstruction compiles; loop induction, control flow, frame and registers differ. |
| `func_801B5534` | DRAFT | Frame is 0x28 instead of 0x20; player/index registers and call delay slot differ. |
| `func_801B5650` | DRAFT | Carousel float lifetimes, matrix-call scheduling, frame and temporary registers differ. |
| `func_801B5DCC` | DRAFT | Carousel float lifetimes, matrix-call scheduling, frame and temporary registers differ. |
| `func_801B6528` | DRAFT | Same 596-byte body; three operands use a0 instead of a2 after guTranslate. |
| `func_801B677C` | DRAFT | Division scheduling, normalized argument lifetimes and integer temporary registers differ. |
| `func_801B695C` | DRAFT | Frame is 0x30 instead of 0x28; bank/frame-pointer temporaries and scheduling differ. |
| `func_801B6A68` | DRAFT | Same 368-byte body; command constants, address arithmetic and temporary registers differ. |
| `func_801B6BD8` | DRAFT | Text helper float argument typing, saved count register, stack slots and scheduling differ. |
| `func_801B6E4C` | DRAFT | Typed portrait/display-list reconstruction compiles; frame, text buffers, registers and scheduling differ. |
| `func_801B849C` | DRAFT | Typed portrait/display-list reconstruction compiles; frame, text buffers, registers and scheduling differ. |
| `func_801B994C` | DRAFT | Same 184-byte body; cursor/global address registers and one lui schedule differ. |
| `func_801B9A04` | DRAFT | Vertex loop unrolling, stack layout, float temporaries and call scheduling differ. |

Clean validation: `make clean && make extract && make && make progress` passed. ROM and all three images are byte-identical.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,544 | 11,380 (3.56%) | 11,380 (3.56%) | 230 | 223 | 0 | 116 | 430 (137,648) |
| boot | 8,468 | 0 (0.00%) | 0 (0.00%) | 21 | 0 | 0 | 0 | 99 (16,028) |
| main | 173,204 | 5,488 (3.17%) | 5,488 (3.17%) | 135 | 99 | 0 | 56 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 5,892 (4.29%) | 5,892 (4.29%) | 67 | 124 | 0 | 60 | 0 (0) |
| ovl_7E00 | 444 | 0 (0.00%) | 0 (0.00%) | 7 | 0 | 0 | 0 | 162 (87,228) |

Suggested names/types (inferences for lead review):

- `func_801B4300`: reset lineup position and shuffle lineup; `D_8012834B` is the reset position byte.
- `func_801B4324`: getSelectionUnlockTier; returns 0/1/2/3 at byte-statistic thresholds 5/55/120 and suppresses the statistic for the player flag.
- `T029Portrait` in the large drafts is a partial 0x8C-byte portrait/character asset record: pixels at +4, palette at +8, signed halfwords at +0x7E/+0x80/+0x82/+0x84, callback at +0x88. Field names remain provisional.
- `func_801B695C` copies 0x60-byte palette banks; `func_801B6A68` emits palette-loading display-list commands.

Matched C uses ordinary byte indexing and conditionals; no unusual tricks, assembly, register bindings, compiler pragmas or new data. Drafts use explicit fixed-offset partial structs, matrix calls and display-list words. The large rendering drafts retain structured-exit gotos and need further stack/text-buffer reconstruction. No headers or symbol changes are required for the two matches. Generated docs were restored after recording progress. Shared setup symlinks remain available in the worktree.
