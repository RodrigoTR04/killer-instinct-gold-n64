# T-042 boot polish — sol-A17

Five functions matched (5,296 bytes). One draft remains unchanged. No commits
made. Changes are limited to three boot C files and T-038/T-042 scratch files.
No Makefile, YAML, symbol, status.csv, main, or overlay edits were needed.

| Function | Result | Final differing words | C / target bytes |
|---|---|---:|---:|
| `func_80001564` | UNCHANGED | 8 | 360 / 360 |
| `boot_dma_chunked` | MATCHED | 0 | 328 / 328 |
| `func_80001F2C` | MATCHED | 0 | 916 / 916 |
| `func_80000FA0` | MATCHED | 0 | 1,136 / 1,136 |
| `func_800016CC` | MATCHED | 0 | 1,316 / 1,316 |
| `func_80000960` | MATCHED | 0 | 1,600 / 1,600 |

The five matched GLOBAL_ASM declarations were replaced by ordinary C, and their
T-038 drafts were deleted. All use the existing default IDO 5.3 flags:
`-O2 -mips2 -G 0 -non_shared -Xcpluscomm -Wab,-r4300_mul -32`.
No inline assembly, register bindings, register hints, or artificial padding.

## Matching details

- **DMA:** inverting the event check and continuing for events other than 1
  reproduces the target's saved-register allocation. Chunk sizes, argument
  order, queue operations, and pointer updates retain their original behavior.
- **Huffman builder:** the existing local gzip 1.2.4 `inflate.c` supplies the
  recognizable `huft_build` structure. Reconstructing it with real arrays,
  correctly scaled pointers, and an eight-byte `Huft` structure matches exactly.
  Its union stores either a 16-bit decoded value or a subtable pointer. The game
  allocates from `D_8000BF90 + D_8000BF9C`; it omits gzip's malloc and invalid-input
  error paths. Base-value tables are `u16[]`; extra-bit tables are `u8[]`.
- **Huffman decoder:** the same source structure matches after removing the
  absent invalid-code checks and sliding-window flushing/wrapping. The game
  copies directly into its output buffer; overlapping runs use the byte loop.
  The masks at `D_80006630` are `u16[]`, not the draft's scalar `s32` accesses.
- **Dynamic tables:** the array has 286 + 30 entries. Declaring the local bit
  count and bit buffer immediately before that array reproduces their spill
  slots at sp+0x534 and sp+0x530. Ordinary repeat loops replace the draft's
  incorrect pointer increments and reconstructed unrolling.
- **Scheduler:** use a complete event switch inside the receive loop, a 32-bit
  initial message storage slot, and an unsigned `osSpTaskYielded` return value.
  Remove redundant framebuffer temporaries and pass the assignment expression
  to `osViSwapBuffer`. Initialize the subscriber index and queue pointer in one
  comma expression to reproduce register assignment and instruction scheduling.
  Its unreachable epilogue has an IDO `.align 5`: a standalone function probe
  reports padding differences, while its complete owning TU matches 916 bytes.
- **Fixed tables (remaining):** the eight differences are store offsets at
  function-relative 0x18, 0x1C, 0x20, 0x28, 0xF0, 0xF4, 0xF8, and 0x100.
  Target unrolled stores visit offsets -12, -8, -4, -16; the draft visits -16,
  -12, -8, -4. Signed/unsigned indices and array elements, pre/post increment,
  for/while/do forms, pointer loops, countdown loops, and explicit batches did
  not improve the original draft. Its GLOBAL_ASM and original draft remain.

FU-2 was unnecessary: all five matches use existing data through externs. The
boot data/rodata ownership and `kig.us.yaml` remain unchanged.

## Reproduction and validation

`score.py` is a relocation-aware iteration aid using the existing flagprobe ELF
reader. Its outputs include both sizes, word counts, and exact differing offsets.
It writes temporary compilation files outside the repository. Examples:

```sh
.venv/bin/python tools/scratch/nonmatching/T-042/score.py src/boot/boot_29F0.c --function func_80001F2C
.venv/bin/python tools/scratch/nonmatching/T-042/score.py tools/scratch/nonmatching/T-038/func_80001564.c
```

Final validation: `make clean && make extract && make all && make progress`
(with `MAKEFLAGS=-j4`). The linked ROM reports
`OK: rebuilt ROM is byte-identical to baserom.us.z64`.
SHA1: `ba52e91b44450c548467044b26951353dc491e04`.
All three compressed images also verify byte-identical. `git diff --check`
passes. Lead-maintained status.csv is untouched; generated progress documents
are restored after recording the table below. Setup uses symlinks to the lead
checkout for the ROM, ROMs directory, virtualenv, and external tools; no ROM
content is committed or placed in a new tracked file.

## Final make progress

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 43,804 (13.73%) | 43,804 (13.73%) | 0 | 355 | 0 | 207 | 437 (138,092) |
| boot | 8,468 | 8,108 (95.75%) | 8,108 (95.75%) | 0 | 1 | 0 | 20 | 99 (16,028) |
| main | 173,204 | 24,416 (14.10%) | 24,416 (14.10%) | 0 | 180 | 0 | 110 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 11,280 (8.21%) | 11,280 (8.21%) | 0 | 174 | 0 | 77 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
