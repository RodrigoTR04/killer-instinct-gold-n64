# T-105 — sol-C39

**0 MATCHED, 8 IMPROVED drafts, 8 UNCHANGED. No commits.**

Read TRACKING, latest WORKLOG, Makefile, permuter README, T-099 screen, each target's latest report entries, and T-096/T-097/T-100/T-102/T-056/T-067 before probing. Missing baserom.us.z64, ROMs, .venv and tools/ext were symlinked from the authorized shared checkout. No ROM was copied or added to git.

IDO 5.3 -O2 -mips2 through asm-processor throughout. Words count differing aligned instructions, masking actual ELF relocation fields and including size differences. These are independently measured words, not permuter penalties. Improved drafts remain nonmatching and do not certify behavior. All eight retained improvements compile in their full owning TUs; unchanged A4F0 still requires prefix context.

| Function | Result, old → new words | Compiled/original B | Retained change / remaining cause |
|---|---|---:|---|
| func_8002A4F0 | UNCHANGED 31 | 920/920 | Synth/configuration stack offsets and sequence-loop induction/register allocation remain. Multiline probes did not improve the clean baseline. |
| func_801C3758 | IMPROVED 36 → 32 | 572/564 | Corrected frame-variable roles and reconciled existing CloudCmd/T030Cloud and vertex-pointer declarations. Frame store and UV index now use the intended values/registers. Extra arg0 home/reloads and command-tail allocation remain; +00..+1C and +1DC onward. |
| func_801CB998 | IMPROVED 36 → 2 | 148/148 | Actual callee is text plus packed u64, with a2/a3 holding the high/low words; the old four-word call unnecessarily preserved a1. Direct u64 globals and one flags local recover the size and all other instructions. Only +48/+4C spill/reload flags at sp+18 instead of sp+1C. |
| func_801ADA04 | IMPROVED 39 → 18 | 208/208 | Explicit pending-mode pointer prevents address retention; separate pending store and array index restore the missing instruction. Next-mode, VI-table and final-reset temporary registers and scheduling remain. |
| func_801BBB60 | UNCHANGED 40 | 292/292 | Palette base and byte-fill constant allocation, unrolled zero-store ordering remain. Normalized/cleaned permuter form is worse (41). |
| func_801BE660 | UNCHANGED 41 | 300/300 | Text cursor versus incoming x home, FP register allocation, spacing load and division schedule remain. Valid cached-spacing candidate worsens to 71 words/292 B. |
| func_801B43A8 | IMPROVED 42 → 34 | 196/196 | Advance group to the completed entry cursor rather than separately adding three; this removes the extra instruction. Saved-register order, memcpy base reuse, random/index temporary numbering remain. |
| func_801C47E0 | IMPROVED 45 → 11 | 260/260 | Reuse offset through page mapping, payload offset and aligned return. Correct 0x38 frame, spill slots and instruction count. Remaining +2C/+40/+60/+6C/+70/+78/+A8/+B4/+D0/+D8/+F0: temporary registers and commutative addu operands. |
| func_800121C8 | UNCHANGED 47 | 304/304 | Global load/store allocation, 0x28 frame versus target 0x18 and overlay-address reuse remain. No cleaned permuter improvement. |
| func_801C48E4 | IMPROVED 48 → 45 | 188/196 | Normalize incoming coordinates explicitly before resource stores. Target still homes/masks/moves them earlier; current code has two fewer instructions and different resource-address temporaries. Typed field, width and K&R probes do not fix it. |
| func_80024028 | UNCHANGED 49 | 284/284 | Packed-color temporary allocation and command scheduling remain. Rejected a raw candidate that truncates 0xA00 into an unsigned char. |
| func_801BBC84 | UNCHANGED 112 | 508/516 | Fire-loop saved registers, initial threshold reload and random/modulo scheduling remain; two missing instructions. Explicit random-decay sequencing retains baseline. |
| func_801B3B84 | IMPROVED 114 → 113 | 552/556 | Reuse the old frame and postfix increment in the branch predicate. Counter/color/conversion registers, alpha spill and one missing instruction remain. Existing draft's uninitialized alpha path is preserved, not promoted into production. |
| func_801B677C | UNCHANGED 117 | 492/480 | Initial divisor/index/remaining registers and division-check scheduling remain. Negative-first multiplication removes one word but does not improve count. Unsigned-remainder score gain rejected because it changes signed comparison/conversion behavior for negative remaining counts. |
| func_80016078 | UNCHANGED 119 | 448/480 | Display-command cursor/float conversion scheduling and argument homes remain; eight missing instructions. Distinct cursor views, callback widths and K&R do not improve the retained baseline. |
| func_801C11F0 | IMPROVED 126 → 113 | 584/580 | Correct typed renderer ABI (text pointer, float x, byte colors) and a float scalar replace integer text/x arguments and union bits. Phase/shade/divisor registers, buffer/frame layout and call setup remain; now one instruction too large. |

## Method and limits

Inspected original instruction sequences and freshly measured all sixteen drafts, then tested concrete call ABI, signedness, pointer/record, loop, offset-reuse and local-lifetime hypotheses before multiline layouts. No compiler flag changes, inline asm, #line, register keyword, synthetic padding or output rewriting.

Some early probe helpers dropped new typedefs in declaration-fallback context; those compiler errors were discarded. A clean build was initially started while layout probes still referenced generated asm; affected missing-file probes were rerun after extraction. Invalid/empty-symbol/compiler-error outputs are never scored as matches. The final independent screen rechecks every retained draft.

final.json records all sixteen independent final measurements; instructions/ contains original baseline instruction differences; experiments.json is a compact probe summary. Helpers expect incoming-source context; generated working sources stay in /tmp.

No GLOBAL_ASM was replaced and no function_owner hints needed removal. Production source, boot, ovl_7E00, YAML, Makefile, status.csv, TRACKING and WORKLOG are untouched. Regenerated linker undefined-symbol changes are retained if any. Only the eight listed drafts and this task's small diagnostic files are changed.

Permuter searches used -j5, --stack-diffs, --stop-on-zero, --best-only and --better-only, with a 900-second bound per search. The five incoming equal-size drafts and three newly equal-size drafts completed their bounds; exit 137 denotes bounded termination, not a build failure. The corrected video-mode draft also completed its 900-second bound. No search output was promoted.

Raw search mutations were reviewed before retention. Rejected examples include an uninitialized shuffle cursor, a truncated display-list constant, duplicate stores, empty conditions and do-once wrappers. Lower weighted scores do not establish fewer differing words or equivalence. Generated search trees, compiler products and bulky logs stay under /tmp/kig-t105.

No task search/probe process remains. `git diff --check` passed. Generated progress documents have no net changes. Changes are left uncommitted for lead review.

## Final validation

`make clean && make extract && make all && make progress` passed (exit 0). ROM and all executable images are byte-identical:

- ROM: ba52e91b44450c548467044b26951353dc491e04
- main: 81736d32e8cda8f399b319a49250dff972b81af8
- ovl_7DF8: ea830aae50ff1422da60d4b7fdbfc29f03b1be39
- ovl_7E00: 2b01138a290212b9d886981e1196f7b6fb45ecdb

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 66,396 (22.90%) | 66,396 (22.90%) | 0 | 205 | 0 | 304 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 30,556 (21.22%) | 30,556 (21.22%) | 0 | 91 | 0 | 146 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 27,372 (19.92%) | 27,372 (19.92%) | 0 | 114 | 0 | 137 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
