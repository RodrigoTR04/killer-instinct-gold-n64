# Resident boot code

The US V1.0 boot image remains resident while main and the executable overlays
run. The game portion is 21 byte-exact C functions (8,468 inventory bytes),
compiled with IDO 5.3 `-O2 -mips2`. SDK C in `src/boot/libultra/` retains its
separate flags and provenance; handwritten entry, exception and cache routines
remain assembly. `include/boot.h` describes the shared game interfaces.

## Startup and resident services

The entry at 0x80000400 clears boot BSS, establishes the stack at 0x8000B2D0,
and jumps to `boot_start`. That routine initializes libultra and starts thread
1 at priority 10. Its idle routine initializes the PI manager, starts thread 3
at priority 10 to load main, then drops its own priority to zero and spins.

`boot_load_main` checks the OS reset-type word at 0x8000030C. On a cold start
it clears 0x8000F960–0x80400000; otherwise it clears only
0x802D4000–0x80400000. It invalidates instruction and data caches over the
larger range, DMA-loads compressed main to 0x802D4000, inflates it to
0x8000F960 with scratch at 0x803A2000, and calls main's entry.

Main then calls `boot_init_scheduler`, subscribes its retrace queue, and calls
`boot_init_dma_events`. The resident scheduler creates the VI manager at
priority 254 and its own thread 20 at priority 13. It receives byte-valued
events: 0 is VI retrace, 1 is DP completion, and 2 is SP completion. It yields
graphics SP work for audio, resumes yielded graphics, starts queued DP work,
swaps completed framebuffers, and sends task completion messages. Up to three
subscriber queues receive a message whose first halfword is 1 on each retrace.
The first subscription argument is unused but preserved in the API.

`boot_dma` performs one blocking PI transfer. `boot_dma_chunked` drains old
retrace notifications, then transfers at most 0x14000 bytes per retrace,
waiting for PI completion after every chunk. Both invalidate destination
D-cache before starting. PI queue storage is shared with startup stack-top
addresses; their numerical coincidence must not be interpreted as independent
simultaneously live allocations.

## Memory map

All ranges below are half-open CPU virtual addresses unless marked ROM.

| Range/address | Use |
|---|---|
| ROM 0x1000–0x7ED0 | Resident initialized boot image |
| 0x80000400–0x80006560 | Entry, game code and SDK text |
| 0x80006560–0x800072D0 | Initialized tables and SDK/game data |
| 0x800071F0–0x800072C8 | 27 compressed-payload ROM-bound pairs |
| 0x800072D0–0x8000F960 | Boot BSS, thread/queue storage and stacks |
| 0x8000BF80–0x8000BFA0 | Inflate pointers, bit state and scratch allocation count |
| 0x8000F960–0x8004A230 | Main initialized image (0x3A8D0 bytes) |
| 0x801ABB20 | Executable overlay 0x7DF8 destination |
| 0x801AD900 | Executable overlay 0x7E00 destination |
| 0x802D4000 | Main compressed staging buffer; reused by later loaders |
| 0x803A2000 | Main inflate Huffman scratch; also used by later loaders |

The executable overlays overlap and are mutually exclusive. See
[segments.md](segments.md) for all payload destinations, BSS boundaries and
lifetime conflicts. Staging and scratch are temporary; they are not additional
resident copies of the expanded main image.

## Compressed-code table at ROM 0x7DF0

`boot_overlay_table` is an array of 27 eight-byte `BootRomRange` records at
CPU 0x800071F0, containing big-endian absolute ROM start and exclusive end
offsets. Destinations and expanded lengths are supplied by callers, not stored
in this table. Entry 0 spans ROM 0xA94D80–0xAB5800 and expands to main.
Entries 1 and 2 start at table ROM offsets 0x7DF8 and 0x7E00 and describe the
two executable overlays. The remaining 24 entries describe eleven byte-table
payloads and thirteen packed graphics entries, including a duplicate graphics
stream. The extraction names `ovl_*` do not imply executable code.

