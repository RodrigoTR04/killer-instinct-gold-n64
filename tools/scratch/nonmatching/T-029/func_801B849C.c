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
extern u8 D_80127CF3[];
extern u8 D_80127CFE[];
extern u8 D_80127D00[];
extern u8 D_80127D32;
extern u8 D_8012830B;
extern s8 D_801CD454;
extern u8 D_801F2EA8[];
extern u8 D_801F2EAC[];
extern u8 D_801F2EB4[];
extern u8 D_801F3608[];
extern u8 D_801F3638;
extern u8 D_801F363C;
extern s32 D_801F3D6C;
extern s32 D_801F3D70;
extern u8 D_8028FCC0[];
extern u8 D_80290BE0[];
extern s32 D_80292A80;
extern s32 D_80292A8C;
extern u8 D_80292AA4[];
extern u8 D_80292AAC[];
extern u8 D_80292AB4[];
extern s32 D_80292ABC;
extern s32 D_80292AD8;
extern f32 D_80292B28;
extern f32 D_80292B2C;
extern f32 D_80292B30;
extern u8 D_802C8CB9;
extern u8 D_802C8CC9;
extern s32 D_802C8CD4;
extern s32 D_802C8CD8;
extern s32 D_802C8CDC;
extern u8 D_802C8CE0;
extern s16 D_802C8CE2;
extern s16 D_802C8CE6;
extern u8 D_802C8CE8;
extern u8 D_802C8CEB;
extern u8 D_802C8D06;
extern u8 D_802C8D0F;
extern u8 D_802C8D10;
extern s16 D_802C8D12;
extern s32 D_802C8D1C;
extern u8 D_802C8D20[];
extern s32 D_802C9F64;
extern s8 D_802C9F69;
extern s32 D_802C9F74;
extern s32 D_802CA064;
extern T029Portrait *D_802C8D18;

