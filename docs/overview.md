# Code architecture — US V1.0

T-107, sol-A36, 2026-10-20. This is a static architecture map for matching
work, not a runtime trace or a recovered original design. Addresses and ranges
are CPU VRAM, half-open, unless explicitly marked ROM. No ROM contents are
reproduced here. Current names come from source/symbol files; names after **→**
are suggestions only. No renames are proposed as part of this task.

**Confidence:** **high** means a direct source operation, SDK identification or
independently documented loader/format fact; **medium** means a role supported
by callers and data flow but not verified in play; **low** means a working
hypothesis. Confidence applies to semantics, not matching status. A matching
function can still have an uncertain interpretation. Scratch drafts are useful
evidence, but are not behavior-validated replacements. In particular, do not
turn their provisional structs into shared headers without checking assembly.

## Image lifetime and entry paths

| Image | CPU text | Initialized image | Lifetime / role |
|---|---|---|---|
| boot | 0x80000400–0x80006560 | through 0x800072D0 | Resident startup, DMA, inflate, scheduler and SDK services (**high**, [boot.md](boot.md)) |
| main | 0x8000F960–0x80042710 | through 0x8004A230 | Resident game orchestration, rendering, audio/input managers and SDK (**high**, main entry and [segments.md](segments.md)) |
| ovl_7DF8 | 0x801ABB20–0x801CD450 | through 0x802956F0 | Frontend/mode orchestration, menus, scores, endings and Pak UI (**high** for these components; **medium** for the aggregate label, evidence below) |
| ovl_7E00 | 0x801AD900–0x801C3F40 | through 0x801D3230 | Custom-ABI gameplay module (**medium** semantic label; **high** assembly-module evidence, [ovl_7E00_asm.md](ovl_7E00_asm.md)) |

The 0x7E00 text endpoint above follows its analyzed text partition; older
loader cache bounds and data splits can include additional padding (the main
loop uses 0x801C3FC0). Do not infer a new TU boundary from that difference.

The actual load sequence is boot → main → alternating frontend/gameplay
phases, not boot loading both overlays at startup:

1. **High:** entry 0x80000400 clears boot BSS and enters
   `boot_start` (0x80000450). `boot_idle_thread` (0x800004AC) initializes PI,
   launches thread 3 to run `boot_load_main` (0x80000520), then becomes idle.
   The loader uses table entry ROM 0x7DF0, DMA staging at 0x802D4000,
   destination 0x8000F960 and inflate scratch at 0x803A2000; it calls main.
   Cold and reset startup clear different RAM ranges. [boot.md](boot.md)
   is the authority for this resident path and its memory aliases.
2. **High:** `func_8000F960` → `gameMain` initializes main BSS, the resident
   scheduler, retrace subscription, audio and controller services. Its endless
   loop calls `func_8000FA80`, then `func_8002A900(0x11)`.
3. **High:** `func_800121C8` → `runFrontendOverlay` loads table entry ROM
   0x7DF8 to 0x801ABB20 and calls `func_801ABB20`. DMA uses 0x802D6000,
   inflate scratch 0x802D4000. Exact call sites and cache bounds are in
   [segments.md](segments.md). **Medium:** this is the frontend phase before
   a fight/session: `func_8000FA80` calls it before loading 0x7E00
   ([T-033 draft](../tools/scratch/nonmatching/T-033/func_8000FA80.c)).
4. **High:** `func_8000FA80` loads table entry ROM 0x7E00 through
   0x802D4000 to 0x801AD900, with scratch 0x803A2000. It loads two indexed
   data tables via `func_80012100`, stage data via `func_80012A8C`, invokes
   a main-image stage callback, then calls `func_801AD900`.
   **Medium:** this is the fighting-engine phase, supported by the adjacent
   two-player state, animation, HUD and replay setup in T-033/T-085.

**High:** the overlays overlap in both initialized storage and working state;
only one complete image can be live. Main/boot services survive their exchange.
The eleven table entries ROM 0x7E08–0x7E58 are data loaded to 0x801DB000 /
0x801E5000, and the thirteen graphics entries ROM 0x7E60–0x7EC0 reuse
0x802D4000. Extraction's `ovl_` prefix does not make these executables. There
are 27 table entries but 26 distinct payloads because graphics slot 12 aliases
slot 6 ([segments.md](segments.md)). **Medium:** the two data slots are
fighter-specific tables: their indices are the two selected character bytes
`D_8004EA9C[2]` in `func_8000FA80`; their exact record semantics remain open.

## Scheduler, threads and retrace

**High:** this subsystem belongs to resident boot, especially
`src/boot/boot_29F0.c`,
0x80001DF0–0x80002590; main's `main.c` 0x8000F960–0x80012950 supplies its
client queue. The authoritative function map is [boot.md](boot.md):

| Address / current name | Role |
|---|---|
| 0x80001DF0 `boot_init_scheduler` | VI manager at priority 254; scheduler thread 20 at priority 13 |
| 0x80001EF4 `boot_subscribe_retrace` | Up to three queue subscribers; first argument unused |
| 0x80001F2C `boot_scheduler_thread` | Event 0 retrace, 1 DP done, 2 SP done; yield graphics for audio |
| 0x800022C0 `boot_start_graphics_task` | Start/resume graphics SP work |
| 0x80002420 `boot_schedule_graphics` | Dequeue and coordinate SP/DP graphics work |
| 0x8000FA50 `func_8000FA50` → `initMainRetraceQueue` | Creates eight-message queue at `D_8004A298` |
| 0x8002AEE4 `func_8002AEE4` → `audioManagerThread` | Separate retrace subscriber; dispatches frame/completion/quit messages |

**High:** named resident state includes `boot_graphics_task` 0x80006678,
`boot_audio_task` 0x8000667C; graphics/audio/scheduler queues at
0x8000CF50/0x8000CF68/0x8000CF80; subscribers 0x8000D180 and count
0x8000D18C. The state bytes at 0x8000D194–0x8000D199 describe audio running,
graphics/DP states, SP activity, swap readiness and resume count
(`symbol_addrs.us.txt`). `BootTask` in [include/boot.h](../include/boot.h)
interprets framebuffer at +0x10, embedded 0x40-byte OSTask at +0x18, and
completion queue/message at +0x58/+0x5C. Preserve unknown fields.

