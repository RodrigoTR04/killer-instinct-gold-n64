# T-092 draft screen

IDO 5.3 -O2 -mips2 through asm-processor. Full owning TU first; prefix fallback removes other GLOBAL_ASM stubs and omits declarations after the target. Relocation masks come only from ELF REL entries. Size differences count as differing words. Declaration fallback keeps TU types/prototypes, omits preceding bodies, and gives explicit draft declarations precedence. Prefix/declaration scores require reconciliation before integration.

| Function | Compiled B | Original B | Differing words | Context | Draft |
|---|---:|---:|---:|---|---|
| func_8002AA98 | 84 | 84 | 2 | full | tools/scratch/nonmatching/T-024/func_8002AA98.c |
| func_8002AAEC | 84 | 84 | 2 | full | tools/scratch/nonmatching/T-024/func_8002AAEC.c |
| func_8002F6F4 | 516 | 516 | 2 | full | tools/scratch/nonmatching/T-024/func_8002F6F4.c |
| func_801BF720 | 104 | 104 | 2 | prefix | tools/scratch/nonmatching/T-023/func_801BF720.c |
| func_801BF914 | 116 | 116 | 2 | full | tools/scratch/nonmatching/T-023/func_801BF914.c |
| func_801C4E38 | 556 | 556 | 2 | declarations | tools/scratch/nonmatching/T-021/func_801C4E38.c |
| func_801B6528 | 596 | 596 | 3 | full | tools/scratch/nonmatching/T-029/func_801B6528.c |
| func_800281C4 | 108 | 108 | 4 | full | tools/scratch/nonmatching/T-024/func_800281C4.c |
| func_801B695C | 268 | 268 | 4 | prefix | tools/scratch/nonmatching/T-029/func_801B695C.c |
| func_801C5064 | 404 | 404 | 4 | declarations | tools/scratch/nonmatching/T-030/func_801C5064.c |
| func_801C8F28 | 428 | 428 | 4 | declarations | tools/scratch/nonmatching/T-034/func_801C8F28.c |
| func_801CC908 | 424 | 424 | 4 | full | tools/scratch/nonmatching/T-021/func_801CC908.c |
| func_801CCD74 | 116 | 116 | 4 | prefix | tools/scratch/nonmatching/T-021/func_801CCD74.c |
| func_801C85C0 | 168 | 168 | 5 | declarations | tools/scratch/nonmatching/T-021/func_801C85C0.c |
| func_801C3524 | 92 | 92 | 6 | full | tools/scratch/nonmatching/T-021/func_801C3524.c |
| func_801C7998 | 256 | 256 | 6 | full | tools/scratch/nonmatching/T-030/func_801C7998.c |
| func_801C3990 | 272 | 272 | 7 | full | tools/scratch/nonmatching/T-030/func_801C3990.c |
| func_80017378 | 1752 | 1752 | 8 | full | tools/scratch/nonmatching/T-033/func_80017378.c |
| func_801C6A80 | 292 | 292 | 8 | full | tools/scratch/nonmatching/T-021/func_801C6A80.c |
| func_8001BDE0 | 316 | 316 | 13 | full | tools/scratch/nonmatching/T-022/func_8001BDE0.c |
| func_8002F45C | 404 | 404 | 13 | full | tools/scratch/nonmatching/T-024/func_8002F45C.c |
| func_801B2010 | 420 | 420 | 14 | full | tools/scratch/nonmatching/T-025/func_801B2010.c |
| func_801B21B4 | 420 | 420 | 14 | full | tools/scratch/nonmatching/T-025/func_801B21B4.c |
| func_801B2358 | 420 | 420 | 14 | full | tools/scratch/nonmatching/T-025/func_801B2358.c |
| func_801B24FC | 420 | 420 | 14 | full | tools/scratch/nonmatching/T-025/func_801B24FC.c |
| func_801B26A0 | 420 | 420 | 14 | full | tools/scratch/nonmatching/T-025/func_801B26A0.c |
| func_801B2844 | 420 | 420 | 14 | full | tools/scratch/nonmatching/T-025/func_801B2844.c |
| func_801B29E8 | 420 | 420 | 14 | full | tools/scratch/nonmatching/T-025/func_801B29E8.c |
| func_801BD200 | 112 | 112 | 14 | full | tools/scratch/nonmatching/T-023/func_801BD200.c |
| func_801C7A98 | 568 | 568 | 14 | prefix | tools/scratch/nonmatching/T-030/func_801C7A98.c |
| func_8002A900 | 220 | 220 | 15 | prefix | tools/scratch/nonmatching/T-024/func_8002A900.c |
| func_801C7F90 | 116 | 116 | 16 | prefix | tools/scratch/nonmatching/T-021/func_801C7F90.c |
| func_801BF988 | 184 | 184 | 17 | full | tools/scratch/nonmatching/T-023/func_801BF988.c |
| func_801B5534 | 168 | 168 | 19 | full | tools/scratch/nonmatching/T-029/func_801B5534.c |
| func_801B17BC | 256 | 256 | 20 | full | tools/scratch/nonmatching/T-025/func_801B17BC.c |
| func_801BD270 | 396 | 396 | 21 | full | tools/scratch/nonmatching/T-023/func_801BD270.c |
| func_801C8AE0 | 324 | 324 | 21 | declarations | tools/scratch/nonmatching/T-034/func_801C8AE0.c |
| func_8001E0B4 | 648 | 648 | 24 | full | tools/scratch/nonmatching/T-022/func_8001E0B4.c |
| func_801B446C | 292 | 292 | 28 | full | tools/scratch/nonmatching/T-029/func_801B446C.c |
| func_801C0800 | 248 | 248 | 29 | full | tools/scratch/nonmatching/T-023/func_801C0800.c |
| func_8002B034 | 440 | 440 | 30 | declarations | tools/scratch/nonmatching/T-024/func_8002B034.c |
| func_8002A4F0 | 920 | 920 | 31 | prefix | tools/scratch/nonmatching/T-024/func_8002A4F0.c |
| func_800269AC | 236 | 236 | 33 | full | tools/scratch/nonmatching/T-032/func_800269AC.c |
| func_801B0520 | 328 | 328 | 36 | full | tools/scratch/nonmatching/T-025/func_801B0520.c |
| func_801B1210 | 284 | 284 | 38 | full | tools/scratch/nonmatching/T-025/func_801B1210.c |
| func_800268C0 | 236 | 236 | 40 | full | tools/scratch/nonmatching/T-032/func_800268C0.c |
| func_801BBB60 | 292 | 292 | 40 | full | tools/scratch/nonmatching/T-023/func_801BBB60.c |
| func_801BE660 | 300 | 300 | 41 | full | tools/scratch/nonmatching/T-023/func_801BE660.c |
| func_800121C8 | 304 | 304 | 47 | full | tools/scratch/nonmatching/T-033/func_800121C8.c |
| func_80024028 | 284 | 284 | 49 | full | tools/scratch/nonmatching/T-032/func_80024028.c |
| func_801B2EF4 | 536 | 536 | 65 | full | tools/scratch/nonmatching/T-025/func_801B2EF4.c |
| func_801B310C | 536 | 536 | 65 | full | tools/scratch/nonmatching/T-025/func_801B310C.c |
| func_801B3324 | 536 | 536 | 65 | full | tools/scratch/nonmatching/T-025/func_801B3324.c |
| func_801B353C | 536 | 536 | 65 | full | tools/scratch/nonmatching/T-025/func_801B353C.c |
| func_801B3754 | 536 | 536 | 65 | full | tools/scratch/nonmatching/T-025/func_801B3754.c |
| func_801B396C | 536 | 536 | 65 | full | tools/scratch/nonmatching/T-025/func_801B396C.c |
| func_801C0610 | 372 | 372 | 71 | prefix | tools/scratch/nonmatching/T-023/func_801C0610.c |
| func_801C2ADC | 600 | 600 | 72 | full | tools/scratch/nonmatching/T-030/func_801C2ADC.c |
| func_801C49A8 | 548 | 548 | 83 | full | tools/scratch/nonmatching/T-030/func_801C49A8.c |
| func_801C3E40 | 504 | 504 | 88 | full | tools/scratch/nonmatching/T-030/func_801C3E40.c |
| func_80024714 | 712 | 712 | 94 | declarations | tools/scratch/nonmatching/T-032/func_80024714.c |
| func_801B1DE4 | 556 | 556 | 111 | full | tools/scratch/nonmatching/T-025/func_801B1DE4.c |
| func_801C9698 | 1148 | 1148 | 135 | declarations | tools/scratch/nonmatching/T-034/func_801C9698.c |
| func_8001D47C | 748 | 748 | 141 | declarations | tools/scratch/nonmatching/T-022/func_8001D47C.c |
| func_801C4240 | 1344 | 1344 | 150 | full | tools/scratch/nonmatching/T-030/func_801C4240.c |
| func_801B6BD8 | 628 | 628 | 153 | full | tools/scratch/nonmatching/T-029/func_801B6BD8.c |
| func_801B0668 | 984 | 984 | 156 | full | tools/scratch/nonmatching/T-025/func_801B0668.c |
| func_800297A4 | 780 | 780 | 180 | declarations | tools/scratch/nonmatching/T-024/func_800297A4.c |
| func_801BD640 | 1068 | 1068 | 191 | full | tools/scratch/nonmatching/T-023/func_801BD640.c |
| func_801B3DB0 | 1360 | 1360 | 255 | full | tools/scratch/nonmatching/T-025/func_801B3DB0.c |
| func_801BF190 | 1256 | 1256 | 284 | full | tools/scratch/nonmatching/T-023/func_801BF190.c |
| func_801B5DCC | 1884 | 1884 | 387 | full | tools/scratch/nonmatching/T-029/func_801B5DCC.c |
| func_801BCB70 | 1676 | 1676 | 391 | full | tools/scratch/nonmatching/T-023/func_801BCB70.c |
| func_801BF678 | 164 | 168 | 9 | full | tools/scratch/nonmatching/T-023/func_801BF678.c |
| func_80032738 | 40 | 20 | 10 | full | tools/scratch/nonmatching/T-026/func_80032738.c |
| func_80032750 | 44 | 60 | 15 | full | tools/scratch/nonmatching/T-026/func_80032750.c |
| func_801C8C24 | 396 | 408 | 22 | declarations | tools/scratch/nonmatching/T-034/func_801C8C24.c |
| func_8003278C | 104 | 92 | 26 | full | tools/scratch/nonmatching/T-026/func_8003278C.c |
| func_80031050 | 120 | 112 | 30 | declarations | tools/scratch/nonmatching/T-026/func_80031050.c |
| func_801C3758 | 572 | 564 | 36 | declarations | tools/scratch/nonmatching/T-030/func_801C3758.c |
| func_801CB998 | 156 | 148 | 36 | declarations | tools/scratch/nonmatching/T-021/func_801CB998.c |
| func_80032600 | 148 | 112 | 37 | full | tools/scratch/nonmatching/T-026/func_80032600.c |
| func_801ADA04 | 204 | 208 | 39 | full | tools/scratch/nonmatching/T-019/func_801ADA04.c |
| func_801B43A8 | 200 | 196 | 42 | full | tools/scratch/nonmatching/T-029/func_801B43A8.c |
| func_80032670 | 180 | 116 | 45 | full | tools/scratch/nonmatching/T-026/func_80032670.c |
| func_801C47E0 | 264 | 260 | 45 | full | tools/scratch/nonmatching/T-030/func_801C47E0.c |
| func_801C48E4 | 188 | 196 | 48 | full | tools/scratch/nonmatching/T-021/func_801C48E4.c |
| func_8002F5F0 | 220 | 212 | 50 | declarations | tools/scratch/nonmatching/T-024/func_8002F5F0.c |
| func_80032504 | 68 | 240 | 60 | full | tools/scratch/nonmatching/T-026/func_80032504.c |
| func_8001AA90 | 488 | 496 | 63 | full | tools/scratch/nonmatching/T-022/func_8001AA90.c |
| func_8001373C | 264 | 256 | 66 | prefix | tools/scratch/nonmatching/T-020/func_8001373C.c |
| func_80015450 | 328 | 324 | 68 | prefix | tools/scratch/nonmatching/T-033/func_80015450.c |
| func_80029AB0 | 284 | 304 | 69 | declarations | tools/scratch/nonmatching/T-024/func_80029AB0.c |
| func_800326F0 | 276 | 72 | 69 | full | tools/scratch/nonmatching/T-026/func_800326F0.c |
| func_801BE540 | 280 | 288 | 69 | full | tools/scratch/nonmatching/T-023/func_801BE540.c |
| func_80023EF0 | 296 | 312 | 71 | full | tools/scratch/nonmatching/T-032/func_80023EF0.c |
| func_801B465C | 332 | 328 | 71 | full | tools/scratch/nonmatching/T-029/func_801B465C.c |
| func_801C6D40 | 316 | 300 | 74 | declarations | tools/scratch/nonmatching/T-021/func_801C6D40.c |
| func_800300DC | 312 | 316 | 76 | declarations | tools/scratch/nonmatching/T-026/func_800300DC.c |
| func_800287D4 | 560 | 556 | 77 | prefix | tools/scratch/nonmatching/T-024/func_800287D4.c |
| func_80030220 | 340 | 348 | 77 | full | tools/scratch/nonmatching/T-026/func_80030220.c |
| func_801BB464 | 320 | 304 | 78 | full | tools/scratch/nonmatching/T-023/func_801BB464.c |
| func_801BE790 | 372 | 384 | 78 | prefix | tools/scratch/nonmatching/T-023/func_801BE790.c |
| func_801BA884 | 496 | 500 | 86 | full | tools/scratch/nonmatching/T-023/func_801BA884.c |
| func_801BED0C | 412 | 408 | 86 | full | tools/scratch/nonmatching/T-023/func_801BED0C.c |
| func_800245B4 | 344 | 352 | 87 | declarations | tools/scratch/nonmatching/T-032/func_800245B4.c |
| func_801AD114 | 612 | 628 | 88 | full | tools/scratch/nonmatching/T-019/func_801AD114.c |
| func_801CC3BC | 364 | 360 | 88 | full | tools/scratch/nonmatching/T-021/func_801CC3BC.c |
| func_801AD7D8 | 548 | 556 | 89 | full | tools/scratch/nonmatching/T-019/func_801AD7D8.c |
| func_801BEEA4 | 364 | 344 | 90 | prefix | tools/scratch/nonmatching/T-023/func_801BEEA4.c |
| func_8002B22C | 392 | 380 | 91 | prefix | tools/scratch/nonmatching/T-024/func_8002B22C.c |
| func_801C224C | 364 | 372 | 91 | full | tools/scratch/nonmatching/T-030/func_801C224C.c |
| func_80026738 | 388 | 392 | 96 | full | tools/scratch/nonmatching/T-032/func_80026738.c |
| func_801BE910 | 400 | 356 | 96 | prefix | tools/scratch/nonmatching/T-023/func_801BE910.c |
| func_8001CD50 | 436 | 460 | 98 | declarations | tools/scratch/nonmatching/T-022/func_8001CD50.c |
| func_80024B0C | 440 | 464 | 99 | full | tools/scratch/nonmatching/T-032/func_80024B0C.c |
| func_80012390 | 500 | 476 | 101 | full | tools/scratch/nonmatching/T-033/func_80012390.c |
| func_8001272C | 544 | 540 | 103 | full | tools/scratch/nonmatching/T-033/func_8001272C.c |
| func_801C17D0 | 436 | 448 | 103 | full | tools/scratch/nonmatching/T-023/func_801C17D0.c |
| func_8002DDD4 | 444 | 452 | 104 | prefix | tools/scratch/nonmatching/T-024/func_8002DDD4.c |
| func_80032360 | 116 | 420 | 105 | full | tools/scratch/nonmatching/T-026/func_80032360.c |
| func_801CD1F0 | 452 | 460 | 107 | full | tools/scratch/nonmatching/T-034/func_801CD1F0.c |
| func_8002FB80 | 512 | 544 | 109 | prefix | tools/scratch/nonmatching/T-024/func_8002FB80.c |
| func_800191F0 | 476 | 492 | 110 | declarations | tools/scratch/nonmatching/T-022/func_800191F0.c |
| func_801C8004 | 444 | 236 | 110 | declarations | tools/scratch/nonmatching/T-021/func_801C8004.c |
| func_801BBC84 | 508 | 516 | 112 | full | tools/scratch/nonmatching/T-023/func_801BBC84.c |
| func_801B3B84 | 552 | 556 | 114 | full | tools/scratch/nonmatching/T-025/func_801B3B84.c |
| func_801B677C | 492 | 480 | 117 | full | tools/scratch/nonmatching/T-029/func_801B677C.c |
| func_80016078 | 448 | 480 | 120 | full | tools/scratch/nonmatching/T-033/func_80016078.c |
| func_801C11F0 | 568 | 580 | 126 | full | tools/scratch/nonmatching/T-023/func_801C11F0.c |
| func_801C2F5C | 556 | 544 | 128 | full | tools/scratch/nonmatching/T-030/func_801C2F5C.c |
| func_801AFFAC | 568 | 576 | 129 | full | tools/scratch/nonmatching/T-025/func_801AFFAC.c |
| func_801BA280 | 532 | 496 | 129 | full | tools/scratch/nonmatching/T-023/func_801BA280.c |
| func_801BA088 | 540 | 504 | 132 | full | tools/scratch/nonmatching/T-023/func_801BA088.c |
| func_801BA470 | 552 | 516 | 133 | full | tools/scratch/nonmatching/T-023/func_801BA470.c |
| func_800170C4 | 696 | 692 | 134 | declarations | tools/scratch/nonmatching/T-033/func_800170C4.c |
| func_8002D9C4 | 476 | 536 | 134 | full | tools/scratch/nonmatching/T-024/func_8002D9C4.c |
| func_801BA674 | 564 | 528 | 135 | full | tools/scratch/nonmatching/T-023/func_801BA674.c |
| func_8002FDA0 | 584 | 572 | 136 | prefix | tools/scratch/nonmatching/T-024/func_8002FDA0.c |
| func_801BB258 | 556 | 524 | 138 | full | tools/scratch/nonmatching/T-023/func_801BB258.c |
| func_80018F20 | 688 | 696 | 140 | full | tools/scratch/nonmatching/T-022/func_80018F20.c |
| func_801BB594 | 580 | 544 | 140 | full | tools/scratch/nonmatching/T-023/func_801BB594.c |
| func_801BADEC | 580 | 568 | 144 | full | tools/scratch/nonmatching/T-023/func_801BADEC.c |
| func_801BD3FC | 440 | 580 | 145 | full | tools/scratch/nonmatching/T-023/func_801BD3FC.c |
| func_80025D58 | 328 | 620 | 146 | full | tools/scratch/nonmatching/T-032/func_80025D58.c |
| func_801BB024 | 600 | 564 | 148 | full | tools/scratch/nonmatching/T-023/func_801BB024.c |
| func_8001BB64 | 592 | 636 | 154 | declarations | tools/scratch/nonmatching/T-022/func_8001BB64.c |
| func_801BEA74 | 676 | 664 | 154 | full | tools/scratch/nonmatching/T-023/func_801BEA74.c |
| func_8001DE5C | 624 | 600 | 155 | full | tools/scratch/nonmatching/T-022/func_8001DE5C.c |
| func_80017A68 | 768 | 772 | 156 | declarations | tools/scratch/nonmatching/T-033/func_80017A68.c |
| func_80030440 | 520 | 632 | 156 | full | tools/scratch/nonmatching/T-026/func_80030440.c |
| func_801C1990 | 588 | 676 | 159 | declarations | tools/scratch/nonmatching/T-023/func_801C1990.c |
| func_800241BC | 840 | 820 | 161 | prefix | tools/scratch/nonmatching/T-032/func_800241BC.c |
| func_801B0A40 | 684 | 668 | 163 | full | tools/scratch/nonmatching/T-025/func_801B0A40.c |
| func_8001346C | 696 | 704 | 165 | full | tools/scratch/nonmatching/T-033/func_8001346C.c |
| func_801ACB1C | 756 | 744 | 176 | prefix | tools/scratch/nonmatching/T-034/func_801ACB1C.c |
| func_801C1434 | 736 | 720 | 176 | declarations | tools/scratch/nonmatching/T-023/func_801C1434.c |
| func_8001D080 | 756 | 764 | 177 | declarations | tools/scratch/nonmatching/T-022/func_8001D080.c |
| func_800131A4 | 676 | 712 | 178 | declarations | tools/scratch/nonmatching/T-033/func_800131A4.c |
| func_8002E150 | 836 | 844 | 179 | full | tools/scratch/nonmatching/T-024/func_8002E150.c |
| func_8001808C | 796 | 808 | 181 | declarations | tools/scratch/nonmatching/T-022/func_8001808C.c |
| func_801BBE88 | 804 | 808 | 184 | full | tools/scratch/nonmatching/T-023/func_801BBE88.c |
| func_800253D0 | 1044 | 1068 | 186 | full | tools/scratch/nonmatching/T-032/func_800253D0.c |
| func_801B2B8C | 884 | 872 | 189 | prefix | tools/scratch/nonmatching/T-025/func_801B2B8C.c |
| func_800193DC | 788 | 808 | 192 | declarations | tools/scratch/nonmatching/T-022/func_800193DC.c |
| func_801B01EC | 828 | 820 | 193 | full | tools/scratch/nonmatching/T-025/func_801B01EC.c |
| func_80017D6C | 824 | 800 | 194 | full | tools/scratch/nonmatching/T-033/func_80017D6C.c |
| func_80018AE0 | 900 | 912 | 194 | declarations | tools/scratch/nonmatching/T-022/func_80018AE0.c |
| func_8001AD04 | 1088 | 1072 | 194 | full | tools/scratch/nonmatching/T-022/func_8001AD04.c |
| func_801B0CDC | 1336 | 1332 | 204 | full | tools/scratch/nonmatching/T-025/func_801B0CDC.c |
| func_801B1A7C | 596 | 872 | 206 | full | tools/scratch/nonmatching/T-025/func_801B1A7C.c |
| func_801C3AA0 | 908 | 928 | 206 | full | tools/scratch/nonmatching/T-030/func_801C3AA0.c |
| func_8002AB90 | 816 | 852 | 208 | prefix | tools/scratch/nonmatching/T-024/func_8002AB90.c |
| func_8001B134 | 980 | 984 | 215 | full | tools/scratch/nonmatching/T-022/func_8001B134.c |
| func_801C90D4 | 1192 | 1200 | 219 | declarations | tools/scratch/nonmatching/T-034/func_801C90D4.c |
| func_801BB7B4 | 960 | 940 | 220 | declarations | tools/scratch/nonmatching/T-023/func_801BB7B4.c |
| func_801BAA78 | 912 | 884 | 222 | full | tools/scratch/nonmatching/T-023/func_801BAA78.c |
| func_801C23C0 | 1812 | 1820 | 222 | prefix | tools/scratch/nonmatching/T-030/func_801C23C0.c |
| func_801C317C | 940 | 936 | 225 | declarations | tools/scratch/nonmatching/T-030/func_801C317C.c |
| func_80031A38 | 680 | 920 | 229 | declarations | tools/scratch/nonmatching/T-026/func_80031A38.c |
| func_800216D4 | 1040 | 1032 | 230 | prefix | tools/scratch/nonmatching/T-032/func_800216D4.c |
| func_801AF68C | 940 | 956 | 231 | prefix | tools/scratch/nonmatching/T-025/func_801AF68C.c |
| func_80027E1C | 940 | 936 | 234 | full | tools/scratch/nonmatching/T-032/func_80027E1C.c |
| func_801B132C | 1144 | 1168 | 237 | full | tools/scratch/nonmatching/T-025/func_801B132C.c |
| func_80028230 | 932 | 976 | 242 | full | tools/scratch/nonmatching/T-024/func_80028230.c |
| func_801C1C34 | 1224 | 1244 | 242 | prefix | tools/scratch/nonmatching/T-023/func_801C1C34.c |
| func_80029BE0 | 1048 | 1060 | 263 | declarations | tools/scratch/nonmatching/T-024/func_80029BE0.c |
| func_801C7310 | 1264 | 1276 | 281 | full | tools/scratch/nonmatching/T-030/func_801C7310.c |
| func_800327E8 | 1156 | 1092 | 284 | full | tools/scratch/nonmatching/T-026/func_800327E8.c |
| func_801C80F0 | 1228 | 1232 | 284 | full | tools/scratch/nonmatching/T-034/func_801C80F0.c |
| func_801BDA6C | 1336 | 1320 | 289 | full | tools/scratch/nonmatching/T-023/func_801BDA6C.c |
| func_801AFAA4 | 1256 | 1288 | 301 | full | tools/scratch/nonmatching/T-025/func_801AFAA4.c |
| func_800257FC | 1232 | 1372 | 337 | full | tools/scratch/nonmatching/T-032/func_800257FC.c |
| func_80015594 | 1464 | 1488 | 339 | declarations | tools/scratch/nonmatching/T-033/func_80015594.c |
| func_801BDF94 | 1440 | 1452 | 353 | full | tools/scratch/nonmatching/T-023/func_801BDF94.c |
| func_80031DD0 | 1020 | 1420 | 355 | declarations | tools/scratch/nonmatching/T-026/func_80031DD0.c |
| func_80014D5C | 1444 | 1780 | 373 | prefix | tools/scratch/nonmatching/T-033/func_80014D5C.c |
| func_800238C4 | 1600 | 1580 | 384 | full | tools/scratch/nonmatching/T-032/func_800238C4.c |
| func_80012B7C | 1560 | 1576 | 391 | declarations | tools/scratch/nonmatching/T-033/func_80012B7C.c |
| func_80024CE0 | 1600 | 1652 | 400 | full | tools/scratch/nonmatching/T-032/func_80024CE0.c |
| func_801B9A04 | 1132 | 1668 | 416 | full | tools/scratch/nonmatching/T-029/func_801B9A04.c |
| func_801B5650 | 1924 | 1916 | 425 | full | tools/scratch/nonmatching/T-029/func_801B5650.c |
| func_8001D7E4 | 1724 | 1656 | 427 | prefix | tools/scratch/nonmatching/T-022/func_8001D7E4.c |
| func_80025FC4 | 1896 | 1908 | 454 | full | tools/scratch/nonmatching/T-032/func_80025FC4.c |
| func_800306B8 | 2096 | 2104 | 510 | full | tools/scratch/nonmatching/T-026/func_800306B8.c |
| func_80020E98 | 2104 | 2108 | 512 | prefix | tools/scratch/nonmatching/T-032/func_80020E98.c |
| func_801C5E74 | 2404 | 2392 | 557 | declarations | tools/scratch/nonmatching/T-030/func_801C5E74.c |
| func_801C08F8 | 2216 | 2296 | 561 | full | tools/scratch/nonmatching/T-023/func_801C08F8.c |
| func_8001178C | 2296 | 2104 | 570 | prefix | tools/scratch/nonmatching/T-033/func_8001178C.c |
| func_8001E33C | 2412 | 2360 | 571 | full | tools/scratch/nonmatching/T-022/func_8001E33C.c |
| func_800142E0 | 2100 | 2400 | 593 | declarations | tools/scratch/nonmatching/T-033/func_800142E0.c |
| func_801BFCBC | 2084 | 2388 | 596 | declarations | tools/scratch/nonmatching/T-023/func_801BFCBC.c |
| func_801BC1B0 | 2320 | 2496 | 624 | full | tools/scratch/nonmatching/T-023/func_801BC1B0.c |
| func_801C9B14 | 3140 | 3184 | 630 | declarations | tools/scratch/nonmatching/T-034/func_801C9B14.c |
| func_801ABB20 | 3576 | 3644 | 658 | prefix | tools/scratch/nonmatching/T-034/func_801ABB20.c |
| func_8002E724 | 2728 | 2832 | 659 | declarations | tools/scratch/nonmatching/T-024/func_8002E724.c |
| func_800310C0 | 2744 | 2424 | 683 | declarations | tools/scratch/nonmatching/T-026/func_800310C0.c |
| func_801C5298 | 3000 | 3036 | 741 | declarations | tools/scratch/nonmatching/T-030/func_801C5298.c |
| func_80028A00 | 3264 | 3340 | 802 | declarations | tools/scratch/nonmatching/T-024/func_80028A00.c |
| func_801B47A4 | 3260 | 3472 | 862 | prefix | tools/scratch/nonmatching/T-029/func_801B47A4.c |
| func_801CAA00 | 3908 | 3992 | 972 | declarations | tools/scratch/nonmatching/T-034/func_801CAA00.c |
| func_80026B38 | 4792 | 4708 | 1182 | full | tools/scratch/nonmatching/T-032/func_80026B38.c |
| func_801B849C | 5312 | 5296 | 1267 | declarations | tools/scratch/nonmatching/T-029/func_801B849C.c |
| func_80019880 | 5216 | 4456 | 1297 | declarations | tools/scratch/nonmatching/T-022/func_80019880.c |
| func_801ADEA0 | 5524 | 5508 | 1349 | prefix | tools/scratch/nonmatching/T-025/func_801ADEA0.c |
| func_801B6E4C | 5652 | 5712 | 1417 | declarations | tools/scratch/nonmatching/T-029/func_801B6E4C.c |
| func_80021B6C | 6908 | 6896 | 1704 | declarations | tools/scratch/nonmatching/T-032/func_80021B6C.c |
| func_8002BBD0 | 7692 | 7668 | 1843 | full | tools/scratch/nonmatching/T-024/func_8002BBD0.c |
| func_8000FA80 | 8148 | 7436 | 2014 | prefix | tools/scratch/nonmatching/T-033/func_8000FA80.c |
| func_8001EC74 | 8476 | 8740 | 2175 | declarations | tools/scratch/nonmatching/T-022/func_8001EC74.c |