s32 func_801B849C(u32 **arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp124;
    u8 sp11F;
    f32 sp118;
    f32 sp114;
    f32 sp110;
    s32 sp9C;
    u8 text[16];
    s8 sp6D;
    s8 sp6C;
    s32 sp60;
    s32 sp5C;
    void *var_a2;
    s16 var_v1;
    s32 temp_a2;
    s32 temp_a3;
    s32 temp_hi;
    s32 temp_t4;
    s32 temp_t4_2;
    s32 temp_t5;
    s32 temp_t7;
    s32 temp_t7_2;
    s32 temp_t9;
    s32 temp_t9_2;
    s32 temp_v0;
    s32 temp_v0_4;
    s32 var_t0_2;
    s32 var_v0;
    s32 var_v1_2;
    s32 var_v1_4;
    u8 temp_v0_2;
    u8 temp_v0_3;
    u8 var_t1;
    T029Portrait *temp_a0;
    u32 *command;
    s32 var_t0;
    T029Portrait *var_v1_3;

    temp_a3 = D_8004A407 & 2;
    sp124 = 0;
    if ((temp_a3 == 0) || (D_802C8D06 != 6)) {
        if ((D_802C8CE0 & 2) && (D_802C8CE6 != 0)) {
            D_802C8CE6 = 0;
            D_802C8CDC = D_802C8CD4 + 1;
            var_v1 = 0;
        } else {
            var_v1 = D_802C8CE6;
            if ((D_802C8CE0 & 1) && (temp_a3 != 0) && (D_802C8CE2 <= 0)) {
                if (var_v1 > 0) {
                    D_802C8CE6 = (var_v1 - (D_802C8CE8 * 9)) - 7;
                    D_802C8CDC = D_802C8CD4 + 1;
                } else {
                    func_801B446C(1);
                }
                goto block_15;
            }
            if ((D_8004A407 == 0) && (var_v1 > 0)) {
                D_802C8CE6 = var_v1 - 0x14;
                D_802C8CDC = D_802C8CD4 + 1;
block_15:
                var_v1 = D_802C8CE6;
            }
        }
        if (var_v1 < 0) {
            D_802C8CE6 = 0;
            D_802C8CDC = D_802C8CD4 + 1;
        }
    }
    temp_a2 = D_802C8CD4;
    temp_v0 = D_802C8CD8;
    var_v1_2 = temp_v0 + 1;
    if ((temp_v0 == temp_a2) || (temp_a2 == var_v1_2)) {
        if (temp_v0 == temp_a2) {
            temp_a0 = (T029Portrait *)(D_801F2EA8 + D_802C8CB9 * 0x8C);
            D_802C8D18 = temp_a0;
            func_801B695C(temp_a0, 1);
        }
        D_801F3638 = 8;
        var_v1_2 = temp_v0 + 1;
        if (temp_v0 == temp_a2) {
            D_801F3D6C = 0;
            D_801F3D70 = 0x27F;
        }
    }
    if ((temp_a2 == var_v1_2) || ((var_v1_3 = (T029Portrait *)(D_801F2EA8 + D_802C8CB9 * 0x8C), (D_802C8D18 == var_v1_3)) && ((D_802C8CE0 & 3) || (D_802C8CE0 & D_8004A407)))) {
        var_v1_3 = (T029Portrait *)(D_801F2EA8 + D_802C8CB9 * 0x8C);
    }
    if (D_802C8D18 == var_v1_3) {
        if (D_801F363C != D_802C8CC9) {
            sp5C = D_802C8D18;
            goto block_32;
        }
    } else {
block_32:
        D_802C8CDC = temp_a2 + 1;
        D_801F3638 = 8;
        D_802CA064 = 0x172;
        D_801F363C = D_802C8CC9;
        func_801B465C(1, 0);
        sp5C = D_802C8D18;
    }
    if ((D_802C8D18 == 0) || (*((s32 *)(D_801F2EAC + (D_802C8CB9 * 0x8C))) == 0)) {
        D_802C8CD8 = D_802C8CDC;
        return 0;
    }
    if (D_802C8D06 & 8) {
        if ((D_8004A407 & 2) && (D_802C8D0F == 0)) {
            if (D_802C8CE0 & 1) {
                func_801B4590(1);
            } else {
                D_80127CFE[1] = (u8) D_80127CFE[0];
            }
        }
        var_t1 = 0;
        sp60 = (s32) D_80127CFE[1];
        if ((s32) D_80127CFE[1] > 0) {
            var_t0 = 0;
            temp_v0_2 = D_80127CFE[1];
            do {
                sp5C = var_t0;
                sp11F = var_t1;
                func_801B677C((var_t0 + 1) & 0xFF, &sp118, &sp114, &sp110, (s32) temp_v0_2);
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
                if ((s32) sp5C >= (s32) D_802C8CEB) {
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
                    command[0] = (s32) ((((((s32) sp118 + 0x190) * 4) & 0xFFF) << 0xC) | 0xE4000000 | (((0x128 - (s32) sp114) * 4) & 0xFFF));
                    command[1] = (u32) ((((((s32) sp118 + 0x14E) * 4) & 0xFFF) << 0xC) | (((0xE6 - (s32) sp114) * 4) & 0xFFF));
                    command = *arg0;
                    *arg0 = command + 2;
                    command[1] = 0;
                    command[0] = 0xB3000000;
                    command = *arg0;
                    *arg0 = command + 2;
                    command[1] = (u32)0x03E002E8;
                    command[0] = 0xB2000000;
                } else {
                    if ((s32) D_802C8CEB >= 0x11) {
                        var_a2 = &D_8028FCC0;
                    } else {
                        var_a2 = *((void * *)(D_801F2EB4 + (D_80127CF3[sp11F] * 0x8C)));
                    }
                    command = *arg0;
                    *arg0 = command + 2;
                    command[1] = (u32)0xFFFCF87C;
                    command[0] = 0xFCFFFFFF;
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
                    command[0] = (s32) ((((((s32) sp118 + 0x190) * 4) & 0xFFF) << 0xC) | 0xE4000000 | (((0x128 - (s32) sp114) * 4) & 0xFFF));
                    command[1] = (u32) ((((((s32) sp118 + 0x14E) * 4) & 0xFFF) << 0xC) | (((0xE6 - (s32) sp114) * 4) & 0xFFF));
                    command = *arg0;
                    *arg0 = command + 2;
                    command[1] = (u32)0x560;
                    command[0] = 0xB3000000;
                    command = *arg0;
                    *arg0 = command + 2;
                    command[0] = 0xB2000000;
                    command[1] = (u32)0x02AAFD56;
                }
                temp_t7 = (sp11F + 1) & 0xFF;
                var_t1 = (u8) temp_t7;
                var_t0 = temp_t7;
            } while (temp_t7 < (s32) D_80127CFE[1]);
            sp60 = (s32) D_80127CFE[1];
        }
        if (D_802C8D06 & 0x20) {
            sp9C = func_801B55DC((u8)sp60);
            command = *arg0;
            *arg0 = command + 2;
            command[0] = 0x03800010;
            command[1] = (u32)&D_80290BE0;
            if (!(D_8004A407 & 2)) {
                var_v0 = func_801BE540(arg0, arg2, &D_80292A80, 300.0f, 360.0f, -1000.0f, 0xFF, 0xFF, 0xFF, 0xFF, 1.0f);
                goto block_57;
            }
            if (D_802C8D0F != 0) {
                var_v0 = func_801BE540(arg0, arg2, &D_80292A8C, 0.0f, (f32) (D_802C8D12 + 0x168), -1000.0f, (s32) D_802C8D10, (s32) D_802C8D10, (s32) D_802C8D10, 0xFF, D_80292B28);
block_57:
                sp124 = var_v0;
            }
            if (sp124 != 0) {
                sp124 += func_801BE540(arg0, (sp124 << 6) + arg2, &sp9C, (f32) (0x12C - (D_802C8D0F * 0x12C)), (f32) (D_802C8D12 + 0x122), -1000.0f, 0xFF, 0x40, 0x40, 0xFF, 1.0f);
            }
        }
    } else {
        temp_v0_3 = D_801F3638;
        if (temp_v0_3 & 8) {
            func_801BCB70(arg0, D_802C8D18->pixels, func_801B6A68(arg0, D_802C8D18, 1), 0xC0, 0x110, -0x10, 0x10, 0, 0, 0xBF, 0x10F, (f32) (D_802C8CE6 + 0x26C), (f32) D_802C8D18->height, (s32) D_802C8D18->width, 0xFF, (u8 *)D_802C8D18 + 0x12);
            if ((D_802C8D18->draw != 0) && (D_802C8D06 != 5)) {
                command = *arg0;
                *arg0 = command + 2;
                command[1] = 0;
                command[0] = 0xE7000000;
                D_802C8D18->draw(arg0, -D_802C8CE6, 0, D_802C8CD4, D_802C8D18, 1);
            }
            if ((D_80127D32 != 0) && (D_802C8D06 == 5) && ((D_802C8CE0 & 3) != 3)) {
                temp_v0_4 = func_801BD640(arg0, arg2, &D_80292AA4, -92.0f, 370.0f, -1600.0f, 0xFF, 0, 0, 0xFF);
                sp124 = temp_v0_4;
                temp_t4 = sp124 + func_801BD640(arg0, (temp_v0_4 << 6) + arg2, &D_80292AAC, -138.0f, 330.0f, -1600.0f, 0xFF, 0, 0, 0xFF);
                sp124 = temp_t4;
                sp124 += func_801BD640(arg0, (temp_t4 << 6) + arg2, (D_80127D32 * 4) - 4 + &D_80127D00, -72.0f, 120.0f, -600.0f, 0xFF, 0, 0, 0xFF);
            } else {
                sp124 = func_801B6BD8(arg0, arg2);
            }
        } else {
            if (temp_v0_3 & 1) {
                func_801BCB70(arg0, D_802C8D18->pixels, func_801B6A68(arg0, D_802C8D18, 1), 0xC0, 0x110, -0x10, 0x10, 0, 0, 0xBF, 0x10F, (f32) (D_802C8CE6 + 0x26C), (f32) D_802C8D18->height, (s32) D_802C8D18->width, 0xFF, (u8 *)D_802C8D18 + 0x5A);
            }
            if (temp_v0_3 & 4) {
                func_801BCB70(arg0, D_802C8D18->pixels, func_801B6A68(arg0, D_802C8D18, 1), 0xC0, 0x110, -0x10, 0x10, 0, 0, 0xBF, 0x10F, (f32) (D_802C8CE6 + 0x26C), (f32) D_802C8D18->height, (s32) D_802C8D18->width, 0xFF, (u8 *)D_802C8D18 + 0x36);
                if ((D_802C8D18->draw != 0) && (D_802C8D06 != 5)) {
                    command = *arg0;
                    *arg0 = command + 2;
                    command[1] = 0;
                    command[0] = 0xE7000000;
                    command = *arg0;
                    *arg0 = command + 2;
                    command[1] = (u32)0xFFFCF67B;
                    command[0] = 0xFCFFFFFF;
                    command = *arg0;
                    *arg0 = command + 2;
                    command[1] = (u32)0xFA;
                    command[0] = 0xF9000000;
                    command = *arg0;
                    *arg0 = command + 2;
                    command[1] = 0;
                    command[0] = 0xB9000002;
                    D_802C8D18->draw(arg0, -D_802C8CE6, 0, D_802C8CD4, D_802C8D18, 1);
                }
            }
        }
    }
    temp_t4_2 = D_802C8CE0 & 3;
    if ((D_802C8CD4 >= 0x1A) && (temp_t4_2 != 3)) {
        temp_hi = (s32) D_802C8CD4 % 3;
        D_802C9F64 = 0x170;
        switch (temp_hi) {                          
        default:
            D_801CD454 = 0;
            break;
        case 0:
            D_801CD454 = 1;
            D_802C9F69 = 3;
            if ((D_802C8CE6 <= 0) && !(D_802C8D06 & 8)) {
                D_801F3D70 = 0x280 - D_802C8D18->clipRight;
            } else {
                D_801F3D70 = 0x27F;
            }
            D_801F3638 = 1;
            break;
        case 1:
            D_801F3638 = 2;
            break;
        case 2:
            if ((D_802C8CE6 <= 0) && !(D_802C8D06 & 8)) {
                D_801F3D6C = 0x280 - D_802C8D18->clipLeft;
                D_801F3D70 = 0x27F;
            } else {
                D_801F3D6C = 0x27E;
                D_801F3D70 = 0x27F;
            }
            D_801F3638 = 4;
            break;
        }
    } else {
        D_801CD454 = 1;
        D_801F3D6C = 0;
        D_801F3D70 = 0x27F;
        if (temp_t4_2 != 3) {
            D_802C9F64 = (s32) (((f32) D_802C8CD4 / 25.0f) * 390.0f);
            D_802C8CDC = D_802C8CD4;
        } else {
            D_802C8CDC = D_802C8CD4 + 1;
        }
        temp_t7_2 = D_802C9F64 + 0xF;
        D_802CA064 = temp_t7_2;
        if (temp_t7_2 >= 0x1E0) {
            D_802CA064 = 0x1DF;
        }
    }
    command = *arg0;
    *arg0 = command + 2;
    command[0] = 0x06000000;
    command[1] = (u32)&D_801F3608;
    D_802C8CD8 = D_802C8CDC;
    if ((D_802C8CDC == (D_802C8CD4 + 1)) || (D_802C8CD4 == D_802C8CDC)) {
        D_801F3D6C = 0;
        D_801F3D70 = 0x27F;
        D_802CA064 = 0x172;
    }
    if (D_8012830B != 0) {
        func_801BF678(text + 8, D_8012830B);
        memcpy(text + 2, &D_80292AB4, 6);
        if (D_8012830B == 1) {
            text[6] = 0;
        }
        temp_t9 = sp124 + func_801BE540(arg0, (sp124 << 6) + arg2, (s32 *) text, 285.0f, (f32) (-0x1C7 - D_802C8D12), -1200.0f, 0, 0, 0, 0xFF, 1.0f);
        sp124 = temp_t9;
        sp124 += func_801BE540(arg0, (temp_t9 << 6) + arg2, (s32 *) text, 290.0f, (f32) (-0x1C2 - D_802C8D12), -1200.0f, 0xFF, 0xFF, 0xFF, 0xFF, 1.0f);
    }
    if (D_802C8D06 == 5) {
        temp_t5 = sp124 + func_801BE540(arg0, (sp124 << 6) + arg2, &D_80292ABC, 0.0f, (f32) (-0x1F9 - D_802C8D12), -1200.0f, 0xFF, 0xFF, 0xFF, 0xFF, D_80292B2C);
        sp124 = temp_t5;
        sp124 += func_801BE540(arg0, (temp_t5 << 6) + arg2, &D_80292AD8, 0.0f, (f32) (-0x221 - D_802C8D12), -1200.0f, 0xFF, 0xFF, 0xFF, 0xFF, D_80292B30);
    }
    var_t0_2 = D_802C8D1C - D_802C9F74;
    if (var_t0_2 < 0x500) {
        var_v1_4 = var_t0_2 & 0x7F;
        if (var_t0_2 < 0) {
            var_t0_2 = 0;
        }
        if (var_v1_4 >= 0x40) {
            var_v1_4 = 0x7F - var_v1_4;
        }
        sp6C = (var_t0_2 >> 7) + 0x30;
        temp_t9_2 = (var_v1_4 * 4) & 0xFF;
        sp6D = 0;
        sp124 += func_801BDA6C(arg0, (sp124 << 6) + arg2, &sp6C, -30.0f, (f32) (-0x1C2 - D_802C8D12), -1200.0f, 0xFF, temp_t9_2, temp_t9_2, 0xFF, 1.5f);
    }
    return sp124;
}