**High:** main uses `D_80044A24` as alternating frame index,
`D_8004A428[2]` for framebuffers, `D_8004A418[2]` for command-buffer bases
and `D_8004A420` for the current command cursor (T-033 and rendering C).
**Medium:** `D_8004A414` is outstanding graphics work: submission increments
it and type-2 completion decrements it in the frame-loop draft. It should not
be called a frame timer without tracing all accesses.

## Audio: game layer versus SDK

**High:** SDK synth/sequence/effects code is excluded from game matching
metrics. `alSyn*`, `alSeq*`, `alCSeq*`, `alCSP*`, `alEvtq*`, `alFx*` and their
private helpers occupy many late-main TUs; the TU table distinguishes these
from game code. [libultra.md](libultra.md), T-073/T-075/T-078 document their
identification and reconstruction. A remaining `func_` name does not imply
game provenance: 0x80039C08 `func_80039C08` is the SDK `alAudioFrame`
algorithm, and 0x8003EF90 `func_8003EF90` is SDK `alFxNew` (**high**, T-075).

The game-facing layer is spread across, rather than filling every byte of,
0x8002A000–0x8002F000:

| TU / range | Key entry → suggested name | Role and evidence |
|---|---|---|
| `main_1AB90.c`, 0x8002A4F0–0x8002AB90 | 0x8002A4F0 `func_8002A4F0` → `initGameAudio`; 0x8002A9DC `func_8002A9DC` → `loadSecondarySequence` | **High** sequence-player integration: DMA, stop/wait, `alCSeqNew`, `alCSPSetSeq`; initializer name **medium**, entry caller |
| same | 0x8002AA98 / 0x8002AAEC `func_8002AA98` / `func_8002AAEC` → `setPrimarySequenceVolume` / `setSecondarySequenceVolume` | **High**, settings multiplier then `alCSPSetVol` |
| `main_1B230.c`, 0x8002AB90–0x8002B500 | 0x8002AB90 `func_8002AB90` → `createAudioManager`; 0x8002AEE4 `func_8002AEE4` → `audioManagerThread` | **High** observed allocation/thread/queue role; **low** exact `amCreateAudioMgr` demo ancestry (T-075 explicitly unconfirmed) |
| same | 0x8002B034 `func_8002B034` → `submitAudioFrame`; 0x8002B1EC `func_8002B1EC` → `handleAudioDone` | **High** AI queue sizing, audio-frame generation and scheduler submission; **medium** completion-handler semantic name |
| same | 0x8002B3A8 `func_8002B3A8` → `getAudioDmaProc`; 0x8002B3E0 `func_8002B3E0` → `retireAudioDmaBuffers` | **High**, DMA pool initialization and frame-aged used/free list recycling |
| `main_1EB40.c`, 0x8002E4A0–0x8002FB80 | 0x8002E4A0 `func_8002E4A0` → `initGameSoundPlayer`; 0x8002E680 `func_8002E680` → `advanceSoundEvents`; 0x8002E724 `func_8002E724` → `dispatchSoundEvent` | **High**, custom group volume, linked voices and libaudio event/synth APIs (T-075/T-081); exact SDK `alSndp*` identity is unsupported |

**High:** `D_800669C0` / `D_800669C4` are two compressed-sequence players;
`D_80066C28` / `D_800669D0` supply sequence addresses/lengths and
`D_80066A34` is a load buffer. `D_80066C50` indexes command lists and audio
frames; `D_80066E18` / `D_80066E50` are retrace/completion queues.
`D_80068158` is the DMA pool and `D_80067ED8` its buffer records.
`D_80048158` toggles command buffers; `D_80048150` advances the DMA frame age.
Evidence: `main_1AB90.c`, `main_1B230.c`.

**High:** custom sound player `D_8004827C` allocates 0x40-byte voice records;
`D_80048278` tracks the voice pool, `D_80048440` the synth and
`D_80069928` the group-volume array initialized to 0x7FFF. T-081 recovers
voice fields: sound +8, synth voice +0xC, ratio/pitch +0x28/+0x2C,
volume +0x34, retries +0x38, pan/FX/flags/state +0x3C..+0x3F.
Its player has event queue +0x14, synth +0x38, maximum voices +0x48;
events contain a halfword type, voice pointer and payload union. The
production TU has several partial views of these layouts; they are evidence
for fields, not yet one authoritative unified struct.

## Controllers and persistent data

**High:** `main_1BBA0.c`, 0x8002B500–0x8002B7E0, wraps SI/controller SDK calls:
0x8002B500 `func_8002B500` → `initControllerQueue`,
0x8002B57C `func_8002B57C` → `detectControllers`,
0x8002B6EC `func_8002B6EC` → `startControllerRead`, and
0x8002B710 `func_8002B710` → `finishControllerRead`.
It registers event 5 (SI), starts asynchronous reading, then blocks for
completion before `osContGetReadData`. `D_800684B8[4]` contains six-byte pad
records (u16 buttons, s8 stick x/y, error, padding); `D_800684A8[4]` contains
four-byte status records. `D_800684D0[4]` supplies pad pointers,
`D_800684E0` is the queue, and `D_80068520` the current valid-controller mask.

**High:** 0x80011FC4 `func_80011FC4` → `mapControllerToGameButtons` uses
`D_80127CA8[][6]` for six configurable actions and maps D-pad/stick directions
to bits 0x40..0x200, with stick thresholds greater than 40 / less than -40.
The record is a four-byte buttons/x/y view, not the whole SDK pad struct.
**Medium:** 0x8001178C `func_8001178C` → `updatePlayerInputsAndPause` also
constructs player snapshots and dispatches pause state (T-033/T-085).

**High:** the late-main `osPfs*`, `__osPfs*`, `__osContRam*` functions are
SDK Controller Pak code, now SDK-named, rather than game save logic.
Principal TUs: `main_24820`, `24B50`, `24E70`, `26480`, `265B0`, `26860`,
`2BA80`, `2CA60`, `2CDF0`; ranges and counts below. T-035/T-037/T-055/T-083
supply identification/matching evidence; old reports' `func_` names are stale.
`OSPfs`, inode/ID pages and file-state records belong to SDK interfaces
(see the PFS declarations in those TUs); do not merge these with game save
records merely because both touch the Pak.

