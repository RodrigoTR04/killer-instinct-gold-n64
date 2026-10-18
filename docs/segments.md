# T-004: decompressed segment map, US V1.0

Ranges are half-open. Cartridge offsets describe compressed storage; **splat
must consume each extracted binary**, with offsets starting at zero and the
VRAM below. This report builds on T-002 rather than repeating its boot analysis.

The 27 table entries contain **26 distinct payloads: 3 CPU executables and
23 data payloads**. Counting table entries gives 3 executable and 24 data entries
(11 byte-table and 13 packed-graphics entries). All destinations are resolved
at the loader level; the byte-table family has two alternative destinations.
Exact original ELF `.data`/`.rodata` ownership remains partly unresolved.
Conservative initialized-data splits below cover every byte without relying
on those hypotheses. This is a static analysis, not a runtime load trace.

**Correction to the supplied background:** ROM 0x7EC0 contains
`00BA40A0 00BB9F20`, identical to **0x7E90**, not 0x7E88. Extracted SHA1s
confirm this. The prior layout document is intentionally unchanged.

## Reproduce

```sh
python3 tools/analysis/extract_segments.py baserom.us.z64
python3 tools/analysis/segments.py baserom.us.z64 > build/segments/map.json
```

Both tools use only the standard library, verify the known US V1.0 SHA1,
and open the ROM read-only. The extractor preserves all 27 table entries,
including the duplicate, writes binaries and a manifest with exact size/SHA1,
and checks DEFLATE EOF. `stream_end` excludes trailing alignment bytes.
`segments.py` prints JSON without writing files. JSON addresses are integers;
`vram` is a list only where the loader offers two slots. `loaded_by` records
DMA/inflate call instruction addresses; `loader_called_by` records callers of
the indexed loader. Empty BSS on data entries means not applicable.

## Complete table

Names correspond to extraction filenames. B = byte-table data, G = packed
graphics data, C = CPU executable. B entries can use either listed slot;
this is not evidence that every possible pair of indices occurs in play.

| Table | Name | ROM | Size | Kind | Load VRAM |
|---|---|---|---|---|---|
| 7DF0 | main | A94D80–AB5800 | 3A8D0 | C | 8000F960 |
| 7DF8 | ovl_7DF8 | AB5810–B00EB0 | E9BD0 | C | 801ABB20 |
| 7E00 | ovl_7E00 | B00EB0–B14BA0 | 25930 | C | 801AD900 |
| 7E08 | ovl_7E08 | B14BA0–B184E0 | 8BB0 | B | 801DB000 / 801E5000 |
| 7E10 | ovl_7E10 | B184E0–B1B780 | 7A20 | B | 801DB000 / 801E5000 |
| 7E18 | ovl_7E18 | B1B780–B1E400 | 6C40 | B | 801DB000 / 801E5000 |
| 7E20 | ovl_7E20 | B1E400–B21630 | 79E0 | B | 801DB000 / 801E5000 |
| 7E28 | ovl_7E28 | B21630–B24490 | 7300 | B | 801DB000 / 801E5000 |
| 7E30 | ovl_7E30 | B24490–B273A0 | 7600 | B | 801DB000 / 801E5000 |
| 7E38 | ovl_7E38 | B273A0–B2A7F0 | 80A0 | B | 801DB000 / 801E5000 |
| 7E40 | ovl_7E40 | B2A7F0–B2D7D0 | 72E0 | B | 801DB000 / 801E5000 |
| 7E48 | ovl_7E48 | B2D7D0–B309D0 | 7BD0 | B | 801DB000 / 801E5000 |
| 7E50 | ovl_7E50 | B309D0–B339A0 | 7410 | B | 801DB000 / 801E5000 |
| 7E58 | ovl_7E58 | B339A0–B35AE0 | 4F70 | B | 801DB000 / 801E5000 |
| 7E60 | ovl_7E60 | B35AE0–B40760 | DA10 | G | 802D4000 |
| 7E68 | ovl_7E68 | B40760–B56180 | 1C340 | G | 802D4000 |
| 7E70 | ovl_7E70 | B56180–B6B450 | 1AF90 | G | 802D4000 |
| 7E78 | ovl_7E78 | B6B450–B80B00 | 1B2F0 | G | 802D4000 |
| 7E80 | ovl_7E80 | B80B00–B8AEE0 | D8D0 | G | 802D4000 |
| 7E88 | ovl_7E88 | B8AEE0–BA40A0 | 20250 | G | 802D4000 |
| 7E90 | ovl_7E90 | BA40A0–BB9F20 | 1C5E0 | G | 802D4000 |
| 7E98 | ovl_7E98 | BB9F20–BC90B0 | 14330 | G | 802D4000 |
| 7EA0 | ovl_7EA0 | BC90B0–BDE990 | 1DF30 | G | 802D4000 |
| 7EA8 | ovl_7EA8 | BDE990–BF2300 | 19820 | G | 802D4000 |
| 7EB0 | ovl_7EB0 | BF2300–BF9100 | 99B0 | G | 802D4000 |
| 7EB8 | ovl_7EB8 | BF9100–BFB020 | 20C0 | G | 802D4000 |
| 7EC0 | ovl_7EC0 | BA40A0–BB9F20 | 1C5E0 | G | 802D4000 |

