# T-016 / FU-9: ovl_7E00 code provenance

The overlay looks like a wholesale handwritten assembly module, with a custom
register convention and shared code entries, rather than an IDO C overlay
containing a few assembly accelerators. This is a provenance assessment, not
proof of the original source language for every byte. Seven compatible leaf
bodies remain uncertain; no function is positively identified as IDO C.

Inventory result (US V1.0, 2026-10-18):

- `handwritten_asm`: **162 entries, 87,228 bytes** (161 high confidence,
  one medium confidence).
- `ido_c`: **0 entries, 0 bytes**.
- `uncertain`: **7 entries, 444 bytes**, low confidence in provenance.

The 169 entries total 87,672 bytes. Separately, the 31 explicit inline data
pools total 4,040 bytes. Together these cover the complete 91,712-byte text
range, `801AD900–801C3F40`. Counts use the existing functions.csv partitions;
several entries are labels, delay slots, or shared tails rather than independent
ABI functions. They must not be treated as 169 separately callable C routines.
No status or exclusion changes are applied by this task.

## Per-entry evidence and reproduction

[The CSV](../tools/analysis/data/ovl_7E00_asm.csv) lists every inventory address,
byte count, class, confidence, and concrete local evidence. Addresses in evidence
refer to original CPU instructions. All code was decoded from the decompressed
ROM bytes with big-endian R4300 binutils, independently of mutable `asm/` output.
Inputs were docs/TRACKING.md (FU-9), docs/compiler_flags.md, docs/segments.md,
symbol_addrs.ovl_7E00.us.txt, and docs/functions.csv.

Reproduce from the repository root:

```sh
python3 tools/analysis/extract_segments.py baserom.us.z64
python3 tools/analysis/ovl_7E00_classify.py
```

The script writes only its owned CSV; extraction writes the existing generated
build/segments outputs. It never writes a ROM. The overlay binary SHA256 is
`d1d2f2692dd066e37bb22332a0e5bf3661b9aced31ccf92d403d563be3166f4d`.
The classifier is a reproducible inventory with explicitly reviewed exceptions,
not a general-purpose compiler detector. No external research was needed.

## Strongest evidence

The entry saves essentially the whole integer register file into a 128-byte
frame: `ra` at `sp+0` (801AD964), `$at` at `sp+4`, `$k0/$k1` at
`sp+104/+108`, and even `sp` at `sp+116`. It manipulates CP0 Status at
801AD9E4–801AD9F0. This is a custom assembly boundary, unrelated to an ordinary
IDO o32 C prologue (ra near the top of the frame with an outgoing argument
area). Alignment alone does not make its frame compiler-generated.

Throughout the overlay, `$s8` is a persistent object/context pointer and
callee-saved registers are scratch without local preservation. For example,
801B03E0 writes through `$s8`; 801BC55C shifts `$s0` without saving/restoring
it. `$k0/$k1` occur in game bodies, not merely the entry register save.
Tiny helpers consume and return values outside a0–a3/v0–v1: 801B9B20 consumes
`t4/t5`, divides into `t7`, and returns without a C ABI result move or IDO's
usual divide checks. 801C247C consumes coordinates in `v0/v1/a0/a1` and returns
several results in floating registers, including integer conversions left in
FPRs. These are deliberate custom interfaces.

Calls often push eight bytes, save `ra` at zero, and preserve selected volatile
registers manually. 801BC5A0 instead copies `ra` to `t3` around a `jal` and falls
into the next inventory body. 801BA4C4/801BA4C8 reload `ra` from a global after
a call. Such whole-module agreements explain frameless calls; treating them
as ordinary ABI functions would incorrectly infer broken code.

Control flow crosses inventory boundaries into interiors. Examples include
801BCF70 → 801BCF9C and 801C0F38 → 801C0F8C. Entries 801B2750 and 801B2794
are themselves delay slots of preceding jumps. Several 4-byte entries merely
set an alternate-entry argument and fall through. The report classifies these
existing partitions without changing symbol boundaries.

The 31 data pools span the module, rather than forming a single isolated
assembly island. Some deliberately overlap instruction bytes: lookup bases
801B6097, 801BF87B, 801BF987, and 801C21FA include bytes from the preceding
delay slot. This byte packing is particularly strong evidence of assembly
layout control. The symbol file documents the individual pools and consumers.
Pool adjacency alone is not used to declare an otherwise compatible leaf
handwritten; explicit per-entry evidence is required.

## Ambiguous leaves and confidence limits

The seven uncertain entries are:

- `801ADD20`, 276 bytes: global byte reads, clamps and stores, ordinary leaf
  return. Register selection differs from the verified IDO probes, but this is
  insufficient to exclude C.
- `801AF2E8`, 64 bytes: two global-byte tests/updates, compatible leaf return.
- `801B6858`, 60 bytes: global clamp with branch-likely scheduling; compatible
  with compiler output. Branch-likely is not intrinsically assembly evidence.
- `801BABFC`, `801BAC04`, `801BB8AC`, 8 bytes each: `jr ra; nop`. Empty C
  functions and handwritten return stubs are indistinguishable here.
- `801C2508`, 20 bytes: stores a0/a1 to globals and returns; ordinary ABI
  argument registers and address materialization cannot establish provenance.

No complete C reconstruction was matched for these leaves. In particular,
`lui at` addressing, comparison results in `at`, aligned frames, and `jr ra`
are compatible with both assembly and IDO. They are not positive IDO evidence.
The CSV's low confidence means the origin is unresolved, not that the bytes or
bounds are uncertain.

One assembly classification is medium confidence: `801BAEC0` (96 bytes) uses
`mult` by a loaded constant five at 801BAED0. A scratch probe compiled with
IDO 5.3 `-O2 -mips2 -G 0 -non_shared -Wab,-r4300_mul -Xcpluscomm`:

```c
int mul5(unsigned char x) { return x * 5; }
```

emits `andi t6,a0,255; sll v0,t6,2; addu v0,v0,t6; jr ra` (argument spill in
the delay slot). This supports the assembly interpretation in context, but is
not a full-function match or proof against every source expression, flag, or
compiler version. Retain this row for explicit lead review if exclusions must
be based only on hard ABI violations.

## Recommendation

Keep this overlay as a cohesive assembly module for matching, preserving the
inline pools, custom interfaces, alternate entries, and cross-label branches.
The lead can exclude the 161 high-confidence entries from C decompilation
work now, review 801BAEC0 separately, and leave the seven leaves unresolved
(or retain them as assembly for the module build without claiming proven
handwritten provenance). There is no evidence here requiring a mixed C/asm
module, although the compatible leaves prevent proving wholesale assembly
source with certainty. Semantic identification as an engine/renderer remains
a hypothesis; instruction provenance does not establish the module's name.