## Compilation diagnostics

### func_801BF720 (prefix)

```text
cfe: Error: /tmp/kig-screen-qcwnkk66/candidate.c, line 90: redeclaration of 'func_801BF720'; previous declaration at line 75 in file '/tmp/kig-screen-qcwnkk66/candidate.c'
 extern s32 func_801BF720(s32);
 -----------^
cfe: Error: /tmp/kig-screen-qcwnkk66/candidate.c, line 90: Incompatible type for the function parameter
 extern s32 func_801BF720(s32);
 -------------------------^
```

### func_801C4E38 (declarations)

```text
cfe: Error: /tmp/kig-screen-bfah5yjd/candidate.c, line 248: redeclaration of 'D_802D39A0'; previous declaration at line 189 in file '/tmp/kig-screen-bfah5yjd/candidate.c'
 extern s32 D_802D39A0;
 -----------^
cfe: Error: /tmp/kig-screen-bfah5yjd/candidate.c, line 249: redeclaration of 'D_802D39A4'; previous declaration at line 190 in file '/tmp/kig-screen-bfah5yjd/candidate.c'
 extern s32 D_802D39A4;
 -----------^
cfe: Error: /tmp/kig-screen-bfah5yjd/candidate.c, line 250: redeclaration of 'D_802D39A8'; previous declaration at line 191 in file '/tmp/kig-screen-bfah5yjd/candidate.c'
 extern s32 D_802D39A8;
 -----------^
```

### func_801B695C (prefix)

```text
cfe: Error: /tmp/kig-screen-11btzr21/candidate.c, line 155: redeclaration of 'D_802C8808'; previous declaration at line 126 in file '/tmp/kig-screen-11btzr21/candidate.c'
 extern u8 D_802C8808[][512];
 ----------^
cfe: Error: /tmp/kig-screen-11btzr21/candidate.c, line 176: Subscripting a non-array.
         command1->w1 = (u32)(&D_802C8808[arg2][D_802C8D08[arg2] * 2]);
 ----------------------------------------------^
```

### func_801C5064 (declarations)

```text
cfe: Error: /tmp/kig-screen-gnmj_ts6/candidate.c, line 226: redeclaration of 'D_802D399F'; previous declaration at line 188 in file '/tmp/kig-screen-gnmj_ts6/candidate.c'
 extern u8 D_802D399F;
 ----------^
```

### func_801C8F28 (declarations)

```text
cfe: Error: /tmp/kig-screen-e2dlj5gk/candidate.c, line 251: redeclaration of 'D_80127D58'; previous declaration at line 129 in file '/tmp/kig-screen-e2dlj5gk/candidate.c'
 extern u8 D_80127D58[2][16];
 ----------^
cfe: Error: /tmp/kig-screen-e2dlj5gk/candidate.c, line 275: Subscripting a non-array.
             D_80127D58[0][i] = v;
 -------------------------^
cfe: Error: /tmp/kig-screen-e2dlj5gk/candidate.c, line 277: Subscripting a non-array.
             D_80127D58[1][i - 10] = v;
 -------------------------^
```

### func_801CCD74 (prefix)

```text
cfe: Error: /tmp/kig-screen-skxmw2iq/candidate.c, line 633: redeclaration of 'func_801CCD74'; previous declaration at line 501 in file '/tmp/kig-screen-skxmw2iq/candidate.c'
 s32 func_801BE540(s32, s32, s32, s32, f32, f32, s32, s32, s32, s32, f32);s32 func_801CCD74(s32 *);
 -----------------------------------------------------------------------------^
cfe: Error: /tmp/kig-screen-skxmw2iq/candidate.c, line 633: Incompatible type for the function parameter
 s32 func_801BE540(s32, s32, s32, s32, f32, f32, s32, s32, s32, s32, f32);s32 func_801CCD74(s32 *);
 -------------------------------------------------------------------------------------------^
```

