# T-113 draft screen

IDO 5.3 -O2 -mips2 through asm-processor. Full owning TU first; prefix fallback removes other GLOBAL_ASM stubs and omits declarations after the target. Relocation masks come only from ELF REL entries. Size differences count as differing words. Declaration fallback keeps TU types/prototypes, omits preceding bodies, and gives explicit draft declarations precedence. Prefix/declaration scores require reconciliation before integration.

| Function | Compiled B | Original B | Differing words | Context | Draft |
|---|---:|---:|---:|---|---|
| func_800269AC | 236 | 236 | 2 | full | tools/scratch/nonmatching/T-032/func_800269AC.c |
| func_8002F6F4 | 516 | 516 | 2 | full | tools/scratch/nonmatching/T-024/func_8002F6F4.c |
| func_801BF720 | 104 | 104 | 2 | prefix | tools/scratch/nonmatching/T-023/func_801BF720.c |
| func_801BF914 | 116 | 116 | 2 | prefix | tools/scratch/nonmatching/T-023/func_801BF914.c |
| func_801C4E38 | 556 | 556 | 2 | declarations | tools/scratch/nonmatching/T-021/func_801C4E38.c |
| func_801CC908 | 424 | 424 | 2 | full | tools/scratch/nonmatching/T-021/func_801CC908.c |
| func_801B6528 | 596 | 596 | 3 | full | tools/scratch/nonmatching/T-029/func_801B6528.c |
| func_8002F45C | 404 | 404 | 4 | full | tools/scratch/nonmatching/T-024/func_8002F45C.c |
| func_801B695C | 268 | 268 | 4 | prefix | tools/scratch/nonmatching/T-029/func_801B695C.c |
| func_801C85C0 | 168 | 168 | 4 | full | tools/scratch/nonmatching/T-021/func_801C85C0.c |
| func_801B5534 | 168 | 168 | 5 | full | tools/scratch/nonmatching/T-029/func_801B5534.c |
| func_801C224C | 372 | 372 | 6 | full | tools/scratch/nonmatching/T-030/func_801C224C.c |
| func_801C7998 | 256 | 256 | 6 | full | tools/scratch/nonmatching/T-030/func_801C7998.c |
| func_801BD270 | 396 | 396 | 7 | full | tools/scratch/nonmatching/T-023/func_801BD270.c |
| func_80017378 | 1752 | 1752 | 8 | full | tools/scratch/nonmatching/T-033/func_80017378.c |
| func_8001BDE0 | 316 | 316 | 8 | full | tools/scratch/nonmatching/T-022/func_8001BDE0.c |
| func_801C47E0 | 260 | 260 | 11 | full | tools/scratch/nonmatching/T-030/func_801C47E0.c |
| func_801BD200 | 112 | 112 | 14 | full | tools/scratch/nonmatching/T-023/func_801BD200.c |
| func_801C7A98 | 568 | 568 | 14 | full | tools/scratch/nonmatching/T-030/func_801C7A98.c |
| func_8002A900 | 220 | 220 | 15 | full | tools/scratch/nonmatching/T-024/func_8002A900.c |
| func_801C7F90 | 116 | 116 | 16 | full | tools/scratch/nonmatching/T-021/func_801C7F90.c |
| func_801ADA04 | 208 | 208 | 18 | full | tools/scratch/nonmatching/T-019/func_801ADA04.c |
| func_801B2EF4 | 536 | 536 | 19 | full | tools/scratch/nonmatching/T-025/func_801B2EF4.c |
| func_801B310C | 536 | 536 | 19 | full | tools/scratch/nonmatching/T-025/func_801B310C.c |
| func_801B3324 | 536 | 536 | 19 | full | tools/scratch/nonmatching/T-025/func_801B3324.c |
| func_801B353C | 536 | 536 | 19 | full | tools/scratch/nonmatching/T-025/func_801B353C.c |
| func_801B3754 | 536 | 536 | 19 | full | tools/scratch/nonmatching/T-025/func_801B3754.c |
| func_801B396C | 536 | 536 | 19 | full | tools/scratch/nonmatching/T-025/func_801B396C.c |
| func_801BB258 | 524 | 524 | 20 | full | tools/scratch/nonmatching/T-023/func_801BB258.c |
| func_801C0800 | 248 | 248 | 21 | full | tools/scratch/nonmatching/T-023/func_801C0800.c |
| func_801C8AE0 | 324 | 324 | 21 | full | tools/scratch/nonmatching/T-034/func_801C8AE0.c |
| func_801B0520 | 328 | 328 | 22 | full | tools/scratch/nonmatching/T-025/func_801B0520.c |
| func_800268C0 | 236 | 236 | 28 | full | tools/scratch/nonmatching/T-032/func_800268C0.c |
| func_801B1210 | 284 | 284 | 28 | full | tools/scratch/nonmatching/T-025/func_801B1210.c |
| func_801B446C | 292 | 292 | 28 | full | tools/scratch/nonmatching/T-029/func_801B446C.c |
| func_8002A4F0 | 920 | 920 | 31 | full | tools/scratch/nonmatching/T-024/func_8002A4F0.c |
| func_801B43A8 | 196 | 196 | 34 | full | tools/scratch/nonmatching/T-029/func_801B43A8.c |
| func_8001373C | 256 | 256 | 36 | prefix | tools/scratch/nonmatching/T-020/func_8001373C.c |
| func_801BBB60 | 292 | 292 | 40 | full | tools/scratch/nonmatching/T-023/func_801BBB60.c |
| func_801BE660 | 300 | 300 | 41 | full | tools/scratch/nonmatching/T-023/func_801BE660.c |
| func_800121C8 | 304 | 304 | 47 | full | tools/scratch/nonmatching/T-033/func_800121C8.c |
| func_80024028 | 284 | 284 | 49 | full | tools/scratch/nonmatching/T-032/func_80024028.c |
| func_80024714 | 712 | 712 | 69 | declarations | tools/scratch/nonmatching/T-032/func_80024714.c |
| func_801C2ADC | 600 | 600 | 71 | full | tools/scratch/nonmatching/T-030/func_801C2ADC.c |
| func_8002B22C | 380 | 380 | 74 | full | tools/scratch/nonmatching/T-024/func_8002B22C.c |
| func_801C49A8 | 548 | 548 | 83 | full | tools/scratch/nonmatching/T-030/func_801C49A8.c |
| func_801C3E40 | 504 | 504 | 88 | declarations | tools/scratch/nonmatching/T-030/func_801C3E40.c |
| func_801B1DE4 | 556 | 556 | 111 | full | tools/scratch/nonmatching/T-025/func_801B1DE4.c |
| func_801BADEC | 568 | 568 | 118 | full | tools/scratch/nonmatching/T-023/func_801BADEC.c |
| func_8002AB90 | 852 | 852 | 119 | full | tools/scratch/nonmatching/T-024/func_8002AB90.c |
| func_801C9698 | 1148 | 1148 | 135 | full | tools/scratch/nonmatching/T-034/func_801C9698.c |
| func_8001D47C | 748 | 748 | 141 | declarations | tools/scratch/nonmatching/T-022/func_8001D47C.c |
| func_801C4240 | 1344 | 1344 | 150 | full | tools/scratch/nonmatching/T-030/func_801C4240.c |
| func_801B6BD8 | 628 | 628 | 153 | full | tools/scratch/nonmatching/T-029/func_801B6BD8.c |
| func_801B0668 | 984 | 984 | 156 | full | tools/scratch/nonmatching/T-025/func_801B0668.c |
| func_800297A4 | 780 | 780 | 180 | declarations | tools/scratch/nonmatching/T-024/func_800297A4.c |
| func_801BD640 | 1068 | 1068 | 191 | full | tools/scratch/nonmatching/T-023/func_801BD640.c |
| func_801B3DB0 | 1360 | 1360 | 255 | full | tools/scratch/nonmatching/T-025/func_801B3DB0.c |
| func_801BF190 | 1256 | 1256 | 284 | declarations | tools/scratch/nonmatching/T-023/func_801BF190.c |
| func_801B5DCC | 1884 | 1884 | 387 | full | tools/scratch/nonmatching/T-029/func_801B5DCC.c |
| func_801BCB70 | 1676 | 1676 | 391 | full | tools/scratch/nonmatching/T-023/func_801BCB70.c |
| func_80032738 | 40 | 20 | 10 | full | tools/scratch/nonmatching/T-026/func_80032738.c |
| func_80032750 | 44 | 60 | 15 | full | tools/scratch/nonmatching/T-026/func_80032750.c |
| func_801C8C24 | 396 | 408 | 22 | full | tools/scratch/nonmatching/T-034/func_801C8C24.c |
| func_8003278C | 104 | 92 | 26 | full | tools/scratch/nonmatching/T-026/func_8003278C.c |
| func_80031050 | 120 | 112 | 30 | declarations | tools/scratch/nonmatching/T-026/func_80031050.c |
| func_801C3758 | 572 | 564 | 32 | full | tools/scratch/nonmatching/T-030/func_801C3758.c |
| func_80032600 | 148 | 112 | 37 | full | tools/scratch/nonmatching/T-026/func_80032600.c |
| func_801BEEA4 | 356 | 344 | 40 | declarations | tools/scratch/nonmatching/T-023/func_801BEEA4.c |
| func_80032670 | 180 | 116 | 45 | full | tools/scratch/nonmatching/T-026/func_80032670.c |
| func_801C48E4 | 188 | 196 | 45 | full | tools/scratch/nonmatching/T-021/func_801C48E4.c |
| func_801C8004 | 228 | 236 | 47 | full | tools/scratch/nonmatching/T-021/func_801C8004.c |
| func_8001AA90 | 488 | 496 | 60 | full | tools/scratch/nonmatching/T-022/func_8001AA90.c |
| func_80032504 | 68 | 240 | 60 | full | tools/scratch/nonmatching/T-026/func_80032504.c |
| func_80015450 | 328 | 324 | 66 | prefix | tools/scratch/nonmatching/T-033/func_80015450.c |
| func_800326F0 | 276 | 72 | 69 | full | tools/scratch/nonmatching/T-026/func_800326F0.c |
| func_801BE540 | 280 | 288 | 69 | full | tools/scratch/nonmatching/T-023/func_801BE540.c |
| func_80023EF0 | 296 | 312 | 71 | declarations | tools/scratch/nonmatching/T-032/func_80023EF0.c |
| func_801B465C | 332 | 328 | 71 | full | tools/scratch/nonmatching/T-029/func_801B465C.c |
| func_800300DC | 312 | 316 | 76 | declarations | tools/scratch/nonmatching/T-026/func_800300DC.c |
| func_801BB464 | 308 | 304 | 76 | full | tools/scratch/nonmatching/T-023/func_801BB464.c |
| func_800287D4 | 560 | 556 | 77 | prefix | tools/scratch/nonmatching/T-024/func_800287D4.c |
| func_80030220 | 340 | 348 | 77 | full | tools/scratch/nonmatching/T-026/func_80030220.c |
| func_801BE790 | 372 | 384 | 78 | prefix | tools/scratch/nonmatching/T-023/func_801BE790.c |
| func_800245B4 | 348 | 352 | 83 | declarations | tools/scratch/nonmatching/T-032/func_800245B4.c |
| func_801BA884 | 496 | 500 | 86 | full | tools/scratch/nonmatching/T-023/func_801BA884.c |
| func_801AD114 | 612 | 628 | 88 | full | tools/scratch/nonmatching/T-019/func_801AD114.c |
| func_801CC3BC | 364 | 360 | 88 | full | tools/scratch/nonmatching/T-021/func_801CC3BC.c |
| func_801AD7D8 | 548 | 556 | 89 | full | tools/scratch/nonmatching/T-019/func_801AD7D8.c |
| func_801CD1F0 | 456 | 460 | 91 | full | tools/scratch/nonmatching/T-034/func_801CD1F0.c |
| func_80026738 | 388 | 392 | 96 | full | tools/scratch/nonmatching/T-032/func_80026738.c |
| func_8001CD50 | 436 | 460 | 98 | declarations | tools/scratch/nonmatching/T-022/func_8001CD50.c |
| func_80012390 | 500 | 476 | 101 | full | tools/scratch/nonmatching/T-033/func_80012390.c |
| func_8001272C | 544 | 540 | 103 | full | tools/scratch/nonmatching/T-033/func_8001272C.c |
| func_801C17D0 | 436 | 448 | 103 | full | tools/scratch/nonmatching/T-023/func_801C17D0.c |
| func_8002DDD4 | 444 | 452 | 104 | prefix | tools/scratch/nonmatching/T-024/func_8002DDD4.c |
| func_80032360 | 116 | 420 | 105 | full | tools/scratch/nonmatching/T-026/func_80032360.c |
| func_8002FB80 | 512 | 544 | 109 | prefix | tools/scratch/nonmatching/T-024/func_8002FB80.c |
| func_800191F0 | 476 | 492 | 110 | declarations | tools/scratch/nonmatching/T-022/func_800191F0.c |
| func_801BBC84 | 508 | 516 | 112 | full | tools/scratch/nonmatching/T-023/func_801BBC84.c |
| func_801B3B84 | 552 | 556 | 113 | full | tools/scratch/nonmatching/T-025/func_801B3B84.c |
| func_801C11F0 | 584 | 580 | 113 | full | tools/scratch/nonmatching/T-023/func_801C11F0.c |
| func_801B677C | 492 | 480 | 117 | full | tools/scratch/nonmatching/T-029/func_801B677C.c |
| func_80016078 | 448 | 480 | 119 | full | tools/scratch/nonmatching/T-033/func_80016078.c |
| func_801C2F5C | 556 | 544 | 128 | full | tools/scratch/nonmatching/T-030/func_801C2F5C.c |
| func_801AFFAC | 568 | 576 | 129 | full | tools/scratch/nonmatching/T-025/func_801AFFAC.c |
| func_800170C4 | 696 | 692 | 134 | declarations | tools/scratch/nonmatching/T-033/func_800170C4.c |
| func_8002D9C4 | 476 | 536 | 134 | full | tools/scratch/nonmatching/T-024/func_8002D9C4.c |
| func_8002FDA0 | 584 | 572 | 136 | prefix | tools/scratch/nonmatching/T-024/func_8002FDA0.c |
| func_80018F20 | 688 | 696 | 138 | full | tools/scratch/nonmatching/T-022/func_80018F20.c |
| func_801BD3FC | 440 | 580 | 145 | full | tools/scratch/nonmatching/T-023/func_801BD3FC.c |
| func_80025D58 | 328 | 620 | 146 | full | tools/scratch/nonmatching/T-032/func_80025D58.c |
| func_80017A68 | 764 | 772 | 149 | full | tools/scratch/nonmatching/T-033/func_80017A68.c |
| func_8001BB64 | 592 | 636 | 154 | declarations | tools/scratch/nonmatching/T-022/func_8001BB64.c |
| func_801BEA74 | 676 | 664 | 154 | full | tools/scratch/nonmatching/T-023/func_801BEA74.c |
| func_8001DE5C | 624 | 600 | 155 | full | tools/scratch/nonmatching/T-022/func_8001DE5C.c |
| func_80030440 | 520 | 632 | 156 | full | tools/scratch/nonmatching/T-026/func_80030440.c |
| func_801C1990 | 604 | 676 | 159 | full | tools/scratch/nonmatching/T-023/func_801C1990.c |
| func_800241BC | 840 | 820 | 160 | prefix | tools/scratch/nonmatching/T-032/func_800241BC.c |
| func_801B0A40 | 684 | 668 | 163 | full | tools/scratch/nonmatching/T-025/func_801B0A40.c |
| func_8001346C | 696 | 704 | 165 | full | tools/scratch/nonmatching/T-033/func_8001346C.c |
| func_801ACB1C | 756 | 744 | 176 | prefix | tools/scratch/nonmatching/T-034/func_801ACB1C.c |
| func_801C1434 | 736 | 720 | 176 | full | tools/scratch/nonmatching/T-023/func_801C1434.c |
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
| func_801B0CDC | 1336 | 1332 | 204 | prefix | tools/scratch/nonmatching/T-025/func_801B0CDC.c |
| func_801B1A7C | 596 | 872 | 206 | prefix | tools/scratch/nonmatching/T-025/func_801B1A7C.c |
| func_801C3AA0 | 908 | 928 | 206 | declarations | tools/scratch/nonmatching/T-030/func_801C3AA0.c |
| func_8001B134 | 980 | 984 | 214 | full | tools/scratch/nonmatching/T-022/func_8001B134.c |
| func_801C90D4 | 1192 | 1200 | 219 | full | tools/scratch/nonmatching/T-034/func_801C90D4.c |
| func_801BB7B4 | 960 | 940 | 220 | declarations | tools/scratch/nonmatching/T-023/func_801BB7B4.c |
| func_801BAA78 | 912 | 884 | 222 | full | tools/scratch/nonmatching/T-023/func_801BAA78.c |
| func_801C23C0 | 1812 | 1820 | 222 | full | tools/scratch/nonmatching/T-030/func_801C23C0.c |
| func_801C317C | 940 | 936 | 225 | full | tools/scratch/nonmatching/T-030/func_801C317C.c |
| func_800216D4 | 1040 | 1032 | 229 | prefix | tools/scratch/nonmatching/T-032/func_800216D4.c |
| func_80031A38 | 680 | 920 | 229 | declarations | tools/scratch/nonmatching/T-026/func_80031A38.c |
| func_801AF68C | 940 | 956 | 231 | prefix | tools/scratch/nonmatching/T-025/func_801AF68C.c |
| func_80027E1C | 940 | 936 | 234 | full | tools/scratch/nonmatching/T-032/func_80027E1C.c |
| func_801B132C | 1144 | 1168 | 237 | full | tools/scratch/nonmatching/T-025/func_801B132C.c |
| func_80028230 | 932 | 976 | 242 | full | tools/scratch/nonmatching/T-024/func_80028230.c |
| func_801C1C34 | 1224 | 1244 | 242 | full | tools/scratch/nonmatching/T-023/func_801C1C34.c |
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
| func_8001D7E4 | 1720 | 1656 | 423 | prefix | tools/scratch/nonmatching/T-022/func_8001D7E4.c |
| func_801B5650 | 1924 | 1916 | 425 | full | tools/scratch/nonmatching/T-029/func_801B5650.c |
| func_80025FC4 | 1896 | 1908 | 454 | full | tools/scratch/nonmatching/T-032/func_80025FC4.c |
| func_800306B8 | 2096 | 2104 | 510 | full | tools/scratch/nonmatching/T-026/func_800306B8.c |
| func_80020E98 | 2104 | 2108 | 512 | prefix | tools/scratch/nonmatching/T-032/func_80020E98.c |
| func_801C5E74 | 2404 | 2392 | 557 | declarations | tools/scratch/nonmatching/T-030/func_801C5E74.c |
| func_801C08F8 | 2216 | 2296 | 561 | full | tools/scratch/nonmatching/T-023/func_801C08F8.c |
| func_8001178C | 2296 | 2104 | 570 | prefix | tools/scratch/nonmatching/T-033/func_8001178C.c |
| func_8001E33C | 2412 | 2360 | 571 | declarations | tools/scratch/nonmatching/T-022/func_8001E33C.c |
| func_800142E0 | 2100 | 2400 | 593 | declarations | tools/scratch/nonmatching/T-033/func_800142E0.c |
| func_801BFCBC | 2084 | 2388 | 596 | full | tools/scratch/nonmatching/T-023/func_801BFCBC.c |
| func_801BC1B0 | 2320 | 2496 | 624 | declarations | tools/scratch/nonmatching/T-023/func_801BC1B0.c |
| func_801C9B14 | 3140 | 3184 | 629 | full | tools/scratch/nonmatching/T-034/func_801C9B14.c |
| func_8002E724 | 2728 | 2832 | 658 | full | tools/scratch/nonmatching/T-024/func_8002E724.c |
| func_801ABB20 | 3576 | 3644 | 658 | prefix | tools/scratch/nonmatching/T-034/func_801ABB20.c |
| func_800310C0 | 2744 | 2424 | 683 | declarations | tools/scratch/nonmatching/T-026/func_800310C0.c |
| func_801C5298 | 3000 | 3036 | 741 | declarations | tools/scratch/nonmatching/T-030/func_801C5298.c |
| func_80028A00 | 3264 | 3340 | 802 | declarations | tools/scratch/nonmatching/T-024/func_80028A00.c |
| func_801B47A4 | 3260 | 3472 | 862 | prefix | tools/scratch/nonmatching/T-029/func_801B47A4.c |
| func_801CAA00 | 3884 | 3992 | 992 | full | tools/scratch/nonmatching/T-034/func_801CAA00.c |
| func_80026B38 | 4792 | 4708 | 1182 | full | tools/scratch/nonmatching/T-032/func_80026B38.c |
| func_801B849C | 5312 | 5296 | 1267 | declarations | tools/scratch/nonmatching/T-029/func_801B849C.c |
| func_80019880 | 5216 | 4456 | 1297 | declarations | tools/scratch/nonmatching/T-022/func_80019880.c |
| func_801ADEA0 | 5524 | 5508 | 1349 | prefix | tools/scratch/nonmatching/T-025/func_801ADEA0.c |
| func_801B6E4C | 5652 | 5712 | 1417 | declarations | tools/scratch/nonmatching/T-029/func_801B6E4C.c |
| func_8002BBD0 | 7692 | 7668 | 1843 | full | tools/scratch/nonmatching/T-024/func_8002BBD0.c |
| func_8000FA80 | 8148 | 7436 | 2014 | prefix | tools/scratch/nonmatching/T-033/func_8000FA80.c |
| func_8001EC74 | 8476 | 8740 | 2175 | declarations | tools/scratch/nonmatching/T-022/func_8001EC74.c |
| func_8001D080 | — | — | — | ERROR | tools/scratch/nonmatching/T-022/func_8001D080.c |
| func_80021B6C | — | — | — | ERROR | tools/scratch/nonmatching/T-032/func_80021B6C.c |

