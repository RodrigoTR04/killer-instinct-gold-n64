/* T-140 DRAFT: 81 differing words, 392/392 bytes in declarations context. */
typedef struct { u32 w0,w1; } T032Gfx267;
typedef struct { s16 id,scale,x,y; } T032Effect267;
typedef struct { s32 id; void *data; s16 halfW,halfH,w,h,w2,h2; u8 pad[4]; s16 flags; u8 tail[2]; } T032Sprite267;
typedef struct { u16 halfW,halfH,w,h; } T032Size267;
extern T032Effect267 D_801D73C8[];
extern T032Sprite267 D_8004CED0[];
extern T032Size267 D_80061368[];
extern s32 D_800612D8[],D_8004EA78;
extern u8 D_80047BF0[];
extern void func_8001EC74(T032Gfx267 **,s32,s32,s32,s32,s32,s32,s32);
void func_80026738(T032Gfx267 **dl) {
    T032Effect267 *effect;
    T032Sprite267 *sprite;
    T032Size267 *size;
    T032Gfx267 *p;
    u16 scale,width;
    u8 kind;
    s32 x,y;
    s32 *currentSlot = &D_8004EA78;
    if (D_801D73C8[0].id != 0) {
        *currentSlot=15;
        if (D_801D73C8[0].id != 0) {
            effect=D_801D73C8;
            do {
                kind=D_80047BF0[effect->id-1]; scale=effect->scale;
                x=effect->x>>7; y=(effect->y>>8)+4; effect++;
                if (kind>=19) scale=0x1000;
                size=&D_80061368[kind]; width=size->w;
                sprite=&D_8004CED0[*currentSlot];
                sprite->halfW=size->halfW; sprite->halfH=size->halfH;
                sprite->w=width; sprite->w2=width; sprite->h=size->h;
                sprite->id=D_800612D8[kind];
                p=(*dl)++; p->w1=0; p->w0=0xE7000000;
                func_8001EC74(dl,x<<12,y<<12,scale,scale,8,0,0);
            } while (effect->id != 0);
        }
    }
}
