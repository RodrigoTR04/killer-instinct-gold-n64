/* DRAFT. Remaining diff: Typed portrait/display-list reconstruction compiles; frame, text buffers, registers and scheduling differ. */
typedef struct T029Portrait {
    s32 reserved;
    void *pixels;
    void *palette;
    u8 pad0C[0x72];
    s16 width, height, clipLeft, clipRight;
    u8 pad86[2];
    void (*draw)(u32 **, s32, s32, s32, void *, s32);
} T029Portrait;
extern void func_801B446C(u8);
extern void func_801B4590(u8);
extern void func_801B465C(s32, s32);
extern void func_801B677C(u8, f32 *, f32 *, f32 *, u16);
extern void func_801B695C(T029Portrait *, s32);
extern s32 func_801B6A68(u32 **, T029Portrait *, s32);
extern s32 func_801B6BD8(u32 **, s32);
extern void func_801BCB70(u32 **, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32, void *);
extern s32 func_801BD640(u32 **, s32, void *, f32, f32, f32, s32, s32, s32, s32);
extern s32 func_801BDA6C(u32 **, s32, void *, f32, f32, f32, s32, s32, s32, s32, f32);
extern s32 func_801BDF94(u32 **, s32, void *, f32, f32, f32, s32, f32, f32);
extern s32 func_801BE540(u32 **, s32, void *, f32, f32, f32, s32, s32, s32, s32, f32);
extern void func_801BF678(void *, u8);
extern void *func_801C9584(u8, s32);
extern void *memcpy(void *, const void *, u32);
extern f32 sinf(f32);
extern u8 D_8004A407;
extern u8 D_80127CE8[];
extern u8 D_80127CFE[];
extern u8 D_80127D00[];
extern u8 D_80127D30;
extern u8 D_80127D31;
extern u8 D_8012830A;
extern s8 D_801CD454;
extern u8 D_801F2EA8[];
extern u8 D_801F2EAC[];
extern u8 D_801F2EB4[];
extern u8 D_801F35D0[];
extern s32 D_801F3600;
extern u8 D_801F3604;
extern s32 D_801F3D6C;
extern s32 D_801F3D70;
extern u8 D_8028FCC0[];
extern u8 D_80290BE0[];
extern s32 D_80292A54;
extern s32 D_80292A60;
extern u8 D_80292A78[];
extern f64 D_80292B18;
extern f32 D_80292B20;
extern f32 D_80292B24;
extern u8 D_802C8C30[];
extern u8 D_802C8C32[];
extern u8 D_802C8CB9;
extern u8 D_802C8CC8;
extern s32 D_802C8CD4;
extern s32 D_802C8CD8;
extern s32 D_802C8CDC;
extern u8 D_802C8CE0;
extern s16 D_802C8CE2;
extern s16 D_802C8CE4;
extern u8 D_802C8CE8;
extern u8 D_802C8CEA;
extern u8 D_802C8D06;
extern u8 D_802C8D07;
extern u8 D_802C8D0F;
extern u8 D_802C8D10;
extern s16 D_802C8D12;
extern u8 D_802C8D20[];
extern s32 D_802CA064;
extern T029Portrait *D_802C8D14;

