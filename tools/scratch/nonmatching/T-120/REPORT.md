# T-120 — sol-C44: cluster 3 joint analysis

**1 matched (556 B), 6 improved (19→7 words each).** No commits.
B3B84 is integrated; its draft is deleted. Family B remains assembly with
improved drafts in place. The final clean verification passed (exit 0).

## Common and unique regions

Original instruction alignment is in `original-shapes.diff`; `baseline.json`
records fresh full-TU instruction differences for both representatives.
Offsets below are relative to each function entry. Measurements use production
IDO 5.3 -O2 -mips2 through asm-processor; only actual ELF relocation fields
are masked. Size differences count as differing words.

| Region | Family B | B3B84 | Diagnosis |
|---|---|---|---|
| Entry/counter | +00–+68 | +00–+64 | Shared frame 0x28, s0 cursor owner, counter in a2, signed old-counter test and increment delay slot. B prepares late store-address high half and primitive constant at +3C/+40; B3B84 prepares 255.0f and reads old alpha at those positions. |
| Unsigned conversion | +6C–+E8 | +68–+E4 | Same FCSR save in t7, unsigned conversion with 2^31 fallback, result a0. Both drafts already match this sequence except primitive constant allocation. |
| Early command | +EC–+124 | +E8–+120 | Same mask t1, RGB shifts t2/t3/t5, ORs t4/t6/t7, separate alpha mask t0. Both drafts swap primitive constant t9 with cursor increment t8. |
| Late command | +128–+16C | +124–+164 | Shared palette signed-halfword load, byte mask and RGB packing, old alpha t7 and final pack t8. B reads old alpha here; B3B84 reads it before the counter branch. Both drafts incorrectly keep old alpha in t0. B3B84 consequently allocates its palette chain one register later. |
| Completion/counter | +170–+184 | +168–+198 | B stores its counter at late entry and uses a2 for completion pointer. B3B84 retains a2 for its delayed counter store and <50 predicate, so its completion pointer correctly uses a3; it also stores 1 to D_8029571A. B's draft hoists completion pointer setup into +3C/+40 and delays counter-address setup. |
| Translation/tail | +188–+214 | +19C–+228 | Same operations with different x constants and temporary numbering from B3B84's extra flag constant. Both incoming drafts already match their own tails, including alpha spill/reload at sp+27. |

The stale byte is the same stack byte in both originals, despite its different
load position. B3B84's extra flag is an actual behavioral difference; moving
its late counter store to B's location would be incorrect. Likewise, forcing
B3B84's completion pointer to a2 would conflict with its live counter.

## Experiments

Completed 3,995 focused full-TU measurements (including repeated baselines,
semantically duplicate variants, and deliberately invalid diagnostic models;
13 compiler errors). `experiments.json` records counts and minima per shape.
Initial sweeps were applied to both representatives; follow-up sweeps targeted
the newly isolated regions.
This is a bounded search, not an exhaustive claim.

- Register/value ownership: separate copies of old alpha, placing those copies
  before the counter branch or inside the late branch, separate old/new values,
  incoming scalar reuse, early-alpha assignment positions, explicit late packed
  values, and shared early/late palette locals.
- Slot ownership: scalar widths, nested old-value scopes, union views, single
  byte arrays and pointer views. These diagnostic variants often change the
  byte read from sp+27, or disturb the final spill/reload. None is retained.
- Value order: moving cursor allocation among conversion/mask/pack/alpha
  assignments, postfix versus explicit cursor updates, packet stores before or
  after cursor updates, early word-store order, and a shared packet pointer.
- Counter/call ownership: direct globals versus local pointers for loads and
  stores, separate versus argument-embedded stores, comma expressions in actual
  call arguments, counter predicate forms, and completion-byte pointers/values.
- Color mask: u8/u16/s16/u32/s32 locals, explicit byte versus halfword masks,
  independent alpha assignments, cast placement, and signed command-word views.
  Unsigned float conversion remains necessary; no signed replacement is accepted.
- Declaration/layout: 767 seeded declaration permutations and mixed declaration/
  token-preserving line layouts across the two shapes; 42 contiguous tail joins;
  block scopes and locally scoped declarations. Mixed-declaration compiler errors
  were counted as errors. No source-layout construct improved the current drafts.

Some deliberately diagnostic variants use different storage extents, read an
uninitialized alternative value, or change observable ordering. Their scores are
negative evidence only. No candidate was accepted on a numeric score alone.
The incoming scratch-only uninitialized-alpha warning stays on family B.

## Successful common-region construct

