/* DRAFT (T-047). See T-047/REPORT.md for comparison counts and remaining differences. */
extern s32 func_8002AB40();
extern s32 func_8002AB64();
extern s32 func_801ADC64();
extern s8 D_8029571A;
extern s32 D_802D3678[];
extern u8 D_802D39D5;

void func_801C780C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {

    if (((arg3 & 0x1000) && !(D_802D3678[arg0 * 2 + 1] & 0x1000)) || D_802D39D5 == 2) {
        func_801ADC64(3);
        func_8002AB64();
        func_8002AB40();
        D_8029571A = 1;
    }
    D_802D3678[arg0 * 2] = arg2;
    D_802D3678[arg0 * 2 + 1] = arg3;
}
