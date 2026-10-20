/* T-050: retained improvement; 88 differing words including size penalty, 364 compiled bytes. Full function remains nonmatching. */
/* DRAFT. Remaining diff: Call arguments, stack frame and control/register allocation differ. */
s32 osPfsChecker(void *);          /* extern */
s32 func_801CBF8C(void);                       /* extern */
extern u8 D_80295560;
extern u8 D_80295580;
extern u8 D_802955AC;
extern u8 D_802955D4;
extern u8 D_802955F8;
extern u8 D_802D3D30;
extern u8 *D_802D3E04;
extern u8 D_802D3E0D;

s32 func_801CC3BC(s32 arg0, s32 arg1) {
    s32 var_a2;

    var_a2 = 1 << arg1;
    if (!(D_802D3E0D & var_a2)) {
        func_801CBF8C();
        if ((D_802D3E0D == 0) & var_a2) {
            return 1;
        }
    }
    if (arg0 == 3) {
        arg0 = osPfsChecker((arg1 * 0x68) + &D_802D3D30);
    }
    if (arg0 == 2) {
        D_802D3E0D &= var_a2 ^ 0xFF;
        arg0 = func_801CBF8C();
    }
    if (arg0 == 1) {
        D_802D3E04 = &D_80295560;
        return arg0;
    }
    if (arg0 != 0xA) {
        if (arg0 == 0xB) {
            goto block_13;
        }
        if (arg0 == 4) {
            D_802D3E04 = &D_802955AC;
            return arg0;
        }
        if (arg0 == 7) {
            D_802D3E04 = &D_802955D4;
            return arg0;
        }
        if (arg0 == 8) {
            D_802D3E04 = &D_802955F8;
        }
        return arg0;
    }
block_13:
    D_802D3E04 = &D_80295580;
    return arg0;
}
