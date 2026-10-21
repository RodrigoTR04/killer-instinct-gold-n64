# T-116 — sol-B37: fresh mid-distance targets

**1 MATCHED (408 B), 5 IMPROVED, 9 UNCHANGED. No commits.**

Production edit: `src/ovl_7DF8/ovl_7DF8_1BD90.c`, func_801C8C24 only. Five improved drafts remain in their original directories.

Read TRACKING, latest WORKLOG, overview, Makefile, permuter README and the requested T-113/T-096/T-097/T-106/T-067/T-082 reports. Missing local dependencies were symlinked from the authorized shared checkout. No ROM copied, no commits, no subagents. Production flags remain IDO 5.3 -O2 -mips2 through asm-processor.

## Selection

All 25 eligible 10–60-word rows were checked against status.csv T2. Prior mentions count `grep -l function tools/scratch/nonmatching/*/REPORT.md` before creating this report. Sort: mention count, equal size, words. First 15 selected; all requested exclusions applied. selection.json records every eligible row and the matching report paths.

| Function | Words | Compiled / original B | Prior reports | Selected |
|---|---:|---:|---:|---|
| func_801C8004 | 47 | 228 / 236 | 3 | yes |
| func_801ADA04 | 18 | 208 / 208 | 4 | yes |
| func_800268C0 | 28 | 236 / 236 | 4 | yes |
| func_801B43A8 | 34 | 196 / 196 | 4 | yes |
| func_801BEEA4 | 40 | 356 / 344 | 4 | yes |
| func_801C48E4 | 45 | 188 / 196 | 4 | yes |
| func_801C7F90 | 16 | 116 / 116 | 5 | yes |
| func_801C0800 | 21 | 248 / 248 | 5 | yes |
| func_801B0520 | 22 | 328 / 328 | 5 | yes |
| func_801BE660 | 41 | 300 / 300 | 5 | yes |
| func_80024028 | 49 | 284 / 284 | 5 | yes |
| func_801C8C24 | 22 | 396 / 408 | 5 | yes |
| func_801C47E0 | 11 | 260 / 260 | 6 | yes |
| func_801BD200 | 14 | 112 / 112 | 6 | yes |
| func_801C8AE0 | 21 | 324 / 324 | 6 | yes |
| func_8001373C | 36 | 256 / 256 | 6 | no |
| func_800121C8 | 47 | 304 / 304 | 7 | no |
| func_801C3758 | 32 | 572 / 564 | 7 | no |
| func_8001AA90 | 60 | 488 / 496 | 7 | no |
| func_8002A900 | 15 | 220 / 220 | 9 | no |
| func_801B446C | 28 | 292 / 292 | 9 | no |
| func_801BBB60 | 40 | 292 / 292 | 9 | no |
| func_801C7A98 | 14 | 568 / 568 | 10 | no |
| func_801B1210 | 28 | 284 / 284 | 10 | no |
| func_8002A4F0 | 31 | 920 / 920 | 10 | no |

## Results

Word counts mask only real ELF relocations and include body length differences. baseline.json contains every differing instruction pair and offset. Probe JSON records failed compiles explicitly. Scripts describe pre-promotion experiments; after draft deletion they are not a standalone rerunnable harness. Permuter weighted scores are not word counts.

