# T-014: graphics formats (US V1.0)

ROM SHA1 `ba52e91b44450c548467044b26951353dc491e04`. Addresses below are CPU VRAM in **decompressed binaries**, not compressed ROM offsets. Analysis used `.venv/bin/python`, rabbitizer, and scratch disassemblies in `/tmp/kig-t014/`, reading `build/segments/main.bin` (base `8000F960`), `ovl_7DF8.bin` (base `801ABB20`), and `ovl_7E00.bin` (base `801AD900`). No `asm/` files were used. ROM input is read only. PNGs and manifests belong under ignored `build/gfx/`; never commit them.

## Important corrections to T-011's provisional names

The main-table `+08` blocks are **Huffman decoding trees, not color palettes**. The main-table `+18` entries are **16-color palettes**, not merely unknown index data. Color frames have a 16-color alphabet but are **not raw CI4 textures**: a context-dependent Huffman bitstream expands through that palette into RGBA16 texels, plus a separate coverage texture. The 0x9900-byte assets are **256×150 CI8 portraits with an RGB888 palette**, not 144×136 RGBA16 pictures. These corrections are established by consumers and recognizable decoded images.

## Containers and frame directory (verified)

All bounds are exclusive. The fourteen 32-byte main records start at `80045E50`. The bounds and aliases are listed exhaustively in [assets.md](assets.md).

| Main table offset | Type | Meaning |
|---|---|---|
| +00/+04 | two BE u32 ROM addresses | Container bounds; slot 11 contains eleven BE-length-prefixed 1172 streams |
| +08/+0C | two BE u32 ROM addresses | Bounds of two consecutive 0x800-byte Huffman table blocks |
| +10/+14 | two BE u32 ROM addresses | Small 1172 stream; semantics still unresolved |
| +18/+1C | two BE u32 ROM addresses | Array of 32-byte, sixteen BE RGBA5551 color palettes |

Evidence for the table/block relationship:

```text
80021A74 addiu a2,zero,0x800
80021A78 jal   80000740             # a0 = main-table +08
80021A7C lw    a0,8(t6)
80021A94 addiu a2,zero,0x800
80021A98 jal   80000740
80021A9C addiu a0,a0,0x800          # second tree block
8002A1B8 lui   t1,0x8006
8002A1BC sw    t9,0x5C64(at)        # color-tree base: 80063C60 + player*800
8002A1D8 sw    t2,0x5C70(at)        # control-tree base: 80064C60 + player*800
8001D3B8 lw    t7,0x5E68(t7)        # main-table +18
8001D3BC sll   t8,v0,5              # palette variant * 32
8001D3CC jal   80000740
8001D3D0 addu  a0,t7,t8             # DMA length = 32
8001D734 lhu   t8,0(a0)
8001D740 sh    t8,-8(t0)            # copies BE colors to low-memory lookup
```

The self-sized records inside the raw containers have this layout:

| Record offset | Encoding | Meaning / evidence |
|---|---|---|
| +00 | LE u16 | Record ID; `80021824–80021838`, `80021930–80021948` |
| +02 | LE u16 | Frame-slot count; `8001DAB4–8001DAD8` |
| +04 | LE u32 | Total byte size including header and directory; `8002182C–80021860`, `800219A8–800219D0` |
| +08 | count × LE u32 | Frame offsets relative to record; `8001DB10–8001DB48` |
| variable | frame bytes | Unique frame offsets below size point at frames; duplicate offsets reuse frames; offsets equal to size are sentinels |

```text
8001DB10 sll   t5,a0,2
8001DB18 addu  v0,t5,a3             # a3 = record base
8001DB1C lbu   t6,0xB(v0)           # high byte of slot's LE offset
8001DB20 lbu   t8,8(v0)
...                                  # assemble all four offset bytes
8001DC50 addu  t6,a3,a2             # frame = record + offset
```

The eleven-stream path at `80021360–800213C4` inflates each child and advances source by its **BE u32 length**, which includes the length word and 1172 stream. The six UI streams at ROM `8F6AE0–8F9FA0` use the same framing (`80024D60–80024DA4`). A child can itself contain self-sized records. They add records beyond the inventory's 825 raw records; they must not be counted as part of those 825.

Every supported frame begins with:

