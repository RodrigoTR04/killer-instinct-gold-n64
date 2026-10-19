/* DRAFT. Remaining diff: Search-loop global base, registers and initial load/control flow differ. */
extern u8 D_80127D30;

void func_801CA784(s32 arg0) {
    s32 var_v0;
    u8 *var_v1;
    u8 var_a0;

    var_v0 = 0;
    if (D_80127D30 != 0) {
        var_v1 = &D_80127D30;
        var_a0 = D_80127D30;
loop_2:
        var_v0 += 1;
        if (arg0 != var_a0) {
            var_v1 += 1;
            if ((var_v0 >= 7) || (var_a0 = *var_v1, (var_a0 == 0))) {
                goto block_5;
            }
            goto loop_2;
        }
    } else {
block_5:
        if (var_v0 < 8) {
            (&D_80127D30)[var_v0] = arg0;
        }
    }
}
