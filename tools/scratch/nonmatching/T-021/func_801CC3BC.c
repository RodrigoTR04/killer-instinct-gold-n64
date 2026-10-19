/* DRAFT. Remaining diff: Call arguments, stack frame and control/register allocation differ. */
s32 func_800347D0(void *, s32, s32, u8 *);          /* extern */
s32 func_801CBF8C();                       /* extern */
extern u8 D_80295560;
extern u8 D_80295580;
extern u8 D_802955AC;
extern u8 D_802955D4;
extern u8 D_802955F8;
extern u8 D_802D3D30;
extern u8 *D_802D3E04;
extern u8 D_802D3E0D;

s32 func_801CC3BC(s32 arg0, s32 arg1) {
    s32 sp18;
    s32 temp_v0;
    s32 var_a0;
    s32 var_a2;

    var_a0 = arg0;
    var_a2 = 1 << arg1;
    if (!(D_802D3E0D & var_a2)) {
        sp18 = var_a2;
        func_801CBF8C(var_a2, &D_802D3E0D);
        var_a0 = arg0;
        if ((D_802D3E0D == 0) & var_a2) {
            return 1;
        }
    }
    if (var_a0 == 3) {
        sp18 = var_a2;
        temp_v0 = func_800347D0((arg1 * 0x68) + &D_802D3D30, arg1, var_a2, &D_802D3E0D);
        var_a0 = temp_v0;
    }
    if (var_a0 == 2) {
        D_802D3E0D &= var_a2 ^ 0xFF;
        var_a0 = func_801CBF8C(var_a0);
    }
    if (var_a0 == 1) {
        D_802D3E04 = &D_80295560;
        return var_a0;
    }
    if (var_a0 != 0xA) {
        if (var_a0 == 0xB) {
            goto block_13;
        }
        if (var_a0 == 4) {
            D_802D3E04 = &D_802955AC;
            return var_a0;
        }
        if (var_a0 == 7) {
            D_802D3E04 = &D_802955D4;
            return var_a0;
        }
        if (var_a0 == 8) {
            D_802D3E04 = &D_802955F8;
        }
        return var_a0;
    }
block_13:
    D_802D3E04 = &D_80295580;
    return var_a0;
}
