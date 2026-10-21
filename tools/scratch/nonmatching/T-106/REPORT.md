# T-106 — sol-B34: coordinate family

**6 MATCHED (3,152 bytes), 2 IMPROVED. No commits.**

Matched func_801BA088, func_801BA280, func_801BA470, func_801BA674,
func_801BB024 and func_801BB594 in ovl_7DF8_5ED0.c; deleted their T-023
drafts. BB258 and BADEC remain drafts, improved in place. BB258 is a true
sibling but not yet matched; BADEC is a related conditional renderer.

Read TRACKING, latest WORKLOG and Makefile first, followed by T-099's screen
and T-050/T-097/T-069/T-067 reports. Missing baserom.us.z64, ROMs, .venv and
tools/ext were symlinked from the authorized main checkout. No ROM was copied
or added to git. No subagents were used.

## Original assembly comparison

All eight originals were compared as instruction streams, including register
operands and control flow. analyze.py records the pre-promotion comparison;
its normalized similarity is only a screening aid, not equivalence evidence.

The seven unconditional two-draw functions are structural siblings: load u16
scale at state+0x7E and s16 y offset at +0x80; compute four signed fixed-point
coordinates; optionally mirror both x coordinates around 0x9B0; call
func_801BC1B0 twice with 15 arguments; reload state scale for the second call.
Four cvt.s.w instructions convert the final coordinates. There is no loop,
inline Gfx builder, struct copy, or missing helper call in this family.

| Function | Original frame | Distinguishing structure |
|---|---:|---|
| 801BA088 | 0x58 | Interleaved frame tables, counter wraps at 0x35 to 2 |
| 801BA280 | 0x58 | Two independent arg3 shift/modulo selectors; no counter update |
| 801BA470 | 0x58 | Interleaved tables; counter wraps at 0x20 |
| 801BA674 | 0x58 | Counter/3 interleaved tables; counter wraps at 12 |
| 801BB024 | 0x58 | Mirror-dependent x offsets and scale*4/3 for both calls |
| 801BB258 | 0x50 | Shared x coordinate; counter/3 tables; wraps at 12 |
| 801BB594 | 0x58 | Separate counter/2 and counter/4 selectors; wraps at 40 |
| 801BADEC | 0x58 | Related coordinate builder, not an unconditional clone: one shared x, two independent conditional animation windows and an early return |

BADEC updates separate counters before its two optional draws. Its initial
12-byte excess does not establish the same nine-instruction defect.

## Shared structural cause and solution

**The drafts cache `state->scale` in a scalar.** With that scalar, IDO carries
scale, y base and y offset across the first draw and rebuilds the second y
coordinate afterward. The original preserves the completed integer pair.
Reading scale directly from the state field instead prevents that
alias-sensitive rematerialization across the call. Removing the cached scale
alone brings all seven unconditional siblings to their exact original sizes.
The load remains u16; no ABI, compiler flag or field-width change is needed.

BA088 original +0x00..0x10 homes a0/a3, but not a2. Original +0x14..0xA0
computes both integer pairs before the mirror branch. Its first call at
+0x12C preserves the second pair in sp+0x4C/sp+0x48. The initial draft has
frame 0x70, homes a2, and spills ingredients for the later recomputation.
Just moving the first y calculation before the branch leaves 540 bytes/132
words: the cached scale still allows IDO to rebuild it. This ruled out a
statement-order-only explanation.

The matched C uses four signed coordinate locals, direct field expressions,
and an explicit counter pointer where applicable. Inlining the base/offset
expressions removes unnecessary local stack slots. The counter pointer
recovers symbolic loads/stores instead of a separately materialized global
address. Declaration order then recovers the exact spill slots. BA088's
stages were 132 words/540 B → 109/504 (direct fields) → 49/504 (explicit
coordinates and inline bases) → 15/504 (counter pointer) → 0/504 (declarations).

The transfer matched BA280, BA470 and BB024. BA674 additionally needs its
byte-addressed table expressions: T-050's typed indexing leaves 36 words;
restoring `*(s32 *)(table + (counter / 3) * 8)` gives zero. BB594 needs both
x calculations before the y calculations, plus declaration order for its
sp+0x50 x spill. This reduces 65 words to two, then zero. Token-preserving
line layouts were tested; the delivered matches need ordinary statement
lines, without scheduling directives or artificial constructs.

All six cleaned functions, with meaningful x0/y0/x1/y1/nextFrame names, were
independently checked through asm-processor in the full owning TU at zero
words before promotion. The final linked build is the relocation/ROM check.
No inline asm, #line, register keyword, volatile workaround, padding or
compiler override is retained. No other production function was edited.