## Verified loader evidence

Instruction addresses here are VRAM, not compressed ROM offsets. Instructions
in call delay slots execute before the call. The DMA ABI is `(ROM,dest,size)`;
the inflate ABI is `(compressed source,expanded dest,scratch)`.

### Main and the executable overlays

Main's bootstrap call sites 0x800005A8/0x800005C4 and indirect entry jump
0x800005D4 are already verified in T-002: table 0x7DF0 → 0x8000F960.

For 0x7DF8, main provides both ROM bounds and destination directly:

```text
800122A0 lui   v0,0x8000
800122A4 addiu v0,v0,0x71F0        # boot table address
800122A8 lw    a0,8(v0)           # table ROM 7DF8 start
800122AC lw    t9,12(v0)          # table ROM 7DF8 end
800122B0 lui   a1,0x802D
800122B4 ori   a1,a1,0x6000
800122B8 jal   800007B4
800122BC subu  a2,t9,a0
800122C0 lui   a0,0x802D
800122C4 lui   a1,0x801B
800122C8 lui   a2,0x802D
800122CC ori   a2,a2,0x4000
800122D0 addiu a1,a1,-0x44E0       # 801ABB20
800122D4 jal   80000900
800122D8 ori   a0,a0,0x6000
800122E0 jal   801ABB20           # executable entry, direct call
```

Its size 0xE9BD0 ends exactly at 0x802956F0, the entry's BSS start.
Main also invalidates I-cache 0x801ABB20–0x801CD450 at 0x80012280,
and D-cache 0x801CD450–0x802956F0 at 0x80012298. These independently
establish the intended text/data boundary.

For 0x7E00:

```text
8000FC38 lui   v0,0x8000
8000FC3C addiu v0,v0,0x71F0
8000FC40 lw    a0,0x10(v0)        # table ROM 7E00 start
8000FC44 lw    t7,0x14(v0)
8000FC48 lui   s0,0x802D
8000FC4C ori   s0,s0,0x4000
8000FC50 or    a1,s0,zero
8000FC54 jal   800007B4
8000FC58 subu  a2,t7,a0
8000FC5C lui   a1,0x801B
8000FC60 lui   a2,0x803A
8000FC64 ori   a2,a2,0x2000
8000FC68 addiu a1,a1,-0x2700       # 801AD900
8000FC6C jal   80000900
8000FC70 or    a0,s0,zero
8000FECC jal   801AD900           # later executable entry call
```

