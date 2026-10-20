# T-048 — ovl_7DF8 polish round 4

Worker sol-A19. All 53 requested functions received bounded compile/compare attempts, in the requested family-first order. No commits were made.

**3 matched (1,068 bytes), 32 improved drafts, 18 unchanged.** The matched functions are func_801AD3BC, func_801CCDE8 and func_801C407C. Improvements remain in their original draft directories.

## Method and limits

Read TRACKING.md, latest WORKLOG.md, Makefile, overlay YAML and reports T-039/T-044/T-047/T-043 first. Missing baserom.us.z64, ROMs, .venv and tools/ext were symlinked from the authorized main checkout. No ROM was copied into tracked files.

Used IDO 5.3 -O2 -mips2 with production flags. Each function had a bounded candidate pass (90-second cap, normally finished sooner), followed by function-specific type, loop, struct/access, call or control-flow experiments. Clone representatives also received counter-form sweeps and their changes were checked against every sibling. No inline asm, register bindings, compiler changes or artificial padding were used. Lower scores that changed pointer semantics or unsupported signedness were rejected.

Scores below are fresh **differing aligned words plus missing/extra words**, masking only actual ELF relocations. They therefore differ from T-039's aligned-word-only screen. Draft lengths are shown separately against the original body length (excluding TU padding). Especially in the first clone family, the original standalone draft had an implicit integer lerp return; adding its real float declaration repairs that context and changes the generated conversion sequence/length. A score improvement is not proof of a match or complete behavior recovery. Only integrated functions passed linked-image verification.

The first pass tested command-pointer spelling, command-store order and local declaration order. Additional function-specific experiments are recorded below. `results.json` records fresh scores and candidate counts; `probe.py` reproduces standalone size-aware screening. Counts do not include all earlier family experiments.

## Every requested function

