/* DRAFT. Remaining diff: Instruction/register/control-flow mismatch; see saved asm-differ output. */
extern s32 func_8002F6F4();
extern void func_801C4BD0();
extern u8 D_8004A258;
extern s32 D_80066C40;
extern f32 D_80291EBC;
extern f64 D_802948B8;
extern f32 D_802D3990;
extern u8 D_802D399C;
extern u8 D_802D399E;
extern u8 D_802D39B4;

u32 func_801C6D40(s32 arg0, u32 arg1) {
    f64 var_f6;
    s32 temp_t0;
    s32 var_v1;
    u32 var_a3;
    u8 temp_t3;
    u8 temp_t7;

    var_a3 = arg1;
    if (arg1 < 0xF0U) {
        temp_t7 = D_802D399C + 1;
        var_v1 = temp_t7 & 0xFF;
        D_802D399C = temp_t7;
        if (var_v1 >= 0x11) {
            D_802D399C = 1;
            var_v1 = 1 & 0xFF;
        }
        if ((var_v1 == 1) || (var_v1 == 8)) {
            func_8002F6F4(D_80066C40, 0x2C, &D_8004A258, var_a3);
            var_a3 = arg1;
        }
        temp_t0 = 0xF0 - var_a3;
        var_f6 = (f64) temp_t0;
        if (temp_t0 < 0) {
            var_f6 += 4294967296.0;
        }
        D_802D3990 = (f32) ((f64) D_80291EBC + (var_f6 * D_802948B8));
    } else {
        if (D_802D399E == 1) {
            func_801C4BD0(0x85, var_a3);
        }
        var_a3 = 0xF0;
        temp_t3 = D_802D399C + 2;
        D_802D399C = temp_t3;
        if ((temp_t3 & 0xFF) >= 0x18) {
            D_802D399C = 0x17;
        }
    }
    D_802D39B4 = 1;
    return var_a3;
}
