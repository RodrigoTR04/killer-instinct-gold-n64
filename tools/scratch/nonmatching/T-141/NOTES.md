# T-141 working notes

`func_801B5DCC`: 15 different words, 1884/1884 bytes, full TU. The
asm-differ comparison separates into these classes:

- At +0x244/+0x248, address calculation and the -10.0f constant load are
  scheduled in opposite order. The selected height-record pointer is held in
  `v1` in the draft and `v0` in the target; this also accounts for the
  `lh` at +0x25c and the three pointer calculations at +0x3a4, +0x528, and
  +0x604. The candidate cause is the lifetime of the selected record across
  the three helper-bearing branches, which also need the original card index.
- At +0x264/+0x268/+0x278/+0x280, the temporary FP registers for the
  -10.0f constant and the height conversion are exchanged. Their source
  statements are the initialization of `z` and conversion of the selected
  record's right height. Different honest orders so far either preserve this
  exchange or add instructions.
- At +0x610..+0x620, the load of the card pointer from the argument slot is
  scheduled after rather than before the height store. `index = arg1->index`
  was moved after the height store to reflect that the index itself is loaded
  after the store; the pointer load is independent and may be scheduled early.
  The store itself also carries the record pointer's `v1`/`v0` difference.

`func_801B5650`: 31 different words, 1920/1916 bytes, full TU. The extra
instruction is an unconditional branch after the final display-list stores,
introduced by the normal `if (state != 5) { ... return result; } return 0;`
shape. The target returns directly at that point and branches to its epilogue
from the state-5 path. The direct early-return shape removes that late branch
but changes the state test to a branch-likely and still emits 1920 bytes.
The selected height-record pointer is again `v1` rather than target `v0`;
the initial height conversion and -10.0f temporary FP registers are exchanged.

The two character conversion declarations in `ovl_7DF8_12C70.c` and the
carousel copy declarations are reconciled with their actual prototypes/views;
`func_801BF720`, `func_801BF914`, and `func_801B695C` now screen in the full
TU at 2, 2 and 4 words respectively. These are nonmatching drafts.

Local-region decomp-permuter runs used `--stack-diffs`: the height setup and
final stores of 5DCC were confined with `PERM_RANDOMIZE`, and the 1DE4 entry
was searched separately. No valid zero was found. A 1DE4 improvement used a
volatile artificial temporary and was rejected. No T4 claim follows from these
notes.

Additional follow-up on the requested structural alternatives:

- `func_801B5DCC`: computing the record afresh from `arg1->index` at the
  final store compiled to 1844/1884 B and 285 differing words. Re-reading the
  card index during the initial no-call region retained the 15-word score;
  a field-offset pointer and separately scoped/raw height temporary did not
  improve it. Deferring the initial -10.0f into the actual state paths emitted
  1928 B. A narrowed index is not supported by the original full-width load.
- `func_801B5650`: moving the state-5 return before the rendering path kept
  the extra instruction and scored 99 words in the matching-frame context;
  using a real local for the rotation-matrix address did not reduce it.
- `func_801B695C`: removing the cached bank pointer produces the correct
  0x28 frame, but moves its three spill slots four bytes earlier (11 words).
  Retaining a distinct frame index and narrowing its scope puts two slots in
  their target positions, but grows the frame to 0x30 (7 words). The existing
  full-TU draft remains at 4 words. Attempts to reuse the input parameter
  for the scaled bank index changed register allocation throughout.
- `func_801BF720` and `func_801BF914` remain 2 words away in the full TU.
  Reusing the result as a selector or predicate and several natural default
  and shared-result forms did not change their scores.
- `func_801B1DE4` remains 15 words away; the named old/new counter variants
  emitted 552/556 bytes rather than the target's 556. The bounded entry-only
  permuter found no acceptable match.
- `func_801BAA78` remains 15 words away. Reusing the input coordinate or
  extracting the counter as a frame value changed scheduling and did not
  improve the full-TU score.

Mid-size structural investigation (full translation-unit scores):

