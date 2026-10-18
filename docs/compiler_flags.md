# T-010: game compiler experiments

US V1.0, SHA1 `ba52e91b44450c548467044b26951353dc491e04`; measured
2026-10-18. **Recommend IDO 5.3 `-O2 -mips2` for game code. Confidence: high
for the sampled functions, medium-high as the game's default.** Ten complete
GAME function bodies (1,064 bytes) match with only ELF relocation fields
masked. Both main and ovl_7DF8 are represented. This is independent of the
already verified SM64-compatible libultra `-O1` result.

Recommended starting build line:

```make
CC = tools/ext/ido/5.3/cc
CFLAGS = -O2 -mips2 -G 0 -non_shared -Wab,-r4300_mul -Xcpluscomm
```

The experiment identifies compiler/optimization/ISA much more strongly than
every auxiliary flag in that line. In particular **`-Wab,-r4300_mul` is not
identified**: removing it preserves all ten matches. `-G 0`, `-non_shared`,
and `-Xcpluscomm` were common controls, not independently recovered original
command-line tokens. The latter is source syntax support. Do not describe the
entire line as a uniquely proven original invocation.

## Reproduce

```sh
# Ten matches, two deliberately retained nonmatches; expected baseline exits 0:
.venv/bin/python tools/scratch/flagprobe/compare.py
# Each individual successful reconstruction can be checked with this command:
.venv/bin/python tools/scratch/flagprobe/compare.py --function 8001C2D4
# Complete 12-function × 30-configuration experiment:
.venv/bin/python tools/scratch/flagprobe/compare.py --matrix --json /tmp/kig-t010-results.json
```

[Probe README](../tools/scratch/flagprobe/README.md),
[comparison implementation](../tools/scratch/flagprobe/compare.py).
The command verifies the ROM SHA1 and decompresses main/7DF8 in memory;
it needs no regenerated `asm/` or extracted files. Generated objects use a
unique temporary directory and are removed. No ROM-derived binaries are
included in these deliverables.

## Selection and reconstruction

Read the verified tracking, research compiler section, libultra, segments and
toolchain notes first. Main candidates were selected from the non-SDK CSV
entries before the SDK-dominated tail; overlay candidates came from an
independent call/prologue/return scan of the verified CPU text. Each retained
function is 21–41 instructions, with complete return/delay-slot boundaries
checked independently of `asm/`. Zero alignment after the body is excluded.

Generated independent spimdisasm 1.42.4 assembly from decompressed bytes and
ran the pinned m2c through `.venv/bin/python`. Corrected unknown argument
and pointer types, raw-byte pointer increments, lost callback arguments, and
control flow manually. For example, m2c introduced a float temporary in
`801B1A14`; updating the existing second argument instead reproduces its
original register allocation. In `8001C2D4`, a compound byte-field update
avoids an extra copy introduced by a standalone temporary. These are normal
C reconstructions, without inline assembly, register-binding extensions,
compiler pragmas, or instruction encodings embedded in C.

The matrix compiles each same C file under IDO 5.3 and 7.1, `-mips1` and
`-mips2`, with `-O1`, `-O2`, `-O3`, `-g`, `-g3`, `-O2 -g`, and `-O2 -g3`.
Every cell also uses the common controls above. Two extra cells per function
remove the multiply workaround from each version's `-O2 -mips2` invocation.
All 360 compilations completed successfully.

## Per-function results

Y means complete equal-size relocation-masked text, N means this C does not
match. **N excludes a configuration for the supplied reconstruction, not a
mathematical proof that no conceivable source could match under it.**
Columns A/B/C/D/E/F respectively mean:

- A: 5.3 `-O2 -mips2`.
- B: 5.3 `-O1 -mips2`.
- C: 5.3 `-O3 -mips2`.
- D: 5.3 `-O2 -mips1`.
- E: 7.1 `-O2 -mips2`.
- F: 7.1 `-O3 -mips2`.

| Segment / function address | Body bytes | A | B | C | D | E | F | Notes |
|---|---:|:---:|:---:|:---:|:---:|:---:|:---:|---|
| main `80013BE0` | 164 | N | N | N | N | N | N | Unresolved: only two words differ under A; C folds `/ 2.0f` into multiply by 0.5, original uses `div.s` |
| main `80017064` | 96 | Y | N | Y | N | Y | Y | Leaf, ordered range tests, branch-likely, unused argument spills |
| main `8001BA18` | 124 | Y | N | Y | N | Y | Y | Leaf, float multiply/compare, float↔double arithmetic, global state update |
| main `8001C2D4` | 156 | Y | N | N | N | N | N | Leaf with frame, nested loops, byte field +12, integer multiply/divide; strongest main discriminator |
| 7DF8 `801ACE04` | 88 | Y | N | Y | N | Y | Y | Conditional calls, arguments preserved across calls, likely epilogue |
| 7DF8 `801ACE5C` | 100 | Y | N | Y | Y | Y | Y | Conditional callback selection; weak ISA/version discriminator |
| 7DF8 `801ACEC0` | 92 | Y | N | Y | N | Y | Y | Indirect `jalr`, seven callback arguments including stacked floats |
| 7DF8 `801ACFC8` | 104 | Y | N | Y | N | Y | Y | Byte flag and conditional callback selection |
| 7DF8 `801ADE48` | 84 | Y | N | N | Y | N | N | Four byte arguments stored through two global bases; scheduling/version discriminator |
| 7DF8 `801B1A14` | 104 | Y | N | N | N | Y | N | Float squares, sqrt-like call, divide and nonnegative clamp; optimization discriminator |
| 7DF8 `801B55DC` | 116 | Y | N | Y | N | N | N | Leaf decimal digit packing, quotient/remainder; version discriminator, **no relocations at all** |
| 7DF8 `801BF914` | 116 | N | N | N | N | N | N | Unresolved character-to-glyph switch; A differs only in final default-result register (`v0` versus original `v1`) |

