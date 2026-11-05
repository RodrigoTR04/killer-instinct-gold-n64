extern u8 D_8004AC88;
extern u8 D_8004EA9E[];
extern s32 D_8004EA78;
extern u8 D_8004EA9A;
extern u8 D_8004EAB8;
extern u16 D_800614A0;
extern u8 D_801D3433;

void func_8001D47C(u8 arg0) {
    u16 *var_v0;
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
        for (i = 0; i != 32; i += 8) {
            s32 l;
            l = (((*var_v0 & 0x3E) >> 1) + ((*var_v0 & 0xF800) >> 11) + ((*var_v0 & 0x7C0) >> 6)) / 3;
            var_v0++;
            *(u16 *)(i + 0) = (l << 11) | (l << 6) | (l << 1);
            l = (((*var_v0 & 0x3E) >> 1) + ((*var_v0 & 0xF800) >> 11) + ((*var_v0 & 0x7C0) >> 6)) / 3;
            var_v0++;
            *(u16 *)(i + 2) = (l << 11) | (l << 6) | (l << 1);
            l = (((*var_v0 & 0x3E) >> 1) + ((*var_v0 & 0xF800) >> 11) + ((*var_v0 & 0x7C0) >> 6)) / 3;
            var_v0++;
            *(u16 *)(i + 4) = (l << 11) | (l << 6) | (l << 1);
            l = (((*var_v0 & 0x3E) >> 1) + ((*var_v0 & 0xF800) >> 11) + ((*var_v0 & 0x7C0) >> 6)) / 3;
            var_v0++;
            *(u16 *)(i + 6) = (l << 11) | (l << 6) | (l << 1);
        }
    } else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {
        for (i = 0; i != 32; i += 8) {
            *(u16 *)(i + 0) = 0;
            *(u16 *)(i + 2) = 0;
            *(u16 *)(i + 4) = 0;
            *(u16 *)(i + 6) = 0;
        }
    } else {
        for (i = 0; i != 32; i += 8) {
            *(u16 *)(i + 0) = *var_v0++;
            *(u16 *)(i + 2) = *var_v0++;
            *(u16 *)(i + 4) = *var_v0++;
            *(u16 *)(i + 6) = *var_v0++;
        }
    }
}
