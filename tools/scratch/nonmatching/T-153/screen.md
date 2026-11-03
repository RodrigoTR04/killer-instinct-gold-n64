# T-092 draft screen

IDO 5.3 -O2 -mips2 through asm-processor. Full owning TU first; prefix fallback removes other GLOBAL_ASM stubs and omits declarations after the target. Relocation masks come only from ELF REL entries. Size differences count as differing words. Declaration fallback keeps TU types/prototypes, omits preceding bodies, and gives explicit draft declarations precedence. Prefix/declaration scores require reconciliation before integration.

| Function | Compiled B | Original B | Differing words | Context | Draft |
|---|---:|---:|---:|---|---|
| func_801B5534 | 168 | 168 | 2 | full | tools/scratch/nonmatching/T-029/func_801B5534.c |
| func_801C4E38 | 556 | 556 | 2 | full | tools/scratch/nonmatching/T-021/func_801C4E38.c |
| func_801C8004 | 236 | 236 | 6 | full | tools/scratch/nonmatching/T-021/func_801C8004.c |
| func_801BD270 | 396 | 396 | 7 | full | tools/scratch/nonmatching/T-023/func_801BD270.c |
| func_8001BDE0 | 316 | 316 | 8 | full | tools/scratch/nonmatching/T-022/func_8001BDE0.c |
| func_801B2B8C | 872 | 872 | 8 | full | tools/scratch/nonmatching/T-025/func_801B2B8C.c |
| func_801BE540 | 288 | 288 | 8 | full | tools/scratch/nonmatching/T-023/func_801BE540.c |
| func_801B5DCC | 1884 | 1884 | 11 | full | tools/scratch/nonmatching/T-029/func_801B5DCC.c |
| func_80023EF0 | 312 | 312 | 12 | full | tools/scratch/nonmatching/T-032/func_80023EF0.c |
| func_801B1DE4 | 556 | 556 | 13 | full | tools/scratch/nonmatching/T-025/func_801B1DE4.c |
| func_80014D5C | 1780 | 1780 | 14 | prefix | tools/scratch/nonmatching/T-033/func_80014D5C.c |
| func_801ADA04 | 208 | 208 | 14 | full | tools/scratch/nonmatching/T-019/func_801ADA04.c |
| func_801BAA78 | 884 | 884 | 14 | full | tools/scratch/nonmatching/T-023/func_801BAA78.c |
| func_801BD200 | 112 | 112 | 14 | full | tools/scratch/nonmatching/T-023/func_801BD200.c |
| func_8002A900 | 220 | 220 | 15 | full | tools/scratch/nonmatching/T-024/func_8002A900.c |
| func_8002FB80 | 544 | 544 | 20 | full | tools/scratch/nonmatching/T-024/func_8002FB80.c |
| func_801C0800 | 248 | 248 | 21 | full | tools/scratch/nonmatching/T-023/func_801C0800.c |
| func_800121C8 | 304 | 304 | 22 | full | tools/scratch/nonmatching/T-033/func_800121C8.c |
| func_801B0520 | 328 | 328 | 22 | full | tools/scratch/nonmatching/T-025/func_801B0520.c |
| func_801BBB60 | 292 | 292 | 26 | full | tools/scratch/nonmatching/T-023/func_801BBB60.c |
| func_801B1210 | 284 | 284 | 27 | full | tools/scratch/nonmatching/T-025/func_801B1210.c |
| func_800268C0 | 236 | 236 | 28 | full | tools/scratch/nonmatching/T-032/func_800268C0.c |
| func_801B446C | 292 | 292 | 28 | full | tools/scratch/nonmatching/T-029/func_801B446C.c |
| func_801C3758 | 564 | 564 | 30 | full | tools/scratch/nonmatching/T-030/func_801C3758.c |
| func_801BE660 | 300 | 300 | 41 | full | tools/scratch/nonmatching/T-023/func_801BE660.c |
| func_801C2F5C | 544 | 544 | 44 | full | tools/scratch/nonmatching/T-030/func_801C2F5C.c |
| func_80024028 | 284 | 284 | 45 | full | tools/scratch/nonmatching/T-032/func_80024028.c |
| func_8001CD50 | 460 | 460 | 46 | prefix | tools/scratch/nonmatching/T-022/func_8001CD50.c |
| func_8002B22C | 380 | 380 | 66 | full | tools/scratch/nonmatching/T-024/func_8002B22C.c |
| func_800300DC | 316 | 316 | 69 | full | tools/scratch/nonmatching/T-026/func_800300DC.c |
| func_801BBC84 | 516 | 516 | 71 | prefix | tools/scratch/nonmatching/T-023/func_801BBC84.c |
| func_8002DDD4 | 452 | 452 | 78 | full | tools/scratch/nonmatching/T-024/func_8002DDD4.c |
| func_80026738 | 392 | 392 | 81 | declarations | tools/scratch/nonmatching/T-032/func_80026738.c |
| func_801C49A8 | 548 | 548 | 83 | declarations | tools/scratch/nonmatching/T-030/func_801C49A8.c |
| func_801C3E40 | 504 | 504 | 88 | declarations | tools/scratch/nonmatching/T-030/func_801C3E40.c |
| func_8001D080 | 764 | 764 | 90 | full | tools/scratch/nonmatching/T-022/func_8001D080.c |
| func_801AFFAC | 576 | 576 | 99 | full | tools/scratch/nonmatching/T-025/func_801AFFAC.c |
| func_8001BB64 | 636 | 636 | 101 | full | tools/scratch/nonmatching/T-022/func_8001BB64.c |
| func_801B0668 | 984 | 984 | 114 | full | tools/scratch/nonmatching/T-025/func_801B0668.c |
| func_801C3AA0 | 928 | 928 | 119 | full | tools/scratch/nonmatching/T-030/func_801C3AA0.c |
| func_801C4240 | 1344 | 1344 | 126 | full | tools/scratch/nonmatching/T-030/func_801C4240.c |
| func_801C1434 | 720 | 720 | 132 | full | tools/scratch/nonmatching/T-023/func_801C1434.c |
| func_800297A4 | 780 | 780 | 180 | declarations | tools/scratch/nonmatching/T-024/func_800297A4.c |
| func_801BD640 | 1068 | 1068 | 191 | full | tools/scratch/nonmatching/T-023/func_801BD640.c |
| func_801B3DB0 | 1360 | 1360 | 255 | prefix | tools/scratch/nonmatching/T-025/func_801B3DB0.c |
| func_801BF190 | 1256 | 1256 | 284 | declarations | tools/scratch/nonmatching/T-023/func_801BF190.c |
| func_801BCB70 | 1676 | 1676 | 391 | full | tools/scratch/nonmatching/T-023/func_801BCB70.c |
| func_801C5E74 | 2392 | 2392 | 527 | full | tools/scratch/nonmatching/T-030/func_801C5E74.c |
| func_80032738 | 40 | 20 | 10 | full | tools/scratch/nonmatching/T-026/func_80032738.c |
| func_80032750 | 44 | 60 | 15 | full | tools/scratch/nonmatching/T-026/func_80032750.c |
| func_8003278C | 104 | 92 | 26 | full | tools/scratch/nonmatching/T-026/func_8003278C.c |
| func_80031050 | 120 | 112 | 30 | declarations | tools/scratch/nonmatching/T-026/func_80031050.c |
| func_801B5650 | 1920 | 1916 | 30 | full | tools/scratch/nonmatching/T-029/func_801B5650.c |
| func_80032600 | 148 | 112 | 37 | full | tools/scratch/nonmatching/T-026/func_80032600.c |
| func_80032670 | 180 | 116 | 45 | full | tools/scratch/nonmatching/T-026/func_80032670.c |
| func_80032504 | 68 | 240 | 60 | full | tools/scratch/nonmatching/T-026/func_80032504.c |
| func_80012390 | 468 | 476 | 67 | full | tools/scratch/nonmatching/T-033/func_80012390.c |
| func_800326F0 | 276 | 72 | 69 | full | tools/scratch/nonmatching/T-026/func_800326F0.c |
| func_801B465C | 332 | 328 | 71 | full | tools/scratch/nonmatching/T-029/func_801B465C.c |
| func_801BE790 | 372 | 384 | 77 | prefix | tools/scratch/nonmatching/T-023/func_801BE790.c |
| func_8002FDA0 | 560 | 572 | 81 | full | tools/scratch/nonmatching/T-024/func_8002FDA0.c |
| func_800245B4 | 348 | 352 | 83 | declarations | tools/scratch/nonmatching/T-032/func_800245B4.c |
| func_8001272C | 536 | 540 | 86 | full | tools/scratch/nonmatching/T-033/func_8001272C.c |
| func_801CC3BC | 364 | 360 | 88 | full | tools/scratch/nonmatching/T-021/func_801CC3BC.c |
| func_801CD1F0 | 456 | 460 | 91 | full | tools/scratch/nonmatching/T-034/func_801CD1F0.c |
| func_801BADEC | 560 | 568 | 100 | full | tools/scratch/nonmatching/T-023/func_801BADEC.c |
| func_801C17D0 | 436 | 448 | 103 | full | tools/scratch/nonmatching/T-023/func_801C17D0.c |
| func_80032360 | 116 | 420 | 105 | full | tools/scratch/nonmatching/T-026/func_80032360.c |
| func_800191F0 | 472 | 492 | 109 | full | tools/scratch/nonmatching/T-022/func_800191F0.c |
| func_8001D47C | 744 | 748 | 134 | full | tools/scratch/nonmatching/T-022/func_8001D47C.c |
| func_801BD3FC | 484 | 580 | 134 | full | tools/scratch/nonmatching/T-023/func_801BD3FC.c |
| func_8001DE5C | 624 | 600 | 155 | full | tools/scratch/nonmatching/T-022/func_8001DE5C.c |
| func_800241BC | 840 | 820 | 158 | declarations | tools/scratch/nonmatching/T-032/func_800241BC.c |
| func_801C1990 | 604 | 676 | 159 | full | tools/scratch/nonmatching/T-023/func_801C1990.c |
| func_8001346C | 696 | 704 | 168 | declarations | tools/scratch/nonmatching/T-033/func_8001346C.c |
| func_801ACB1C | 756 | 744 | 176 | prefix | tools/scratch/nonmatching/T-034/func_801ACB1C.c |
| func_8002E150 | 836 | 844 | 179 | full | tools/scratch/nonmatching/T-024/func_8002E150.c |
| func_801C23C0 | 1812 | 1820 | 189 | declarations | tools/scratch/nonmatching/T-030/func_801C23C0.c |
| func_801B01EC | 828 | 820 | 191 | full | tools/scratch/nonmatching/T-025/func_801B01EC.c |
| func_801B0CDC | 1336 | 1332 | 202 | declarations | tools/scratch/nonmatching/T-025/func_801B0CDC.c |
| func_801B1A7C | 596 | 872 | 206 | prefix | tools/scratch/nonmatching/T-025/func_801B1A7C.c |
| func_801BB7B4 | 960 | 940 | 220 | declarations | tools/scratch/nonmatching/T-023/func_801BB7B4.c |
| func_801C317C | 940 | 936 | 225 | declarations | tools/scratch/nonmatching/T-030/func_801C317C.c |
| func_800216D4 | 1040 | 1032 | 229 | declarations | tools/scratch/nonmatching/T-032/func_800216D4.c |
| func_801AF68C | 940 | 956 | 231 | prefix | tools/scratch/nonmatching/T-025/func_801AF68C.c |
| func_80027E1C | 940 | 936 | 234 | full | tools/scratch/nonmatching/T-032/func_80027E1C.c |
| func_801B132C | 1144 | 1168 | 237 | full | tools/scratch/nonmatching/T-025/func_801B132C.c |
| func_80028230 | 932 | 976 | 242 | full | tools/scratch/nonmatching/T-024/func_80028230.c |
| func_801C1C34 | 1224 | 1244 | 242 | prefix | tools/scratch/nonmatching/T-023/func_801C1C34.c |
| func_80029BE0 | 1048 | 1060 | 263 | declarations | tools/scratch/nonmatching/T-024/func_80029BE0.c |
| func_801C7310 | 1264 | 1276 | 281 | full | tools/scratch/nonmatching/T-030/func_801C7310.c |
| func_800327E8 | 1156 | 1092 | 284 | full | tools/scratch/nonmatching/T-026/func_800327E8.c |
| func_801BDA6C | 1336 | 1320 | 289 | full | tools/scratch/nonmatching/T-023/func_801BDA6C.c |
| func_801AFAA4 | 1256 | 1288 | 301 | full | tools/scratch/nonmatching/T-025/func_801AFAA4.c |
| func_80015594 | 1472 | 1488 | 305 | declarations | tools/scratch/nonmatching/T-033/func_80015594.c |
| func_800257FC | 1232 | 1372 | 337 | declarations | tools/scratch/nonmatching/T-032/func_800257FC.c |
| func_801BDF94 | 1436 | 1452 | 352 | full | tools/scratch/nonmatching/T-023/func_801BDF94.c |
| func_800238C4 | 1600 | 1580 | 383 | full | tools/scratch/nonmatching/T-032/func_800238C4.c |
| func_80012B7C | 1560 | 1576 | 391 | declarations | tools/scratch/nonmatching/T-033/func_80012B7C.c |
| func_80024CE0 | 1492 | 1652 | 394 | declarations | tools/scratch/nonmatching/T-032/func_80024CE0.c |
| func_801B9A04 | 1608 | 1668 | 406 | full | tools/scratch/nonmatching/T-029/func_801B9A04.c |
| func_8001D7E4 | 1720 | 1656 | 423 | declarations | tools/scratch/nonmatching/T-022/func_8001D7E4.c |
| func_80025FC4 | 1896 | 1908 | 454 | declarations | tools/scratch/nonmatching/T-032/func_80025FC4.c |
| func_80020E98 | 2076 | 2108 | 497 | declarations | tools/scratch/nonmatching/T-032/func_80020E98.c |
| func_800306B8 | 2096 | 2104 | 510 | full | tools/scratch/nonmatching/T-026/func_800306B8.c |
| func_8001178C | 2272 | 2104 | 556 | prefix | tools/scratch/nonmatching/T-033/func_8001178C.c |
| func_801C08F8 | 2216 | 2296 | 561 | prefix | tools/scratch/nonmatching/T-023/func_801C08F8.c |
| func_8001E33C | 2404 | 2360 | 569 | declarations | tools/scratch/nonmatching/T-022/func_8001E33C.c |
| func_800142E0 | 2100 | 2400 | 593 | declarations | tools/scratch/nonmatching/T-033/func_800142E0.c |
| func_801BFCBC | 2084 | 2388 | 596 | prefix | tools/scratch/nonmatching/T-023/func_801BFCBC.c |
| func_801BC1B0 | 2320 | 2496 | 624 | declarations | tools/scratch/nonmatching/T-023/func_801BC1B0.c |
| func_801C9B14 | 3140 | 3184 | 629 | declarations | tools/scratch/nonmatching/T-034/func_801C9B14.c |
| func_8002E724 | 2728 | 2832 | 658 | full | tools/scratch/nonmatching/T-024/func_8002E724.c |
| func_801ABB20 | 3576 | 3644 | 658 | prefix | tools/scratch/nonmatching/T-034/func_801ABB20.c |
| func_800310C0 | 2744 | 2424 | 683 | declarations | tools/scratch/nonmatching/T-026/func_800310C0.c |
| func_801C5298 | 3000 | 3036 | 741 | declarations | tools/scratch/nonmatching/T-030/func_801C5298.c |
| func_801B47A4 | 3260 | 3472 | 862 | prefix | tools/scratch/nonmatching/T-029/func_801B47A4.c |
| func_801CAA00 | 3884 | 3992 | 992 | declarations | tools/scratch/nonmatching/T-034/func_801CAA00.c |
| func_80026B38 | 4792 | 4708 | 1182 | full | tools/scratch/nonmatching/T-032/func_80026B38.c |
| func_801B849C | 5312 | 5296 | 1267 | declarations | tools/scratch/nonmatching/T-029/func_801B849C.c |
| func_80019880 | 5216 | 4456 | 1297 | declarations | tools/scratch/nonmatching/T-022/func_80019880.c |
| func_801ADEA0 | 5524 | 5508 | 1349 | prefix | tools/scratch/nonmatching/T-025/func_801ADEA0.c |
| func_801B6E4C | 5652 | 5712 | 1417 | declarations | tools/scratch/nonmatching/T-029/func_801B6E4C.c |
| func_8002BBD0 | 7692 | 7668 | 1843 | full | tools/scratch/nonmatching/T-024/func_8002BBD0.c |
| func_8000FA80 | 8148 | 7436 | 2014 | prefix | tools/scratch/nonmatching/T-033/func_8000FA80.c |
| func_8001EC74 | 8476 | 8740 | 2175 | declarations | tools/scratch/nonmatching/T-022/func_8001EC74.c |
| func_80015450 | — | — | — | ERROR | tools/scratch/nonmatching/T-033/func_80015450.c |
| func_80016078 | — | — | — | ERROR | tools/scratch/nonmatching/T-033/func_80016078.c |
| func_800170C4 | — | — | — | ERROR | tools/scratch/nonmatching/T-033/func_800170C4.c |
| func_80017378 | — | — | — | ERROR | tools/scratch/nonmatching/T-033/func_80017378.c |
| func_80017D6C | — | — | — | ERROR | tools/scratch/nonmatching/T-033/func_80017D6C.c |
| func_800193DC | — | — | — | ERROR | tools/scratch/nonmatching/T-022/func_800193DC.c |
| func_80021B6C | — | — | — | ERROR | tools/scratch/nonmatching/T-032/func_80021B6C.c |
| func_80024714 | — | — | — | ERROR | tools/scratch/nonmatching/T-032/func_80024714.c |
| func_800253D0 | — | — | — | ERROR | tools/scratch/nonmatching/T-032/func_800253D0.c |
| func_80028A00 | — | — | — | ERROR | tools/scratch/nonmatching/T-024/func_80028A00.c |
| func_80030220 | — | — | — | ERROR | tools/scratch/nonmatching/T-026/func_80030220.c |
| func_80030440 | — | — | — | ERROR | tools/scratch/nonmatching/T-026/func_80030440.c |
| func_80031A38 | — | — | — | ERROR | tools/scratch/nonmatching/T-026/func_80031A38.c |
| func_80031DD0 | — | — | — | ERROR | tools/scratch/nonmatching/T-026/func_80031DD0.c |
| func_801B695C | — | — | — | ERROR | tools/scratch/nonmatching/T-029/func_801B695C.c |
| func_801BEEA4 | — | — | — | ERROR | tools/scratch/nonmatching/T-023/func_801BEEA4.c |
| func_801BF720 | — | — | — | ERROR | tools/scratch/nonmatching/T-023/func_801BF720.c |
| func_801BF914 | — | — | — | ERROR | tools/scratch/nonmatching/T-023/func_801BF914.c |
| func_801C224C | — | — | — | ERROR | tools/scratch/nonmatching/T-030/func_801C224C.c |
| func_801C47E0 | — | — | — | ERROR | tools/scratch/nonmatching/T-030/func_801C47E0.c |
| func_801C48E4 | — | — | — | ERROR | tools/scratch/nonmatching/T-021/func_801C48E4.c |
| func_801C80F0 | — | — | — | ERROR | tools/scratch/nonmatching/T-034/func_801C80F0.c |
| func_801C90D4 | — | — | — | ERROR | tools/scratch/nonmatching/T-034/func_801C90D4.c |

