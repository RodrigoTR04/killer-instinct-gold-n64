# T-080 / FU-12 — sol-C30

Integrated **117 excluded SDK functions in 71 C objects**: boot 69 functions / 44 objects
(11,904 inventory bytes), main 48 functions / 27 objects (11,120 inventory bytes).
These byte totals include the inventory's original padding; they are not progress gains.
No commits. No status.csv, overlay source, non-SDK function, or libaudio body changes.

Source: n64decomp/sm64 commit `9921382a68bb0c865e5e45eb594d9c64db59b1af`.
Function bodies and storage definitions are verbatim. Includes use the small isolated
`include/sdk/libultra.h` declaration/macro subset. Main's string exports are spelled
`main_memcpy`, `main_strlen`, and `main_strchr`, matching the existing symbol namespace.

The integration recipe, section placement, padding, and IDO ABI metadata details are
in `docs/libultra_rebuild.md`, “Integration (T-080)”. `boot.json` / `main.json` retain
T-018 results and source/object placements; `*-sections.json` records data/BSS/rodata.
`audit.py` checks source provenance, map ownership, section addresses/sizes, and linked bytes.

## Per-function results

Common CFLAGS: `-c -G 0 -non_shared -Xcpluscomm -Wab,-r4300_mul -nostdinc -signed -32
-DVERSION_US -DTARGET_N64 -D_LANGUAGE_C -DF3D_OLD -D_FINALROM -Iinclude`.
The optimization/ISA flags below are per object. `llmuldiv` has `-32` after `-mips3` too.
“Linked-exact” means actual final image equality, with no relocation masking.

### boot

