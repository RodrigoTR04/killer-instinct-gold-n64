/* T-022 DRAFT: 287 instruction words differ; compiled 1160 bytes, original 1148 bytes */

extern u8 D_80045088;
extern u8 D_8004A688;
extern u8 D_8004AE88;
extern u8 D_8004AE89;
extern f32 D_800695E0;
extern u8 D_8018FED0;
extern u8 *D_8019B69C;
extern u8 D_801D3430;
extern u8 D_801D5C30;

void func_80018664(void) {
    u8 *var_v1;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 var_f0;
    f32 var_f0_2;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 var_a1;
    s32 var_a1_2;
    u8 temp_t5;
    u8 temp_t7;
    u8 var_a0;
    u8 *temp_v0;

    if ((D_8004A401 == 3) && (D_800698C4 == 0x14)) {
        D_8004AA3C = 0;
        D_8004A730 = 0;
        (*(s8 *)((u8 *)(&D_8004A688) + 0)) = 1;
        (*(s8 *)((u8 *)(&D_8004A688) + 7)) = 0;
        D_8004A738 = 2;
    }
    D_8004AE89 += 1;
    if ((s32) D_8004AE88 >= 0xA) {
        var_a0 = 0x13 - D_8004AE88;
    } else {
        var_a0 = D_8004AE88;
    }
    if (D_8004AE89 == *(&D_80045088 + D_8004AE88)) {
        temp_t7 = D_8004AE88 + 1;
        D_8004AE89 = 0;
        D_8004AE88 = temp_t7;
        if ((temp_t7 & 0xFF) >= 0x14) {
            D_8004AE88 = 0;
        }
    }
    D_8019B69C = (var_a0 << 0xC) + &D_8018FED0;
    if ((s32) D_8004AA2C < 0x78) {
        temp_a0 = 0x3C - D_8004AA2C;
        var_a1 = -temp_a0;
        if (temp_a0 >= 0) {
            var_a1 = temp_a0;
        }
        D_800695E0 = (f32) ((f64) (f32) temp_a0 / (((f64) (f32) var_a1 * 0.25) + 20.0));
    } else {
        temp_a0_2 = D_8004AA2C - 0xB4;
        if (temp_a0_2 >= 0) {
            var_a1_2 = temp_a0_2;
        } else {
            var_a1_2 = 0xB4 - D_8004AA2C;
        }
        D_800695E0 = (f32) ((f64) (f32) temp_a0_2 / (((f64) (f32) var_a1_2 * 0.25) + 20.0));
    }
    temp_t5 = D_8004AA2C + 1;
    D_8004AA2C = temp_t5;
    if ((temp_t5 & 0xFF) >= 0xF0) {
        D_8004AA2C = 0;
    }
    var_v1 = &D_801D3430;
    if (D_8004AA28 == 0) {
        do {
            if ((*(u8 *)((u8 *)(var_v1) + 0)) == 0x3C) {
                temp_f2 = D_800695E0 * 6.0f;
                var_f0 = temp_f2;
                if (temp_f2 > 0.0f) {
                    if (temp_f2 > 5.0f) {
                        var_f0 = 5.0f;
                    }
                } else if (temp_f2 < -5.0f) {
                    var_f0 = -5.0f;
                }
                (*(s16 *)((u8 *)(var_v1) + 0x56)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)(var_v1) + 0x56)) + var_f0);
                *D_8004A860 += (f32) (*(s16 *)((u8 *)(var_v1) + 0x54)) / 256.0f;
                (*(s16 *)((u8 *)(var_v1) + 0x54)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)(var_v1) + 0x54)) - ((*D_8004A860 * 256.0f) / 100.0f));
                *D_8004A920 -= (f32) (*(s16 *)((u8 *)(var_v1) + 0x56)) / 256.0f;
                (*(s16 *)((u8 *)(var_v1) + 0x56)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)(var_v1) + 0x56)) + ((*D_8004A920 * 256.0f) / 100.0f));
            }
            if ((*(u8 *)((u8 *)(var_v1) + 0x100)) == 0x3C) {
                temp_v0 = var_v1 + 0x100;
                temp_f2_2 = D_800695E0 * 6.0f;
                var_f0_2 = temp_f2_2;
                if (temp_f2_2 > 0.0f) {
                    if (temp_f2_2 > 5.0f) {
                        var_f0_2 = 5.0f;
                    }
                } else if (temp_f2_2 < -5.0f) {
                    var_f0_2 = -5.0f;
                }
                (*(s16 *)((u8 *)(temp_v0) + 0x56)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)(temp_v0) + 0x56)) + var_f0_2);
                *D_8004A860 += (f32) (*(s16 *)((u8 *)(temp_v0) + 0x54)) / 256.0f;
                (*(s16 *)((u8 *)(temp_v0) + 0x54)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)(temp_v0) + 0x54)) - ((*D_8004A860 * 256.0f) / 100.0f));
                *D_8004A920 -= (f32) (*(s16 *)((u8 *)(temp_v0) + 0x56)) / 256.0f;
                (*(s16 *)((u8 *)(temp_v0) + 0x56)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)(temp_v0) + 0x56)) + ((*D_8004A920 * 256.0f) / 100.0f));
            }
            var_v1 += 0x200;
        } while (var_v1 != &D_801D5C30);
    }
}
