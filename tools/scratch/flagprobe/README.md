# T-010 game compiler probes

From the repository root, reproduce all ten full-body matches and two known
nonmatches (exit 0 means the expected baseline was reproduced):

```sh
.venv/bin/python tools/scratch/flagprobe/compare.py
```

Run one match independently (exit 0 match; exit 1 mismatch):

```sh
.venv/bin/python tools/scratch/flagprobe/compare.py --function 8001C2D4
```

Reproduce all 360 experiments, including both compiler versions, both ISAs,
seven optimization/debug configurations, and two controls without the multiply
workaround:

```sh
.venv/bin/python tools/scratch/flagprobe/compare.py --matrix --json /tmp/kig-t010-results.json
```

Choose another configuration explicitly:

```sh
.venv/bin/python tools/scratch/flagprobe/compare.py --function 801B55DC --version 7.1 --cflags '-O2 -mips2 -G 0 -non_shared -Wab,-r4300_mul -Xcpluscomm'
```

The script uses Python's standard library, the installed IDO compilers, and the
verified US V1.0 ROM (override with `--rom`). It verifies the ROM SHA1, expands
the two needed segments in memory, and uses a unique temporary directory for
objects. It does not need `asm/`, `build/segments/`, m2c, or binutils to compare.
No ROM-derived binaries are stored here.

It extracts the named ELF function's size, requires the complete target size,
and masks only actual R_MIPS_26/HI16/LO16 relocation fields. It retains
registers, opcode order, branch offsets, stack/field offsets, and ordinary
immediates. Unknown text relocation kinds fail closed. Padding is excluded.
External symbol values, double constant contents, and jump-table contents are
not established by this text-only comparison. The switch probe remains a
nonmatch; no claim of a matching jump-table reconstruction is made.

The C files are plausible isolated reconstructions derived from independent
spimdisasm/m2c output and manual type/control-flow correction, not original
source or recovered function names. `80013BE0.c` and `801BF914.c` deliberately
preserve unresolved cases. See `docs/compiler_flags.md` for the experiment
matrix, discriminating examples, confidence, and limits.