### func_801C85C0 (declarations)

```text
cfe: Error: /tmp/kig-screen-7m6hz0lg/candidate.c, line 128: redeclaration of 'func_801C7E98'; previous declaration at line 97 in file '/tmp/kig-screen-7m6hz0lg/candidate.c'
 extern void func_801C7E98();
 ------------^
cfe: Error: /tmp/kig-screen-7m6hz0lg/candidate.c, line 128: prototype and non-prototype declaration found for func_801C7E98, the type of this parameter is not compatible with the type after applying default argument promotion
 extern void func_801C7E98();
 -------------------------^
cfe: Error: /tmp/kig-screen-7m6hz0lg/candidate.c, line 132: redeclaration of 'D_80127D30'; previous declaration at line 113 in file '/tmp/kig-screen-7m6hz0lg/candidate.c'
 extern u8 D_80127D30;
 ----------^
```

### func_801C7A98 (prefix)

```text
cfe: Error: /tmp/kig-screen-oe3ocxqb/candidate.c, line 411: redeclaration of 'D_80292674'; previous declaration at line 36 in file '/tmp/kig-screen-oe3ocxqb/candidate.c'
 extern u8 D_80292674;
 ----------^
cfe: Error: /tmp/kig-screen-oe3ocxqb/candidate.c, line 425: Unacceptable operand of == or !=
     if (D_80292674 == 4) {
 -------------------^
```

### func_8002A900 (prefix)

```text
cfe: Error: /tmp/kig-screen-99ubcl9x/candidate.c, line 64: redeclaration of 'D_80066C28'; previous declaration at line 29 in file '/tmp/kig-screen-99ubcl9x/candidate.c'
 extern T052SequenceEntry *D_80066C28;
 --------------------------^
cfe: Error: /tmp/kig-screen-99ubcl9x/candidate.c, line 70: redeclaration of 'boot_dma'; previous declaration at line 41 in file '/tmp/kig-screen-99ubcl9x/candidate.c'
 extern void boot_dma(s32, s32, s32);
 ------------^
cfe: Error: /tmp/kig-screen-99ubcl9x/candidate.c, line 70: Incompatible function return type for this function.
 extern void boot_dma(s32, s32, s32);
 --------------------^
```

### func_801C7F90 (prefix)

```text
cfe: Error: /tmp/kig-screen-jxvmrtsf/candidate.c, line 142: redeclaration of 'D_80127CC0'; previous declaration at line 122 in file '/tmp/kig-screen-jxvmrtsf/candidate.c'
 extern u8 D_80127CC0[];
 ----------^
cfe: Error: /tmp/kig-screen-jxvmrtsf/candidate.c, line 164: Subscripting a non-array.
             b |= D_80127CC0[i] << 4;
 ---------------------------^
cfe: Error: /tmp/kig-screen-jxvmrtsf/candidate.c, line 167: Subscripting a non-array.
             b = D_80127CC0[i];
 --------------------------^
cfe: Error: /tmp/kig-screen-jxvmrtsf/candidate.c, line 177: redeclaration of 'D_80127CC0'; previous declaration at line 122 in file '/tmp/kig-screen-jxvmrtsf/candidate.c'
 extern u8 D_80127CC0[];
 ----------^
cfe: Error: /tmp/kig-screen-jxvmrtsf/candidate.c, line 194: Subscripting a non-array.
             D_80127CC0[i] = (*arg0++ >> 4) & 0xF;
 ----------------------^
cfe: Error: /tmp/kig-screen-jxvmrtsf/candidate.c, line 196: Subscripting a non-array.
             D_80127CC0[i] = *arg0 & 0xF;
 ----------------------^
```

### func_801C8AE0 (declarations)

```text
cfe: Error: /tmp/kig-screen-1rc9qwp0/candidate.c, line 213: redeclaration of 'D_80127D30'; previous declaration at line 113 in file '/tmp/kig-screen-1rc9qwp0/candidate.c'
 extern u8 D_80127D30;
 ----------^
```

### func_8002B034 (declarations)

```text
cfe: Error: /tmp/kig-screen-0wv1_13e/candidate.c, line 68: redeclaration of 'D_80066C50'; previous declaration at line 12 in file '/tmp/kig-screen-0wv1_13e/candidate.c'
 extern u8 *D_80066C50[];
 -----------^
cfe: Error: /tmp/kig-screen-0wv1_13e/candidate.c, line 69: redeclaration of 'func_8002B034'; previous declaration at line 16 in file '/tmp/kig-screen-0wv1_13e/candidate.c'
 s32 func_8002B034(T024AudioTask *task,T024AudioTask *previous) { u32 physical; s32 count; u8 *end; func_8002B3E0(); physical=osVirtualToPhysical(task->buffer); if(previous) osAiSetNextBuffer(previous->buffer,previous->samples*4); task->samples=(D_80068168-(osAiGetLength()>>2)+0x60)&0xFFF0; if((u32)task->samples<D_80068164) task->samples=D_80068164; end=(u8 *)func_80039C08(D_80066C50[D_80048158],&count,physical,task->samples); if(count==0) return 0; task->state=0; task->queue=D_80066E50; task->message=task->body; task->type=2; task->commands=D_80066C50[D_80048158]; task->commandSize=((end-D_80066C50[D_80048158])>>3)*8; task->taskType=2; task->boot=D_80042710; task->bootSize=D_800427E0-D_80042710; task->flags=2; task->code=D_80043BF0; task->data=D_80049F70; task->dataSize=0x800; task->yield=0; task->yieldSize=0x400; osWritebackDCacheAll(); osSendMesg(D_8000CF68,&task->state,1); D_80048158^=1; return 1; }
 ----^
cfe: Error: /tmp/kig-screen-0wv1_13e/candidate.c, line 69: Incompatible type for the function parameter
 s32 func_8002B034(T024AudioTask *task,T024AudioTask *previous) { u32 physical; s32 count; u8 *end; func_8002B3E0(); physical=osVirtualToPhysical(task->buffer); if(previous) osAiSetNextBuffer(previous->buffer,previous->samples*4); task->samples=(D_80068168-(osAiGetLength()>>2)+0x60)&0xFFF0; if((u32)task->samples<D_80068164) task->samples=D_80068164; end=(u8 *)func_80039C08(D_80066C50[D_80048158],&count,physical,task->samples); if(count==0) return 0; task->state=0; task->queue=D_80066E50; task->message=task->body; task->type=2; task->commands=D_80066C50[D_80048158]; task->commandSize=((end-D_80066C50[D_80048158])>>3)*8; task->taskType=2; task->boot=D_80042710; task->bootSize=D_800427E0-D_80042710; task->flags=2; task->code=D_80043BF0; task->data=D_80049F70; task->dataSize=0x800; task->yield=0; task->yieldSize=0x400; osWritebackDCacheAll(); osSendMesg(D_8000CF68,&task->state,1); D_80048158^=1; return 1; }
 ---------------------------------^
cfe: Error: /tmp/kig-screen-0wv1_13e/candidate.c, line 69: Unacceptable operand of '-'.
 s32 func_8002B034(T024AudioTask *task,T024AudioTask *previous) { u32 physical; s32 count; u8 *end; func_8002B3E0(); physical=osVirtualToPhysical(task->buffer); if(previous) osAiSetNextBuffer(previous->buffer,previous->samples*4); task->samples=(D_80068168-(osAiGetLength()>>2)+0x60)&0xFFF0; if((u32)task->samples<D_80068164) task->samples=D_80068164; end=(u8 *)func_80039C08(D_80066C50[D_80048158],&count,physical,task->samples); if(count==0) return 0; task->state=0; task->queue=D_80066E50; task->message=task->body; task->type=2; task->commands=D_80066C50[D_80048158]; task->commandSize=((end-D_80066C50[D_80048158])>>3)*8; task->taskType=2; task->boot=D_80042710; task->bootSize=D_800427E0-D_80042710; task->flags=2; task->code=D_80043BF0; task->data=D_80049F70; task->dataSize=0x800; task->yield=0; task->yieldSize=0x400; osWritebackDCacheAll(); osSendMesg(D_8000CF68,&task->state,1); D_80048158^=1; return 1; }
 -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------^
```

### func_8002A4F0 (prefix)

```text
cfe: Error: /tmp/kig-screen-q_cc8yy3/candidate.c, line 160: redeclaration of 'D_80066C28'; previous declaration at line 43 in file '/tmp/kig-screen-q_cc8yy3/candidate.c'
 extern T052SequenceEntry *D_80066C28;
 --------------------------^
cfe: Error: /tmp/kig-screen-q_cc8yy3/candidate.c, line 170: 'start' undefined; reoccurrences will not be reported.
         boot_dma((s32)D_80066C28[index].start, (s32)D_80066A34, D_800669D0[index]);
 ---------------------------------------^
cfe: Error: /tmp/kig-screen-q_cc8yy3/candidate.c, line 170: member of structure or union required
         boot_dma((s32)D_80066C28[index].start, (s32)D_80066A34, D_800669D0[index]);
 ----------------------------------------^
```

### func_801C0610 (prefix)

```text
cfe: Error: /tmp/kig-screen-xvctmmbo/candidate.c, line 84: redeclaration of 'func_801C0610'; previous declaration at line 65 in file '/tmp/kig-screen-xvctmmbo/candidate.c'
 extern void func_801C0610(s32, u32);
 ------------^
cfe: Error: /tmp/kig-screen-xvctmmbo/candidate.c, line 84: Incompatible type for the function parameter
 extern void func_801C0610(s32, u32);
 --------------------------^
cfe: Error: /tmp/kig-screen-xvctmmbo/candidate.c, line 92: The number of arguments doesn't agree with the number in the declaration.
     func_801C0610(arg0, arg1);
 -----------------^
```

### func_80024714 (declarations)

```text
cfe: Error: /tmp/kig-screen-j9pg6bbz/candidate.c, line 174: redeclaration of 'D_8004D278'; previous declaration at line 144 in file '/tmp/kig-screen-j9pg6bbz/candidate.c'
 extern u8 D_1EB6D0[],D_1F3200[],D_2C2280[],D_2CF0A0[],D_469660[],D_470390[],D_53CC40[],D_543D10[],D_8004D278[],D_8004EA9C[],D_8004F396[];
 --------------------------------------------------------------------------------------------------^
cfe: Error: /tmp/kig-screen-j9pg6bbz/candidate.c, line 198: Unacceptable operand of '+'.
         temp_v0_2 = (T032Resource714 *)(D_8004D278 + arg0 * 8);
 ---------------------------------------------------^
cfe: Error: /tmp/kig-screen-j9pg6bbz/candidate.c, line 206: Unacceptable operand of '+'.
         temp_v0_3 = (T032Resource714 *)(D_8004D278 + arg0 * 8);
 ---------------------------------------------------^
cfe: Error: /tmp/kig-screen-j9pg6bbz/candidate.c, line 220: Unacceptable operand of '+'.
         var_v0 = (T032Resource714 *)(D_8004D278 + arg0 * 8);
 ------------------------------------------------^
cfe: Error: /tmp/kig-screen-j9pg6bbz/candidate.c, line 229: Unacceptable operand of '+'.
         var_v0 = (T032Resource714 *)(D_8004D278 + arg0 * 8);
 ------------------------------------------------^
```

### func_801C9698 (declarations)

```text
cfe: Error: /tmp/kig-screen-q9aj8yf2/candidate.c, line 303: redeclaration of 'D_802D39FC'; previous declaration at line 39 in file '/tmp/kig-screen-q9aj8yf2/candidate.c'
 extern u8 D_802D39FC;
 ----------^
cfe: Error: /tmp/kig-screen-q9aj8yf2/candidate.c, line 304: redeclaration of 'D_802D3A01'; previous declaration at line 39 in file '/tmp/kig-screen-q9aj8yf2/candidate.c'
 extern u8 D_802D3A01;
 ----------^
```

### func_8001D47C (declarations)

```text
cfe: Error: /tmp/kig-screen-2u669w1k/candidate.c, line 53: redeclaration of 'D_8004CE90'; previous declaration at line 38 in file '/tmp/kig-screen-2u669w1k/candidate.c'
 extern u8 D_8004CE90[];
 ----------^
```

### func_800297A4 (declarations)

```text
cfe: Error: /tmp/kig-screen-1jeblp8b/candidate.c, line 84: redeclaration of 'D_80061D60'; previous declaration at line 76 in file '/tmp/kig-screen-1jeblp8b/candidate.c'
 extern T024Burst D_80061D60[];
 -----------------^
```

### func_801C8C24 (declarations)

```text
cfe: Error: /tmp/kig-screen-ze9lg0vx/candidate.c, line 215: redeclaration of 'D_80127D30'; previous declaration at line 113 in file '/tmp/kig-screen-ze9lg0vx/candidate.c'
 extern u8 D_80127D30;
 ----------^
```

### func_80031050 (declarations)

```text
cfe: Error: /tmp/kig-screen-6irlyt7x/candidate.c, line 8: 'D_8004CED0' undefined; reoccurrences will not be reported.
     u8 *entry = (u8 *)D_8004CED0;
 ----------------------^
```

### func_801C3758 (declarations)

```text
cfe: Error: /tmp/kig-screen-v3vn0ygf/candidate.c, line 264: redeclaration of 'D_802D38E0'; previous declaration at line 210 in file '/tmp/kig-screen-v3vn0ygf/candidate.c'
 extern T030Vertex3758 *D_802D38E0;
 -----------------------^
cfe: Error: /tmp/kig-screen-v3vn0ygf/candidate.c, line 266: redeclaration of 'func_801C3758'; previous declaration at line 206 in file '/tmp/kig-screen-v3vn0ygf/candidate.c'
 void func_801C3758(u32 **arg0, T030Cloud3758 *arg1, s8 arg2) {
 -----^
cfe: Error: /tmp/kig-screen-v3vn0ygf/candidate.c, line 266: Incompatible type for the function parameter
 void func_801C3758(u32 **arg0, T030Cloud3758 *arg1, s8 arg2) {
 -------------------------^
cfe: Error: /tmp/kig-screen-v3vn0ygf/candidate.c, line 274: Selector requires struct/union as left hand side
     D_802D38E0[D_80290D88].x = arg1->x - arg2;
 --------------------------^
cfe: Error: /tmp/kig-screen-v3vn0ygf/candidate.c, line 275: Selector requires struct/union as left hand side
     D_802D38E0[D_80290D88+1].x = arg1->x + arg2;
 ----------------------------^
cfe: Error: /tmp/kig-screen-v3vn0ygf/candidate.c, line 276: Selector requires struct/union as left hand side
     D_802D38E0[D_80290D88+2].x = arg1->x;
 ----------------------------^
cfe: Error: /tmp/kig-screen-v3vn0ygf/candidate.c, line 277: Selector requires struct/union as left hand side
     D_802D38E0[D_80290D88].y = arg1->y - arg2;
 --------------------------^
cfe: Error: /tmp/kig-screen-v3vn0ygf/candidate.c, line 278: Selector requires struct/union as left hand side
     D_802D38E0[D_80290D88+1].y = arg1->y - arg2;
 ----------------------------^
cfe: Error: /tmp/kig-screen-v3vn0ygf/candidate.c, line 279: Selector requires struct/union as left hand side
     D_802D38E0[D_80290D88+2].y = arg1->y + arg2;
 ----------------------------^
cfe: Error: /tmp/kig-screen-v3vn0ygf/candidate.c, line 280: Selector requires struct/union as left hand side
     D_802D38E0[D_80290D88].z = arg1->z;
 --------------------------^
cfe: Error: /tmp/kig-screen-v3vn0ygf/candidate.c, line 281: Selector requires struct/union as left hand side
     D_802D38E0[D_80290D88+1].z = arg1->z;
 ----------------------------^
cfe: Error: /tmp/kig-screen-v3vn0ygf/candidate.c, line 282: Selector requires struct/union as left hand side
     D_802D38E0[D_80290D88+2].z = arg1->z;
 ----------------------------^
cfe: Error: /tmp/kig-screen-v3vn0ygf/candidate.c, line 284: Selector requires struct/union as left hand side
     D_802D38E0[D_80290D88].s = uv[0];
 --------------------------^
cfe: Error: /tmp/kig-screen-v3vn0ygf/candidate.c, line 285: Selector requires struct/union as left hand side
     D_802D38E0[D_80290D88].t = uv[1];
 --------------------------^
cfe: Error: /tmp/kig-screen-v3vn0ygf/candidate.c, line 286: Selector requires struct/union as left hand side
     D_802D38E0[D_80290D88+1].s = uv[2];
 ----------------------------^
cfe: Error: /tmp/kig-screen-v3vn0ygf/candidate.c, line 287: Selector requires struct/union as left hand side
     D_802D38E0[D_80290D88+1].t = uv[3];
 ----------------------------^
cfe: Error: /tmp/kig-screen-v3vn0ygf/candidate.c, line 288: Selector requires struct/union as left hand side
     D_802D38E0[D_80290D88+2].s = uv[4];
 ----------------------------^
cfe: Error: /tmp/kig-screen-v3vn0ygf/candidate.c, line 289: Selector requires struct/union as left hand side
     D_802D38E0[D_80290D88+2].t = uv[5];
 ----------------------------^
```