| Function | Bytes | Starting words | Best words | Notes |
| --- | ---: | ---: | ---: | --- |
| func_801BEEA4 | 344 | 39 | 16 | Shared insertion index and position scalar. |
| func_801C49A8 | 548 | 83 | 83 | Correct reload variant scores 108; old draft caches a global across a call. |
| func_801C3758 | 564 | 30 | 30 | Frame and next-frame split probes. |
| func_801C2F5C | 544 | 44 | 44 | Confirmed selector load occurs after helper calls. |
| func_801AD114 | 628 | 88 | 88 | Correcting two actual no-argument callees produced 123 words / 608 B; target retains argument setup through call branches. |
| func_801C47E0 | 260 | 11 | 11 | Fresh m2c; offset and result lifetimes, integer widths and pointer types did not improve the register choices. |
| func_801C0800 | 248 | 21 | 21 | Color packing and display-list store-order variants did not improve scheduling. |
| func_801C48E4 | 196 | 25 | 0 | Narrow input dimensions and actual unsigned-width callee arguments recover the original masking and argument setup. |
| func_801ADA04 | 208 | 14 | 14 | Direct condition and mode-update variants did not improve allocation. |
| func_801BD200 | 112 | 14 | 14 | Shared limit, enabled flag, and player-array pointers retained or worsened allocation. |
| func_801C8004 | 236 | 6 | 6 | Separate first- and second-scan cursor variables do not recover target registers. |
| func_801BE660 | 300 | 41 | 41 | Fresh m2c; hoisting the spacing constant and using literal constants worsened matching. |
| func_801B0520 | 328 | 22 | 22 | Frame, result, and global reload variants did not recover the target register allocation. |
| func_801C4240 | 1344 | 126 | 126 | Fresh m2c; moving the timer store before the float computation retained 126 words and a 16-byte oversized frame. |
| func_801B446C | 292 | 28 | 28 | Fresh m2c; byte-width flag and pointer/compound-update variants did not improve the global-base register. |
| func_801C11F0 | 580 | 113 | 90 | A separate intensity scalar follows the original value lifetime and restores the original 580-byte text size; frame and registers still differ. |
| func_801AFFAC | 576 | 99 | 99 | Fresh m2c; sharing the fade counter with the incoming frame and using the actual signed value left 99 words. |
| func_801AD7D8 | 556 | 89 | 89 | Fresh m2c; first divergence is allocation of the retained command-list start, followed by reusing the boot-end address for code. |
| func_801C5298 | 3036 | 741 | 738 | Declaration-context diagnostic corrects the three-argument func_801C48E4 and six-argument func_800131A4 calls; it emits 2,984 of 3,036 bytes and requires full-TU reconciliation. |
| func_801B1210 | 284 | 27 | 27 | Reusing the frame argument for alpha changes register allocation throughout and does not improve the draft. |
| func_801C47E0 (follow-up) | 260 | 11 | 10 | Reusing the bank value for the subsequent transfer length removes one differing word; the remaining register allocation still differs. |
| func_801BADEC | 568 | 100 | 99 | Fresh m2c; sharing the vertical offset gives a one-word improvement; delaying the first coordinate or caching scale regresses. |
| func_801BD270 | 396 | 7 | 7 | Corrected func_8002B6EC to its real zero-argument prototype; the remaining seven words concern the order and registers used to pack the 64-bit controller result. Signed-width and equivalent packing variants did not improve it. |
| func_801BE540 | 288 | 8 | 8 | Fresh m2c and full-TU diff identify the string cursor and character registers; byte/full-width character and loop-increment variants retained eight words or worsened. |
| func_801C224C | 372 | 6 | 6 | Fresh m2c and full-TU diff identify the entry selector and endpoint-address instructions; a separate selector local and the actual byte-width callee prototype worsened the match. |
| func_801C3AA0 | 928 | 119 | 119 | Fresh m2c checked against assembly: the count reload occurs after cosf and again after the random loop; explicitly retaining the intermediate count emitted 932 B and scored 196 words. T-139 also ran a 600-second full-TU search. |
