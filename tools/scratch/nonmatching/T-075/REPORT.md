# T-075 — sol-B25: SDK identification sweep

**1 MATCHED (1,048 B), 1 IMPROVED draft, 2 strong candidates UNCHANGED.**
All 127 starting main T2 rows were screened. No commits. No symbol renames,
status.csv edits, boot/overlay edits, or compiler flag changes.

## Sweep and shortlist

[SCREEN.md](SCREEN.md) records every starting row, signature disposition,
SDK call names and floating literals. `sweep.py` regenerates it without
changing status.csv. Sixteen T-072 reservations and the fifteen documented
private-ABI libaudio rows were excluded from implementation. Screening does
not mean that every game function received a matching attempt.

| Function | Candidate SDK name | Evidence / result |
|---|---|---|
| func_8003EF90 | **alFxNew** | **MATCHED**, 1,048 B. Six preset/custom parameter cases, indexed delay sections, resampler and lowpass allocations; exact SDK ALDelay/ALLowPass/ALResampler layouts and u16 i/j/k. Reference: audio/drvrNew.c. |
| func_80037780 | **_bnkfPatchInst**, with inlined _bnkfPatchSound/_bnkfPatchWaveTable | **IMPROVED 64→63** differing words, 256→252 / 244 B, in owning TU. flags at instrument+3/sound+14/wave+9; sound array at +16; ADPCM book/loop versus raw loop relocation. Reference: audio/bnkf.c. Original has an additional jr-ra/nop return stub and receives table in a3 rather than the public source's a2; no attempt to force that private signature or synthesize the extra stub. |
| func_80038DE0 | **__getTrackByte** | **UNCHANGED**, 47 words, 192 / 196 B. Exact 0xFE escape/backreference format, curLoc[16] at +0x18, curBUPtr[16] at +0x58, byte curBULen[16] at +0x98. Reference: audio/cseq.c. Verbatim statement sequence and backup arithmetic still differ in scheduling/temp allocation. 250 source-line layouts (`track_probe.py`) gave no improvement. |
| func_80039C08 | **alAudioFrame** | **UNCHANGED**, retained draft 160 words, 608 / 648 B. Earliest client callback search, ~15 sample quantization, microseconds→samples with 1,000,000.0 and 0.5, aSegment, output filter setParam/handler, _collectPVoices. Reference: audio/synthesizer.c. Source helper-call form emits 448 B/162 words; expanded helpers emit 612 B/161 words. Original reflects inlined helper stack/alias lifetimes, not reproduced by these ordinary C versions. |
| func_80042198 | **alFxParamHdl** (already identified in T-035) | **UNCHANGED / skipped**, no rewrite. Parameter dispatch and 16777215.0 / 173123.404906676 match SDK audio/reverb.c. Existing T-035 draft and asm-owned pool/jump table remain. |
| func_8002AB90 | possible **amCreateAudioMgr** demo derivative | **UNCHANGED / weak candidate**, no reference identity established. Configures DMA proc, rounds frame samples, allocates command lists and three audio frames, creates message queues/audio thread. Includes game-specific custom FX parameters. |
| func_8002B034 | possible **__amHandleFrameMsg** demo derivative | **UNCHANGED / weak candidate**, no reference identity established. Uses AI queue length, computes frame size, calls alAudioFrame, constructs RSP task and sends scheduler message. |
| func_8002B1EC | possible **__amHandleDoneMsg** demo derivative | **UNCHANGED / weak candidate**, no reference identity established. Small AI completion/underrun routine adjacent to audio-manager code. |

The demo labels are search leads, not confirmed identities. No public-source
implementation was substituted for them. The game sound-player functions
around 0x8002E4A0 use libaudio event/voice APIs but custom globals, voice
records and grouped-volume state; SDK API calls alone do not establish
alSndp* identity. Matrix callers such as 0x80029BE0/0x8002B9B4 and screen
projection at 0x8002DDD4 are game transformations, not newly found gu helpers.
The decoder/pixel kernels at 0x80031050–0x800327E8 have private state,
computed stores and arithmetic coding, not the SDK matrix/vector signatures.
No additional hidden osPfs candidate or unnamed gu helper was identified.

