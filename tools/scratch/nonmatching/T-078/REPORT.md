# T-078 — sol-A27: libaudio IDO 5.3 -O3

**All 19 targeted T2 functions matched: 11,476 original bytes.**
Promoted 111 GLOBAL_ASM functions in total (31,420 inventory bytes), including the surrounding already-named SDK routines. No commits, symbol renames, register bindings, inline assembly, boot/overlay edits, or status.csv changes.

## Finding and source provenance

The private register ABI is ordinary IDO 5.3 interprocedural optimization.
Compiling the complete original SDK source with its static helpers at -O3
reproduces the unsaved-register/private-argument convention and compiler-generated
return stubs. Compiling individual helpers at -O3 is insufficient.
The main build remains -O2 -mips2; only the listed audio objects use -O3.

Reference: n64decomp/libreultra revision
`1aca5c13ca041cef86f8dc194b727361dad9c09b`, `src/audio` and `include/2.0I/PR`.
`include/libaudio/` scopes the required original SDK types and audio macros,
using existing common scalar types rather than importing graphics and OS headers.
Public sources were also checked against decompals/ultralib as recorded by T-075.
No SDK symbol naming cleanup was attempted. Existing func_ names are retained;
`alGlobals` is mapped to existing `D_80048440`, and the new SDK caller of
`alFxNew` uses the existing `func_8003EF90` symbol via a header alias.

Version adaptations are source-supported historical behavior:

- Release assertions are disabled (`assert(x)` expands to `((void)0)`), equivalent to NDEBUG. Debug/profiling paths remain disabled.
- synthesizer.c predates the later unconditional final `paramSamples &= ~0xf` fix. The alignment inside the callback loop is retained; removing only the later post-loop alignment gives exact 648-byte alAudioFrame at O3.
- reverb.c uses its commented historical `rsinc = (f32)val / 0xffffff`, stores the raw input/output parameters, and only sets the lowpass cutoff. This version does not call init_lpfilter from alFxParamHdl. Signed `% 8` is essential: changing it to `& 7` loses the original switch bounds check. Unused L_INC/val/lastval/blob statics were omitted.
- drvrNew.c/alFxNew already has the corresponding historical formula from T-075 and stays unchanged at O2.

## TU map and full-file flag matrix

Offsets are decompressed main-image offsets. Existing boundaries come from
docs/tu_boundaries.md; original-file boundaries without padding were confirmed
by complete SDK object layout and final linked equality.

Integrated onto current local master `71e6864`, including T-080 `f536160`.
T-080's libultra sources, headers, symbol files, Makefile SDK flags, and all
`libultra/` YAML boundaries are unchanged. Controller objects remain at
0x2A830/0x2ABF0; CRC remains `libultra/crc` at 0x319D0. Audio sequence
code uses master's `main_319D0` name at **0x31B50** (formerly main_31B50
in the original T-078 patch). No main_2A830 audio source is retained.

Only three extra audio text boundaries are needed on this layout: 0x2B190
(synaddplayer), 0x2B1E0 (synallocvoice), and 0x2FC40 (load).
Audio data starts at 0x38CB0 and audio rodata at 0x39790, after the neighboring
T-080 SDK pools. Each range has one owner; the final image comparison checks
all original addresses. No game code is compiled at O3.

Each cell is **different instruction words / emitted .text bytes** against the
entire original padded TU slice, masking only actual ELF relocation fields.
O3 zeros are diagnostic; the full clean linked build below verifies all
addresses and all data too. O1/O2 were tested on these same complete C TUs,
not isolated helpers. Source comments, SDK statement order within each original
file, and ordinary types are retained. Independent source groups in a combined
TU are ordered to match IDO's emitted order; mainbus/load needed separate objects.

