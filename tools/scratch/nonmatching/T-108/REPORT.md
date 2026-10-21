# T-108 — sol-C40: game audio subsystem types

**Shared header adopted in three TUs; all 29 existing C matches preserved.
No additional GLOBAL_ASM function matched. Three drafts improved; all seven
remaining audio drafts now compile in their complete owning TUs using the
shared types. No commits.**

## Scope and evidence

Read TRACKING, the latest WORKLOG, overview (including the audio sections and
TU table), Makefile, game/SDK audio headers, T-075/T-078/T-081 and the latest
relevant T-089/T-092/T-095/T-096/T-097/T-099/T-102/T-104 findings. The adjacent
`main_1AB90.c` sequence-control TU is included; the intervening rendering TUs
and all SDK audio TUs are excluded from edits.

`include/audio_game.h` provides the following o32 layouts. Unknown storage is
explicitly reserved rather than assigned speculative meanings. Size-check
typedefs verify the frame, voice, player and SDK-compatible event sizes under
IDO; they emit no data.

| Type | Layout / evidence |
|---|---|
| `AudioMessageQueue` | 0x18-byte SDK queue layout. Manager queues at 66E18/66E50/683F8 are followed by message arrays at 66E30/66E68/68410. Initializer supplies capacities 8/8/32. |
| `AudioDmaBuffer` | 0x14 bytes: next/prev +0/+4, ROM start +8, frame age +C, sample buffer +10. B22C loads every field; B3E0 walks and recycles links; AB90 allocates 32 buffers of 0x800 bytes. |
| `AudioDmaPool` | Initialized byte +0, used/free heads +4/+8. B3A8 initializes it, B22C allocates, B3E0 retires by `frame + 1 < D_80048150`. |
| `AudioSettings` | Rate +0, **unsigned** frame count +4, command count +8. AB90's `bgez`/2^32 float conversion proves the unsigned frame-count conversion. |
| `AudioManagerBuffers` | 0x14-byte heterogeneous pointer table: two command lists then three frames. A union documents both typed roles and preserves the original slot indexing used by matching C. No aggregate is invented across unrelated globals. |
| `AudioRspTask` | 0x40-byte OSTask layout at frame +20. B034 writes audio type, flags, boot/code/data pointers, commands +30/length +34 and yield +38/+3C. Unaccessed middle fields remain reserved. |
| `AudioFrame` | Allocation 0x88. Sample buffer +0, signed sample count +4; scheduler message starts +8; task type +14; embedded RSP task +20; completion queue +60/message +64; completion record +68 (halfword type, frame pointer +6C). AB90 uses **sh** at +68 and reloads the slot before storing self at +6C. Tail +70..87 remains unknown. |
| `GameAudioVoice` | 0x40. Links +0/+4, `ALSound *` +8, embedded **ALVoice** +C (0x1C bytes), ratio/pitch +28/+2C, owner-pointer +30, volume s16 +34, allocation **priority +36**, retries +38, **pan +3C**, fx/flags/state +3D/+3E/+3F. F45C initialization, F5F0 release and E724 call arguments establish these fields. Earlier partial drafts interchanged the priority/pan names. |
| `GameAudioEvent` | 0x10: halfword type, voice +4, integer/float/repeat-ID union +8, bank +C. E724 loads the repeat ID with `lh +A`, and F6F4 stores its sign-extended integer at +8. Fits the SDK `ALEvent` copy size. |
| `GameAudioPlayer` | 0x58: embedded **ALPlayer** +0 (0x14 bytes), **ALEventQueue** +14 (0x14), game event +28 (0x10), **ALSynth pointer** +38, current voice +40, pool +44, maximum physical voices +48, interval/delta/time +4C/+50/+54. E4A0 allocations and E680/E724 accesses agree. The config's former `priority` is the cap compared against D_80048280, not a scheduling priority. |
| `GameAudioVoiceLists` | Three pointers at D_80048270: active head, active tail, free head. F45C and F5F0 mutate all three; F3DC counts both forward lists and the backward tail walk. |
| Cancellation event views | Item size 0x1C with next/prev, delta +8, event type +C, voice +10 and remaining payload. Queue is the SDK's two link sentinels plus count. F31C follows allocated.next at queue +8 and repairs the next delta before unlinking. |

SDK `ALSound`, `ALKeyMap`, `ALEnvelope`, `ALBank`, `ALSeqFile`, `ALCSeq`,
`ALCSPlayer`, `ALSynConfig`, `ALGlobals`, `ALHeap`, `ALVoiceConfig` and
`BootDmaMessage` are reused rather than cloned. The game repurposes ALKeyMap
bytes: velocityMin is the next chain ID, velocityMax is its delay multiplier,
keyMin contains group/high-ID bits, and keyMax carries flags/FX bits.

The group-volume global remains `u16 *`: FAA0 uses lhu. The dispatcher uses
an explicit signed-halfword view because its volume arithmetic uses lh.
The event clock's local tick event retains its unsigned halfword type.
`GameAudioGroupEvent` preserves FAC0's pre-existing 24-byte local workspace;
this does not assert that the queue copies more than its 16-byte event.

## Header adoption