## Compilation diagnostics

### func_80014D5C (prefix)

```text
cfe: Error: /tmp/kig-screen-gea9a0v3/candidate.c, line 972: redeclaration of 'D_8004A264'; previous declaration at line 583 in file '/tmp/kig-screen-gea9a0v3/candidate.c'
 extern s32 D_8004A264, D_8004ACF8, D_80066C40;
 -----------^
```

### func_8001CD50 (prefix)

```text
cfe: Error: /tmp/kig-screen-4a7x80h1/candidate.c, line 374: redeclaration of 'D_8004F396'; previous declaration at line 45 in file '/tmp/kig-screen-4a7x80h1/candidate.c'
 extern u8 D_1EB6D0[],D_1F3200[],D_2C2280[],D_2CF0A0[],D_469660[],D_470390[],D_53CC40[],D_543D10[],D_8004EA9C[],D_8004F396[];
 ---------------------------------------------------------------------------------------------------------------^
cfe: Error: /tmp/kig-screen-4a7x80h1/candidate.c, line 437: Subscripting a non-array.
     D_8004F396[arg0] = 1;
 --------------^
```

### func_801BBC84 (prefix)

```text
cfe: Error: /tmp/kig-screen-m_4v099w/candidate.c, line 1411: redeclaration of 'D_802C9D20'; previous declaration at line 1366 in file '/tmp/kig-screen-m_4v099w/candidate.c'
 extern s16 D_802C9D20[];
 -----------^
```

### func_80026738 (declarations)

```text
cfe: Error: /tmp/kig-screen-nevh_th2/candidate.c, line 129: redeclaration of 'D_8004CED0'; previous declaration at line 4 in file '/tmp/kig-screen-nevh_th2/candidate.c'
 extern T032Sprite267 D_8004CED0[];
 ---------------------^
cfe: Error: /tmp/kig-screen-nevh_th2/candidate.c, line 133: redeclaration of 'func_8001EC74'; previous declaration at line 33 in file '/tmp/kig-screen-nevh_th2/candidate.c'
 extern void func_8001EC74(T032Gfx267 **,s32,s32,s32,s32,s32,s32,s32);
 ------------^
cfe: Error: /tmp/kig-screen-nevh_th2/candidate.c, line 133: Incompatible type for the function parameter
 extern void func_8001EC74(T032Gfx267 **,s32,s32,s32,s32,s32,s32,s32);
 --------------------------^
cfe: Error: /tmp/kig-screen-nevh_th2/candidate.c, line 134: redeclaration of 'func_80026738'; previous declaration at line 34 in file '/tmp/kig-screen-nevh_th2/candidate.c'
 void func_80026738(T032Gfx267 **dl) {
 -----^
cfe: Error: /tmp/kig-screen-nevh_th2/candidate.c, line 134: Incompatible type for the function parameter
 void func_80026738(T032Gfx267 **dl) {
 --------------------------------^
```

### func_801C49A8 (declarations)

```text
cfe: Error: /tmp/kig-screen-4w7nidk5/candidate.c, line 70: redeclaration of 'D_8004CED0'; previous declaration at line 37 in file '/tmp/kig-screen-4w7nidk5/candidate.c'
 extern T030State49 D_8004CED0;
 -------------------^
cfe: Error: /tmp/kig-screen-4w7nidk5/candidate.c, line 73: redeclaration of 'D_8007D900'; previous declaration at line 40 in file '/tmp/kig-screen-4w7nidk5/candidate.c'
 extern u8 D_8007D900[], D_800B0C60[], D_802918F0[];
 ----------^
cfe: Error: /tmp/kig-screen-4w7nidk5/candidate.c, line 73: redeclaration of 'D_800B0C60'; previous declaration at line 41 in file '/tmp/kig-screen-4w7nidk5/candidate.c'
 extern u8 D_8007D900[], D_800B0C60[], D_802918F0[];
 ------------------------^
cfe: Error: /tmp/kig-screen-4w7nidk5/candidate.c, line 86: Selector requires struct/union as left hand side
     buffer = &D_8004CED0.buffers[arg1];
 ------------------------^
```

### func_801C3E40 (declarations)