No function-pointer jump is needed to establish these overlays as executable:
both have direct entry calls. Their initialized ranges overlap and their BSS
and asset regions are reused: the two overlays are mutually exclusive as
complete images. The indexed data at 0x801DB000/0x801E5000 lies inside
0x7DF8's initialized range, another lifetime conflict. Graphics destination
0x802D4000 is also the staging buffer used when loading 0x7E00. Do not combine
these into a single continuously resident linker image.

### Entries 0x7E08–0x7E58: two indexed byte-table slots

Main's function 0x80012100 takes two byte indices in a0/a1. It uses boot table
address 0x80007208 = ROM 0x7E08, with stride eight. The first index loads at
0x801DB000, the second at 0x801E5000:

```text
80012100 andi  a3,a0,0xFF
80012104 lui   t7,0x8000
80012108 addiu t7,t7,0x7208
8001210C sll   t6,a3,3
80012114 addu  v0,t6,t7
8001211C lw    a0,0(v0)
80012120 lw    t8,4(v0)
8001212C lui   a1,0x802D
80012130 ori   a1,a1,0x4000
80012138 jal   800007B4
8001213C subu  a2,t8,a0
80012144 lui   a0,0x802D
80012148 lui   a1,0x801D
80012154 ori   a1,a1,0xB000
80012158 ori   a0,a0,0x4000
8001215C jal   80012338
...
80012164 lbu   t1,0x27(sp)         # saved second argument
80012168 lui   t3,0x8000
8001216C addiu t3,t3,0x7208
80012170 sll   t2,t1,3
80012174 addu  v0,t2,t3
80012178 lw    a0,0(v0)
8001217C lw    t4,4(v0)
8001218C jal   800007B4            # a1=802D4000
80012190 subu  a2,t4,a0
80012198 lui   a0,0x802D
8001219C lui   a1,0x801E
800121A8 ori   a1,a1,0x5000
800121AC ori   a0,a0,0x4000
800121B0 jal   80012338
800121B4 subu  a2,t5,t6
```

0x80012338 is a thin wrapper: at 0x80012344 it sets a2=0x803A0000,
then calls inflate at 0x80012348 with delay-slot `ori a2,a2,0x2000`.
Callers are main 0x8000FD28 and 0x80011B68, using the pair of byte indices
stored at 0x8004EA9E. Index 0–10 maps directly to the eleven table entries.
The buffers are 0xA000 apart, greater than every expanded size (max 0x8BB0).

Verified: these are non-CPU data, with byte runs and structured tables rather
than instruction streams. Hypothesis: character-specific tables (two player
slots); exact interpretation of the bytes is unresolved. No entry jump into
either slot was found. Do not classify these as executable overlays solely
because of the extraction name prefix.

### Entries 0x7E60–0x7EC0: indexed packed graphics

The loader at 0x80012A8C uses index a0, table base 0x80007260 (ROM 0x7E60),
and a thirteen-word destination array at 0x80044DF4. **Every array word is
0x802D4000**. Therefore every table entry's load address is resolved, including
the duplicate index 12.

```text
80012AC0 lbu   t6,0x1B(sp)         # saved index
80012AC4 lui   t8,0x8000
80012AC8 addiu t8,t8,0x7260
80012ACC sll   t7,t6,3
80012AD0 addu  v0,t7,t8
80012AD4 lw    a0,0(v0)
80012AD8 lw    t9,4(v0)
80012ADC lui   a1,0x8031
80012AE0 ori   a1,a1,0x3090
80012AE4 jal   80000740
80012AE8 subu  a2,t9,a0
80012AEC lbu   t0,0x1B(sp)
80012AF0 lui   a1,0x8004
80012AF8 sll   t1,t0,2
80012AFC addu  a1,a1,t1
80012B00 lui   a2,0x8031
80012B04 ori   a2,a2,0x1090
80012B08 lw    a1,0x4DF4(a1)       # 802D4000 for all 13 indices
80012B0C jal   80000900
80012B10 ori   a0,a0,0x3090        # a0's lui 8031 at 80012AF4
```

