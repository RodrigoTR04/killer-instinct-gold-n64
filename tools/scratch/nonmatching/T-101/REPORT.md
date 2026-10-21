# T-101 — sol-A34: family B, round 2

**0 MATCHED; all 6 drafts IMPROVED 57→19 differing words, 536/536 bytes. Family B remains unsolved. No commits.**

Only these six T-025 drafts were changed. Production GLOBAL_ASM stubs and all
matched C, including family A, remain unchanged. The inherited late-path
uninitialized alpha read is still explicitly marked; these are scratch drafts,
not behavior-validated replacements.

Read TRACKING, latest WORKLOG, Makefile, T-098, T-097 and T-096. Missing
baserom.us.z64, ROMs, .venv and tools/ext were symlinked to the shared project.
No ROM was copied or added to git. No subagents were used.

## Method

Every accepted improvement was compiled inside the complete owning TU with
IDO 5.3 -O2 -mips2 through asm-processor. Counts include length differences;
only actual ELF relocation fields are masked. All six final drafts were
independently measured. `recheck.py` repeats that check after extraction;
`final.json` records the six results and the representative's instructions.
`experiments.json` summarizes the diagnostic sweeps without bulky probe logs.
Compiler products and search outputs remain under /tmp.

## Region 1: entry, counter and call (+00–+68)

T-098 already recovered the signed counter in a2, slti v0,a2,10, ordinary
beqz and shared increment delay slot. The local counter pointer and
`*counter = arg1` as the third lerp argument are retained. B's denominator
10 occupies the jal delay slot; the counter store precedes it. Family A's
call setup must not be transplanted literally.

The target prepares the late counter-store high address in at at +3C and
FA000000 in t9 at +40. The incoming draft instead hoisted the stale byte
load into this prefix. The final candidate removes that early byte load,
but hoists the completion-flag address into a3 at +3C/+40 instead. This is
still incorrect scheduling and allocation, not a relocation-only difference.

Tried cached flag pointers, prefix/postfix flag increments, explicit flag
loads into incoming arg1, direct versus local counter stores, counter pointer
initialization placement, constant-command locals, goto/if forms, declaration
moves and token-preserving line joins. None reduced the final 19 words.

## Region 2: unsigned float conversion and command allocation (+6C–+110)

Target saves FCSR in t7, converts to u32 using the 2^31 fallback, masks the
result into t1, then loads the display cursor at +F0. FCSR restoration occurs
at +104; the cursor increment/store follow at +10C/+110. The incoming draft
allocated the command during conversion, shifting much of this sequence.

**Successful hypothesis:** compute packed color and assign alpha before
`p0 = (*arg0)++`. Moving allocation there, rather than loading p0 before
packing and updating its owner separately, reduces 57→22 words. All conversion
instructions, FCSR registers, and the +F0 cursor load now agree. This is a
source lifetime/order change; the emitted command remains the same.

The remaining early differences are the command constant in t8 rather than
t9 (+7C/+124), and cursor increment/store using t9 rather than t8
(+10C/+110). Sizes and stack frame remain exact.

## Region 3: color mask, packing and alpha (+EC–+124)

Target masks the u32 conversion result into t1 and replicates it with shifts
24,16,8 and two ORs, then ORs in t1. It independently masks the result into
t0 for tail alpha. The conversion must remain unsigned; a signed conversion
loses the target's fallback sequence.

**Successful hypothesis:** form the entire RGBA value in `packed`, including
the fourth byte, then assign that temporary to word 1. This reduces 22→21
by recovering `or t7,t6,t1`; reversing the operands only at the final store
did not change IDO's chosen order.

The byte color with `(u16)value` is retained from T-098. Tested u16/s16/u32/s32
color temporaries, low-byte masks before/after narrowing, direct lerp-result
assignment, chained alpha/color assignments, unsigned shift casts, signed
command fields, and alpha assignment at several points. These either retain
the best count or disturb conversion/masks and scheduling. No extra u16 mask,
changed conversion semantics, or stack-shape repair was retained.

## Region 4: late command and completion flag (+128–+184)

Target stores the incremented counter, loads v1 from s0, reads stale alpha
from sp+27 into t7, increments the cursor in t8, stores command word 0 using
t9, reads signed palette color into v0, and obtains the completion-flag
pointer in a2. Its palette mask/replication uses t1–t6, then ORs t6 with old
alpha t7 into t8. The flag value uses a1; the new tail alpha becomes 255 in t0.