| Function | C file | Object flags | T-018 | Integration |
|---|---|---|---|---|
| `osInitialize` (0x80002590) | `src/boot/libultra/osInitialize.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `osCreateThread` (0x800027C0) | `src/boot/libultra/osCreateThread.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `osStartThread` (0x80002910) | `src/boot/libultra/osStartThread.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `osSetThreadPri` (0x80002A60) | `src/boot/libultra/osSetThreadPri.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `osCreatePiManager` (0x80002D50) | `src/boot/libultra/osCreatePiManager.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `osCreateMesgQueue` (0x80002ED0) | `src/boot/libultra/osCreateMesgQueue.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `osPiStartDma` (0x80002F00) | `src/boot/libultra/osPiStartDma.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `osRecvMesg` (0x80003010) | `src/boot/libultra/osRecvMesg.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `memcpy` (0x80003150) | `src/boot/libultra/string.c` | `-O2 -mips2` | MATCH | linked-exact |
| `strlen` (0x8000317C) | `src/boot/libultra/string.c` | `-O2 -mips2` | MATCH | linked-exact |
| `strchr` (0x800031A4) | `src/boot/libultra/string.c` | `-O2 -mips2` | MATCH | linked-exact |
| `osCreateViManager` (0x800031F0) | `src/boot/libultra/osCreateViManager.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `viMgrMain` (0x80003374) | `src/boot/libultra/osCreateViManager.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `osSetEventMesg` (0x80003550) | `src/boot/libultra/osSetEventMesg.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `osViSetEvent` (0x800035C0) | `src/boot/libultra/osViSetEvent.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `osSpTaskYield` (0x80003630) | `src/boot/libultra/osSpTaskYield.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `_VirtualToPhysicalTask` (0x80003650) | `src/boot/libultra/osSpTaskLoadGo.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `osSpTaskLoad` (0x8000376C) | `src/boot/libultra/osSpTaskLoadGo.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `osSpTaskStartGo` (0x800038CC) | `src/boot/libultra/osSpTaskLoadGo.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `osSendMesg` (0x80003910) | `src/boot/libultra/osSendMesg.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `osSpTaskYielded` (0x80003A60) | `src/boot/libultra/osSpTaskYielded.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `osViSwapBuffer` (0x80003AE0) | `src/boot/libultra/osViSwapBuffer.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `osViSetMode` (0x80003C60) | `src/boot/libultra/osViSetMode.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `__osSiRawReadIo` (0x80003D00) | `src/boot/libultra/__osSiRawReadIo.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `__osSiRawWriteIo` (0x80003D50) | `src/boot/libultra/__osSiRawWriteIo.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `osPiRawReadIo` (0x800046F0) | `src/boot/libultra/osPiRawReadIo.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `__ull_rshift` (0x80004750) | `src/boot/libultra/llmuldiv.c` | `-O1 -mips3 -32` | MATCH | linked-exact |
| `__ull_rem` (0x8000477C) | `src/boot/libultra/llmuldiv.c` | `-O1 -mips3 -32` | MATCH | linked-exact |
| `__ull_div` (0x800047B8) | `src/boot/libultra/llmuldiv.c` | `-O1 -mips3 -32` | MATCH | linked-exact |
| `__ll_lshift` (0x800047F4) | `src/boot/libultra/llmuldiv.c` | `-O1 -mips3 -32` | MATCH | linked-exact |
| `__ll_rem` (0x80004820) | `src/boot/libultra/llmuldiv.c` | `-O1 -mips3 -32` | MATCH | linked-exact |
| `__ll_div` (0x8000485C) | `src/boot/libultra/llmuldiv.c` | `-O1 -mips3 -32` | MATCH | linked-exact |
| `__ll_mul` (0x800048B8) | `src/boot/libultra/llmuldiv.c` | `-O1 -mips3 -32` | MATCH | linked-exact |
| `__ull_divremi` (0x800048E8) | `src/boot/libultra/llmuldiv.c` | `-O1 -mips3 -32` | MATCH | linked-exact |
| `__ll_mod` (0x80004948) | `src/boot/libultra/llmuldiv.c` | `-O1 -mips3 -32` | MATCH | linked-exact |
| `__ll_rshift` (0x800049E4) | `src/boot/libultra/llmuldiv.c` | `-O1 -mips3 -32` | MATCH | linked-exact |
| `__osDequeueThread` (0x80004A50) | `src/boot/libultra/__osDequeueThread.c` | `-O1 -mips2` | MATCH | linked-exact |
| `__osPiCreateAccessQueue` (0x80004A90) | `src/boot/libultra/__osPiCreateAccessQueue.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `__osPiGetAccess` (0x80004AE0) | `src/boot/libultra/__osPiCreateAccessQueue.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `__osPiRelAccess` (0x80004B24) | `src/boot/libultra/__osPiCreateAccessQueue.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `osGetThreadPri` (0x80004B50) | `src/boot/libultra/osGetThreadPri.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `osPiRawStartDma` (0x80004B70) | `src/boot/libultra/osPiRawStartDma.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `__osDevMgrMain` (0x80004C50) | `src/boot/libultra/__osDevMgrMain.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `osJamMesg` (0x80004DD0) | `src/boot/libultra/osJamMesg.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `osPiGetCmdQueue` (0x80004F20) | `src/boot/libultra/osPiGetCmdQueue.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `__osTimerServicesInit` (0x80004F50) | `src/boot/libultra/osTimer.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `__osTimerInterrupt` (0x80004FDC) | `src/boot/libultra/osTimer.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `__osSetTimerIntr` (0x80005154) | `src/boot/libultra/osTimer.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `__osInsertTimer` (0x800051C8) | `src/boot/libultra/osTimer.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `__osViInit` (0x80005350) | `src/boot/libultra/__osViInit.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `__osViGetCurrentContext` (0x80005480) | `src/boot/libultra/__osViGetCurrentContext.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `__osViSwapContext` (0x80005490) | `src/boot/libultra/__osViSwapContext.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `__osSpSetStatus` (0x80005800) | `src/boot/libultra/__osSpSetStatus.c` | `-O1 -mips2` | MATCH | linked-exact |
| `osVirtualToPhysical` (0x80005B20) | `src/boot/libultra/osVirtualToPhysical.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `__osSpSetPc` (0x80005BA0) | `src/boot/libultra/__osSpSetPc.c` | `-O1 -mips2` | MATCH | linked-exact |
| `__osSpRawStartDma` (0x80005BE0) | `src/boot/libultra/__osSpRawStartDma.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `__osSpDeviceBusy` (0x80005C70) | `src/boot/libultra/__osSpDeviceBusy.c` | `-O1 -mips2` | MATCH | linked-exact |
| `__osSpGetStatus` (0x80005CA0) | `src/boot/libultra/__osSpGetStatus.c` | `-O1 -mips2` | MATCH | linked-exact |
| `__osSiDeviceBusy` (0x80005CE0) | `src/boot/libultra/__osSiDeviceBusy.c` | `-O1 -mips2` | MATCH | linked-exact |
| `u32_to_string` (0x80005D10) | `src/boot/libultra/kdebugserver.c` | `-O1 -mips2` | MATCH | linked-exact |
| `string_to_u32` (0x80005D40) | `src/boot/libultra/kdebugserver.c` | `-O1 -mips2` | MATCH | linked-exact |
| `send_packet` (0x80005D98) | `src/boot/libultra/kdebugserver.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `send` (0x80005E58) | `src/boot/libultra/kdebugserver.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `process_command_memory` (0x80005F30) | `src/boot/libultra/kdebugserver.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `process_command_register` (0x80005F7C) | `src/boot/libultra/kdebugserver.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `kdebugserver` (0x80005FA8) | `src/boot/libultra/kdebugserver.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `__osSyncPutChars` (0x80006190) | `src/boot/libultra/__osSyncPutChars.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `osDestroyThread` (0x80006320) | `src/boot/libultra/osDestroyThread.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `__osAtomicDec` (0x80006500) | `src/boot/libultra/__osAtomicDec.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |

### main

| Function | C file | Object flags | T-018 | Integration |
|---|---|---|---|---|
| `osViSetSpecialFeatures` (0x80032C30) | `src/main/libultra/osViSetSpecialFeatures.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `guPerspectiveF` (0x80032DF0) | `src/main/libultra/guPerspectiveF.c` | `-O3 -mips2` | MATCH_MASKED | linked-exact |
| `guPerspective` (0x80033020) | `src/main/libultra/guPerspectiveF.c` | `-O3 -mips2` | MATCH_MASKED | linked-exact |
| `guTranslateF` (0x800338E0) | `src/main/libultra/guTranslateF.c` | `-O3 -mips2` | MATCH_MASKED | linked-exact |
| `guTranslate` (0x80033928) | `src/main/libultra/guTranslateF.c` | `-O3 -mips2` | MATCH_MASKED | linked-exact |
| `guRotateF` (0x80033980) | `src/main/libultra/guRotateF.c` | `-O3 -mips2` | MATCH_MASKED | linked-exact |
| `guRotate` (0x80033B14) | `src/main/libultra/guRotateF.c` | `-O3 -mips2` | MATCH_MASKED | linked-exact |
| `guLookAtReflectF` (0x80033B70) | `src/main/libultra/guLookAtRef.c` | `-O3 -mips2` | MATCH_MASKED | linked-exact |
| `guLookAtReflect` (0x80033FB0) | `src/main/libultra/guLookAtRef.c` | `-O3 -mips2` | MATCH_MASKED | linked-exact |
| `guScaleF` (0x80034030) | `src/main/libultra/guScaleF.c` | `-O3 -mips2` | MATCH_MASKED | linked-exact |
| `guScale` (0x80034084) | `src/main/libultra/guScaleF.c` | `-O3 -mips2` | MATCH_MASKED | linked-exact |
| `main_memcpy` (0x800340E0) | `src/main/libultra/string.c` | `-O2 -mips2` | MATCH | linked-exact |
| `main_strlen` (0x8003410C) | `src/main/libultra/string.c` | `-O2 -mips2` | MATCH | linked-exact |
| `main_strchr` (0x80034134) | `src/main/libultra/string.c` | `-O2 -mips2` | MATCH | linked-exact |
| `osEepromProbe` (0x80036730) | `src/main/libultra/osEepromProbe.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `osEepromLongWrite` (0x800367A0) | `src/main/libultra/osEepromLongWrite.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `osEepromLongRead` (0x800368E0) | `src/main/libultra/osEepromLongRead.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `osViBlack` (0x80036A20) | `src/main/libultra/osViBlack.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `sinf` (0x80036A90) | `src/main/libultra/sinf.c` | `-O2 -mips2` | MATCH_MASKED | linked-exact |
| `cosf` (0x80036C50) | `src/main/libultra/cosf.c` | `-O2 -mips2` | MATCH_MASKED | linked-exact |
| `guMtxF2L` (0x800371A0) | `src/main/libultra/guMtxF2L.c` | `-O3 -mips2` | MATCH | linked-exact |
| `guMtxIdentF` (0x800372A0) | `src/main/libultra/guMtxF2L.c` | `-O3 -mips2` | MATCH | linked-exact |
| `guMtxIdent` (0x80037328) | `src/main/libultra/guMtxF2L.c` | `-O3 -mips2` | MATCH_MASKED | linked-exact |
| `guMtxL2F` (0x80037358) | `src/main/libultra/guMtxF2L.c` | `-O3 -mips2` | MATCH | linked-exact |
| `guOrthoF` (0x80037510) | `src/main/libultra/guOrthoF.c` | `-O3 -mips2` | MATCH_MASKED | linked-exact |
| `guOrtho` (0x80037664) | `src/main/libultra/guOrthoF.c` | `-O3 -mips2` | MATCH_MASKED | linked-exact |
| `osAiSetNextBuffer` (0x80039A00) | `src/main/libultra/osAiSetNextBuffer.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `osContInit` (0x8003A190) | `src/main/libultra/osContInit.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `__osContGetInitData` (0x8003A38C) | `src/main/libultra/osContInit.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `__osPackRequestData` (0x8003A45C) | `src/main/libultra/osContInit.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `osContStartReadData` (0x8003A550) | `src/main/libultra/osContStartReadData.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `osContGetReadData` (0x8003A614) | `src/main/libultra/osContStartReadData.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `__osPackReadData` (0x8003A6BC) | `src/main/libultra/osContStartReadData.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `guNormalize` (0x8003B1E0) | `src/main/libultra/guNormalize.c` | `-O3 -mips2` | MATCH_MASKED | linked-exact |
| `__osSiCreateAccessQueue` (0x8003B270) | `src/main/libultra/__osSiCreateAccessQueue.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `__osSiGetAccess` (0x8003B2C0) | `src/main/libultra/__osSiCreateAccessQueue.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `__osSiRelAccess` (0x8003B304) | `src/main/libultra/__osSiCreateAccessQueue.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `__osSiRawStartDma` (0x8003B330) | `src/main/libultra/__osSiRawStartDma.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `osEepromWrite` (0x8003C900) | `src/main/libultra/osEepromWrite.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `__osPackEepWriteData` (0x8003CAB0) | `src/main/libultra/osEepromWrite.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `__osEepStatus` (0x8003CBBC) | `src/main/libultra/osEepromWrite.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `osSetTimer` (0x8003CDE0) | `src/main/libultra/osSetTimer.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `osEepromRead` (0x8003CEC0) | `src/main/libultra/osEepromRead.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `__osPackEepReadData` (0x8003D0B0) | `src/main/libultra/osEepromRead.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `__osAiDeviceBusy` (0x8003EC00) | `src/main/libultra/__osAiDeviceBusy.c` | `-O1 -mips2` | MATCH | linked-exact |
| `osGetTime` (0x80041220) | `src/main/libultra/osGetTime.c` | `-O1 -mips2` | MATCH_MASKED | linked-exact |
| `__osContAddressCrc` (0x80041330) | `src/main/libultra/crc.c` | `-O1 -mips2` | MATCH | linked-exact |
| `__osContDataCrc` (0x800413E0) | `src/main/libultra/crc.c` | `-O1 -mips2` | MATCH | linked-exact |