| Function | Result (fresh old → new score) | Draft bytes old → new / target | Attempt / remaining issue |
|---|---|---|---|
| func_801B2EF4 | IMPROVED 128→88 | 416→536 / 536 | Declare float lerp return, share command cursor and split equivalent counter stores; tried counter forms and declaration order. Frame, alpha slot and unsigned-conversion scheduling remain. |
| func_801B310C | IMPROVED 128→88 | 416→536 / 536 | Declare float lerp return, share command cursor and split equivalent counter stores; tried counter forms and declaration order. Frame, alpha slot and unsigned-conversion scheduling remain. |
| func_801B3324 | IMPROVED 128→88 | 416→536 / 536 | Declare float lerp return, share command cursor and split equivalent counter stores; tried counter forms and declaration order. Frame, alpha slot and unsigned-conversion scheduling remain. |
| func_801B353C | IMPROVED 128→88 | 416→536 / 536 | Declare float lerp return, share command cursor and split equivalent counter stores; tried counter forms and declaration order. Frame, alpha slot and unsigned-conversion scheduling remain. |
| func_801B3754 | IMPROVED 128→88 | 416→536 / 536 | Declare float lerp return, share command cursor and split equivalent counter stores; tried counter forms and declaration order. Frame, alpha slot and unsigned-conversion scheduling remain. |
| func_801B396C | IMPROVED 128→88 | 416→536 / 536 | Declare float lerp return, share command cursor and split equivalent counter stores; tried counter forms and declaration order. Frame, alpha slot and unsigned-conversion scheduling remain. |
| func_801B2010 | IMPROVED 100→87 | 432→412 / 420 | Declare float lerp return and share command cursor; tried 32-bit counter forms and command spelling. Counter branch and display-list allocation remain. |
| func_801B21B4 | IMPROVED 101→87 | 428→412 / 420 | Declare float lerp return and share command cursor; tried 32-bit counter forms and command spelling. Counter branch and display-list allocation remain. |
| func_801B2358 | IMPROVED 101→87 | 428→412 / 420 | Declare float lerp return and share command cursor; tried 32-bit counter forms and command spelling. Counter branch and display-list allocation remain. |
| func_801B24FC | IMPROVED 101→87 | 428→412 / 420 | Declare float lerp return and share command cursor; tried 32-bit counter forms and command spelling. Counter branch and display-list allocation remain. |
| func_801B26A0 | IMPROVED 101→87 | 428→412 / 420 | Declare float lerp return and share command cursor; tried 32-bit counter forms and command spelling. Counter branch and display-list allocation remain. |
| func_801B2844 | IMPROVED 101→87 | 428→412 / 420 | Declare float lerp return and share command cursor; tried 32-bit counter forms and command spelling. Counter branch and display-list allocation remain. |
| func_801B29E8 | IMPROVED 101→88 | 428→412 / 420 | Declare float lerp return and share command cursor; tried 32-bit counter forms and command spelling. Counter branch and display-list allocation remain. |
| func_801C8AE0 | UNCHANGED | 324→324 / 324 | Tried the actual queue array, packed accumulator widths and local order; loop temporary-register numbering remains. |
| func_801AD3BC | MATCHED | 428→428 / 428 | Write the final framebuffer command word before its address; the 428-byte body screens exactly and was integrated. |
| func_801C51F8 | IMPROVED 35→26 | 160→160 / 160 | Postincrement command pointers; tried callback parameters, constant locals, field signedness and address declarations. Constant registers/scheduling remain. |
| func_801CCDE8 | MATCHED | 184→196 / 196 | Return directly after a failed controller probe instead of jumping to the shared final return; integrated 196-byte body. |
| func_801CB998 | UNCHANGED | 156→156 / 148 | Tried typed packed-score calls, mask lifetime, argument width and local order; rejected widened mask semantics, retained original. |
| func_801B0520 | UNCHANGED | 328→328 / 328 | Tried earlier frame store, redundant-store removal and position width; global bases and command scheduling remain. |
| func_801C3758 | UNCHANGED | 572→572 / 564 | Tried direct byte frame wrapping, radius widths and command forms; argument spill and vertex scheduling remain. |
| func_801ADA04 | UNCHANGED | 204→204 / 208 | Tried plain pending-mode if/else rewrite and local order; global-address reuse and scheduling remain. |
| func_801BE660 | UNCHANGED | 300→300 / 300 | Tried indexed glyph access, code width and double multiplication; font traversal and float allocation remain. |
| func_801CC0CC | UNCHANGED | 212→212 / 216 | Tried indexed nested CRC loops with three accumulator types and declaration order; saved-register/prologue differences remain. |
| func_801B1210 | IMPROVED 42→39 | 284→284 / 284 | Reorder first command stores; tried fade widths and query prototype. Alpha/global/call scheduling remains. |
| func_801B43A8 | UNCHANGED | 200→200 / 196 | Tried indexed 3x3 shuffle with three index widths and pointer declaration order; pointer lifetimes/registers remain. |
| func_801C6A80 | IMPROVED 43→30 | 292→292 / 292 | Update the byte phase directly, then read it for comparisons; tried phase widths and typed audio calls. Remaining bases/registers differ. |
| func_801C1704 | IMPROVED 51→50 | 172→136 / 204 | Use s16 bounded clear counter; tried pointer loop and two-dimensional arrays. Original unrolling/address calculation remains different. |
| func_801C71FC | IMPROVED 44→39 | 200→180 / 172 | Store player state with direct arg0*2 indexing instead of multiply/divide temporary; remaining spills/registers differ. |
| func_801BF788 | IMPROVED 44→21 | 204→200 / 200 | Use u16 packed input and separate final accumulator update; two distinct input/output cursors preserved. Saved registers still differ. |
| func_801C48E4 | UNCHANGED | 188→188 / 196 | Tried argument widths and typed renderer setup; rejected width-only gain without matching narrowing evidence. Original spills remain. |
| func_801BFB40 | IMPROVED 51→47 | 216→208 / 200 | Chain the viewport dimension assignments; tried other chained initializers. Copy/global-base scheduling remains. |
| func_801C7998 | IMPROVED 60→55 | 276→220 / 256 | Use a full-width bounded result index; tried explicit u64 switch local and index widths. Switch/high-word setup still differs; draft needs rodata if integrated. |
| func_801C35D8 | IMPROVED 66→65 | 380→372 / 384 | Assign visibility with a plain boolean expression; tried direct cloud callback pointer. Saved registers and command scheduling remain. |
| func_801BE540 | UNCHANGED | 280→280 / 288 | Tried indexed glyph access, float space width and code signedness; rejected unsigned-index gain because it changes negative-code handling. |
| func_801C0610 | IMPROVED 72→71 | 372→372 / 372 | Reorder the second command stores; tried typed matrix pointer and multiply spelling. Matrix loads and command registers remain. |
| func_801B18BC | IMPROVED 72→4 | 308→300 / 300 | Pass indexed x coordinate, allowing IDO to strength-reduce the loop itself; 4 remaining initialization-scheduling words. Tried constant locals, initialization/declaration order and call types. |
| func_801C2ADC | UNCHANGED | 600→600 / 600 | Tried sequence-index/pressed-bit widths and local order; 64-bit comparisons, clear unrolling and switch remain different. |
| func_801BBB60 | IMPROVED 73→71 | 312→296 / 292 | Use s16 bounded palette index; tried unsigned counter and for-loop initialization. Unrolling/store order remains different. |
| func_801BE790 | UNCHANGED | 372→372 / 384 | Tried table/cursor initialization and update order plus local order; table-store and loop-register differences remain. |
| func_801B6A68 | IMPROVED 75→20 | 368→368 / 368 | Postincrement all command cursors; tried shared pointer, store order and texture-bank arithmetic. 20 command constant/register words remain. |
| func_801C407C | MATCHED | 436→444 / 444 | Chain RGB clears in original address order; integrated 444-byte body with complete TU rodata ownership. |
| func_801C6D40 | IMPROVED 77→74 | 320→316 / 300 | Express the hand-expanded unsigned conversion as (f64)(u32)(0xF0-var_a3); remaining phase/control-flow registers differ. |
| func_801BB464 | UNCHANGED | 320→320 / 304 | Tried scale-local widths and declaration order; coordinate/call spills and table loads remain. |
| func_801BA884 | UNCHANGED | 496→496 / 500 | Tried scale-local widths and declaration order; both render calls still differ in coordinate registers and spills. |
| func_801C7CD0 | IMPROVED 86→74 | 376→376 / 380 | Chain RGB clears; tried wider mode cache and replay condition. Remaining mode/global-base/call differences remain. |
| func_801BED0C | UNCHANGED | 412→412 / 408 | Tried signed packed arithmetic, loop widths and local order; 64-bit divide/remainder allocation remains. |
| func_801C49A8 | IMPROVED 88→85 | 548→548 / 548 | Reorder first display-list command stores; tried flags/scale widths and dead spill removal. Frame and call spills remain. |
| func_801C224C | UNCHANGED | 364→364 / 372 | Tried byte mode cache, copy-index widths and declaration order; mode-cache saved register/frame and copy scheduling remain. |
| func_801BEEA4 | UNCHANGED | 364→364 / 344 | Tried score/count widths and insertion cursor structure; rejected signedness changes and cursor merging that altered insertion addresses. |
| func_801C17D0 | IMPROVED 107→105 | 400→400 / 448 | Reorder pointer/value declarations; tried branch-local pointers, value signedness and player width. Stat branches and 64-bit stores remain. |
| func_801C3E40 | IMPROVED 98→96 | 492→492 / 504 | Reorder triangle command stores; tried ring-index width, fade alpha type and decrement placement. Vertex/update scheduling remains. |
| func_801C5064 | IMPROVED 95→93 | 404→404 / 404 | Keep loaded byte count in s32; tried indexed text table and spacing expression. Frame, saved floats and text-call scheduling remain. |
| func_801BE910 | UNCHANGED | 400→400 / 356 | Tried wide score parameter and short loop counter; rejected score narrowing changes without matching evidence. Loop unrolling/register differences remain. |