## Compilation diagnostics

### func_801BF720 (prefix)

```text
cfe: Error: /tmp/kig-screen-ggy4pm_y/candidate.c, line 146: redeclaration of 'func_801BF720'; previous declaration at line 131 in file '/tmp/kig-screen-ggy4pm_y/candidate.c'
 extern s32 func_801BF720(s32);
 -----------^
cfe: Error: /tmp/kig-screen-ggy4pm_y/candidate.c, line 146: Incompatible type for the function parameter
 extern s32 func_801BF720(s32);
 -------------------------^
```

### func_801BF914 (prefix)

```text
cfe: Error: /tmp/kig-screen-x72lpz90/candidate.c, line 187: redeclaration of 'func_801BF914'; previous declaration at line 172 in file '/tmp/kig-screen-x72lpz90/candidate.c'
 extern s32 func_801BF914(s32);
 -----------^
cfe: Error: /tmp/kig-screen-x72lpz90/candidate.c, line 187: Incompatible type for the function parameter
 extern s32 func_801BF914(s32);
 -------------------------^
```

### func_801C4E38 (declarations)

```text
cfe: Error: /tmp/kig-screen-ob2xj_6n/candidate.c, line 248: redeclaration of 'D_802D39A0'; previous declaration at line 189 in file '/tmp/kig-screen-ob2xj_6n/candidate.c'
 extern s32 D_802D39A0;
 -----------^
cfe: Error: /tmp/kig-screen-ob2xj_6n/candidate.c, line 249: redeclaration of 'D_802D39A4'; previous declaration at line 190 in file '/tmp/kig-screen-ob2xj_6n/candidate.c'
 extern s32 D_802D39A4;
 -----------^
cfe: Error: /tmp/kig-screen-ob2xj_6n/candidate.c, line 250: redeclaration of 'D_802D39A8'; previous declaration at line 191 in file '/tmp/kig-screen-ob2xj_6n/candidate.c'
 extern s32 D_802D39A8;
 -----------^
```

### func_801B695C (prefix)

