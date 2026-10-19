# Matching a function

Run `tools/setup.sh`, then `make extract`. Pick an eligible T1 function in
`docs/functions.csv`. Generate a first reconstruction with
`.venv/bin/python tools/ext/m2c/m2c.py --help` and the function's extracted
assembly. Edit the reconstruction in `src/<image>/`; replace that function's
`GLOBAL_ASM` line with its C definition, using types from `common.h` and existing
symbol names for extern declarations. Delete its obsolete generated assembly
(or run `make clean && make extract`) before measuring progress.

Run `make`, then compare with asm-differ, for example:

```
KIG_IMAGE=main .venv/bin/python tools/ext/asm-differ/diff.py func_80017064
KIG_IMAGE=ovl_7DF8 .venv/bin/python tools/ext/asm-differ/diff.py func_801B55DC
```

Install asm-differ's optional Python requirements if its CLI requests them.
Iterate on C until the function matches, then run
`make clean && make extract && make && make progress`. T4 is automatic: the C
object must provide the symbol at its original address and all images and the
ROM must match. Never assign T4 manually or reset the original inventory.

## Build conventions

Game C uses IDO 5.3 `-c -G 0 -non_shared -Xcpluscomm -Wab,-r4300_mul -O2
-mips2 -32`. Target-specific `CFLAGS` in Makefile allow per-file overrides
(for example future SDK files using `-O1`). C source and header changes trigger
recompilation; asm-processor dependency files track included assembly.

Splat `c` subsegments emit per-function assembly under
`asm/nonmatchings/<image>/<file>/`. The pinned asm-processor preprocesses
`GLOBAL_ASM` before IDO and merges the assembled functions afterward: IDO cannot
parse GNU inline asm. `include/include_asm.h` supplies the GNU `.include` form
for compatible compilers; IDO uses `GLOBAL_ASM` through asm-processor.

The initial main translation unit is provisional, not a claim about original
file boundaries. The overlay boundary at 0x801ADEA0 preserves the four bytes
of alignment after func_801ADE48; the following unit (`ovl_7DF8_2380.c`, provisional name) starts at that
boundary.
Other routines remain per-function GLOBAL_ASM. Main's constants D_800489D0 and
D_800489D8 remain owned by assembly data at their original addresses; C reads
them as external doubles rather than emitting new constants.

Do not edit ROMs or generated progress numbers, and coordinate shared-checkout
changes with other workers. Do not commit generated asm, assets, or tools/ext.
