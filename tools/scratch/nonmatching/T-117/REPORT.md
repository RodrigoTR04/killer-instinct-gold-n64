# T-117 — sol-C43: template-driven clone matching

Two functions promoted: func_801BB258 (524 B) and func_8001AD04 (1,072 B),
1,596 bytes total. func_8001B134 has an exact 984-byte code draft but remains
assembly pending constant-pool integration. B3B84 and BADEC drafts improved.
No commits. No ROM contents copied or added to git.

Read TRACKING, latest WORKLOG, clones, Makefile, permuter README and the
T-106/T-111/T-097/T-101/T-103 reports. Missing local prerequisites were
symlinked to the authorized shared project. No subagents were used.

## Template differences

`compare_templates.py` decodes untouched extracted original images, including
already-matched templates, and writes the complete operand-preserving
instruction diffs to `template-diffs.txt`. It does not compare rebuilt C or
mask away registers/constants. The relative disassembly branch operands remain
visible. All acceptance measurements use actual ELF relocation masks only.

### BA674 → BB258

Both call BC1B0 twice and increment/wrap their counter at 12, using the same
counter/3 interleaved byte-table addressing. There is no removed draw or
counter branch. The state fields remain u16 scale at +7E and s16 yOffset +80.

- Counter/table symbols 801F39C8/39CC/39D0 become 801F3C10/3C14/3C18.
- BA674 x offsets 0x184 and 0xE4 become a shared 0xC4 offset.
- y offsets 0x8C/0x83 become 0xD7/0x153.
- First draw dimensions 18/54/18/54, terminal 17/53, become
  2C/20/2C/20, terminal 2B/1F.
- Second draw dimensions 2C/2C/2C/2B become 2C/2B/2C/2B;
  terminal 2B/2A stays the same.
- Frame shrinks 0x58→0x50; scale remains t0, shared x values t2/t1.

Copied the matched template and changed those expressions. Two equal x
expressions let IDO share the calculation while preserving the two semantic
coordinates. Computing x1 then x0, y1 then y0, and mirroring x1 before x0
recovers the original copy/register order. Declaration order x1,y1,counter,
y0,nextFrame,x0 recovers the 0x50 frame. A literal initial template measured
46 words; computation changes reached 13, declaration order reached two,
and reversing the mirror statements reached zero. Full-TU measurement:
524/524 bytes, zero words. Promoted; deleted the T-023 draft.

### Family B → B3B84

Same unsigned lerp conversion, palette packing, translation and final display
commands. Counter changes 801D30C0→801D30D8; entry/completion threshold 2→8;
translation x -125→178. B3B84 additionally stores 1 to D_8029571A when its
incremented counter is below 50. Its late counter store occurs after completion
handling, rather than at the branch entry. Its original stale alpha byte load
at +40 is hoisted before the branch (family B loads it in the late block).

Transferring B's current draft, moving the late counter store and restoring
the early source word-0 store reduces the current full-TU baseline
113 words / 552 B to 16 words / 556 B (original 556 B). Remaining differences
are alpha t7 versus t0, command t9 versus t8 and the consequent palette pack
register chain. A separate old-alpha local and widths did not improve it.
The inherited uninitialized alpha read remains explicitly marked scratch-only;
this draft is not a production replacement. Family B's six drafts unchanged.

### AD04 → B134 (cluster 4)

Shared core: read two transform indices from 12-byte stage records, check
6000 depth, ramp movement/audio from position+2000, rotate and decay audio
past depth 2000, update both angles, increment hold toward 50 and call B50C
for both transform indices. Neither function has an extra hidden helper.

- Movement threshold 1500→1000; initial ramp denominator 3500→3000.
- Rotation predicate angle<360 && hold>=50 becomes angle<90.
- Both rotation acceleration calls use 0.3/0.0.
- AD04 clears both A920 entries after its B50C calls; B134 omits those stores.
- B134 is 88 B shorter: threshold/branch simplification and removed clears,
  with different register/spill scheduling throughout the shared core.

