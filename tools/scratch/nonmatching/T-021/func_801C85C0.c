/* DRAFT. Remaining diff: Saved pointer register assignment and loop scheduling differ. */
extern void func_801C7E98();
extern s32 D_80127D00;
extern s8 D_80127D20;
extern s8 D_80127D28;
extern u8 D_80127D30;

void func_801C85C0(void) {
    s32 *var_s3;
    s32 var_s0;
    s8 *var_s1;
    s8 *var_s2;
    u8 *var_s4;

    var_s4 = &D_80127D30;
    var_s3 = &D_80127D00;
    var_s2 = &D_80127D28;
    var_s1 = &D_80127D20;
    var_s0 = 0;
    do {
        *var_s1 = 0;
        *var_s2 = 0;
        *var_s3 = 0;
        *var_s4 = 0;
        func_801C7E98(0, (var_s0 + 2) & 0xFF);
        var_s0 += 1;
        var_s1 += 1;
        var_s2 += 1;
        var_s3 += 1;
        var_s4 += 1;
    } while (var_s0 != 8);
}