```text
cfe: Error: /tmp/kig-screen-_ruf0ecv/candidate.c, line 51: redeclaration of 'D_802D3940'; previous declaration at line 14 in file '/tmp/kig-screen-_ruf0ecv/candidate.c'
 extern T030Triangle3E40 *D_802D3940;
 -------------------------^
cfe: Error: /tmp/kig-screen-_ruf0ecv/candidate.c, line 71: 'v' undefined; reoccurrences will not be reported.
                 D_802D3940[slot].v[0].a -= 32;
 --------------------------------^
cfe: Error: /tmp/kig-screen-_ruf0ecv/candidate.c, line 71: member of structure or union required
                 D_802D3940[slot].v[0].a -= 32;
 ---------------------------------^
cfe: Error: /tmp/kig-screen-_ruf0ecv/candidate.c, line 72: member of structure or union required
                 if (D_802D3940[slot].v[0].a < 32) {
 -------------------------------------^
cfe: Error: /tmp/kig-screen-_ruf0ecv/candidate.c, line 73: member of structure or union required
                     D_802D3940[slot].v[0].a = 32;
 -------------------------------------^
cfe: Error: /tmp/kig-screen-_ruf0ecv/candidate.c, line 77: member of structure or union required
                     dx = D_802D3940[slot].v[1].r;
 ------------------------------------------^
cfe: Error: /tmp/kig-screen-_ruf0ecv/candidate.c, line 78: member of structure or union required
                     D_802D3940[slot].v[0].x += dx;
 -------------------------------------^
cfe: Error: /tmp/kig-screen-_ruf0ecv/candidate.c, line 79: member of structure or union required
                     D_802D3940[slot].v[1].x += dx;
 -------------------------------------^
cfe: Error: /tmp/kig-screen-_ruf0ecv/candidate.c, line 80: member of structure or union required
                     D_802D3940[slot].v[2].x += dx;
 -------------------------------------^
cfe: Error: /tmp/kig-screen-_ruf0ecv/candidate.c, line 81: member of structure or union required
                     dy = D_802D3940[slot].v[1].g;
 ------------------------------------------^
cfe: Error: /tmp/kig-screen-_ruf0ecv/candidate.c, line 82: member of structure or union required
                     D_802D3940[slot].v[0].y += dy;
 -------------------------------------^
cfe: Error: /tmp/kig-screen-_ruf0ecv/candidate.c, line 83: member of structure or union required
                     D_802D3940[slot].v[1].y += dy;
 -------------------------------------^
cfe: Error: /tmp/kig-screen-_ruf0ecv/candidate.c, line 84: member of structure or union required
                     D_802D3940[slot].v[2].y += dy;
 -------------------------------------^
```

### func_800297A4 (declarations)

```text
cfe: Error: /tmp/kig-screen-048epinv/candidate.c, line 159: redeclaration of 'D_80061D60'; previous declaration at line 151 in file '/tmp/kig-screen-048epinv/candidate.c'
 extern T024Burst D_80061D60[];
 -----------------^
```

### func_801B3DB0 (prefix)

```text
cfe: Error: /tmp/kig-screen-0s0wlkpx/candidate.c, line 953: redeclaration of 'D_8012834B'; previous declaration at line 809 in file '/tmp/kig-screen-0s0wlkpx/candidate.c'
 extern u8 D_8012834B;
 ----------^
```

### func_801BF190 (declarations)

```text
cfe: Error: /tmp/kig-screen-4s84ufnv/candidate.c, line 188: redeclaration of 'D_80127D80'; previous declaration at line 60 in file '/tmp/kig-screen-4s84ufnv/candidate.c'
 extern T023Table190 D_80127D80[];
 --------------------^
```

### func_80031050 (declarations)

```text
cfe: Error: /tmp/kig-screen-ctrdqhfv/candidate.c, line 8: 'D_8004CED0' undefined; reoccurrences will not be reported.
     u8 *entry = (u8 *)D_8004CED0;
 ----------------------^
```

### func_801BE790 (prefix)

```text
cfe: Error: /tmp/kig-screen-wercq5i1/candidate.c, line 21: redeclaration of 'func_801BE910'; previous declaration at line 6 in file '/tmp/kig-screen-wercq5i1/candidate.c'
 void func_801BE910(T023Entry910 *out, s32 count, s32 score, s32 step) {
 -----^
cfe: Error: /tmp/kig-screen-wercq5i1/candidate.c, line 21: Incompatible type for the function parameter
 void func_801BE910(T023Entry910 *out, s32 count, s32 score, s32 step) {
 ---------------------------------^
cfe: Error: /tmp/kig-screen-wercq5i1/candidate.c, line 73: redeclaration of 'D_80127D80'; previous declaration at line 5 in file '/tmp/kig-screen-wercq5i1/candidate.c'
 extern T100ScoreTable D_80127D80[];
 ----------------------^
cfe: Error: /tmp/kig-screen-wercq5i1/candidate.c, line 82: Selector requires struct/union as left hand side
         if (packed % 11 != 0) D_80127D80[i].entries[(packed % 11) - 1].name = text;
 ----------------------------------------------------------------------^
cfe: Error: /tmp/kig-screen-wercq5i1/candidate.c, line 87: Selector requires struct/union as left hand side
         if (packed % 6 != 0) D_80127D80[i].entries[(packed % 6) - 1].name = text;
 --------------------------------------------------------------------^
cfe: Error: /tmp/kig-screen-wercq5i1/candidate.c, line 132: redeclaration of 'D_80127E50'; previous declaration at line 9 in file '/tmp/kig-screen-wercq5i1/candidate.c'
 extern T023Entry910 D_80127E50;
 --------------------^
cfe: Error: /tmp/kig-screen-wercq5i1/candidate.c, line 133: redeclaration of 'D_80127EA0'; previous declaration at line 9 in file '/tmp/kig-screen-wercq5i1/candidate.c'
 extern s32 D_80127EA0;
 -----------^
cfe: Error: /tmp/kig-screen-wercq5i1/candidate.c, line 134: redeclaration of 'D_80127EF0'; previous declaration at line 9 in file '/tmp/kig-screen-wercq5i1/candidate.c'
 extern s32 D_80127EF0;
 -----------^
cfe: Error: /tmp/kig-screen-wercq5i1/candidate.c, line 135: redeclaration of 'D_80127F40'; previous declaration at line 9 in file '/tmp/kig-screen-wercq5i1/candidate.c'
 extern s32 D_80127F40;
 -----------^
cfe: Error: /tmp/kig-screen-wercq5i1/candidate.c, line 246: redeclaration of 'D_80127F90'; previous declaration at line 9 in file '/tmp/kig-screen-wercq5i1/candidate.c'
 extern u8 D_80127F90;
 ----------^
cfe: Error: /tmp/kig-screen-wercq5i1/candidate.c, line 247: redeclaration of 'D_80128148'; previous declaration at line 9 in file '/tmp/kig-screen-wercq5i1/candidate.c'
 extern u8 D_80128148;
 ----------^
cfe: Error: /tmp/kig-screen-wercq5i1/candidate.c, line 248: redeclaration of 'D_80128300'; previous declaration at line 9 in file '/tmp/kig-screen-wercq5i1/candidate.c'
 extern u8 D_80128300;
 ----------^
cfe: Error: /tmp/kig-screen-wercq5i1/candidate.c, line 259: Unacceptable operand of == or !=
   first = &D_80127F90; do { next = func_801BF788(cursor, first, 5); first += 0x28; cursor = next; } while (((u32) first) < ((u32) (&D_80128148))); second = &D_80128148; do { next_2 = func_801BF788(cursor, second, 5); second += 0x28;  cursor = next_2; } while (second != (&D_80128300));
 ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------^
cfe: Error: /tmp/kig-screen-wercq5i1/candidate.c, line 305: redeclaration of 'D_80127F90'; previous declaration at line 9 in file '/tmp/kig-screen-wercq5i1/candidate.c'
 extern u8 D_80127F90;
 ----------^
cfe: Error: /tmp/kig-screen-wercq5i1/candidate.c, line 306: redeclaration of 'D_80128148'; previous declaration at line 9 in file '/tmp/kig-screen-wercq5i1/candidate.c'
 extern u8 D_80128148;
 ----------^
cfe: Error: /tmp/kig-screen-wercq5i1/candidate.c, line 307: redeclaration of 'D_80128300'; previous declaration at line 9 in file '/tmp/kig-screen-wercq5i1/candidate.c'
 extern u8 D_80128300;
 ----------^
cfe: Error: /tmp/kig-screen-wercq5i1/candidate.c, line 326: Unacceptable operand of == or !=
   while (second != (&D_80128300));
 ----------------^
```

### func_800245B4 (declarations)

```text
cfe: Error: /tmp/kig-screen-bo2klne4/candidate.c, line 293: redeclaration of 'D_8004D278'; previous declaration at line 68 in file '/tmp/kig-screen-bo2klne4/candidate.c'
 extern T032Cache245 D_8004D278[];
 --------------------^
cfe: Error: /tmp/kig-screen-bo2klne4/candidate.c, line 297: redeclaration of 'func_800245B4'; previous declaration at line 265 in file '/tmp/kig-screen-bo2klne4/candidate.c'
 void func_800245B4(s32 player, u32 start, s32 size) {
 -----^
cfe: Error: /tmp/kig-screen-bo2klne4/candidate.c, line 297: Incompatible type for the function parameter
 void func_800245B4(s32 player, u32 start, s32 size) {
 -----------------------------------^
cfe: Error: /tmp/kig-screen-bo2klne4/candidate.c, line 299: Subscripting a non-array.
     T032Cache245 *bank = &D_8004D278[player];
 ------------------------------------^
```

### func_800241BC (declarations)

```text
cfe: Error: /tmp/kig-screen-lfg4don2/candidate.c, line 278: redeclaration of 'D_8004D278'; previous declaration at line 68 in file '/tmp/kig-screen-lfg4don2/candidate.c'
 T032Resource1BC; extern u8 D_119F0[],D_13200[],D_1D640[],D_24D60[],D_2ECB0[],D_471440[],D_472FB0[],D_48FD0[],D_543D10[],D_54D720[],D_8004D278[],D_8004EA9C[],D_8023E408[],D_8B70[]; extern u8 D_8004F395;
 -----------------------------------------------------------------------------------------------------------------------------------^
cfe: Error: /tmp/kig-screen-lfg4don2/candidate.c, line 296: Unacceptable operand of '+'.
         temp_v0_2 = (T032Resource1BC *)(D_8004D278 + arg0 * 8);
 ---------------------------------------------------^
cfe: Error: /tmp/kig-screen-lfg4don2/candidate.c, line 303: Unacceptable operand of '+'.
         temp_v0_3 = (T032Resource1BC *)(D_8004D278 + arg0 * 8);
 ---------------------------------------------------^
cfe: Error: /tmp/kig-screen-lfg4don2/candidate.c, line 308: Unacceptable operand of '+'.
         temp_v0_4 = (T032Resource1BC *)(D_8004D278 + arg0 * 8);
 ---------------------------------------------------^
cfe: Error: /tmp/kig-screen-lfg4don2/candidate.c, line 318: Unacceptable operand of '+'.
         temp_v0_5 = (T032Resource1BC *)(D_8004D278 + arg0 * 8);
 ---------------------------------------------------^
cfe: Error: /tmp/kig-screen-lfg4don2/candidate.c, line 328: Unacceptable operand of '+'.
         temp_v0_6 = (T032Resource1BC *)(D_8004D278 + arg0 * 8);
 ---------------------------------------------------^
```

### func_8001346C (declarations)

```text
cfe: Error: /tmp/kig-screen-ujcxr3hm/candidate.c, line 140: redeclaration of 'func_8001BB64'; previous declaration at line 84 in file '/tmp/kig-screen-ujcxr3hm/candidate.c'
 extern void func_8001BB64(T033DrawCommand **);
 ------------^
cfe: Error: /tmp/kig-screen-ujcxr3hm/candidate.c, line 140: Incompatible type for the function parameter
 extern void func_8001BB64(T033DrawCommand **);
 --------------------------^
cfe: Error: /tmp/kig-screen-ujcxr3hm/candidate.c, line 150: redeclaration of 'func_8001346C'; previous declaration at line 83 in file '/tmp/kig-screen-ujcxr3hm/candidate.c'
 void func_8001346C(T033DrawCommand **arg0, s32 arg1, f32 arg2) {
 -----^
cfe: Error: /tmp/kig-screen-ujcxr3hm/candidate.c, line 150: Incompatible type for the function parameter
 void func_8001346C(T033DrawCommand **arg0, s32 arg1, f32 arg2) {
 -------------------------------------^
```

### func_801ACB1C (prefix)

