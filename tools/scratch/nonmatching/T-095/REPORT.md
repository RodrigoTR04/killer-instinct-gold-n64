# T-095 — sol-B31

**2 MATCHED (696 B), 7 IMPROVED, 7 UNCHANGED. No commits.**

Read TRACKING, latest WORKLOG, Makefile, tools/permuter/README, the T-092 ranked screen, latest relevant per-function report entries, and T-056/T-061/T-067/T-082. Missing ROM/tool prerequisites were symlinked from the authorized shared checkout. No ROM was copied into git.

Production IDO 5.3 -O2 -mips2 through asm-processor throughout. First checked the asm differences, declarations/argument widths, relevant callee ABIs, field accesses and loop shapes, then ordinary multiline layouts. Additional structural and cleanup probes continued while searches ran. Counts below are independently measured relocation-masked differing instruction words, including missing/extra words; they are not permuter penalties. Improved drafts are diagnostic, not behavior certification.

Each of the sixteen functions received a local decomp-permuter search with -j5, --stack-diffs --stop-on-zero --best-only --better-only. At most eight searches ran concurrently. Nonmatching runs were interrupted after about 900 seconds; the two independently proven matches stopped early. Exact durations/exit codes and raw penalties are in results.json. Timeout/interrupt exit 137 is a bounded search termination, not a build failure. No subagents/network workers. Generated search trees and probe objects remain outside the repo under /tmp/t095.

| Function | Result | Words old → retained | Bytes | Work and what remains |
|---|---|---:|---:|---|
| func_801B17BC | MATCHED | 20 → 0 | 256 | MATCHED, 256 B. Unsigned byte color parameters, s32 counter, named image pointer, chained three-global reset, and one documented setup-line join. Clean complete-TU and linked checks are exact; draft deleted. |
| func_801BD270 | IMPROVED | 21 → 11 | 396 | Initialize the u64 result before shifting and combine the shifted axis with its first addition. Remaining: axis/button spill widths/slots and carry-chain register/scheduling differences. |
| func_801C8AE0 | UNCHANGED | 21 → 21 | 324 | Queue array view, accumulator widths, separate packed-result locals and layouts did not improve the retained code. Remaining: loop/tail temporary numbering. Lower raw outputs use redundant masks and were not retained; legacy queue declaration still requires reconciliation. |
| func_8001E0B4 | IMPROVED | 24 → 11 | 648 | Inline the indexed record address, name the high-bit predicate, and reorder live declarations. Removed empty statement and unused pointer. Remaining: setup and flag/branch scheduling (11 words); typed load widths checked against asm. |
| func_801B446C | UNCHANGED | 28 → 28 | 292 | Checked cached flag/bit widths, direct flag loads, array views and layouts. Remaining: flag base retention and dependent scheduling. Rejected a lower score that redirects the completion flag store into the queue cursor. |
| func_801C0800 | IMPROVED | 29 → 21 | 248 | Use a scoped command pointer for the final display-list command and commute the matrix-address sum. Removed the raw do-once wrapper. Remaining: color packing temporary allocation and final command/index scheduling. |
| func_8002B034 | MATCHED | 30 → 0 | 440 | MATCHED, 440 B. Multiline stores and a nested RSP-task view retain the original frame/slots; the RSP pointer serves both yield fields. Preserve the existing integer-address second argument, use the actual func_80039C08 SDK ABI and boot_audio_queue name. Complete TU and linked checks are exact; draft deleted. |
| func_8002A4F0 | UNCHANGED | 31 → 31 | 920 | Checked sequence-loop shape, count/length widths and stack-local layout. Remaining: settings/size spill offsets and sequence-loop induction. Lower weighted candidates worsened word count or required a do-once wrapper; baseline retained. |
| func_800269AC | IMPROVED | 33 → 25 | 236 | Separate named environment-command cursor preserves all three original command positions. Remaining: global/command temporary registers and call setup. Rejected another lower weighted output that reorders display-list commands. |
| func_801B0520 | IMPROVED | 36 → 22 | 328 | Named frame-state pointer used for the second position test and transform input. Remaining: initial frame result register, color temporaries, global base reuse and scheduling. Simplified-shift candidates were not retained. |
| func_801B1210 | IMPROVED | 38 → 29 | 284 | Separate named mode-command cursor; removed the raw duplicate pointer assignment and retained the direct stores. Remaining: alpha/global temporary allocation and command/call scheduling. |
| func_800268C0 | IMPROVED | 40 → 28 | 236 | Snapshot the four sprite dimensions before output stores; group the packed source offset and name its high byte. Remaining: offset-address and copy temporary allocation/scheduling. Full-TU score retains target size. |
| func_801BBB60 | UNCHANGED | 40 → 40 | 292 | Checked palette cursor initialization, fill/store loop shape and layouts. Remaining: palette base/register allocation and unrolled stores. Rejected a raw candidate that advances the palette before the zero store. |
| func_801BE660 | UNCHANGED | 41 → 41 | 300 | Checked glyph/index views, const versus literal spacing, x/width lifetimes, division forms and layouts. Remaining: text/float allocation, spacing-constant load placement and division shape. Lower weighted outputs worsen actual words/size. |
| func_800121C8 | UNCHANGED | 47 → 47 | 304 | Checked global array views, mode width/predicate, overlay-address lifetime and layouts. Remaining: global load/store allocation, stack frame and overlay-call address scheduling. Empty/do-once wrappers are removed before considering improvements. |
| func_80024028 | UNCHANGED | 49 → 49 | 284 | Checked color argument widths, signed/unsigned packing, OR/add forms, staged values and multiline layouts. Remaining: packed-color expression temporary registers and command scheduling; no cleaned improvement. |

All seven improved drafts compile and reproduce their counts in their complete owning TUs. The unchanged C8AE0 and A4F0 baselines retain the screen’s declaration/prefix fallback contexts; they are not claimed integrated. Raw mutations were reviewed for semantics and cleaned before retention.

Integrated only func_8002B034 in src/main/main_1B230.c and func_801B17BC in src/ovl_7DF8/ovl_7DF8_3F60.c, plus their needed declarations. No inline asm, #line, register keyword, padding locals, binary rewriting or compiler changes. No boot, ovl_7E00, YAML, Makefile, symbol-address, status.csv, TRACKING or WORKLOG edits. Generated progress documents were restored after capturing the table.

## Final validation

`make clean && make extract && make all && make progress` passed (exit 0) on the final production source. ROM and all executable images are byte-identical:

- ROM: ba52e91b44450c548467044b26951353dc491e04
- main: 81736d32e8cda8f399b319a49250dff972b81af8
- ovl_7DF8: ea830aae50ff1422da60d4b7fdbfc29f03b1be39
- ovl_7E00: 2b01138a290212b9d886981e1196f7b6fb45ecdb

`git diff --check` passed. No task search/probe processes remain. The deleted matched drafts were T-024/func_8002B034.c and T-025/func_801B17BC.c. Changes are left uncommitted for lead review.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 59,092 (20.39%) | 59,092 (20.39%) | 0 | 228 | 0 | 281 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 29,300 (20.35%) | 29,300 (20.35%) | 0 | 97 | 0 | 140 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 21,324 (15.52%) | 21,324 (15.52%) | 0 | 131 | 0 | 120 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
