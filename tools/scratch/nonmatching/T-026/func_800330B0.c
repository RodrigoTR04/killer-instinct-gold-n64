/* DRAFT. Remaining diff: 499 differing instruction words; emitted 2012 / original 1900 bytes (positional comparison). */
/* Recovered matrix (float), light (byte), and reflection (s32) layouts. */
extern void guMtxIdentF(void *);                                    /* extern */
extern f32 sqrtf();                                /* extern */
extern f64 D_80049000;
extern f64 D_80049008;
extern f64 D_80049010;

void func_800330B0(void *arg0, void *arg1, void *arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10, f32 arg11, f32 arg12, f32 arg13, f32 arg14, f32 arg15, f32 arg16, f32 arg17, s32 arg18, s32 arg19) {
    f32 sp88;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 temp_f0;
    f32 temp_f10;
    f32 temp_f10_2;
    f32 temp_f10_3;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f14;
    f32 temp_f14_2;
    f32 temp_f14_3;
    f32 temp_f14_4;
    f32 temp_f16;
    f32 temp_f16_2;
    f32 temp_f16_3;
    f32 temp_f18;
    f32 temp_f18_2;
    f32 temp_f18_3;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f22_2;
    f32 temp_f24;
    f32 temp_f24_2;
    f32 temp_f26;
    f32 temp_f26_2;
    f32 temp_f28;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f2_4;
    f32 temp_f2_6;
    f32 temp_f30;
    f32 temp_f30_2;
    f32 temp_f4;
    f32 temp_f4_2;
    f32 temp_f4_3;
    f32 temp_f6;
    f32 temp_f6_2;
    f32 temp_f6_3;
    f32 temp_f6_4;
    f32 temp_f8;
    f32 temp_f8_2;
    f64 temp_f12_3;
    f64 temp_f12_4;
    f64 temp_f12_5;
    f64 temp_f12_6;
    f64 temp_f12_7;
    f64 temp_f12_8;
    f64 temp_f2_5;
    f64 temp_f2_7;
    f64 var_f0;
    f64 var_f0_2;
    f64 var_f0_3;
    f64 var_f0_4;
    f64 var_f0_5;
    f64 var_f0_6;

    guMtxIdentF(arg0);
    temp_f0 = arg6 - arg3;
    temp_f30 = arg7 - arg4;
    temp_f14 = arg8 - arg5;
    sp88 = temp_f14;
    temp_f2 = (f32) (-1.0 / (f64) sqrtf((temp_f0 * temp_f0) + (temp_f30 * temp_f30) + (temp_f14 * temp_f14), temp_f14));
    temp_f28 = temp_f0 * temp_f2;
    temp_f30_2 = temp_f30 * temp_f2;
    temp_f20 = sp88 * temp_f2;
    sp88 = temp_f20;
    temp_f22 = (arg10 * temp_f20) - (arg11 * temp_f30_2);
    temp_f24 = (arg11 * temp_f28) - (arg9 * temp_f20);
    temp_f26 = (arg9 * temp_f30_2) - (arg10 * temp_f28);
    temp_f2_2 = (f32) (1.0 / (f64) sqrtf((temp_f22 * temp_f22) + (temp_f24 * temp_f24) + (temp_f26 * temp_f26)));
    temp_f22_2 = temp_f22 * temp_f2_2;
    temp_f24_2 = temp_f24 * temp_f2_2;
    temp_f26_2 = temp_f26 * temp_f2_2;
    temp_f14_2 = (temp_f30_2 * temp_f26_2) - (sp88 * temp_f24_2);
    arg9 = temp_f14_2;
    temp_f16 = (sp88 * temp_f22_2) - (temp_f28 * temp_f26_2);
    arg10 = temp_f16;
    temp_f18 = (temp_f28 * temp_f24_2) - (temp_f30_2 * temp_f22_2);
    arg11 = temp_f18;
    temp_f2_3 = (f32) (1.0 / (f64) sqrtf((temp_f14_2 * temp_f14_2) + (temp_f16 * temp_f16) + (temp_f18 * temp_f18)));
    arg9 *= temp_f2_3;
    arg10 *= temp_f2_3;
    arg11 *= temp_f2_3;
    temp_f2_4 = (f32) (1.0 / (f64) sqrtf((arg12 * arg12) + (arg13 * arg13) + (arg14 * arg14)));
    temp_f10 = arg12 * temp_f2_4;
    temp_f8 = arg13 * temp_f2_4;
    arg12 = temp_f10;
    temp_f6 = arg14 * temp_f2_4;
    temp_f4 = temp_f10 + temp_f28;
    arg13 = temp_f8;
    temp_f10_2 = temp_f8 + temp_f30_2;
    arg14 = temp_f6;
    sp5C = temp_f4;
    temp_f6_2 = temp_f6 + sp88;
    sp58 = temp_f10_2;
    sp54 = temp_f6_2;
    temp_f2_5 = (f64) sqrtf((temp_f4 * temp_f4) + (temp_f10_2 * temp_f10_2) + (temp_f6_2 * temp_f6_2));
    if (D_80049000 < temp_f2_5) {
        temp_f12 = (f32) (1.0 / temp_f2_5);
        temp_f14_3 = sp5C * temp_f12;
        temp_f16_2 = sp58 * temp_f12;
        temp_f18_2 = sp54 * temp_f12;
        (*(s32 *)((u8 *)arg2 + 0x0)) = (s32) ((f32) (arg18 * 4) + (((temp_f14_3 * temp_f22_2) + (temp_f16_2 * temp_f24_2) + (temp_f18_2 * temp_f26_2)) * (f32) arg18 * 2.0f));
        (*(s32 *)((u8 *)arg2 + 0x4)) = (s32) ((f32) (arg19 * 4) + (((temp_f14_3 * arg9) + (temp_f16_2 * arg10) + (temp_f18_2 * arg11)) * (f32) arg19 * 2.0f));
    } else {
        (*(s32 *)((u8 *)arg2 + 0x0)) = (s32) (arg18 * 2);
        (*(s32 *)((u8 *)arg2 + 0x4)) = (s32) (arg19 * 2);
    }
    temp_f2_6 = (f32) (1.0 / (f64) sqrtf((arg15 * arg15) + (arg16 * arg16) + (arg17 * arg17)));
    temp_f4_2 = arg15 * temp_f2_6;
    temp_f8_2 = arg16 * temp_f2_6;
    arg15 = temp_f4_2;
    temp_f6_3 = arg17 * temp_f2_6;
    temp_f10_3 = temp_f4_2 + temp_f28;
    arg16 = temp_f8_2;
    temp_f4_3 = temp_f8_2 + temp_f30_2;
    arg17 = temp_f6_3;
    sp5C = temp_f10_3;
    temp_f6_4 = temp_f6_3 + sp88;
    sp58 = temp_f4_3;
    sp54 = temp_f6_4;
    temp_f2_7 = (f64) sqrtf((temp_f10_3 * temp_f10_3) + (temp_f4_3 * temp_f4_3) + (temp_f6_4 * temp_f6_4));
    if (D_80049008 < temp_f2_7) {
        temp_f12_2 = (f32) (1.0 / temp_f2_7);
        temp_f14_4 = sp5C * temp_f12_2;
        temp_f16_3 = sp58 * temp_f12_2;
        temp_f18_3 = sp54 * temp_f12_2;
        (*(s32 *)((u8 *)arg2 + 0x8)) = (s32) ((f32) (arg18 * 4) + (((temp_f14_4 * temp_f22_2) + (temp_f16_3 * temp_f24_2) + (temp_f18_3 * temp_f26_2)) * (f32) arg18 * 2.0f));
        (*(s32 *)((u8 *)arg2 + 0xC)) = (s32) ((f32) (arg19 * 4) + (((temp_f14_4 * arg9) + (temp_f16_3 * arg10) + (temp_f18_3 * arg11)) * (f32) arg19 * 2.0f));
    } else {
        (*(s32 *)((u8 *)arg2 + 0x8)) = (s32) (arg18 * 2);
        (*(s32 *)((u8 *)arg2 + 0xC)) = (s32) (arg19 * 2);
    }
    temp_f12_3 = (f64) temp_f22_2 * 128.0;
    if (temp_f12_3 < D_80049010) {
        var_f0 = temp_f12_3;
    } else {
        var_f0 = D_80049010;
    }
    temp_f12_4 = (f64) temp_f24_2 * 128.0;
    (*(s8 *)((u8 *)arg1 + 0x8)) = (s8) (s32) var_f0;
    if (temp_f12_4 < D_80049010) {
        var_f0_2 = temp_f12_4;
    } else {
        var_f0_2 = D_80049010;
    }
    temp_f12_5 = (f64) temp_f26_2 * 128.0;
    (*(s8 *)((u8 *)arg1 + 0x9)) = (s8) (s32) var_f0_2;
    if (temp_f12_5 < D_80049010) {
        var_f0_3 = temp_f12_5;
    } else {
        var_f0_3 = D_80049010;
    }
    (*(s8 *)((u8 *)arg1 + 0xA)) = (s8) (s32) var_f0_3;
    temp_f12_6 = (f64) arg9 * 128.0;
    if (temp_f12_6 < D_80049010) {
        var_f0_4 = temp_f12_6;
    } else {
        var_f0_4 = D_80049010;
    }
    (*(s8 *)((u8 *)arg1 + 0x18)) = (s8) (s32) var_f0_4;
    temp_f12_7 = (f64) arg10 * 128.0;
    if (temp_f12_7 < D_80049010) {
        var_f0_5 = temp_f12_7;
    } else {
        var_f0_5 = D_80049010;
    }
    (*(s8 *)((u8 *)arg1 + 0x19)) = (s8) (s32) var_f0_5;
    temp_f12_8 = (f64) arg11 * 128.0;
    if (temp_f12_8 < D_80049010) {
        var_f0_6 = temp_f12_8;
    } else {
        var_f0_6 = D_80049010;
    }
    (*(s8 *)((u8 *)arg1 + 0x0)) = 0;
    (*(s8 *)((u8 *)arg1 + 0x1)) = 0;
    (*(s8 *)((u8 *)arg1 + 0x2)) = 0;
    (*(s8 *)((u8 *)arg1 + 0x3)) = 0;
    (*(s8 *)((u8 *)arg1 + 0x4)) = 0;
    (*(s8 *)((u8 *)arg1 + 0x5)) = 0;
    (*(s8 *)((u8 *)arg1 + 0x6)) = 0;
    (*(s8 *)((u8 *)arg1 + 0x7)) = 0;
    (*(s8 *)((u8 *)arg1 + 0x10)) = 0;
    (*(s8 *)((u8 *)arg1 + 0x11)) = 0x80;
    (*(s8 *)((u8 *)arg1 + 0x12)) = 0;
    (*(s8 *)((u8 *)arg1 + 0x13)) = 0;
    (*(s8 *)((u8 *)arg1 + 0x14)) = 0;
    (*(s8 *)((u8 *)arg1 + 0x15)) = 0x80;
    (*(s8 *)((u8 *)arg1 + 0x16)) = 0;
    (*(s8 *)((u8 *)arg1 + 0x17)) = 0;
    (*(s8 *)((u8 *)arg1 + 0x1A)) = (s8) (s32) var_f0_6;
    (*(f32 *)((u8 *)arg0 + 0x0)) = temp_f22_2;
    (*(f32 *)((u8 *)arg0 + 0x10)) = temp_f24_2;
    (*(f32 *)((u8 *)arg0 + 0x20)) = temp_f26_2;
    (*(f32 *)((u8 *)arg0 + 0x4)) = arg9;
    (*(f32 *)((u8 *)arg0 + 0x14)) = arg10;
    (*(f32 *)((u8 *)arg0 + 0x24)) = arg11;
    (*(f32 *)((u8 *)arg0 + 0x30)) = (f32) -((arg3 * temp_f22_2) + (arg4 * temp_f24_2) + (arg5 * temp_f26_2));
    (*(f32 *)((u8 *)arg0 + 0x34)) = (f32) -((arg3 * arg9) + (arg4 * arg10) + (arg5 * arg11));
    (*(f32 *)((u8 *)arg0 + 0x8)) = temp_f28;
    (*(f32 *)((u8 *)arg0 + 0x18)) = temp_f30_2;
    (*(f32 *)((u8 *)arg0 + 0xC)) = 0.0f;
    (*(f32 *)((u8 *)arg0 + 0x1C)) = 0.0f;
    (*(f32 *)((u8 *)arg0 + 0x2C)) = 0.0f;
    (*(f32 *)((u8 *)arg0 + 0x28)) = sp88;
    (*(f32 *)((u8 *)arg0 + 0x3C)) = 1.0f;
    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) -((arg3 * temp_f28) + (arg4 * temp_f30_2) + (arg5 * sp88));
}