```text
cfe: Error: /tmp/kig-screen-mc82u99e/candidate.c, line 450: redeclaration of 'D_802C8808'; previous declaration at line 421 in file '/tmp/kig-screen-mc82u99e/candidate.c'
 extern u8 D_802C8808[][512];
 ----------^
cfe: Error: /tmp/kig-screen-mc82u99e/candidate.c, line 471: Subscripting a non-array.
         command1->w1 = (u32)(&D_802C8808[arg2][D_802C8D08[arg2] * 2]);
 ----------------------------------------------^
```

### func_8001373C (prefix)

```text
cfe: Error: /tmp/kig-screen-ele6u_a8/candidate.c, line 503: redeclaration of 'func_8001373C'; previous declaration at line 98 in file '/tmp/kig-screen-ele6u_a8/candidate.c'
 extern void func_8001373C(void *, f32, f32, f32, s32, s32, s32);
 ------------^
cfe: Error: /tmp/kig-screen-ele6u_a8/candidate.c, line 503: Incompatible type for the function parameter
 extern void func_8001373C(void *, f32, f32, f32, s32, s32, s32);
 --------------------------^
```

### func_80024714 (declarations)

```text
cfe: Error: /tmp/kig-screen-l1to83g9/candidate.c, line 294: redeclaration of 'D_8004D278'; previous declaration at line 264 in file '/tmp/kig-screen-l1to83g9/candidate.c'
 extern u8 D_1EB6D0[],D_1F3200[],D_2C2280[],D_2CF0A0[],D_469660[],D_470390[],D_53CC40[],D_543D10[],D_8004D278[],D_8004EA9C[],D_8004F396[];
 --------------------------------------------------------------------------------------------------^
cfe: Error: /tmp/kig-screen-l1to83g9/candidate.c, line 316: Unacceptable operand of '+'.
         temp_v0_2 = (T032Resource714 *)(D_8004D278 + arg0 * 8);
 ---------------------------------------------------^
cfe: Error: /tmp/kig-screen-l1to83g9/candidate.c, line 325: Unacceptable operand of '+'.
         temp_v0_3 = (T032Resource714 *)(D_8004D278 + arg0 * 8);
 ---------------------------------------------------^
cfe: Error: /tmp/kig-screen-l1to83g9/candidate.c, line 340: Unacceptable operand of '+'.
         var_v0 = (T032Resource714 *)(D_8004D278 + arg0 * 8);
 ------------------------------------------------^
cfe: Error: /tmp/kig-screen-l1to83g9/candidate.c, line 350: Unacceptable operand of '+'.
         var_v0 = (T032Resource714 *)(D_8004D278 + arg0 * 8);
 ------------------------------------------------^
```

### func_801C3E40 (declarations)

```text
cfe: Error: /tmp/kig-screen-np7lxflh/candidate.c, line 51: redeclaration of 'D_802D3940'; previous declaration at line 14 in file '/tmp/kig-screen-np7lxflh/candidate.c'
 extern T030Triangle3E40 *D_802D3940;
 -------------------------^
cfe: Error: /tmp/kig-screen-np7lxflh/candidate.c, line 71: 'v' undefined; reoccurrences will not be reported.
                 D_802D3940[slot].v[0].a -= 32;
 --------------------------------^
cfe: Error: /tmp/kig-screen-np7lxflh/candidate.c, line 71: member of structure or union required
                 D_802D3940[slot].v[0].a -= 32;
 ---------------------------------^
cfe: Error: /tmp/kig-screen-np7lxflh/candidate.c, line 72: member of structure or union required
                 if (D_802D3940[slot].v[0].a < 32) {
 -------------------------------------^
cfe: Error: /tmp/kig-screen-np7lxflh/candidate.c, line 73: member of structure or union required
                     D_802D3940[slot].v[0].a = 32;
 -------------------------------------^
cfe: Error: /tmp/kig-screen-np7lxflh/candidate.c, line 77: member of structure or union required
                     dx = D_802D3940[slot].v[1].r;
 ------------------------------------------^
cfe: Error: /tmp/kig-screen-np7lxflh/candidate.c, line 78: member of structure or union required
                     D_802D3940[slot].v[0].x += dx;
 -------------------------------------^
cfe: Error: /tmp/kig-screen-np7lxflh/candidate.c, line 79: member of structure or union required
                     D_802D3940[slot].v[1].x += dx;
 -------------------------------------^
cfe: Error: /tmp/kig-screen-np7lxflh/candidate.c, line 80: member of structure or union required
                     D_802D3940[slot].v[2].x += dx;
 -------------------------------------^
cfe: Error: /tmp/kig-screen-np7lxflh/candidate.c, line 81: member of structure or union required
                     dy = D_802D3940[slot].v[1].g;
 ------------------------------------------^
cfe: Error: /tmp/kig-screen-np7lxflh/candidate.c, line 82: member of structure or union required
                     D_802D3940[slot].v[0].y += dy;
 -------------------------------------^
cfe: Error: /tmp/kig-screen-np7lxflh/candidate.c, line 83: member of structure or union required
                     D_802D3940[slot].v[1].y += dy;
 -------------------------------------^
cfe: Error: /tmp/kig-screen-np7lxflh/candidate.c, line 84: member of structure or union required
                     D_802D3940[slot].v[2].y += dy;
 -------------------------------------^
```

### func_8001D47C (declarations)

```text
cfe: Error: /tmp/kig-screen-ooaizuq3/candidate.c, line 53: redeclaration of 'D_8004CE90'; previous declaration at line 38 in file '/tmp/kig-screen-ooaizuq3/candidate.c'
 extern u8 D_8004CE90[];
 ----------^
```

### func_800297A4 (declarations)

```text
cfe: Error: /tmp/kig-screen-pthdqyqm/candidate.c, line 107: redeclaration of 'D_80061D60'; previous declaration at line 99 in file '/tmp/kig-screen-pthdqyqm/candidate.c'
 extern T024Burst D_80061D60[];
 -----------------^
```

### func_801BF190 (declarations)

```text
cfe: Error: /tmp/kig-screen-mg3qz56r/candidate.c, line 127: redeclaration of 'D_80127D80'; previous declaration at line 32 in file '/tmp/kig-screen-mg3qz56r/candidate.c'
 extern T023Table190 D_80127D80[];
 --------------------^
```

### func_80031050 (declarations)

```text
cfe: Error: /tmp/kig-screen-xa0z198o/candidate.c, line 8: 'D_8004CED0' undefined; reoccurrences will not be reported.
     u8 *entry = (u8 *)D_8004CED0;
 ----------------------^
```

### func_801BEEA4 (declarations)

```text
cfe: Error: /tmp/kig-screen-z2v44cl_/candidate.c, line 56: redeclaration of 'D_80127D80'; previous declaration at line 32 in file '/tmp/kig-screen-z2v44cl_/candidate.c'
 extern T023TableEA4 D_80127D80[];
 --------------------^
```

### func_80015450 (prefix)

```text
cfe: Error: /tmp/kig-screen-5i2gy8tb/candidate.c, line 867: redeclaration of 'D_801D3430'; previous declaration at line 514 in file '/tmp/kig-screen-5i2gy8tb/candidate.c'
 extern T05518664Obj D_801D3430[40];
 --------------------^
```

### func_80023EF0 (declarations)

```text
cfe: Error: /tmp/kig-screen-94l0s4m_/candidate.c, line 246: redeclaration of 'D_801D3430'; previous declaration at line 82 in file '/tmp/kig-screen-94l0s4m_/candidate.c'
 extern T032Actor23E D_801D3430[], D_801D5C30[];
 --------------------^
```

### func_800300DC (declarations)

```text
cfe: Error: /tmp/kig-screen-d0y43kk4/candidate.c, line 49: redeclaration of 'func_800300DC'; previous declaration at line 15 in file '/tmp/kig-screen-d0y43kk4/candidate.c'
 void func_800300DC(u8 *src, s32 outputAddress, s32 length) {
 -----^
cfe: Error: /tmp/kig-screen-d0y43kk4/candidate.c, line 49: Incompatible type for the function parameter
 void func_800300DC(u8 *src, s32 outputAddress, s32 length) {
 -----------------------^
```

### func_800287D4 (prefix)

```text
cfe: Error: /tmp/kig-screen-p3jgj6wj/candidate.c, line 123: redeclaration of 'D_80061538'; previous declaration at line 83 in file '/tmp/kig-screen-p3jgj6wj/candidate.c'
 extern T024Particle D_80061538[][20];
 --------------------^
cfe: Error: /tmp/kig-screen-p3jgj6wj/candidate.c, line 126: 'active' undefined; reoccurrences will not be reported.
     D_80061538[group][index].active = 1;
 ----------------------------^
cfe: Error: /tmp/kig-screen-p3jgj6wj/candidate.c, line 126: member of structure or union required
     D_80061538[group][index].active = 1;
 -----------------------------^
```

### func_801BE790 (prefix)

```text
cfe: Error: /tmp/kig-screen-urtdjcw0/candidate.c, line 41: redeclaration of 'func_801BE910'; previous declaration at line 6 in file '/tmp/kig-screen-urtdjcw0/candidate.c'
 void func_801BE910(T023Entry910 *out, s32 count, s32 score, s32 step) {
 -----^
cfe: Error: /tmp/kig-screen-urtdjcw0/candidate.c, line 41: Incompatible type for the function parameter
 void func_801BE910(T023Entry910 *out, s32 count, s32 score, s32 step) {
 ---------------------------------^
cfe: Error: /tmp/kig-screen-urtdjcw0/candidate.c, line 65: redeclaration of 'D_80127D80'; previous declaration at line 5 in file '/tmp/kig-screen-urtdjcw0/candidate.c'
 extern T100ScoreTable D_80127D80[];
 ----------------------^
cfe: Error: /tmp/kig-screen-urtdjcw0/candidate.c, line 74: Selector requires struct/union as left hand side
         if (packed % 11 != 0) D_80127D80[i].entries[(packed % 11) - 1].name = text;
 ----------------------------------------------------------------------^
cfe: Error: /tmp/kig-screen-urtdjcw0/candidate.c, line 79: Selector requires struct/union as left hand side
         if (packed % 6 != 0) D_80127D80[i].entries[(packed % 6) - 1].name = text;
 --------------------------------------------------------------------^
cfe: Error: /tmp/kig-screen-urtdjcw0/candidate.c, line 91: redeclaration of 'D_80127E50'; previous declaration at line 9 in file '/tmp/kig-screen-urtdjcw0/candidate.c'
 extern T023Entry910 D_80127E50;
 --------------------^
cfe: Error: /tmp/kig-screen-urtdjcw0/candidate.c, line 92: redeclaration of 'D_80127EA0'; previous declaration at line 9 in file '/tmp/kig-screen-urtdjcw0/candidate.c'
 extern s32 D_80127EA0;
 -----------^
cfe: Error: /tmp/kig-screen-urtdjcw0/candidate.c, line 93: redeclaration of 'D_80127EF0'; previous declaration at line 9 in file '/tmp/kig-screen-urtdjcw0/candidate.c'
 extern s32 D_80127EF0;
 -----------^
cfe: Error: /tmp/kig-screen-urtdjcw0/candidate.c, line 94: redeclaration of 'D_80127F40'; previous declaration at line 9 in file '/tmp/kig-screen-urtdjcw0/candidate.c'
 extern s32 D_80127F40;
 -----------^
```

### func_800245B4 (declarations)

```text
cfe: Error: /tmp/kig-screen-6nzkpkek/candidate.c, line 291: redeclaration of 'D_8004D278'; previous declaration at line 264 in file '/tmp/kig-screen-6nzkpkek/candidate.c'
 extern T032Cache245 D_8004D278[];
 --------------------^
cfe: Error: /tmp/kig-screen-6nzkpkek/candidate.c, line 295: redeclaration of 'func_800245B4'; previous declaration at line 261 in file '/tmp/kig-screen-6nzkpkek/candidate.c'
 void func_800245B4(s32 player, u32 start, s32 size) {
 -----^
cfe: Error: /tmp/kig-screen-6nzkpkek/candidate.c, line 295: Incompatible type for the function parameter
 void func_800245B4(s32 player, u32 start, s32 size) {
 -----------------------------------^
cfe: Error: /tmp/kig-screen-6nzkpkek/candidate.c, line 297: Subscripting a non-array.
     T032Cache245 *bank = &D_8004D278[player];
 ------------------------------------^
```