| Frame offset | Encoding | Meaning |
|---|---|---|
| +00 | LE signed i16 | Horizontal origin/anchor |
| +02 | LE signed i16 | Vertical origin/anchor |
| +04 | LE u16 | Logical width |
| +06 | LE u16 | Height |
| +08 | bytes/bits | Format-specific image data |

`80031124–80031184` establishes these fields for Huffman color frames; `80031A90–80031AFC` for masks; `8002390C–80023988` for byte spans. Signed origins are explicitly sign-corrected at `8001DF00–8001DF28` and used in placement, rather than changing pixel dimensions.

## Character color frames: context Huffman spans

Verified consumer: `800310C0`, selected by `8001DE34`; second/companion data uses `80031A38` at `8001DE44`. `8001DE5C` handles an additional paired-frame/effect path that this decoder does not reproduce.

Bits are MSB first, starting at frame +08. Two kinds of symbol share one bit position.

**Control symbols** (`80032670`): start at the second 0x800-byte block. Each node occupies three bytes. If byte 0 is zero, byte 1 is the leaf value. Otherwise read a bit; the selected child is a *relative forward distance in nodes*. For bit 0, distance = byte1 + ((byte0 >> 5) << 8); for bit 1, distance = byte2 + ((byte0 & 0x1C) << 6). Add three times that distance to the current node's byte address. Repeat until a leaf.

```text
80032678 lbu   v0,0(v1)
8003267C bnez  v0,...
80032688 lbu   v0,1(v1)             # leaf
80032698 lbu   t7,0(fp)             # next compressed byte
800326A4 andi  fp,t7,0x80           # MSB first
800326B4 andi  v0,v0,0x1C           # high child-distance bits
800326BC sll   v0,v0,6
800326C4 addu  t2,t2,fp
800326C8 sll   fp,fp,1
800326D0 addu  t2,t2,fp             # total delta *= 3
800326D4 srl   v0,v0,5              # other branch's high bits
```

**Color symbols** (`80032600`): sixteen context trees, each at first_block + previous_color*128. Start each span with context zero. Node format is again three bytes: byte0==0 is a leaf with color index in byte1; otherwise choose byte1/byte2 by the next bit, multiply by three, and add to current node. A leaf sets the context for the next color. Palette indices are 0–15.

```text
80032604 addu  t3,t6,t8             # tree base + context offset
8003260C lbu   v0,0(v1)
80032618 lbu   v0,1(v1)
80032620 sll   t8,v0,7              # next context = color * 128
80032648 lbu   fp,2(v1)             # right relative child
8003265C lbu   fp,1(v1)             # left relative child
800313D0 jal   80032600
800313D4 move  t8,zero              # reset context at span start
800313D8 sll   v0,v0,1
800313DC lh    v0,0(v0)             # palette[color], NOT ROM pixel bytes
```

The first control is an initial transparent offset. Initial `F3` escapes to `254 + next_control` (`800312A8–800312C0`); initial `FF` represents a blank row. For each span: read coverage, then literal count, then that many context-coded colors. Read the next transparent skip. A skip `FE` extends to `254 + next_control`; `FF` ends the row. Other skips can cross a row boundary; carry the excess into the next row. This is why treating the stream as byte RLE or resetting the bit reader each row fails. Examples: a first 79×127 frame consumes 12,379 meaningful bits, fitting its 1,548-byte extent.

The runtime adds a duplicated edge texel on each side of each span. Coverage uses `(coverage & 7)<<5` at the left and `(coverage>>4)<<6` at the right (`800313E0–80031438`); interior coverage is FF. Color and coverage odd rows are pre-swapped for TMEM (`80031724/80031730` XOR 4). Texture color row stride is `align4(width+2)` pixels (`80031170–8003118C`); the separate byte plane has its own eight-byte alignment.

**Decoder limitation:** PNGs retain the logical, opaque color interior, with transparent skipped pixels. They omit the runtime's duplicated border texels and fractional edge coverage. They are recognizable sprite reconstructions, not bit-exact RDP output. Only palette variant zero is exported. Additional variants in the +18 array are real but not exported as duplicate images. Some paired/effect frames remain rejected by strict span/bounds/consumption checks.

## Companion alpha masks: byte/nibble runs

Verified consumer `80031A38`. These are coverage/intensity masks, not colored pictures or CI4 texel arrays. Each row starts with a byte length **including the length byte**. Length 1 is an empty row. Otherwise the next byte is the initial transparent skip; subsequent bytes are commands up to the row end:

| Command | Action |
|---|---|
| 00, n | Skip n transparent pixels |
| Nonzero, bit3 clear, low3 nonzero | Repeat high nibble for low3 pixels |
| Nonzero, bit3 clear, low3 zero; next byte n | Repeat high nibble for n pixels |
| Bit3 set, low3 0..3 | Emit high nibble, then high nibble + low3 + 1 |
| Bit3 set, low3 4..7 | Emit high nibble, then high nibble - (low3 & 3) - 1 |

The runtime stores nibble<<4 in byte texels. PNG previews normalize nibble 0..15 to alpha 0..255 and use white RGB; this is explicitly a mask visualization. Odd-row XOR swaps are removed in the logical PNG.

```text
80031B10 lbu   t0,0(s0)
80031B18 addu  t0,t0,s0             # end = row start + length
80031B28 lbu   t1,0(s0)             # initial transparent skip
80031B50 lbu   t1,0(s0)             # command
80031B60 andi  t2,t1,8              # adjacent pair flag
80031B6C andi  t2,t1,7              # short repeat count
80031B74 andi  t1,t1,0xF0           # output intensity/coverage
80031B78 lbu   t2,0(s0)             # extended repeat count
80031B94 andi  t2,t2,3              # negative pair delta case
80031B98 negu  t2,t2
80031BA4 sll   t2,t2,4
80031BB8 sb    t1,0(s2)             # one BYTE per output pixel
```

## Byte-span UI images

Verified consumer `800238C4`. Row byte lengths include the length byte. A row contains packets `{coverage, transparent_skip, literal_count, literal_bytes[count]}`. The palette parameter is a byte-addressed little-endian 16-bit lookup: **add the literal byte directly**, not literal*2. Interior colors force bit0 to one. The left duplicated color preserves the palette low bit; right duplicates the last literal. Coverage is `(coverage&7)<<5` left, `(coverage&0x38)<<2` right. The decoder exports logical width, without runtime alignment/border padding, and represents edge coverage as PNG alpha.

```text
800239D8 lbu   t9,0(t2)             # row length
800239E8 addu  v0,t9,s2             # end offset
80023A20 lbu   s4,1(t2)             # skip
80023A24 lbu   fp,0(t2)             # coverage
80023A28 lbu   s7,2(t2)             # count
80023B88 lbu   v1,0(t2)             # literal
80023B94 addu  v0,v1,s6             # palette + BYTE offset
80023B98 lbu   t7,1(v0)
80023B9C lbu   t9,0(v0)
80023BAC addu  a2,t8,t9             # LE palette word
80023C20 ori   t9,a2,1              # force opaque interior
80024E24 lui   a1,0x8004
80024E28 addiu a1,a1,0x7C38         # fixed UI palette supplied by caller
80024E2C jal   800238C4
```

The six compressed UI records use this fixed palette. Other callers can supply a different palette, e.g. metadata at ROM A94460; the tool does not assume the fixed UI palette works for every arbitrary frame.

## Portraits: 256×150 CI8 with RGB888 palette

The ten pairs at 7DF8 CPU `80291FE8` select 1172 streams. Each inflates to exactly 0x9900 bytes:

| Expanded offset | Size | Meaning |
|---|---|---|
| 0000 | 0300 | 256 RGB888 triplets, in R,G,B order |
| 0300 | 9600 | 256×150 row-major unsigned 8-bit palette indices |

The palette conversion is `(R & F8)<<8 | (G & F8)<<3 | (B & F8)>>2 | 1`. PNGs use this same five-bit quantization and expand to eight-bit channels. It is not direct 24-bit RGB display and not RGBA5551 source data.

```text
801C5FB0 addiu v1,t7,-0x2700        # 8007D900 = expanded start
801C5FBC addiu v0,v0,-0x2400        # 8007DC00 = start + 300
801C5FC4 lbu   t8,2(v1)             # B
801C5FC8 lbu   t7,0(v1)             # R
801C5FD4 andi  t6,t9,0x3E
801C5FDC andi  t9,t8,0xF800
801C5FE0 lbu   t8,-0xB(v1)          # G (v1 advanced 12)
801C5FF0 andi  t9,t6,0x7C0
801C5FF8 ori   t6,t8,1
801C5FFC sh    t6,-8(a0)            # compact RGB palette into RGBA16
801C6098 bne   v1,v0,...            # stop at expanded +300
801C6150 lui   t9,0xFD10            # RGBA16 palette image load
801C61B8 ori   t7,t7,0xC000         # F0 load-TLUT parameter 073FC000
801C6244 addiu t6,zero,0x96         # height 150
801C6278 lw    a1,0xDC(sp)          # expanded +300 pixel data
801C627C addiu a2,zero,2            # image format CI
801C6280 addiu a3,zero,0x100        # width 256
801C6298 jal   801BC1B0             # textured rectangle renderer
```