| Function | Result | Words before → after | Diagnosis and experiments |
|---|---|---:|---|
| func_801C8004 | IMPROVED | 47 → 38 | First loop keeps current byte/pointer in v0/a1 rather than v1/v0; missing slti loop test; second loop lacks two old-mask moves (+9C/+AC) and is 8 B short. Named unit step improves allocation (47→38); direct shift/count-loop probes did not recover structure. |
| func_801ADA04 | UNCHANGED | 18 → 18 | mode+14 uses v1 versus target t7 (+28), current-mode load t7 versus t8 (+1C/+3C); pending-mode multiply and final -1 allocation differ. Direct reloads, cached fields, spacing literals and line forms failed. Redundant !=0 predicate reaches 14 but was not retained. |
| func_800268C0 | UNCHANGED | 28 → 28 | Packed offset assembly differs at +3C..+6C; four cached s16 dimensions allocate a0..a3 instead of t7/t8/t1/t0 (+AC..+DC). Direct field stores, base/offset reassociation and layouts did not improve honest cleaned C. |
| func_801B43A8 | UNCHANGED | 34 → 34 | Global group address is cached across memcpy in s1 instead of rematerialized s2 (+04..+44); inner random/count/value use a2/a3/a1 instead of a1/a2/a0. Independent group increment and copy prototype probes do not solve it; low candidates with uninitialized entry were rejected. |
| func_801BEEA4 | IMPROVED | 40 → 39 | Incoming frame 0x60 versus 0x48, slot/next and destination lifetime cause extra spill/recompute; branch increments not hoisted into delay slots (+60..+CC). Preincremented slot is retained; reusing slot as copy-size local reaches 16/344 but giving copy size its own name loses it. Remaining +64/+8C/+A8, +CC onward. |
| func_801C48E4 | IMPROVED | 45 → 25 | Missing a1/a2 home stores shifts prefix (+10 onward). Taking first parameter address recovers its home and exact size, leaving second home and schedule differences from +44. Taking both addresses matches prefix through +A4 but emits extra post-narrow stores. Narrow ABI/K&R/callee prototypes fail; signedness-changing probe rejected. |
| func_801C7F90 | IMPROVED | 16 → 3 | Cached second-byte pointer removes shared address allocation; indexed clear plus multiline source recovers unrolled store rotation. Remaining +1C/+20/+24: symbolic endpoint and start addiu versus second-byte store ordering. Pointer-end and explicit four-byte loop probes worsen code. |
| func_801C0800 | UNCHANGED | 21 → 21 | Color pack register chain differs +90..+B8, then display-list address/store scheduling +C0..+EC. Direct command reuse, arithmetic packing and multiline layouts fail; split shift candidate needs artificial expression to preserve 19 words and is rejected. |
| func_801B0520 | UNCHANGED | 22 → 22 | frame uses v1 rather than v0 (+04/+08/+20/+3C); command constant allocation +70/+94 and color chain +B8..+E4; cached frame pointer yields t0 rather than v0 at +E8 onward. Direct reload/input reuse probes fail. |
| func_801BE660 | UNCHANGED | 41 → 41 | x not homed at +14; float constants/global spacing allocated differently +2C..+4C, double conversion +AC..+BC; IDO strength-reduces width/2 to multiply where target divides (+D0 onward). Cached spacing/literal, x pointer, division precision and layouts fail. Candidate overwriting width during spacing calculation rejected. Literal requires late-rodata ownership if pursued. |
| func_80024028 | UNCHANGED | 49 → 49 | Packing order/registers diverge +38..+74 and +94..+B4; command constant schedule +7C..+D0; byte8 shift is sra instead of srl at +E8, subsequent EC pack differs. Ordered bitwise packing/unsigned shift/layouts tested; redundant-mask outputs not retained. |
| func_801C8C24 | MATCHED | 22 → 0 | Main loop already exact. Tail lacked explicit +1/+2/+3 pointers and was 12 B short (+E8 onward). Separate u16 byteIndex assigned from loop index restores IDO unrolling and all 408 B. Clean named locals, independent full-TU zero; integrated and draft deleted. |
| func_801C47E0 | UNCHANGED | 11 → 11 | +2C/+40 bank mask uses t2 versus t1; +60..+78 pointer/offset use t1/t0 versus t2/v0; +A8/+B4 offset reload t0 versus v0; +D8 addu operands reversed and old-byte restore +D0/+F0. Offset algebra and line layouts fail. |
| func_801BD200 | UNCHANGED | 14 → 14 | Initial global limit cached v0 rather than t6, pushing flags/result/one to v1/a1/a2 (+00..+34); postcall one uses a2 versus a1 (+44/+4C/+60). Local limit/result/flag pointers, declaration order and one constant do not solve it. Empty-branch score improvements rejected. |
| func_801C8AE0 | IMPROVED | 21 → 15 | Final OR/copy allocation and tail nibble temporaries differ +90 onward. Explicit low-byte mask and cached final low nibble recover main-loop allocation; remaining tail offsets +CC..+118. Return-width and packed-local probes do not solve tail. |

## Search and review evidence

Each selected target received structural/type probes, token-preserving multiline layouts, then a 900-second bounded local permuter search using `--stack-diffs --stop-on-zero --best-only --better-only -j5`. Searches use /tmp/kig-t116 only; no generated permuter directories belong in git. The first three were started in one launcher, then the other twelve in a second launcher; the first launcher was terminated without terminating its timeout-owned searches. No search was duplicated. Timeout exits include 137 after the configured interrupt/kill grace; residual orphan forkserver workers from the terminated first launcher were stopped before clean. Wall-clock caps and original logs are in /tmp; retained JSON records and scripts describe measurements. Compiler errors and behavior-changing outputs are never matches.

The C8C24 match survives separate named index assignment, descriptive local names and normal multiline formatting. It needs no rodata change. No inline asm, #line, register keyword, dead branch, volatile workaround, compiler override or padding is retained. status.csv remains lead-owned. Other production functions are unchanged.

## Final verification

`make clean && make extract && make all && make progress` passed (exit 0).
ROM and all executable images are byte-identical:

- ROM: `ba52e91b44450c548467044b26951353dc491e04`
- main: `81736d32e8cda8f399b319a49250dff972b81af8`
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`

The progress inventory reran extract/build after whitespace-only indentation cleanup during the first build; its final resolved image checks also passed. `git diff --check` passed. No search/probe processes remain. Generated docs/functions.csv and docs/progress.html were restored after recording metrics; no net linker-script changes. No boot, ovl_7E00, YAML, Makefile, status.csv, TRACKING or WORKLOG edits. No commits. Matched eligible bytes increase 70,884→71,292 (+408); T4 increases 315→316.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 289,876 | 71,292 (24.59%) | 71,292 (24.59%) | 0 | 193 | 0 | 316 | 490 (167,316) |
| boot | 8,468 | 8,468 (100.00%) | 8,468 (100.00%) | 0 | 0 | 0 | 21 | 99 (16,028) |
| main | 143,980 | 31,204 (21.67%) | 31,204 (21.67%) | 0 | 90 | 0 | 147 | 222 (63,616) |
| ovl_7DF8 | 137,428 | 31,620 (23.01%) | 31,620 (23.01%) | 0 | 103 | 0 | 148 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