| TU | SDK file(s) | O1 | O2 | O3 |
|---|---|---:|---:|---:|
| main_27D70 | heapinit | 20 / 80 | 0 / 64 | 0 / 64 |
| main_27DB0 | heapalloc | 28 / 112 | 0 / 96 | 0 / 96 |
| main_27E10 | bnkf | 243 / 976 | 188 / 752 | 0 / 592 |
| main_28060 | csplayer | 1498 / 6016 | 1200 / 4832 | 0 / 4656 |
| main_29290 | cspsetbank | 19 / 80 | 11 / 64 | 0 / 64 |
| main_292D0 | cspgetstate | 0 / 16 | 0 / 16 | 0 / 16 |
| main_292E0 | cspplay, cspstop, cseq | 879 / 3536 | 738 / 2960 | 0 / 2848 |
| main_29E00 | cspsetseq | 19 / 80 | 11 / 64 | 0 / 64 |
| main_29E40 | cspsetvol | 18 / 80 | 13 / 64 | 0 / 64 |
| main_2A160 | synthesizer | 514 / 2064 | 434 / 1648 | 0 / 1744 |
| main_2AE50 | event | 231 / 928 | 204 / 832 | 0 / 832 |
| main_2B190 | synaddplayer | 23 / 96 | 0 / 80 | 0 / 80 |
| main_2B1E0 | synallocvoice | 169 / 688 | 138 / 544 | 0 / 560 |
| main_2B410 | synsetvol | 51 / 208 | 0 / 160 | 0 / 160 |
| main_2B4B0 | synstartvoice | 52 / 208 | 0 / 144 | 0 / 144 |
| main_2B540 | synsetpan | 48 / 192 | 0 / 144 | 0 / 144 |
| main_2B5D0 | synsetpitch | 48 / 192 | 0 / 144 | 0 / 144 |
| main_2B660 | synsetfxmix | 52 / 208 | 0 / 160 | 0 / 160 |
| main_2B700 | synstopvoice | 43 / 176 | 0 / 128 | 0 / 128 |
| main_2D860 | seqplayer | 1992 / 7984 | 1633 / 6544 | 0 / 6464 |
| main_2F1A0 | synstartvoiceparam | 71 / 288 | 0 / 240 | 0 / 240 |
| main_2F290 | syndelete | 0 / 16 | 0 / 16 | 0 / 16 |
| main_2FA50 | synallocfx | 59 / 240 | 13 / 160 | 0 / 160 |
| main_2FAF0 | mainbus | 124 / 496 | 83 / 336 | 0 / 336 |
| main_2FC40 | load | 1040 / 4160 | 724 / 2864 | 0 / 2896 |
| main_30790 | resample | 248 / 992 | 192 / 752 | 0 / 768 |
| main_30A90 | env | 1071 / 4320 | 799 / 3200 | 0 / 3168 |
| main_316F0 | auxbus | 87 / 352 | 65 / 272 | 0 / 272 |
| main_31950 | copy | 32 / 96 | 0 / 128 | 0 / 128 |
| main_319D0 | seq, synsetpriority, filter | 511 / 2048 | 405 / 1632 | 0 / 1616 |
| main_321A0 | reverb | 1022 / 4096 | 774 / 3104 | 0 / 3088 |

The remaining audio TUs retain their existing default flags and assembly:

| TU | Contents / disposition |
|---|---|
| main_29E80 | AI OS functions plus alLink/alUnlink/alInit/alClose; remains asm/default flags |
| main_2B780 | alSynFreeVoice plus alCents2Ratio; guNormalize is now a separate T-080 object |
| main_2F2A0 | drvrNew; __osAiDeviceBusy is now a separate T-080 object; retain matched alFxNew/default flags |
| main_31800 | alSaveParam/alSavePull; osGetTime is now a separate T-080 object |

The retained T-075 alFxNew body was separately tested in its actual declarations:
O1 = 337 words, 1348/1048 bytes; O2 = 0, 1048/1048; O3 = 0, 1048/1048.
There is no reason to change flags for that mixed unit. Its existing match and
all other prior C matches remain exact in final linked validation.

## Per-function results

Every row below replaces its GLOBAL_ASM with C and matches in the linked image.
Inventory extents sometimes include a following inlined helper's 8-byte return
stub; the complete original source naturally emits these stubs, without padding
arrays or artificial return functions.