| TU | Preserved matches | Result |
|---|---:|---|
| main_1AB90 | 7/7 | Sequence players and sequences typed, actual `ALSeqFile.seqArray[index].offset` replaces the misleading offset-table view. SDK prototypes replace local opaque declarations. |
| main_1B230 | 5/5 | Shared frames/RSP task, typed completion-frame pointers, real queues/DMA records, typed DMA callback return and manager buffer table. |
| main_1EB40 | 17/17 | Shared player/voice/event layouts, SDK embedded records and explicit SDK base-pointer casts replace independent per-function partial types. |

E680 now returns `ALMicroTime delta`, matching the SDK callback contract and
the original unchanged v0 return value. Its typed player argument and
ALVoiceHandler cast remain: changing the argument to void* plus a local player
alias changed four instructions and was reverted. Using the signed shared
event as E680's local tick record changed seven instructions (constant/temp
allocation); the original unsigned tick-record view was restored. Both final
E680 and its initializer are exact. No mismatching header adoption remains.

## Remaining functions

`probe.py` compiles each candidate inside the **complete current TU** through
asm-processor, IDO 5.3 -O2 -mips2 -32 and the normal assembler. It compares
against extracted original main bytes, masking only ELF relocation fields.
Counts are positional differing words, including size differences; these are
not behavior-validation claims. `results.json` records the final measurements.

| Function | Incoming → retained differing words | C / original bytes | Result / diagnosis |
|---|---:|---:|---|
| 8002A4F0 | 31 → 31 | 920 / 920 | Shared SDK/game config types and sequence-file fields now work in the complete TU. Settings/size stack slots and sequence-loop induction remain. |
| 8002A900 | 15 → 15 | 220 / 220 | Full-TU declaration conflicts removed. +00..24 frame/index/counter ownership and +58..64 sequence-player setup remain. |
| 8002AB90 | 208 → 119 | 852 / 852 | Improved from fresh incoming standalone/prefix measurement (816 bytes; old draft comment said 210). Correct unsigned frame conversion, signed truncation then unsigned conversion back for rounding, completion sh/self-pointer fields and pointer-based command/frame allocation loops. Final measurement is complete-TU. Extra n move/rounding, config/induction registers, local parameter-copy stack position and loop scheduling remain. |
| 8002B22C | 85 → 74 | 380 / 380 | Put the address-order exit **inside** the non-null list loop. This recovers the original body length (incoming 396) and branch structure. Remaining: pool/input register lifetimes, address-end temporary, spills, call scheduling and list insertion. |
| 8002E724 | 660 → 658 | 2728 / 2832 | Uses shared real SDK/game types; unsigned type reads, signed volume view and linked-tail reference are explicit. Still a large dispatch/control-flow, stack/register and scheduling mismatch. Its rodata already belongs to this TU after T-091; no YAML or ownership changes needed or made. |
| 8002F45C | 4 → 4 | 404 / 404 | +B4/+C0 decay-time load/add uses a1 rather than v1; +DC/+E4 flag load/mask uses v1 rather than t3. Shared voice and SDK key/envelope types preserve the best code. |
| 8002F6F4 | 2 → 2 | 516 / 516 | +68/+160 step load/store still uses sp+74 rather than sp+64. Real bank/instrument/sound indexing and player.current replace raw pointer arithmetic. Coherent timing aggregates worsened other slots (best four differences), so were rejected. |

All seven drafts were updated **in place** in T-024 to use the shared header.
No function reached zero, so no GLOBAL_ASM or draft was deleted. Initializer
and cache rewrites that worsened size/register allocation were discarded.
In particular, converting the truncation destination itself to unsigned
introduced FCSR conversion sequences absent from the original; retained C
truncates to s32 and only converts the subsequent value to u32 for the float
comparison. No uninitialized-step workaround was added to F6F4: initializing
it would change the original instruction stream.

Experiments include complete-TU scoring, ordinary expression and declaration
orders, multiline layouts, pointer/counter loop forms, timing-record layouts,
and a 900-second local decomp-permuter search of F45C with three local
workers, --stack-diffs and --stop-on-zero. It completed 6,211 iterations
(49 compile errors), retaining its initial weighted penalty 20 / four words;
no improved candidate was emitted. The import helper's GCC
preprocessing initially omitted `_LANGUAGE_C`, hiding ABI declarations; the
disposable base was regenerated with that define. No helper/build-system edit
was needed. Some later whitespace probes encountered changing-header compile
errors; those errors are not scores or improvements. No raw permuter output,
objects, assembly dumps or large logs are retained in the repository.

## Verification

`make clean && make extract && make all && make progress` passed (exit 0).
`git diff --check` passed. The ROM and all executable images are byte-identical:

- ROM: `ba52e91b44450c548467044b26951353dc491e04`
- main: `81736d32e8cda8f399b319a49250dff972b81af8`
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`

The three adopted TUs compiled without warnings. No task search/probe
process remains; the permuter ended with the configured timeout (exit 137).

No status.csv, Makefile, YAML, boot, overlay or SDK source edits. The shared
prerequisites missing from this worktree were symlinked from the authorized
main checkout. No ROM was copied into git or committed. No commits were made.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 66,512 (22.94%) | 66,512 (22.94%) | 0 | 204 | 0 | 305 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 30,556 (21.22%) | 30,556 (21.22%) | 0 | 91 | 0 | 146 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 27,488 (20.00%) | 27,488 (20.00%) | 0 | 113 | 0 | 138 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
