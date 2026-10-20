# T-081 — sol-B27: five huge main drafts

**0 MATCHED, 4 IMPROVED, 1 UNCHANGED.** All five were measured and attempted.
No production C, ownership metadata, build settings, or status.csv changes.
No commits. No deleted drafts: all five functions remain GLOBAL_ASM.

## Results

Counts compare corresponding instruction words in the current owning TU,
masking only actual ELF relocation fields and including length differences.
These are positional diagnostics, not edit distances or behavior validation.
Baseline measurements were repeated here; old draft-header counts used other
contexts. Final retained drafts use multiline statements and braces.

| Function | TU | Result: old → new words | Final C / original bytes | What remains |
|---|---|---|---:|---|
| func_800306B8 | main_20AE0 | IMPROVED **520 → 513** | 2096 / 2104 | Much larger stack frame and different register allocation; clipping, glyph iteration and division scheduling still differ. |
| func_80020E98 | main_D3F0 | IMPROVED **526 → 512** | 2104 / 2108 | Loop counters, byte-stream decoding, cache clearing/unrolling, stack slots and registers. |
| func_8001E33C | main_D3F0 | IMPROVED **602 → 571** | 2412 / 2360 | Player-state addressing, color/scale live ranges, branch layout, spills and render-call setup. |
| func_800142E0 | main_2FF0 | UNCHANGED **593** | 2100 / 2400 | Both strip loops, clipping branches and command cursor allocation; natural initial-command rewrite was worse. |
| func_8002E724 | main_1EB40 | IMPROVED **699 → 660** | 2728 / 2832 | Dispatch/body layout, voice stealing, event locals, float conversion and call scheduling; also asm-owned jump table. |

## Recovered structure and experiments

### func_800306B8

The function measures a terminated glyph string when x is zero, centers it,
sets eight initial RDP commands, then emits each non-space glyph. Glyphs are
four bytes (width, height, spacing, baseline); colors are four byte channels;
scale is a signed word table. Commands are two-word, eight-byte records.
The three mirrored character sets select texture starts and signed texture
steps. A cached combiner mode switches between glyph 0x47 and normal glyphs.

Corrected two draft errors found against the assembly:

- The normal-glyph branch must test the **previous** combiner mode before
  clearing it. The old draft set it to zero and then tested zero, deleting
  the FCFFFFFF/FFFDF2F9 command path.
- Mirrored steps use signed `-0x1FC00 / scale`, followed by a 16-bit mask.
  The old hexadecimal numerator was unsigned C and emitted unsigned division;
  the original uses signed `div` and signed division checks.

Retained typed Gfx/glyph/color records and one reusable command temporary.
A separate natural rewrite with named coordinates, for loops, scoped glyph
math and an advancing cursor emitted 2040 B but scored 523 words; rejected.
The retained source is closer in size and positional score, but neither is
near a match. The callee is the existing s32 func_80030EF0(u8), with its
result reduced to a byte by the caller.

### func_80020E98

Recovered the three destination-selection paths, the special player-2
portrait decode (two frame groups followed by eleven inflate blocks), the
256-by-three cache of first/alternate pointers, optional bank-1 additions,
missing-entry fallback, and final two palette DMAs. The 32-byte ROM-entry
and 28-byte sprite layouts already present in the draft/TU are retained.
Byte-stream headers are little-endian except the compressed block lengths.

Moved ROM-entry/end initialization after destination selection, as in the
original. Replaced cached sprite accesses with indexed global accesses:
assembly recomputes D_8004EA78 after output-table stores, whose pointer
contents can alias other data. Also re-read the frame count in the inner
loop condition; the assembly reloads it after the decoder call rather than
keeping an invariant local. This brought emitted size from 1928 to 2104 B.
An intermediate compact layout scored 510 at 2096 B; final multiline layout
scores 512 and is the retained result, not a claim of 510.

### func_8001E33C

Recovered the 0x30-byte player drawing record: position floats at +0xC,
+0x10,+0x14; flip byte +0x21; kind halfword +0x22; signed RGB adjustments
at +0x28/+0x2A/+0x2C. Used float arrays for the transform banks and a Gfx
record for emitted commands. The render path has a three-object special
mode, a kind-0xBE alternate draw, and ordinary tinted/flash sprite draws.
The sprite mode at D_8004CEE8 is a **signed halfword**, not the old u8;
it is now accessed as D_8004CED0[player].flags.

The renderer consumes byte mode/flip/extra arguments. func_80016760 is the
existing void(s32) function, not a three-argument function. The sound call
uses the three arguments established by its other callers; the old extra
fourth argument was a decompiler artifact. These prototype corrections
reduced 602 to 571 words. The 359.0f comparison literal belongs to this TU's
already-owned rodata and replaces D_80048A34 in the draft. No ownership hint
for this function is present, and no symbol metadata was changed.

