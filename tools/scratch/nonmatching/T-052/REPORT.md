# T-052 — sol-A20: main polish round 3

Result: **2 MATCHED (436 bytes), 15 IMPROVED drafts, 26 UNCHANGED**. All 43 requested functions received compiled C alternatives. No commits.

## Method

Read TRACKING, latest WORKLOG entries, Makefile and the T-040/T-045/T-046 reports before editing. Missing baserom, ROMs, .venv and tools/ext were symlinked from the main checkout. ROM bytes were never copied into git.

Used production IDO 5.3 `-O2 -mips2` flags with bounded batches of alternative C forms. Small wrappers received statement/temporary/loop alternatives, including all 120 independent store orders for B91C. Larger drafts received function-specific loop, structure, type or expression rewrites, then only promising candidates received another short round. No inline assembly, register bindings, compiler flag changes or binary patching.

Counts below are **positional differing instruction words**, masking only actual ELF HI16/LO16/26 relocation fields, measured with `probe.py`. Original and new body sizes are included because a lower count alone is not a size match. Missing target tail words are not counted as emitted mismatches; oversized bodies compare against the following original bytes. These are diagnostic draft improvements, not behavioral validation or linked-match claims. `retained.json` preserves measurements, including supplemental declarations needed to compile old drafts. Old counts can differ from historical report headers because only real relocations are masked.

## Every requested function, in requested size order