**High:** `ovl_7DF8_200C0.c`, 0x801CBBE0–0x801CD450, is the game-facing
Pak layer. 0x801CBBE0 `func_801CBBE0` → `queryPakPresence` builds a presence
mask from four controller query records; 0x801CBCCC `func_801CBCCC` →
`pakWorkerThread` waits on messages and dispatches operations;
0x801CCEAC `func_801CCEAC` → `pakNameToAscii` converts file names (T-034).
`D_802D3FC8` is its worker queue; `D_802D3E14/15` participate in operation
status. **Medium:** precise status-byte meanings need an operation-by-operation
trace. EEPROM SDK objects are separate; their presence alone does not establish
which game settings are stored on cartridge versus Pak.

## Rendering and text

**High:** rendering is shared between main and the frontend overlay, rather
than isolated inside one executable overlay. Main stage code lives largely in
`main_2FF0.c` (0x80012950–0x8001C370), object/matrix emission in
`main_CA10.c` (0x8001C370–0x8001CD50), sprite/animation/asset work in
`main_D3F0.c` (0x8001CD50–0x80024CE0), HUD in `main_15380.c`
(0x80024CE0–0x80026AA0), and camera transforms in `main_1BE80.c`
(0x8002B7E0–0x8002E150). These are broad roles; individual untraced entries
inside a mixed TU must retain uncertain names.

| Address / current name → suggestion | Confidence and evidence |
|---|---|
| 0x8001256C `func_8001256C` → `emitFramebufferClear` | **High**, emits color image, RGBA5551 fill color, fill rectangle and sync commands |
| 0x80012A8C `func_80012A8C` → `loadStagePacket` | **High**, indexed DMA/inflate; stage callbacks `D_800451EC`, [gfx_format.md](gfx_format.md) |
| 0x8001C0E4 `func_8001C0E4` → `expandStageBatches` | **High**, arrays of counted command/vertex batches, calls 0x8002FFDC |
| 0x8001C5AC `func_8001C5AC` → `emitStageObjectTransforms` | **High** transform/list builder; **medium** object naming, T-069 matched C |
| 0x8001D7E4 `func_8001D7E4` → `selectPlayerAnimationFrame` | **Medium**, paired normal/fallback animation pointers indexed by animation/player, T-069 |
| 0x8001E33C `func_8001E33C` → `drawPlayerSprite` | **High**, position/flip/tint/flash paths, T-081 |
| 0x80020E98 `func_80020E98` → `loadSpriteBank` | **High**, sprite/portrait destinations, frame caches, palette DMA, T-081 |
| 0x800238C4 `func_800238C4` → `decodeUiByteSpans` | **High**, palette byte offsets and coverage spans, gfx_format/T-069 |
| 0x80025354 `func_80025354` → `initHudSprites` | **High**, four descriptors and health/display counter clears, T-032 |
| 0x800257FC `func_800257FC` → `drawHealthBar` | **High** health/player/flash parameters and clipping, T-069 |
| 0x8002BBD0 `func_8002BBD0` → `updateCameraState` | **Medium**, large camera state machine, T-085 |
| 0x8002DDD4 `func_8002DDD4` → `projectWorldToScreen` | **High** screen projection role, T-075; game transform, not SDK gu identity |
| 0x8002FB80 / 0x8002FDA0 `func_8002FB80` / `func_8002FDA0` → `expandStageCommands` / `expandStageVertices` | **High**, counted tagged command and delta-vertex streams, gfx_format |
| 0x8002FFDC `func_8002FFDC` → `expandStageBatch` | **High**, combines both decoders |
| 0x80030020 / 0x800300DC `func_80030020` / `func_800300DC` → `decodeStageTextures` / `decodeRgba16Backrefs` | **High**, type/count dispatch and RGBA16 backreferences, gfx_format |

**High:** T-069 establishes two-word/eight-byte `Gfx` records, 64-byte
s64-aligned matrices, three banks of twenty matrices per frame (0x500 bank,
0xF00 frame). `D_8004A998` holds four display-list pointers per group;
`D_8004AEB8` supplies matrix storage, with active-frame state `D_80044A24`.
T-081's 0x800142E0 builder has 200 commands per frame (0x640 stride),
scissor/combiner/image/tile setup, clipped strips and final fill/sync. These
are distinct buffers/layouts, not contradictory sizes for one allocation.

**High:** observed command families include E7 pipe sync, BA/B9 mode changes,
FC combiner, FD texture image, F0 TLUT loading, F2 tile size, F6 fill rectangle,
F7 fill color, FF color image, 04 vertices and BF triangles. Command words are
format evidence, not sufficient image-boundary detection. Stage packets use
unaligned tagged commands: tags 00 copy a command, 01 reference a texture,
10 expand a triangle, 11 expand vertices. Main sprite rendering uploads
expanded RGBA16 color and separate coverage; the FD900000 load does not make
source sprites ordinary CI8 textures. Portrait rendering really uses CI8 and
a converted palette. Details and decoding limits: [gfx_format.md](gfx_format.md).

**High:** the main sprite descriptor is 28 bytes; T-081's player drawing record
is a separate 0x30-byte structure with position floats +0xC/+0x10/+0x14,
flip +0x21, kind +0x22 and signed RGB adjustments +0x28/+0x2A/+0x2C.
`D_8004CED0` holds sprite descriptors, `D_8004EA78` is a sprite/cache pointer,
and `D_8004A4C0` / `D_8004A998` participate in stage/render data
(T-069/T-081, main sources). Do not equate these with the larger engine player
records at `D_801D3430` merely because all are indexed by player.

There are at least two text paths:

- **High:** main `main_20AE0.c`, 0x80030440–0x80031050:
  0x800306B8 `func_800306B8` → `drawGlyphString2D` measures/centers strings,
  clips and emits glyph rectangles; 0x80030EF0 `func_80030EF0` →
  `charToGlyphIndex` maps characters. Four-byte glyph metrics are width,
  height, spacing and baseline; colors are four bytes and scales signed words.
  Mirrored variants use signed texture steps; glyph 0x47 changes combiner
  state (T-081). Decoder helpers in 0x80031050–0x80032C30 are a different
  concern from string layout.
- **High:** overlay `ovl_7DF8_116E0.c`, 0x801BD200–0x801BE790, contains
  glyph/matrix text rendering: 0x801BDA6C `func_801BDA6C` is a glyph/highlight
  builder (T-076); 0x801BDF94 `func_801BDF94` → `drawTransformedGlyphString`
  can rotate the string, stagger glyphs, set lighting and emit per-glyph
  translate/rotate/scale/list commands. Its eight-byte glyph records contain
  a display-list pointer and float width; signed glyph indices, special
  punctuation and fixed-advance handling are documented by T-079.
  0x801BE660 `func_801BE660` is another spacing/text helper (**medium** exact
  role, T-095). These metrics are not main's four-byte bitmap metrics.