An explicit `(alpha & 0xFF)` in the late packed word separates the old-alpha
load from the tail alpha definition. On B3B84 this independently recovers the
prefix load into t7 and the whole late palette chain, but initially moves the
early primitive constant out of the conversion schedule (41 positional words).
Adding a shared `u32 primitive = 0xFA000000` value, assigned after the entry
check and used by both branches, recovers t9 for that command constant and t8
for cursor increments. Assigning `alpha = value` independently of the narrow
color recovers the separate t0 byte mask. This reaches two words. Joining the
early packet's two stores on one physical line restores word 1 before word 0
in the branch delay slot and reaches zero. The production comment identifies
that line grouping. Ordinary C only; no inline asm, #line, register keyword,
volatile, compiler alteration, artificial branch, or padding.

The shared mask/constant/alpha/store construct transfers to all six B copies,
independently reducing each to seven words at 536 B. `propagation.json` records
those checks. Their late word-0 source store must precede packing. B3B84 retains
its delayed counter store and extra frame<50 flag; the family constants and
globals are unchanged.

## Remaining family-B-specific region

For representative B2EF4 the seven remaining offsets are +3C/+40, +130,
+148/+14C, +170/+184. The draft hoists old alpha's `lbu t7,27(sp)` to +3C,
moves the late primitive constant to +130, and keeps completion address in a3
instead of target a2. Counter-store address scheduling is otherwise recovered.
Conversion, early packing, late palette packing, and the translation tail match.

A focused residual permuter reached weighted zero after 1,107 iterations
(14 compiler errors) by inserting `if (counter) {}` after the late counter
store. **Rejected as an artificial empty branch.** Ordinary packet/block scopes,
removing that branch, actual completion-predicate inversion, prefix/postfix
increments and natural completion goto variants retain seven words. No family-B
function is promoted on that result. Declaration permutations, OR grouping,
completion-pointer/value reuse and mask forms did not improve seven.

## Permuter search accounting

Disposable outputs stayed under /tmp. Initial broad B3B84 search used -j6 for
about 26 minutes (last 13,876 iterations/197 errors); initial B search used -j3
for about 15 minutes (1,890/32). Both were stopped when the improved seed was
found. B3B84's saved 120-weight candidate adds a do/while tail wrapper and still
measures 16 words in full TU; rejected. B's 680-weight candidate restores an
already-present line join. A masked B3B84 diagnostic search was restarted with
mutation restricted to the early packet; its final stage completed 633/15 in
about four minutes, with no accepted result. Short aborted import/focus attempts
are not counted as completed searches.

The final -j6 residual search preserved early and tail store line joins using
PERM_FORCE_SAMELINE and restricted randomization to prefix/late regions. It ran
about five minutes before the rejected empty-branch zero. Combined sequential
search stages exceed 30 minutes; no individual 30-minute timeout completed.
All runs used --stack-diffs --stop-on-zero --best-only --better-only. Weighted
scores are not word counts. Searches were stopped explicitly; no output dirs
are delivered. `search-stages.json` records initial stage iteration counters.

## Per-function results

| Function | Before words / B | Final words / B | Result |
|---|---:|---:|---|
| func_801B2EF4 | 19 / 536 | 7 / 536 | Improved draft |
| func_801B310C | 19 / 536 | 7 / 536 | Improved draft |
| func_801B3324 | 19 / 536 | 7 / 536 | Improved draft |
| func_801B353C | 19 / 536 | 7 / 536 | Improved draft |
| func_801B3754 | 19 / 536 | 7 / 536 | Improved draft |
| func_801B396C | 19 / 536 | 7 / 536 | Improved draft |
| func_801B3B84 | 16 / 556 | 0 / 556 | Promoted; draft deleted |

`final.json` independently measures all retained drafts and production B3B84.
The original uninitialized-alpha behavior is preserved and commented in the
matched C; no initialization or different stack byte was substituted.


## Final verification

`make clean && make extract && make all && make progress` passed (exit 0)
after the production promotion and all draft updates. ROM and all three
executable images are byte-identical, preserving families A/C, BB258 and every
other existing match.

- ROM: ba52e91b44450c548467044b26951353dc491e04
- main: 81736d32e8cda8f399b319a49250dff972b81af8
- ovl_7DF8: ea830aae50ff1422da60d4b7fdbfc29f03b1be39
- ovl_7E00: 2b01138a290212b9d886981e1196f7b6fb45ecdb

No main, boot, ovl_7E00, YAML, Makefile, status.csv, TRACKING or WORKLOG edit.
Dependency symlinks point to the authorized shared checkout; no ROM was copied
or added to git. No commits or subagents. No task searches remain.
Generated progress docs were restored after recording the table below, leaving
shared progress outputs for the lead. `git diff --check` passes.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 73,960 (25.51%) | 73,960 (25.51%) | 0 | 189 | 0 | 320 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 32,792 (22.78%) | 32,792 (22.78%) | 0 | 88 | 0 | 149 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 32,700 (23.79%) | 32,700 (23.79%) | 0 | 101 | 0 | 150 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