### func_801CB998 (declarations)

```text
cfe: Error: /tmp/kig-screen-8zy2bbe0/candidate.c, line 363: redeclaration of 'D_80127D30'; previous declaration at line 113 in file '/tmp/kig-screen-8zy2bbe0/candidate.c'
 extern u8 D_80127D30;
 ----------^
cfe: Error: /tmp/kig-screen-8zy2bbe0/candidate.c, line 378: Should only subscript an array with an integral expression
         func_801BED0C(D_80127CFC[D_80127D30], arg1, D_802D3800, D_802D3804);
 --------------------------------^
```

### func_8002F5F0 (declarations)

```text
cfe: Error: /tmp/kig-screen-19f9xe_b/candidate.c, line 178: redeclaration of 'D_80048270'; previous declaration at line 156 in file '/tmp/kig-screen-19f9xe_b/candidate.c'
 extern T024ReleaseLists D_80048270;
 ------------------------^
cfe: Error: /tmp/kig-screen-19f9xe_b/candidate.c, line 181: 'head' undefined; reoccurrences will not be reported.
 void func_8002F5F0(T024FreeVoice *voice) { T024ReleasedVoice *p=(T024ReleasedVoice *)voice; if(p==D_80048270.head) D_80048270.head=p->next; if(p==D_80048270.tail) D_80048270.tail=p->prev; alUnlink(p); if(D_80048270.free) { p->next=D_80048270.free; p->prev=0; D_80048270.free->prev=p; } else { p->prev=0; p->next=0; } D_80048270.free=p; if(p->flags&4) D_80048280--; p->state=0; if(p->owner) { if(p==*p->owner) *p->owner=0; p->owner=0; } }
 ------------------------------------------------------------------------------------------------------------^
cfe: Error: /tmp/kig-screen-19f9xe_b/candidate.c, line 181: member of structure or union required
 void func_8002F5F0(T024FreeVoice *voice) { T024ReleasedVoice *p=(T024ReleasedVoice *)voice; if(p==D_80048270.head) D_80048270.head=p->next; if(p==D_80048270.tail) D_80048270.tail=p->prev; alUnlink(p); if(D_80048270.free) { p->next=D_80048270.free; p->prev=0; D_80048270.free->prev=p; } else { p->prev=0; p->next=0; } D_80048270.free=p; if(p->flags&4) D_80048280--; p->state=0; if(p->owner) { if(p==*p->owner) *p->owner=0; p->owner=0; } }
 -------------------------------------------------------------------------------------------------------------^
cfe: Error: /tmp/kig-screen-19f9xe_b/candidate.c, line 181: member of structure or union required
 void func_8002F5F0(T024FreeVoice *voice) { T024ReleasedVoice *p=(T024ReleasedVoice *)voice; if(p==D_80048270.head) D_80048270.head=p->next; if(p==D_80048270.tail) D_80048270.tail=p->prev; alUnlink(p); if(D_80048270.free) { p->next=D_80048270.free; p->prev=0; D_80048270.free->prev=p; } else { p->prev=0; p->next=0; } D_80048270.free=p; if(p->flags&4) D_80048280--; p->state=0; if(p->owner) { if(p==*p->owner) *p->owner=0; p->owner=0; } }
 ------------------------------------------------------------------------------------------------------------------------------^
cfe: Error: /tmp/kig-screen-19f9xe_b/candidate.c, line 181: 'tail' undefined; reoccurrences will not be reported.
 void func_8002F5F0(T024FreeVoice *voice) { T024ReleasedVoice *p=(T024ReleasedVoice *)voice; if(p==D_80048270.head) D_80048270.head=p->next; if(p==D_80048270.tail) D_80048270.tail=p->prev; alUnlink(p); if(D_80048270.free) { p->next=D_80048270.free; p->prev=0; D_80048270.free->prev=p; } else { p->prev=0; p->next=0; } D_80048270.free=p; if(p->flags&4) D_80048280--; p->state=0; if(p->owner) { if(p==*p->owner) *p->owner=0; p->owner=0; } }
 ------------------------------------------------------------------------------------------------------------------------------------------------------------^
cfe: Error: /tmp/kig-screen-19f9xe_b/candidate.c, line 181: member of structure or union required
 void func_8002F5F0(T024FreeVoice *voice) { T024ReleasedVoice *p=(T024ReleasedVoice *)voice; if(p==D_80048270.head) D_80048270.head=p->next; if(p==D_80048270.tail) D_80048270.tail=p->prev; alUnlink(p); if(D_80048270.free) { p->next=D_80048270.free; p->prev=0; D_80048270.free->prev=p; } else { p->prev=0; p->next=0; } D_80048270.free=p; if(p->flags&4) D_80048280--; p->state=0; if(p->owner) { if(p==*p->owner) *p->owner=0; p->owner=0; } }
 -------------------------------------------------------------------------------------------------------------------------------------------------------------^
cfe: Error: /tmp/kig-screen-19f9xe_b/candidate.c, line 181: member of structure or union required
 void func_8002F5F0(T024FreeVoice *voice) { T024ReleasedVoice *p=(T024ReleasedVoice *)voice; if(p==D_80048270.head) D_80048270.head=p->next; if(p==D_80048270.tail) D_80048270.tail=p->prev; alUnlink(p); if(D_80048270.free) { p->next=D_80048270.free; p->prev=0; D_80048270.free->prev=p; } else { p->prev=0; p->next=0; } D_80048270.free=p; if(p->flags&4) D_80048280--; p->state=0; if(p->owner) { if(p==*p->owner) *p->owner=0; p->owner=0; } }
 ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------^
cfe: Error: /tmp/kig-screen-19f9xe_b/candidate.c, line 181: 'prev' undefined; reoccurrences will not be reported.
 void func_8002F5F0(T024FreeVoice *voice) { T024ReleasedVoice *p=(T024ReleasedVoice *)voice; if(p==D_80048270.head) D_80048270.head=p->next; if(p==D_80048270.tail) D_80048270.tail=p->prev; alUnlink(p); if(D_80048270.free) { p->next=D_80048270.free; p->prev=0; D_80048270.free->prev=p; } else { p->prev=0; p->next=0; } D_80048270.free=p; if(p->flags&4) D_80048280--; p->state=0; if(p->owner) { if(p==*p->owner) *p->owner=0; p->owner=0; } }
 ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------^
cfe: Error: /tmp/kig-screen-19f9xe_b/candidate.c, line 181: member of structure or union required
 void func_8002F5F0(T024FreeVoice *voice) { T024ReleasedVoice *p=(T024ReleasedVoice *)voice; if(p==D_80048270.head) D_80048270.head=p->next; if(p==D_80048270.tail) D_80048270.tail=p->prev; alUnlink(p); if(D_80048270.free) { p->next=D_80048270.free; p->prev=0; D_80048270.free->prev=p; } else { p->prev=0; p->next=0; } D_80048270.free=p; if(p->flags&4) D_80048280--; p->state=0; if(p->owner) { if(p==*p->owner) *p->owner=0; p->owner=0; } }
 ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------^
```

### func_8001373C (prefix)

```text
cfe: Error: /tmp/kig-screen-0vj5p7v_/candidate.c, line 505: redeclaration of 'func_8001373C'; previous declaration at line 99 in file '/tmp/kig-screen-0vj5p7v_/candidate.c'
 extern void func_8001373C(void *, f32, f32, f32, s32, s32, s32);
 ------------^
cfe: Error: /tmp/kig-screen-0vj5p7v_/candidate.c, line 505: Incompatible type for the function parameter
 extern void func_8001373C(void *, f32, f32, f32, s32, s32, s32);
 --------------------------^
```

### func_80015450 (prefix)

```text
cfe: Error: /tmp/kig-screen-l4inkqoc/candidate.c, line 884: redeclaration of 'D_801D3430'; previous declaration at line 514 in file '/tmp/kig-screen-l4inkqoc/candidate.c'
 extern T05518664Obj D_801D3430[40];
 --------------------^
```

### func_80029AB0 (declarations)

```text
cfe: Error: /tmp/kig-screen-rkst5a2x/candidate.c, line 86: redeclaration of 'D_80061D60'; previous declaration at line 76 in file '/tmp/kig-screen-rkst5a2x/candidate.c'
 extern T024Effect D_80061D60[];
 ------------------^
```

### func_801C6D40 (declarations)

```text
cfe: Error: /tmp/kig-screen-ugfbux24/candidate.c, line 375: redeclaration of 'D_802D3990'; previous declaration at line 178 in file '/tmp/kig-screen-ugfbux24/candidate.c'
 extern f32 D_802D3990;
 -----------^
cfe: Error: /tmp/kig-screen-ugfbux24/candidate.c, line 402: Type f32  of rhs of assignment expression is incompatible with type struct   of lhs
         D_802D3990 = (f32) ((f64) D_80291EBC + (var_f6 * D_802948B8));
 -------------------^
```

### func_800300DC (declarations)

```text
cfe: Error: /tmp/kig-screen-y7i1gj8u/candidate.c, line 49: redeclaration of 'func_800300DC'; previous declaration at line 15 in file '/tmp/kig-screen-y7i1gj8u/candidate.c'
 void func_800300DC(u8 *src, s32 outputAddress, s32 length) {
 -----^
cfe: Error: /tmp/kig-screen-y7i1gj8u/candidate.c, line 49: Incompatible type for the function parameter
 void func_800300DC(u8 *src, s32 outputAddress, s32 length) {
 -----------------------^
```

### func_800287D4 (prefix)

```text
cfe: Error: /tmp/kig-screen-omegv8o0/candidate.c, line 106: redeclaration of 'D_80061538'; previous declaration at line 66 in file '/tmp/kig-screen-omegv8o0/candidate.c'
 extern T024Particle D_80061538[][20];
 --------------------^
cfe: Error: /tmp/kig-screen-omegv8o0/candidate.c, line 109: 'active' undefined; reoccurrences will not be reported.
     D_80061538[group][index].active = 1;
 ----------------------------^
cfe: Error: /tmp/kig-screen-omegv8o0/candidate.c, line 109: member of structure or union required
     D_80061538[group][index].active = 1;
 -----------------------------^
```

### func_801BE790 (prefix)

```text
cfe: Error: /tmp/kig-screen-okxrr0fj/candidate.c, line 46: redeclaration of 'func_801BE910'; previous declaration at line 6 in file '/tmp/kig-screen-okxrr0fj/candidate.c'
 extern void func_801BE910(s32 *, s32, s32, s32);
 ------------^
cfe: Error: /tmp/kig-screen-okxrr0fj/candidate.c, line 46: Incompatible type for the function parameter
 extern void func_801BE910(s32 *, s32, s32, s32);
 --------------------------^
cfe: Error: /tmp/kig-screen-okxrr0fj/candidate.c, line 49: redeclaration of 'D_80127E50'; previous declaration at line 9 in file '/tmp/kig-screen-okxrr0fj/candidate.c'
 extern s32 D_80127E50;
 -----------^
cfe: Error: /tmp/kig-screen-okxrr0fj/candidate.c, line 50: redeclaration of 'D_80127EA0'; previous declaration at line 9 in file '/tmp/kig-screen-okxrr0fj/candidate.c'
 extern s32 D_80127EA0;
 -----------^
cfe: Error: /tmp/kig-screen-okxrr0fj/candidate.c, line 51: redeclaration of 'D_80127EF0'; previous declaration at line 9 in file '/tmp/kig-screen-okxrr0fj/candidate.c'
 extern s32 D_80127EF0;
 -----------^
cfe: Error: /tmp/kig-screen-okxrr0fj/candidate.c, line 52: redeclaration of 'D_80127F40'; previous declaration at line 9 in file '/tmp/kig-screen-okxrr0fj/candidate.c'
 extern s32 D_80127F40;
 -----------^
```

### func_800245B4 (declarations)

```text
cfe: Error: /tmp/kig-screen-3ore9qqu/candidate.c, line 171: redeclaration of 'D_8004D278'; previous declaration at line 144 in file '/tmp/kig-screen-3ore9qqu/candidate.c'
 extern T032Cache245 D_8004D278[];
 --------------------^
cfe: Error: /tmp/kig-screen-3ore9qqu/candidate.c, line 175: redeclaration of 'func_800245B4'; previous declaration at line 141 in file '/tmp/kig-screen-3ore9qqu/candidate.c'
 void func_800245B4(s32 player, u32 start, s32 size) {
 -----^
cfe: Error: /tmp/kig-screen-3ore9qqu/candidate.c, line 175: Incompatible type for the function parameter
 void func_800245B4(s32 player, u32 start, s32 size) {
 -----------------------------------^
cfe: Error: /tmp/kig-screen-3ore9qqu/candidate.c, line 176: Subscripting a non-array.
     T032Cache245 *bank = &D_8004D278[player];
 ------------------------------------^
```

### func_801BEEA4 (prefix)

```text
cfe: Error: /tmp/kig-screen-cxfgaz7m/candidate.c, line 53: redeclaration of 'func_801BEEA4'; previous declaration at line 16 in file '/tmp/kig-screen-cxfgaz7m/candidate.c'
 extern s32 func_801BEEA4(s32, s32, s32);
 -----------^
cfe: Error: /tmp/kig-screen-cxfgaz7m/candidate.c, line 53: Incompatible type for the function parameter
 extern s32 func_801BEEA4(s32, s32, s32);
 ------------------------------^
```

### func_8002B22C (prefix)

```text
cfe: Error: /tmp/kig-screen-jgm05_5a/candidate.c, line 139: redeclaration of 'D_80068158'; previous declaration at line 89 in file '/tmp/kig-screen-jgm05_5a/candidate.c'
 extern T024DmaPool D_80068158;
 -------------------^
cfe: Error: /tmp/kig-screen-jgm05_5a/candidate.c, line 141: redeclaration of 'func_8002B22C'; previous declaration at line 95 in file '/tmp/kig-screen-jgm05_5a/candidate.c'
 extern s32 func_8002B22C(s32, s32, void *);
 -----------^
cfe: Error: /tmp/kig-screen-jgm05_5a/candidate.c, line 141: Incompatible function return type for this function.
 extern s32 func_8002B22C(s32, s32, void *);
 ------------------------^
cfe: Error: /tmp/kig-screen-jgm05_5a/candidate.c, line 170: Unacceptable operand of == or !=
             if (D_80068158.used == dmaPtr) {
 --------------------------------^
```

### func_801BE910 (prefix)

```text
cfe: Error: /tmp/kig-screen-sbj4fbak/candidate.c, line 31: redeclaration of 'func_801BE910'; previous declaration at line 9 in file '/tmp/kig-screen-sbj4fbak/candidate.c'
 extern void func_801BE910(s32 *, s32, s32, s32);
 ------------^
cfe: Error: /tmp/kig-screen-sbj4fbak/candidate.c, line 31: Incompatible type for the function parameter
 extern void func_801BE910(s32 *, s32, s32, s32);
 --------------------------^
```

### func_8001CD50 (declarations)

```text
cfe: Error: /tmp/kig-screen-3t_955k6/candidate.c, line 86: 'D_8004EA9C' undefined; reoccurrences will not be reported.
     func_8001D37C((*(u8 *)((u8 *)(D_8004EA9C) + 0)), (*(u8 *)((u8 *)(D_8004EA9C) + 1)));
 ----------------------------------^
cfe: Error: /tmp/kig-screen-3t_955k6/candidate.c, line 104: redeclaration of 'func_8001CF1C'; previous declaration at line 15 in file '/tmp/kig-screen-3t_955k6/candidate.c'
 void func_8001CF1C(void) {
 -----^
cfe: Error: /tmp/kig-screen-3t_955k6/candidate.c, line 104: Incompatible function return type for this function.
 void func_8001CF1C(void) {
 ------------------^
cfe: Error: /tmp/kig-screen-3t_955k6/candidate.c, line 130: redeclaration of 'func_8001D37C'; previous declaration at line 17 in file '/tmp/kig-screen-3t_955k6/candidate.c'
 void func_8001D37C(u8 arg0, u8 arg1) {
 -----^
cfe: Error: /tmp/kig-screen-3t_955k6/candidate.c, line 130: Incompatible function return type for this function.
 void func_8001D37C(u8 arg0, u8 arg1) {
 ------------------^
cfe: Error: /tmp/kig-screen-3t_955k6/candidate.c, line 146: redeclaration of 'T022Sprite'; previous declaration at line 11 in file '/tmp/kig-screen-3t_955k6/candidate.c'
 } T022Sprite;
 --^
```

