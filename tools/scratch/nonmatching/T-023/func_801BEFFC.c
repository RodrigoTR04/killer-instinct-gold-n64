/* DRAFT. Remaining diff: Saved score/value pointer registers are exchanged; global-address setup differs. */
extern void func_801BE910(s32 *, s32, s32, s32);
extern s32 func_801BEEA4(s32, s32, s32);
extern s32 func_801BF0E8(s32 *, s32, s32);
extern s32 D_80127E50;
extern s32 D_80127EA0;
extern s32 D_80127EF0;
extern s32 D_80127F40;
extern s32 D_802D36D0;
extern s32 D_802D3748;

void func_801BEFFC(void) {
    s32 *var_s1;
    s32 *var_s2;
    s32 temp_s3;
    s32 var_s0;

    temp_s3 = func_801BF0E8(&D_80127F40, 0xA, func_801BF0E8(&D_80127EF0, 0xA, func_801BF0E8(&D_80127EA0, 0xA, 0)));
    func_801BE910(&D_80127E50, 0xA, 0, 0);
    var_s0 = 0;
    if (temp_s3 > 0) {
        var_s2 = &D_802D36D0;
        var_s1 = &D_802D3748;
        do {
            func_801BEEA4(0, *var_s1, *var_s2);
            var_s0 += 1;
            var_s1 += 1;
            var_s2 += 1;
        } while (var_s0 != temp_s3);
    }
    if (var_s0 < 0xA) {
        do {
            func_801BEEA4(0, 1, 0);
            var_s0 += 1;
        } while (var_s0 < 0xA);
    }
}
