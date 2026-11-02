/* T-093 DRAFT: 427 -> 423 relocation-masked words; 1720/1656 bytes. Correct one-argument 244F0 ABI. */
/* T-069 DRAFT: 427 relocation-masked positional words differ in TU context; 1724 bytes. See T-069/REPORT.md. */

extern u8 D_8004EA9C[];
s32 func_8001D47C(u8);                          /* extern */
void func_8001DE5C(u8 *, u8 *, u8);  /* extern */
void func_80024144(s32,s32);                      /* extern */
void func_800241BC(s32);                      /* extern */
void func_800244F0(s32);                      /* extern */
void func_80024714(s32);                      /* extern */
void func_8002A1A0(u8);                          /* extern */
void func_800310C0(u8 *);  /* extern */
void func_80031A38(u8 *);  /* extern */
typedef struct { u8 *normal,*fallback; } T069Animation;
extern s32 D_8004EA78;
extern s32 D_8004EA90;
extern s32 D_8004EA94;
extern s16 D_8004EA98;
extern u8 D_8004EA9A;
extern u8 D_8004F394;
extern u8 D_8004F395;
extern u8 D_8004F396[];
extern u8 D_8004F398;
extern u8 D_801D34BE[][256];

void func_8001D7E4(s32 arg0, s32 arg1, s32 arg2, u8 arg3, u8 arg4) {
    s32 sp50;
    u8 *sp1C;
    T022Sprite *temp_t0;
    s16 var_t2;
    s32 temp_t5;
    s32 temp_t7;
    s32 temp_v1_2;
    s32 var_a0;
    s32 var_a1;
    s32 var_a2;
    s32 var_a3_2;
    s32 var_v0;
    u8 temp_v0;
    u8 temp_v0_2;
    u8 *temp_v0_4;
    T069Animation *temp_v1;
    u8 *var_a3;

    if ((arg1 == 0xC7) && (D_8004F398 == 0)) {
        func_800244F0(arg3);
    } else if ((((arg1 == 0xB0) && (D_8004EA9C[arg3] != 1)) || ((arg1 == 0xAE) && ((temp_v0 = D_8004EA9C[arg3], (temp_v0 == 3)) || (temp_v0 == 5))) || ((arg1 == 0xAB) && (D_8004EA9C[arg3] == 4)) || (((arg1 == 0x99) || (arg1 == 0xAB)) && (D_8004EA9C[arg3] == 2))) && (D_8004F395 == 0)) {
        func_800241BC(arg3);
    } else if (((arg1 == 0xB9) || (arg1 == 0xBA) || (arg1 == 0xBB) || (arg1 == 0xB1)) && (D_8004F394 == 0)) {
        func_80024144(arg3, arg1);
    } else {
        temp_v0_2 = D_8004EA9C[arg3];
        if (((temp_v0_2 == 1) && ((arg1 == 0x84) || (arg1 == 0x85))) || ((temp_v0_2 == 2) && ((arg1 == 0x84) || (arg1 == 0x86) || (arg1 == 0xAD) || (arg1 == 0xBC))) || ((temp_v0_2 == 4) && ((arg1 == 0x85) || (arg1 == 0x86))) || ((temp_v0_2 == 5) && ((arg1 == 0x83) || (arg1 == 0x86)))) {
                if (D_8004F396[arg3] == 0) {
                        func_80024714(arg3);
            }
        }
    }
    func_8002A1A0(arg3);
    D_8004EA78 = arg0;
    func_8001D47C(arg3);
    var_v0 = arg1 & 0xFFFF;
    D_8004EA90 = arg2 - 1;
    D_8004EA98 = (s16) arg1;
    if (var_v0 < 0) {
        D_8004EA98 = 0;
        var_v0 = 0 & 0xFFFF;
    } else if (var_v0 >= 0x100) {
        D_8004EA98 = 0xFF;
        var_v0 = 0xFF & 0xFFFF;
    }
    temp_v1 = &((T069Animation (*)[3])&D_8004D278)[var_v0][arg3];
    var_a3 = temp_v1->normal;
    if (var_a3 != 0) {
        var_t2 = 0;
        if (D_8004EA9A == 1) {
            return;
        }
    } else {
        var_a3 = temp_v1->fallback;
        var_t2 = 5;
        if (var_a3 == 0) {
            return;
        }
    }
        var_a0 = D_8004EA90;
        temp_t5 = (var_a3[3] << 8) + var_a3[2];
        D_8004EA94 = temp_t5;
        if (var_a0 >= temp_t5) {
            var_a0 = temp_t5 - 1;
            D_8004EA90 = var_a0;
        }
        if (var_a0 < 0) {
            D_8004EA90 = 0;
            var_a0 = 0;
        }
        temp_t0 = &D_8004CED0[D_8004EA78];
        temp_t0->flags = var_t2;
        temp_v0_4 = (var_a0 * 4) + var_a3;
        var_a2 = ((u32)temp_v0_4[0xB] << 24) + temp_v0_4[8] + (temp_v0_4[9] << 8) + (temp_v0_4[0xA] << 0x10);
        temp_v1_2 = ((u32)var_a3[7] << 24) + var_a3[4] + (var_a3[5] << 8) + (var_a3[6] << 0x10);
        if (var_a2 >= temp_v1_2) {
            do {
                temp_t7 = var_a0 - 1;
                D_8004EA90 = temp_t7;
                temp_v0_4 = (temp_t7 * 4) + var_a3;
                var_a0 = temp_t7;
                var_a2 = ((u32)temp_v0_4[0xB] << 24) + temp_v0_4[8] + (temp_v0_4[9] << 8) + (temp_v0_4[0xA] << 0x10);
            } while (var_a2 >= temp_v1_2);
        }
        switch (D_8004EA9A) {
        case 0:
            sp50 = 0x8890;
            break;
        case 2:
            sp50 = 0x1E40;
            break;
        case 3:
            sp50 = 0x780;
            break;
        case 4:
            sp50 = 0x780;
            break;
        case 5:
            sp50 = 0x6180;
            break;
        case 6:
        case 7:
        case 8:
            sp50 = 0x1800;
            break;
        case 10:
            sp50 = 0x7E90;
            break;
        case 9:
            sp50 = 0x3408;
            break;
        case 11:
            sp50 = 0x100;
            break;
        case 12:
            sp50 = 0x1200;
            break;
        }
        sp1C = var_a3 + var_a2;
        if (sp50 < ((((sp1C[7] << 8) + sp1C[6] + 1) & 0xFFFE) * ((sp1C[4] + (sp1C[5] << 8) + 9) & 0xFFF8))) {
            temp_t0->height2 = 0x10;
            temp_t0->width = 0x10;
            temp_t0->width2 = 0x10;
            temp_t0->height = temp_t0->height2;
            return;
        }
        if ((var_t2 != 0) && (arg4 != 0)) {
            arg4 = 0U;
        }
        if (arg4 != 0) {
            var_a3 = ((T069Animation (*)[3])&D_8004D278)[arg4][arg3].fallback;
            if (var_a3 == 0) {
                func_8001DE5C(sp1C, 0, 0U);
                return;
            }
            var_a1 = var_a0;
            temp_t5 = (var_a3[3] << 8) + var_a3[2];
            if (var_a0 >= temp_t5) {
                var_a1 = temp_t5 - 1;
            }
            temp_v0_4 = (var_a1 * 4) + var_a3;
            temp_v1_2 = ((u32)var_a3[7] << 24) + var_a3[4] + (var_a3[5] << 8) + (var_a3[6] << 0x10);
            var_a3_2 = ((u32)temp_v0_4[0xB] << 24) + temp_v0_4[8] + (temp_v0_4[9] << 8) + (temp_v0_4[0xA] << 0x10);
            if (var_a3_2 >= temp_v1_2) {
                do {
                    var_a3_2 = ((u32)temp_v0_4[7] << 24) + temp_v0_4[4] + (temp_v0_4[5] << 8) + (temp_v0_4[6] << 0x10);
                    temp_v0_4 -= 4;
                } while (var_a3_2 >= temp_v1_2);
            }
            if (var_t2 == 0) {
                if (D_8004EA9E[arg3] == 9) {
                    func_8001DE5C(sp1C, var_a3 + var_a3_2, 0x13U);
                    return;
                }
                func_8001DE5C(sp1C, var_a3 + var_a3_2, D_801D34BE[arg3][0]);
            }
        } else {
            if (var_t2 == 0) {
                func_800310C0(sp1C);
                return;
            }
            func_80031A38(sp1C);
        }
}
