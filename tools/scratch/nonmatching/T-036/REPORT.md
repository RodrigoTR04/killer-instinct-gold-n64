# T-036 / sol-C14

Worktree: `/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-b86aa93e`  
Base: `05f18d0`. No commits made.

Three exact matches, **788 bytes**. Twelve improved drafts and sixteen unchanged drafts. All 31 drafts received an insertion attempt, beginning with the smallest positional differences. Only full-ROM-verified matches remain in `src/main/main_2FF0.c`.

Baseline clean build/extraction and progress succeeded: ROM and all three images OK, 126 T4. Compiler: IDO 5.3, existing `-O2 -mips2` flags. Iteration used the full translation unit through asm-processor, the normal main linker scripts, and asm-differ. Positional word counts compare linked instructions at the original function address; changed function sizes also move relocations, so these are not asm-differ edit-distance scores. Unchanged rows retain T-022's historical notes rather than claiming new improved measurements.

## Matches

- `func_8001D37C` (176 bytes): removed redundant byte masking, used the conditional selector directly, and reversed addition operands to reproduce evaluation/register order. Moved the existing `T022DmaEntry` declaration immediately above this function; no new typedef was introduced.
- `func_8001C1B0` (292 bytes): byte-typed third/fourth parameters used directly, with the color index added to the pointer separately from the +12 field offset. IDO generates the original unrolled loop.
- `func_8001BF1C` (320 bytes): corrected `guTranslate` to four arguments and the last parameter to float, corrected the table's 12-byte byte stride, reused the display-list pointer, and split the Y calculation into assignment plus compound subtraction.

Deleted drafts:

- `tools/scratch/nonmatching/T-022/func_8001D37C.c`
- `tools/scratch/nonmatching/T-022/func_8001C1B0.c`
- `tools/scratch/nonmatching/T-022/func_8001BF1C.c`

## Draft improvements and limits

- `80018E88`: direct external constant reads reduce four words to two; the remaining loads are swapped at +0x04/+0x20.
- `8001C370`: an explicit inner bound and reordered outer initialization reproduce all body registers. Four prologue save/setup words remain (+0x08, +0x1C, +0x34, +0x38).
- `8001CF1C`: reuse loop variables across walks and express the second walk with `i + 1` and `i++`. Six initialization/scheduling words remain; the loop bodies agree.
- `8001CBCC`: place matrix stores in natural row order. The 320-byte body size now agrees; frame/stack-local placement and initial float-load scheduling remain different. An unused-padding-local experiment was discarded; no speculative padding was retained.
- `8001BDE0`: reuse the list pointer and index across both walks. Remaining differences are float saved-register selection and the initial display-list-pointer scheduling.
- `8001B620`: correct the table byte stride and zero-argument RNG call, and reuse the table pointer. Target body size restored; stack placement and float/global scheduling remain different.
- `8001DE5C` and `8001EC74`: reuse m2c's same-typed variable versions corresponding to the same original registers. These remain large provisional reconstructions; no claim of runtime validation is made for drafts.
- `8001E0B4`, `8001B134`, `8001D47C`, and `8001D7E4`: repair missing/conflicting extern integration after the TU split (preserving unsigned byte reads by casts, the float global's byte view, and the DMA buffer's array view). These compile in the current TU; some positional-count improvement relative to T-022 comes from the changed TU/layout, not instruction improvements.
- `8001808C`, `8001D080`, and `8001CD50`: insertion requires moving their already-existing identical typedef above the function and removing the later duplicate. Diagnostic relocation of those declarations confirmed the historical nonmatches, so their drafts remain unchanged. `8001CD50` also needs the missing `D_8004EA9C` extern and `func_8001D37C`'s void return declaration when integrated.
- `80019880`: still blocked by existing earlier `extern void func_80019880(void)` declarations versus the draft's six-argument definition, as well as the draft's scalar declarations of globals already declared as arrays later in this TU. No unrelated declarations were edited to promote a nonmatch.

No inline assembly, register binding, compiler pragmas, emitted data/rodata, or padding tricks were retained. No yaml/configuration, headers, other source files, status inventory, ROMs, or main-checkout files were modified.

## All 31 drafts