This establishes dimensions independently of factorizing the expanded byte count. Portrait 00 visibly shows a character against wooden scenery, with coherent anatomy, palette and row layout.

## G_SETTIMG and runtime texture formats

`800201A8` emits `FD100000`: `G_SETTIMG`, RGBA, 16-bit; it loads the CPU-expanded character color texture. `8002024C` emits `FD900000`: I-format, **16-bit load size**, for the byte coverage buffer (the load count is halved at `800202B0–800202C0`). A load's size is not proof that the final render tile is 16-bit. Together with the decoder's explicit byte stores, this explains the separate color/coverage planes. There is no evidence here for directly uploading character source as CI4 or CI8. The portrait path really does load a TLUT and pass CI format to its renderer.

## Stage packets and other unresolved data

The thirteen table entries 7E60–7EC0 (twelve unique streams, one alias) still have **zero decoded stage images**. Their wrapper bytecode has interleaved GBI commands and payload bytes. A `B7/E7/BA/B9/BB/FC` signature at varying alignment does not establish image dimensions, texture bounds, segment relocation or a palette. The tool deliberately does not turn guessed aligned byte ranges into purported stage textures. Frame pairing/effects, exact RDP edge behavior, stage packet decoding, and the small +10 streams remain open.

## Reproduction, validation and coverage

```sh
python3 tools/analysis/extract_segments.py baserom.us.z64
python3 tools/analysis/gfx_decode.py baserom.us.z64 --out build/gfx
```

The decoder uses only stdlib (`zlib`, `struct`, etc.), verifies the complete ROM hash, reads the checked-in inventory to locate the 825 raw records, and discovers records in the seventeen compressed children. Every exported frame passes dimension, node-traversal, span/row bounds and payload-consumption checks; at most three trailing alignment bytes are accepted. Duplicate frame slots are exported once per unique offset; frame totals therefore count **distinct payloads**, not animation slots. A record is “decoded” if at least one distinct frame decodes, and “complete” only if all its distinct frame payloads decode. This is structural decoding coverage, not a claim that every image was visually inspected or that effects match the RDP.

The generated manifest records dimensions, origins, source ROM addresses, record IDs, frame offsets, image class, compressed-child status and class totals. Failed frame candidates are omitted from PNG output and reflected in the printed totals. The source families in the summary describe container ownership; the printed image-class counts describe actual decoding algorithms.

Visual inspection confirmed recognizable colored character poses and the CI8 portraits. The T-014 baseline (superseded by T-017 below) had these counts:

| Container family | Records with ≥1 image / total | Completely decoded records | Unique frame payloads decoded / total |
|---|---:|---:|---:|
| Main-table character containers (including 11 inflated records) | 803 / 806 | 691 | 5,923 / 6,142 |
| Other raw containers + six inflated UI records | 10 / 36 | 10 | 89 / 227 |
| Portraits | 10 / 10 | 10 | 10 / 10 |
| Stage packet entries (includes alias) | 0 / 13 | 0 | not enumerated |

Thus **813 / 842 sprite records** have at least one image (796 / 825 raw records, plus all 17 inflated records); 701 / 842 are complete. Sprite payload coverage is **6,012 / 6,369 (94.39%)**. Adding portraits gives **6,022 PNGs**: 4,967 Huffman color frames, 994 alpha masks, 51 byte-span UI/font frames, 10 portraits. These are image counts, not unique visual poses: separate records can contain identical pictures. The remaining 357 sprite payloads are rejected, rather than exported as purported successful images.

Inspected examples:

- `build/gfx/huffman_character/085B8C_0043_id027_02E48.png`: recognizable orange/blue fighter performing a high kick.
- `build/gfx/huffman_character/169CF4_0134_id030_00E10.png`: recognizable green/gray fighter pose.
- `build/gfx/portraits/portrait_00_A77960.png`: coherent character portrait with wooden background.
- `build/gfx/byte_spans/8F6CE3_0837_id011_00078.png`: readable gold letter **A**; confirms font glyph decoding.
- `build/gfx/byte_spans/8F6AE0_0836_id002_00010.png`: clean curved UI bar outline.
- `build/gfx/alpha_masks/008B70_0000_id199_00E20.png`: coherent fighter silhouette. Companion mask normalization is a preview, not a colored sprite.

