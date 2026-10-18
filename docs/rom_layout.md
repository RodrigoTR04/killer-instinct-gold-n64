# US 1.0 ROM layout (T-002)

All ranges below are **start inclusive, end exclusive**. ROM was opened read-only;
no extracted binaries are written. Facts are distinguished from provisional
classifications. This is sufficient for an initial split of the bootstrap and
opaque compressed segments, not yet a complete function/asset inventory.

## Reproduction

```sh
python3 tools/analysis/inspect_rom.py baserom.us.z64
python3 tools/analysis/inspect_rom.py baserom.us.z64 0x1000 0x1200
python3 tools/analysis/inspect_rom.py baserom.us.z64 --main 0 0x130
python3 tools/analysis/compressed_blocks.py baserom.us.z64
```

Both scripts use Python's standard library only and print to stdout. `--main`
decompresses the first table entry in memory. Its printed offsets are then
**decompressed offsets**, not cartridge offsets. The minimal instruction decoder
prints unsupported instructions as words; it is not a full MIPS disassembler.
Do not interpret its output on data as executable code. Its default address
mapping is for ROM >= 0x1000, not IPL3's DMEM execution address.

## Verified header and IPL3

ROM size `0xC00000` (12 MiB); SHA1
`ba52e91b44450c548467044b26951353dc491e04`.

| ROM offset | Field | Value |
|---|---|---|
| 0x00 | PI bus configuration / z64 byte-order signature | 0x80371240 |
| 0x04 | clock-rate field | 0x0000000F |
| 0x08 | entrypoint | 0x80000400 |
| 0x0C | release / SDK-format field | 0x00001444 |
| 0x10 | CRC1 | 0x9E8FE2BA |
| 0x14 | CRC2 | 0x8B270770 |
| 0x20 | title, 20 bytes | `KILLER INSTINCT GOLD` |
| 0x3B | manufacturer | N |
| 0x3C | cartridge ID | KI |
| 0x3E | country | E (US) |
| 0x3F | revision | 0 |

`0x1444` is reported as the raw release field; its precise version encoding
has not been independently established and is **not proof of the linked CPU
library version**. Likewise `0xF` is the raw
clock field, not a 15-Hz clock. `osInitialize` masks low clock-field bits and
uses a default clock when the masked value is zero; see ROM 0x3318–0x3380 (mask `0xFFFFFFF0`, then multiply by 3/4).

IPL3 is ROM `[0x40,0x1000)`, length `0xFC0`:

* MD5 `e24dd796b2fa16511521139d28c8356b`
* SHA1 `b2afae246e1dab746bfb28cb346e2911965eefa1`