```text
cfe: Error: /tmp/kig-screen-iq5no668/candidate.c, line 360: redeclaration of 'func_801AD3BC'; previous declaration at line 62 in file '/tmp/kig-screen-iq5no668/candidate.c'
 void func_801AD3BC(DisplayCommand **arg0, RenderState *arg1) {
 -----^
cfe: Error: /tmp/kig-screen-iq5no668/candidate.c, line 360: Incompatible type for the function parameter
 void func_801AD3BC(DisplayCommand **arg0, RenderState *arg1) {
 ------------------------------------^
cfe: Error: /tmp/kig-screen-iq5no668/candidate.c, line 485: redeclaration of 'func_801AD7D8'; previous declaration at line 63 in file '/tmp/kig-screen-iq5no668/candidate.c'
 void func_801AD7D8(DisplayCommand *arg0, DisplayCommand **arg1, s32 arg2, s32 arg3, s32 *arg4) {
 -----^
cfe: Error: /tmp/kig-screen-iq5no668/candidate.c, line 485: Incompatible type for the function parameter
 void func_801AD7D8(DisplayCommand *arg0, DisplayCommand **arg1, s32 arg2, s32 arg3, s32 *arg4) {
 -----------------------------------^
cfe: Error: /tmp/kig-screen-iq5no668/candidate.c, line 559: redeclaration of 'D_802C9F70'; previous declaration at line 80 in file '/tmp/kig-screen-iq5no668/candidate.c'
 extern RenderState D_802C9F70;
 -------------------^
```

### func_801C23C0 (declarations)

```text
cfe: Error: /tmp/kig-screen-fv6ukgmq/candidate.c, line 233: redeclaration of 'D_802D3898'; previous declaration at line 176 in file '/tmp/kig-screen-fv6ukgmq/candidate.c'
 extern f32 D_802D3880[4],D_802D3898[12];
 -------------------------^
```

### func_801B0CDC (declarations)

```text
cfe: Error: /tmp/kig-screen-ip8pq6b3/candidate.c, line 92: redeclaration of 'D_801CD454'; previous declaration at line 35 in file '/tmp/kig-screen-ip8pq6b3/candidate.c'
 extern u8 D_801CD454;
 ----------^
```

### func_801B1A7C (prefix)

```text
cfe: Error: /tmp/kig-screen-pe0sfqi1/candidate.c, line 47: redeclaration of 'func_801B1A7C'; previous declaration at line 23 in file '/tmp/kig-screen-pe0sfqi1/candidate.c'
 extern f32 func_801B1A7C(void *, void *, f32, s32);
 -----------^
cfe: Error: /tmp/kig-screen-pe0sfqi1/candidate.c, line 47: Incompatible type for the function parameter
 extern f32 func_801B1A7C(void *, void *, f32, s32);
 -------------------------^
cfe: Error: /tmp/kig-screen-pe0sfqi1/candidate.c, line 91: redeclaration of 'func_801B1A7C'; previous declaration at line 23 in file '/tmp/kig-screen-pe0sfqi1/candidate.c'
 extern f32 func_801B1A7C(void *, void *, f32, s32);
 -----------^
cfe: Error: /tmp/kig-screen-pe0sfqi1/candidate.c, line 91: Incompatible type for the function parameter
 extern f32 func_801B1A7C(void *, void *, f32, s32);
 -------------------------^
cfe: Error: /tmp/kig-screen-pe0sfqi1/candidate.c, line 135: redeclaration of 'func_801B1A7C'; previous declaration at line 23 in file '/tmp/kig-screen-pe0sfqi1/candidate.c'
 extern f32 func_801B1A7C(void *, void *, f32, s32);
 -----------^
cfe: Error: /tmp/kig-screen-pe0sfqi1/candidate.c, line 135: Incompatible type for the function parameter
 extern f32 func_801B1A7C(void *, void *, f32, s32);
 -------------------------^
cfe: Error: /tmp/kig-screen-pe0sfqi1/candidate.c, line 179: redeclaration of 'func_801B1A7C'; previous declaration at line 23 in file '/tmp/kig-screen-pe0sfqi1/candidate.c'
 extern f32 func_801B1A7C(void *, void *, f32, s32);
 -----------^
cfe: Error: /tmp/kig-screen-pe0sfqi1/candidate.c, line 179: Incompatible type for the function parameter
 extern f32 func_801B1A7C(void *, void *, f32, s32);
 -------------------------^
cfe: Error: /tmp/kig-screen-pe0sfqi1/candidate.c, line 223: redeclaration of 'func_801B1A7C'; previous declaration at line 23 in file '/tmp/kig-screen-pe0sfqi1/candidate.c'
 extern f32 func_801B1A7C(void *, void *, f32, s32);
 -----------^
cfe: Error: /tmp/kig-screen-pe0sfqi1/candidate.c, line 223: Incompatible type for the function parameter
 extern f32 func_801B1A7C(void *, void *, f32, s32);
 -------------------------^
cfe: Error: /tmp/kig-screen-pe0sfqi1/candidate.c, line 267: redeclaration of 'func_801B1A7C'; previous declaration at line 23 in file '/tmp/kig-screen-pe0sfqi1/candidate.c'
 extern f32 func_801B1A7C(void *, void *, f32, s32);
 -----------^
cfe: Error: /tmp/kig-screen-pe0sfqi1/candidate.c, line 267: Incompatible type for the function parameter
 extern f32 func_801B1A7C(void *, void *, f32, s32);
 -------------------------^
cfe: Error: /tmp/kig-screen-pe0sfqi1/candidate.c, line 311: redeclaration of 'func_801B1A7C'; previous declaration at line 23 in file '/tmp/kig-screen-pe0sfqi1/candidate.c'
 extern f32 func_801B1A7C(void *, void *, f32, s32);
 -----------^
cfe: Error: /tmp/kig-screen-pe0sfqi1/candidate.c, line 311: Incompatible type for the function parameter
 extern f32 func_801B1A7C(void *, void *, f32, s32);
 -------------------------^
```

### func_801BB7B4 (declarations)

```text
cfe: Error: /tmp/kig-screen-sdsv26m3/candidate.c, line 1362: redeclaration of 'func_8002F6F4'; previous declaration at line 1058 in file '/tmp/kig-screen-sdsv26m3/candidate.c'
 extern s32 func_8002F6F4();
 -----------^
cfe: Error: /tmp/kig-screen-sdsv26m3/candidate.c, line 1362: Incompatible function return type for this function.
 extern s32 func_8002F6F4();
 ------------------------^
cfe: Error: /tmp/kig-screen-sdsv26m3/candidate.c, line 1370: redeclaration of 'D_80127CE8'; previous declaration at line 854 in file '/tmp/kig-screen-sdsv26m3/candidate.c'
 extern u8 D_80127CE8[];
 ----------^
cfe: Error: /tmp/kig-screen-sdsv26m3/candidate.c, line 1374: redeclaration of 'D_802C8CB8'; previous declaration at line 804 in file '/tmp/kig-screen-sdsv26m3/candidate.c'
 extern u8 D_802C8CB8;
 ----------^
cfe: Error: /tmp/kig-screen-sdsv26m3/candidate.c, line 1377: redeclaration of 'D_802C8CEA'; previous declaration at line 858 in file '/tmp/kig-screen-sdsv26m3/candidate.c'
 extern u8 D_802C8CEA;
 ----------^
cfe: Error: /tmp/kig-screen-sdsv26m3/candidate.c, line 1407: Unacceptable operand of a multiplicative operator.
             temp_a1 = *(s32 *)(D_801F2EB8 + (D_80127CE8[D_802C8D0D] * 0x8C));
 -------------------------------------------------------^
cfe: Error: /tmp/kig-screen-sdsv26m3/candidate.c, line 1423: Unacceptable operand of a multiplicative operator.
             func_8002F6F4(D_80066C40, *(s32 *)(D_801F2EB8 + (D_802C8CB8 * 0x8C)), &D_8004A258);
 -------------------------------------------------------------^
```

### func_801C317C (declarations)

```text
cfe: Error: /tmp/kig-screen-opmejfxi/candidate.c, line 322: redeclaration of 'D_80285574'; previous declaration at line 170 in file '/tmp/kig-screen-opmejfxi/candidate.c'
 extern s32 **D_80285574;
 -------------^
cfe: Error: /tmp/kig-screen-opmejfxi/candidate.c, line 351: Dereferenced a non-pointer.
     D_802956F4 += func_801BDF94((FrontendGfxWords **)arg0, (D_802956F4 << 6) + D_802C9F70.matrices, **D_80285574, (f32) (((s32) (arg1 * -2) / 3) - 0x5A), 200.0f, (f32) (arg2 - 0x3E8), 1, 1.0f, ((f32) (arg3 + 0x1E) / 30.0f) * 360.0f);
 ------------------------------------------------------------------------------------------------------^
cfe: Error: /tmp/kig-screen-opmejfxi/candidate.c, line 352: Subscripting a non-array.
     var_a1 = &D_80285574[var_v1];
 ------------------------^
cfe: Error: /tmp/kig-screen-opmejfxi/candidate.c, line 371: Subscripting a non-array.
                 var_a1 = &D_80285574[temp_t2];
 ------------------------------------^
cfe: Error: /tmp/kig-screen-opmejfxi/candidate.c, line 382: Subscripting a non-array.
                 var_a0 = D_80285574[temp_t5];
 -----------------------------------^
cfe: Error: /tmp/kig-screen-opmejfxi/candidate.c, line 399: Subscripting a non-array.
                 D_802956F4 += func_801BD640((FrontendGfxWords **)arg0, (temp_t0 << 6) + D_802C9F70.matrices, *(s32 *)((u8 *)D_80285574[D_80285578] + var_s0), temp_f24, (f32) var_s2, temp_f20, 0xFF, 0xFF, 0xFF, D_802D3834);
 --------------------------------------------------------------------------------------------------------------------------------------^
cfe: Error: /tmp/kig-screen-opmejfxi/candidate.c, line 402: Subscripting a non-array.
                 var_a2 = *(s32 *)((u8 *)D_80285574[D_80285578] + var_s0);
 --------------------------------------------------^
```

### func_800216D4 (declarations)

```text
cfe: Error: /tmp/kig-screen-055l52v4/candidate.c, line 215: redeclaration of 'D_8004D278'; previous declaration at line 68 in file '/tmp/kig-screen-055l52v4/candidate.c'
 extern T032Cache216 D_8004D278[][3];
 --------------------^
cfe: Error: /tmp/kig-screen-055l52v4/candidate.c, line 257: Subscripting a non-array.
         D_8004D278[i][player].second=0; D_8004D278[i][player].first=0;
 ------------------^
cfe: Error: /tmp/kig-screen-055l52v4/candidate.c, line 257: Subscripting a non-array.
         D_8004D278[i][player].second=0; D_8004D278[i][player].first=0;
 --------------------------------------------------^
cfe: Error: /tmp/kig-screen-055l52v4/candidate.c, line 260: Subscripting a non-array.
     while ((u32)(p+15)<(u32)(destination+size)) { id=p[0]+(p[1]<<8); entry=&D_8004D278[id][player];
 --------------------------------------------------------------------------------------^
cfe: Error: /tmp/kig-screen-055l52v4/candidate.c, line 267: Subscripting a non-array.
     i++) { entry=&D_8004D278[i][player]; if (!entry->first && !entry->second) {
 ----------------------------^
```

### func_801AF68C (prefix)

```text
cfe: Error: /tmp/kig-screen-6t6qzsom/candidate.c, line 151: redeclaration of 'D_802A1A60'; previous declaration at line 85 in file '/tmp/kig-screen-6t6qzsom/candidate.c'
 extern s32 D_802A1A60[];
 -----------^
```

### func_801C1C34 (prefix)

```text
cfe: Error: /tmp/kig-screen-zgp56m7e/candidate.c, line 217: redeclaration of 'D_8028326C'; previous declaration at line 151 in file '/tmp/kig-screen-zgp56m7e/candidate.c'
 extern s32 D_8028326C[];
 -----------^
```

### func_80029BE0 (declarations)

```text
cfe: Error: /tmp/kig-screen-116k6iaa/candidate.c, line 183: redeclaration of 'D_80061D60'; previous declaration at line 151 in file '/tmp/kig-screen-116k6iaa/candidate.c'
 extern T024DrawBurst D_80061D60[];
 ---------------------^
cfe: Error: /tmp/kig-screen-116k6iaa/candidate.c, line 193: redeclaration of 'func_8002A004'; previous declaration at line 186 in file '/tmp/kig-screen-116k6iaa/candidate.c'
 void func_8002A004(float m[4][4], float x, float y, float z) {
 -----^
cfe: Error: /tmp/kig-screen-116k6iaa/candidate.c, line 193: Incompatible type for the function parameter
 void func_8002A004(float m[4][4], float x, float y, float z) {
 -------------------------^
```

