# T-005: CPU libultra identification and function inventories

Target: KI Gold US 1.0, SHA1 `ba52e91b44450c548467044b26951353dc491e04`.
Research performed 2026-10-18. No commits; ROM read-only; decompression in memory.

## Conclusion and confidence

**The CPU library is an early, SM64-US-compatible libultra lineage. The exact SDK
revision letter remains unresolved.** High confidence in that binary lineage;
medium confidence in a **pre-2.0I** release family (D–H remain open rather than
being individually identified). Do not label this ROM 2.0G, I, or J on present evidence.
The graphics microcode's 2.0D string remains independent evidence about RSP code.

Machine-readable version probes: [`libultra_version.json`](../tools/analysis/data/libultra_version.json).

Two large, version-sensitive anchors provide substantially stronger evidence
than the earlier ABI guesses:

| KI region | Reference | Result |
|---|---|---|
| `80002590–800027C0`, 560 bytes | SM64 `VERSION_US`, `lib/src/osInitialize.c`, IDO 5.3 `-O1 -mips2` | Full function relocation-masked match |
| `80003DA0–80004610`, 2160 bytes | SM64 `VERSION_US`, `lib/asm/__osExceptionPreamble.s`, GNU MIPS assembler `-mips3 -32` | Entire text section relocation-masked match, including exception handlers, queue/context-switch helpers and alignment |
| Same initialize region | ultralib 2.0I final-ROM build, 652-byte function | **Does not match**; I includes the additional TV-type / `osViClock` initialization |
| Same exception region | ultralib 2.0I final-ROM build, 2320-byte text section | **Does not match**; the KI block instead matches SM64 US in full |

