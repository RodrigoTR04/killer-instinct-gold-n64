/* T-022 DRAFT: 195 instruction words differ; compiled 812 bytes, original 636 bytes */


extern u8 D_8004AC8E;
extern u8 D_8004AC92;
extern u8 D_8004AC95;
extern u8 D_801D7DF8;
extern u8 D_801D7DFC;

void func_8001BB64(u8 **arg0) {
    s16 colors[3];
    s16 *var_a3;
    s16 var_a3_2;
    s16 var_a3_3;
    s16 var_v0_2;
    s16 var_v1_2;
    s16 var_v1_3;
    s32 temp_a1;
    s32 var_v1;
    u8 *var_t0;
    u8 temp_t8;
    u8 var_a1;
    u8 var_v0;
    u8 *temp_a2;
    u8 *temp_a2_2;
    u8 *temp_a2_3;
    u8 *temp_a2_4;

    if (D_8004AA28 == 0) {
        var_v1 = 0;
        if ((s32) D_801D7DFC > 0) {
            var_v1 = ((D_801D7DFC * 4) - 1) & 0xFF;
        }
        var_v0 = (*(u8 *)((u8 *)(&D_801D7DF8) + 0));
        var_a1 = (*(u8 *)((u8 *)(&D_801D7DF8) + 1));
    } else {
        var_v1 = 0;
        var_v0 = 0;
        var_a1 = 0;
    }
    var_t0 = &D_8004AC92;
    var_a3 = &colors[0];
    do {
        temp_t8 = *var_t0;
        var_t0 += 1;
        *var_a3 = temp_t8 + var_v1;
        if (*var_a3 >= 0x80) {
            *var_a3 = 0x7F;
        }
        var_a3 += 1;
    } while (var_t0 != &D_8004AC95);
    temp_a2 = *arg0;
    *arg0 = temp_a2 + 8;
    (*(s32 *)((u8 *)(temp_a2) + 0)) = 0xFB000000;
    (*(s32 *)((u8 *)(temp_a2) + 4)) = (s32) (((colors[2] & 0xFF) << 8) | (colors[0] << 0x18) | ((colors[1] & 0xFF) << 0x10));
    switch (var_a1) {                               /* irregular */
    case 2:
        var_v1_2 = (*(u8 *)((u8 *)(&D_8004AC8E) + 2)) + (var_v0 * 4);
        if (var_v1_2 >= 0x80) {
            var_v1_2 = 0x7F;
        }
        temp_a2_2 = *arg0;
        *arg0 = temp_a2_2 + 8;
        (*(s32 *)((u8 *)(temp_a2_2) + 0)) = 0xFA000100;
        (*(s32 *)((u8 *)(temp_a2_2) + 4)) = (s32) (((*(u8 *)((u8 *)(&D_8004AC8E) + 1)) << 0x10) | ((*(u8 *)((u8 *)(&D_8004AC8E) + 0)) << 0x18) | ((var_v1_2 & 0xFF) << 8) | 0xFF);
        return;
    case 1:
    case 4:
        temp_a1 = var_v0 * 4;
        var_a3_2 = (*(u8 *)((u8 *)(&D_8004AC8E) + 0)) + temp_a1;
        if (var_a3_2 >= 0x80) {
            var_a3_2 = 0x7F;
        }
        var_v0_2 = (*(u8 *)((u8 *)(&D_8004AC8E) + 1)) + temp_a1;
        if (var_v0_2 >= 0x80) {
            var_v0_2 = 0x7F;
        }
        var_v1_3 = (*(u8 *)((u8 *)(&D_8004AC8E) + 2)) + temp_a1;
        if (var_v1_3 >= 0x80) {
            var_v1_3 = 0x7F;
        }
        temp_a2_3 = *arg0;
        *arg0 = temp_a2_3 + 8;
        (*(s32 *)((u8 *)(temp_a2_3) + 0)) = 0xFA000100;
        (*(s32 *)((u8 *)(temp_a2_3) + 4)) = (s32) ((var_a3_2 << 0x18) | ((var_v0_2 & 0xFF) << 0x10) | ((var_v1_3 & 0xFF) << 8) | 0xFF);
        return;
    default:
        var_a3_3 = (*(u8 *)((u8 *)(&D_8004AC8E) + 0)) + (var_v0 * 4);
        if (var_a3_3 >= 0x80) {
            var_a3_3 = 0x7F;
        }
        temp_a2_4 = *arg0;
        *arg0 = temp_a2_4 + 8;
        (*(s32 *)((u8 *)(temp_a2_4) + 0)) = 0xFA000100;
        (*(s32 *)((u8 *)(temp_a2_4) + 4)) = (s32) (((*(u8 *)((u8 *)(&D_8004AC8E) + 2)) << 8) | (var_a3_3 << 0x18) | ((*(u8 *)((u8 *)(&D_8004AC8E) + 1)) << 0x10) | 0xFF);
        return;
    }
}
