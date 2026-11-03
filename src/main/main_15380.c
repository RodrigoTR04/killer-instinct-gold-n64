#include "common.h"

typedef struct { u16 *pixels; u8 *alpha; s16 halfW,halfH,w,h,w2,h2; u8 pad[4]; s16 flags; u8 tail[2]; } T032Sprite25D;
extern T032Sprite25D D_8004CED0[];

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_15380/func_80024CE0.s")

extern void func_8001D768(s32, s32 *);
extern s32 D_800470C0[], D_80046EF0[], D_8011E670[], D_8011E990[];
extern u16 D_80061490[2];
extern u8 D_80061494[2], D_8004D26C;
void func_80025354(void) {
    func_8001D768(6, D_800470C0);
    func_8001D768(7, D_80046EF0);
    func_8001D768(8, D_8011E670);
    func_8001D768(9, D_8011E990);
    D_80061490[0] = 0; D_80061490[1] = 0;
    D_80061494[0] = 0; D_80061494[1] = 0;
    D_8004D26C = 0;
}


typedef struct { u32 w0, w1; } T032Gfx269AC;
typedef struct { u8 pad[0x56]; u16 health; u8 pad58[0x37]; u8 flash; u8 tail[0x70]; } T032HudActor253;
typedef struct { s16 halfW; u8 tail[26]; } T032Half253;
extern T032HudActor253 D_801D3430[];
extern T032Half253 D_8004CED8[];
extern s32 D_8004EA78,D_801D8760;
extern s32 *D_80047D38[];
extern u8 D_80047D60[],D_801D5D50[];
extern u8 D_8004A40C,D_8004D26C,D_801D87FE,D_801D3235,D_801D3335;
extern void func_8001D768(s32,s32 *),func_800257FC(u8,u16,u8,u8);
extern void func_8001EC74(T032Gfx269AC **,s32,s32,s32,s32,s32,s32,s32);
extern void func_80025FC4(T032Gfx269AC **,s32,s32,u8,u8),func_80026738(T032Gfx269AC **),func_800269AC(T032Gfx269AC **);
void func_800253D0(T032Gfx269AC **arg0)
    {
    T032Gfx269AC *temp_v0;
    T032Gfx269AC *temp_v0_10;
    T032Gfx269AC *temp_v0_2;
    T032Gfx269AC *temp_v0_3;
    T032Gfx269AC *temp_v0_4;
    T032Gfx269AC *temp_v0_5;
    T032Gfx269AC *temp_v0_6;
    T032Gfx269AC *temp_v0_7;
    T032Gfx269AC *temp_v0_8;
    T032Gfx269AC *temp_v0_9;
    if ((D_8004A40C == 0) && (D_801D87FE == 0)) { D_8004D26C += 1; }
    temp_v0 = (*arg0)++;
    temp_v0->w0 = 0x06000000; temp_v0->w1 = (u32)&D_80047D60;
    D_8004EA78 = 4;
    func_800257FC((u8)D_8004EA78, D_801D3430[0].health, 0, D_801D3430[0].flash);
    func_8001EC74(arg0, 0x4F000, 0x16000, 0x1000, 0x1000, 0, 0, 0);
    D_8004EA78 = 5;
    func_800257FC((u8)D_8004EA78, D_801D3430[1].health, 1, D_801D3430[1].flash); temp_v0_2 = (*arg0)++;
    temp_v0_2->w0 = 0xE7000000; temp_v0_2->w1 = 0;
    func_8001EC74(arg0, 0xF1000, 0x16000, 0x1000, 0x1000, 0, 0, 0);
    if ((D_801D5D50[2] != 0) || ((s32) D_801D5D50[1] >= 6) || ((D_801D5D50[0] & 8) != 8))
    {
    temp_v0_3 = (*arg0)++;
    temp_v0_3->w0 = 0xE7000000; temp_v0_3->w1 = 0;
    temp_v0_4 = (*arg0)++;
    temp_v0_4->w0 = 0xFA000100; temp_v0_4->w1 = (u32)-1;
    temp_v0_5 = (*arg0)++;
    temp_v0_5->w0 = 0xFB000000; temp_v0_5->w1 = (u32)0xFF80;
    D_8004EA78 = 6;
    func_8001D768(D_8004EA78, D_80047D38[D_801D5D50[2]]);
    func_8001EC74(arg0, 0x9A000, 0x19000, 0x1000, 0x1000, 7, 0, 0);
    D_8004EA78 = 7;
    func_8001D768(D_8004EA78, D_80047D38[D_801D5D50[1]]);
    temp_v0_6 = (*arg0)++; temp_v0_6->w1 = 0;
    temp_v0_6->w0 = 0xE7000000;
    func_8001EC74(arg0, 0xAA000, 0x19000, 0x1000, 0x1000, 7, 0, 0); }
    temp_v0_7 = (*arg0)++;
    temp_v0_7->w1 = 0;
    temp_v0_7->w0 = 0xE7000000;
    temp_v0_8 = (*arg0)++;
    temp_v0_8->w0 = 0xFA000100; temp_v0_8->w1 = (u32)0xFFFF00FF;
    temp_v0_9 = (*arg0)++;
    temp_v0_9->w0 = 0xFB000000; temp_v0_9->w1 = (u32)0xA00000FF;
    D_8004EA78 = 8;
    func_8001EC74(arg0, ((-D_8004CED8[D_8004EA78].halfW) * 0x1000) + 0x8F000, 0x23000, 0x1000, 0x1000, 7, 0, 0);
    temp_v0_10 = (*arg0)++;
    temp_v0_10->w0 = 0xE7000000; temp_v0_10->w1 = 0;
    D_8004EA78 = 9;
    func_8001EC74(arg0, (D_8004CED8[D_8004EA78].halfW << 0xC) + 0xB1000, 0x23000, 0x1000, 0x1000, 7, 0, 0); func_80025FC4(arg0, 0x14, 0x1C, 0, (s32) D_801D3235);
    func_80025FC4(arg0, 0xF2, 0x1C, 1, (s32) D_801D3335);
    func_80026738(arg0);
    func_800269AC(arg0);
    if (D_8004A40C == 0)
    {
    D_801D8760 = 0;
    }
    }