### func_8002DDD4 (prefix)

```text
cfe: Error: /tmp/kig-screen-mnc6z4it/candidate.c, line 116: redeclaration of 'func_8002DDD4'; previous declaration at line 106 in file '/tmp/kig-screen-mnc6z4it/candidate.c'
 extern void func_8002DDD4(float, float, float, float *, float *);
 ------------^
cfe: Error: /tmp/kig-screen-mnc6z4it/candidate.c, line 116: Incompatible type for the function parameter
 extern void func_8002DDD4(float, float, float, float *, float *);
 -----------------------------------------------^
```

### func_8002FB80 (prefix)

```text
cfe: Error: /tmp/kig-screen-bt1wn6hi/candidate.c, line 9: redeclaration of 'func_8002FB80'; previous declaration at line 4 in file '/tmp/kig-screen-bt1wn6hi/candidate.c'
 extern void func_8002FB80(s32, s32, s32, s32, s32);
 ------------^
cfe: Error: /tmp/kig-screen-bt1wn6hi/candidate.c, line 9: Incompatible type for the function parameter
 extern void func_8002FB80(s32, s32, s32, s32, s32);
 --------------------------^
```

### func_800191F0 (declarations)

```text
cfe: Error: /tmp/kig-screen-q_4sunot/candidate.c, line 1209: redeclaration of 'D_801D3430'; previous declaration at line 851 in file '/tmp/kig-screen-q_4sunot/candidate.c'
 extern u8 D_801D3430;
 ----------^
```

### func_801C8004 (declarations)

```text
cfe: Error: /tmp/kig-screen-oonwl6wo/candidate.c, line 125: redeclaration of 'D_80127C68'; previous declaration at line 7 in file '/tmp/kig-screen-oonwl6wo/candidate.c'
 extern u8 D_80127C68;
 ----------^
```

### func_800170C4 (declarations)

```text
cfe: Error: /tmp/kig-screen-1fv8tzun/candidate.c, line 1020: redeclaration of 'D_80045030'; previous declaration at line 892 in file '/tmp/kig-screen-1fv8tzun/candidate.c'
 extern u8 D_80045030;
 ----------^
cfe: Error: /tmp/kig-screen-1fv8tzun/candidate.c, line 1021: redeclaration of 'D_80045060'; previous declaration at line 893 in file '/tmp/kig-screen-1fv8tzun/candidate.c'
 extern T033170C4Vertex *D_80045060;
 ------------------------^
cfe: Error: /tmp/kig-screen-1fv8tzun/candidate.c, line 1026: redeclaration of 'D_8004AC8D'; previous declaration at line 13 in file '/tmp/kig-screen-1fv8tzun/candidate.c'
 extern u8 D_8004AC8D;
 ----------^
cfe: Error: /tmp/kig-screen-1fv8tzun/candidate.c, line 1027: redeclaration of 'D_8004AD28'; previous declaration at line 895 in file '/tmp/kig-screen-1fv8tzun/candidate.c'
 extern T033170C4Vertex D_8004AD28;
 -----------------------^
cfe: Error: /tmp/kig-screen-1fv8tzun/candidate.c, line 1028: redeclaration of 'D_8004ADE8'; previous declaration at line 896 in file '/tmp/kig-screen-1fv8tzun/candidate.c'
 extern T033170C4Vertex D_8004ADE8;
 -----------------------^
cfe: Error: /tmp/kig-screen-1fv8tzun/candidate.c, line 1038: redeclaration of 'D_801D3430'; previous declaration at line 851 in file '/tmp/kig-screen-1fv8tzun/candidate.c'
 extern T033170C4Object D_801D3430;
 -----------------------^
```

### func_8002FDA0 (prefix)

```text
cfe: Error: /tmp/kig-screen-rgjt541c/candidate.c, line 12: redeclaration of 'func_8002FDA0'; previous declaration at line 8 in file '/tmp/kig-screen-rgjt541c/candidate.c'
 extern void func_8002FDA0(s32, s32, s32);
 ------------^
cfe: Error: /tmp/kig-screen-rgjt541c/candidate.c, line 12: Incompatible type for the function parameter
 extern void func_8002FDA0(s32, s32, s32);
 --------------------------^
```

### func_8001BB64 (declarations)

```text
cfe: Error: /tmp/kig-screen-13e78t16/candidate.c, line 1429: redeclaration of 'D_8004AC92'; previous declaration at line 17 in file '/tmp/kig-screen-13e78t16/candidate.c'
 extern u8 D_8004AA28,D_801D7DFC,D_801D7DF8,D_8004AC92,D_8004AC8E;
 -------------------------------------------^
cfe: Error: /tmp/kig-screen-13e78t16/candidate.c, line 1429: redeclaration of 'D_8004AC8E'; previous declaration at line 17 in file '/tmp/kig-screen-13e78t16/candidate.c'
 extern u8 D_8004AA28,D_801D7DFC,D_801D7DF8,D_8004AC92,D_8004AC8E;
 ------------------------------------------------------^
cfe: Error: /tmp/kig-screen-13e78t16/candidate.c, line 1448: Unacceptable operand of == or !=
     } while (src != &D_8004AC92 + 3);
 -----------------^
cfe: Error: /tmp/kig-screen-13e78t16/candidate.c, line 1458: Unacceptable operand of shift operator.
         cmd->w1 = ((&D_8004AC8E)[1] << 16) | ((&D_8004AC8E)[0] << 24) | ((b & 255) << 8) | 255;
 --------------------------------^
cfe: Error: /tmp/kig-screen-13e78t16/candidate.c, line 1476: Unacceptable operand of shift operator.
         cmd->w1 = ((&D_8004AC8E)[2] << 8) | (r << 24) | ((&D_8004AC8E)[1] << 16) | 255;
 --------------------------------^
```

### func_80017A68 (declarations)

```text
cfe: Error: /tmp/kig-screen-5tiffd7k/candidate.c, line 1029: redeclaration of 'D_8004A5E0'; previous declaration at line 5 in file '/tmp/kig-screen-5tiffd7k/candidate.c'
 extern s8 D_8004A5E0;
 ----------^
cfe: Error: /tmp/kig-screen-5tiffd7k/candidate.c, line 1034: redeclaration of 'D_8004AA29'; previous declaration at line 13 in file '/tmp/kig-screen-5tiffd7k/candidate.c'
 extern u8 D_8004AA29;
 ----------^
cfe: Error: /tmp/kig-screen-5tiffd7k/candidate.c, line 1035: redeclaration of 'D_8004AC8D'; previous declaration at line 13 in file '/tmp/kig-screen-5tiffd7k/candidate.c'
 extern u8 D_8004AC8D;
 ----------^
cfe: Error: /tmp/kig-screen-5tiffd7k/candidate.c, line 1100: This expression is not an lvalue.
         (&D_8004A5E0)[35] = 0xF;
 --------------------------^
cfe: Error: /tmp/kig-screen-5tiffd7k/candidate.c, line 1101: This expression is not an lvalue.
         (&D_8004A5E0)[42] = 0x17;
 --------------------------^
cfe: Error: /tmp/kig-screen-5tiffd7k/candidate.c, line 1103: This expression is not an lvalue.
         (&D_8004A5E0)[35] = 0x17;
 --------------------------^
cfe: Error: /tmp/kig-screen-5tiffd7k/candidate.c, line 1104: This expression is not an lvalue.
         (&D_8004A5E0)[42] = 0xF;
 --------------------------^
```

### func_801C1990 (declarations)

```text
cfe: Error: /tmp/kig-screen-8z82xmrs/candidate.c, line 107: redeclaration of 'D_80128310'; previous declaration at line 87 in file '/tmp/kig-screen-8z82xmrs/candidate.c'
 extern u8 D_80128308[], D_8012830A[], D_80128310[], D_80128328[];
 --------------------------------------^
cfe: Error: /tmp/kig-screen-8z82xmrs/candidate.c, line 107: redeclaration of 'D_80128328'; previous declaration at line 87 in file '/tmp/kig-screen-8z82xmrs/candidate.c'
 extern u8 D_80128308[], D_8012830A[], D_80128310[], D_80128328[];
 ----------------------------------------------------^
```

### func_800241BC (prefix)

```text
cfe: Error: /tmp/kig-screen-an9w2zsj/candidate.c, line 222: redeclaration of 'D_8004D278'; previous declaration at line 141 in file '/tmp/kig-screen-an9w2zsj/candidate.c'
 extern struct { u8 pad[0x12A8]; T032Bank banks[2]; } D_8004D278;
 -----------------------------------------------------^
cfe: Error: /tmp/kig-screen-an9w2zsj/candidate.c, line 243: Selector requires struct/union as left hand side
   D_8004D278.banks[player].data = base;
 ------------^
cfe: Error: /tmp/kig-screen-an9w2zsj/candidate.c, line 244: Selector requires struct/union as left hand side
   D_8004D278.banks[player].zero = 0;
 ------------^
```

### func_801ACB1C (prefix)

```text
cfe: Error: /tmp/kig-screen-9x38dstf/candidate.c, line 284: redeclaration of 'func_801AD3BC'; previous declaration at line 62 in file '/tmp/kig-screen-9x38dstf/candidate.c'
 void func_801AD3BC(DisplayCommand **arg0, RenderState *arg1) {
 -----^
cfe: Error: /tmp/kig-screen-9x38dstf/candidate.c, line 284: Incompatible type for the function parameter
 void func_801AD3BC(DisplayCommand **arg0, RenderState *arg1) {
 ------------------------------------^
```

### func_801C1434 (declarations)

```text
cfe: Error: /tmp/kig-screen-danqtu2p/candidate.c, line 84: redeclaration of 'func_801C0610'; previous declaration at line 64 in file '/tmp/kig-screen-danqtu2p/candidate.c'
 extern void func_801C0610(s32);
 ------------^
cfe: Error: /tmp/kig-screen-danqtu2p/candidate.c, line 84: The number of parameters for function is different from the previous declaration
 extern void func_801C0610(s32);
 -------------------------^
cfe: Error: /tmp/kig-screen-danqtu2p/candidate.c, line 93: The number of arguments doesn't agree with the number in the declaration.
     func_801C0610(list);
 -----------------^
```

### func_8001D080 (declarations)

```text
cfe: Error: /tmp/kig-screen-pex1pe3p/candidate.c, line 106: 'D_8004AC88' undefined; reoccurrences will not be reported.
     if (D_8004AC88 == 0xC) {
 --------^
cfe: Error: /tmp/kig-screen-pex1pe3p/candidate.c, line 143: redeclaration of 'T022Sprite'; previous declaration at line 35 in file '/tmp/kig-screen-pex1pe3p/candidate.c'
 } T022Sprite;
 --^
```

### func_800131A4 (declarations)

```text
cfe: Error: /tmp/kig-screen-7plze7u3/candidate.c, line 79: redeclaration of 'D_8004A738'; previous declaration at line 4 in file '/tmp/kig-screen-7plze7u3/candidate.c'
 extern s8 D_8004A738, D_8004A688;
 ----------^
cfe: Error: /tmp/kig-screen-7plze7u3/candidate.c, line 79: redeclaration of 'D_8004A688'; previous declaration at line 6 in file '/tmp/kig-screen-7plze7u3/candidate.c'
 extern s8 D_8004A738, D_8004A688;
 ----------------------^
cfe: Error: /tmp/kig-screen-7plze7u3/candidate.c, line 117: Unacceptable operand of relational operator.
     if ((&D_8004A738)[part] > 0) {
 ----------------------------^
cfe: Error: /tmp/kig-screen-7plze7u3/candidate.c, line 125: Unacceptable operand of relational operator.
         } while (i < (&D_8004A738)[part]);
 -------------------^
```

### func_8001808C (declarations)

```text
cfe: Error: /tmp/kig-screen-welc2q6o/candidate.c, line 1041: redeclaration of 'D_8004A5E0'; previous declaration at line 5 in file '/tmp/kig-screen-welc2q6o/candidate.c'
 extern s8 D_8004A5E0;
 ----------^
cfe: Error: /tmp/kig-screen-welc2q6o/candidate.c, line 1042: redeclaration of 'D_8004A730'; previous declaration at line 3 in file '/tmp/kig-screen-welc2q6o/candidate.c'
 extern s8 D_8004A730;
 ----------^
cfe: Error: /tmp/kig-screen-welc2q6o/candidate.c, line 1043: redeclaration of 'D_8004A738'; previous declaration at line 4 in file '/tmp/kig-screen-welc2q6o/candidate.c'
 extern s8 D_8004A738;
 ----------^
cfe: Error: /tmp/kig-screen-welc2q6o/candidate.c, line 1047: redeclaration of 'D_8004AC89'; previous declaration at line 116 in file '/tmp/kig-screen-welc2q6o/candidate.c'
 extern s8 D_8004AC89;
 ----------^
cfe: Error: /tmp/kig-screen-welc2q6o/candidate.c, line 1048: redeclaration of 'D_8004AC8A'; previous declaration at line 117 in file '/tmp/kig-screen-welc2q6o/candidate.c'
 extern s8 D_8004AC8A;
 ----------^
cfe: Error: /tmp/kig-screen-welc2q6o/candidate.c, line 1067: redeclaration of 'D_800614D8'; previous declaration at line 121 in file '/tmp/kig-screen-welc2q6o/candidate.c'
 extern u8 D_800614D8;
 ----------^
cfe: Error: /tmp/kig-screen-welc2q6o/candidate.c, line 1069: redeclaration of 'D_80061CB8'; previous declaration at line 123 in file '/tmp/kig-screen-welc2q6o/candidate.c'
 extern u8 D_80061CB8;
 ----------^
cfe: Error: /tmp/kig-screen-welc2q6o/candidate.c, line 1104: This expression is not an lvalue.
     D_8004A730 = 9;
 ---------------^
cfe: Error: /tmp/kig-screen-welc2q6o/candidate.c, line 1114: This expression is not an lvalue.
     D_8004A738 = 0;
 ---------------^
cfe: Error: /tmp/kig-screen-welc2q6o/candidate.c, line 1165: redeclaration of 'T022Position'; previous declaration at line 1027 in file '/tmp/kig-screen-welc2q6o/candidate.c'
 typedef struct { u8 pad[0x28]; s16 x, y, z; } T022Position;
 ----------------------------------------------^
```

### func_801B2B8C (prefix)

```text
cfe: Error: /tmp/kig-screen-cjvxzkqn/candidate.c, line 276: redeclaration of 'func_8002F6F4'; previous declaration at line 46 in file '/tmp/kig-screen-cjvxzkqn/candidate.c'
 extern void func_8002F6F4(s32, s32, void *);
 ------------^
cfe: Error: /tmp/kig-screen-cjvxzkqn/candidate.c, line 276: Incompatible function return type for this function.
 extern void func_8002F6F4(s32, s32, void *);
 -------------------------^
```

### func_800193DC (declarations)

```text
cfe: Error: /tmp/kig-screen-8gqepvkm/candidate.c, line 1212: redeclaration of 'D_8004A5E0'; previous declaration at line 5 in file '/tmp/kig-screen-8gqepvkm/candidate.c'
 extern s8 D_8004A5E0;
 ----------^
cfe: Error: /tmp/kig-screen-8gqepvkm/candidate.c, line 1213: redeclaration of 'D_8004A738'; previous declaration at line 4 in file '/tmp/kig-screen-8gqepvkm/candidate.c'
 extern s8 D_8004A738;
 ----------^
cfe: Error: /tmp/kig-screen-8gqepvkm/candidate.c, line 1214: redeclaration of 'D_8004AC89'; previous declaration at line 116 in file '/tmp/kig-screen-8gqepvkm/candidate.c'
 extern s8 D_8004AC89;
 ----------^
cfe: Error: /tmp/kig-screen-8gqepvkm/candidate.c, line 1215: redeclaration of 'D_8004AC8A'; previous declaration at line 117 in file '/tmp/kig-screen-8gqepvkm/candidate.c'
 extern s8 D_8004AC8A;
 ----------^
cfe: Error: /tmp/kig-screen-8gqepvkm/candidate.c, line 1243: redeclaration of 'D_800614D8'; previous declaration at line 121 in file '/tmp/kig-screen-8gqepvkm/candidate.c'
 extern u8 D_800614D8;
 ----------^
cfe: Error: /tmp/kig-screen-8gqepvkm/candidate.c, line 1245: redeclaration of 'D_80061CB8'; previous declaration at line 123 in file '/tmp/kig-screen-8gqepvkm/candidate.c'
 extern u8 D_80061CB8;
 ----------^
cfe: Error: /tmp/kig-screen-8gqepvkm/candidate.c, line 1279: This expression is not an lvalue.
     D_8004A738 = 0;
 ---------------^
```

