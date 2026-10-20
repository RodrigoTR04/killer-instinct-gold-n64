# T-084 / FU-13 boot readability — sol-B28

Changes are uncommitted for lead review. The SDK implementation, main/overlay
implementation, build flags, YAML layout and status.csv are untouched. The only
main source changes are three boot API renames in declarations and calls,
required to keep all users consistent with the renamed resident functions.

## Changes

- Added include/boot.h with shared game interfaces, gzip state/table declarations,
  an eight-byte huft, ROM-bound pair records, PI DMA messages, and scheduler task
  fields with the original 0x10/0x18/0x58/0x5C offsets.
- Startup uses named ROM range members. DMA helpers use descriptive locals and
  PI message records. The inflate wrapper uses shared pointer types instead of
  conflicting scalar declarations. Huffman algorithm names follow gzip 1.2.4;
  reference-local names and declaration order are retained for direct comparison.
- Scheduler accesses task/framebuffer/completion fields through BootTask members
  and uses named event/subscriber locals. Unknown task bytes remain opaque.
- Added docs/boot.md with startup flow, scheduler behavior, memory map, table
  format, decoder differences and all 21 eligible functions.

## Renames (old → new)

| Old | New |
|---|---|
| `func_80000450` | `boot_start` |
| `func_800004AC` | `boot_idle_thread` |
| `func_80000520` | `boot_load_main` |
| `func_800005EC` | `boot_decode_backrefs` |
| `func_800006B0` | `boot_init_pi` |
| `func_800006FC` | `boot_init_dma_events` |
| `func_80000960` | `huft_build` |
| `func_80000FA0` | `inflate_codes` |
| `func_80001410` | `inflate_stored` |
| `func_80001564` | `inflate_fixed` |
| `func_800016CC` | `inflate_dynamic` |
| `func_80001BF0` | `inflate_block` |
| `func_80001D10` | `inflate` |
| `func_80001DF0` | `boot_init_scheduler` |
| `func_80001EF4` | `boot_subscribe_retrace` |
| `func_80001F2C` | `boot_scheduler_thread` |
| `func_800022C0` | `boot_start_graphics_task` |
| `func_80002420` | `boot_schedule_graphics` |
| `D_8000BF80` | `inflate_input` |
| `D_8000BF84` | `inflate_output` |
| `D_8000BF88` | `inflate_inptr` |
| `D_8000BF8C` | `wp` |
| `D_8000BF90` | `inflate_huft_pool` |
| `D_8000BF94` | `bb` |
| `D_8000BF98` | `bk` |
| `D_8000BF9C` | `hufts` |
| `D_80006560` | `border` |
| `D_80006574` | `cplens` |
| `D_800065B4` | `cplext` |
| `D_800065D4` | `cpdist` |
| `D_80006610` | `cpdext` |
| `D_80006630` | `mask_bits` |
| `D_80006654` | `lbits` |
| `D_80006658` | `dbits` |
| `D_800071F0` | `boot_overlay_table` |
| `D_80006678` | `boot_graphics_task` |
| `D_8000667C` | `boot_audio_task` |

## Matching constraints and reverted attempts

The original signed fixed-Huffman loop index, local order, event switch and
64-bit osDpSetNextBuffer second argument are retained. Unknown SDK storage
continues to use loose declarations where giving it a new type would require
changing the SDK interface. No inline assembly, register binding, encoded
instructions, padding or compiler-flag changes were introduced.

A link failure after renaming boot_start came from the retained generated
asm/boot_entry.s still naming func_80000450. Removing that generated file and
extracting again fixed it; no source alias or linker workaround was added.
The final clean build regenerates it naturally.

## Additional scheduler/queue renames

| Old | New |
|---|---|
| `D_8000CF50` | `boot_graphics_queue` |
| `D_8000CF68` | `boot_audio_queue` |
| `D_8000CF80` | `boot_scheduler_queue` |
| `D_8000D180` | `boot_retrace_subscribers` |
| `D_8000D18C` | `boot_retrace_subscriber_count` |
| `D_8000D190` | `boot_next_framebuffer` |
| `D_8000D194` | `boot_audio_running` |
| `D_8000D195` | `boot_graphics_state` |
| `D_8000D196` | `boot_dp_state` |
| `D_8000D197` | `boot_graphics_sp_active` |
| `D_8000D198` | `boot_swap_ready` |
| `D_8000D199` | `boot_graphics_resume_count` |
| `D_8000BF18` | `boot_pi_completion_queue` |
| `D_8000BF50` | `boot_dma_retrace_queue` |

## Final validation

Each of the five game TUs was rebuilt and the complete ROM compared after its
cleanup (`/tmp/t084-tu1.log` through `/tmp/t084-tu5.log`). All five passed.
No readability change had to be reverted for code generation. The final shared
header/declaration and scheduler-state naming pass also passed the required
`make clean && make extract && make all && make progress` (MAKEFLAGS=-j4).

- ROM SHA1: ba52e91b44450c548467044b26951353dc491e04.
- main SHA1: 81736d32e8cda8f399b319a49250dff972b81af8.
- ovl_7DF8 SHA1: ea830aae50ff1422da60d4b7fdbfc29f03b1be39.
- ovl_7E00 SHA1: 2b01138a290212b9d886981e1196f7b6fb45ecdb.
- Boot remains 21/21 eligible functions, 8,468/8,468 bytes at T4.
- git diff --check passes. No status.csv, SDK source, overlay implementation,
  Makefile or YAML changes. Generated cross-image undefined-symbol scripts
  reflect the renamed resident exports. Generated progress documents have no diff.
- Prerequisites are local symlinks to the lead checkout; ROMs were neither
  copied nor added to git. No commits were made.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 70,556 (22.11%) | 70,556 (22.11%) | 0 | 272 | 0 | 290 | 437 (138,092) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 173,204 | 44,288 (25.57%) | 44,288 (25.57%) | 0 | 126 | 0 | 164 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 17,800 (12.95%) | 17,800 (12.95%) | 0 | 146 | 0 | 105 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
