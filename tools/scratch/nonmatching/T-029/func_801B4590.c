/* DRAFT. Remaining diff: Byte argument is saved twice; frame is 0x28 instead of 0x20; registers differ. */
extern void func_801AC95C(u8 *, s32);
extern u8 D_80127CE8[];
extern u8 D_80127CFE[];
extern u8 D_802C8D06;
extern u8 D_802C8CE0;
extern u8 D_802C8CEA[];
extern s8 D_802C8D0F;
void func_801B4590(u8 arg0) {
    u8 *entry;
    if (D_802C8D06 & 8) {
        arg0 = arg0 & 0xFF;
        entry = &D_80127CFE[arg0];
        func_801AC95C(&D_80127CE8[arg0 * 11], *entry);
        D_802C8CE0 |= 1 << arg0;
        if (D_8004A407 & (1 << (1 - arg0))) D_802C8D0F = 1;
        D_802C8CEA[arg0] = *entry + 16;
    }
}