### func_80018AE0 (declarations)

```text
cfe: Error: /tmp/kig-screen-37q1m5fx/candidate.c, line 1203: redeclaration of 'D_800614D8'; previous declaration at line 121 in file '/tmp/kig-screen-37q1m5fx/candidate.c'
 extern u8 D_800614D8;
 ----------^
cfe: Error: /tmp/kig-screen-37q1m5fx/candidate.c, line 1204: redeclaration of 'D_80061520'; previous declaration at line 122 in file '/tmp/kig-screen-37q1m5fx/candidate.c'
 extern s8 D_80061520;
 ----------^
cfe: Error: /tmp/kig-screen-37q1m5fx/candidate.c, line 1205: redeclaration of 'D_80061CB8'; previous declaration at line 123 in file '/tmp/kig-screen-37q1m5fx/candidate.c'
 extern u8 D_80061CB8;
 ----------^
cfe: Error: /tmp/kig-screen-37q1m5fx/candidate.c, line 1264: This expression is not an lvalue.
     D_8004A730 = 9;
 ---------------^
cfe: Error: /tmp/kig-screen-37q1m5fx/candidate.c, line 1274: This expression is not an lvalue.
     D_8004A738 = 0;
 ---------------^
```

### func_8002AB90 (prefix)

```text
cfe: Error: /tmp/kig-screen-9nmqcaqs/candidate.c, line 95: redeclaration of 'D_80067ED8'; previous declaration at line 9 in file '/tmp/kig-screen-9nmqcaqs/candidate.c'
 extern T024DmaBuffer D_80067ED8[];
 ---------------------^
cfe: Error: /tmp/kig-screen-9nmqcaqs/candidate.c, line 98: redeclaration of 'func_8002B3A8'; previous declaration at line 12 in file '/tmp/kig-screen-9nmqcaqs/candidate.c'
 void *func_8002B3A8(T024DmaPool **state) {
 ------^
cfe: Error: /tmp/kig-screen-9nmqcaqs/candidate.c, line 98: Incompatible function return type for this function.
 void *func_8002B3A8(T024DmaPool **state) {
 -------------------^
```

### func_801C90D4 (declarations)

```text
cfe: Error: /tmp/kig-screen-g_giozh3/candidate.c, line 272: redeclaration of 'D_802D39FC'; previous declaration at line 39 in file '/tmp/kig-screen-g_giozh3/candidate.c'
 extern u8 D_802D39FC;
 ----------^
```

### func_801BB7B4 (declarations)

```text
cfe: Error: /tmp/kig-screen-jchgku13/candidate.c, line 224: redeclaration of 'func_8002F6F4'; previous declaration at line 179 in file '/tmp/kig-screen-jchgku13/candidate.c'
 extern s32 func_8002F6F4();
 -----------^
cfe: Error: /tmp/kig-screen-jchgku13/candidate.c, line 224: Incompatible function return type for this function.
 extern s32 func_8002F6F4();
 ------------------------^
cfe: Error: /tmp/kig-screen-jchgku13/candidate.c, line 232: redeclaration of 'D_80127CE8'; previous declaration at line 80 in file '/tmp/kig-screen-jchgku13/candidate.c'
 extern u8 D_80127CE8[];
 ----------^
cfe: Error: /tmp/kig-screen-jchgku13/candidate.c, line 236: redeclaration of 'D_802C8CB8'; previous declaration at line 62 in file '/tmp/kig-screen-jchgku13/candidate.c'
 extern u8 D_802C8CB8;
 ----------^
cfe: Error: /tmp/kig-screen-jchgku13/candidate.c, line 239: redeclaration of 'D_802C8CEA'; previous declaration at line 84 in file '/tmp/kig-screen-jchgku13/candidate.c'
 extern u8 D_802C8CEA;
 ----------^
cfe: Error: /tmp/kig-screen-jchgku13/candidate.c, line 269: Unacceptable operand of a multiplicative operator.
             temp_a1 = *(s32 *)(D_801F2EB8 + (D_80127CE8[D_802C8D0D] * 0x8C));
 -------------------------------------------------------^
cfe: Error: /tmp/kig-screen-jchgku13/candidate.c, line 285: Unacceptable operand of a multiplicative operator.
             func_8002F6F4(D_80066C40, *(s32 *)(D_801F2EB8 + (D_802C8CB8 * 0x8C)), &D_8004A258);
 -------------------------------------------------------------^
```

### func_801C23C0 (prefix)

```text
cfe: Error: /tmp/kig-screen-igegbytg/candidate.c, line 305: redeclaration of 'D_802C9F70'; previous declaration at line 153 in file '/tmp/kig-screen-igegbytg/candidate.c'
 extern T030Render2D34 D_802C9F70;
 ----------------------^
cfe: Error: /tmp/kig-screen-igegbytg/candidate.c, line 307: redeclaration of 'func_801C2D34'; previous declaration at line 138 in file '/tmp/kig-screen-igegbytg/candidate.c'
 void func_801C2D34(T030Cmd2D34 **arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
 -----^
cfe: Error: /tmp/kig-screen-igegbytg/candidate.c, line 307: Incompatible type for the function parameter
 void func_801C2D34(T030Cmd2D34 **arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
 ---------------------------------^
```

### func_801C317C (declarations)

```text
cfe: Error: /tmp/kig-screen-6d3lxw87/candidate.c, line 191: redeclaration of 'D_802C9F70'; previous declaration at line 135 in file '/tmp/kig-screen-6d3lxw87/candidate.c'
 extern T030Render317C D_802C9F70;
 ----------------------^
```

### func_80031A38 (declarations)

```text
cfe: Error: /tmp/kig-screen-izvfjcsw/candidate.c, line 12: Syntax Error
     T022Sprite *sprite = &D_8004CED0[D_8004EA78];
 -----------------------^
cfe: Error: /tmp/kig-screen-izvfjcsw/candidate.c, line 13: Syntax Error
     u8 *out = sprite->data;
 -------^
cfe: Error: /tmp/kig-screen-izvfjcsw/candidate.c, line 14: Syntax Error
     s32 width = input[4] + (input[5]<<8);
 --------^
cfe: Error: /tmp/kig-screen-izvfjcsw/candidate.c, line 15: Syntax Error
     s32 height = input[6] + (input[7]<<8);
 --------^
cfe: Error: /tmp/kig-screen-izvfjcsw/candidate.c, line 16: Syntax Error
     s32 stride = (width+7)&0xFFF8;
 --------^
cfe: Error: /tmp/kig-screen-izvfjcsw/candidate.c, line 17: Syntax Error
     s32 y;
 --------^
```

### func_800216D4 (prefix)

```text
cfe: Error: /tmp/kig-screen-hbz6spzz/candidate.c, line 208: redeclaration of 'D_8004D278'; previous declaration at line 90 in file '/tmp/kig-screen-hbz6spzz/candidate.c'
 extern struct { u8 pad[0x12A8]; T032Bank banks[2]; } D_8004D278;
 -----------------------------------------------------^
cfe: Error: /tmp/kig-screen-hbz6spzz/candidate.c, line 229: Selector requires struct/union as left hand side
   D_8004D278.banks[player].data = base;
 ------------^
cfe: Error: /tmp/kig-screen-hbz6spzz/candidate.c, line 230: Selector requires struct/union as left hand side
   D_8004D278.banks[player].zero = 0;
 ------------^
```

### func_801AF68C (prefix)

```text
cfe: Error: /tmp/kig-screen-a3pzbx31/candidate.c, line 151: redeclaration of 'D_802A1A60'; previous declaration at line 85 in file '/tmp/kig-screen-a3pzbx31/candidate.c'
 extern s32 D_802A1A60[];
 -----------^
```

### func_801C1C34 (prefix)

```text
cfe: Error: /tmp/kig-screen-q4z77kb8/candidate.c, line 186: redeclaration of 'D_802C9F70'; previous declaration at line 112 in file '/tmp/kig-screen-q4z77kb8/candidate.c'
 extern T030Render2D34 D_802C9F70;
 ----------------------^
```

### func_80029BE0 (declarations)

```text
cfe: Error: /tmp/kig-screen-cljya0c6/candidate.c, line 89: redeclaration of 'D_80061D60'; previous declaration at line 76 in file '/tmp/kig-screen-cljya0c6/candidate.c'
 extern T024DrawBurst D_80061D60[];
 ---------------------^
cfe: Error: /tmp/kig-screen-cljya0c6/candidate.c, line 99: redeclaration of 'func_8002A004'; previous declaration at line 92 in file '/tmp/kig-screen-cljya0c6/candidate.c'
 void func_8002A004(float m[4][4], float x, float y, float z) {
 -----^
cfe: Error: /tmp/kig-screen-cljya0c6/candidate.c, line 99: Incompatible type for the function parameter
 void func_8002A004(float m[4][4], float x, float y, float z) {
 -------------------------^
```

### func_80015594 (declarations)

```text
cfe: Error: /tmp/kig-screen-1fxaodvl/candidate.c, line 509: redeclaration of 'func_80015594'; previous declaration at line 146 in file '/tmp/kig-screen-1fxaodvl/candidate.c'
 void func_80015594(T03315594Command **arg0,s32 *arg1,f32 arg2,s32 arg3,f32 arg4,f32 arg5,f32 arg6) {
 -----^
cfe: Error: /tmp/kig-screen-1fxaodvl/candidate.c, line 509: prototype and non-prototype declaration found for func_80015594, the type of this parameter is not compatible with the type after applying default argument promotion
 void func_80015594(T03315594Command **arg0,s32 *arg1,f32 arg2,s32 arg3,f32 arg4,f32 arg5,f32 arg6) {
 ---------------------------------------------------------^
```

### func_80031DD0 (declarations)

```text
cfe: Error: /tmp/kig-screen-rfma1ia2/candidate.c, line 16: Syntax Error
     T022Sprite *sprite = &D_8004CED0[D_8004EA78];
 -----------------------^
cfe: Error: /tmp/kig-screen-rfma1ia2/candidate.c, line 17: Syntax Error
     u8 *intensity = sprite->data;
 -------^
cfe: Error: /tmp/kig-screen-rfma1ia2/candidate.c, line 18: Syntax Error
     u16 *color = (u16 *)sprite->unk0;
 --------^
cfe: Error: /tmp/kig-screen-rfma1ia2/candidate.c, line 18: Syntax Error
     u16 *color = (u16 *)sprite->unk0;
 -----------------------^
cfe: Error: /tmp/kig-screen-rfma1ia2/candidate.c, line 19: Syntax Error
     u16 *palette = D_800482D0[((s16 *)sprite)[13]];
 --------^
cfe: Error: /tmp/kig-screen-rfma1ia2/candidate.c, line 19: Syntax Error
     u16 *palette = D_800482D0[((s16 *)sprite)[13]];
 -------------------------------------^
cfe: Error: /tmp/kig-screen-rfma1ia2/candidate.c, line 21: Syntax Error
     s32 top = vertical >> 16;
 --------^
cfe: Error: /tmp/kig-screen-rfma1ia2/candidate.c, line 22: Syntax Error
     s32 height = input[6] + (input[7]<<8);
 --------^
cfe: Error: /tmp/kig-screen-rfma1ia2/candidate.c, line 23: Syntax Error
     s32 y;
 --------^
```

### func_80014D5C (prefix)

```text
cfe: Error: /tmp/kig-screen-vbxiwep_/candidate.c, line 810: redeclaration of 'func_8002F8F8'; previous declaration at line 527 in file '/tmp/kig-screen-vbxiwep_/candidate.c'
 extern void func_8002F8F8(void *);
 ------------^
cfe: Error: /tmp/kig-screen-vbxiwep_/candidate.c, line 810: Incompatible function return type for this function.
 extern void func_8002F8F8(void *);
 -------------------------^
cfe: Error: /tmp/kig-screen-vbxiwep_/candidate.c, line 811: redeclaration of 'func_8002F6F4'; previous declaration at line 526 in file '/tmp/kig-screen-vbxiwep_/candidate.c'
 extern void *func_8002F6F4(void *, s16, void **);
 -------------^
cfe: Error: /tmp/kig-screen-vbxiwep_/candidate.c, line 811: Incompatible function return type for this function.
 extern void *func_8002F6F4(void *, s16, void **);
 --------------------------^
```

### func_80012B7C (declarations)

```text
cfe: Error: /tmp/kig-screen-ccnx1m1k/candidate.c, line 76: redeclaration of 'D_8004A730'; previous declaration at line 3 in file '/tmp/kig-screen-ccnx1m1k/candidate.c'
 extern s8 D_8004A730, D_8004A5E0;
 ----------^
cfe: Error: /tmp/kig-screen-ccnx1m1k/candidate.c, line 76: redeclaration of 'D_8004A5E0'; previous declaration at line 5 in file '/tmp/kig-screen-ccnx1m1k/candidate.c'
 extern s8 D_8004A730, D_8004A5E0;
 ----------------------^
```

### func_8001D7E4 (prefix)

```text
cfe: Error: /tmp/kig-screen-hz470w24/candidate.c, line 352: redeclaration of 'D_8004D278'; previous declaration at line 79 in file '/tmp/kig-screen-hz470w24/candidate.c'
 extern struct { u8 pad[0x12A8]; T032Bank banks[2]; } D_8004D278;
 -----------------------------------------------------^
cfe: Error: /tmp/kig-screen-hz470w24/candidate.c, line 353: redeclaration of 'func_800244F0'; previous declaration at line 73 in file '/tmp/kig-screen-hz470w24/candidate.c'
 void func_800244F0(s32 player)
 -----^
cfe: Error: /tmp/kig-screen-hz470w24/candidate.c, line 353: Incompatible function return type for this function.
 void func_800244F0(s32 player)
 ------------------^
cfe: Error: /tmp/kig-screen-hz470w24/candidate.c, line 373: Selector requires struct/union as left hand side
   D_8004D278.banks[player].data = base;
 ------------^
cfe: Error: /tmp/kig-screen-hz470w24/candidate.c, line 374: Selector requires struct/union as left hand side
   D_8004D278.banks[player].zero = 0;
 ------------^
```

### func_80020E98 (prefix)

```text
cfe: Error: /tmp/kig-screen-b29xkqar/candidate.c, line 287: redeclaration of 'D_8004D278'; previous declaration at line 93 in file '/tmp/kig-screen-b29xkqar/candidate.c'
 extern struct { u8 pad[0x12A8]; T032Bank banks[2]; } D_8004D278;
 -----------------------------------------------------^
cfe: Error: /tmp/kig-screen-b29xkqar/candidate.c, line 308: Selector requires struct/union as left hand side
   D_8004D278.banks[player].data = base;
 ------------^
cfe: Error: /tmp/kig-screen-b29xkqar/candidate.c, line 309: Selector requires struct/union as left hand side
   D_8004D278.banks[player].zero = 0;
 ------------^
```

### func_801C5E74 (declarations)

```text
cfe: Error: /tmp/kig-screen-dfcjmd0h/candidate.c, line 265: redeclaration of 'func_801C51F8'; previous declaration at line 226 in file '/tmp/kig-screen-dfcjmd0h/candidate.c'
 extern void func_801C51F8(T030Cmd5E74 **);
 ------------^
cfe: Error: /tmp/kig-screen-dfcjmd0h/candidate.c, line 265: Incompatible type for the function parameter
 extern void func_801C51F8(T030Cmd5E74 **);
 --------------------------^
```

### func_8001178C (prefix)

```text
cfe: Error: /tmp/kig-screen-2nwmv29j/candidate.c, line 347: redeclaration of 'func_80011FC4'; previous declaration at line 96 in file '/tmp/kig-screen-2nwmv29j/candidate.c'
 s32 func_80011FC4(T020Controller *arg0, u8 arg1) {
 ----^
cfe: Error: /tmp/kig-screen-2nwmv29j/candidate.c, line 347: prototype and non-prototype declaration found for func_80011FC4, the type of this parameter is not compatible with the type after applying default argument promotion
 s32 func_80011FC4(T020Controller *arg0, u8 arg1) {
 -------------------------------------------^
cfe: Error: /tmp/kig-screen-2nwmv29j/candidate.c, line 379: redeclaration of 'func_80012100'; previous declaration at line 97 in file '/tmp/kig-screen-2nwmv29j/candidate.c'
 void func_80012100(u8 arg0, u8 arg1) {
 -----^
cfe: Error: /tmp/kig-screen-2nwmv29j/candidate.c, line 379: prototype and non-prototype declaration found for func_80012100, the type of this parameter is not compatible with the type after applying default argument promotion
 void func_80012100(u8 arg0, u8 arg1) {
 ----------------------^
cfe: Error: /tmp/kig-screen-2nwmv29j/candidate.c, line 468: redeclaration of 'D_8004A258'; previous declaration at line 56 in file '/tmp/kig-screen-2nwmv29j/candidate.c'
 extern void *D_8004A258[];
 -------------^
cfe: Error: /tmp/kig-screen-2nwmv29j/candidate.c, line 475: Subscripting a non-array.
         if (D_8004A258[i] != 0) {
 ----------------------^
cfe: Error: /tmp/kig-screen-2nwmv29j/candidate.c, line 476: Subscripting a non-array.
             func_8002F8F8(D_8004A258[i]);
 ------------------------------------^
```