Main 0x8000FE14 and overlay 0x7DF8 at 0x801C228C/0x801C4EC8 call this
loader. The first two subsequently dispatch through callbacks in **main**'s
0x800451EC table (jalr at 0x8000FE34 / 0x801C22B4), rather than jumping into
the decompressed buffer. The thirteen destination ranges overlap completely
at their starts, so these graphics payloads are mutually exclusive.

Classification is high confidence packed graphics, **not raw aligned Gfx
arrays**: all start with a byte prefix and recognizable B7/E7/BA/B9/BB/FC
command sequences at varying alignments, followed by packed geometry/texture
bytes. For example 0x7E60 has `B7000000` at +1, `E7000000` at +0xA,
`BA001402` at +0x13 and `B900031D` at +0x1C. Hypothesis: stage graphics
(the shared index at 0x8004AC88 and stage-specific main callbacks support this).
No CPU entry pointers into the destination were identified. The command packet
format and exact stage-index names have not been decoded.

## CPU boundaries and BSS

| Image | CPU text offsets | Initialized non-CPU offsets | Cleared BSS VRAM |
|---|---|---|---|
| main | 0–32DB0 | 32DB0–3A8D0 (RSP + data) | 8004A230–80127C30; 80128350–801726D0 |
| ovl_7DF8 | 0–21930 | 21930–E9BD0 | 802956F0–802D3FF0 |
| ovl_7E00 | 0–16640 | 16640–25930 | 801D3230–801DA030 |

These text splits are suitable for conservative splat splits. For main use
binary subsegments for RSP code instead of CPU `asm` disassembly. For both
overlays keep initialized bytes as `data`/`bin` until finer ownership is known.
No BSS consumes bytes in the decompressed input file. Main's second BSS range
is discontinuous; do not silently fill its gap as BSS.

Main's final CPU routine returns at 0x80042700 with stack restoration in its
delay slot, followed by two zero words. At 0x80042710 RSP boot code begins.
T-002's statement that CPU code extends through 0x80042930 was a lower-bound
provisional interpretation: those later instructions actually belong to RSP.

```text
80042700 03E00008 jr    ra
80042704 27BD00A8 addiu sp,sp,0xA8
80042708 00000000 nop
8004270C 00000000 nop
80042710 34210001 ori   at,at,1
80042714 0900041A j     0x1068     # RSP IMEM address, not CPU 84001068
...
80042728 40870000 mtc0  a3,SP_MEM_ADDR
8004272C 40820800 mtc0  v0,SP_DRAM_ADDR
80042730 40831000 mtc0  v1,SP_RD_LEN
```

Main entry's BSS calls are at 0x8000F978 and 0x8000F98C, to bootstrap bzero
0x80002B80. First sets a0=0x8004A230 and a1=end-start with end=0x80127C30;
second sets a0=0x80128350 and a1=0x4A380. This agrees with T-002.

0x7DF8's final routine returns at 0x801CD440; its delay slot and alignment
zeros end at 0x801CD450, also the independently observed cache split:

```text
801CD43C 27BD0040 addiu sp,sp,0x40
801CD440 03E00008 jr    ra
801CD444 00000000 nop
801CD448 00000000 nop
801CD44C 00000000 nop
801CD450 00000000                 # start initialized data/cache split
801CD454 00000000                 # accessed mutable global
801CD460 E7000000 00000000        # graphics pipe sync, not CPU text
```

Its BSS is directly established by the entry:

```text
801ABB24 lui   a2,0x8029
801ABB28 lui   t6,0x802D
801ABB2C addiu a2,a2,0x56F0
801ABB30 addiu t6,t6,0x3FF0
801ABB34 subu  a1,t6,a2
801ABB60 blez  a1,801ABB70
801ABB68 jal   80002B80
801ABB6C or    a0,a2,zero
```

