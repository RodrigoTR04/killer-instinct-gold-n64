# T-123 — sol-C45: near-miss sweep

## Result

**668 bytes promoted (0.2304% of 289,876 B), against the 2,030-byte target. Target not achieved; shortfall 1,362 B.** `func_801B0A40` is integrated C and its draft is deleted. `func_801B5534` improves from five to two differing words and remains a draft. No commits, ROM copies, compiler flag changes, inline assembly, artificial branches, register bindings, or padding were introduced. TRACKING, WORKLOG and status.csv were not edited.

Measurements are positional differing instruction words, including length differences and masking only actual ELF relocation fields. IDO 5.3 `-O2 -mips2` and asm-processor were used. Initial instruction-level diagnoses were regenerated in `/tmp/t123-diag/results.json`; bulky search sources and logs remain in `/tmp/t123-*`.

| Function | Bytes | Before words | After words | Result / remaining difference |
|---|---:|---:|---:|---|
| func_801B0A40 | 668 | 0 text, linked failure | 0 linked | MATCHED: neighboring assembly function owns the four extern constants |
| func_80017378 | 1,752 | 6 | 6 | Unchanged: +59C..+5B0 increments versus four model stores |
| func_801B6528 | 596 | 3 | 3 | Unchanged: card reload at +178 uses a0 versus a2; dependent loads at +1A0/+1E8 |
| func_801C4E38 | 556 | 2 | 2 | Unchanged: +88/+B8 spill/reload at sp+18 versus sp+1C |
| func_801CC908 | 424 | 2 | 2 | Unchanged: +C/+19C frame is 40 versus 30; existing spill offsets otherwise agree |
| func_8002F45C | 404 | 4 | 4 | Unchanged: decayTime uses a1 versus v1; keyMax uses v1 versus t3 |
| func_801C224C | 372 | 6 | 6 | Unchanged: incoming selector uses s0 versus a2; save/move scheduling at entry |
| func_801B695C | 268 | 4 | 4 | Unchanged: frame 30 versus 28, with corresponding incoming argument home |
| func_800269AC | 236 | 2 | 2 | Unchanged: primitive color/opcode stores reversed at +88/+8C |
| func_801C85C0 | 168 | 4 | 4 | Unchanged: byte-normalized next selector scheduled after initial zero stores |
| func_801B5534 | 168 | 5 | 2 | IMPROVED: u8 input, s32 callee input; remaining scaled-index spill at sp+18 versus sp+1C |
| func_801C7F90 | 116 | 3 | 3 | Unchanged: +1C..+24 cursor setup versus initial byte clear |
| func_801BF914 | 116 | 2 | 2 | Unchanged: default in v0 versus v1, missing return move |
| func_801BF720 | 104 | 2 | 2 | Unchanged: default in v0 versus v1, missing return move |

## Constant ownership

`func_801B0A40` already had exact text with extern references. Added explicit f64/f32 `force_migration:True function_owner:func_801B0CDC` hints for D_802928E8, D_802928F0, D_802928F8 and D_80292900. Splat now retains these definitions in the neighboring assembly function's pool, in their original order and original addresses. No YAML change or C named-constant definition is needed. The converted function owns no rodata pool or owner hints; its constants remain assembly-owned externs, as explicitly suggested in the task. Literal conversion's stack-layout problem is therefore avoided. The initial complete build verified the whole overlay and ROM byte-for-byte, not merely relocation-masked text.

## Diagnosis and searches

Read TRACKING conventions and T-123 row, recent WORKLOG, overview, permuter README, T-121 report and fresh screen, and clones.md. There is no matched clone template for this candidate set in the recorded clone clusters. Missing `.venv`, `tools/ext` and baserom were symlinked from the authorized shared checkout.

Started with 0A40, then 17378. For 17378, examined original assembly and imported object disassembly: everything outside the final pointer-loop scheduling agrees. Tested 1,024 source boundary combinations; increment positions and order; do/while/for/goto loop forms; typed scalar cursors; typed model records and pointer arrays; grouped zero stores; and meaningful model/rotation access forms. No improvement below six words. The original three-entry rotation endpoint is preserved; no counter/trip-count change was accepted. A 300-second permuter run with `--stack-diffs --stop-on-zero --best-only --better-only -j4` produced no improvement when independently measured in the full TU.

Then worked downward by size, with bounded independent compiler probes running concurrently. 6528 received a 180-second permuter run and typed card-cache/lifetime probes. Permuter weighted-score improvements independently remeasured at 7–9 words, worse than the three-word draft, so were rejected. 4E38 received two-input records and selector-cache placement/type probes in declaration context; no zero. CC908 received dead-copy elimination, actual mask/status/handle records, declaration orders, widths and lexical scopes; no zero. F45C received meaningful decay/keyMax temporaries, signedness, alias and expression/layout variants; no improvement. 224C received a separate selector local, widths, declaration order, casts and boundaries; no improvement.

The small candidates received bank/frame records and widths (695C), next-selector caching before different zero stores (85C0), command access/cursor and store forms (269AC), endpoint/cursor loop forms and initial-clear ordering (7F90), and switch/result widths, cases, returns, breaks and gotos (BF720/BF914). None improved. Across the targeted scripts, 6,812 candidate source files were generated (including invalid/worse variants and diagnostic controls); counts are in `/tmp/t123-search-counts.json`. Tests stayed in /tmp and were not copied into drafts unless independently better.

5534's original assembly reloads the input with `lbu sp+23`, while its draft used a word input. Changing only the input to u8 worsens allocation because the draft incorrectly says the callee also takes u8. The callee's own assembly preserves full a0 in s1 and its draft declares s32. Correcting both recovers the target move and byte reloads, reducing five differences to two. A 180-second stack-aware permuter run and real sample/remainder/index temporary probes did not remove the remaining spill-slot mismatch. The improved, readable draft is retained.

## Validation and final progress

`make clean && make extract && make all && make progress` completed successfully (exit 0). An earlier completed validation also used `make -j8 all`. All three images verify against their original hashes; the rebuilt ROM is byte-identical to the baserom (SHA-1 `ba52e91b44450c548467044b26951353dc491e04`), including unchanged bytes outside the spliced slots. Logs are `/tmp/t123-exact-extract.log`, `/tmp/t123-exact-all.log`, and `/tmp/t123-exact-progress.log`; the earlier parallel-build log is `/tmp/t123-final.log`. `git diff --check` passes. Splat reports pre-existing user-symbol segment diagnostics during extraction, but extraction and the complete build succeed. An earlier incremental verification overlapped the start of clean extraction and failed on removed assets; it is superseded by this completed clean sequence. Generated functions.csv and progress.html are restored for the lead to regenerate.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 76,276 (26.31%) | 76,276 (26.31%) | 0 | 186 | 0 | 323 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 33,776 (23.46%) | 33,776 (23.46%) | 0 | 87 | 0 | 150 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 34,032 (24.76%) | 34,032 (24.76%) | 0 | 99 | 0 | 152 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
