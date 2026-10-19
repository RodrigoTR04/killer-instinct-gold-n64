# T-032 / sol-B13

Worktree: `/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-9b528953`.
Base: `cfe1ae0`. No commits. Main checkout and ROMs were not modified.

All 29 functions attempted, beginning with the smallest. Seven functions match (1,280 bytes); 22 compiled drafts; zero NOT ATTEMPTED. Only full-ROM-verified implementations remain in src/. Drafts reconstruct field types and control flow; they are provisional and are not runtime-ready replacements.

Baseline: `make extract && make && make progress` passed the ROM and all three images, with 122 T4 functions.

## Per-function results

Counts compare linked instruction words at corresponding function offsets, without masking relocations. They are not asm-differ edit distances. Changed text sizes and generated switch rodata can shift later symbols and inflate positional counts. Byte sizes are compiled/original body sizes. Each draft was inserted into its original translation unit and compiled with production IDO flags; all failed candidates were restored to GLOBAL_ASM. The final measurements use the retained draft code. asm-differ was also used to inspect the min-scan's scheduling differences before its successful reconstruction.

| Function | Status | Remaining diff / validation |
|---|---|---|
| `func_80020E98` | DRAFT | 526 positional words differ; 1928/2108 bytes |
| `func_800216D4` | DRAFT | 230 positional words differ; 1040/1032 bytes |
| `func_80021ADC` | MATCHED | Full ROM and all images OK |
| `func_80021B6C` | DRAFT | 1711 positional words differ; 6920/6896 bytes; switch-generated rodata also differs |
| `func_8002365C` | MATCHED | Full ROM and all images OK |
| `func_80023790` | MATCHED | Full ROM and all images OK |
| `func_800238C4` | DRAFT | 392 positional words differ; 1612/1580 bytes |
| `func_80023EF0` | DRAFT | 81 positional words differ; 324/312 bytes |
| `func_80024028` | DRAFT | 53 positional words differ; 284/284 bytes |
| `func_80024144` | MATCHED | Full ROM and all images OK |
| `func_800241BC` | DRAFT | 167 positional words differ; 840/820 bytes |
| `func_800244F0` | DRAFT | 26 positional words differ; 192/196 bytes |
| `func_800245B4` | DRAFT | 87 positional words differ; 344/352 bytes |
| `func_80024714` | DRAFT | 104 positional words differ; 712/712 bytes |
| `func_800249DC` | DRAFT | 64 positional words differ; 312/304 bytes; switch-generated rodata also differs |
| `func_80024B0C` | DRAFT | 101 positional words differ; 440/464 bytes |
| `func_80024CE0` | DRAFT | 409 positional words differ; 1492/1652 bytes |
| `func_80025354` | MATCHED | Full ROM and all images OK |
| `func_800253D0` | DRAFT | 214 positional words differ; 1044/1068 bytes |
| `func_800257FC` | DRAFT | 343 positional words differ; 1216/1372 bytes |
| `func_80025D58` | DRAFT | 147 positional words differ; 328/620 bytes |
| `func_80025FC4` | DRAFT | 456 positional words differ; 1896/1908 bytes |
| `func_80026738` | DRAFT | 96 positional words differ; 388/392 bytes |
| `func_800268C0` | DRAFT | 40 positional words differ; 236/236 bytes |
| `func_800269AC` | DRAFT | 33 positional words differ; 236/236 bytes |
| `func_80026AA0` | MATCHED | Full ROM and all images OK |
| `func_80026B38` | DRAFT | 1183 positional words differ; 4792/4708 bytes; switch-generated rodata also differs |
| `func_80027DA0` | MATCHED | Full ROM and all images OK |
| `func_80027E1C` | DRAFT | 238 positional words differ; 964/936 bytes |

## Reconstruction notes

