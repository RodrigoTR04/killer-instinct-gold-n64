# T-085 — sol-C32

**23 eligible functions attempted: 2 MATCHED (304 bytes), 11 IMPROVED drafts, 10 UNCHANGED.** The requested TUs are not all finished. Five resident stubs were reserved for T-082 and were not touched. No commits.

Read TRACKING, latest WORKLOG, Makefile and T-067/T-056/T-061/T-069/T-046/T-051 reports. Missing baserom.us.z64, ROMs, .venv and tools/ext were symlinked from /home/rodri/Projects/killer-instinct-gold-n64. No ROM was copied or added to git.

## Method and limits

`probe.py` compiles a draft with its owning TU prefix, using production IDO 5.3 -O2 -mips2 flags. Counts compare corresponding instruction words, mask only real ELF relocation fields, and include missing/extra words. They are diagnostics, not behavior validation. Baselines were freshly measured; they can differ from older standalone reports. Promoted functions alone receive linked matching claims.

Reconciled event-player, voice-list, global signedness and decoder pointer declarations in temporary TU copies. Tried argument widths, typed tile arrays, camera-copy loops, global-player reloads, command argument declarations and switch types. Every eligible function received token-preserving multiline layout probes (16 fixed layouts where compilable, then 65 randomized layouts and a final 60-layout pass). Large functions still need substantial reconstruction; this is a bounded attempt, not an exhaustive search. Rejected RGB signed-narrowing changes and an arbitrary larger event payload; the retained initializer uses the TU's established 16-byte event shape. Temporary candidates, objects and logs stay in /tmp.

## Results

| Function | Result | Remaining / evidence |
|---|---|---|
| func_8000FA80 | IMPROVED 2015→2014 | 8148/7436 B. Checked DMA/controller argument declarations and layouts. Main frame loop, task/render/replay structure and register allocation remain far from matching. |
| func_8001178C | UNCHANGED 570 | 2296/2104 B. Controller prototype and switch forms do not improve dispatch/control flow. |
| func_800121C8 | IMPROVED 55→54 | 304/304 B. Mode widths and multiline layouts; load/store and top-byte temporary allocation remain. |
| func_80012390 | IMPROVED 109→101 | 500/476 B. Corrected record size to bytes 4–7, initial cursor to buffer start, and next-block alignment to (cursor+15)&~15, per asm. Remaining loop setup and image-copy allocation. |
| func_8001256C | UNCHANGED 63 | 356/356 B. Checked RGB argument widths and command layouts. Rejected the tiny signed-narrowing diagnostic improvement; full-width command temporaries still differ. |
| func_8001272C | IMPROVED 105→103 | 544/548 B. Projection storage/argument widths and layouts; effect/clamp temporaries and call setup remain. |
| func_8002E4A0 | IMPROVED 115→33 | 480/480 B. Reload global player rather than caching it across calls; link each voice to the preceding 64-byte record; use 16-byte event. Remaining register/address allocation and scheduling. |
| func_8002E724 | UNCHANGED 660 | 2728/2832 B. Reconciled T040Player wrapper with extended event-player view; checked volume-table width, switch and layouts. Large event dispatcher and its jump table remain. |
| func_8002F5F0 | UNCHANGED 50 | 220/212 B. Rebuilt candidate using TU T024Link/T024VoiceLists and an extended voice view. List insertion/owner cleanup branching and scheduling remain. Original draft retained. |
| func_8002F6F4 | IMPROVED 30→18 | 516/516 B. Reused TU player queue declaration, removed conflicting byte-pointer extern and tuned multiline layout. Stack slots, bank/voice registers and repeat-event setup remain. |
| func_8002BBD0 | IMPROVED 1875→1843 | 7692/7668 B. Removed conflicting unsigned global declarations in context; tested unsigned mode dispatch and layouts. Camera state machine/FP scheduling and rodata references remain substantial. Baseline uses TU's s32/s8 declarations. |
| func_8002D9C4 | UNCHANGED 134 | 476/536 B. Aggregate versus indexed five-float copy, conversion timing and layouts. Original unrolled copy and FP live ranges not recovered. |
| func_8002DDD4 | UNCHANGED 104 | 444/452 B. Output/camera types, local lifetimes and layouts; projection/clamp scheduling remains. |
| func_8002A4F0 | UNCHANGED 53 | 920/920 B. Config field widths and layouts; stack config/heap and sequence-loop registers remain. |
| func_8002FB80 | UNCHANGED 109 | 512/544 B. Loop widths and multiline layouts; packed command switch/address allocation remains. |
| func_8002FDA0 | UNCHANGED 136 | 584/572 B. Decoded-value widths and layouts; packed vertex decoding/previous-record control flow remains. |
| func_800300DC | UNCHANGED 76 | 312/316 B. Reconciled TU void-pointer ABI; run-count expression, output signedness and layouts. Backreference loop/register allocation remains. |
| func_80030220 | IMPROVED 78→77 | 340/348 B. Endpoint/cursor lifetimes and layouts; random-call ordering, saved registers and final coordinate division remain. |
| func_8003037C | MATCHED | 188-byte body, 196-byte TU allocation including original tail padding. Multiline layout with adjacent delta/end initialization resolves two setup words. |
| func_80030440 | IMPROVED 158→156 | 520/632 B. Byte dimensions and indexed input cursor; tried typed tile/header arrays and layouts. Output run unrolling, saved registers and row address arithmetic remain. |
| func_800306B8 | IMPROVED 513→510 | 2096/2104 B. Glyph/string widths and layouts; text command builder and clipping register allocation remain. |
| func_80026B38 | IMPROVED 1183→1182 | 4792/4708 B. Projection signatures, switch types and layouts; large effect dispatcher, command allocation and table contents remain. |
| func_8002A1E0 | MATCHED | 116 B. Ordinary multiline layout resolves the accumulator-clear/loop-initialization schedule. main_1A880 now has no GLOBAL_ASM stubs. |

Reserved and skipped: func_8002A900, func_8002AA98, func_8002AAEC, func_8002B9B4, func_8002F45C. The other three requested skips are outside these eight TUs.

Deleted drafts:

- tools/scratch/nonmatching/T-024/func_8002A1E0.c
- tools/scratch/nonmatching/T-026/func_8003037C.c

Neither promoted function has function_owner reservations. No symbol hints, YAML, Makefile, status.csv, boot, overlay or SDK source were edited. Regenerated linker_scripts/*.undefined_syms.txt changes are retained if present.

## Final validation

`make clean && make extract && make -j8 all && make progress` passed (parallel jobs only affect build scheduling). The ROM SHA1 remains `ba52e91b44450c548467044b26951353dc491e04`. All existing matched functions remain matching: full main and both overlay images are byte-identical.

- main: `81736d32e8cda8f399b319a49250dff972b81af8`
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`

`git diff --check` passes. Regenerated undefined-symbol files have no net changes. Generated docs/functions.csv and docs/progress.html were restored after recording the table; status.csv was untouched. Setup symlinks remain untracked and must not be staged.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 53,112 (18.32%) | 53,112 (18.32%) | 0 | 251 | 0 | 258 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 26,844 (18.64%) | 26,844 (18.64%) | 0 | 105 | 0 | 132 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 17,800 (12.95%) | 17,800 (12.95%) | 0 | 146 | 0 | 105 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
