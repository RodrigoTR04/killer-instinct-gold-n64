/* T-059 DRAFT: 141 relocation-masked positional words differ; 748 emitted bytes. See T-059/REPORT.md. */
extern u8 D_8004AC88;
extern u8 D_8004EA9E[];
extern u8 D_8004CE90[];
extern s32 D_8004EA78;
extern u8 D_8004EA9A;
extern u8 D_8004EAB8;
extern u16 D_800614A0;
extern u8 D_801D3433;

void func_8001D47C(s32 arg0) {
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_lo_3;
    s32 temp_lo_4;
    s32 temp_t6;
    u16 *var_a0;
    u16 *var_a0_2;
    u16 *var_v0;
    u16 temp_a1;
    u16 temp_a2;
    u16 temp_a3;
    u16 temp_t8;
    u16 temp_v1;
    u8 *var_t0;
    u8 *var_t0_2;
    u8 *var_t0_3;

    temp_t6 = arg0 & 0xFF;
    if (D_8004EA9A == 0xB) {
        var_v0 = &D_800614A0;
    } else {
        var_v0 = (temp_t6 << 5) + D_8004CE90;
    }
    if (D_8004AC88 == 0xC) {
        if (D_8004EA78 == 1) {
            var_v0 = (u16 *)0x803A3FC0;
        } else if ((D_8004EA78 == 0) && (D_801D3433 != 0)) {
            var_v0 = (u16 *)0x803A3FE0;
        }
    }
    if (D_8004EAB8 == 1) {
        s32 i;
        for (i = 0; i != 32; i += 2) {
            s32 pixel = *(u16 *)((u8 *)var_v0 + i);
            s32 level = (((pixel & 0x3E) >> 1) + ((pixel & 0xF800) >> 11) + ((pixel & 0x7C0) >> 6)) / 3;
            *(u16 *)i = (level << 11) | (level << 6) | (level << 1);
        }
    } else if (D_8004EA9E[temp_t6] == 9 && D_8004EA78 < 2) {
        s32 i;
        for (i = 0; i != 32; i += 2) *(u16 *)i = 0;
    } else {
        s32 i;
        for (i = 0; i != 32; i += 2) *(u16 *)i = *(u16 *)((u8 *)var_v0 + i);
    }
}
