# T-039: ovl_7DF8 draft follow-up

Worker sol-B14. Worktree: `/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-bf763a8b`. No commits made.

Four matches retained in source; two drafts improved. All other attempted C was restored to GLOBAL_ASM. No previously matched function was edited. No headers, build configuration, status.csv, symbols, ROMs, or main-checkout files were edited.

## Matches and improvements

| Function | Draft directory | Status | Change |
|---|---|---|---|
| func_801CBF8C | T-034 | MATCHED | Move changed assignment after EEPROM read. |
| func_801C8668 | T-021 | MATCHED | Existing draft matches in full build. |
| func_801AF424 | T-025 | MATCHED | Compute matrix pointers at use sites; frame 0x80 and perspNorm at sp+0x7E. |
| func_801B994C | T-029 | MATCHED | Postincrement display-list cursor and use unsigned color-mask expression. |
| func_801CD174 | T-021 | IMPROVED | 2 differing words, +0x2C/+0x48 pointer spill offsets; 124/124 bytes (was 5). |
| func_801B695C | T-029 | IMPROVED | 39 differing words; 268/268 bytes, frame 0x30 versus 0x28 (was 45). |

## Declarations and techniques

New declarations live immediately above their new functions. Added T039GfxF424 and T039Gfx801B994C local display-list types and the extern declarations required by those functions, func_801CBF8C, and func_801C8668. No existing declaration or prototype of another function was changed. In func_801AF424 the pre-existing func_801AF5B8 definition remains untouched; an unprototyped extern declaration is added before the caller. No inline assembly, data definitions, register binding, or padding tricks were introduced. The two improved drafts only reorder local declarations.

Deleted drafts:

- `tools/scratch/nonmatching/T-034/func_801CBF8C.c`
- `tools/scratch/nonmatching/T-021/func_801C8668.c`
- `tools/scratch/nonmatching/T-025/func_801AF424.c`
- `tools/scratch/nonmatching/T-029/func_801B994C.c`

## Attempt details

The original standalone sweep attempted all 178 drafts; 161 compiled in standalone context. Counts below compare corresponding instruction words with actual ELF relocation fields masked; they are screening counts, not asm-differ scores. They do not prove matching relocation targets, rodata, alignment, or equal size. Compile failures were due to standalone context and are not proof that the draft cannot compile in its source file.

Further iterations tested local order, expression spelling, integer width/signedness, loop/cursor form, and float temporaries. Rows noting further iterations received those additional attempts. Unchanged screening-only rows were not rewritten. func_801C8AE0, func_801C8F28, func_801C4D28, func_801C3990, func_801C3580 and func_801C35AC were also checked in full translation units; unresolved C was removed. func_801CCD74 additionally has a conflicting draft integer declaration for the pointer global D_802D3E04; all temporary experiments resolving that conflict were restored.

Skipped for assembly-owned jump tables/rodata: func_801ADCFC, func_801CBCCC, func_801BF720, and func_801BF914. No data ownership changes attempted.

