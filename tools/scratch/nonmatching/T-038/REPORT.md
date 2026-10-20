# T-038 boot C infrastructure and matching

Worktree: `/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-fd99607d`.
No commits made. No ROMs, headers, symbol files, status.csv, other source areas,
or lead-checkout files changed.

## Infrastructure

- `kig.us.yaml`: entry remains `hasm` at ROM 0x1000–0x1050; boot text is
  split into 51 C translation units. Forty-nine inter-unit boundaries satisfy
  the documented 1–3-zero-word alignment criterion. The separate SDK boundary
  before handwritten bzero follows a 64-byte zero gap. See `boundaries.md` for
  every offset and preceding function. Source provenance remains provisional.
- `Makefile`: discovers every `src/boot/*.c` with the same wildcard/patsubst
  pattern as main, uses the existing generic asm-processor C rule, and tracks
  the generated `boot_entry.s` in extraction. Target-specific `CFLAGS` still
  apply through that rule. Main and overlay rules are unchanged.
- Entry and all 98 SDK functions stay assembly (entry `hasm`, SDK
  `GLOBAL_ASM`). All 99 excluded functions retain excluded status. Boot data
  and BSS remain in their original assembly objects; C only declares externs.
- `tools/progress/inventory.py`: add whole-symbol boundaries to the assembly
  inclusion test. Previously a `boot_dma_chunked.s` stub suppressed credit for
  the distinct `boot_dma` C definition. The existing recursive source scan and
  boot linker-ownership check need no changes. No diff-config change was needed.
- `probe.py` and `probe-results.json` reproduce the six remaining drafts across
  IDO 5.3 O1/O2 × mips1/mips2/mips3. The comparator masks emitted relocations;
  its word counts compare overlapping offsets and report lengths separately.
  Only the complete linked checks establish matching status.

The infrastructure-only clean extraction, build and progress check passed before
matching, with total T4=164 and boot T4=0 (recorded in /tmp/t038-infra2.log).
All 21 eligible functions were attempted, starting with smaller candidates.

## Results

All shipped boot C uses the default flags:
`-c -G 0 -non_shared -Xcpluscomm -Wab,-r4300_mul -O2 -mips2 -32`.
No boot object override was needed. All six remaining drafts were also compiled
with O1/mips2, O1/mips1, O2/mips1, O2/mips3 and O1/mips3; none matched.
Draft rows below report the default configuration. No functions were left
unattempted. Only the six unmatched drafts remain in this directory.

| Function | Result | Flags used for result |
|---|---|---|
| `func_80000450` | MATCHED | IDO 5.3 `-O2 -mips2` |
| `func_800004AC` | MATCHED | IDO 5.3 `-O2 -mips2` |
| `func_80000520` | MATCHED | IDO 5.3 `-O2 -mips2` |
| `func_800005EC` | MATCHED | IDO 5.3 `-O2 -mips2` |
| `func_800006B0` | MATCHED | IDO 5.3 `-O2 -mips2` |
| `func_800006FC` | MATCHED | IDO 5.3 `-O2 -mips2` |
| `boot_dma` | MATCHED | IDO 5.3 `-O2 -mips2` |
| `boot_dma_chunked` | DRAFT: 36 differing overlapping words; 328 / 328 B | IDO 5.3 `-O2 -mips2` |
| `boot_inflate` | MATCHED | IDO 5.3 `-O2 -mips2` |
| `func_80000960` | DRAFT: 398 differing overlapping words; 2176 / 1600 B | IDO 5.3 `-O2 -mips2` |
| `func_80000FA0` | DRAFT: 283 differing overlapping words; 1260 / 1136 B | IDO 5.3 `-O2 -mips2` |
| `func_80001410` | MATCHED | IDO 5.3 `-O2 -mips2` |
| `func_80001564` | DRAFT: 8 differing overlapping words; 360 / 360 B | IDO 5.3 `-O2 -mips2` |
| `func_800016CC` | DRAFT: 328 differing overlapping words; 1468 / 1316 B | IDO 5.3 `-O2 -mips2` |
| `func_80001BF0` | MATCHED | IDO 5.3 `-O2 -mips2` |
| `func_80001D10` | MATCHED | IDO 5.3 `-O2 -mips2` |
| `func_80001DF0` | MATCHED | IDO 5.3 `-O2 -mips2` |
| `func_80001EF4` | MATCHED | IDO 5.3 `-O2 -mips2` |
| `func_80001F2C` | DRAFT: 209 differing overlapping words; 880 / 916 B | IDO 5.3 `-O2 -mips2` |
| `func_800022C0` | MATCHED | IDO 5.3 `-O2 -mips2` |
| `func_80002420` | MATCHED | IDO 5.3 `-O2 -mips2` |

`func_80001564` is equal-sized and differs only in the store offsets/order in
its two unrolled fill loops. Index/pointer loop spellings, signedness, and
explicit batching did not resolve it. `boot_dma_chunked` has the same size and
instruction structure but different saved-register allocation. The larger
Huffman drafts still need corrected types, stack layout and control-flow work;
the scheduler draft retains m2c control flow and differs in size and registers.
Their `GLOBAL_ASM` lines remain in the built source.

The matched implementations use ordinary C without register binding or encoded
instructions. One unusual ABI detail is explicit: the boot caller passes the
DP byte count in a2/a3, represented by a u64 second parameter for
`osDpSetNextBuffer`. Bit-buffer routines preserve unsigned shift/count types;
DMA argument signedness and SDK void return declarations affect IDO scheduling.

## Final validation

Passed `make clean && make extract && make && make progress` after the final
progress-tool fix. ROM SHA1: `ba52e91b44450c548467044b26951353dc491e04`.
Main, ovl_7DF8 and ovl_7E00 all verified byte-identical as well. `git diff --check`
passed. Total T4 rises from 164 to 179; boot contributes 15 functions / 2,812 B.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,544 | 27,420 (8.58%) | 27,420 (8.58%) | 40 | 350 | 0 | 179 | 430 (137,648) |
| boot | 8,468 | 2,812 (33.21%) | 2,812 (33.21%) | 6 | 0 | 0 | 15 | 99 (16,028) |
| main | 173,204 | 14,300 (8.26%) | 14,300 (8.26%) | 27 | 172 | 0 | 91 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 10,308 (7.50%) | 10,308 (7.50%) | 0 | 178 | 0 | 73 | 0 (0) |
| ovl_7E00 | 444 | 0 (0.00%) | 0 (0.00%) | 7 | 0 | 0 | 0 | 162 (87,228) |

After recording these results, restored `docs/functions.csv` and
`docs/progress.html` as requested. Setup symlinks `.venv`, `ROMs`, `tools/ext`
remain local/untracked and must not be included in the lead's commit.

Reproduce draft diagnostics:

```sh
.venv/bin/python tools/scratch/nonmatching/T-038/probe.py
```
