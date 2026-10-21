# T-104 — sol-B33

**1 MATCHED (116 B), 5 IMPROVED, 15 UNCHANGED. No commits.**

Read TRACKING, latest WORKLOG, Makefile, permuter README, T-099 screen/report,
T-096/T-097 instruction-level diagnoses, T-067 scheduling notes, and the latest
relevant T-093/T-094/T-095 reports. Missing baserom.us.z64, ROMs, .venv and
tools/ext were symlinked from the authorized shared checkout. No ROM was copied
or added to git.

## Method

Every initial draft received an instruction-by-instruction comparison, concrete
C probes, then ordinary line-layout probes. `instructions.json` records target
and draft instructions at every differing offset. Counts include missing words
and mask only actual ELF relocation fields. Current incoming scores differ from
the older refreshed screen because T-099 improved four drafts after that screen.
These counts are separate from weighted permuter penalties.

Production IDO 5.3 -O2 -mips2 through asm-processor throughout. Full TU context
is preferred; legacy prefix/declaration fallbacks are explicitly identified.
Improved scratch code is diagnostic, not behavior certification. No compiler
flags, linker inputs, binary instructions or ROM bytes were rewritten.

Each unresolved function received a bounded local decomp-permuter search with
-j5, --stack-diffs --stop-on-zero --best-only --better-only. Search inputs and
compiler products stay in /tmp/kig-t104, outside the repository. An initial
temporary importer dropped function return types; that preliminary round was
stopped and discarded as search evidence. The corrected round explicitly retains
all signatures, notably BD270's u64 and BD200's u8. Final comparisons independently
compile the complete production TU. No subagents or network workers were used.

## Per-function findings

Offsets are relative to the function. Words refer to the actual incoming drafts,
not the older screen or the production assembly. The retained-result column reports independently checked changes.

| Function | Incoming words / B | Result | Diagnosis and concrete experiments |
|---|---:|---|---|
| func_801CC908 | 2 / 424 | UNCHANGED | Only +0C/+19C frame allocation/free: 0x40 instead of 0x30. Mask/status/handle spills already agree. Removing duplicate status/dead home locals and permuting the three live locals obtains frame 0x30 but moves the mask spill to +20 instead of +24. Cached handle/status pointers, scopes, unsigned mask, single-element handle array and file-index record do not solve both requirements together. No padding local retained. |
| func_801CCD74 | 4 / 116 | MATCHED, 116 B | +10/+14 previous/current loads must own t6/v1, with a1 addressing previous; +20 comparison and +28 store follow those owners. Direct current/previous global reads, current-first comparison and previous-first chained clear solve all four. Cleaned against the TU's existing s32-output ABI; full-TU zero, integrated and draft deleted. |
| func_801C85C0 | 4 / 168 | UNCHANGED | +48/+4C index add/mask should precede byte/word clears at +50/+58. Tested explicit next-index local, counter starting at two, widths and layouts. Existing earlier callee definition takes two u8 arguments. Reconciled full TU is 24 words; byte/halfword counters reach 11, still worse than the fallback. No callee change retained. |
| func_801BF678 | 9 / 164 (target 168) | IMPROVED, 7 | Initial constant ownership/order is recovered by a joined setup line. Tail still has mflo before counter decrement, pointer decrement in the branch delay slot and one missing nop. Tested all independent divide/counter/pointer update orders, postdecrement condition and layouts. |
| func_8001E0B4 | 9 / 648 | UNCHANGED | +5C..+70 counter initialization precedes five global bases; +E4/+E8/+F4 flag loads/halfword clear are scheduled differently. Late counter initialization and moving the clear after flag evaluation retain or worsen differences. Load/store widths stay unchanged. |
| func_8002F45C | 4 / 404 | UNCHANGED | +B4/+C0 envelope loop load/add owns a1 instead of v1; +DC/+E4 key flag load/mask owns v1 instead of t3. Tested named loop value, direct flag expression, flag widths and layouts. Pan, its spills, frame and owner/flag order already agree. |
| func_801BD270 | 7 / 396 | UNCHANGED | +154..+170 high-word addition, low-word carry and sign contribution order/registers differ. Incoming s16 Y and u16 buttons already recover the target halfword spill widths/slots. Explicit axis words of u32/s32/u64, commuted additions and layouts do not solve the carry chain. |
| func_8001BDE0 | 13 / 316 | IMPROVED, 9 | Updating the command cursor with *arg0 += 8 recovers v1 at +40/+4C/+64/+74. Remaining input threshold/offset ownership is f24/f20 instead of f20/f24, including saves and comparisons. Threshold snapshot and layouts do not fix FP allocation. Mutable external scale/offset semantics preserved. |
| func_801BD200 | 14 / 112 | UNCHANGED | Initial maximum should load into t6, cursor into v0, result address into v1 and one into a1; draft retains maximum in v0, cursor a1 and one a2. Explicit maximum/result pointers, minimum via incoming argument and layouts do not recover those lifetimes. |
| func_801C7A98 | 14 / 568 | UNCHANGED | +17C onward mode base should occupy a1, maximum address a0 and constant five a2; draft's scalar/record lifetime also changes branch/store scheduling. Cached mode pointer, maximum widths and layouts tested. Prefix score still needs later scalar-mode declaration reconciliation. |
| func_8002A900 | 15 / 220 | UNCHANGED | +00..+24 current index load/frame saves and index/counter s1/s0 ownership; +58..+64 current-index store and sequence-player setup. Cached current-index pointer, earlier counter setup and layouts tested. Prefix context's later music-table/boot_dma declaration conflicts remain. |
| func_801C7F90 | 16 / 116 | UNCHANGED | Initial scalar clear should use symbolic at; draft retains its address in a1. Four-way clear loop stores zero at -3/-2/-1 then -4 in the delay slot, versus -4/-3/-2 then -1. Separate initial clears, for-loop update and layouts do not solve both. Prefix/global-array reconciliation remains necessary. |
| func_801B5534 | 18 / 168 | IMPROVED, 5 | Use one random sample and direct remainder expressions for the two output tables; IDO shares the divide and emits the early index shift. Remaining player home reload is lw at +20 rather than lbu at +23, offset spill/reload +18 instead of +1C, and call narrowing versus move. Parameter/local byte views and explicit precomputed offsets worsen size/allocation. |
| func_801C0800 | 21 / 248 | UNCHANGED | +90..+B8 RGBA packing temp ownership, then final command/address and index update temps differ. Tested right-associated/commuted packing, unsigned/add forms and layouts. No split-shift or do-once workaround retained. |
| func_801C8AE0 | 21 / 324 | UNCHANGED | +90 onward packed result owns t5 rather than t7; following byte loads and nibble pairs inherit the wrong temporary sequence. Tested signed/unsigned accumulators, separate packed result, narrowing and tail commutation. Declaration fallback only; raw redundant masks/comma-zero constructs rejected. |
| func_801B0520 | 22 / 328 | UNCHANGED | Initial frame uses v1 rather than v0; color packing temps and second frame read/base reuse differ. Input reuse, direct global reads, frame pointer lifetime and right-grouped color expression do not improve clean code. Duplicate color stores rejected. |
| func_801C8C24 | 22 / 396 (target 408) | UNCHANGED | Loop agrees; tail lacks explicit arg0+1/+2/+3 addresses in v1/a0/a1 and interleaves epilogue reloads earlier. Postincrement unpacking and four named byte addresses fold back to indexed loads. Declaration fallback only; three words remain missing. |
| func_800269AC | 25 / 236 | IMPROVED, 2 | Separate primitive-command cursor recovers almost all temp/global ownership; command-first stores recover t7 command and t8 alpha. Only +88/+8C stores remain reversed. Dedicated/scoped cursors, typed words, alias uses, scalar constants and token-preserving layouts tested; all three display-list command positions preserved. |
| func_800268C0 | 28 / 236 | UNCHANGED | Source-offset base/add grouping and byte temp ownership differ; after decode slot reload is t0 instead of a0 and dimension copies use argument regs instead of t7/t8/t1/t0. Tested commuted entry/base expressions and packed-offset grouping. A raw lower score reads dimensions through the output size record and was rejected. |
| func_801B446C | 28 / 292 | UNCHANGED | Target retains &flag in t0 and loads/stores through it; draft folds symbolic addresses, shifting branch/completion scheduling. Pointer |=, reloaded flags and byte flags tested. Raw candidates redirect flag accesses through cursor, sometimes uninitialized; rejected. |
| func_801B1210 | 29 / 284 | IMPROVED, 28 | Alpha/current global should occupy t1 instead of v0/v1; command stores and final alpha store/call setup differ. Input reuse, unsigned alpha input and assignment in call argument do not solve it. Removing the raw do-once wrapper and narrowing the layout change to one joined command pair retains one word of improvement. Raw unreachable-store/dummy-goto candidates rejected. |