### func_80015594 (declarations)

```text
cfe: Error: /tmp/kig-screen-uc9cwszo/candidate.c, line 639: redeclaration of 'func_80015594'; previous declaration at line 222 in file '/tmp/kig-screen-uc9cwszo/candidate.c'
 void func_80015594(T03315594Command **arg0,s32 *arg1,f32 arg2,s32 arg3,f32 arg4,f32 arg5,f32 arg6) {
 -----^
cfe: Error: /tmp/kig-screen-uc9cwszo/candidate.c, line 639: Incompatible type for the function parameter
 void func_80015594(T03315594Command **arg0,s32 *arg1,f32 arg2,s32 arg3,f32 arg4,f32 arg5,f32 arg6) {
 --------------------------------------^
cfe: Error: /tmp/kig-screen-uc9cwszo/candidate.c, line 839: redeclaration of 'D_80068930'; previous declaration at line 636 in file '/tmp/kig-screen-uc9cwszo/candidate.c'
 extern T033RenderCommand D_80068930[][200];
 -------------------------^
cfe: Error: /tmp/kig-screen-uc9cwszo/candidate.c, line 850: Subscripting a non-array.
     g = D_80068930[D_80044A24];
 ------------------^
```

### func_800257FC (declarations)

```text
cfe: Error: /tmp/kig-screen-f0w2ak74/candidate.c, line 98: redeclaration of 'D_8004CED0'; previous declaration at line 4 in file '/tmp/kig-screen-f0w2ak74/candidate.c'
 extern T032Sprite257 D_8004CED0[];
 ---------------------^
cfe: Error: /tmp/kig-screen-f0w2ak74/candidate.c, line 108: redeclaration of 'func_800257FC'; previous declaration at line 32 in file '/tmp/kig-screen-f0w2ak74/candidate.c'
 void func_800257FC(s32 unused,u16 health,u8 player,u8 flash) {
 -----^
cfe: Error: /tmp/kig-screen-f0w2ak74/candidate.c, line 108: Incompatible type for the function parameter
 void func_800257FC(s32 unused,u16 health,u8 player,u8 flash) {
 -----------------------^
cfe: Error: /tmp/kig-screen-f0w2ak74/candidate.c, line 164: redeclaration of 'func_80025D58'; previous declaration at line 107 in file '/tmp/kig-screen-f0w2ak74/candidate.c'
 void func_80025D58(s32 x, s32 color, s32 alpha, s32 kind) {
 -----^
cfe: Error: /tmp/kig-screen-f0w2ak74/candidate.c, line 164: Incompatible type for the function parameter
 void func_80025D58(s32 x, s32 color, s32 alpha, s32 kind) {
 ------------------------------^
```

### func_80012B7C (declarations)

```text
cfe: Error: /tmp/kig-screen-_4lk64mg/candidate.c, line 80: redeclaration of 'D_8004A730'; previous declaration at line 3 in file '/tmp/kig-screen-_4lk64mg/candidate.c'
 extern s8 D_8004A730, D_8004A5E0;
 ----------^
cfe: Error: /tmp/kig-screen-_4lk64mg/candidate.c, line 80: redeclaration of 'D_8004A5E0'; previous declaration at line 5 in file '/tmp/kig-screen-_4lk64mg/candidate.c'
 extern s8 D_8004A730, D_8004A5E0;
 ----------------------^
cfe: Error: /tmp/kig-screen-_4lk64mg/candidate.c, line 270: redeclaration of 'func_8001346C'; previous declaration at line 87 in file '/tmp/kig-screen-_4lk64mg/candidate.c'
 func_8001346C(T033RenderCommand **, u8, f32);
 ^
cfe: Error: /tmp/kig-screen-_4lk64mg/candidate.c, line 270: Incompatible type for the function parameter
 func_8001346C(T033RenderCommand **, u8, f32);
 --------------^
cfe: Error: /tmp/kig-screen-_4lk64mg/candidate.c, line 271: redeclaration of 'func_8001BB64'; previous declaration at line 86 in file '/tmp/kig-screen-_4lk64mg/candidate.c'
 extern void func_8001BB64(T033RenderCommand **);
 ------------^
cfe: Error: /tmp/kig-screen-_4lk64mg/candidate.c, line 271: Incompatible type for the function parameter
 extern void func_8001BB64(T033RenderCommand **);
 --------------------------^
```

### func_80024CE0 (declarations)

```text
cfe: Error: /tmp/kig-screen-2z6e56ip/candidate.c, line 9: redeclaration of 'D_8004CED0'; previous declaration at line 4 in file '/tmp/kig-screen-2z6e56ip/candidate.c'
 extern T032Sprite24C D_8004CED0[];
 ---------------------^
```

### func_8001D7E4 (declarations)

```text
cfe: Error: /tmp/kig-screen-w4w3_j4g/candidate.c, line 84: redeclaration of 'D_8004D278'; previous declaration at line 68 in file '/tmp/kig-screen-w4w3_j4g/candidate.c'
 extern T069Animation D_8004D278[][3];
 ---------------------^
cfe: Error: /tmp/kig-screen-w4w3_j4g/candidate.c, line 155: Subscripting a non-array.
     temp_v1 = &D_8004D278[var_v0][arg3];
 -------------------------^
cfe: Error: /tmp/kig-screen-w4w3_j4g/candidate.c, line 244: Subscripting a non-array.
             temp_t0_2 = D_8004D278[arg4][arg3].fallback;
 ----------------------------------^
```

### func_80025FC4 (declarations)

```text
cfe: Error: /tmp/kig-screen-znle5wzl/candidate.c, line 128: redeclaration of 'func_80025FC4'; previous declaration at line 34 in file '/tmp/kig-screen-znle5wzl/candidate.c'
 void func_80025FC4(T032Gfx25F **arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4) {
 -----^
cfe: Error: /tmp/kig-screen-znle5wzl/candidate.c, line 128: Incompatible type for the function parameter
 void func_80025FC4(T032Gfx25F **arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4) {
 --------------------------------^
```

### func_80020E98 (declarations)

```text
cfe: Error: /tmp/kig-screen-3tegtbx1/candidate.c, line 218: redeclaration of 'D_8004D278'; previous declaration at line 68 in file '/tmp/kig-screen-3tegtbx1/candidate.c'
 extern T032Cache20E D_8004D278[][3];
 --------------------^
cfe: Error: /tmp/kig-screen-3tegtbx1/candidate.c, line 347: Dereferenced a non-pointer.
         var_s3_2 = &(*D_8004D278)[arg0];
 ----------------------^
cfe: Error: /tmp/kig-screen-3tegtbx1/candidate.c, line 348: Subscripting a non-array.
         var_v1_2 = (s32) D_8004D278[199][arg0].second;
 -----------------------------------^
cfe: Error: /tmp/kig-screen-3tegtbx1/candidate.c, line 352: Dereferenced a non-pointer.
         var_s3_2 = &(*D_8004D278)[arg0];
 ----------------------^
cfe: Error: /tmp/kig-screen-3tegtbx1/candidate.c, line 359: Subscripting a non-array.
         temp_v0_3 = &D_8004D278[var_s5_2][arg0];
 -------------------------------^
cfe: Error: /tmp/kig-screen-3tegtbx1/candidate.c, line 364: Subscripting a non-array.
     D_8004D278[199][arg0].second = (u8 *)var_v1_2;
 --------------^
cfe: Error: /tmp/kig-screen-3tegtbx1/candidate.c, line 371: Subscripting a non-array.
                 D_8004D278[temp_t1_3][arg0].second = var_s4_2;
 --------------------------^
cfe: Error: /tmp/kig-screen-3tegtbx1/candidate.c, line 373: Subscripting a non-array.
                 temp_v1 = &D_8004D278[temp_t1_3][arg0];
 -------------------------------------^
cfe: Error: /tmp/kig-screen-3tegtbx1/candidate.c, line 386: Subscripting a non-array.
         D_8004D278[176][arg0].first = 0;
 ------------------^
cfe: Error: /tmp/kig-screen-3tegtbx1/candidate.c, line 387: Subscripting a non-array.
         D_8004D278[176][arg0].second = (u8 *)temp_a1;
 ------------------^
cfe: Error: /tmp/kig-screen-3tegtbx1/candidate.c, line 388: Subscripting a non-array.
         D_8004D278[175][arg0].first = 0;
 ------------------^
cfe: Error: /tmp/kig-screen-3tegtbx1/candidate.c, line 389: Subscripting a non-array.
         D_8004D278[175][arg0].second = (u8 *) ((((u8 *)temp_a1)[7] << 0x18) + temp_a1 + ((u8 *)temp_a1)[4] + (((u8 *)temp_a1)[5] << 8) + (((u8 *)temp_a1)[6] << 0x10));
 ------------------^
cfe: Error: /tmp/kig-screen-3tegtbx1/candidate.c, line 393: Subscripting a non-array.
         temp_v0_4 = &D_8004D278[var_s5_3][arg0];
 -------------------------------^
```

### func_8001178C (prefix)

```text
cfe: Error: /tmp/kig-screen-gr_aviqt/candidate.c, line 345: redeclaration of 'func_80011FC4'; previous declaration at line 98 in file '/tmp/kig-screen-gr_aviqt/candidate.c'
 s32 func_80011FC4(T020Controller *arg0, u8 arg1) {
 ----^
cfe: Error: /tmp/kig-screen-gr_aviqt/candidate.c, line 345: prototype and non-prototype declaration found for func_80011FC4, the type of this parameter is not compatible with the type after applying default argument promotion
 s32 func_80011FC4(T020Controller *arg0, u8 arg1) {
 -------------------------------------------^
cfe: Error: /tmp/kig-screen-gr_aviqt/candidate.c, line 377: redeclaration of 'func_80012100'; previous declaration at line 99 in file '/tmp/kig-screen-gr_aviqt/candidate.c'
 void func_80012100(u8 arg0, u8 arg1) {
 -----^
cfe: Error: /tmp/kig-screen-gr_aviqt/candidate.c, line 377: prototype and non-prototype declaration found for func_80012100, the type of this parameter is not compatible with the type after applying default argument promotion
 void func_80012100(u8 arg0, u8 arg1) {
 ----------------------^
cfe: Error: /tmp/kig-screen-gr_aviqt/candidate.c, line 466: redeclaration of 'D_8004A258'; previous declaration at line 58 in file '/tmp/kig-screen-gr_aviqt/candidate.c'
 extern void *D_8004A258[];
 -------------^
cfe: Error: /tmp/kig-screen-gr_aviqt/candidate.c, line 473: Subscripting a non-array.
         if (D_8004A258[i] != 0) {
 ----------------------^
cfe: Error: /tmp/kig-screen-gr_aviqt/candidate.c, line 474: Subscripting a non-array.
             func_8002F8F8(D_8004A258[i]);
 ------------------------------------^
```

### func_801C08F8 (prefix)

```text
cfe: Error: /tmp/kig-screen-hjnh6nf0/candidate.c, line 232: redeclaration of 'D_8028326C'; previous declaration at line 110 in file '/tmp/kig-screen-hjnh6nf0/candidate.c'
 extern s32 D_8028326C[];
 -----------^
```

### func_8001E33C (declarations)

```text
cfe: Error: /tmp/kig-screen-167fh8c5/candidate.c, line 206: redeclaration of 'func_8001EC74'; previous declaration at line 78 in file '/tmp/kig-screen-167fh8c5/candidate.c'
 s32 func_8001EC74(T081Gfx **, s32, s32, u32, u32, u8, u8, u8);
 ----^
cfe: Error: /tmp/kig-screen-167fh8c5/candidate.c, line 206: Incompatible type for the function parameter
 s32 func_8001EC74(T081Gfx **, s32, s32, u32, u32, u8, u8, u8);
 ------------------^
cfe: Error: /tmp/kig-screen-167fh8c5/candidate.c, line 224: redeclaration of 'D_8004A450'; previous declaration at line 82 in file '/tmp/kig-screen-167fh8c5/candidate.c'
 extern T081Object D_8004A450[];
 ------------------^
```

### func_800142E0 (declarations)

