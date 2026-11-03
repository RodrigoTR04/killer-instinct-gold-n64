# T-136 working notes

Baseline: extraction, build and progress passed; ROM and all three images byte-identical. Total 82,572 / 289,876 eligible bytes (28.49%). Full screen: /tmp/terra-1-screen.md. The FU-16 main candidates in range are already T4.

Near misses selected by payoff: func_80017378 (1,752 B, 6 differing words, full TU) and func_8001BDE0 (316 B, 8 words, full TU). Together they would satisfy the 2,030 B requirement. The former differs only in scheduling the model and rotation pointer increments against four stores; the latter differs in allocation of threshold and scale to floating point registers. Historical reports document extensive attempts.

New experiments: 17378 pointer update placement, statement line grouping, struct views, pointer types, interleaving independent stores, and while/do/for control; 1BDE0 argument/local arrangements, comparison forms and loop structure; 1373C distance locals and impulse types. No improvement from these initial batches. Scratch variants and scripts reside in /tmp/t136-*. No source promotion or byte gain claimed.

The 14D5C declaration-order search (seed 136, 180 s, 1,140 compiles) improved 136 to 135 differing words at 1,780 bytes in prefix context. Independently remeasured after the search. Saved the candidate to T-033; the full TU still has conflicting legacy declarations, so this is not a match.

`func_80014D5C-full-tu.c` reconciles the three legacy function declarations with later declarations already in the owning TU and casts the integer-stored pointer arguments consistently with existing code. It compiles in the full TU at 139 words / 1,780 B. The lower 135-word prefix candidate remains the T-033 draft; this alternative removes its full-TU declaration blocker, but is not an improvement in word count or a promotion.

`func_80015450` improves 51 to 49 differing words (324 bytes, prefix) by joining the object initialization and loop opening; independently measured and saved in T-033. Loop/index scheduling remains.

The full-TU 14D5C alternative has a 0x20 stack frame matching the original, versus the prior report's 0x50 prefix result. Its differences concentrate in the early branch/setup region; one extra instruction shifts a substantial portion of the code before it re-aligns. Subsequent pointer update variants for 17378 and a 300-second permuter search of 1BDE0 did not improve their six- and eight-word baselines.

An explicit byte `kind` snapshot improves 15450 a further 49 to 48 words in prefix context; saved to T-033.

Further triage: lower-threshold clone screen (0.70) found no additional main T2 cluster. The 1373C distance/local ownership variants did not beat 28 words. Const-qualified 1BDE0 constants and alternate third-argument ABI experiments were worse than the original (the latter were diagnostic only). 15450 loop and register-lifetime variants yielded the saved 48-word `kind` result. The 14D5C timer-pointer and early-branch sweeps did not improve the 139-word full-TU alternative; full-TU declorder also remained at 139.

15450 byte cursor / current object view improves 48 to 43 words, 324 bytes in prefix context. Independently remeasured and saved; iteration still spans the same 0x100-byte records and reads the same fields.

The exhaustive 2,048 boundary layouts for the current 17378 loop did not improve six words. Rewriting 121C8 to reload the overlay address and varying its mode/global ordering did not improve 47 words. 1BDE0's for/do-loop conditions and 15450's cached index and alternate cursor types also did not beat the saved drafts.

A focused 600-second permuter run limited to the 17378 loop completed 4,831 iterations and retained six words / 1,752 B. A fresh 15450 reconstruction using a rotation pointer across the wrap and pitch update measured 48 words; the current byte-cursor draft remains better at 43.

A snapshot of the packed input word improves 121C8 from 47 to 46 differing words / 304 B in full TU; independently remeasured and saved in T-033. The incoming value is read from ordinary nonvolatile RAM with no intervening calls or writes.

A final clean baseline (`make clean && make extract && make -j8 && make progress`) passes: ROM byte-identical, all three images OK, and total remains 82,572 / 289,876 B (28.49%). No new T4 bytes. A fresh 1BDE0 reconstruction using separate forward/reverse cursors, constant and local forms, measured no better than the original eight-word draft.
