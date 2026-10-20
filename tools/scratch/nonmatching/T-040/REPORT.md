# T-040 (opus-3): main T2 near-miss drafts

Worktree: /home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-b057ab66 (base 13b3eeb). No commits.

Result: **23 functions matched** (main T4 110 → 133). 6 drafts improved; the rest were checked and left unchanged.
Final `make clean && make extract && make && make progress` passed: the ROM and all 3 images are OK. No Makefile changes.

## Matched (C in src, draft deleted)
| Function | Draft dir | TU | Key change |
|---|---|---|---|
| func_8001C370 | T-022 | main_2FF0 | plain nested `for` loops with indexing |
| func_8001CF1C | T-022 | main_2FF0 | plain `for` loops, `i * 0x2000` |
| func_80011FC4 | T-020 | main | `(buttons = arg0->buttons) & map[3]` operand order |
| func_80013BE0 | T-020 | main_2FF0 | `/ 2` (int) instead of `/ 2.0f`, so it isn't folded to `* 0.5f` |
| func_80012100 | T-020 | main | index the global array directly, no pointer local (spill slot) |
| func_800126D0 | T-020 | main | indexed `for` loop |
| func_8002A1A0 | T-024 | main_1A7F0 | globals declared as `u8 [][0x800]` |
| func_8002F3DC | T-024 | main_1EB40 | `for (n = 0; p; p = p->next) n++` |
| func_8002F31C | T-024 | main_1EB40 | libultra alEvtqFlushType style `thisItem`/`nextItem` alias locals |
| func_8002A40C | T-024 | main_1A880 | `u8 *src`, then `src += 8` |
| func_8002970C | T-024 | main_18440 | array access without a pointer local (spill slot) |
| func_8002A150 | T-024 | main_1A7F0 | `s32 z = 0;` shared by the store and the call arg (odd but needed) |
| func_8002B500 | T-024 | main_1BBA0 | `&D_800684B8[i]` (OSContPad array) |
| func_8002B710 | T-024 | main_1BBA0 | `for (i < 4) if (pad[i].errno == 0) mask \|= 1 << i` |
| func_8002B3A8 | T-024 | main_1B230 | audiomgr `__amDmaNew` (used = 0, then free, then initialized) |
| func_8002B3E0 | T-024 | main_1B230 | audiomgr `__clearAudioDMA` verbatim (uninitialised iomsg) |
| func_8002E680 | T-024 | main_1EB40 | u16 event type; `T040NextEvent *next` pointer local declared first |
| func_80028600 | T-024 | main_18440 | `for (i < 3) D_80061CC8[i] = 0.0f` |
| func_8002FFDC | T-024 | main_20220 | all params s32 (no s16 sign-extension) |
| func_8002F2B0 | T-024 | main_1EB40 | 16-byte event; f32 local copied with `*(s32 *)&pitch` |
| func_8002F8F8 | T-024 | main_1EB40 | s16 type, `flags &= ~0x10` |
| func_8002E08C | T-024 | main_1BE80 | the real func_8002DDD4 signature (x, z, y, &a, &b) |
| func_8002A254 | T-024 | main_1A880 | two indexed loops, stores swapped in the first one |

## Declarations changed outside the target function (build OK)
- main_1A880.c, func_8002A40C (matched this task): its extern line was split into `extern s32 D_80066188[], D_800665A0[], D_80065C80[]; extern u8 D_80066080[];` so it agrees with func_8002A254.
- main_1BBA0.c, func_8002B500 (matched this task): added `typedef T040ContPad`, declared `extern T040ContPad D_800684B8[4]` and used `&D_800684B8[i]`. This lets func_8002B710 share the declaration.
- main_1B230.c: the T024DmaBuffer/T024DmaPool typedefs and `extern D_80068158` moved up to func_8002B3A8, which comes before func_8002B3E0. Both are new matches.
- No changes to functions matched before this task.

## Improved (draft updated)
| Function | Dir | Before → after | Remaining |
|---|---|---|---|
| func_8001CBCC | T-022 | 16 → 2 | rodata-blocked, see below; the stack-slot layout is solved |
| func_8002A004 | T-024 | 20 → 2 | rodata-blocked, see below |
| func_8002A1E0 | T-024 | 6 → 3 | zero store scheduled before the loop-constant setup |
| func_800281C4 | T-024 | 11 → 4 | addiu order within the if/else arms |
| func_80013C84 | T-020 | 3 → 0 standalone | matches with the prototype `boot_dma(u32, u32, u32)`, but main_2FF0.c prototypes it with pointer args for matched callers. Needs a lead decision on that shared prototype |

## Rodata-blocked (finding)
The "lwc1 const before mtc1 a1" swap in func_8001CBCC and func_8002A004, and the constant-load order in func_80018E88, come from **float literals**. Using `0.017453292f`, or `359.0f`/`0.2`, instead of the extern D_ constants matches standalone. These literals live in the TU's .rodata, which the data asm owns, so the functions can't move to C until rodata ownership changes. func_80018E88: header updated, code unchanged.

## Checked, unchanged
- func_8001BDE0 (15): FP callee-saved register assignment (f20/f22/f24) doesn't move with declaration order or with locals vs globals.
- func_8002B7E0, func_8002B95C, func_8002B91C, func_8002DCC8, func_8002B1EC (2–4 words): a single prologue/home-store instruction is scheduled one slot off. IDO 7.1, -O1/-O3, -g3 and dropping -r4300_mul don't change it. B1EC needs separate `lui` for the load and the store; making it volatile doesn't help.
- func_8002AA98, func_8002AAEC (10, 80/84 bytes): an extra `move a1,t0` after a double sign-extend. Not solved.
- func_800244F0 (25): register/spill shape not solved.
- func_80016760: the original reuses `$at` across D_8004A730/1/2 stores, which happens when the array is defined in the TU. Data-ownership-blocked.
- func_80014250: same boot_dma prototype issue as 13C84. Not fully resolved (18 standalone with the u32 prototype).
- osPfsFileState (T-037/main_265B0.c): an exhaustive search over all 20,160 declaration orders still leaves the same 2 words (start_bank spill 0x34 vs 0x38). Unchanged.

## Skipped
- func_800414F8, func_80041978, func_800419C8 (T-035): libaudio IPA -O3 temp-register cycling (t6–t9 only). The libultra `__readVarLen` source gives 16 words under -O2.

## Tooling notes
Standalone compile and compare, with HI16/LO16/26 relocation fields masked, takes about 0.1 s per try, versus about 35 s for an in-tree link. This made permutation searches cheap. Writing plain, natural C (indexed loops, the libultra/demo audiomgr source) fixed most near-misses better than tuning the m2c-style drafts.