## Game flow and overlay responsibilities

**High:** `func_8000F960` is the permanent outer loop. **Medium:**
`func_8000FA80` → `runGameSession` encompasses frontend entry, gameplay-module
loading, stage/fighter setup and the active frame loop, rather than just one
frame. T-033 reconstructs task submission, camera, player snapshots, animation,
HUD and replay paths; T-085 warns that substantial details remain unmatched.
`func_8001178C` handles input/pause; the stage render dispatchers at
0x80012B7C / 0x8001346C belong to rendering, so their switches should not be
mistaken for the top-level game state enum.

**High:** `func_801ABB20` clears overlay BSS and dispatches `D_80295708`;
its attract substate is `D_8029571A`, with previous/return-state storage around
`D_80295710/14` (T-034 draft and source accessors). The entry loops until
state 10. **Medium:** suggested name `runFrontendStateMachine`; modes combine
menus, timed demonstrations and transitions back to gameplay. Numeric states
0/1/2/3/4/5/6/8/9 have intertwined initialization and return paths; assigning
complete names from only this draft would overstate confidence.
`D_8004A407`, `D_80127C40`, `D_80127D50` and `D_8012834B` affect mode/session
setup; their complete enums remain **low confidence**.

**High:** frontend ownership is supported independently of that state-machine
draft by score/name processing in `ovl_7DF8_12C70.c` and `_13FF0.c`, ending
text and portrait drawing in `_190B0.c`, and Pak operation/UI code in
`_200C0.c`. **Medium:** `_3F60.c` and the large `_5ED0.c` provide menu scenes,
transitions and UI animation; repeated interpolators and clone builders are
visual effects, not evidence of seven separate game states (T-025/T-077/T-097).
`_1BD90.c` includes replay/mode setup: 0x801C7CD0 `func_801C7CD0` →
`configureModeReplay` uses two u64 replay values and a narrowed mode byte
(**medium**, T-066). `_18520.c` contains a post-fight presentation initializer,
0x801C407C `func_801C407C` → `initFinishPresentation` (**medium** exact name,
source selects rating text and audio, resets camera and draws a scene).

**Medium:** 0x7E00 appears to own the fighting simulation/round engine while
main supplies platform services, assets, camera and rendering. Strongest
semantic evidence is its load and entry immediately after selected fighter
and stage setup, and subsequent consumption of `D_801D3430` player state by
main's frame loop (T-033). **Low:** exact ownership of hit detection, move
scripts, AI, round timer, victory and round transitions is not established by
current reports. Health-bar rendering and animation selection prove consumers,
not the location of authoritative combat updates. Future matching work should
trace producers before naming those fields/functions.

**High:** 0x7E00 is a cohesive assembly module with custom interfaces, persistent
`s8` context, scratch use of callee-saved and kernel registers, alternate
entries, cross-boundary branches and 31 inline data pools. Its 169 inventory
entries are not 169 independent o32 functions. All remain assembly/excluded;
seven compatible leaves have uncertain original provenance. **Low:** a precise
original module name cannot be recovered from register conventions alone.
See [ovl_7E00_asm.md](ovl_7E00_asm.md), including T-041's padding result.

## TU inventory and matching snapshot

Ranges below come from the current `c` subsegments in `kig.main.us.yaml` and
`kig.ovl_7DF8.us.yaml`, ending at the next text subsegment. They include TU
alignment padding; inferred historical boundaries are qualified in
[tu_boundaries.md](tu_boundaries.md). Current SDK extraction has split some
of the original 87 main groups further, so this table follows today's files.

Counts are read directly from [functions.csv](functions.csv): **T4 / total**
inventory rows in each range, plus an **excluded** column. Excluded SDK
functions can be matching C yet have tier `excluded`, so T4/total is deliberately
not a C-coverage percentage. No source-pragma counting or old worker totals
are substituted. Role confidence/evidence is carried in each row; a first
function anchor identifies where to begin inspection, not proof of every
function in that TU. All paths are relative to `src/main/` or `src/ovl_7DF8/`.

### main

