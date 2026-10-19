/* DRAFT. Remaining diff: Instruction/register/control-flow mismatch; see saved asm-differ output. */
s32 __osContDataCrc();

s32 func_801CC0CC(s32 arg0, s32 arg1) {
    s32 temp_s1;
    s32 temp_t0;
    s32 temp_t6;
    s32 var_s0;
    s32 var_s1;
    s32 var_s4;
    u8 temp_t3;

    temp_t6 = (s32) (arg1 + 0x7F) >> 7;
    var_s4 = 0;
    if ((temp_t6 - 1) > 0) {
loop_2:
        var_s1 = 0;
        var_s0 = 0;
        do {
            temp_s1 = var_s1 + __osContDataCrc((var_s4 << 6) + arg0 + (var_s0 << 5));
            var_s0 += 1;
            temp_t0 = temp_s1 & 0xFF;
            var_s1 = temp_t0;
        } while (var_s0 != 4);
        temp_t3 = *(u8 *)((arg1 - temp_t6) + var_s4 + arg0 + 1);
        var_s4 += 1;
        if (temp_t0 != temp_t3) {
            return 1;
        }
        if (var_s4 >= (temp_t6 - 1)) {
            goto block_7;
        }
        goto loop_2;
    }
block_7:
    return 0;
}