- `func_80021ADC`: inflate a small per-player sprite. Its second argument must be `u8` to reproduce the incoming argument spill. `T032RomEntry` is a 32-byte descriptor: ROM start/end at +0/+4, palette source at +8, and sprite start/end at +0x10/+0x14. The +0xC word and final eight bytes remain semantically unknown. The typedef guard lets earlier resource-loader drafts share this declaration when inserted for testing.
- `func_8002365C` / `func_80023790`: minimum left bound / maximum right bound over a range of four-byte records in a 1,024-byte bank selected by `D_8004EA78`. Both parameters are `u16`. The ternary arm order matters: testing `value >= result ? result : value` for min, and `value < result ? result : value` for max reproduces IDO's original branch-likely scheduling and narrowing.
- `func_80024144`: load the selected player's 32-byte palette after resource setup; kind 0xBA selects the second palette. A signed ROM-address word plus a separately computed signed offset preserves the original addu operand order. Its declaration of `func_80020E98` uses the reconstructed `u8, u8, void *` signature.
- `func_80025354`: initialize four HUD sprite descriptors and clear health/display counters.
- `func_80026AA0`: advance two nested animation-counter pairs (4/18 and 10/6 cycles).
- `func_80027DA0`: initialize the orthographic projection and rotation matrices. Spelling the first rotation argument as integer literal `0`, converted by the f32 prototype, reproduces the original immediate load; `0.0f` shares a floating zero register and differs.
- Shared sprites retain the existing 0x1C-byte layout (`T022Sprite` in main_2FF0.c): pixel/data words at +0/+4; half sizes at +8/+A; dimensions at +C/+E and +10/+12; flags at +18. Actor drafts reconstruct 0x100-byte records from byte/halfword/word loads, including screen coordinates at +68/+6C and scale at +70. Resource-cache entries are interleaved by player at eight-byte strides and resource ID at 24-byte strides.
- The 21B6C/26B38 renderer drafts required recovering jump-table targets from original assembly data before m2c could recover control flow. The retained C has typed display-list, actor/effect, model, and sprite records plus manually recovered stack arrays. Their switch tables still generate new rodata; they cannot be promoted while original data ownership remains unresolved. `func_800249DC` has the same switch-table issue.
- Larger drafts retain substantial stack/register scheduling and loop-unrolling differences. The 21B6C draft initializes otherwise indeterminate carried locals to zero; that is a provisional reconstruction choice, not a recovered original initialization. The drafts are research artifacts, not behavior-certified replacements.
- `boot_inflate` is declared void earlier in main_2FF0.c, but the original 20E98 routine consumes its return value as the inflated size. The 20E98 draft uses a function-pointer cast returning s32 for its compile experiment. A consistent s32-returning declaration needs lead review outside this task's editable scope. No header or symbol files were changed.

No inline assembly, register bindings, extra padding functions, compiler pragmas, or new global data definitions were introduced. Matched source uses natural C; the literal/ternary/type details above affect code generation.

## Final validation

`make clean && make extract && make && make progress` passed. The ROM and all three decompressed images are byte-identical. Total T4 increased from 122 to 129; main T4 increased from 64 to 71. M1/M2 increased by 1,280 bytes. The official T2 count is unchanged because this task does not edit the status inventory.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,544 | 13,032 (4.08%) | 13,032 (4.08%) | 154 | 286 | 0 | 129 | 430 (137,648) |
| boot | 8,468 | 0 (0.00%) | 0 (0.00%) | 21 | 0 | 0 | 0 | 99 (16,028) |
| main | 173,204 | 7,308 (4.22%) | 7,308 (4.22%) | 57 | 162 | 0 | 71 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 5,724 (4.17%) | 5,724 (4.17%) | 69 | 124 | 0 | 58 | 0 (0) |
| ovl_7E00 | 444 | 0 (0.00%) | 0 (0.00%) | 7 | 0 | 0 | 0 | 162 (87,228) |

Generated `docs/functions.csv` and `docs/progress.html` were restored after capturing the table. `git diff --check` passed. The only source edits are the seven assigned function implementations and their adjacent declarations/types in the four permitted files. The scratch deliverables are 22 annotated C drafts and this report. Setup symlinks remain local artifacts.

Suggested names: `inflate_player_sprite` (80021ADC), `find_sprite_min_left` (8002365C), `find_sprite_max_right` (80023790), `load_player_palette` (80024144), `init_hud_sprites` (80025354), `advance_effect_animation_counters` (80026AA0), and `init_hud_matrices` (80027DA0). These are semantic suggestions; no symbols were renamed.