### func_8001CD50 (declarations)

```text
cfe: Error: /tmp/kig-screen-s4l6q9v4/candidate.c, line 86: 'D_8004EA9C' undefined; reoccurrences will not be reported.
     func_8001D37C((*(u8 *)((u8 *)(D_8004EA9C) + 0)), (*(u8 *)((u8 *)(D_8004EA9C) + 1)));
 ----------------------------------^
cfe: Error: /tmp/kig-screen-s4l6q9v4/candidate.c, line 104: redeclaration of 'func_8001CF1C'; previous declaration at line 15 in file '/tmp/kig-screen-s4l6q9v4/candidate.c'
 void func_8001CF1C(void) {
 -----^
cfe: Error: /tmp/kig-screen-s4l6q9v4/candidate.c, line 104: Incompatible function return type for this function.
 void func_8001CF1C(void) {
 ------------------^
cfe: Error: /tmp/kig-screen-s4l6q9v4/candidate.c, line 130: redeclaration of 'func_8001D37C'; previous declaration at line 17 in file '/tmp/kig-screen-s4l6q9v4/candidate.c'
 void func_8001D37C(u8 arg0, u8 arg1) {
 -----^
cfe: Error: /tmp/kig-screen-s4l6q9v4/candidate.c, line 130: Incompatible function return type for this function.
 void func_8001D37C(u8 arg0, u8 arg1) {
 ------------------^
cfe: Error: /tmp/kig-screen-s4l6q9v4/candidate.c, line 146: redeclaration of 'T022Sprite'; previous declaration at line 11 in file '/tmp/kig-screen-s4l6q9v4/candidate.c'
 } T022Sprite;
 --^
```

### func_8002DDD4 (prefix)

```text
cfe: Error: /tmp/kig-screen-qluv6i50/candidate.c, line 116: redeclaration of 'func_8002DDD4'; previous declaration at line 106 in file '/tmp/kig-screen-qluv6i50/candidate.c'
 extern void func_8002DDD4(float, float, float, float *, float *);
 ------------^
cfe: Error: /tmp/kig-screen-qluv6i50/candidate.c, line 116: Incompatible type for the function parameter
 extern void func_8002DDD4(float, float, float, float *, float *);
 -----------------------------------------------^
```

### func_8002FB80 (prefix)

```text
cfe: Error: /tmp/kig-screen-kqpu31xa/candidate.c, line 9: redeclaration of 'func_8002FB80'; previous declaration at line 4 in file '/tmp/kig-screen-kqpu31xa/candidate.c'
 extern void func_8002FB80(s32, s32, s32, s32, s32);
 ------------^
cfe: Error: /tmp/kig-screen-kqpu31xa/candidate.c, line 9: Incompatible type for the function parameter
 extern void func_8002FB80(s32, s32, s32, s32, s32);
 --------------------------^
```

### func_800191F0 (declarations)

```text
cfe: Error: /tmp/kig-screen-ms1kuuwu/candidate.c, line 1209: redeclaration of 'D_801D3430'; previous declaration at line 851 in file '/tmp/kig-screen-ms1kuuwu/candidate.c'
 extern u8 D_801D3430;
 ----------^
```

### func_800170C4 (declarations)

```text
cfe: Error: /tmp/kig-screen-69gr6_rr/candidate.c, line 1020: redeclaration of 'D_80045030'; previous declaration at line 892 in file '/tmp/kig-screen-69gr6_rr/candidate.c'
 extern u8 D_80045030;
 ----------^
cfe: Error: /tmp/kig-screen-69gr6_rr/candidate.c, line 1021: redeclaration of 'D_80045060'; previous declaration at line 893 in file '/tmp/kig-screen-69gr6_rr/candidate.c'
 extern T033170C4Vertex *D_80045060;
 ------------------------^
cfe: Error: /tmp/kig-screen-69gr6_rr/candidate.c, line 1026: redeclaration of 'D_8004AC8D'; previous declaration at line 13 in file '/tmp/kig-screen-69gr6_rr/candidate.c'
 extern u8 D_8004AC8D;
 ----------^
cfe: Error: /tmp/kig-screen-69gr6_rr/candidate.c, line 1027: redeclaration of 'D_8004AD28'; previous declaration at line 895 in file '/tmp/kig-screen-69gr6_rr/candidate.c'
 extern T033170C4Vertex D_8004AD28;
 -----------------------^
cfe: Error: /tmp/kig-screen-69gr6_rr/candidate.c, line 1028: redeclaration of 'D_8004ADE8'; previous declaration at line 896 in file '/tmp/kig-screen-69gr6_rr/candidate.c'
 extern T033170C4Vertex D_8004ADE8;
 -----------------------^
cfe: Error: /tmp/kig-screen-69gr6_rr/candidate.c, line 1038: redeclaration of 'D_801D3430'; previous declaration at line 851 in file '/tmp/kig-screen-69gr6_rr/candidate.c'
 extern T033170C4Object D_801D3430;
 -----------------------^
```

### func_8002FDA0 (prefix)

```text
cfe: Error: /tmp/kig-screen-zsb7w5rm/candidate.c, line 12: redeclaration of 'func_8002FDA0'; previous declaration at line 8 in file '/tmp/kig-screen-zsb7w5rm/candidate.c'
 extern void func_8002FDA0(s32, s32, s32);
 ------------^
cfe: Error: /tmp/kig-screen-zsb7w5rm/candidate.c, line 12: Incompatible type for the function parameter
 extern void func_8002FDA0(s32, s32, s32);
 --------------------------^
```

### func_8001BB64 (declarations)

```text
cfe: Error: /tmp/kig-screen-205nzvmv/candidate.c, line 1429: redeclaration of 'D_8004AC92'; previous declaration at line 17 in file '/tmp/kig-screen-205nzvmv/candidate.c'
 extern u8 D_8004AA28,D_801D7DFC,D_801D7DF8,D_8004AC92,D_8004AC8E;
 -------------------------------------------^
cfe: Error: /tmp/kig-screen-205nzvmv/candidate.c, line 1429: redeclaration of 'D_8004AC8E'; previous declaration at line 17 in file '/tmp/kig-screen-205nzvmv/candidate.c'
 extern u8 D_8004AA28,D_801D7DFC,D_801D7DF8,D_8004AC92,D_8004AC8E;
 ------------------------------------------------------^
cfe: Error: /tmp/kig-screen-205nzvmv/candidate.c, line 1448: Unacceptable operand of == or !=
     } while (src != &D_8004AC92 + 3);
 -----------------^
cfe: Error: /tmp/kig-screen-205nzvmv/candidate.c, line 1458: Unacceptable operand of shift operator.
         cmd->w1 = ((&D_8004AC8E)[1] << 16) | ((&D_8004AC8E)[0] << 24) | ((b & 255) << 8) | 255;
 --------------------------------^
cfe: Error: /tmp/kig-screen-205nzvmv/candidate.c, line 1476: Unacceptable operand of shift operator.
         cmd->w1 = ((&D_8004AC8E)[2] << 8) | (r << 24) | ((&D_8004AC8E)[1] << 16) | 255;
 --------------------------------^
```

### func_800241BC (prefix)

```text
cfe: Error: /tmp/kig-screen-0pxiowu_/candidate.c, line 336: redeclaration of 'D_8004D278'; previous declaration at line 274 in file '/tmp/kig-screen-0pxiowu_/candidate.c'
 extern struct { u8 pad[0x12A8]; T032Bank banks[2]; } D_8004D278;
 -----------------------------------------------------^
cfe: Error: /tmp/kig-screen-0pxiowu_/candidate.c, line 357: Selector requires struct/union as left hand side
   D_8004D278.banks[player].data = base;
 ------------^
cfe: Error: /tmp/kig-screen-0pxiowu_/candidate.c, line 358: Selector requires struct/union as left hand side
   D_8004D278.banks[player].zero = 0;
 ------------^
```

### func_801ACB1C (prefix)

```text
cfe: Error: /tmp/kig-screen-gp_4wnf4/candidate.c, line 284: redeclaration of 'func_801AD3BC'; previous declaration at line 62 in file '/tmp/kig-screen-gp_4wnf4/candidate.c'
 void func_801AD3BC(DisplayCommand **arg0, RenderState *arg1) {
 -----^
cfe: Error: /tmp/kig-screen-gp_4wnf4/candidate.c, line 284: Incompatible type for the function parameter
 void func_801AD3BC(DisplayCommand **arg0, RenderState *arg1) {
 ------------------------------------^
```

### func_800131A4 (declarations)

```text
cfe: Error: /tmp/kig-screen-3e6nt1ir/candidate.c, line 79: redeclaration of 'D_8004A738'; previous declaration at line 4 in file '/tmp/kig-screen-3e6nt1ir/candidate.c'
 extern s8 D_8004A738, D_8004A688;
 ----------^
cfe: Error: /tmp/kig-screen-3e6nt1ir/candidate.c, line 79: redeclaration of 'D_8004A688'; previous declaration at line 6 in file '/tmp/kig-screen-3e6nt1ir/candidate.c'
 extern s8 D_8004A738, D_8004A688;
 ----------------------^
cfe: Error: /tmp/kig-screen-3e6nt1ir/candidate.c, line 117: Unacceptable operand of relational operator.
     if ((&D_8004A738)[part] > 0) {
 ----------------------------^
cfe: Error: /tmp/kig-screen-3e6nt1ir/candidate.c, line 125: Unacceptable operand of relational operator.
         } while (i < (&D_8004A738)[part]);
 -------------------^
```

### func_8001808C (declarations)

```text
cfe: Error: /tmp/kig-screen-4760sg4w/candidate.c, line 1041: redeclaration of 'D_8004A5E0'; previous declaration at line 5 in file '/tmp/kig-screen-4760sg4w/candidate.c'
 extern s8 D_8004A5E0;
 ----------^
cfe: Error: /tmp/kig-screen-4760sg4w/candidate.c, line 1042: redeclaration of 'D_8004A730'; previous declaration at line 3 in file '/tmp/kig-screen-4760sg4w/candidate.c'
 extern s8 D_8004A730;
 ----------^
cfe: Error: /tmp/kig-screen-4760sg4w/candidate.c, line 1043: redeclaration of 'D_8004A738'; previous declaration at line 4 in file '/tmp/kig-screen-4760sg4w/candidate.c'
 extern s8 D_8004A738;
 ----------^
cfe: Error: /tmp/kig-screen-4760sg4w/candidate.c, line 1047: redeclaration of 'D_8004AC89'; previous declaration at line 116 in file '/tmp/kig-screen-4760sg4w/candidate.c'
 extern s8 D_8004AC89;
 ----------^
cfe: Error: /tmp/kig-screen-4760sg4w/candidate.c, line 1048: redeclaration of 'D_8004AC8A'; previous declaration at line 117 in file '/tmp/kig-screen-4760sg4w/candidate.c'
 extern s8 D_8004AC8A;
 ----------^
cfe: Error: /tmp/kig-screen-4760sg4w/candidate.c, line 1067: redeclaration of 'D_800614D8'; previous declaration at line 121 in file '/tmp/kig-screen-4760sg4w/candidate.c'
 extern u8 D_800614D8;
 ----------^
cfe: Error: /tmp/kig-screen-4760sg4w/candidate.c, line 1069: redeclaration of 'D_80061CB8'; previous declaration at line 123 in file '/tmp/kig-screen-4760sg4w/candidate.c'
 extern u8 D_80061CB8;
 ----------^
cfe: Error: /tmp/kig-screen-4760sg4w/candidate.c, line 1104: This expression is not an lvalue.
     D_8004A730 = 9;
 ---------------^
cfe: Error: /tmp/kig-screen-4760sg4w/candidate.c, line 1114: This expression is not an lvalue.
     D_8004A738 = 0;
 ---------------^
cfe: Error: /tmp/kig-screen-4760sg4w/candidate.c, line 1165: redeclaration of 'T022Position'; previous declaration at line 1027 in file '/tmp/kig-screen-4760sg4w/candidate.c'
 typedef struct { u8 pad[0x28]; s16 x, y, z; } T022Position;
 ----------------------------------------------^
```

