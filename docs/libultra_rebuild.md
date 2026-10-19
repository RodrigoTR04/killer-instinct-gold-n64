# T-018 FU-4: pinned SM64-US library rebuild

Research only, 2026-10-18. No build integration or commits performed.

Reproduce from the repository root:

```sh
./tools/scratch/libultra/fetch.sh
.venv/bin/python tools/scratch/libultra/build.py
.venv/bin/python tools/scratch/libultra/compare.py
```

The source is n64decomp/sm64 commit
`9921382a68bb0c865e5e45eb594d9c64db59b1af`. Fetching that archive is the
only network operation. Generated sources and objects are locally ignored.
All 135 selected C/assembly objects compile successfully; CN-only libgcc
sources are deliberately excluded. No make invocation is involved.

## Method and limits

The comparator selects every status.csv row whose note contains libultra,
resolves it against the audited boot/main function inventories, verifies the
ROM SHA1 and decompressed main SHA1, and reads boot directly using
ROM = VRAM - 0x7FFFF400. Main uses base 0x8000F960.

C uses IDO 5.3, O1/MIPS II by default, O3 for al*/gu*, O2 for math,
string and ldiv, and O1/MIPS III for ll*. These follow the US branches of
the pinned Makefile (an empty OPT_FLAGS means the compiler default O1).
Common options and defines, including VERSION_US, TARGET_N64, F3D_OLD and
_FINALROM, are recorded in results.csv. Assembly uses cpp then GNU binutils
as -EB -mips3 -32. Source is unmodified.

ELF symbols provide C body sizes. Assembly glabels have no ELF function
size, so the audited target extent determines the compared assembly span;
internal labels do not truncate __osException. Actual R_MIPS_26 target bits
and R_MIPS_HI16/LO16 immediate fields are masked. R_MIPS_PC16 branches to
same-section symbols are resolved, never masked. Unexpected relocation kinds
are errors. All other bits must match, including registers, constants and
branch distances. C body tails must contain only zero padding through the
inventory boundary. MATCH is equality before masking; MATCH_MASKED requires
masking. Byte totals count complete inventory extents, including padding;
they are not sums of C ELF symbol sizes.

A masked match does not validate the identity or final values of relocated
symbols, rodata/data/bss, or a complete linked image. This work establishes
rebuildable text, not a unique SDK revision letter. NOT_FOUND means no named
text implementation in this pinned source library, not a failed compiler
configuration or evidence for an SDK revision mismatch.

## Results

- MATCH: 52 functions, 4,716 bytes.
- MATCH_MASKED: 96 functions, 23,328 bytes.
- NO_MATCH: 1 functions, 24 bytes.
- NOT_FOUND: 118 functions, 23,716 bytes.

Total: 267 functions, 51,784 bytes. A repeated rebuild and comparison produced
identical results.csv SHA256 values. Per-function sources, flags and extent
notes are in tools/scratch/libultra/results.csv.

## The one NO_MATCH

main 0x80039AB0 osAiGetLength (24 inventory bytes): the SM64 function body
is 12 bytes and matches exactly, followed by a zero word in the object.
KI has an additional return/no-op stub at 0x80039AC0 before _timeToSamples.
The audited inventory folds that stub into osAiGetLength. Therefore the
complete 24-byte entry is NO_MATCH; this is an extent/extra-stub issue,
not evidence that its actual getter body needs another SDK revision or flags.
Keep the extra stub separate during eventual boundary work, or retain the
original extent until it is named. This research does not change the inventory.

## Every NOT_FOUND

These implementations are absent from the selected SM64-US library; source
search also found neither __lookupVoice nor alFxPull anywhere in the archive.
SM64 uses its own audio engine rather than the full SDK sequence/synthesis
library present in KI. Missing gu/controller/OS operations likewise are not
made available merely by changing flags. Existing T-005 references identify
many in ultralib-I; this task fetched no second reference and does not claim
those sources were rebuilt here. An earlier SDK archive or separately
validated implementations are needed. In particular no 2.0I-versus-2.0H
revision diagnosis can be inferred from source absence.

