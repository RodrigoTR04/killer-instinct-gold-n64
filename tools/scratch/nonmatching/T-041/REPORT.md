# T-041: seven uncertain ovl_7E00 leaves

Result: **0 integrated matches; 4 exact instruction bodies blocked by per-TU
padding; 2 further leaves blocked by slot size and instruction differences;
1 layout-compatible leaf still nonmatching.** All seven remain assembly in
the build. The scratch C files are drafts, not behavior-validated replacements.
No status.csv, boot, main, ovl_7DF8, ROM inputs, or tracked build configuration
changes are retained. No commit was made.

## Per-function results

| Function | Original slot | Draft body / TU `.text` | Result |
|---|---:|---:|---|
| `801ADD20` | 276 B | 260 / 272 B | Not matched; [draft](func_801ADD20.c). Global-byte reads, index/row clamps, signed adjustment clamp, result clamp and conditional pointer selection reconstructed. Different registers, hoisted address setup, shared global base, and pointer-selection branches: 64 of 68 overlapping words differ, and the draft TU is 4 B shorter. Even an exact 276 B body would emit 288 B, exceeding the slot by 12 B. |
| `801AF2E8` | 64 B | 60 / 64 B | Not matched; [draft](func_801AF2E8.c). Copies the low byte into the high byte of a big-endian halfword (clearing the low byte), then decrements the high byte when nonzero. Size fits, but 15 of 16 words differ: original reuses `a2` for every load/shift/decrement, uses independent HI/LO global accesses and empty branch delay slots; IDO uses `v0/v1/t6/t7`, materializes a shared base, schedules arithmetic in delay slots, and returns 4 B earlier. |
| `801B6858` | 60 B | 60 / 64 B | Not matched; [draft](func_801B6858.c). Signed clamp to `[-0x20000, 0x20000]`. Body length agrees, but 14 of 15 words differ. IDO uses a shared address base, `v0` for the value and a comparison against `0x20001`; original loads the bound into `v1`, compares it to `a0`, and reuses that bound register for the lower clamp. Four padding bytes exceed the slot. |
| `801BABFC` | 8 B | 8 / 16 B | Exact `jr ra; nop` body; [draft](func_801BABFC.c). Not integratable: 8 padding bytes overwrite the next stub at `801BAC04`. |
| `801BAC04` | 8 B | 8 / 16 B | Exact `jr ra; nop` body; [draft](func_801BAC04.c). Not integratable: 8 padding bytes extend into the inline data pool beginning at `801BAC0C` (offset `0xD30C`). Those pool bytes happen to be zero, but keeping the existing data subsegment intact would duplicate them and move the following bytes. |
| `801BB8AC` | 8 B | 8 / 16 B | Exact `jr ra; nop` body; [draft](func_801BB8AC.c). Not integratable: 8 padding bytes overwrite the first two instructions of `801BB8B4`. |
| `801C2508` | 20 B | 20 / 32 B | All five instructions match after relocation; [draft](func_801C2508.c). Stores `a0/a1` into `D_801D9ED4/D_801D9ED8`. Not integratable: 12 padding bytes overwrite the beginning of `801C251C`. |

Word counts above are positional comparisons after linking each draft at its
original address and resolving globals to their original VRAM addresses. They
are not edit-distance scores. Full original/draft disassembly, padding and
mismatch offsets are in [comparison.txt](comparison.txt).

## Experiments and integration

Read README.md, docs/TRACKING.md, docs/ovl_7E00_asm.md, docs/toolchain.md,
Makefile and overlay configuration before implementing. This fresh worktree
had no local tools or ROM link, so reused the existing installed toolchain via
ignored local links and linked the existing local baserom; no ROM was copied.

Temporarily inserted seven separate `c` subsegments with a dedicated source
file for each function. Splits used offsets `0x420–0x534`, `0x19E8–0x1A28`,
`0x8F58–0x8F94`, `0xD2FC–0xD304`, `0xD304–0xD30C`, `0xDFAC–0xDFB4`, and
`0x14C08–0x14C1C`. Resumed assembly scans used the existing
`.text.pXXXXX` / `linker_section_order: .text` convention; the inline data
subsegments were unchanged. Splat accepted all seven splits, and all seven
C objects compiled through the normal asm-processor rule. A temporary generic
addition to the ovl_7E00 object list included its C files beside its assembly
object. Both YAML and Makefile were restored exactly after the unsuccessful
trials; the temporary `src/ovl_7E00` files were removed.

All probes used IDO 5.3 with the existing flags:
`-c -G 0 -non_shared -Xcpluscomm -Wab,-r4300_mul -O2 -mips2 -32`.
No inline assembly, register binding, fake arguments, section truncation,
compiler flag exceptions or padding removal was used.

For `801AF2E8`, also tested a two-byte array representation, separate byte
symbols, signed/unsigned 32-bit and byte temporaries, and volatile byte reads.
The array variant emitted 48 B (shared base and scheduled arithmetic); scalar
variants emitted 64 B but kept different register allocation and scheduling.
The retained nonvolatile signed-scalar draft fits the original slot but does
not match. Volatile experiments did not match and were discarded.

The layout conclusions use the overlay's existing `SUBALIGN(4)`: forcing a
16-byte function start is not the issue. IDO emits a `.text` section whose
*size* rounds up to 16 bytes, even when the linker places it at a word-aligned
address. Six original slots are not multiples of 16. None can be replaced by
an independent exact C TU while retaining the immediately following assembly
or inline data. This is evidence for retaining assembly under the requested
separate-file constraint, **not proof that the original bodies were handwritten**.
In particular, four bodies are indistinguishable from IDO C. The seventh
leaf's register/scheduling mismatch also does not prove assembly provenance.
Do not automatically reclassify the seven entries as proven handwritten asm.

## Reproduction and validation

After `make extract`, reproduce the isolated compilations and comparisons:

```sh
.venv/bin/python tools/scratch/nonmatching/T-041/compare.py
# Add --write-evidence to regenerate comparison.txt.
```

The script compiles each draft through asm-processor, links only its text at
the original VRAM using `SUBALIGN(4)`, resolves `D_XXXXXXXX` symbols, and compares
against the existing decompressed overlay. It uses a temporary directory and
does not retain binary ROM excerpts.

Final validation completed successfully:

```sh
make clean && make extract && make -j4 all
make progress
.venv/bin/python tools/scratch/nonmatching/T-041/compare.py
```

The build printed `OK: rebuilt ROM is byte-identical to baserom.us.z64`;
SHA1 of both outputs was `ba52e91b44450c548467044b26951353dc491e04`.
All three decompressed executable images also passed `verify-images`.
The final scratch comparison reproduced the table above. Progress remained
unchanged because no C replacement was integrated.
