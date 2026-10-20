# T-045 — sol-C18: main polish round 2

Worktree: `/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-ce4f7418`. No commits.

**5 matches (720 original code bytes), 8 improved drafts.** Main T4: 133 → 138. Total T4: 230 → 235. All 157 starting drafts were screened; 38 were classified as blockers, and 106 have no retained changes. Screening is not a claim that all large drafts received a rewrite: the table explicitly distinguishes baseline screening from focused refinements.

## FU-16 part 2: declaration reconciliation

`src/main/main_2FF0.c` now declares `boot_dma(s32, s32, s32)`, exactly agreeing with `src/boot/boot_12B0.c`; boot was not edited. Pointer addresses are cast at existing call sites. In `func_80012A8C`, both endpoints must be converted before subtraction: `(s32)range->end - (s32)range->start`. Leaving pointer subtraction there adds a move and shifts the TU. The signed declaration plus signed symbol-address arithmetic matches `func_80013C84` and `func_8001BB10`. Existing callers `80012A8C`, `8001D37C`, `8001D42C`, `80021ADC`, and `80024144` retain their exact code, demonstrated by the complete image comparison.

`func_80014250` was retried with typed symbol addresses, pointer differences, integer differences, local endpoints, scope variants and signed/unsigned operand combinations. Its saved draft is 144/144 bytes and three words off in the production TU: the ra save is after the two address addius instead of before them. The second DMA/inflate pair matches. It remains GLOBAL_ASM.

## Matches and declarations

- `main_2FF0.c`: `func_80013C84` (84 B), `func_8001BB10` (84 B).
- `main_20220.c`: `func_80030020` (188 B). The old draft advanced the source/target/length pointers by 16/16/4 bytes; the original uses arrays with 4/4/2-byte strides. Typed pointers, a u16 count, local cursors inside the guarded loop, and a two-case switch reproduce the original. Added declarations for `func_800300DC(void *, void *, s32)` and `func_8002A40C(void *, void *, s32)`.
- `main_1EB40.c`: `func_8002F944` (184 B), `func_8002FAC0` (180 B). Used the existing list-head and queue declarations instead of conflicting pointer externs. The first uses a u8 mask and a 16-byte event record; the second uses a u8 group/u16 volume and a 24-byte event record. Unused event payload fields remain opaque. Changed the three `func_8002F944` wrapper declarations from s32 to u8; the wrappers still match.

Deleted drafts:

```
T-020/func_80013C84.c
T-022/func_8001BB10.c
T-024/func_8002F944.c
T-024/func_8002FAC0.c
T-026/func_80030020.c
```

No Makefile override was needed. No boot, overlay, yaml, or status.csv edits; no inline asm or register bindings. Generated docs/functions.csv and docs/progress.html were restored after capturing the final table. Local dependency symlinks point to the authorized main checkout; no ROM was copied or added to git.

## Diagnostics and limitations

Focused refinements started with the small T-026/T-032/T-033 candidates, plus FU-16. Existing T-035 ABI findings were confirmed from the reports/assembly and left alone. The broader standalone screen used production IDO 5.3 -O2 -mips2 with instruction-position comparison, masking relocation address fields and counting size differences. Drafts that depend on shared declarations can fail that standalone screen; those entries are marked explicitly. It is only a diagnostic, not linked validation or an edit-distance score. Prior report counts were sometimes unmasked and are not directly comparable.

The 8 retained improvements are annotated in place. `80014250` and `800244F0` were also compiled in their complete production TU; `8003037C` was linked and measured against the original image before being restored to GLOBAL_ASM. The other five improvements are standalone measurements only, and are not behavior-certified. `8003037C` has an exact standalone body but differs by two setup instructions in the actual TU, so it was deliberately not promoted. `800244F0` now has the correct size/register shape but its size spill remains at 0x24 rather than 0x20.

## Every screened/attempted function