- boot 0x80003B30 `osViGetCurrentFramebuffer` (64 bytes): absent from pinned SM64 library.
- boot 0x80003B70 `osViGetNextFramebuffer` (64 bytes): absent from pinned SM64 library.
- boot 0x80003BB0 `osDpSetNextBuffer` (176 bytes): absent from pinned SM64 library.
- boot 0x80005CB0 `__osDpDeviceBusy` (48 bytes): absent from pinned SM64 library.
- main 0x80033080 `guRandom` (48 bytes): absent from pinned SM64 library.
- main 0x8003381C `guLookAtHilite` (196 bytes): absent from pinned SM64 library.
- main 0x80035D30 `osContStartQuery` (132 bytes): absent from pinned SM64 library.
- main 0x80035DB4 `osContGetQuery` (44 bytes): absent from pinned SM64 library.
- main 0x80036DF0 `guRotateRPYF` (332 bytes): absent from pinned SM64 library.
- main 0x80036F3C `guRotateRPY` (84 bytes): absent from pinned SM64 library.
- main 0x80036F90 `guMtxXFMF` (160 bytes): absent from pinned SM64 library.
- main 0x80037030 `guMtxCatF` (368 bytes): absent from pinned SM64 library.
- main 0x80037410 `osUnmapTLB` (64 bytes): absent from pinned SM64 library.
- main 0x800376D0 `alHeapInit` (64 bytes): absent from pinned SM64 library.
- main 0x80037710 `alHeapDBAlloc` (112 bytes): absent from pinned SM64 library.
- main 0x800379C0 `__CSPPostNextSeqEvent` (112 bytes): absent from pinned SM64 library.
- main 0x80038A80 `alCSPNew` (368 bytes): absent from pinned SM64 library.
- main 0x80038BF0 `alCSPSetBank` (64 bytes): absent from pinned SM64 library.
- main 0x80038C30 `alCSPGetState` (16 bytes): absent from pinned SM64 library.
- main 0x80038C40 `alCSPPlay` (48 bytes): absent from pinned SM64 library.
- main 0x80038C70 `alCSPStop` (48 bytes): absent from pinned SM64 library.
- main 0x80038CA0 `alCSeqGetLoc` (160 bytes): absent from pinned SM64 library.
- main 0x80038D40 `alCSeqSetLoc` (160 bytes): absent from pinned SM64 library.
- main 0x80038F04 `alCSeqNextEvent` (760 bytes): absent from pinned SM64 library.
- main 0x800391FC `alCSeqNew` (276 bytes): absent from pinned SM64 library.
- main 0x80039310 `alCSeqNewMarker` (364 bytes): absent from pinned SM64 library.
- main 0x8003947C `alCSeqGetTicks` (8 bytes): absent from pinned SM64 library.
- main 0x80039484 `alCSeqSecToTicks` (252 bytes): absent from pinned SM64 library.
- main 0x80039580 `alCSeqTicksToSec` (108 bytes): absent from pinned SM64 library.
- main 0x800395EC `__alCSeqNextDelta` (372 bytes): absent from pinned SM64 library.
- main 0x80039760 `alCSPSetSeq` (64 bytes): absent from pinned SM64 library.
- main 0x800397A0 `alCSPSetVol` (64 bytes): absent from pinned SM64 library.
- main 0x80039940 `alUnlink` (48 bytes): absent from pinned SM64 library.
- main 0x80039970 `alLink` (36 bytes): absent from pinned SM64 library.
- main 0x80039994 `alClose` (56 bytes): absent from pinned SM64 library.
- main 0x800399CC `alInit` (52 bytes): absent from pinned SM64 library.
- main 0x80039AC8 `_timeToSamples` (88 bytes): absent from pinned SM64 library.
- main 0x80039B20 `_freePVoice` (56 bytes): absent from pinned SM64 library.
- main 0x80039B58 `_collectPVoices` (96 bytes): absent from pinned SM64 library.
- main 0x80039BB8 `__freeParam` (24 bytes): absent from pinned SM64 library.
- main 0x80039BD0 `__allocParam` (56 bytes): absent from pinned SM64 library.
- main 0x80039E90 `alSynNew` (768 bytes): absent from pinned SM64 library.
- main 0x8003A7B0 `alEvtqFlushType` (172 bytes): absent from pinned SM64 library.
- main 0x8003A85C `alEvtqFlush` (112 bytes): absent from pinned SM64 library.
- main 0x8003A8CC `alEvtqPostEvent` (292 bytes): absent from pinned SM64 library.
- main 0x8003A9F0 `alEvtqNextEvent` (140 bytes): absent from pinned SM64 library.
- main 0x8003AA7C `alEvtqNew` (116 bytes): absent from pinned SM64 library.
- main 0x8003AAF0 `alSynAddPlayer` (80 bytes): absent from pinned SM64 library.
- main 0x8003AB40 `_allocatePVoice` (232 bytes): absent from pinned SM64 library.
- main 0x8003AC28 `alSynAllocVoice` (328 bytes): absent from pinned SM64 library.
- main 0x8003AD70 `alSynSetVol` (160 bytes): absent from pinned SM64 library.
- main 0x8003AE10 `alSynStartVoice` (144 bytes): absent from pinned SM64 library.
- main 0x8003AEA0 `alSynSetPan` (144 bytes): absent from pinned SM64 library.
- main 0x8003AF30 `alSynSetPitch` (144 bytes): absent from pinned SM64 library.
- main 0x8003AFC0 `alSynSetFXMix` (160 bytes): absent from pinned SM64 library.
- main 0x8003B060 `alSynStopVoice` (128 bytes): absent from pinned SM64 library.
- main 0x8003B0E0 `alSynFreeVoice` (176 bytes): absent from pinned SM64 library.
- main 0x8003B190 `alCents2Ratio` (80 bytes): absent from pinned SM64 library.
- main 0x8003D1C0 `__setInstChanState` (84 bytes): absent from pinned SM64 library.
- main 0x8003D214 `__resetPerfChanState` (128 bytes): absent from pinned SM64 library.
- main 0x8003D294 `__initFromBank` (188 bytes): absent from pinned SM64 library.
- main 0x8003D350 `__vsDelta` (36 bytes): absent from pinned SM64 library.
- main 0x8003D374 `__vsVol` (136 bytes): absent from pinned SM64 library.
- main 0x8003D3FC `__seqpReleaseVoice` (300 bytes): absent from pinned SM64 library.
- main 0x8003D528 `__voiceNeedsNoteKill` (168 bytes): absent from pinned SM64 library.
- main 0x8003D5D0 `__unmapVoice` (112 bytes): absent from pinned SM64 library.
- main 0x8003D640 `__postNextSeqEvent` (220 bytes): absent from pinned SM64 library.
- main 0x8003D794 `__vsPan` (72 bytes): absent from pinned SM64 library.
- main 0x8003D7DC `__lookupVoice` (116 bytes): absent from pinned SM64 library.
- main 0x8003D850 `__mapVoice` (112 bytes): absent from pinned SM64 library.
- main 0x8003D8C0 `__lookupSoundQuick` (252 bytes): absent from pinned SM64 library.
- main 0x8003E800 `__seqpStopOsc` (260 bytes): absent from pinned SM64 library.
- main 0x8003E904 `__initChanState` (112 bytes): absent from pinned SM64 library.
- main 0x8003E974 `alSeqpNew` (396 bytes): absent from pinned SM64 library.
- main 0x8003EB00 `alSynStartVoiceParams` (240 bytes): absent from pinned SM64 library.
- main 0x8003EBF0 `alSynDelete` (16 bytes): absent from pinned SM64 library.
- main 0x8003EC30 `alSaveNew` (68 bytes): absent from pinned SM64 library.
- main 0x8003EC74 `alMainBusNew` (84 bytes): absent from pinned SM64 library.
- main 0x8003ECC8 `alAuxBusNew` (84 bytes): absent from pinned SM64 library.
- main 0x8003ED1C `alResampleNew` (136 bytes): absent from pinned SM64 library.
- main 0x8003EDA4 `alLoadNew` (168 bytes): absent from pinned SM64 library.
- main 0x8003EE4C `alEnvmixerNew` (164 bytes): absent from pinned SM64 library.
- main 0x8003EEF0 `init_lpfilter` (160 bytes): absent from pinned SM64 library.
- main 0x8003F3B0 `alSynAllocFX` (160 bytes): absent from pinned SM64 library.
- main 0x8003F450 `alMainBusParam` (48 bytes): absent from pinned SM64 library.
- main 0x8003F480 `alMainBusPull` (288 bytes): absent from pinned SM64 library.
- main 0x8003F5A0 `alLoadParam` (468 bytes): absent from pinned SM64 library.
- main 0x8003F774 `alRaw16Pull` (940 bytes): absent from pinned SM64 library.
- main 0x8003FC4C `alAdpcmPull` (1188 bytes): absent from pinned SM64 library.
- main 0x800400F0 `alResampleParam` (236 bytes): absent from pinned SM64 library.
- main 0x800401DC `alResamplePull` (532 bytes): absent from pinned SM64 library.
- main 0x800403F0 `_ldexpf` (40 bytes): absent from pinned SM64 library.
- main 0x80040418 `_frexpf` (236 bytes): absent from pinned SM64 library.
- main 0x80040504 `alEnvmixerParam` (224 bytes): absent from pinned SM64 library.
- main 0x80040AFC `alEnvmixerPull` (1364 bytes): absent from pinned SM64 library.
- main 0x80041050 `alAuxBusParam` (48 bytes): absent from pinned SM64 library.
- main 0x80041080 `alAuxBusPull` (224 bytes): absent from pinned SM64 library.
- main 0x80041160 `alSaveParam` (52 bytes): absent from pinned SM64 library.
- main 0x80041194 `alSavePull` (140 bytes): absent from pinned SM64 library.
- main 0x800412B0 `alCopy` (128 bytes): absent from pinned SM64 library.
- main 0x800414B0 `alSeqGetLoc` (28 bytes): absent from pinned SM64 library.
- main 0x800414CC `alSeqSetLoc` (28 bytes): absent from pinned SM64 library.
- main 0x800414E8 `alSeqGetTicks` (16 bytes): absent from pinned SM64 library.
- main 0x80041544 `alSeqNextEvent` (388 bytes): absent from pinned SM64 library.
- main 0x800416C8 `alSeqNewMarker` (288 bytes): absent from pinned SM64 library.
- main 0x800417E8 `alSeqSecToTicks` (228 bytes): absent from pinned SM64 library.
- main 0x800418CC `alSeqTicksToSec` (84 bytes): absent from pinned SM64 library.
- main 0x80041920 `__alSeqNextDelta` (88 bytes): absent from pinned SM64 library.
- main 0x800419F8 `alSeqNew` (216 bytes): absent from pinned SM64 library.
- main 0x80041AD0 `alSynSetPriority` (16 bytes): absent from pinned SM64 library.
- main 0x80041AE0 `alFilterNew` (32 bytes): absent from pinned SM64 library.
- main 0x80041B00 `_doModFunc` (168 bytes): absent from pinned SM64 library.
- main 0x80041BA8 `_filterBuffer` (184 bytes): absent from pinned SM64 library.
- main 0x80041C60 `_saveBuffer` (392 bytes): absent from pinned SM64 library.
- main 0x80041DE8 `_loadBuffer` (396 bytes): absent from pinned SM64 library.
- main 0x80041F74 `_loadOutputBuffer` (1084 bytes): absent from pinned SM64 library.
- main 0x800423B0 `alFxParam` (24 bytes): absent from pinned SM64 library.
- main 0x800423C8 `alFxPull` (840 bytes): absent from pinned SM64 library.

