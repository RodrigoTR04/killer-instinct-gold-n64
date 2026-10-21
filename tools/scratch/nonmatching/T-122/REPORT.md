# T-122 — sol-B39: 176–219-word screen band

**0 MATCHED; 9 IMPROVED drafts; 7 UNCHANGED. No commits.**

All sixteen incoming drafts were measured with IDO 5.3 `-O2 -mips2` through asm-processor. Words count differing corresponding instructions plus missing/extra instructions, masking only ELF relocation fields. This is a positional diagnostic, not edit distance. Only a zero reconciled in its complete TU and linked byte-identically could be promoted; none was found. Improved drafts replace the existing drafts in place. No production C, status.csv, Makefile, YAML, boot or ovl_7E00 source changed.

## Per-function results

| Function | Result, differing words old → new | Compiled bytes old → new / original | Context | Structural cause / remaining issue |
|---|---|---:|---|---|
| func_801C1434 | IMPROVED 176 → 132 | 736 → 720 / 720 | full | Cache the player selector across callbacks, reload flags after the first draw, and use promoted full-width fourth argument for func_801C11F0. Remaining input homing, score-word temporaries and branch scheduling. |
| func_800131A4 | IMPROVED 178 → 41 | 676 → 712 / 712 | full | Signed 16-bit part/counter and callback return, unsigned count/order loads, explicit shift/subtract seven-byte stride, symbolic physical display-list address. Remaining store order and saved-register allocation. |
| func_8002E150 | UNCHANGED 179 | 836 → 836 / 844 | full | Address-taken input experiment removes the union copy/save but still differs in frame size and FP polynomial scheduling. Literal/layout probes did not improve retained draft. Existing function_owner reservation remains untouched because this function is not converted. |
| func_800297A4 | UNCHANGED 180 | 780 → 780 / 780 | declarations | Burst layout and unsigned RNG conversions retained. Equal size; free-slot traversal, loop induction and integer/FP allocation remain. Lower permuter scores must preserve all three geometry branches and unsigned conversions. |
| func_8001808C | UNCHANGED 181 | 796 → 796 / 808 | declarations | Stage setup has the expected stores/calls. Literal and layout experiments do not recover three missing words, callback/store scheduling and FP temporaries. |
| func_801BBE88 | IMPROVED 184 → 150 | 804 → 808 / 808 | full | One typed command cursor and cached height-global address recover reload/address materialization and exact size. Remaining command-store scheduling and temporary allocation. |
| func_800253D0 | IMPROVED 186 → 183 | 1044 → 1044 / 1068 | full | Confirmed byte HUD inputs and actor stride. Word/byte union and pointer-global diagnostics do not solve six missing words. Retained token-preserving source layout improvement; call/store scheduling remains. |
| func_801B2B8C | IMPROVED 189 → 178 | 884 → 868 / 872 | prefix | Reuse one command cursor removes four excess instructions. Still one word short; matrix/alpha and command scheduling remain. Original reads a local stack byte before its else-branch alpha reset; no speculative initialization retained. |
| func_801BD640 | UNCHANGED 191 | 1068 → 1068 / 1068 | full | Existing glyph/Gfx widths and float matrix prototypes retained. Equal size; matrix base, saved registers, packed color and glyph-loop lifetimes remain. Aligned matrix and layout/search diagnostics did not establish a match. |
| func_800193DC | UNCHANGED 192 | 788 → 788 / 808 | declarations | Stage and byte setup matches high-level structure; five missing words and FP/store scheduling remain. Literal and token-layout experiments did not improve the retained draft. |
| func_801B01EC | IMPROVED 193 → 191 | 828 → 828 / 820 | full | Aligned matrix and shared-zero diagnostics do not fix two excess words. Token-preserving multiline layout improves scheduling; FP/global/call lifetimes remain. |
| func_80017D6C | UNCHANGED 194 | 824 → 824 / 800 | full | Confirmed full-width stage indices, cached transform pointers and indexed copy tail. Index widths, literals and pointer-representation/layout probes do not remove six extra words. |
| func_80018AE0 | UNCHANGED 194 | 900 → 900 / 912 | declarations | Stage initialization and callback sequence retained. Literal/layout diagnostics do not fix three missing words and FP/store ordering. |
| func_801B0CDC | IMPROVED 204 → 202 | 1336 → 1336 / 1332 | prefix | Existing sprite ABI and unsigned integer tick/40 division retained. Matrix alignment/shared zero do not remove one excess word. Token-preserving layout improves two words; FP/matrix and command scheduling remain. |
| func_801C3AA0 | IMPROVED 206 → 119 | 908 → 928 / 928 | full | Flat 16-byte vertices, slot*3 calculated after RNG, count computed before remaining capacity, no cached active count across trig/RNG calls, double half-width calculation and final global reload recover exact size. Remaining register/slot differences. |
| func_801C90D4 | IMPROVED 219 → 217 | 1192 → 1192 / 1200 | full | Promoted colors and float fade values retained; widening colors or FP locals changes conversion semantics/code shape. Token-preserving layout improves scheduling; two missing words and stack/color/fade-loop allocation remain. |

## Structural findings

