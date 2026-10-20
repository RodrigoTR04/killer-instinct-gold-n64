# T-044 — ovl_7DF8 polish round 2

Worker: sol-C17. No commits; changes are left for lead review.

## Results

Attempted 24 functions, concentrating on the smallest remaining T-039 screen counts: **5 MATCHED (720 bytes), 7 improved drafts, 12 unchanged**. The four T-043-owned functions were not touched. No main/boot/ovl_7E00 source, YAML, Makefile, or status.csv changes.

Counts below use actual ELF relocation masks, like T-039. They compare aligned instruction words and report size separately; relocation-masked zero is only a screening result. The five integrated functions were additionally verified in the complete linked overlay and ROM. `compare.py` reproduces standalone draft counts using the normal IDO 5.3 `-O2 -mips2` flags. Original screening counts can differ from a fresh comparison because T-039 retained improved drafts and some drafts have different lengths.

| Function | Draft directory | Result | Attempt / remaining issue |
|---|---|---|---|
| func_801CD174 | T-021 | MATCHED | Local struct groups the pointer and output value, putting the pointer at sp+0x1C and output at sp+0x20. Tested declaration permutations, padding, aggregate layouts and pointer lifetimes. 124 bytes. |
| func_801C3580 | T-021 | UNCHANGED | Tested callee return types, parameter widths, explicit returns and argument expressions; two scheduling words remain. |
| func_801C35AC | T-021 | UNCHANGED | Same wrapper experiments; two scheduling words remain. |
| func_801C8F28 | T-034 | UNCHANGED | Tested index/value widths, signed 64-bit storage and output-address forms; four register operands remain. |
| func_801BF850 | T-023 | UNCHANGED | Split nested calls, changed loop termination/address expressions and tried one cursor; four words remain. |
| func_801BFA40 | T-023 | UNCHANGED | Same call/cursor/address experiments; four words remain, plus original trailing alignment. |
| func_801C4D28 | T-021 | UNCHANGED | Load/declaration permutations, whole-vector assignment and float widths did not resolve six float-register operands. |
| func_801BEFFC | T-023 | MATCHED | Index the two score arrays with the loop counter instead of maintaining two pointer cursors. Actual array declarations replace scalar-address indexing. 236 bytes. |
| func_801C3990 | T-030 | UNCHANGED | Tested zero initialization timing, literal forms and float widths; did not resolve float-register selection. No rodata ownership changes. |
| func_801CCD74 | T-021 | IMPROVED 4 words | Was 7; chained zero assignments improve bases/registers. Draft now consistently uses pointer globals, pointer local and pointer-to-pointer output, resolving its previous D_802D3E04 integer declaration conflict. 116/116 bytes. |
| func_801CD100 | T-021 | MATCHED | Indexed descending for loop replaces the separate pointer cursor/do loop; also tested conditions, widths and update ordering. 116 bytes. |
| func_801C72B0 | T-021 | MATCHED | Signed byte initialized to -1, with chained zero assignments. The chain must be D_802956F8 = D_802956FC = D_80295700 = 0; reverse spelling passes relocation masking but fails linked address checks. 96 bytes. |
| func_801BD200 | T-023 | UNCHANGED | Tried return widths, conditional minimum, chained flag writes and integer return; no retained improvement. |
| func_801C3524 | T-021 | IMPROVED 8 words | Was 14; postincrement the display-list pointer directly. Tried constant locals, command-store order, casts and separate command locals; remaining temporary allocation/address scheduling. 92/92 bytes. |
| func_801C7A98 | T-030 | UNCHANGED | Tested maximum/level widths and scalar versus struct maximum; 14 words remain. |
| func_801CC908 | T-021 | IMPROVED 13 words | Was 15; declare D_802927A4 as a pointer table and index it, replacing byte-load-to-pointer conversion. Tried callee return widths and removing dead stores. 424/424 bytes. |
| func_801C85C0 | T-021 | IMPROVED 9 words | Was 14; reorder cursor initialization. Tested all 24 initialization permutations and indexed writes. 168/168 bytes. |
| func_801C4D6C | T-021 | IMPROVED 17 words | s16 local counter fixes length to 204/204 bytes (old draft 196/204). Aligned-word differences remain 17; old draft also lacked two words. Tried widths and direct global counting. |
| func_801C7F90 | T-021 | IMPROVED 16 words | Was 17; chain the initial byte clears. Tried loop forms and index widths. 116/116 bytes. |
| func_801BF988 | T-023 | UNCHANGED | Tested packed/score widths, cursor initialization order and indexed input; 17 words remain. |
| func_801C4780 | T-021 | UNCHANGED | Tested aggregate alignment types, plain struct and packed integer argument representation; no improvement. |
| func_801C4BD0 | T-021 | MATCHED | Typed func_801C47E0(u32, u32, void *, u32) fixes the reloads/call scheduling. K&R u8 parameter definition preserves existing unprototyped callers in this TU; use existing u8 declaration for D_802D399D. 148 bytes. |
| func_801C8C24 | T-034 | UNCHANGED | Tried explicit nibble pointers, loaded scalar bytes and manual unrolling; no retained improvement. |
| func_801B695C | T-029 | IMPROVED 4 words | Was 39; reuse the loaded frame index as destination offset, inline the bank toggle and spell the frame stride as (offset * 3 << 5) + frames. All instructions/registers/spill slots now agree except the 0x30 frame versus 0x28 and its parameter reload offsets. Tested local permutations, types, expression order, aggregate layouts, variable reuse and callee return types. 268/268 bytes. |

No inline assembly, register variables, compiler flags, or data ownership changes were used.

## Deleted drafts

- tools/scratch/nonmatching/T-021/func_801CD174.c
- tools/scratch/nonmatching/T-021/func_801CD100.c
- tools/scratch/nonmatching/T-021/func_801C72B0.c
- tools/scratch/nonmatching/T-021/func_801C4BD0.c
- tools/scratch/nonmatching/T-023/func_801BEFFC.c

## Validation

`make clean && make extract && make -j4 all && make progress` passed. ROM SHA1:
`ba52e91b44450c548467044b26951353dc491e04`. main, ovl_7DF8 and ovl_7E00
are all byte-identical. `git diff --check` passed. Generated docs/functions.csv
and docs/progress.html were restored after recording this table; status.csv is
untouched. Total T4 increased 202 → 207; ovl_7DF8 T4 increased 77 → 82.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,100 | 39,228 (12.29%) | 39,228 (12.29%) | 0 | 355 | 0 | 207 | 437 (138,092) |
| boot | 8,468 | 2,812 (33.21%) | 2,812 (33.21%) | 0 | 6 | 0 | 15 | 99 (16,028) |
| main | 173,204 | 24,416 (14.10%) | 24,416 (14.10%) | 0 | 180 | 0 | 110 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 12,000 (8.73%) | 12,000 (8.73%) | 0 | 169 | 0 | 82 | 0 (0) |
| ovl_7E00 | 0 | 0 (n/a) | 0 (n/a) | 0 | 0 | 0 | 0 | 169 (87,672) |

Local setup uses symlinks to the main checkout for baserom.us.z64, ROMs/,
.venv and tools/ext. No copyrighted ROM content was copied into tracked files.