T-017 additionally inspected stage texture samples and the auxiliary skull sprite. Character identities and stage names are deliberately not assigned from appearances alone.

## Stage packets (T-017)

Verified from `build/segments/main.bin`, disassembled with rabbitizer in
`/tmp/kig-t017/`; no generated `asm/` input. The loader is `80012A8C`
(DMA `80012AE4`, inflate `80012B0C`). Boot slots `7E60–7EC0` inflate to
`802D4000`; slot 12 duplicates slot 6. These streams are outside the inventory's
`7ED0–A94D80` depth-0 accounting region.

There is **no single byte prefix/header before a conventional display list**.
`8002FB80` expands a counted stream of tagged commands. The high two bits
of each tag select the following format; the packed input can be unaligned.

| Tag high bits | Input bytes | Expansion (verified code) |
|---|---:|---|
| 00 | 9 | Ignore tag, copy next eight bytes as one GBI command (`8002FC54–8002FC9C`) |
| 01 | 4 | Emit FD; low six tag bits index a texture destination pointer array; next three bytes become the remaining command header (`8002FD2C–8002FD7C`) |
| 10 | 2 | Emit BF triangle: tag bits 5:4 are the flag; remaining three nibbles are vertex indices multiplied by ten (`8002FBF4–8002FC48`) |
| 11 | 3 | Emit 04 vertex load: address = vertex destination + `(tag&63)*4096 + byte1*16`; byte2 supplies count/cache header (`8002FCA0–8002FD28`) |

`8002FFDC` combines command expansion with vertex expansion at `8002FDA0`.
Arguments are packed-command pointer/count, packed-vertex pointer/count,
texture destination pointer array, vertex destination, and display-list output.
`8001C0E4` batches these calls using six main-image arrays plus a batch count.
Stage initialization callbacks come from `800451EC`; decoder `STAGE_CALLS`
records their actual call addresses and argument constants. For example stage 11
calls `8002FFDC` at `80019830`: commands `802D4000`, count 84, vertices
`802D4158`, count 116, texture destinations `802D6098`. Other stages use the
batch wrapper (stage 0 at `80018E38`). Boundaries come from these consumers,
not a scan for plausible GBI opcodes.

Vertices are reconstructed as standard 16-byte N64 vertices. Each starts with
a BE u16 flag word. Successive low two-bit fields encode XYZ: 0 reuses the
previous coordinate, 1/2 subtract a signed byte, 3 subtracts a BE halfword
(modulo 16 bits), as shown at `8002FE10–8002FEB4`. The next two single bits
conditionally read BE halfwords for ST; the next four bits conditionally read
RGBA bytes (`8002FEB8–8002FFC0`). Absent fields reuse the previous vertex;
initial state is the 16-byte record at `80048290`. Geometry exports contain XYZ
and triangles with validated cache references. Each batch is a separate local
coordinate space: **OBJ omits runtime matrices, object placement, animation,
materials, UVs and visibility ordering** and is not a rendered stage.

`80030020` reads parallel source/destination pointer arrays and BE u16 size/type
entries. High three bits select the decoder; low thirteen bits are its count.
Type 0 calls `800300DC` and emits that many RGBA5551 halfwords. For an even
first byte, read a second byte and emit `(first<<8)+((second&0xC0)<<1)+
(second&0x3F)`. For an odd first byte, copy one previous halfword, or two when
bit7 is set; backward distance is `((first>>1)&63)+1`. Overlapping copies are
intentional. This is a separate texture compression layer inside the inflated
stage packet. RGBA16 PNG dimensions are obtained from F2 tile-size commands
associated with each tagged FD reference, and accepted only when their area
matches the decoded texel count. No arbitrary width is silently guessed.