0x7E00 ends CPU text with `jr ra; nop` at 0x801C3F38/3F3C.
At 0x801C3F40 begins a pointer table to initialized words at
0x801C3F8C–3FA8 (values 80000000,81000000,…,87000000), followed by byte
lookup tables; this is demonstrably data. The I-cache invalidation end used
by main is 0x801C3FC0, which includes this first 0x80 data bytes; it is not a
reason to disassemble that data as CPU text. Initialized data continues to
0x801D3230, including packed scripts and embedded data pointers at its end.
The entry byte-clear loop is exact:

```text
801AD900 3C08801D lui   t0,0x801D
801AD904 3C09801E lui   t1,0x801E
801AD908 25083230 addiu t0,t0,0x3230
801AD90C 2529A030 addiu t1,t1,-0x5FD0  # 801DA030
801AD910 25080001 addiu t0,t0,1
801AD914 1509FFFE bne   t0,t1,801AD910
801AD918 A100FFFF sb    zero,-1(t0)
```

### Data versus rodata: verified contents, candidate section splits

There is no ELF section table in these payloads. Distinguish a proven CPU
text boundary from a hypothesized original `.rodata` start.

* **Main:** initialized CPU data starts at **0x80044A10** after the RSP text.
  A candidate `.data`/`.rodata` boundary is **0x80048760** (offset 0x38E00):
  immediately preceding words include math tables and `10,10,20,0`; following
  bytes are floating constants and ordered game-code switch tables.
  The region includes SDK constants and graphics display lists, so it is not
  purely compiler-generated rodata. In particular 0x800496D0–0x80049770 is a
  graphics setup display list, referenced at 0x8000FFD0.
* **0x7DF8:** `.data` starts at **0x801CD450**. Candidate rodata start
  **0x802927B0** (offset 0xE6C90): two ordered early-function switch tables,
  then floats and literal strings including copyright/menu text, character
  biographies, endings, credits, and controller-pak messages. Earlier bytes
  contain display lists, mutable globals, geometry, and pointer arrays.
  This boundary is plausible linker ordering, not independently proven.
* **0x7E00:** initialized data starts at **0x801C3F40**; a single separate
  `.rodata` start is **unresolved**. Its data intermixes lookup tables,
  function dispatch pointers, and packed scripts. Keep the entire range
  0x801C3F40–0x801D3230 together for an initial split.

Actual indirect dispatch establishes concrete read-only table contents:

```text
# Main switch table at 80048780, five targets 80011E80..80011F1C
80011E60 sltiu at,t9,5
80011E68 sll   t9,t9,2
80011E6C lui   at,0x8005
80011E70 addu  at,at,t9
80011E74 lw    t9,-0x7880(at)      # 80048780 + index*4
80011E78 jr    t9

# 7DF8 switch table at 802956C4, ten targets in CPU text
801CBD98 addiu t8,t7,-2
801CBD9C sltiu at,t8,10
801CBDA4 sll   t8,t8,2
801CBDA8 lui   at,0x8029
801CBDAC addu  at,at,t8
801CBDB0 lw    t8,0x56C4(at)
801CBDB4 jr    t8
```

The latter table is binary offsets 0xE9BA4–0xE9BCC, followed by four zero
alignment bytes to the image end. The JSON also inventories aligned runs of
four or more pointers into each image's CPU text as `rodata_candidates`.
These are explicitly **candidates**: a callback array in writable data can
have the same byte shape as a switch table. No claim is made that all such
runs are jump tables or that all rodata contains pointers.

### Main RSP subsegments

| Decompressed offsets | CPU storage VRAM | Type | Evidence |
|---|---|---|---|
| 32DB0–32E80 | 80042710–800427E0 | RSP boot text | SP CP0 DMA registers and task boot pointer |
| 32E80–34290 | 800427E0–80043BF0 | graphics RSP text | graphics task ucode pointer; vector instructions; next audio pointer |
| 34290–350B0 | 80043BF0–80044A10 | audio RSP text | audio task ucode pointer; vector loops; next initialized data |
| 39E10–3A610 | 80049770–80049F70 | graphics RSP data | graphics task data pointer, 0x800-byte length |
| 3A610–3A8D0 | 80049F70–8004A230 | audio RSP data | audio task data pointer; coefficient table to image end |

