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
        } else if (D_8004EA78 == 0) {
            if (D_801D3433 != 0) {
                var_v0 = (u16 *)0x803A3FE0;
            }
        }
    }
    if (D_8004EAB8 == 1) {
        u16 *src = var_v0;
        for (i = 0; i != 32; i += 2) {
            s32 pixel = *src;
            s32 level = (((pixel & 0x3E) >> 1) + ((pixel & 0xF800) >> 11) + ((pixel & 0x7C0) >> 6)) / 3;
            src++;
            *(u16 *)i = (level << 11) | (level << 6) | (level << 1);
        }
    } else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {
        for (i = 0; i != 32; i += 2) *(u16 *)i = 0;
    } else {
        for (i = 0; i != 32; i += 2) *(u16 *)i = *var_v0++;
    }
}