| Function | Draft directory | Result | Detail |
|---|---|---|---|
| `func_8000FA80` | T-033 | UNCHANGED | screened existing draft; no retained rewrite; standalone requires shared TU declarations/types |
| `func_8001178C` | T-033 | SKIPPED | switch/jump-table rodata ownership (prior reports) |
| `func_800121C8` | T-033 | IMPROVED 55 words | standalone; s32 decoded mode; 304 bytes, previously 308 |
| `func_80012390` | T-033 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_8001256C` | T-033 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_8001272C` | T-033 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_80012950` | T-033 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_80012B7C` | T-033 | SKIPPED | switch/jump-table rodata ownership (prior reports) |
| `func_800131A4` | T-033 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_8001346C` | T-033 | SKIPPED | switch/jump-table rodata ownership (prior reports) |
| `func_8001373C` | T-020 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_80013C84` | T-020 | MATCHED | signed DMA declaration and signed address subtraction |
| `func_80013CD8` | T-033 | UNCHANGED | screened existing draft; no retained rewrite; standalone requires shared TU declarations/types |
| `func_80014250` | T-020 | IMPROVED 3 words | full TU; initial ra save/address-load scheduling; 144 bytes |
| `func_800142E0` | T-033 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_80014D5C` | T-033 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_80015450` | T-033 | SKIPPED | double 50.0 literal emits rodata owned by data asm; other codegen differences remain |
| `func_80015594` | T-033 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_80015F6C` | T-020 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_80016078` | T-033 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_80016258` | T-033 | UNCHANGED | screened existing draft; no retained rewrite; standalone requires shared TU declarations/types |
| `func_80016760` | T-020 | SKIPPED | asm-owned data: needs the global byte array defined in this TU (T-040) |
| `func_80016910` | T-033 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_80016BE0` | T-033 | UNCHANGED | screened existing draft; no retained rewrite; standalone requires shared TU declarations/types |
| `func_800170C4` | T-033 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_80017378` | T-033 | UNCHANGED | screened existing draft; no retained rewrite; standalone requires shared TU declarations/types |
| `func_80017A68` | T-033 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_80017D6C` | T-033 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_8001808C` | T-022 | UNCHANGED | screened existing draft; no retained rewrite; standalone requires shared TU declarations/types |
| `func_80018664` | T-022 | UNCHANGED | screened existing draft; no retained rewrite; standalone requires shared TU declarations/types |
| `func_80018AE0` | T-022 | UNCHANGED | screened existing draft; no retained rewrite; standalone requires shared TU declarations/types |
| `func_80018E88` | T-022 | SKIPPED | asm-owned float/double literals (FU-16) |
| `func_80018F20` | T-022 | UNCHANGED | screened existing draft; no retained rewrite; standalone requires shared TU declarations/types |
| `func_800191F0` | T-022 | UNCHANGED | screened existing draft; no retained rewrite; standalone requires shared TU declarations/types |
| `func_800193DC` | T-022 | UNCHANGED | screened existing draft; no retained rewrite; standalone requires shared TU declarations/types |
| `func_80019880` | T-022 | UNCHANGED | screened existing draft; no retained rewrite; standalone requires shared TU declarations/types |
| `func_8001AA90` | T-022 | UNCHANGED | screened existing draft; no retained rewrite; standalone requires shared TU declarations/types |
| `func_8001AD04` | T-022 | UNCHANGED | screened existing draft; no retained rewrite; standalone requires shared TU declarations/types |
| `func_8001B134` | T-022 | UNCHANGED | screened existing draft; no retained rewrite; standalone requires shared TU declarations/types |
| `func_8001B620` | T-022 | UNCHANGED | screened existing draft; no retained rewrite; standalone requires shared TU declarations/types |
| `func_8001BB10` | T-022 | MATCHED | signed DMA addresses and size subtraction |
| `func_8001BB64` | T-022 | UNCHANGED | screened existing draft; no retained rewrite; standalone requires shared TU declarations/types |
| `func_8001BDE0` | T-022 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_8001C43C` | T-022 | UNCHANGED | screened existing draft; no retained rewrite; standalone requires shared TU declarations/types |
| `func_8001C5AC` | T-022 | UNCHANGED | screened existing draft; no retained rewrite; standalone requires shared TU declarations/types |
| `func_8001CBCC` | T-022 | SKIPPED | asm-owned float/double literals (FU-16) |
| `func_8001CD50` | T-022 | UNCHANGED | screened existing draft; no retained rewrite; standalone requires shared TU declarations/types |
| `func_8001D080` | T-022 | UNCHANGED | screened existing draft; no retained rewrite; standalone requires shared TU declarations/types |
| `func_8001D47C` | T-022 | UNCHANGED | screened existing draft; no retained rewrite; standalone requires shared TU declarations/types |
| `func_8001D7E4` | T-022 | UNCHANGED | screened existing draft; no retained rewrite; standalone requires shared TU declarations/types |
| `func_8001DE5C` | T-022 | UNCHANGED | screened existing draft; no retained rewrite; standalone requires shared TU declarations/types |
| `func_8001E0B4` | T-022 | UNCHANGED | screened existing draft; no retained rewrite; standalone requires shared TU declarations/types |
| `func_8001E33C` | T-022 | UNCHANGED | screened existing draft; no retained rewrite; standalone requires shared TU declarations/types |
| `func_8001EC74` | T-022 | UNCHANGED | screened existing draft; no retained rewrite; standalone requires shared TU declarations/types |
| `func_80020E98` | T-032 | UNCHANGED | screened existing draft; no retained rewrite; standalone requires shared TU declarations/types |
| `func_800216D4` | T-032 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_80021B6C` | T-032 | SKIPPED | switch/jump-table rodata ownership (prior reports) |
| `func_800238C4` | T-032 | UNCHANGED | screened existing draft; no retained rewrite; standalone requires shared TU declarations/types |
| `func_80023EF0` | T-032 | UNCHANGED | screened existing draft; no retained rewrite; standalone requires shared TU declarations/types |
| `func_80024028` | T-032 | IMPROVED 49 words | standalone; packed-color arithmetic; 284 bytes |
| `func_800241BC` | T-032 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_800244F0` | T-032 | IMPROVED 2 words | full TU; size spill at 0x24 instead of 0x20; 196 bytes |
| `func_800245B4` | T-032 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_80024714` | T-032 | UNCHANGED | screened existing draft; no retained rewrite; standalone requires shared TU declarations/types |
| `func_800249DC` | T-032 | SKIPPED | switch/jump-table rodata ownership (prior reports) |
| `func_80024B0C` | T-032 | UNCHANGED | integer-zero variant did not improve |
| `func_80024CE0` | T-032 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_800253D0` | T-032 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_800257FC` | T-032 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_80025D58` | T-032 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_80025FC4` | T-032 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_80026738` | T-032 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_800268C0` | T-032 | UNCHANGED | tried parameter widths/address types; no lower diagnostic count |
| `func_800269AC` | T-032 | UNCHANGED | tried global array view; no improvement |
| `func_80026B38` | T-032 | SKIPPED | switch/jump-table rodata ownership (prior reports) |
| `func_80027E1C` | T-032 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_800281C4` | T-024 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_80028230` | T-024 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_800287D4` | T-024 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_80028A00` | T-024 | UNCHANGED | screened existing draft; no retained rewrite; standalone requires shared TU declarations/types |
| `func_800297A4` | T-024 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_80029AB0` | T-024 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_80029BE0` | T-024 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_8002A004` | T-024 | SKIPPED | asm-owned float/double literals (FU-16) |
| `func_8002A1E0` | T-024 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_8002A300` | T-024 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_8002A4F0` | T-024 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_8002A900` | T-024 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_8002A9DC` | T-024 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_8002AA98` | T-024 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_8002AAEC` | T-024 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_8002AB90` | T-024 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_8002AEE4` | T-024 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_8002B034` | T-024 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_8002B1EC` | T-024 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_8002B22C` | T-024 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_8002B57C` | T-024 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_8002B7E0` | T-024 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_8002B91C` | T-024 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_8002B95C` | T-024 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_8002B9B4` | T-024 | UNCHANGED | integer-zero and unary-negation variants did not improve |
| `func_8002BBD0` | T-024 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_8002D9C4` | T-024 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_8002DCC8` | T-024 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_8002DDD4` | T-024 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_8002DF98` | T-024 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_8002E150` | T-024 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_8002E4A0` | T-024 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_8002E724` | T-024 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_8002F45C` | T-024 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_8002F5F0` | T-024 | UNCHANGED | screened existing draft; no retained rewrite; standalone requires shared TU declarations/types |
| `func_8002F6F4` | T-024 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_8002F944` | T-024 | MATCHED | u8 mask, 16-byte event, acquire interrupt mask before reading list, comparison order |
| `func_8002FAC0` | T-024 | MATCHED | u8 group/u16 volume, 24-byte event, comparison order |
| `func_8002FB80` | T-024 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_8002FDA0` | T-024 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_80030020` | T-026 | MATCHED | typed pointer arrays/u16 count, correct 4/4/2-byte strides, two-case switch |
| `func_800300DC` | T-026 | IMPROVED 76 words | standalone; cursor local; 312 bytes |
| `func_80030220` | T-026 | IMPROVED 78 words | standalone; cursor locals/endpoint expression; 340 bytes |
| `func_8003037C` | T-026 | IMPROVED 2 words | linked; pointer setup instructions swapped; 188-byte body plus 8-byte TU pad |
| `func_80030440` | T-026 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_800306B8` | T-026 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_80031050` | T-026 | SKIPPED | private decoder/helper ABI or handwritten register allocation |
| `func_800310C0` | T-026 | SKIPPED | private decoder/helper ABI or handwritten register allocation |
| `func_80031A38` | T-026 | SKIPPED | private decoder/helper ABI or handwritten register allocation |
| `func_80031DD0` | T-026 | UNCHANGED | screened existing draft; no retained rewrite; standalone requires shared TU declarations/types |
| `func_80032360` | T-026 | SKIPPED | handwritten computed-tail stores/unaligned doubleword clears |
| `func_80032504` | T-026 | SKIPPED | handwritten computed-tail stores/unaligned doubleword clears |
| `func_80032600` | T-026 | SKIPPED | private decoder/helper ABI or handwritten register allocation |
| `func_80032670` | T-026 | SKIPPED | private decoder/helper ABI or handwritten register allocation |
| `func_800326F0` | T-026 | SKIPPED | native 64-bit instruction/register ABI; mips2 C uses word pairs |
| `func_80032738` | T-026 | SKIPPED | native 64-bit instruction/register ABI; mips2 C uses word pairs |
| `func_80032750` | T-026 | SKIPPED | private decoder/helper ABI or handwritten register allocation |
| `func_8003278C` | T-026 | SKIPPED | private decoder/helper ABI or handwritten register allocation |
| `func_800327E8` | T-026 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_800330B0` | T-026 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_80035F10` | T-026 | UNCHANGED | T-037 -mips1 candidate remains closer (2 spill words); no new flags |
| `func_80037780` | T-026 | UNCHANGED | typed SDK-style relocation rewrite did not improve size/ABI; extra return stub remains |
| `func_80037A30` | T-026 | SKIPPED | private-register/IPA audio ABI (FU-15 and draft notes) |
| `func_80037A6C` | T-026 | SKIPPED | private-register/IPA audio ABI (FU-15 and draft notes) |
| `func_80037C3C` | T-026 | SKIPPED | private-register/IPA audio ABI (FU-15 and draft notes) |
| `func_8003846C` | T-026 | SKIPPED | private-register/IPA audio ABI (FU-15 and draft notes) |
| `func_80038DE0` | T-026 | IMPROVED 47 words | standalone; typed sequence arrays and postincrements; 192 bytes |
| `func_80038EA4` | T-026 | SKIPPED | private-register/IPA audio ABI (FU-15 and draft notes) |
| `func_80039C08` | T-026 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_8003D71C` | T-026 | SKIPPED | private-register/IPA audio ABI (FU-15 and draft notes) |
| `func_8003D9BC` | T-026 | SKIPPED | private-register/IPA audio ABI (FU-15 and draft notes) |
| `func_8003E1DC` | T-026 | SKIPPED | private-register/IPA audio ABI (FU-15 and draft notes) |
| `func_8003EF90` | T-026 | UNCHANGED | screened existing draft; no retained rewrite |
| `func_8003FB20` | T-026 | SKIPPED | private-register/IPA audio ABI (FU-15 and draft notes) |
| `func_800405E4` | T-035 | SKIPPED | private-register/IPA audio ABI (FU-15 and draft notes) |
| `func_800407B4` | T-035 | SKIPPED | private-register/IPA audio ABI (FU-15 and draft notes) |
| `func_80040A4C` | T-035 | SKIPPED | private-register/IPA audio ABI (FU-15 and draft notes) |
| `func_800414F8` | T-035 | SKIPPED | private-register audio ABI; explicit task exclusion |
| `func_80041978` | T-035 | SKIPPED | private-register audio ABI; explicit task exclusion |
| `func_800419C8` | T-035 | SKIPPED | private-register audio ABI; explicit task exclusion |
| `func_80042198` | T-035 | SKIPPED | asm-owned jump table and float literals |

## Lead-vet integration with T-046

Stashed all T-045 changes, fetched master from `/home/rodri/Projects/killer-instinct-gold-n64`, rebased onto `838fc16`, and reapplied the stash without conflicts. Read T-046's report before resolving its rodata ownership interaction.

T-046 assigned `D_800489D0`, `D_800489D8`, `D_800489E0`, and `D_800489E8` to asm owner `func_8001BB10`. Promoting that owner removed their definitions. Their actual C users are `func_8001BA18` and `func_8001BA94`. Replaced the former's extern loads with double literals `0.001` and the latter's with `0.007`, retaining the original casts. Removed the four extern declarations and four `force_migration` symbol entries. IDO emits all four constants in their original pool slots, and both existing functions still match. No replacement asm owner or yaml change was needed.

The function table above records the original T-045 screening baseline; T-046 subsequently resolved some of its rodata blockers. The final table below includes all changes already landed on current master as well as these five T-045 matches.

## Final clean validation

`make clean && make extract && make -j12 all && make progress` passed. The rebuilt ROM and all three images are byte-identical. ROM SHA1: `ba52e91b44450c548467044b26951353dc491e04`.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 50,648 (15.87%) | 50,648 (15.87%) | 0 | 315 | 0 | 247 | 437 (138,092) |
| boot | 8,468 | 8,108 (95.75%) | 8,108 (95.75%) | 0 | 1 | 0 | 20 | 99 (16,028) |
| main | 173,204 | 29,404 (16.98%) | 29,404 (16.98%) | 0 | 150 | 0 | 140 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 13,136 (9.56%) | 13,136 (9.56%) | 0 | 164 | 0 | 87 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
