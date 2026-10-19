/* DRAFT. Remaining diff: 177 linked instruction words; compiled 892 bytes, original 748 bytes. */

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
        var_a0 = var_v0;
        var_t0 = 0;
        do {
            temp_v1 = *var_a0;
            var_t0 += 8;
            var_a0 += 4;
            temp_lo = (s32) (((s32) (temp_v1 & 0x3E) >> 1) + ((s32) (temp_v1 & 0xF800) >> 0xB) + ((s32) (temp_v1 & 0x7C0) >> 6)) / 3;
            (*(s16 *)((u8 *)(var_t0) + -8)) = (s16) ((temp_lo << 0xB) | (temp_lo << 6) | (temp_lo * 2));
            temp_a1 = (*(u16 *)((u8 *)(var_a0) + -6));
            temp_lo_2 = (s32) (((s32) (temp_a1 & 0x3E) >> 1) + ((s32) (temp_a1 & 0xF800) >> 0xB) + ((s32) (temp_a1 & 0x7C0) >> 6)) / 3;
            (*(s16 *)((u8 *)(var_t0) + -6)) = (s16) ((temp_lo_2 << 0xB) | (temp_lo_2 << 6) | (temp_lo_2 * 2));
            temp_a2 = (*(u16 *)((u8 *)(var_a0) + -4));
            temp_lo_3 = (s32) (((s32) (temp_a2 & 0x3E) >> 1) + ((s32) (temp_a2 & 0xF800) >> 0xB) + ((s32) (temp_a2 & 0x7C0) >> 6)) / 3;
            (*(s16 *)((u8 *)(var_t0) + -4)) = (s16) ((temp_lo_3 << 0xB) | (temp_lo_3 << 6) | (temp_lo_3 * 2));
            temp_a3 = (*(u16 *)((u8 *)(var_a0) + -2));
            temp_lo_4 = (s32) (((s32) (temp_a3 & 0x3E) >> 1) + ((s32) (temp_a3 & 0xF800) >> 0xB) + ((s32) (temp_a3 & 0x7C0) >> 6)) / 3;
            (*(s16 *)((u8 *)(var_t0) + -2)) = (s16) ((temp_lo_4 << 0xB) | (temp_lo_4 << 6) | (temp_lo_4 * 2));
        } while (var_t0 != (u8 *)0x20);
        return;
    }
    var_a0_2 = var_v0;
    if (D_8004EA9E[temp_t6] == 9) {
        var_t0_2 = 0;
        if (D_8004EA78 < 2) {
            do {
                var_t0_2 += 8;
                (*(s16 *)((u8 *)(var_t0_2) + -6)) = 0;
                (*(s16 *)((u8 *)(var_t0_2) + -4)) = 0;
                (*(s16 *)((u8 *)(var_t0_2) + -2)) = 0;
                (*(s16 *)((u8 *)(var_t0_2) + -8)) = 0;
            } while (var_t0_2 != (u8 *)0x20);
            return;
        }
    }
    var_t0_3 = 0;
    do {
        temp_t8 = *var_a0_2;
        var_t0_3 += 8;
        var_a0_2 += 4;
        (*(u16 *)((u8 *)(var_t0_3) + -8)) = temp_t8;
        (*(u16 *)((u8 *)(var_t0_3) + -6)) = (u16) (*(u16 *)((u8 *)(var_a0_2) + -6));
        (*(u16 *)((u8 *)(var_t0_3) + -4)) = (u16) (*(u16 *)((u8 *)(var_a0_2) + -4));
        (*(u16 *)((u8 *)(var_t0_3) + -2)) = (u16) (*(u16 *)((u8 *)(var_a0_2) + -2));
    } while (var_t0_3 != (u8 *)0x20);
}
