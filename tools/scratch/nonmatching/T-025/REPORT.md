T-025 / sol-A10

Worktree: /home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3aca5c0f

6 matched functions / 284 bytes. All 39 functions received reconstructed C compile attempts, smallest first. No commits. Only verified C remains in src; 33 nonmatches are restored to GLOBAL_ASM and saved here as drafts.

| Function | Bytes | Status | Remaining diff |
|---|---:|---|---|
| `func_801AF67C` | 16 | MATCHED |  |
| `func_801AF5D4` | 24 | MATCHED |  |
| `func_801AF5B8` | 28 | MATCHED |  |
| `func_801AFA80` | 36 | MATCHED |  |
| `func_801B19F0` | 36 | MATCHED |  |
| `func_801AFA48` | 52 | DRAFT | Body matches; missing four-byte boundary alignment after the return shifts following code. |
| `func_801AF5EC` | 144 | MATCHED |  |
| `func_801B17BC` | 256 | DRAFT | Global-address initialization is scheduled after the loop-index/pointer setup instead of before it. |
| `func_801B1210` | 284 | DRAFT | Alpha/global/display-list temporary registers and store/call scheduling differ; same body size. |
| `func_801B18BC` | 300 | DRAFT | Large loop increment is hoisted into an extra saved register; register allocation, scheduling and trailing padding differ. |
| `func_801B0520` | 328 | DRAFT | Integer and display-list temporary registers, constant scheduling and global-address reuse differ. |
| `func_801AF424` | 404 | DRAFT | Instruction sequence matches apart from frame 0x88 versus 0x80 and perspective-normalization slot sp+0x86 versus sp+0x7E. |
| `func_801B2010` | 420 | DRAFT | Counter update/branch form, temporary registers and display-list scheduling differ. |
| `func_801B21B4` | 420 | DRAFT | Counter update/branch form, temporary registers and display-list scheduling differ. |
| `func_801B2358` | 420 | DRAFT | Counter update/branch form, temporary registers and display-list scheduling differ. |
| `func_801B24FC` | 420 | DRAFT | Counter update/branch form, temporary registers and display-list scheduling differ. |
| `func_801B26A0` | 420 | DRAFT | Counter update/branch form, temporary registers and display-list scheduling differ. |
| `func_801B2844` | 420 | DRAFT | Counter update/branch form, temporary registers and display-list scheduling differ. |
| `func_801B29E8` | 420 | DRAFT | Counter update/branch form, temporary registers and display-list scheduling differ. |
| `func_801B2EF4` | 536 | DRAFT | Frame/local alpha slot, counter update, unsigned float conversion and display-list scheduling differ. |
| `func_801B310C` | 536 | DRAFT | Frame/local alpha slot, counter update, unsigned float conversion and display-list scheduling differ. |
| `func_801B3324` | 536 | DRAFT | Frame/local alpha slot, counter update, unsigned float conversion and display-list scheduling differ. |
| `func_801B353C` | 536 | DRAFT | Frame/local alpha slot, counter update, unsigned float conversion and display-list scheduling differ. |
| `func_801B3754` | 536 | DRAFT | Frame/local alpha slot, counter update, unsigned float conversion and display-list scheduling differ. |
| `func_801B396C` | 536 | DRAFT | Frame/local alpha slot, counter update, unsigned float conversion and display-list scheduling differ. |
| `func_801B1DE4` | 556 | DRAFT | Counter/interpolation globals, pointer lifetime across the vertex helper, float temporaries and display-list scheduling differ. |
| `func_801B3B84` | 556 | DRAFT | Frame/local alpha slot, counter update, unsigned float conversion and display-list scheduling differ. |
| `func_801AFFAC` | 576 | DRAFT | Interpolation/control-flow temporaries and unsigned color-conversion/packing scheduling differ. |
| `func_801B0A40` | 668 | DRAFT | Float temporaries, matrix local stack layout and call/display-list scheduling differ. |
| `func_801B01EC` | 820 | DRAFT | Float/global temporaries, matrix stack layout and call/display-list scheduling differ. |
| `func_801B1A7C` | 872 | DRAFT | Compiler unrolls the vertex loop twice rather than four times; saved/float registers and scheduling differ. |
| `func_801B2B8C` | 872 | DRAFT | Matrix stack layout, counter/unsigned alpha conversion, temporary registers and display-list scheduling differ. |
| `func_801AF68C` | 956 | DRAFT | Callback dispatch and queue-compaction loop induction/unrolling, stack layout and temporary registers differ. |
| `func_801B0668` | 984 | DRAFT | Float temporaries, matrix stack layout and call/display-list scheduling differ. |
| `func_801B132C` | 1168 | DRAFT | Selection interpolation/control-flow, float and saved registers, and helper-call scheduling differ. |
| `func_801AFAA4` | 1288 | DRAFT | Texture-swap condition/control flow, float temporaries and display-list/call scheduling differ. |
| `func_801B0CDC` | 1332 | DRAFT | Matrix stack layout, float/integer temporaries and call/display-list scheduling differ. |
| `func_801B3DB0` | 1360 | DRAFT | Typed initialization loops have different induction/unrolling, saved registers and scheduling. |
| `func_801ADEA0` | 5508 | DRAFT | DMA/inflate cursor lifetime and stack layout (0x48 versus 0x40), then asset-call temporary registers differ. |

Suggested names/types:

- `D_802A2178`: active effect flag mask; `func_801AF5D4`: enableEffectFlags; `func_801AF67C`: queryEffectFlags; `func_801AF5EC`: disableEffectFlagsAndResetTimers.
- `T025Effect` is a partial 0x68-byte effect record: flags at +8, start/state timestamp at +0x10. The array has 52 entries.
- `func_801AF5B8`: reset camera position; floats at +0xC8/+0xCC/+0xD0 are set to {0,0,-600}.
- `func_801AFA80` and `func_801B19F0`: linear interpolation with signed integer numerator/denominator.

Matched C uses ordinary array indexing, compound flag updates and a partial struct. No inline assembly, register binding, new data definitions or compiler pragmas. Draft fade callbacks preserve an original read of an uninitialized alpha byte before assignment on their steady-state path; this is documented reconstruction, not a recommended new-code idiom.

Iteration builds reused extracted generated files with make --assume-old options, while retaining ROM and image verification. Final validation uses the requested unmodified make clean && make extract && make && make progress sequence.


Clean validation passed: rebuilt ROM and main/ovl_7DF8/ovl_7E00 images are byte-identical. Generated docs/functions.csv and docs/progress.html were restored after recording progress, so no docs changes are part of this work.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,544 | 9,520 (2.98%) | 9,520 (2.98%) | 398 | 81 | 0 | 90 | 430 (137,648) |
| boot | 8,468 | 0 (0.00%) | 0 (0.00%) | 21 | 0 | 0 | 0 | 99 (16,028) |
| main | 173,204 | 4,200 (2.42%) | 4,200 (2.42%) | 213 | 40 | 0 | 37 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 5,320 (3.87%) | 5,320 (3.87%) | 157 | 41 | 0 | 53 | 0 (0) |
| ovl_7E00 | 444 | 0 (0.00%) | 0 (0.00%) | 7 | 0 | 0 | 0 | 162 (87,228) |
