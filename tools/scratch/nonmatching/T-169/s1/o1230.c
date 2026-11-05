extern u8 D_8004AC88;
extern u8 D_8004EA9E[];
extern s32 D_8004EA78;
extern u8 D_8004EA9A;
extern u8 D_8004EAB8;
extern u16 D_800614A0;
extern u8 D_801D3433;

void func_8001D47C(u8 arg0) {
    u16 *var_v0;
    u16 *src;
    u16 *dst;
    u16 *de;
    if (D_8004EA9A == 0xB) {
        var_v0 = &D_800614A0;
    } else {
        var_v0 = (u16 *)((arg0 << 5) + (u8 *)D_8004CE90);
    }
    if (D_8004AC88 == 0xC) {
        if (D_8004EA78 == 1) {
            var_v0 = (u16 *)0x803A3FC0;
        } else if ((D_8004EA78 == 0) && (D_801D3433 != 0)) {
            var_v0 = (u16 *)0x803A3FE0;
        }
    }
    src = var_v0;
    dst = (u16 *)0;
    de = dst + 16;
    if (D_8004EAB8 == 1) {
        s32 p;
        s32 l;
        while (dst != de) {
            p = src[1];
            l = (((p & 0x3E) >> 1) + ((p & 0xF800) >> 11) + ((p & 0x7C0) >> 6)) / 3;
            dst[1] = (l << 11) | (l << 6) | (l << 1);
            p = src[2];
            l = (((p & 0x3E) >> 1) + ((p & 0xF800) >> 11) + ((p & 0x7C0) >> 6)) / 3;
            dst[2] = (l << 11) | (l << 6) | (l << 1);
            p = src[3];
            l = (((p & 0x3E) >> 1) + ((p & 0xF800) >> 11) + ((p & 0x7C0) >> 6)) / 3;
            dst[3] = (l << 11) | (l << 6) | (l << 1);
            p = src[0];
            l = (((p & 0x3E) >> 1) + ((p & 0xF800) >> 11) + ((p & 0x7C0) >> 6)) / 3;
            dst[0] = (l << 11) | (l << 6) | (l << 1);
            src += 4;
            dst += 4;
        }
    } else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {
        dst = (u16 *)0;
        de = dst + 16;
        while (dst != de) {
            dst[1] = 0;
            dst[2] = 0;
            dst[3] = 0;
            dst[0] = 0;
            dst += 4;
        }
    } else {
        src = var_v0;
        dst = (u16 *)0;
        de = dst + 16;
        while (dst != de) {
            dst[1] = src[1];
            dst[2] = src[2];
            dst[3] = src[3];
            dst[0] = src[0];
            src += 4;
            dst += 4;
        }
    }
}