```text
cfe: Error: /tmp/kig-screen-9lbjmqx9/candidate.c, line 561: redeclaration of 'func_800142E0'; previous declaration at line 383 in file '/tmp/kig-screen-9lbjmqx9/candidate.c'
 void func_800142E0(T033142E0Command **arg0, s32 *arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6) {
 -----^
cfe: Error: /tmp/kig-screen-9lbjmqx9/candidate.c, line 561: prototype and non-prototype declaration found for func_800142E0, the type of this parameter is not compatible with the type after applying default argument promotion
 void func_800142E0(T033142E0Command **arg0, s32 *arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6) {
 -------------------------------------------------------------------------------^
```

### func_801BFCBC (prefix)

```text
cfe: Error: /tmp/kig-screen-36igr0a2/candidate.c, line 332: redeclaration of 'func_8002F6F4'; previous declaration at line 52 in file '/tmp/kig-screen-36igr0a2/candidate.c'
 extern void func_8002F6F4();
 ------------^
cfe: Error: /tmp/kig-screen-36igr0a2/candidate.c, line 332: Incompatible function return type for this function.
 extern void func_8002F6F4();
 -------------------------^
```

### func_801BC1B0 (declarations)

```text
cfe: Error: /tmp/kig-screen-prvxpcfw/candidate.c, line 1408: redeclaration of 'func_801BC1B0'; previous declaration at line 1080 in file '/tmp/kig-screen-prvxpcfw/candidate.c'
 void func_801BC1B0(u8 **arg0, s32 arg1, s32 arg2, u32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, u32 arg8, s32 arg9, u32 arg10, f32 arg11, f32 arg12, s32 arg13, s32 arg14) {
 -----^
cfe: Error: /tmp/kig-screen-prvxpcfw/candidate.c, line 1408: Incompatible type for the function parameter
 void func_801BC1B0(u8 **arg0, s32 arg1, s32 arg2, u32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, u32 arg8, s32 arg9, u32 arg10, f32 arg11, f32 arg12, s32 arg13, s32 arg14) {
 ------------------------^
```

### func_801C9B14 (declarations)

```text
cfe: Error: /tmp/kig-screen-34z0u6hs/candidate.c, line 698: redeclaration of 'func_801C9698'; previous declaration at line 643 in file '/tmp/kig-screen-34z0u6hs/candidate.c'
 extern void func_801C9698(FrontendGfxWords **, FrontendRenderContext *);
 ------------^
cfe: Error: /tmp/kig-screen-34z0u6hs/candidate.c, line 698: Incompatible type for the function parameter
 extern void func_801C9698(FrontendGfxWords **, FrontendRenderContext *);
 --------------------------^
cfe: Error: /tmp/kig-screen-34z0u6hs/candidate.c, line 703: redeclaration of 'D_802923A0'; previous declaration at line 134 in file '/tmp/kig-screen-34z0u6hs/candidate.c'
 extern u8 D_802923A0;
 ----------^
cfe: Error: /tmp/kig-screen-34z0u6hs/candidate.c, line 711: redeclaration of 'D_80292698'; previous declaration at line 268 in file '/tmp/kig-screen-34z0u6hs/candidate.c'
 extern FrontendMenuItem ***D_80292698[];
 ---------------------------^
cfe: Error: /tmp/kig-screen-34z0u6hs/candidate.c, line 717: redeclaration of 'D_8029538C'; previous declaration at line 87 in file '/tmp/kig-screen-34z0u6hs/candidate.c'
 extern u8 D_8029538C[];
 ----------^
cfe: Error: /tmp/kig-screen-34z0u6hs/candidate.c, line 718: redeclaration of 'D_802953A0'; previous declaration at line 88 in file '/tmp/kig-screen-34z0u6hs/candidate.c'
 extern u8 D_802953A0[0x24];
 ----------^
cfe: Error: /tmp/kig-screen-34z0u6hs/candidate.c, line 719: redeclaration of 'D_802953C4'; previous declaration at line 89 in file '/tmp/kig-screen-34z0u6hs/candidate.c'
 extern u8 D_802953C4[];
 ----------^
cfe: Error: /tmp/kig-screen-34z0u6hs/candidate.c, line 720: redeclaration of 'D_802953E4'; previous declaration at line 90 in file '/tmp/kig-screen-34z0u6hs/candidate.c'
 extern u8 D_802953E4[];
 ----------^
cfe: Error: /tmp/kig-screen-34z0u6hs/candidate.c, line 721: redeclaration of 'D_802953F8'; previous declaration at line 91 in file '/tmp/kig-screen-34z0u6hs/candidate.c'
 extern u8 D_802953F8[];
 ----------^
cfe: Error: /tmp/kig-screen-34z0u6hs/candidate.c, line 722: redeclaration of 'D_80295418'; previous declaration at line 92 in file '/tmp/kig-screen-34z0u6hs/candidate.c'
 extern u8 D_80295418[];
 ----------^
cfe: Error: /tmp/kig-screen-34z0u6hs/candidate.c, line 821: Unacceptable operand of relational operator.
             if (D_802923A0 < row) {
 ---------------------------^
cfe: Error: /tmp/kig-screen-34z0u6hs/candidate.c, line 856: Unacceptable operand of == or !=
                         if (row == D_802923A0 && visible) {
 --------------------------------^
cfe: Error: /tmp/kig-screen-34z0u6hs/candidate.c, line 908: Unacceptable operand of relational operator.
             if (D_802923A0 >= last) {
 ---------------------------^
```

### func_801ABB20 (prefix)

```text
cfe: Error: /tmp/kig-screen-kt5q62nv/candidate.c, line 702: redeclaration of 'D_8004A428'; previous declaration at line 77 in file '/tmp/kig-screen-kt5q62nv/candidate.c'
 extern u32 D_8004A428[];
 -----------^
cfe: Error: /tmp/kig-screen-kt5q62nv/candidate.c, line 753: redeclaration of 'func_801AD794'; previous declaration at line 37 in file '/tmp/kig-screen-kt5q62nv/candidate.c'
 void func_801AD794(RenderState *arg0, s32 arg1, s32 arg2, s32 arg3) {
 -----^
cfe: Error: /tmp/kig-screen-kt5q62nv/candidate.c, line 753: Incompatible type for the function parameter
 void func_801AD794(RenderState *arg0, s32 arg1, s32 arg2, s32 arg3) {
 --------------------------------^
cfe: Error: /tmp/kig-screen-kt5q62nv/candidate.c, line 768: redeclaration of 'D_80295721'; previous declaration at line 109 in file '/tmp/kig-screen-kt5q62nv/candidate.c'
 extern u8 D_80044A24, D_80295721;
 ----------------------^
cfe: Error: /tmp/kig-screen-kt5q62nv/candidate.c, line 787: redeclaration of 'D_8004A2D8'; previous declaration at line 72 in file '/tmp/kig-screen-kt5q62nv/candidate.c'
 extern u8 D_8004A2D8[][32];
 ----------^
cfe: Error: /tmp/kig-screen-kt5q62nv/candidate.c, line 788: redeclaration of 'osSendMesg'; previous declaration at line 24 in file '/tmp/kig-screen-kt5q62nv/candidate.c'
 extern s32 osSendMesg(void *, void *, s32);
 -----------^
cfe: Error: /tmp/kig-screen-kt5q62nv/candidate.c, line 788: Incompatible type for the function parameter
 extern s32 osSendMesg(void *, void *, s32);
 ------------------------------^
cfe: Error: /tmp/kig-screen-kt5q62nv/candidate.c, line 848: redeclaration of 'D_80295721'; previous declaration at line 109 in file '/tmp/kig-screen-kt5q62nv/candidate.c'
 extern u8 D_80295721;
 ----------^
cfe: Error: /tmp/kig-screen-kt5q62nv/candidate.c, line 864: redeclaration of 'D_802C9F70'; previous declaration at line 111 in file '/tmp/kig-screen-kt5q62nv/candidate.c'
 extern RenderState D_802C9F70;
 -------------------^
```

### func_800310C0 (declarations)

```text
cfe: Error: /tmp/kig-screen-xqcjch0z/candidate.c, line 88: 'D_8004CED0' undefined; reoccurrences will not be reported.
     var_s1 = (u8 *)D_8004CED0;
 -------------------^
```

### func_801C5298 (declarations)

```text
cfe: Error: /tmp/kig-screen-oagem6pk/candidate.c, line 299: redeclaration of 'func_801C5064'; previous declaration at line 227 in file '/tmp/kig-screen-oagem6pk/candidate.c'
 extern void func_801C5064(T030Cmd5298 **,T030Render5298 *,s32,s32);
 ------------^
cfe: Error: /tmp/kig-screen-oagem6pk/candidate.c, line 299: Incompatible type for the function parameter
 extern void func_801C5064(T030Cmd5298 **,T030Render5298 *,s32,s32);
 --------------------------^
cfe: Error: /tmp/kig-screen-oagem6pk/candidate.c, line 300: redeclaration of 'func_801C51F8'; previous declaration at line 258 in file '/tmp/kig-screen-oagem6pk/candidate.c'
 extern void func_801C51F8(T030Cmd5298 **);
 ------------^
cfe: Error: /tmp/kig-screen-oagem6pk/candidate.c, line 300: Incompatible type for the function parameter
 extern void func_801C51F8(T030Cmd5298 **);
 --------------------------^
cfe: Error: /tmp/kig-screen-oagem6pk/candidate.c, line 304: redeclaration of 'D_4AC40'; previous declaration at line 256 in file '/tmp/kig-screen-oagem6pk/candidate.c'
 extern u8 D_4AC40[],D_801F3164[],D_801F3176[],D_801F3308[],D_801F331A[];
 ----------^
cfe: Error: /tmp/kig-screen-oagem6pk/candidate.c, line 320: redeclaration of 'D_802D3990'; previous declaration at line 178 in file '/tmp/kig-screen-oagem6pk/candidate.c'
 extern f32 D_802D3990[];
 -----------^
cfe: Error: /tmp/kig-screen-oagem6pk/candidate.c, line 321: redeclaration of 'D_802D399F'; previous declaration at line 188 in file '/tmp/kig-screen-oagem6pk/candidate.c'
 extern u8 D_802D3985,D_802D399C,D_802D399F,D_802D39B4,D_802D39B6,D_802D39BA;
 --------------------------------^
cfe: Error: /tmp/kig-screen-oagem6pk/candidate.c, line 440: Subscripting a non-array.
         func_8002DDD4(D_802D3990[0], D_802D3990[1], D_802D3990[2], &spEC, &spE8);
 --------------------------------^
cfe: Error: /tmp/kig-screen-oagem6pk/candidate.c, line 440: Subscripting a non-array.
         func_8002DDD4(D_802D3990[0], D_802D3990[1], D_802D3990[2], &spEC, &spE8);
 -----------------------------------------------^
cfe: Error: /tmp/kig-screen-oagem6pk/candidate.c, line 440: Subscripting a non-array.
         func_8002DDD4(D_802D3990[0], D_802D3990[1], D_802D3990[2], &spEC, &spE8);
 --------------------------------------------------------------^
cfe: Error: /tmp/kig-screen-oagem6pk/candidate.c, line 441: Subscripting a non-array.
         func_8002DCC8(D_802D3990[0], D_802D3990[1], D_802D3990[2], &spE4);
 --------------------------------^
cfe: Error: /tmp/kig-screen-oagem6pk/candidate.c, line 441: Subscripting a non-array.
         func_8002DCC8(D_802D3990[0], D_802D3990[1], D_802D3990[2], &spE4);
 -----------------------------------------------^
cfe: Error: /tmp/kig-screen-oagem6pk/candidate.c, line 441: Subscripting a non-array.
         func_8002DCC8(D_802D3990[0], D_802D3990[1], D_802D3990[2], &spE4);
 --------------------------------------------------------------^
```

### func_801B47A4 (prefix)

