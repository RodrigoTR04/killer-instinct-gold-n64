/* DRAFT. Remaining diff: Instruction/register/control-flow mismatch; see saved asm-differ output. */
extern s32 func_8002A8C4();
extern s32 func_8002F6F4();
extern void func_801C4BD0();
extern u8 D_8004A258;
extern f32 D_8004AC84;
extern s32 D_80066C40;
extern u32 D_802921D4;
extern u8 D_802D3984;
extern u8 D_802D399C;
extern u8 D_802D399D;
extern u8 D_802D399E;

u32 func_801C6A80(s32 arg0, u32 arg1) {
    s32 temp_v0;
    u32 var_v0;
    u8 temp_t9;

    if (arg1 < 0xF0U) {
        temp_t9 = D_802D399C + D_802D399D;
        temp_v0 = temp_t9 & 0xFF;
        D_802D399C = temp_t9;
        if (temp_v0 >= 0xB) {
            D_802D399D = 0xFF;
            if (D_802D3984 == 0) {
                D_802D3984 += 1;
                func_8002A8C4(&D_802D399D);
            }
        } else if (temp_v0 < 2) {
            D_802D399D = 1;
        }
    } else {
        if (D_802D399E == 0) {
            func_801C4BD0(0x84);
        }
        var_v0 = D_802921D4;
        D_802D399C = (u8) (var_v0 >> 8);
        if ((arg1 < 0x168U) || (var_v0 != 0x900)) {
            var_v0 += 0x80;
        }
        if (var_v0 >= 0xA01U) {
            var_v0 = 0x700;
        }
        D_802921D4 = var_v0;
        if (var_v0 == 0x930) {
            func_8002F6F4(D_80066C40, 0x1A, &D_8004A258);
        }
    }
    D_8004AC84 = 40.0f;
    return arg1;
}