## References and reproduction

Public references consulted:

- https://github.com/n64decomp/libreultra — revision `1aca5c13ca041cef86f8dc194b727361dad9c09b`
- https://github.com/decompals/ultralib — revision `e24c836796df4bf520ff8b11a5c9d2cea3a66cbd`

The strong-candidate files under this directory (`bnk.c`, `track.c`,
`frame.c`, `fx.c`) retain the tested adaptations. The bank improvement also
replaces its old T-026 draft. The track/frame production functions and their
old drafts remain unchanged. Counts are positional instruction-word
comparisons, masking real ELF relocation fields and including size differences;
they are diagnostics, not behavior validation. T-055 `ctx.py` compiles in
the actual owning TU after removing other GLOBAL_ASM pragmas. Its `sc.py`
expects `/tmp/t055ref/main.bin`; use a symlink to `build/segments/main.bin`.
For alFxNew the final linked build is the matching proof.

## Matched alFxNew and rodata ownership

`src/main/main_2F2A0.c` replaces only func_8003EF90's GLOBAL_ASM with the
SDK-derived C. Types are local adaptations; symbol spellings stay unchanged.
The older target uses the reference source's commented historical rsinc
formula `(f32)param[j++] / 16777215.0f`, rather than its newer
`frequency / 1000 * 2 / outputRate` formula. The remaining source algorithm
is unchanged. Both 16-bit parameter-index truncation and 8-byte-aligned
ALLowPass coefficient storage matter. The old draft's advancing s32 pointer
and field layout did not reproduce them.

The complete main_2F2A0 rodata is **0x39C50–0x39C80**, aligned at both ends:

| Image offset | Address | Contents |
|---|---|---|
| 0x39C50–0x39C68 | 0x800495B0 | six-entry switch table |
| 0x39C68 | 0x800495C8 | float 16777215.0 |
| 0x39C6C | 0x800495CC | alignment zero |
| 0x39C70 | 0x800495D0 | double 173123.404906676 |
| 0x39C78–0x39C80 | 0x800495D8 | trailing alignment zero |

A scan of all generated assembly in main_2F2A0 finds these references only
in func_8003EF90. The preceding D_800495A8 belongs to the sequence-player
code; the next jtbl_800495E0 belongs to alResampleParam. YAML gives the
complete range to `[0x39C50, .rodata, main_2F2A0]` and resumes asm data at
0x39C80 as main_after_2F2A0. This follows T-073; no symbol hints or renames
are needed. The existing neighboring GLOBAL_ASM functions are retained.
Default IDO 5.3 -O2 -mips2 matches; no -mips1 override was warranted.

Deleted matched draft: `tools/scratch/nonmatching/T-026/func_8003EF90.c`.

## Final validation

`make clean && make extract && make all && make progress` passed in an
isolated final run. The ROM and all three images are byte-identical:

- ROM: `ba52e91b44450c548467044b26951353dc491e04`
- main: `81736d32e8cda8f399b319a49250dff972b81af8`
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`

The full main_2F2A0 text slice 0x2F2A0–0x2FA50 and its rodata slice
0x39C50–0x39C80 also compare exactly. The linker places the C rodata at
0x800495B0 with size 0x30. `git diff --check` passes. Regenerated
linker_scripts/*.undefined_syms.txt files are retained (no net changes).
Generated docs/functions.csv and docs/progress.html were restored after
recording the table. Lead-maintained status.csv is untouched.

Missing baserom.us.z64, ROMs, .venv and tools/ext were symlinked from
`/home/rodri/Projects/killer-instinct-gold-n64`. No ROM was copied or added
to git. No inline asm, register bindings, forced registers or padding arrays
were used. Earlier overlapping local validation processes produced transient
build errors; the final sequence above ran after all of them had exited.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 70,556 (22.11%) | 70,556 (22.11%) | 0 | 272 | 0 | 290 | 437 (138,092) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 173,204 | 44,288 (25.57%) | 44,288 (25.57%) | 0 | 126 | 0 | 164 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 17,800 (12.95%) | 17,800 (12.95%) | 0 | 146 | 0 | 105 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
