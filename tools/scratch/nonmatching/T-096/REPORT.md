# T-096 — sol-C35: hard residue

**3 MATCHED (572 bytes), 0 IMPROVED, 16 UNCHANGED. No commits.**

Promoted `func_8002AA98` (84 B), `func_8002AAEC` (84 B), and
`func_801C5064` (404 B). Their drafts were deleted. Other drafts are unchanged.
Only main_1AB90.c and ovl_7DF8_190B0.c have production edits. No boot,
ovl_7E00, YAML, Makefile, status.csv, tracking or worklog edits.

Read TRACKING, latest WORKLOG and Makefile first. Searched each requested
function across previous REPORT.md files; prior-reports.json records the
per-function hit list, including the requested T-053/057/061/062/066/071/
077/082/088/089/092 reports. Prior work already covered many proposed
hypotheses, including counter storage classes, lerp helpers and argument
widths. This round tested the current complete-TU context rather than
assuming the older prefix measurements still applied.

Missing baserom.us.z64, ROMs, .venv and tools/ext were symlinked from
`/home/rodri/Projects/killer-instinct-gold-n64`. No ROM was copied into git.

## Method and evidence

Production IDO 5.3 -O2 -mips2 through asm-processor throughout. Scores count
aligned instruction differences plus length differences and mask only actual
ELF HI16/LO16/26 relocation fields. A zero score is only a candidate until
linked-image comparison passes. instructions.json records every original
baseline difference, including target/draft disassembly. results.json records
the probes, including compiler errors; errors are not counted as successful
tests. The recorded sweeps contain 759 rows (including repeated baselines), of which
525 produced nonempty measurable code. No compiler flag changes, inline asm,
register bindings, #line,
padding objects or binary rewriting were retained.

Current-TU reconciliation was necessary before measuring three legacy drafts:
BF720 has a later signed-input prototype; B695C's palette symbol is now a
512-byte-row array; C4E38's output globals are pointers, not integers, and its
audio return declaration conflicts with the current TU. C5064's count global
already has an s8 declaration; its draft's unsigned reads need explicit u8
casts. These were handled in probe copies. The integrated C5064 uses those
casts and leaves the existing declaration and other functions unchanged.

Source-order diagnostics moved the target to the TU end and, separately,
replaced surrounding C bodies with declarations. Every successfully compiled
such probe retained the baseline score. The two 80017378 variants failed on
legacy implicit/declaration conflicts, so no source-order conclusion is
claimed for that function. Array extent probes used 1/2/256 elements; they
are compiler diagnostics, not proposed bounds for the actual assets. GCC-style
alignment attributes are rejected by IDO here; those entries provide no
alignment evidence. Event unions with real u64/f64 members provided valid
alignment diagnostics for F6F4.

Static-function probes did not yield an ELF body measurable by this reader
(the named symbol has size zero or is absent, also with static conversion).
Their reported zero-byte outputs are **invalid measurements**, not eliminated
function or mismatch claims. Static storage for the family counter was tested
separately with an externally visible function and did produce measurable code.
No static-linkage change was retained.

## Per-function findings

Offsets are relative to each function. UNCHANGED counts describe the retained
incoming drafts, not the production GLOBAL_ASM bodies.

