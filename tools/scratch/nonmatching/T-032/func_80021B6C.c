/* DRAFT. Remaining diff: 1711 positional words differ; 6920/6896 bytes; switch-generated rodata also differs */
typedef struct { u32 w0,w1; } T032Gfx21B;
typedef struct { f32 x,y,z,enabled,lastPlayer; } T032Transform21B;
typedef struct { void *data; u8 pad[12]; } T032Model21B;
typedef struct { void *first,*second; } T032Cache21B;
typedef struct { u8 kind; u8 pad1[3]; s32 x; s32 y; s32 z; u8 pad10[4]; u8 frame; u8 pad15[15]; u8 facing; u8 pad25[15]; u16 resource; u8 pad36[4]; u8 variant; u8 pad3B[25]; u8 player; u8 character; u8 model; u8 pad57[1]; u16 scaleX; u16 scaleY; u8 pad5C[12]; s32 screenX; s32 screenY; u32 scale; u8 pad74[24]; u8 flags; u8 pad8D[1]; u8 palette; u8 pad8F[5]; u8 image; u8 pad95[2]; u8 fade; s32 altZ; u8 pad9C[44]; u16 clipRight; u16 clipLeft; u8 tail[52]; } T032Actor21B;
extern T032Actor21B D_801D3430[];
extern T032Cache21B D_8004D278[][3];
extern u8 D_801D7370[],D_8004EA9C[];
extern u8 D_80044A24;
extern s32 D_8004EA78,D_8004D1A8,D_8004D1AC,D_8004D1C4,D_8004D1C8;
extern s16 D_8004D272,D_8004F392;
extern s8 D_8004EA9A,D_8004EAB8,D_8004AC8E[3],D_8004AC92[3],D_8004AC8F,D_8004AC90,D_8004AC93,D_8004AC94;
extern u8 D_8004A407,D_8004A408,D_8004EABA,D_8004EABB,D_8004EABC,D_8004EABD,D_8004EABE,D_8004EABF,D_8004EAC0,D_8004F395;
extern u16 D_800460D4[],*D_800460E0[],*D_800460E8[],*D_800460F0[],*D_800460F8[];
extern u32 *D_800460D8[];
extern u8 D_8011ECB0[],D_80196010[],D_8019A010[],D_8019F400[],D_801A3A90[],D_801AA940[],D_80350000[],D_8035E100[];
extern void func_80023EF0(void),func_8001E33C(T032Gfx21B **,u8),func_8002E08C(T032Actor21B *,T020Position *);
extern void func_8002BB74(s32,s32,s32,f32 *,f32 *,f32 *),func_8002DCC8(f32,f32,f32,void *);
extern void func_8001C5AC(T032Gfx21B **,s32,void *,u8,s32,f32,f32,f32,f32,f32,f32,u32);
extern void func_8001D7E4(s32,u8,u8,s32,s32),func_8001EC74(T032Gfx21B **,s32,s32,u32,u32,s32,s32,s32);
extern void func_800249DC(u8,u8,u8 *),func_80024028(T032Gfx21B **,u8,u8),func_800241BC(u8),func_80024B0C(T032Gfx21B **,u8),func_80027E1C(T032Gfx21B **,T032Actor21B *);
void func_80021B6C(T032Gfx21B **arg0) {
    u8 sp18B;
    u8 sp189;
    u8 sp188;
    u8 bankUsed[2][6];
    u8 spriteUsed[6][2];
    u8 sp17B;
    u8 order[2];
    s32 sp174;
    u8 sp167;
    u8 sp165;
    u8 sp164;
    u8 sp163;
    u8 sp162;
    u8 sp160;
    s32 sp158;
    s32 sp154;
    s32 sp150;
    s32 sp14C;
    s32 sp148;
    s32 sp144;
    f32 sp128;
    f32 sp124;
    f32 sp120;
    T020Position sp114;
    T032Gfx21B *sp110;
    void *sp10C;
    s32 sp78;                                       /* compiler-managed */
    u8 *sp70;
    f32 var_f18;
    s16 temp_t1;
    s16 temp_t1_2;
    s32 temp_hi;
    s32 temp_t0_2;
    s32 temp_t2;
    s32 temp_t4_2;
    s32 temp_t6;
    s32 temp_t6_2;
    s32 temp_t6_5;
    s32 temp_t7;
    s32 temp_t9_5;
    s32 temp_v0_11;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v1_10;
    s32 temp_v1_11;
    s32 temp_v1_12;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 temp_v1_8;
    s32 temp_v1_9;
    s32 var_s2;
    s32 var_s7;
    s32 var_t0_2;
    s32 var_t1;
    s32 var_t1_2;
    s32 var_t2;
    s32 var_t3;
    s32 var_v1_2;
    s8 temp_v0_3;
    s8 var_fp;
    s8 var_fp_3;
    s8 var_fp_4;
    u32 temp_t9;
    u8 *temp_t0;
    u8 *temp_v1_7;
    u8 *var_v0;
    u8 temp_a1;
    u8 temp_s1;
    u8 temp_t0_3;
    u8 temp_t0_4;
    u8 temp_t1_3;
    u8 temp_t4_5;
    u8 temp_t5_5;
    u8 temp_t7_2;
    u8 temp_t8_6;
    u8 temp_v0_2;
    u8 temp_v0_8;
    u8 var_fp_2;
    u8 var_s1;
    u8 var_s3;
    u8 var_s5;
    u8 var_t0;
    u8 var_v1;
    u8 *temp_a0;
    T032Actor21B *temp_s0;
    T032Gfx21B *temp_t4;
    T032Gfx21B *temp_t4_3;
    T032Gfx21B *temp_t4_4;
    T032Gfx21B *temp_t4_6;
    T032Gfx21B *temp_t4_7;
    T032Gfx21B *temp_t5;
    T032Gfx21B *temp_t5_2;
    T032Gfx21B *temp_t5_3;
    T032Gfx21B *temp_t5_4;
    T032Gfx21B *temp_t5_6;
    T032Gfx21B *temp_t5_7;
    T032Gfx21B *temp_t5_8;
    T032Gfx21B *temp_t6_3;
    T032Gfx21B *temp_t6_4;
    T032Gfx21B *temp_t6_6;
    T032Gfx21B *temp_t7_3;
    T032Gfx21B *temp_t7_4;
    T032Gfx21B *temp_t7_5;
    T032Gfx21B *temp_t8;
    T032Gfx21B *temp_t8_2;
    T032Gfx21B *temp_t8_3;
    T032Gfx21B *temp_t8_4;
    T032Gfx21B *temp_t8_5;
    T032Gfx21B *temp_t9_2;
    T032Gfx21B *temp_t9_3;
    T032Gfx21B *temp_t9_4;
    T032Gfx21B *temp_t9_6;
    u8 *temp_v0;
    T032Transform21B *temp_v0_10;
    T032Gfx21B *temp_v0_12;
    T032Gfx21B *temp_v0_4;
    T022Sprite *temp_v0_7;
    T032Transform21B *temp_v0_9;
    T032Gfx21B *temp_v1;
    T032Gfx21B *temp_v1_2;
    T032Gfx21B *temp_v1_5;
    u8 *temp_v1_6;

    func_80023EF0();
    sp17B = 0;
    sp188 = 0;
    sp189 = 0;
    sp18B = 0;
    var_fp = 0;
    for (var_fp = 0; var_fp < 6; var_fp++) {
        spriteUsed[var_fp][0] = 0; spriteUsed[var_fp][1] = 0;
        bankUsed[1][var_fp] = 0; bankUsed[0][var_fp] = 0;
    }
    temp_t4 = *arg0;
    sp110 = temp_t4;
    sp110 = temp_t4 + 1;
    temp_t4->w1 = -1;
    temp_t4->w0 = 0xBB000201;
    temp_t8 = sp110;
    sp110 = temp_t8 + 1;
    temp_t8->w1 = 0;
    temp_t8->w0 = 0xE7000000;
    temp_t5 = sp110;
    sp110 = temp_t5 + 1;
    temp_t5->w1 = 0;
    temp_t5->w0 = 0xBA001701;
    temp_t8_2 = sp110;
    sp110 = temp_t8_2 + 1;
    temp_t8_2->w1 = 0;
    temp_t8_2->w0 = 0xBA001301;
    temp_t5_2 = sp110;
    sp110 = temp_t5_2 + 1;
    var_fp_2 = 0x27;
    temp_t5_2->w1 = 0;
    temp_t5_2->w0 = 0xBA001001;
    do {
        temp_v0_2 = D_801D7370[var_fp_2];
        if ((s32) temp_v0_2 < 2) {
            order[temp_v0_2] = var_fp_2;
        }
        var_fp_2 = (u8) (s8) (var_fp_2 - 1);
    } while ((s32) var_fp_2 >= 0);
    if ((s32) order[0] < (s32) order[1]) {
        var_fp_3 = 0;
    } else {
        var_fp_3 = 1;
    }
    temp_v0_3 = var_fp_3 ^ 1;
    if (((&D_801D3430[var_fp_3])->scale - (&D_801D3430[temp_v0_3])->scale) < -0x80) {
        D_801D7370[order[var_fp_3]] = temp_v0_3;
        D_801D7370[order[temp_v0_3]] = var_fp_3;
    }
    var_fp_4 = 0x27;
    var_s7 = 0;
    var_s5 = 0;
    var_s3 = 0;
    var_s2 = 0;
    do {
        temp_a1 = D_801D7370[var_fp_4];
        sp167 = 0;
        if ((s32) temp_a1 < 2) {
            if ((temp_a1 + 1) != D_8004A408) {
                func_8001E33C(&sp110, temp_a1);
            }
        } else {
            temp_v0_4 = sp110;
            sp110 = temp_v0_4 + 1;
            temp_s0 = &D_801D3430[temp_a1];
            temp_v0_4->w1 = 0;
            temp_v0_4->w0 = 0xE7000000;
            temp_s1 = temp_s0->kind;
            switch (temp_s1) {                      /* switch 1 */
            case 0x3D:                              /* switch 1 */
                temp_t6_2 = temp_s0->z;
                temp_s0->z = (s32) -temp_s0->altZ;
                sp174 = temp_t6_2;
                /* fallthrough */
            case 0x11:                              /* switch 1 */
            case 0x12:                              /* switch 1 */
            case 0x15:                              /* switch 1 */
            case 0x1A:                              /* switch 1 */
            case 0x1E:                              /* switch 1 */
            case 0x21:                              /* switch 1 */
            case 0x29:                              /* switch 1 */
            case 0x38:                              /* switch 1 */
                var_s3 = temp_s0->player;
                if ((temp_s1 != 0x15) || (temp_s0->variant == 0)) {
                    func_8002E08C(temp_s0, &sp114);
                }
                if ((s32) temp_s0->facing >= 0x80) {
                    sp165 = 1;
                } else {
                    sp165 = 0;
                }
                var_s7 = (s32) temp_s0->scaleX;
                var_s2 = (s32) temp_s0->resource;
                var_s5 = temp_s0->frame;
                sp150 = (s32) temp_s0->scaleY;
                if (var_s7 == 0) {
                    var_s7 = 0x1000;
                }
                if (sp150 == 0) {
                    sp150 = 0x1000;
                }
                break;
            case 0x28:                              /* switch 1 */
            case 0x3B:                              /* switch 1 */
                func_8002BB74(temp_s0->x, temp_s0->y, temp_s0->z, &sp120, &sp124, &sp128);
                break;
            }
            switch (temp_s1) {                      /* switch 2 */
            case 0x12:                              /* switch 2 */
                sp144 = 4;
                sp148 = (s32) temp_s0->clipLeft;
                if (temp_s0->character != (D_8004EA9C[var_s3] + 1)) {
                    var_s1 = (var_s3 ^ 1) & 0xFF;
                } else {
                    var_s1 = var_s3 & 0xFF;
                }
                if (D_8004AC88 == 0xC) {
                    var_s3 = 0;
                    var_s1 = 0;
                }
                sp14C = (s32) temp_s0->clipRight;
                func_800249DC(var_s1, (u8) var_s2, &sp160);
                var_t1 = sp14C;
                if (spriteUsed[sp160][var_s1] == 0) {
                    if ((D_8004EA9C[var_s3] == 0) && (var_s2 == 0x58) && (var_s5 != 0) && ((s32) var_s5 < 8)) {
                        sp144 = 0xB - var_s5;
                        var_s5 = 7;
                    }
                    if ((D_8004D278[var_s2][var_s1].first != 0) && (sp160 != 4) && (sp160 != 5)) {
                        sp167 = 1;
                    } else {
                        temp_t0 = D_8004EA9C[var_s1];
                        var_v1 = *temp_t0;
                        if ((var_v1 == 9) && (var_s2 == 0xC6)) {
                            D_8004EAB8 = 1;
                        }
                        if (sp160 == 5) {
                            if ((var_s2 == D_8004EABD) && (D_8004EABE == var_s5)) {
                                temp_t4_2 = (D_8004EABF & 0xFF) * 0x17BB0;
                                D_8004EAC0 = D_8004EABF;
                                D_8004D1A8 = temp_t4_2 + 0x80254860;
                                D_8004D1AC = temp_t4_2 + 0x80264580;
                                D_8004D1C4 = temp_t4_2 + 0x80320E20;
                                D_8004D1C8 = temp_t4_2 + 0x80330B40;
                            } else {
                                D_8004EABD = (u8) var_s2;
                                D_8004EABE = var_s5;
                                D_8004EABF = D_8004EAC0;
                                sp70 = temp_t0;
                                func_8001D7E4(D_8004EA78, (u8) var_s2, var_s5, var_s1 & 0xFF, 0);
                                goto block_55;
                            }
                        } else {
                            sp70 = temp_t0;
                            func_8001D7E4(D_8004EA78, (u8) var_s2, var_s5, var_s1 & 0xFF, 0);
block_55:
                            var_v1 = *temp_t0;
                        }
                        if ((var_v1 == 9) && (var_s2 == 0xC6)) {
                            D_8004EAB8 = 0;
                        }
                    }
                }
                if (sp167 == 0) {
                    var_t0 = ((u8 *)&D_8004CED0[D_8004EA78].flags)[1];
                    if ((sp160 != 4) && (sp160 != 5)) {
                        sp14C = var_t1;
                        sp163 = var_t0;
                        func_80024028(&sp110, temp_s0->palette, temp_s0->fade);
                        var_t0 = sp163;
                        var_t1 = sp14C;
                    }
                    if ((var_t1 != 0) || (sp148 != 0)) {
                        if (var_t1 == 0) {
                            var_t1 = 0x140;
                        }
                        temp_v1 = sp110;
                        sp110 = temp_v1 + 1;
                        temp_v1->w0 = (s32) ((((s32) ((f32) sp148 * 4.0f) & 0xFFF) << 0xC) | 0xED000000);
                        temp_v1->w1 = (s32) ((((s32) ((f32) (var_t1 << D_8004AA28) * 4.0f) & 0xFFF) << 0xC) | ((s32) ((f32) (0xF0 << D_8004AA28) * 4.0f) & 0xFFF));
                    }
                    temp_t4_3 = sp110;
                    if ((sp160 == 4) || (sp160 == 5)) {
                        sp110 = temp_t4_3 + 1;
                        temp_t4_3->w0 = 0xFA000100;
                        temp_t4_3->w1 = 0;
                        temp_t5_3 = sp110;
                        sp110 = temp_t5_3 + 1;
                        temp_t5_3->w1 = 0;
                        temp_t5_3->w0 = 0xFB000000;
                    }
                    temp_t9 = (u32) (temp_s0->scale * sp144) >> 2;
                    sp14C = var_t1;
                    func_8001EC74(&sp110, (s32) temp_s0->screenX / 16, (s32) temp_s0->screenY / 16, (u32) (temp_t9 * var_s7) >> 0xC, (u32) (temp_t9 * sp150) >> 0xC, (s32) var_t0, (s32) sp165, 0);
                    temp_t9_2 = sp110;
                    sp110 = temp_t9_2 + 1;
                    temp_t9_2->w1 = 0xC00;
                    temp_t9_2->w0 = 0xBA000903;
                    if ((sp14C != 0) || (sp148 != 0)) {
                        temp_v1_2 = sp110;
                        sp110 = temp_v1_2 + 1;
                        temp_v1_2->w0 = 0xED000000;
                        temp_v1_2->w1 = (s32) ((((s32) ((f32) (0x140 << D_8004AA28) * 4.0f) & 0xFFF) << 0xC) | ((s32) ((f32) (0xF0 << D_8004AA28) * 4.0f) & 0xFFF));
                    }
                    spriteUsed[sp160][var_s1] = 1;
                }
                break;
            case 0x11:                              /* switch 2 */
                temp_v0_5 = var_s2 - 1;
                D_8004EA78 = 0xF;
                var_t3 = temp_v0_5;
                if ((temp_v0_5 < 0) || (temp_v0_5 >= 2)) {
                    var_t3 = 0;
                }
                temp_t7 = (var_s5 - 1) & 0xFF;
                temp_v0_6 = D_800460D4[var_t3] - 1;
                var_s5 = (u8) temp_t7;
                if (temp_v0_6 < temp_t7) {
                    var_s5 = temp_v0_6 & 0xFF;
                }
                temp_t0_2 = var_t3 * 4;
                temp_v0_7 = &D_8004CED0[D_8004EA78];
                temp_v0_7->unk0 = (s32) D_800460D8[var_t3][var_s5];
                temp_t2 = var_s5 * 2;
                temp_t1 = D_800460E0[var_t3][var_s5];
                temp_v0_7->width = temp_t1;
                temp_v0_7->width2 = temp_t1;
                temp_t1_2 = D_800460E8[var_t3][var_s5];
                temp_v0_7->height = temp_t1_2;
                temp_v0_7->height2 = temp_t1_2;
                temp_v0_7->halfWidth = (s16) D_800460F0[var_t3][var_s5];
                temp_v0_7->halfHeight = (s16) D_800460F8[var_t3][var_s5];
                temp_v1_3 = temp_s0->scale;
                func_8001EC74(&sp110, (s32) temp_s0->screenX / 16, (s32) temp_s0->screenY / 16, (u32) (temp_v1_3 * var_s7) >> 0xC, (u32) (temp_v1_3 * sp150) >> 0xC, 8, (s32) sp165, 0);
                break;
            case 0x15:                              /* switch 2 */
            case 0x1A:                              /* switch 2 */
                if (var_s2 == 0xC) {
                    var_s7 *= 2;
                    sp150 *= 2;
                }
                D_8004EA9A = 2;
                switch (temp_s1) {                  /* switch 3; irregular */
                case 21:                            /* switch 3 */
                    D_8004EA78 = 0xB;
                    sp78 = (s32) sp18B;
                    func_80024028(&sp110, temp_s0->palette, temp_s0->fade);
                    if (temp_s0->variant != 0) {
                        if (D_8004A407 == 1) {
                            var_v1_2 = 0x8020B480;
                        } else {
                            var_v1_2 = 0x802D7A40;
                        }
                        D_8004CED0[D_8004EA78].data = (sp78 * 0x1E40) + var_v1_2 + (D_80044A24 * 0x30D40);
                        func_8001D7E4(D_8004EA78, (u8) var_s2, var_s5, 2, 0);
                        sp18B += 1;
                    } else if (sp78 < 2) {
                        D_8004CED0[D_8004EA78].data = (D_80044A24 * 0x3C80) + (sp18B * 0x1E40) + &D_8011ECB0;
                        func_8001D7E4(D_8004EA78, (u8) var_s2, var_s5, 2, 0);
                        sp18B += 1;
                    }
                    break;
                default:                            /* switch 3 */
                case 26:                            /* switch 3 */
                    D_8004EA78 = 0x11;
                    func_80024028(&sp110, 2U, temp_s0->fade);
                    break;
                }
                temp_v1_4 = temp_s0->scale;
                func_8001EC74(&sp110, (s32) temp_s0->screenX / 16, (s32) temp_s0->screenY / 16, (u32) (temp_v1_4 * var_s7) >> 0xC, (u32) (temp_v1_4 * sp150) >> 0xC, 5, (s32) sp165, 0);
                temp_t8_3 = sp110;
                sp110 = temp_t8_3 + 1;
                temp_t8_3->w1 = 0xC00;
                temp_t8_3->w0 = 0xBA000903;
                break;
            case 0x1E:                              /* switch 2 */
                if (temp_s0->character == (D_8004EA9C[0] + 1)) {
                    var_s3 = 0;
                } else {
                    var_s3 = 1;
                }
                func_80024028(&sp110, temp_s0->palette, temp_s0->fade);
                switch (var_s2) {                   /* switch 4; irregular */
                case 0x15:                          /* switch 4 */
                    D_8004EA78 = 0x10;
                    D_8004EA9A = 3;
                    var_s3 = 2;
                    if ((s32) sp189 <= 0) {
                        func_8001D7E4(D_8004EA78, (u8) var_s2, var_s5, 2, 0);
                    }
                    sp189 += 1;
                    break;
                case 0x6D:                          /* switch 4 */
                case 0x74:                          /* switch 4 */
                case 0xAE:                          /* switch 4 */
                case 0xB0:                          /* switch 4 */
                case 0xB1:                          /* switch 4 */
                case 0xC7:                          /* switch 4 */
                    if ((var_s2 == 0xB1) || (var_s2 == 0xB0) || (var_s2 == 0xC7)) {
                        var_s3 = temp_s0->player;
                    }
                    if (var_s2 == 0xAE) {
                        var_s3 = (temp_s0->player ^ 1) & 0xFF;
                    }
                    if ((var_s2 == 0xAE) && (D_8004EA9C[var_s3] == 4)) {
                        temp_t7_2 = (temp_s0->player ^ 1) & 0xFF;
                        var_s3 = temp_t7_2;
                        if (D_8004F395 == 0) {
                            func_800241BC(temp_t7_2);
                            D_8004F392 = 1;
                        }
                        temp_t5_4 = sp110;
                        temp_t6_3 = temp_t5_4 + 1;
                        sp110 = temp_t6_3;
                        temp_t5_4->w0 = (s32) (((s32) ((f32) (0xDC - (D_8004F392 * 3)) * 4.0f) & 0xFFF) | 0xED000000);
                        temp_t5_4->w1 = (s32) ((((s32) ((f32) (0x140 << D_8004AA28) * 4.0f) & 0xFFF) << 0xC) | ((s32) ((f32) (0xF0 << D_8004AA28) * 4.0f) & 0xFFF));
                        if ((D_8004F392 * 5) < 0xFF) {
                            temp_t6_4 = sp110;
                            sp110 = temp_t6_4 + 1;
                            temp_t6_4->w0 = 0xFA000100;
                            temp_t6_4->w1 = (s32) ((D_8004F392 * 5) & 0xFF);
                        } else {
                            sp110 = temp_t6_3 + 1;
                            temp_t6_3->w1 = 0xFF;
                            temp_t5_4[1].w0 = 0xFA000100;
                        }
                        func_80024B0C(&sp110, var_s3);
                        temp_v1_5 = sp110;
                        sp110 = temp_v1_5 + 1;
                        temp_v1_5->w0 = 0xED000000;
                        temp_v1_5->w1 = (s32) ((((s32) ((f32) (0x140 << D_8004AA28) * 4.0f) & 0xFFF) << 0xC) | ((s32) ((f32) (0xF0 << D_8004AA28) * 4.0f) & 0xFFF));
                        temp_t9_3 = sp110;
                        sp110 = temp_t9_3 + 1;
                        temp_t9_3->w1 = 0;
                        temp_t9_3->w0 = 0xB9000002;
                    } else {
                        func_800249DC(var_s3, (u8) var_s2, &sp160);
                        temp_v1_6 = bankUsed[var_s3];
                        var_v0 = temp_v1_6 + sp160;
                        if ((s32) *var_v0 <= 0) {
                            sp78 = temp_v1_6;
                            func_8001D7E4(D_8004EA78, (u8) var_s2, var_s5, var_s3 & 0xFF, 0);
                            var_v0 = temp_v1_6 + sp160;
                        }
                        *var_v0 = 1;
                    }
                    break;
                case 0xAF:                          /* switch 4 */
                    temp_t5_5 = (temp_s0->player ^ 1) & 0xFF;
                    D_8004EA9A = 6;
                    var_s3 = temp_t5_5;
                    temp_v1_7 = bankUsed[temp_t5_5];
                    temp_v0_8 = temp_v1_7[1];
                    temp_t6_5 = (temp_v0_8 * 2) + temp_t5_5 + 0x12;
                    D_8004EA78 = temp_t6_5;
                    if ((s32) temp_v0_8 < 3) {
                        sp70 = temp_v1_7;
                        func_8001D7E4(temp_t6_5, (u8) var_s2, var_s5, temp_t5_5 & 0xFF, 0);
                        temp_v1_7[1] = (u8) (temp_v1_7[1] + 1);
                    } else {
                        D_8004EA78 = temp_t5_5 + 0x12;
                    }
                    break;
                default:                            /* switch 4 */
                    D_8004EA78 = 0x11;
                    break;
                }
                if (((var_s2 != 0xAE) || (D_8004EA9C[var_s3] != 4)) && (D_8004EA78 != 0x11)) {
                    temp_v1_8 = temp_s0->scale;
                    func_8001EC74(&sp110, (s32) temp_s0->screenX / 16, (s32) temp_s0->screenY / 16, (u32) (temp_v1_8 * var_s7) >> 0xC, (u32) (temp_v1_8 * sp150) >> 0xC, 5, (s32) sp165, 0);
                }
                temp_t9_4 = sp110;
                sp110 = temp_t9_4 + 1;
                temp_t9_4->w1 = 0xC00;
                temp_t9_4->w0 = 0xBA000903;
                break;
            case 0x21:                              /* switch 2 */
                func_80027E1C(&sp110, temp_s0);
                break;
            case 0x28:                              /* switch 2 */
                func_8002DCC8(sp120, sp124, sp128, &temp_s0->scale);
                temp_t5_6 = sp110;
                sp110 = temp_t5_6 + 1;
                temp_t5_6->w1 = 0x80000;
                temp_t5_6->w0 = 0xBA001301;
                temp_t0_3 = temp_s0->model;
                temp_v0_9 = &((T032Transform21B *)&D_8004A9D8)[temp_t0_3];
                func_8001C5AC(&sp110, 0, 0, temp_t0_3, (s32) temp_s0->player, sp120, sp124, sp128, temp_v0_9->x, temp_v0_9->y, temp_v0_9->z, 0U);
                temp_t4_4 = sp110;
                sp110 = temp_t4_4 + 1;
                temp_t4_4->w1 = 0;
                temp_t4_4->w0 = 0xE7000000;
                temp_t8_4 = sp110;
                sp110 = temp_t8_4 + 1;
                temp_t8_4->w1 = 0;
                temp_t8_4->w0 = 0xBA001301;
                temp_t4_5 = temp_s0->player;
                var_f18 = (f32) temp_t4_5;
                if ((s32) temp_t4_5 < 0) {
                    var_f18 += 4294967296.0f;
                }
                ((T032Transform21B *)&D_8004A9D8)[temp_s0->model].lastPlayer = var_f18;
                break;
            case 0x29:                              /* switch 2 */
                switch (D_8004AC88) {               /* switch 5 */
                case 8:                             /* switch 5 */
                    D_8004EA9A = 0xC;
                    var_s2 = 0x46;
                    D_8004EA78 = 0x1F;
                    sp78 = (s32) sp17B;
                    func_80024028(&sp110, 9U, 0U);
                    if (sp78 <= 0) {
                        func_8001D7E4(D_8004EA78, 0x46U, var_s5, 2, 0);
                        sp17B += 1;
                    }
                    temp_v1_9 = temp_s0->scale;
                    func_8001EC74(&sp110, (s32) temp_s0->screenX / 16, (s32) temp_s0->screenY / 16, (u32) (temp_v1_9 * var_s7 * 2) >> 0xC, (u32) (temp_v1_9 * sp150 * 2) >> 0xC, 5, (s32) sp165, 0);
                    temp_t7_3 = sp110;
                    sp110 = temp_t7_3 + 1;
                    temp_t7_3->w1 = 0xC00;
                    temp_t7_3->w0 = 0xBA000903;
                    break;
                case 2:                             /* switch 5 */
                case 3:                             /* switch 5 */
                case 5:                             /* switch 5 */
                case 7:                             /* switch 5 */
                case 9:                             /* switch 5 */
                    var_t2 = 0x1000;
                    var_t1_2 = 1;
                    switch (D_8004AC88) {           /* switch 6 */
                    case 2:                         /* switch 6 */
                        sp10C = &D_801A3A90;
                        break;
                    case 3:                         /* switch 6 */
                        sp10C = &D_8019A010;
                        break;
                    case 5:                         /* switch 6 */
                        sp10C = &D_801AA940;
                        break;
                    case 7:                         /* switch 6 */
                        var_t1_2 = 0;
                        sp10C = &D_80196010;
                        if ((s32) temp_s0 & 0x200) {
                            var_t2 = 0x1400;
                        }
                        break;
                    case 9:                         /* switch 6 */
                        sp10C = &D_8019F400;
                        break;
                    }
                    var_t0_2 = -1;
                    if (!((s32) temp_s0 & 0x100)) {
                        var_t0_2 = 1;
                    }
                    temp_t8_5 = sp110;
                    sp110 = temp_t8_5 + 1;
                    temp_t8_5->w1 = 0x80000;
                    temp_t8_5->w0 = 0xBA001301;
                    var_s7 = (s32) (var_s7 * var_t2) / 4096;
                    temp_hi = (s32) (D_8004D272 * 8 * var_t0_2) % 360;
                    func_8001C5AC(&sp110, 0, sp10C, 0U, (s32) temp_s0->player, sp120, sp124, sp128, (f32) (temp_hi * var_t1_2), 0.0f, (f32) (temp_hi * (var_t1_2 ^ 1)), (u32) (temp_s0->scale * var_s7 * 2) >> 0xC);
                    temp_t4_6 = sp110;
                    sp110 = temp_t4_6 + 1;
                    temp_t4_6->w1 = 0;
                    temp_t4_6->w0 = 0xBA001301;
                    break;
                }
                break;
            case 0x38:                              /* switch 2 */
                if (D_8004A408 == 0) {
                    sp150 = 0x1000;
                    var_s2 = 0x63;
                    var_s7 = 0x1000;
                    if (temp_s0->character == (D_8004EA9C[0] + 1)) {
                        var_s3 = 0;
                    } else {
                        var_s3 = 1;
                    }
                    temp_t9_5 = var_s3 + 0x12;
                    D_8004EA78 = temp_t9_5;
                    if ((s32) sp188 < 4) {
                        D_8004EA78 = temp_t9_5 + (sp188 * 2);
                        D_8004EA9A = sp188 + 6;
                        func_8001D7E4(D_8004EA78, 0x63U, var_s5, 2, 0);
                        sp188 += 1;
                    }
                    func_80024028(&sp110, temp_s0->palette, 0U);
                    temp_v1_10 = temp_s0->scale;
                    func_8001EC74(&sp110, (s32) temp_s0->screenX / 16, (s32) temp_s0->screenY / 16, (u32) (temp_v1_10 << 0xC) >> 0xC, (u32) (temp_v1_10 << 0xC) >> 0xC, 5, 0, 0);
                    temp_t7_4 = sp110;
                    sp110 = temp_t7_4 + 1;
                    temp_t7_4->w1 = 0xC00;
                    temp_t7_4->w0 = 0xBA000903;
                }
                break;
            case 0x3B:                              /* switch 2 */
                func_8002DCC8(sp120, sp124, sp128, &temp_s0->scale);
                if (((T032Transform21B *)&D_8004A9D8)[temp_s0->model].enabled != 0.0f) {
                    D_8004AA34(&sp114);
                    if (sp114.x > 0) {
                        D_8004AC8E[0] = (s8) sp114.x;
                        D_8004AC92[0] = 0;
                    } else {
                        D_8004AC8E[0] = 0;
                        D_8004AC92[0] = (s8) -sp114.x;
                    }
                    if (sp114.y > 0) {
                        D_8004AC8F = (s8) sp114.y;
                        D_8004AC93 = 0;
                    } else {
                        D_8004AC8F = 0;
                        D_8004AC93 = (s8) -sp114.y;
                    }
                    if (sp114.z > 0) {
                        D_8004AC90 = (s8) sp114.z;
                        D_8004AC94 = 0;
                    } else {
                        D_8004AC90 = 0;
                        D_8004AC94 = (s8) -sp114.z;
                    }
                }
                temp_t5_7 = sp110;
                sp110 = temp_t5_7 + 1;
                temp_t5_7->w1 = 0x80000;
                temp_t5_7->w0 = 0xBA001301;
                temp_t0_4 = temp_s0->model;
                temp_v0_10 = &((T032Transform21B *)&D_8004A9D8)[temp_t0_4];
                func_8001C5AC(&sp110, 0, ((T032Model21B *)&D_8004A998)[temp_t0_4].data, 0U, 0, sp120, sp124, sp128, temp_v0_10->x, temp_v0_10->y, temp_v0_10->z, 0U);
                temp_t4_7 = sp110;
                sp110 = temp_t4_7 + 1;
                temp_t4_7->w1 = 0;
                temp_t4_7->w0 = 0xBA001301;
                if (((T032Transform21B *)&D_8004A9D8)[temp_s0->model].enabled != 0.0f) {
                    D_8004AC8E[0] = 0;
                    D_8004AC8E[1] = 0;
                    D_8004AC8E[2] = 0;
                    D_8004AC92[0] = 0;
                    D_8004AC92[1] = 0;
                    D_8004AC92[2] = 0;
                }
                break;
            case 0x3D:                              /* switch 2 */
                temp_t5_8 = sp110;
                sp110 = temp_t5_8 + 1;
                temp_t5_8->w1 = 0;
                temp_t5_8->w0 = 0xFA000100;
                temp_t7_5 = sp110;
                sp110 = temp_t7_5 + 1;
                temp_t7_5->w1 = 0;
                temp_t7_5->w0 = 0xFB000000;
                D_8004EA78 = 0x20;
                D_8004EA9A = 0;
                temp_t1_3 = temp_s0->image;
                temp_s0->flags = 0;
                if (temp_t1_3 == 0x77) {
                    var_s2 = 0x60;
                }
                if ((var_s2 != D_8004EABA) || (D_8004EABB != var_s5)) {
                    sp78 = (s32) var_s5;
                    func_8001D7E4(D_8004EA78, (u8) var_s2, var_s5, 1, (s32) temp_t1_3);
                    D_8004EABA = (u8) var_s2;
                    D_8004EABB = var_s5;
                } else {
                    temp_t8_6 = D_8004EABC ^ 1;
                    temp_v0_11 = temp_t8_6 & 0xFF;
                    D_8004EABC = temp_t8_6;
                    D_8004CED0[32].unk0 = (void *) ((temp_v0_11 * 0x7080) + &D_80350000);
                    D_8004CED0[32].data = (void *) ((temp_v0_11 * 0x3840) + &D_8035E100);
                }
                if (var_s5 != 0x77) {
                    temp_v1_11 = temp_s0->scale;
                    func_8001EC74(&sp110, (s32) temp_s0->screenX / 16, (s32) temp_s0->screenY / 16, (u32) (temp_v1_11 * var_s7) >> 0xC, (u32) (temp_v1_11 * sp150) >> 0xC, (s32) D_8004AC89, 0, (s32) D_8004AC8A);
                }
                temp_s0->z = sp174;
                func_8002E08C(temp_s0, &sp114);
                temp_v0_12 = sp110;
                sp110 = temp_v0_12 + 1;
                temp_v0_12->w1 = 0;
                temp_v0_12->w0 = 0xE7000000;
                temp_t6_6 = sp110;
                sp110 = temp_t6_6 + 1;
                temp_t6_6->w1 = 0;
                temp_t6_6->w0 = 0xFA000100;
                temp_t9_6 = sp110;
                sp110 = temp_t9_6 + 1;
                temp_t9_6->w1 = 0;
                temp_t9_6->w0 = 0xFB000000;
                temp_v1_12 = temp_s0->scale;
                func_8001EC74(&sp110, (s32) temp_s0->screenX / 16, (s32) temp_s0->screenY / 16, (u32) (temp_v1_12 * var_s7) >> 0xC, (u32) (temp_v1_12 * sp150) >> 0xC, (s32) ((u8 *)&D_8004CED0[D_8004EA78].flags)[0], 0, 0);
                break;
            }
        }
        var_fp_4 -= 1;
    } while (var_fp_4 >= 0);
    sp154 = var_s7;
    sp164 = var_s5;
    sp162 = var_s3;
    sp158 = var_s2;
    *arg0 = sp110;
}