### func_800142E0

The per-frame buffer has 200 eight-byte commands (0x640 stride). Initial
commands configure scissor, combiner, image and tiles. Negative angles wrap
by 360; the horizontal texture coordinate uses signed modulo 240. The body
builds repeated clipped strips and a second nine-strip section, then a
state-dependent final fill and sync; it reports the byte length by pointer
difference. No switch/jump table is involved.

Tried a typed [frame][200] buffer, then natural sequential command emission
for the first thirteen commands with explicit angle-normalization loops.
Typed indexing alone remained 593/2100 B. The cursor rewrite emitted
2080 B but scored 597, so neither change replaces the existing draft.

### func_8002E724

This is an audio event dispatcher over linked voices. Voice offsets agree
with the assembly: sound +8, embedded synth voice +0xC, ratio/pitch
+0x28/+0x2C, volume +0x34, retries +0x38, pan/fx/flags/state +0x3C..+0x3F.
Player queue is +0x14, synth pointer +0x38, maximum voices +0x48.
Events carry a halfword type, voice pointer and integer/float/repeat payload
union. Cases cover allocation, stealing/retry, release, pan/pitch/fx/volume,
decay, freeing and repeated sound creation; selected events propagate to
following linked voices until the flag/mask stop condition.

The assembly copies **type, replacement voice and payload only** when
following a link. Replaced the whole-record copy and assigned the next voice
before copying type/payload, reproducing the original data flow. Recovered
signed halfword reads from the group-volume table. Split the merged
8/0x800/0x40 cases into separate volume/envelope paths. Repeated envelope
loads after calls and nested MIN/MAX clamp expressions better reproduce the
original than cached envelopes and flattened clamps. These structural
changes increase size from 2364 to 2728 B while reducing the score to 660.

Its 16-entry table **jtbl_80048FB0**, main-image **0x39650–0x39690**, is in
`main_remaining_0` assembly rodata. main_1EB40 currently owns no C rodata.
A future match needs a T-046/T-073-style ownership change, preserving the
neighboring constant blocks and original table order. YAML was not touched;
ownership alone will not solve the remaining 660 instruction differences.

## Reproduction and scope

`probe.py` splices each retained draft into its current TU and invokes
T-055/sc.py. Use:

```
mkdir -p /tmp/t055ref
cp build/main.bin /tmp/t055ref/main.bin
.venv/bin/python tools/scratch/nonmatching/T-081/probe.py
```

The helper reconciles the existing non-prototype 142E0 declaration, missing
E33 transform declarations (also now supplied in the retained draft), and
audio's older partial voice types. For audio it temporarily treats the group
volume table as signed, matching target lh instructions; it makes no claim
that changing unrelated getters' declarations preserves their code. Only the
target function is scored. A prospective promotion must reconcile the entire
TU and pass linked verification. The baseline can be reproduced by passing
an original draft extracted with `git show HEAD:<draft-path>` as the second
argument after the suffix.

Eight statement/brace layouts were screened. Several 142E0/audio layouts
initially hit the probe's exact-string declaration substitutions; these are
compile failures, not scores. The helper was made whitespace-tolerant and
the final retained layouts were all remeasured. No generated probe objects,
disassemblies or bulky logs are retained. No inline asm, #line, register
bindings, address tricks, compiler changes, or output rewriting.

Missing baserom.us.z64, ROMs, .venv and tools/ext were symlinked to the
authorized checkout. No ROM was committed or copied into git. Changes are
restricted to four improved scratch drafts, this report and its probe helper;
no production C, boot/overlay source, YAML, Makefile, tracking/worklog,
function_owner hint or status.csv edits. Regenerated undefined-symbol files
are retained if they have net changes. Deleted drafts: **none**.

## Final verification

`make clean && make extract && make all && make progress` **passed**.
`git diff --check` passed. All images and the ROM are byte-identical:

- ROM: `ba52e91b44450c548467044b26951353dc491e04`
- main: `81736d32e8cda8f399b319a49250dff972b81af8`
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`

No regenerated undefined-symbol file has a net change. Generated progress
files also have no net change. The final table is:

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 70,556 (22.11%) | 70,556 (22.11%) | 0 | 272 | 0 | 290 | 437 (138,092) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 173,204 | 44,288 (25.57%) | 44,288 (25.57%) | 0 | 126 | 0 | 164 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 17,800 (12.95%) | 17,800 (12.95%) | 0 | 146 | 0 | 105 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