### func_801B2B8C (prefix)

```text
cfe: Error: /tmp/kig-screen-8usqgd2y/candidate.c, line 571: redeclaration of 'func_8002F6F4'; previous declaration at line 341 in file '/tmp/kig-screen-8usqgd2y/candidate.c'
 extern void func_8002F6F4(s32, s32, void *);
 ------------^
cfe: Error: /tmp/kig-screen-8usqgd2y/candidate.c, line 571: Incompatible function return type for this function.
 extern void func_8002F6F4(s32, s32, void *);
 -------------------------^
```

### func_800193DC (declarations)

```text
cfe: Error: /tmp/kig-screen-by3p1n60/candidate.c, line 1212: redeclaration of 'D_8004A5E0'; previous declaration at line 5 in file '/tmp/kig-screen-by3p1n60/candidate.c'
 extern s8 D_8004A5E0;
 ----------^
cfe: Error: /tmp/kig-screen-by3p1n60/candidate.c, line 1213: redeclaration of 'D_8004A738'; previous declaration at line 4 in file '/tmp/kig-screen-by3p1n60/candidate.c'
 extern s8 D_8004A738;
 ----------^
cfe: Error: /tmp/kig-screen-by3p1n60/candidate.c, line 1214: redeclaration of 'D_8004AC89'; previous declaration at line 116 in file '/tmp/kig-screen-by3p1n60/candidate.c'
 extern s8 D_8004AC89;
 ----------^
cfe: Error: /tmp/kig-screen-by3p1n60/candidate.c, line 1215: redeclaration of 'D_8004AC8A'; previous declaration at line 117 in file '/tmp/kig-screen-by3p1n60/candidate.c'
 extern s8 D_8004AC8A;
 ----------^
cfe: Error: /tmp/kig-screen-by3p1n60/candidate.c, line 1243: redeclaration of 'D_800614D8'; previous declaration at line 121 in file '/tmp/kig-screen-by3p1n60/candidate.c'
 extern u8 D_800614D8;
 ----------^
cfe: Error: /tmp/kig-screen-by3p1n60/candidate.c, line 1245: redeclaration of 'D_80061CB8'; previous declaration at line 123 in file '/tmp/kig-screen-by3p1n60/candidate.c'
 extern u8 D_80061CB8;
 ----------^
cfe: Error: /tmp/kig-screen-by3p1n60/candidate.c, line 1279: This expression is not an lvalue.
     D_8004A738 = 0;
 ---------------^
```

### func_80018AE0 (declarations)

```text
cfe: Error: /tmp/kig-screen-yaxy4k57/candidate.c, line 1203: redeclaration of 'D_800614D8'; previous declaration at line 121 in file '/tmp/kig-screen-yaxy4k57/candidate.c'
 extern u8 D_800614D8;
 ----------^
cfe: Error: /tmp/kig-screen-yaxy4k57/candidate.c, line 1204: redeclaration of 'D_80061520'; previous declaration at line 122 in file '/tmp/kig-screen-yaxy4k57/candidate.c'
 extern s8 D_80061520;
 ----------^
cfe: Error: /tmp/kig-screen-yaxy4k57/candidate.c, line 1205: redeclaration of 'D_80061CB8'; previous declaration at line 123 in file '/tmp/kig-screen-yaxy4k57/candidate.c'
 extern u8 D_80061CB8;
 ----------^
cfe: Error: /tmp/kig-screen-yaxy4k57/candidate.c, line 1264: This expression is not an lvalue.
     D_8004A730 = 9;
 ---------------^
cfe: Error: /tmp/kig-screen-yaxy4k57/candidate.c, line 1274: This expression is not an lvalue.
     D_8004A738 = 0;
 ---------------^
```

### func_801B0CDC (prefix)

```text
cfe: Error: /tmp/kig-screen-3z1rd5gj/candidate.c, line 175: redeclaration of 'D_801CD454'; previous declaration at line 33 in file '/tmp/kig-screen-3z1rd5gj/candidate.c'
 extern s8 D_801CD454;
 ----------^
```

### func_801B1A7C (prefix)

```text
cfe: Error: /tmp/kig-screen-e953j7kt/candidate.c, line 47: redeclaration of 'func_801B1A7C'; previous declaration at line 23 in file '/tmp/kig-screen-e953j7kt/candidate.c'
 extern f32 func_801B1A7C(void *, void *, f32, s32);
 -----------^
cfe: Error: /tmp/kig-screen-e953j7kt/candidate.c, line 47: Incompatible type for the function parameter
 extern f32 func_801B1A7C(void *, void *, f32, s32);
 -------------------------^
cfe: Error: /tmp/kig-screen-e953j7kt/candidate.c, line 91: redeclaration of 'func_801B1A7C'; previous declaration at line 23 in file '/tmp/kig-screen-e953j7kt/candidate.c'
 extern f32 func_801B1A7C(void *, void *, f32, s32);
 -----------^
cfe: Error: /tmp/kig-screen-e953j7kt/candidate.c, line 91: Incompatible type for the function parameter
 extern f32 func_801B1A7C(void *, void *, f32, s32);
 -------------------------^
cfe: Error: /tmp/kig-screen-e953j7kt/candidate.c, line 135: redeclaration of 'func_801B1A7C'; previous declaration at line 23 in file '/tmp/kig-screen-e953j7kt/candidate.c'
 extern f32 func_801B1A7C(void *, void *, f32, s32);
 -----------^
cfe: Error: /tmp/kig-screen-e953j7kt/candidate.c, line 135: Incompatible type for the function parameter
 extern f32 func_801B1A7C(void *, void *, f32, s32);
 -------------------------^
cfe: Error: /tmp/kig-screen-e953j7kt/candidate.c, line 179: redeclaration of 'func_801B1A7C'; previous declaration at line 23 in file '/tmp/kig-screen-e953j7kt/candidate.c'
 extern f32 func_801B1A7C(void *, void *, f32, s32);
 -----------^
cfe: Error: /tmp/kig-screen-e953j7kt/candidate.c, line 179: Incompatible type for the function parameter
 extern f32 func_801B1A7C(void *, void *, f32, s32);
 -------------------------^
cfe: Error: /tmp/kig-screen-e953j7kt/candidate.c, line 223: redeclaration of 'func_801B1A7C'; previous declaration at line 23 in file '/tmp/kig-screen-e953j7kt/candidate.c'
 extern f32 func_801B1A7C(void *, void *, f32, s32);
 -----------^
cfe: Error: /tmp/kig-screen-e953j7kt/candidate.c, line 223: Incompatible type for the function parameter
 extern f32 func_801B1A7C(void *, void *, f32, s32);
 -------------------------^
cfe: Error: /tmp/kig-screen-e953j7kt/candidate.c, line 267: redeclaration of 'func_801B1A7C'; previous declaration at line 23 in file '/tmp/kig-screen-e953j7kt/candidate.c'
 extern f32 func_801B1A7C(void *, void *, f32, s32);
 -----------^
cfe: Error: /tmp/kig-screen-e953j7kt/candidate.c, line 267: Incompatible type for the function parameter
 extern f32 func_801B1A7C(void *, void *, f32, s32);
 -------------------------^
cfe: Error: /tmp/kig-screen-e953j7kt/candidate.c, line 311: redeclaration of 'func_801B1A7C'; previous declaration at line 23 in file '/tmp/kig-screen-e953j7kt/candidate.c'
 extern f32 func_801B1A7C(void *, void *, f32, s32);
 -----------^
cfe: Error: /tmp/kig-screen-e953j7kt/candidate.c, line 311: Incompatible type for the function parameter
 extern f32 func_801B1A7C(void *, void *, f32, s32);
 -------------------------^
```

### func_801C3AA0 (declarations)

```text
cfe: Error: /tmp/kig-screen-q21dy2c1/candidate.c, line 49: redeclaration of 'D_802D3940'; previous declaration at line 14 in file '/tmp/kig-screen-q21dy2c1/candidate.c'
 extern T030Triangle3AA0 *D_802D3940;
 -------------------------^
cfe: Error: /tmp/kig-screen-q21dy2c1/candidate.c, line 75: 'v' undefined; reoccurrences will not be reported.
                 D_802D3940[slot].v[0].x = px-30;
 --------------------------------^
cfe: Error: /tmp/kig-screen-q21dy2c1/candidate.c, line 75: member of structure or union required
                 D_802D3940[slot].v[0].x = px-30;
 ---------------------------------^
cfe: Error: /tmp/kig-screen-q21dy2c1/candidate.c, line 76: member of structure or union required
                 D_802D3940[slot].v[0].y = py;
 ---------------------------------^
cfe: Error: /tmp/kig-screen-q21dy2c1/candidate.c, line 77: member of structure or union required
                 D_802D3940[slot].v[0].z = pz;
 ---------------------------------^
cfe: Error: /tmp/kig-screen-q21dy2c1/candidate.c, line 78: member of structure or union required
                 D_802D3940[slot].v[0].a = 255;
 ---------------------------------^
cfe: Error: /tmp/kig-screen-q21dy2c1/candidate.c, line 80: member of structure or union required
                 D_802D3940[slot].v[1].a = (absRandom*8)/intWidth;
 ---------------------------------^
cfe: Error: /tmp/kig-screen-q21dy2c1/candidate.c, line 81: member of structure or union required
                 D_802D3940[slot].v[1].x = px+30;
 ---------------------------------^
cfe: Error: /tmp/kig-screen-q21dy2c1/candidate.c, line 82: member of structure or union required
                 D_802D3940[slot].v[1].y = py;
 ---------------------------------^
cfe: Error: /tmp/kig-screen-q21dy2c1/candidate.c, line 83: member of structure or union required
                 D_802D3940[slot].v[1].z = pz;
 ---------------------------------^
cfe: Error: /tmp/kig-screen-q21dy2c1/candidate.c, line 84: member of structure or union required
                 D_802D3940[slot].v[2].x = px;
 ---------------------------------^
cfe: Error: /tmp/kig-screen-q21dy2c1/candidate.c, line 85: member of structure or union required
                 D_802D3940[slot].v[2].y = py-30;
 ---------------------------------^
cfe: Error: /tmp/kig-screen-q21dy2c1/candidate.c, line 86: member of structure or union required
                 D_802D3940[slot].v[2].z = pz;
 ---------------------------------^
cfe: Error: /tmp/kig-screen-q21dy2c1/candidate.c, line 87: member of structure or union required
                 D_802D3940[slot].v[1].r = guRandom()%3;
 ---------------------------------^
cfe: Error: /tmp/kig-screen-q21dy2c1/candidate.c, line 90: member of structure or union required
                 D_802D3940[slot].v[1].g = guRandom()%5-1;
 ---------------------------------^
```

### func_801BB7B4 (declarations)