| Function | Status | Remaining diff / evidence |
|---|---|---|
| `func_8001BB10` | UNCHANGED | 3 words; 84/84 bytes |
| `func_80018E88` | IMPROVED | 2 linked words; 152/152 bytes |
| `func_8001C370` | IMPROVED | 4 linked words; 204/204 bytes |
| `func_8001D37C` | MATCHED | 0; 176/176 bytes; ROM and all images OK |
| `func_8001CF1C` | IMPROVED | 6 linked words; 356/356 bytes |
| `func_8001CBCC` | IMPROVED | 16 linked words; 320/320 bytes |
| `func_8001E0B4` | IMPROVED | 61 linked words; 648/648 bytes |
| `func_8001C43C` | UNCHANGED | 65 words; 272/248 bytes |
| `func_8001AA90` | UNCHANGED | 66 words; 488/496 bytes |
| `func_8001C1B0` | MATCHED | 0; 292/292 bytes; ROM and all images OK |
| `func_8001BDE0` | IMPROVED | 15 linked words; 316/316 bytes |
| `func_8001BF1C` | MATCHED | 0; 320/320 bytes; ROM and all images OK |
| `func_8001CD50` | UNCHANGED | 104 words; 436/460 bytes |
| `func_800191F0` | UNCHANGED | 123 words; 508/492 bytes |
| `func_80018F20` | UNCHANGED | 141 words; 688/696 bytes |
| `func_8001DE5C` | IMPROVED | 149 linked words; 624/600 bytes |
| `func_8001D080` | UNCHANGED | 177 words; 756/764 bytes |
| `func_8001808C` | UNCHANGED | 184 words; 796/808 bytes |
| `func_800193DC` | UNCHANGED | 194 words; 788/808 bytes |
| `func_8001BB64` | UNCHANGED | 195 words; 812/636 bytes |
| `func_80018AE0` | UNCHANGED | 201 words; 896/912 bytes |
| `func_8001D47C` | IMPROVED | 177 linked words; 892/748 bytes |
| `func_8001B134` | IMPROVED | 228 linked words; 984/984 bytes |
| `func_8001B620` | IMPROVED | 87 linked words; 1016/1016 bytes |
| `func_8001AD04` | UNCHANGED | 251 words; 1100/1072 bytes |
| `func_80018664` | UNCHANGED | 287 words; 1160/1148 bytes |
| `func_8001C5AC` | UNCHANGED | 431 words; 1908/1568 bytes |
| `func_8001D7E4` | IMPROVED | 413 linked words; 1748/1656 bytes |
| `func_8001E33C` | UNCHANGED | 604 words; 2420/2360 bytes |
| `func_8001EC74` | IMPROVED | 2174 linked words; 8476/8740 bytes |
| `func_80019880` | UNCHANGED | Build failed before byte comparison: cfe: Error: src/main/main.c, line 1083: redeclaration of 'D_8004ACCC'; previous declaration at line 487 in file 'src/main/main.c'; cfe: Error: src/main/main.c, line 1083: redeclaration of 'D_8004ACD0'; previous declaration at line 488 in file 'src/main/main.c' |

## TU-boundary hints

None discovered in this run. All three promoted functions preserve the entire linked main image; no body-only match with an alignment/padding mismatch was found.

## Final validation

`make clean && make extract && make && make progress` passed. ROM and all three images are byte-identical. `git diff --check` passed. Total T4 increased from 126 to 129; main T4 increased from 64 to 67.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
| Total | 319,544 | 13,256 (4.15%) | 13,256 (4.15%) | 117 | 323 | 0 | 129 | 430 (137,648) |
| boot | 8,468 | 0 (0.00%) | 0 (0.00%) | 21 | 0 | 0 | 0 | 99 (16,028) |
| main | 173,204 | 6,816 (3.94%) | 6,816 (3.94%) | 64 | 159 | 0 | 67 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 6,440 (4.69%) | 6,440 (4.69%) | 25 | 164 | 0 | 62 | 0 (0) |
| ovl_7E00 | 444 | 0 (0.00%) | 0 (0.00%) | 7 | 0 | 0 | 0 | 162 (87,228) |

Setup symlinks (`ROMs`, `baserom.us.z64`, `.venv`, `tools/ext`) remain local setup artifacts. Generated `docs/functions.csv` and `docs/progress.html` were restored after capturing progress.