| Function | Result | Body bytes old → new (target) | Attempt / remaining issue |
|---|---|---|---|
| `func_8002B1EC` | UNCHANGED | 64 → 64 (64) | Early returns, quotient tests, array/struct globals and zero-result temporaries leave the separate load/store address scheduling unresolved. |
| `func_8002B91C` | UNCHANGED | 64 → 64 (64) | All 120 store orders and local-copy forms leave the two parameter-home-store swaps unresolved. |
| `func_8002AA98` | UNCHANGED | 80 → 80 (84) | Split scaling/cast temporaries and call parameter types do not reproduce the extra final argument move; narrowing the product was rejected. |
| `func_8002AAEC` | UNCHANGED | 80 → 80 (84) | Same scaling/cast family as AA98; no equivalent form reproduces the final move. |
| `func_8002B95C` | UNCHANGED | 88 → 88 (88) | Parameter copies, matrix pointer local and matrix declaration forms retain the two prologue words. |
| `func_800281C4` | UNCHANGED | 108 → 108 (108) | Branch assignment order, integer addresses and ternaries do not fix the branch-arm address setup order. |
| `func_8002A1E0` | UNCHANGED | 116 → 116 (116) | Countdown, zero-based and do/while loops leave the zero-store/loop-constant schedule unresolved. |
| `func_8002A9DC` | MATCHED | 192 → 188 (188) | 32-bit index removes the unnecessary halfword argument handling; full linked match. |
| `func_8002B7E0` | UNCHANGED | 208 → 208 (208) | Separate zero stores, norm types and conditional assignment do not fix the two early prologue words. |
| `func_8002F5F0` | UNCHANGED | 220 → 220 (212) | Owner temporary and free-head restructuring reduce size only, without improving the remaining instruction sequence. |
| `func_8002A900` | IMPROVED 55→24 words | 224 → 220 (220) | Remove the draft-only index mask; frame and pre-DMA global-address reuse still differ. |
| `func_8002DF98` | IMPROVED 56→2 words | 240 → 244 (244) | Put the three-term dot product first in the final addition; only the initial matrix-load/mtc1 swap remains. |
| `func_8001C43C` | MATCHED | 272 → 248 (248) | Indexed loops with increment before destination store; signed byte arrays and unsigned input bytes; full linked match. |
| `func_8001373C` | UNCHANGED | 264 → 264 (256) | Literal constants, distance-local order and separate division temporaries retain the unwanted stack frame/spill. |
| `func_80015F6C` | IMPROVED 34→27 words | 268 → 268 (268) | Chained white RGB stores improve scheduling; timer reload and predecrement forms do not help further. |
| `func_8002A300` | IMPROVED 42→7 words | 296 → 268 (268) | Word-sized accumulator/run length and guarded decrement loop remove truncations and the extra inner-loop comparison. |
| `func_8002DCC8` | UNCHANGED | 268 → 268 (268) | All delta declaration orders and a length temporary leave the original four scheduling differences. |
| `func_80029AB0` | UNCHANGED | 284 → 284 (304) | Indexed effects and a single-element inner loop are unrolled back to the same code; cursor/register shape remains. |
| `func_80023EF0` | IMPROVED 81→67 words | 324 → 296 (312) | Boolean facing value removes branch machinery; missing position type is now supplied in the draft. |
| `func_80012950` | IMPROVED 56→40 words | 316 → 312 (316) | 32-bit argument improves the initialization sequence; chained float clears and array clear order do not help. |
| `func_8001BDE0` | UNCHANGED | 316 → 316 (316) | Structured forward loop, reversed factor loads and direct global factors do not improve FP callee-save allocation. |
| `func_8002AEE4` | IMPROVED 71→48 words | 320 → 336 (336) | Top-tested message loop recovers the target body size and improves control flow; message dispatch still differs. |
| `func_800245B4` | UNCHANGED | 344 → 344 (352) | Indexed row loop and explicit cache field copies do not improve the interval-check/control-flow shape. |
| `func_8001256C` | UNCHANGED | 356 → 356 (356) | Command/value order, unsigned color and an explicit cursor do not improve the display-list register allocation. |
| `func_8002B57C` | IMPROVED 66→4 words | 348 → 368 (368) | Typed four-byte controller-status records and a four-element loop produce the original unrolling; four branch-scheduling words remain. |
| `func_8002B22C` | IMPROVED 94→93 words | 396 → 392 (380) | Mask the DMA address to even alignment instead of subtracting its low bit; cache-list allocation still differs. |
| `func_80026738` | UNCHANGED | 388 → 388 (392) | Scale/kind widening and delayed effect-pointer advance do not improve the sprite setup sequence. |
| `func_8002F45C` | IMPROVED 76→39 words | 416 → 404 (404) | Keep pan in a word local, avoiding byte truncation; key-load timing and next/prev order do not help further. |
| `func_8002B034` | UNCHANGED | 440 → 440 (440) | Sample comparison and command-byte-mask alternatives lose the existing register shape; original draft retained. |
| `func_8002DDD4` | UNCHANGED | 444 → 444 (452) | Float depth test and explicit result conversions do not recover the original frame or FP register allocation. |
| `func_8001CD50` | UNCHANGED | 436 → 436 (460) | Shared zero and chained paired clears do not improve the initialization schedule; standalone declaration gap diagnosed. |
| `func_80012390` | IMPROVED 110→106 words | 480 → 464 (476) | Use a plain byte-zero sentinel instead of multiplying by 0x01010101; indexed pixel copying does not help. |
| `func_80016078` | UNCHANGED | 448 → 448 (480) | Cursor form and integer dimensions shorten the body without recovering the original instruction sequence; float dimension semantics retained. |
| `func_8002E4A0` | UNCHANGED | 428 → 428 (480) | Pointer voice linking and signed loop indices do not help; moving current initialization across external calls was not retained. |
| `func_800191F0` | IMPROVED 123→106 words | 508 → 476 (492) | Remove redundant halfword self-stores; a typed scalar actor loop loses the original four-way unrolling. |
| `func_8001AA90` | IMPROVED 62→61 words | 488 → 488 (496) | Preincrement the byte phase counter directly; wrapping-loop and sine-local changes do not help further. |
| `func_8002F6F4` | UNCHANGED | 516 → 516 (516) | Complement bit clear, word repeat id and event declaration order all reproduce the same 30-word mismatch. |
| `func_8002D9C4` | UNCHANGED | 476 → 476 (536) | Explicit pose field copies shorten the body but leave nearly every emitted word different; original struct-copy draft retained. |
| `func_8001272C` | UNCHANGED | 544 → 544 (540) | For-loop traversal, word fade and a local fade comparison do not improve the clamp/render sequence. |
| `func_8002FB80` | UNCHANGED | 512 → 512 (544) | Unsigned loop, output-end traversal and signed input bytes do not recover the packed-command switch shape. |
| `func_800287D4` | IMPROVED 90→89 words | 560 → 560 (556) | Write x before y in the position update; cursor traversal and equivalent RNG comparison do not help. |
| `func_8002FDA0` | IMPROVED 143→136 words | 580 → 584 (572) | Unsigned decoded halfword local avoids sign extensions before halfword stores; switch/vertex frame still differs. |
| `func_8001DE5C` | UNCHANGED | 624 → 624 (600) | Literal sign-extension arithmetic, word flag argument and aligned-width widening do not produce a convincing closer frame; original retained. |

## Source, declarations and ownership

- `main_1AB90.c`: replaced A9DC's GLOBAL_ASM with C, with an eight-byte sequence-entry structure, a 32-bit index, and explicit casts for the existing `boot_dma(s32,s32,s32)` ABI. Existing sequence-player declarations are reused.
- `main_2FF0.c`: replaced C43C's GLOBAL_ASM with C. Its forward declaration takes byte pointers. After integration with T-051, the TU defines `u8 D_8004A730[8]` and `s8 D_8004A738[8]`; D_8004A5E0/D_8004A688 are extern signed-byte arrays with a seven-byte row stride. Each of these four symbols has one declaration/definition in the TU. Existing first-byte stores in 15B64/18418/1971C now index `[0]` or `[0][0]`; full image validation confirms those functions remain identical.
- C43C was the forced asm owner of D_800489F8/D_800489FC. Their actual C user, the already-matched `func_8001BF1C`, now uses `1500.0f` and `4525.0f`. Removed its two externs and the two force_migration/function_owner symbol lines. IDO emits both constants at their original addresses and BF1C remains byte-identical. C43C itself has no floating-point operations. No replacement owner or yaml change was necessary.
- No main undefined-symbol change was required. Regenerated undefined-symbol changes are retained after the master integration, as requested by the lead. No boot/overlay source, yaml, Makefile or status.csv edits.

