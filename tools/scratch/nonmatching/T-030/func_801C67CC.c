/* T-087: zero masked instruction differences; integration blocked by asm-owned rodata. */
extern void func_801C4C64(f32 *, f32 *);
extern void func_801C4BD0();
extern f32 D_80291F10[], D_80291F40[];
extern f64 D_802948A0, D_802948A8, D_802948B0;

extern u8 D_802D399C, D_802D399D, D_802D399E, D_802D39B4;

s32 func_801C67CC(s32 arg0, u32 arg1) {

    f32 temp_f0;




    s32 temp_v0;






    if (arg1 >= 0xF1U) {


        if (360.0 < (f64)arg1) {
            if (D_802D39B4 != 0xFF) {

                func_801C4C64(D_80291F10, D_80291F40);

                D_802D39B4 = 0xFF;
            }
            return (u32)((f64)arg1 - 360.0);
        }
        if (D_802D399E == 0) {

            func_801C4BD0(0xD);
            D_802D399D = 2;
        }
        temp_v0 = (D_802D399C += D_802D399D);
        if (temp_v0 >= 8) {
            if (temp_v0 >= 0x22) {
                D_802D399C = 0xD;
            } else if (temp_v0 >= 0xC) {
                D_802D399D = 3;
            }
            D_802D3990.x = (f32) (D_80291E8C[0].x - (((f32) arg1 - 240.0f) * 3.0f));
            temp_f0 = (f32) ((f64)arg1 - 372.0) / 120.0f;
            D_802D3990.y = (f32) (D_80291E8C[0].y + ((-temp_f0 * temp_f0 * 200.0f) + 200.0f));
        }
        arg1 = 0x1E0 - arg1;
        goto block_25;
    }
    temp_v0 = (D_802D399C += D_802D399D);
    if (temp_v0 >= 0x15) {
        D_802D399D = 0xFF;
    } else if (temp_v0 < 2) {
        D_802D399D = 1;
    }
block_25:
    D_802D39B4 = 1;
    return (s32) arg1;
}
