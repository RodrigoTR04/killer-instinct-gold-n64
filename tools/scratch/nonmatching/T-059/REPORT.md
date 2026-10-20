# T-059 — sol-C22: main mid-size draft polish

**0 MATCHED, 5 IMPROVED drafts, 7 UNCHANGED.** All twelve requested functions
received bounded structural/type/control-flow experiments. No commits were
made. Production C, ownership hints, YAML, Makefile, status.csv, boot and
overlay sources are untouched. Five original draft files are updated in place.

## Results

Counts use standalone IDO 5.3 production `-O2 -mips2` flags, comparing
corresponding emitted instruction words while masking only real ELF
relocations. They are diagnostic positional counts, not edit distance or
linked matches. Sizes accompany the counts because shortened code can make
this metric misleading. Baselines reproduce T-054 exactly.

| Function | Result | Emitted/original B | Effort and remaining blocker |
|---|---|---:|---|
| func_8001E0B4 | **IMPROVED 59→26** | 648/648 | Original +0x1A8 is `lh`, not `lbu`: corrected the kind field to s16 with byte-based record addressing. Removed the redundant u16 cast after signed half-scale division: inputs come from lhu or 0x1000, so the quotient already fits. Original has signed division rounding and no post-division mask. Tried signed scale locals, mirror boolean/local, typed Gfx command and actor-loop forms. Remaining 26 differences concern setup registers/scheduling and branch delay slots. |
| func_80018F20 | **IMPROVED 91→90** | 696/696 | Color byte stores now use u8, including the original 0x80 values. Typed stage records, byte-table views, explicit order cursor, store signedness and half-scale expression were tested. Changing all order stores to unsigned scores 77 but grows to 704 B; rejected. Remaining constant reuse and setup/callback scheduling differences. |
| func_80024714 | UNCHANGED (94) | 712/712 | Replaced giant padded resource structure with two-player address-slot arrays and flat pointer arrays; also tried direct slot addresses and direct dispatch. Typed arrays retain 94; direct slot addresses worsen to 100. Remaining address setup/register allocation. |
| func_80030440 | UNCHANGED (122) | 488/632 | Tested row cursor, source byte offset, run countdown/equality termination, direct output expression and counter widths. Row cursor scores 89 but shrinks to 364 B, losing more of the original loop/unroll shape; not retained as an improvement. Equality termination emits 616 B but scores 150. Remaining nested-loop unrolling/control flow. |
| func_8002A4F0 | **IMPROVED 129→65** | 920/920 | Typed sequence-entry cursor with a fixed 48-entry end pointer replaces indexed source loads. Destination indexing still advances consistently with the source. Also tried shared config assignment, pointer/counter/do loops, source/destination cursors and length types. Remaining stack layout/config-store order and sequence-loop register/control flow. |
| func_800170C4 | UNCHANGED (134) | 696/692 | Tried pointer/equality vertex loops, explicit groups of two/four aggregate copies and indexed object traversal. Pointer form grows to 736 B/149; explicit groups inhibit the original compiler shape further. Remaining aggregate-copy loop setup/unrolling and allocation. |
| func_8001BB64 | **IMPROVED 144→143** | 592/636 | Packed environment color now ORs blue, red, green in the original expression order. Tested indexed color loop, channel widths, dispatch width and end-symbol sentinel. Widening colors scores 141 but shortens the already undersized body; original loads/stores explicitly use signed halfwords, so retained that representation. Remaining loop and switch/register allocation. |
| func_800241BC | UNCHANGED (161) | 840/820 | Tried two-player resource-slot arrays, flat pointer arrays, direct slot bases and direct dispatch. Arrays emit the same code; direct bases worsen to 166. Remaining DMA/resource pointer lifetime and scheduling differences. |
| func_800131A4 | UNCHANGED (169) | 676/712 | Tried cursor-store order, narrow counters, table cursor and cached draw count. Cached count scores 164 but changes reload behavior across callbacks, so rejected. Remaining callback ABI and loop/control-flow shape. |
| func_8001D47C | **IMPROVED 179→141** | 748/748 | Palette loops now use a byte displacement 0..30 with 2-byte steps, matching the original byte counter. Tested destination/source cursors, pixel widths and selector ABI. Original genuinely starts the output cursor at address zero; retained that existing hardware-address behavior, confirmed by original `move t0,zero` and halfword stores. Remaining unrolled grayscale division and registers. |
| func_800253D0 | UNCHANGED (180) | 1044/1068 | Tried shared command cursor, explicit cursor advancement, value-first command stores and full-width HUD call ABI. Shared cursor worsens to 206; wider ABI 194. Remaining call/register scheduling and HUD command shape. |
| func_8001AD04 | UNCHANGED (194) | 1088/1072 | Tried direct indexed depth, scoped/short indices, shared rotation pointer, literal pool and unsigned indices. Changing only a saved index to u32 scores 144, but making the full transform-index representation consistently unsigned returns 194; no convincing layout/type basis for retaining the isolated score reduction. Literal pool leaves body metric unchanged. Remaining floating-point pointer lifetimes/register scheduling. |

Deleted drafts: **none**. No function was promoted and no function-owner
hint needed removal or reassignment. Regenerated undefined-symbol files
have no final diff; their generated results were kept.

## Diagnostics

`*-base.c` preserves each original baseline. `probe.py` performs the standalone
comparison; `refine.py`, `focused.py`, `near.py`, `scale.py`, `loops.py`,
`final_pass.py`, `audio.py`, `floats.py`, and `index.py` record successive
bounded experiments. JSON diagnostics retain failed compiles, counts, sizes
and differing offsets. Selected candidate C files retain the improvements
and notable rejected forms; scripts regenerate other probe files if needed.
`retained.json` and `retain.py` identify the five installed choices.
Some probes deliberately test alternate signedness or alias/reload assumptions;
those diagnostic forms are not automatically suitable for production. No
inline assembly, register variables or build transformations were used.

## Clean validation

`make clean && make extract && make -j8 all && make progress` passed.
The ROM and all three executable images are byte-identical:

- ROM: `ba52e91b44450c548467044b26951353dc491e04`
- main: `81736d32e8cda8f399b319a49250dff972b81af8`
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`

`git diff --check` passed. Prerequisites were missing and were symlinked to
`/home/rodri/Projects/killer-instinct-gold-n64` as authorized. No ROM was
copied or committed. No production source was changed, so progress is unchanged.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 54,584 (17.11%) | 54,584 (17.11%) | 0 | 305 | 0 | 257 | 437 (138,092) |
| boot | 8,468 | 8,108 (95.75%) | 8,108 (95.75%) | 0 | 1 | 0 | 20 | 99 (16,028) |
| main | 173,204 | 31,772 (18.34%) | 31,772 (18.34%) | 0 | 145 | 0 | 145 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 14,704 (10.70%) | 14,704 (10.70%) | 0 | 159 | 0 | 92 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