Deleted drafts:

- `tools/scratch/nonmatching/T-024/func_8002A9DC.c`
- `tools/scratch/nonmatching/T-022/func_8001C43C.c`

Improved drafts are updated in their original directories. Added standalone declarations to the retained 23EF0, 191F0 and 1AA90 drafts where needed; these declarations do not alter production source.

## Original validation before T-051 integration

`make clean && make extract && make -j8 all && make progress` passed after the final source edits. The ROM is byte-identical, SHA1 `ba52e91b44450c548467044b26951353dc491e04`. All three decompressed images printed OK:

- main: `81736d32e8cda8f399b319a49250dff972b81af8`
- ovl_7DF8: `ea830aae50ff1422da60d4b7fdbfc29f03b1be39`
- ovl_7E00: `2b01138a290212b9d886981e1196f7b6fb45ecdb`

`git diff --check` passed. Generated docs/functions.csv and docs/progress.html are restored after recording the table; the lead can regenerate them when vetting. status.csv is untouched, including the two old T2 override rows for the deleted drafts (inventory still correctly recognizes the C definitions as T4).

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 52,152 (16.34%) | 52,152 (16.34%) | 0 | 310 | 0 | 252 | 437 (138,092) |
| boot | 8,468 | 8,108 (95.75%) | 8,108 (95.75%) | 0 | 1 | 0 | 20 | 99 (16,028) |
| main | 173,204 | 29,840 (17.23%) | 29,840 (17.23%) | 0 | 148 | 0 | 142 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 14,204 (10.34%) | 14,204 (10.34%) | 0 | 161 | 0 | 90 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |

## Lead-vet integration with current master

Fetched `master` from `/home/rodri/Projects/killer-instinct-gold-n64` and fast-forwarded this worktree from `665ed1f` to `716e1db`, then reapplied the uncommitted T-052 changes. Resolved all five conflicting hunks in main_2FF0.c. No commits were created.

T-051's YAML/BSS ownership and the `size:0x8 allow_addend:True` hint on D_8004A730 are retained. The two BSS definitions are consolidated at the top of main_2FF0.c, in original address order: unsigned `D_8004A730[8]`, then signed `D_8004A738[8]`. C43C indexes both count arrays (callers pass up to seven entries), so A738 cannot remain a scalar. Its eight-byte slot ends at the existing BSS boundary 0x8004A740; no padding object or BSS ownership/layout change was introduced. A730 remains unsigned, preserving 16760's existing definition and codegen.

Removed duplicate externs for these symbols and the two seven-byte-stride tables; there is one definition/declaration for each in the TU. Consolidated C43C's prototype as well. Existing first-element accesses use `[0]` or `[0][0]`. T-052's C43C force-migration hint removals and BF1C literals remain.

Final integration validation: `make clean && make extract && make -j8 all && make progress` passed. The ROM SHA1 remains `ba52e91b44450c548467044b26951353dc491e04`, and main/ovl_7DF8/ovl_7E00 all printed OK with the hashes recorded above. Thus all previously matched code remains identical, including 16760, C43C and A9DC.

Linked ELF symbol checks confirm:

| Symbol | Address | Size |
|---|---|---|
| D_8004A730 | 0x8004A730 | 8 bytes |
| D_8004A738 | 0x8004A738 | 8 bytes |
| func_80016760 | 0x80016760 | 196 bytes |
| func_8001C43C | 0x8001C43C | 248 bytes |
| func_8002A9DC | 0x8002A9DC | 188 bytes |

Retained regenerated overlay undefined-symbol changes: the two removed C43C-owned constant symbols disappear from both `ovl_7DF8.undefined_syms.txt` and `ovl_7E00.undefined_syms.txt`. The main undefined-symbol file needs no additional change. Generated progress documents are retained for this integration run. `git diff --check` passed; no branch commits were made.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 52,848 (16.56%) | 52,848 (16.56%) | 0 | 307 | 0 | 255 | 437 (138,092) |
| boot | 8,468 | 8,108 (95.75%) | 8,108 (95.75%) | 0 | 1 | 0 | 20 | 99 (16,028) |
| main | 173,204 | 30,036 (17.34%) | 30,036 (17.34%) | 0 | 147 | 0 | 143 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 14,704 (10.70%) | 14,704 (10.70%) | 0 | 159 | 0 | 92 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |
