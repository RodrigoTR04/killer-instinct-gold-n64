# T-037: remaining libultra pfs TUs in main (-O2 -mips1)

All of these are libultra 2.0-era Controller Pak code, as T-035 predicted. Every function builds with `-O2 -mips1`. Three of the four TUs now match fully in the ROM (`make` reports the ROM and all 3 images OK).

| TU | Flags | Fully matched | Functions (suggested libultra name) |
|---|---|---|---|
| main_24E70 | -O2 -mips1 | yes | 800347D0 osPfsChecker, 80034DBC corrupted_init (static), 800350A0 corrupted (static), 80035240 __osPfsGetNextPage (static), 80035320 osPfsReadWriteFile, 80035690 osPfsAllocateFile, 80035A84 __osPfsDeclearPage (static), 80035C84 __osClearPage (static) |
| main_26480 | -O2 -mips1 | yes | 80035DE0 osPfsNumFiles |
| main_26860 | -O2 -mips1 | yes | 800361C0 osPfsDeleteFile, 80036440 __osPfsReleasePages, 80036644 __osBlockSum |
| main_265B0 | (none; src unchanged) | no | 80035F10 osPfsFileState: 2 words differ under -mips1 (144 under -mips2) |

main_24E70 holds three libultra source files in one splat TU (pfschecker.c, pfsreadwritefile.c, pfsallocatefile.c). They all use the same flags, so one src file works.

Callee names implied by the matches: 8003BC0C __osCheckId, 8003BA08 __osGetId, 8003BD24 __osPfsRWInode, 8003BFC0 __osPfsSelectBank, 8003C030 __osContRamRead, 8003C3C0 __osContRamWrite, 8003B3E0 __osSumcalc, 80034630 osPfsFindFile, 8003C750 osPfsFreeBlocks.

## Notes on the matching C
- osPfsAllocateFile: everything after the free-space check is nested in `if (file_size_in_pages != 0) { ... } return 5;`. The inode backup is an element-wise `.ipage` copy loop, not a struct assignment. It also needs one unused 4-byte local (`u8 pad[4]`) between `file_size_in_pages` and `inode` to get the frame layout right. The original probably had an extra unused local there.
- __osPfsReleasePages: the lower page bound has to be computed into a temporary (`lim`) with an if/else of two ternaries.
- __osBlockSum: needs `*sum = *sum + __osSumcalc(...)`. Using `+=` swaps the addu operands.
- osPfsChecker: needs `bank != next_page.inode_t.bank`, with the operands in that order.
- No rodata or jump tables are involved.

## main_265B0 (osPfsFileState): not matched
Candidate: `T-037/main_265B0.c`. With `s32 start_bank` (it was u8 in the T-026 draft) and the declaration order chosen by an exhaustive permutation of 7 groups, the register allocation now matches. Only the start_bank spill slot differs: `sw/lw t0,0x34(sp)` in the candidate vs `0x38(sp)` in the ROM. Variable types, block scoping and padding locals don't fix it. Under -O2 -mips2 it is much worse (144 words). src is left unchanged and the T-026 draft is kept, with a pointer added to its header.

## Tools (in this dir)
`sc.sh <file.c> <-mips1|-mips2> func:imageoff ...` compiles a candidate standalone and counts differing words against build/segments/main.bin (jal targets masked; set `V=v` for a side-by-side listing). `perm.py` permutes the declaration block of one function. `var.py` tries text substitutions.
