/* DRAFT. Remaining diff: 570 positional differing words; 2296/2104 bytes */
typedef struct { u16 buttons; s8 x, y; } T033Input;
typedef struct { s32 x,y,z; u8 padC[0x14]; u8 a,b; u16 state; s32 facing; u8 pad28[8]; } T033Snapshot;
typedef struct { u8 kind,pad1[3]; s32 x,y,z; u8 pad10[4]; u8 a,pad15[15]; u8 b,pad25[15]; u16 state; u8 pad36[0x62]; s32 facing; u8 pad9C[0x64]; } T033Player;
extern u8 D_471440;
extern u8 D_472FB0;
extern u8 D_80044DE4;
extern u8 D_8004A258;
extern u8 D_8004A401;
extern u8 D_8004A402;
extern u8 D_8004A404;
extern u8 D_8004A405;
extern s8 D_8004A406;
extern u8 D_8004A407;
extern s8 D_8004A408;
extern u8 D_8004A40A;
extern u8 D_8004A40C;
extern u8 D_8004A40D;
extern u8 D_8004A40E;
extern s8 D_8004A40F;
extern s16 D_8004A410;
extern T033Snapshot D_8004A450[2];
extern T033Snapshot D_8004A4B0;
extern s8 D_8004A4B4;
extern u16 D_8004AA2A;
extern u8 D_8004AC88;
extern s8 D_8004AC8A;
extern u8 D_8004ACDC;
extern s8 D_8004EABD;
extern s8 D_8004EABE;
extern s16 D_8004F392;
extern s8 D_8004F394;
extern s8 D_8004F395;
extern s8 D_8004F398;
extern u8 D_80068520;
extern s32 D_800698C4;
extern s32 D_80069940;
extern u8 D_8011E670;
extern u8 D_80127C50;
extern u8 D_801D3430;
extern s16 D_801D73C8;
extern u16 D_801D876C;
extern u8 D_801D8771;
extern u8 D_801D87EC;
extern u8 D_801D87FE;
extern u8 D_8023E408;
extern void func_8003037C();
extern s32 func_80011FC4();
extern void func_80012100();
extern T033Input ** func_8002B710();
extern void func_8001D37C();
extern void func_8001CF1C();
extern void func_800126D0();
extern s32 func_801AE454();
extern void func_80021ADC();
extern void func_8002B8B0();
extern void func_8002FA5C();
extern void func_8002B6EC();
extern void func_8001272C();
extern void func_8002AA98();
extern void func_80020E98();
extern void func_8001D768();
void func_8001178C(u8 *arg0) {
    T033Input **sp68;
    u8 *sp40;
    void *sp3C;
    T033Player *var_s2;
    T033Snapshot *var_v0;
    s32 temp_a1;
    s32 temp_v0_2;
    s32 var_s0;
    s32 var_s1;
    s32 var_v1;
    u16 var_v1_2;
    u16 var_v1_3;
    u8 *temp_v0_3;
    u8 *temp_v0_6;
    u8 *var_a0;
    u8 temp_v0;
    u8 var_s1_2;
    T033Input **temp_a0;
    T033Input *temp_v0_4;
    T033Input *temp_v0_5;

    var_a0 = arg0;
    if ((D_8004A401 == 3) || (D_8004A401 == 4)) {
        temp_v0 = *(&D_80044DE4 + D_8004AC88);
        var_a0 = &D_8004ACDC;
        if (temp_v0 != 0) {
            if ((s32) D_8004ACDC < (s32) temp_v0) {
                D_8004ACDC += 1;
            } else {
                D_8004A408 = (D_801D8771 ^ 1) + 1;
            }
        }
    }
    sp68 = func_8002B710(var_a0);
    func_8002B6EC();
    var_s0 = func_80011FC4(sp68[0], 0);
    temp_v0_2 = func_80011FC4(sp68[1], 1);
    temp_a1 = temp_v0_2;
    if (D_8004A40C == 0) {
        if ((D_8004F392 != 0) && (D_801D87FE == 0)) {
            D_8004F392 += 1;
        }
        D_80069940 = 0;
        D_801D73C8 = 0;
        if ((D_8004AC88 == 0xC) && (var_v1 = 1, (D_8004A407 == 1))) {
            var_s0 = temp_v0_2;
        } else {
            var_v1 = 0;
        }
        if (sp68[var_v1]->buttons & 0x2000) {
            if (D_8004A405 == 0) {
                D_8004A405 = 1;
                D_8004A406 = 1;
            } else {
                D_8004A406 = 0;
            }
        } else {
            D_8004A405 = 0;
            D_8004A406 = 0;
        }
        D_8004A4B4 = func_801AE454(var_s0, temp_a1);
        if (D_801D87FE != 0) {
            if (D_8004A40D == 0) {
                D_8004A40D = 1;
            }
        } else {
            D_8004A40D = 0;
        }
        func_8001272C();
        if ((&D_801D87EC)[0] != 0) {
            func_8002B8B0((&D_801D87EC)[1] + 2);
        } else if (D_8004AC88 == 0xC) {
            func_8002B8B0(0U);
        } else {
            func_8002B8B0(D_80127C50);
        }
        D_8004A410 -= 1;
        if ((D_8004A410 == 0) && (D_8004A407 == 3)) {
            D_8004A401 = 0;
        }
    }
    D_8004A450[0].x = (s32) ((T033Player *)&D_801D3430)[0].x;
    D_8004A450[0].y = (s32) ((T033Player *)&D_801D3430)[0].y;
    D_8004A450[0].z = (s32) ((T033Player *)&D_801D3430)[0].z;
    D_8004A450[0].state = (u16) ((T033Player *)&D_801D3430)[0].state;
    var_s2 = (T033Player *)&D_801D3430;
    var_s1 = 0;
    D_8004A450[0].a = (u8) ((T033Player *)&D_801D3430)[0].a;
    D_8004A450[0].b = (u8) ((T033Player *)&D_801D3430)[0].b;
    D_8004A450[0].facing = (s32) ((T033Player *)&D_801D3430)[0].facing;
    D_8004A450[1].x = (s32) ((T033Player *)&D_801D3430)[1].x;
    D_8004A450[1].y = (s32) ((T033Player *)&D_801D3430)[1].y;
    D_8004A450[1].z = (s32) ((T033Player *)&D_801D3430)[1].z;
    D_8004A450[1].state = (u16) ((T033Player *)&D_801D3430)[1].state;
    D_8004A450[1].a = (u8) ((T033Player *)&D_801D3430)[1].a;
    D_8004A450[1].b = (u8) ((T033Player *)&D_801D3430)[1].b;
    D_8004A450[1].facing = (s32) ((T033Player *)&D_801D3430)[1].facing;
    do {
        if ((D_8004A40C == 0) && (D_8004A450[var_s1].state == 0xBE) && (D_801D87FE == 0)) {
            func_8003037C(&D_8023E408, (&D_472FB0 - &D_471440) + 0x8023D580, 0x93);
        }
        temp_v0_3 = D_8004EA9C + var_s1;
        if (((u8 *)var_s2)[-0x170] == 0x47) {
            *temp_v0_3 = var_s2->kind - 1;
            sp3C = (var_s1 * 0x320) + &D_8011E670;
            sp40 = temp_v0_3;
            func_80012100(D_8004EA9C[0], D_8004EA9C[1]);
            func_8001CF1C();
            func_8001D37C(D_8004EA9C[0], D_8004EA9C[1]);
            func_80021ADC(var_s1 & 0xFF, *sp40);
            func_8001D768(var_s1 + 8, sp3C);
            func_80020E98(0, D_8004EA9C[0], 0);
            func_80020E98(1 & 0xFF, D_8004EA9C[1], 0);
            D_8004F398 = 0;
            D_8004F395 = 0;
            D_8004F394 = 0;
            D_8004EABD = 0xFF;
            D_8004EABE = 0xFF;
        }
        var_s1 += 1;
        var_s2++;
    } while (var_s1 < 2);
    var_s1_2 = 0;
    if (D_8004AC88 == 0) {
        var_v0 = D_8004A450;
        do {
            if (var_v0->facing == 0) {
                var_v0->facing = (s32) -var_v0->z;
            } else {
                var_v0->facing = 0;
            }
            var_v0++;
        } while (var_v0 != &D_8004A4B0);
    }
    D_8004AC8A = 1;
    if (1 & 0xFF) {
        D_8004A450[0].facing = (s32) -D_8004A450[0].facing;
        D_8004A450[1].facing = (s32) -D_8004A450[1].facing;
    }
    do {
        if (D_80068520 & (1 << var_s1_2)) {
            temp_a0 = sp68 + var_s1_2;
            if ((D_8004A40C != 0) && ((var_s1_2 + 1) != D_8004A407) && (var_s1_2 == D_8004A40E)) {
                if ((s32) D_8004A40C < 3) {
                    temp_v0_4 = *temp_a0;
                    var_v1_2 = temp_v0_4->buttons;
                    if ((var_v1_2 & 0x800) || (temp_v0_4->y >= 0x29)) {
                        D_8004A40C = 1;
                        var_v1_2 = (*temp_a0)->buttons;
                    }
                    if ((var_v1_2 & 0x400) || ((*temp_a0)->y < -0x28)) {
                        D_8004A40C = 2;
                    }
                } else {
                    temp_v0_5 = *temp_a0;
                    var_v1_3 = temp_v0_5->buttons;
                    if ((var_v1_3 & 0x200) || (temp_v0_5->x < -0x28)) {
                        D_8004A40C = 3;
                        var_v1_3 = (*temp_a0)->buttons;
                    }
                    if ((var_v1_3 & 0x100) || ((*temp_a0)->x >= 0x29)) {
                        D_8004A40C = 4;
                    }
                }
            }
            if ((*temp_a0)->buttons & 0x1000) {
                if (D_8004A407 == 3) {
                    func_800126D0(temp_a0, 2U);
                    D_8004A401 = 0;
                } else if ((var_s1_2 + 1) == D_8004A407) {
                    func_800126D0(temp_a0, 2U);
                    func_8002FA5C(((s32 *)&D_8004A258)[3], 8, D_8004AA2A);
                    D_8004A401 = 0;
                    D_8004A404 = 1;
                } else {
                    temp_v0_6 = var_s1_2 + &D_8004A40A;
                    if ((*temp_v0_6 == 1) && ((D_8004A401 != 1) || (D_800698C4 == 0))) {
                        *temp_v0_6 = 0;
                        switch (D_8004A40C) {
                        case 0:
                            D_8004A40C = 1;
                            D_8004A40F = 0;
                            func_8002AA98(0x4650, 2U);
                            func_8002FA5C(((s32 *)&D_8004A258)[3], 8, 0U);
                            D_8004A40E = var_s1_2;
                            break;
                        case 1:
                            if (var_s1_2 == D_8004A40E) {
                                D_8004A40C = 0;
                                D_8004A40F = 0;
                                func_8002AA98(0x7FFF, 2U);
                                func_8002FA5C(((s32 *)&D_8004A258)[3], 8, D_8004AA2A);
                            }
                            break;
                        case 2:
                            if (var_s1_2 == D_8004A40E) {
                                D_8004A40C = 3;
                                D_8004A40F = 0;
                            }
                            break;
                        case 3:
                            if (var_s1_2 == D_8004A40E) {
                                D_8004A40C = 2;
                                D_8004A40F = 0x3C;
                            }
                            break;
                        case 4:
                            if (var_s1_2 == D_8004A40E) {
                                D_8004A40C = 0;
                                D_8004A401 = 0;
                                D_8004A40F = 0;
                                D_8004A404 = 2;
                                func_800126D0(temp_a0, 2U);
                                func_8002FA5C(((s32 *)&D_8004A258)[3], 8, D_8004AA2A);
                            }
                            break;
                        }
                    }
                }
            } else {
                *(&D_8004A40A + var_s1_2) = 1;
            }
        }
        var_s1_2 += 1;
    } while (var_s1_2 != 2);
    if ((D_8004A402 == 0) && (D_801D876C != 0)) {
        D_8004A402 = 1;
        D_8004A401 = 2;
    }
}
