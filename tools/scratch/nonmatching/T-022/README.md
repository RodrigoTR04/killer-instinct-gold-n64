# T-022 results

T-036 follow-up: three more drafts matched (788 bytes), and twelve drafts improved. 24 of the original 52 functions now match; 28 drafts remain. See [T-036 report](../T-036/REPORT.md). The validation and aggregate totals below describe the original T-022 run.

All 52 functions attempted in ascending size order. 21 matched, 2,548 bytes. No commits made.

Draft word counts compare linked instructions at corresponding function positions; size changes also shift relocations. They are not asm-differ edit-distance scores.

| Function | Bytes | Status | Remaining difference |
|---|---:|---|---|
| `func_8001C5A0` | 12 | MATCHED | — |
| `func_800183B4` | 24 | MATCHED | — |
| `func_8001864C` | 24 | MATCHED | — |
| `func_80018E70` | 24 | MATCHED | — |
| `func_800191D8` | 24 | MATCHED | — |
| `func_80019704` | 24 | MATCHED | — |
| `func_80019868` | 24 | MATCHED | — |
| `func_8001A9E8` | 56 | MATCHED | — |
| `func_8001CD0C` | 68 | MATCHED | — |
| `func_800183CC` | 76 | MATCHED | — |
| `func_8001D42C` | 80 | MATCHED | — |
| `func_8001BB10` | 84 | DRAFT | 3 words; 84/84 bytes |
| `func_8001C534` | 108 | MATCHED | — |
| `func_8001AA20` | 112 | MATCHED | — |
| `func_8001BA94` | 124 | MATCHED | — |
| `func_8001D768` | 124 | MATCHED | — |
| `func_8001AC80` | 132 | MATCHED | — |
| `func_8001C05C` | 136 | MATCHED | — |
| `func_80018E88` | 152 | DRAFT | T-036: 2 linked words; 152/152 bytes |
| `func_8001D37C` | 176 | MATCHED | T-036; draft deleted |
| `func_8001C0E4` | 204 | MATCHED | — |
| `func_8001C370` | 204 | DRAFT | T-036: 4 linked words; 204/204 bytes |
| `func_8001C43C` | 248 | DRAFT | 65 words; 272/248 bytes |
| `func_8001B50C` | 276 | MATCHED | — |
| `func_8001C1B0` | 292 | MATCHED | T-036; draft deleted |
| `func_8001BDE0` | 316 | DRAFT | T-036: 15 linked words; 316/316 bytes |
| `func_8001BF1C` | 320 | MATCHED | T-036; draft deleted |
| `func_8001CBCC` | 320 | DRAFT | T-036: 16 linked words; 320/320 bytes |
| `func_8001971C` | 332 | MATCHED | — |
| `func_8001CF1C` | 356 | DRAFT | T-036: 6 linked words; 356/356 bytes |
| `func_8001CD50` | 460 | DRAFT | 104 words; 436/460 bytes |
| `func_800191F0` | 492 | DRAFT | 123 words; 508/492 bytes |
| `func_8001AA90` | 496 | DRAFT | 66 words; 488/496 bytes |
| `func_80018418` | 564 | MATCHED | — |
| `func_8001DE5C` | 600 | DRAFT | T-036: 149 linked words; 624/600 bytes |
| `func_8001BB64` | 636 | DRAFT | 195 words; 812/636 bytes |
| `func_8001E0B4` | 648 | DRAFT | T-036: 61 linked words; 648/648 bytes |
| `func_80018F20` | 696 | DRAFT | 141 words; 688/696 bytes |
| `func_8001D47C` | 748 | DRAFT | T-036: 177 linked words; 892/748 bytes |
| `func_8001D080` | 764 | DRAFT | 177 words; 756/764 bytes |
| `func_8001808C` | 808 | DRAFT | 184 words; 796/808 bytes |
| `func_800193DC` | 808 | DRAFT | 194 words; 788/808 bytes |
| `func_80018AE0` | 912 | DRAFT | 201 words; 896/912 bytes |
| `func_8001B134` | 984 | DRAFT | T-036: 228 linked words; 984/984 bytes |
| `func_8001B620` | 1016 | DRAFT | T-036: 87 linked words; 1016/1016 bytes |
| `func_8001AD04` | 1072 | DRAFT | 251 words; 1100/1072 bytes |
| `func_80018664` | 1148 | DRAFT | 287 words; 1160/1148 bytes |
| `func_8001C5AC` | 1568 | DRAFT | 431 words; 1908/1568 bytes |
| `func_8001D7E4` | 1656 | DRAFT | T-036: 413 linked words; 1748/1656 bytes |
| `func_8001E33C` | 2360 | DRAFT | 604 words; 2420/2360 bytes |
| `func_80019880` | 4456 | DRAFT | Build failed before byte comparison: cfe: Error: src/main/main.c, line 1083: redeclaration of 'D_8004ACCC'; previous declaration at line 487 in file 'src/main/main.c'; cfe: Error: src/main/main.c, line 1083: redeclaration of 'D_8004ACD0'; previous declaration at line 488 in file 'src/main/main.c' |
| `func_8001EC74` | 8740 | DRAFT | T-036: 2174 linked words; 8476/8740 bytes |

Final clean validation: `make clean && make extract && make && make progress` passed; ROM and all three images byte-identical.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,544 | 4,888 (1.53%) | 4,888 (1.53%) | 516 | 9 | 0 | 44 | 430 (137,648) |
| boot | 8,468 | 0 (0.00%) | 0 (0.00%) | 21 | 0 | 0 | 0 | 99 (16,028) |
| main | 173,204 | 4,200 (2.42%) | 4,200 (2.42%) | 244 | 9 | 0 | 37 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 688 (0.50%) | 688 (0.50%) | 244 | 0 | 0 | 7 | 0 (0) |
| ovl_7E00 | 444 | 0 (0.00%) | 0 (0.00%) | 7 | 0 | 0 | 0 | 162 (87,228) |

Suggested types/names: `T022Position` has s16 XYZ at +0x28/+0x2A/+0x2C; `T022Sprite` is a 0x1C-byte descriptor; `T022DmaEntry` is a 0x20-byte ROM-entry record. `func_8001D768` initializes a sprite descriptor; `func_8001D42C` loads a 32-byte variant record; `func_8001C05C` loads two RGB triplets and six configuration bytes. `func_8001A9E8` forwards an incoming float to `func_8001AA90`.

No inline assembly, register bindings, emitted data, or compiler pragmas were introduced. `func_800183CC` writes Z/Y/X in source order to reproduce IDO scheduling. Initializer types and several external call signatures remain provisional.
