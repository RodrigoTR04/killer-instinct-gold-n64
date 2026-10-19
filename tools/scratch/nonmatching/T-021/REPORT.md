T-021 / sol-B7

Worktree: /home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-b0e96171

Matched: 23 functions / 2716 bytes.

Only verified matches remain in src. No commits. All 45 functions of at most 200 bytes received compile attempts. Larger functions with unresolved m2c fields or jump tables are NOT ATTEMPTED; their preliminary output is retained for follow-up.

| Function | Bytes | Status | Remaining diff / note |
|---|---:|---|---|
| `func_801C2110` | 316 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801C224C` | 372 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801C23C0` | 1820 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801C2ADC` | 600 | NOT ATTEMPTED | m2c needs original jump-table data. |
| `func_801C2D34` | 552 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801C2F5C` | 544 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801C317C` | 936 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801C3524` | 92 | DRAFT | Same size; display-list pointer/temporary registers and two instruction schedules differ. |
| `func_801C3580` | 44 | DRAFT | One lui is scheduled before the ra save instead of after it. |
| `func_801C35AC` | 44 | DRAFT | One lui is scheduled before the ra save instead of after it. |
| `func_801C35D8` | 384 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801C3758` | 564 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801C3990` | 272 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801C3AA0` | 928 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801C3E40` | 504 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801C4040` | 60 | MATCHED |  |
| `func_801C407C` | 444 | NOT ATTEMPTED | m2c needs original jump-table data. |
| `func_801C4238` | 8 | MATCHED |  |
| `func_801C4240` | 1344 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801C4780` | 84 | DRAFT | Argument representation/spills, temporary registers and scheduling differ. |
| `func_801C47E0` | 260 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801C48E4` | 196 | DRAFT | u16 argument spills/scheduling and pointer temporary registers differ. |
| `func_801C49A8` | 548 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801C4BD0` | 148 | DRAFT | Argument reload/register allocation and one call delay-slot schedule differ. |
| `func_801C4C64` | 196 | MATCHED |  |
| `func_801C4D28` | 68 | DRAFT | Six float register operands differ (f0/f2/f12 versus f4/f6/f8); same instruction sequence. |
| `func_801C4D6C` | 204 | DRAFT | Instruction/register/control-flow mismatch; see saved asm-differ output. |
| `func_801C4E38` | 556 | DRAFT | Compile blocked by unresolved types/prototypes: extern s32 func_801C4C64(); |
| `func_801C5064` | 404 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801C51F8` | 160 | DRAFT | Display-list pointer and constant registers plus scheduling differ. |
| `func_801C5298` | 3036 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801C5E74` | 2392 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801C67CC` | 692 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801C6A80` | 292 | DRAFT | Instruction/register/control-flow mismatch; see saved asm-differ output. |
| `func_801C6BA4` | 212 | MATCHED |  |
| `func_801C6C78` | 200 | MATCHED |  |
| `func_801C6D40` | 300 | DRAFT | Instruction/register/control-flow mismatch; see saved asm-differ output. |
| `func_801C6E6C` | 24 | MATCHED |  |
| `func_801C6E84` | 184 | MATCHED |  |
| `func_801C6F3C` | 224 | MATCHED |  |
| `func_801C701C` | 24 | MATCHED |  |
| `func_801C7034` | 204 | MATCHED |  |
| `func_801C7100` | 252 | MATCHED |  |
| `func_801C71FC` | 172 | DRAFT | Argument spills, indexing and register allocation differ. |
| `func_801C72B0` | 96 | DRAFT | Global-address registers, chained zero stores, and scheduling differ. |
| `func_801C7310` | 1276 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801C780C` | 160 | DRAFT | Instruction/register/control-flow mismatch; see saved asm-differ output. |
| `func_801C78B0` | 232 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801C7998` | 256 | NOT ATTEMPTED | m2c needs original jump-table data. |
| `func_801C7A98` | 568 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801C7CD0` | 380 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801C7E4C` | 76 | MATCHED |  |
| `func_801C7E98` | 120 | DRAFT | Six-byte copy loop has multiplication and register/scheduling differences. |
| `func_801C7F10` | 48 | MATCHED |  |
| `func_801C7F40` | 80 | MATCHED |  |
| `func_801C7F90` | 116 | DRAFT | Clear-loop store order and global-address register allocation/scheduling differ. |
| `func_801C8004` | 236 | DRAFT | Compile blocked by unresolved types/prototypes: extern u8 D_80127C68; |
| `func_801C80F0` | 1232 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801C85C0` | 168 | DRAFT | Saved pointer register assignment and loop scheduling differ. |
| `func_801C8668` | 64 | DRAFT | Four byte-store offsets/order differ; loop and registers match in closest draft. |
| `func_801C86A8` | 448 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801C8868` | 464 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801C8A38` | 168 | DRAFT | One variable shift scheduled before three addiu instructions; otherwise matches. |
| `func_801C8AE0` | 324 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801C8C24` | 408 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801C8DBC` | 364 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801C8F28` | 428 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801C90D4` | 1200 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801C9584` | 276 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801C9698` | 1148 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801C9B14` | 3184 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801CA784` | 96 | DRAFT | Search-loop global base, registers and initial load/control flow differ. |
| `func_801CA7E4` | 312 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801CA91C` | 228 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801CAA00` | 3992 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801CB998` | 148 | DRAFT | Live call argument/stack handling and temporary registers differ. |
| `func_801CBA2C` | 428 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801CBBE0` | 236 | DRAFT | Same instructions; frame is 0x28 versus 0x30 and query buffer is sp+0x18 versus sp+0x20. |
| `func_801CBCCC` | 516 | NOT ATTEMPTED | m2c needs original jump-table data. |
| `func_801CBED0` | 128 | MATCHED |  |
| `func_801CBF50` | 60 | MATCHED |  |
| `func_801CBF8C` | 320 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801CC0CC` | 216 | DRAFT | Instruction/register/control-flow mismatch; see saved asm-differ output. |
| `func_801CC1A4` | 192 | DRAFT | Checksum accumulation and saved-register allocation/scheduling differ. |
| `func_801CC264` | 100 | MATCHED |  |
| `func_801CC2C8` | 136 | DRAFT | EEPROM result/control flow, global base and return-branch scheduling differ. |
| `func_801CC350` | 108 | MATCHED |  |
| `func_801CC3BC` | 360 | DRAFT | Call arguments, stack frame and control/register allocation differ. |
| `func_801CC524` | 104 | MATCHED |  |
| `func_801CC58C` | 116 | MATCHED |  |
| `func_801CC600` | 104 | MATCHED |  |
| `func_801CC668` | 284 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801CC784` | 244 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801CC878` | 144 | DRAFT | Compile blocked by unresolved types/prototypes: s32 func_801CC668(?); |
| `func_801CC908` | 424 | DRAFT | Compile blocked by unresolved types/prototypes: s32 func_801CC350(s32 *, s32); |
| `func_801CCAB0` | 284 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801CCBCC` | 424 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801CCD74` | 116 | DRAFT | Global bases a1/a2 and corresponding comparison/load registers are exchanged. |
| `func_801CCDE8` | 196 | DRAFT | Early-return branch shape differs (three fewer instructions). |
| `func_801CCEAC` | 396 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801CD038` | 64 | MATCHED |  |
| `func_801CD078` | 136 | DRAFT | Compile blocked by unresolved types/prototypes: ? sp36; |
| `func_801CD100` | 116 | DRAFT | Same size; counter/pointer registers and division scheduling differ. |
| `func_801CD174` | 124 | DRAFT | Stack slots differ: pointer at sp+0x18 instead of 0x1C; output at sp+0x1C instead of 0x20. |
| `func_801CD1F0` | 460 | NOT ATTEMPTED | Preliminary m2c only; unresolved field/type reconstruction. |
| `func_801CD3BC` | 140 | MATCHED |  |

Clean validation: `make clean && make extract && make && make progress` passed. ROM and all three images are byte-identical.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,544 | 3,780 (1.18%) | 3,780 (1.18%) | 536 | 0 | 0 | 33 | 430 (137,648) |
| boot | 8,468 | 0 (0.00%) | 0 (0.00%) | 21 | 0 | 0 | 0 | 99 (16,028) |
| main | 173,204 | 376 (0.22%) | 376 (0.22%) | 287 | 0 | 0 | 3 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 3,404 (2.48%) | 3,404 (2.48%) | 221 | 0 | 0 | 30 | 0 (0) |
| ovl_7E00 | 444 | 0 (0.00%) | 0 (0.00%) | 7 | 0 | 0 | 0 | 162 (87,228) |

Suggested types/names: `T021Six` is a six-byte palette/permutation entry. `func_801C7E4C` initializes it to {6,1,3,7,2,0}; `func_801C4C64` copies a 3x4 matrix and a four-float vector into rendering globals. Controller Pak wrapper return types deserve follow-up: current matching void wrappers preserve v0, but callers consume their callee results. No headers changed.

No assembly, register-binding extensions, new data or emitted rodata were added. Narrow unsigned fields and compound assignments are the key compiler idioms.
