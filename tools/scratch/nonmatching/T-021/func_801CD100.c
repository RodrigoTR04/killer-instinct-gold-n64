/* DRAFT. Remaining diff: Same size; counter/pointer registers and division scheduling differ. */
void func_801CD100(s8 *arg0, u32 arg1) {
    s32 var_v0;
    s8 *var_v1;



    var_v1 = arg0 + 3;
    var_v0 = 3;
    do {
        if ((var_v0 != 3) && (arg1 == 0)) {
            *var_v1 = 0x20;
        } else {
            *var_v1 = (arg1 % 10U) + 0x30;
        }
        var_v0 -= 1;
        arg1 = arg1 / 10U;
        var_v1 -= 1;
    } while (var_v0 >= 0);
}