| Function | Result | Precise difference and experiments |
|---|---|---|
| func_801BF720 | UNCHANGED, 2, 104 B | +1C target loads space (32) into v1; draft uses v0. +64 target moves v1 to v0 in the return delay slot; draft has nop. Tested TU order/context, result and return widths, shared-label return, case assignments with break, and explicit default case. None improves the two words. No callee/global ABI to alter in this leaf. |
| func_801BF914 | UNCHANGED, 2, 116 B | +68 default 27 goes into v1 versus v0; +70 return move versus nop. Same context, width and switch/return experiments as BF720; unchanged. Narrow return types introduce additional sign/zero extension. |
| func_801C4E38 | UNCHANGED, 2, 556 B | +88 sw v0 and +B8 lw v0 use target sp+1C versus draft sp+18. Pointer table/output declarations reconciled; tested unprototyped callees, explicit selector widths, unused third parameters, table extents and surrounding function context. No valid improvement. |
| func_801B6528 | UNCHANGED, 3, 596 B | +178 target reloads card into a2 from sp+24; draft uses a0. +1A0/+1E8 dependent index loads consequently use a2 versus a0. Tested TU context, symbol extents, and explicitly moving the post-guTranslate card view into arg2, arg3 or a fresh typed local. No improvement; command bytes already match. |
| func_801B695C | UNCHANGED, 4, 268 B | +00/+100 frame allocation/free is target 28 versus draft 30; +08/+5C arg0 home/store follows that frame, target sp+28 versus sp+30. All actual local spill slots already agree. Tested memcpy absent/non-prototype/typed declarations and void/int/pointer/u64 returns, size widths, unused third parameters, asset qualifiers, palette view reconciliation and TU context. Valid copy-prototype changes retain four differences; extra parameters worsen code. |
| func_801C5064 | MATCHED, 4→0, 404 B | +B0 zero belongs in f22, not f24; +BC depth belongs in f24, not f22; +E8 mfc1 a3 consumes zero; +114 stack argument consumes depth. The external mutable-depth declaration gave the wrong allocation. Literal -1950.0f fixes all four; literal 0.67f also preserves zero and emits the original first constant. Integrated both literals. Named zero, depth volatility and declaration reordering do not solve it. |
| func_801C7998 | UNCHANGED, 6, 256 B | +08..+1C: draft sign-extends masked low word into t8, homes arguments later, and stores t8 as the high word; target homes a0/a1 first, clears v1, stores low t9, stores zero high, then clears t8. Tested explicit u16/u32/u64 widening, unsigned mask suffixes and typed mask locals, plus TU context. Keeping all high-button cases gives no improvement; no 8-bit truncation retained. |
| func_801C6A80 | UNCHANGED, 8, 292 B | +44..+64: target loads byte flag directly through v0 and stores the increment through symbolic at. Draft retains its address in v1, shifting flag load, FF store and branch scheduling. Tested defined versus extern byte flag, signedness/width diagnostics, assignment/++/conditional updates, unprototyped audio calls and TU context. None improves eight. Wider flag candidates are not equivalent and were rejected. |
| func_801B2010 | UNCHANGED, 14, 420 B | Counter D_801D309C; common family-A differences below. Independently recompiled with complete owning TU. Representative received static/local/defined/volatile storage and lerp declaration experiments. |
| func_801B21B4 | UNCHANGED, 14, 420 B | Counter D_801D30A0; same 14 offsets and allocation issue. Independent full-TU baseline, source-context and symbol-extent probes. |
| func_801B2358 | UNCHANGED, 14, 420 B | Counter D_801D30A4; same 14 offsets. Independent full-TU baseline, source-context and symbol-extent probes. |
| func_801B24FC | UNCHANGED, 14, 420 B | Counter D_801D30A8; same 14 offsets. Independent full-TU baseline, source-context and symbol-extent probes. |
| func_801B26A0 | UNCHANGED, 14, 420 B | Counter D_801D30AC; same 14 offsets. Independent full-TU baseline, source-context and symbol-extent probes. |
| func_801B2844 | UNCHANGED, 14, 420 B | Counter D_801D30B0; same 14 offsets. Independent full-TU baseline, source-context and symbol-extent probes. |
| func_801B29E8 | UNCHANGED, 14, 420 B | Counter D_801D30B4; same 14 offsets. Independent full-TU baseline, source-context and symbol-extent probes; preserves its distinct global start value. |
| func_8002AA98 | MATCHED, 2→0, 84 B | +2C target mflo a2 versus v0; +30 sra t9 consumes a2 versus v0. Callee return/prototype and product signedness changes do not solve it. Reusing incoming volume for the full product and arithmetic shift, then assigning a named s16 narrowed local, solves it with the original one-argument signature. |
| func_8002AAEC | MATCHED, 2→0, 84 B | Same +2C/+30 issue, same solution independently verified. The sequence-player pointer remains D_800669C4, versus C0 in AA98. |
| func_8002F6F4 | UNCHANGED, 2, 516 B | +68 lw s4 and +160 sw s4: target step slot sp+64 versus draft sp+74. Tested callee non-prototypes, event union alignment/size, timing aggregate layouts and step widths/initialization. Valid aligned unions retain two; timing structs reach the target step slot but disturb repeat/time slots (best seven differences). Initializing step changes 71 words. |
| func_80017378 | UNCHANGED, 8, 1752 B | +590/+598 endpoint/base addiu order differs. +59C..+5B0 target increments rotation/model pointers before four stores through negative offsets; draft stores first, then increments. Tested declared global array extents, grouped rotation clear, reversed model/rotation order, and explicit common increments before stores. No improvement. Earlier T-064 already tested ordinary pointer/for/goto forms. |

