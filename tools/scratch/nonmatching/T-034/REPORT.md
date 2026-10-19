# T-034 (opus-1): ovl_7DF8 leftovers. Report written by the lead from the worker's final reply.

11 matched: func_801CA91C, func_801CC784, func_801C9584 (a one-case switch was needed), func_801CCAB0 (u64 save fields), func_801CA7E4, func_801C8DBC, func_801CCEAC, func_801CBA2C, func_801C86A8, func_801C8868, and func_801CCBCC. The lead landed func_801CCBCC by changing func_801CC350/524/600 to return s32 (they return their callee's result) and func_801CC350's first parameter to s32 *.

| Draft | Remaining diff |
|---|---|
| func_801ADCFC | Code identical standalone; the switch emits its own jump table, but jtbl_802927C8 is owned by the data asm |
| func_801CBF8C | One `li t8,1` scheduled differently |
| func_801C8AE0 | Temp register numbers only |
| func_801C8C24 | Trailing nibble unpack addresses its bytes differently |
| func_801C8F28 | 4 lines, temp register numbers only |
| func_801CD1F0 | Saved-register allocation (param = OSPfsState, 36 B) |
| func_801CBCCC | Identical apart from alignment nops; jtbl_802956C4 ownership |
| func_801ACB1C | ~120 lines: frame, registers, display-list scheduling |
| func_801C9698 / func_801C90D4 / func_801C80F0 | Same length; register allocation and scheduling |
| func_801C9B14 / func_801ABB20 / func_801CAA00 | Large; branch layout. func_801ABB20 also needs jtbl_802927B0 |

Notes:
- IDO lays out the stack in local-declaration order.
- `addiu tN,$zero,0` pairs are a zeroed u64.
- D_80127D30 should be declared u8[8]. The T034_D_80127D30 #define cast is a stopgap; see FU-13.

Suggested names:
- func_801C86A8/8868: pack/unpack button config
- func_801C8AE0/8C24: pack/unpack high-score names
- func_801C8DBC/8F28: pack/unpack stat levels
- func_801CA7E4/A91C: queue remove/rotate
- func_801CCEAC: convert a Controller Pak name to ASCII
- func_801CBCCC: save thread main