**Successful hypothesis:** place the late source word-0 store after the
word-1 store. IDO still emits word 0 before word 1, but now keeps the stale
alpha load in the late block. This reduces 21→19 words. The draft comments
identify both ordering choices. This is ordinary separate-field C; no
volatile, inline assembly, artificial branch, or compiler flag was retained.

In the final candidate, +128 introduces the counter-store lui instead of the
store itself. The store, cursor load, stale-byte load, palette-address lui and
cursor increment/store are consequently shifted by one instruction through
+140. The stale read is **sp+27**, now at +134 into t0. The palette mask and
replication at +150–+164 agree exactly. The primitive constant/store occupy
+148/+14C instead of the target's completion-flag address setup. At +168/+16C,
the old alpha is t0 and the packed result t7, versus target t7/t8. At
+170/+184 the flag pointer remains a3 rather than a2. These are real
unresolved differences.

Tried distinct old-alpha temporaries (both uninitialized and explicit copies),
branch scopes, pointer/array/union representations, masks and casts at the
late read, alpha widths, direct use of other existing temporaries, deferred
palette masks, separate packed late values, allocation placement, and flag
pointer/value lifetimes. Wrong stack offsets and additional reads/stores were
rejected. An uninitialized separate byte is not a repair for the required
sp+27 read. Initializing alpha would change the target and was not retained.

## Region 5: translation and final commands (+188–+214)

The entire region already agrees in the final candidate: signed depth load,
argument setup, alpha spill/reload at sp+27, guTranslate call, environment
color, shared display-list pointer and epilogue. Distinct per-copy x
coordinates and entry/completion thresholds are preserved. No tail changes
were necessary.

## Permuter

Used the shared decomp-permuter with `--stack-diffs --stop-on-zero
--best-only --better-only -j 3` in bounded searches from the 22-word and
19-word stages. Scores are weighted assembly differences, not word counts.
Normalization changed initial scheduling (initial weighted scores 695 and
680). Lower weighted outputs introduced empty conditionals, including one
reading an uninitialized color temporary. Those artificial branches were
rejected. A chained color/alpha assignment suggested by a search was tested
without the empty branch; it did not improve the retained 19-word candidate.
No permuter output was promoted automatically.

## Per-copy results

| Function | Counter | Threshold | x | Result | Bytes |
|---|---|---:|---:|---|---:|
| func_801B2EF4 | D_801D30C0 | 2 | -125.0f | 57→19 | 536/536 |
| func_801B310C | D_801D30C4 | 3 | -75.0f | 57→19 | 536/536 |
| func_801B3324 | D_801D30C8 | 4 | -30.0f | 57→19 | 536/536 |
| func_801B353C | D_801D30CC | 5 | 14.0f | 57→19 | 536/536 |
| func_801B3754 | D_801D30D0 | 6 | 70.0f | 57→19 | 536/536 |
| func_801B396C | D_801D30D4 | 7 | 128.0f | 57→19 | 536/536 |

No production declaration change, draft deletion, or function promotion.
The next useful target is the counter-store/primitive-constant/completion-
flag address lifetimes, together with the old versus new alpha register.

The two bounded searches completed about 5,739 and 7,669 iterations,
respectively (69 and 111 compile errors reported by the permuter). Neither
produced an acceptable match. The first and second searches overlapped;
their output directories were shared, but each process loaded its initial
base before the second base was installed. No result is accepted on that
basis: retained candidates were measured independently in the full TU.
The completed focused sweeps contain 891 measurements, including repeated
baselines and deliberately rejected diagnostics. This is not an exhaustive
search. No task probe process remains.

## Final verification

`make clean && make extract && make all && make progress` passed (exit 0).
The ROM and all executable images are byte-identical, preserving every
already-matched function, including family A:

- ROM: ba52e91b44450c548467044b26951353dc491e04
- main: 81736d32e8cda8f399b319a49250dff972b81af8
- ovl_7DF8: ea830aae50ff1422da60d4b7fdbfc29f03b1be39
- ovl_7E00: 2b01138a290212b9d886981e1196f7b6fb45ecdb

`git diff --check` passed. No commits. No generated progress files differ.
main, boot, ovl_7E00, YAML, Makefile, status.csv, TRACKING and WORKLOG are
untouched. Local dependency symlinks remain untracked. Matching totals are
unchanged; the task's requested exact matches were not achieved.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 63,432 (21.88%) | 63,432 (21.88%) | 0 | 215 | 0 | 294 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 29,576 (20.54%) | 29,576 (20.54%) | 0 | 94 | 0 | 143 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 25,388 (18.47%) | 25,388 (18.47%) | 0 | 121 | 0 | 130 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
