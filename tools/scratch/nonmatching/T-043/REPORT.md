# T-043 — sol-B15: ovl_7DF8 rodata ownership

Partial result: rodata ownership is implemented for all three owning TUs; two
functions are matched C. The two glyph conversions remain GLOBAL_ASM because
of instruction differences, rather than rodata ownership. No commits were made.

| Function | Owning TU | Bytes | Result |
|---|---|---:|---|
| func_801ADCFC | ovl_7DF8.c | 220 | Matched C; T-034 draft deleted |
| func_801CBCCC | ovl_7DF8_200C0.c | 516 | Matched C; T-034 draft deleted |
| func_801BF720 | ovl_7DF8_12C70.c | 104 | Still asm; C draft differs at +0x1C and +0x64 |
| func_801BF914 | ovl_7DF8_12C70.c | 116 | Still asm; C draft differs at +0x68 and +0x70 |

The original BF720 default loads 32 into v1, then moves v1 into v0 in the
return delay slot. C loads v0 directly, then has a nop in that delay slot.
BF914 has the corresponding difference for 27. With both drafts installed,
the entire overlay had exactly eight differing bytes, all in these four
instruction words. All rodata bytes and both other target functions already
matched. The drafts were restored to asm to retain a matching final build.
Their comments now describe the remaining blocker accurately.

## Reusable rodata ownership recipe

1. Locate the complete original TU's rodata, including preceding constants and
   assembly-function tables, through symbol references and the original image.
   Use `[offset, .rodata, original_c_subsegment_name]` in splat. The leading dot
   and matching name pair the range to the existing C object and enable splat's
   normal migration of rodata into GLOBAL_ASM function files.
2. Preserve complete TU alignment. IDO pads .rodata to 16 bytes. Moving only an
   individual table at an unaligned address gives the wrong layout. Here the
   first TU includes the preceding func_801ABB20 table; the glyph TU includes
   func_801BF190's preceding double; the save TU includes its regular strings
   before its late jump table. No artificial C padding is needed.
3. Compile the switch normally: IDO emits its own jump table, and asm-processor
   combines it with the migrated assembly functions' rodata in original order.
   No hand-written table of C label addresses, inline asm, or register binding
   is used. The ABB20 table remains assembly-defined in ABB20's generated .s,
   and BF190's double remains assembly-defined in BF190's .s. The two retained
   glyph asm functions similarly keep their migrated tables in their own .s.
4. For existing C functions whose strings migrate out of the original data
   assembly, supply matching C definitions at their original declaration
   positions. This change defines const u8 arrays D_80295648, D_80295698 and
   D_802956A8 using their exact original string literals. Their existing users'
   function bodies are unchanged.
5. Keep unrelated ranges asm-owned. Here they remain `type: data`, with
   `linker_section_order: .rodata` to interleave their existing .data input
   sections between the C .rodata input sections in address order. Changing
   them to `type: rodata` instead causes splat to emit jump table references to
   local .L labels in other objects, which cannot link. The preserved data
   disassembly retains the original numeric table words and symbol references.
6. The Makefile previously linked exactly one data assembly object per image.
   Its single generic object-list change collects generated assembly files in
   each image's data directory, allowing the two additional data fragments to
   link without overlay-specific object names. Extract before building, as in
   the requested workflow; clean after changing the split to remove stale
   generated assembly files.

| Image offsets (end exclusive) | Ownership |
|---|---|
| 0x21930–0xE6C90 | Original data assembly |
| 0xE6C90–0xE6CC0 | ovl_7DF8.c .rodata |
| 0xE6CC0–0xE70D0 | Assembly data fragment remaining_0 |
| 0xE70D0–0xE7160 | ovl_7DF8_12C70.c .rodata |
| 0xE7160–0xE9A40 | Assembly data fragment remaining_1 |
| 0xE9A40–0xE9BD0 | ovl_7DF8_200C0.c .rodata |

## Attempts and caveats

The standalone probes used the production IDO 5.3 -O2 -mips2 flags and compared
ELF function bodies while masking only actual relocation fields. Local scalar
widths, input signedness, early-return structure, explicit/default placement,
case assignment versus direct returns, and common return labels were tried.
`sweep.py` retains the broader switch-control-flow experiment (768 candidates
per function); none matched. Standalone counts do not prove linked matching;
the linked image comparison established the exact remaining differences above.

No T-044 function bodies, other images' source, status overrides, tracking
files, or worklog entries were edited. Generated progress files are restored
after recording final results, since they are outside this task's allowed scope.
Local prerequisites are symlinks to the main checkout; ROM contents were never
copied into source control.

## Final validation

`make clean && make extract && make all && make progress` passed. The ROM
SHA1 is `ba52e91b44450c548467044b26951353dc491e04`; main, ovl_7DF8, and
ovl_7E00 each printed OK. The ovl_7DF8 SHA1 remains
`ea830aae50ff1422da60d4b7fdbfc29f03b1be39`. T4 increases by two functions and
736 bytes. `git diff --check` passed.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 39,244 (12.30%) | 39,244 (12.30%) | 0 | 358 | 0 | 204 | 437 (138,092) |
| boot | 8,468 | 2,812 (33.21%) | 2,812 (33.21%) | 0 | 6 | 0 | 15 | 99 (16,028) |
| main | 173,204 | 24,416 (14.10%) | 24,416 (14.10%) | 0 | 180 | 0 | 110 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 12,016 (8.74%) | 12,016 (8.74%) | 0 | 172 | 0 | 79 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