All other tested configurations are accounted for here:

| Flags after common controls | IDO 5.3 matches / 12 | IDO 7.1 matches / 12 |
|---|---:|---:|
| `-O1 -mips1` or `-O1 -mips2` | 0 each | 0 each |
| `-O2 -mips2` | 10 | 7 |
| `-O2 -mips1` | 2 | 1 |
| `-O3 -mips2` | 7 | 6 |
| `-O3 -mips1` | 1 | 1 |
| `-g`, either ISA | 0 each | 0 each |
| `-g3`, either ISA | 0 each | 0 each |
| `-O2 -g`, either ISA | 0 each | 0 each |
| `-O2 -g3`, either ISA | 1 each | 1 each |
| `-O2 -mips2`, without multiply workaround | 10 | 7 |

The sole `-O3 -mips1` or `-O2 -g3` match is `801ACE5C`. All successes
under any `-O2 -mips1` cell are `801ACE5C`, plus `801ADE48` for 5.3.
Removing the multiply workaround preserves exactly the corresponding version's
normal `-O2 -mips2` success set.

## Discriminating evidence

**ISA:** branch-likely instructions are present in the original main and
overlay game bodies, not merely SDK code. `80017084` is `bnel`, for example;
`8001C350` is a loop `bnel` with the next iteration's load in its delay slot.
The tested mips1 compilations change scheduling/control flow and fail these
bodies. `ldc1` in `8001BA18` is another useful mips2-level pattern. Two
functions happen to match mips1 too; those functions cannot identify ISA alone.
This supports mips2 over mips1, without claiming higher ISAs were tested.

**Optimization:** `8001C2D4` is 156 bytes under matching 5.3 O2, versus
140 under O1 and 144 under O3. The original saves `s0`, retains an outer
integer counter, and schedules the inner loop's next pointer load into a
branch-likely delay slot. `801B1A14` matches at 104 bytes under O2; O3
produces 96, eliminates the first float argument's spill/reload, and changes
register allocation. These are stronger distinctions than an isolated tiny
wrapper matching multiple optimization levels.

**Compiler version:** under O2/mips2, 7.1 emits 148 bytes for `8001C2D4`,
removes its frame, and converts the outer counter to a pointer/end test.
For relocation-free `801B55DC`, 5.3 reproduces all 29 words, while 7.1 emits
28: it keeps the normalized byte in `a0`, changes quotient/remainder
registers, and puts the shift directly in the early return delay slot.
`801ADE48` supplies a third version-sensitive match. Seven simpler bodies
match both versions; that does not make those bodies evidence for 7.1.

**Debug:** plain `-g` and `-O2 -g` fail all twelve probes, with different
spill/frame patterns (the 104-byte float routine becomes 152 bytes).
`-O2 -g3` is not equivalent to unoptimized debug: it retains most of
`8001C2D4`, but moves its byte store ahead of the generated division checks,
leaving ten mismatching words despite identical size. Hence neither frame
presence nor debug metadata alone establishes debug flags.

**Multiply workaround:** the original nested-loop sequence includes
`multu; mflo; nop; nop; div`. Both with and without `-Wab,-r4300_mul`
reproduce it. That sequence is therefore **not evidence establishing this
flag**. A targeted hazardous multiply sequence would be needed to distinguish
it. Keep the customary Rare flag in the recommended line as a conservative
starting convention, not an experimentally unique result.

## Limits and object variation

The full-size comparator masks only actual emitted `R_MIPS_26` target bits
and `R_MIPS_HI16`/`LO16` immediates; it does not mask all address-looking
instructions. Ordinary branch displacements, arithmetic constants, register
choices, stack offsets and nonrelocated field offsets remain significant.
The decimal formatter has no maskable relocations, so its result is fully
byte-exact. The float/double probe uses separately declared external double
constants at `800489D0`/`800489D8` (both read as 0.001); text comparison does
not validate external values or prove whether original C spelled them as
literals. Nor does masked text establish external symbol identity.

The switch's 27-entry table at `80292C0C` was supplied separately to m2c
from the original bytes. Its five nondefault cases are space, period, slash,
colon and comma. Its reconstruction remains two words away from a text match;
no matching switch/table claim is made. `80013BE0` also remains unresolved:
its division could reflect original source typing, an additional optimizer
option, or a different object setting. A near-match is not proof of an
exception and is not included in the ten successes.

There is **no positive evidence here for differing game-object flags**:
one default explains ten bodies across both executable images, with
version-sensitive examples in each. SDK O1 is a separately established
library configuration, not a game-object exception. Sampling 1,064 matched
bytes cannot establish every game object or rule out local exceptions;
retain per-object flexibility and expand probes when a larger reconstruction
resists the recommended default. Compiler mismatch conclusions apply to the
plausible supplied C and tested candidates, rather than all possible source
programs or untested optimizer switches.
