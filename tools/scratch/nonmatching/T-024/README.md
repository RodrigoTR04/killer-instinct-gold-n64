# T-024 results

All 78 assigned functions attempted in ascending size order. 19 matched, 1,288 bytes; 59 drafts. No commits made.

Only verified matches remain in `src/main/main.c`. Drafts are real reconstructions with corrected types/control flow; none are raw m2c output.

Word counts compare linked instruction words at corresponding function positions, without relocation masking. Size changes can shift later symbols and inflate these counts. They are not asm-differ edit-distance scores. Sizes are compiled/target bytes.

| Function | Bytes | Status | Remaining diff |
|---|---:|---|---|
| `func_8002A194` | 12 | MATCHED | — |
| `func_8002F6C4` | 24 | MATCHED | — |
| `func_8002F6DC` | 24 | MATCHED | — |
| `func_8002F9FC` | 32 | MATCHED | — |
| `func_8002FA1C` | 32 | MATCHED | — |
| `func_8002FA3C` | 32 | MATCHED | — |
| `func_8002FAA0` | 32 | MATCHED | — |
| `func_8002AB40` | 36 | MATCHED | — |
| `func_8002AB64` | 36 | DRAFT | body matches before relocation; missing 8 bytes of following alignment padding |
| `func_8002B6EC` | 36 | MATCHED | — |
| `func_80029770` | 52 | MATCHED | — |
| `func_8002B3A8` | 56 | DRAFT | 2 differing words; 56/56 bytes |
| `func_8002A1A0` | 60 | DRAFT | 13 differing words; 56/60 bytes |
| `func_8002A888` | 60 | MATCHED | — |
| `func_8002A8C4` | 60 | MATCHED | — |
| `func_8002B1EC` | 64 | DRAFT | 4 differing words; 64/64 bytes |
| `func_8002B91C` | 64 | DRAFT | 4 differing words; 64/64 bytes |
| `func_8002A150` | 68 | DRAFT | 3 differing words; 68/68 bytes |
| `func_8002FA5C` | 68 | MATCHED | — |
| `func_8002FFDC` | 68 | DRAFT | 18 differing words; 80/68 bytes |
| `func_8002F8F8` | 76 | DRAFT | 2 differing words; 76/76 bytes |
| `func_8002AA98` | 84 | DRAFT | 10 differing words; 80/84 bytes |
| `func_8002AAEC` | 84 | DRAFT | 10 differing words; 80/84 bytes |
| `func_8002B95C` | 88 | DRAFT | 2 differing words; 88/88 bytes |
| `func_8002BB74` | 92 | MATCHED | — |
| `func_8002970C` | 100 | DRAFT | 2 differing words; 100/100 bytes |
| `func_800281C4` | 108 | DRAFT | 11 differing words; 108/108 bytes |
| `func_8002B8B0` | 108 | DRAFT | 20 differing words; 108/108 bytes |
| `func_8002DBDC` | 108 | MATCHED | — |
| `func_8002F2B0` | 108 | DRAFT | 21 differing words; 100/108 bytes |
| `func_8002A1E0` | 116 | DRAFT | 6 differing words; 116/116 bytes |
| `func_8002B500` | 124 | DRAFT | 4 differing words; 124/124 bytes |
| `func_8002F234` | 124 | MATCHED | — |
| `func_8002DC48` | 128 | MATCHED | — |
| `func_8002F3DC` | 128 | DRAFT | 31 differing words; 128/128 bytes |
| `func_8002BAF0` | 132 | MATCHED | — |
| `func_8002E680` | 164 | DRAFT | 18 differing words; 164/164 bytes |
| `func_8002A254` | 172 | DRAFT | 27 differing words; 172/172 bytes |
| `func_8002FAC0` | 180 | DRAFT | 41 differing words; 168/180 bytes |
| `func_8002E08C` | 184 | DRAFT | 19 differing words; 192/184 bytes |
| `func_8002F944` | 184 | DRAFT | 46 differing words; 176/184 bytes |
| `func_8002A9DC` | 188 | DRAFT | 45 differing words; 192/188 bytes |
| `func_8002F31C` | 192 | DRAFT | 6 differing words; 192/192 bytes |
| `func_8002B710` | 196 | DRAFT | 34 differing words; 180/196 bytes |
| `func_80028708` | 204 | MATCHED | — |
| `func_8002B7E0` | 208 | DRAFT | 2 differing words; 208/208 bytes |
| `func_8002F5F0` | 212 | DRAFT | 50 differing words; 220/212 bytes |
| `func_8002A40C` | 220 | DRAFT | 14 differing words; 220/220 bytes |
| `func_8002A900` | 220 | DRAFT | 55 differing words; 224/220 bytes |
| `func_8002DF98` | 244 | DRAFT | 57 differing words; 240/244 bytes |
| `func_80028600` | 264 | DRAFT | 18 differing words; 264/264 bytes |
| `func_8002A300` | 268 | DRAFT | 45 differing words; 296/268 bytes |
| `func_8002DCC8` | 268 | DRAFT | 4 differing words; 268/268 bytes |
| `func_8002B3E0` | 280 | DRAFT | 13 differing words; 280/280 bytes |
| `func_80029AB0` | 304 | DRAFT | 69 differing words; 284/304 bytes |
| `func_8002B9B4` | 316 | DRAFT | 10 differing words; 316/316 bytes |
| `func_8002A004` | 324 | DRAFT | 20 differing words; 324/324 bytes |
| `func_8002AEE4` | 336 | DRAFT | 76 differing words; 320/336 bytes |
| `func_8002B57C` | 368 | DRAFT | 76 differing words; 348/368 bytes |
| `func_8002B22C` | 380 | DRAFT | 95 differing words; 396/380 bytes |
| `func_8002F45C` | 404 | DRAFT | 80 differing words; 416/404 bytes |
| `func_8002B034` | 440 | DRAFT | 30 differing words; 440/440 bytes |
| `func_8002DDD4` | 452 | DRAFT | 104 differing words; 444/452 bytes |
| `func_8002E4A0` | 480 | DRAFT | 115 differing words; 428/480 bytes |
| `func_8002F6F4` | 516 | DRAFT | 30 differing words; 516/516 bytes |
| `func_8002D9C4` | 536 | DRAFT | 134 differing words; 476/536 bytes |
| `func_8002FB80` | 544 | DRAFT | 109 differing words; 512/544 bytes |
| `func_800287D4` | 556 | DRAFT | 91 differing words; 560/556 bytes |
| `func_8002FDA0` | 572 | DRAFT | 143 differing words; 580/572 bytes |
| `func_800297A4` | 780 | DRAFT | 180 differing words; 780/780 bytes |
| `func_8002E150` | 844 | DRAFT | 180 differing words; 836/844 bytes |
| `func_8002AB90` | 852 | DRAFT | 210 differing words; 816/852 bytes |
| `func_8002A4F0` | 920 | DRAFT | 155 differing words; 916/920 bytes |
| `func_80028230` | 976 | DRAFT | 242 differing words; 932/976 bytes |
| `func_80029BE0` | 1060 | DRAFT | 263 differing words; 1048/1060 bytes |
| `func_8002E724` | 2832 | DRAFT | 699 differing words; 2364/2832 bytes |
| `func_80028A00` | 3340 | DRAFT | 802 differing words; 3264/3340 bytes |
| `func_8002BBD0` | 7668 | DRAFT | 1919 differing words; 7804/7668 bytes |