These are **CPU storage** addresses. RSP execution uses IMEM/DMEM addressing;
do not apply the CPU storage address when interpreting RSP jumps. RSP gfx text
can contain multiple IMEM pieces; the table does not assert all 0x1410 bytes
are resident in IMEM at once.

The graphics task setup at 0x8001149C stores boot pointer 0x80042710,
0x800114CC stores ucode pointer 0x800427E0, and 0x800114D8 stores data pointer
0x80049770; 0x800114D4 loads the 0x800 data length. The graphics identifier
`RSP SW Version: 2.0D, 04-01-96` is at binary +0x3A080 / CPU 0x800499E0,
inside that data blob. Audio task setup constructs boot pointer at
0x8002B12C, ucode pointer 0x80043BF0 at 0x8002B164, and data pointer
0x80049F70 at 0x8002B174, stored at 0x8002B198. Its task declares a data
transfer size of 0x800 (0x8002B178/0x8002B19C), which extends past initialized
audio data into zeroed main BSS. **Do not extend the file-backed subsegment**
based on that transfer length. Actual initialized audio data is 0x2C0 bytes.

## Other ROM regions requested

**0xA94460–0xA94D80 is referenced**, explicitly read as two adjacent blocks:

```text
80020F50 lui   a0,0x00A9
80020F54 lui   t8,0x00A9
80020F58 addiu t8,t8,0x4560
80020F5C addiu a0,a0,0x4460        # ROM A94460
80020F60 lui   a1,0x802D
80020F64 ori   a1,a1,0x4000        # destination 802D4000
80020F68 subu  a2,t8,a0           # 0x100 bytes
80020F70 jal   800007B4
...
80020F7C lui   a0,0x00A9
80020F80 lui   t9,0x00A9
80020F84 ori   s3,s3,0x4100        # s3's lui 802D at 80020F78
80020F88 addiu t9,t9,0x4D80
80020F8C addiu a0,a0,0x4560        # ROM A94560
80020F90 subu  a2,t9,a0           # 0x820 bytes
80020F94 jal   800007B4
80020F98 or    a1,s3,zero          # destination 802D4100
```

Subsequent code parses little-endian byte fields from the second block:
0x80020FE0/0x80020FE4 load bytes +3/+2, shift/add into a count, and iterate
records. Purpose is asset metadata/lookup data; precise schema unresolved.
Also 0x7DF8's ROM-pair asset table at CPU 0x80291FE8 includes 0xA94460 as
an end bound at 0x8029201C (pair beginning at 0x80292018). That is a bound
reference, not a load of this metadata block.

**0xAB5800–0xAB5810:** no explicit DMA or dereference of the 16-byte record
was identified. Its words are `000F4240 000F4240 00000000 00000000`.
0xAB5800 is referenced as the main compressed stream's end bound through
boot table 0x7DF0; the loader excludes it from the DMA, so this is **not**
evidence of consuming the record itself. The next payload starts at 0xAB5810.
Aligned raw pointer and materialized-address searches across boot and all
three CPU text images found no direct consumer. This is a negative static
result, **not proof of unreachability**: arithmetic/computed addressing could
still reach it. Its apparent meaning (two 1,000,000 values) is unresolved.

## Verified versus open

Verified: all 27 table contents and expanded hashes; executable destinations
and entry calls; indexed destination expressions for both data families;
three CPU text ends and three images' entry BSS clears; RSP storage blobs;
explicit reads of the intervening A94460 region. No load VRAM is wholly unknown.

Open: original `.data`/`.rodata` boundaries (candidate starts above, especially
0x7E00); exact byte-table and packed-graphics packet formats/names; full runtime
index/load sequence; computed consumers of the AB5800 record. The field-level
confidence in JSON intentionally preserves these limits. A matching build
should retain opaque initialized bytes until these semantic splits are proven.