## Proposed integration and object boundaries

Introduce a separate pinned libultra source/vendor input and object rule set
later, with IDO 5.3 and per-file options above. Do not replace all functions
with an unordered archive: explicitly place objects in each segment in the
address order below, retaining original section alignment and explicit gaps.
The inferred base is target entry minus its ELF symbol offset. Multiple
functions from one source must remain one object: e.g. string, llmuldiv,
osSpTaskLoadGo, osCreateViManager, osTimer, and __osExceptionPreamble.
The exception assembly includes its callable helpers and internal labels.
Do not emit a separate object per helper or reinsert original assembly for
helpers already covered by that object's text.

Each entry below gives the actual rebuilt object .text span, not a claim
that neighboring source objects fill every original file boundary. Whole
text equality is independently checked with the same relocation masks;
where it fails, preserve the original neighboring bytes and investigate
alignment/tail extent before integrating. Match-only C symbols can omit
object-end padding, so function matches alone are insufficient for placement.
Data/rodata/bss placement and relocation symbol mappings remain future work.
Retain assembly for all absent functions and the osAiGetLength extra stub.
Main's gu functions listed as matches can use SM64; absent gu helpers and
the SDK audio sequence/synthesis functions, including __lookupVoice, cannot.

The comparison also regenerates ignored build/placements.json to reproduce
these whole-object checks: 93/94 complete text placements match. The sole
exception is osAiSetFrequency: its 0x160-byte body matches, but the rebuilt
object has 0x10 zero alignment bytes through 0x80039950, whereas KI starts
alUnlink at 0x80039940. Trim/repack that object's trailing text padding to
0x160 after confirming original input-section alignment; do not overwrite
alUnlink or place the unmodified 0x170-byte section there.