```text
cfe: Error: /tmp/kig-screen-qpr0bd8d/candidate.c, line 1075: redeclaration of 'D_802C8CE8'; previous declaration at line 895 in file '/tmp/kig-screen-qpr0bd8d/candidate.c'
 extern u8 D_802C8CE0, D_802C8D06, D_802C8CE8;
 ----------------------------------^
cfe: Error: include/frontend.h, line 158: redeclaration of 'D_80127CA8'; previous declaration at line 887 in file '/tmp/kig-screen-qpr0bd8d/candidate.c'
 extern u16 D_80127CA8[][6];
 -----------^
cfe: Error: include/frontend.h, line 166: redeclaration of 'D_802D3678'; previous declaration at line 897 in file '/tmp/kig-screen-qpr0bd8d/candidate.c'
 extern u64 D_802D3678[2];
 -----------^
cfe: Error: include/frontend.h, line 170: redeclaration of 'D_802D3A06'; previous declaration at line 895 in file '/tmp/kig-screen-qpr0bd8d/candidate.c'
 extern u8 D_802D3A00, D_802D3A06, D_802D3E15;
 ----------------------^
cfe: Error: include/frontend.h, line 195: redeclaration of 'func_801C7CD0'; previous declaration at line 879 in file '/tmp/kig-screen-qpr0bd8d/candidate.c'
 void func_801C7CD0(u8);
 -----^
cfe: Error: include/frontend.h, line 195: Incompatible type for the function parameter
 void func_801C7CD0(u8);
 -------------------^
```

### func_801CAA00 (declarations)

```text
cfe: Error: /tmp/kig-screen-g1o11byb/candidate.c, line 772: redeclaration of 'func_801C7998'; previous declaration at line 113 in file '/tmp/kig-screen-g1o11byb/candidate.c'
 extern s32 func_801C7998(s32, s32);
 -----------^
cfe: Error: /tmp/kig-screen-g1o11byb/candidate.c, line 772: Incompatible function return type for this function.
 extern s32 func_801C7998(s32, s32);
 ------------------------^
cfe: Error: /tmp/kig-screen-g1o11byb/candidate.c, line 781: redeclaration of 'D_80127D00'; previous declaration at line 266 in file '/tmp/kig-screen-g1o11byb/candidate.c'
 extern u8 D_80127D00[8][4];
 ----------^
cfe: Error: /tmp/kig-screen-g1o11byb/candidate.c, line 784: redeclaration of 'D_802923A0'; previous declaration at line 134 in file '/tmp/kig-screen-g1o11byb/candidate.c'
 extern u8 D_802923A0;
 ----------^
cfe: Error: /tmp/kig-screen-g1o11byb/candidate.c, line 791: redeclaration of 'D_80295428'; previous declaration at line 93 in file '/tmp/kig-screen-g1o11byb/candidate.c'
 extern u8 D_80295428[];
 ----------^
cfe: Error: /tmp/kig-screen-g1o11byb/candidate.c, line 861: Unacceptable operand of relational operator.
                 if (D_802923A0 >= D_802923A4) {
 -------------------------------^
cfe: Error: /tmp/kig-screen-g1o11byb/candidate.c, line 926: Unacceptable operand of relational operator.
             if ((buttons & 0x400) && !(prev->buttons & 0x400) && D_802923A0 >= D_802923A8 - 1) {
 ----------------------------------------------------------------------------^
cfe: Error: /tmp/kig-screen-g1o11byb/candidate.c, line 958: The number of arguments doesn't agree with the number in the declaration.
                         key = func_801C7998(hi, buttons);
 -------------------------------------------^
cfe: Error: /tmp/kig-screen-g1o11byb/candidate.c, line 989: Subscripting a non-array.
         ch = &D_80127D00[D_802D39FC][D_802D3A01];
 ------------------------------------^
cfe: Error: /tmp/kig-screen-g1o11byb/candidate.c, line 1036: Subscripting a non-array.
                     if (D_80127D00[D_802D39FC][D_802D3A01] <= 0x20) {
 ----------------------------------------------^
cfe: Error: /tmp/kig-screen-g1o11byb/candidate.c, line 1037: Subscripting a non-array.
                         D_80127D00[D_802D39FC][D_802D3A01] = D_802D3A02;
 ----------------------------------------------^
```

### func_801B849C (declarations)

```text
cfe: Error: /tmp/kig-screen-7r1cp922/candidate.c, line 1073: Incompatible type for the function parameter
 extern s32 func_801BDA6C(u32 **, s32, void *, f32, f32, f32, s32, s32, s32, s32, f32);
 -------------------------^
cfe: Error: /tmp/kig-screen-7r1cp922/candidate.c, line 1074: redeclaration of 'func_801BDF94'; previous declaration at line 215 in file 'include/frontend.h'
 extern s32 func_801BDF94(u32 **, s32, void *, f32, f32, f32, s32, f32, f32);
 -----------^
cfe: Error: /tmp/kig-screen-7r1cp922/candidate.c, line 1074: Incompatible type for the function parameter
 extern s32 func_801BDF94(u32 **, s32, void *, f32, f32, f32, s32, f32, f32);
 -------------------------^
cfe: Error: /tmp/kig-screen-7r1cp922/candidate.c, line 1075: redeclaration of 'func_801BE540'; previous declaration at line 216 in file 'include/frontend.h'
 extern s32 func_801BE540(u32 **, s32, void *, f32, f32, f32, s32, s32, s32, s32, f32);
 -----------^
cfe: Error: /tmp/kig-screen-7r1cp922/candidate.c, line 1075: Incompatible type for the function parameter
 extern s32 func_801BE540(u32 **, s32, void *, f32, f32, f32, s32, s32, s32, s32, f32);
 -------------------------^
cfe: Error: /tmp/kig-screen-7r1cp922/candidate.c, line 1077: redeclaration of 'func_801C9584'; previous declaration at line 206 in file 'include/frontend.h'
 extern void *func_801C9584(u8, s32);
 -------------^
cfe: Error: /tmp/kig-screen-7r1cp922/candidate.c, line 1077: Incompatible function return type for this function.
 extern void *func_801C9584(u8, s32);
 --------------------------^
```

### func_80019880 (declarations)

```text
cfe: Error: /tmp/kig-screen-qncgmk_8/candidate.c, line 2243: redeclaration of 'D_8004A428'; previous declaration at line 796 in file '/tmp/kig-screen-qncgmk_8/candidate.c'
 extern u8 D_8004A428;
 ----------^
cfe: Error: /tmp/kig-screen-qncgmk_8/candidate.c, line 2250: redeclaration of 'D_8004ACCC'; previous declaration at line 364 in file '/tmp/kig-screen-qncgmk_8/candidate.c'
 extern u8 D_8004ACCC;
 ----------^
cfe: Error: /tmp/kig-screen-qncgmk_8/candidate.c, line 2251: redeclaration of 'D_8004ACD0'; previous declaration at line 364 in file '/tmp/kig-screen-qncgmk_8/candidate.c'
 extern u8 D_8004ACD0;
 ----------^
cfe: Error: /tmp/kig-screen-qncgmk_8/candidate.c, line 2253: redeclaration of 'D_8004ACD4'; previous declaration at line 13 in file '/tmp/kig-screen-qncgmk_8/candidate.c'
 extern u8 D_8004ACD4;
 ----------^
cfe: Error: /tmp/kig-screen-qncgmk_8/candidate.c, line 2256: redeclaration of 'D_80068930'; previous declaration at line 797 in file '/tmp/kig-screen-qncgmk_8/candidate.c'
 extern u8 D_80068930;
 ----------^
cfe: Error: /tmp/kig-screen-qncgmk_8/candidate.c, line 2261: redeclaration of 'func_80019880'; previous declaration at line 386 in file '/tmp/kig-screen-qncgmk_8/candidate.c'
 void func_80019880(u8 **arg0, s32 *arg1, s32 arg2, s32 arg3, f32 arg5, f32 arg6) {
 -----^
cfe: Error: /tmp/kig-screen-qncgmk_8/candidate.c, line 2261: Incompatible type for the function parameter
 void func_80019880(u8 **arg0, s32 *arg1, s32 arg2, s32 arg3, f32 arg5, f32 arg6) {
 ------------------------^
```

### func_801ADEA0 (prefix)

```text
cfe: Error: /tmp/kig-screen-s9brzd4l/candidate.c, line 497: redeclaration of 'D_801D18B8'; previous declaration at line 19 in file '/tmp/kig-screen-s9brzd4l/candidate.c'
 extern T025Effect D_801D18B8[];
 ------------------^
cfe: Error: /tmp/kig-screen-s9brzd4l/candidate.c, line 505: 'flags' undefined; reoccurrences will not be reported.
         if (D_801D18B8[i].flags & arg0) D_801D18B8[i].state = -1;
 -------------------------^
cfe: Error: /tmp/kig-screen-s9brzd4l/candidate.c, line 505: member of structure or union required
         if (D_801D18B8[i].flags & arg0) D_801D18B8[i].state = -1;
 --------------------------^
cfe: Error: /tmp/kig-screen-s9brzd4l/candidate.c, line 505: 'state' undefined; reoccurrences will not be reported.
         if (D_801D18B8[i].flags & arg0) D_801D18B8[i].state = -1;
 -----------------------------------------------------^
cfe: Error: /tmp/kig-screen-s9brzd4l/candidate.c, line 505: member of structure or union required
         if (D_801D18B8[i].flags & arg0) D_801D18B8[i].state = -1;
 ------------------------------------------------------^
```

### func_801B6E4C (declarations)

```text
cfe: Error: /tmp/kig-screen-twrl7tjr/candidate.c, line 1319: Unacceptable operand of a multiplicative operator.
                         var_a2 = *((void * *)(D_801F2EB4 + (D_80127CE8[sp133] * 0x8C)));
 ----------------------------------------------------------------------^
cfe: Error: /tmp/kig-screen-twrl7tjr/candidate.c, line 1416: Unacceptable operand of a multiplicative operator.
                 sp134 = func_801BDF94(arg0, arg2, (D_80127D30 * 4) - 4 + &D_80127D00, -290.0f, (f32) (var_v1 + 0xF0), -400.0f, 0, 1.0f, 0.0f);
 ---------------------------------------------------^
cfe: Error: /tmp/kig-screen-twrl7tjr/candidate.c, line 1417: Unacceptable operand of &.
                 sp134 += func_801BD640(arg0, (sp134 << 6) + arg2, func_801C9584((D_80127D30 - 1) & 0xFF, 1), -740.0f, (f32) (var_v1 + 0x212), -1600.0f, (s32) var_t0_2, (s32) var_t1_2, (s32) var_t1_2, 0xFF);
 --------------------------------------------------------------------------------------------^
cfe: Error: /tmp/kig-screen-twrl7tjr/candidate.c, line 1418: Unacceptable operand of &.
                 sp134 += func_801BD640(arg0, (sp134 << 6) + arg2, func_801C9584((D_80127D30 - 1) & 0xFF, 0), -770.0f, (f32) (var_v1 + 0x1D6), -1600.0f, 0xFF, 0xFF, 0xFF, 0xFF);
 --------------------------------------------------------------------------------------------^
cfe: Error: /tmp/kig-screen-twrl7tjr/candidate.c, line 1516: Unacceptable operand of == or !=
         if (D_8012830A == 1) {
 -----------------------^
```

### func_8000FA80 (prefix)

```text
cfe: Error: /tmp/kig-screen-vmkvnfy4/candidate.c, line 398: redeclaration of 'func_80012100'; previous declaration at line 76 in file '/tmp/kig-screen-vmkvnfy4/candidate.c'
 void func_80012100(u8 arg0, u8 arg1) {
 -----^
cfe: Error: /tmp/kig-screen-vmkvnfy4/candidate.c, line 398: prototype and non-prototype declaration found for func_80012100, the type of this parameter is not compatible with the type after applying default argument promotion
 void func_80012100(u8 arg0, u8 arg1) {
 ----------------------^
```

### func_8001EC74 (declarations)

```text
cfe: Error: /tmp/kig-screen-pxs5yrz0/candidate.c, line 210: redeclaration of 'func_8001EC74'; previous declaration at line 78 in file '/tmp/kig-screen-pxs5yrz0/candidate.c'
 void func_8001EC74(u8 **arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5, u8 arg6, u8 arg7) {
 -----^
cfe: Error: /tmp/kig-screen-pxs5yrz0/candidate.c, line 210: Incompatible function return type for this function.
 void func_8001EC74(u8 **arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5, u8 arg6, u8 arg7) {
 ------------------^
cfe: Error: /tmp/kig-screen-pxs5yrz0/candidate.c, line 823: 'D_8004AA28' undefined; reoccurrences will not be reported.
                                     if ((temp_t7_4 < (0xF0 << D_8004AA28)) && (sp9C < (0x140 << D_8004AA28)) && (sp9C >= -0x12B) && (temp_t7_4 >= -0x12B)) {
 --------------------------------------------------------------^
```

