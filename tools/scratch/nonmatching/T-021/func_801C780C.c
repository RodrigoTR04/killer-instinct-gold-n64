/* DRAFT. Remaining diff: Instruction/register/control-flow mismatch; see saved asm-differ output. */
extern s32 func_8002AB40();
extern s32 func_8002AB64();
extern s32 func_801ADC64();
extern s8 D_8029571A;
extern s32 D_802D3678[];
extern u8 D_802D39D5;

void func_801C780C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 *sp1C;
    s32 *var_v0;

    if (((arg3 & 0x1000) && (var_v0 = &D_802D3678[arg0*2], ((var_v0[1] & 0x1000) == 0))) || (var_v0 = &D_802D3678[arg0*2], (D_802D39D5 == 2))) {
        sp1C = var_v0;
        func_801ADC64(3);
        func_8002AB64();
        func_8002AB40();
        D_8029571A = 1;
    }
    var_v0[0] = arg2;
    var_v0[1] = arg3;
}