| File | Address range | Inferred role — confidence; evidence | T4 / total | Excluded |
|---|---|---|---:|---:|
| `main.c` | 0x8000F960–0x80012950 | Startup, session/frame orchestration, input mapping, overlay loading — **high**; 8000F960 / T-033 | 9 / 14 | 0 |
| `main_2FF0.c` | 0x80012950–0x8001C370 | Stage loading, callbacks and display-list builders — **high**; 80012A8C / gfx_format | 47 / 71 | 0 |
| `main_CA10.c` | 0x8001C370–0x8001CD50 | Stage objects, matrices and display-list groups — **high**; 8001C5AC / T-069 | 7 / 7 | 0 |
| `main_D3F0.c` | 0x8001CD50–0x80024CE0 | Sprite banks, animation, palettes and player rendering — **high**; 8001E33C / T-081 | 11 / 28 | 0 |
| `main_15380.c` | 0x80024CE0–0x80026AA0 | HUD sprites, health and UI geometry — **high**; 80025354 / T-032; T-069 | 1 / 9 | 0 |
| `main_17140.c` | 0x80026AA0–0x80027DA0 | Additional HUD/display-list composition — **medium**; 80026AA0 / source | 1 / 2 | 0 |
| `main_18440.c` | 0x80027DA0–0x8002A150 | Camera/scene initialization and transformations — **medium**; 80027DA0 / source | 8 / 14 | 0 |
| `main_1A7F0.c` | 0x8002A150–0x8002A1E0 | Decoder bit/input-state helpers — **medium**; 8002A150 / source | 3 / 3 | 0 |
| `main_1A880.c` | 0x8002A1E0–0x8002A4F0 | Type-1 texture byte decoder — **high**; 8002A40C / gfx_format | 4 / 4 | 0 |
| `main_1AB90.c` | 0x8002A4F0–0x8002AB90 | Game sequence/audio control — **high**; 8002A9DC / source | 7 / 9 | 0 |
| `main_1B230.c` | 0x8002AB90–0x8002B500 | Audio manager thread, RSP tasks and DMA cache — **high**; 8002B034 / T-075 | 5 / 7 | 0 |
| `main_1BBA0.c` | 0x8002B500–0x8002B7E0 | Controller/SI manager wrappers — **high**; 8002B500 / source | 4 / 4 | 0 |
| `main_1BE80.c` | 0x8002B7E0–0x8002E150 | Camera state machine and projection — **medium**; 8002BBD0 / T-085; T-075 | 12 / 15 | 0 |
| `main_1E7F0.c` | 0x8002E150–0x8002E4A0 | Scene/camera helper; exact role unresolved — **low**; 8002E150 / source boundary | 0 / 1 | 0 |
| `main_1EB40.c` | 0x8002E4A0–0x8002FB80 | Custom sound player and linked voice events — **high**; 8002E4A0 / T-081 | 17 / 20 | 0 |
| `main_20220.c` | 0x8002FB80–0x80030440 | Packed stage commands, vertices and textures — **high**; 8002FFDC / gfx_format | 4 / 8 | 0 |
| `main_20AE0.c` | 0x80030440–0x80031050 | Bitmap text and character-to-glyph mapping — **high**; 800306B8 / T-081 | 1 / 3 | 0 |
| `main_216F0.c` | 0x80031050–0x80032360 | Sprite color/mask expansion kernels — **high**; 800310C0, 80031A38 / gfx_format | 0 / 4 | 0 |
| `main_22A00.c` | 0x80032360–0x80032600 | Pixel/decoder support kernels; exact split unresolved — **medium**; 80032360 / source; T-075 | 0 / 2 | 0 |
| `main_22CA0.c` | 0x80032600–0x800326F0 | Context-coded color-symbol decoder — **high**; 80032600 / gfx_format | 0 / 2 | 0 |
| `main_22D90.c` | 0x800326F0–0x80032750 | Private decoder/random-state helpers — **low**; 800326F0 / source callers | 0 / 2 | 0 |
| `main_22DF0.c` | 0x80032750–0x80032C30 | Byte decoder state and symbol decoding — **high**; 80032750 / gfx_format | 0 / 3 | 0 |
| `libultra/osViSetSpecialFeatures.c` | 0x80032C30–0x80032DF0 | SDK support: osViSetSpecialFeatures — **high**; source / libultra.md; T-078; T-080 | 0 / 1 | 1 |
| `libultra/guPerspectiveF.c` | 0x80032DF0–0x80033080 | SDK support: guPerspectiveF, guPerspective — **high**; source / libultra.md; T-078; T-080 | 0 / 2 | 2 |
| `main_23720.c` | 0x80033080–0x800330B0 | SDK support: guRandom — **high**; source / libultra.md; T-078; T-080 | 0 / 1 | 1 |
| `main_23750.c` | 0x800330B0–0x800338E0 | SDK support: guLookAtHiliteF, guLookAtHilite — **high**; source / libultra.md; T-078; T-080 | 0 / 2 | 2 |
| `libultra/guTranslateF.c` | 0x800338E0–0x80033980 | SDK support: guTranslateF, guTranslate — **high**; source / libultra.md; T-078; T-080 | 0 / 2 | 2 |
| `libultra/guRotateF.c` | 0x80033980–0x80033B70 | SDK support: guRotateF, guRotate — **high**; source / libultra.md; T-078; T-080 | 0 / 2 | 2 |
| `libultra/guLookAtRef.c` | 0x80033B70–0x80034030 | SDK support: guLookAtReflectF, guLookAtReflect — **high**; source / libultra.md; T-078; T-080 | 0 / 2 | 2 |
| `libultra/guScaleF.c` | 0x80034030–0x800340D0 | SDK support: guScaleF, guScale — **high**; source / libultra.md; T-078; T-080 | 0 / 2 | 2 |
| `main_24770.c` | 0x800340D0–0x800340E0 | SDK support: sqrtf — **high**; source / libultra.md; T-078; T-080 | 0 / 1 | 1 |
| `libultra/string.c` | 0x800340E0–0x80034180 | SDK support: main_memcpy, main_strlen, main_strchr — **high**; source / libultra.md; T-078; T-080 | 0 / 3 | 3 |
| `main_24820.c` | 0x80034180–0x800344B0 | SDK Controller Pak operations — **high**; SDK-named source / T-035; T-037; T-083 | 0 / 3 | 3 |
| `main_24B50.c` | 0x800344B0–0x800347D0 | SDK Controller Pak operations — **high**; SDK-named source / T-035; T-037; T-083 | 0 / 3 | 3 |
| `main_24E70.c` | 0x800347D0–0x80035D30 | SDK Controller Pak operations — **high**; SDK-named source / T-035; T-037; T-083 | 0 / 8 | 8 |
| `main_263D0.c` | 0x80035D30–0x80035DE0 | SDK support: osContStartQuery, osContGetQuery — **high**; source / libultra.md; T-078; T-080 | 0 / 2 | 2 |
| `main_26480.c` | 0x80035DE0–0x80035F10 | SDK Controller Pak operations — **high**; SDK-named source / T-035; T-037; T-083 | 0 / 1 | 1 |
| `main_265B0.c` | 0x80035F10–0x800361C0 | SDK Controller Pak operations — **high**; SDK-named source / T-035; T-037; T-083 | 0 / 1 | 1 |
| `main_26860.c` | 0x800361C0–0x80036730 | SDK Controller Pak operations — **high**; SDK-named source / T-035; T-037; T-083 | 0 / 3 | 3 |
| `libultra/osEepromProbe.c` | 0x80036730–0x800367A0 | SDK support: osEepromProbe — **high**; source / libultra.md; T-078; T-080 | 0 / 1 | 1 |
| `libultra/osEepromLongWrite.c` | 0x800367A0–0x800368E0 | SDK support: osEepromLongWrite — **high**; source / libultra.md; T-078; T-080 | 0 / 1 | 1 |
| `libultra/osEepromLongRead.c` | 0x800368E0–0x80036A20 | SDK support: osEepromLongRead — **high**; source / libultra.md; T-078; T-080 | 0 / 1 | 1 |
| `libultra/osViBlack.c` | 0x80036A20–0x80036A90 | SDK support: osViBlack — **high**; source / libultra.md; T-078; T-080 | 0 / 1 | 1 |
| `libultra/sinf.c` | 0x80036A90–0x80036C50 | SDK support: sinf — **high**; source / libultra.md; T-078; T-080 | 0 / 1 | 1 |
| `libultra/cosf.c` | 0x80036C50–0x80036DC0 | SDK support: cosf — **high**; source / libultra.md; T-078; T-080 | 0 / 1 | 1 |
| `main_27460.c` | 0x80036DC0–0x80036DF0 | SDK support: osWritebackDCacheAll — **high**; source / libultra.md; T-078; T-080 | 0 / 1 | 1 |
| `main_27490.c` | 0x80036DF0–0x80036F90 | SDK support: guRotateRPYF, guRotateRPY — **high**; source / libultra.md; T-078; T-080 | 0 / 2 | 2 |
| `main_27630.c` | 0x80036F90–0x800371A0 | SDK support: guMtxXFMF, guMtxCatF — **high**; source / libultra.md; T-078; T-080 | 0 / 2 | 2 |
| `libultra/guMtxF2L.c` | 0x800371A0–0x80037410 | SDK support: guMtxF2L, guMtxIdentF, guMtxIdent and helpers — **high**; source / libultra.md; T-078; T-080 | 0 / 4 | 4 |
| `main_27AB0.c` | 0x80037410–0x80037450 | SDK support: osUnmapTLB — **high**; source / libultra.md; T-078; T-080 | 0 / 1 | 1 |
| `main_27AF0.c` | 0x80037450–0x80037510 | SDK support: osMapTLB — **high**; source / libultra.md; T-078; T-080 | 0 / 1 | 1 |
| `libultra/guOrthoF.c` | 0x80037510–0x800376D0 | SDK support: guOrthoF, guOrtho — **high**; source / libultra.md; T-078; T-080 | 0 / 2 | 2 |
| `main_27D70.c` | 0x800376D0–0x80037710 | SDK support: alHeapInit — **high**; source / libultra.md; T-078; T-080 | 0 / 1 | 1 |
| `main_27DB0.c` | 0x80037710–0x80037770 | SDK support: alHeapDBAlloc — **high**; source / libultra.md; T-078; T-080 | 0 / 1 | 1 |
| `main_27E10.c` | 0x80037770–0x800379C0 | SDK support: func_80037770, func_80037780, alBnkfNew and helpers — **high**; source / libultra.md; T-078; T-080 | 1 / 4 | 3 |
| `main_28060.c` | 0x800379C0–0x80038BF0 | SDK support: __CSPPostNextSeqEvent, func_80037A30, func_80037A6C and helpers — **high**; source / libultra.md; T-078; T-080 | 0 / 6 | 6 |
| `main_29290.c` | 0x80038BF0–0x80038C30 | SDK support: alCSPSetBank — **high**; source / libultra.md; T-078; T-080 | 0 / 1 | 1 |
| `main_292D0.c` | 0x80038C30–0x80038C40 | SDK support: alCSPGetState — **high**; source / libultra.md; T-078; T-080 | 0 / 1 | 1 |
| `main_292E0.c` | 0x80038C40–0x80039760 | SDK support: alCSPPlay, alCSPStop, alCSeqGetLoc and helpers — **high**; source / libultra.md; T-078; T-080 | 0 / 13 | 13 |
| `main_29E00.c` | 0x80039760–0x800397A0 | SDK support: alCSPSetSeq — **high**; source / libultra.md; T-078; T-080 | 0 / 1 | 1 |
| `main_29E40.c` | 0x800397A0–0x800397E0 | SDK support: alCSPSetVol — **high**; source / libultra.md; T-078; T-080 | 0 / 1 | 1 |
| `main_29E80.c` | 0x800397E0–0x80039A00 | SDK support: osAiSetFrequency, alUnlink, alLink and helpers — **high**; source / libultra.md; T-078; T-080 | 0 / 5 | 5 |
| `libultra/osAiSetNextBuffer.c` | 0x80039A00–0x80039AB0 | SDK support: osAiSetNextBuffer — **high**; source / libultra.md; T-078; T-080 | 0 / 1 | 1 |
| `main_2A150.c` | 0x80039AB0–0x80039AC0 | SDK support: osAiGetLength — **high**; source / libultra.md; T-078; T-080 | 0 / 1 | 1 |
| `main_2A160.c` | 0x80039AC0–0x8003A190 | SDK support: func_80039AC0, _timeToSamples, _freePVoice and helpers — **high**; source / libultra.md; T-078; T-080 | 2 / 9 | 7 |
| `libultra/osContInit.c` | 0x8003A190–0x8003A550 | SDK support: osContInit, __osContGetInitData, __osPackRequestData — **high**; source / libultra.md; T-078; T-080 | 0 / 3 | 3 |
| `libultra/osContStartReadData.c` | 0x8003A550–0x8003A7B0 | SDK support: osContStartReadData, osContGetReadData, __osPackReadData — **high**; source / libultra.md; T-078; T-080 | 0 / 3 | 3 |
| `main_2AE50.c` | 0x8003A7B0–0x8003AAF0 | SDK support: alEvtqFlushType, alEvtqFlush, alEvtqPostEvent and helpers — **high**; source / libultra.md; T-078; T-080 | 0 / 5 | 5 |
| `main_2B190.c` | 0x8003AAF0–0x8003AB40 | SDK support: alSynAddPlayer — **high**; source / libultra.md; T-078; T-080 | 0 / 1 | 1 |
| `main_2B1E0.c` | 0x8003AB40–0x8003AD70 | SDK support: _allocatePVoice, alSynAllocVoice — **high**; source / libultra.md; T-078; T-080 | 0 / 2 | 2 |
| `main_2B410.c` | 0x8003AD70–0x8003AE10 | SDK support: alSynSetVol — **high**; source / libultra.md; T-078; T-080 | 0 / 1 | 1 |
| `main_2B4B0.c` | 0x8003AE10–0x8003AEA0 | SDK support: alSynStartVoice — **high**; source / libultra.md; T-078; T-080 | 0 / 1 | 1 |
| `main_2B540.c` | 0x8003AEA0–0x8003AF30 | SDK support: alSynSetPan — **high**; source / libultra.md; T-078; T-080 | 0 / 1 | 1 |
| `main_2B5D0.c` | 0x8003AF30–0x8003AFC0 | SDK support: alSynSetPitch — **high**; source / libultra.md; T-078; T-080 | 0 / 1 | 1 |
| `main_2B660.c` | 0x8003AFC0–0x8003B060 | SDK support: alSynSetFXMix — **high**; source / libultra.md; T-078; T-080 | 0 / 1 | 1 |
| `main_2B700.c` | 0x8003B060–0x8003B0E0 | SDK support: alSynStopVoice — **high**; source / libultra.md; T-078; T-080 | 0 / 1 | 1 |
| `main_2B780.c` | 0x8003B0E0–0x8003B1E0 | SDK support: alSynFreeVoice, alCents2Ratio — **high**; source / libultra.md; T-078; T-080 | 0 / 2 | 2 |
| `libultra/guNormalize.c` | 0x8003B1E0–0x8003B270 | SDK support: guNormalize — **high**; source / libultra.md; T-078; T-080 | 0 / 1 | 1 |
| `libultra/__osSiCreateAccessQueue.c` | 0x8003B270–0x8003B330 | SDK support: __osSiCreateAccessQueue, __osSiGetAccess, __osSiRelAccess — **high**; source / libultra.md; T-078; T-080 | 0 / 3 | 3 |
| `libultra/__osSiRawStartDma.c` | 0x8003B330–0x8003B3E0 | SDK support: __osSiRawStartDma — **high**; source / libultra.md; T-078; T-080 | 0 / 1 | 1 |
| `main_2BA80.c` | 0x8003B3E0–0x8003C3C0 | SDK Controller Pak operations — **high**; SDK-named source / T-035; T-037; T-083 | 0 / 10 | 10 |
| `main_2CA60.c` | 0x8003C3C0–0x8003C750 | SDK Controller Pak operations — **high**; SDK-named source / T-035; T-037; T-083 | 0 / 2 | 2 |
| `main_2CDF0.c` | 0x8003C750–0x8003C900 | SDK Controller Pak operations — **high**; SDK-named source / T-035; T-037; T-083 | 0 / 1 | 1 |
| `libultra/osEepromWrite.c` | 0x8003C900–0x8003CDE0 | SDK support: osEepromWrite, __osPackEepWriteData, __osEepStatus — **high**; source / libultra.md; T-078; T-080 | 0 / 3 | 3 |
| `libultra/osSetTimer.c` | 0x8003CDE0–0x8003CEC0 | SDK support: osSetTimer — **high**; source / libultra.md; T-078; T-080 | 0 / 1 | 1 |
| `libultra/osEepromRead.c` | 0x8003CEC0–0x8003D1C0 | SDK support: osEepromRead, __osPackEepReadData — **high**; source / libultra.md; T-078; T-080 | 0 / 2 | 2 |
| `main_2D860.c` | 0x8003D1C0–0x8003EB00 | SDK support: __setInstChanState, __resetPerfChanState, __initFromBank and helpers — **high**; source / libultra.md; T-078; T-080 | 1 / 20 | 19 |
| `main_2F1A0.c` | 0x8003EB00–0x8003EBF0 | SDK support: alSynStartVoiceParams — **high**; source / libultra.md; T-078; T-080 | 0 / 1 | 1 |
| `main_2F290.c` | 0x8003EBF0–0x8003EC00 | SDK support: alSynDelete — **high**; source / libultra.md; T-078; T-080 | 0 / 1 | 1 |
| `libultra/__osAiDeviceBusy.c` | 0x8003EC00–0x8003EC30 | SDK support: __osAiDeviceBusy — **high**; source / libultra.md; T-078; T-080 | 0 / 1 | 1 |
| `main_2F2A0.c` | 0x8003EC30–0x8003F3B0 | SDK support: alSaveNew, alMainBusNew, alAuxBusNew and helpers — **high**; source / libultra.md; T-078; T-080 | 0 / 8 | 8 |
| `main_2FA50.c` | 0x8003F3B0–0x8003F450 | SDK support: alSynAllocFX — **high**; source / libultra.md; T-078; T-080 | 0 / 1 | 1 |
| `main_2FAF0.c` | 0x8003F450–0x8003F5A0 | SDK support: alMainBusParam, alMainBusPull — **high**; source / libultra.md; T-078; T-080 | 0 / 2 | 2 |
| `main_2FC40.c` | 0x8003F5A0–0x800400F0 | SDK support: alLoadParam, alRaw16Pull, func_8003FB20 and helpers — **high**; source / libultra.md; T-078; T-080 | 0 / 4 | 4 |
| `main_30790.c` | 0x800400F0–0x800403F0 | SDK support: alResampleParam, alResamplePull — **high**; source / libultra.md; T-078; T-080 | 0 / 2 | 2 |
| `main_30A90.c` | 0x800403F0–0x80041050 | SDK support: _ldexpf, _frexpf, alEnvmixerParam and helpers — **high**; source / libultra.md; T-078; T-080 | 0 / 7 | 7 |
| `main_316F0.c` | 0x80041050–0x80041160 | SDK support: alAuxBusParam, alAuxBusPull — **high**; source / libultra.md; T-078; T-080 | 0 / 2 | 2 |
| `main_31800.c` | 0x80041160–0x80041220 | SDK support: alSaveParam, alSavePull — **high**; source / libultra.md; T-078; T-080 | 0 / 2 | 2 |
| `libultra/osGetTime.c` | 0x80041220–0x800412B0 | SDK support: osGetTime — **high**; source / libultra.md; T-078; T-080 | 0 / 1 | 1 |
| `main_31950.c` | 0x800412B0–0x80041330 | SDK support: alCopy — **high**; source / libultra.md; T-078; T-080 | 0 / 1 | 1 |
| `libultra/crc.c` | 0x80041330–0x800414B0 | SDK support: __osContAddressCrc, __osContDataCrc — **high**; source / libultra.md; T-078; T-080 | 0 / 2 | 2 |
| `main_319D0.c` | 0x800414B0–0x80041B00 | SDK support: alSeqGetLoc, alSeqSetLoc, alSeqGetTicks and helpers — **high**; source / libultra.md; T-078; T-080 | 1 / 15 | 14 |
| `main_321A0.c` | 0x80041B00–0x80042710 | SDK support: _doModFunc, _filterBuffer, _saveBuffer and helpers — **high**; source / libultra.md; T-078; T-080 | 0 / 8 | 8 |