| Existing symbol | SDK identity | Inventory bytes | Result |
|---|---|---:|---|
| func_80037780 | _bnkfPatchInst (+ _bnkfPatchBank stub) | 244 | MATCH |
| func_80037A30 | __setUsptFromTempo (+ __CSPRepostEvent stub) | 60 | MATCH |
| func_80037A6C | __CSPHandleMetaMsg | 464 | MATCH |
| func_80037C3C | __CSPHandleMIDIMsg (+ __CSPHandleNextSeqEvent stub) | 2096 | MATCH |
| func_8003846C | __CSPVoiceHandler | 1556 | MATCH |
| func_80038DE0 | __getTrackByte | 196 | MATCH |
| func_80038EA4 | __readVarLen (+ __alCSeqGetTrackEvent stub) | 96 | MATCH |
| func_80039C08 | alAudioFrame | 648 | MATCH |
| func_8003D71C | __handleMetaMsg | 120 | MATCH |
| func_8003D9BC | __handleMIDIMsg (+ __handleNextSeqEvent stub) | 2080 | MATCH |
| func_8003E1DC | __seqpVoiceHandler | 1572 | MATCH |
| func_8003FB20 | _decodeChunk | 300 | MATCH |
| func_800405E4 | _getRate | 464 | MATCH |
| func_800407B4 | _pullSubFrame | 664 | MATCH |
| func_80040A4C | _getVol | 176 | MATCH |
| func_800414F8 | readVarLen | 76 | MATCH |
| func_80041978 | read32 | 80 | MATCH |
| func_800419C8 | read16 | 48 | MATCH |
| func_80042198 | alFxParamHdl | 536 | MATCH |

Surrounding named SDK functions promoted in the same fully matching units:

- `alHeapInit` (52 B).
- `alHeapDBAlloc` (84 B).
- `alBnkfNew` (260 B).
- `alSeqFileNew` (64 B).
- `__CSPPostNextSeqEvent` (112 B).
- `alCSPNew` (364 B).
- `alCSPSetBank` (52 B).
- `alCSPGetState` (8 B).
- `alCSPPlay` (48 B).
- `alCSPStop` (48 B).
- `alCSeqGetLoc` (160 B).
- `alCSeqSetLoc` (160 B).
- `alCSeqNextEvent` (760 B).
- `alCSeqNew` (276 B).
- `alCSeqNewMarker` (364 B).
- `alCSeqGetTicks` (8 B).
- `alCSeqSecToTicks` (252 B).
- `alCSeqTicksToSec` (108 B).
- `__alCSeqNextDelta` (360 B).
- `alCSPSetSeq` (52 B).
- `alCSPSetVol` (60 B).
- `_timeToSamples` (88 B).
- `_freePVoice` (56 B).
- `_collectPVoices` (96 B).
- `__freeParam` (24 B).
- `__allocParam` (48 B).
- `alSynNew` (768 B).
- `alEvtqFlushType` (172 B).
- `alEvtqFlush` (112 B).
- `alEvtqPostEvent` (292 B).
- `alEvtqNextEvent` (140 B).
- `alEvtqNew` (116 B).
- `alSynAddPlayer` (80 B).
- `_allocatePVoice` (232 B).
- `alSynAllocVoice` (320 B).
- `alSynSetVol` (156 B).
- `alSynStartVoice` (140 B).
- `alSynSetPan` (132 B).
- `alSynSetPitch` (132 B).
- `alSynSetFXMix` (148 B).
- `alSynStopVoice` (120 B).
- `__setInstChanState` (84 B).
- `__resetPerfChanState` (128 B).
- `__initFromBank` (180 B).
- `__vsDelta` (36 B).
- `__vsVol` (136 B).
- `__seqpReleaseVoice` (300 B).
- `__voiceNeedsNoteKill` (168 B).
- `__unmapVoice` (112 B).
- `__postNextSeqEvent` (220 B).
- `__vsPan` (72 B).
- `__lookupVoice` (116 B).
- `__mapVoice` (112 B).
- `__lookupSoundQuick` (252 B).
- `__seqpStopOsc` (260 B).
- `__initChanState` (112 B).
- `alSeqpNew` (384 B).
- `alSynStartVoiceParams` (228 B).
- `alSynDelete` (8 B).
- `alSynAllocFX` (152 B).
- `alMainBusParam` (48 B).
- `alMainBusPull` (288 B).
- `alLoadParam` (468 B).
- `alRaw16Pull` (940 B).
- `alAdpcmPull` (1184 B).
- `alResampleParam` (236 B).
- `alResamplePull` (520 B).
- `_ldexpf` (40 B).
- `_frexpf` (236 B).
- `alEnvmixerParam` (224 B).
- `alEnvmixerPull` (1352 B).
- `alAuxBusParam` (48 B).
- `alAuxBusPull` (216 B).
- `alCopy` (116 B).
- `alSeqGetLoc` (28 B).
- `alSeqSetLoc` (28 B).
- `alSeqGetTicks` (8 B).
- `alSeqNextEvent` (388 B).
- `alSeqNewMarker` (288 B).
- `alSeqSecToTicks` (228 B).
- `alSeqTicksToSec` (84 B).
- `__alSeqNextDelta` (88 B).
- `alSeqNew` (216 B).
- `alSynSetPriority` (16 B).
- `alFilterNew` (28 B).
- `_doModFunc` (168 B).
- `_filterBuffer` (184 B).
- `_saveBuffer` (392 B).
- `_loadBuffer` (396 B).
- `_loadOutputBuffer` (548 B).
- `alFxParam` (24 B).
- `alFxPull` (832 B).

