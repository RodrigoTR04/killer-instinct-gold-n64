/* DRAFT. Remaining diff: 101 positional words differ; 440/464 bytes */
typedef struct { u32 w0,w1; } T032Gfx24B;
typedef struct { u8 pad[12]; f32 x,y,z; u8 tail[24]; } T032Pos24B;
extern T032Pos24B D_8004A450[];
extern u8 D_471440[],D_472FB0[],D_80046130[];
extern u8 D_80044A24;
extern f32 D_8004AC84,D_800695DC,D_800695E0;
extern void guTranslate(void *,f32,f32,f32),guRotateRPY(void *,f32,f32,f32),guScale(void *,f32,f32,f32);
void func_80024B0C(T032Gfx24B **dl,s32 player) {
    T032Pos24B *pos = &D_8004A450[player ^ 1];
    u8 *base = (u8 *)(D_472FB0 - D_471440 + 0x8023D400);
    T032Gfx24B *p;
    f32 scale;
    guTranslate(base + D_80044A24 * 192,pos->x,pos->y,pos->z);
    guRotateRPY(base + (D_80044A24 * 3 + 1) * 64,0.0f,-D_800695DC,D_800695E0);
    scale = 230.0f / D_8004AC84;
    guScale(base + (D_80044A24 * 3 + 2) * 64,scale,scale,scale);
    p = (*dl)++; p->w0 = 0x01040040; p->w1 = (u32)(base + D_80044A24 * 192);
    p = (*dl)++; p->w0 = 0x01000040; p->w1 = (u32)(base + (D_80044A24 * 3 + 1) * 64);
    p = (*dl)++; p->w0 = 0x01000040; p->w1 = (u32)(base + (D_80044A24 * 3 + 2) * 64);
    p = (*dl)++; p->w1 = (u32)D_80046130; p->w0 = 0x06000000;
}
