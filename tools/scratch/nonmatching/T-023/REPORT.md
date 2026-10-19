T-023 / sol-B8

Worktree: /home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-1fba501a

Matched: 4 functions / 352 bytes. All 55 functions received real C compile attempts, in size order; none is NOT ATTEMPTED. Only verified matches remain in src. No commits.

Baseline: ROM and all three images OK, 46 T4 functions. Iterative builds used make --assume-old for extraction outputs to avoid re-extracting after every source edit; final validation uses the requested clean extraction/build/progress sequence.

| Function | Bytes | Status | Remaining diff |
|---|---:|---|---|
| `func_801BFB10` | 48 | MATCHED |  |
| `func_801BFC8C` | 48 | MATCHED |  |
| `func_801BF720` | 104 | DRAFT | C switch emits a new jump table; assembly-owned rodata blocks retention. |
| `func_801BD200` | 112 | DRAFT | Same instruction count; global-base/value registers and scheduling differ. |
| `func_801BF914` | 116 | DRAFT | C switch emits a new jump table; default-result register also differs. |
| `func_801C0784` | 124 | MATCHED |  |
| `func_801BFC08` | 132 | MATCHED |  |
| `func_801BF0E8` | 168 | DRAFT | First global load uses a reused base rather than a separate lui; four bytes shorter. |
| `func_801BF678` | 168 | DRAFT | Pointer/counter registers and division scheduling differ. |
| `func_801BF988` | 184 | DRAFT | Saved input/accumulator registers and final result temporaries differ. |
| `func_801BF850` | 196 | DRAFT | Two pairs of global-address addiu instructions are reversed; otherwise text matches. |
| `func_801BFA40` | 196 | DRAFT | Two address-setup pairs differ; original also has twelve bytes of trailing alignment. |
| `func_801BF788` | 200 | DRAFT | Saved-register allocation, accumulator temporaries and scheduling differ. |
| `func_801BFB40` | 200 | DRAFT | Struct-copy/global initialization scheduling and base registers differ. |
| `func_801C1704` | 204 | DRAFT | Multiply versus shift/subtract address calculation; clear-loop unrolling and stores differ. |
| `func_801BEFFC` | 236 | DRAFT | Saved score/value pointer registers are exchanged; global-address setup differs. |
| `func_801C0800` | 248 | DRAFT | Display-list temporaries, packed-color arguments and scheduling differ. |
| `func_801BE540` | 288 | DRAFT | Compile blocked by incompatible func_801BE540 declaration outside assigned range. |
| `func_801BBB60` | 292 | DRAFT | Palette-loop types, unrolled store order and global-base scheduling differ. |
| `func_801BE660` | 300 | DRAFT | Font traversal, float registers, call arguments and scheduling differ. |
| `func_801BB464` | 304 | DRAFT | Rendering-coordinate temporaries, stack spills, table loads and scheduling differ. |
| `func_801BEEA4` | 344 | DRAFT | Score signedness, stack frame, insertion-loop registers and control flow differ. |
| `func_801BE910` | 356 | DRAFT | Score narrowing and loop unrolling/register allocation differ. |
| `func_801C0610` | 372 | DRAFT | Display-list base registers, matrix address loads and scheduling differ. |
| `func_801BE790` | 384 | DRAFT | Table initialization/store scheduling and loop pointer registers differ. |
| `func_801BD270` | 396 | DRAFT | 64-bit return packing, stack temporaries and pad-field scheduling differ. |
| `func_801BED0C` | 408 | DRAFT | 64-bit divide/remainder code, loop registers and scheduling differ. |
| `func_801C17D0` | 448 | DRAFT | Stat comparison control flow, 64-bit result stores and saved registers differ. |
| `func_801BA280` | 496 | DRAFT | Rendering-coordinate temporaries, stack spills, table loads and scheduling differ. |
| `func_801BA884` | 500 | DRAFT | Rendering-coordinate temporaries, stack spills, table loads and scheduling differ. |
| `func_801BA088` | 504 | DRAFT | Rendering-coordinate temporaries, stack spills, table loads and scheduling differ. |
| `func_801BA470` | 516 | DRAFT | Rendering-coordinate temporaries, stack spills, table loads and scheduling differ. |
| `func_801BBC84` | 516 | DRAFT | Fire-effect traversal, random-call temporaries and loop scheduling differ. |
| `func_801BB258` | 524 | DRAFT | Rendering-coordinate temporaries, stack spills, table loads and scheduling differ. |
| `func_801BA674` | 528 | DRAFT | Rendering-coordinate temporaries, stack spills, table loads and scheduling differ. |
| `func_801BB594` | 544 | DRAFT | Rendering-coordinate temporaries, stack spills, table loads and scheduling differ. |
| `func_801BB024` | 564 | DRAFT | Rendering-coordinate temporaries, stack spills, table loads and scheduling differ. |
| `func_801BADEC` | 568 | DRAFT | Rendering-coordinate temporaries, stack spills, table loads and scheduling differ. |
| `func_801BD3FC` | 580 | DRAFT | 64-bit input unpacking, button-history loads and branching differ. |
| `func_801C11F0` | 580 | DRAFT | Digit buffer/float-bit union stack layout and call scheduling differ. |
| `func_801BEA74` | 664 | DRAFT | 64-bit mixed-radix multiply/add sequencing and stack/register allocation differ. |
| `func_801C1990` | 676 | DRAFT | Stat-array comparisons, branch layout and 64-bit zero stores differ. |
| `func_801C1434` | 720 | DRAFT | 64-bit score loads/call ABI, branches and saved-register allocation differ. |
| `func_801BBE88` | 808 | DRAFT | Display-list pointer/register allocation and command-store scheduling differ. |
| `func_801BAA78` | 884 | DRAFT | Rendering temporaries, stack spills and display-list command scheduling differ. |
| `func_801BB7B4` | 940 | DRAFT | Audio-handle loads/types, saved temporaries and branch scheduling differ. |
| `func_801BD640` | 1068 | DRAFT | Font/matrix pointers, float/double temporaries, stack and scheduling differ. |
| `func_801C1C34` | 1244 | DRAFT | Text/digit buffers, pointer traversal and rendering-call register allocation differ. |
| `func_801BF190` | 1256 | DRAFT | Score/name buffers, table traversal, stack frame and rendering calls differ. |
| `func_801BDA6C` | 1320 | DRAFT | Glyph/matrix pointers, float/double arithmetic and rendering scheduling differ. |
| `func_801BDF94` | 1452 | DRAFT | Matrix/vector buffer types, float arguments, stack and rendering scheduling differ. |
| `func_801BCB70` | 1676 | DRAFT | Mask pointer types, clipping arithmetic, stack and display-list scheduling differ. |
| `func_801C08F8` | 2296 | DRAFT | 64-bit score decoding, text buffers, float arguments and rendering sequencing differ. |
| `func_801BFCBC` | 2388 | DRAFT | 64-bit input ABI, state-machine branches, stack and global scheduling differ. |
| `func_801BC1B0` | 2496 | DRAFT | Clipping arithmetic, stack frame, temporary registers and display-list stores differ. |