s32 func_801B6E4C(u32 **arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp134;
    u8 sp133;
    f32 sp12C;
    f32 sp128;
    f32 sp124;
    s32 spB0;
    s32 spA8;
    u8 spA3;
    u8 spA2;
    u8 spA1;
    u8 spA0;
    u8 text[16];
    f32 sp68;
    s32 sp64;
    void *var_a2;
    f32 temp_f0;
    f64 var_f6;
    s16 temp_v0_3;
    s16 temp_v0_4;
    s16 var_v0;
    s32 temp_a1;
    s32 temp_a3;
    s32 temp_hi;
    s32 temp_v0;
    s32 temp_v1_35;
    s32 var_a0;
    s32 var_t0;
    s32 var_v1;
    s32 var_v1_2;
    u8 temp_v0_2;
    u8 var_t0_2;
    u8 var_t1;
    u8 var_t1_2;
    T029Portrait *temp_a0;
    T029Portrait *temp_t0;
    u32 *command;
    T029Portrait *var_a1;

    sp134 = 0;
    var_f6 = (f64) arg3;
    if (arg3 < 0) {
        var_f6 += 4294967296.0;
    }
    temp_a1 = D_8004A407 & 1;
    D_802C8D10 = (u8) (u32) ((sinf((f32) (var_f6 * D_80292B18 * 2.0)) * 63.0f) + 128.0f);
    if ((temp_a1 == 0) || (D_802C8D06 != 6)) {
        if ((D_802C8CE0 & 1) && (D_802C8CE4 != 0)) {
            D_802C8CE4 = 0;
            D_802C8CDC = D_802C8CD4 + 1;
            var_v0 = 0;
        } else {
            var_v0 = D_802C8CE4;
            if ((D_802C8CE0 & 2) && (temp_a1 != 0) && (D_802C8CE2 <= 0)) {
                if (var_v0 > 0) {
                    D_802C8CE4 = (var_v0 - (D_802C8CE8 * 9)) - 7;
                    D_802C8CDC = D_802C8CD4 + 1;
                } else {
                    func_801B446C(0);
                }
                var_v0 = D_802C8CE4;
            } else if ((D_8004A407 == 0) && (var_v0 > 0)) {
                D_802C8CE4 = var_v0 - 0x14;
                D_802C8CDC = D_802C8CD4 + 1;
                var_v0 = D_802C8CE4;
                D_802CA064 = 0x172;
            }
        }
        if (var_v0 < 0) {
            D_802C8CE4 = 0;
            D_802C8CDC = D_802C8CD4 + 1;
        }
    }
    temp_v0 = D_802C8CD4 + 1;
    temp_a3 = D_802C8CD8 + 1;
    D_802C8CD4 = temp_v0;
    if (temp_v0 == temp_a3) {
        D_802CA064 = 0x7B;
    }
    var_a1 = (T029Portrait *)(D_801F2EA8 + D_802C8CB8[0] * 0x8C);
    var_a0 = var_a1->pixels;
    if (var_a0 == 0) {
        D_801F3D6C = 0;
        D_801F3D70 = 0x27F;
    }
    if ((D_802C8CD8 == temp_v0) || (temp_v0 == temp_a3)) {
        if (D_802C8CD8 == temp_v0) {
            temp_a0 = (T029Portrait *)(D_801F2EA8 + D_802C8CB8[0] * 0x8C);
            D_802C8D14 = temp_a0;
            func_801B695C(temp_a0, 0);
            var_a1 = (T029Portrait *)(D_801F2EA8 + D_802C8CB8[0] * 0x8C);
            var_a0 = var_a1->pixels;
        }
        D_801F3600 = 8;
        D_801F3D6C = 0;
        if (var_a0 == 0) {
            D_801F3D70 = 0x27F;
        }
    }
    temp_t0 = D_802C8D14;
    if ((temp_t0 != var_a1) || (D_801F3604 != D_802C8CC8)) {
        D_802C8CDC = D_802C8CD4 + 1;
        D_801F3600 = 8;
        D_802CA064 = 0x172;
        D_801F3D6C = 0;
        D_801F3604 = D_802C8CC8;
        func_801B465C(0, 0);
    }
    if ((temp_t0 == 0) || (*((s32 *)(D_801F2EAC + (D_802C8CB8[0] * 0x8C))) == 0)) {
        return 0;
    }
    if (D_802C8D06 & 8) {
        if ((D_8004A407 & 1) && (D_802C8D0F == 0)) {
            if (D_802C8CE0 & 2) {
                func_801B4590(0);
            } else {
                D_80127CFE[0] = (u8) D_80127CFE[1];
            }
        }
        temp_v0_2 = D_80127CFE[0];
        var_t1 = 0;
        var_t0 = 0;
        if ((s32) temp_v0_2 > 0) {
            do {
                sp64 = var_t0;
                sp133 = var_t1;
                func_801B677C((var_t0 + 1) & 0xFF, &sp12C, &sp128, &sp124, (s32) temp_v0_2);
                command = *arg0;
                *arg0 = command + 2;
                command[0] = 0xB900031D;
                command[1] = (u32)0x0F0A4000;
                command = *arg0;
                *arg0 = command + 2;
                command[1] = 0;
                command[0] = 0xBA001301;
                command = *arg0;
                *arg0 = command + 2;
                command[1] = 0;
                command[0] = 0xBA000C02;
                if (sp64 >= (s32) D_802C8CEA) {
                    command = *arg0;
                    *arg0 = command + 2;
                    command[0] = 0xFA000000;
                    command[1] = (u32)0xFF0000FF;
                    command = *arg0;
                    *arg0 = command + 2;
                    command[0] = 0xFB000000;
                    command[1] = (u32)0xFF00FF;
                    command = *arg0;
                    *arg0 = command + 2;
                    command[1] = (u32)0x5FFEF3FB;
                    command[0] = 0xFC30FE23;
                    command = *arg0;
                    *arg0 = command + 2;
                    command[0] = 0xFD900000;
                    command[1] = (u32)&D_802C8D20;
                    command = *arg0;
                    *arg0 = command + 2;
                    command[0] = 0xF5900000;
                    command[1] = (u32)0x07080200;
                    command = *arg0;
                    *arg0 = command + 2;
                    command[1] = 0;
                    command[0] = 0xE6000000;
                    command = *arg0;
                    *arg0 = command + 2;
                    command[1] = (u32)0x077FF100;
                    command[0] = 0xF3000000;
                    command = *arg0;
                    *arg0 = command + 2;
                    command[1] = 0;
                    command[0] = 0xE7000000;
                    command = *arg0;
                    *arg0 = command + 2;
                    command[1] = (u32)0x80200;
                    command[0] = 0xF5881000;
                    command = *arg0;
                    *arg0 = command + 2;
                    command[0] = 0xF2000000;
                    command[1] = (u32)0xFC0FC;
                    command = *arg0;
                    *arg0 = command + 2;
                    command[0] = (s32) (((((0x132 - (s32) sp12C) * 4) & 0xFFF) << 0xC) | 0xE4000000 | (((0x128 - (s32) sp128) * 4) & 0xFFF));
                    command[1] = (u32) (((((0xF0 - (s32) sp12C) * 4) & 0xFFF) << 0xC) | (((0xE6 - (s32) sp128) * 4) & 0xFFF));
                    command = *arg0;
                    *arg0 = command + 2;
                    command[1] = 0;
                    command[0] = 0xB3000000;
                    command = *arg0;
                    *arg0 = command + 2;
                    command[1] = (u32)0x03E002E8;
                    command[0] = 0xB2000000;
                } else {
                    if ((s32) D_802C8CEA >= 0x11) {
                        var_a2 = &D_8028FCC0;
                    } else {
                        var_a2 = *((void * *)(D_801F2EB4 + (D_80127CE8[sp133] * 0x8C)));
                    }
                    command = *arg0;
                    *arg0 = command + 2;
                    command[0] = 0xFCFFFFFF;
                    command[1] = (u32)0xFFFCF87C;
                    command = *arg0;
                    *arg0 = command + 2;
                    command[1] = (u32)var_a2;
                    command[0] = 0xFD100000;
                    command = *arg0;
                    *arg0 = command + 2;
                    command[1] = (u32)0x07080200;
                    command[0] = 0xF5100000;
                    command = *arg0;
                    *arg0 = command + 2;
                    command[1] = 0;
                    command[0] = 0xE6000000;
                    command = *arg0;
                    *arg0 = command + 2;
                    command[1] = (u32)0x0778F0BB;
                    command[0] = 0xF3000000;
                    command = *arg0;
                    *arg0 = command + 2;
                    command[1] = 0;
                    command[0] = 0xE7000000;
                    command = *arg0;
                    *arg0 = command + 2;
                    command[1] = (u32)0x80200;
                    command[0] = 0xF5101600;
                    command = *arg0;
                    *arg0 = command + 2;
                    command[0] = 0xF2000000;
                    command[1] = (u32)0xAC0AC;
                    command = *arg0;
                    *arg0 = command + 2;
                    command[0] = (s32) (((((0x132 - (s32) sp12C) * 4) & 0xFFF) << 0xC) | 0xE4000000 | (((0x128 - (s32) sp128) * 4) & 0xFFF));
                    command[1] = (u32) (((((0xF0 - (s32) sp12C) * 4) & 0xFFF) << 0xC) | (((0xE6 - (s32) sp128) * 4) & 0xFFF));
                    command = *arg0;
                    *arg0 = command + 2;
                    command[1] = (u32)0x560;
                    command[0] = 0xB3000000;
                    command = *arg0;
                    *arg0 = command + 2;
                    command[0] = 0xB2000000;
                    command[1] = (u32)0x02AAFD56;
                }
                var_t0 = (sp133 + 1) & 0xFF;
                var_t1 = (u8) var_t0;
            } while (var_t0 < (s32) D_80127CFE[0]);
        }
        sp134 = func_801B6BD8(arg0, arg2);
        if (D_802C8D06 & 0x10) {
            spB0 = func_801B55DC(D_80127CFE[0]);
            command = *arg0;
            *arg0 = command + 2;
            command[0] = 0x03800010;
            command[1] = (u32)&D_80290BE0;
            if (!(D_8004A407 & 1)) {
                sp134 += func_801BE540(arg0, (sp134 << 6) + arg2, &D_80292A54, -300.0f, 360.0f, -1000.0f, 0xFF, 0xFF, 0xFF, 0xFF, 1.0f);
            } else if (D_802C8D0F != 0) {
                sp134 += func_801BE540(arg0, (sp134 << 6) + arg2, &D_80292A60, 0.0f, (f32) (D_802C8D12 + 0x168), -1000.0f, (s32) D_802C8D10, (s32) D_802C8D10, (s32) D_802C8D10, 0xFF, D_80292B20);
            }
            if (sp134 != 0) {
                sp134 += func_801BE540(arg0, (sp134 << 6) + arg2, &spB0, (f32) ((D_802C8D0F * 0x12C) - 0x12C), (f32) (D_802C8D12 + 0x122), -1000.0f, 0xFF, 0x40, 0x40, 0xFF, 1.0f);
            }
        }
    } else {
        if (D_802C8D06 == 5) {
            var_t0_2 = D_802C8D10;
            var_t1_2 = 0xFF;
            spA0 = 0xFF;
            spA1 = 0xFF;
            if (D_802C8D07 == 0xFF) {
                goto block_62;
            }
            if (D_802C8D07 == 0) {
                var_t1_2 = 0;
            } else {
                spA1 = var_t0_2;
                spA0 = 0;
block_62:
                var_t0_2 = 0xFF;
            }
            temp_v0_3 = *((s16 *)(D_802C8C30 + (D_802C8CB8[0] * 4)));
            if (temp_v0_3 < 0xB4) {
                if ((D_802C8CE0 & 1) && (temp_v0_3 > 0)) {
                    var_v1 = (s32) ((temp_v0_3 * temp_v0_3) - (temp_v0_3 * 0x64)) / 50;
                } else {
                    var_v1 = 0;
                }
                if (var_v1 < 0) {
                    var_v1 = 0;
                }
                spA8 = var_v1;
                spA3 = var_t0_2;
                spA2 = var_t1_2;
                sp134 = func_801BDF94(arg0, arg2, (D_80127D30 * 4) - 4 + &D_80127D00, -290.0f, (f32) (var_v1 + 0xF0), -400.0f, 0, 1.0f, 0.0f);
                sp134 += func_801BD640(arg0, (sp134 << 6) + arg2, func_801C9584((D_80127D30 - 1) & 0xFF, 1), -740.0f, (f32) (var_v1 + 0x212), -1600.0f, (s32) var_t0_2, (s32) var_t1_2, (s32) var_t1_2, 0xFF);
                sp134 += func_801BD640(arg0, (sp134 << 6) + arg2, func_801C9584((D_80127D30 - 1) & 0xFF, 0), -770.0f, (f32) (var_v1 + 0x1D6), -1600.0f, 0xFF, 0xFF, 0xFF, 0xFF);
            }
            temp_v0_4 = *((s16 *)(D_802C8C32 + (D_802C8CB9 * 4)));
            if (temp_v0_4 < 0xB4) {
                if ((D_802C8CE0 & 2) && (temp_v0_4 > 0)) {
                    var_v1_2 = (s32) ((temp_v0_4 * temp_v0_4) - (temp_v0_4 * 0x64)) / 50;
                } else {
                    var_v1_2 = 0;
                }
                if (var_v1_2 < 0) {
                    var_v1_2 = 0;
                }
                temp_f0 = (f32) var_v1_2;
                sp68 = temp_f0;
                sp134 += func_801BDF94(arg0, (sp134 << 6) + arg2, (D_80127D31 * 4) - 4 + &D_80127D00, 100.0f, temp_f0 + 240.0f, -400.0f, 0, 1.0f, 0.0f);
                sp134 += func_801BD640(arg0, (sp134 << 6) + arg2, func_801C9584((D_80127D31 - 1) & 0xFF, 1), 420.0f, sp68 + D_80292B24, -1600.0f, (s32) spA1, (s32) spA0, (s32) spA0, 0xFF);
                sp134 += func_801BD640(arg0, (sp134 << 6) + arg2, func_801C9584((D_80127D31 - 1) & 0xFF, 0), 400.0f, sp68 + 470.0f, -1600.0f, 0xFF, 0xFF, 0xFF, 0xFF);
            }
        }
        if (D_801F3600 & 8) {
            func_801BCB70(arg0, D_802C8D14->pixels, func_801B6A68(arg0, D_802C8D14, 0), 0xC0, 0x110, 0x10, 0x10, 0, 0, 0xBF, 0x10F, (f32) -D_802C8CE4, (f32) D_802C8D14->height, (s32) D_802C8D14->width, 0xFF, (u8 *)D_802C8D14 + 0x12);
            if ((D_802C8D14->draw != 0) && (D_802C8D06 != 5)) {
                command = *arg0;
                *arg0 = command + 2;
                command[1] = 0;
                command[0] = 0xE7000000;
                D_802C8D14->draw(arg0, -D_802C8CE4, 0, D_802C8CD4, D_802C8D14, 0);
            }
        } else {
            if (D_801F3600 & 1) {
                func_801BCB70(arg0, D_802C8D14->pixels, func_801B6A68(arg0, D_802C8D14, 0), 0xC0, 0x110, 0x10, 0x10, 0, 0, 0xBF, 0x10F, (f32) -D_802C8CE4, (f32) D_802C8D14->height, (s32) D_802C8D14->width, 0xFF, (u8 *)D_802C8D14 + 0x5A);
            }
            if (D_801F3600 & 2) {
                func_801BCB70(arg0, D_802C8D14->pixels, func_801B6A68(arg0, D_802C8D14, 0), 0xC0, 0x110, 0x10, 0x10, 0, 0, 0xBF, 0x10F, (f32) -D_802C8CE4, (f32) D_802C8D14->height, (s32) D_802C8D14->width, 0xFF, (u8 *)D_802C8D14 + 0x36);
                if ((D_802C8D14->draw != 0) && (D_802C8D06 != 5)) {
                    command = *arg0;
                    *arg0 = command + 2;
                    command[1] = 0;
                    command[0] = 0xE7000000;
                    command = *arg0;
                    *arg0 = command + 2;
                    command[0] = 0xB900031D;
                    command[1] = (u32)0x0F0A4000;
                    command = *arg0;
                    *arg0 = command + 2;
                    command[1] = (u32)0xFA;
                    command[0] = 0xF9000000;
                    command = *arg0;
                    *arg0 = command + 2;
                    command[1] = 0;
                    command[0] = 0xB9000002;
                    command = *arg0;
                    *arg0 = command + 2;
                    command[1] = 0;
                    command[0] = 0xE7000000;
                    D_802C8D14->draw(arg0, -D_802C8CE4, 0, D_802C8CD4, D_802C8D14, 0);
                }
            }
        }
    }
    if ((D_802C8CD4 >= 0x1A) && ((D_802C8CE0 & 3) != 3)) {
        temp_hi = (s32) D_802C8CD4 % 3;
        switch (temp_hi) {                          
        default:
            D_801CD454 = 0;
            break;
        case 0:
            D_801CD454 = 1;
            if ((D_802C8CE4 <= 0) && !(D_802C8D06 & 8)) {
                D_801F3D6C = (s32) D_802C8D14->clipRight;
                D_801F3D70 = 0x27F;
            } else {
                D_801F3D6C = 0;
                D_801F3D70 = 0x27F;
            }
            D_801F3600 = 1;
            break;
        case 1:
            D_801CD454 = 1;
            D_801F3D6C = 0;
            if ((D_802C8CE4 <= 0) && !(D_802C8D06 & 8)) {
                D_801F3D70 = (s32) D_802C8D14->clipLeft;
            } else {
                D_801F3D70 = 2;
            }
            D_801F3600 = 2;
            break;
        case 2:
            D_801CD454 = 1;
            D_801F3600 = 4;
            D_801F3D6C = 0;
            D_801F3D70 = 1;
            break;
        }
    }
    if (D_8012830A != 0) {
        func_801BF678(text + 8, D_8012830A);
        memcpy(text + 2, &D_80292A78, 6);
        if (D_8012830A == 1) {
            text[6] = 0;
        }
        temp_v1_35 = sp134 + func_801BE540(arg0, (sp134 << 6) + arg2, (s32 *) text, -325.0f, (f32) (-0x1C7 - D_802C8D12), -1200.0f, 0, 0, 0, 0xFF, 1.0f);
        sp134 = temp_v1_35;
        sp134 += func_801BE540(arg0, (temp_v1_35 << 6) + arg2, (s32 *) text, -330.0f, (f32) (-0x1C2 - D_802C8D12), -1200.0f, 0xFF, 0xFF, 0xFF, 0xFF, 1.0f);
    }
    command = *arg0;
    *arg0 = command + 2;
    command[0] = 0x06000000;
    command[1] = (u32)&D_801F35D0;
    return sp134;
}
