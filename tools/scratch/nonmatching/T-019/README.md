# T-019 / sol-A7

17 new matches, 1,632 bytes. Final clean extraction/build/progress passed: ROM and all three images byte-identical. No commits.

| Function | Bytes | Status | Remaining diff |
|---|---:|---|---|
| `func_801ABB20` | 3644 | NOT ATTEMPTED |  |
| `func_801AC95C` | 380 | MATCHED |  |
| `func_801ACAD8` | 68 | MATCHED |  |
| `func_801ACB1C` | 744 | NOT ATTEMPTED |  |
| `func_801ACF1C` | 52 | MATCHED |  |
| `func_801ACF50` | 52 | MATCHED |  |
| `func_801ACF84` | 68 | MATCHED |  |
| `func_801AD030` | 52 | MATCHED |  |
| `func_801AD064` | 52 | MATCHED |  |
| `func_801AD098` | 52 | MATCHED |  |
| `func_801AD0CC` | 72 | MATCHED |  |
| `func_801AD114` | 628 | DRAFT | Control flow, argument spills, registers; 648 versus 628 bytes. |
| `func_801AD388` | 52 | MATCHED |  |
| `func_801AD3BC` | 428 | DRAFT | Segmented-address hoisting and instruction scheduling; 428 bytes. |
| `func_801AD568` | 556 | DRAFT | 0x28 versus 0x40 stack frame; pointer lifetimes and scheduling. |
| `func_801AD794` | 68 | MATCHED |  |
| `func_801AD7D8` | 556 | DRAFT | Folded command-pointer increments; 544 versus 556 bytes. |
| `func_801ADA04` | 208 | DRAFT | Global-address reuse and registers; 204 versus 208 bytes. |
| `func_801ADAD4` | 64 | MATCHED |  |
| `func_801ADB14` | 12 | MATCHED |  |
| `func_801ADB20` | 144 | MATCHED |  |
| `func_801ADBB0` | 180 | MATCHED |  |
| `func_801ADC64` | 152 | MATCHED |  |
| `func_801ADCFC` | 220 | NOT ATTEMPTED |  |
| `func_801ADDD8` | 112 | MATCHED |  |

Final `make progress`:

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,544 | 2,696 (0.84%) | 2,696 (0.84%) | 542 | 0 | 0 | 27 | 430 (137,648) |
| boot | 8,468 | 0 (0.00%) | 0 (0.00%) | 21 | 0 | 0 | 0 | 99 (16,028) |
| main | 173,204 | 376 (0.22%) | 376 (0.22%) | 287 | 0 | 0 | 3 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 2,320 (1.69%) | 2,320 (1.69%) | 227 | 0 | 0 | 24 | 0 (0) |
| ovl_7E00 | 444 | 0 (0.00%) | 0 (0.00%) | 7 | 0 | 0 | 0 | 162 (87,228) |

Suggested names/types: partial `RenderState`; `func_801AD794` → initializeRenderState; `func_801AC95C` → fillAndShuffleDigits; `D_8004A414` → pendingGraphicsTasks. No header or symbol changes required. One m2c structured-exit goto remains only in the `func_801AD114` draft; no asm or register tricks in matched C.