The KI initialize reads cartridge header offset 4, masks low four bits, computes
clock × 3/4, and returns after cold-reset NMI-buffer clearing. It has neither
the I TV-clock tail nor the J PI-domain speed setup / unmap-all-TLB path.
[ultralib's versioned initialize source](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/os/initialize.c)
explicitly distinguishes the pre-J header-clock path from J and later.
[SM64's source](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osInitialize.c)
distinguishes US from EU/SH/CN additions and reproduces the KI function.

**Why no exact letter:** neither anchor is accompanied by an independently
version-labelled D/E/F/G/H archive in this research. SM64 US is a concrete binary
reference, not itself proof of an SDK release label. Several later I routines
also match KI exactly; shared unchanged functions cannot establish I. ultralib's
[compatibility matrix](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/README.md#compatibility)
does not promise matching G/H builds. A trial G build of its current source uses
the same later initialize body and is therefore **not a valid G exclusion**.
A locally modified/mixed library remains possible; matching these anchors does
not prove every object came from one archive.

`osPiRawStartDma` is the historical public name used by the matching SM64
reference; the current ultralib C source spells its implementation
`__osPiRawStartDma`. At `800046F0`, the routine is **osPiRawReadIo**: it loads
from cartridge space and writes through `a1`. GoldenEye's `pirawwrite.s` labels
those same words `osPiRawWriteIo`; that reference label was rejected.
Likewise GoldenEye aliases `bzero` as `memset`; KI's two-argument routine is
`bzero`, not the three-argument C `memset`.

## Inventory scope and boundary rules

- **boot: 120 CPU entries; 98 SDK entries named; 22 entry/game/unknown entries.** See [`boot_functions.csv`](../tools/analysis/data/boot_functions.csv).
- **main: 472 CPU entries; 169 SDK entries named; 303 entry/game/unknown entries.** See [`main_functions.csv`](../tools/analysis/data/main_functions.csv).

Boot covers the complete verified text `[80000400,80006560)` with **audited
entry boundaries**. Main covers CPU text `[8000F960,80042710)`; game-function
boundaries there are **candidates**, not a claim of a complete original symbol
table. The requested scan through `80042930` is retained as an explicit
`rsp_data` row ending `80042940`, excluded from CPU function counts.

Important correction to the prior coarse main bound: `alFxPull` at `800423C8`
is a full 832-byte SDK match, returning at `80042700` with its delay slot at
`80042704`. Alignment follows through `8004270F`. At `80042710` starts RSP code:
`j 0x04001068`, DMA writes to SP CP0 registers 0/1/2, polling register 6, and
later jumps to RSP IMEM. Interpreting these as R4300 CP0 registers creates
nonsensical CPU operations. This is an ISA boundary observation, not a claim
that all later expanded main bytes have been classified.

CSV end addresses are exclusive; size includes padding up to the next entry.
Thus an exact matched body may be shorter than its CSV extent. Exception
preamble and separately callable assembly helpers are individual entries;
`counter`, `cart`, `rcp`, `prenmi`, `sw1`, `sw2`, `panic` and redispatch labels
remain internal to `__osException`. The exception block as a whole is matched.
There is no separate function at a delayed stack decrement such as `80000924`
or `80001C04`; their entries are `80000900` and `80001BF0`. The entry stub's
stack setup in a jump delay slot at `80000430` is likewise not a function.

`asm_candidate` marks actual CP0 instructions / `eret` / k0/k1 register use,
not a compiler verdict. Cache routines and other handwritten assembly can have
`no` because they use none of those instructions. All boot SDK-looking entries
have names; the 21 unnamed non-entry boot routines are loader, inflate and
scheduler/game code, rather than evidence of unidentified SDK objects.

## Match evidence

Every named entry is recorded below and in
[`libultra_matches.json`](../tools/analysis/data/libultra_matches.json).
`exact` means all compared words match; `masked` masks **only ELF relocation
fields** (or explicitly annotated relocations in GoldenEye assembly), retaining
registers, opcode order, nonrelocated branches and ordinary constants. Whole assembly text
matches include alignment. `structural` is reserved for short accessors/stubs
whose semantics and object/caller context establish the name; these cannot
identify a version. Ambiguous templates were resolved by call relocation
identities and context, rather than choosing the first match. In particular PI
and SI access queues, current/next VI getters and gu wrappers have identical
relocation-masked templates.

Reference sets (commit pinned):

- `sm64-us`: [n64decomp/sm64 `9921382a68bb`](https://github.com/n64decomp/sm64/tree/9921382a68bb0c865e5e45eb594d9c64db59b1af).
- `ultralib-I`: [decompals/ultralib `e24c836796df`](https://github.com/decompals/ultralib/tree/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd).
- `007`: [n64decomp/007 `c4356466796c`](https://github.com/n64decomp/007/tree/c4356466796c697dfd298010b9bed261f9ed8c6a).

### Boot named SDK entries

| Address | Name | Match | Reference source |
|---|---|---|---|
| `80002590` | `osInitialize` | masked | [sm64-us: lib/src/osInitialize.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osInitialize.c) |
| `800027C0` | `osCreateThread` | masked | [sm64-us: lib/src/osCreateThread.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osCreateThread.c) |
| `80002910` | `osStartThread` | masked | [sm64-us: lib/src/osStartThread.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osStartThread.c) |
| `80002A60` | `osSetThreadPri` | masked | [sm64-us: lib/src/osSetThreadPri.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osSetThreadPri.c) |
| `80002B80` | `bzero` | exact | [sm64-us: lib/asm/bzero.s](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/asm/bzero.s) |
| `80002C20` | `osInvalICache` | exact | [sm64-us: lib/asm/osInvalICache.s](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/asm/osInvalICache.s) |
| `80002CA0` | `osInvalDCache` | exact | [sm64-us: lib/asm/osInvalDCache.s](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/asm/osInvalDCache.s) |
| `80002D50` | `osCreatePiManager` | masked | [sm64-us: lib/src/osCreatePiManager.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osCreatePiManager.c) |
| `80002ED0` | `osCreateMesgQueue` | masked | [sm64-us: lib/src/osCreateMesgQueue.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osCreateMesgQueue.c) |
| `80002F00` | `osPiStartDma` | masked | [sm64-us: lib/src/osPiStartDma.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osPiStartDma.c) |
| `80003010` | `osRecvMesg` | masked | [sm64-us: lib/src/osRecvMesg.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osRecvMesg.c) |
| `80003150` | `memcpy` | exact | [ultralib-I: src/libc/string.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/libc/string.c) |
| `8000317C` | `strlen` | exact | [ultralib-I: src/libc/string.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/libc/string.c) |
| `800031A4` | `strchr` | exact | [ultralib-I: src/libc/string.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/libc/string.c) |
| `800031F0` | `osCreateViManager` | masked | [sm64-us: lib/src/osCreateViManager.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osCreateViManager.c) |
| `80003374` | `viMgrMain` | masked | [sm64-us: lib/src/osCreateViManager.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osCreateViManager.c) |
| `80003550` | `osSetEventMesg` | masked | [sm64-us: lib/src/osSetEventMesg.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osSetEventMesg.c) |
| `800035C0` | `osViSetEvent` | masked | [sm64-us: lib/src/osViSetEvent.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osViSetEvent.c) |
| `80003630` | `osSpTaskYield` | masked | [sm64-us: lib/src/osSpTaskYield.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osSpTaskYield.c) |
| `80003650` | `_VirtualToPhysicalTask` | masked | [sm64-us: lib/src/osSpTaskLoadGo.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osSpTaskLoadGo.c) |
| `8000376C` | `osSpTaskLoad` | masked | [sm64-us: lib/src/osSpTaskLoadGo.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osSpTaskLoadGo.c) |
| `800038CC` | `osSpTaskStartGo` | masked | [sm64-us: lib/src/osSpTaskLoadGo.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osSpTaskLoadGo.c) |
| `80003910` | `osSendMesg` | masked | [sm64-us: lib/src/osSendMesg.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osSendMesg.c) |
| `80003A60` | `osSpTaskYielded` | masked | [sm64-us: lib/src/osSpTaskYielded.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osSpTaskYielded.c) |
| `80003AE0` | `osViSwapBuffer` | masked | [sm64-us: lib/src/osViSwapBuffer.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osViSwapBuffer.c) |
| `80003B30` | `osViGetCurrentFramebuffer` | masked | [ultralib-I: src/io/vigetcurrframebuf.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/io/vigetcurrframebuf.c) |
| `80003B70` | `osViGetNextFramebuffer` | masked | [ultralib-I: src/io/vigetnextframebuf.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/io/vigetnextframebuf.c) |
| `80003BB0` | `osDpSetNextBuffer` | masked | [ultralib-I: src/io/dpsetnextbuf.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/io/dpsetnextbuf.c) |
| `80003C60` | `osViSetMode` | masked | [sm64-us: lib/src/osViSetMode.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osViSetMode.c) |
| `80003CD0` | `__osSetSR` | exact | [sm64-us: lib/asm/__osSetSR.s](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/asm/__osSetSR.s) |
| `80003CE0` | `__osGetSR` | exact | [sm64-us: lib/asm/__osGetSR.s](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/asm/__osGetSR.s) |
| `80003CF0` | `__osSetFpcCsr` | exact | [sm64-us: lib/asm/__osSetFpcCsr.s](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/asm/__osSetFpcCsr.s) |
| `80003D00` | `__osSiRawReadIo` | masked | [sm64-us: lib/src/__osSiRawReadIo.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/__osSiRawReadIo.c) |
| `80003D50` | `__osSiRawWriteIo` | masked | [sm64-us: lib/src/__osSiRawWriteIo.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/__osSiRawWriteIo.c) |
| `80003DA0` | `__osExceptionPreamble` | masked | [sm64-us: lib/asm/__osExceptionPreamble.s](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/asm/__osExceptionPreamble.s) |
| `80003DB0` | `__osException` | masked | [sm64-us: lib/asm/__osExceptionPreamble.s](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/asm/__osExceptionPreamble.s) |
| `800042F8` | `send_mesg` | masked | [ultralib-I: src/os/exceptasm.s](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/os/exceptasm.s) |
| `800043AC` | `handle_CpU` | exact | [ultralib-I: src/os/exceptasm.s](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/os/exceptasm.s) |
| `800043E0` | `__osEnqueueAndYield` | masked | [sm64-us: lib/asm/__osExceptionPreamble.s](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/asm/__osExceptionPreamble.s) |
| `80004470` | `__osEnqueueThread` | exact | [ultralib-I: src/os/exceptasm.s](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/os/exceptasm.s) |
| `800044B8` | `__osPopThread` | masked | [sm64-us: lib/asm/__osExceptionPreamble.s](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/asm/__osExceptionPreamble.s) |
| `800044C8` | `__osDispatchThread` | masked | [sm64-us: lib/asm/__osExceptionPreamble.s](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/asm/__osExceptionPreamble.s) |
| `80004608` | `__osCleanupThread` | masked | [sm64-us: lib/asm/__osExceptionPreamble.s](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/asm/__osExceptionPreamble.s) |
| `80004610` | `osWritebackDCache` | exact | [sm64-us: lib/asm/osWritebackDCache.s](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/asm/osWritebackDCache.s) |
| `80004690` | `osMapTLBRdb` | exact | [sm64-us: lib/asm/osMapTLBRdb.s](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/asm/osMapTLBRdb.s) |
| `800046F0` | `osPiRawReadIo` | masked | [sm64-us: lib/src/osPiRawReadIo.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osPiRawReadIo.c) |
| `80004750` | `__ull_rshift` | exact | [sm64-us: lib/src/math/llmuldiv.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/math/llmuldiv.c) |
| `8000477C` | `__ull_rem` | exact | [sm64-us: lib/src/math/llmuldiv.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/math/llmuldiv.c) |
| `800047B8` | `__ull_div` | exact | [sm64-us: lib/src/math/llmuldiv.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/math/llmuldiv.c) |
| `800047F4` | `__ll_lshift` | exact | [sm64-us: lib/src/math/llmuldiv.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/math/llmuldiv.c) |
| `80004820` | `__ll_rem` | exact | [sm64-us: lib/src/math/llmuldiv.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/math/llmuldiv.c) |
| `8000485C` | `__ll_div` | exact | [sm64-us: lib/src/math/llmuldiv.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/math/llmuldiv.c) |
| `800048B8` | `__ll_mul` | exact | [sm64-us: lib/src/math/llmuldiv.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/math/llmuldiv.c) |
| `800048E8` | `__ull_divremi` | exact | [sm64-us: lib/src/math/llmuldiv.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/math/llmuldiv.c) |
| `80004948` | `__ll_mod` | exact | [sm64-us: lib/src/math/llmuldiv.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/math/llmuldiv.c) |
| `800049E4` | `__ll_rshift` | exact | [sm64-us: lib/src/math/llmuldiv.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/math/llmuldiv.c) |
| `80004A10` | `__osDisableInt` | exact | [sm64-us: lib/asm/__osDisableInt.s](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/asm/__osDisableInt.s) |
| `80004A30` | `__osRestoreInt` | exact | [sm64-us: lib/asm/__osRestoreInt.s](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/asm/__osRestoreInt.s) |
| `80004A50` | `__osDequeueThread` | exact | [sm64-us: lib/src/__osDequeueThread.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/__osDequeueThread.c) |
| `80004A90` | `__osPiCreateAccessQueue` | masked | [sm64-us: lib/src/__osPiCreateAccessQueue.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/__osPiCreateAccessQueue.c) |
| `80004AE0` | `__osPiGetAccess` | masked | [sm64-us: lib/src/__osPiCreateAccessQueue.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/__osPiCreateAccessQueue.c) |
| `80004B24` | `__osPiRelAccess` | masked | [sm64-us: lib/src/__osPiCreateAccessQueue.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/__osPiCreateAccessQueue.c) |
| `80004B50` | `osGetThreadPri` | masked | [sm64-us: lib/src/osGetThreadPri.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osGetThreadPri.c) |
| `80004B70` | `osPiRawStartDma` | masked | [sm64-us: lib/src/osPiRawStartDma.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osPiRawStartDma.c) |
| `80004C50` | `__osDevMgrMain` | masked | [sm64-us: lib/src/__osDevMgrMain.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/__osDevMgrMain.c) |
| `80004DD0` | `osJamMesg` | masked | [sm64-us: lib/src/osJamMesg.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osJamMesg.c) |
| `80004F20` | `osPiGetCmdQueue` | masked | [sm64-us: lib/src/osPiGetCmdQueue.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osPiGetCmdQueue.c) |
| `80004F50` | `__osTimerServicesInit` | masked | [sm64-us: lib/src/osTimer.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osTimer.c) |
| `80004FDC` | `__osTimerInterrupt` | masked | [sm64-us: lib/src/osTimer.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osTimer.c) |
| `80005154` | `__osSetTimerIntr` | masked | [sm64-us: lib/src/osTimer.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osTimer.c) |
| `800051C8` | `__osInsertTimer` | masked | [sm64-us: lib/src/osTimer.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osTimer.c) |
| `80005350` | `__osViInit` | masked | [sm64-us: lib/src/__osViInit.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/__osViInit.c) |
| `80005480` | `__osViGetCurrentContext` | structural | [ultralib-I: src/io/vigetcurrcontext.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/io/vigetcurrcontext.c) |
| `80005490` | `__osViSwapContext` | masked | [sm64-us: lib/src/__osViSwapContext.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/__osViSwapContext.c) |
| `800057F0` | `osGetCount` | exact | [sm64-us: lib/asm/osGetCount.s](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/asm/osGetCount.s) |
| `80005800` | `__osSpSetStatus` | structural | [ultralib-I: src/io/spsetstat.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/io/spsetstat.c) |
| `80005810` | `bcopy` | exact | [sm64-us: lib/asm/bcopy.s](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/asm/bcopy.s) |
| `80005B20` | `osVirtualToPhysical` | masked | [sm64-us: lib/src/osVirtualToPhysical.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osVirtualToPhysical.c) |
| `80005BA0` | `__osSpSetPc` | exact | [sm64-us: lib/src/__osSpSetPc.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/__osSpSetPc.c) |
| `80005BE0` | `__osSpRawStartDma` | masked | [sm64-us: lib/src/__osSpRawStartDma.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/__osSpRawStartDma.c) |
| `80005C70` | `__osSpDeviceBusy` | exact | [sm64-us: lib/src/__osSpDeviceBusy.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/__osSpDeviceBusy.c) |
| `80005CA0` | `__osSpGetStatus` | structural | [ultralib-I: src/io/spgetstat.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/io/spgetstat.c) |
| `80005CB0` | `__osDpDeviceBusy` | exact | [ultralib-I: src/io/dp.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/io/dp.c) |
| `80005CE0` | `__osSiDeviceBusy` | exact | [sm64-us: lib/src/__osSiDeviceBusy.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/__osSiDeviceBusy.c) |
| `80005D10` | `u32_to_string` | exact | [sm64-us: lib/src/kdebugserver.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/kdebugserver.c) |
| `80005D40` | `string_to_u32` | exact | [sm64-us: lib/src/kdebugserver.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/kdebugserver.c) |
| `80005D98` | `send_packet` | masked | [sm64-us: lib/src/kdebugserver.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/kdebugserver.c) |
| `80005E58` | `send` | masked | [sm64-us: lib/src/kdebugserver.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/kdebugserver.c) |
| `80005F30` | `process_command_memory` | masked | [sm64-us: lib/src/kdebugserver.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/kdebugserver.c) |
| `80005F7C` | `process_command_register` | masked | [sm64-us: lib/src/kdebugserver.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/kdebugserver.c) |
| `80005FA8` | `kdebugserver` | masked | [sm64-us: lib/src/kdebugserver.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/kdebugserver.c) |
| `80006190` | `__osSyncPutChars` | masked | [sm64-us: lib/src/__osSyncPutChars.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/__osSyncPutChars.c) |
| `800062C0` | `osSetIntMask` | masked | [sm64-us: lib/asm/osSetIntMask.s](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/asm/osSetIntMask.s) |
| `80006320` | `osDestroyThread` | masked | [sm64-us: lib/src/osDestroyThread.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osDestroyThread.c) |
| `80006420` | `__osSetCompare` | exact | [sm64-us: lib/asm/__osSetCompare.s](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/asm/__osSetCompare.s) |
| `80006430` | `__osProbeTLB` | exact | [sm64-us: lib/asm/__osProbeTLB.s](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/asm/__osProbeTLB.s) |
| `800064F0` | `__osGetCause` | exact | [sm64-us: lib/asm/__osGetCause.s](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/asm/__osGetCause.s) |
| `80006500` | `__osAtomicDec` | masked | [sm64-us: lib/src/__osAtomicDec.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/__osAtomicDec.c) |

### Main named SDK entries

| Address | Name | Match | Reference source |
|---|---|---|---|
| `80032C30` | `osViSetSpecialFeatures` | masked | [sm64-us: lib/src/osViSetSpecialFeatures.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osViSetSpecialFeatures.c) |
| `80032DF0` | `guPerspectiveF` | masked | [sm64-us: lib/src/guPerspectiveF.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/guPerspectiveF.c) |
| `80033020` | `guPerspective` | masked | [sm64-us: lib/src/guPerspectiveF.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/guPerspectiveF.c) |
| `80033080` | `guRandom` | masked | [ultralib-I: src/gu/random.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/gu/random.c) |
| `8003381C` | `guLookAtHilite` | masked | [ultralib-I: src/gu/lookathil.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/gu/lookathil.c) |
| `800338E0` | `guTranslateF` | masked | [sm64-us: lib/src/guTranslateF.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/guTranslateF.c) |
| `80033928` | `guTranslate` | masked | [sm64-us: lib/src/guTranslateF.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/guTranslateF.c) |
| `80033980` | `guRotateF` | masked | [sm64-us: lib/src/guRotateF.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/guRotateF.c) |
| `80033B14` | `guRotate` | masked | [sm64-us: lib/src/guRotateF.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/guRotateF.c) |
| `80033B70` | `guLookAtReflectF` | masked | [sm64-us: lib/src/guLookAtRef.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/guLookAtRef.c) |
| `80033FB0` | `guLookAtReflect` | masked | [sm64-us: lib/src/guLookAtRef.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/guLookAtRef.c) |
| `80034030` | `guScaleF` | masked | [sm64-us: lib/src/guScaleF.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/guScaleF.c) |
| `80034084` | `guScale` | masked | [sm64-us: lib/src/guScaleF.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/guScaleF.c) |
| `800340D0` | `sqrtf` | exact | [sm64-us: lib/asm/sqrtf.s](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/asm/sqrtf.s) |
| `800340E0` | `memcpy` | exact | [ultralib-I: src/libc/string.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/libc/string.c) |
| `8003410C` | `strlen` | exact | [ultralib-I: src/libc/string.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/libc/string.c) |
| `80034134` | `strchr` | exact | [ultralib-I: src/libc/string.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/libc/string.c) |
| `80035D30` | `osContStartQuery` | masked | [ultralib-I: src/io/contquery.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/io/contquery.c) |
| `80035DB4` | `osContGetQuery` | masked | [ultralib-I: src/io/contquery.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/io/contquery.c) |
| `80036730` | `osEepromProbe` | masked | [sm64-us: lib/src/osEepromProbe.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osEepromProbe.c) |
| `800367A0` | `osEepromLongWrite` | masked | [sm64-us: lib/src/osEepromLongWrite.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osEepromLongWrite.c) |
| `800368E0` | `osEepromLongRead` | masked | [sm64-us: lib/src/osEepromLongRead.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osEepromLongRead.c) |
| `80036A20` | `osViBlack` | masked | [sm64-us: lib/src/osViBlack.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osViBlack.c) |
| `80036A90` | `sinf` | masked | [sm64-us: lib/src/math/sinf.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/math/sinf.c) |
| `80036C50` | `cosf` | masked | [sm64-us: lib/src/math/cosf.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/math/cosf.c) |
| `80036DC0` | `osWritebackDCacheAll` | exact | [sm64-us: lib/asm/osWritebackDCacheAll.s](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/asm/osWritebackDCacheAll.s) |
| `80036DF0` | `guRotateRPYF` | masked | [ultralib-I: src/gu/rotaterpy.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/gu/rotaterpy.c) |
| `80036F3C` | `guRotateRPY` | masked | [ultralib-I: src/gu/rotaterpy.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/gu/rotaterpy.c) |
| `80036F90` | `guMtxXFMF` | exact | [ultralib-I: src/gu/mtxcatf.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/gu/mtxcatf.c) |
| `80037030` | `guMtxCatF` | exact | [ultralib-I: src/gu/mtxcatf.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/gu/mtxcatf.c) |
| `800371A0` | `guMtxF2L` | exact | [sm64-us: lib/src/guMtxF2L.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/guMtxF2L.c) |
| `800372A0` | `guMtxIdentF` | exact | [sm64-us: lib/src/guMtxF2L.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/guMtxF2L.c) |
| `80037328` | `guMtxIdent` | masked | [sm64-us: lib/src/guMtxF2L.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/guMtxF2L.c) |
| `80037358` | `guMtxL2F` | exact | [sm64-us: lib/src/guMtxF2L.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/guMtxF2L.c) |
| `80037410` | `osUnmapTLB` | exact | [ultralib-I: src/os/unmaptlb.s](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/os/unmaptlb.s) |
| `80037450` | `osMapTLB` | exact | [sm64-us: lib/asm/osMapTLB.s](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/asm/osMapTLB.s) |
| `80037510` | `guOrthoF` | masked | [sm64-us: lib/src/guOrthoF.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/guOrthoF.c) |
| `80037664` | `guOrtho` | masked | [sm64-us: lib/src/guOrthoF.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/guOrthoF.c) |
| `800376D0` | `alHeapInit` | exact | [ultralib-I: src/audio/heapinit.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/heapinit.c) |
| `80037710` | `alHeapDBAlloc` | exact | [ultralib-I: src/audio/heapalloc.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/heapalloc.c) |
| `80037874` | `alBnkfNew` | masked | [sm64-us: lib/src/alBnkfNew.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/alBnkfNew.c) |
| `80037978` | `alSeqFileNew` | exact | [sm64-us: lib/src/alBnkfNew.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/alBnkfNew.c) |
| `800379C0` | `__CSPPostNextSeqEvent` | masked | [ultralib-I: src/audio/csplayer.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/csplayer.c) |
| `80038A80` | `alCSPNew` | masked | [ultralib-I: src/audio/csplayer.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/csplayer.c) |
| `80038BF0` | `alCSPSetBank` | masked | [ultralib-I: src/audio/cspsetbank.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/cspsetbank.c) |
| `80038C30` | `alCSPGetState` | structural | [ultralib-I: src/audio/cspgetstate.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/cspgetstate.c) |
| `80038C40` | `alCSPPlay` | masked | [ultralib-I: src/audio/cspplay.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/cspplay.c) |
| `80038C70` | `alCSPStop` | masked | [ultralib-I: src/audio/cspstop.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/cspstop.c) |
| `80038CA0` | `alCSeqGetLoc` | exact | [ultralib-I: src/audio/cseq.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/cseq.c) |
| `80038D40` | `alCSeqSetLoc` | exact | [ultralib-I: src/audio/cseq.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/cseq.c) |
| `80038F04` | `alCSeqNextEvent` | masked | [ultralib-I: src/audio/cseq.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/cseq.c) |
| `800391FC` | `alCSeqNew` | masked | [ultralib-I: src/audio/cseq.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/cseq.c) |
| `80039310` | `alCSeqNewMarker` | masked | [ultralib-I: src/audio/cseq.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/cseq.c) |
| `8003947C` | `alCSeqGetTicks` | structural | [ultralib-I: src/audio/cseq.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/cseq.c) |
| `80039484` | `alCSeqSecToTicks` | masked | [ultralib-I: src/audio/cseq.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/cseq.c) |
| `80039580` | `alCSeqTicksToSec` | masked | [ultralib-I: src/audio/cseq.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/cseq.c) |
| `800395EC` | `__alCSeqNextDelta` | exact | [ultralib-I: src/audio/cseq.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/cseq.c) |
| `80039760` | `alCSPSetSeq` | masked | [ultralib-I: src/audio/cspsetseq.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/cspsetseq.c) |
| `800397A0` | `alCSPSetVol` | masked | [ultralib-I: src/audio/cspsetvol.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/cspsetvol.c) |
| `800397E0` | `osAiSetFrequency` | masked | [sm64-us: lib/src/osAiSetFrequency.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osAiSetFrequency.c) |
| `80039940` | `alUnlink` | exact | [ultralib-I: src/audio/sl.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/sl.c) |
| `80039970` | `alLink` | exact | [ultralib-I: src/audio/sl.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/sl.c) |
| `80039994` | `alClose` | masked | [ultralib-I: src/audio/sl.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/sl.c) |
| `800399CC` | `alInit` | masked | [ultralib-I: src/audio/sl.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/sl.c) |
| `80039A00` | `osAiSetNextBuffer` | masked | [sm64-us: lib/src/osAiSetNextBuffer.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osAiSetNextBuffer.c) |
| `80039AB0` | `osAiGetLength` | structural | [ultralib-I: src/io/aigetlen.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/io/aigetlen.c) |
| `80039AC8` | `_timeToSamples` | masked | [ultralib-I: src/audio/synthesizer.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/synthesizer.c) |
| `80039B20` | `_freePVoice` | masked | [ultralib-I: src/audio/synthesizer.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/synthesizer.c) |
| `80039B58` | `_collectPVoices` | masked | [ultralib-I: src/audio/synthesizer.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/synthesizer.c) |
| `80039BB8` | `__freeParam` | masked | [ultralib-I: src/audio/synthesizer.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/synthesizer.c) |
| `80039BD0` | `__allocParam` | masked | [ultralib-I: src/audio/synthesizer.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/synthesizer.c) |
| `80039E90` | `alSynNew` | masked | [ultralib-I: src/audio/synthesizer.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/synthesizer.c) |
| `8003A190` | `osContInit` | masked | [sm64-us: lib/src/osContInit.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osContInit.c) |
| `8003A38C` | `__osContGetInitData` | masked | [sm64-us: lib/src/osContInit.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osContInit.c) |
| `8003A45C` | `__osPackRequestData` | masked | [sm64-us: lib/src/osContInit.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osContInit.c) |
| `8003A550` | `osContStartReadData` | masked | [sm64-us: lib/src/osContStartReadData.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osContStartReadData.c) |
| `8003A614` | `osContGetReadData` | masked | [sm64-us: lib/src/osContStartReadData.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osContStartReadData.c) |
| `8003A6BC` | `__osPackReadData` | masked | [sm64-us: lib/src/osContStartReadData.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osContStartReadData.c) |
| `8003A7B0` | `alEvtqFlushType` | masked | [ultralib-I: src/audio/event.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/event.c) |
| `8003A85C` | `alEvtqFlush` | masked | [ultralib-I: src/audio/event.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/event.c) |
| `8003A8CC` | `alEvtqPostEvent` | masked | [ultralib-I: src/audio/event.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/event.c) |
| `8003A9F0` | `alEvtqNextEvent` | masked | [ultralib-I: src/audio/event.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/event.c) |
| `8003AA7C` | `alEvtqNew` | masked | [ultralib-I: src/audio/event.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/event.c) |
| `8003AAF0` | `alSynAddPlayer` | masked | [ultralib-I: src/audio/synaddplayer.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/synaddplayer.c) |
| `8003AB40` | `_allocatePVoice` | masked | [ultralib-I: src/audio/synallocvoice.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/synallocvoice.c) |
| `8003AC28` | `alSynAllocVoice` | masked | [ultralib-I: src/audio/synallocvoice.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/synallocvoice.c) |
| `8003AD70` | `alSynSetVol` | masked | [ultralib-I: src/audio/synsetvol.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/synsetvol.c) |
| `8003AE10` | `alSynStartVoice` | masked | [ultralib-I: src/audio/synstartvoice.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/synstartvoice.c) |
| `8003AEA0` | `alSynSetPan` | masked | [ultralib-I: src/audio/synsetpan.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/synsetpan.c) |
| `8003AF30` | `alSynSetPitch` | masked | [ultralib-I: src/audio/synsetpitch.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/synsetpitch.c) |
| `8003AFC0` | `alSynSetFXMix` | masked | [ultralib-I: src/audio/synsetfxmix.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/synsetfxmix.c) |
| `8003B060` | `alSynStopVoice` | masked | [ultralib-I: src/audio/synstopvoice.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/synstopvoice.c) |
| `8003B0E0` | `alSynFreeVoice` | masked | [ultralib-I: src/audio/synfreevoice.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/synfreevoice.c) |
| `8003B190` | `alCents2Ratio` | masked | [ultralib-I: src/audio/cents2ratio.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/cents2ratio.c) |
| `8003B1E0` | `guNormalize` | masked | [sm64-us: lib/src/guNormalize.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/guNormalize.c) |
| `8003B270` | `__osSiCreateAccessQueue` | masked | [sm64-us: lib/src/__osSiCreateAccessQueue.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/__osSiCreateAccessQueue.c) |
| `8003B2C0` | `__osSiGetAccess` | masked | [sm64-us: lib/src/__osSiCreateAccessQueue.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/__osSiCreateAccessQueue.c) |
| `8003B304` | `__osSiRelAccess` | masked | [sm64-us: lib/src/__osSiCreateAccessQueue.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/__osSiCreateAccessQueue.c) |
| `8003B330` | `__osSiRawStartDma` | masked | [sm64-us: lib/src/__osSiRawStartDma.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/__osSiRawStartDma.c) |
| `8003C900` | `osEepromWrite` | masked | [sm64-us: lib/src/osEepromWrite.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osEepromWrite.c) |
| `8003CAB0` | `__osPackEepWriteData` | masked | [sm64-us: lib/src/osEepromWrite.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osEepromWrite.c) |
| `8003CBBC` | `__osEepStatus` | masked | [sm64-us: lib/src/osEepromWrite.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osEepromWrite.c) |
| `8003CDE0` | `osSetTimer` | masked | [sm64-us: lib/src/osSetTimer.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osSetTimer.c) |
| `8003CEC0` | `osEepromRead` | masked | [sm64-us: lib/src/osEepromRead.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osEepromRead.c) |
| `8003D0B0` | `__osPackEepReadData` | masked | [sm64-us: lib/src/osEepromRead.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osEepromRead.c) |
| `8003D1C0` | `__setInstChanState` | exact | [ultralib-I: src/audio/seqplayer.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/seqplayer.c) |
| `8003D214` | `__resetPerfChanState` | exact | [ultralib-I: src/audio/seqplayer.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/seqplayer.c) |
| `8003D294` | `__initFromBank` | masked | [ultralib-I: src/audio/seqplayer.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/seqplayer.c) |
| `8003D350` | `__vsDelta` | exact | [ultralib-I: src/audio/seqplayer.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/seqplayer.c) |
| `8003D374` | `__vsVol` | exact | [ultralib-I: src/audio/seqplayer.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/seqplayer.c) |
| `8003D3FC` | `__seqpReleaseVoice` | masked | [ultralib-I: src/audio/seqplayer.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/seqplayer.c) |
| `8003D528` | `__voiceNeedsNoteKill` | masked | [ultralib-I: src/audio/seqplayer.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/seqplayer.c) |
| `8003D5D0` | `__unmapVoice` | exact | [ultralib-I: src/audio/seqplayer.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/seqplayer.c) |
| `8003D640` | `__postNextSeqEvent` | masked | [ultralib-I: src/audio/seqplayer.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/seqplayer.c) |
| `8003D794` | `__vsPan` | exact | [ultralib-I: src/audio/seqplayer.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/seqplayer.c) |
| `8003D7DC` | `__lookupVoice` | exact | [ultralib-I: src/audio/seqplayer.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/seqplayer.c) |
| `8003D850` | `__mapVoice` | exact | [ultralib-I: src/audio/seqplayer.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/seqplayer.c) |
| `8003D8C0` | `__lookupSoundQuick` | exact | [ultralib-I: src/audio/seqplayer.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/seqplayer.c) |
| `8003E800` | `__seqpStopOsc` | masked | [ultralib-I: src/audio/seqplayer.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/seqplayer.c) |
| `8003E904` | `__initChanState` | masked | [ultralib-I: src/audio/seqplayer.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/seqplayer.c) |
| `8003E974` | `alSeqpNew` | masked | [ultralib-I: src/audio/seqplayer.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/seqplayer.c) |
| `8003EB00` | `alSynStartVoiceParams` | masked | [ultralib-I: src/audio/synstartvoiceparam.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/synstartvoiceparam.c) |
| `8003EBF0` | `alSynDelete` | structural | [ultralib-I: src/audio/syndelete.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/syndelete.c) |
| `8003EC00` | `__osAiDeviceBusy` | exact | [sm64-us: lib/src/__osAiDeviceBusy.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/__osAiDeviceBusy.c) |
| `8003EC30` | `alSaveNew` | masked | [ultralib-I: src/audio/drvrnew.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/drvrnew.c) |
| `8003EC74` | `alMainBusNew` | masked | [ultralib-I: src/audio/drvrnew.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/drvrnew.c) |
| `8003ECC8` | `alAuxBusNew` | masked | [ultralib-I: src/audio/drvrnew.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/drvrnew.c) |
| `8003ED1C` | `alResampleNew` | masked | [ultralib-I: src/audio/drvrnew.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/drvrnew.c) |
| `8003EDA4` | `alLoadNew` | masked | [ultralib-I: src/audio/drvrnew.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/drvrnew.c) |
| `8003EE4C` | `alEnvmixerNew` | masked | [ultralib-I: src/audio/drvrnew.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/drvrnew.c) |
| `8003EEF0` | `init_lpfilter` | exact | [ultralib-I: src/audio/drvrnew.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/drvrnew.c) |
| `8003F3B0` | `alSynAllocFX` | masked | [ultralib-I: src/audio/synallocfx.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/synallocfx.c) |
| `8003F450` | `alMainBusParam` | exact | [ultralib-I: src/audio/mainbus.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/mainbus.c) |
| `8003F480` | `alMainBusPull` | exact | [ultralib-I: src/audio/mainbus.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/mainbus.c) |
| `8003F5A0` | `alLoadParam` | masked | [ultralib-I: src/audio/load.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/load.c) |
| `8003F774` | `alRaw16Pull` | exact | [ultralib-I: src/audio/load.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/load.c) |
| `8003FC4C` | `alAdpcmPull` | masked | [ultralib-I: src/audio/load.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/load.c) |
| `800400F0` | `alResampleParam` | masked | [ultralib-I: src/audio/resample.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/resample.c) |
| `800401DC` | `alResamplePull` | masked | [ultralib-I: src/audio/resample.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/resample.c) |
| `800403F0` | `_ldexpf` | exact | [ultralib-I: src/audio/env.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/env.c) |
| `80040418` | `_frexpf` | exact | [ultralib-I: src/audio/env.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/env.c) |
| `80040504` | `alEnvmixerParam` | exact | [ultralib-I: src/audio/env.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/env.c) |
| `80040AFC` | `alEnvmixerPull` | masked | [ultralib-I: src/audio/env.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/env.c) |
| `80041050` | `alAuxBusParam` | exact | [ultralib-I: src/audio/auxbus.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/auxbus.c) |
| `80041080` | `alAuxBusPull` | exact | [ultralib-I: src/audio/auxbus.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/auxbus.c) |
| `80041160` | `alSaveParam` | exact | [ultralib-I: src/audio/save.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/save.c) |
| `80041194` | `alSavePull` | exact | [ultralib-I: src/audio/save.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/save.c) |
| `80041220` | `osGetTime` | masked | [sm64-us: lib/src/osGetTime.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/osGetTime.c) |
| `800412B0` | `alCopy` | exact | [ultralib-I: src/audio/copy.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/copy.c) |
| `80041330` | `__osContAddressCrc` | exact | [sm64-us: lib/src/crc.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/crc.c) |
| `800413E0` | `__osContDataCrc` | exact | [sm64-us: lib/src/crc.c](https://github.com/n64decomp/sm64/blob/9921382a68bb0c865e5e45eb594d9c64db59b1af/lib/src/crc.c) |
| `800414B0` | `alSeqGetLoc` | exact | [ultralib-I: src/audio/seq.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/seq.c) |
| `800414CC` | `alSeqSetLoc` | exact | [ultralib-I: src/audio/seq.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/seq.c) |
| `800414E8` | `alSeqGetTicks` | structural | [ultralib-I: src/audio/seq.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/seq.c) |
| `80041544` | `alSeqNextEvent` | masked | [ultralib-I: src/audio/seq.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/seq.c) |
| `800416C8` | `alSeqNewMarker` | masked | [ultralib-I: src/audio/seq.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/seq.c) |
| `800417E8` | `alSeqSecToTicks` | masked | [ultralib-I: src/audio/seq.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/seq.c) |
| `800418CC` | `alSeqTicksToSec` | masked | [ultralib-I: src/audio/seq.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/seq.c) |
| `80041920` | `__alSeqNextDelta` | masked | [ultralib-I: src/audio/seq.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/seq.c) |
| `800419F8` | `alSeqNew` | masked | [ultralib-I: src/audio/seq.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/seq.c) |
| `80041AD0` | `alSynSetPriority` | structural | [ultralib-I: src/audio/synsetpriority.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/synsetpriority.c) |
| `80041AE0` | `alFilterNew` | exact | [ultralib-I: src/audio/filter.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/filter.c) |
| `80041B00` | `_doModFunc` | exact | [ultralib-I: src/audio/reverb.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/reverb.c) |
| `80041BA8` | `_filterBuffer` | masked | [ultralib-I: src/audio/reverb.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/reverb.c) |
| `80041C60` | `_saveBuffer` | masked | [ultralib-I: src/audio/reverb.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/reverb.c) |
| `80041DE8` | `_loadBuffer` | masked | [ultralib-I: src/audio/reverb.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/reverb.c) |
| `80041F74` | `_loadOutputBuffer` | masked | [ultralib-I: src/audio/reverb.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/reverb.c) |
| `800423B0` | `alFxParam` | exact | [ultralib-I: src/audio/reverb.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/reverb.c) |
| `800423C8` | `alFxPull` | masked | [ultralib-I: src/audio/reverb.c](https://github.com/decompals/ultralib/blob/e24c836796df4bf520ff8b11a5c9d2cea3a66cbd/src/audio/reverb.c) |

## Unidentified SDK-looking main entries

The following candidates lie among SDK objects but lack an accepted full
signature. Some may be Rare audio extensions or SDK routines with code/version
changes. Names are deliberately withheld. Eight-byte entries may be real empty
stubs; their context needs review. Main code before `80032C30` is mostly game
code, but cannot be assumed free of SDK or Rare support functions.

`800330B0`, `80034180`, `8003431C`, `800343F4`, `800344B0`, `80034554`, `80034630`, `800347D0`, `80034DBC`, `800350A0`, `80035240`, `80035320`, `80035690`, `80035A84`, `80035C84`, `80035DE0`, `80035F10`, `800361C0`, `80036440`, `80036644`, `80037780`, `8003786C`, `80037A30`, `80037A64`, `80037A6C`, `80037C3C`, `80038464`, `8003846C`, `80038DE0`, `80038EA4`, `80038EFC`, `80039C08`, `8003B3E0`, `8003B45C`, `8003B558`, `8003B8A4`, `8003BA08`, `8003BC0C`, `8003BD24`, `8003BFC0`, `8003C030`, `8003C25C`, `8003C3C0`, `8003C5E4`, `8003C750`, `8003D71C`, `8003D9BC`, `8003E1D4`, `8003E1DC`, `8003EF90`, `8003FB20`, `800405E4`, `800407B4`, `80040A4C`, `800414F8`, `80041978`, `800419C8`.

## Reproduction and limitations

Inventory generation requires only Python's standard library:

```sh
python3 tools/analysis/boot_functions.py baserom.us.z64
# To inspect raw reference candidates (not the curated accepted-name list):
python3 tools/analysis/libultra_sig.py baserom.us.z64 /tmp/kig-t005/007 --output /tmp/kig-t005/007-candidates.json
python3 tools/analysis/libultra_sig.py baserom.us.z64 /tmp/kig-t005/ultralib/build/I/libultra_rom --objects --output /tmp/kig-t005/I-candidates.json
```

Reference setup used shallow clones of the three pinned repos above, entirely
under `/tmp/kig-t005/`. IDO was the [ido-static-recomp v1.2 5.3 Linux release](https://github.com/decompals/ido-static-recomp/releases/tag/v1.2).
`make -C /tmp/kig-t005/ultralib/tools ido/cc` obtains its compiler. Build I
objects with `make VERSION=I TARGET=libultra_rom COMPARE=0 -j4` in that scratch
clone. All needed objects compiled; final archive packaging failed because
`mips-linux-gnu-ar` was not on PATH. Matching reads the generated ELF objects,
so packaging is not needed; no original reference archive comparison was run.

SM64 C files were compiled directly with that IDO compiler, `-c -G 0 -nostdinc
-Xcpluscomm -non_shared -Wab,-r4300_mul -mips2 -o32 -O1 -DVERSION_US
-DTARGET_N64 -D_LANGUAGE_C -DF3D_OLD`, including SM64 `include`, `include/libc`
and `lib/src`. Audio/gu C used `-O3`; math used `-O2`; 64-bit integer helpers
used `-mips3 -32 -O1`. Nonmatching or failing reference files are not positive
evidence. SM64 assembly was preprocessed with `cpp -P -DVERSION_US
-DTARGET_N64 -D_LANGUAGE_ASSEMBLY -I.../sm64/include` and assembled using GNU
MIPS binutils 2.46 `as -EB -mips3 -32`. Both full-object exception matching and
individual IDO object matching were performed. Binary data remains in scratch
or memory; repository artifacts contain names, bounds and hashes only.

The matcher intentionally emits **candidates**, including tiny signatures and
identical wrappers that can collide. The checked-in JSON is a curated set;
do not overwrite it with raw candidates. Generic `jr ra; nop` stubs and bare
relocated loads were rejected without contextual evidence. GoldenEye's local
exception labels are not automatically classified as separate functions.

Validation: inventories reproduce deterministically; rows are aligned,
contiguous and nonoverlapping across each stated scan range; accepted SDK
match lengths fit their CSV extents; all reference-source links were checked
against the pinned local clones. Main game boundary completeness, exact early
SDK release letter and unidentified SDK-looking routines remain open. The next
version-identification step needs authenticated D/E/F/G/H archives or an
independently version-labelled early binary, compared at initialize, exception,
VI init/modes, AI buffer and controller-init routines together.