## Deferred / unchanged

- `osAiSetFrequency` (`0x800397E0`): T-018's function body matches, but its SDK
  `.text` section is 0x170 bytes, while KI supplies 0x160 before `alUnlink`.
  Integrating the unmodified object would overwrite audio. Retained the original
  assembly and did not introduce an object-text truncation step.
- `osAiGetLength`: T-018 NO_MATCH was an extent issue. T-038 has already split the
  extra stub; this task follows the requested MATCH/MATCH_MASKED set and leaves the
  getter assembly untouched.
- SDK handwritten assembly (cache/exception/TLB/etc.), all NOT_FOUND functions,
  and main libaudio `al*` / `n_al*` remain unchanged. No matching C candidate failed
  after correct section placement and flags; the only deferred MATCH candidate is
  `osAiSetFrequency` above.
- `-O3` SDK C compiles directly with the same IDO 5.3 driver because the installed
  asm-processor CLI rejects `-O3`. These units contain no assembly insertion.
- Converting SDK storage definitions to externs was tried and rejected: IDO changed
  text in osInitialize, osCreatePiManager, osCreateViManager, and osTimer. Final
  sources retain the original definitions and map their sections explicitly.

## Validation

Required clean sequence: `make clean && make extract && make all && make progress`.
ROM SHA1: `ba52e91b44450c548467044b26951353dc491e04`.
Main: `81736d32e8cda8f399b319a49250dff972b81af8`.
Both overlays retain their original verified hashes. All comparisons are byte-for-byte.
`audit.py` additionally verifies C object ownership and the NOLOAD storage addresses.

## Final make progress

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 70,556 (22.11%) | 70,556 (22.11%) | 0 | 272 | 0 | 290 | 437 (138,092) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 173,204 | 44,288 (25.57%) | 44,288 (25.57%) | 0 | 126 | 0 | 164 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 17,800 (12.95%) | 17,800 (12.95%) | 0 | 146 | 0 | 105 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
