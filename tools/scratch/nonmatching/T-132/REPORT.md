# T-132 — sol-B42

Partial result: **0 functions matched, 0 B / 289,876 B (0.00%)**.
The 2,030 B target was not reached. The 3F60 title/menu string pool is now
C-owned and six improved drafts are retained. No nonmatching function was
promoted. No shared toolchain modifications or subagents were used.

## Pool migration

Applied T-126's recipe to all nine strings at 0x802927F0–0x80292878:
the directly referenced copyright/title string plus the eight indirect menu
strings at D_80292814–D_80292870. Definitions are ordered `const u8[]` arrays
in src/ovl_7DF8/ovl_7DF8_3F60.c. The existing YAML .rodata segment already
covers the pool; no YAML change was necessary. The eight force_migration /
function_owner hints became force_not_migration, with the same explicit
non-migration hint added for D_802927F0. This prevents splat assigning C-owned
objects to remaining GLOBAL_ASM functions.

The T-025 draft now uses the C-owned D_802927F0 declaration and a -1500.0f
literal in place of external D_80292918. The numeric object remains in the
original GLOBAL_ASM until text promotion; IDO emits the literal in the draft.
An explicit func_801AF67C prototype avoids a permuter type-map crash.
The function remains at 28 differing words. Its target uses t1 for the alpha
and global load, while the honest draft uses v0/v1; store/call setup scheduling
also differs. Parameter reuse instead uses an extra saved register.

## Triage and per-function results

All ten original assembly files were inspected and fresh m2c outputs are
retained here as m2c_<address>.txt. A second context-informed m2c pass was
used for the ordinary C candidates. Before values come from the assigned
screen; final counts include missing/extra words and relocation masking.

| Function | Before → after words | Compiled/original B | Result / diagnosis |
|---|---:|---:|---|
| func_801B1210 | 28 → 28 | 284/284 | Pool migrated, text unchanged. Alpha and command scheduling residue. |
| func_800257FC | 337 → 337 | 1232/1372 | Ordinary C health-bar renderer, but narrow clip bounds and row cursor/frame remain. Tried widened comparison view, scoped XOR mask and do-loop. |
| func_80015594 | 339 → 305 | 1472/1488 | Saved T-033 draft. Separate incrementing texture-coordinate counters, do-loop, and `-offset * 2` restore target structure. Declaration fallback: existing non-prototype declaration conflicts with float parameters. Fresh per-command m2c version was smaller and worse. |
| func_801BDF94 | 353 → 352 | 1436/1452 | Saved T-023 draft. Exact numeric literals improve it slightly; byte-array reflection storage was also tried. Text/length loop, matrix types, float lifetimes and frame remain. |
| func_80031DD0 | 355 → 355 | 1020/1420 incoming | Deprioritized after asm triage: gp as a general counter, sd stores, trapping sub marked handwritten, irreducible decoder flow. Fresh m2c falls back to gotos. Not a promising plain IDO C target. |
| func_80014D5C | 373 → 136 | 1780/1780 | Saved T-033 draft. Restore all three separate unsigned float-to-byte conversions; cache initial timer load. Exact size; remaining differences concentrate before the color loop, frame (0x50 vs 0x20), constant/address register lifetimes, and division/store scheduling. Prefix context: legacy F6F4/F8F8 return declarations conflict with later TU declarations. |
| func_800238C4 | 384 → 383 | 1600/1580 | Saved T-032 draft. Reverse the independent alpha/pixel XOR-mask setup. Narrow width/height and row-loop alternatives tried; automatic pixel-loop unrolling/frame remains. |
| func_80012B7C | 391 → 391 corrected | 1560/1576 | Found old draft writes BC001C04 through the advanced cursor. Original writes the fourth packet in each branch. Corrected evidence is func_80012B7C-corrected.txt; incumbent left unchanged since the corrected draft did not improve. Unsigned list/count views, s16 callback return and packet source-line joins tried. |
| func_80024CE0 | 400 → 394 | 1492/1652 | Saved fresh T-032 draft. Per-stage pack pointers, explicit sprite slots, original postincrement descriptor initialization. Also corrects old D_8004CED4=base to D_8004CED0[12].alpha=base. Full TU compiles; saved-register allocation and source-byte endian arithmetic remain. |
| func_801B9A04 | 416 → 406 | 1608/1668 | Saved T-029 draft. Initialize vertex cursors and count before radius call; use count+1 bound, producing target's unrolling structure. Explicit unrolling and bounds/end-pointer variants were worse. Remaining FP/command scheduling and frame differ. |

The six saved drafts were independently remeasured after copying back.
Full TU: BDF94, 238C4, 24CE0, B9A04. Prefix: 14D5C.
Declaration fallback: 15594. These are drafts, not byte-exact claims.

## Bounded searches and rejected candidates

Structural sweeps covered alpha liveness/global views/packet scopes, command
store ordering, counted versus do-loops, texture counters, sprite array views,
loader phase pointers, vertex bound/unrolling shapes, matrix storage and
repeated float conversions. Search scripts and candidates live under /tmp/t132-*.
No permuter directories were created in the repository.

1210 received a 120-second declaration/layout search (28 unchanged), a
240-second permuter run and a second 120-second run after fixing the missing
query prototype. The first run's type-map errors were diagnosed. Candidates
that moved the alpha store after return or inserted empty `if (1) {}` were
rejected; the latter scored 23 words but violates the task's hard rules.
14D5C received a 180-second permuter pass and a 90-second declaration/layout pass (142→136 in 776 compiles).
No permuter candidate was adopted. Declaration search results require the
independent remeasurement recorded below.

## Validation

`make clean && make extract && make -j8 && make progress` exited successfully.
All three executable images and the rebuilt ROM are byte-identical. No new
T4 function is claimed. The final declaration-order result for 14D5C was
independently remeasured at 136 words / 1780 B in prefix context and copied
back without changing executable tokens. Saved declorder result JSON files
record the search dimensions and bounds.

```
OK: rebuilt ROM is byte-identical to baserom.us.z64
OK: main 81736d32e8cda8f399b319a49250dff972b81af8 (239824 bytes)
OK: ovl_7DF8 ea830aae50ff1422da60d4b7fdbfc29f03b1be39 (957392 bytes)
OK: ovl_7E00 2b01138a290212b9d886981e1196f7b6fb45ecdb (153904 bytes)
| Total | 289,876 | 82,572 (28.49%) | 82,572 (28.49%) | 0 | 175 | 0 | 334 | 490 (167,316) |
```

Generated progress outputs have no net change. README.md is restored;
TRACKING.md, WORKLOG.md, functions.csv and status.csv were not manually edited.

## Follow-ups

- 1210's ordinary strings no longer block promotion. Its late float must still
  move naturally to IDO's literal pool when a valid exact text draft exists.
- 14D5C is the strongest new follow-up: exact size, 136 words, matching most
  of the color-loop and tail. Reconcile the legacy audio prototypes and examine
  its early constant/address lifetimes plus frame before another permutation pass.
- 15594 is 16 B short and needs its declarations reconciled before full-TU
  promotion. The saved loop counters are substantially closer than the old draft.
- 24CE0's retained rewrite also fixes a real old-draft addressing error;
  avoid using the old assignment to the first sprite's alpha field as a template.
- 12B7C has a corrected unscored incumbent alternative in this directory;
  do not promote the old fourth-packet cursor store.
- 31DD0 should be classified as a handwritten decoder candidate before more
  IDO matching time is spent on it.
