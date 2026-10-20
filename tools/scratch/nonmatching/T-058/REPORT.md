# T-058 — sol-A21: main near-misses

**1 MATCHED (316 bytes), 4 IMPROVED drafts, 10 UNCHANGED.** All 15 requested
functions were attempted. Changes are uncommitted for lead review.

## Method and evidence

Read TRACKING, latest WORKLOG, Makefile, and T-052/T-040/T-046/T-051 reports.
Missing baserom, ROMs, .venv, and tools/ext were symlinked from the authorized
main checkout. No ROM bytes were copied or added to git.

Used IDO 5.3 with production `-O2 -mips2 -G 0 -non_shared -Xcpluscomm
-Wab,-r4300_mul -32`. Fifteen experiment batches include statement/declaration
orders, local copies, chained stores, loop/branch forms, scalar widths,
callee return/argument types, array/struct access, K&R definitions, and
parameter qualifiers. No inline asm, register bindings, compiler overrides,
or build transformations were used. No subagents were launched.

`attempt_counts.json` counts **4,336 archived compiler-result records** across
all functions (including baselines, compile errors and repeated candidates
across batches; this is not a count of distinct successful implementations).
Some preliminary rounds have logs rather than complete per-candidate JSON;
they are additional experiments, not included in that count. `inputs/*.txt`
preserves the starting drafts, so the probes do not silently use the improved
drafts as their new baseline. Generated candidates have `.candidate.txt`
extensions and are diagnostic alternatives, not additional retained drafts.

`probe.py` measures positional instruction differences, masking only actual
ELF HI16/LO16/26 relocation fields. `linkprobe.py` additionally resolves those
relocations with the real linker and original symbol addresses, placing text
with four-byte subalignment to avoid inventing alignment gaps for non-16-byte
function starts. `retained.json` rechecks every starting and retained draft
with both methods. Only the promoted function is a matching claim, supported
by the complete clean image/ROM validation.

Unsigned/narrowed products, altered floating-point argument ABIs, const stores,
and other behavior-changing diagnostic forms were rejected. In particular,
the AA98/AAEC variants with apparently lower counts narrow the product or
change the volume argument's signedness; neither is retained. Lower positional
counts alone do not prove a match or even correct behavior.

## Per-function results

Word counts in the result column use T-052's relocation-masked positional
metric. All retained target-sized drafts also have the same fully resolved
count, except the **old AEE4 baseline is 49 resolved words versus 48 masked**.
Offsets below are relative to the function start.