Previously matched stubs remain C and match: func_80037770/_bnkfPatchWaveTable,
func_80037778/_bnkfPatchSound, func_80039AC0/_timeToSamplesNoRound,
func_80039C00/__nextSampleTime, func_8003D348/__setUsptFromTempo, and
func_800414F0/read8. Their SDK bodies are
inlined by O3, so the out-of-line copy becomes the original return stub.

## Data and rodata ownership

T-073's recipe assigns complete aligned pools to C and resumes asm data at the
next boundary; neighboring pools remain untouched. The env initialized data
uses `type: .data, linker_section_order: .rodata` to preserve its original
position among the existing asm fragments. This is necessary: a plain .data
entry would place it before the rodata fragments and shift addresses.

| Range (image offsets) | Owner | Contents |
|---|---|---|
| 0x38CB0–0x38DF0 | main_30A90 .data | eqpower[128] and _getRate local logtab initialization |
| 0x39790–0x399D0 | main_28060 .rodata | sequence-player switches and float |
| 0x399D0–0x399E0 | main_292E0 .rodata | two 1,000,000.0 doubles |
| 0x399E0–0x399F0 | main_2A160 .rodata | two 1,000,000.0 doubles |
| 0x39A10–0x39C50 | main_2D860 .rodata | sequence-player switches and float |
| 0x39C50–0x39C80 | main_2F2A0 .rodata | existing T-075 alFxNew pool, unchanged |
| 0x39C80–0x39CC0 | main_30790 .rodata | resample switch |
| 0x39CC0–0x39D20 | main_30A90 .rodata | two doubles and envelope switch |
| 0x39D20–0x39D30 | main_319D0 .rodata | two 1,000,000.0 doubles |
| 0x39D30–0x39D60 | main_321A0 .rodata | existing reverb ownership, now emitted by C |

The complete pools and neighboring original bytes are proven by full-image
comparison. No force_migration, function_owner, symbol-address hacks, or
handwritten linker edits were needed. Regenerated undefined_syms files are kept.

## Makefile changes and reproduction

Every TU in the matrix has this target-specific line (expanded explicitly in
Makefile):

```
build/src/main/main_<off>.c.o: CFLAGS := -c -G 0 -non_shared -Xcpluscomm -Wab,-r4300_mul -O3 -mips2 -32
```