```text
cfe: Error: /tmp/kig-screen-kpj2i3fn/candidate.c, line 696: redeclaration of 'func_8002F6F4'; previous declaration at line 474 in file '/tmp/kig-screen-kpj2i3fn/candidate.c'
 extern s32 func_8002F6F4();
 -----------^
cfe: Error: /tmp/kig-screen-kpj2i3fn/candidate.c, line 696: Incompatible function return type for this function.
 extern s32 func_8002F6F4();
 ------------------------^
cfe: Error: /tmp/kig-screen-kpj2i3fn/candidate.c, line 704: redeclaration of 'D_80127CE8'; previous declaration at line 375 in file '/tmp/kig-screen-kpj2i3fn/candidate.c'
 extern u8 D_80127CE8[];
 ----------^
cfe: Error: /tmp/kig-screen-kpj2i3fn/candidate.c, line 708: redeclaration of 'D_802C8CB8'; previous declaration at line 357 in file '/tmp/kig-screen-kpj2i3fn/candidate.c'
 extern u8 D_802C8CB8;
 ----------^
cfe: Error: /tmp/kig-screen-kpj2i3fn/candidate.c, line 711: redeclaration of 'D_802C8CEA'; previous declaration at line 379 in file '/tmp/kig-screen-kpj2i3fn/candidate.c'
 extern u8 D_802C8CEA;
 ----------^
cfe: Error: /tmp/kig-screen-kpj2i3fn/candidate.c, line 741: Unacceptable operand of a multiplicative operator.
             temp_a1 = *(s32 *)(D_801F2EB8 + (D_80127CE8[D_802C8D0D] * 0x8C));
 -------------------------------------------------------^
cfe: Error: /tmp/kig-screen-kpj2i3fn/candidate.c, line 757: Unacceptable operand of a multiplicative operator.
             func_8002F6F4(D_80066C40, *(s32 *)(D_801F2EB8 + (D_802C8CB8 * 0x8C)), &D_8004A258);
 -------------------------------------------------------------^
```

### func_800216D4 (prefix)

```text
cfe: Error: /tmp/kig-screen-wggtwksv/candidate.c, line 336: redeclaration of 'D_8004D278'; previous declaration at line 211 in file '/tmp/kig-screen-wggtwksv/candidate.c'
 extern struct { u8 pad[0x12A8]; T032Bank banks[2]; } D_8004D278;
 -----------------------------------------------------^
cfe: Error: /tmp/kig-screen-wggtwksv/candidate.c, line 357: Selector requires struct/union as left hand side
   D_8004D278.banks[player].data = base;
 ------------^
cfe: Error: /tmp/kig-screen-wggtwksv/candidate.c, line 358: Selector requires struct/union as left hand side
   D_8004D278.banks[player].zero = 0;
 ------------^
```

### func_80031A38 (declarations)

```text
cfe: Error: /tmp/kig-screen-q_7dyg3k/candidate.c, line 12: Syntax Error
     T022Sprite *sprite = &D_8004CED0[D_8004EA78];
 -----------------------^
cfe: Error: /tmp/kig-screen-q_7dyg3k/candidate.c, line 13: Syntax Error
     u8 *out = sprite->data;
 -------^
cfe: Error: /tmp/kig-screen-q_7dyg3k/candidate.c, line 14: Syntax Error
     s32 width = input[4] + (input[5]<<8);
 --------^
cfe: Error: /tmp/kig-screen-q_7dyg3k/candidate.c, line 15: Syntax Error
     s32 height = input[6] + (input[7]<<8);
 --------^
cfe: Error: /tmp/kig-screen-q_7dyg3k/candidate.c, line 16: Syntax Error
     s32 stride = (width+7)&0xFFF8;
 --------^
cfe: Error: /tmp/kig-screen-q_7dyg3k/candidate.c, line 17: Syntax Error
     s32 y;
 --------^
```

### func_801AF68C (prefix)

```text
cfe: Error: /tmp/kig-screen-60fmso_6/candidate.c, line 151: redeclaration of 'D_802A1A60'; previous declaration at line 85 in file '/tmp/kig-screen-60fmso_6/candidate.c'
 extern s32 D_802A1A60[];
 -----------^
```

### func_80029BE0 (declarations)

```text
cfe: Error: /tmp/kig-screen-a4vf2xmp/candidate.c, line 131: redeclaration of 'D_80061D60'; previous declaration at line 99 in file '/tmp/kig-screen-a4vf2xmp/candidate.c'
 extern T024DrawBurst D_80061D60[];
 ---------------------^
cfe: Error: /tmp/kig-screen-a4vf2xmp/candidate.c, line 141: redeclaration of 'func_8002A004'; previous declaration at line 134 in file '/tmp/kig-screen-a4vf2xmp/candidate.c'
 void func_8002A004(float m[4][4], float x, float y, float z) {
 -----^
cfe: Error: /tmp/kig-screen-a4vf2xmp/candidate.c, line 141: Incompatible type for the function parameter
 void func_8002A004(float m[4][4], float x, float y, float z) {
 -------------------------^
```

### func_80015594 (declarations)

```text
cfe: Error: /tmp/kig-screen-n9idz10k/candidate.c, line 509: redeclaration of 'func_80015594'; previous declaration at line 146 in file '/tmp/kig-screen-n9idz10k/candidate.c'
 void func_80015594(T03315594Command **arg0,s32 *arg1,f32 arg2,s32 arg3,f32 arg4,f32 arg5,f32 arg6) {
 -----^
cfe: Error: /tmp/kig-screen-n9idz10k/candidate.c, line 509: prototype and non-prototype declaration found for func_80015594, the type of this parameter is not compatible with the type after applying default argument promotion
 void func_80015594(T03315594Command **arg0,s32 *arg1,f32 arg2,s32 arg3,f32 arg4,f32 arg5,f32 arg6) {
 ---------------------------------------------------------^
```

### func_80031DD0 (declarations)

```text
cfe: Error: /tmp/kig-screen-dqgwugid/candidate.c, line 16: Syntax Error
     T022Sprite *sprite = &D_8004CED0[D_8004EA78];
 -----------------------^
cfe: Error: /tmp/kig-screen-dqgwugid/candidate.c, line 17: Syntax Error
     u8 *intensity = sprite->data;
 -------^
cfe: Error: /tmp/kig-screen-dqgwugid/candidate.c, line 18: Syntax Error
     u16 *color = (u16 *)sprite->unk0;
 --------^
cfe: Error: /tmp/kig-screen-dqgwugid/candidate.c, line 18: Syntax Error
     u16 *color = (u16 *)sprite->unk0;
 -----------------------^
cfe: Error: /tmp/kig-screen-dqgwugid/candidate.c, line 19: Syntax Error
     u16 *palette = D_800482D0[((s16 *)sprite)[13]];
 --------^
cfe: Error: /tmp/kig-screen-dqgwugid/candidate.c, line 19: Syntax Error
     u16 *palette = D_800482D0[((s16 *)sprite)[13]];
 -------------------------------------^
cfe: Error: /tmp/kig-screen-dqgwugid/candidate.c, line 21: Syntax Error
     s32 top = vertical >> 16;
 --------^
cfe: Error: /tmp/kig-screen-dqgwugid/candidate.c, line 22: Syntax Error
     s32 height = input[6] + (input[7]<<8);
 --------^
cfe: Error: /tmp/kig-screen-dqgwugid/candidate.c, line 23: Syntax Error
     s32 y;
 --------^
```

### func_80014D5C (prefix)

```text
cfe: Error: /tmp/kig-screen-nr1wn04r/candidate.c, line 810: redeclaration of 'func_8002F8F8'; previous declaration at line 527 in file '/tmp/kig-screen-nr1wn04r/candidate.c'
 extern void func_8002F8F8(void *);
 ------------^
cfe: Error: /tmp/kig-screen-nr1wn04r/candidate.c, line 810: Incompatible function return type for this function.
 extern void func_8002F8F8(void *);
 -------------------------^
cfe: Error: /tmp/kig-screen-nr1wn04r/candidate.c, line 811: redeclaration of 'func_8002F6F4'; previous declaration at line 526 in file '/tmp/kig-screen-nr1wn04r/candidate.c'
 extern void *func_8002F6F4(void *, s16, void **);
 -------------^
cfe: Error: /tmp/kig-screen-nr1wn04r/candidate.c, line 811: Incompatible function return type for this function.
 extern void *func_8002F6F4(void *, s16, void **);
 --------------------------^
```

### func_80012B7C (declarations)

```text
cfe: Error: /tmp/kig-screen-ffdud8j7/candidate.c, line 76: redeclaration of 'D_8004A730'; previous declaration at line 3 in file '/tmp/kig-screen-ffdud8j7/candidate.c'
 extern s8 D_8004A730, D_8004A5E0;
 ----------^
cfe: Error: /tmp/kig-screen-ffdud8j7/candidate.c, line 76: redeclaration of 'D_8004A5E0'; previous declaration at line 5 in file '/tmp/kig-screen-ffdud8j7/candidate.c'
 extern s8 D_8004A730, D_8004A5E0;
 ----------------------^
```

### func_8001D7E4 (prefix)

```text
cfe: Error: /tmp/kig-screen-68xr70t2/candidate.c, line 473: redeclaration of 'D_8004D278'; previous declaration at line 80 in file '/tmp/kig-screen-68xr70t2/candidate.c'
 extern struct { u8 pad[0x12A8]; T032Bank banks[2]; } D_8004D278;
 -----------------------------------------------------^
cfe: Error: /tmp/kig-screen-68xr70t2/candidate.c, line 494: Selector requires struct/union as left hand side
   D_8004D278.banks[player].data = base;
 ------------^
cfe: Error: /tmp/kig-screen-68xr70t2/candidate.c, line 495: Selector requires struct/union as left hand side
   D_8004D278.banks[player].zero = 0;
 ------------^
```

### func_80020E98 (prefix)

```text
cfe: Error: /tmp/kig-screen-lgg6z38h/candidate.c, line 407: redeclaration of 'D_8004D278'; previous declaration at line 213 in file '/tmp/kig-screen-lgg6z38h/candidate.c'
 extern struct { u8 pad[0x12A8]; T032Bank banks[2]; } D_8004D278;
 -----------------------------------------------------^
cfe: Error: /tmp/kig-screen-lgg6z38h/candidate.c, line 428: Selector requires struct/union as left hand side
   D_8004D278.banks[player].data = base;
 ------------^
cfe: Error: /tmp/kig-screen-lgg6z38h/candidate.c, line 429: Selector requires struct/union as left hand side
   D_8004D278.banks[player].zero = 0;
 ------------^
```

### func_801C5E74 (declarations)

```text
cfe: Error: /tmp/kig-screen-3oui708t/candidate.c, line 296: redeclaration of 'func_801C5064'; previous declaration at line 227 in file '/tmp/kig-screen-3oui708t/candidate.c'
 extern void func_801C5064(T030Cmd5E74 **,T030Render5E74 *,s32,s32);
 ------------^
cfe: Error: /tmp/kig-screen-3oui708t/candidate.c, line 296: Incompatible type for the function parameter
 extern void func_801C5064(T030Cmd5E74 **,T030Render5E74 *,s32,s32);
 --------------------------^
cfe: Error: /tmp/kig-screen-3oui708t/candidate.c, line 297: redeclaration of 'func_801C51F8'; previous declaration at line 258 in file '/tmp/kig-screen-3oui708t/candidate.c'
 extern void func_801C51F8(T030Cmd5E74 **);
 ------------^
cfe: Error: /tmp/kig-screen-3oui708t/candidate.c, line 297: Incompatible type for the function parameter
 extern void func_801C51F8(T030Cmd5E74 **);
 --------------------------^
```

### func_8001178C (prefix)

```text
cfe: Error: /tmp/kig-screen-rrkw2mo3/candidate.c, line 347: redeclaration of 'func_80011FC4'; previous declaration at line 96 in file '/tmp/kig-screen-rrkw2mo3/candidate.c'
 s32 func_80011FC4(T020Controller *arg0, u8 arg1) {
 ----^
cfe: Error: /tmp/kig-screen-rrkw2mo3/candidate.c, line 347: prototype and non-prototype declaration found for func_80011FC4, the type of this parameter is not compatible with the type after applying default argument promotion
 s32 func_80011FC4(T020Controller *arg0, u8 arg1) {
 -------------------------------------------^
cfe: Error: /tmp/kig-screen-rrkw2mo3/candidate.c, line 379: redeclaration of 'func_80012100'; previous declaration at line 97 in file '/tmp/kig-screen-rrkw2mo3/candidate.c'
 void func_80012100(u8 arg0, u8 arg1) {
 -----^
cfe: Error: /tmp/kig-screen-rrkw2mo3/candidate.c, line 379: prototype and non-prototype declaration found for func_80012100, the type of this parameter is not compatible with the type after applying default argument promotion
 void func_80012100(u8 arg0, u8 arg1) {
 ----------------------^
cfe: Error: /tmp/kig-screen-rrkw2mo3/candidate.c, line 468: redeclaration of 'D_8004A258'; previous declaration at line 56 in file '/tmp/kig-screen-rrkw2mo3/candidate.c'
 extern void *D_8004A258[];
 -------------^
cfe: Error: /tmp/kig-screen-rrkw2mo3/candidate.c, line 475: Subscripting a non-array.
         if (D_8004A258[i] != 0) {
 ----------------------^
cfe: Error: /tmp/kig-screen-rrkw2mo3/candidate.c, line 476: Subscripting a non-array.
             func_8002F8F8(D_8004A258[i]);
 ------------------------------------^
```