Snapshot totals: **146 T4 / 459 functions; 222 excluded**.

### ovl_7DF8

| File | Address range | Inferred role — confidence; evidence | T4 / total | Excluded |
|---|---|---|---:|---:|
| `ovl_7DF8.c` | 0x801ABB20–0x801ADEA0 | Frontend entry, mode dispatch, transition helpers — **high**; 801ABB20 / T-034 | 25 / 30 | 0 |
| `ovl_7DF8_2380.c` | 0x801ADEA0–0x801AFA80 | Frontend scene initialization/update helpers — **medium**; 801ADEA0 / source | 6 / 8 | 0 |
| `ovl_7DF8_3F60.c` | 0x801AFA80–0x801B19F0 | Menu scene/transition rendering and interpolation — **medium**; 801AFA80 / T-025 | 3 / 12 | 0 |
| `ovl_7DF8_5ED0.c` | 0x801B19F0–0x801BD200 | Menu/UI scene builders and animated transitions — **medium**; 801B2010 / T-077; T-097 | 15 / 57 | 0 |
| `ovl_7DF8_116E0.c` | 0x801BD200–0x801BE790 | Transformed glyph/string rendering — **high**; 801BDF94 / T-079 | 0 / 8 | 0 |
| `ovl_7DF8_12C70.c` | 0x801BE790–0x801BFB10 | Score tables, packed names and ranking aggregation — **high**; 801BED0C, 801BF788 / source; T-023 | 8 / 15 | 0 |
| `ovl_7DF8_13FF0.c` | 0x801BFB10–0x801C3990 | Score/name entry and timed camera/UI scenes — **high**; 801C08F8, 801C23C0 / T-079 | 13 / 27 | 0 |
| `ovl_7DF8_17E70.c` | 0x801C3990–0x801C4040 | Animated triangle/vertex effect — **medium**; 801C3990 / source | 1 / 3 | 0 |
| `ovl_7DF8_18520.c` | 0x801C4040–0x801C47E0 | Finish/rating presentation and input — **medium**; 801C407C / source | 4 / 5 | 0 |
| `ovl_7DF8_18CC0.c` | 0x801C47E0–0x801C4BD0 | Presentation asset/scene helpers; exact split unresolved — **low**; 801C47E0 / caller 801C407C | 0 / 3 | 0 |
| `ovl_7DF8_190B0.c` | 0x801C4BD0–0x801C72B0 | Ending text, portraits and presentation — **high**; 801C5FB0 / gfx_format; source | 18 / 21 | 0 |
| `ovl_7DF8_1B790.c` | 0x801C72B0–0x801C78B0 | Timed frontend screen/input state — **medium**; 801C72B0, 801C780C / source | 2 / 3 | 0 |
| `ovl_7DF8_1BD90.c` | 0x801C78B0–0x801CBBE0 | Mode/replay setup, settings and frontend helpers — **medium**; 801C7CD0 / T-066 | 17 / 30 | 0 |
| `ovl_7DF8_200C0.c` | 0x801CBBE0–0x801CD450 | Pak query/worker, save UI and name conversion — **high**; 801CBBE0 / T-087; T-034 | 26 / 29 | 0 |

