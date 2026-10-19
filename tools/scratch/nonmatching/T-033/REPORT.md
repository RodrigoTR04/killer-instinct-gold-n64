# T-033 / sol-A15

Worktree: `/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-9f33d227`.

All 27 assigned functions received C compile attempts. Four MATCHED (2,188 original bytes); 23 DRAFT; zero NOT ATTEMPTED. No commits. Only full-ROM-verified matches remain in `src/main/main_2FF0.c`; `src/main/main.c` is unchanged.

Small candidates were reconstructed first, with larger typed reconstructions prepared during builds. Smaller candidates received bounded standalone variants in addition to full translation-unit builds. In particular, the successful `8001383C` refinement moved the third light-position assignment before the color assignments and chained the three background-color resets. This is ordinary C scheduling, with no inline assembly, register binding, volatile tricks, compiler pragmas, or data definitions.

Every draft was inserted into its assigned source file and built with `make`, then restored to GLOBAL_ASM. All final drafts compiled in that process. Word counts below compare linked instruction words at corresponding positions, with no relocation masking. They are not asm-differ edit distances. Changed sizes can shift other symbols and inflate counts. Sizes include assembly trailing padding: `8001272C`, for example, has a 540-byte inventory body but a 548-byte assembly span.

| Function | Inventory bytes | Status | Remaining difference (compiled / assembly bytes) |
|---|---:|---|---|
| `func_8000FA80` | 7436 | DRAFT | 2028 positional differing words; 8148/7436 bytes |
| `func_8001178C` | 2104 | DRAFT | 570 positional differing words; 2296/2104 bytes |
| `func_800121C8` | 304 | DRAFT | 65 positional differing words; 308/304 bytes |
| `func_80012390` | 476 | DRAFT | 110 positional differing words; 480/476 bytes |
| `func_8001256C` | 356 | DRAFT | 63 positional differing words; 356/356 bytes |
| `func_8001272C` | 540 | DRAFT | 106 positional differing words; 544/548 bytes |
| `func_80012950` | 316 | DRAFT | 57 positional differing words; 316/316 bytes |
| `func_80012B7C` | 1576 | DRAFT | 391 positional differing words; 1560/1576 bytes |
| `func_800131A4` | 712 | DRAFT | 181 positional differing words; 732/712 bytes |
| `func_8001346C` | 704 | DRAFT | 170 positional differing words; 732/704 bytes |
| `func_8001383C` | 872 | MATCHED | — |
| `func_80013CD8` | 1140 | DRAFT | 133 positional differing words; 1140/1140 bytes |
| `func_800142E0` | 2400 | DRAFT | 593 positional differing words; 2100/2400 bytes |
| `func_80014C40` | 284 | MATCHED | — |
| `func_80014D5C` | 1780 | DRAFT | 400 positional differing words; 1788/1780 bytes |
| `func_80015450` | 324 | DRAFT | 68 positional differing words; 328/324 bytes |
| `func_80015594` | 1488 | DRAFT | 358 positional differing words; 1368/1488 bytes |
| `func_80015B64` | 364 | MATCHED | — |
| `func_80015CD0` | 668 | MATCHED | — |
| `func_80016078` | 480 | DRAFT | 120 positional differing words; 448/480 bytes |
| `func_80016258` | 1288 | DRAFT | 206 positional differing words; 1280/1288 bytes |
| `func_80016910` | 720 | DRAFT | 83 positional differing words; 728/720 bytes |
| `func_80016BE0` | 1156 | DRAFT | 326 positional differing words; 1388/1156 bytes |
| `func_800170C4` | 692 | DRAFT | 266 positional differing words; 1084/692 bytes |
| `func_80017378` | 1752 | DRAFT | 463 positional differing words; 1904/1752 bytes |
| `func_80017A68` | 772 | DRAFT | 156 positional differing words; 768/772 bytes |
| `func_80017D6C` | 800 | DRAFT | 195 positional differing words; 824/800 bytes |

The larger drafts retain provisional layouts and call ABIs; they are not verified runtime replacements. `8000FA80` reconstructs the 0x60-byte task wrapper, camera records, player snapshots, and display commands, but packed HUD/replay views and several callbacks still need review. `8001178C` reconstructs controller input and player snapshots. The rendering switches in `80012B7C` and `8001346C`, and the pause switch in `8001178C`, also need compiler-generated jump-table ownership reconciled with the assembly-owned rodata before promotion. No data ownership was changed.

Suggested names/types:

- `func_80014C40`: apply stage force sources. The target has signed 16-bit velocity accumulators at +0x28/+0x2A/+0x2C, consistent with the existing `8001373C` reconstruction.
- `func_80015B64`: select a stage visibility region; it swaps display-list entries according to height/depth and returns a region derived from two oblique planes.
- `func_80015CD0` and `func_8001383C`: stage scene initializers.
- Stage display records are 12 bytes: display-list pointer at +0, signed 16-bit flags at +4, transform index at +8. Rotation/transform records use a 20-byte stride. The first three floats are rotations; the last two fields remain provisional.
- Shared callback `D_8004AEAC` is called with five integer-converted coordinates in some callers, while existing declarations and several implementations take four. Draft callers retain an explicit function-pointer view; a shared prototype audit is needed outside this task.
- Existing `func_8001B50C`, `func_8001BA94`, and `func_8001AC80` have single-argument, single-float, and no-argument definitions respectively. Drafts remove m2c's spurious live-register arguments to those functions.

`attempt.py` reproduces a full-source insertion/build/restoration for a saved draft. `probe.py` checks syntax against the committed TU, and `metric.py` provides a standalone relocation-masked diagnostic; neither diagnostic substitutes for ROM validation.

Final clean validation: `make clean && make extract && make -j16 && make progress` passed. The ROM and all three images are byte-identical. T4 increased from 124 to 128. Generated `docs/functions.csv` and `docs/progress.html` were restored after recording this table.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,544 | 14,108 (4.42%) | 14,108 (4.42%) | 138 | 303 | 0 | 128 | 430 (137,648) |
| boot | 8,468 | 0 (0.00%) | 0 (0.00%) | 21 | 0 | 0 | 0 | 99 (16,028) |
| main | 173,204 | 8,216 (4.74%) | 8,216 (4.74%) | 60 | 162 | 0 | 68 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 5,892 (4.29%) | 5,892 (4.29%) | 50 | 141 | 0 | 60 | 0 (0) |
| ovl_7E00 | 444 | 0 (0.00%) | 0 (0.00%) | 7 | 0 | 0 | 0 | 162 (87,228) |