### func_8001E33C (declarations)

```text
cfe: Error: /tmp/kig-screen-sy3vk6ke/candidate.c, line 202: redeclaration of 'func_8001EC74'; previous declaration at line 74 in file '/tmp/kig-screen-sy3vk6ke/candidate.c'
 s32 func_8001EC74(T081Gfx **, s32, s32, u32, u32, u8, u8, u8);
 ----^
cfe: Error: /tmp/kig-screen-sy3vk6ke/candidate.c, line 202: Incompatible type for the function parameter
 s32 func_8001EC74(T081Gfx **, s32, s32, u32, u32, u8, u8, u8);
 ------------------^
cfe: Error: /tmp/kig-screen-sy3vk6ke/candidate.c, line 220: redeclaration of 'D_8004A450'; previous declaration at line 78 in file '/tmp/kig-screen-sy3vk6ke/candidate.c'
 extern T081Object D_8004A450[];
 ------------------^
```

### func_800142E0 (declarations)

```text
cfe: Error: /tmp/kig-screen-1rsu3_0y/candidate.c, line 485: redeclaration of 'func_800142E0'; previous declaration at line 307 in file '/tmp/kig-screen-1rsu3_0y/candidate.c'
 void func_800142E0(T033142E0Command **arg0, s32 *arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6) {
 -----^
cfe: Error: /tmp/kig-screen-1rsu3_0y/candidate.c, line 485: prototype and non-prototype declaration found for func_800142E0, the type of this parameter is not compatible with the type after applying default argument promotion
 void func_800142E0(T033142E0Command **arg0, s32 *arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6) {
 -------------------------------------------------------------------------------^
```

### func_801BC1B0 (declarations)

```text
cfe: Error: /tmp/kig-screen-rwdk4ixu/candidate.c, line 703: redeclaration of 'func_801BC1B0'; previous declaration at line 496 in file '/tmp/kig-screen-rwdk4ixu/candidate.c'
 void func_801BC1B0(u8 **arg0, s32 arg1, s32 arg2, u32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, u32 arg8, s32 arg9, u32 arg10, f32 arg11, f32 arg12, s32 arg13, s32 arg14) {
 -----^
cfe: Error: /tmp/kig-screen-rwdk4ixu/candidate.c, line 703: Incompatible type for the function parameter
 void func_801BC1B0(u8 **arg0, s32 arg1, s32 arg2, u32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, u32 arg8, s32 arg9, u32 arg10, f32 arg11, f32 arg12, s32 arg13, s32 arg14) {
 ------------------------^
```

### func_801ABB20 (prefix)

```text
cfe: Error: /tmp/kig-screen-7x53stw_/candidate.c, line 626: redeclaration of 'D_8004A428'; previous declaration at line 77 in file '/tmp/kig-screen-7x53stw_/candidate.c'
 extern u32 D_8004A428[];
 -----------^
cfe: Error: /tmp/kig-screen-7x53stw_/candidate.c, line 677: redeclaration of 'func_801AD794'; previous declaration at line 37 in file '/tmp/kig-screen-7x53stw_/candidate.c'
 void func_801AD794(RenderState *arg0, s32 arg1, s32 arg2, s32 arg3) {
 -----^
cfe: Error: /tmp/kig-screen-7x53stw_/candidate.c, line 677: Incompatible type for the function parameter
 void func_801AD794(RenderState *arg0, s32 arg1, s32 arg2, s32 arg3) {
 --------------------------------^
```

### func_800310C0 (declarations)

```text
cfe: Error: /tmp/kig-screen-smpqforx/candidate.c, line 88: 'D_8004CED0' undefined; reoccurrences will not be reported.
     var_s1 = (u8 *)D_8004CED0;
 -------------------^
```

### func_801C5298 (declarations)

```text
cfe: Error: /tmp/kig-screen-3ndyuoo_/candidate.c, line 299: redeclaration of 'func_801C5064'; previous declaration at line 227 in file '/tmp/kig-screen-3ndyuoo_/candidate.c'
 extern void func_801C5064(T030Cmd5298 **,T030Render5298 *,s32,s32);
 ------------^
cfe: Error: /tmp/kig-screen-3ndyuoo_/candidate.c, line 299: Incompatible type for the function parameter
 extern void func_801C5064(T030Cmd5298 **,T030Render5298 *,s32,s32);
 --------------------------^
cfe: Error: /tmp/kig-screen-3ndyuoo_/candidate.c, line 300: redeclaration of 'func_801C51F8'; previous declaration at line 258 in file '/tmp/kig-screen-3ndyuoo_/candidate.c'
 extern void func_801C51F8(T030Cmd5298 **);
 ------------^
cfe: Error: /tmp/kig-screen-3ndyuoo_/candidate.c, line 300: Incompatible type for the function parameter
 extern void func_801C51F8(T030Cmd5298 **);
 --------------------------^
cfe: Error: /tmp/kig-screen-3ndyuoo_/candidate.c, line 304: redeclaration of 'D_4AC40'; previous declaration at line 256 in file '/tmp/kig-screen-3ndyuoo_/candidate.c'
 extern u8 D_4AC40[],D_801F3164[],D_801F3176[],D_801F3308[],D_801F331A[];
 ----------^
cfe: Error: /tmp/kig-screen-3ndyuoo_/candidate.c, line 320: redeclaration of 'D_802D3990'; previous declaration at line 178 in file '/tmp/kig-screen-3ndyuoo_/candidate.c'
 extern f32 D_802D3990[];
 -----------^
cfe: Error: /tmp/kig-screen-3ndyuoo_/candidate.c, line 321: redeclaration of 'D_802D399F'; previous declaration at line 188 in file '/tmp/kig-screen-3ndyuoo_/candidate.c'
 extern u8 D_802D3985,D_802D399C,D_802D399F,D_802D39B4,D_802D39B6,D_802D39BA;
 --------------------------------^
cfe: Error: /tmp/kig-screen-3ndyuoo_/candidate.c, line 440: Subscripting a non-array.
         func_8002DDD4(D_802D3990[0], D_802D3990[1], D_802D3990[2], &spEC, &spE8);
 --------------------------------^
cfe: Error: /tmp/kig-screen-3ndyuoo_/candidate.c, line 440: Subscripting a non-array.
         func_8002DDD4(D_802D3990[0], D_802D3990[1], D_802D3990[2], &spEC, &spE8);
 -----------------------------------------------^
cfe: Error: /tmp/kig-screen-3ndyuoo_/candidate.c, line 440: Subscripting a non-array.
         func_8002DDD4(D_802D3990[0], D_802D3990[1], D_802D3990[2], &spEC, &spE8);
 --------------------------------------------------------------^
cfe: Error: /tmp/kig-screen-3ndyuoo_/candidate.c, line 441: Subscripting a non-array.
         func_8002DCC8(D_802D3990[0], D_802D3990[1], D_802D3990[2], &spE4);
 --------------------------------^
cfe: Error: /tmp/kig-screen-3ndyuoo_/candidate.c, line 441: Subscripting a non-array.
         func_8002DCC8(D_802D3990[0], D_802D3990[1], D_802D3990[2], &spE4);
 -----------------------------------------------^
cfe: Error: /tmp/kig-screen-3ndyuoo_/candidate.c, line 441: Subscripting a non-array.
         func_8002DCC8(D_802D3990[0], D_802D3990[1], D_802D3990[2], &spE4);
 --------------------------------------------------------------^
```

### func_80028A00 (declarations)

```text
cfe: Error: /tmp/kig-screen-jbe8uakc/candidate.c, line 127: Syntax Error
     T024RenderParticle *particle;
 -----------------------^
cfe: Error: /tmp/kig-screen-jbe8uakc/candidate.c, line 128: Syntax Error
     f32 temp_f20;
 --------^
cfe: Error: /tmp/kig-screen-jbe8uakc/candidate.c, line 129: Syntax Error
     f32 temp_f22;
 --------^
cfe: Error: /tmp/kig-screen-jbe8uakc/candidate.c, line 130: Syntax Error
     f32 temp_f24;
 --------^
cfe: Error: /tmp/kig-screen-jbe8uakc/candidate.c, line 131: Syntax Error
     f32 temp_f2;
 --------^
cfe: Error: /tmp/kig-screen-jbe8uakc/candidate.c, line 132: Syntax Error
     f32 temp_f2_2;
 --------^
cfe: Error: /tmp/kig-screen-jbe8uakc/candidate.c, line 133: Syntax Error
     f32 temp_f2_3;
 --------^
cfe: Error: /tmp/kig-screen-jbe8uakc/candidate.c, line 134: Syntax Error
     f32 var_f10;
 --------^
cfe: Error: /tmp/kig-screen-jbe8uakc/candidate.c, line 135: Syntax Error
     f32 var_f16;
 --------^
cfe: Error: /tmp/kig-screen-jbe8uakc/candidate.c, line 136: Syntax Error
     f32 var_f18;
 --------^
cfe: Error: /tmp/kig-screen-jbe8uakc/candidate.c, line 137: Syntax Error
     f32 var_f18_2;
 --------^
cfe: Error: /tmp/kig-screen-jbe8uakc/candidate.c, line 138: Syntax Error
     f32 var_f4;
 --------^
cfe: Error: /tmp/kig-screen-jbe8uakc/candidate.c, line 139: Syntax Error
     f32 var_f4_2;
 --------^
cfe: Error: /tmp/kig-screen-jbe8uakc/candidate.c, line 140: Syntax Error
     f32 var_f8;
 --------^
cfe: Error: /tmp/kig-screen-jbe8uakc/candidate.c, line 141: Syntax Error
     s16 temp_t0;
 --------^
cfe: Error: /tmp/kig-screen-jbe8uakc/candidate.c, line 142: Syntax Error
     s16 temp_t2;
 --------^
cfe: Error: /tmp/kig-screen-jbe8uakc/candidate.c, line 143: Syntax Error
     s16 var_a3;
 --------^
cfe: Error: /tmp/kig-screen-jbe8uakc/candidate.c, line 144: Syntax Error
     s32 temp_a2;
 --------^
cfe: Error: /tmp/kig-screen-jbe8uakc/candidate.c, line 145: Syntax Error
     s32 temp_t5;
 --------^
cfe: Error: /tmp/kig-screen-jbe8uakc/candidate.c, line 146: Syntax Error
     s32 temp_t7;
 --------^
cfe: Error: /tmp/kig-screen-jbe8uakc/candidate.c, line 147: Syntax Error
     s32 temp_t9;
 --------^
cfe: Error: /tmp/kig-screen-jbe8uakc/candidate.c, line 148: Syntax Error
     s32 temp_v0_6;
 --------^
cfe: Error: /tmp/kig-screen-jbe8uakc/candidate.c, line 149: Syntax Error
     s32 temp_v0_7;
 --------^
cfe: Error: /tmp/kig-screen-jbe8uakc/candidate.c, line 150: Syntax Error
     s32 temp_v1_10;
 --------^
cfe: Error: /tmp/kig-screen-jbe8uakc/candidate.c, line 151: Syntax Error
     s32 temp_v1_11;
 --------^
cfe: Error: /tmp/kig-screen-jbe8uakc/candidate.c, line 152: Syntax Error
     s32 temp_v1_6;
 --------^
cfe: Error: /tmp/kig-screen-jbe8uakc/candidate.c, line 153: Syntax Error
     s32 var_a1;
 --------^
cfe: Error: /tmp/kig-screen-jbe8uakc/candidate.c, line 154: Syntax Error
     s32 var_a1_3;
 --------^
cfe: Error: /tmp/kig-screen-jbe8uakc/candidate.c, line 155: Syntax Error
     s32 var_a2_2;
 --------^
cfe: Error: /tmp/kig-screen-jbe8uakc/candidate.c, line 156: Syntax Error
     s32 var_fp;
 --------^
cfe: Fatal: Too many errors... goodbye.
```

