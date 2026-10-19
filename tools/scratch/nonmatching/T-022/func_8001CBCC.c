/* T-022 DRAFT: 47 instruction words differ; compiled 312 bytes, original 320 bytes */

extern void func_8001CBCC(f32 *, f32, f32, f32);
s32 guMtxIdentF(f32 *);                         /* extern */
extern f32 D_80045C00;

void func_8001CBCC(f32 *arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 sp40;
    f32 sp3C;
    f32 sp34;
    f32 sp30;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f14_2;
    f32 temp_f20;
    f32 temp_f22;

    arg1 *= D_80045C00;
    arg2 *= D_80045C00;
    arg3 *= D_80045C00;
    temp_f20 = sinf(arg1);
    temp_f22 = cosf(arg1);
    sp40 = sinf(arg2);
    sp34 = cosf(arg2);
    sp3C = sinf(arg3);
    sp30 = cosf(arg3);
    guMtxIdentF(arg0);
    temp_f0 = -sp34;
    (*(f32 *)((u8 *)(arg0) + 8)) = sp40;
    temp_f14_2 = temp_f20 * sp40;
    (*(f32 *)((u8 *)(arg0) + 0)) = temp_f0 * sp30;
    (*(f32 *)((u8 *)(arg0) + 4)) = (f32) (temp_f0 * sp3C);
    (*(f32 *)((u8 *)(arg0) + 0x10)) = (f32) ((temp_f14_2 * sp30) - (temp_f22 * sp3C));
    temp_f0_2 = temp_f22 * sp40;
    (*(f32 *)((u8 *)(arg0) + 0x18)) = (f32) (temp_f20 * sp34);
    (*(f32 *)((u8 *)(arg0) + 0x14)) = (f32) ((temp_f14_2 * sp3C) + (temp_f22 * sp30));
    (*(f32 *)((u8 *)(arg0) + 0x20)) = (f32) ((temp_f0_2 * sp30) + (temp_f20 * sp3C));
    (*(f32 *)((u8 *)(arg0) + 0x28)) = (f32) (temp_f22 * sp34);
    (*(f32 *)((u8 *)(arg0) + 0x24)) = (f32) ((temp_f0_2 * sp3C) - (temp_f20 * sp30));
}