### func_800142E0 (declarations)

```text
cfe: Error: /tmp/kig-screen-iskpa3ot/candidate.c, line 485: redeclaration of 'func_800142E0'; previous declaration at line 307 in file '/tmp/kig-screen-iskpa3ot/candidate.c'
 void func_800142E0(T033142E0Command **arg0, s32 *arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6) {
 -----^
cfe: Error: /tmp/kig-screen-iskpa3ot/candidate.c, line 485: prototype and non-prototype declaration found for func_800142E0, the type of this parameter is not compatible with the type after applying default argument promotion
 void func_800142E0(T033142E0Command **arg0, s32 *arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6) {
 -------------------------------------------------------------------------------^
```

### func_801BFCBC (declarations)

```text
cfe: Error: /tmp/kig-screen-i64n_od3/candidate.c, line 65: redeclaration of 'D_802D37D8'; previous declaration at line 15 in file '/tmp/kig-screen-i64n_od3/candidate.c'
 extern s32 D_8004A25C, D_8004A278, D_80066C40, D_802D37D0, D_802D37D8[], D_802D37E0[], D_802D37F0[], D_802D3818[], D_802D3820, D_802D3824;
 -----------------------------------------------------------^
cfe: Error: /tmp/kig-screen-i64n_od3/candidate.c, line 65: redeclaration of 'D_802D37E0'; previous declaration at line 15 in file '/tmp/kig-screen-i64n_od3/candidate.c'
 extern s32 D_8004A25C, D_8004A278, D_80066C40, D_802D37D0, D_802D37D8[], D_802D37E0[], D_802D37F0[], D_802D3818[], D_802D3820, D_802D3824;
 -------------------------------------------------------------------------^
cfe: Error: /tmp/kig-screen-i64n_od3/candidate.c, line 65: redeclaration of 'D_802D37F0'; previous declaration at line 15 in file '/tmp/kig-screen-i64n_od3/candidate.c'
 extern s32 D_8004A25C, D_8004A278, D_80066C40, D_802D37D0, D_802D37D8[], D_802D37E0[], D_802D37F0[], D_802D3818[], D_802D3820, D_802D3824;
 ---------------------------------------------------------------------------------------^
cfe: Error: /tmp/kig-screen-i64n_od3/candidate.c, line 66: redeclaration of 'D_80128300'; previous declaration at line 15 in file '/tmp/kig-screen-i64n_od3/candidate.c'
 extern u32 D_80128300[];
 -----------^
cfe: Error: /tmp/kig-screen-i64n_od3/candidate.c, line 83: Subscripting a non-array.
         y = D_802D37E0[player]; x = D_802D37D8[player]; cursor = D_802D37EA[player];
 ----------------------^
cfe: Error: /tmp/kig-screen-i64n_od3/candidate.c, line 83: Subscripting a non-array.
         y = D_802D37E0[player]; x = D_802D37D8[player]; cursor = D_802D37EA[player];
 ----------------------------------------------^
cfe: Error: /tmp/kig-screen-i64n_od3/candidate.c, line 86: Subscripting a non-array.
             D_802D37E0[player] = y - 1;
 ----------------------^
cfe: Error: /tmp/kig-screen-i64n_od3/candidate.c, line 87: Subscripting a non-array.
             if (y - 1 < 0) D_802D37E0[player] = 0;
 -------------------------------------^
cfe: Error: /tmp/kig-screen-i64n_od3/candidate.c, line 91: Subscripting a non-array.
             value = D_802D37E0[player] + 1; D_802D37E0[player] = value;
 ------------------------------^
cfe: Error: /tmp/kig-screen-i64n_od3/candidate.c, line 91: Subscripting a non-array.
             value = D_802D37E0[player] + 1; D_802D37E0[player] = value;
 ------------------------------------------------------^
cfe: Error: /tmp/kig-screen-i64n_od3/candidate.c, line 92: Subscripting a non-array.
             if (value >= 33) D_802D37E0[player] = 32;
 ---------------------------------------^
cfe: Error: /tmp/kig-screen-i64n_od3/candidate.c, line 94: Subscripting a non-array.
         } else if (!(buttons & 0x800) && (D_802D37E0[player] & 7)) {
 ----------------------------------------------------^
cfe: Error: /tmp/kig-screen-i64n_od3/candidate.c, line 95: Subscripting a non-array.
             if (D_802D37E8[player] & 1) D_802D37E0[player]++;
 --------------------------------------------------^
cfe: Error: /tmp/kig-screen-i64n_od3/candidate.c, line 96: Subscripting a non-array.
             else D_802D37E0[player]--;
 ---------------------------^
cfe: Error: /tmp/kig-screen-i64n_od3/candidate.c, line 99: Subscripting a non-array.
             D_802D37D8[player] = x - 1;
 ----------------------^
cfe: Error: /tmp/kig-screen-i64n_od3/candidate.c, line 100: Subscripting a non-array.
             if (x - 1 < 0) D_802D37D8[player] = 0;
 -------------------------------------^
cfe: Error: /tmp/kig-screen-i64n_od3/candidate.c, line 104: Subscripting a non-array.
             value = D_802D37D8[player] + 1; D_802D37D8[player] = value;
 ------------------------------^
cfe: Error: /tmp/kig-screen-i64n_od3/candidate.c, line 104: Subscripting a non-array.
             value = D_802D37D8[player] + 1; D_802D37D8[player] = value;
 ------------------------------------------------------^
cfe: Error: /tmp/kig-screen-i64n_od3/candidate.c, line 105: Subscripting a non-array.
             if (value >= 41) D_802D37D8[player] = 40;
 ---------------------------------------^
cfe: Error: /tmp/kig-screen-i64n_od3/candidate.c, line 107: Subscripting a non-array.
         } else if (!(buttons & 0x200) && (D_802D37D8[player] & 7)) {
 ----------------------------------------------------^
cfe: Error: /tmp/kig-screen-i64n_od3/candidate.c, line 108: Subscripting a non-array.
             if (D_802D37E8[player] & 2) D_802D37D8[player]++;
 --------------------------------------------------^
cfe: Error: /tmp/kig-screen-i64n_od3/candidate.c, line 109: Subscripting a non-array.
             else D_802D37D8[player]--;
 ---------------------------^
cfe: Error: /tmp/kig-screen-i64n_od3/candidate.c, line 115: Subscripting a non-array.
             D_802D37F0[player] = (D_802D37F0[player] & ~(255 << shift)) | (value << shift);
 --------------------------------------------^
cfe: Error: /tmp/kig-screen-i64n_od3/candidate.c, line 123: Subscripting a non-array.
             func_801BED0C(D_802D37F0[player], D_802D3800[player]);
 ------------------------------------^
cfe: Error: /tmp/kig-screen-i64n_od3/candidate.c, line 125: Subscripting a non-array.
             D_80128300[player] = D_802D37F0[player];
 -------------------------------------------^
```

### func_801C9B14 (declarations)

```text
cfe: Error: /tmp/kig-screen-v9_m3mbo/candidate.c, line 324: redeclaration of 'D_802923F5'; previous declaration at line 33 in file '/tmp/kig-screen-v9_m3mbo/candidate.c'
 extern u8 D_802923F5;
 ----------^
cfe: Error: /tmp/kig-screen-v9_m3mbo/candidate.c, line 354: redeclaration of 'D_802D39FC'; previous declaration at line 39 in file '/tmp/kig-screen-v9_m3mbo/candidate.c'
 extern u8 D_802D39FC;
 ----------^
cfe: Error: /tmp/kig-screen-v9_m3mbo/candidate.c, line 356: redeclaration of 'D_802D3A07'; previous declaration at line 39 in file '/tmp/kig-screen-v9_m3mbo/candidate.c'
 extern u8 D_802D3A07;
 ----------^
```

### func_801ABB20 (prefix)

```text
cfe: Error: /tmp/kig-screen-6cp92jq5/candidate.c, line 626: redeclaration of 'D_8004A428'; previous declaration at line 77 in file '/tmp/kig-screen-6cp92jq5/candidate.c'
 extern u32 D_8004A428[];
 -----------^
cfe: Error: /tmp/kig-screen-6cp92jq5/candidate.c, line 677: redeclaration of 'func_801AD794'; previous declaration at line 37 in file '/tmp/kig-screen-6cp92jq5/candidate.c'
 void func_801AD794(RenderState *arg0, s32 arg1, s32 arg2, s32 arg3) {
 -----^
cfe: Error: /tmp/kig-screen-6cp92jq5/candidate.c, line 677: Incompatible type for the function parameter
 void func_801AD794(RenderState *arg0, s32 arg1, s32 arg2, s32 arg3) {
 --------------------------------^
```

### func_8002E724 (declarations)

```text
cfe: Error: /tmp/kig-screen-ck1kak19/candidate.c, line 163: redeclaration of 'D_80069928'; previous declaration at line 22 in file '/tmp/kig-screen-ck1kak19/candidate.c'
 extern s16 *D_80069928;
 ------------^
cfe: Error: /tmp/kig-screen-ck1kak19/candidate.c, line 172: redeclaration of 'func_8002E724'; previous declaration at line 71 in file '/tmp/kig-screen-ck1kak19/candidate.c'
 void func_8002E724(T024EventPlayer *player,T024VoiceEvent *event)
 -----^
cfe: Error: /tmp/kig-screen-ck1kak19/candidate.c, line 172: Incompatible type for the function parameter
 void func_8002E724(T024EventPlayer *player,T024VoiceEvent *event)
 ------------------------------------^
cfe: Error: /tmp/kig-screen-ck1kak19/candidate.c, line 397: redeclaration of 'func_8002F2B0'; previous declaration at line 168 in file '/tmp/kig-screen-ck1kak19/candidate.c'
 void func_8002F2B0(T024PitchVoice *voice) {
 -----^
cfe: Error: /tmp/kig-screen-ck1kak19/candidate.c, line 397: Incompatible type for the function parameter
 void func_8002F2B0(T024PitchVoice *voice) {
 -----------------------------------^
cfe: Error: /tmp/kig-screen-ck1kak19/candidate.c, line 525: redeclaration of 'func_8002FA5C'; previous declaration at line 171 in file '/tmp/kig-screen-ck1kak19/candidate.c'
 void func_8002FA5C(s32 object, s16 type, s32 value) {
 -----^
cfe: Error: /tmp/kig-screen-ck1kak19/candidate.c, line 525: Incompatible type for the function parameter
 void func_8002FA5C(s32 object, s16 type, s32 value) {
 -----------------------^
```

### func_800310C0 (declarations)

```text
cfe: Error: /tmp/kig-screen-1t1hmr_6/candidate.c, line 88: 'D_8004CED0' undefined; reoccurrences will not be reported.
     var_s1 = (u8 *)D_8004CED0;
 -------------------^
```

### func_801C5298 (declarations)

```text
cfe: Error: /tmp/kig-screen-gztw28ec/candidate.c, line 268: redeclaration of 'func_801C51F8'; previous declaration at line 226 in file '/tmp/kig-screen-gztw28ec/candidate.c'
 extern void func_801C51F8(T030Cmd5298 **);
 ------------^
cfe: Error: /tmp/kig-screen-gztw28ec/candidate.c, line 268: Incompatible type for the function parameter
 extern void func_801C51F8(T030Cmd5298 **);
 --------------------------^
cfe: Error: /tmp/kig-screen-gztw28ec/candidate.c, line 272: redeclaration of 'D_4AC40'; previous declaration at line 224 in file '/tmp/kig-screen-gztw28ec/candidate.c'
 extern u8 D_4AC40[],D_801F3164[],D_801F3176[],D_801F3308[],D_801F331A[];
 ----------^
cfe: Error: /tmp/kig-screen-gztw28ec/candidate.c, line 288: redeclaration of 'D_802D3990'; previous declaration at line 178 in file '/tmp/kig-screen-gztw28ec/candidate.c'
 extern f32 D_802D3990[];
 -----------^
cfe: Error: /tmp/kig-screen-gztw28ec/candidate.c, line 289: redeclaration of 'D_802D399F'; previous declaration at line 188 in file '/tmp/kig-screen-gztw28ec/candidate.c'
 extern u8 D_802D3985,D_802D399C,D_802D399F,D_802D39B4,D_802D39B6,D_802D39BA;
 --------------------------------^
cfe: Error: /tmp/kig-screen-gztw28ec/candidate.c, line 408: Subscripting a non-array.
         func_8002DDD4(D_802D3990[0], D_802D3990[1], D_802D3990[2], &spEC, &spE8);
 --------------------------------^
cfe: Error: /tmp/kig-screen-gztw28ec/candidate.c, line 408: Subscripting a non-array.
         func_8002DDD4(D_802D3990[0], D_802D3990[1], D_802D3990[2], &spEC, &spE8);
 -----------------------------------------------^
cfe: Error: /tmp/kig-screen-gztw28ec/candidate.c, line 408: Subscripting a non-array.
         func_8002DDD4(D_802D3990[0], D_802D3990[1], D_802D3990[2], &spEC, &spE8);
 --------------------------------------------------------------^
cfe: Error: /tmp/kig-screen-gztw28ec/candidate.c, line 409: Subscripting a non-array.
         func_8002DCC8(D_802D3990[0], D_802D3990[1], D_802D3990[2], &spE4);
 --------------------------------^
cfe: Error: /tmp/kig-screen-gztw28ec/candidate.c, line 409: Subscripting a non-array.
         func_8002DCC8(D_802D3990[0], D_802D3990[1], D_802D3990[2], &spE4);
 -----------------------------------------------^
cfe: Error: /tmp/kig-screen-gztw28ec/candidate.c, line 409: Subscripting a non-array.
         func_8002DCC8(D_802D3990[0], D_802D3990[1], D_802D3990[2], &spE4);
 --------------------------------------------------------------^
```

### func_80028A00 (declarations)

```text
cfe: Error: /tmp/kig-screen-4nbkzbfp/candidate.c, line 110: Syntax Error
     T024RenderParticle *particle;
 -----------------------^
cfe: Error: /tmp/kig-screen-4nbkzbfp/candidate.c, line 111: Syntax Error
     f32 temp_f20;
 --------^
cfe: Error: /tmp/kig-screen-4nbkzbfp/candidate.c, line 112: Syntax Error
     f32 temp_f22;
 --------^
cfe: Error: /tmp/kig-screen-4nbkzbfp/candidate.c, line 113: Syntax Error
     f32 temp_f24;
 --------^
cfe: Error: /tmp/kig-screen-4nbkzbfp/candidate.c, line 114: Syntax Error
     f32 temp_f2;
 --------^
cfe: Error: /tmp/kig-screen-4nbkzbfp/candidate.c, line 115: Syntax Error
     f32 temp_f2_2;
 --------^
cfe: Error: /tmp/kig-screen-4nbkzbfp/candidate.c, line 116: Syntax Error
     f32 temp_f2_3;
 --------^
cfe: Error: /tmp/kig-screen-4nbkzbfp/candidate.c, line 117: Syntax Error
     f32 var_f10;
 --------^
cfe: Error: /tmp/kig-screen-4nbkzbfp/candidate.c, line 118: Syntax Error
     f32 var_f16;
 --------^
cfe: Error: /tmp/kig-screen-4nbkzbfp/candidate.c, line 119: Syntax Error
     f32 var_f18;
 --------^
cfe: Error: /tmp/kig-screen-4nbkzbfp/candidate.c, line 120: Syntax Error
     f32 var_f18_2;
 --------^
cfe: Error: /tmp/kig-screen-4nbkzbfp/candidate.c, line 121: Syntax Error
     f32 var_f4;
 --------^
cfe: Error: /tmp/kig-screen-4nbkzbfp/candidate.c, line 122: Syntax Error
     f32 var_f4_2;
 --------^
cfe: Error: /tmp/kig-screen-4nbkzbfp/candidate.c, line 123: Syntax Error
     f32 var_f8;
 --------^
cfe: Error: /tmp/kig-screen-4nbkzbfp/candidate.c, line 124: Syntax Error
     s16 temp_t0;
 --------^
cfe: Error: /tmp/kig-screen-4nbkzbfp/candidate.c, line 125: Syntax Error
     s16 temp_t2;
 --------^
cfe: Error: /tmp/kig-screen-4nbkzbfp/candidate.c, line 126: Syntax Error
     s16 var_a3;
 --------^
cfe: Error: /tmp/kig-screen-4nbkzbfp/candidate.c, line 127: Syntax Error
     s32 temp_a2;
 --------^
cfe: Error: /tmp/kig-screen-4nbkzbfp/candidate.c, line 128: Syntax Error
     s32 temp_t5;
 --------^
cfe: Error: /tmp/kig-screen-4nbkzbfp/candidate.c, line 129: Syntax Error
     s32 temp_t7;
 --------^
cfe: Error: /tmp/kig-screen-4nbkzbfp/candidate.c, line 130: Syntax Error
     s32 temp_t9;
 --------^
cfe: Error: /tmp/kig-screen-4nbkzbfp/candidate.c, line 131: Syntax Error
     s32 temp_v0_6;
 --------^
cfe: Error: /tmp/kig-screen-4nbkzbfp/candidate.c, line 132: Syntax Error
     s32 temp_v0_7;
 --------^
cfe: Error: /tmp/kig-screen-4nbkzbfp/candidate.c, line 133: Syntax Error
     s32 temp_v1_10;
 --------^
cfe: Error: /tmp/kig-screen-4nbkzbfp/candidate.c, line 134: Syntax Error
     s32 temp_v1_11;
 --------^
cfe: Error: /tmp/kig-screen-4nbkzbfp/candidate.c, line 135: Syntax Error
     s32 temp_v1_6;
 --------^
cfe: Error: /tmp/kig-screen-4nbkzbfp/candidate.c, line 136: Syntax Error
     s32 var_a1;
 --------^
cfe: Error: /tmp/kig-screen-4nbkzbfp/candidate.c, line 137: Syntax Error
     s32 var_a1_3;
 --------^
cfe: Error: /tmp/kig-screen-4nbkzbfp/candidate.c, line 138: Syntax Error
     s32 var_a2_2;
 --------^
cfe: Error: /tmp/kig-screen-4nbkzbfp/candidate.c, line 139: Syntax Error
     s32 var_fp;
 --------^
cfe: Fatal: Too many errors... goodbye.
```

