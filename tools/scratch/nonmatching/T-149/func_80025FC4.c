/* T-149 DRAFT: 274 differing words, 1900/1908 bytes in the full TU. */

extern u32 osVirtualToPhysical(void *);
extern void *D_8004D020,*D_8004D03C,*D_8004D040,*D_8004D058;
extern u8 D_80047DD0[];


void func_80025FC4(T032Gfx269AC **arg0, s32 arg1, s32 arg2, u8 arg3, u8 arg4) {
    s32 var_a3;
    s32 var_t1;
    s32 sp88;
    u8 var_v0;
    s32 var_t2;
    s32 sp80;
    s32 decremented;
    s32 sp84;
    u8 *temp_v1;
    s32 temp_t9;
    s32 var_a2;
    s32 temp_t9_4;
    T032Gfx269AC *g;
    s32 temp_v1_4;
    s32 temp_v1_2;
    s32 temp_t9_2;
    s32 temp_lo;
    s32 temp_v1_3;
    s32 sp78;
    s32 var_t3;
    s32 temp_t9_3;
    s32 var_t4;
    s32 temp_t7;
    temp_v1 = &D_80061494[arg3];
    var_v0 = *temp_v1;
    if (((s32) arg4 < (s32) var_v0) && (D_8004A40C == 0) && (decremented = var_v0 - 1, (D_801D87FE == 0))) {
        *temp_v1 = decremented;
        var_v0 = decremented & 0xFF;
    } else if (((s32) var_v0 < (s32) arg4) && (D_8004A40C == 0)) {
        temp_t9 = var_v0 + 1;
        if (D_801D87FE == 0) {
            *temp_v1 = temp_t9;
            var_v0 = temp_t9 & 0xFF;
        }
    }
    temp_v1_2 = var_v0 & 0xFF;
    if (temp_v1_2 != 0) {
        if (arg3 == 0) {
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
                    var_t1 = arg1 + 1;
                    sp84 = 0x20;
                    sp78 = 2;
                    var_t3 = arg1 + 0x3A;
                    var_a3 = 5;
                    temp_t9_2 = (s32) ((temp_v1_2 * var_a2) - 0x360) / 16;
                    var_t2 = (arg1 - temp_t9_2) + 0x37;
                    sp88 = var_t2;
                    var_t4 = (0x37 - temp_t9_2) << 5;
                } else {
                    var_t3 = arg1 + 0x3A;
                    var_a3 = 2;
                    temp_t9_3 = (s32) (temp_v1_2 * var_a2) / 16;
                    temp_v1_3 = (arg1 - temp_t9_3) + 0x37;
                    var_t2 = temp_v1_3;
                    sp88 = temp_v1_3;
                    temp_lo = ((s32) (temp_v1_2 + 0xF) / 16) * var_a2;
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
                    sp88 = arg1 + 0x38;
                    sp78 = 2;
                    var_t2 = arg1;
                    var_t4 = 0x700;
                    var_a3 = 5;
                    temp_t7 = (s32) ((temp_v1_2 * var_a2) - 0x360) / 16;
                    var_t3 = arg1 + temp_t7 + 2;
                    var_t1 = var_t3;
                    sp84 = (0x36 - temp_t7) << 5;
                } else {
                    var_t2 = arg1;
                    var_t4 = 0x700;
                    var_a3 = 2;
                    temp_t9_4 = (s32) (temp_v1_2 * var_a2) / 16;
                    temp_v1_4 = arg1 + temp_t9_4 + 2;
                    var_t3 = temp_v1_4;
                    var_t1 = temp_v1_4;
                    sp88 = arg1 + (((s32) (temp_v1_2 + 0xF) / 16) * var_a2) + 2;
                    sp84 = (0x36 - temp_t9_4) << 5;
                    sp78 = 5;
                }
            }
        }
        g = *arg0;
        *arg0 = g + 1;
        g->w1 = 0;
        g->w0 = 0xE7000000;
        g = *arg0;
        *arg0 = g + 1;
        g->w1 = (u32)0xFF;
        g->w0 = 0xFA000100;
        g = *arg0;
        *arg0 = g + 1;
        g->w1 = 0;
        g->w0 = 0xFB000000;
        D_8004EA78 = arg3 + 0xD;
        g = *arg0;
        *arg0 = g + 1;
        g->w0 = 0x06000000;
        g->w1 = (u32)D_80047DD0;
        if ((temp_v1_2 >= 0x61) && (temp_v1_2 != 0xC0) && ((D_8004D26C & 8) == 8)) {
            g = *arg0;
            *arg0 = g + 1;
            g->w0 = 0xFD100000;







            g->w1 = osVirtualToPhysical(D_8004D020);

        } else {
            g = *arg0;
            *arg0 = g + 1;
            g->w0 = 0xFD100000;







            g->w1 = osVirtualToPhysical(D_8004D03C);

        }
        g = *arg0;
        *arg0 = g + 1;
        g->w0 = 0xF3000000;
        g->w1 = (u32)0x293000;
        if (temp_v1_2 >= 0x61) {
            g = *arg0;
            *arg0 = g + 1;
            g->w0 = 0xFD100000;






            g->w1 = osVirtualToPhysical(D_8004D058);

        } else {
            g = *arg0;
            *arg0 = g + 1;
            g->w0 = 0xFD100000;






            g->w1 = osVirtualToPhysical(D_8004D020);

        }
        g = *arg0;
        *arg0 = g + 1;
        g->w0 = 0xF3000000;
        g->w1 = (u32)0x04293000;
        g = *arg0;
        *arg0 = g + 1;
        g->w0 = 0xFD900000;






        g->w1 = osVirtualToPhysical(D_8004D040);
        g = *arg0;
        *arg0 = g + 1;
        g->w0 = 0xF3000000;
        g->w1 = (u32)0x0115F000;
        if (var_t1 != -1) {
            g = *arg0;
            *arg0 = g + 1;
            g->w0 = (s32) ((((sp88 * 4) & 0xFFF) << 0xC) | 0xE4000000 | (((s32) (arg2 + 0xB) * 4) & 0xFFF));
            g->w1 = (u32) (((sp78 & 7) << 0x18) | (((var_t1 * 4) & 0xFFF) << 0xC) | (((s32) arg2 * 4) & 0xFFF));
            g = *arg0;
            *arg0 = g + 1;
            g->w0 = 0xB3000000;
            g->w1 = (u32) (sp84 << 0x10);
            g = *arg0;
            *arg0 = g + 1;
            g->w0 = 0xB2000000;
            g->w1 = (u32) ((sp80 << 0x10) | 0x400);
        }
        g = *arg0;
        *arg0 = g + 1;
        g->w0 = (s32) ((((var_t3 * 4) & 0xFFF) << 0xC) | 0xE4000000 | (((s32) (arg2 + 0xB) * 4) & 0xFFF));
        g->w1 = (u32) (((var_a3 & 7) << 0x18) | (((var_t2 * 4) & 0xFFF) << 0xC) | (((s32) arg2 * 4) & 0xFFF));
        g = *arg0;
        *arg0 = g + 1;
        g->w1 = (u32) (var_t4 << 0x10);
        g->w0 = 0xB3000000;
        g = *arg0;
        *arg0 = g + 1;
        g->w0 = 0xB2000000;
        g->w1 = (u32) ((sp80 << 0x10) | 0x400);
        g = *arg0;
        *arg0 = g + 1;
        g->w1 = 0;
        g->w0 = 0xE7000000;
        g = *arg0;
        *arg0 = g + 1;
        g->w1 = 0;
        g->w0 = 0xBA001402;
    }
}