## Integration and validation

Only CCD74 and its two needed externs change production C. No boot, ovl_7E00,
YAML, Makefile, status.csv, TRACKING or WORKLOG edits. No inline asm, #line,
register keyword, dummy branches, padding objects or compiler overrides.
Improved drafts stay in their original directories; no search output directory
or bulky log is part of the deliverable. Changes remain uncommitted for lead review.


`make clean && make extract && make all && make progress` passed (exit 0).
The ROM and all three executable images are byte-identical:

- ROM: ba52e91b44450c548467044b26951353dc491e04
- main: 81736d32e8cda8f399b319a49250dff972b81af8
- ovl_7DF8: ea830aae50ff1422da60d4b7fdbfc29f03b1be39
- ovl_7E00: 2b01138a290212b9d886981e1196f7b6fb45ecdb

All five retained improvements independently compile in their complete owning TUs.
BF678 remains 164/168 B; the other four are target-sized. CCD74's linked-image
validation resolves every relocation, beyond its preliminary masked zero.
Generated progress documents are restored after capturing this table. Local
prerequisite symlinks stay untracked. No ROM or generated search tree is staged.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 65,692 (22.66%) | 65,692 (22.66%) | 0 | 206 | 0 | 303 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 30,092 (20.90%) | 30,092 (20.90%) | 0 | 92 | 0 | 145 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 27,132 (19.74%) | 27,132 (19.74%) | 0 | 114 | 0 | 137 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |


The corrected searches have all finished. Twenty unresolved functions ran
900.1–900.3 seconds each; CCD74 stopped after 215.3 seconds after its independent
clean full-TU match. Exit 137 reflects bounded process-group interrupt termination,
not a build failure. No task search/probe processes remain. No additional clean
match emerged. Late raw outputs that move the digit counter decrement into only
one branch, overwrite the final environment command or add empty pointer
conditions were rejected. Caching E0B4's active-selector byte early was independently
checked at ten words and was not retained. The preliminary malformed-signature runs are not included in these
durations. `results.json` records corrected durations, weighted penalties, retained
word counts/contexts. `git diff --check` passes.