| Function | Source draft directory | Result | Screening / attempt note |
|---|---|---|---|
| func_801AD114 | T-019 | UNCHANGED | 159 relocation-masked differing words in original screen. |
| func_801AD3BC | T-019 | UNCHANGED | 32 relocation-masked differing words in original screen. |
| func_801AD568 | T-019 | UNCHANGED | 128 relocation-masked differing words in original screen. |
| func_801AD7D8 | T-019 | UNCHANGED | 129 relocation-masked differing words in original screen. |
| func_801ADA04 | T-019 | UNCHANGED | 40 relocation-masked differing words in original screen. |
| func_801C3524 | T-021 | UNCHANGED | 14 relocation-masked differing words in original screen. Further iterations did not match. |
| func_801C3580 | T-021 | UNCHANGED | 2 relocation-masked differing words in original screen. Further iterations did not match. |
| func_801C35AC | T-021 | UNCHANGED | 2 relocation-masked differing words in original screen. Further iterations did not match. |
| func_801C4780 | T-021 | UNCHANGED | 19 relocation-masked differing words in original screen. |
| func_801C48E4 | T-021 | UNCHANGED | 46 relocation-masked differing words in original screen. |
| func_801C4BD0 | T-021 | UNCHANGED | 19 relocation-masked differing words in original screen. |
| func_801C4D28 | T-021 | UNCHANGED | 6 relocation-masked differing words in original screen. Further iterations did not match. |
| func_801C4D6C | T-021 | UNCHANGED | 17 relocation-masked differing words in original screen. |
| func_801C4E38 | T-021 | UNCHANGED | Standalone compile failed. |
| func_801C51F8 | T-021 | UNCHANGED | 35 relocation-masked differing words in original screen. |
| func_801C6A80 | T-021 | UNCHANGED | 43 relocation-masked differing words in original screen. |
| func_801C6D40 | T-021 | UNCHANGED | 77 relocation-masked differing words in original screen. |
| func_801C71FC | T-021 | UNCHANGED | 44 relocation-masked differing words in original screen. |
| func_801C72B0 | T-021 | UNCHANGED | 13 relocation-masked differing words in original screen. |
| func_801C780C | T-021 | UNCHANGED | 30 relocation-masked differing words in original screen. |
| func_801C7E98 | T-021 | UNCHANGED | Standalone compile failed. |
| func_801C7F90 | T-021 | UNCHANGED | 17 relocation-masked differing words in original screen. |
| func_801C8004 | T-021 | UNCHANGED | 110 relocation-masked differing words in original screen. |
| func_801C85C0 | T-021 | UNCHANGED | 14 relocation-masked differing words in original screen. |
| func_801C8668 | T-021 | MATCHED | Full ROM and all images verified. |
| func_801C8A38 | T-021 | UNCHANGED | Standalone compile failed. |
| func_801CA784 | T-021 | UNCHANGED | 22 relocation-masked differing words in original screen. |
| func_801CB998 | T-021 | UNCHANGED | 36 relocation-masked differing words in original screen. |
| func_801CBBE0 | T-021 | UNCHANGED | 23 relocation-masked differing words in original screen. |
| func_801CC0CC | T-021 | UNCHANGED | 42 relocation-masked differing words in original screen. |
| func_801CC1A4 | T-021 | UNCHANGED | 22 relocation-masked differing words in original screen. |
| func_801CC2C8 | T-021 | UNCHANGED | 25 relocation-masked differing words in original screen. |
| func_801CC3BC | T-021 | UNCHANGED | 101 relocation-masked differing words in original screen. |
| func_801CC668 | T-021 | UNCHANGED | Standalone compile failed. |
| func_801CC878 | T-021 | UNCHANGED | Standalone compile failed. |
| func_801CC908 | T-021 | UNCHANGED | 15 relocation-masked differing words in original screen. |
| func_801CCD74 | T-021 | UNCHANGED | 7 relocation-masked differing words in original screen. Further iterations did not match. |
| func_801CCDE8 | T-021 | UNCHANGED | 35 relocation-masked differing words in original screen. |
| func_801CD078 | T-021 | UNCHANGED | Standalone compile failed. |
| func_801CD100 | T-021 | UNCHANGED | 13 relocation-masked differing words in original screen. |
| func_801CD174 | T-021 | IMPROVED | 2 differing words, +0x2C/+0x48 pointer spill offsets; 124/124 bytes (was 5). |
| func_801BA088 | T-023 | UNCHANGED | 132 relocation-masked differing words in original screen. |
| func_801BA280 | T-023 | UNCHANGED | 131 relocation-masked differing words in original screen. |
| func_801BA470 | T-023 | UNCHANGED | 133 relocation-masked differing words in original screen. |
| func_801BA674 | T-023 | UNCHANGED | 136 relocation-masked differing words in original screen. |
| func_801BA884 | T-023 | UNCHANGED | 85 relocation-masked differing words in original screen. |
| func_801BAA78 | T-023 | UNCHANGED | 223 relocation-masked differing words in original screen. |
| func_801BADEC | T-023 | UNCHANGED | 144 relocation-masked differing words in original screen. |
| func_801BB024 | T-023 | UNCHANGED | 148 relocation-masked differing words in original screen. |
| func_801BB258 | T-023 | UNCHANGED | 138 relocation-masked differing words in original screen. |
| func_801BB464 | T-023 | UNCHANGED | 78 relocation-masked differing words in original screen. |
| func_801BB594 | T-023 | UNCHANGED | 140 relocation-masked differing words in original screen. |
| func_801BB7B4 | T-023 | UNCHANGED | 220 relocation-masked differing words in original screen. |
| func_801BBB60 | T-023 | UNCHANGED | 73 relocation-masked differing words in original screen. |
| func_801BBC84 | T-023 | UNCHANGED | 110 relocation-masked differing words in original screen. |
| func_801BBE88 | T-023 | UNCHANGED | 183 relocation-masked differing words in original screen. |
| func_801BC1B0 | T-023 | UNCHANGED | 580 relocation-masked differing words in original screen. |
| func_801BCB70 | T-023 | UNCHANGED | 416 relocation-masked differing words in original screen. |
| func_801BD200 | T-023 | UNCHANGED | 14 relocation-masked differing words in original screen. |
| func_801BD270 | T-023 | UNCHANGED | 21 relocation-masked differing words in original screen. |
| func_801BD3FC | T-023 | UNCHANGED | 110 relocation-masked differing words in original screen. |
| func_801BD640 | T-023 | UNCHANGED | 265 relocation-masked differing words in original screen. |
| func_801BDA6C | T-023 | UNCHANGED | 348 relocation-masked differing words in original screen. |
| func_801BDF94 | T-023 | UNCHANGED | 406 relocation-masked differing words in original screen. |
| func_801BE540 | T-023 | UNCHANGED | 67 relocation-masked differing words in original screen. |
| func_801BE660 | T-023 | UNCHANGED | 41 relocation-masked differing words in original screen. |
| func_801BE790 | T-023 | UNCHANGED | 75 relocation-masked differing words in original screen. |
| func_801BE910 | T-023 | UNCHANGED | 96 relocation-masked differing words in original screen. |
| func_801BEA74 | T-023 | UNCHANGED | 154 relocation-masked differing words in original screen. |
| func_801BED0C | T-023 | UNCHANGED | 86 relocation-masked differing words in original screen. |
| func_801BEEA4 | T-023 | UNCHANGED | 90 relocation-masked differing words in original screen. |
| func_801BEFFC | T-023 | UNCHANGED | 6 relocation-masked differing words in original screen. Further iterations did not match. |
| func_801BF0E8 | T-023 | UNCHANGED | 32 relocation-masked differing words in original screen. |
| func_801BF190 | T-023 | UNCHANGED | 310 relocation-masked differing words in original screen. |
| func_801BF678 | T-023 | UNCHANGED | 19 relocation-masked differing words in original screen. |
| func_801BF720 | T-023 | UNCHANGED | 2 relocation-masked differing words in original screen. Skipped: rodata ownership. |
| func_801BF788 | T-023 | UNCHANGED | 44 relocation-masked differing words in original screen. |
| func_801BF850 | T-023 | UNCHANGED | 4 relocation-masked differing words in original screen. Further iterations did not match. |
| func_801BF914 | T-023 | UNCHANGED | 2 relocation-masked differing words in original screen. Skipped: rodata ownership. |
| func_801BF988 | T-023 | UNCHANGED | 17 relocation-masked differing words in original screen. |
| func_801BFA40 | T-023 | UNCHANGED | 4 relocation-masked differing words in original screen. Further iterations did not match. |
| func_801BFB40 | T-023 | UNCHANGED | 51 relocation-masked differing words in original screen. |
| func_801BFCBC | T-023 | UNCHANGED | 520 relocation-masked differing words in original screen. |
| func_801C0610 | T-023 | UNCHANGED | 72 relocation-masked differing words in original screen. |
| func_801C0800 | T-023 | UNCHANGED | 29 relocation-masked differing words in original screen. |
| func_801C08F8 | T-023 | UNCHANGED | 560 relocation-masked differing words in original screen. |
| func_801C11F0 | T-023 | UNCHANGED | 123 relocation-masked differing words in original screen. |
| func_801C1434 | T-023 | UNCHANGED | 176 relocation-masked differing words in original screen. |
| func_801C1704 | T-023 | UNCHANGED | 43 relocation-masked differing words in original screen. |
| func_801C17D0 | T-023 | UNCHANGED | 95 relocation-masked differing words in original screen. |
| func_801C1990 | T-023 | UNCHANGED | 137 relocation-masked differing words in original screen. |
| func_801C1C34 | T-023 | UNCHANGED | 310 relocation-masked differing words in original screen. |
| func_801ADEA0 | T-025 | UNCHANGED | 1349 relocation-masked differing words in original screen. |
| func_801AF424 | T-025 | MATCHED | Full ROM and all images verified. |
| func_801AF68C | T-025 | UNCHANGED | 227 relocation-masked differing words in original screen. |
| func_801AFAA4 | T-025 | UNCHANGED | 286 relocation-masked differing words in original screen. |
| func_801AFFAC | T-025 | UNCHANGED | 140 relocation-masked differing words in original screen. |
| func_801B01EC | T-025 | UNCHANGED | 210 relocation-masked differing words in original screen. |
| func_801B0520 | T-025 | UNCHANGED | 36 relocation-masked differing words in original screen. |
| func_801B0668 | T-025 | UNCHANGED | 248 relocation-masked differing words in original screen. |
| func_801B0A40 | T-025 | UNCHANGED | 168 relocation-masked differing words in original screen. |
| func_801B0CDC | T-025 | UNCHANGED | 301 relocation-masked differing words in original screen. |
| func_801B1210 | T-025 | UNCHANGED | 42 relocation-masked differing words in original screen. |
| func_801B132C | T-025 | UNCHANGED | 296 relocation-masked differing words in original screen. |
| func_801B17BC | T-025 | UNCHANGED | 26 relocation-masked differing words in original screen. |
| func_801B18BC | T-025 | UNCHANGED | 72 relocation-masked differing words in original screen. |
| func_801B1A7C | T-025 | UNCHANGED | 167 relocation-masked differing words in original screen. |
| func_801B1DE4 | T-025 | UNCHANGED | 138 relocation-masked differing words in original screen. |
| func_801B2010 | T-025 | UNCHANGED | 100 relocation-masked differing words in original screen. |
| func_801B21B4 | T-025 | UNCHANGED | 101 relocation-masked differing words in original screen. |
| func_801B2358 | T-025 | UNCHANGED | 101 relocation-masked differing words in original screen. |
| func_801B24FC | T-025 | UNCHANGED | 101 relocation-masked differing words in original screen. |
| func_801B26A0 | T-025 | UNCHANGED | 101 relocation-masked differing words in original screen. |
| func_801B2844 | T-025 | UNCHANGED | 101 relocation-masked differing words in original screen. |
| func_801B29E8 | T-025 | UNCHANGED | 101 relocation-masked differing words in original screen. |
| func_801B2B8C | T-025 | UNCHANGED | 164 relocation-masked differing words in original screen. |
| func_801B2EF4 | T-025 | UNCHANGED | 98 relocation-masked differing words in original screen. |
| func_801B310C | T-025 | UNCHANGED | 98 relocation-masked differing words in original screen. |
| func_801B3324 | T-025 | UNCHANGED | 98 relocation-masked differing words in original screen. |
| func_801B353C | T-025 | UNCHANGED | 98 relocation-masked differing words in original screen. |
| func_801B3754 | T-025 | UNCHANGED | 98 relocation-masked differing words in original screen. |
| func_801B396C | T-025 | UNCHANGED | 98 relocation-masked differing words in original screen. |
| func_801B3B84 | T-025 | UNCHANGED | 102 relocation-masked differing words in original screen. |
| func_801B3DB0 | T-025 | UNCHANGED | 273 relocation-masked differing words in original screen. |
| func_801B43A8 | T-029 | UNCHANGED | 42 relocation-masked differing words in original screen. |
| func_801B446C | T-029 | UNCHANGED | Standalone compile failed. |
| func_801B4590 | T-029 | UNCHANGED | Standalone compile failed. Further iterations did not match. |
| func_801B465C | T-029 | UNCHANGED | Standalone compile failed. |
| func_801B47A4 | T-029 | UNCHANGED | Standalone compile failed. |
| func_801B5534 | T-029 | UNCHANGED | 32 relocation-masked differing words in original screen. |
| func_801B5650 | T-029 | UNCHANGED | Standalone compile failed. |
| func_801B5DCC | T-029 | UNCHANGED | Standalone compile failed. |
| func_801B6528 | T-029 | UNCHANGED | Standalone compile failed. Further iterations did not match. |
| func_801B677C | T-029 | UNCHANGED | 117 relocation-masked differing words in original screen. |
| func_801B695C | T-029 | IMPROVED | 39 differing words; 268/268 bytes, frame 0x30 versus 0x28 (was 45). |
| func_801B6A68 | T-029 | UNCHANGED | 75 relocation-masked differing words in original screen. |
| func_801B6BD8 | T-029 | UNCHANGED | 153 relocation-masked differing words in original screen. |
| func_801B6E4C | T-029 | UNCHANGED | Standalone compile failed. |
| func_801B849C | T-029 | UNCHANGED | 1267 relocation-masked differing words in original screen. |
| func_801B994C | T-029 | MATCHED | Full ROM and all images verified. |
| func_801B9A04 | T-029 | UNCHANGED | Standalone compile failed. |
| func_801C224C | T-030 | UNCHANGED | 89 relocation-masked differing words in original screen. |
| func_801C23C0 | T-030 | UNCHANGED | 430 relocation-masked differing words in original screen. |
| func_801C2ADC | T-030 | UNCHANGED | 72 relocation-masked differing words in original screen. |
| func_801C2D34 | T-030 | UNCHANGED | 119 relocation-masked differing words in original screen. |
| func_801C2F5C | T-030 | UNCHANGED | 128 relocation-masked differing words in original screen. |
| func_801C317C | T-030 | UNCHANGED | 226 relocation-masked differing words in original screen. |
| func_801C35D8 | T-030 | UNCHANGED | 65 relocation-masked differing words in original screen. |
| func_801C3758 | T-030 | UNCHANGED | 36 relocation-masked differing words in original screen. |
| func_801C3990 | T-030 | UNCHANGED | 7 relocation-masked differing words in original screen. Further iterations did not match. |
| func_801C3AA0 | T-030 | UNCHANGED | 201 relocation-masked differing words in original screen. |
| func_801C3E40 | T-030 | UNCHANGED | 95 relocation-masked differing words in original screen. |
| func_801C407C | T-030 | UNCHANGED | 76 relocation-masked differing words in original screen. |
| func_801C4240 | T-030 | UNCHANGED | 326 relocation-masked differing words in original screen. |
| func_801C47E0 | T-030 | UNCHANGED | 45 relocation-masked differing words in original screen. |
| func_801C49A8 | T-030 | UNCHANGED | 88 relocation-masked differing words in original screen. |
| func_801C5064 | T-030 | UNCHANGED | 95 relocation-masked differing words in original screen. |
| func_801C5298 | T-030 | UNCHANGED | 732 relocation-masked differing words in original screen. |
| func_801C5E74 | T-030 | UNCHANGED | 557 relocation-masked differing words in original screen. |
| func_801C67CC | T-030 | UNCHANGED | 171 relocation-masked differing words in original screen. |
| func_801C7310 | T-030 | UNCHANGED | 316 relocation-masked differing words in original screen. |
| func_801C7998 | T-030 | UNCHANGED | 60 relocation-masked differing words in original screen. |
| func_801C7A98 | T-030 | UNCHANGED | 14 relocation-masked differing words in original screen. Further iterations did not match. |
| func_801C7CD0 | T-030 | UNCHANGED | 85 relocation-masked differing words in original screen. |
| func_801ABB20 | T-034 | UNCHANGED | 641 relocation-masked differing words in original screen. |
| func_801ACB1C | T-034 | UNCHANGED | 176 relocation-masked differing words in original screen. |
| func_801ADCFC | T-034 | UNCHANGED | 0 relocation-masked differing words in original screen. Skipped: rodata ownership. |
| func_801C80F0 | T-034 | UNCHANGED | Standalone compile failed. |
| func_801C8AE0 | T-034 | UNCHANGED | 21 relocation-masked differing words in original screen. Further iterations did not match. |
| func_801C8C24 | T-034 | UNCHANGED | 19 relocation-masked differing words in original screen. |
| func_801C8F28 | T-034 | UNCHANGED | 4 relocation-masked differing words in original screen. Further iterations did not match. |
| func_801C90D4 | T-034 | UNCHANGED | 217 relocation-masked differing words in original screen. |
| func_801C9698 | T-034 | UNCHANGED | 136 relocation-masked differing words in original screen. |
| func_801C9B14 | T-034 | UNCHANGED | 619 relocation-masked differing words in original screen. |
| func_801CAA00 | T-034 | UNCHANGED | Standalone compile failed. |
| func_801CBCCC | T-034 | UNCHANGED | 15 relocation-masked differing words in original screen. Skipped: rodata ownership. |
| func_801CBF8C | T-034 | MATCHED | Full ROM and all images verified. |
| func_801CD1F0 | T-034 | UNCHANGED | 105 relocation-masked differing words in original screen. |