Snapshot totals: **138 T4 / 251 functions; 0 excluded**.

Two SDK-dominated TUs retain T4 rows in the inventory; that is recorded as-is,
not silently reclassified here. **High:** the table reports tiers faithfully;
**low:** the remaining classification discrepancy's intended resolution.

## Open questions and useful next traces

1. **Medium hypothesis, high priority:** 0x7E00 is the combat engine. Trace
   main's per-frame calls into it and writes to `D_801D3430` to separate move
   execution, AI, collision, damage, round completion and presentation. Evidence
   to start with: `func_8000FA80`, `func_8001178C`, `func_801AD900` and the
   custom-ABI caveats in ovl_7E00_asm. Preserve shared entries and inline pools.
2. **Low confidence:** complete frontend/session enums. Map every assignment
   and callback for `D_80295708`, `D_8029571A`, `D_8004A407`, `D_80127C40`
   and `D_8012834B`; distinguish attract demo, replay, human play and return
   transitions. T-034's entry draft provides control flow, not final enum names.
3. **Medium hypothesis:** the two byte-table slots are fighter scripts/data.
   Follow their consumers in 0x7E00 and establish record boundaries before
   claiming animation, move or AI formats (segments.md; `func_80012100`).
4. **High-confidence need:** consolidate structs only after auditing fields.
   Task wrappers, sprite descriptors, drawing records, engine player state,
   camera contexts and sound-player partial views currently overlap in purpose
   but have different layouts. T-069/T-081 recover useful offsets; T-033's
   snapshot/replay views still need assembly review.