### func_801B47A4 (prefix)

```text
cfe: Error: /tmp/kig-screen-3ipai1kd/candidate.c, line 657: redeclaration of 'D_802C8800'; previous declaration at line 410 in file '/tmp/kig-screen-3ipai1kd/candidate.c'
 extern u8 D_802C8800[];
 ----------^
cfe: Error: /tmp/kig-screen-3ipai1kd/candidate.c, line 666: Subscripting a non-array.
     if (D_802C8800[1] == 0 && D_801F35AC >= 51) {
 ------------------^
cfe: Error: /tmp/kig-screen-3ipai1kd/candidate.c, line 668: Subscripting a non-array.
         D_802C8800[1] = 1;
 ------------------^
```

### func_801B849C (declarations)

```text
cfe: Error: /tmp/kig-screen-r7rsg_2w/candidate.c, line 485: redeclaration of 'func_801B6A68'; previous declaration at line 424 in file '/tmp/kig-screen-r7rsg_2w/candidate.c'
 extern s32 func_801B6A68(u32 **, T029Portrait *, s32);
 -----------^
cfe: Error: /tmp/kig-screen-r7rsg_2w/candidate.c, line 485: Incompatible type for the function parameter
 extern s32 func_801B6A68(u32 **, T029Portrait *, s32);
 -------------------------^
```

### func_80019880 (declarations)

```text
cfe: Error: /tmp/kig-screen-w9fkthuu/candidate.c, line 1275: redeclaration of 'D_8004ACCC'; previous declaration at line 288 in file '/tmp/kig-screen-w9fkthuu/candidate.c'
 extern u8 D_8004ACCC;
 ----------^
cfe: Error: /tmp/kig-screen-w9fkthuu/candidate.c, line 1276: redeclaration of 'D_8004ACD0'; previous declaration at line 288 in file '/tmp/kig-screen-w9fkthuu/candidate.c'
 extern u8 D_8004ACD0;
 ----------^
cfe: Error: /tmp/kig-screen-w9fkthuu/candidate.c, line 1278: redeclaration of 'D_8004ACD4'; previous declaration at line 13 in file '/tmp/kig-screen-w9fkthuu/candidate.c'
 extern u8 D_8004ACD4;
 ----------^
cfe: Error: /tmp/kig-screen-w9fkthuu/candidate.c, line 1286: redeclaration of 'func_80019880'; previous declaration at line 310 in file '/tmp/kig-screen-w9fkthuu/candidate.c'
 void func_80019880(u8 **arg0, s32 *arg1, s32 arg2, s32 arg3, f32 arg5, f32 arg6) {
 -----^
cfe: Error: /tmp/kig-screen-w9fkthuu/candidate.c, line 1286: Incompatible type for the function parameter
 void func_80019880(u8 **arg0, s32 *arg1, s32 arg2, s32 arg3, f32 arg5, f32 arg6) {
 ------------------------^
```

### func_801ADEA0 (prefix)

```text
cfe: Error: /tmp/kig-screen-htw5s_q3/candidate.c, line 497: redeclaration of 'D_801D18B8'; previous declaration at line 19 in file '/tmp/kig-screen-htw5s_q3/candidate.c'
 extern T025Effect D_801D18B8[];
 ------------------^
cfe: Error: /tmp/kig-screen-htw5s_q3/candidate.c, line 505: 'flags' undefined; reoccurrences will not be reported.
         if (D_801D18B8[i].flags & arg0) D_801D18B8[i].state = -1;
 -------------------------^
cfe: Error: /tmp/kig-screen-htw5s_q3/candidate.c, line 505: member of structure or union required
         if (D_801D18B8[i].flags & arg0) D_801D18B8[i].state = -1;
 --------------------------^
cfe: Error: /tmp/kig-screen-htw5s_q3/candidate.c, line 505: 'state' undefined; reoccurrences will not be reported.
         if (D_801D18B8[i].flags & arg0) D_801D18B8[i].state = -1;
 -----------------------------------------------------^
cfe: Error: /tmp/kig-screen-htw5s_q3/candidate.c, line 505: member of structure or union required
         if (D_801D18B8[i].flags & arg0) D_801D18B8[i].state = -1;
 ------------------------------------------------------^
```

### func_801B6E4C (declarations)

```text
cfe: Error: /tmp/kig-screen-38_063k8/candidate.c, line 483: redeclaration of 'func_801B6A68'; previous declaration at line 424 in file '/tmp/kig-screen-38_063k8/candidate.c'
 extern s32 func_801B6A68(u32 **, T029Portrait *, s32);
 -----------^
cfe: Error: /tmp/kig-screen-38_063k8/candidate.c, line 483: Incompatible type for the function parameter
 extern s32 func_801B6A68(u32 **, T029Portrait *, s32);
 -------------------------^
cfe: Error: /tmp/kig-screen-38_063k8/candidate.c, line 495: redeclaration of 'D_80127CE8'; previous declaration at line 375 in file '/tmp/kig-screen-38_063k8/candidate.c'
 extern u8 D_80127CE8[];
 ----------^
cfe: Error: /tmp/kig-screen-38_063k8/candidate.c, line 529: redeclaration of 'D_802C8CEA'; previous declaration at line 379 in file '/tmp/kig-screen-38_063k8/candidate.c'
 extern u8 D_802C8CEA;
 ----------^
cfe: Error: /tmp/kig-screen-38_063k8/candidate.c, line 735: Unacceptable operand of a multiplicative operator.
                         var_a2 = *((void * *)(D_801F2EB4 + (D_80127CE8[sp133] * 0x8C)));
 ----------------------------------------------------------------------^
```

### func_8000FA80 (prefix)

```text
cfe: Error: /tmp/kig-screen-zu5982xu/candidate.c, line 397: redeclaration of 'func_80012100'; previous declaration at line 76 in file '/tmp/kig-screen-zu5982xu/candidate.c'
 void func_80012100(u8 arg0, u8 arg1) {
 -----^
cfe: Error: /tmp/kig-screen-zu5982xu/candidate.c, line 397: prototype and non-prototype declaration found for func_80012100, the type of this parameter is not compatible with the type after applying default argument promotion
 void func_80012100(u8 arg0, u8 arg1) {
 ----------------------^
```

### func_8001EC74 (declarations)

```text
cfe: Error: /tmp/kig-screen-v0rsnoe7/candidate.c, line 206: redeclaration of 'func_8001EC74'; previous declaration at line 74 in file '/tmp/kig-screen-v0rsnoe7/candidate.c'
 void func_8001EC74(u8 **arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5, u8 arg6, u8 arg7) {
 -----^
cfe: Error: /tmp/kig-screen-v0rsnoe7/candidate.c, line 206: Incompatible function return type for this function.
 void func_8001EC74(u8 **arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5, u8 arg6, u8 arg7) {
 ------------------^
cfe: Error: /tmp/kig-screen-v0rsnoe7/candidate.c, line 819: 'D_8004AA28' undefined; reoccurrences will not be reported.
                                     if ((temp_t7_4 < (0xF0 << D_8004AA28)) && (sp9C < (0x140 << D_8004AA28)) && (sp9C >= -0x12B) && (temp_t7_4 >= -0x12B)) {
 --------------------------------------------------------------^
```

### func_8001D080 (ERROR)

```text
cfe: Error: /tmp/kig-screen-n9ufhpzc/candidate.c, line 33: Syntax Error
 extern T022Sprite D_8004CED0[];
 ------------------^
cfe: Error: /tmp/kig-screen-n9ufhpzc/candidate.c, line 33: Empty declaration specifiers
 extern T022Sprite D_8004CED0[];
 ------------------^
cfe: Error: /tmp/kig-screen-n9ufhpzc/candidate.c, line 49: Syntax Error
     T022Sprite *temp_a1; s32 temp_t6;
 -----------------------------^
cfe: Error: /tmp/kig-screen-n9ufhpzc/candidate.c, line 50: Syntax Error
     s32 temp_t8;
 --------^
cfe: Error: /tmp/kig-screen-n9ufhpzc/candidate.c, line 51: Syntax Error
     s32 temp_v1_2; u8 temp_t9; u8 temp_t9_2;
 --------^
cfe: Error: /tmp/kig-screen-n9ufhpzc/candidate.c, line 51: Syntax Error
     s32 temp_v1_2; u8 temp_t9; u8 temp_t9_2;
 ----------------------^
cfe: Error: /tmp/kig-screen-n9ufhpzc/candidate.c, line 51: Syntax Error
     s32 temp_v1_2; u8 temp_t9; u8 temp_t9_2;
 ----------------------------------^
```

```text
:35:8: Missing type in declaration
```

### func_80021B6C (ERROR)

```text
cfe: Error: /tmp/kig-screen-_v839o8k/candidate.c, line 224: redeclaration of 'D_8004AC8A'; previous declaration at line 72 in file '/tmp/kig-screen-_v839o8k/candidate.c'
 extern u8 D_8004AC8A; extern u8 D_8004AC88,D_8004AA28,D_8004A9D8,D_8004A998,D_8004AC89;
 ----------^
cfe: Error: /tmp/kig-screen-_v839o8k/candidate.c, line 224: redeclaration of 'D_8004AC89'; previous declaration at line 71 in file '/tmp/kig-screen-_v839o8k/candidate.c'
 extern u8 D_8004AC8A; extern u8 D_8004AC88,D_8004AA28,D_8004A9D8,D_8004A998,D_8004AC89;
 ----------------------------------------------------------------------------^
cfe: Error: /tmp/kig-screen-_v839o8k/candidate.c, line 270: redeclaration of 'D_801D3430'; previous declaration at line 82 in file '/tmp/kig-screen-_v839o8k/candidate.c'
 } T032Actor21B; extern T032Actor21B D_801D3430[];
 ------------------------------------^
cfe: Error: /tmp/kig-screen-_v839o8k/candidate.c, line 280: redeclaration of 'func_8001EC74'; previous declaration at line 74 in file '/tmp/kig-screen-_v839o8k/candidate.c'
 extern void func_8001C5AC(T032Gfx21B **,s32,void *,u8,s32,f32,f32,f32,f32,f32,f32,u32); extern void func_8001D7E4(s32,u8,u8,s32,s32),func_8001EC74(T032Gfx21B **,s32,s32,u32,u32,s32,s32,s32);
 -------------------------------------------------------------------------------------------------------------------------------------^
cfe: Error: /tmp/kig-screen-_v839o8k/candidate.c, line 280: Incompatible function return type for this function.
 extern void func_8001C5AC(T032Gfx21B **,s32,void *,u8,s32,f32,f32,f32,f32,f32,f32,u32); extern void func_8001D7E4(s32,u8,u8,s32,s32),func_8001EC74(T032Gfx21B **,s32,s32,u32,u32,s32,s32,s32);
 --------------------------------------------------------------------------------------------------------------------------------------------------^
cfe: Error: /tmp/kig-screen-_v839o8k/candidate.c, line 393: Subscripting a non-array.
     temp_v0_3 = var_fp_3 ^ 1; if (((&D_801D3430[var_fp_3])->scale - (&D_801D3430[temp_v0_3])->scale) < -0x80) { D_801D7370[order[var_fp_3]] = temp_v0_3;
 -----------------------------------------------^
cfe: Error: /tmp/kig-screen-_v839o8k/candidate.c, line 408: Subscripting a non-array.
             temp_s0 = &D_801D3430[temp_a1];
 ---------------------------------^
```

```text
cfe: Error: /tmp/kig-screen-312vaj9b/candidate.c, line 77: redeclaration of 'T020Position'; previous declaration at line 70 in file '/tmp/kig-screen-312vaj9b/candidate.c'
 T020Position;
 ^
```