Each stream has a two-byte 0x1172 prefix followed by raw DEFLATE, with zero
padding to a 16-byte ROM boundary. There is no ordinary gzip header or trailer.
The 16-byte record after main at ROM 0xAB5800 is outside its table range.
[compression.md](compression.md) documents byte-exact stream reproduction.

## Inflate implementation

The code follows gzip 1.2.4 `inflate.c`. Names `huft`, `huft_build`,
`inflate_codes`, `inflate_stored`, `inflate_fixed`, `inflate_dynamic`,
`inflate_block`, `inflate`, `bb`, `bk`, `wp`, `hufts`, `border`, `cplens`,
`cplext`, `cpdist`, `cpdext`, `mask_bits`, `lbits` and `dbits` follow that
reference. Single-letter algorithm locals are retained where they correspond
to the reference; their types and declaration order preserve matching.

`boot_inflate` installs input/output/scratch pointers, skips the two-byte
prefix, and returns the expanded byte count. `bb` holds buffered bits, `bk`
the number available, and `wp` the output position. `inflate_inptr` indexes
the compressed input. Each block resets `hufts`, the number of eight-byte
`huft` entries allocated from caller scratch. A table entry contains an
operation/extra-bit count, consumed-bit count, and a union of decoded value
or child-table pointer.

Stored, fixed-Huffman and dynamic-Huffman blocks are supported. The dynamic
path reads lengths in gzip's `border` order and builds literal/length and
distance tables. Output goes directly into contiguous destination memory;
there is no gzip sliding-window flush/wrap. Nonoverlapping copies use memcpy,
while overlapping backreferences use a byte loop. Allocation uses the scratch
pool instead of malloc/free. Several gzip invalid-input checks are absent,
including stored-length complement validation; this is the original trusted
ROM-data decoder, not a general-purpose validated decompression API.

`boot_decode_backrefs` is a separate compact byte/backreference decoder, not
a DEFLATE block handler: zero control emits a literal; other controls encode
a length of 1–8 bytes and a backwards distance.

## Game function list

| Address | Name | Purpose |
|---|---|---|
| 0x80000450 | `boot_start` | Initialize SDK and launch idle thread |
| 0x800004AC | `boot_idle_thread` | Initialize PI, launch main loader, become idle |
| 0x80000520 | `boot_load_main` | Clear RAM, DMA/inflate main, enter main |
| 0x800005EC | `boot_decode_backrefs` | Decode compact literals/backreferences |
| 0x800006B0 | `boot_init_pi` | Initialize PI manager and completion queue |
| 0x800006FC | `boot_init_dma_events` | Subscribe DMA pacing queue to retrace |
| 0x80000740 | `boot_dma` | Blocking PI transfer |
| 0x800007B4 | `boot_dma_chunked` | Retrace-paced PI transfer |
| 0x80000900 | `boot_inflate` | Install stream pointers and decode 0x1172 payload |
| 0x80000960 | `huft_build` | Build Huffman lookup tables in scratch |
| 0x80000FA0 | `inflate_codes` | Decode Huffman literals and backreferences |
| 0x80001410 | `inflate_stored` | Decode uncompressed DEFLATE block |
| 0x80001564 | `inflate_fixed` | Build and decode fixed-Huffman block |
| 0x800016CC | `inflate_dynamic` | Read and decode dynamic-Huffman block |
| 0x80001BF0 | `inflate_block` | Read final/type bits and dispatch block |
| 0x80001D10 | `inflate` | Decode complete DEFLATE stream |
| 0x80001DF0 | `boot_init_scheduler` | Initialize resident scheduler and VI/SP/DP queues |
| 0x80001EF4 | `boot_subscribe_retrace` | Register a retrace subscriber |
| 0x80001F2C | `boot_scheduler_thread` | Dispatch retrace, SP and DP events |
| 0x800022C0 | `boot_start_graphics_task` | Start or resume graphics SP task |
| 0x80002420 | `boot_schedule_graphics` | Dequeue graphics and schedule DP/SP work |
