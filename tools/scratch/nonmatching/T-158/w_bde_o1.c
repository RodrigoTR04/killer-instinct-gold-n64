/* T-109 DRAFT: 8 differing words, 316/316 B. Preserve the threshold, then reuse the incoming float as the scale. FP allocation remains. */
extern u8 D_8004AA28;
extern u8 D_8004AC88;
extern u8 D_8004AA28, D_8004AC88;
void func_8001BF1C(u8 **, s32, s32, f32);
extern f32 D_800489F0;
extern f32 D_800489F4;
extern u8 D_8004A4C8;
extern u8 D_801D7E00;
extern u8 D_801D8550;
void func_8001BDE0(u8 **arg0, s32 arg1, f32 arg2) { u8 *var_s1; f32 temp_f0; f32 temp_f0_2; f32 threshold;
    f32 temp_f24; f32 new_var3; f32 new_var4; s32 var_s0; u8 *temp_v1;
    threshold = arg2; if (D_8004AA28 != 1) { temp_v1 = *arg0;
        *arg0 += 8; (*(s32 *)((u8 *)(temp_v1) + 0)) = 0x06000000; (*(s32 *)((u8 *)(temp_v1) + 4)) = (s32) *(s32 *)((u8 *)&D_8004A4C8 + arg1 * 0xC); temp_f24 = D_800489F0; new_var3 = D_800489F4; arg2 = new_var3;
        var_s1 = &D_801D7E00;
        var_s0 = 0;
        loop_2:
        temp_f0 = ((*(f32 *)((u8 *)(var_s1) + 0xF0)) * arg2) - temp_f24;
        if (temp_f0 <= threshold) { func_8001BF1C(arg0, arg1, var_s0, temp_f0);
            var_s0 += 1; var_s1 += 0x30;
            if (var_s0 < 0x28) {
                goto loop_2; } }
        var_s1 = &D_801D8550;
        var_s0 = 0x27; loop_5:
        temp_f0_2 = ((*(f32 *)((u8 *)(var_s1) + 0xF0)) * arg2) - temp_f24;
        if (threshold < temp_f0_2) {
            func_8001BF1C(arg0, arg1, var_s0, temp_f0_2); var_s0 -= 1; var_s1 -= 0x30;
            if (var_s0 >= 0) {
                goto loop_5;
            }
        }
    }
}