The MD5 exactly matches **6102/7101**, and differs from known 6103
`319038097346e12c26c3c21b56f86f23`, 6105
`ff22a296e55d34ab0a077dc2ba5f5796`, and 6106
`6460387749ac0bd925aa5430bc7864fe`. For this US cartridge, call it **CIC 6102**.
Hash reference: [n64checksum's IPL3 hash table](https://github.com/Dragorn421/n64checksum/blob/main/README.md).
The matching [N64-IPL source](https://github.com/decompals/N64-IPL/blob/main/src/ipl3.s)
distinguishes X103/X106 entry adjustments; this 6102 variant uses the header
entrypoint unchanged. Do **not** subtract the 6103/6106 entrypoint offsets.
IPL3 loads the first `0x100000` bytes after the header:
ROM `[0x1000,0x101000)` → RAM `[0x80000400,0x80100400)`.
This includes asset bytes after the small bootstrap; it is not a 1-MiB text segment.

## Verified entry and bootstrap

For the uncompressed bootstrap, `VRAM = ROM + 0x7FFFF400`.

```text
ROM      VRAM      word      instruction
001000   80000400  3C088000  lui   t0,0x8000
001004   80000404  250872D0  addiu t0,t0,0x72D0
001008   80000408  34098690  ori   t1,zero,0x8690
00100C   8000040C  2129FFF8  addi  t1,t1,-8
001010   80000410  AD000000  sw    zero,0(t0)
001014   80000414  AD000004  sw    zero,4(t0)
001018   80000418  1520FFFC  bnez  t1,0x8000040C
00101C   8000041C  21080008  addi  t0,t0,8       # delay slot
001020   80000420  3C0A8000  lui   t2,0x8000
001024   80000424  3C1D8001  lui   sp,0x8001
001028   80000428  254A0450  addiu t2,t2,0x450
00102C   8000042C  01400008  jr    t2
001030   80000430  27BDB2D0  addiu sp,sp,-0x4D30 # delay slot
```

Thus bootstrap BSS is `[0x800072D0,0x8000F960)`, size `0x8690`;
initial stack top is `0x8000B2D0`; boot function is `0x80000450` (ROM 0x1050).
This function calls likely `osInitialize` at `0x80002590`, creates thread 1
(entry `0x800004AC`), and starts it. That thread initializes the PI manager,
creates thread 3 at `0x80000520`, and stops the first thread.

Bootstrap executable bytes end at ROM `0x7160` (VRAM `0x80006560`): the
preceding routine ends `jr ra; nop` at ROM 0x7150/0x7154 with zero alignment.
From 0x7160 are inflate tables, SDK globals/VI modes, and ROM-pair tables.
Bootstrap initialized data ends at `0x7ED0`, whose mapped address is exactly
the BSS start. Treat `[0x1000,0x7ED0)` as one boot segment with text/data
subsegments; `[0x7ED0,... )` is cartridge asset storage, **not ROM-backed BSS**.

## Verified main loader and compressed executable

Thread 3 reads the pair at VRAM `0x800071F0` (ROM `0x7DF0`):
`{0x00A94D80,0x00AB5800}`. Relevant instructions:

```text
ROM 1190 / 80000590: lui v0,0x8000; addiu v0,v0,0x71F0
ROM 1198 / 80000598: lw a0,0(v0); lw t7,4(v0)
ROM 11A0 / 800005A0: lui a1,0x802D; ori a1,a1,0x4000
ROM 11A8 / 800005A8: jal 0x80000740; subu a2,t7,a0
ROM 11B0 / 800005B0: # a0=0x802D4000, a1=0x8000F960, a2=0x803A2000
ROM 11C4 / 800005C4: jal 0x80000900
ROM 11CC / 800005CC: lui t9,0x8000; ori t9,t9,0xF960
ROM 11D4 / 800005D4: jalr t9; nop
```

ROM `[0xA94D80,0xAB5800)` is therefore **verified compressed main code/data**.
The actual stream ends at `0xAB57FB`, followed by 5 alignment bytes. Its first
two bytes are `11 72`; raw DEFLATE starts at `0xA94D82`. Python zlib with
`wbits=-15` reaches EOF and produces exactly `0x3A8D0` bytes, SHA1
`81736d32e8cda8f399b319a49250dff972b81af8`.
It maps to `[0x8000F960,0x8004A230)`; no linear ROM-to-VRAM mapping exists
inside this compressed span. The boot inflate wrapper at ROM 0x1500 explicitly
advances its source pointer by two bytes before inflating.

The decompressed main begins:

```text
+000000 / 8000F960: 27BDFFE8 addiu sp,sp,-24
+000004 / 8000F964: 3C048005 lui a0,0x8005
+000008 / 8000F968: 3C0E8012 lui t6,0x8012
+00000C / 8000F96C: 2484A230 addiu a0,a0,-0x5DD0
+000014 / 8000F974: 25CE7C30 addiu t6,t6,0x7C30
+000018 / 8000F978: 0C000AE0 jal 0x80002B80 # bzero
+00001C / 8000F97C: 01C42823 subu a1,t6,a0
```

This clears additional BSS `[0x8004A230,0x80127C30)`, size `0xDDA00`.
The next call clears `[0x80128350,0x801726D0)`, size `0x4A380`.
These are distinct from the bootstrap BSS. Main contains code through at least
VRAM `0x80042930` (decompressed +0x32FD0), and data/RSP microcode later;
its precise text/rodata boundary remains unverified.

### Later DMA and overlays

`0x80000740` (ROM 0x1340) invalidates the destination D-cache, builds an
OSIoMesg, calls `0x80002F00` with normal priority/read direction, then blocks
on `0x80003010`. A chunked version at `0x800007B4` (ROM 0x13B4) uses chunks
of at most `0x14000` bytes. Its calls to DMA/receive are at ROM 0x149C/0x14AC.
`0x80002F00` (ROM 0x3B00) is confidently `osPiStartDma`: seven-argument
interface, message type 11/12, return queue, DRAM/ROM address and length fields.

Raw PI DMA is at `0x80004B70` (ROM 0x5770):

```text
ROM 5790: 3C0EA460 lui t6,0xA460
ROM 5794: 8DD00010 lw s0,0x10(t6) # PI_STATUS
ROM 5798: 320F0003 andi t7,s0,3   # wait for DMA/IO idle
ROM 57C0: 3C08A460 lui t0,0xA460
ROM 57C4: AD020000 sw v0,0(t0)    # translated DRAM address
ROM 57E8: ADAC0004 sw t4,4(t5)    # cart address, masked to physical
ROM 5810: 25CFFFFF addiu t7,t6,-1
ROM 5818: AF0F000C sw t7,0xC(t8)  # PI_WR_LEN, cart -> RAM
ROM 582C: AD280008 sw t0,8(t1)    # PI_RD_LEN, opposite direction
```

The ROM-pair table `[0x7DF0,0x7EC8)` has 27 entries (including a duplicate).
`compressed_blocks.py` prints them all. First entries:

| Table ROM | Cartridge span | Expanded size | Status |
|---|---|---|---|
| 0x7DF0 | 0xA94D80–0xAB5800 | 0x3A8D0 | main, verified destination 0x8000F960 |
| 0x7DF8 | 0xAB5810–0xB00EB0 | 0xE9BD0 | additional executable; destination unresolved |
| 0x7E00 | 0xB00EB0–0xB14BA0 | 0x25930 | executable overlay, destination 0x801AD900 |
| 0x7E08 | 0xB14BA0–0xB184E0 | 0x8BB0 | data-looking payload, purpose unresolved |
| 0x7EB8 | 0xBF9100–0xBFB020 | 0x20C0 | final table payload |

The second payload starts `27BDFFA8 3C068029 3C0E802D 24C656F0 ...`, a
function prologue with BSS bounds `0x802956F0`/`0x802D3FF0`.
The third starts `3C08801D 3C09801E 25083230 2529A030 ...`, a byte-clear
loop for `[0x801D3230,0x801DA030)`.
Main at decompressed +0x2D8 (VRAM 0x8000FC38) takes table offsets +0x10/+0x14
(the third pair), DMAs to `0x802D4000` at +0x2F4, then inflates to
`0x801AD900` at +0x30C. This destination plus expanded length is exactly
`0x801D3230`, matching that overlay's BSS start.
There are many more loader calls; e.g. main VRAM 0x80012138, 0x800122B8,
0x80012AE4, 0x80014270, 0x80020F70. Not every compressed table entry is code.

## SDK identification: confidence and limits

No literal `libultra`, `osInitialize`, `2.0I`, `2.0J`, `2.0K`, or `2.0L`
version string was found in the cartridge or first decompressed main payload.
**CPU libultra revision is unresolved.** Header release 0x1444 and RSP 2.0D are separate
pieces of evidence, not interchangeable version identifiers.

| ROM / VRAM | Identification | Confidence / evidence |
|---|---|---|
| 0x3190 / 0x80002590 | osInitialize | high: boot's first SDK call, FPU setup, PIF SI handshake, installs exception vectors |
| 0x33C0 / 0x800027C0 | osCreateThread | high: boot caller supplies thread/id/entry/arg/stack/priority |
| 0x3510 / 0x80002910 | osStartThread | high: boot-created thread argument |
| 0x3780 / 0x80002B80 | bzero | high: main/BSS calls and sizes |
| 0x3820 / 0x80002C20 | osInvalICache | medium: bootstrap whole-main cache operation |
| 0x38A0 / 0x80002CA0 | osInvalDCache | high: called before every ROM DMA |
| 0x3AD0 / 0x80002ED0 | osCreateMesgQueue | high: queue/buffer/count call pattern |
| 0x3B00 / 0x80002F00 | osPiStartDma | high: OSIoMesg construction described above |
| 0x3C10 / 0x80003010 | osRecvMesg | high: queue/message/blocking flag |
| 0x49A0 / 0x80003DA0 | exception vector preamble | high: `3C1A8000 275A3DB0 03400008 00000000` |
| 0x49B0 / 0x80003DB0 | __osException | high: k0/k1, CP0 status, full context saves |
| 0x5770 / 0x80004B70 | osPiRawStartDma | high: PI register sequence above |

These are **instruction/ABI identifications**, not a claim of a byte-exact match
against a specific SDK archive. No external SDK archive byte-signature match
was performed. The vector preamble above is a useful exact local signature;
version-specific signature comparison remains necessary. MI register accesses
include ROM 0x4B50 (`lui t1,0xA430`); VI accesses include 0x6044, 0x60AC,
0x62C4 (`0xA440`); PI accesses include 0x52F0/0x5790 (`0xA460`).

## Coarse map of all 12 MiB

| Cartridge range | Classification | Evidence / certainty |
|---|---|---|
| 0x000000–0x000040 | header | verified fields above |
| 0x000040–0x001000 | IPL3 6102 | exact hash match |
| 0x001000–0x007160 | bootstrap CPU text | instruction continuity, SDK routines, final return/alignment |
| 0x007160–0x007ED0 | bootstrap tables/data | inflate tables, VI records, ROM pair table, exact BSS boundary |
| 0x007ED0–0x8E6234 | assets, mixed encoding | provisional purpose; high entropy, scattered validated 1172 streams |
| 0x8E6234–0x8F9F92 | packed 1172 asset stream group | multiple complete streams, often four bytes between them |
| 0x8F9F92–0xA6AA70 | lower-entropy asset region | provisional purpose; 64-KiB entropy mostly 6.06–7.40 bits/byte |
| 0xA6AA70–0xA94460 | compressed asset group | verified 1172 streams, many expand to exactly 0x9900 bytes |
| 0xA94460–0xA94D80 | intervening data/alignment | unresolved, do not assume all padding |
| 0xA94D80–0xAB5800 | compressed main text/data | verified DMA/decompression/jump |
| 0xAB5800–0xAB5810 | 16-byte intervening record | starts `000F4240 000F4240 00000000 00000000` |
| 0xAB5810–0xBFB020 | compressed overlays/data | ROM-pair table; all 26 distinct payload starts validate |
| 0xBFB020–0xC00000 | padding | every byte is 0xFF; 0x4FE0 bytes |

Entropy is measured in aligned 64-KiB blocks by `inspect_rom.py`, not a claim
of exact asset boundaries. Examples: block 0x000000 = 6.814, 0x010000 = 7.689,
0x130000 = 7.980, 0x900000 = 6.666, 0x9B0000 = 6.058,
0xA70000 = 7.977, 0xB40000 = 7.995. High entropy alone proves neither
compression nor encryption.

Compression results: no Yay0/Yaz0/MIO0 magic; one `RNC` at 0x420091 is followed
by 0x89 (not RNC method 1/2), so it is not a credible RNC header. There are
220 raw `1172` occurrences; 71 reach raw-DEFLATE EOF under an 8-MiB output cap.
Two tiny unaligned hits (0x6134C9, 0x6A8DAF) are likely accidental, illustrating
why magic/EOF alone does not prove an asset. The aligned table payloads and
repeated groups are much stronger evidence. Random zlib-looking 789C/78DA
pairs also occur; their presence does not establish zlib-wrapped compression.
Verified examples outside the table: 0x121F70→0x121FEF expands to 0x168;
0x1F4290→0x1F66FE expands to 0x8708;
0x54E7D0→0x551E59 expands to 0x9C48.

## Notable strings

| Location | Text | Interpretation |
|---|---|---|
| ROM 0x20 | KILLER INSTINCT GOLD | header title |
| ROM 0xA94D80, expanded +0x3A080, VRAM 0x800499E0 | RSP SW Version: 2.0D, 04-01-96 | verified graphics microcode build identifier |
| same stream, expanded +0x3A09F, VRAM 0x800499FF | SGI U64 GFX SW TEAM: S Anderson, S Carr, H Cheng, K Luster, R Moore, N Pooley, A Srinivasan | microcode attribution |

There is no direct cartridge offset for a string inside a DEFLATE stream.
No credible compiler/build filename or game debug ASCII string was identified
in the raw ROM or first main payload. Printable coincidences such as raw
0xD52FE `ERare\\E7#` repeat in apparent assets and are not treated as Rare
copyright/version strings. Other compressed payloads need a semantic string
pass before concluding that debug text is absent globally.

## Next split and unresolved work

Start splat with header/IPL3, boot at ROM 0x1000 VRAM 0x80000400,
text/data split 0x7160, boot end 0x7ED0, and opaque assets/compressed spans
above. Bootstrap BSS belongs in RAM, not a consumed cartridge range.
A separate decompression-aware build step will be required for main and
executable overlays; do not assign their compressed cartridge offsets a linear
VRAM mapping. Further work: identify precise main/overlay text/data boundaries,
second payload destination and lifetime, all table consumers/asset types,
CPU SDK archive signatures/version, and dynamic overlay load order.