### Family A: counter and lerp

All seven differ at +34,+38,+3C,+44,+48,+4C,+60,+64,+68,+6C,+70,+74,+78,+80.
Target loads the signed counter directly into a2, computes `slti v0,a2,1`,
uses ordinary beqz, increments a2 in the delay slot, and stores through
symbolic at on each branch. Draft retains &counter in v1, loads into v0,
uses bgtzl, increments in both branch paths, and moves the argument to a2
at the call. Code from +84 onward already agrees under relocation masks.

The target has a real jal to func_801B19F0, not an inlined expression and
not a call to earlier func_801AFA80. Both helpers' matching C is float lerp;
T-025/T-077 already establish their identical implementations. Relocation
masking alone would incorrectly allow the earlier helper, so that is not a
matching candidate. An unprototyped float helper promotes float arguments
to doubles and does not recover the target ABI. Word signed/unsigned count
prototypes preserve the baseline; narrower types worsen it.

Representative tests combined extern/defined/file-static/volatile counters
with old-value predicates, common postfix increment, increment-before-call
and branch-local stores; a function-static counter was also measured.
No improvement; changing storage to emit new BSS is diagnostic only. A
static inline helper at O2 cannot explain the observed jal without retaining
an actual helper body, and no new helper is justified. SDK display-list
macros expand to the already-matching command stores; they do not explain
the earlier counter prefix. No helper, global or another TU was changed. A declaration confined to another
TU cannot affect this O2 compile: there is no inter-TU optimization or shared
precompiled declaration state in the Makefile. Only declarations visible in
the caller TU can change its ABI/code generation.

### Additional diagnostic limits

A two-parameter volume probe also reached zero by assigning the extra
parameter, but it was not retained: existing callers use one argument.
The final solution needs no signature/caller changes. Invalid generated
variants (declaration-after-statement, conflicting prototypes, unsupported
alignment attributes) remain explicit errors in results.json and provide
no evidence. The final C was tested independently in the linked build.

F6F4 has an existing uninitialized step path: the target loads sp+64 before
the first allocation; if that allocation fails, it accumulates that value.
The draft likewise leaves step uninitialized. This is not solved by a spill
match, and no new undefined behavior was introduced or promoted here.

Probe scripts use /tmp/kig-t096 and temporary compiler directories. They
expect the incoming drafts/source version, before these three promotions.
Initial baseline.json had two unreconciled declaration errors; delivered
instructions.json uses the corrected complete-TU baselines. Some final
static-only probes overlapped clean's removal of generated asm and failed;
those errors were excluded. No successful result depends on that overlap.

## Final verification

`make clean && make extract && make -j6 all && make progress` passed
(exit 0). Parallel jobs affect build scheduling only. The ROM and all three
executable images are byte-identical:

- ROM: ba52e91b44450c548467044b26951353dc491e04
- main: 81736d32e8cda8f399b319a49250dff972b81af8
- ovl_7DF8: ea830aae50ff1422da60d4b7fdbfc29f03b1be39
- ovl_7E00: 2b01138a290212b9d886981e1196f7b6fb45ecdb

`git diff --check` passed. Generated functions.csv/progress.html were restored
after recording this table. status.csv is untouched for the lead. No probe
processes remain. No commits. Matched game bytes increase 58,396→58,968
(+572), T4 279→282.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 58,968 (20.34%) | 58,968 (20.34%) | 0 | 227 | 0 | 282 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 29,028 (20.16%) | 29,028 (20.16%) | 0 | 96 | 0 | 141 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 21,472 (15.62%) | 21,472 (15.62%) | 0 | 131 | 0 | 120 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