Current output: **368/391 texture entries**, plus **13 OBJ files**, representing
12 unique packets. There are 18 type-1 entries dispatched to `8002A40C`:
that routine reads an eight-byte compressed header, builds decoder state via
`8002A254/80032750/8002A1E0`, and emits bytes using `800327E8`; it is not the
RGBA16 backreference format. They remain explicitly rejected. Five type-0
entries have no F2 dimensions in the traced initialization lists; these also
remain rejected despite their texels decoding. `manifest.json` gives every
texture's source offset, type, count, observed dimensions and rejection reason.
Stage 3's callback passes batch count 15 (`80015F14`) for arrays with fourteen
valid packet pointers; the fifteenth reads adjacent count data as pointers.
The exporter rejects and records that batch rather than treating arbitrary
memory as geometry. Whether this is a runtime bug or depends on state outside
this static path is unresolved.

Hypotheses/limits: visual stage names are not assigned. Tile dimensions are
storage views, not proof of intended material orientation. Runtime code can
reuse textures in additional lists; the five absent dimensions require tracing
those paths. Type-1 texture recovery and exact stage rendering remain open.

### Auxiliary sprite containers and remaining frame failures (T-017)

The previous decoder selected Huffman tables only when the record's ROM address
fell inside a main-table +00 interval. That excluded character auxiliary records
loaded by immediate-address DMA, incorrectly routing them through byte-span UI
and mask decoders. These are valid record directories, not corrupt headers.
T-017 adds the following associations:

| ROM container range | Main-table Huffman/palette index |
|---|---:|
| `013200–01D640` | 2 |
| `01D640–024D60` | 3 |
| `024D60–02ECB0` | 4 |
| `049FD0–0566D0` | record ID 0–10 selects character index |
| `1EB6D0–1F3200` | 1 |
| `2C2280–2CF0A0` | 2 |
| `469660–470390` | 4 |
| `53CC40–54D720` | 5 |

Evidence distinction: immediate container bounds and loader branches are verified
code facts (`80024760–80024964` selects indices 1/2/4/5 for the four relevant
auxiliary groups). The broader table associations were also checked by attempting
all fourteen tree sets on each container's first frame: exactly one distinct
character tree decodes the full frame within the existing three-byte padding
bound. The eleven records at `049FD0–0566D0` instead select the tree by their
record ID (0–10); using tree zero for the whole container fails on IDs 1–10. Palette-zero selection and recognizable output support
these associations; this is static format inference, not an observed runtime
palette trace. A decoded `013200`, record 153 frame at +5C is a recognizable
metal skull with glowing eyes. The decoder also handles consecutive blank-row
FF controls by advancing a row for each (`800312C4–80031324`).

Every rejected frame is now individually listed in `build/gfx/manifest.json`:
ROM record location, record ID, frame offset, extent, primary decoder error and
fallback mask error. This preserves diagnostic evidence rather than silently
counting skipped records. A failed Huffman span or unread input is not accepted
merely by relaxing bounds: that could produce plausible but incorrect pixels.
The paired/effect path at `8001DE5C` and its alternate consumption rules still
require tracing before those frames can be claimed as decoded.


T-017 final coverage: **839/842 sprite records**, **725 complete**, and
**6,147/6,369 distinct sprite frames (96.51%)**: 135 additional frames and
26 additional records recovered. Auxiliary-inclusive character containers:
830/833 records, 716 complete, 6,078/6,300 frames; other/UI containers:
9/9 records complete, 69/69 frames. With ten portraits and 368 stage textures,
the manifest contains **6,525 PNG entries**. Old output files can remain in an
existing output directory; the manifest is the authoritative set for this run.

The remaining **222 frames** fail the primary Huffman decode as follows:
138 exhaust their bounded frame input while reading bits; 84 request a span
past the logical row width. The fallback mask decoder also rejects all of them
(142 row overruns, 59 out-of-range nibble pairs, 21 invalid row extents).
No frame directories fail parsing. The only wholly rejected records are ROM
`2D9B80` (ID 3, four frames), `38423C` (ID 112, three frames), and `385868`
(ID 113, three frames). These have valid dimensions/directories but incompatible
span consumption under the implemented color/mask paths. Assigning a specific
alternate format to them is still a hypothesis, not a verified result.

Sanity checks: viewed stage 0 texture 00, stage 5 texture 05 and recovered
`013200` ID 153 frame +5C. Stage output contains 22,493 local vertices and
13,037 triangles including the duplicated slot. Six stage entries have every
texture decoded; geometry bounds pass for every exported triangle. Inventory
regeneration was byte-identical, and all 1,021 depth-0 intervals partition
exactly 11,062,960 bytes from `7ED0` through `A94D80`.
