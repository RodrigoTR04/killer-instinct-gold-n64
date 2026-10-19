/* DRAFT. Remaining diff: 802 differing words; 3264/3340 bytes */
typedef struct { u32 w0,w1; } T024ParticleCommand;
typedef struct { float x,y,z; s16 speed,timer; } T024RenderParticle;
typedef struct { float x,y,z; } T024ParticleOrigin;
typedef struct { u32 flags; void *texture; s16 x,y,width,height,stride; u8 pad[10]; } T024ParticleSprite;
extern T024RenderParticle D_80061538[][20];
extern T024ParticleOrigin D_800614D8[];

extern u8 D_80061520[],D_80061CB8[];
extern u8 D_80048080[];
void func_80028A00(T024ParticleCommand **,s32);
void func_8002DCC8(float,float,float,u32 *);
void func_8002DDD4(float,float,float,s32 *,s32 *);
void func_8001BB64(void *);
u32 osVirtualToPhysical(void *);

extern u8 D_8004AA28;
extern s32 D_8004EA78;
extern f32 D_8006152C;
extern f32 D_80061530;
extern u8 D_80061CD4;
extern s16 D_80061CD6;

void func_80028A00(T024ParticleCommand **displayList, s32 group) {
    s32 spDC;
    s32 spD8;
    s32 spD4;
    s32 spD0;
    s32 spCC;
    u32 spC4;
    u8 *sp7C;
    T024ParticleCommand *temp_a0;
    T024ParticleCommand *temp_a2_2;
    T024ParticleCommand *temp_t1;
    T024ParticleCommand *temp_v0_5;
    T024ParticleCommand *temp_v1;
    T024ParticleCommand *temp_v1_12;
    T024ParticleCommand *temp_v1_13;
    T024ParticleCommand *temp_v1_14;
    T024ParticleCommand *temp_v1_15;
    T024ParticleCommand *temp_v1_2;
    T024ParticleCommand *temp_v1_3;
    T024ParticleCommand *temp_v1_4;
    T024ParticleCommand *temp_v1_5;
    T024ParticleCommand *temp_v1_7;
    T024ParticleCommand *temp_v1_8;
    T024ParticleOrigin *temp_v0_3;
    T022Sprite *temp_v0;
    T022Sprite *temp_v0_4;
    T024RenderParticle *particle;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 var_f10;
    f32 var_f16;
    f32 var_f18;
    f32 var_f18_2;
    f32 var_f4;
    f32 var_f4_2;
    f32 var_f8;
    s16 temp_t0;
    s16 temp_t2;
    s16 var_a3;
    s32 temp_a2;
    s32 temp_t5;
    s32 temp_t7;
    s32 temp_t9;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v1_10;
    s32 temp_v1_11;
    s32 temp_v1_6;
    s32 var_a1;
    s32 var_a1_3;
    s32 var_a2_2;
    s32 var_fp;
    u32 temp_a0_2;
    u32 temp_v1_9;
    u32 var_a1_2;
    u32 var_a2;
    u8 *temp_v0_2;

    if (D_80061CD4 == 0xFF) {
        D_80061CD6 = 1;
    }
    D_8004EA78 = 0xA;
    temp_v1 = *displayList;
    *displayList = temp_v1 + 8;
    temp_v1->w0 = 0x06000000;
    temp_v1->w1 = (u32) D_80048080;
    temp_v0 = &D_8004CED0[D_8004EA78];
    temp_t0 = temp_v0->width2;
    temp_t2 = temp_v0->height;
    temp_t5 = (temp_t0 + 7) & 0xFFF8;
    spD0 = temp_v0->width - 2;
    temp_v1_2 = *displayList;
    *displayList = temp_v1_2 + 8;
    temp_v1_2->w0 = 0xF5700000;
    temp_v1_2->w1 = 0x01080200;
    temp_v1_3 = *displayList;
    *displayList = temp_v1_3 + 8;
    temp_v1_3->w1 = 0x03080200;
    temp_v1_3->w0 = ((((s32) (temp_t0 + 7) >> 3) & 0x1FF) << 9) | 0xF5680000;
    temp_v1_4 = *displayList;
    *displayList = temp_v1_4 + 8;
    temp_v1_4->w0 = 0xF2000000;
    temp_v1_4->w1 = ((((temp_t5 - 1) * 4) & 0xFFF) << 0xC) | 0x03000000 | (((temp_t2 - 1) * 4) & 0xFFF);
    temp_v1_5 = *displayList;
    *displayList = temp_v1_5 + 8;
    temp_v1_5->w0 = 0xFD900000;
    spD4 = (s32) temp_t0;
    spCC = (s32) temp_t2;
    temp_v1_5->w1 = osVirtualToPhysical(D_8004CED0[D_8004EA78].data);
    temp_a0 = *displayList;
    *displayList = temp_a0 + 8;
    var_a1 = 0x7FF;
    temp_a2 = ((s32) ((temp_t5 * ((0x1000 / temp_t5) & 0xFFFE)) + 1) >> 1) - 1;
    temp_a0->w0 = 0xF3000000;
    if (temp_a2 < 0x7FF) {
        var_a1 = temp_a2;
    }
    temp_a0->w1 = ((var_a1 & 0xFFF) << 0xC) | 0x01000000;
    temp_v0_2 = &D_80061520[group];
    var_fp = 0;
    if ((s32) *temp_v0_2 > 0) {
        particle = D_80061538[group];
        sp7C = temp_v0_2;
        do {
            if (particle->timer != 0xA) {
                temp_v0_3 = &D_800614D8[group];
                temp_f24 = particle->z + temp_v0_3->z;
                temp_f20 = particle->x + temp_v0_3->x;
                temp_f22 = particle->y + temp_v0_3->y;
                func_8002DCC8(temp_f20, temp_f22, temp_f24, &spC4);
                var_f8 = (f32) spC4;
                if ((s32) spC4 < 0) {
                    var_f8 += 4294967296.0f;
                }
                spC4 = (u32) ((((particle->y / D_80061530) / 20.0f) + 1.0f) * var_f8);
                func_8002DDD4(temp_f20, temp_f22, temp_f24, &spDC, &spD8);
                temp_v0_4 = &D_8004CED0[D_8004EA78];
                temp_v1_6 = (spDC >> 4) - (temp_v0_4->halfWidth * spC4);
                temp_t7 = (spD8 >> 4) - (temp_v0_4->height * spC4);
                spD8 = temp_t7;
                spD8 = (temp_v0_4->halfHeight * spC4) + temp_t7;
                if (spC4 < 0x2BCU) {
                    spC4 = 0x2BC;
                }
                spDC = temp_v1_6;
                if ((spD4 * -0x1000) < temp_v1_6) {
                    spDC = temp_v1_6;
                    if (spD8 > 0) {
                        spDC = temp_v1_6;
                        if ((temp_v1_6 < ((spD4 << 0xC) + 0x140000)) && (spD8 < 0xF0000) && (spC4 >= 0x19AU)) {
                            var_a3 = particle->timer;
                            if (var_a3 >= 0xC1) {
                                var_a3 = 0xC0;
                            }
                            temp_v1_7 = *displayList;
                            *displayList = temp_v1_7 + 8;
                            temp_v1_7->w1 = 0;
                            temp_v1_7->w0 = 0xE7000000;
                            temp_f2 = particle->y;
                            if (temp_f2 < D_8006152C) {
                                temp_v0_5 = *displayList;
                                *displayList = temp_v0_5 + 8;
                                temp_v0_5->w0 = 0xFA000100;
                                temp_f2_2 = particle->y;
                                var_f18 = (f32) D_80061CB8[2];
                                if ((s32) D_80061CB8[2] < 0) {
                                    var_f18 += 4294967296.0f;
                                }
                                var_f10 = (f32) D_80061CB8[0];
                                if ((s32) D_80061CB8[0] < 0) {
                                    var_f10 += 4294967296.0f;
                                }
                                var_f18_2 = (f32) D_80061CB8[1];
                                if ((s32) D_80061CB8[1] < 0) {
                                    var_f18_2 += 4294967296.0f;
                                }
                                temp_v0_5->w1 = (((u32) (var_f18 + (((f32) (D_80061CB8[5] - D_80061CB8[2]) * temp_f2_2) / D_8006152C)) & 0xFF) << 8) | ((u32) ((((f32) (D_80061CB8[3] - D_80061CB8[0]) * temp_f2_2) / D_8006152C) + var_f10) << 0x18) | (((u32) ((((f32) (D_80061CB8[4] - D_80061CB8[1]) * temp_f2_2) / D_8006152C) + var_f18_2) & 0xFF) << 0x10) | (var_a3 & 0xFF);
                            } else if (temp_f2 < (D_8006152C * 2.0f)) {
                                temp_a2_2 = *displayList;
                                *displayList = temp_a2_2 + 8;
                                temp_a2_2->w0 = 0xFA000100;
                                temp_f2_3 = particle->y - D_8006152C;
                                var_f4 = (f32) D_80061CB8[5];
                                if ((s32) D_80061CB8[5] < 0) {
                                    var_f4 += 4294967296.0f;
                                }
                                var_f16 = (f32) D_80061CB8[3];
                                if ((s32) D_80061CB8[3] < 0) {
                                    var_f16 += 4294967296.0f;
                                }
                                var_f4_2 = (f32) D_80061CB8[4];
                                if ((s32) D_80061CB8[4] < 0) {
                                    var_f4_2 += 4294967296.0f;
                                }
                                temp_a2_2->w1 = (((u32) (var_f4 + (((f32) (D_80061CB8[8] - D_80061CB8[5]) * temp_f2_3) / D_8006152C)) & 0xFF) << 8) | ((u32) ((((f32) (D_80061CB8[6] - D_80061CB8[3]) * temp_f2_3) / D_8006152C) + var_f16) << 0x18) | (((u32) ((((f32) (D_80061CB8[7] - D_80061CB8[4]) * temp_f2_3) / D_8006152C) + var_f4_2) & 0xFF) << 0x10) | (var_a3 & 0xFF);
                            } else {
                                temp_v1_8 = *displayList;
                                *displayList = temp_v1_8 + 8;
                                temp_v1_8->w0 = 0xFA000100;
                                temp_v1_8->w1 = (D_80061CB8[8] << 8) | (D_80061CB8[6] << 0x18) | (D_80061CB8[7] << 0x10) | (var_a3 & 0xFF);
                            }
                            temp_t1 = *displayList;
                            var_a2 = 0;
                            *displayList = temp_t1 + 8;
                            temp_v0_6 = 0xA - D_8004AA28;
                            var_a1_2 = 0;
                            temp_a0_2 = (u32) (spDC + ((spD0 + 2) * spC4)) >> temp_v0_6;
                            if (temp_a0_2 != 0) {
                                var_a2 = temp_a0_2;
                            }
                            temp_v1_9 = (u32) (spD8 + (spCC * spC4)) >> temp_v0_6;
                            if (temp_v1_9 != 0) {
                                var_a1_2 = temp_v1_9;
                            }
                            temp_t1->w0 = (var_a1_2 & 0xFFF) | 0xE4000000 | ((var_a2 & 0xFFF) << 0xC);
                            temp_v0_7 = 0xA - D_8004AA28;
                            temp_v1_10 = spDC >> temp_v0_7;
                            if (temp_v1_10 > 0) {
                                var_a2_2 = temp_v1_10;
                            } else {
                                var_a2_2 = 0;
                            }
                            temp_v1_11 = spD8 >> temp_v0_7;
                            if (temp_v1_11 > 0) {
                                var_a1_3 = temp_v1_11;
                            } else {
                                var_a1_3 = 0;
                            }
                            temp_t1->w1 = (var_a1_3 & 0xFFF) | 0x03000000 | ((var_a2_2 & 0xFFF) << 0xC);
                            temp_v1_12 = *displayList;
                            *displayList = temp_v1_12 + 8;
                            temp_v1_12->w0 = 0xB3000000;
                            temp_v1_12->w1 = (((s32) (32.0f - ((((f32) spD8 / 4096.0f) - (f32) (spD8 >> 0xC)) * 32.0f)) - 0) & 0xFFFF) | (0 * -0x10000);
                            temp_v1_13 = *displayList;
                            *displayList = temp_v1_13 + 8;
                            temp_v1_13->w0 = 0xB2000000;
                            temp_t9 = ((u32) (0x1000 << (0xA - D_8004AA28)) / spC4) & 0xFFFF & 0xFFFF;
                            temp_v1_13->w1 = (temp_t9 << 0x10) | temp_t9;
                        }
                    }
                }
            }
            var_fp += 1;
            particle += 0x10;
        } while (var_fp < (s32) *sp7C);
    }
    temp_v1_14 = *displayList;
    *displayList = temp_v1_14 + 8;
    temp_v1_14->w1 = 0;
    temp_v1_14->w0 = 0xE7000000;
    temp_v1_15 = *displayList;
    *displayList = temp_v1_15 + 8;
    temp_v1_15->w1 = 0x80000;
    temp_v1_15->w0 = 0xBA001301;
    func_8001BB64(displayList);
}
