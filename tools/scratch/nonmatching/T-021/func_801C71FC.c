/* DRAFT. Remaining diff: Argument spills, indexing and register allocation differ. */
extern void func_801C4D6C();
extern u8 D_80295720;
extern s32 D_802D3678[];
extern s32 D_802D367C[];
extern s8 D_802D39B6;
extern u8 D_802D39BA;

void func_801C71FC(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_t2;

    if (((arg0 + 1) == D_80295720) && (arg3 & 0x1000) && !(D_802D367C[arg0 * 2] & 0x1000)) {
        if (D_802D39BA & 3) {
            D_802D39BA &= 0xFC;
            func_801C4D6C();
        } else {
            D_802D39BA = 0;
        }
        D_802D39B6 = 1;
    }
    temp_t2 = arg0 * 8;
    D_802D3678[temp_t2 / 4] = arg2;
    D_802D367C[temp_t2 / 4] = arg3;
}
