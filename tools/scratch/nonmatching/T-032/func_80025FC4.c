/* DRAFT. Remaining diff: 456 positional words differ; 1896/1908 bytes */
typedef struct { u32 w0,w1; } T032Gfx25F;
extern u32 osVirtualToPhysical(void *);
extern void *D_8004D020,*D_8004D03C,*D_8004D040,*D_8004D058;
extern u8 D_80047DD0[],D_8004A40C,D_8004D26C,D_801D87FE;
extern u8 D_80061494[2];
extern s32 D_8004EA78;
void func_80025FC4(T032Gfx25F **arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4) {
    s32 sp98;
    s32 sp94;
    s32 sp90;
    s32 sp8C;
    s32 sp88;
    s32 sp84;
    s32 sp80;
    s32 sp7C;
    s32 sp78;
    T032Gfx25F *sp64;
    T032Gfx25F *sp60;
    T032Gfx25F *sp58;
    T032Gfx25F *sp54;
    T032Gfx25F *sp4C;
    s32 sp24;
    s32 temp_lo;
    s32 temp_t6;
    s32 temp_t7;
    s32 temp_t9_2;
    s32 temp_t9_3;
    s32 temp_t9_4;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 var_a3;
    s32 var_t1;
    s32 var_t2;
    s32 var_t3;
    s32 var_t4;
    s32 var_v0_2;
    s32 var_v0_3;
    u8 *temp_v1;
    u8 temp_t6_2;
    u8 temp_t9;
    u8 var_v0;
    T032Gfx25F *temp_v1_10;
    T032Gfx25F *temp_v1_11;
    T032Gfx25F *temp_v1_12;
    T032Gfx25F *temp_v1_13;
    T032Gfx25F *temp_v1_14;
    T032Gfx25F *temp_v1_15;
    T032Gfx25F *temp_v1_16;
    T032Gfx25F *temp_v1_17;
    T032Gfx25F *temp_v1_18;
    T032Gfx25F *temp_v1_19;
    T032Gfx25F *temp_v1_20;
    T032Gfx25F *temp_v1_21;
    T032Gfx25F *temp_v1_22;
    T032Gfx25F *temp_v1_23;
    T032Gfx25F *temp_v1_24;
    T032Gfx25F *temp_v1_5;
    T032Gfx25F *temp_v1_6;
    T032Gfx25F *temp_v1_7;
    T032Gfx25F *temp_v1_8;
    T032Gfx25F *temp_v1_9;
    T032Gfx25F *var_a1;
    T032Gfx25F *var_a1_2;
    s32 var_a2;

    var_a2 = arg2;
    temp_t6 = arg3 & 0xFF;
    temp_v1 = &D_80061494[temp_t6];
    var_v0 = *temp_v1;
    if (((s32) arg4 < (s32) var_v0) && (D_8004A40C == 0) && (temp_t6_2 = var_v0 - 1, (D_801D87FE == 0))) {
        *temp_v1 = temp_t6_2;
        var_v0 = temp_t6_2 & 0xFF;
    } else if (((s32) var_v0 < (s32) arg4) && (D_8004A40C == 0)) {
        temp_t9 = var_v0 + 1;
        if (D_801D87FE == 0) {
            *temp_v1 = temp_t9;
            var_v0 = temp_t9 & 0xFF;
        }
    }
    temp_v1_2 = var_v0 & 0xFF;
    if (temp_v1_2 != 0) {
        if (temp_t6 == 0) {
            sp80 = 0x400;
            if (temp_v1_2 == 0xC0) {
                var_t1 = -1;
                var_t2 = arg1 + 1;
                var_t3 = arg1 + 0x3A;
                var_t4 = 0x20;
                if ((D_8004D26C & 8) == 8) {
                    var_a3 = 2;
                } else {
                    var_a3 = 5;
                }
            } else {
                var_a2 = 9;
                if (temp_v1_2 >= 0x61) {
                    var_a2 = 9;
                    var_t1 = arg1 + 1;
                    sp84 = 0x20;
                    sp78 = 2;
                    var_t3 = arg1 + 0x3A;
                    var_a3 = 5;
                    temp_t9_2 = (s32) ((temp_v1_2 * 9) - 0x360) / 16;
                    var_t2 = (arg1 - temp_t9_2) + 0x37;
                    sp88 = var_t2;
                    var_t4 = (0x37 - temp_t9_2) << 5;
                } else {
                    var_t3 = arg1 + 0x3A;
                    var_a3 = 2;
                    temp_t9_3 = (s32) (temp_v1_2 * 9) / 16;
                    temp_v1_3 = (arg1 - temp_t9_3) + 0x37;
                    var_t2 = temp_v1_3;
                    sp88 = temp_v1_3;
                    temp_lo = ((s32) (temp_v1_2 + 0xF) / 16) * 9;
                    var_t4 = (0x37 - temp_t9_3) << 5;
                    sp78 = 5;
                    var_t1 = (arg1 - temp_lo) + 0x37;
                    sp84 = (0x37 - temp_lo) << 5;
                }
            }
        } else {
            sp80 = 0xFC00;
            if (temp_v1_2 == 0xC0) {
                var_t1 = -1;
                var_t2 = arg1;
                var_t3 = arg1 + 0x38;
                var_t4 = 0x700;
                if ((D_8004D26C & 8) == 8) {
                    var_a3 = 2;
                } else {
                    var_a3 = 5;
                }
            } else {
                var_a2 = 9;
                if (temp_v1_2 >= 0x61) {
                    var_a2 = 9;
                    sp88 = arg1 + 0x38;
                    sp78 = 2;
                    var_t2 = arg1;
                    var_t4 = 0x700;
                    var_a3 = 5;
                    temp_t7 = (s32) ((temp_v1_2 * 9) - 0x360) / 16;
                    var_t3 = arg1 + temp_t7 + 2;
                    var_t1 = var_t3;
                    sp84 = (0x36 - temp_t7) << 5;
                } else {
                    var_t2 = arg1;
                    var_t4 = 0x700;
                    var_a3 = 2;
                    temp_t9_4 = (s32) (temp_v1_2 * 9) / 16;
                    temp_v1_4 = arg1 + temp_t9_4 + 2;
                    var_t3 = temp_v1_4;
                    var_t1 = temp_v1_4;
                    sp88 = arg1 + (((s32) (temp_v1_2 + 0xF) / 16) * 9) + 2;
                    sp84 = (0x36 - temp_t9_4) << 5;
                    sp78 = 5;
                }
            }
        }
        temp_v1_5 = *arg0;
        *arg0 = temp_v1_5 + 1;
        temp_v1_5->w1 = 0;
        temp_v1_5->w0 = 0xE7000000;
        temp_v1_6 = *arg0;
        *arg0 = temp_v1_6 + 1;
        temp_v1_6->w1 = (u32)0xFF;
        temp_v1_6->w0 = 0xFA000100;
        temp_v1_7 = *arg0;
        *arg0 = temp_v1_7 + 1;
        temp_v1_7->w1 = 0;
        temp_v1_7->w0 = 0xFB000000;
        D_8004EA78 = temp_t6 + 0xD;
        temp_v1_8 = *arg0;
        *arg0 = temp_v1_8 + 1;
        temp_v1_8->w0 = 0x06000000;
        temp_v1_8->w1 = (u32)D_80047DD0;
        if ((temp_v1_2 >= 0x61) && (temp_v1_2 != 0xC0) && ((D_8004D26C & 8) == 8)) {
            temp_v1_9 = *arg0;
            *arg0 = temp_v1_9 + 1;
            temp_v1_9->w0 = 0xFD100000;
            sp90 = var_t4;
            sp94 = var_t3;
            sp98 = var_t2;
            sp8C = var_t1;
            sp24 = temp_v1_2;
            sp7C = var_a3;
            sp64 = temp_v1_9;
            var_v0_2 = osVirtualToPhysical(D_8004D020);
            var_a1 = sp64;
        } else {
            temp_v1_10 = *arg0;
            *arg0 = temp_v1_10 + 1;
            temp_v1_10->w0 = 0xFD100000;
            sp90 = var_t4;
            sp94 = var_t3;
            sp98 = var_t2;
            sp8C = var_t1;
            sp24 = temp_v1_2;
            sp7C = var_a3;
            sp60 = temp_v1_10;
            var_v0_2 = osVirtualToPhysical(D_8004D03C);
            var_a1 = sp60;
        }
        var_a1->w1 = var_v0_2;
        temp_v1_11 = *arg0;
        *arg0 = temp_v1_11 + 1;
        temp_v1_11->w0 = 0xF3000000;
        temp_v1_11->w1 = (u32)0x293000;
        if (temp_v1_2 >= 0x61) {
            temp_v1_12 = *arg0;
            *arg0 = temp_v1_12 + 1;
            temp_v1_12->w0 = 0xFD100000;
            sp90 = var_t4;
            sp94 = var_t3;
            sp98 = var_t2;
            sp8C = var_t1;
            sp7C = var_a3;
            sp58 = temp_v1_12;
            var_v0_3 = osVirtualToPhysical(D_8004D058);
            var_a1_2 = sp58;
        } else {
            temp_v1_13 = *arg0;
            *arg0 = temp_v1_13 + 1;
            temp_v1_13->w0 = 0xFD100000;
            sp90 = var_t4;
            sp94 = var_t3;
            sp98 = var_t2;
            sp8C = var_t1;
            sp7C = var_a3;
            sp54 = temp_v1_13;
            var_v0_3 = osVirtualToPhysical(D_8004D020);
            var_a1_2 = sp54;
        }
        var_a1_2->w1 = var_v0_3;
        temp_v1_14 = *arg0;
        *arg0 = temp_v1_14 + 1;
        temp_v1_14->w0 = 0xF3000000;
        temp_v1_14->w1 = (u32)0x04293000;
        temp_v1_15 = *arg0;
        *arg0 = temp_v1_15 + 1;
        temp_v1_15->w0 = 0xFD900000;
        sp90 = var_t4;
        sp94 = var_t3;
        sp98 = var_t2;
        sp8C = var_t1;
        sp7C = var_a3;
        sp4C = temp_v1_15;
        sp4C->w1 = osVirtualToPhysical(D_8004D040);
        temp_v1_16 = *arg0;
        *arg0 = temp_v1_16 + 1;
        temp_v1_16->w0 = 0xF3000000;
        temp_v1_16->w1 = (u32)0x0115F000;
        if (var_t1 != -1) {
            temp_v1_17 = *arg0;
            *arg0 = temp_v1_17 + 1;
            temp_v1_17->w0 = (s32) ((((sp88 * 4) & 0xFFF) << 0xC) | 0xE4000000 | (((s32) (arg2 + 0xB) * 4) & 0xFFF));
            temp_v1_17->w1 = (u32) (((sp78 & 7) << 0x18) | (((var_t1 * 4) & 0xFFF) << 0xC) | (((s32) arg2 * 4) & 0xFFF));
            temp_v1_18 = *arg0;
            *arg0 = temp_v1_18 + 1;
            temp_v1_18->w0 = 0xB3000000;
            temp_v1_18->w1 = (u32) (sp84 << 0x10);
            temp_v1_19 = *arg0;
            *arg0 = temp_v1_19 + 1;
            temp_v1_19->w0 = 0xB2000000;
            temp_v1_19->w1 = (u32) ((sp80 << 0x10) | 0x400);
        }
        temp_v1_20 = *arg0;
        *arg0 = temp_v1_20 + 1;
        temp_v1_20->w0 = (s32) ((((var_t3 * 4) & 0xFFF) << 0xC) | 0xE4000000 | (((s32) (arg2 + 0xB) * 4) & 0xFFF));
        temp_v1_20->w1 = (u32) (((var_a3 & 7) << 0x18) | (((var_t2 * 4) & 0xFFF) << 0xC) | (((s32) arg2 * 4) & 0xFFF));
        temp_v1_21 = *arg0;
        *arg0 = temp_v1_21 + 1;
        temp_v1_21->w1 = (u32) (var_t4 << 0x10);
        temp_v1_21->w0 = 0xB3000000;
        temp_v1_22 = *arg0;
        *arg0 = temp_v1_22 + 1;
        temp_v1_22->w0 = 0xB2000000;
        temp_v1_22->w1 = (u32) ((sp80 << 0x10) | 0x400);
        temp_v1_23 = *arg0;
        *arg0 = temp_v1_23 + 1;
        temp_v1_23->w1 = 0;
        temp_v1_23->w0 = 0xE7000000;
        temp_v1_24 = *arg0;
        *arg0 = temp_v1_24 + 1;
        temp_v1_24->w1 = 0;
        temp_v1_24->w0 = 0xBA001402;
    }
}