#pragma GLOBAL_ASM("asm/nonmatchings/main/main_15380/func_800257FC.s")

extern s32 D_8004EA78;
typedef struct { u8 value[13]; } T032Height13;
typedef struct { u8 value[14]; } T032Height14;
extern T032Height13 D_80047DAC;
extern T032Height14 D_80047DBC;
void func_80025D58(s32 x, s32 color, s32 alpha, s32 kind) {
    s32 y;
    s32 pixelXor;
    s32 alphaXor;
    s32 height;
    T032Height13 heights;
    T032Height14 otherHeights;
    heights = D_80047DAC;
    otherHeights = D_80047DBC;
    height = (kind == 0 ? heights.value[x-6] : otherHeights.value[x-111]);
    for (y=10; y < height + 10; y++) {
        if ((y & 1) == 1) { alphaXor=4; pixelXor=2; }
        else { alphaXor=0; pixelXor=0; }
        D_8004CED0[D_8004EA78].pixels[(y * D_8004CED0[D_8004EA78].w2 + x) ^ pixelXor]=color;
        D_8004CED0[D_8004EA78].alpha[(y * ((D_8004CED0[D_8004EA78].w2+7)&0xFFF8) + x) ^ alphaXor]=alpha;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_15380/func_80025FC4.s")

typedef struct { u16 halfW, halfH, w, h; } T032Size268;
extern T032Size268 D_80061368[];
extern s32 D_800612D8[];

/* Effect list: four halfwords per entry (icon id, scale, x, y), terminated by a zero id. */
extern s16 D_801D73C8[];
extern u8 D_80047BF0[];
void func_80026738(T032Gfx269AC **dl)
{
    T032Size268 *size;
    T032Gfx269AC *p;
    s32 scale;
    u32 width;
    u8 kind;
    s32 x;
    s32 y;
    s32 i = 0;
    if (D_801D73C8[0] != 0)
    {
        D_8004EA78 = 15;
        while (D_801D73C8[i] != 0)
        {
            kind = D_80047BF0[D_801D73C8[i] - 1];
            scale = (u16)D_801D73C8[i + 1];
            x = (u16)D_801D73C8[i + 2] >> 7;
            y = ((u16)D_801D73C8[i + 3] >> 8) + 4;
            i += 4;
            if (kind >= 19)
            {
                scale = 0x1000;
            }
            size = &D_80061368[kind];
            D_8004CED0[D_8004EA78].halfW = size->halfW;
            D_8004CED0[D_8004EA78].halfH = size->halfH;
            width = size->w;
            D_8004CED0[D_8004EA78].w = width;
            D_8004CED0[D_8004EA78].w2 = width;
            D_8004CED0[D_8004EA78].h = size->h;
            D_8004CED0[D_8004EA78].pixels = (u16 *)D_800612D8[kind];
            p = (*dl)++;
            p->w1 = 0;
            p->w0 = 0xE7000000;
            func_8001EC74(dl, x << 12, y << 12, scale, scale, 8, 0, 0);
        }
    }
}

/* Resource header: little-endian 32-bit entry offsets start at +8. */
typedef struct { u8 byte[4]; } T032Offset;
extern u8 D_80047C38[];
extern void func_800238C4(u8 *, void *);
void func_800268C0(u8 *base, s32 index, s32 id, s32 slot)
{
    T032Offset *offsets;
    D_8004CED0[D_8004EA78].pixels = (u16 *)id;
    offsets = (T032Offset *)(base + 8) + index;
    func_800238C4(base + offsets->byte[0] + (offsets->byte[1] << 8) + (offsets->byte[2] << 16) + (offsets->byte[3] << 24), D_80047C38);
    D_80061368[slot].halfW = D_8004CED0[D_8004EA78].halfW;
    D_80061368[slot].halfH = D_8004CED0[D_8004EA78].halfH;
    D_80061368[slot].w = D_8004CED0[D_8004EA78].w2;
    D_80061368[slot].h = D_8004CED0[D_8004EA78].h;
    D_800612D8[slot] = id;
}

extern void func_8001EC74(T032Gfx269AC **, s32, s32, s32, s32, s32, s32, s32);
extern s32 D_8004EA78, D_801D8760, D_801D8764, D_801D8768;
extern u8 D_801D5D50[];
void func_800269AC(T032Gfx269AC **dl)
{
    T032Gfx269AC *environment;
    T032Gfx269AC *p;
    T032Gfx269AC *primitive;
    if (D_801D8760)
    {
        if ((D_801D5D50[2] == 0) && (D_801D5D50[1] == 0))
        {
            D_8004EA78 = 30;
        }
        else
        {
            D_8004EA78 = 29;
        }
        p = (*dl)++; p->w1 = 0; p->w0 = 0xE7000000;
        primitive = (*dl)++; primitive->w0 = 0xFA000100; primitive->w1 = 255;
        environment = (*dl)++; p = environment; p->w0 = 0xFB000000; p->w1 = 0;
        func_8001EC74(dl, D_801D8760 * 16, D_801D8764 * 16, D_801D8768, D_801D8768, 8, 0, 0);
    }
}
