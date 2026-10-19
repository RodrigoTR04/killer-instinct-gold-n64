/* T-022 DRAFT: 38 instruction words differ; compiled 356 bytes, original 356 bytes */
s32 osMapTLB(s32, s32, s32, s32, s32, s32); /* extern */
s32 osUnmapTLB(s32);                            /* extern */

void func_8001CF1C(void) {
    s32 temp_s4;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s2;
    s32 var_s2_2;
    s32 var_s3;
    s32 var_s3_2;

    var_s0 = 0;
    do {
        osUnmapTLB(var_s0);
        var_s0 += 1;
    } while (var_s0 < 0x1F);
    osMapTLB(0, 0, 0, 0x3A4000, -1, -1);
    var_s3 = 0x1DC000;
    var_s2 = 0x1DB000;
    var_s0_2 = 0;
    var_s1 = 0;
    do {
        temp_s4 = var_s0_2 + 1;
        osMapTLB(temp_s4, 0, ((*(u8 *)((u8 *)(D_8004EA9C) + 0)) << 0x10) + var_s1 + 0x10000, var_s2, var_s3, -1);
        var_s0_2 = temp_s4;
        var_s1 += 0x2000;
        var_s2 += 0x2000;
        var_s3 += 0x2000;
    } while (temp_s4 < 5);
    var_s0_3 = 0;
    var_s1_2 = 0;
    if ((*(u8 *)((u8 *)(D_8004EA9C) + 0)) != (*(u8 *)((u8 *)(D_8004EA9C) + 1))) {
        var_s3_2 = 0x1E6000;
        var_s2_2 = 0x1E5000;
        do {
            osMapTLB(var_s0_3 + 6, 0, ((*(u8 *)((u8 *)(D_8004EA9C) + 1)) << 0x10) + var_s1_2 + 0x10000, var_s2_2, var_s3_2, -1);
            var_s0_3 += 1;
            var_s1_2 += 0x2000;
            var_s2_2 += 0x2000;
            var_s3_2 += 0x2000;
        } while (var_s0_3 != 5);
    }
}