### func_80015450 (ERROR)

```text
expected one owner, got 0
```

### func_80016078 (ERROR)

```text
expected one owner, got 0
```

### func_800170C4 (ERROR)

```text
expected one owner, got 0
```

### func_80017378 (ERROR)

```text
expected one owner, got 0
```

### func_80017D6C (ERROR)

```text
expected one owner, got 0
```

### func_800193DC (ERROR)

```text
expected one owner, got 0
```

### func_80021B6C (ERROR)

```text
cfe: Error: /tmp/kig-screen-y87h993m/candidate.c, line 228: redeclaration of 'D_8004AC8A'; previous declaration at line 76 in file '/tmp/kig-screen-y87h993m/candidate.c'
 extern u8 D_8004AC8A; extern u8 D_8004AC88,D_8004AA28,D_8004A9D8,D_8004A998,D_8004AC89;
 ----------^
cfe: Error: /tmp/kig-screen-y87h993m/candidate.c, line 228: redeclaration of 'D_8004AC89'; previous declaration at line 75 in file '/tmp/kig-screen-y87h993m/candidate.c'
 extern u8 D_8004AC8A; extern u8 D_8004AC88,D_8004AA28,D_8004A9D8,D_8004A998,D_8004AC89;
 ----------------------------------------------------------------------------^
cfe: Error: /tmp/kig-screen-y87h993m/candidate.c, line 274: redeclaration of 'D_801D3430'; previous declaration at line 86 in file '/tmp/kig-screen-y87h993m/candidate.c'
 } T032Actor21B; extern T032Actor21B D_801D3430[];
 ------------------------------------^
cfe: Error: /tmp/kig-screen-y87h993m/candidate.c, line 275: redeclaration of 'D_8004D278'; previous declaration at line 68 in file '/tmp/kig-screen-y87h993m/candidate.c'
 extern T032Cache21B D_8004D278[][3];
 --------------------^
cfe: Error: /tmp/kig-screen-y87h993m/candidate.c, line 284: redeclaration of 'func_8001EC74'; previous declaration at line 78 in file '/tmp/kig-screen-y87h993m/candidate.c'
 extern void func_8001C5AC(T032Gfx21B **,s32,void *,u8,s32,f32,f32,f32,f32,f32,f32,u32); extern void func_8001D7E4(s32,u8,u8,s32,s32),func_8001EC74(T032Gfx21B **,s32,s32,u32,u32,s32,s32,s32);
 -------------------------------------------------------------------------------------------------------------------------------------^
cfe: Error: /tmp/kig-screen-y87h993m/candidate.c, line 284: Incompatible function return type for this function.
 extern void func_8001C5AC(T032Gfx21B **,s32,void *,u8,s32,f32,f32,f32,f32,f32,f32,u32); extern void func_8001D7E4(s32,u8,u8,s32,s32),func_8001EC74(T032Gfx21B **,s32,s32,u32,u32,s32,s32,s32);
 --------------------------------------------------------------------------------------------------------------------------------------------------^
cfe: Error: /tmp/kig-screen-y87h993m/candidate.c, line 397: Subscripting a non-array.
     temp_v0_3 = var_fp_3 ^ 1; if (((&D_801D3430[var_fp_3])->scale - (&D_801D3430[temp_v0_3])->scale) < -0x80) { D_801D7370[order[var_fp_3]] = temp_v0_3;
 -----------------------------------------------^
cfe: Error: /tmp/kig-screen-y87h993m/candidate.c, line 412: Subscripting a non-array.
             temp_s0 = &D_801D3430[temp_a1];
 ---------------------------------^
cfe: Error: /tmp/kig-screen-y87h993m/candidate.c, line 463: Subscripting a non-array.
                     } if ((D_8004D278[var_s2][var_s1].first != 0) && (sp160 != 4) && (sp160 != 5)) {
 -------------------------------------^
```

```text
'NoneType' object is not subscriptable
```

### func_80024714 (ERROR)

```text
expected one owner, got 0
```

### func_800253D0 (ERROR)

```text
expected one owner, got 0
```

### func_80028A00 (ERROR)

```text
cfe: Error: /tmp/kig-screen-1ex_5otz/candidate.c, line 181: Syntax Error
     T024RenderParticle *particle;
 -----------------------^
cfe: Error: /tmp/kig-screen-1ex_5otz/candidate.c, line 182: Syntax Error
     f32 temp_f20;
 --------^
cfe: Error: /tmp/kig-screen-1ex_5otz/candidate.c, line 183: Syntax Error
     f32 temp_f22;
 --------^
cfe: Error: /tmp/kig-screen-1ex_5otz/candidate.c, line 184: Syntax Error
     f32 temp_f24;
 --------^
cfe: Error: /tmp/kig-screen-1ex_5otz/candidate.c, line 185: Syntax Error
     f32 temp_f2;
 --------^
cfe: Error: /tmp/kig-screen-1ex_5otz/candidate.c, line 186: Syntax Error
     f32 temp_f2_2;
 --------^
cfe: Error: /tmp/kig-screen-1ex_5otz/candidate.c, line 187: Syntax Error
     f32 temp_f2_3;
 --------^
cfe: Error: /tmp/kig-screen-1ex_5otz/candidate.c, line 188: Syntax Error
     f32 var_f10;
 --------^
cfe: Error: /tmp/kig-screen-1ex_5otz/candidate.c, line 189: Syntax Error
     f32 var_f16;
 --------^
cfe: Error: /tmp/kig-screen-1ex_5otz/candidate.c, line 190: Syntax Error
     f32 var_f18;
 --------^
cfe: Error: /tmp/kig-screen-1ex_5otz/candidate.c, line 191: Syntax Error
     f32 var_f18_2;
 --------^
cfe: Error: /tmp/kig-screen-1ex_5otz/candidate.c, line 192: Syntax Error
     f32 var_f4;
 --------^
cfe: Error: /tmp/kig-screen-1ex_5otz/candidate.c, line 193: Syntax Error
     f32 var_f4_2;
 --------^
cfe: Error: /tmp/kig-screen-1ex_5otz/candidate.c, line 194: Syntax Error
     f32 var_f8;
 --------^
cfe: Error: /tmp/kig-screen-1ex_5otz/candidate.c, line 195: Syntax Error
     s16 temp_t0;
 --------^
cfe: Error: /tmp/kig-screen-1ex_5otz/candidate.c, line 196: Syntax Error
     s16 temp_t2;
 --------^
cfe: Error: /tmp/kig-screen-1ex_5otz/candidate.c, line 197: Syntax Error
     s16 var_a3;
 --------^
cfe: Error: /tmp/kig-screen-1ex_5otz/candidate.c, line 198: Syntax Error
     s32 temp_a2;
 --------^
cfe: Error: /tmp/kig-screen-1ex_5otz/candidate.c, line 199: Syntax Error
     s32 temp_t5;
 --------^
cfe: Error: /tmp/kig-screen-1ex_5otz/candidate.c, line 200: Syntax Error
     s32 temp_t7;
 --------^
cfe: Error: /tmp/kig-screen-1ex_5otz/candidate.c, line 201: Syntax Error
     s32 temp_t9;
 --------^
cfe: Error: /tmp/kig-screen-1ex_5otz/candidate.c, line 202: Syntax Error
     s32 temp_v0_6;
 --------^
cfe: Error: /tmp/kig-screen-1ex_5otz/candidate.c, line 203: Syntax Error
     s32 temp_v0_7;
 --------^
cfe: Error: /tmp/kig-screen-1ex_5otz/candidate.c, line 204: Syntax Error
     s32 temp_v1_10;
 --------^
cfe: Error: /tmp/kig-screen-1ex_5otz/candidate.c, line 205: Syntax Error
     s32 temp_v1_11;
 --------^
cfe: Error: /tmp/kig-screen-1ex_5otz/candidate.c, line 206: Syntax Error
     s32 temp_v1_6;
 --------^
cfe: Error: /tmp/kig-screen-1ex_5otz/candidate.c, line 207: Syntax Error
     s32 var_a1;
 --------^
cfe: Error: /tmp/kig-screen-1ex_5otz/candidate.c, line 208: Syntax Error
     s32 var_a1_3;
 --------^
cfe: Error: /tmp/kig-screen-1ex_5otz/candidate.c, line 209: Syntax Error
     s32 var_a2_2;
 --------^
cfe: Error: /tmp/kig-screen-1ex_5otz/candidate.c, line 210: Syntax Error
     s32 var_fp;
 --------^
cfe: Fatal: Too many errors... goodbye.
```

```text
'NoneType' object is not subscriptable
```

### func_80030220 (ERROR)

```text
expected one owner, got 0
```

### func_80030440 (ERROR)

```text
expected one owner, got 0
```

### func_80031A38 (ERROR)

```text
cfe: Error: /tmp/kig-screen-ttm3qaqw/candidate.c, line 12: Syntax Error
     T022Sprite *sprite = &D_8004CED0[D_8004EA78];
 -----------------------^
cfe: Error: /tmp/kig-screen-ttm3qaqw/candidate.c, line 13: Syntax Error
     u8 *out = sprite->data;
 -------^
cfe: Error: /tmp/kig-screen-ttm3qaqw/candidate.c, line 14: Syntax Error
     s32 width = input[4] + (input[5]<<8);
 --------^
cfe: Error: /tmp/kig-screen-ttm3qaqw/candidate.c, line 15: Syntax Error
     s32 height = input[6] + (input[7]<<8);
 --------^
cfe: Error: /tmp/kig-screen-ttm3qaqw/candidate.c, line 16: Syntax Error
     s32 stride = (width+7)&0xFFF8;
 --------^
cfe: Error: /tmp/kig-screen-ttm3qaqw/candidate.c, line 17: Syntax Error
     s32 y;
 --------^
```

```text
'NoneType' object is not subscriptable
```

### func_80031DD0 (ERROR)

```text
cfe: Error: /tmp/kig-screen-1f27t882/candidate.c, line 16: Syntax Error
     T022Sprite *sprite = &D_8004CED0[D_8004EA78];
 -----------------------^
cfe: Error: /tmp/kig-screen-1f27t882/candidate.c, line 17: Syntax Error
     u8 *intensity = sprite->data;
 -------^
cfe: Error: /tmp/kig-screen-1f27t882/candidate.c, line 18: Syntax Error
     u16 *color = (u16 *)sprite->unk0;
 --------^
cfe: Error: /tmp/kig-screen-1f27t882/candidate.c, line 18: Syntax Error
     u16 *color = (u16 *)sprite->unk0;
 -----------------------^
cfe: Error: /tmp/kig-screen-1f27t882/candidate.c, line 19: Syntax Error
     u16 *palette = D_800482D0[((s16 *)sprite)[13]];
 --------^
cfe: Error: /tmp/kig-screen-1f27t882/candidate.c, line 19: Syntax Error
     u16 *palette = D_800482D0[((s16 *)sprite)[13]];
 -------------------------------------^
cfe: Error: /tmp/kig-screen-1f27t882/candidate.c, line 21: Syntax Error
     s32 top = vertical >> 16;
 --------^
cfe: Error: /tmp/kig-screen-1f27t882/candidate.c, line 22: Syntax Error
     s32 height = input[6] + (input[7]<<8);
 --------^
cfe: Error: /tmp/kig-screen-1f27t882/candidate.c, line 23: Syntax Error
     s32 y;
 --------^
```

```text
'NoneType' object is not subscriptable
```

### func_801B695C (ERROR)

```text
expected one owner, got 0
```

### func_801BEEA4 (ERROR)

```text
expected one owner, got 0
```

### func_801BF720 (ERROR)

```text
expected one owner, got 0
```

### func_801BF914 (ERROR)

```text
expected one owner, got 0
```

### func_801C224C (ERROR)

```text
expected one owner, got 0
```

### func_801C47E0 (ERROR)

```text
expected one owner, got 0
```

### func_801C48E4 (ERROR)

```text
expected one owner, got 0
```

### func_801C80F0 (ERROR)

```text
expected one owner, got 0
```

### func_801C90D4 (ERROR)

```text
expected one owner, got 0
```