Suggested names/types:

- `func_80029770`: reset four effect timers; a natural four-iteration loop reproduces the unrolled original. Effect records are 0x140 bytes, with an s16 timer at +0x12C.
- `func_8002BAF0` / `func_8002BB74`: convert integer world coordinates using `D_8004AC84` and vertical bias `D_8004AC80`.
- `func_8002DBDC` / `func_8002DC48`: adjust angle continuity / normalize degrees.
- `func_8002F234`: stop/free a synth voice and remove queued events. Player queue is +0x14, synth pointer +0x38; voice flags are +0x3E.
- `func_8002FA5C`: post a 16-byte audio event. `func_8002FAA0`: read a group-volume table entry.

Existing declarations outside the assigned range constrain several drafts: `func_800281C4` and `func_80028600` appear to return void; `func_80028600` likely takes u8/f32/f32/s8; `func_8002A900` likely takes u16; `func_8002FAC0` likely takes u8/s16; `func_8002FFDC` likely takes word-sized forwarding arguments rather than the existing s16 second/fourth arguments. These declarations were not changed.

No inline assembly, register bindings, volatile tricks, compiler pragmas, or new data definitions were introduced. The retained 16-byte event layout and unrolled reset loop are the main code-generation details. Large switch drafts (`func_8002E724`, `func_8002BBD0`) still need jump-table ownership resolved; double/float math drafts also need constant ownership checked before promotion. The camera and particle drafts use reconstructed typed contexts and corrected call signatures.

Final clean validation: `make clean && make extract && make && make progress` passed. ROM and all three images are byte-identical. `git diff --check` passed.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,544 | 8,892 (2.78%) | 8,892 (2.78%) | 407 | 76 | 0 | 86 | 430 (137,648) |
| boot | 8,468 | 0 (0.00%) | 0 (0.00%) | 21 | 0 | 0 | 0 | 99 (16,028) |
| main | 173,204 | 5,488 (3.17%) | 5,488 (3.17%) | 194 | 40 | 0 | 56 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 3,404 (2.48%) | 3,404 (2.48%) | 185 | 36 | 0 | 30 | 0 (0) |
| ovl_7E00 | 444 | 0 (0.00%) | 0 (0.00%) | 7 | 0 | 0 | 0 | 162 (87,228) |

Worktree: `/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-13afb831`.