## Remaining drafts

BB258 received the shared direct-field fix, explicit coordinate/counter
locals, coordinate/declaration searches and a bounded permuter search. It is
524/524 bytes and improves 138→20 words. Remaining differences are a register
cycle among scale, the original x and its copied x (t0/t1/t2), including the
scale argument and x spill/reload. The retained u32 cast on the 0x153 scale
product is equivalent: the input is u16 and the product fits signed s32.
No change to the struct's u16 scale member is retained.

BADEC retains the safe coordinate-array improvement, 580→568 bytes and
144→118 words. Its conditional calls and redundant counter stores need a
separate control-flow/register solution. Direct-field/pointer diagnostics
reached 108 words but 560/568 bytes; these are not promoted or retained as the
best draft. It is not counted among the six matches.

| Function | Result | Words before → after | Compiled bytes before → after | Original bytes |
|---|---|---:|---:|---:|
| func_801BA088 | MATCHED | 132 → 0 | 540 → 504 | 504 |
| func_801BA280 | MATCHED | 129 → 0 | 532 → 496 | 496 |
| func_801BA470 | MATCHED | 133 → 0 | 552 → 516 | 516 |
| func_801BA674 | MATCHED | 135 → 0 | 564 → 528 | 528 |
| func_801BB024 | MATCHED | 148 → 0 | 600 → 564 | 564 |
| func_801BB258 | IMPROVED | 138 → 20 | 556 → 524 | 524 |
| func_801BB594 | MATCHED | 140 → 0 | 580 → 544 | 544 |
| func_801BADEC | IMPROVED | 144 → 118 | 580 → 568 | 568 |

## Measurement, searches and rejected experiments

Scores count differing aligned instruction words plus size difference in
words, masking only real ELF relocation fields. Production flags are IDO 5.3
-O2 -mips2 through asm-processor. No alternate flags were retained.

Local searches used tools/permuter/import_fn.py and the shared install with
--stack-diffs, --stop-on-zero, --best-only, --better-only and four processes:
180 seconds on the incoming BA088 draft, 300 seconds on a safe input-reuse
diagnostic, a direct-field BA088 search stopped after manual diagnosis found
the match, and 180 seconds on BB258. BB258's useful candidate supplied the
unsigned-product expression; a redundant copy was removed and the candidate
remeasured. None of the permuter's behavior-changing low-score outputs was
retained. Its weighted score is not a differing-word count.

Other diagnostics covered scalar widths, expression grouping, source layouts,
inner scopes, coordinate structs/arrays, initialized locals and input reuse.
Unsafe input reuse overwrites a still-needed coordinate base and was rejected.
Runtime aggregate initializers fail IDO's constant-expression requirement.
A broad text substitution that also changed the struct member width was
rejected. No width-changing diagnostic is proposed C.

A fixed-name scratch probe collision occurred during overlapping early
scripts. Those results are not acceptance evidence. The retained probe helper
uses a process-specific temporary path and raises compiler errors. Final
candidates were independently remeasured sequentially in full TU context.
A measurement attempted during make clean failed because generated assembly
was temporarily absent; it was rerun after extraction. No compiler error is
scored as a match. Probe products and bulky logs remain in /tmp.

Scripts here record pre-promotion experiments: after promotion, splat no
longer emits nonmatching assembly for the six C functions. Original code
bytes remain in the untouched build/segments image. No generated objects or
ROM data are included in the deliverable.

## Final verification

`make clean && make extract && make all && make progress` passed (exit 0).
The ROM and all three executable images are byte-identical:

- ROM: `ba52e91b44450c548467044b26951353dc491e04`
- main: `81736d32e8cda8f399b319a49250dff972b81af8`
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`

`git diff --check` passed. No task probe/permuter processes remain. No commits.
Generated docs/functions.csv and docs/progress.html were restored after
recording the table. No net linker-script changes remain. status.csv,
TRACKING, WORKLOG, main, boot, ovl_7E00, YAML and Makefile are untouched.
Matched bytes increase 66,512→69,664 (+3,152); T4 increases 305→311.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 69,664 (24.03%) | 69,664 (24.03%) | 0 | 198 | 0 | 311 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 30,556 (21.22%) | 30,556 (21.22%) | 0 | 91 | 0 | 146 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 30,640 (22.30%) | 30,640 (22.30%) | 0 | 107 | 0 | 144 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
