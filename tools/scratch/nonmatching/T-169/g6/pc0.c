extern u8 D_8004AC88;
extern u8 D_8004EA9E[];
extern s32 D_8004EA78;
extern u8 D_8004EA9A;
extern u8 D_8004EAB8;
extern u16 D_800614A0;
extern u8 D_801D3433;

void func_8001D47C(u8 arg0) {
    u16 *var_v0;
    u16 *dst;
    s32 i;
    if (D_8004EA9A == 0xB) {
        var_v0 = &D_800614A0;
    } else {
        var_v0 = (u16 *)((arg0 << 5) + (u8 *)D_8004CE90);
    }
    if (D_8004AC88 == 0xC) {
        if (D_8004EA78 == 1) {
            var_v0 = (u16 *)0x803A3FC0;
        } else if ((D_801D3433 != 0) && (D_8004EA78 == 0)) {
            var_v0 = (u16 *)0x803A3FE0;
        }
    }
    if (D_8004EAB8 == 1) {
        for (dst = (u16 *)0; dst != (u16 *)0x20; dst += 4) {
            s32 pixel;
            s32 l;
            pixel = *var_v0++;
            l = (((pixel & 0x3E) >> 1) + ((pixel & 0xF800) >> 11) + ((pixel & 0x7C0) >> 6)) / 3;
            dst[0] = (l << 11) | (l << 6) | (l << 1);
            pixel = *var_v0++;
            l = (((pixel & 0x3E) >> 1) + ((pixel & 0xF800) >> 11) + ((pixel & 0x7C0) >> 6)) / 3;
            dst[1] = (l << 11) | (l << 6) | (l << 1);
            pixel = *var_v0++;
            l = (((pixel & 0x3E) >> 1) + ((pixel & 0xF800) >> 11) + ((pixel & 0x7C0) >> 6)) / 3;
            dst[2] = (l << 11) | (l << 6) | (l << 1);
            pixel = *var_v0++;
            l = (((pixel & 0x3E) >> 1) + ((pixel & 0xF800) >> 11) + ((pixel & 0x7C0) >> 6)) / 3;
            dst[3] = (l << 11) | (l << 6) | (l << 1);
        }
    } else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {
        for (dst = (u16 *)0; dst != (u16 *)0x20; dst += 4) {
            dst[0] = 0;
            dst[1] = 0;
            dst[2] = 0;
            dst[3] = 0;
        }
    } else {
        for (dst = (u16 *)0; dst != (u16 *)0x20; dst += 4) {
            dst[0] = *var_v0++;
            dst[1] = *var_v0++;
            dst[2] = *var_v0++;
            dst[3] = *var_v0++;
        }
    }
}
