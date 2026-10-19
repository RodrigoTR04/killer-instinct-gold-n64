/* DRAFT. Remaining diff: Two pairs of global-address addiu instructions are reversed; otherwise text matches. */
extern u8 *func_801BF788(u8 *, u8 *, s32);
extern u8 D_80127EA0;
extern u8 D_80127EF0;
extern u8 D_80127F40;
extern u8 D_80127F90;
extern u8 D_80128148;
extern u8 D_80128300;

void func_801BF850(u8 *arg0) {
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *var_s0;
    u8 *var_s0_2;
    u8 *var_s1;

    var_s1 = func_801BF788(func_801BF788(func_801BF788(arg0, &D_80127EA0, 10), &D_80127EF0, 0xA), &D_80127F40, 0xA);
    var_s0 = &D_80127F90;
    do {
        temp_v0 = func_801BF788(var_s1, var_s0, 5);
        var_s0 += 0x28;
        var_s1 = temp_v0;
    } while ((u32) var_s0 < (u32) &D_80128148);
    var_s0_2 = &D_80128148;
    do {
        temp_v0_2 = func_801BF788(var_s1, var_s0_2, 5);
        var_s0_2 += 0x28;
        var_s1 = temp_v0_2;
    } while (var_s0_2 != &D_80128300);
}
