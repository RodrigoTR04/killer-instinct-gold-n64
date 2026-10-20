extern u8 D_8004AC88;
extern s8 D_8004AC89;
extern s8 D_8004AC8A;
extern u8 D_8004EA9E[];
/* DRAFT. Remaining diff: 61 linked instruction words; compiled 648 bytes, original 648 bytes. */

s32 func_8001EC74(u8 **, s32, s32, u32, u32, s32, s32, s32); /* extern */
extern u8 D_80046100;
extern u8 D_8004A408;
extern u8 D_8004A450;
extern u8 D_8004CEE8;
extern s16 D_8004D26E;
extern s32 D_8004EA78;
extern u8 D_801D3430;
extern u16 D_801D876C;
extern u8 D_801D8770;
extern u8 D_801D87E0;
extern u8 D_801D87E1;

void func_8001E0B4(u8 **arg0) {
    s32 temp_v0_2;
    s32 temp_v1_2;
    s32 var_s0;
    s32 var_t4;
    u32 var_t1;
    u32 var_t2;
    u8 temp_v0;
    u8 var_v1;
    u8 *temp_t0;
    u8 *temp_t3;
    u8 *temp_v1;

    temp_v1 = *arg0;
    *arg0 = temp_v1 + 8;
    var_s0 = 0;
    (*(s32 *)((u8 *)(temp_v1) + 0)) = 0x06000000;
    (*(u8 **)((u8 *)(temp_v1) + 4)) = &D_80046100;
    do {
        if ((D_801D876C == 0) || (var_s0 != (*(u8 *)((u8 *)(&D_801D8770) + 1)))) {
            temp_t3 = &D_8004A450 + (var_s0 * 0x30);
            if ((*(u16 *)((u8 *)(temp_t3) + 0x22)) != 0xBE) {
                temp_t0 = (var_s0 << 8) + &D_801D3430;
                if ((*(u8 *)((u8 *)(temp_t0) + -0x17C)) == 0) {
                    temp_v1_2 = var_s0 + 1;
                    if (temp_v1_2 != D_8004A408) {
                        D_8004D26E = 0;
                        if ((s32) (*(u8 *)((u8 *)(temp_t3) + 0x21)) >= 0x80) {
                            var_t4 = 1;
                        } else {
                            var_t4 = 0;
                        }
                        var_t2 = (*(u16 *)((u8 *)(temp_t0) + 0x58));
                        D_8004EA78 = var_s0;
                        var_t1 = (*(u16 *)((u8 *)(temp_t0) + 0x5A));
                        if (var_t2 == 0) {
                            var_t2 = 0x1000;
                        }
                        if (var_t1 == 0) {
                            var_t1 = 0x1000;
                        }
                        if (D_8004AC88 == 0) {
                            var_t1 = (u16) ((s32) var_t1 / 2);
                        }
                        if (temp_v1_2 == D_801D87E0) {
                            if (D_801D87E1 != 0) {
                                D_8004D26E = 0x80 - (D_801D87E1 * 2);
                            }
                        } else {
                            D_8004D26E = 0x80;
                        }
                        temp_v0 = (*(u8 *)((u8 *)(temp_t0) + -0x170));
                        if (temp_v0 != 0) {
                            if ((s32) temp_v0 < 0x40) {
                                D_8004D26E = 0x80 - (temp_v0 * 2);
                            } else {
                                D_8004D26E = 0;
                            }
                        }
                        if (*(&D_8004CEE8 + (D_8004EA78 * 0x1C)) != 5) {
                            if (D_8004EA9E[var_s0] == 9) {
                                var_v1 = 1;
                            } else {
                                var_v1 = ((u8)D_8004AC89);
                            }
                            if (!((*(u8 *)((u8 *)(temp_t0) + 0x95)) & 0x10)) {
                                temp_v0_2 = (*(s32 *)((u8 *)(temp_t0) + 0x70));
                                func_8001EC74(arg0, (s32) (*(s32 *)((u8 *)(temp_t0) + 0x68)) / 16, (*(s32 *)((u8 *)(temp_t3) + 0x1C)), (u32) (temp_v0_2 * var_t2) >> 0xC, (u32) (temp_v0_2 * var_t1) >> 0xC, (s32) var_v1, var_t4, (s32) ((u8)D_8004AC8A));
                            }
                        }
                    }
                }
            }
        }
        var_s0 += 1;
    } while (var_s0 != 2);
}