5. **Low confidence:** exact game-audio ancestry. Compare the manager against
   SDK demos without assuming identity; the custom voice/group event player
   must remain distinct from proven SDK synth/sequence/effect code (T-075).
6. **Medium confidence:** persistence ownership and worker synchronization.
   Trace callers of EEPROM/Pak APIs, enumerate game record checksums/versioning,
   and define the Pak worker's message/status protocol before naming every
   status flag (`ovl_7DF8_200C0.c`).
7. **High-confidence unresolved format work:** type-1 stage textures, five
   textures without traced dimensions, paired/effect sprite paths, and exact
   coverage/edge behavior remain open (gfx_format.md). Static geometry export
   omits runtime placement, materials and visibility. Do not infer stage names
   or full rendering correctness from decoded assets alone.
8. **High-confidence bookkeeping limit:** tables reflect this checkout's CSV
   snapshot and current YAML splits, not historical source filenames or a
   promise that every SDK C function is classified T4. Recompute counts from
   the CSV after the lead lands other workers; do not copy old report totals.

## Evidence index

Primary maps: [boot.md](boot.md), [segments.md](segments.md),
[rom_layout.md](rom_layout.md), [tu_boundaries.md](tu_boundaries.md),
[libultra.md](libultra.md), [ovl_7E00_asm.md](ovl_7E00_asm.md),
[gfx_format.md](gfx_format.md). Progress snapshot and chronology:
[functions.csv](functions.csv), [TRACKING.md](TRACKING.md), [WORKLOG.md](WORKLOG.md).

Worker references above are `tools/scratch/nonmatching/T-NNN/REPORT.md` unless
explicitly called a draft. Especially useful:
[T-033](../tools/scratch/nonmatching/T-033/REPORT.md) (main orchestration),
[T-034](../tools/scratch/nonmatching/T-034/REPORT.md) (overlay entry),
[T-069](../tools/scratch/nonmatching/T-069/REPORT.md) (matrices/Gfx),
[T-075](../tools/scratch/nonmatching/T-075/REPORT.md) (SDK versus game audio),
[T-079](../tools/scratch/nonmatching/T-079/REPORT.md) (glyphs and camera scenes),
[T-081](../tools/scratch/nonmatching/T-081/REPORT.md) (glyph/sprite/voice layouts),
[T-085](../tools/scratch/nonmatching/T-085/REPORT.md) (large main-loop limits).
