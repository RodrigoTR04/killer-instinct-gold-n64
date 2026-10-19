/* NOT ATTEMPTED. Remaining diff: Preliminary m2c only; unresolved field/type reconstruction. */
extern s32 func_801CBF8C();
s32 func_801CC0CC(u8 *, ?, s32);                     /* extern */
s32 func_801CC350(s32 *, s32);                      /* extern */
extern s32 func_801CC3BC();
s32 func_801CC524(s32, s32, s32);                   /* extern */
extern u8 D_80295618;
extern u8 D_80295628;
extern u8 D_802D3A30;
extern u8 *D_802D3E04;
extern u8 D_802D3E0D;

s32 func_801CC668(s32 arg0) {
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 temp_v1;
    s32 var_a2;
    s32 var_v0;

    temp_v1 = 1 << arg0;
    if (!(D_802D3E0D & temp_v1)) {
        sp24 = temp_v1;
        func_801CBF8C();
        if (!(D_802D3E0D & temp_v1)) {
            return 1;
        }
    }
    D_802D3E04 = &D_80295618;
    var_v0 = func_801CC350(&sp2C, arg0);
    var_a2 = var_v0;
    if (var_v0 != 0) {
        if (var_v0 != 5) {
            func_801CC3BC(var_a2, arg0, var_a2);
            var_v0 = func_801CC350(&sp2C, arg0);
            var_a2 = var_v0;
        } else {
            D_802D3E04 = &D_80295628;
        }
    }
    if (var_v0 == 0) {
        var_v0 = func_801CC524(sp2C, arg0, var_a2);
        var_a2 = var_v0;
        if (var_v0 != 0) {
            func_801CC3BC(var_a2, arg0, var_a2);
            var_v0 = func_801CC524(sp2C, arg0);
            var_a2 = var_v0;
        }
    }
    if (var_v0 == 0) {
        sp28 = var_a2;
        if (func_801CC0CC(&D_802D3A30, 0x300, var_a2) != 0) {
            var_a2 = 1;
        }
    }
    return var_a2;
}