The corresponding target-specific ASMPROC adds `-O2` before the compiler command.
That option selects asm-processor's parser model: this checkout's parser accepts
O0/O1/O2 but rejects O3. IDO itself receives **only -O3**. These reconstructed
TUs contain no GLOBAL_ASM placeholders. `--force --convert-statics global` is
used where necessary to preserve existing private symbol spellings from mdebug,
without changing the C linkage seen by IDO or its IPA decisions. Audio header
files are explicit prerequisites for all reconstructed objects.

`matrix.py` reproduces the complete-TU O1/O2/O3 diagnostics without modifying
sources. `probe.py` reproduces initial complete-reference-file diagnostics;
set SDK_ROOT to a checkout of the pinned libreultra tree. Debug symbol recovery
is only for diagnostics; zero-size static ELF symbols use the next text symbol
as their end. Accordingly its two-word misses at inlined-stub boundaries are
not failures of the final linked implementation. Initial unmodified-reference
probes also include later SDK changes; the final matrix uses the adapted C.

Deleted matched drafts:

- `tools/scratch/nonmatching/T-026/func_80037780.c`.
- `tools/scratch/nonmatching/T-026/func_80037A30.c`.
- `tools/scratch/nonmatching/T-026/func_80037A6C.c`.
- `tools/scratch/nonmatching/T-026/func_80037C3C.c`.
- `tools/scratch/nonmatching/T-026/func_8003846C.c`.
- `tools/scratch/nonmatching/T-026/func_80038DE0.c`.
- `tools/scratch/nonmatching/T-026/func_80038EA4.c`.
- `tools/scratch/nonmatching/T-026/func_80039C08.c`.
- `tools/scratch/nonmatching/T-026/func_8003D71C.c`.
- `tools/scratch/nonmatching/T-026/func_8003D9BC.c`.
- `tools/scratch/nonmatching/T-026/func_8003E1DC.c`.
- `tools/scratch/nonmatching/T-026/func_8003FB20.c`.
- `tools/scratch/nonmatching/T-035/func_800405E4.c`.
- `tools/scratch/nonmatching/T-035/func_800407B4.c`.
- `tools/scratch/nonmatching/T-035/func_80040A4C.c`.
- `tools/scratch/nonmatching/T-035/func_800414F8.c`.
- `tools/scratch/nonmatching/T-035/func_80041978.c`.
- `tools/scratch/nonmatching/T-035/func_800419C8.c`.
- `tools/scratch/nonmatching/T-035/func_80042198.c`.
- `tools/scratch/nonmatching/T-075/bnk.c`.
- `tools/scratch/nonmatching/T-075/frame.c`.
- `tools/scratch/nonmatching/T-075/track.c`.

## Final clean validation

`make clean && make extract && make all && make progress` passed after
integration onto master `71e6864` (including T-080 `f536160`) and all source
and symbol-preservation changes. The ROM and all three executable
images are byte-identical:

- ROM: `ba52e91b44450c548467044b26951353dc491e04`
- main: `81736d32e8cda8f399b319a49250dff972b81af8`
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`

All 31 complete reconstructed audio TU text slices match at O3, including
alignment; every prior C match is preserved. All promoted function addresses,
constant pools, initialized arrays, and compiler-generated stubs are checked
by linked image equality. No changes to status.csv, TRACKING, WORKLOG, boot,
or overlay sources/configurations. Regenerated linker_scripts/*.undefined_syms.txt
files have no net diff. `git diff --check` passes. Generated functions.csv and
progress.html were restored after recording this table for the lead.

Missing baserom.us.z64, ROMs, .venv, and tools/ext were symlinked from the
authorized main checkout. No ROM was copied or added to git; no commits were made.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 82,032 (25.71%) | 82,032 (25.71%) | 0 | 253 | 0 | 309 | 437 (138,092) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 173,204 | 55,764 (32.20%) | 55,764 (32.20%) | 0 | 107 | 0 | 183 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 17,800 (12.95%) | 17,800 (12.95%) | 0 | 146 | 0 | 105 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
