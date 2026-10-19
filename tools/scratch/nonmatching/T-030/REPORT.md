T-030 / sol-C13

Worktree: /home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-49e9e79f

2 matched functions / 548 bytes. All 25 functions received reconstructed C compile attempts. None is NOT ATTEMPTED. Only verified matching C remains in src. No commits.

Baseline: ROM and all three images byte-identical; 115 T4 functions.

| Function | Status | Remaining diff |
|---|---|---|
| `func_801C2110` | MATCHED |  |
| `func_801C224C` | DRAFT | Mode-cache saved register, frame (0x18 vs 0x20), and copy-loop scheduling differ. |
| `func_801C23C0` | DRAFT | Camera-vector stack layout (0xA0 vs 0x70), float temporaries and call scheduling differ. |
| `func_801C2ADC` | DRAFT | 64-bit input comparison/register allocation and clear-loop unrolling differ; C emits a jump table. |
| `func_801C2D34` | DRAFT | Matrix-call float temporaries, display-list pointer registers and scheduling differ. |
| `func_801C2F5C` | DRAFT | Sprite/layout pointer lifetimes, callback arguments, frame (0x90 vs 0x60) and scheduling differ. |
| `func_801C317C` | DRAFT | Text-position float temporaries, saved counters, stack slots and call scheduling differ. |
| `func_801C35D8` | DRAFT | Visibility-flag branch shape, saved-register assignment and display-list scheduling differ. |
| `func_801C3758` | DRAFT | Extra argument spill, frame-wrap assignments, vertex/display-list registers and scheduling differ. |
| `func_801C3990` | DRAFT | Loop matches; f0 and f2 are exchanged for zero and the external float before guTranslate. |
| `func_801C3AA0` | DRAFT | Particle/random arithmetic, saved float/integer registers and vertex-store scheduling differ. |
| `func_801C3E40` | DRAFT | Display-list/count/index registers, vertex updates and instruction scheduling differ. |
| `func_801C407C` | DRAFT | Switch emits new rodata; initialization register allocation and scheduling also differ. |
| `func_801C4240` | DRAFT | Projection-output/float stack layout, display-list temporaries and call scheduling differ. |
| `func_801C47E0` | DRAFT | Frame (0x40 vs 0x38), aligned-offset expression reuse, return temporaries and scheduling differ. |
| `func_801C49A8` | DRAFT | Frame (0x58 vs 0x48), mode/flag registers, argument spills and call scheduling differ. |
| `func_801C5064` | DRAFT | Frame (0x78 vs 0x80), saved float/integer registers and text-call scheduling differ. |
| `func_801C5298` | DRAFT | Camera-vector/temporary stack layout, interpolation loop and rendering-call scheduling differ. |
| `func_801C5E74` | DRAFT | Palette conversion loop unrolling, asset/coordinate pointer registers, frame and rendering scheduling differ. |
| `func_801C67CC` | DRAFT | Frame (0x60 vs 0x28), double lifetime/spills and unsigned-result conversion registers differ. |
| `func_801C7310` | DRAFT | Tick/float and text-layout temporaries, stack layout and audio/render call scheduling differ. |
| `func_801C78B0` | MATCHED |  |
| `func_801C7998` | DRAFT | C emits a jump table; 64-bit switch high-word setup, narrow increments and registers differ. |
| `func_801C7A98` | DRAFT | Four-way unrolled threshold loop is close; final maximum/mode globals and registers differ. |
| `func_801C7CD0` | DRAFT | Narrow mode argument, global-base registers, initialization and call scheduling differ. |

Drafts have explicit types and field layouts, not unedited m2c output. The adjacent .diff.txt files record the last compiled attempts; absolute data addresses can shift when a draft changes total text size. Their headers summarize the substantive differences. GLOBAL_ASM was restored after every failed attempt. Iteration builds used --assume-old for extraction outputs only; ROM and image verification remained enabled.

Suggested names/types:

- func_801C2110: evaluateCubicPositionAndVelocity; coefficients are three consecutive four-float polynomials, with three-float position and derivative outputs.
- func_801C78B0: expandPlayerButtonPermutation; D_80127C68 contains six-byte permutation records, D_80127CA8 holds two six-halfword outputs, D_802923AC is the halfword lookup table.
- T030Cloud*: 12-byte record with signed halfword x/y/z, angle at +6, angular width at +8, animation frame at +0xA, signed fade/size at +0xB. T030Vertex* is the standard 16-byte vertex layout. The particle system groups three vertices and repurposes the second vertex's color bytes as signed velocity metadata.
- Rendering records have matrix-buffer pointers at +0xF8. The 0x8C-byte sprite record has a texture pointer at +4, clip data at +0x12, scale at +0x7E, vertical offset at +0x80 and callback at +0x88. D_802854D0 uses 16-byte layout records: signed x/y/scale words followed by a flip byte at +0xC.
- func_801C2ADC takes a player index and a 64-bit input word; the o32 ABI leaves a1 unused. D_8028557C is five seven-halfword input sequences. The jump-table cases were recovered from original assembly-owned data for the attempt.

Matching-source details: func_801C2110 needs local 2.0f/3.0f multipliers and natural polynomial ordering to preserve IDO multiplication and addition scheduling. func_801C78B0 uses an old-style parameter definition because the unchanged callers declare it without a prototype; an ANSI u8 prototype conflicts with those declarations under IDO. Its existing T021Six typedef/declaration was moved above the new shared user, without changing the other function bodies. No new data, inline assembly, register binding or compiler pragmas were introduced. All new draft typedef names begin T030.

The progress scanner recognizes only the ANSI definition of func_801C2110, so automatic T4 rises from 115 to 116. func_801C78B0 remains T1 in that generated table despite its byte-identical C: inventory.py:98 does not recognize K&R parameter declarations between the function signature and opening brace. No progress code or status was edited. To make this match count automatically, coordinate an ANSI u8/u8 prototype update for the two unchanged func_801C78B0 declarations above its callers, then use the equivalent ANSI definition. Those declarations belong to other functions and were left alone under this task's scope. Broader rendering and callback signatures should also be coordinated separately before promoting the drafts.

Final validation: `make clean && make extract && make && make progress` passed. ROM, main, ovl_7DF8 and ovl_7E00 are byte-identical. All 23 final drafts also compile independently under the specified IDO flags. Generated docs were restored after capturing progress to honor task scope. No commits.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,544 | 11,636 (3.64%) | 11,636 (3.64%) | 231 | 222 | 0 | 116 | 430 (137,648) |
| boot | 8,468 | 0 (0.00%) | 0 (0.00%) | 21 | 0 | 0 | 0 | 99 (16,028) |
| main | 173,204 | 5,596 (3.23%) | 5,596 (3.23%) | 135 | 98 | 0 | 57 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 6,040 (4.40%) | 6,040 (4.40%) | 68 | 124 | 0 | 59 | 0 (0) |
| ovl_7E00 | 444 | 0 (0.00%) | 0 (0.00%) | 7 | 0 | 0 | 0 | 162 (87,228) |