`800131A4`: the original sign-extends both the part and loop counter, uses unsigned count/order loads, and computes the seven-byte table stride with shift/subtract. The callback result is consumed as s16; changing only the local leaves a different extension. These changes reduce the original 676/712-byte draft to exact size with 84 words different. A clean permuter-derived temporary preserves the original float argument while converting callback inputs; the physical display-list reference uses the existing `D_4AC40` symbol. Token-preserving declaration/statement layout then reaches 41 words. Its count/order declarations are reconciled against the TU arrays; the final score is full-TU. Remaining differences are command stores, saved-register assignment and loop expression scheduling.

`801BBE88`: replacing nineteen artificial command aliases with one typed cursor gives 184→163 words. Caching the address of the mutable height global, while continuing to reload its value, gives exact 808-byte size and 150 words. It uses shared `FrontendGfxWords`. No command is removed or packed differently.

`801C3AA0`: the target multiplies a particle slot by three, then shifts by four for the 16-byte vertex stride. The old triangle aggregate encouraged a different multiply. Use the existing TU vertex type and flat array, calculate `slot = index * 3` after RNG, compute count before remaining capacity, and reload the global active count after calls and at the final increment. Use double multiplication for the half-width clamp, as in the original. This recovers 928/928 bytes and improves 206→119 words. It compiles in its complete TU after removing the stale alternate vertex declaration. No rodata ownership change is needed for this nonmatching draft; the angle constant remains the original extern.

`801C1434`: cache the player selector over callbacks, reload flags after the first callback, and use the promoted full-width last argument of `801C11F0`. The target passes `player-1` directly, without the draft’s byte truncation. The retained candidate is 720/720 bytes at 132 words; a narrower-call candidate scores 121 but is 728 bytes and is not retained.

Other probes covered callee widths, aligned 64-byte matrix storage, shared-zero locals, transform pointer/index expressions, HUD word/byte views and literal constants. No changed-width RNG conversion, speculative alpha initialization, fake padding or compiler flag change was retained. `801B2B8C` still has the original draft’s local alpha issue: the original reads sp+0xB7 before resetting alpha in one branch; assigning arg1 or an arbitrary initial value is not supported by the assembly.

`8002E150` remains nonmatching and unconverted, so its function_owner hints and constants were not changed. The address-taken input experiment recovers input homing but changes FP lifetimes/frame size and does not improve the retained score. Promotion would need literal constants and ownership-hint cleanup as requested.

## Searches, evidence and limits

Read TRACKING, latest WORKLOG, overview, Makefile, the four shared headers, permuter README, T-113 screen, T-100/T-102/T-106/T-069 and latest target report entries. Missing prerequisites were symlinked from the authorized shared checkout; no ROM was copied or added to git. No subagents were used.

Five-worker permuter searches used `--stack-diffs --stop-on-zero --best-only --better-only`, bounded at 900 seconds, on the two initially equal-size functions and the structurally equalized drafts. Weighted permuter scores are not the table’s differing-word counts. Layout searches used declaration/statement boundaries only; twelve broad checks used 60-second budgets, with focused 300-second checks on 131A4, 3AA0 and 2B8C. Separate command-store/declaration searches on 131A4 ran eight and four minutes; neither beat the retained 41-word layout. A final five-minute full-TU layout pass checked the reconciled draft and remained 41 words.

Search inputs for 297A4 and 3AA0 needed declaration reconciliation; full-TU/declaration extraction supplied the disposable input after import_fn’s initial conflicting declarations. A malformed 1434 import briefly included other TU GLOBAL_ASM stubs after a temporary-body extraction error; that process tree was terminated, its scores discarded, the draft trimmed to its own function, and the corrected search started separately. Compiler errors never count as matches.

Lower weighted-score outputs were audited. The particle candidate that recomputed its final index after `index++` changes the destination vertex and was rejected. Burst candidates dropped geometry or changed unsigned conversions; they were rejected. A 131 candidate included an empty pointer test; it was rejected. The retained 131 float-copy candidate has that no-op comma removed and meaningful temporary names. No inline asm, #line or register keyword is retained.

All bulky logs, objects, search output and disposable generated C live in `/tmp`; no permuter output directories are deliverables. `probe.py` and `measure.py` reproduce the measurement method. `baseline.json`, `results.json`, `notes.json`, `instructions.json` and `searches.json` record compact evidence. Prefix/declaration rows are explicitly labeled and are not integration claims.

## Final validation

`make clean && make extract && make all && make progress` completed successfully (exit 0). ROM and all executable images are byte-identical:

- ROM: `ba52e91b44450c548467044b26951353dc491e04`
- main: `81736d32e8cda8f399b319a49250dff972b81af8` (239,824 bytes)
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39` (957,392 bytes)
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb` (153,904 bytes)

`git diff --check` passes. Generated progress documents have no net diff. No linker-script changes resulted. No production function is promoted, so matched bytes and tiers are unchanged. No commits.


| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 74,388 (25.66%) | 74,388 (25.66%) | 0 | 189 | 0 | 320 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 33,776 (23.46%) | 33,776 (23.46%) | 0 | 87 | 0 | 150 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 32,144 (23.39%) | 32,144 (23.39%) | 0 | 102 | 0 | 149 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