Suggested names/types:

- `func_801BFB10`: refresh/rebuild high-score tables after loading persistent data; it calls two storage routines and `func_801BEFFC`.
- `func_801BFC08`: advance high-score page/scroll position; the page index is `D_802D37D0`, the scroll position is `D_802D37F8`.
- `func_801BFC8C`: previous high-score page, wrapping from zero to thirteen, then resets scroll to 160.
- `func_801C0784`: draw the high-score page with scroll clamping; clears `D_801CD454`. Its first argument is a display-list cursor despite the currently matching integer signature.
- `func_801BF720`/`func_801BF914`: packed-name glyph encode/decode. The switch tables remain assembly-owned.
- `D_80127D80`: eight-byte table descriptors (entry pointer, u8 count, u8 ordering flag, two padding bytes); entries appear to be eight bytes (u32 packed name, u16 score, two padding bytes). Draft signedness still needs verification.
- `func_801BEA74` and `func_801BED0C` encode/decode a 64-bit mixed-radix score-placement value, using radices 11 and 6.
- `func_801BE540` has an incompatible declaration outside this range: the matched downstream wrapper declares integer text/x arguments and 32-bit colors, while its body indicates a text pointer, float x, and byte colors. This needs coordinated type cleanup rather than editing another worker's function.

No inline assembly, register binding, new data definitions, or compiler pragmas were added. The matching previous-page function uses a post-decrement condition; direct global comparisons (rather than cached locals) were needed for the scrolling wrapper. Drafts use explicit display-list/glyph types, byte-offset matrix access, and unions for a few float bit patterns; these are not retained in src. `func_801BFA40` has twelve bytes of original trailing alignment, an additional blocker after its address scheduling differences.

Final validation: `make clean && make extract && make && make progress` passed. ROM and all three images are byte-identical. Generated docs were restored afterward to honor scope.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,544 | 5,408 (1.69%) | 5,408 (1.69%) | 474 | 45 | 0 | 50 | 430 (137,648) |
| boot | 8,468 | 0 (0.00%) | 0 (0.00%) | 21 | 0 | 0 | 0 | 99 (16,028) |
| main | 173,204 | 1,652 (0.95%) | 1,652 (0.95%) | 265 | 9 | 0 | 16 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 3,756 (2.73%) | 3,756 (2.73%) | 181 | 36 | 0 | 34 | 0 (0) |
| ovl_7E00 | 444 | 0 (0.00%) | 0 (0.00%) | 7 | 0 | 0 | 0 | 162 (87,228) |