### func_801B47A4 (prefix)

```text
cfe: Error: /tmp/kig-screen-ephfzmd6/candidate.c, line 362: redeclaration of 'D_802C8800'; previous declaration at line 115 in file '/tmp/kig-screen-ephfzmd6/candidate.c'
 extern u8 D_802C8800[];
 ----------^
cfe: Error: /tmp/kig-screen-ephfzmd6/candidate.c, line 371: Subscripting a non-array.
     if (D_802C8800[1] == 0 && D_801F35AC >= 51) {
 ------------------^
cfe: Error: /tmp/kig-screen-ephfzmd6/candidate.c, line 373: Subscripting a non-array.
         D_802C8800[1] = 1;
 ------------------^
```

### func_801CAA00 (declarations)

```text
cfe: Error: /tmp/kig-screen-ezk7oqlj/candidate.c, line 377: redeclaration of 'func_801C7CD0'; previous declaration at line 42 in file '/tmp/kig-screen-ezk7oqlj/candidate.c'
 extern void func_801C7CD0(s32, s32, s32);
 ------------^
cfe: Error: /tmp/kig-screen-ezk7oqlj/candidate.c, line 377: Incompatible type for the function parameter
 extern void func_801C7CD0(s32, s32, s32);
 --------------------------^
cfe: Error: /tmp/kig-screen-ezk7oqlj/candidate.c, line 378: redeclaration of 'func_801C7E98'; previous declaration at line 97 in file '/tmp/kig-screen-ezk7oqlj/candidate.c'
 extern void func_801C7E98(s32, s32);
 ------------^
cfe: Error: /tmp/kig-screen-ezk7oqlj/candidate.c, line 378: Incompatible type for the function parameter
 extern void func_801C7E98(s32, s32);
 --------------------------^
cfe: Error: /tmp/kig-screen-ezk7oqlj/candidate.c, line 391: redeclaration of 'D_802926AC'; previous declaration at line 34 in file '/tmp/kig-screen-ezk7oqlj/candidate.c'
 extern u8 ***D_802926AC;
 -------------^
cfe: Error: /tmp/kig-screen-ezk7oqlj/candidate.c, line 395: redeclaration of 'D_802D3678'; previous declaration at line 37 in file '/tmp/kig-screen-ezk7oqlj/candidate.c'
 extern T034PadPrev D_802D3678[];
 -------------------^
cfe: Error: /tmp/kig-screen-ezk7oqlj/candidate.c, line 397: redeclaration of 'D_802D39FC'; previous declaration at line 39 in file '/tmp/kig-screen-ezk7oqlj/candidate.c'
 extern u8 D_802D39FC;
 ----------^
cfe: Error: /tmp/kig-screen-ezk7oqlj/candidate.c, line 400: redeclaration of 'D_802D3A01'; previous declaration at line 39 in file '/tmp/kig-screen-ezk7oqlj/candidate.c'
 extern u8 D_802D3A01;
 ----------^
cfe: Error: /tmp/kig-screen-ezk7oqlj/candidate.c, line 401: redeclaration of 'D_802D3A02'; previous declaration at line 39 in file '/tmp/kig-screen-ezk7oqlj/candidate.c'
 extern u8 D_802D3A02;
 ----------^
cfe: Error: /tmp/kig-screen-ezk7oqlj/candidate.c, line 404: redeclaration of 'D_802D3A07'; previous declaration at line 39 in file '/tmp/kig-screen-ezk7oqlj/candidate.c'
 extern u8 D_802D3A07;
 ----------^
cfe: Error: /tmp/kig-screen-ezk7oqlj/candidate.c, line 429: Selector requires struct/union as left hand side
         if ((buttons & 0x100) && !(D_802D3678[port].buttons & 0x100)) {
 ---------------------------------------------------^
cfe: Error: /tmp/kig-screen-ezk7oqlj/candidate.c, line 450: Subscripting an array of incomplete type which is not an object type.
                         *D_802926AC[sel] = D_80295428;
 -----------------------------------^
cfe: Error: /tmp/kig-screen-ezk7oqlj/candidate.c, line 463: Selector requires struct/union as left hand side
             if ((buttons & 0xC30F) && !(D_802D3678[port].buttons & 0xC30F)) {
 --------------------------------------------------------^
cfe: Error: /tmp/kig-screen-ezk7oqlj/candidate.c, line 500: The number of arguments doesn't agree with the number in the declaration.
                                         func_801C7CD0(5, 2, 3);
 -----------------------------------------------------^
```

### func_801B849C (declarations)

```text
cfe: Error: /tmp/kig-screen-bu1yn4hj/candidate.c, line 190: redeclaration of 'func_801B6A68'; previous declaration at line 129 in file '/tmp/kig-screen-bu1yn4hj/candidate.c'
 extern s32 func_801B6A68(u32 **, T029Portrait *, s32);
 -----------^
cfe: Error: /tmp/kig-screen-bu1yn4hj/candidate.c, line 190: Incompatible type for the function parameter
 extern s32 func_801B6A68(u32 **, T029Portrait *, s32);
 -------------------------^
```

### func_80019880 (declarations)

```text
cfe: Error: /tmp/kig-screen-5zvuj97n/candidate.c, line 1275: redeclaration of 'D_8004ACCC'; previous declaration at line 288 in file '/tmp/kig-screen-5zvuj97n/candidate.c'
 extern u8 D_8004ACCC;
 ----------^
cfe: Error: /tmp/kig-screen-5zvuj97n/candidate.c, line 1276: redeclaration of 'D_8004ACD0'; previous declaration at line 288 in file '/tmp/kig-screen-5zvuj97n/candidate.c'
 extern u8 D_8004ACD0;
 ----------^
cfe: Error: /tmp/kig-screen-5zvuj97n/candidate.c, line 1278: redeclaration of 'D_8004ACD4'; previous declaration at line 13 in file '/tmp/kig-screen-5zvuj97n/candidate.c'
 extern u8 D_8004ACD4;
 ----------^
cfe: Error: /tmp/kig-screen-5zvuj97n/candidate.c, line 1286: redeclaration of 'func_80019880'; previous declaration at line 310 in file '/tmp/kig-screen-5zvuj97n/candidate.c'
 void func_80019880(u8 **arg0, s32 *arg1, s32 arg2, s32 arg3, f32 arg5, f32 arg6) {
 -----^
cfe: Error: /tmp/kig-screen-5zvuj97n/candidate.c, line 1286: Incompatible type for the function parameter
 void func_80019880(u8 **arg0, s32 *arg1, s32 arg2, s32 arg3, f32 arg5, f32 arg6) {
 ------------------------^
```

### func_801ADEA0 (prefix)

```text
cfe: Error: /tmp/kig-screen-ye7ia9_4/candidate.c, line 497: redeclaration of 'D_801D18B8'; previous declaration at line 19 in file '/tmp/kig-screen-ye7ia9_4/candidate.c'
 extern T025Effect D_801D18B8[];
 ------------------^
cfe: Error: /tmp/kig-screen-ye7ia9_4/candidate.c, line 505: 'flags' undefined; reoccurrences will not be reported.
         if (D_801D18B8[i].flags & arg0) D_801D18B8[i].state = -1;
 -------------------------^
cfe: Error: /tmp/kig-screen-ye7ia9_4/candidate.c, line 505: member of structure or union required
         if (D_801D18B8[i].flags & arg0) D_801D18B8[i].state = -1;
 --------------------------^
cfe: Error: /tmp/kig-screen-ye7ia9_4/candidate.c, line 505: 'state' undefined; reoccurrences will not be reported.
         if (D_801D18B8[i].flags & arg0) D_801D18B8[i].state = -1;
 -----------------------------------------------------^
cfe: Error: /tmp/kig-screen-ye7ia9_4/candidate.c, line 505: member of structure or union required
         if (D_801D18B8[i].flags & arg0) D_801D18B8[i].state = -1;
 ------------------------------------------------------^
```

### func_801B6E4C (declarations)

```text
cfe: Error: /tmp/kig-screen-5fcqojym/candidate.c, line 188: redeclaration of 'func_801B6A68'; previous declaration at line 129 in file '/tmp/kig-screen-5fcqojym/candidate.c'
 extern s32 func_801B6A68(u32 **, T029Portrait *, s32);
 -----------^
cfe: Error: /tmp/kig-screen-5fcqojym/candidate.c, line 188: Incompatible type for the function parameter
 extern s32 func_801B6A68(u32 **, T029Portrait *, s32);
 -------------------------^
cfe: Error: /tmp/kig-screen-5fcqojym/candidate.c, line 200: redeclaration of 'D_80127CE8'; previous declaration at line 80 in file '/tmp/kig-screen-5fcqojym/candidate.c'
 extern u8 D_80127CE8[];
 ----------^
cfe: Error: /tmp/kig-screen-5fcqojym/candidate.c, line 234: redeclaration of 'D_802C8CEA'; previous declaration at line 84 in file '/tmp/kig-screen-5fcqojym/candidate.c'
 extern u8 D_802C8CEA;
 ----------^
cfe: Error: /tmp/kig-screen-5fcqojym/candidate.c, line 440: Unacceptable operand of a multiplicative operator.
                         var_a2 = *((void * *)(D_801F2EB4 + (D_80127CE8[sp133] * 0x8C)));
 ----------------------------------------------------------------------^
```

### func_80021B6C (declarations)

```text
cfe: Error: /tmp/kig-screen-xlcghway/candidate.c, line 119: Syntax Error
 extern void func_80023EF0(void),func_8001E33C(T032Gfx21B **,u8),func_8002E08C(T032Actor21B *,T020Position *);
 ---------------------------------------------------------------------------------------------^
cfe: Error: /tmp/kig-screen-xlcghway/candidate.c, line 148: Syntax Error
     T020Position sp114;
 -----------------^
cfe: Error: /tmp/kig-screen-xlcghway/candidate.c, line 149: Syntax Error
     T032Gfx21B *sp110;
 ---------------^
cfe: Error: /tmp/kig-screen-xlcghway/candidate.c, line 150: Syntax Error
     void *sp10C;
 ----^
cfe: Error: /tmp/kig-screen-xlcghway/candidate.c, line 151: Syntax Error
     s32 sp78;                                        
 --------^
cfe: Error: /tmp/kig-screen-xlcghway/candidate.c, line 153: Syntax Error
     f32 var_f18;
 --------^
cfe: Error: /tmp/kig-screen-xlcghway/candidate.c, line 154: Syntax Error
     s16 temp_t1;
 --------^
cfe: Error: /tmp/kig-screen-xlcghway/candidate.c, line 155: Syntax Error
     s16 temp_t1_2;
 --------^
cfe: Error: /tmp/kig-screen-xlcghway/candidate.c, line 156: Syntax Error
     s32 temp_hi;
 --------^
cfe: Error: /tmp/kig-screen-xlcghway/candidate.c, line 157: Syntax Error
     s32 temp_t0_2;
 --------^
cfe: Error: /tmp/kig-screen-xlcghway/candidate.c, line 158: Syntax Error
     s32 temp_t2;
 --------^
cfe: Error: /tmp/kig-screen-xlcghway/candidate.c, line 159: Syntax Error
     s32 temp_t4_2;
 --------^
cfe: Error: /tmp/kig-screen-xlcghway/candidate.c, line 160: Syntax Error
     s32 temp_t6;
 --------^
cfe: Error: /tmp/kig-screen-xlcghway/candidate.c, line 161: Syntax Error
     s32 temp_t6_2;
 --------^
cfe: Error: /tmp/kig-screen-xlcghway/candidate.c, line 162: Syntax Error
     s32 temp_t6_5;
 --------^
cfe: Error: /tmp/kig-screen-xlcghway/candidate.c, line 163: Syntax Error
     s32 temp_t7;
 --------^
cfe: Error: /tmp/kig-screen-xlcghway/candidate.c, line 164: Syntax Error
     s32 temp_t9_5;
 --------^
cfe: Error: /tmp/kig-screen-xlcghway/candidate.c, line 165: Syntax Error
     s32 temp_v0_11;
 --------^
cfe: Error: /tmp/kig-screen-xlcghway/candidate.c, line 166: Syntax Error
     s32 temp_v0_5;
 --------^
cfe: Error: /tmp/kig-screen-xlcghway/candidate.c, line 167: Syntax Error
     s32 temp_v0_6;
 --------^
cfe: Error: /tmp/kig-screen-xlcghway/candidate.c, line 168: Syntax Error
     s32 temp_v1_10;
 --------^
cfe: Error: /tmp/kig-screen-xlcghway/candidate.c, line 169: Syntax Error
     s32 temp_v1_11;
 --------^
cfe: Error: /tmp/kig-screen-xlcghway/candidate.c, line 170: Syntax Error
     s32 temp_v1_12;
 --------^
cfe: Error: /tmp/kig-screen-xlcghway/candidate.c, line 171: Syntax Error
     s32 temp_v1_3;
 --------^
cfe: Error: /tmp/kig-screen-xlcghway/candidate.c, line 172: Syntax Error
     s32 temp_v1_4;
 --------^
cfe: Error: /tmp/kig-screen-xlcghway/candidate.c, line 173: Syntax Error
     s32 temp_v1_8;
 --------^
cfe: Error: /tmp/kig-screen-xlcghway/candidate.c, line 174: Syntax Error
     s32 temp_v1_9;
 --------^
cfe: Error: /tmp/kig-screen-xlcghway/candidate.c, line 175: Syntax Error
     s32 var_s2;
 --------^
cfe: Error: /tmp/kig-screen-xlcghway/candidate.c, line 176: Syntax Error
     s32 var_s7;
 --------^
cfe: Error: /tmp/kig-screen-xlcghway/candidate.c, line 177: Syntax Error
     s32 var_t0_2;
 --------^
cfe: Fatal: Too many errors... goodbye.
```

### func_8000FA80 (prefix)

```text
cfe: Error: /tmp/kig-screen-kgnxk6c6/candidate.c, line 397: redeclaration of 'func_80012100'; previous declaration at line 76 in file '/tmp/kig-screen-kgnxk6c6/candidate.c'
 void func_80012100(u8 arg0, u8 arg1) {
 -----^
cfe: Error: /tmp/kig-screen-kgnxk6c6/candidate.c, line 397: prototype and non-prototype declaration found for func_80012100, the type of this parameter is not compatible with the type after applying default argument promotion
 void func_80012100(u8 arg0, u8 arg1) {
 ----------------------^
```

### func_8001EC74 (declarations)

```text
cfe: Error: /tmp/kig-screen-zt2ife79/candidate.c, line 699: 'D_8004AA28' undefined; reoccurrences will not be reported.
                                     if ((temp_t7_4 < (0xF0 << D_8004AA28)) && (sp9C < (0x140 << D_8004AA28)) && (sp9C >= -0x12B) && (temp_t7_4 >= -0x12B)) {
 --------------------------------------------------------------^
```

