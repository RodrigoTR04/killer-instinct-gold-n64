/* T-054 DRAFT: 234 relocation-masked positional words differ; 940 emitted bytes. See T-054/REPORT.md. */

typedef struct { u32 w0,w1; } T032Gfx27E;
typedef struct { s16 x,y; u8 pad[12]; } T032Vertex27E;
typedef struct { T032Vertex27E v[4]; } T032Quad27E;
typedef struct { u8 pad[0x54]; u8 owner; u8 pad55[0x13]; s32 x,y,scale; u8 pad74[0x60]; u8 age; u8 padD5[3]; s16 dx,dy; u8 tail[0x24]; } T032Actor27E;
extern T032Actor27E D_801D3430[];
extern T032Vertex27E D_80047EA0[2][3][4];
extern u8 D_80044A24,D_80061CDC,D_80061CE0[],D_80061D20[],D_4AC40[];
void func_80027E1C(T032Gfx27E **arg0, T032Actor27E *arg1) {
    f32 temp_f12;
    f32 temp_f16;
    f32 temp_f16_2;
    f32 temp_f16_3;
    f32 var_f0;
    f32 var_f12;
    f32 var_f14;
    f32 var_f2;
    s32 temp_f10;
    s32 temp_t2;
    u8 temp_v0;
    s32 var_t1;
    T032Quad27E *temp_t3;
    T032Actor27E *temp_t4;
    T032Gfx27E *temp_v0_10;
    T032Gfx27E *temp_v0_11;
    T032Gfx27E *temp_v0_12;
    T032Gfx27E *temp_v0_13;
    T032Gfx27E *temp_v0_2;
    T032Gfx27E *temp_v0_3;
    T032Gfx27E *temp_v0_4;
    T032Gfx27E *temp_v0_5;
    T032Gfx27E *temp_v0_6;
    T032Gfx27E *temp_v0_7;
    T032Gfx27E *temp_v0_8;
    T032Gfx27E *temp_v0_9;

    if ((s32) D_80061CDC < 3) {
        temp_v0 = arg1->owner;
        temp_t4 = &D_801D3430[temp_v0];
        temp_t2 = temp_t4->scale;
        var_t1 = arg1->age;
        var_f12 = (f32) arg1->x;
        var_f14 = (f32) arg1->y;
        var_f0 = (f32) temp_t4->x + (f32) (arg1->dx * temp_t2);
        var_f2 = (f32) temp_t4->y - (f32) (arg1->dy * temp_t2);
        if ((s32) var_t1 < 0x15) {
            temp_f16 = (f32) var_t1;
            var_f12 = (((var_f12 - var_f0) * temp_f16) / 21.0f) + var_f0;
            var_f14 = (((var_f14 - var_f2) * temp_f16) / 21.0f) + var_f2;
        } else if ((s32) var_t1 >= 0x51) {
            if ((s32) var_t1 >= 0x7D) {
                var_t1 = 0x7C;
            }
            temp_f16_2 = (f32) (s16) (var_t1 - 0x50);
            var_f0 += ((var_f12 - var_f0) * temp_f16_2) / 44.0f;
            var_f2 += ((var_f14 - var_f2) * temp_f16_2) / 44.0f;
        }
        temp_t3 = (T032Quad27E *)&D_80047EA0[D_80044A24][D_80061CDC][0];
        temp_f12 = var_f12 / 65536.0f;
        temp_t3->v[0].x = (s16) (s32) (var_f0 / 65536.0f);
        temp_t3->v[0].y = (s16) (s32) (var_f2 / 65536.0f);
        temp_f16_3 = (f32) ((s32) ((&D_801D3430[temp_v0 ^ 1])->scale * 0xA) / 4096);
        temp_f10 = (s32) (var_f14 / 65536.0f);
        temp_t3->v[1].y = (s16) temp_f10;
        temp_t3->v[2].y = (s16) temp_f10;
        temp_t3->v[3].y = (s16) temp_f10;
        temp_t3->v[2].x = (s16) (s32) temp_f12;
        temp_t3->v[1].x = (s16) (s32) (temp_f12 - temp_f16_3);
        temp_t3->v[3].x = (s16) (s32) (temp_f16_3 + temp_f12);
        temp_v0_2 = (*arg0)++;
        temp_v0_2->w0 = 0x01030040; temp_v0_2->w1 = (u32)&D_80061D20;
        temp_v0_3 = (*arg0)++;
        temp_v0_3->w0 = 0x01060040; temp_v0_3->w1 = (u32)&D_80061CE0;
        temp_v0_4 = (*arg0)++;
        temp_v0_4->w0 = 0x04300040;
        temp_v0_4->w1 = (u32) (&D_80047EA0[D_80044A24][D_80061CDC][0]);
        temp_v0_5 = (*arg0)++;
        temp_v0_5->w0 = 0xBB000000; temp_v0_5->w1 = 0;
        temp_v0_6 = (*arg0)++;
        temp_v0_6->w0 = 0xE7000000; temp_v0_6->w1 = 0;
        temp_v0_7 = (*arg0)++;
        temp_v0_7->w0 = 0xB900031D; temp_v0_7->w1 = (u32)0x504240;
        temp_v0_8 = (*arg0)++;
        temp_v0_8->w0 = 0xFCFFFFFF; temp_v0_8->w1 = (u32)0xFFFE793C;
        temp_v0_9 = (*arg0)++;
        temp_v0_9->w0 = 0xB6000000; temp_v0_9->w1 = (u32)0x3000;
        temp_v0_10 = (*arg0)++;
        temp_v0_10->w0 = 0xBF000000; temp_v0_10->w1 = (u32)0xA14;
        temp_v0_11 = (*arg0)++;
        temp_v0_11->w0 = 0xBF000000; temp_v0_11->w1 = (u32)0x1E14;
        temp_v0_12 = (*arg0)++;
        temp_v0_12->w0 = 0xBD000000; temp_v0_12->w1 = 0;
        temp_v0_13 = (*arg0)++;
        temp_v0_13->w0 = 0x01030040; temp_v0_13->w1 = (u32)&D_4AC40;
        D_80061CDC += 1;
    }
}