Objects in proposed address order (hex end is exclusive):

- boot `0x80002590–0x800027C0`: `lib/src/osInitialize.o`; whole text MATCH (relocations masked).
- boot `0x800027C0–0x80002910`: `lib/src/osCreateThread.o`; whole text MATCH (relocations masked).
- boot `0x80002910–0x80002A60`: `lib/src/osStartThread.o`; whole text MATCH (relocations masked).
- boot `0x80002A60–0x80002B40`: `lib/src/osSetThreadPri.o`; whole text MATCH (relocations masked).
- boot `0x80002B80–0x80002C18`: `lib/asm/bzero.o`; whole text MATCH (relocations masked).
- boot `0x80002C20–0x80002C94`: `lib/asm/osInvalICache.o`; whole text MATCH (relocations masked).
- boot `0x80002CA0–0x80002D4C`: `lib/asm/osInvalDCache.o`; whole text MATCH (relocations masked).
- boot `0x80002D50–0x80002ED0`: `lib/src/osCreatePiManager.o`; whole text MATCH (relocations masked).
- boot `0x80002ED0–0x80002F00`: `lib/src/osCreateMesgQueue.o`; whole text MATCH (relocations masked).
- boot `0x80002F00–0x80003010`: `lib/src/osPiStartDma.o`; whole text MATCH (relocations masked).
- boot `0x80003010–0x80003150`: `lib/src/osRecvMesg.o`; whole text MATCH (relocations masked).
- boot `0x80003150–0x800031F0`: `lib/src/string.o`; whole text MATCH (relocations masked).
- boot `0x800031F0–0x80003550`: `lib/src/osCreateViManager.o`; whole text MATCH (relocations masked).
- boot `0x80003550–0x800035C0`: `lib/src/osSetEventMesg.o`; whole text MATCH (relocations masked).
- boot `0x800035C0–0x80003630`: `lib/src/osViSetEvent.o`; whole text MATCH (relocations masked).
- boot `0x80003630–0x80003650`: `lib/src/osSpTaskYield.o`; whole text MATCH (relocations masked).
- boot `0x80003650–0x80003910`: `lib/src/osSpTaskLoadGo.o`; whole text MATCH (relocations masked).
- boot `0x80003910–0x80003A60`: `lib/src/osSendMesg.o`; whole text MATCH (relocations masked).
- boot `0x80003A60–0x80003AE0`: `lib/src/osSpTaskYielded.o`; whole text MATCH (relocations masked).
- boot `0x80003AE0–0x80003B30`: `lib/src/osViSwapBuffer.o`; whole text MATCH (relocations masked).
- boot `0x80003C60–0x80003CD0`: `lib/src/osViSetMode.o`; whole text MATCH (relocations masked).
- boot `0x80003CD0–0x80003CE0`: `lib/asm/__osSetSR.o`; whole text MATCH (relocations masked).
- boot `0x80003CE0–0x80003CF0`: `lib/asm/__osGetSR.o`; whole text MATCH (relocations masked).
- boot `0x80003CF0–0x80003D00`: `lib/asm/__osSetFpcCsr.o`; whole text MATCH (relocations masked).
- boot `0x80003D00–0x80003D50`: `lib/src/__osSiRawReadIo.o`; whole text MATCH (relocations masked).
- boot `0x80003D50–0x80003DA0`: `lib/src/__osSiRawWriteIo.o`; whole text MATCH (relocations masked).
- boot `0x80003DA0–0x80004610`: `lib/asm/__osExceptionPreamble.o`; whole text MATCH (relocations masked).
- boot `0x80004610–0x80004684`: `lib/asm/osWritebackDCache.o`; whole text MATCH (relocations masked).
- boot `0x80004690–0x800046F0`: `lib/asm/osMapTLBRdb.o`; whole text MATCH (relocations masked).
- boot `0x800046F0–0x80004750`: `lib/src/osPiRawReadIo.o`; whole text MATCH (relocations masked).
- boot `0x80004750–0x80004A10`: `lib/src/math/llmuldiv.o`; whole text MATCH (relocations masked).
- boot `0x80004A10–0x80004A30`: `lib/asm/__osDisableInt.o`; whole text MATCH (relocations masked).
- boot `0x80004A30–0x80004A4C`: `lib/asm/__osRestoreInt.o`; whole text MATCH (relocations masked).
- boot `0x80004A50–0x80004A90`: `lib/src/__osDequeueThread.o`; whole text MATCH (relocations masked).
- boot `0x80004A90–0x80004B50`: `lib/src/__osPiCreateAccessQueue.o`; whole text MATCH (relocations masked).
- boot `0x80004B50–0x80004B70`: `lib/src/osGetThreadPri.o`; whole text MATCH (relocations masked).
- boot `0x80004B70–0x80004C50`: `lib/src/osPiRawStartDma.o`; whole text MATCH (relocations masked).
- boot `0x80004C50–0x80004DD0`: `lib/src/__osDevMgrMain.o`; whole text MATCH (relocations masked).
- boot `0x80004DD0–0x80004F20`: `lib/src/osJamMesg.o`; whole text MATCH (relocations masked).
- boot `0x80004F20–0x80004F50`: `lib/src/osPiGetCmdQueue.o`; whole text MATCH (relocations masked).
- boot `0x80004F50–0x80005350`: `lib/src/osTimer.o`; whole text MATCH (relocations masked).
- boot `0x80005350–0x80005480`: `lib/src/__osViInit.o`; whole text MATCH (relocations masked).
- boot `0x80005480–0x80005490`: `lib/src/__osViGetCurrentContext.o`; whole text MATCH (relocations masked).
- boot `0x80005490–0x800057F0`: `lib/src/__osViSwapContext.o`; whole text MATCH (relocations masked).
- boot `0x800057F0–0x80005800`: `lib/asm/osGetCount.o`; whole text MATCH (relocations masked).
- boot `0x80005800–0x80005810`: `lib/src/__osSpSetStatus.o`; whole text MATCH (relocations masked).
- boot `0x80005810–0x80005B20`: `lib/asm/bcopy.o`; whole text MATCH (relocations masked).
- boot `0x80005B20–0x80005BA0`: `lib/src/osVirtualToPhysical.o`; whole text MATCH (relocations masked).
- boot `0x80005BA0–0x80005BE0`: `lib/src/__osSpSetPc.o`; whole text MATCH (relocations masked).
- boot `0x80005BE0–0x80005C70`: `lib/src/__osSpRawStartDma.o`; whole text MATCH (relocations masked).
- boot `0x80005C70–0x80005CA0`: `lib/src/__osSpDeviceBusy.o`; whole text MATCH (relocations masked).
- boot `0x80005CA0–0x80005CB0`: `lib/src/__osSpGetStatus.o`; whole text MATCH (relocations masked).
- boot `0x80005CE0–0x80005D10`: `lib/src/__osSiDeviceBusy.o`; whole text MATCH (relocations masked).
- boot `0x80005D10–0x80006190`: `lib/src/kdebugserver.o`; whole text MATCH (relocations masked).
- boot `0x80006190–0x800062C0`: `lib/src/__osSyncPutChars.o`; whole text MATCH (relocations masked).
- boot `0x800062C0–0x80006320`: `lib/asm/osSetIntMask.o`; whole text MATCH (relocations masked).
- boot `0x80006320–0x80006420`: `lib/src/osDestroyThread.o`; whole text MATCH (relocations masked).
- boot `0x80006420–0x8000642C`: `lib/asm/__osSetCompare.o`; whole text MATCH (relocations masked).
- boot `0x80006430–0x800064E8`: `lib/asm/__osProbeTLB.o`; whole text MATCH (relocations masked).
- boot `0x800064F0–0x80006500`: `lib/asm/__osGetCause.o`; whole text MATCH (relocations masked).
- boot `0x80006500–0x80006560`: `lib/src/__osAtomicDec.o`; whole text MATCH (relocations masked).
- main `0x80032C30–0x80032DF0`: `lib/src/osViSetSpecialFeatures.o`; whole text MATCH (relocations masked).
- main `0x80032DF0–0x80033080`: `lib/src/guPerspectiveF.o`; whole text MATCH (relocations masked).
- main `0x800338E0–0x80033980`: `lib/src/guTranslateF.o`; whole text MATCH (relocations masked).
- main `0x80033980–0x80033B70`: `lib/src/guRotateF.o`; whole text MATCH (relocations masked).
- main `0x80033B70–0x80034030`: `lib/src/guLookAtRef.o`; whole text MATCH (relocations masked).
- main `0x80034030–0x800340D0`: `lib/src/guScaleF.o`; whole text MATCH (relocations masked).
- main `0x800340D0–0x800340D8`: `lib/asm/sqrtf.o`; whole text MATCH (relocations masked).
- main `0x800340E0–0x80034180`: `lib/src/string.o`; whole text MATCH (relocations masked).
- main `0x80036730–0x800367A0`: `lib/src/osEepromProbe.o`; whole text MATCH (relocations masked).
- main `0x800367A0–0x800368E0`: `lib/src/osEepromLongWrite.o`; whole text MATCH (relocations masked).
- main `0x800368E0–0x80036A20`: `lib/src/osEepromLongRead.o`; whole text MATCH (relocations masked).
- main `0x80036A20–0x80036A90`: `lib/src/osViBlack.o`; whole text MATCH (relocations masked).
- main `0x80036A90–0x80036C50`: `lib/src/math/sinf.o`; whole text MATCH (relocations masked).
- main `0x80036C50–0x80036DC0`: `lib/src/math/cosf.o`; whole text MATCH (relocations masked).
- main `0x80036DC0–0x80036DF0`: `lib/asm/osWritebackDCacheAll.o`; whole text MATCH (relocations masked).
- main `0x800371A0–0x80037410`: `lib/src/guMtxF2L.o`; whole text MATCH (relocations masked).
- main `0x80037450–0x80037510`: `lib/asm/osMapTLB.o`; whole text MATCH (relocations masked).
- main `0x80037510–0x800376D0`: `lib/src/guOrthoF.o`; whole text MATCH (relocations masked).
- main `0x80037780–0x800379C0`: `lib/src/alBnkfNew.o`; whole text MATCH (relocations masked).
- main `0x800397E0–0x80039950`: `lib/src/osAiSetFrequency.o`; whole text NO_MATCH; preserve tail/gap.
- main `0x80039A00–0x80039AB0`: `lib/src/osAiSetNextBuffer.o`; whole text MATCH (relocations masked).
- main `0x80039AB0–0x80039AC0`: `lib/src/osAiGetLength.o`; whole text MATCH (relocations masked).
- main `0x8003A190–0x8003A550`: `lib/src/osContInit.o`; whole text MATCH (relocations masked).
- main `0x8003A550–0x8003A7B0`: `lib/src/osContStartReadData.o`; whole text MATCH (relocations masked).
- main `0x8003B1E0–0x8003B270`: `lib/src/guNormalize.o`; whole text MATCH (relocations masked).
- main `0x8003B270–0x8003B330`: `lib/src/__osSiCreateAccessQueue.o`; whole text MATCH (relocations masked).
- main `0x8003B330–0x8003B3E0`: `lib/src/__osSiRawStartDma.o`; whole text MATCH (relocations masked).
- main `0x8003C900–0x8003CDE0`: `lib/src/osEepromWrite.o`; whole text MATCH (relocations masked).
- main `0x8003CDE0–0x8003CEC0`: `lib/src/osSetTimer.o`; whole text MATCH (relocations masked).
- main `0x8003CEC0–0x8003D1C0`: `lib/src/osEepromRead.o`; whole text MATCH (relocations masked).
- main `0x8003EC00–0x8003EC30`: `lib/src/__osAiDeviceBusy.o`; whole text MATCH (relocations masked).
- main `0x80041220–0x800412B0`: `lib/src/osGetTime.o`; whole text MATCH (relocations masked).
- main `0x80041330–0x800414B0`: `lib/src/crc.o`; whole text MATCH (relocations masked).
