/* DRAFT. Remaining diff: Global-address initialization is scheduled after the loop-index/pointer setup instead of before it. */
extern void func_801C47E0(s32, s32, void *, u8);
extern void func_801C48E4(s32, u8, s32);
extern u8 D_800F4070;
extern s8 D_801CD454;
extern s32 D_802956F8, D_802956FC, D_80295700;
extern u8 D_802C8724;
s32 func_801B17BC(u8 arg0, s8 arg1, s8 arg2) {
    u8 colors[3];
    s32 i;
    u8 *p;
    u8 color;
    colors[0] = arg0;
    colors[1] = arg1;
    colors[2] = arg2;
    D_802C8724 = 0;
    i = 0;
    p = colors;
    do {
        color = *p;
        if (color == 8) D_802C8724 |= 1 << i;
        func_801C47E0((color + 0x80) & 0xFF, 0, &D_800F4070, color);
        func_801C48E4(i, *p, 1);
        i++;
        p++;
    } while (i != 3);
    D_801CD454 = 0;
    D_80295700 = 0;
    D_802956FC = 0;
    D_802956F8 = 0;
    return 0;
}