Replaced decompiler pointer temporaries with direct indexed global expressions
and two transform-index locals. AD04 immediately reached 1072/1072 bytes and
zero words, independently confirmed in the full owning TU. Ordinary float
literals emit the original constants. Promoted; deleted its T-022 draft.

The direct transfer to B134 initially produced 960 B / 224 words because IDO
kept the position pointer in s0. A meaningful else around the complete rotation
path recovers 984/984 bytes and zero words. A natural shared return also
matches, but the retained draft uses the readable else. A bounded permuter
search independently found zero with an artificial `if (1)` barrier; rejected.
The natural control-flow solution was independently measured in full TU.

B134 owns force_migration doubles 48998/A0/A8/B0 actually used by already
matched B50C. Its promotion requires B50C to emit 3.14159/180.0 literals and
removal of those ownership hints. That edits an already-matched function
outside the allowed bodies; requested the narrow scope exception. Until an
answer authorizes it, B134 stays asm and its exact code is updated in place
in T-022. No hints or B50C body were changed. No linker changes are required
for the two integrated matches.

### BADEC

Preserved its separate animation windows [21,39) and [28,46), both increment
and redundant stores, mirrored shared x and the second draw's +0x318 frame
offset. Tested direct/cached initial scale, scalar/array coordinates, declaration
and computation orders. Initial scale as s32 and scalar coordinates gives
102 words / 552 B versus the incoming 106 / 568 B (original 568 B).
This is a modest positional-score improvement with a size regression, not a
match or an edit-distance guarantee. Kept the improved draft in place; no
GLOBAL_ASM replacement. Scale values are still zero-extended from u16; all
constant products fit signed s32. Conditional call behavior is preserved.

## Verification

All candidate scores count differing instruction words plus size differences,
masking only actual ELF relocations. `recheck.py` measures retained drafts in
complete production TUs. Compiler failures were never treated as matches.
Temporary searches/objects stayed under /tmp. No permuter output directories
are delivered. Honest C only; no inline asm, #line, register, volatile barriers,
compiler changes, artificial branches or padding retained.

Retained full-TU results (`results.json`):

| Function | Before words / bytes | Final words / bytes | Original B | Result |
|---|---:|---:|---:|---|
| func_801BB258 | 20 / 524 | 0 / 524 | 524 | Promoted |
| func_8001AD04 | 194 / 1088 | 0 / 1072 | 1072 | Promoted |
| func_8001B134 | 214 / 980 | 0 / 984 | 984 | Exact code draft, ownership pending |
| func_801B3B84 | 113 / 552 | 16 / 556 | 556 | Improved scratch draft |
| func_801BADEC | 106 / 568 | 102 / 552 | 568 | Improved positional score; short body |

B3B84's historical 114-word screen is not the current baseline. The fresh
baseline is recorded in baseline.json. Main baselines are the inherited screen
and report counts; no claim of a fresh pre-edit full-TU baseline for those.
One final draft check overlapped make clean and failed on missing generated
assembly. It was rerun after extraction; all three retained drafts then
compiled successfully in full context. Exploratory BADEC coordinate-order
generators hit assertions and produced no accepted results.

`make clean && make extract && make all && make progress` passed (exit 0).
ROM and all three executable images are byte-identical, preserving every
already-matched function, including families A and C:

- ROM: ba52e91b44450c548467044b26951353dc491e04
- main: 81736d32e8cda8f399b319a49250dff972b81af8
- ovl_7DF8: ea830aae50ff1422da60d4b7fdbfc29f03b1be39
- ovl_7E00: 2b01138a290212b9d886981e1196f7b6fb45ecdb

`git diff --check` passed. No task searches remain. No commits. Boot,
ovl_7E00, YAML, Makefile, status.csv, TRACKING and WORKLOG are untouched.
No net linker-script differences. Generated progress docs were restored after
recording this table, leaving those shared outputs for the lead.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 72,480 (25.00%) | 72,480 (25.00%) | 0 | 192 | 0 | 317 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 32,276 (22.42%) | 32,276 (22.42%) | 0 | 89 | 0 | 148 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 31,736 (23.09%) | 31,736 (23.09%) | 0 | 103 | 0 | 148 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