## Final validation

`make clean && make extract && make -j4 && make progress` passed. The rebuilt ROM SHA1 is `ba52e91b44450c548467044b26951353dc491e04`; main, ovl_7DF8 and ovl_7E00 are all byte-identical. All four retained functions report asm-differ CURRENT (0). Total T4 increased 168 → 172, and ovl_7DF8 T4 increased 73 → 77. `git diff --check` passed. Generated docs/functions.csv and docs/progress.html were restored after recording the table below.

| Area | Eligible bytes | M1 bytes (%) | M2 bytes (%) | T1 fns | T2 fns | T3 fns | T4 fns | Excluded fns (bytes) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Total | 319,544 | 27,768 (8.69%) | 27,768 (8.69%) | 28 | 369 | 0 | 172 | 430 (137,648) |
| boot | 8,468 | 0 (0.00%) | 0 (0.00%) | 21 | 0 | 0 | 0 | 99 (16,028) |
| main | 173,204 | 16,488 (9.52%) | 16,488 (9.52%) | 0 | 195 | 0 | 95 | 169 (34,392) |
| ovl_7DF8 | 137,428 | 11,280 (8.21%) | 11,280 (8.21%) | 0 | 174 | 0 | 77 | 0 (0) |
| ovl_7E00 | 444 | 0 (0.00%) | 0 (0.00%) | 7 | 0 | 0 | 0 | 162 (87,228) |
