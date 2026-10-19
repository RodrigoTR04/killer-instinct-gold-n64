# T-035 (opus-2)

Worktree: /home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-bf14a84c (base e6405c7). No commits.

## Key finding: libultra pfs objects are built with `-O2 -mips1`
These files are libultra Controller Pak code: main_24820, main_24B50, main_2BA80, main_2CA60 and main_2CDF0. They match exactly with IDO 5.3 `-O2 -mips1`. The tell is the load-delay `nop`s. I wrote complete C for all five files (`T-035/main_*.c`, 19 functions). For each file I put the C into src/, deleted its `.o`, rebuilt only that object with
`make build/src/main/<f>.c.o CFLAGS="-c -G 0 -non_shared -Xcpluscomm -Wab,-r4300_mul -O2 -mips1 -32"`,
then ran `make`. The ROM and all 3 images were OK each time. Afterwards I restored src (GLOBAL_ASM), because a normal build uses -mips2.
**Lead action:** add per-object `-mips1` CFLAGS overrides in the Makefile for those 5 objects. Then drop in the files.
main_265B0, main_26480, main_26860 and main_24E70 are probably the same libultra -mips1 code (osPfsNumFiles in main_26480 already matches standalone).

## Libaudio files are built with interprocedural -O3
The libaudio functions in main_30A90/319D0/321A0/2D860/28060/292E0 have nonstandard ABIs:
- they use callee-saved registers without saving them
- they pass ints in a0 next to f12
- they only use t6-t9
This is a ucode -O3 IPA build. A per-file -O2 or -O3 compile doesn't reproduce it, because -O3 on a single file inlines the static helpers.

## Part A
| Function | Status | Notes |
|---|---|---|
| func_800414F0 | MATCHED | empty function (kept in src/main/main_319D0.c) |
| func_800414F8 | DRAFT | readVarLen; temp-register allocation (IPA build) |
| func_80041978 | DRAFT | read32; load order/temps |
| func_800419C8 | DRAFT | read16; 6 temp-register words |
| func_80040A4C | DRAFT | _getVol; args in a0/a1/a2 next to f12 (IPA ABI), ~20 words |
| func_800405E4 | DRAFT | _getRate; uses unsaved s0-s2/f20/f22, nonstandard args; can't be produced at -O2 |
| func_800407B4 | DRAFT | _pullSubFrame; same IPA register ABI |
| func_80042198 | DRAFT | alFxParamHdl; jump table + float consts are rodata owned by data asm; bounds-check/reg diffs |

## Part B (T-026 drafts)
Matched standalone byte-for-byte under -O2 -mips1 (relocs aside), and verified per-file in the full ROM as described above:
3B3E0 3B45C 3B558 3B8A4 3BA08 3BC0C 3BD24 3BFC0 3C030 3C25C (main_2BA80), 34180 3431C 343F4 (main_24820), 344B0 34554 34630 (main_24B50), 3C3C0 3C5E4 (main_2CA60), 3C750 (main_2CDF0).
Also matched standalone (-mips1), with no full-ROM test: 35DE0 (osPfsNumFiles, main_26480).
Improved: 35F10 (osPfsFileState). Only s-register permutation and one spill slot remain.
None of these matches can live in src under the current -mips2 flags, so I didn't delete any drafts. Each draft header records its -mips1 status.
Unusual idioms: the libultra cast-lvalue `*((T *)ptr)++` (3431C, cfe warning 665); `*(u8 *)((u32)id + k)` (3BA08); a 40-byte read-format struct with a pad byte (3C030/3C3C0).
Skipped as non-producible: 32738/326F0 (native 64-bit daddiu/sd), 32750/3278C/32600/32670 (handwritten asm-style decoder), 31050/3FB20/37A6C (private register ABI fragments), 37A30/38EA4/3D71C (libaudio IPA ABI; 3D71C tried, no gain). Unchanged: everything else.
