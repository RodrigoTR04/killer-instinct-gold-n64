/* DRAFT. Remaining diff: Pointer/counter registers and division scheduling differ. */
void func_801BF678(s32 arg0, s32 arg1) {
    s8 *var_v1;
    s32 var_v0;

    var_v1 = (s8 *)(arg0 + 5);
    var_v0 = 5;
    do {
        if ((arg1 != 0) || (var_v0 == 5)) {
            *var_v1 = (arg1 % 10) + 0x30;
        } else {
            *var_v1 = 0x20;
        }
        var_v0 -= 1;
        arg1 = arg1 / 10;
        var_v1 -= 1;
    } while (var_v0 >= 0);
}