## Integration and rodata ownership

- func_801AD3BC: use the existing RenderState definition and add DisplayCommand plus the required externs at the original pragma position. Final framebuffer command store order fixes scheduling; 428 bytes.
- func_801CCDE8: direct early return after failed probe; preserve the TU's existing u8 return declaration and osRecvMesg prototype, and type the controller calls. 196 bytes.
- func_801C407C: chained RGB clears preserve the original bases/address order. 444 bytes. Define the three original const strings SUPREME, two-spaces-ULTRA and AWESOME where their asm definitions migrate out.

New YAML subsegment: `[0xE7CC0, .rodata, ovl_7DF8_18520]`, ending at `0xE7D10`; both ends are 16-byte aligned. This owns the complete TU range: five strings, the switch jump table and four float constants plus alignment. The two remaining strings and float constants migrate into the unchanged func_801C4240 GLOBAL_ASM file. A new asm-owned data fragment `ovl_7DF8_remaining_2` begins at 0xE7D10 and ends at existing save-TU rodata 0xE9A40. Other rodata ownership is unchanged. Makefile is unchanged.

Deleted drafts:

- tools/scratch/nonmatching/T-019/func_801AD3BC.c
- tools/scratch/nonmatching/T-021/func_801CCDE8.c
- tools/scratch/nonmatching/T-030/func_801C407C.c

## Final verification

`make clean && make extract && make all && make progress` passed on the final integrated source. ROM SHA1: `ba52e91b44450c548467044b26951353dc491e04`; byte comparison against baserom passed.

All image comparisons passed:

- main: `81736d32e8cda8f399b319a49250dff972b81af8`
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`

Total T4 increases 240 → 243; ovl_7DF8 T4 increases 87 → 90. Matched code increases by 1,068 bytes. `git diff --check` passed. Generated docs/functions.csv and docs/progress.html were restored after recording the table. Main, boot, ovl_7E00, their YAML files, Makefile, status.csv, TRACKING.md and WORKLOG.md are unchanged. Local prerequisite symlinks are untracked; no ROM content is part of the patch.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 50,520 (15.83%) | 50,520 (15.83%) | 0 | 319 | 0 | 243 | 437 (138,092) |
| boot | 8,468 | 8,108 (95.75%) | 8,108 (95.75%) | 0 | 1 | 0 | 20 | 99 (16,028) |
| main | 173,204 | 28,208 (16.29%) | 28,208 (16.29%) | 0 | 157 | 0 | 133 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 14,204 (10.34%) | 14,204 (10.34%) | 0 | 161 | 0 | 90 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