| Function | Result | Bytes old → retained (target) | Archived records | Attempts / remaining differences |
|---|---|---|---:|---|
| func_8002DF98 | UNCHANGED, 2 words | 244 → 244 (244) | 199 | Product operand reversals, explicit products/results, flat/row/struct matrix views, local loads and parameter qualifiers. Only +0x10/+0x14 remain: `mtc1 a1` versus matrix load order. Splitting the first products does not move that schedule. |
| func_8002B57C | UNCHANGED, 4 words | 368 → 368 (368) | 72 | Signed/unsigned 8/16/32-bit indices, nested/inverted guards, do/while versus for, equality bound, and explicit four-controller expansion. Remaining +0x84/+0x88 and +0xA8/+0xAC are the original branch/address-setup scheduling pairs. |
| func_8002A300 | UNCHANGED, 7 words | 268 → 268 (268) | 171 | Declaration/initialization permutations, explicit input/output/count copies, all three setup-call return types, word/halfword/byte accumulator forms, comma expressions, inverted delta arm, and decrement-loop forms. The body from +0x3C onward matches; only prologue scheduling at +0x1C/+0x20/+0x24/+0x28/+0x2C/+0x30/+0x38 remains. |
| func_8002A900 | IMPROVED **24→18** | 220 → 220 (220) | 45 | Initialize the wait counter after the optional DMA block. Tried index/count/state widths, argument casts, scalar/array last-index declarations and call returns. Frame/prologue and pre-DMA allocation still differ, plus wait-loop scheduling. Updated T-024 draft. |
| func_80015F6C | IMPROVED **27→21** | 268 → 268 (268) | 303 | Corrected audio prototypes: F8F8 takes one voice pointer; F6F4 returns a pointer and takes a halfword id. Separate white stores in 1/0/2 order. Tested all white-store orders, chains, typed white locals, return types, RGB struct/array forms, timer widths, inverted color guard and tail if/else. White-value register allocation and subsequent temporary numbering remain different. Updated T-020 draft. |
| func_8002F45C | IMPROVED **39→27** | 404 → 404 (404) | 147 | Corrected `key` to u8 and `state` to s32 (original uses lbu and sw); calculate pan before the status store; declare old interrupt mask before key pointer. Also tried all independent initialization orders, pan widths, key-load timing and next/prev order. Frame is still 0x30 versus original 0x38, key/pan spill slots and pan register differ, and several stores are reordered. Updated T-024 draft. |
| func_80012950 | **MATCHED** | 312 → **316** (316) | 1,915 | Unsigned phase bytes, `AD08 = AD09 = 0`, and separate ascending chains for each three-byte array produce the original descending stores and base registers. Use `20000.0f` in the owning TU. Full image and ROM verification passed. Deleted T-033 draft. |
| func_8002AEE4 | IMPROVED **48→13** (resolved **49→13**) | 336 → 336 (336) | 452 | Fixed first-buffer skip: test ready before clearing it. Put message declaration between samples and ready. Tested all five local declaration orders, scalar/client widths, explicit registration prototypes, scalar initialization orders, switch/if forms and top/bottom-tested loops. Remaining +0x1C..+0x48 are prologue/registration/client-slot scheduling; +0x9C/+0x108 use the loop's constant register for done=1 rather than immediate 1. Updated T-024 draft. |
| func_8002B1EC | UNCHANGED, 4 words | 64 → 64 (64) | 46 | Early return, combined guard, divide/shift/bound tests, length return widths and global qualifiers. Separate load/store address setup remains at +0x18/+0x1C/+0x20/+0x2C. |
| func_8002B91C | UNCHANGED, 4 words | 64 → 64 (64) | 156 | All 120 store orders, parameter qualifiers and K&R forms. Double-parameter diagnostics change ABI and were rejected. Home stores remain one slot off at +0x04/+0x08 and +0x14/+0x18. |
| func_8002B95C | UNCHANGED, 2 words | 88 → 88 (88) | 50 | Perspective return type, norm width, matrix parameter shape, parameter qualifiers and K&R forms. +0x24/+0x28 remain the prologue/home-store scheduling swap. |
| func_8002B7E0 | UNCHANGED, 2 words | 208 → 208 (208) | 24 | Perspective return type, norm widths and B8B0 argument signedness/width. +0x08/+0x0C remain the prologue swap. |
| func_8002DCC8 | UNCHANGED, 4 words | 268 → 268 (268) | 34 | Every delta declaration order, sum orders, qualifiers and K&R forms. Reordered floating sums were diagnostic only. Original +0x20/+0x24 and +0x30/+0x34 scheduling pairs remain. |
| func_8002AA98 | UNCHANGED, 9 emitted words + missing tail word | 80 → 80 (84) | 361 | Product/result/parameter signedness and widths, explicit intermediate shift/cast forms, multiply operand order, and void/s32 callee returns. No equivalent form recovers the original mflo a2, double sign extension and final move a1,t0. Narrow-product candidates rejected. |
| func_8002AAEC | UNCHANGED, 9 emitted words + missing tail word | 80 → 80 (84) | 361 | Same volume-scaling family as AA98, tested independently. Same remaining instruction/register shape and missing word; behavior-changing candidates rejected. |

## 12950 integration and relocation trap

The first zero-masked-difference candidate was **not** a match: the linked
image differed in four relocation operands. It cleared the same bytes, but
used AD08 where the original materializes AD09, and exchanged the two color
array bases. This was caught by full-image verification and motivated the
resolved-link probe. It was never counted as matched.

The final natural form needs **both phase bytes unsigned**, then
`D_8004AD08 = D_8004AD09 = 0`. Each color array gets its own chain:
`a[0] = a[1] = a[2] = 0`. The original base-symbol operands now match too.
No other function body was changed to achieve this. The new declarations
agree with existing declarations in main_2FF0.c; D_8004AD09 had no preceding
production C declaration in that TU.

12950 naturally owned D_800487A0 at the first slot of main_2FF0's existing
.rodata range. Promoting it uses literal `20000.0f`, which emits the original
word at 0x800487A0. All later rodata remains byte-identical. **No
force_migration/function_owner hint, symbol-address file, BSS mapping or YAML
was changed.** The source edit is confined to 12950 and its declarations.
Other workers' functions are untouched.

Deleted draft:

- `tools/scratch/nonmatching/T-033/func_80012950.c`

The four improved drafts stay at their original paths. No other draft was
deleted. All ten unchanged drafts retain their original contents.

## Final validation

After the final source change and draft deletion:

`make clean && make extract && make -j8 all && make progress` **passed**.

- ROM: `ba52e91b44450c548467044b26951353dc491e04`, byte-identical.
- main: `81736d32e8cda8f399b319a49250dff972b81af8`, byte-identical.
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`, byte-identical.
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`, byte-identical.
- `git diff --check` passed.

No boot/overlay source, YAML, Makefile, status.csv, TRACKING or WORKLOG edits.
Regenerated linker files have no diff. Generated progress documents were
restored after recording this table, leaving metric updates for the lead.
No commits were made.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 54,900 (17.20%) | 54,900 (17.20%) | 0 | 304 | 0 | 258 | 437 (138,092) |
| boot | 8,468 | 8,108 (95.75%) | 8,108 (95.75%) | 0 | 1 | 0 | 20 | 99 (16,028) |
| main | 173,204 | 32,088 (18.53%) | 32,088 (18.53%) | 0 | 144 | 0 | 146 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 14,704 (10.70%) | 14,704 (10.70%) | 0 | 159 | 0 | 92 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
